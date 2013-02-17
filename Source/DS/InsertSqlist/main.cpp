#include <stdio.h>
#include <malloc.h>
#include <windows.h>
//////////////////////////////////////////////////////////////////////////
#pragma comment(lib,"kernel32.lib")
#pragma comment(lib,"shell32.lib")
#pragma comment(lib,"msvcrt.lib")
#pragma comment(linker, "/opt:nowin98")
#pragma comment(linker, "/FILEALIGN:512")
#pragma comment(linker, "/ALIGN:512")
#pragma comment(linker, "/ALIGN:4096")
#pragma comment(linker, "/MERGE:.rdata=.data")
#pragma comment(linker, "/MERGE:.text=.data")
#pragma comment(linker, "/MERGE:.reloc=.data")
#pragma comment(linker, "/ENTRY:EntryPoint")
//////////////////////////////////////////////////////////////////////////
typedef int ElemType;
typedef bool Status;
typedef struct 
{
	ElemType *elem;
	size_t length;
	size_t listsize;
}Sqlist;
//////////////////////////////////////////////////////////////////////////
bool Search = FALSE;
//////////////////////////////////////////////////////////////////////////
Status InitSqlist(Sqlist &List,const size_t &n)
{
	List.elem = (ElemType *)malloc(sizeof(ElemType) * n);
	List.length = n;
	List.listsize = sizeof(ElemType) * n;
	if(List.elem == NULL) return FALSE;
	for(size_t ix = 0;ix != n;++ix)
		List.elem[ix] = 2 * ix + 2;
	return TRUE;
}

Status Sqlist_Insert(Sqlist &List,const ElemType &insertval)
{
	bool isfound = 0;
	size_t head = 0,end = List.length - 1;
	if(insertval < List.elem[head]) head = -1;
	else if(insertval > List.elem[end]) head = List.length;
	else for(size_t mid = (head + end) / 2;mid != head;mid = (head + end) / 2)
	{
		if(insertval > List.elem[mid]) head = mid;
		else if(insertval < List.elem[mid]) end = mid;
		else
		{
			head = end = mid;
			isfound = 1;
		}
	}
	if(Search)
	{
		Search = FALSE;
		if(isfound)
		{
			printf("%d(List.elem[%d]) has been found.\n",insertval,head);
			return TRUE;
		}
		else
		{
			printf("%d dosen't exist.\n",insertval);
			return FALSE;
		}
	}
	List.elem = (ElemType *)realloc( List.elem,(List.listsize += sizeof(ElemType)) );
	if(List.elem == NULL) return FALSE;
	if(head != List.length)
	{
		for(size_t ix = List.length;ix != head;--ix)
			List.elem[ix] = List.elem[ix - 1];
		List.elem[head + 1] = insertval;
	}
	else List.elem[List.length] = insertval;
	++List.length;
	return TRUE;
}

Status Sqlist_Insert(Sqlist &List,const ElemType &insertval,const size_t &locate)
{
	if(locate > List.length || locate < 0) return FALSE;
	List.elem = (ElemType *)realloc( List.elem,(List.listsize += sizeof(ElemType)) );
	if(List.elem == NULL) return FALSE;
	for(size_t ix = List.length;ix != locate;--ix)
		List.elem[ix] = List.elem[ix - 1];
	List.elem[locate] = insertval;
	++List.length;
	return TRUE;
}

int main()
{
	Sqlist List;
	size_t ix = 0,select,locate;
	const size_t num = 8;
	ElemType insertval = 11;
	if(!InitSqlist(List,num))
	{
		printf("Initialize error.\n");
		return 0;
	}
	while(1)
	{		
		printf("**********************************************************\n"
		       "1.List the Sequent list.\n"
			   "2.Insert a new elem to the Sqlist automaticly.\n"
			   "3.Insert a new elem to the Sqlist with specified location.\n"
			   "4.Search a value in the Sequent list.\n"
			   "5.Exit.\n"
			   "**********************************************************\n\n"
			   "Enter your choice: ");
		scanf("%d",&select);
		system("cls");
		switch(select)
		{
		case 1:for(ix = 0;ix != List.length;++ix)
				   printf("%d  ",List.elem[ix]);
	           printf("\n");
			   system("Pause>NUL");
			   break;
		case 2:printf("Enter the value you want to insert:");
			   scanf("%d",&insertval);
			   Sqlist_Insert(List,insertval);
			   break;
		case 3:printf("Enter the value you want to insert:");
			   scanf("%d",&insertval);
			   printf("\nEnter the location you want to insert,\n"
				      "if you don't specify it,program will find it automaticly.\n"
					  "(Warnning:Location must littler than %d):",List.length);
			   scanf("%d",&locate);
			   Sqlist_Insert(List,insertval,locate);
			   break;
		case 4:printf("Enter the value you want to search:");
			   scanf("%d",&insertval);
			   Search = TRUE;
			   Sqlist_Insert(List,insertval);
			   system("Pause>NUL");
			   break;
		case 5:return 0;
		default:printf("Invaild selection.\n");
				system("Pause>NUL");
		}
		system("cls");
	}
}

void  EntryPoint()
{
	ExitProcess(main());
}