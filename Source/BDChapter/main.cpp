#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")

#include "MyLibrary.cpp"

Char *szChapterName[] =
{
//    "アバンタイトル",
    "オープニング",
    "Aパート",
    "Bパート",
    "エンディング",
    "次回予告",
};

Char *szChapterYoshuga[] =
{
    "アバンタイトル",
    "オープニング",
    "Aパート",
    "Bパート",
    "エンディング",
    "Cパート",
    "エンディング2",
    "次回予告",
};

Char *szSorano[] =
{
    "Avant",
    "Opening",
    "A Part",
    "B Part",
    "Ending",
    "C Part",
    "Preview",
};

Char *szHighSchool[] =
{
    "Avant",
    "Opening",
    "A Part",
    "B Part",
    "Ending",
//    "C Part",
//    "Episode",
    "Next",
};

Char *szBakaTest[] =
{
    "Avant",
    "OP",
    "A Part",
    "B Part",
    "ED",
    "C Part",
    "Next",
    "またみてね",
};

Char *FateZero[] =
{
    "Avant",
    "Opening",
    "A Part",
    "B Part",
    "C Part",
    "D Part",
    "E Part",
    "Ending",
    "Next",
};


#define chapter szHighSchool

ForceInline void main2(int argc, wchar_t **argv)
{
    FILE *fp;
    u8 pts[14];
    u32 chp, ts[100];

    for (int i = 1; i != argc; ++i)
    {
        fp = _wfopen(argv[i], L"rb");
        if (fp == NULL)
        {
            _wperror(argv[i]);
            continue;
        }

        if (fseek(fp, -14, SEEK_END) != 0)
        {
            wprintf(L"%s: Invalid mpls file\n", argv[i]);
            fclose(fp);
            continue;
        }

        chp = 0;
        do
        {
            if (!fread(pts, 14, 1, fp) || pts[13])
                break;
            ts[chp] = Bswap(*(pu32)&pts[4]) - pts[13];
            ++chp;
        } while (!fseek(fp, -28, SEEK_CUR));

        fclose(fp);

        if (chp)
        {
            wchar_t name[MAX_PATH];

            printf("%u chapters\n\n", chp);

            u32 cnt, offset = ts[chp - 1];

            wcscpy(name, argv[i]);
            rmextw(name);
            wcscat(name, L".Chapter.txt");
            fp = _wfopen(name, L"wb");
            if (!fp)
            {
                _wperror(name);
                continue;
            }

            bool first = true;

            cnt = 0;
            while (chp--)
            {
                u64 t;
                double timestamp;
/*
                if (first && cnt == countof(chapter) - 1)
                    ++cnt;
*/
                if (/*first && */cnt == countof(chapter))
                {
                    first = false;
                    cnt = 0;
#if 1
                    offset = ts[chp];
#endif
                }

                ts[chp] -= offset;
                timestamp = ts[chp] / 45000.0;
                t = (u64)timestamp;

                ++cnt;
                fprintf(fp, "CHAPTER%02u=%02I64u:%02I64u:%06.3f\r\n"
                            "CHAPTER%02uNAME=%s\r\n",
                            cnt, t / 3600, t / 60 % 60, fmod(timestamp, 60), cnt,
                            chapter[cnt - 1]);
            }

            fclose(fp);
        }

    }
}

void __cdecl main(int argc, wchar_t **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}