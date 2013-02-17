diff --git a/main.c b/_main.c
index aef14ff..b8b3993 100644
--- a/main.c
+++ b/_main.c
@@ -1,11 +1,15 @@
 #include <stdio.h>
+#include <stdlib.h>
+#include <time.h>
+#include <conio.h>
 #define TRUE 1
 #define FALSE 0
 #define MAXPRI 100
 #define NIL -1
+#define MAX_PROCESS_NUM 3
 
 //进程控制块
-struct {     
+struct _tagPCB {
 	int id;    //进程号
 	char status;  //进程状态，'e'-执行态 'r'-高就绪态  't'-低就绪态 'w'-等待态  'c'-完成态
 	int nextwr;   //等待链指针，指示在同一信号量上等待的下一个等待进程的进程号。
@@ -27,7 +31,7 @@ char savearea[3][4];
 
 char addr;//当前执行程序的当前指针
 
-void main();
+int main();
 void init();
 float random();
 int timeint(char ad);
@@ -44,28 +48,44 @@ void eexit(int n);
 
 //--------------------------------------------------------------------
 //主程序
-void main()
+int main()
 {
-	int currentProcess;
+	int currentProcess, i, proc[MAX_PROCESS_NUM] = {0};
+	struct _tagPCB *lppcb[MAX_PROCESS_NUM] = {0};
+
+	srand(time(NULL));
 	printf("进程管理器\n");
 	init();
 	printf("s1=%d,s2=%d\n",s1,s2);
 	printf("进程1、进程2、进程3已经准备好！\n");
+	printf("输入要启动的进程 [1,2,3] : ");
+
+	i = scanf("%d, %d, %d", &proc[0], &proc[1], &proc[2]) - 1;
+
+	for (; i >= 0; --i)
+	{
+		if (proc[i] > 0 && proc[i] < 4)
+		{
+			--proc[i];
+			lppcb[proc[i]] = &pcb[proc[i]];
+		}
+	}
+
 	for (;;)
 	{
 		currentProcess=scheduler(); //进程调度，选择优先级别最高的就绪进程运行。
-		if (currentProcess==NIL) 
+		if (currentProcess==NIL)
 			break;  //所有进程已经运行完毕，结束。
 		switch (currentProcess)
 		{
 		case 0:
-			process1();
+			lppcb[currentProcess] ? process1() : eexit(currentProcess);
 			break;
 		case 1:
-			process2();
+			lppcb[currentProcess] ? process2() : eexit(currentProcess);
 			break;
 		case 2:
-			process3();
+			lppcb[currentProcess] ? process3() : eexit(currentProcess);
 			break;
 		default:
 			printf("进程号出错！\n");
@@ -73,6 +93,7 @@ void main()
 		}
 	}
 	printf("最后结果：s1=%d,s2=%d\n",s1,s2);
+	return getch();
 }
 
 
@@ -87,8 +108,8 @@ void init()
 		pcb[j].id=j;
 		pcb[j].status='r';
 		pcb[j].nextwr=NIL;
-		printf("\n进程 %d 的优先数？",j+1);
-		scanf("%d",&i);
+		i = rand() % (MAXPRI + 1);
+		printf("\n进程 %d 的优先数 %d\n",j+1, i);
 		pcb[j].priority=i;
 	}
 	//初始化两个信号量
@@ -148,7 +169,7 @@ int scheduler()
 			pcb[pd].status='e';
 			exe=pd;
 			printf("进程%d正在执行\n",exe+1);
-			
+
 		}
 		else if (pcb[pd].priority<pcb[exe].priority)//选中进程的优选级别高于当前进程
 		{
@@ -288,11 +309,11 @@ a1: printf("
 	if (timeint('b')) //检查进程1的时间片是否到。若到，阻塞进程，处理器空闲。参数'b'表示下一次执行地址。
 		break;//进程1的时间片到而退出
 	//下面是时间片未到或者重新得到时间片时执行
-b1: printf("s1=%d\n",++s1); //s1=s1+1  
+b1: printf("s1=%d\n",++s1); //s1=s1+1
     printf("进程1释放信号量1（与s1相联系）并退出临界区\n");
 	if (v(0,'c')) //若没有等待信号量1的进程，到"c1"点继续执行，否则退出。
 		break; //后面处理器重新调度
-	
+
 	//程序执行s2=s2+1计算。
 c1: printf("进程1申请信号量2（与s2相联系）\n");
     if (p(1,'d'))  //若申请失败 ，当前进程（进程1）被阻塞，处理器空闲。
@@ -301,13 +322,13 @@ c1: printf("
 d1: printf("进程1得到s2,正在临界区2\n");
 	if (timeint('e')) //检查进程1的时间片是否到。若到，阻塞进程1，处理器空闲。
 		break;
-e1: printf("s2=%d\n",++s2);  //s2=s2+1 
+e1: printf("s2=%d\n",++s2);  //s2=s2+1
     printf("进程1释放信号量2（与s2相联系）并退出临界区\n");
 	if (v(1,'f'))
 		break;
 f1: printf("进程1循环计算次数=%d\n",registeri);
 	}
-	
+
 	if (registeri<6) return;
 	eexit(0);//结束进程1
 }
@@ -337,11 +358,11 @@ void process2()
 a2: printf("进程2得到s2,正在临界区2\n");
 	if (timeint('b')) //检查进程2的时间片是否到。若到，阻塞进程2，处理器空闲。
 		break;//退出
-b2: printf("s2=%d\n",++s2); //s2=s2+1  
+b2: printf("s2=%d\n",++s2); //s2=s2+1
     printf("进程2释放信号量2（与s2相联系）并退出临界区\n");
 	if (v(1,'c')) //若没有等待信号量2的进程，到"c2"点继续执行，否则退出。
-		break; 
-	
+		break;
+
 	//进程执行s1=s1+1计算。
 c2: printf("进程2申请信号量1（与s1相联系）\n");
     if (p(0,'d'))  //若申请失败 ，当前进程（进程2）被阻塞，处理器空闲。
@@ -350,13 +371,13 @@ c2: printf("
 d2: printf("进程2得到s1,正在临界区1\n");
 	if (timeint('e')) //检查进程2的时间片是否到。若到，阻塞进程2，处理器空闲。
 		break;
-e2: printf("s1=%d\n",++s1);  //s1=s1+1 
+e2: printf("s1=%d\n",++s1);  //s1=s1+1
     printf("进程2释放信号量1（与s1相联系）并退出临界区\n");
 	if (v(0,'f'))
 		break;
 f2: printf("进程2循环计算次数=%d\n",registeri);
 	}
-	
+
 	if (registeri<6) return;
 	eexit(1);//结束进程2
 }
@@ -382,14 +403,14 @@ void process3()
 a3: printf("进程3得到s2,正在临界区2\n");
 	if (timeint('b')) //检查进程3的时间片是否到。若到，阻塞进程3，处理器空闲。
 		break;//退出
-b3: printf("s2=%d\n",++s2); //s2=s2+1  
+b3: printf("s2=%d\n",++s2); //s2=s2+1
     printf("进程3释放信号量2（与s2相联系）并退出临界区\n");
 	if (v(1,'c')) //若没有等待信号量2的进程，到"c3"点继续执行，否则退出。
-		break; 
-	
+		break;
+
 c3: printf("进程3循环计算次数=%d\n",registeri);
 	}
-	
+
 	if (registeri<6) return;
 	eexit(2);//结束进程3
 }
