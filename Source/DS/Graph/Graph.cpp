#include "Graph.h"


void CreateALGraph(ALGraph &G)
{
	switch(G.type)
	{
	case UDG:CreateUDG(G);
			 break;
	case DG:
	case UDN:
	case DN:
	default:break;
	}
}

void CreateUDG(ALGraph &G)
{
	G.vertices = (VNode *)malloc(G.vexnum * sizeof(VNode));
	memset(G.vertices,0,G.vexnum * sizeof(VNode));
	unsigned v1,v2;
	int weight;
	for (unsigned i = 0;i != G.arcnum;++i)
	{
		do 
		{
			printf("输入第%d条弧所依附的结点及其权:",i + 1);
			scanf("%u,%u,%d",&v1,&v2,&weight);
		} while (v1 >= G.vexnum && v2 >= G.vexnum);
		if (CreateArcNode(G,v1 - 1,v2 - 1,weight) ||
			CreateArcNode(G,v2 - 1 ,v1 - 1,weight))
		{
			--i;
			printf("被指向的结点已存在.\n");
			system("pause");
		}
		system("cls");
	}
}

bool CreateArcNode(ALGraph &G,const unsigned &v1,const unsigned &v2,const int &weight)
{
	ArcNode *ptrArc;
	if (G.vertices[v1].firstarc == NULL)
	{
		ptrArc = G.vertices[v1].firstarc = (ArcNode *)malloc(sizeof(ArcNode));
		G.vertices[v1].adjvex = v2;
	}
	else
	{
		if (G.vertices[v1].adjvex == v2)
		{
			return 1;
		}
		ptrArc = G.vertices[v1].firstarc;
		while (ptrArc->next)
		{
			if (ptrArc->adjvex == v2)
			{
				return 1;
			}
			ptrArc = ptrArc->next;
		}
		ptrArc->next = (ArcNode *)malloc(sizeof(ArcNode));
		ptrArc = ptrArc->next;
	}
	ptrArc->next = NULL;
	ptrArc->weight = weight;
	ptrArc->adjvex = v2;
	return 0;
}

void Chart(const ALGraph &G)
{
	ArcNode *ptrArc;
	for (unsigned i = 0;i != G.vexnum;++i)
	{
		ptrArc = G.vertices[i].firstarc;
		printf("V%d → ",i + 1);
		while (ptrArc)  
		{
			printf("V%d → ",ptrArc->adjvex + 1);
			ptrArc = ptrArc->next;
		}
		printf("\b\b \n");
	}
	printf("\n");
}

void DFST(const ALGraph &G)		//Depth First Search Traverse
{
	bool *visited = (bool *)malloc(G.vexnum);
	memset(visited,0,G.vexnum);
	for (unsigned i = 0;i != G.vexnum;++i)
	{
		if (!visited[i])
			DFS(G,i,visited);
	}
	printf("\b\b \n");
}

void DFS(const ALGraph &G,unsigned i,bool *visited)
{
	visited[i] = 1;
	printf("V%d → ",i + 1);
	ArcNode *ptrArc = G.vertices[i].firstarc;
	while (ptrArc)
	{
		if (!visited[ptrArc->adjvex])
			DFS(G,ptrArc->adjvex,visited);
		ptrArc = ptrArc->next;
	}
}