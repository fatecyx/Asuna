#include <windows.h>
#include <stdio.h>
#include <string>
#include "Stack.h"
#include "Queue.h"
using std::string;

#pragma comment(linker,"/NODEFAULTLIB:LIBC")
#pragma comment(linker,"/ALIGN:4096")

int main()
{
/*	string exp;
	SElemtype val;
	SqStack sqstack;
	InitSqStack(sqstack);
	while(1)
	{
		char a;
		scanf("%c",&a);
		if(a == '\n') break;
		exp += a;
	}
	for (string::size_type ix = 0;ix != exp.size();++ix)
	{
		switch (exp[ix])
		{
		case '(': Push(sqstack,')');
				  break;
		case '[': Push(sqstack,']');
				  break;
		case '{': Push(sqstack,'}');
				  break;
		case ')': 
		case ']': 
		case '}': if (!IsEmpty(sqstack))
				  {
					  SElemtype temp;
					  Pop(sqstack,temp);
					  if (temp != exp[ix])
					  {
						  printf("missing '%c' before '%c' @ exp[%d]\n",temp,exp[ix],ix);
						  --ix;
					  }
				  }
			      else printf("Syntax error: '%c' @ exp[%d]\n",exp[ix],ix);
			      break;
		}
	}
	while (!IsEmpty(sqstack))
	{
		SElemtype temp;
		Pop(sqstack,temp);
		printf("missing %c\n",temp);
	}
	printf("\n");

	Clear(sqstack);

	do 
	{
		scanf("%d",&val);
	} while (val > LONG_MAX);
	do
	{
		Push(sqstack,val % 2);
		val /= 2;
	} while (val);
	printf("bin: ");
	while (!IsEmpty(sqstack))
	{
		Pop(sqstack,val);
		printf("%d",val);
	}
	printf("\n");
*/	
	bool Palindrome = 1;
	SqStack sq;
	LinkQueue q;
	InitSqStack(sq);
	q.front = q.rear = NULL;
	q.LQNum = 0;
	while (1)
	{
		char c;
		scanf("%c",&c);
		if (c == '@') break;
		EnQueue(q,c);
		Push(sq,c);
	}
	for (size_t mid = q.LQNum / 2 + q.LQNum % 2;
		 q.LQNum != mid;)
		 {
			 QElemtype temp1,temp2;
			 DeQueue(q,temp1);
			 Pop(sq,temp2);
			 if (temp1 != temp2)
			 {
				 Palindrome = 0;
				 break;
			 }
		 }
	if(Palindrome) printf("Palindrome.");
	else printf("Not palindrome.");
	printf("\n");
	Clear(sq);
	ClearQueue(q);
	return 0;
}