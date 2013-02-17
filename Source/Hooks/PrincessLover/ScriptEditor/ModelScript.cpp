#include "ModelScript.h"
#include "FileDisk.h"

PCTChar CModelScript::GetErrorString(Long ErrorCode)
{
    static TChar *szErrorString[] =
    {
        _T("Open file failed"),
        _T("Seek file failed"),
        _T("Read file failed"),
        _T("Write file failed"),
        _T("Out of memory"),
        _T("Invalid encoding, support UTF-16 LE with BOM only"),
        _T("Invalid translation file"),
        _T("Empty original text"),
        _T("Empty translation text"),
    };

    if (ErrorCode < SCR_ERROR_FIRST || ErrorCode >= SCR_ERROR_LAST)
        return _T("");

    ErrorCode -= SCR_ERROR_FIRST;
    if (ErrorCode > countof(szErrorString))
        return _T("");

    return szErrorString[ErrorCode];
}

Bool CModelScript::IsComment(PWChar pszText)
{
    return pszText[0] == '/' && pszText[1] == '/';
}

Bool CModelScript::IsControlSentance(PWChar pszText)
{
    switch (*pszText)
    {
        case '@':
        case '\\':
        case '^':
        case '\r':
        case '\n':
        case 0:
            return True;
    }

    return False;
}

PWChar CModelScript::PeekLine(PVoid pBuffer, PVoid pEndOfBuffer, PVoid pOutBuffer, PSizeT pcbOutBuffer)
{
    if (pBuffer == NULL)
        return NULL;

    WChar  ch;
    PWChar pStart, pEnd, pOutput;
    SSizeT BufferSize;

    if (pcbOutBuffer != NULL)
    {
        BufferSize = *pcbOutBuffer;
        *pcbOutBuffer = 0;
    }

    pStart = (PWChar)pBuffer;
    pEnd   = pEndOfBuffer ? (PWChar)pEndOfBuffer : pStart + StrLengthW(pStart);

    if (pStart >= pEnd)
        return NULL;

    pOutput = (PWChar)pOutBuffer;
    if (*pStart == BOM_UTF16_LE)
        ++pStart;

    while (pStart < pEnd)
    {
        ch = *pStart++;
        if (ch == '\n')
            break;
        if (pOutput == NULL)
            continue;

        if (BufferSize > 0 && ch != '\r')
        {
            *pOutput++ = ch;
            BufferSize -= sizeof(ch);
        }
    }

    if (pOutput && BufferSize > 0)
        *pOutput = 0;

    BufferSize = (PByte)pOutput - (PByte)pOutBuffer;
    if (pcbOutBuffer)
        *pcbOutBuffer = BufferSize;

    if (BufferSize == 0)
        return pStart < pEnd ? pStart : NULL;

    return pStart;
}

SizeT CModelScript::FindCharName(PCWChar pszCharName)
{
    SizeT Index;
    StringW *pCharName;

    Index = 0;
    pCharName = &m_VecCharNameOriginal[0];
    for (SizeT i = m_VecCharNameOriginal.size(); i; --i, ++Index, ++pCharName)
    {
        if (*pCharName != pszCharName)
            continue;

        return Index;
    }

    m_VecCharNameOriginal.push_back(pszCharName);

    return Index;
}

Long CModelScript::ParseScript(PCTChar pszScriptPath)
{
    Long      Result;
    PVoid     pBuffer;
    CFileDisk file;

    m_ScriptPath = _T("");

    if (!file.Open(pszScriptPath))
        return SCR_ERROR_IO_FAILED_OPEN;

    pBuffer = m_mem.Alloc(file.GetSize());
    if (pBuffer == NULL)
        return SCR_ERROR_OUT_OF_MEMORY;

    if (!file.Read(pBuffer))
    {
        m_mem.Free(pBuffer);
        return SCR_ERROR_IO_FAILED_READ;
    }

    Result = ParseScriptWorker(pBuffer, file.GetSize());
    m_mem.Free(pBuffer);
    if (SCR_FAILED(Result))
        return Result;

    Result = ParseTranslationFile(pszScriptPath);
    if (SCR_FAILED(Result))
        return Result;

    m_ScriptPath = pszScriptPath;

    return Result;
}

