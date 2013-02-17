#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")

#include <Windows.h>
#include "crt_h.h"
#include "my_crt.h"
#include "my_common.h"

Bool WINAPI IsShiftJIS(UINT UChar)
{
    if ((UChar >= 0x8140 && UChar <= 0x9F7E) || (UChar >= 0xE080 && UChar <= 0xEFFC))
        return True;

    return False;
}

ForceInline void main2(int argc, char **argv)
{
    FILE *fp, *fsc;
    char szOutFile[MAX_PATH], buf[0x1024];

    for (int i = 1; i != argc; ++i)
    {
        fp = fopen(argv[i], "rb");

        if (!fp) continue;

        strcpy(szOutFile, argv[i]);
//        rmext(szOutFile);
//        strcat(szOutFile, "_sc.txt");
        rmname(szOutFile);
        strcat(szOutFile, "sc.txt");
        fsc = fopen(szOutFile, "ab+");
        if (!fsc)
        {
            fclose(fp);
            continue;
        }

        while (fgets(buf, countof(buf), fp))
        {
            u32 v;
            char *pText, *pText2, *pName, *pName2;

            if (strnicmp(buf, ".message", 8))
                continue;

            pText  = strrchr(buf, '\t');
            pText2 = strrchr(buf, ' ');

            if (pText2)
                pText = max(pText2, pText);
            else if (!pText)
                continue;

            *pText++ = 0;
            pName  = strrchr(buf, '\t');
            pName2 = strrchr(buf, ' ');
            if (pName2)
                pName = max(pName, pName2);
            else if (!pName)
                continue;

            if ((UChar)(*++pName) < 0x80)
                pName = NULL;

            if (pName)
            {
                while(v = (UChar)*pName++)
                {
                    if (v < 0x80)
                        continue;
                    v = (v << 8) + (UChar)*pName++;
                    if (IsShiftJIS(v))
                    {
                        v = HIBYTE(v)|(LOBYTE(v) << 8);
                        fwrite(&v, 2, 1, fsc);
                    }
                }
            }

            if (pText)
            {
                while(v = (UChar)*pText++)
                {
                    if (v < 0x80)
                        continue;
                    v = (v << 8) + (UChar)*pText++;
                    if (IsShiftJIS(v))
                    {
                        v = HIBYTE(v)|(LOBYTE(v) << 8);
                        fwrite(&v, 2, 1, fsc);
                    }
                }
            }

//            printf("%s%s", pName ? pName : "", pText);
//            fprintf(fsc, "%s\t%s", pName ? pName : "", pText);
        }

        fclose(fp);
        fclose(fsc);
    }
}

void __cdecl main(int argc, char **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}