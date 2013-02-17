#include "ystb.h"
#include "gal_common.h"

CYurisScriptParser::CYurisScriptParser()
{

}

CYurisScriptParser::~CYurisScriptParser()
{

}

Bool CYurisScriptParser::Auto(PWChar pszFile)
{
    WChar *p, buf[MAX_PATH * 2];
    FILE *fp = _wfopen(pszFile, L"rb");
    if (fp == NULL)
        return False;

    fread(buf, sizeof(buf), 1, fp);
    fclose(fp);
    if (*(PUInt32)buf == TAG4('YSTB'))
        return Parse(pszFile);

    if (*(PUInt16)buf != 0xFEFF)
        return False;

    p = buf;
    for (PWChar end = p + countof(buf); p < end; ++p)
    {
        while (p < end && *p++ != L'\n');
        if (p >= end)
            break;

        if (*p == L'#')
        {
            return Import(pszFile);
        }
    }

    return False;
}

Bool CYurisScriptParser::Parse(PWChar pszFile)
{
    if (file.Open(pszFile) == False)
        return False;

    Bool   r;
    LPVoid lpBuffer;
    UInt32 BufferSize;
    SYSHeader *pHeader;

    BufferSize = file.GetSize();
    lpBuffer = m.Alloc(BufferSize);
    if (lpBuffer == NULL)
        return False;

    if (file.Read(lpBuffer, BufferSize) == False)
    {
        m.Free(lpBuffer);
        return False;
    }

    pHeader = (SYSHeader *)lpBuffer;
    if (pHeader->magic == TAG4('YSTB'))
        r = ParseB(lpBuffer, BufferSize, pszFile);
    else
        r = False;

    m.Free(lpBuffer);

    return r;
}

