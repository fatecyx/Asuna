#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")

#include <Windows.h>
#include "crt_h.h"
#include "my_crt.h"
#include "my_common.h"

Void TrimTail(Char *buf)
{
    Int len = strlen(buf) - 1;
    while (len > 0 && (buf[len] == '\r' || buf[len] == '\n'))
            buf[len--] = 0;
}

char* getsandtrim(Char *buf, size_t n, FILE *fp)
{
    char *i = fgets(buf, n, fp);
    TrimTail(buf);
    return i;
}

ForceInline Void main2(Int argc, Char **argv)
{
    if (argc < 3)
        return;

    DWORD len, comment;
    FILE *fcn, *fjp, *fout, *fp;
    Char name[MAX_PATH], buf1[0x1000], buf2[0x1000], buf3[0x1000], buf4[0x1000], buf5[0x1000];

    fcn = fopen(argv[1], "rb");
    if (!fcn)
        return;

    fjp = fopen(argv[2], "rb");
    if (!fjp)
    {
        fclose(fcn);
        return;
    }

    if (argc > 3)
        strcpy(name, argv[3]);
    else
    {
        strcpy(name, argv[1]);
        rmext(name);
        strcat(name, "_full.txt");
    }
    fout = fopen(name, "wb");
    if (!fout)
    {
        fclose(fcn);
        fclose(fjp);
        return;
    }

    comment = 0;
    fp = fcn;
    while (!feof(fjp) && !feof(fcn))
    {
        buf1[0] = 0;
        getsandtrim(buf1, sizeof(buf1), fcn);

        getsandtrim(buf2, sizeof(buf2), fjp);
        buf2[0] = 0;
        getsandtrim(buf2, sizeof(buf2), fjp);
        
        buf3[0] = 0;
        getsandtrim(buf3, sizeof(buf3), fjp);

        getsandtrim(buf4, sizeof(buf4), fjp);
        buf4[0] = 0;
        getsandtrim(buf4, sizeof(buf4), fcn);

        if (strcmp(buf2, buf4))
        {
            len = strlen(buf2);
            memset(buf5, 0, len * 2 + 4);
            len = MultiByteToWideChar(932, 0, buf2, len, (PWChar)buf5, sizeof(buf5) / sizeof(WChar));
            for (int i = 0; ; i++)
            {
                WChar c = ((PWChar)buf5)[i];
                if (c == 0)
                    break;
                else if (c == 0x30FB)
                    ((PWChar)buf5)[i] = L'¡¤';
            }
            len = WideCharToMultiByte(936, 0, (PWChar)buf5, len, buf2, sizeof(buf2), NULL, NULL);
            buf2[len] = 0;
            if (strcmp(buf2, buf4))
            {
                if (!comment)
                {
                    fprintf(fout, ";%s\n", findname(name));
                    comment = 1;
                }
                fprintf(fout, "%s\n", buf1);
                fprintf(fout, "%s\n", buf2);
                fprintf(fout, "%s\n", buf3);
                fprintf(fout, "%s\n", buf4);
            }
        }
        getsandtrim(buf1, sizeof(buf1), fcn);
        getsandtrim(buf1, sizeof(buf1), fcn);
    }

    len = fsize(fout);
    fclose(fcn);
    fclose(fjp);
    fclose(fout);
    if (len == 0)
        remove(name);
}

void __cdecl main(Int argc, Char **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}