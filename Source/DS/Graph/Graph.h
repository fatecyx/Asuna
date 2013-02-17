#include <windows.h>
#include <stdio.h>

typedef unsigned VertexType;
typedef enum GraphType{UDG,DG,UDN,DN};

typedef struct ArcNode
{
	unsigned adjvex;		//指向的顶点的位置
	struct ArcNode *next;	//指向下一条弧的指针
	int weight;
}ArcNode;

typedef struct
{
	ArcNode *firstarc;		//第一条依附该结点的弧
	unsigned adjvex;
//	VertexType data;
}VNode;

typedef struct 
{
	VNode *vertices;
	unsigned vexnum;		//当前顶点数
	unsigned arcnum;		//当前弧数
	unsigned short type;	//图类型
}ALGraph;

void CreateALGraph(ALGraph &G);
void CreateUDG(ALGraph &G);
void Chart(const ALGraph &G);
void BFST(const ALGraph &G);
void DFST(const ALGraph &G);
void DFS(const ALGraph &G,unsigned i,bool *visited);
bool CreateArcNode(ALGraph &G,				//邻接链表
				   const unsigned &v1,		//顶点一
				   const unsigned &v2,		//顶点二
				   const int &weight);		//权