Bool CYurisScriptParser::ParseB(LPVoid lpBuffer, UInt32 BufferSize, PWChar pszInputFile)
{
    SYSHeader *pHeader;
    SYSTBInfo  info;
    WChar      szFile[MAX_PATH];

    pHeader = (SYSHeader *)lpBuffer;
    switch (pHeader->ver)
    {
        case 0x12C:
        case 0x1C2:
            break;
            
        default:
            return False;
    }

    info.ppOPCode = (SYSOPCode **)m.Alloc(pHeader->PartCount * 4);
    if (info.ppOPCode == NULL)
        return False;

    info.PartCount   = pHeader->PartCount;
    info.pOPInfo     = (SYSOPInfo *)((PByte)lpBuffer + sizeof(*pHeader));
    info.pbOPCode    = (PByte)info.pOPInfo + pHeader->PartSize;
    info.pbData      = info.pbOPCode + pHeader->OPCodeSize;
    info.pIndexTable = (PUInt32)(info.pbData + pHeader->DataSize);

    WChar Buffer[0x1000];
    PByte pbOPCode, pbEnd;
    UInt32 LineWrote;
    SYSOPCode *pOPCode;
    SYSOPInfo *pOPInfo;
    FILE *fp1, *fp;

    fp = NULL;
    fp1 = NULL;
//    fp = fopen("E:\\Desktop\\Source\\Unpacker\\magustale\\ystbext\\dbg.c", "wb");
    lstrcpyW(szFile, pszInputFile);
    chextw(szFile, L".txt");

    LineWrote = 0;
    pbEnd = (PByte)lpBuffer + BufferSize;
    pbOPCode = info.pbOPCode;
    pOPInfo = info.pOPInfo;
    for (UInt32 i = 0; i != info.PartCount - 1; ++i, ++pOPInfo)
    {
        info.ppOPCode[i] = (SYSOPCode *)pbOPCode;
        pOPCode = info.ppOPCode[i];
        pbOPCode += pOPInfo->count * sizeof(*pOPCode);

        for (UInt32 j = 0, k = pOPInfo->count; j != k; ++j, ++pOPCode)
        {
            PByte p;
            UInt32 len, CodePage;
/*
            for (UInt32 l = 8; l; )
                fprintf(fp, "%01X", (pOPCode->op >> --l) & 1);

            fprintf(fp, " %02X %02X %02X %02X %08X %08X\n",
                pOPCode->op, pOPCode->reserve, pOPCode->flag1,
                pOPCode->flag2, pOPCode->Length, pOPCode->Offset);

            fprintf(fp1, "%02X %02X %02X %02X %02X %08X %08X: ",
                pOPInfo->op, pOPCode->op, pOPCode->reserve, pOPCode->flag1,
                pOPCode->flag2, pOPCode->Length, pOPCode->Offset);

            p = info.pbData + pOPCode->Offset;
            fwrite(p, pOPCode->Length, 1, fp1);
            fprintf(fp1, "\n");

            continue;
*/
            len = 0;
            if (pOPInfo->op == 0x59)
            {
                p = info.pbData + pOPCode->Offset;
                len = pOPCode->Length;
            }
            else if (pOPCode->flag1 == 3)
            {
                switch (pOPInfo->op)
                {
                    case 0x01:
                    case 0x1B:
                        continue;
                }

                p = info.pbData + pOPCode->Offset;
                if (p >= pbEnd || *p++ != 0x4D)
                    continue;

                len = *(PUInt16)p;
                p += 2;
                if (len == 0 || len >= pOPCode->Length)
                    continue;

                static Char *szCtrl[] = 
                {
                    "\"es.SE\"", 
                    "\"es.BTN.CG.SET\"", 
                };

                for (UInt32 a = 0; a != countof(szCtrl); ++a)
                {
                    if (!strnicmp((PChar)p, szCtrl[a], len))
                    {
                        len = 0;
                        break;
                    }
                }

                BREAK_IF(len == 0);

                if (*p == '"')
                {
                    ++p;
                    --len;
                }

                if (p[len - 1] == '"')
                    --len;

                if (IsAnsi((PCChar)p, len))
                    continue;
            }

            CONTINUE_IF(len == 0);

            CodePage = IsShiftJISString((PCChar)p, len) ? CP_SHIFTJIS : CP_GB2312;
            len = MultiByteToWideChar(CodePage, MB_ERR_INVALID_CHARS, (PCChar)p, len, Buffer, countof(Buffer));
            if (len == 0/* && GetLastError() == ERROR_NO_UNICODE_TRANSLATION*/)
                continue;

            if (LineWrote++ == 0)
            {
                fp1 = _wfopen(szFile, L"wb");
                if(fp1 == NULL)
                    goto PARSE_END;

                fputc(0xFF, fp1);
                fputc(0xFE, fp1);
                fwprintf(fp1, L";%s\r\n"
                    L"#YSTB\r\n", findnamew(pszInputFile));
            }

            Buffer[len] = 0;
            fwprintf(fp1, L"============================================================%X,%X\r\n", i, j);

#if 0
            fwprintf(fp1, L"%02X %02X %02X %02X %02X %08X %08X: ", pOPInfo->op, pOPCode->op, pOPCode->reserve, pOPCode->flag1,
                pOPCode->flag2, pOPCode->Length, pOPCode->Offset);
#endif
            fwprintf(fp1, L"%s\r\n"
                L"----------------------------------------------------------------------------------\r\n"
                L"\r\n",
                Buffer);
        }
    }

PARSE_END:
//        fclose(fp);
    if (fp1)
    {
        fclose(fp1);
    }

    m.Free(info.ppOPCode);

    return True;
}

Bool CYurisScriptParser::IsAnsi(PCChar p, UInt32 len)
{
    for (UInt32 i = 0; i != len; ++p, ++i)
    {
        if (*p < 0)
            return False;
    }

    return True;
}

