#include "BinTree.h"
#include "Stack.h"

void CreateBinTree(BinTree &BT,char *&data,const char *End)	//InOrder
{
	if (End == data) return;
	if (' ' == *data)
	{
//		printf("%c,BT->data=NULL,len=%d\n",*data,strlen(data));
		BT = NULL;
	}
	else
	{
		BT = (BinTree)malloc(sizeof(BTNode));
		BT->data = *data;
		BT->lc = BT->rc = NULL;
//		printf("%c,BT->data=%c,len=%d\n",*data,BT->data,strlen(data));
		if (End != data)
			CreateBinTree(BT->lc,++data,End);
		if (End != data)
			CreateBinTree(BT->rc,++data,End);
	}
}

void TraverseBinTree(const BinTree &BT,unsigned &nodenum)
{
	if (BT)
	{
		++nodenum;
		TraverseBinTree(BT->lc,nodenum);
		printf("%c",BT->data);
		TraverseBinTree(BT->rc,nodenum);
	}
	else
	{
		printf(" ");
	}
}

void TravBinTree(const BinTree &BT,unsigned &nodenum)	//PreOrder,non-recursion
{
	SqStack sq;
	InitSqStack(sq);
	BinTree point = BT;
	while (point || !IsEmpty(sq))
	{
		if (point)
		{
			++nodenum;
			Push(sq,point);
			printf("%c",point->data);
			point = point->lc;
		}
		else
		{
			printf(" ");
			Pop(sq,point);
			point = point->rc;
		}
	}
	free(sq.base);
}

bool SearchBinTree(const BinTree &BT,const TElemtype &val)
{
	if (BT)
	{
		if (BT->data != val)
		{
			if (SearchBinTree(BT->lc,val) == TRUE)
			{
				return TRUE;
			}
			else if (SearchBinTree(BT->rc,val) == TRUE)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

void BinTreeDepth(const BinTree &BT,unsigned &depth,unsigned temp)
{
	if (BT)
	{
		++temp;
		BinTreeDepth(BT->lc,depth,temp);
		BinTreeDepth(BT->rc,depth,temp);
	}
	else
	{
		depth = depth > temp ? depth : temp;
	}
}