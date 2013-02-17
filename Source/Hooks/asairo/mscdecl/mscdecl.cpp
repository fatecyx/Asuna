#pragma comment(lib, "ntdll.lib")

#include "crt_h.h"
#include "my_crt.h"
#include "mscdecl.h"
#include "Mem.cpp"
#include "FileDisk.cpp"

#define CODE_7D(p) if (Code7D(p, v) == False) return 0;

Bool WINAPI Code7D(PByte &pbCode, Int32 &value)
{
    if (*pbCode++ > 0x7D)
        return False;

    value = *(PInt32)pbCode - 1;
    pbCode += 4;
    return True;
}

Int32 WINAPI GetText(PByte &pbCode)
{
    Int32 v;
    v = *(PInt32)(pbCode);
    pbCode += v + 4;

    return v;
}

CMscDecl::CMscDecl()
{
    m_scr.pCode = NULL;
    m_scr.num   = 0;
    m_index[0].index = NULL;
    m_index[1].index = NULL;
}

CMscDecl::~CMscDecl()
{
    Close();
}

Void CMscDecl::Close()
{
    if (m_scr.pCode)
    {
        while (m_scr.num--)
            Free(m_scr.pCode[m_scr.num].param);
    }

    SafeFree(&m_scr.pCode);
    m_scr.max = 0;
    m_scr.num = 0;
}

Bool CMscDecl::DecompileFile(PCWChar lpMscFile, PCWChar lpOutputFile /* = NULL */)
{
    Bool        r;
    CFileDisk   file;
    Int32       iLength;
    LPVoid      lpBuffer;
    PByte       pbIndex;
    WChar       szFileName[MAX_PATH];
    SMscHeader  h;

    if (lpOutputFile)
        lstrcpyW(szFileName, lpOutputFile);
    else
    {
        lstrcpyW(szFileName, lpMscFile);
        rmextw(szFileName);
        lstrcatW(szFileName, L".txt");
    }

    if (file.Open(lpMscFile) == False)
        return False;

    iLength = file.GetSize();
    lpBuffer = Alloc(iLength);
    if (lpBuffer == NULL)
        return False;

    file.Read(lpBuffer, iLength);
    file.Close();

    pbIndex = (PByte)lpBuffer + sizeof(h);
    for (int i = 0; i != 2; i++)
    {
        Int l = *(PInt32)pbIndex;

        m_index[i].num = l / sizeof(*m_index[i].index);
        if (m_index[i].num)
            m_index[i].index = (SMscIndex *)(pbIndex + 4);
        pbIndex += 4 + l;
    }

    h = *(SMscHeader *)lpBuffer;
    r = Decompile((PByte)lpBuffer + h.uBegOffset, iLength - h.uBegOffset);
    Free(lpBuffer);

    if (r)
    {
        FILE *fp;
        SCode *pCode;
        fp = _wfopen(szFileName, L"wb");
        if (!fp)
            return r;

        pCode = m_scr.pCode;
        if (pCode == NULL)
            return r;

        for (UInt32 i = 0; i != m_scr.num; ++i, ++pCode)
        {
            SMscText *pText = pCode->pText;

            if (pText == NULL)
                continue;

            for (UInt32 j = 0; j != pCode->textnum; ++j)
            {
                if (pText->len)
                {
                    UInt32 offset;

                    offset = pCode->offset + h.uBegOffset + ((PByte)pText - pCode->param + 1);
                    fprintf(fp, "==========================================%08X\n", offset);
                    fwrite(pText->text, pText->len, 1, fp);
                    fprintf(fp, "\n"
                                "------------------------------------------\n"
                                "\n");
                }
                pText = (SMscText *)((PByte)pText + pText->len + 4);
            }
        }

        fclose(fp);
    }

    return r;
}

Int32 CMscDecl::FindNearestOffset(Int32 pos)
{
    Int32 v, min, offset = -1;
    SMscIndex *idx = 0;

    min = INT_MAX;
    for (Int32 i = 0; i != countof(m_index); ++i)
    {
        SMscIndex *index = m_index[i].index;
        if (index == NULL)
            continue;
        for (Int32 j = 0; j != m_index[i].num; ++j, ++index)
        {
            if (index->unk == true)
                continue;

            v = index->offset - pos;
            if (v >= 0 && v < min)
            {
                offset = index->offset;
                min = v;
                idx = index;
            }
        }
    }

    if (idx) idx->unk = true;

    return offset;
}

