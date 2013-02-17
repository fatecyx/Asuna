#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker, "/MERGE:.text=.Nagisa /SECTION:.Nagisa,ERW")
#pragma comment(linker, "/MERGE:.rdata=.Nagisa")
#pragma comment(linker, "/MERGE:.data=.Nagisa")

#include "../thFXTPacker.h"
#include <stdio.h>
#include "getmainargs.h"

void __cdecl main(int argc, char **argv)
{
	getargs(&argc, &argv);
	if (argc == 1)
	{
		thFXTPacker::Help_Pack(argv[0]);
		return;
	}

	while (--argc)
	{		
		thFXTPacker thfp(argv[argc]);
		
		if (thfp.Init() == true)
		{
			thfp.Pack();
		}
	}
}