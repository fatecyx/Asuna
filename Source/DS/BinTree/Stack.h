typedef BinTree SElemtype;
typedef bool Status;
typedef struct
{
	SElemtype *base;
	SElemtype *top;
	size_t StackSize;
}SqStack;

#define STACK_INIT_SIZE 10
#define STACK_INCRESEMENT 10

Status InitSqStack(SqStack &sqstack)	//³õÊ¼»¯Õ»
{
	sqstack.base = (SElemtype *)malloc(STACK_INIT_SIZE * sizeof(SElemtype));
	if(sqstack.base == NULL) exit(EXIT_FAILURE);
	sqstack.StackSize = STACK_INIT_SIZE;
	sqstack.top = sqstack.base;
	return 0;
}

Status Push(SqStack &sqstack,const SElemtype &val)	//Ñ¹Õ»
{
	if(size_t(sqstack.top - sqstack.base) >= sqstack.StackSize)
	{
		sqstack.base = (SElemtype *)realloc(sqstack.base,
			(sqstack.StackSize + STACK_INCRESEMENT) * sizeof(SElemtype));
		if(sqstack.base == NULL) exit(EXIT_FAILURE);
		sqstack.top = sqstack.base + sqstack.StackSize;
		sqstack.StackSize += STACK_INCRESEMENT;
	}
	*sqstack.top++ = val;
	return 0;
}

Status Pop(SqStack &sqstack,SElemtype &val)	//³öÕ»
{
	if(sqstack.base == sqstack.top) return 1;	//¿ÕÕ»
	val = *--sqstack.top;
	return 0;
}

Status IsEmpty(const SqStack &sqstack)	//ÅÐ¶ÏÊÇ·ñÎª¿Õ
{
	if(sqstack.base == sqstack.top) return TRUE;
	else return FALSE;
}

Status GetTop(const SqStack &sqstack,SElemtype &val)	//·µ»ØÕ»¶¥ÔªËØ
{
	if(!IsEmpty(sqstack))
	{
		val = *(sqstack.top - 1);
		return 0;
	}
	else return 1;
}

void Clear(SqStack &sqstack)	//Çå¿Õ
{
	free(sqstack.base);
	sqstack.base = (SElemtype *)malloc(STACK_INIT_SIZE * sizeof(SElemtype));
	if(sqstack.base == NULL) exit(EXIT_FAILURE);
	sqstack.top = sqstack.base;
	sqstack.StackSize = STACK_INIT_SIZE;
}