Int32 CMscDecl::FindOffsetByID(Int32 id)
{
    for (Int32 i = 0; i != countof(m_index); ++i)
    {
        SMscIndex *index = m_index[i].index;
        if (index == NULL)
            continue;

        for (Int32 j = 0; j != m_index[i].num; ++j, ++index)
            if (index->id == id && index->unk == false)
            {
                index->unk = true;
                return index->offset;
            }
    }

    return -1;
}

Bool CMscDecl::Decompile(LPCVoid lpBuffer, Int32 iLength)
{
    if (lpBuffer == NULL || iLength <= 0)
        return False;

    PByte pbBuffer, pbStart, pbEnd;

    Close();

    m_scr.max = 1000;
    m_scr.pCode = (SCode *)Alloc(m_scr.max * sizeof(*m_scr.pCode));

    pbBuffer = (PByte)lpBuffer;
    pbEnd = pbBuffer + iLength;

    m_jump1 = -2;
    pbStart = pbBuffer;
    while (pbStart < pbEnd)
    {
        Int32 i = DecompileCode(pbStart, lpBuffer);
        if (i == 0)
        {
            i = FindNearestOffset(pbStart - (PByte)lpBuffer);
            if (i == -1)
                break;

            pbStart = (PByte)lpBuffer + i;
        }
        else if (0) if (m_jump1 != -2)
        {
            i = FindOffsetByID(m_jump1 + 1);
            m_jump1 = -2;
            if (i != -1)
                pbStart = (PByte)lpBuffer + i;
        }
    }

    return True;
}

UInt32 CMscDecl::DecompileCode(PByte &pbBuffer, LPCVoid lpBuffer)
{
    UInt32 l;
    PByte pbCode = pbBuffer;
    SCode code = { 0 };

    l = -1;
    switch (code.op = *pbCode++)
    {
        case 0: l = GetCode00(pbCode, &code); break;
        case 1: l = GetCode01(pbCode, &code); break;
        case 2: l = GetCode02(pbCode, &code); break;
        case 3: l = GetCode03(pbCode, &code); break;
        case 4: l = GetCode04(pbCode, &code); break;
        case 5: l = GetCode05(pbCode, &code); break;
        case 6: l = GetCode06(pbCode, &code); break;
        default: return 0;
    }

    if (l == 0)
        return 0;

    l = pbCode - pbBuffer;
    if (l)
    {
        if (m_scr.num == m_scr.max)
        {
            m_scr.max *= 2;
            m_scr.pCode = (SCode *)ReAlloc(m_scr.max * sizeof(*m_scr.pCode), m_scr.pCode);
        }

        m_scr.pCode[m_scr.num] = code;
        m_scr.pCode[m_scr.num].offset = pbCode - (PByte)lpBuffer - l;
        ++m_scr.num;
    }

    pbBuffer = pbCode;
    if (code.op == 0 && code.param && code.param[0] == 6 && code.len == 1)
        return 0;

    return l;
}

