/************************************************************************/
/* 使得一个消费者专门取奇数并求奇数之和，                        */
/* 另外一个消费者专门取偶数并求偶数之和                          */
/************************************************************************/

#ifndef _MSC_VER
#include <sys/mman.h>
#include <sys/types.h>
#include <linux/sem.h>
#include <unistd.h>
#endif

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

#define MAXSEM 5

#ifdef _MSC_VER
#include <Windows.h>

#define sleep(x) Sleep(x * 1000)

struct sembuf
{
    int sem_num;
    int sem_op;
    int sem_flg;
};
union semun
{
    int val;
    void *buf;
    USHORT *array;
    void *__buf;
    void *__pad;
};
enum { SEM_UNDO, SETVAL, PROT_READ, PROT_WRITE, MAP_SHARED, MAP_ANONYMOUS, IPC_PRIVATE, IPC_CREAT };

int fork() { return 0; }
void semop(int, struct sembuf*, int) {}
int semget(int, int, int) { return 0; }
int semctl(int, int, int, union semun) { return 0; }
void* mmap(void*, int, int, int, int, int ){ return 0; }

#endif

//声明三个信号灯ID
int fullid;
int emptyid;
int mutxid;

int main()
{
    struct sembuf P,V;
    union semun arg;
    //声明共享主存
    int *array;
    int *sum;
    int *set;
    int *get;
    int arraysize;

    //映射共享主存。该主存区可以被进程共享。
    arraysize = sizeof(int) * MAXSEM;
    array = (int *)mmap(NULL, arraysize,  PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    sum  = (int *)mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    get   = (int *)mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    set   = (int *)mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    *sum = 0;
    *get = 0;
    *set = 0;

    //生成信号灯
    fullid  = semget(IPC_PRIVATE ,1, IPC_CREAT|00666);
    emptyid = semget(IPC_PRIVATE ,1, IPC_CREAT|00666);
    mutxid  = semget(IPC_PRIVATE ,1, IPC_CREAT|00666);

    //为信号灯赋值
    arg.val = 0;
    if(semctl(fullid , 0 , SETVAL , arg) == -1)
        perror("semctl setval error");

    arg.val = MAXSEM;
    if(semctl(emptyid , 0 ,SETVAL , arg) == -1)
        perror("semctl setval error");

    arg.val = 1;
    if(semctl(mutxid , 0 ,SETVAL , arg) == -1)
        perror("setctl setval error");

    //初始化P,V操作
    V.sem_num = 0;
    V.sem_op  = 1;
    V.sem_flg = SEM_UNDO;
    P.sem_num = 0;
    P.sem_op  = -1;
    P.sem_flg = SEM_UNDO;

    //生产者进程
    if(fork() == 0)
    {
        int i = 0;
        while(i < 100)
        {
            semop(emptyid , &P ,1 );
            semop(mutxid , &P , 1);
            array[*(set) % MAXSEM] = i + 1;
            printf("Producer %d\n", array[(*set) % MAXSEM]);
            (*set)++;
            semop(mutxid, &V, 1);
            semop(fullid, &V, 1);
            i++;
        }
        sleep(3);
        printf("Producer is over");
        exit(0);
    }
    else
    {
        //Odd_ConsumerA  进程
        if(fork()==0)
        {
            while(1)
            {
                semop(fullid, &P, 1);
                semop(mutxid, &P, 1);
                if(*get == 100)
                    break;
                *sum += array[(*get)%MAXSEM];
                printf("The ComsumerA Get Number %d\n", array[(*get)%MAXSEM] );
                (*get)++;
                if( *get ==100)
                    printf("The sum is %d \n ", *sum);
                semop(mutxid , &V , 1);
                semop(emptyid , &V ,1 );
                sleep(1);
            }
            printf("ConsumerA is over");
            exit(0);
        }
        else
        {
            //Even_Consumer B进程
            if(fork()==0)
            {
                while(1)
                {
                    semop(fullid , &P , 1);
                    semop(mutxid , &P , 1);
                    if(*get == 100)
                        break;
                    *sum += array[(*get)%MAXSEM];
                    printf("The ComsumerB Get Number %d\n", array[(*get)%MAXSEM] );
                    (*get)++;
                    if( *get ==100)
                        printf("The sum is %d \n ", *sum);
                    semop(mutxid , &V , 1);
                    semop(emptyid , &V ,1 );
                    sleep(1);
                }
                printf("ConsumerB is over\n");
                exit(0);
            }
        }
    }
    return 0;
}