Bool CYurisScriptParser::Import(PWChar pszText)
{
    FILE *fp, *fscr;
    LPVoid lpBuffer;
    UInt32 BufferSize, ScriptSize, ScriptType;
    WChar  szFile[MAX_PATH * 2];

    fp = _wfopen(pszText, L"r");
    if (fp == NULL)
        return False;

    wcscpy(szFile, pszText);
    chextw(szFile, L".ybn");
    fscr = _wfopen(szFile, L"rb+");
    if (fscr == NULL)
    {
        fclose(fp);
        return False;
    }

    ScriptSize = fsize(fscr);
    BufferSize = fsize(fp) + ScriptSize;
    lpBuffer = m.Alloc(BufferSize);
    if (lpBuffer == NULL)
    {
        fclose(fp);
        fclose(fscr);
        return False;
    }

    fread(lpBuffer, ScriptSize, 1, fscr);
    fseek(fscr, 0, SEEK_SET);

    _setmode(_fileno(fp), _O_BINARY);
    fseek(fp, 2, SEEK_SET);
    while (fgetsW(szFile, countof(szFile), fp) >= 0)
    {
        if (szFile[0] == ';')
            continue;
        if (szFile[0] == '#')
        {
            if (!wcscmp(szFile, L"#YSTB"))
                ScriptType = SCR_YSTB;
            else if (!wcscmp(szFile, L"#YSCM"))
                ScriptType = SCR_YSCM;
            else if (!wcscmp(szFile, L"#YSCF"))
                ScriptType = SCR_YSCF;
            else if (!wcscmp(szFile, L"#YSER"))
                ScriptType = SCR_YSER;
            else if (!wcscmp(szFile, L"#YSLB"))
                ScriptType = SCR_YSLB;
            else if (!wcscmp(szFile, L"#YSTD"))
                ScriptType = SCR_YSTD;
            else if (!wcscmp(szFile, L"#YSTL"))
                ScriptType = SCR_YSTL;
            else
                ScriptType = SCR_INVALID;
            break;
        }
    }

    switch (ScriptType)
    {
        case SCR_YSTB: ScriptSize = ImportYSTB(lpBuffer, ScriptSize, BufferSize, fp); break;
        default: ScriptSize = 0;
    }

    if (ScriptSize)
    {
        fseek(fscr, 0, SEEK_SET);
        fwrite(lpBuffer, ScriptSize,1, fscr);
        chsize(fileno(fscr), ScriptSize);
    }

    fclose(fp);
    fclose(fscr);

    m.Free(lpBuffer);

    return !!ScriptSize;
}