UInt32 CMscDecl::GetCode00(PByte &pbBuffer, SCode *pCode)
{
    Int32 v;
    PByte pbCode = pbBuffer;

    switch (*pbCode++)
    {
        case 0:     // 00 00 [01 | 02]  c
            v = *pbCode++;
            switch (v)
            {
                case 1:
                case 2:
                    v = *(PInt32)pbCode - 1;
                    if (v < 0 || v > 0x44C)
                        return 0;

                    pbCode += 4;
                    v = *pbCode++;
                    if (v < 0 || v > 2)
                        return 0;

                    break;

                default:
                    return 0;
            }

            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 1:
            for (int i = 0; i != 2; ++i)
            {
                CODE_7D(pbCode);
                ++pbCode;
            }
            CODE_7D(pbCode);
            if (v > 0x800) return 0;
//            m_jump1 = v;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case SYM_00_JUMP_OFFSET:  // 00 02 offset
        case SYM_00_JUMP_ID:      // 00 03 index_id tbl_1
            CODE_7D(pbCode);
            if (v > 0x800) return 0;
            pCode->next = v;
            m_jump1 = v;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            return 0;
            break;

        case 4:
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 5: // 00 05 xx xx xx xx xx xx
            CODE_7D(pbCode);
            ++pbCode;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 6:
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 7: // 00 07 xx    c
            v = *pbCode++;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case SYM_00_LOAD_SCRIPT: // 00 08 text
            GetText(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 1);
            break;

        case 9:
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0xA:
            ++pbCode;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0xB: case 0xC:
        case 0xD: case 0xE: case 0xF:
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x10:
        case 0x11:
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x12: case 0x13: case 0x14:
            pCode->len = -1;
            break;

        case 0x16:
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x17:
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x20:
            CODE_7D(pbCode);
            CODE_7D(pbCode);
            pbCode += 2;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x30:
        case 0x31:
        case 0x32:
        case 0x35:
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x33:
        case 0x34:
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x36:
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            pbCode++;
            break;

        case 0x37:  // 00 37 xx
            CODE_7D(pbCode);
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        default:
            return 0;
    }

    pbBuffer = pbCode;
    return pCode->len;
}

