#pragma comment(lib,"msvcrt6.lib")
#pragma comment(linker,"/ALIGN:0x1000 /NODEFAULTLIB:LIBC")
#pragma comment(linker,"/MERGE:.data=.text /SECTION:.text,EWR")

#include "Graph.h"

void main()
{
	ALGraph G;
	printf("依次输入图的顶点,弧的数量,图的类型:\n"
		   "(0.无向图 1.有向图 2.无向网 3.有向网)\n");
	scanf("%u,%u,%u",&G.vexnum,&G.arcnum,&G.type);
	CreateALGraph(G);
	Chart(G);
	DFST(G);
}