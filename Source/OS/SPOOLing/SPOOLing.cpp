#pragma comment(linker, "/ENTRY:main")
//用户进程在各自的缓冲区中形成输出字符串，调用spoolserver请求输出；spoolserver接受//请求，从用户//缓冲区中取出数据送到输出井，并构造请求块reqblock,提交给SPOOLing进程使用。
//SPOOLing进程取出某reqblock，根据其信息将数据从输出井取出来打印。释放相关资源。
#include <stdio.h>

#define WELLSIZE 500  //输出井的大小
#define FALSE 0
#define TRUE 1

//进程控制块
struct
{
    int id;//进程标识数
    char status;//进程状态,'e'为执行态，'c'为完成态。
    int bufflag;//用户缓冲区userbuf空闲标志：FALSE为无数据，TRUE为有数据。
    int filec;//本进程需要输出的文件数（用户指定）
}pcb[4];//pcb[0]为SPOOLing进程，pcb[1]、pcb[2]、pcb[3]为3个用户进程

//输出请求块，共10块。
struct
{
    int reqid;//请求进程的标识数
    int size;//输出文件长度
    int addr;//输出文件在输出井well的指针
}reqblock[10];
int ebp=0;//输出请求块组中的当前空闲块号。
int ebc=10;//输出请求块组中的当前空闲块数
int cbp=0;//输出请求块组的当前输出块号
//每个作业需要输出时，要在输出请求块中登记。块分配的顺序是从0到9的环形分配。
//真正输出时，要从输出请求块中获取输出的信息。输出块的顺序是从0到9，并环形循环。

int well[WELLSIZE];//输出井
int wellptr=0;//输出井当前指针,环形指针。
int wellsize=WELLSIZE;//输出井剩余大小

int userbuf[3][50];//用户缓冲区
int f[4];//4个进程输出的文件数
int n;//输出文件总数

void main();
void scheduler();
float random() ;
void userpro(int idnum);
int spoolserver(int idnum,int charnum);
void spoolout();


//------------------------------------------------------------------------------
void main()
{
    int i,j;
    printf("SPOOLing系统\n");
    //初始化
    for (i=0;i<WELLSIZE;i++) //初始化输出井
        well[i]=0;
    for (i=0;i<3;i++)//初始化用户缓冲区
        for(j=0;j<50;j++)  userbuf[i][j]=0;
        for (i=0;i<4;i++) //初始化进程控制块
        {
            pcb[i].id=i;
            pcb[i].status='e';//所有进程初始为可执行态
            if (i)  //对于用户进程
            {
                pcb[i].bufflag=FALSE;
                printf("用户%d的输出文件数？\n",i);
                scanf("%d",&pcb[i].filec);
                n+=pcb[i].filec;
            }
        }
        for (i=0;i<4;i++)
            f[i]=0;
        //调度进程执行
        scheduler();
        printf("所有文件已经输出。结束！\n");
}

//------------------------------------------------------------------------------------
//调度进程执行，直到所有数据输出完毕。
//三个用户进程的调度概率30%，SPOOLing进程为10%。
void scheduler()
{
    float x;
    for (;;)
    {
        x=random();
        if (x<0.3 && pcb[1].status=='e')
            userpro(1);
        else if (x>=0.3 && x<0.6 && pcb[2].status=='e')
            userpro(2);
        else if (x>=0.6 && x<0.9 && pcb[3].status=='e')
            userpro(3);
        else if (x>=0.9 && pcb[0].status=='e')
            spoolout();//执行SPOOLing进程
        if (n==0)  //所有文件输出完毕
            break;
    }
}



//-----------------------------------------------------------------------------------
float random() //产生随机数
{
    int m;
    static int seed;
    if ((m=seed)<0)
        m=-m;
    seed=(25173*seed+13849)%65536;
    return (float)(m/32767.0);
}



//-------------------------------------------------------------------------------------
//该进程每次运行产生一串符号串输出。若进程对应缓冲区无数据，产生数据。数据送到输出井。
//idnum是进程号
void userpro(int idnum)
{
    int c,j;

    //若进程idnum的缓冲区没有数据，为之产生数据。
    if (pcb[idnum].bufflag==FALSE)
    {
        pcb[idnum].bufflag=TRUE;

        printf("用户%d生成的数据：",idnum);
        for (j=0;j<49;++j)
        {
            c=65+(int)(random()*10.0);//随机字符
            userbuf[idnum-1][j]=c;
            if (c==65)  //随机部分值为0
            {
                userbuf[idnum-1][j]=0;
                break;//最后一个字符正好是字符串结束标记
            }
            else
                printf("%c",c);
        }
        if (c!=65)//有49个字符产生，最后一个应该为字符串结束标记
            userbuf[idnum-1][j]=0;

        printf("\n");

    }//if (pcb[idnum].bufflag==FALSE)

    //输出缓冲区数据到输出井
    if (spoolserver(idnum,j+1))
        if (--pcb[idnum].filec==0)//该进程的全部文件数出完毕
        {
            pcb[idnum].status='c';//进程为终止态
            printf("用户%d的程序结束！\n",idnum);
        }
}


//--------------------------------------------------------------------------------
//登记输出请求块，将用户缓冲区userbuf的数据送入输出井well。成功送入，返回TRUE，否则返回FALSE.
//idnum为进程号,charnum为输出的字符个数.
int spoolserver(int idnum,int charnum)
{
    int k;
    if (charnum>wellsize || ebc==0)//字符数超过输出井剩余空间的大小或输出请求块的空闲块数为0
        return (FALSE);//无法输出

    //登记输出请求块
    reqblock[ebp].reqid=idnum;
    reqblock[ebp].size=charnum;
    reqblock[ebp].addr=wellptr;//字符在输出井中的起始位置
    ebc--;//空闲输出请求块数减一
    ebp=(++ebp)%10;//空闲块指针指向下一块
    //把数据用户缓冲区传到输出井,起始位置由输出井当前指针决定
    for (k=0;k<charnum;++k)
    {
        well[wellptr++]=userbuf[idnum-1][k];
        wellptr=wellptr%WELLSIZE;
    }
    wellsize=wellsize-charnum;
    pcb[idnum].bufflag=FALSE;//进程缓冲区已无数据
    return (TRUE);
}

//---------------------------------------------------------------------
//SPOOLing进程的程序，负责从输出井取出数据打印。
void spoolout()
{
    int id,address,size,c;
    if (ebc<10)  //有输出请求块
    { //取出当前输出请求块cbp的输出数据
        FILE *fp;
        wchar_t szFileName[256];
        id=reqblock[cbp].reqid;
        swprintf(szFileName, L"用户%d_%d.txt", id, f[id]);
        fp = _wfopen(szFileName, L"ab");
        size=reqblock[cbp].size;
        address=reqblock[cbp].addr;//数据在输出井的起始位置
        cbp=(++cbp)%10;//指向下一个输出块(下一个可输出的块)
        printf("输出用户%d第%d个文件,大小=%d个字符:",id,++f[id],size-1);
        address=address%WELLSIZE;
        //真正输出数据
        while((c=well[address++])!=0)
        {
            fputc(c, fp);
            address=address%WELLSIZE;
        }
        printf("\n");
        fclose(fp);
        n--;//输出文件数减一
        wellsize+=size;//增加输出井剩余空间
        ebc++;//输出请求块组的空闲块增一
    }
}