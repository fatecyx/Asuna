#ifndef _NPACK_H_6d321938_9b8d_4a73_a0a3_26414d003255_
#define _NPACK_H_6d321938_9b8d_4a73_a0a3_26414d003255_

#include "CompactPacker.h"
#include "cxdec.h"

#define FRETURN(_Status) if (!NT_SUCCESS(_Status)) return _Status;
#define FBREAK(_Status) if (!NT_SUCCESS(_Status)) {Status = _Status; break;}

typedef struct
{
    ULONG FileSize;
    ULONG Index;
    ULONG Hash[8];

} NP_FIND_FILE_INFO;

class NPackReader : public UnpackerImpl<NPackReader>
{
protected:
    NtFileDisk  m_File;
    Cxdec       m_cxdec;
    PVOID       m_Key;
    PCOMPACT_PACK_ENTRY *m_Entry;

public:
    NPackReader()
    {
        m_Entry = NULL;
        m_Key   = NULL;
    }

    UPK_STATUS ReleaseAll()
    {
        m_cxdec.Release();

        if (m_Entry != NULL)
        {
            FreeMemory(m_Entry);
            m_Entry = NULL;
        }

        if (m_Key != NULL)
        {
            Nt_FreeMemory(NtCurrentProcess(), m_Key);
            m_Key = NULL;
        }

        return __super::ReleaseAll();
    }

    VOID GenerateKey(PVOID Buffer)
    {
        ULONG   Size;
        PULONG  Seed;

        Size = 0x290;
        Seed = (PULONG)PtrAdd(Nt_FindLdrModuleByHandle(&__ImageBase)->EntryPoint, 0x20);

        sha256(Seed, Size, Buffer);
        for (ULONG Count = 0x1000 / 0x20 - 1; Count; --Count)
        {
            sha256(Buffer, 0x20, PtrAdd(Buffer, 0x20));
            Buffer = PtrAdd(Buffer, 0x20);
        }
    }

    UPK_STATUS Open(PCWSTR FileName)
    {
        PVOID               IndexBuffer;
        NTSTATUS            Status;
        COMPACT_PACK_HEADER Header;

        ReleaseAll();

        Status = m_File.Open(FileName);
        if (!NT_SUCCESS(Status))
            return Status;

        CXDEC_OPTION Option;

        ULONG Body1[6] = { 3, 2, 1, 4, 5, 0 };
        ULONG Body2[8] = { 7, 6, 5, 1, 0, 3, 4, 2 };
        ULONG Tail[3]  = { 1, 0, 2 };

        Status = Nt_AllocateMemory(NtCurrentProcess(), &m_Key, 0x1000);
        FRETURN(Status);

        GenerateKey(m_Key);

        Option.DecryptBlock     = (PULONG)m_Key;
        Option.Body1IndexMap    = Body1;
        Option.Body2IndexMap    = Body2;
        Option.TailIndexMap     = Tail;
        Option.Const[0]         = TAG4('Rias');
        Option.Const[1]         = TAG4('Grmy');
        Option.FunctionCount    = 0x100;
        Option.FunctionSize     = 0x100;
        Option.LoopCount        = 6;

        m_cxdec.SetOption(&Option);
        m_cxdec.Initialize();

        Status = m_File.Read(&Header, sizeof(Header));
        FRETURN(Status);

        ULONG Key[4] = { TAG4('Rias'), TAG4('Grem'), TAG3('ory'), Key[0] * Key[2] };

        m_cxdec.Decrypt2(0, &Header, sizeof(Header), Key);
        if (Header.Magic ^= COMPACT_PACK_MAGIC)
            return STATUS_UNSUCCESSFUL;

        Status = m_File.Seek(Header.EntryOffset, FILE_BEGIN);
        FRETURN(Status);

        IndexBuffer = AllocateMemory(Header.EntrySize.LowPart);
        if (IndexBuffer == NULL)
            return STATUS_INSUFFICIENT_RESOURCES;

        Status = m_File.Read(IndexBuffer, Header.EntrySize.LowPart);

        if (NT_SUCCESS(Status))
            Status = InitIndex(&Header, IndexBuffer);

        FreeMemory(IndexBuffer);

        return Status;
    }

