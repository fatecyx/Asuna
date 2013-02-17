#pragma comment(linker, "/MERGE:.text=.Kaede /SECTION:.Kaede,ERW")
#pragma comment(linker, "/MERGE:.rdata=.Kaede")

#include "my_common.h"
#include "nt_api.h"

EXTC ASM uint_32 LBEncode(void *dst, size_t dstsize, void *src, size_t srcsize)
{
    __asm
    {
        sub     esp, 024h;
        push    ebx;
        push    ebp;
        push    esi;
        mov     esi, dword ptr [esp+038h];  // dstsize
        push    edi;
        push    esi;
        push    HEAP_ZERO_MEMORY;
        call    Nt_GetProcessHeap;
        push    eax;
        call    dword ptr [RtlAllocateHeap];
        mov     ebx, eax;
        add      dword ptr [esp+38h], 2;
        mov     eax, dword ptr [esp+040h]; // *src
        mov     dword ptr [esp+020h], eax;
        mov     eax, dword ptr [esp+044h]; // srcsize
        test    eax, eax;
        mov     edi, 8;
        mov     ebp, ebx;
        mov     esi, 2;
        mov     dword ptr [esp+030h], ebx;
        mov     dword ptr [esp+028h], edi;
        mov     dword ptr [esp+024h], ebp;
        mov     dword ptr [esp+02Ch], esi;
        mov     dword ptr [esp+01Ch], 0;
        je      FALCOM_00401819;

FALCOM_004012C2:

        mov     ecx, dword ptr [esp+044h];
        mov     edx, dword ptr [esp+040h];
        push    ecx;
        push    edx;
        call    _FALCOM_004011F0;
        add     esp, 8;
        cmp     eax, 0Eh;
        mov     dword ptr [esp+014h], eax;
        jb      FALCOM_00401409;
        push    7;
        push    3;
        lea     ecx, dword ptr [esp+02Ch];
        call    _FALCOM_00401110;
        mov     eax, dword ptr [esp+02Ch];
        mov     ecx, dword ptr [esp+030h];
        mov     edi, dword ptr [esp+014h];
        mov     edx, dword ptr [esp+028h];
        mov     byte ptr [eax+ecx], 1;
        inc     eax;
        lea     ebx, dword ptr [edi-0Eh];
        cmp     ebx, 0Fh;
        mov     dword ptr [esp+02Ch], eax;
        jbe     FALCOM_00401365;
        test    edx, edx;
        jnz     FALCOM_0040132B;
        lea     esi, dword ptr [eax+ecx];
        add     eax, 2;
        mov     word ptr [esi], dx;
        mov     dword ptr [esp+024h], esi;
        mov     edx, 010h;
        mov     dword ptr [esp+02Ch], eax;
        jmp     FALCOM_0040132F;

FALCOM_0040132B:

        mov     esi, dword ptr [esp+024h];

FALCOM_0040132F:

        mov     ecx, 010h;
        sub     ecx, edx;
        mov     eax, 1;
        shl     eax, cl;
        push    4;
        shr     ebx, 8;
        push    ebx;
        or      word ptr [esi], ax;
        dec     edx;
        lea     ecx, dword ptr [esp+02Ch];
        mov     dword ptr [esp+030h], edx;
        call    _FALCOM_00401180;
        mov     esi, dword ptr [esp+02Ch];
        mov     ebx, dword ptr [esp+030h];
        lea     eax, dword ptr [edi-0Eh];
        mov     byte ptr [esi+ebx], al;
        inc     esi;
        jmp     FALCOM_004013AD;

FALCOM_00401365:

        test    edx, edx;
        jnz     FALCOM_00401382;
        add     ecx, eax;
        mov     esi, ecx;
        add     eax, 2;
        mov     word ptr [ecx], dx;
        mov     dword ptr [esp+024h], esi;
        mov     edx, 010h;
        mov     dword ptr [esp+02Ch], eax;
        jmp     FALCOM_00401386;

FALCOM_00401382:

        mov     esi, dword ptr [esp+024h];

FALCOM_00401386:

        mov     ecx, 010h;
        sub     ecx, edx;
        xor     eax, eax;
        shl     eax, cl;
        push    4;
        push    ebx;
        lea     ecx, dword ptr [esp+02Ch];
        or      word ptr [esi], ax;
        dec     edx;
        mov     dword ptr [esp+030h], edx;
        call    _FALCOM_00401180;
        mov     esi, dword ptr [esp+02Ch];
        mov     ebx, dword ptr [esp+030h];

FALCOM_004013AD:

        mov     eax, dword ptr [esp+040h];
        mov     cl, byte ptr [eax];
        mov     ebp, dword ptr [esp+024h];
        add     eax, edi;
        mov     dword ptr [esp+040h], eax;
        sub     dword ptr [esp+044h], edi;
        mov     eax, dword ptr [esp+01Ch];
        mov     edx, 01FFFh;
        mov     byte ptr [esi+ebx], cl;
        inc     esi;
        sub     edx, eax;
        cmp     edi, edx;
        mov     dword ptr [esp+02Ch], esi;
        ja      FALCOM_004013E7;
        add     eax, edi;
        mov     edi, dword ptr [esp+028h];
        mov     dword ptr [esp+01Ch], eax;
        jmp     FALCOM_0040180D;

FALCOM_004013E7:

        add     edi, eax;
        mov     eax, dword ptr [esp+020h];
        lea     ecx, dword ptr [eax+edi-01FFFh];
        mov     edi, dword ptr [esp+028h];
        mov     dword ptr [esp+020h], ecx;
        mov     dword ptr [esp+01Ch], 01FFFh;
        jmp     FALCOM_0040180D;

FALCOM_00401409:

        mov     eax, dword ptr [esp+044h];
        cmp     eax, 010Dh;
        mov     dword ptr [esp+010h], eax;
        jb      FALCOM_00401420;
        mov     dword ptr [esp+010h], 010Dh;

FALCOM_00401420:

        mov     eax, dword ptr [esp+040h];
        lea     edx, dword ptr [esp+010h];
        push    edx;
        push    eax;
        lea     ecx, dword ptr [esp+024h];
        call    _FALCOM_00401000;
        cmp     eax, -1;
        mov     dword ptr [esp+018h], eax;
        je      FALCOM_0040157F;
        test    edi, edi;
        jnz     FALCOM_0040145B;
        lea     ebp, dword ptr [esi+ebx];
        add     esi, 2;
        mov     word ptr [ebp], di;
        mov     dword ptr [esp+024h], ebp;
        mov     edi, 010h;
        mov     dword ptr [esp+02Ch], esi;

FALCOM_0040145B:

        mov     ecx, 010h;
        sub     ecx, edi;
        mov     edx, 1;
        shl     edx, cl;
        or      word ptr [ebp], dx;
        dec     edi;
        cmp     eax, 0FFh;
        jbe     FALCOM_004014CC;
        test    edi, edi;
        jnz     FALCOM_00401490;
        add     ebx, esi;
        mov     ebp, ebx;
        add     esi, 2;
        mov     word ptr [ebx], di;
        mov     dword ptr [esp+024h], ebp;
        mov     edi, 010h;
        mov     dword ptr [esp+02Ch], esi;

FALCOM_00401490:

        mov     ecx, 010h;
        sub     ecx, edi;
        mov     edx, 1;
        shl     edx, cl;
        push    5;
        shr     eax, 8;
        push    eax;
        or      word ptr [ebp], dx;
        dec     edi;
        lea     ecx, dword ptr [esp+02Ch];
        mov     dword ptr [esp+030h], edi;
        call    _FALCOM_00401180;
        mov     esi, dword ptr [esp+02Ch];
        mov     edi, dword ptr [esp+028h];
        mov     ebx, dword ptr [esp+030h];
        mov     ebp, dword ptr [esp+024h];
        mov     eax, dword ptr [esp+018h];
        jmp     FALCOM_004014F7;

FALCOM_004014CC:

        test    edi, edi;
        jnz     FALCOM_004014E3;
        lea     ebp, dword ptr [esi+ebx];
        mov     word ptr [ebp], di;
        mov     dword ptr [esp+024h], ebp;
        mov     edi, 010h;
        add     esi, 2;

FALCOM_004014E3:

        mov     ecx, 010h;
        sub     ecx, edi;
        xor     edx, edx;
        shl     edx, cl;
        or      word ptr [ebp], dx;
        dec     edi;
        mov     dword ptr [esp+028h], edi;

FALCOM_004014F7:

        mov     byte ptr [esi+ebx], al;
        mov     eax, dword ptr [esp+010h];
        inc     esi;
        mov     edx, 2;
        cmp     eax, edx;
        mov     dword ptr [esp+02Ch], esi;
        jnz     FALCOM_00401660;
        test    edi, edi;
        jnz     FALCOM_0040152A;
        lea     ebp, dword ptr [esi+ebx];
        add     esi, edx;
        mov     word ptr [ebp], di;
        mov     dword ptr [esp+024h], ebp;
        mov     edi, 010h;
        mov     dword ptr [esp+02Ch], esi;

FALCOM_0040152A:

        mov     ecx, 010h;
        sub     ecx, edi;
        mov     eax, 1;
        shl     eax, cl;
        sub     dword ptr [esp+044h], edx;
        or      word ptr [ebp], ax;
        add     dword ptr [esp+040h], edx;
        mov     eax, dword ptr [esp+01Ch];
        mov     ecx, 01FFFh;
        dec     edi;
        sub     ecx, eax;
        cmp     ecx, edx;
        mov     dword ptr [esp+028h], edi;
        jb      FALCOM_00401563;
        add     eax, edx;
        mov     dword ptr [esp+01Ch], eax;
        jmp     FALCOM_0040180D;

FALCOM_00401563:

        mov     edx, dword ptr [esp+020h];
        lea     eax, dword ptr [edx+eax-01FFDh];
        mov     dword ptr [esp+020h], eax;
        mov     dword ptr [esp+01Ch], 01FFFh;
        jmp     FALCOM_0040180D;

FALCOM_0040157F:

        mov     eax, dword ptr [esp+01Ch];
        mov     edx, dword ptr [esp+014h];
        mov     ecx, 01FFFh;
        sub     ecx, eax;
        cmp     edx, 3;
        jbe     FALCOM_004017A2;
        cmp     ecx, 1;
        jb      FALCOM_004015A3;
        inc     eax;
        mov     dword ptr [esp+01Ch], eax;
        jmp     FALCOM_004015BA;

FALCOM_004015A3:

        mov     ecx, dword ptr [esp+020h];
        lea     eax, dword ptr [ecx+eax-01FFEh];
        mov     dword ptr [esp+020h], eax;
        mov     dword ptr [esp+01Ch], 01FFFh;

FALCOM_004015BA:

        test    edi, edi;
        jnz     FALCOM_004015D1;
        lea     ebp, dword ptr [esi+ebx];
        mov     word ptr [ebp], di;
        mov     dword ptr [esp+024h], ebp;
        mov     edi, 010h;
        add     esi, 2;

FALCOM_004015D1:

        xor     eax, eax;
        mov     ecx, 010h;
        sub     ecx, edi;
        shl     eax, cl;
        or      word ptr [ebp], ax;
        mov     eax, dword ptr [esp+040h];
        mov     cl, byte ptr [eax];
        dec     edi;
        mov     byte ptr [esi+ebx], cl;
        mov     ecx, dword ptr [esp+044h];
        inc     esi;
        inc     eax;
        dec     ecx;
        dec     edx;
        test    edi, edi;
        mov     dword ptr [esp+040h], eax;
        mov     dword ptr [esp+044h], ecx;
        mov     dword ptr [esp+010h], edx;
        jnz     FALCOM_00401615;
        lea     ebp, dword ptr [esi+ebx];
        mov     word ptr [ebp], di;
        mov     dword ptr [esp+024h], ebp;
        mov     edi, 010h;
        add     esi, 2;

FALCOM_00401615:

        mov     ecx, 010h;
        sub     ecx, edi;
        mov     edx, 1;
        shl     edx, cl;
        or      word ptr [ebp], dx;
        dec     edi;
        jnz     FALCOM_0040163F;
        lea     ebp, dword ptr [esi+ebx];
        mov     word ptr [ebp], 0;
        mov     dword ptr [esp+024h], ebp;
        mov     edi, 010h;
        add     esi, 2;

FALCOM_0040163F:

        xor     eax, eax;
        mov     ecx, 010h;
        sub     ecx, edi;
        shl     eax, cl;
        or      word ptr [ebp], ax;
        mov     eax, dword ptr [esp+010h];
        dec     edi;
        mov     byte ptr [esi+ebx], 1;
        inc     esi;
        mov     dword ptr [esp+028h], edi;
        mov     dword ptr [esp+02Ch], esi;

FALCOM_00401660:

        cmp     eax, 3;
        jnz     FALCOM_004016C7;
        test    edi, edi;
        jnz     FALCOM_00401680;
        lea     ebp, dword ptr [esi+ebx];
        add     esi, 2;
        mov     word ptr [ebp], di;
        mov     dword ptr [esp+024h], ebp;
        mov     edi, 010h;
        mov     dword ptr [esp+02Ch], esi;

FALCOM_00401680:

        mov     ecx, 010h;
        sub     ecx, edi;
        xor     edx, edx;
        shl     edx, cl;
        or      word ptr [ebp], dx;
        dec     edi;
        jnz     FALCOM_004016AB;
        lea     ebp, dword ptr [esi+ebx];
        add     esi, 2;
        mov     word ptr [ebp], 0;
        mov     dword ptr [esp+024h], ebp;
        mov     edi, 010h;
        mov     dword ptr [esp+02Ch], esi;

FALCOM_004016AB:

        mov     ecx, 010h;
        sub     ecx, edi;
        mov     edx, 1;
        shl     edx, cl;
        or      word ptr [ebp], dx;
        dec     edi;
        mov     dword ptr [esp+028h], edi;
        jmp     FALCOM_00401759;

FALCOM_004016C7:

        cmp     eax, 4;
        lea     ecx, dword ptr [esp+024h];
        jnz     FALCOM_004016D4;
        push    2;
        jmp     FALCOM_004016DB;

FALCOM_004016D4:

        cmp     eax, 5;
        jnz     FALCOM_004016F7;
        push    3;

FALCOM_004016DB:

        push    0;
        call    _FALCOM_00401110;
        push    1;
        lea     ecx, dword ptr [esp+028h];
        call    _FALCOM_004010C0;
        mov     esi, dword ptr [esp+02Ch];
        mov     ebx, dword ptr [esp+030h];
        jmp     FALCOM_0040174D;

FALCOM_004016F7:

        cmp     eax, 0Dh;
        ja      FALCOM_0040172D;
        push    4;
        push    0;
        call    _FALCOM_00401110;
        push    1;
        lea     ecx, dword ptr [esp+028h];
        call    _FALCOM_004010C0;
        mov     eax, dword ptr [esp+010h];
        push    3;
        add     eax, -6;
        push    eax;
        lea     ecx, dword ptr [esp+02Ch];
        call    _FALCOM_00401180;
        mov     esi, dword ptr [esp+02Ch];
        mov     ebx, dword ptr [esp+030h];
        jmp     FALCOM_0040174D;

FALCOM_0040172D:

        push    5;
        push    0;
        call    _FALCOM_00401110;
        mov     cl, byte ptr [esp+010h];
        mov     esi, dword ptr [esp+02Ch];
        mov     ebx, dword ptr [esp+030h];
        sub     cl, 0Eh;
        mov     byte ptr [esi+ebx], cl;
        inc     esi;
        mov     dword ptr [esp+02Ch], esi;

FALCOM_0040174D:

        mov     edi, dword ptr [esp+028h];
        mov     ebp, dword ptr [esp+024h];
        mov     eax, dword ptr [esp+010h];

FALCOM_00401759:

        mov     edx, dword ptr [esp+044h];
        mov     ecx, dword ptr [esp+040h];
        sub     edx, eax;
        add     ecx, eax;
        mov     dword ptr [esp+044h], edx;
        mov     dword ptr [esp+040h], ecx;
        mov     ecx, dword ptr [esp+01Ch];
        mov     edx, 01FFFh;
        sub     edx, ecx;
        cmp     eax, edx;
        ja      FALCOM_00401787;
        add     ecx, eax;
        mov     dword ptr [esp+01Ch], ecx;
        jmp     FALCOM_0040180D;

FALCOM_00401787:

        add     eax, ecx;
        mov     ecx, dword ptr [esp+020h];
        lea     edx, dword ptr [ecx+eax-01FFFh];
        mov     dword ptr [esp+020h], edx;
        mov     dword ptr [esp+01Ch], 01FFFh;
        jmp     FALCOM_0040180D;

FALCOM_004017A2:

        cmp     ecx, 1;
        jb      FALCOM_004017AE;
        inc     eax;
        mov     dword ptr [esp+01Ch], eax;
        jmp     FALCOM_004017C5;

FALCOM_004017AE:

        mov     edx, dword ptr [esp+020h];
        lea     eax, dword ptr [edx+eax-01FFEh];
        mov     dword ptr [esp+020h], eax;
        mov     dword ptr [esp+01Ch], 01FFFh;

FALCOM_004017C5:

        test    edi, edi;
        jnz     FALCOM_004017DC;
        lea     ebp, dword ptr [esi+ebx];
        mov     word ptr [ebp], di;
        mov     dword ptr [esp+024h], ebp;
        mov     edi, 010h;
        add     esi, 2;

FALCOM_004017DC:

        mov     eax, dword ptr [esp+040h];
        xor     edx, edx;
        mov     ecx, 010h;
        sub     ecx, edi;
        shl     edx, cl;
        or      word ptr [ebp], dx;
        mov     cl, byte ptr [eax];
        dec     edi;
        inc     esi;
        mov     byte ptr [esi+ebx-1], cl;
        inc     eax;
        mov     dword ptr [esp+040h], eax;
        mov     eax, dword ptr [esp+044h];
        dec     eax;
        mov     dword ptr [esp+028h], edi;
        mov     dword ptr [esp+02Ch], esi;
        mov     dword ptr [esp+044h], eax;

FALCOM_0040180D:

        mov     eax, dword ptr [esp+044h];
        test    eax, eax;
        jnz     FALCOM_004012C2;

FALCOM_00401819:

        push    7;
        push    3;
        lea     ecx, dword ptr [esp+02Ch];
        call    _FALCOM_00401110;
        mov     ecx, dword ptr [esp+02Ch];
        mov     eax, dword ptr [esp+030h];
        mov     edi, dword ptr [esp+038h];
        lea     ebx, dword ptr [ecx+1];
        mov     byte ptr [ecx+eax], 0;
        mov     ecx, ebx;
        mov     edx, ecx;
        shr     ecx, 2;
        mov     esi, eax;
        rep     movs dword ptr es:[edi], dword ptr [esi];
        mov     ecx, edx;
        and     ecx, 3;
        push    eax;
        rep     movs byte ptr es:[edi], byte ptr [esi];
        push    0;
        call    Nt_GetProcessHeap;
        push    eax;
        call    dword ptr [RtlFreeHeap];
        pop     edi;
        pop     esi;
        pop     ebp;
        lea      eax, dword ptr [ebx+2];
        mov    ebx, dword ptr [esp+2Ch];
        mov    word ptr [ebx-2], ax;
        inc      eax;
        pop     ebx;
        add     esp, 024h;
        ret		10h;
_FALCOM_00401180:
        push    edi
            mov     edi, dword ptr [esp+0Ch]
        test    edi, edi
            mov     eax, ecx
            je      FALCOM_004011E5
            push    ebx
            mov     ebx, dword ptr [esp+0Ch]
        push    ebp
            push    esi
            lea     esi, dword ptr [edi-1]

FALCOM_00401195:

        mov     ecx, dword ptr [eax+4]
        test    ecx, ecx
            jnz     FALCOM_004011BF
            mov     ecx, dword ptr [eax+8]
        mov     edx, dword ptr [eax+0Ch]
        mov     word ptr [ecx+edx], 0
            mov     ecx, dword ptr [eax+8]
        mov     edx, dword ptr [eax+0Ch]
        add     edx, ecx
            add     ecx, 2
            mov     dword ptr [eax], edx
            mov     dword ptr [eax+4], 010h
            mov     dword ptr [eax+8], ecx

FALCOM_004011BF:

        mov     edx, dword ptr [eax]
        mov     ecx, esi
            mov     ebp, ebx
            shr     ebp, cl
            mov     ecx, 010h
            sub     ecx, dword ptr [eax+4]
        and     ebp, 1
            shl     ebp, cl
            or      word ptr [edx], bp
            mov     ebp, dword ptr [eax+4]
        dec     ebp
            dec     esi
            dec     edi
            mov     dword ptr [eax+4], ebp
            jnz     FALCOM_00401195
            pop     esi
            pop     ebp
            pop     ebx

FALCOM_004011E5:

        pop     edi
            ret     8
_FALCOM_00401000:
        sub     esp, 010h
            mov     eax, dword ptr [ecx]
        cmp     eax, 3
            mov     dword ptr [esp+4], ecx
            jnb     FALCOM__00401017
            or      eax, 0FFFFFFFFh
            add     esp, 010h
            ret     8

FALCOM__00401017:

        push    ebx
            mov     ebx, dword ptr [esp+01Ch]
        cmp     dword ptr [ebx], eax
            push    edi
            mov     edi, 2
            mov     dword ptr [esp+8], edi
            jbe     FALCOM__0040102C
            mov     dword ptr [ebx], eax

FALCOM__0040102C:

        push    esi
            mov     esi, dword ptr [ecx]
        lea     edx, dword ptr [esi-3]
        test    edx, edx
            mov     dword ptr [esp+014h], esi
            jl      FALCOM__00401099
            mov     ecx, dword ptr [ebx]
        push    ebp
            mov     ebp, dword ptr [esp+024h]
        mov     dword ptr [esp+01Ch], ecx
            lea     ebx, dword ptr [ecx+edx]
        sub     ebp, edx
            jmp     FALCOM__00401050

FALCOM__0040104C:

        mov     esi, dword ptr [esp+018h]

FALCOM__00401050:

        cmp     ebx, esi
            ja      FALCOM__00401056
            mov     esi, ebx

FALCOM__00401056:

        cmp     edx, esi
            mov     eax, edx
            jnb     FALCOM__00401078
            mov     ecx, dword ptr [esp+014h]
        mov     edi, dword ptr [ecx+4]

FALCOM__00401063:

        mov     cl, byte ptr [edi+eax]
        cmp     cl, byte ptr [eax+ebp]
        jnz     FALCOM__00401070
            inc     eax
            cmp     eax, esi
            jb      FALCOM__00401063

FALCOM__00401070:

        mov     edi, dword ptr [esp+010h]
        mov     ecx, dword ptr [esp+01Ch]

FALCOM__00401078:

        sub     eax, edx
            cmp     eax, edi
            jbe     FALCOM__0040108C
            cmp     eax, ecx
            mov     edi, eax
            mov     dword ptr [esp+024h], edx
            mov     dword ptr [esp+010h], edi
            je      FALCOM__00401093

FALCOM__0040108C:

        dec     edx
            dec     ebx
            inc     ebp
            test    edx, edx
            jge     FALCOM__0040104C

FALCOM__00401093:

        cmp     edi, 3
            pop     ebp
            jnb     FALCOM__004010A5

FALCOM__00401099:

        pop     esi
            pop     edi
            or      eax, 0FFFFFFFFh
            pop     ebx
            add     esp, 010h
            ret     8

FALCOM__004010A5:

        mov     edx, dword ptr [esp+024h]
        mov     eax, dword ptr [esp+010h]
        mov     ecx, dword ptr [esp+020h]
        pop     esi
            mov     dword ptr [edx], edi
            mov     eax, dword ptr [eax]
        pop     edi
            sub     eax, ecx
            pop     ebx
            add     esp, 010h
            ret     8;
_FALCOM_004010C0:
        mov     eax, ecx
            mov     ecx, dword ptr [eax+4]
        test    ecx, ecx
            jnz     FALCOM_004010EC
            mov     ecx, dword ptr [eax+8]
        mov     edx, dword ptr [eax+0Ch]
        mov     word ptr [ecx+edx], 0
            mov     ecx, dword ptr [eax+8]
        mov     edx, dword ptr [eax+0Ch]
        add     edx, ecx
            add     ecx, 2
            mov     dword ptr [eax], edx
            mov     dword ptr [eax+4], 010h
            mov     dword ptr [eax+8], ecx

FALCOM_004010EC:

        xor     edx, edx
            mov     dl, byte ptr [esp+4]
        push    esi
            mov     esi, dword ptr [eax]
        push    edi
            mov     edi, dword ptr [eax+4]
        mov     ecx, 010h
            sub     ecx, edi
            and     edx, 1
            shl     edx, cl
            pop     edi
            or      word ptr [esi], dx
            dec     dword ptr [eax+4]
        pop     esi
            ret     4
_FALCOM_00401110:
        push    edi
            mov     edi, dword ptr [esp+0Ch]
        test    edi, edi
            mov     eax, ecx
            je      FALCOM_00401171
            mov     edx, dword ptr [esp+8]
        push    ebx
            push    esi

FALCOM_00401121:

        mov     ecx, dword ptr [eax+4]
        test    ecx, ecx
            jnz     FALCOM_0040114B
            mov     ecx, dword ptr [eax+8]
        mov     esi, dword ptr [eax+0Ch]
        mov     word ptr [ecx+esi], 0
            mov     ecx, dword ptr [eax+8]
        mov     esi, dword ptr [eax+0Ch]
        add     esi, ecx
            add     ecx, 2
            mov     dword ptr [eax], esi
            mov     dword ptr [eax+4], 010h
            mov     dword ptr [eax+8], ecx

FALCOM_0040114B:

        mov     ebx, dword ptr [eax+4]
        mov     esi, dword ptr [eax]
        mov     ecx, 010h
            sub     ecx, ebx
            xor     ebx, ebx
            mov     bl, dl
            shr     edx, 1
            and     ebx, 1
            shl     ebx, cl
            or      word ptr [esi], bx
            mov     ebx, dword ptr [eax+4]
        dec     ebx
            dec     edi
            mov     dword ptr [eax+4], ebx
            jnz     FALCOM_00401121
            pop     esi
            pop     ebx

FALCOM_00401171:

        pop     edi
            ret     8

_FALCOM_004011F0:
        mov     ecx, dword ptr [esp+4]       ; 源文件地址
            push    ebx
            push    esi
            push    edi
            mov     edi, dword ptr [esp+014h]    ; 块大小
            mov     eax, 1
            dec     edi
            mov     esi, 3

FALCOM_00401206:

        cmp     eax, edi
            jnb     FALCOM_0040125A
            mov     bl, byte ptr [ecx+1]
        cmp     byte ptr [ecx], bl
            jnz     FALCOM_0040125A
            lea     edx, dword ptr [esi-1]
        cmp     edx, edi
            jnb     FALCOM_0040124B
            mov     dl, byte ptr [ecx+2]
        cmp     bl, dl
            jnz     FALCOM_0040124B
            cmp     esi, edi
            jnb     FALCOM_00401250
            mov     bl, byte ptr [ecx+3]
        cmp     dl, bl
            jnz     FALCOM_00401250
            lea     edx, dword ptr [esi+1]
        cmp     edx, edi
            jnb     FALCOM_00401257
            cmp     bl, byte ptr [ecx+4]
        jnz     FALCOM_00401257
            add     esi, 4
            add     eax, 4
            add     ecx, 4
            cmp     esi, 0100Fh
            jb      FALCOM_00401206
            pop     edi
            pop     esi
            pop     ebx
            ret

FALCOM_0040124B:

        pop     edi
            pop     esi
            inc     eax
            pop     ebx
            ret

FALCOM_00401250:

        pop     edi
            pop     esi
            add     eax, 2
            pop     ebx
            ret

FALCOM_00401257:

        add     eax, 3

FALCOM_0040125A:

        pop     edi
            pop     esi
            pop     ebx
            ret
    }
}