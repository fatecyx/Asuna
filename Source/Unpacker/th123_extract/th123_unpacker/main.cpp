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
		thFXTPacker::Help_Unpack(argv[0]);
		return;
	}

	while (--argc)
	{
		thFXTPacker::sDecOpt opt = {true, true, false, false};

		while (argc && argv[argc][0] == '/')
		{
			WORD p = *(WORD *)(argv[argc] + 1);

			if (p == '0n')
			{
				--argc;
				opt.bDecodeCv0 = false;
			}
			else if (p == '1n')
			{
				--argc;
				opt.bDecodeCv1 = false;
			}
			else if (p == '2n')
			{
				--argc;
				opt.bDecodeCv2 = false;
			}
			else if (p == '3n')
			{
				--argc;
				opt.bDecodeCv3 = false;
			}
			else
			{
				break;
			}
		}

		thFXTPacker thfp(argv[argc], &opt);

		if (thfp.Init() == true)
		{
			thfp.ExtractAllFiles();
		}
	}
}