Void CModelScript::GenerateTranslationFileName(PTChar pszScriptPath)
{
    lstrcpy(pszScriptPath + StrLength(pszScriptPath), _T(".txt"));
}

Long CModelScript::ParseTranslationFile(PCTChar pszScriptPath)
{
    PTChar pszTransPath;
    WChar  szBuffer[0x1000];
    PVoid  pvBuffer;
    WChar  ch;
    PWChar pText, pEnd, pBuffer;
    CFileDisk file;

    pszTransPath = (PTChar)szBuffer;
    lstrcpy(pszTransPath, pszScriptPath);
    GenerateTranslationFileName(pszTransPath);

    if (!file.Open(pszTransPath))
    {
        m_VecTextTranslation = m_VecTextOrigianl;
        m_VecCharNameTranslation = m_VecCharNameOriginal;
        return SCR_ERROR_SUCCESS;
    }

    pvBuffer = m_mem.Alloc(file.GetSize());
    if (pvBuffer == NULL)
        return SCR_ERROR_OUT_OF_MEMORY;

    if (!file.Read(pvBuffer))
    {
        m_mem.Free(pvBuffer);
        return SCR_ERROR_IO_FAILED_READ;
    }

    pText = (PWChar)pvBuffer;
    if (*pText != BOM_UTF16_LE)
    {
        m_mem.Free(pvBuffer);
        return SCR_ERROR_INVALID_ENCODING;
    }

    SizeT PhysicalLine;
    StringW CharName;
    SScriptText ScrText;

    m_VecCharNameTranslation.clear();
    m_VecTextTranslation.clear();

    PhysicalLine = 0;
    pEnd = (PWChar)((PByte)pvBuffer + file.GetSize());
    while (pText < pEnd)
    {
        SizeT LineSize = sizeof(szBuffer);

        pText = PeekLine(pText, pEnd, szBuffer, &LineSize);
        if (pText == NULL)
            break;

        ++PhysicalLine;
        LineSize /= sizeof(*szBuffer);
        if (!StrNICompareW(szBuffer, L"@Text=", 6))
        {
            SizeT  Index;
            PWChar pStart;

            pStart = szBuffer + 6;
            pBuffer = pStart;
            for (Index = 3; Index; --Index)
            {
                while (ch = *pBuffer++)
                {
                    if (ch == ',')
                        break;
                }

                if (ch == 0)
                    break;

                switch (Index)
                {
                    case 3:
                        ScrText.PhysicalLine = StringToInt32W(pStart);
                        break;

                    case 2:
                        ScrText.LogicalLine = StringToInt32W(pStart);
                        break;

                    case 1:
                        ScrText.CharNameIndex = StringToInt32W(pStart);
                        break;
                }

                pStart = pBuffer;
            }

            if (Index != 0)
                goto CLEAR_THEN_RETURN;

            ScrText.Text = pStart;
            m_VecTextTranslation.push_back(ScrText);
        }
        else if (!StrNICompareW(szBuffer, L"@Name=", 6))
        {
            PWChar pStart;

            pStart = szBuffer + 6;
            pBuffer = pStart;
            while (ch = *pBuffer++)
            {
                if (ch != ',')
                    continue;

                pBuffer[-1] = 0;
                CharName = pStart;
                m_VecCharNameTranslation.push_back(CharName);
                pStart = pBuffer;
            }

            if (pStart + 1 != pBuffer)
            {
                CharName = pStart;
                m_VecCharNameTranslation.push_back(CharName);
            }
        }
    }

    m_mem.Free(pvBuffer);
    if (m_VecTextTranslation.size() != m_VecTextOrigianl.size())
        return SCR_ERROR_INVALID_TRANSLATION_FILE;

    return SCR_ERROR_SUCCESS;

CLEAR_THEN_RETURN:
    m_VecCharNameTranslation.clear();
    m_VecTextTranslation.clear();

    return SCR_ERROR_INVALID_TRANSLATION_FILE;
}