UInt32 CYurisScriptParser::ImportYSTB(LPVoid lpBuffer, UInt32 ScriptSize, UInt32 BufferSize, FILE *fp)
{
    PByte pbOPCode, pbEnd;
    Int32 SizeDiff, SizeDiffTotal;
    UInt32  IndexCount, MaxCount;
    PUInt32   *pOffsetIndex;
    SYSOPCode *pOPCode;
    SYSOPInfo *pOPInfo;
    SYSHeader *pHeader;
    SYSTBInfo  info;
    WChar      szSource[0x1000];//, szTrans[0x1000];

#define szTrans szSource

    pHeader = (SYSHeader *)lpBuffer;
    switch (pHeader->ver)
    {
        case 0x12C:
        case 0x1C2:
            break;

        default:
            return 0;
    }

    info.ppOPCode = (SYSOPCode **)m.Alloc(pHeader->PartCount * 4);
    if (info.ppOPCode == NULL)
        return 0;

    MaxCount = pHeader->PartCount;
    pOffsetIndex = (PUInt32 *)m.Alloc(MaxCount * sizeof(*pOffsetIndex));
    if (pOffsetIndex == NULL)
    {
        m.Free(info.ppOPCode);
        return 0;
    }

    info.PartCount   = pHeader->PartCount;
    info.pOPInfo     = (SYSOPInfo *)((PByte)lpBuffer + sizeof(*pHeader));
    info.pbOPCode    = (PByte)info.pOPInfo + pHeader->PartSize;
    info.pbData      = info.pbOPCode + pHeader->OPCodeSize;
    info.pIndexTable = (PUInt32)(info.pbData + pHeader->DataSize);

    IndexCount = 0;
    pbEnd = (PByte)lpBuffer + ScriptSize;
    pbOPCode = info.pbOPCode;
    pOPInfo = info.pOPInfo;
    for (UInt32 i = 0, **p = pOffsetIndex; i != info.PartCount - 1; ++i, ++pOPInfo)
    {
        info.ppOPCode[i] = (SYSOPCode *)pbOPCode;
        pOPCode = info.ppOPCode[i];
        pbOPCode += pOPInfo->count * sizeof(*pOPCode);

        if (pOPInfo->op == 0x3E)
            continue;

        for (UInt32 j = 0, k = pOPInfo->count; j != k; ++j, ++pOPCode)
        {
            if (pOPCode->Length == 0)
                continue;

            if (pOPCode->Offset + info.pbData >= pbEnd)
                continue;

            if (IndexCount == MaxCount)
            {
                MaxCount *= 2;
                pOffsetIndex = (PUInt32 *)m.ReAlloc(pOffsetIndex, MaxCount * sizeof(*pOffsetIndex));
                p = pOffsetIndex + IndexCount;
            }

            ++IndexCount;
            *p++ = &pOPCode->Offset;
        }
    }

    PWChar p;

    SizeDiff = 0;
    SizeDiffTotal = 0;

    fseek(fp, 2, SEEK_SET);
    while (fgetsW(szSource, countof(szSource), fp) >= 0)
    {
        if (szSource[0] != '=')
            continue;

        Char   szMB[0x1000];
        PByte  pbDataToMove;
        UInt32 MajorIndex, MinorIndex;
        Int32  LengthTrans, LengthOrig;

        p = szSource;
        while (*p == '=' && *p) ++p;
        if (*p == 0)
            continue;

        if (swscanf(p, L"%X,%X", &MajorIndex, &MinorIndex) != 2)
            continue;

        if (MajorIndex >= info.PartCount)
            continue;

        pOPCode = info.ppOPCode[MajorIndex];
        pOPCode += MinorIndex;

        if ((PByte)pOPCode >= pbEnd)
            continue;

        while ((LengthTrans = fgetsW(szTrans, countof(szTrans), fp)) >= 0)
        {
            if (szTrans[0] != '-')
                continue;
            LengthTrans = fgetsW(szTrans, countof(szTrans), fp);
            break;
        }

        if (LengthTrans == 0)
            continue;
        else if (LengthTrans == -1)
            break;

        FilterString(szTrans, LengthTrans);
        LengthTrans = WideCharToMultiByte(CP_GB2312, 0, szTrans, LengthTrans, szMB, sizeof(szMB), 0, 0);

        LengthOrig = pOPCode->Length;
        pbDataToMove = pOPCode->Offset + info.pbData;
        if (*pbDataToMove == 0x4D)
        {
            LengthOrig = *(PUInt16)++pbDataToMove;
            pbDataToMove += 2;

            if (*pbDataToMove == '"')
            {
                ++pbDataToMove;
                --LengthOrig;
            }

            pbDataToMove += LengthOrig;
            if (*(pbDataToMove - 1) == '"')
            {
                --pbDataToMove;
                --LengthOrig;
            }
        }
        else
            pbDataToMove += LengthOrig;

        SizeDiff = LengthTrans - LengthOrig;
        memmove(pbDataToMove + SizeDiff, pbDataToMove, pbEnd - pbDataToMove);

        if (SizeDiff)
        {
            pbEnd += SizeDiff;
            SizeDiffTotal += SizeDiff;
            pOPCode->Length += SizeDiff;
            pHeader->DataSize += SizeDiff;
        }

        pbDataToMove = pOPCode->Offset + info.pbData;
        if (*pbDataToMove == 0x4D)
        {
            ++pbDataToMove;
            if (SizeDiff)
                *(PUInt16)pbDataToMove += SizeDiff;

            pbDataToMove += 2;
            if (*pbDataToMove == '"')
                ++pbDataToMove;
        }

        memcpy(pbDataToMove, szMB, LengthTrans);
        UpdateOffset(pOffsetIndex, IndexCount, SizeDiff, pOPCode->Offset, &info);
    }

    m.Free(pOffsetIndex);
    m.Free(info.ppOPCode);

    return ScriptSize + SizeDiffTotal;
}

Void CYurisScriptParser::UpdateOffset(PUInt32 *pOffsetIndex, UInt32 Count, Int32 Diff, UInt32 ModifiedOffset, SYSTBInfo *pTBInfo)
{
    if (pOffsetIndex == NULL)
        return;

    while (Count--)
    {
        if ((UInt32)**pOffsetIndex > ModifiedOffset)
        {
            SYSOPCode *pOPCode = NULL;

            pOPCode = (SYSOPCode *)((PByte)*pOffsetIndex - ((PByte)&pOPCode->Offset - (PByte)pOPCode));
            pOPCode->Offset += Diff;
            if (pTBInfo->pbData + pOPCode->Offset <= ModifiedOffset + pTBInfo->pbData &&
                pTBInfo->pbData + pOPCode->Offset + pOPCode->Length >= ModifiedOffset + pTBInfo->pbData)
                pOPCode->Length += Diff;
        }
        ++pOffsetIndex;
    }
}