#include <windows.h>
#include <malloc.h>
#include <stdio.h>
#include <time.h>

typedef int Elemtype;
typedef struct Linklist
{
	Elemtype data;
	struct Linklist *next;
}Linklist;

size_t Search(Linklist *point,const Elemtype &Value)
{
	for(size_t ix = 1;point->next != NULL;point = point->next,++ix)
		if(point->data == Value) return ix;
	return 0;
}

void Junk(Linklist * &head)
{
	Elemtype min = head->data;
	Linklist *p = head,*pmin = head;
	while(p->next->next != NULL)
	{
		if(p->next->data < min)
		{
			min = p->next->data;
			pmin = p;
		}
		p = p->next;
	}
	p = pmin;
	pmin = pmin->next;
	p->next = p->next->next;
	pmin->next = head->next;
	head = pmin;
}

int main()
{
	Linklist *head = NULL,*p = NULL;
	head = p = (Linklist *)malloc(sizeof(Linklist));
	srand((unsigned)time(NULL));
	for(size_t ix = 0;ix != 10;++ix)
	{
		p->next = (Linklist *)malloc(sizeof(Linklist));
		p->data = rand()%100;
		p = p->next;
		p->next = NULL;
	}
	for(Linklist *point = head;point->next != NULL;point = point->next)
		printf("%d  ",point->data);
	printf("\n");
	Elemtype Value;
	scanf("%d",&Value);
	printf("%d\n",Search(head,Value));
	Junk(head);
	{for(Linklist *point = head;point->next != NULL;point = point->next)
		printf("%d  ",point->data);}
	printf("\n");
	return 0;
}