#include "LinkList.h"

bool LinkList_Init(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	if (NULL == L) return 1;
	L->next = NULL;
	return 0;
}

bool LinkList_Insert(LinkList &L,const SElemtype &val)
{
	return 0;
}

bool LinkList_Pushback(LinkList &L,const SElemtype &val)
{
	LinkList tp = L;
	if (NULL == L)
		L = tp = (LinkList)malloc(sizeof(LNode));
	else
	{
		while(tp->next)
			tp = tp->next;
		tp->next = (LinkList)malloc(sizeof(LNode));
		if (NULL == tp->next) return 1;
		tp = tp->next;
	}
	tp->data = val;
	tp->next = NULL;
	return 0;
}

bool LinkList_Delete(LinkList &L,LinkList PL)
{
	if (L == PL)
	{
//		L = PL->next;
		free(PL);
	}
	else
	{
		LinkList temp = L;
		while (temp->next != PL)
			temp = temp->next;
		temp->next = PL->next;
		free(PL);
	}
	return 0;
}