Long CModelScript::ParseScriptWorker(PVoid pvBuffer, SizeT BufferSize)
{
    SizeT  LogicalLine, PhysicalLine, LineSize;
    WChar  ch, LineBuffer[0x1000];
    PWChar pBuffer, pText, pEnd;

    pText = (PWChar)pvBuffer;
    pEnd  = (PWChar)((PByte)pvBuffer + BufferSize);

    if (*pText != BOM_UTF16_LE)
        return SCR_ERROR_INVALID_ENCODING;

    SScriptText ScrText;

    m_VecCharNameOriginal.clear();
    m_VecTextOrigianl.clear();

    ++pText;
    LogicalLine  = 0;
    PhysicalLine = 0;
    while (pText < pEnd)
    {
        LineSize = sizeof(LineBuffer);
        pText = PeekLine(pText, pEnd, LineBuffer, &LineSize);
        if (pText == NULL)
            break;

        ++PhysicalLine;
        if (LineSize == 0)
        {
            ++LogicalLine;
            continue;
        }

        if (IsComment(LineBuffer))
            continue;

        ++LogicalLine;
        if (IsControlSentance(LineBuffer))
            continue;

        ScrText.Text          = L"";
        ScrText.CharNameIndex = -1;
        ScrText.VoiceName     = L"";
        ScrText.LogicalLine   = LogicalLine;
        ScrText.PhysicalLine  = PhysicalLine;

        LineSize /= sizeof(*pText);
        pBuffer = LineBuffer + LineSize - 1;
        while (pBuffer > LineBuffer)
        {
            ch = *pBuffer;
            if (ch == ',')
            {
                *pBuffer++ = 0;
                break;
            }
            --pBuffer;
        }

        ScrText.Text = pBuffer--;

        if (pBuffer >= LineBuffer)
        {
            while (pBuffer > LineBuffer)
            {
                ch = *pBuffer;
                if (ch == ',')
                {
                    *pBuffer++ = 0;
                    break;
                }
                --pBuffer;
            }
            ScrText.CharNameIndex = FindCharName(pBuffer--);
        }

        if (pBuffer >= LineBuffer)
        {

            while (pBuffer > LineBuffer)
            {
                ch = *pBuffer;
                if (ch == ',')
                {
                    ++pBuffer;
                    break;
                }
                --pBuffer;
            }

            ScrText.VoiceName = pBuffer;
        }

        m_VecTextOrigianl.push_back(ScrText);
    }

    return SCR_ERROR_SUCCESS;
}

PWChar CModelScript::GetCharNameOriginalByIndex(SizeT Index)
{
    if (Index > m_VecCharNameOriginal.size())
        return NULL;

    return m_VecCharNameOriginal[Index];
}

PWChar CModelScript::GetCharNameTranslationByIndex(SizeT Index)
{
    if (Index > m_VecCharNameTranslation.size())
        return NULL;

    return m_VecCharNameTranslation[Index];
}

SizeT CModelScript::GetTextListOriginal(SScriptText **pScriptText)
{
    if (pScriptText != NULL)
        *pScriptText = &m_VecTextOrigianl[0];
    return m_VecTextOrigianl.size();
}

SizeT CModelScript::GetTextListTranslation(SScriptText **pScriptText)
{
    if (pScriptText != NULL)
        *pScriptText = &m_VecTextTranslation[0];
    return m_VecTextTranslation.size();
}

SizeT CModelScript::GetTextListOriginalCount()
{
    return GetTextListOriginal(NULL);
}

SizeT CModelScript::GetTextListTranslationCount()
{
    return GetTextListTranslation(NULL);
}

Bool
CModelScript::
UpdateTextWorker(
    VectorText &VecText,
    SizeT Index,
    PCWChar pszText,
    SScriptText **pChangedText
)
{
    if (pChangedText != NULL)
        *pChangedText = NULL;

    if (Index > VecText.size())
        return NULL;

    SScriptText *pText;

    pText = &VecText[Index];

    if (pChangedText != NULL)
        *pChangedText = pText;

    if (pText->Text == pszText)
        return False;

    pText->Text = pszText;

    return True;
}