UInt32 CMscDecl::GetCode01(PByte &pbBuffer, SCode *pCode)
{
    Int32 v;
    PByte pbCode = pbBuffer;

    switch (*pbCode++)
    {
        case SYM_01_SET_TITLE:         // 01 00 text   c
        case SYM_01_UNKNOWN_CHARNAME:  // 01 18 text   c
            GetText(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 1);
            break;

        case 1: // 01 01 xx c
            v = *pbCode++;
//            if (v > 0xA) return 0;
            GetText(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 2);
            break;

        case 2: // 01 02 xx c
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x1F:
        case SYM_01_CHAR_INFO: // 01 03 xx text xx text    c
            v = 0;             // 3 text: unknown, name, test_voice
            for (int i = 0; i != 3; i++)
                GetText(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 1, 3);
            break;

        case SYM_01_LOAD_SOUND:    // 01 04 xx text xx: 0 = debug, 1 = VOICE, 2 = SE, 3 = BGM  c
            if (*pbCode++ > 3)
                return 0;

            GetText(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 2);
            break;

        case 5:
        case 6:
        case 7:
            for (int i = 0; i != 2; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 8:
            CODE_7D(pbCode);
            if (v > 0x1F) return 0;
            for (int i = 0; i != 6; i++)
            	CODE_7D(pbCode);
            break;

        case 9:
            for (int i = 0; i != 3; i++)
                GetText(pbCode);
            ++pbCode;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 1, 3);
            break;

        case 0xA:
            for (int i = 0; i != 2; i++)
                CODE_7D(pbCode);
            break;

        case 0xB:
            CODE_7D(pbCode);
            if (v > 1) return 0;
            CODE_7D(pbCode);
            GetText(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 11);
            break;

        case 0xC:
            ++pbCode;
            CODE_7D(pbCode);
            break;

        case 0xD:   // c
            CODE_7D(pbCode);
            if (v > 0xC7) return 0;
            GetText(pbCode);
            GetText(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 6, 2);
            break;

        case 0xE:
            v = *pbCode++;
            if (v > 6)
                return 0;

            for (int i = 0; i != 4; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0xF:
        case 0x11:
        case 0x14:
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x10:
            v = *pbCode++;
            if (v > 6)
                return 0;

            for (int i = 0; i != 3; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x12:
            for (int i = 0; i != 7; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x13:
            for (int i = 0; i != 5; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x15:  // 01 15 xx text    c
            if (*pbCode++ > 2)
                return 0;
            GetText(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 2);
            break;

        case 0x16:
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x17: // 01 17 xx text xx text c
        case 0x1E: // 01 1E xx text xx text c
            for (int i = 0; i != 2; i++)
                GetText(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 1, 2);
            break;

        case 0x19:
            GetText(pbCode);
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 1);
            break;

        case 0x1A:
            v = *pbCode++;
            if (v > 0 && v < 3)
                ++pbCode;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x1B:
            v = *pbCode++;
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x1C:
            v = *pbCode++;
            CODE_7D(pbCode);
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x1D:
            v = *pbCode++;
            CODE_7D(pbCode);
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        default:
            return 0;
    }

    pbBuffer = pbCode;

    return pCode->len;
}

UInt32 CMscDecl::GetCode02(PByte &pbBuffer, SCode *pCode)
{
    Int32 v;
    PByte pbCode = pbBuffer;

    switch (*pbCode++)
    {
        case 0:
            CODE_7D(pbCode);
            GetText(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 6);
            break;

        case 1:
            CODE_7D(pbCode);
//            if (v > 0x136) return 0;
            for (int i = 0; i != 2; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 2:
        case 0x17:
            CODE_7D(pbCode);
//            if (v > 0x135) return 0;
            ++pbCode;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 3:
            for (int i = 0; i != 5; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 4:
        case 6:
        case 7:
        case 0xD:
        case 0xE:
        case 0xF:
        case 0x13:
            for (int i = 0; i != 2; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 5:
        case 0xA:
        case 0x10:
        case 0x11:
            CODE_7D(pbCode);
//            if (v > 0x136) return 0;
            for (int i = 0; i != 2; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 8:
        case 0xB:
            CODE_7D(pbCode);
//            if (v > 136) return 0;
            for (int i = 0; i != 3; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0xC:
            CODE_7D(pbCode);
//            if (v > 136) return 0;
            for (int i = 0; i != 3; i++)
                CODE_7D(pbCode);
            ++pbCode;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 9:
            for (int i = 0; i != 6; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x12:
            for (int i = 0; i != 5; i++)
                CODE_7D(pbCode);
            GetText(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 26);
            break;

        case 0x14:
            CODE_7D(pbCode);
            GetText(pbCode);
            for (int i = 0; i != 3; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 6);
            break;

        case 0x15:
            CODE_7D(pbCode);
 //           if (v > 135) return 0;
            for (int i = 0; i != 3; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0x16:
            CODE_7D(pbCode);
            GetText(pbCode);
            for (int i = 0; i != 4; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 6);
            break;

        default:
            return 0;
    }

    pbBuffer = pbCode;

    return pCode->len;
}

UInt32 CMscDecl::GetCode03(PByte &pbBuffer, SCode *pCode)
{
    Int32 v;
    PByte pbCode = pbBuffer;

    switch (*pbCode++)
    {
        case 0:
            CODE_7D(pbCode);
            GetText(pbCode);
            CODE_7D(pbCode);
            v = *pbCode++;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 6);
            break;

        case 1:
            CODE_7D(pbCode);
            CODE_7D(pbCode);
            v = *pbCode++;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 2:
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 3:
            GetText(pbCode);
            v = *pbCode++;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 1);
            break;

        default:
            return 0;
    }

    pbBuffer = pbCode;

    return pCode->len;
}

UInt32 CMscDecl::GetCode04(PByte &pbBuffer, SCode *pCode)
{
    Int32 v;
    PByte pbCode = pbBuffer;

    switch (*pbCode++)
    {
        case 0: // switch
            CODE_7D(pbCode);
            if (v > 0x136)
                return 0;

            v = *pbCode++;
            if (v < 5)
                CODE_7D(pbCode);
            if (v > 0x800)
                return 0;

            pCode->next = v;
//            m_vecnext.push_back(v);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 1:
        case 2:
            CODE_7D(pbCode);
            v = *pbCode++;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 3:
        case 4:
            CODE_7D(pbCode);
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        default:
            return 0;
    }

    pbBuffer = pbCode;

    return pCode->len;
}

UInt32 CMscDecl::GetCode05(PByte &pbBuffer, SCode *pCode)
{
    Int32 v;
    PByte pbCode = pbBuffer;

    switch (*pbCode++)
    {
        case 0:
            CODE_7D(pbCode);
            GetText(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 6);
            break;

        case 1:
            for (int i = 0; i != 8; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 2:
            for (int i = 0; i != 7; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 3:
        case 4:
            for (int i = 0; i != 2; i++)
                CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 5:
            v = *pbCode++;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 6:
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 7:
            pbCode += 2;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        default:
            return 0;
    }

    pbBuffer = pbCode;

    return pCode->len;
}

UInt32 CMscDecl::GetCode06(PByte &pbBuffer, SCode *pCode)
{
    Int32 v;
    PByte pbCode = pbBuffer;

    switch (*pbCode++)
    {
        case 0:
            GetText(pbCode);
            CODE_7D(pbCode);
            ++pbCode;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 1);
            break;

        case 1: // c
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 2:
        case 0xA:
            GetText(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 1);
            break;

        case 3:
        case 7:
        case 0xD:
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 4:
            CODE_7D(pbCode);
            GetText(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len, 6);
            break;

        case 5:
            CODE_7D(pbCode);
            ++pbCode;
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 6: case 8: case 9:
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0xB:
            v = *pbCode++;
            CODE_7D(pbCode);
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0xC:
            CODE_7D(pbCode);
            CODE_7D(pbCode);
            CODE_7D(pbCode);
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        case 0xE:
            CODE_7D(pbCode);
            CODE_7D(pbCode);
            pCode->len = pbCode - pbBuffer;
            GetParam(pCode, pbCode - pCode->len);
            break;

        default:
            return 0;
    }

    pbBuffer = pbCode;

    return pCode->len;
}

Void CMscDecl::GetParam(SCode *pCode, PByte pbCode, UInt32 uTextOffset /* = -1 */, UInt32 uTextNum /* = 1 */)
{
    pCode->param = (PByte)Alloc(pCode->len);
    memcpy(pCode->param, pbCode, pCode->len);
    if (uTextOffset != -1)
    {
        pCode->pText = (SMscText *)(pCode->param + uTextOffset);
        pCode->textnum = uTextNum;
    }
}

Bool CMscDecl::PeekText(PCWChar lpMscFile, PCWChar lpOutputFile /* = NULL */)
{
    CFileDisk   file;
    Int32       iLength, iTextNum;
    LPVoid      lpBuffer;
    PByte       pbBuffer, pbEnd;
    Char        szBuffer[0x1000];
    WChar       szFileName[MAX_PATH];
    FILE       *fp;
    SMscHeader *h;
    SMscText *pText;

    if (lpOutputFile)
        lstrcpyW(szFileName, lpOutputFile);
    else
    {
        lstrcpyW(szFileName, lpMscFile);
        rmextw(szFileName);
        lstrcatW(szFileName, L".txt");
    }

    fp = _wfopen(szFileName, L"wb");
    if (fp == NULL)
        return False;

    if (file.Open(lpMscFile) == False)
        return False;

    iLength = file.GetSize();
    lpBuffer = Alloc(iLength);
    if (lpBuffer == NULL)
        return False;

    file.Read(lpBuffer, iLength);
    file.Close();

    h = (SMscHeader *)lpBuffer;
    pbBuffer = (PByte)lpBuffer;

    pText = NULL;
    iTextNum = 1;
    pbEnd = pbBuffer + iLength;
    pbBuffer += h->uBegOffset;
    while (pbBuffer < pbEnd)
    {
        PByte  pbTemp;
        UInt32 c = *pbBuffer++;

        pbTemp = pbBuffer;
        switch (c)
        {
            case 0:
                if (*pbBuffer++ == SYM_00_LOAD_SCRIPT)
                    pText = (SMscText *)pbBuffer;
                break;

            case 1:
                c = *pbBuffer++;
                switch (c)
                {
                    case 0:
                    case 0x18:
                        pText = (SMscText *)pbBuffer;
                        break;

                    case 1:
                        if (*pbBuffer++ <= 0xA)
                            pText = (SMscText *)pbBuffer;
                        break;

                    case 3:
                    case 0x1F:
                        pText = (SMscText *)pbBuffer;
                        iTextNum = 3;
                        break;

                    case 4:
                        if (*pbBuffer++ <= 3)
                            pText = (SMscText *)pbBuffer;
                        break;

                    case 0xD:
                        if (*pbBuffer++ <= 0x7D)
                        {
                            pbBuffer += 4;
                            pText = (SMscText *)pbBuffer;
                            iTextNum = 2;
                        }
                        break;

                    case 0x15:
                        if (*pbBuffer++ <= 2)
                            pText = (SMscText *)pbBuffer;
                        break;

                    case 0x17:
                    case 0x1E:
                        pText = (SMscText *)pbBuffer;
                        iTextNum = 2;
                        break;

                    case 0x19:
                        pText = (SMscText *)pbBuffer;
                        break;
                }
                break;

            case 2:
                c = *pbBuffer++;
                switch (c)
                {
                    case 0:
                        if (*pbBuffer++ <= 0x7D)
                        {
                            pbBuffer += 4;
                            pText = (SMscText *)pbBuffer;
                        }
                        break;

                    case 0x12:
                        if (*pbBuffer++ > 0x7D)
                            break;
                        pbBuffer += 4;
                        if (*pbBuffer++ > 0x7D)
                            break;
                        pbBuffer += 4;
                        if (*pbBuffer++ > 0x7D)
                            break;
                        pbBuffer += 4;
                        if (*pbBuffer++ > 0x7D)
                            break;
                        pbBuffer += 4;
                        if (*pbBuffer++ > 0x7D)
                            break;
                        pbBuffer += 4;
                        pText = (SMscText *)pbBuffer;
                        break;

                    case 0x14:
                    case 0x16:
                        if (*pbBuffer++ <= 0x7D)
                        {
                            pbBuffer += 4;
                            pText = (SMscText *)pbBuffer;
                        }
                        break;
                }

            case 3:
                c = *pbBuffer++;
                switch (c)
                {
                    case 0:
                        if (*pbBuffer++ <= 0x7D)
                        {
                            pbBuffer += 4;
                            pText = (SMscText *)pbBuffer;
                        }
                        break;

                    case 3:
                        pText = (SMscText *)pbBuffer;
                        break;
                }
                break;

            case 5:
                if (*pbBuffer++ == 0 && *pbBuffer++ <= 0x7D)
                {
                    pbBuffer += 4;
                    pText = (SMscText *)pbBuffer;
                }
                break;

            case 6:
                c = *pbBuffer++;
                if (c == 0 || c == 2 || c == 0xA)
                    pText = (SMscText *)pbBuffer;
                else if (c == 4 && *pbBuffer++ <= 0x7D)
                {
                    pbBuffer += 4;
                    pText = (SMscText *)pbBuffer;
                }
                break;
        }

        if (pText)
        {
            while (iTextNum --)
            {
                if ((PByte)pText >= pbEnd ||
                    (PByte)pText + 4 + pText->len >= pbEnd ||
//                    (iTextNum && !pText->len) ||
                    !IsTextValid(pText) ||
                    (iTextNum == 0 && *((PByte)pText + 4 + pText->len) > 6))
                {
                    pText = (SMscText *)pbTemp;
                    break;
                }

                if (pText->len)
                {
                    memcpy(szBuffer, pText->text, pText->len);
                    szBuffer[pText->len] = 0;
                    for (Int i = pText->len - 1; i > 0; --i)
                    {
                        if (szBuffer[i] == '\r' || szBuffer[i] == '\n')
                            szBuffer[i] = 0;
                        else
                            break;
                    }
                    fprintf(fp, "==========================================%08X\n"
                                "%s\n"
                                "------------------------------------------\n"
                                "\n"
                                , (PByte)pText - (PByte)lpBuffer, szBuffer);
//                    fflush(fp);
                }
                pText = (SMscText *)((PByte)pText + pText->len + 4);
                pbTemp = (PByte)pText;
            }

            pText = NULL;
            iTextNum = 1;
        }

        pbBuffer = pbTemp;
    }

    Free(lpBuffer);
    fclose(fp);

    return True;
}

NoInline Bool CMscDecl::IsTextValid(SMscText *pText)
{
    if (pText->len > 0x200 ||
        pText->len > strlen(pText->text) ||
        (pText->len && (UChar)pText->text[0] < 0x20))
        return False;

    Byte c;
    PChar p = pText->text;
    PByte pbCode;

    for (Int i = 0; i < (Int)pText->len; )
    {
        c = *p++;
        ++i;
        if ((c < 0x20 && c != '\n' && c != '\r') || c == 0x7F)
            return False;
        else if ((Char)c < 0)
        {
            c = *p++;
            if (c < 0x40)
                return False;
            ++i;
        }
    }

    pbCode = (PByte)pText->text + pText->len;

    return True;
}