    UPK_STATUS FindFile(PSTR FileName, NP_FIND_FILE_INFO *FindInfo)
    {
        ULONG Length, Hash[4];
        PCOMPACT_PACK_ENTRY *Entry;

        Length = StrLengthA(FileName);
        sha256(FileName, Length, FindInfo->Hash);

        Hash[0] = FindInfo->Hash[0] ^ FindInfo->Hash[4];
        Hash[1] = FindInfo->Hash[1] ^ FindInfo->Hash[5];
        Hash[2] = FindInfo->Hash[2] ^ FindInfo->Hash[6];
        Hash[3] = FindInfo->Hash[3] ^ FindInfo->Hash[7];

        Entry = FindFileEntry(m_Entry, m_Index.FileCount.LowPart, Hash);
        if (Entry == NULL)
            return STATUS_OBJECT_NAME_NOT_FOUND;

        FindInfo->FileSize  = (*Entry)->FileSize.LowPart;
        FindInfo->Index     = Entry - m_Entry;

        return STATUS_SUCCESS;
    }

    UPK_STATUS GetFileData(PVOID Buffer, NP_FIND_FILE_INFO *FindInfo)
    {
        NTSTATUS                        Status;
        PCOMPACT_PACK_ENTRY             Entry;
        PCOMPACT_PACK_COMPRESSED_HEADER Compressed;

        Entry = m_Entry[FindInfo->Index];
        Status = m_File.Seek(Entry->Offset, FILE_BEGIN);
        FRETURN(Status);

        Compressed = NULL;

        LOOP_ONCE
        {
            if (FLAG_ON(Entry->Flags, UNPACKER_ENTRY_COMPRESSED))
            {
                Compressed = (PCOMPACT_PACK_COMPRESSED_HEADER)AllocateMemory(Entry->CompressedSize.LowPart);
                if (Compressed == NULL)
                    FBREAK(STATUS_INSUFFICIENT_RESOURCES);

                Status = m_File.Read(Compressed, Entry->CompressedSize.LowPart);
                FBREAK(Status);

                if (FLAG_ON(Entry->Flags, UNPACKER_ENTRY_ENCRYPTED))
                    m_cxdec.Decrypt2(0, Compressed, Entry->CompressedSize.LowPart, &FindInfo->Hash[4]);

                UCL_NRV2E_Decompress(Compressed + 1, Compressed->CompressedSize.LowPart, Buffer, &FindInfo->FileSize);

                break;
            }

            Status = m_File.Read(Buffer, Entry->FileSize.LowPart);
            FBREAK(Status);

            if (FLAG_ON(Entry->Flags, UNPACKER_ENTRY_ENCRYPTED))
            {
                m_cxdec.Decrypt2(0, Buffer, FindInfo->FileSize, &FindInfo->Hash[4]);
            }
        }

        FreeMemory(Compressed);

        return Status;
    }

protected:
    static INT CDECL SortEntry(PCOMPACT_PACK_ENTRY *Entry1, PCOMPACT_PACK_ENTRY *Entry2)
    {
        ULONG  Count;
        PULONG Hash1, Hash2;

        Hash1 = (*Entry1)->FileNameHash;
        Hash2 = (*Entry2)->FileNameHash;
        Count = countof((*Entry1)->FileNameHash);

        do
        {
            if (*Hash1 < *Hash2)
                return -1;
            else if (*Hash1 > *Hash2)
                return 1;

            ++Hash1;
            ++Hash2;

        } while (--Count);

        return 0;
    }

