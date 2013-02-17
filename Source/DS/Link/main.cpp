#include <ctype.h>
#include "LinkList.h"

void LinkList_printC(const LinkList &L)
{
	LinkList PL = L;
	while (PL)
	{
		printf("%c",PL->data);
		PL = PL->next;
	}
	printf("\n");
}

void LinkList_printI(const LinkList &L)
{
	LinkList PL = L;
	while (PL)
	{
		printf("%d",PL->data);
		PL = PL->next;
	}
	printf("\n");
}

int main()
{
	LinkList list = NULL;
	LinkList Char = NULL,Num = NULL,Other = NULL;
	char c = 0;
	printf("type a string:");
	while (c != 10)
	{
		scanf("%c",&c);
		if (c != 10)
			LinkList_Pushback(list,c);
	}
	LinkList PL = list;
	while (PL)
	{
		if (PL->data >= '0' && PL->data<='9')
			LinkList_Pushback(Num,PL->data);
		else if (toupper(PL->data) <= 'Z' && toupper(PL->data) >='A')
			LinkList_Pushback(Char,PL->data);
		else LinkList_Pushback(Other,PL->data);
		PL = PL->next;
	}
	printf("Original list:");
	LinkList_printC(list);
	printf("Numbers:");
	LinkList_printC(Num);
	printf("Other:");
	LinkList_printC(Other);
	printf("Characters:");
	LinkList_printC(Char);
	printf("\n\n\n");
/*
	LinkList joy = NULL,out = NULL;
	for (int val =1;val != 10;++val)
		LinkList_Pushback(joy,val);
	LinkList temp = joy;
	while (temp->next)
		temp = temp->next;
	temp->next = joy;
	for (int val = 1,outnum = 0;outnum != 9;++val,joy = joy->next)
	{
		if (4 == val)
		{
			if (NULL == out)
			{
				out = temp = joy->next;
				joy->next = joy->next->next;
				temp->next = NULL;
			}
			else
			{
				if (joy->next != joy)
				{
					temp->next = joy->next;
					joy->next = joy->next->next;
					temp = temp->next;
					temp->next = NULL;
				}
				else
				{
					printf("sdf");
					temp->next = joy;
					joy->next = NULL;
				}
			}
			joy = joy->next;
			val = 1;
			++outnum;
		}
	}
	LinkList_printI(out);
*/
	return 0;
}