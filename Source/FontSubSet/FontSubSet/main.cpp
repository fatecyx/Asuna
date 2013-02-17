#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "FontSubSet.h"

ForceInline Void main2(Int argc, WChar **argv)
{
	_wsetlocale(LC_CTYPE, L"");

	{
		CFontSubSet fss(argc, argv);
		if (fss.ParseCmdLine() == FALSE)
		{
			_tprintf(_T("Parse command line failed.\n"));
		}
		else if (fss.ParseAss() == FALSE)
		{
			_tprintf(_T("Parse ass file failed.\n"));
		}
		else if (fss.SubSet() == FALSE)
		{
			_tprintf(_T("Subset failed.\n"));
		}
	}
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}