    UPK_STATUS InitIndex(PCOMPACT_PACK_HEADER Header, PVOID IndexBuffer)
    {
        ULONG                           Size;
        PCOMPACT_PACK_ENTRY             Entry, *EntryTable;
        PCOMPACT_PACK_COMPRESSED_HEADER Compressed;

        if (FLAG_ON(Header->Flags, UNPACKER_ENTRY_ENCRYPTED))
        {
            ULONG Key[4] =
            {
                _rotl(Header->Reserve, 11),
                _rotl(Key[0], 11),
                _rotl(Key[1], 11),
                _rotl(Key[2], 11),
            };

            m_cxdec.Decrypt2(0, IndexBuffer, Header->EntrySize.LowPart, Key);
        }

        Compressed = (PCOMPACT_PACK_COMPRESSED_HEADER)IndexBuffer;

        m_Index.Entry = (UNPACKER_FILE_ENTRY_BASE *)AllocateMemory(Compressed->OriginalSize.LowPart);
        if (m_Index.Entry == NULL)
            return STATUS_INSUFFICIENT_RESOURCES;

        UCL_NRV2E_Decompress(Compressed + 1, Compressed->CompressedSize.LowPart, m_Index.Entry, &Size);

        m_Index.EntrySize = sizeof(*Entry) - sizeof(Entry->Buffer) - sizeof(Entry->FileName);
        m_Index.EntrySize = ROUND_UP(m_Index.EntrySize, 16);

        m_Index.FileCount.QuadPart = Size / m_Index.EntrySize;

        m_Entry = (PCOMPACT_PACK_ENTRY *)AllocateMemory(m_Index.FileCount.LowPart * sizeof(*m_Entry));
        if (m_Entry == NULL)
            return STATUS_INSUFFICIENT_RESOURCES;

        Entry = (PCOMPACT_PACK_ENTRY)m_Index.Entry;
        EntryTable = m_Entry;
        for (ULONG64 FileCount = m_Index.FileCount.QuadPart; FileCount; --FileCount)
        {
            *EntryTable++ = Entry;
            Entry = PtrAdd(Entry, Entry->EntrySize);
        }

        qsort(m_Entry, m_Index.FileCount.LowPart, sizeof(EntryTable), (int (__cdecl *)(const void *,const void *))SortEntry);

        return STATUS_SUCCESS;
    }

#pragma push_macro("COMPARE_HASH")

#define COMPARE_HASH(_Index) \
            if (Entry->FileNameHash[_Index] < Hash[_Index]) \
            { \
                Left = Middle + 1; \
                continue; \
            } \
            else if (Entry->FileNameHash[_Index] > Hash[_Index]) \
            { \
                Right = Middle - 1; \
                continue; \
            }

    PCOMPACT_PACK_ENTRY*
    FindFileEntry(
        PCOMPACT_PACK_ENTRY *EntryBase,
        ULONG                EntryCount,
        PULONG               Hash
    )
    {
        ULONG Left, Right, Middle;
        PCOMPACT_PACK_ENTRY Entry;

        Left  = 0;
        Right = EntryCount - 1;

        if (Hash[0] < EntryBase[Left]->FileNameHash[0] ||
            Hash[0] > EntryBase[Right]->FileNameHash[0])
        {
            return NULL;
        }

        while (Left < Right)
        {
            Middle = (Right - Left) / 2 + Left;
            Entry = EntryBase[Middle];

            COMPARE_HASH(0);
            COMPARE_HASH(1);
            COMPARE_HASH(2);
            COMPARE_HASH(3);

            return &EntryBase[Middle];
        }

        Entry = EntryBase[Left];

        return (Entry->FileNameHash[0] == Hash[0] &&
                Entry->FileNameHash[1] == Hash[1] &&
                Entry->FileNameHash[2] == Hash[2] &&
                Entry->FileNameHash[3] == Hash[3]
               ) ? &EntryBase[Left] : NULL;
    }

#pragma pop_macro("COMPARE_HASH")
};

#endif // _NPACK_H_6d321938_9b8d_4a73_a0a3_26414d003255_
