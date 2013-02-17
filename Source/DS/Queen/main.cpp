#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")

#define USE_CRT_ALLOC

#include <Windows.h>
#include "crt_h.h"
#include "my_crt.h"
#include "my_common.h"

const UInt32 Max = 8;

Bool bCtrlC;

BOOL CALLBACK HandlerRoutine(DWORD dwCtrlType)
{
    switch(dwCtrlType)
    {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        bCtrlC = True;
        return True;
    }
    return False;
}

typedef struct
{
    Byte Column[Max];
    UInt32 valid;
} SColumnMask;

void GenerateChart(Int Row)
{
	if (!Row) return;
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	PChar begin,end,separator;
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(StdOut,coord);
	for (Int c,r = 0;r != Row * 2 + 1;++r)
	{
		c = 1;
		if (r % 2 == 0)
        {
            if (r == 0)
            {
                begin = "©³";
                separator = "©¥©×";
                end = "©¥©·";
            }
			else if (r == Row * 2)
            {
                begin = "©»";
                separator = "©¥©ß";
                end = "©¥©¿";
            }
			else
            {
                begin = "©Ç";
                separator = "©¥©ï";
                end = "©¥©Ï";
            }
        }
		else
        {
            begin = "©§";
            separator = "¡¡©§";
            end = "¡¡©§";
        }

		printf("%s",begin);
		while (c++ != Row)
			printf("%s",separator);
		printf("%s\t\n",end,r);
	}
}

void Move(Int Y, Int X, Int Row, Bool bRemove = 0)
{
	HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = (X * 2 -1) * 2;
	coord.Y = Y * 2 - 1;
	SetConsoleCursorPosition(StdOut,coord);
    printf("%s", bRemove ? "¡¡" : "¡ñ");
	coord.X = 0;
	coord.Y = Row * 2 + 1;
	SetConsoleCursorPosition(StdOut,coord);
}

void ReMove(Int Y, Int X, Int Row)
{
	Move(Y, X, Row, 1);
}

NoInline Bool IsValid(SColumnMask *mask, Int Row)
{
    Byte col, cur = mask->Column[Row];

    for (Int i = 0; i != Row; ++i)
    {
        col = mask->Column[i];
        if (col == cur)
            return False;
        else if (col + i == cur + Row)
            return False;
        else if (i - col == Row - cur)
            return False;
    }

    return True;
}

Void Try(SColumnMask *mask, Int Row)
{
    Bool bEnd = False;

TRY_BEG:
    while (!bEnd)
    {
        if (Row == Max)
        {
            for (Int32 r = 0; r != Max; ++r)
                Move(r + 1, mask->Column[r] + 1, Max);

            Sleep(50);
            for (Int32 r = 0; r != Max; ++r)
                ReMove(r + 1, mask->Column[r] + 1, Max);

            printf("\r%u", ++mask->valid);
//            return;
            ++mask->Column[--Row];
            continue;
        }

//        mask->Column[Row] = 0;
        for (Int i = 0; /*i != Max && */!bCtrlC; ++i)
        {
            if (IsValid(mask, Row))
            {
                if (++Row != Max)
                    mask->Column[Row] = 0;
                goto TRY_BEG;
//                Try(mask, Row + 1);
            }
            if (++mask->Column[Row] == 8)
                break;
        }

        mask->Column[Row] = 0;
        while (Row >= 0 && ++mask->Column[--Row] == 8) mask->Column[Row] = 0;
        if (Row < 0)
            break;
    }
}

ForceInline Void main2(Int argc, Char **argv)
{
    SColumnMask mask = { 0 };

    SetConsoleCtrlHandler(HandlerRoutine, True);
    GenerateChart(Max);
    Try(&mask, 0);
    printf("\n");
}

void __cdecl main(Int argc, Char **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}