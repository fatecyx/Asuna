#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kaede")
#pragma comment(linker,"/MERGE:.CRT=.Kaede /MERGE:.ATL=.Kaede")
#pragma comment(linker,"/MERGE:.data=.Kaede")
#pragma comment(lib, "bass.lib")
#pragma comment(lib, "bass_aac.lib")

#include <Windows.h>
#include <algorithm>
#include "crt_h.h"
#include "my_crt.h"
#include "my_mem.h"

#pragma pack(1)

typedef struct
{
    BYTE key[256];
    BYTE a;
    BYTE b;
} SKey;

typedef struct
{
    u32 h1;
    BYTE seed[0x20];
    u32 h2;
} SSeed;

#pragma pack()

NoInline Void Mask1(const PBYTE pbSeed, u32 SeedSize, SKey *p)
{
    BYTE a, b, c, d;
    PBYTE pkey = p->key;

    for (int i = 0; i != sizeof(p->key); ++i)
    {
        pkey[i] = i;
    }

    p->a = p->b = 0;

    a = b = c = d = 0;
    for (int i = 0; i != sizeof(p->key); ++i)
    {
        a = pkey[i];
        b = pbSeed[c++];
        c %= SeedSize;
        d += a + b;
        pkey[i] = pkey[d];
        pkey[d] = a;
    }
}

NoInline Void Mask2(PBYTE pbDest, u32 size, SKey *p)
{
    BYTE a, b, c, d;
    PBYTE pkey;

    a = p->a;
    b = p->b;
    pkey = p->key;
    for (int i = 0; i != size; ++i)
    {
        c = pkey[++a];
        b += c;
        d = pkey[b];
        pkey[b] = c;
        pkey[a] = d;
        c += d;
        *pbDest++ ^= pkey[c];
    }

    p->a = a;
    p->b = b;
}

NoInline Void Mask3(u32 size, SKey *p)
{
    BYTE a, b, c, d, *pkey;

    a = p->a;
    b = p->b;
    pkey = p->key;

    for (u32 i = 0; i != size; ++i)
    {
        c = pkey[++a];
        b += c;
        d = pkey[b];
        pkey[b] = c;
        pkey[a] = d;
    }

    p->a = a;
    p->b = b;
}

ForceInline Void main2(int argc, char **argv)
{
    SKey  okey, deckey;
    SSeed seed;
    uchar sz_seed[] = "galstars_ef2";
    uchar seed_hash[] = "409f82efb7ffcaa58f6c15f3158a08c3";
    FILE *fp;
    u32 len, cur, *pdict;
    uchar *buf, *dict;

    if (argc < 2)
        return;

    Mask1(sz_seed, sizeof(sz_seed) - 1, &okey);
    memcpy(seed.seed, seed_hash, sizeof(seed_hash) - 1);
    for (int i = 1; i != argc; ++i)
    {
        fp = fopen(argv[i], "rb");
        if (!fp) return;

        len = fsize(fp);
        buf = (uchar *)malloc(len);
        dict = (uchar *)malloc(len >> 12 + 20);
        fread(buf, len, 1, fp);
        fclose(fp);

        cur = 0;
        pdict = (pu32)dict;

        int size = 0x1000;
        while (cur < len)
        {
            int r, s, h;

            s = cur >> 12;
            deckey = okey;
            Mask3(s * 4, &deckey);
            r = (s + 8 + 3) & ~3;
            ZeroMemory(dict, r);
            Mask2(dict, r, &deckey);

            if (len - cur < 0x1000)
            {
                size = len - cur;
            }

            h = *pdict;
            seed.h1 = h;
            seed.h2 = h ^ s;
            Mask1((PBYTE)&seed, sizeof(seed), &deckey);
            Mask3(0x24, &deckey);
            Mask2(buf + cur, size, &deckey);
            cur += size;
        }

        strcpy((char *)deckey.key, (char *)argv[i]);
        rmext((char *)deckey.key);
        strcat((char *)deckey.key, "_dec.paz");
        fp = fopen((char *)deckey.key, "wb");
        if (fp)
        {
            fwrite(buf, len, 1, fp);
            fclose(fp);
        }

        free(dict);
        free(buf);
    }

    return;
}

void __cdecl main(int argc, char **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}