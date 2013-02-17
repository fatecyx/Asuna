#include <windows.h>
#include <malloc.h>
#include <stdio.h>

typedef int TElemtype;
typedef struct BTNode
{
	TElemtype data;
	struct BTNode *lc;
	struct BTNode *rc;
	struct BTNode *parent;
}BTNode,*BinTree;

void CreateBinTree(BTNode *&BT,char *&data,const char *End);	//PreOrder
void TraverseBinTree(const BinTree &BT,unsigned &nodenum);		//PreOrder traverse
void TravBinTree(const BinTree &BT,unsigned &nodenum);
bool SearchBinTree(const BinTree &BT,const TElemtype &val);
void BinTreeDepth(const BinTree &BT,unsigned &depth,unsigned temp = 0);