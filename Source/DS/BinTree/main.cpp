#pragma comment(linker,"/NODEFAULTLIB:LIBC")

#include "BinTree.h"

int main()
{
	char str[255] = ""/*"ABC  DE G  F   "*/;
	char *pstr = str;
	unsigned nodenum = 0,depth = 0;
	BinTree bt;
	do
	{
		char c;
		scanf("%c",&c);
		if ('\n' != c)
		{
			*pstr++ = c;
		}
		else
		{
			break;
		}
	} while (1);
	pstr = str;
	printf("%s,<-string\n\n",str);
	CreateBinTree(bt,pstr,strlen(str) + str - 1);
	TraverseBinTree(bt,nodenum);
	printf("#End\nBTNode number(s)=%d\n",nodenum);
//	printf("\n\n");
//	nodenum = 0;
//	TravBinTree(bt,nodenum);
//	printf(".\nBTNode number(s)=%d\n",nodenum);
	BinTreeDepth(bt,depth);
	printf("\nfind=%u,depth=%u\n",SearchBinTree(bt,'a'),depth);
	return 0;
}