Bool CModelScript::UpdateTextOriginal(SizeT Index, PCWChar pszText, SScriptText **pChangedText)
{
    return UpdateTextWorker(m_VecTextOrigianl, Index, pszText, pChangedText);
}

Bool CModelScript::UpdateTextTranslation(SizeT Index, PCWChar pszText, SScriptText **pChangedText)
{
    return UpdateTextWorker(m_VecTextTranslation, Index, pszText, pChangedText);
}

SScriptText* CModelScript::GetTextOriginal(SizeT Index)
{
    return Index > m_VecTextOrigianl.size() ? NULL : &m_VecTextOrigianl[Index];
}

SScriptText* CModelScript::GetTextTranslation(SizeT Index)
{
    return Index > m_VecTextTranslation.size() ? NULL : &m_VecTextTranslation[Index];
}

Void CModelScript::GetTextSelectionRange(SScriptText *pText, PSizeT pStart, PSizeT pEnd)
{
    SizeT  Start, End;
    WChar  ch;
    PWChar pszBuffer;

    Start = 0;
    End   = pText->Text.GetLength();
    pszBuffer = pText->Text;
    while (ch = pszBuffer[Start])
    {
        if (ch != L'¡¸' &&
            ch != L'¡¡' &&
            ch != '\t'  &&
            ch != ' ')
        {
            break;
        }
        ++Start;
    }

    while (ch = pszBuffer[End - 1])
    {
        if (ch != L'¡£' &&
            ch != L'¡­'  &&
            ch != L'¡¹' &&
            ch != L'£¡' &&
            ch != L'£¿' &&
            ch != '\t'  &&
            ch != ' ')
        {
            break;
        }
        --End;
    }

    *pStart = Start;
    *pEnd = End;
}

Long CModelScript::SaveTranslationToFile()
{
    SizeT  Length;
    PTChar pszTransPath;
    WChar  szBuffer[0x1000];
    CFileDisk file;
    SScriptText *pText;

    if (m_VecTextTranslation.size() == 0)
        return SCR_ERROR_EMPTY_TRANSLATION_TEXT;

    pszTransPath = (PTChar)szBuffer;
    memcpy(pszTransPath, m_ScriptPath.GetBuffer(), (m_ScriptPath.GetLength() + 1) * sizeof(*pszTransPath));
    GenerateTranslationFileName(pszTransPath);

    if (!file.Open(pszTransPath, file.FILE_ACCESS_WRITE, file.FILE_SHAREMODE_READ, file.FILE_CREATE_ALWAYS))
        return SCR_ERROR_IO_FAILED_OPEN;

    Length = BOM_UTF16_LE;
    if (!file.Write(&Length, 2))
        return SCR_ERROR_IO_FAILED_WRITE;

    Length = m_VecCharNameOriginal.size();
    if (Length != 0)
    {
        SizeT i;
        StringW *pCharName;

        i = Length;
        Length = wsprintfW(szBuffer, L"@Name=");
        pCharName = &m_VecCharNameOriginal[0];
        do
        {
            Length += wsprintfW(szBuffer + Length, L"%s,", pCharName->GetBuffer());
            ++pCharName;
        } while (--i);

        if (Length != 0)
        {
            *(PUInt32)&szBuffer[Length - 1] = 0x000A000D;
            if (!file.Write(szBuffer, ++Length * sizeof(*szBuffer)))
                return SCR_ERROR_IO_FAILED_WRITE;
        }
    }

    pText = &m_VecTextTranslation[0];
    for (SizeT i = m_VecTextTranslation.size(); i; --i)
    {
        Length = wsprintfW(
                     szBuffer,
                     L"@Text=%d,%d,%d,%s\r\n",
                     pText->PhysicalLine,
                     pText->LogicalLine,
                     pText->CharNameIndex,
                     pText->Text);
        if (!file.Write(szBuffer, Length * sizeof(*szBuffer)))
            return SCR_ERROR_IO_FAILED_WRITE;

        ++pText;
    }

    return SCR_ERROR_SUCCESS;
}

