#include "ModelSplitter.h"
#include "sha256.h"
#include "LZMA/C/Lzma86.h"
#include "BinarySplitterMsg.h"
#pragma comment(lib, "ntdll.lib")

#define PART_FILE_SUFFIX _T("part")

Int CModelSplitter::GenerateOutputFileName(PCTChar pszOutFile, PTChar pszBuffer, Int64 Index)
{
    return FormatString(pszBuffer, _T("%s.%s%d"), pszOutFile, PART_FILE_SUFFIX, Index);
}

Long
CModelSplitter::
VerifyIsOutputFileExist(
    PCTChar pszInFile,
    PTChar  pszOutFile,
    SizeT   BufferCount,
    Int64   SliceSizeInByte
)
{
    Int64  Parts, Index;
    HANDLE hFile;
    TChar  szBuffer[MAX_PATH + 30];
    LARGE_INTEGER FileSize;

    UNUSED_VARIABLE(BufferCount);

    hFile = CreateFile(
                pszInFile,
                GENERIC_READ,
                0,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return BSERR_OPEN_FILE;

    GetFileSizeEx(hFile, &FileSize);
    CloseHandle(hFile);

    if ((UInt64)SliceSizeInByte > (UInt64)FileSize.QuadPart)
        return BSERR_INVALID_SLICE_SIZE;

    Parts = FileSize.QuadPart / SliceSizeInByte;
    if (pszOutFile[0] == 0)
    {
        lstrcpy(szBuffer, pszInFile);
        rmext(szBuffer);
    }
    else
    {
        lstrcpy(szBuffer, pszOutFile);
    }

    Index = 0;
    do
    {
        GenerateOutputFileName(szBuffer, pszOutFile, Index++);
        if (IsPathExists(pszOutFile))
            return BSERR_NORMAL;

    } while (--Parts);

    return BSERR_SUCCESS;
}

Long CModelSplitter::Split(SPLIT_OPTION *pSplitOption)
{
    SPLIT_WORK_THREAD_INFO *pInfo;

    if (pSplitOption == NULL)
        return BSERR_INVALID_PARAM;

    pInfo = new SPLIT_WORK_THREAD_INFO;
    if (pInfo == NULL)
        return BSERR_OUT_OF_MEMORY;

    pInfo->SpliceSizeInByte     = pSplitOption->SpliceSizeInByte;
    pInfo->InputFile            = pSplitOption->InputFile;
    pInfo->CallbackParam        = pSplitOption->CallbackParam;
    pInfo->pfShowErrorMessage   = pSplitOption->pfShowErrorMessage;
    pInfo->pfShowAskMessage     = pSplitOption->pfShowAskMessage;
    pInfo->pfShowStatusMessage  = pSplitOption->pfShowStatusMessage;
    pInfo->pfShowStatus         = pSplitOption->pfShowStatus;
    pInfo->Password             = pSplitOption->Password;
    pInfo->This                 = this;
    pInfo->Flags                = 0;

    if (pSplitOption->fCompress)     pInfo->Flags |= SPLIT_FLAG_COMPRESS;
    if (pSplitOption->fEncrypt)      pInfo->Flags |= SPLIT_FLAG_ENCRYPT;
    if (pSplitOption->fSaveFileName) pInfo->Flags |= SPLIT_FLAG_SAVE_ORIG_NAME;

    if (!pSplitOption->OutputFile.IsEmpty())
    {
        pInfo->OutputFile = pSplitOption->OutputFile;
    }
    else
    {
        pInfo->OutputFile = pInfo->InputFile;
        pInfo->OutputFile.RemoveExtension();
    }

    if (!QueueUserWorkItem((LPTHREAD_START_ROUTINE)SplitWorkerCallback, pInfo, WT_EXECUTEDEFAULT))
    {
        delete pInfo;
        return BSERR_QUEUE_USER_WORD_ITEM;
    }

    return BSERR_SUCCESS;
}

Long CModelSplitter::Merge(MERGE_OPTION *pMergeOption)
{
    MERGE_WORK_THREAD_INFO *pInfo;

    if (pMergeOption == NULL)
        return BSERR_INVALID_PARAM;

    pInfo = new MERGE_WORK_THREAD_INFO;
    if (pInfo == NULL)
        return BSERR_OUT_OF_MEMORY;

    pInfo->InputFile            = pMergeOption->InputFile;
    pInfo->CallbackParam        = pMergeOption->CallbackParam;
    pInfo->pfShowErrorMessage   = pMergeOption->pfShowErrorMessage;
    pInfo->pfShowAskMessage     = pMergeOption->pfShowAskMessage;
    pInfo->pfShowStatusMessage  = pMergeOption->pfShowStatusMessage;
    pInfo->pfShowStatus         = pMergeOption->pfShowStatus;
    pInfo->Password             = pMergeOption->Password;
    pInfo->This                 = this;
    pInfo->Flags                = 0;

    if (pMergeOption->OutputFile.IsEmpty())
    {
        pInfo->OutputFile = pInfo->InputFile;
        pInfo->OutputFile.ReplaceExtension(_T(".bin"));
    }
    else
    {
        pInfo->OutputFile = pMergeOption->OutputFile;
    }

    if (pMergeOption->fRestoreFileName) pInfo->Flags |= MERGE_FLAG_RESTORE_NAME;

    if (!QueueUserWorkItem((LPTHREAD_START_ROUTINE)MergeWorkerCallback, pInfo, WT_EXECUTEDEFAULT))
    {
        delete pInfo;
        return BSERR_QUEUE_USER_WORD_ITEM;
    }

    return BSERR_SUCCESS;
}

Long CModelSplitter::VeirfyIsFirstFile(PCTChar pszFile, PInt32 pFlags)
{
    CFileDisk file;
    BS_PART_FILE_HEADER_FIRST FileHeader;

    if (pFlags == NULL)
        return BSERR_INVALID_PARAM;

    *pFlags = 0;

    if (!file.Open(pszFile))
        return BSERR_OPEN_FILE;

    if (file.GetSize() < sizeof(BS_PART_FILE_HEADER))
        return BSERR_INVALID_FILE_SIZE;

    if (!file.Read(&FileHeader, sizeof(FileHeader)))
        return BSERR_READ_FILE;

    DecryptHeader(&FileHeader, 0);
    if (FileHeader.Magic != BS_FILE_HEADER_MAGIC)
        return BSERR_INVALID_FORMAT;

    if (!TEST_BITS(FileHeader.Flags, SPLIT_FLAG_FIRST_FILE))
        return BSERR_MERGE_NOT_FIRST;

    *pFlags = FileHeader.Flags & (SPLIT_FLAG_ENCRYPT | SPLIT_FLAG_SAVE_ORIG_NAME);

    return BSERR_SUCCESS;
}

// for LZMA

EXTC void* MyAlloc(size_t size)
{
    return HeapAlloc(CMem::GetGlobalHeap(), 0, size);
}

EXTC void MyFree(void *address)
{
    HeapFree(CMem::GetGlobalHeap(), 0, address);
}

/************************************************************************/
/* merge                                                                */
/************************************************************************/

ULong STDCALL CModelSplitter::MergeWorkerCallback(MERGE_WORK_THREAD_INFO *pInfo)
{
    return pInfo->This->MergeWorkerNT5(pInfo);
}

ULong CModelSplitter::MergeWorkerNT6(MERGE_WORK_THREAD_INFO *pInfo)
{
    return MergeWorkerNT5(pInfo);
}

Bool CModelSplitter::IsAllPartsExists(MERGE_WORK_THREAD_INFO *pInfo, const BS_PART_FILE_HEADER_FIRST *pHeaderFirst)
{
    TChar  szSuffix[25];
    String PartFile(pInfo->InputFile);

#define SHOW_MSG(...)    pInfo->pfShowErrorMessage(pInfo->CallbackParam, __VA_ARGS__)
#define SHOW_STATUS(Status, Info) pInfo->pfShowStatusMessage((pInfo->CallbackParam), (Status), (PCTChar)(Info))

    for (UInt32 Index = pHeaderFirst->Parts; Index; )
    {
        FormatString(szSuffix, _T(".%s%d"), PART_FILE_SUFFIX, --Index);
        PartFile.ReplaceExtension(szSuffix);
        if (!IsPathExists(PartFile))
        {
            SHOW_STATUS(BSERR_FILE_NOT_FOUND, PartFile);
            return False;
        }
    }

    return True;

#undef SHOW_MSG
#undef SHOW_STATUS

}

ULong CModelSplitter::MergeWorkerNT5(MERGE_WORK_THREAD_INFO *pInfo)
{
    Long                      Status;
    PVoid                     pvBuffer, pvBufferDecompress;
    UInt32                    Key[8], PwdHash[4], Hash[8];
    sha256_ctx                s_ctx;
    aes_encrypt_ctx           aes_ctx;
    BS_PART_FILE_HEADER       FileHeader;
    BS_PART_FILE_HEADER_FIRST FileHeaderFirst;

    CFileDisk file, fileout;

    const SizeT MergeBufferSize = 64 * MEMORY_PAGE_SIZE;       // 256 KB
    const SizeT MergeDecompressBufferSize = MergeBufferSize * 2;

#define SHOW_MSG(...)    pInfo->pfShowErrorMessage(pInfo->CallbackParam, __VA_ARGS__)
#define SHOW_STATUS(Status, Info) pInfo->pfShowStatusMessage((pInfo->CallbackParam), (Status), (PCTChar)(Info))

    if (!file.Open(pInfo->InputFile))
    {
        SHOW_STATUS(BSERR_OPEN_FILE, pInfo->InputFile);
        goto _Exit;
    }

    if (!file.Read(&FileHeaderFirst, sizeof(FileHeaderFirst)))
    {
        SHOW_STATUS(BSERR_READ_FILE, pInfo->InputFile);
        goto _Exit;
    }

    DecryptHeader2(&FileHeaderFirst, NULL);
    if (FileHeaderFirst.Magic != BS_FILE_HEADER_MAGIC)
    {
        SHOW_STATUS(BSERR_INVALID_FORMAT, pInfo->InputFile);
        goto _Exit;
    }

    if (!TEST_BITS(FileHeaderFirst.Flags, SPLIT_FLAG_FIRST_FILE))
    {
        SHOW_STATUS(BSERR_MERGE_NOT_FIRST, pInfo->InputFile);
        goto _Exit;
    }

    if (TEST_BITS(FileHeaderFirst.Flags, SPLIT_FLAG_ENCRYPT))
    {
        if (pInfo->Password.IsEmpty())
        {
            SHOW_STATUS(BSERR_MERGE_INVALID_PASSWORD, NULL);
            goto _Exit;
        }

        InitKey(&aes_ctx, Key, PwdHash, 0, pInfo->Password, pInfo->Password.GetLength() * sizeof(WChar));
        Decrypt(&aes_ctx, &FileHeaderFirst.Parts, sizeof(FileHeaderFirst) - sizeof(FileHeader), Key);
        if (memcmp(FileHeaderFirst.PasswordHash, PwdHash, sizeof(PwdHash)))
        {
            SHOW_STATUS(BSERR_MERGE_INVALID_PASSWORD, NULL);
            goto _Exit;
        }
    }

    if (!IsAllPartsExists(pInfo, &FileHeaderFirst))
        goto _Exit;

    if (TEST_BITS(pInfo->Flags, MERGE_FLAG_RESTORE_NAME) &&
        TEST_BITS(FileHeaderFirst.Flags, SPLIT_FLAG_SAVE_ORIG_NAME) &&
        FileHeaderFirst.FileNameLength != 0)
    {
        FileHeaderFirst.OriginalFileName[FileHeaderFirst.FileNameLength] = 0;
        pInfo->OutputFile.ReplaceFileName(FileHeaderFirst.OriginalFileName);
    }

    if (IsPathExists(pInfo->OutputFile))
    {
        if (!pInfo->pfShowAskMessage(
            pInfo->CallbackParam,
            _T("%s\n%s"),
            (PCTChar)pInfo->OutputFile,
            BS_ERR_STRING_CONFIRM_TO_OVERWRITE))
        {
            goto _Exit;
        }
    }

    pvBuffer            = NULL;
    pvBufferDecompress  = NULL;
    Status              = BSERR_NORMAL;

    LOOP_ONCE
    {
        pvBuffer = VirtualAllocEx(
            NtCurrentProcess(),
            NULL,
            MergeBufferSize,
            MEM_RESERVE|MEM_COMMIT,
            PAGE_READWRITE);
        if (pvBuffer == NULL)
        {
            SHOW_STATUS(BSERR_OUT_OF_MEMORY, NULL);
            break;
        }

        if (TEST_BITS(FileHeaderFirst.Flags, SPLIT_FLAG_COMPRESS))
        {
            pvBufferDecompress = VirtualAllocEx(
                NtCurrentProcess(),
                0,
                MergeDecompressBufferSize,
                MEM_RESERVE|MEM_COMMIT,
                PAGE_READWRITE);
            if (pvBufferDecompress == NULL)
            {
                SHOW_STATUS(BSERR_OUT_OF_MEMORY, NULL);
                break;
            }
        }

        if (!fileout.Create(pInfo->OutputFile))
        {
            SHOW_STATUS(BSERR_CREATE_FILE, pInfo->OutputFile);
            break;
        }

        UInt32 Index = 0;
        ULarge_Integer PartSize, AlignedSize, FileSize, BytesProcessed;

        FileSize.LowPart = sizeof(FileHeaderFirst) - sizeof(FileHeaderFirst.OriginalFileName) - sizeof(FileHeaderFirst.FileNameLength);;
        if (TEST_BITS(FileHeaderFirst.Flags, SPLIT_FLAG_SAVE_ORIG_NAME))
             FileSize.LowPart += sizeof(FileHeaderFirst.FileNameLength) + FileHeaderFirst.FileNameLength * sizeof(WChar);

        file.Seek(file.FILE_SEEK_BEGIN, FileSize.LowPart);
        PartSize.LowPart = file.GetSize(&PartSize.HighPart);
        PartSize.QuadPart -= FileSize.LowPart;
        FileSize.QuadPart = FileHeaderFirst.FileSize;
        BytesProcessed.QuadPart = 0;

        FileHeader = *(BS_PART_FILE_HEADER *)&FileHeaderFirst;

        LOOP_ALWAYS
        {
            TChar szSuffix[25];

            if (FileHeader.Index != Index)
            {
                SHOW_STATUS(BSERR_MERGE_PART_FILE_CORRUPT, pInfo->InputFile);
                goto _Error;
            }

            if (PartSize.QuadPart == 0)
            {
                SHOW_STATUS(BSERR_INVALID_FILE_SIZE, pInfo->InputFile);
                goto _Error;
            }

            sha256_init(&s_ctx);
            if (TEST_BITS(FileHeaderFirst.Flags, SPLIT_FLAG_ENCRYPT))
                InitKey(&aes_ctx, Key, PwdHash, Index, pInfo->Password, pInfo->Password.GetLength() * sizeof(WChar));

            AlignedSize.QuadPart = ROUND_DOWN(PartSize.QuadPart, MergeBufferSize);
            PartSize.QuadPart   -= AlignedSize.QuadPart;

            while (AlignedSize.QuadPart != 0)
            {
                if (!file.Read(pvBuffer, MergeBufferSize))
                {
                    SHOW_STATUS(BSERR_READ_FILE, pInfo->InputFile);
                    goto _Error;
                }

                sha256_update(&s_ctx, (PByte)pvBuffer, MergeBufferSize);

                if (TEST_BITS(FileHeader.Flags, SPLIT_FLAG_ENCRYPT))
                    Decrypt(&aes_ctx, pvBuffer, MergeBufferSize, Key);

                if (TEST_BITS(FileHeader.Flags, SPLIT_FLAG_COMPRESS))
                {
                    // not implemented
                }

                if (!fileout.Write(pvBuffer, MergeBufferSize))
                {
                    SHOW_STATUS(BSERR_WRITE_FILE, pInfo->OutputFile);
                    goto _Error;
                }

                BytesProcessed.QuadPart += MergeBufferSize;
                if (!pInfo->pfShowStatus(pInfo->CallbackParam, &BytesProcessed, &FileSize))
                    goto _ForceStop;

                AlignedSize.QuadPart -= MergeBufferSize;
            }

            if (PartSize.LowPart != 0)
            {
                if (!file.Read(pvBuffer, PartSize.LowPart))
                {
                    SHOW_STATUS(BSERR_READ_FILE, pInfo->InputFile);
                    goto _Error;
                }

                sha256_update(&s_ctx, (PByte)pvBuffer, PartSize.LowPart);

                if (TEST_BITS(FileHeader.Flags, SPLIT_FLAG_ENCRYPT))
                    Decrypt(&aes_ctx, pvBuffer, PartSize.LowPart, Key);

                if (!fileout.Write(pvBuffer, PartSize.LowPart))
                {
                    SHOW_STATUS(BSERR_WRITE_FILE, pInfo->OutputFile);
                    goto _Error;
                }

                BytesProcessed.QuadPart += PartSize.LowPart;
                if (!pInfo->pfShowStatus(pInfo->CallbackParam, &BytesProcessed, &FileSize))
                    goto _ForceStop;
            }

            sha256_final(&s_ctx, (PByte)Hash);
            if (memcmp(Hash, FileHeader.DataHash, sizeof(Hash)))
            {
                SHOW_STATUS(BSERR_MERGE_PART_FILE_CORRUPT, pInfo->InputFile);
                break;
            }

            if (TEST_BITS(FileHeader.Flags, SPLIT_FLAG_LAST_FILE))
            {
                Status = BSERR_SUCCESS;
                break;
            }

            ++Index;
            FormatString(szSuffix, _T(".%s%d"), PART_FILE_SUFFIX, Index);
            pInfo->InputFile.ReplaceExtension(szSuffix);
            if (!file.Open(pInfo->InputFile))
            {
                SHOW_STATUS(BSERR_OPEN_FILE, pInfo->InputFile);
                break;
            }

            if (!file.Read(&FileHeader, sizeof(FileHeader)))
            {
                SHOW_STATUS(BSERR_READ_FILE, pInfo->InputFile);
                goto _Error;
            }

            DecryptHeader2(&FileHeader, Hash);
            PartSize.QuadPart = file.GetSize() - sizeof(FileHeader);

            if (FileHeader.Magic != BS_FILE_HEADER_MAGIC ||
                (Index + 1 == FileHeaderFirst.Parts && !TEST_BITS(FileHeader.Flags, SPLIT_FLAG_LAST_FILE)) ||
                (Index + 1 != FileHeaderFirst.Parts && TEST_BITS(FileHeader.Flags, SPLIT_FLAG_LAST_FILE)))
            {
                SHOW_STATUS(BSERR_MERGE_PART_FILE_CORRUPT, pInfo->InputFile);
                goto _Error;
            }
        }
    }

_ForceStop:
_Error:
/*
    if (BS_FAILED(Status))
        fileout.Delete();
*/
    if (BS_FAILED(Status))
    {
        fileout.Close();
        DeleteFile(pInfo->OutputFile);
    }

    if (pvBuffer)           VirtualFreeEx(NtCurrentProcess(), pvBuffer,           0, MEM_RELEASE);
    if (pvBufferDecompress) VirtualFreeEx(NtCurrentProcess(), pvBufferDecompress, 0, MEM_RELEASE);

_Exit:
    pInfo->pfShowStatus(pInfo->CallbackParam, NULL, NULL);
    delete pInfo;

    return 0;

#undef SHOW_MSG
#undef SHOW_STATUS

}

/************************************************************************/
/* split                                                                */
/************************************************************************/

ULong STDCALL CModelSplitter::SplitWorkerCallback(SPLIT_WORK_THREAD_INFO *pInfo)
{
    return pInfo->This->SplitWorkerNT5(pInfo);
}

ULong CModelSplitter::SplitWorkerNT5(SPLIT_WORK_THREAD_INFO *pInfo)
{
    union
    {
        BS_PART_FILE_HEADER       FileHeader;
        BS_PART_FILE_HEADER_FIRST FileHeaderFirst;
    };

    Long                Status;
    UInt32              Index, HeaderSize;
    TChar               szSuffix[25];
    HANDLE              hFileIn, hFileOut;
    PVoid               pvBuffer, pvBuffer1, pvBuffer2;
    ULARGE_INTEGER      FileSize, PartSize;
    CIoCompletionPort   IoCompletionPort;

    const SizeT SplitBufferSize = 64 * MEMORY_PAGE_SIZE;       // 256 KB

#define SHOW_MSG(...) pInfo->pfShowErrorMessage(pInfo->CallbackParam, __VA_ARGS__)
#define SHOW_STATUS(Status, Info) pInfo->pfShowStatusMessage((pInfo->CallbackParam), (Status), (PCTChar)(Info))

    Index     = 0;
    Status    = BSERR_SUCCESS;
    pvBuffer1 = NULL;
    pvBuffer2 = NULL;
    hFileIn   = INVALID_HANDLE_VALUE;
    hFileOut  = INVALID_HANDLE_VALUE;

    hFileIn = CreateFileW(
                    pInfo->InputFile,
                    GENERIC_READ,
                    FILE_SHARE_READ,
                    NULL,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,
                    NULL);
    if (hFileIn == INVALID_HANDLE_VALUE)
    {
        SHOW_STATUS(BSERR_OPEN_FILE, pInfo->InputFile);
        goto _Exit;
    }

    if (!GetFileSizeEx(hFileIn, (PLARGE_INTEGER)&FileSize))
    {
        SHOW_STATUS(BSERR_GET_FILE_SIZE, pInfo->InputFile);
        goto _Exit;
    }

    if (FileSize.QuadPart == 0)
    {
        SHOW_STATUS(BSERR_ZERO_FILE_SIZE, pInfo);
        goto _Exit;
    }
    else if ((ULong64)FileSize.QuadPart <= (ULong64)pInfo->SpliceSizeInByte.QuadPart)
    {
        SHOW_STATUS(BSERR_INVALID_SLICE_SIZE, NULL);
        goto _Exit;
    }

    HeaderSize = sizeof(FileHeaderFirst) - sizeof(FileHeaderFirst.FileNameLength) - sizeof(FileHeaderFirst.OriginalFileName);
    if (TEST_BITS(pInfo->Flags, SPLIT_FLAG_SAVE_ORIG_NAME))
    {
        Int Length;
        PTChar pszFileName;

        HeaderSize += sizeof(FileHeaderFirst.FileNameLength);
        pszFileName = findname(pInfo->InputFile);

#if defined(UNICODE) || defined(_UNICODE)
        FileHeaderFirst.FileNameLength = StrLengthW(pszFileName);
        Length = FileHeaderFirst.FileNameLength * sizeof(WChar);
        HeaderSize += Length;
        CopyMemory(FileHeaderFirst.OriginalFileName, pszFileName, Length);
#else
        FileHeaderFirst.FileNameLength = MultiByteToWideChar(
            CP_ACP,
            0,
            pszFileName,
            -1,
            FileHeaderFirst.OriginalFileName,
            countof(FileHeaderFirst.OriginalFileName));
        --FileHeaderFirst.FileNameLength;
        Length = FileHeaderFirst.FileNameLength * sizeof(WChar);
        HeaderSize += Length;
#endif
    }

    PartSize.QuadPart = pInfo->SpliceSizeInByte.QuadPart - HeaderSize;
    FileHeaderFirst.Parts = ((FileSize.QuadPart - PartSize.QuadPart - 1) / (pInfo->SpliceSizeInByte.QuadPart - sizeof(FileHeader)) + 1) + 1;
    for (UInt32 i = 0; i != FileHeaderFirst.Parts; ++i)
    {
        FormatString(szSuffix, _T(".%s%d"), PART_FILE_SUFFIX, i);
        pInfo->OutputFile.ReplaceExtension(szSuffix);
        if (IsPathExists(pInfo->OutputFile))
        {
            if (!pInfo->pfShowAskMessage(
                     pInfo->CallbackParam,
                     _T("%s\n%s"),
                     (PCTChar)pInfo->OutputFile,
                     BS_ERR_STRING_CONFIRM_TO_OVERWRITE))
            {
                goto _Error;
            }
            else
            {
                break;
            }
        }
    }

    pvBuffer1 = VirtualAllocEx(
                    NtCurrentProcess(),
                    NULL,
                    SplitBufferSize,
                    MEM_RESERVE|MEM_COMMIT,
                    PAGE_READWRITE);
    if (pvBuffer1 == NULL)
    {
        SHOW_STATUS(BSERR_OUT_OF_MEMORY, NULL);
        goto _Exit;
    }

    pvBuffer2 = VirtualAllocEx(
                    NtCurrentProcess(),
                    NULL,
                    SplitBufferSize,
                    MEM_RESERVE|MEM_COMMIT,
                    PAGE_READWRITE);
    if (pvBuffer2 == NULL)
    {
        SHOW_STATUS(BSERR_OUT_OF_MEMORY, NULL);
        goto _Exit;
    }

    UInt32              Key[8], PrevPartHash[8];
    sha256_ctx          s_ctx;
    aes_encrypt_ctx     aes_ctx;
    ULarge_Integer      BytesProcessed, TotalSize;
    OVERLAPPED          OverlappedRead, OverlappedWrite;

    if (!IoCompletionPort.Create(0))
    {
        SHOW_STATUS(BSERR_IOCP_CREATE, NULL);
        goto _Exit;
    }
    if (!IoCompletionPort.AssociateDevice(hFileIn, BS_IOCP_KEY_READ))
    {
        SHOW_STATUS(BSERR_IOCP_ASSOCIATE_DEVICE, pInfo->InputFile);
        goto _Exit;
    }

    OverlappedRead.Offset     = 0;
    OverlappedRead.OffsetHigh = 0;
    OverlappedRead.hEvent     = NULL;
    OverlappedWrite.hEvent    = NULL;

    FileHeaderFirst.Magic = BS_FILE_HEADER_MAGIC;
    FileHeaderFirst.FileSize = FileSize.QuadPart;

    Index  = 0;
    Status = BSERR_NORMAL;
    BytesProcessed.QuadPart = 0;
    TotalSize.QuadPart = FileSize.QuadPart;

    FileHeader = *(BS_PART_FILE_HEADER *)&FileHeaderFirst;

    LOOP_ALWAYS
    {
        ULong     BytesToWrite, BytesToRead, BytesTransfered;
        ULong_Ptr CompletionKey;

        FileSize.QuadPart -= min(PartSize.QuadPart, FileSize.QuadPart);

        FormatString(szSuffix, _T(".%s%d"), PART_FILE_SUFFIX, Index);
        pInfo->OutputFile.ReplaceExtension(szSuffix);
        hFileOut = CreateFileW(
                       pInfo->OutputFile,
                       GENERIC_WRITE,
                       FILE_SHARE_READ,
                       NULL,
                       CREATE_ALWAYS,
                       FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,
                       NULL);
        if (hFileOut == INVALID_HANDLE_VALUE)
        {
            SHOW_STATUS(BSERR_CREATE_FILE, pInfo->OutputFile);
            goto _Error;
        }
        if (!IoCompletionPort.AssociateDevice(hFileOut, BS_IOCP_KEY_WRITE))
        {
            SHOW_STATUS(BSERR_IOCP_ASSOCIATE_DEVICE, pInfo->OutputFile);
            goto _Error;
        }

        sha256_init(&s_ctx);
        if (TEST_BITS(pInfo->Flags, SPLIT_FLAG_ENCRYPT))
            InitKey(&aes_ctx, Key, FileHeaderFirst.PasswordHash, Index, (PCWChar)pInfo->Password, pInfo->Password.GetLength() * sizeof(WChar));

        FileHeader.Flags = pInfo->Flags;
        if (Index == 0)
            FileHeader.Flags |= SPLIT_FLAG_FIRST_FILE;
        if (FileSize.QuadPart == 0)
            FileHeader.Flags |= SPLIT_FLAG_LAST_FILE;

        pvBuffer                    = NULL;
        BytesToWrite                = 0;
        OverlappedWrite.Offset      = HeaderSize;
        OverlappedWrite.OffsetHigh  = 0;
        FileHeader.PartOriginalSize = PartSize.QuadPart;

        BytesToRead = min(SplitBufferSize, PartSize.QuadPart);
        ReadFile(hFileIn, pvBuffer1, BytesToRead, NULL, &OverlappedRead);

        LOOP_ALWAYS
        {
            LPOVERLAPPED  pOverlapped;
            LARGE_INTEGER Offset;

            if (!IoCompletionPort.GetStatus(&CompletionKey, &BytesTransfered, &pOverlapped))
            {
                SHOW_STATUS(BSERR_IOCP_GET_STATUS, NULL);
                goto _Error;
            }

            if (CompletionKey == BS_IOCP_KEY_READ)
            {
                Bool bContinue;
                if (BytesToWrite != 0)
                {
                    IoCompletionPort.PostStatus(CompletionKey, BytesTransfered, pOverlapped);
                    continue;
                }

                BytesProcessed.QuadPart += BytesTransfered;
                bContinue = pInfo->pfShowStatus(pInfo->CallbackParam, &BytesProcessed, &TotalSize);
                if (!bContinue)
                {
                    goto _Error;
                }

                pvBuffer     = pvBuffer1;
                BytesToWrite = BytesTransfered;

                Offset.LowPart          = OverlappedRead.Offset;
                Offset.HighPart         = OverlappedRead.OffsetHigh;
                Offset.QuadPart        += BytesTransfered;
                pOverlapped->Offset     = Offset.LowPart;
                pOverlapped->OffsetHigh = Offset.HighPart;

                PartSize.QuadPart -= BytesTransfered, PartSize.QuadPart;
                if (PartSize.QuadPart != 0)
                {

                    Swap(pvBuffer1, pvBuffer2);
                    BytesToRead = min(SplitBufferSize, PartSize.QuadPart);
                    ReadFile(hFileIn, pvBuffer1, BytesToRead, NULL, pOverlapped);
                }

                if (BytesToWrite != 0)
                {

                    if (TEST_BITS(FileHeader.Flags, SPLIT_FLAG_COMPRESS))
                    {
                        // not implemented
                    }

                    if (TEST_BITS(FileHeader.Flags, SPLIT_FLAG_ENCRYPT))
                        Encrypt(&aes_ctx, pvBuffer, BytesToWrite, Key);

                    sha256_update(&s_ctx, (PByte)pvBuffer, BytesToWrite);
                    WriteFile(hFileOut, pvBuffer, BytesToWrite, NULL, &OverlappedWrite);
                }
            }
            else // if (CompletionKey == SPLIT_IOCP_KEY_WRITE)
            {
                if (PartSize.QuadPart != 0)
                {
                    BytesToWrite            = 0;
                    Offset.LowPart          = pOverlapped->Offset;
                    Offset.HighPart         = pOverlapped->OffsetHigh;
                    Offset.QuadPart        += BytesTransfered;
                    pOverlapped->Offset     = Offset.LowPart;
                    pOverlapped->OffsetHigh = Offset.HighPart;
                    continue;
                }

                sha256_final(&s_ctx, (PByte)FileHeader.DataHash);

                BS_PART_FILE_HEADER_FIRST Header = FileHeaderFirst;

                Header.Index = Index;
                if (TEST_BITS(Header.Flags, SPLIT_FLAG_FIRST_FILE))
                {
                    if (TEST_BITS(Header.Flags, SPLIT_FLAG_ENCRYPT))
                        Encrypt(&aes_ctx, (PByte)&Header + sizeof(FileHeader), HeaderSize - sizeof(FileHeader), &Key[4]);

                    EncryptHeader2(&Header, NULL);
                }
                else
                {
                    EncryptHeader2(&Header, PrevPartHash);
                }

                CopyMemory(PrevPartHash, FileHeader.DataHash, sizeof(PrevPartHash));

                OverlappedWrite.Offset = 0;
                OverlappedWrite.OffsetHigh = 0;
                WriteFile(hFileOut, &Header, HeaderSize, NULL, &OverlappedWrite);
                IoCompletionPort.GetStatus(&CompletionKey, &BytesTransfered, &pOverlapped);
                break;
            }
        }

        if (TEST_BITS(FileHeader.Flags, SPLIT_FLAG_LAST_FILE))
        {
            Status = BSERR_SUCCESS;
            break;
        }

        CloseHandle(hFileOut);
        hFileOut = INVALID_HANDLE_VALUE;

        ++Index;
        HeaderSize = sizeof(BS_PART_FILE_HEADER);
        PartSize.QuadPart = pInfo->SpliceSizeInByte.QuadPart - HeaderSize;
        PartSize.QuadPart = min(FileSize.QuadPart, PartSize.QuadPart);
    }

_Error:
_Exit:
    if (pvBuffer1) VirtualFreeEx(NtCurrentProcess(), pvBuffer1, 0, MEM_RELEASE);
    if (pvBuffer2) VirtualFreeEx(NtCurrentProcess(), pvBuffer2, 0, MEM_RELEASE);

    if (hFileIn  != INVALID_HANDLE_VALUE) CloseHandle(hFileIn);
    if (hFileOut != INVALID_HANDLE_VALUE) CloseHandle(hFileOut);

    if (BS_FAILED(Status))
    {
        do
        {
            FormatString(szSuffix, _T(".%s%d"), PART_FILE_SUFFIX, Index);
            pInfo->OutputFile.ReplaceExtension(szSuffix);
            DeleteFile(pInfo->OutputFile);
        } while (--Index != -1);
    }

    pInfo->pfShowStatus(pInfo->CallbackParam, NULL, NULL);
    delete pInfo;

    return 0;

#undef SHOW_MSG
#undef SHOW_STATUS

}

Void CModelSplitter::InitKey(aes_encrypt_ctx *aes_context, UInt32 (Key)[8], UInt32 (PwdHash)[4], UInt32 Index, PCWChar pszPassword, SizeT cbSize)
{
    sha256((PByte)pszPassword, cbSize, (PByte)Key);

    ++Index;
    Key[0] = _rotl(Key[0], Index);
    Key[1] = _rotl(Key[1], Index);
    Key[2] = _rotl(Key[2], Index);
    Key[3] = _rotl(Key[3], Index);

    aes_encrypt_key128(&Key[4], aes_context);

    if (PwdHash != NULL)
    {
        PwdHash[0] = Key[0] ^ Key[4];
        PwdHash[1] = Key[1] ^ Key[5];
        PwdHash[2] = Key[2] ^ Key[6];
        PwdHash[3] = Key[3] ^ Key[7];
    }

    Key[4] = Key[0];
    Key[5] = Key[1];
    Key[6] = Key[2];
    Key[7] = Key[3];
}

Void CModelSplitter::Encrypt(aes_encrypt_ctx *aes_context, PVoid pvBuffer, SizeT Size, PVoid pvKey)
{
    SizeT   AlignedSize;
    PByte   pbBuffer = (PByte)pvBuffer;
    PUInt32 pKey = (PUInt32)pvKey;

    AlignedSize = ROUND_DOWN(Size, 16);
    for (SizeT s = AlignedSize; s != 0; s -= 16)
    {
        aes_encrypt(pKey, pKey, aes_context);

        pKey[0] = *((PUInt32)pbBuffer + 0) ^= pKey[0];
        pKey[1] = *((PUInt32)pbBuffer + 1) ^= pKey[1];
        pKey[2] = *((PUInt32)pbBuffer + 2) ^= pKey[2];
        pKey[3] = *((PUInt32)pbBuffer + 3) ^= pKey[3];

        pbBuffer += 16;
    }

    if (Size -= AlignedSize)
    {
        Byte Buffer[16];

        CopyMemory(Buffer, pbBuffer, Size);
//        ZeroMemory(Buffer + Size, sizeof(Buffer) - Size);

        aes_encrypt(pKey, pKey, aes_context);

        pKey[0] = *((PUInt32)Buffer + 0) ^= pKey[0];
        pKey[1] = *((PUInt32)Buffer + 1) ^= pKey[1];
        pKey[2] = *((PUInt32)Buffer + 2) ^= pKey[2];
        pKey[3] = *((PUInt32)Buffer + 3) ^= pKey[3];

        CopyMemory(pbBuffer, Buffer, Size);
    }
}

Void CModelSplitter::Decrypt(aes_encrypt_ctx *aes_context, PVoid pvBuffer, SizeT Size, PVoid pvKey)
{
    SizeT   AlignedSize;
    PByte   pbBuffer = (PByte)pvBuffer;
    PUInt32 pKey = (PUInt32)pvKey;

    AlignedSize = ROUND_DOWN(Size, 16);
    for (SizeT s = AlignedSize; s != 0; s -= 16)
    {
        aes_encrypt(pKey, pKey, aes_context);

        Swap(((PUInt32)pbBuffer)[0], pKey[0]);
        Swap(((PUInt32)pbBuffer)[1], pKey[1]);
        Swap(((PUInt32)pbBuffer)[2], pKey[2]);
        Swap(((PUInt32)pbBuffer)[3], pKey[3]);

        *((PUInt32)pbBuffer + 0) ^= pKey[0];
        *((PUInt32)pbBuffer + 1) ^= pKey[1];
        *((PUInt32)pbBuffer + 2) ^= pKey[2];
        *((PUInt32)pbBuffer + 3) ^= pKey[3];

        pbBuffer += 16;
    }

    if (Size -= AlignedSize)
    {
        Byte Buffer[16];

        CopyMemory(Buffer, pbBuffer, Size);
//        ZeroMemory(Buffer + Size, sizeof(Buffer) - Size);

        aes_encrypt(pKey, pKey, aes_context);

        Swap(((PUInt32)Buffer)[0], pKey[0]);
        Swap(((PUInt32)Buffer)[1], pKey[1]);
        Swap(((PUInt32)Buffer)[2], pKey[2]);
        Swap(((PUInt32)Buffer)[3], pKey[3]);

        *((PUInt32)Buffer + 0) ^= pKey[0];
        *((PUInt32)Buffer + 1) ^= pKey[1];
        *((PUInt32)Buffer + 2) ^= pKey[2];
        *((PUInt32)Buffer + 3) ^= pKey[3];

        CopyMemory(pbBuffer, Buffer, Size);
    }
}

Void CModelSplitter::EncryptHeader(BS_PART_FILE_HEADER *pHeader, UInt32 Index)
{
    UInt32 Key[8];
    aes_encrypt_ctx aes_ctx;

    InitKey(&aes_ctx, Key, NULL, Index, BS_INTERNAL_ENCRYPT_KEY, sizeof(BS_INTERNAL_ENCRYPT_KEY));
    Encrypt(&aes_ctx, pHeader, sizeof(*pHeader), Key);
}

Void CModelSplitter::DecryptHeader(BS_PART_FILE_HEADER *pHeader, UInt32 Index)
{
    UInt32 Key[8];
    aes_encrypt_ctx aes_ctx;

    InitKey(&aes_ctx, Key, NULL, Index, BS_INTERNAL_ENCRYPT_KEY, sizeof(BS_INTERNAL_ENCRYPT_KEY));
    Decrypt(&aes_ctx, pHeader, sizeof(*pHeader), Key);
}

Void CModelSplitter::EncryptHeader2(BS_PART_FILE_HEADER *pHeader, UInt32 (PrevPartHash)[8])
{
    UInt32 Key[4];
    aes_encrypt_ctx aes_ctx;

    if (PrevPartHash == NULL)
    {
        EncryptHeader(pHeader, 0);
        return;
    }

    Key[0] = PrevPartHash[0];
    Key[1] = PrevPartHash[1];
    Key[2] = PrevPartHash[2];
    Key[3] = PrevPartHash[3];
    aes_encrypt_key128(&PrevPartHash[4], &aes_ctx);
    Encrypt(&aes_ctx, pHeader, sizeof(*pHeader), Key);
}

Void CModelSplitter::DecryptHeader2(BS_PART_FILE_HEADER *pHeader, UInt32 (PrevPartHash)[8])
{
    UInt32 Key[4];
    aes_encrypt_ctx aes_ctx;

    if (PrevPartHash == NULL)
    {
        DecryptHeader(pHeader, 0);
        return;
    }

    Key[0] = PrevPartHash[0];
    Key[1] = PrevPartHash[1];
    Key[2] = PrevPartHash[2];
    Key[3] = PrevPartHash[3];
    aes_encrypt_key128(&PrevPartHash[4], &aes_ctx);
    Decrypt(&aes_ctx, pHeader, sizeof(*pHeader), Key);
}