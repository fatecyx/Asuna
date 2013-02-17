#define INITSIZE 100
#define INCRESEMENT 20
#if _MSC_VER < 1310
#define for if (1) for
#endif

typedef struct _BOOKNODE
{
/*	int ISBN;
	TCHAR *BookName;
	TCHAR *Author;
	DWORD Reserve;
	double UnitPrice;
*/
	TCHAR *BookInfo[5];
} BOOKNODE;

typedef struct _BOOK
{
	BOOKNODE *pNode;
	DWORD MaxNum;
	SHORT TipNum;
	DWORD BookNum;
} BOOK;

TCHAR *Tip[] = {
		"书号",		// name
		"书名",		// isbn
		"作者",		// author
		"数量",		// book number
		"单价",		// unit price
};

enum SEARCHMETHOD
{
	BINCHOP,		// Binary Chop
	SEQS,			// Sequence Search
};
enum SEARCHTYPE
{
	ISBN,			// search by isbn
	NAME,			// search by book name
	CANCEL			// cancel
};
enum EToken
{
	ERR_INIT = -2,		// initialization faild
	ERR_NORMAL,			// normal error
	ERR_SUCCESS = 0,	// no error
	ERR_NOBOOK,			// no book
	ERR_ADDBOOK,		// add book failed
};

TCHAR Separator[] = "--------";

void		ClearScreen		();
int			Menu			(BOOK *Book);
int			Sort			(BOOK *Book);
int			Delete			(BOOK *Book);
void		_Delete			(BOOK *Book, DWORD sn);
int			AddBook			(BOOK *Book);
int			List			(const BOOK *Book);
int			Search			(BOOK *Book);
int			Initialization	(BOOK *Book);
void		Print			(TCHAR **String, 
							 SHORT n, 
							 COORD coord, 
							 const SHORT *ShiftRight);