Long CModelScript::DeleteTranslationFile()
{
    TChar szPath[MAX_PATH];

    m_ScriptPath.CopyTo(szPath, countof(szPath));
    GenerateTranslationFileName(szPath);
    DeleteFile(szPath);

    return SCR_ERROR_SUCCESS;
}

Long CModelScript::SubmitAllTranslation()
{
    SizeT  LogicalLine, PhysicalLine, LineSize, BufferSize;
    WChar  LineBuffer[0x1000];
    PWChar pText, pEnd;
    PVoid  pvBuffer;
    CFileDisk file;

//    Long   Result;
//    Result = SaveTranslation();
//    if (SCR_FAILED(Result))
//        return Result;

    if (!file.Open(
            m_ScriptPath,
            file.FILE_ACCESS_READ | file.FILE_ACCESS_WRITE,
            file.FILE_SHAREMODE_READ,
            file.FILE_OPEN_EXIST))
    {
        return SCR_ERROR_IO_FAILED_OPEN;
    }

    BufferSize = file.GetSize();
    pvBuffer = m_mem.Alloc(BufferSize);
    if (pvBuffer == NULL)
        return SCR_ERROR_OUT_OF_MEMORY;

    if (!file.Read(pvBuffer))
    {
        m_mem.Free(pvBuffer);
        return SCR_ERROR_IO_FAILED_READ;
    }

    pText = (PWChar)pvBuffer;
    if (*pText != BOM_UTF16_LE)
    {
        m_mem.Free(pvBuffer);
        return SCR_ERROR_INVALID_ENCODING;
    }

    file.Seek(file.FILE_SEEK_BEGIN, 2);
    pEnd = (PWChar)((PByte)pvBuffer + BufferSize);

    SScriptText *pOrigText, *pTransText;

    ++pText;
    pOrigText  = &m_VecTextOrigianl[0];
    pTransText = &m_VecTextTranslation[0];
    LogicalLine  = 0;
    PhysicalLine = 0;
    while (pText < pEnd)
    {
        LineSize = sizeof(LineBuffer);
        pText = PeekLine(pText, pEnd, LineBuffer, &LineSize);
        if (pText == NULL)
            break;

        ++PhysicalLine;
        LogicalLine += !IsComment(LineBuffer);
        lstrcatW(LineBuffer, L"\r\n");
        if (LineSize == 0 || IsComment(LineBuffer) || IsControlSentance(LineBuffer))
        {
            file.Write(LineBuffer, LineSize + 4);
            continue;
        }

        if (PhysicalLine != pTransText->PhysicalLine || LogicalLine != pTransText->LogicalLine)
        {
            ;
        }

        LineSize = 0;
        if (!pTransText->VoiceName.IsEmpty() && pTransText->VoiceName != L"")
            LineSize = wsprintfW(LineBuffer, L"%s,", (PWChar)pTransText->VoiceName);
        else if (!pOrigText->VoiceName.IsEmpty() && pOrigText->VoiceName != L"")
            LineSize = wsprintfW(LineBuffer, L"%s,", (PWChar)pOrigText->VoiceName);

        if (pTransText->CharNameIndex != -1)
            LineSize += wsprintfW(LineBuffer + LineSize, L"%s,", GetCharNameTranslationByIndex(pTransText->CharNameIndex));

        LineSize += wsprintfW(LineBuffer + LineSize, L"%s\r\n", (PWChar)pTransText->Text);
        file.Write(LineBuffer, LineSize * sizeof(*LineBuffer));

        ++pOrigText;
        ++pTransText;
    }

    m_mem.Free(pvBuffer);
    file.SetEndOfFile();
    DeleteTranslationFile();

    m_VecTextOrigianl = m_VecTextTranslation;
    m_VecCharNameOriginal = m_VecCharNameTranslation;

    return SCR_ERROR_SUCCESS;
}