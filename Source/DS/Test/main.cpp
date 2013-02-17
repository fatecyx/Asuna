#include <stdio.h>
#include <windows.h>
#include <string>
#include <iostream>
using std::string;
using std::cin;
using std::getline;

typedef int SElemtype;
typedef bool Status;
typedef struct
{
	SElemtype *base;
	SElemtype *top;
	size_t StackSize;
}SqStack;

const size_t STACK_INIT_SIZE = 10,
			 STACK_INCRESEMENT = 10;

Status InitSqStack(SqStack &sqstack)	//³õÊ¼»¯Õ»
{
	sqstack.base = new SElemtype[STACK_INIT_SIZE];
	if(sqstack.base == NULL) exit(EXIT_FAILURE);
	sqstack.StackSize = STACK_INIT_SIZE;
	sqstack.top = sqstack.base;
	return 0;
}

Status Push(SqStack &sqstack,const int &val)	//Ñ¹Õ»
{
	if(size_t(sqstack.top - sqstack.base) >= sqstack.StackSize)
	{
		sqstack.base = (SElemtype *)realloc(sqstack.base,
											sqstack.StackSize + STACK_INCRESEMENT);
		if(sqstack.base == NULL) exit(EXIT_FAILURE);
		sqstack.top = sqstack.base + sqstack.StackSize;
		sqstack.StackSize += STACK_INCRESEMENT;
	}
	*sqstack.top++ = val;
	++sqstack.StackSize;
	return 0;
}

SElemtype Pop(SqStack &sqstack)	//³öÕ»
{
	if(sqstack.base == sqstack.top) return FALSE;	//¿ÕÕ»
	--sqstack.top;
	return 0;
}

SElemtype Pop(SqStack &sqstack,int &val)	//³öÕ»
{
	if(sqstack.base == sqstack.top) return FALSE;	//¿ÕÕ»
	val = *--sqstack.top;
	return 0;
}

Status IsEmpty(const SqStack &sqstack)	//ÅÐ¶ÏÊÇ·ñÎª¿Õ
{
	if(sqstack.base == sqstack.top) return TRUE;
	else return FALSE;
}

SElemtype GetTop(const SqStack &sqstack)	//·µ»ØÕ»¶¥ÔªËØ
{
	return *(sqstack.top - 1);
}

Status Clear(SqStack &sqstack)	//Çå¿Õ
{
	sqstack.top = sqstack.base;
	return 0;
}

int main()
{
	string exp;
	SElemtype val,val_bin,val_oct,val_hex;
	SqStack sqstack;
	InitSqStack(sqstack);
	getline(cin,exp);
	for (string::size_type ix = 0;ix != exp.size();++ix)
	{
		switch(exp[ix])
		{
		case '(': Push(sqstack,')');
				  break;
		case '[': Push(sqstack,']');
				  break;
		case '{': Push(sqstack,'}');
				  break;
		case ')': 
		case ']': 
		case '}': if(!IsEmpty(sqstack))
				  {
//					  SElemtype temp;
					  if(GetTop(sqstack) != exp[ix])
					  {
						  printf("missing '%c' before '%c'\n",GetTop(sqstack),exp[ix]);
					  }
					  else Pop(sqstack);
				  }
			      else printf("Syntax error: '%c'\n",exp[ix]);
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

	scanf("%d",&val);
	val_bin = val_oct = val_hex = val;
	do
	{
		Push(sqstack,val_bin % 2);
		val_bin /= 2;
	} while (val_bin);
	printf("bin: ");
	while (sqstack.base != sqstack.top)
	{
		Pop(sqstack,val);
		printf("%d",val);
	}
	printf("\noct: %o\n"
		   "hex: %X",val_oct,val_hex);
	printf("\n");
	return 0;
}