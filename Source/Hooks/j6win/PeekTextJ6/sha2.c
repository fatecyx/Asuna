#include "sha2.h"

ASM Void STDCALL sha256(PByte message, UInt len, PByte digest)
{
    static ULong table[] = 
    {
        0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5, 0xD807AA98, 0x12835B01, 
        0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174, 0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 
        0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA, 0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 
        0x06CA6351, 0x14292967, 0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85, 
        0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070, 0x19A4C116, 0x1E376C08, 
        0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3, 0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 
        0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
    };

    __asm
    {
            push    ebp
            mov     ebp, esp
            add     esp, -080h
            push    edi
            push    esi
            mov     edx, dword ptr [ebp+010h]
            mov     edi, dword ptr [ebp+0Ch]
            mov     esi, dword ptr [ebp+8]
            mov     dword ptr [edx], 06A09E667h
            mov     dword ptr [edx+4], 0BB67AE85h
            mov     dword ptr [edx+8], 03C6EF372h
            mov     dword ptr [edx+0Ch], 0A54FF53Ah
            mov     dword ptr [edx+010h], 0510E527Fh
            mov     dword ptr [edx+014h], 09B05688Ch
            mov     dword ptr [edx+018h], 01F83D9ABh
            mov     dword ptr [edx+01Ch], 05BE0CD19h
            shr     edi, 6
            je      sha2_7160801C

sha2_7160800D:

        push    dword ptr [ebp+010h]
            push    esi
            call    sha2_71608078            ;<= Jump/Call 地址无法决定
            add     esi, 040h
            dec     edi
            jnz     sha2_7160800D

sha2_7160801C:

        mov     ecx, dword ptr [ebp+0Ch]
            lea     edi, dword ptr [ebp-080h]
            and     ecx, 03Fh
            push    dword ptr [ebp+010h]
            push    edi
            mov     eax, ecx
            cld
            rep     movs byte ptr es:[edi], byte ptr [esi]
            mov     byte ptr [edi], 080h
            inc     edi
            mov     ecx, eax
            xor     eax, eax
            bswap   esi
            sub     ecx, 037h
            ja      sha2_71608043
            neg     ecx
            rep     stos byte ptr es:[edi]
            jmp     sha2_71608056

sha2_71608043:

        sub     ecx, 040h
            neg     ecx
            rep     stos byte ptr es:[edi]
            call    sha2_71608078            ;<= Jump/Call 地址无法决定
            lea     edx, dword ptr [ebp-040h]
            push    dword ptr [ebp+010h]
            push    edx

sha2_71608056:

        mov     esi, dword ptr [ebp+0Ch]
            mov     eax, esi
            rol     esi, 3
            shl     eax, 3
            and     esi, 7
            bswap   eax
            bswap   esi
            mov     dword ptr [edi+4], eax
            mov     dword ptr [edi], esi
            call    sha2_71608078            ;<= Jump/Call 地址无法决定
            pop     esi
            pop     edi
            leave
            ret     0Ch                          ;<= Procedure End


sha2_71608078:                           ;<= Procedure Start

        sub     esp, 0128h
        mov     dword ptr [esp+0Ch], ebp
        mov     dword ptr [esp+8], ebx
        mov     dword ptr [esp+4], edi
        mov     dword ptr [esp], esi
        mov     esi, dword ptr [esp+012Ch]
        mov     eax, dword ptr [esi]
        mov     ebx, dword ptr [esi+4]
        mov     ecx, dword ptr [esi+8]
        mov     edx, dword ptr [esi+0Ch]
        mov     ebp, dword ptr [esi+010h]
        mov     edi, dword ptr [esi+014h]
        bswap   eax
        bswap   ebx
        bswap   ecx
        bswap   edx
        bswap   ebp
        bswap   edi
        mov     dword ptr [esp+028h], eax
        mov     dword ptr [esp+02Ch], ebx
        mov     dword ptr [esp+030h], ecx
        mov     dword ptr [esp+034h], edx
        mov     dword ptr [esp+038h], ebp
        mov     dword ptr [esp+03Ch], edi
        mov     eax, dword ptr [esi+018h]
        mov     ebx, dword ptr [esi+01Ch]
        mov     ecx, dword ptr [esi+020h]
        mov     edx, dword ptr [esi+024h]
        mov     ebp, dword ptr [esi+028h]
        mov     edi, dword ptr [esi+02Ch]
        bswap   eax
        bswap   ebx
        bswap   ecx
        bswap   edx
        bswap   ebp
        bswap   edi
        mov     dword ptr [esp+040h], eax
        mov     dword ptr [esp+044h], ebx
        mov     dword ptr [esp+048h], ecx
        mov     dword ptr [esp+04Ch], edx
        mov     dword ptr [esp+050h], ebp
        mov     dword ptr [esp+054h], edi
        mov     eax, dword ptr [esi+030h]
        mov     ebx, dword ptr [esi+034h]
        mov     ecx, dword ptr [esi+038h]
        mov     edx, dword ptr [esi+03Ch]
        bswap   eax
        bswap   ebx
        bswap   ecx
        bswap   edx
        mov     dword ptr [esp+058h], eax
        mov     dword ptr [esp+05Ch], ebx
        mov     dword ptr [esp+060h], ecx
        mov     dword ptr [esp+064h], edx
        mov     ecx, -0C0h
        mov     esi, dword ptr [esp+0130h]
        nop

sha2_71608130:

        mov     eax, dword ptr [esp+ecx+0ECh]
        mov     ebx, dword ptr [esp+ecx+0120h]
        mov     edi, dword ptr [esp+ecx+010Ch]
        mov     ebp, eax
        mov     edx, ebx
        ror     eax, 7
        shr     ebp, 3
        ror     ebx, 011h
        shr     edx, 0Ah
        xor     ebp, eax
        ror     eax, 0Bh
        xor     edx, ebx
        ror     ebx, 2
        xor     eax, ebp
        add     edi, dword ptr [esp+ecx+0E8h]
        xor     ebx, edx
        add     edi, eax
        add     edi, ebx
        mov     dword ptr [esp+ecx+0128h], edi
        add     ecx, 4
        jnz     sha2_71608130
        mov     eax, dword ptr [esi]
        mov     ebx, dword ptr [esi+4]
        mov     ecx, dword ptr [esi+8]
        mov     edx, dword ptr [esi+0Ch]
        mov     ebp, dword ptr [esi+010h]
        mov     edi, dword ptr [esi+014h]
        mov     dword ptr [esp+010h], ebx
        mov     dword ptr [esp+014h], ecx
        mov     dword ptr [esp+018h], edx
        mov     dword ptr [esp+01Ch], edi
        mov     ebx, dword ptr [esi+018h]
        mov     edx, dword ptr [esi+01Ch]
        mov     dword ptr [esp+020h], ebx
        mov     ecx, -0100h
        lea     esi, dword ptr [esi]

sha2_716081B0:

        mov     ebx, ebp
        add     edx, dword ptr [esp+ecx+0128h]
        mov     edi, ebp
        ror     ebx, 6
        mov     esi, ebp
        ror     edi, 0Bh
        add     edx, dword ptr [ecx+table+100h]
        ror     esi, 019h
        xor     ebx, edi
        mov     edi, dword ptr [esp+020h]
        xor     ebx, esi
        mov     esi, dword ptr [esp+01Ch]
        mov     dword ptr [esp+01Ch], ebp
        mov     dword ptr [esp+020h], esi
        xor     esi, edi
        mov     dword ptr [esp+024h], edi
        add     edx, ebx
        and     esi, ebp
        mov     ebx, dword ptr [esp+010h]
        xor     esi, edi
        mov     edi, dword ptr [esp+014h]
        add     edx, esi
        mov     ebp, ebx
        mov     dword ptr [esp+014h], ebx
        xor     ebx, eax
        mov     dword ptr [esp+010h], eax
        and     ebp, eax
        and     ebx, edi
        mov     esi, eax
        add     ebx, ebp
        ror     esi, 2
        mov     ebp, eax
        ror     eax, 0Dh
        xor     eax, esi
        ror     ebp, 016h
        xor     eax, ebp
        mov     ebp, dword ptr [esp+018h]
        mov     dword ptr [esp+018h], edi
        add     ebp, edx
        add     eax, edx
        mov     edx, dword ptr [esp+024h]
        add     eax, ebx
        add     ecx, 4
        jnz     sha2_716081B0
        mov     esi, dword ptr [esp+0130h]
        mov     ebx, dword ptr [esp+010h]
        mov     ecx, dword ptr [esp+014h]
        add     dword ptr [esi], eax
        add     dword ptr [esi+4], ebx
        mov     ebx, dword ptr [esp+01Ch]
        mov     eax, dword ptr [esp+020h]
        add     dword ptr [esi+8], ecx
        add     dword ptr [esi+0Ch], edi
        add     dword ptr [esi+010h], ebp
        add     dword ptr [esi+014h], ebx
        add     dword ptr [esi+018h], eax
        add     dword ptr [esi+01Ch], edx
        mov     esi, dword ptr [esp]
        mov     edi, dword ptr [esp+4]
        mov     ebx, dword ptr [esp+8]
        mov     ebp, dword ptr [esp+0Ch]
        add     esp, 0128h
        ret     8;

    }
}