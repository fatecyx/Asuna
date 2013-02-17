#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int fork(){ return 0; }

int main()
{
    int i,p_id;
    //添加创建进程代码
    p_id = fork();
    if (p_id == -1)
    {
        perror("Create process failed.\n");
        return -1
    }
    else if(p_id)
    {
        printf("parent process.\n");
    }
    else
    {
        printf("child process.\n");
    }   
}