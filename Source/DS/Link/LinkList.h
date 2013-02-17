#include <windows.h>
#include <stdio.h>
#include <malloc.h>

typedef int SElemtype;
typedef struct LNode
{
	SElemtype data;
	unsigned sn;
	struct LNode *next;
	struct LNode *prior;
}LNode,*LinkList;

bool LinkList_Init(LinkList &L);
bool LinkList_Insert(LinkList &L,const SElemtype &val);
bool LinkList_Pushback(LinkList &L,const SElemtype &val);
bool LinkList_Delete(LinkList &L,LinkList *&PL);