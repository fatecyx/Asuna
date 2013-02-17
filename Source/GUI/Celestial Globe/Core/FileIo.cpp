#include "FileIo.h"
#include "nt_api.h"

CCGFileIo::CCGFileIo()
{
    m_FileHandle = INVALID_HANDLE_VALUE;
}

CGSTATUS CCGFileIo::Close()
{
    NTSTATUS Status;

    if (m_FileHandle == INVALID_HANDLE_VALUE)
        return STATUS_SUCCESS;

    Status = NtClose(m_FileHandle);

    if (!NT_SUCCESS(Status))
        return Status;

    m_FileHandle = INVALID_HANDLE_VALUE;

    return Status;
}

CGSTATUS
CCGFileIo::CreateFileInternal(
    LPCWSTR         FileName,
    FileShareMode   ShareMode,
    FileAccess      Access,
    ULONG           CreationDisposition
)
{
    ULONG               CreateOptions;
    NTSTATUS            Status;
    UNICODE_STRING      NtFilePath;
    OBJECT_ATTRIBUTES   ObjectAttributes;
    IO_STATUS_BLOCK     IoStatusBlock;

    Close();

    Status = RtlDosPathNameToNtPathName_U(FileName, &NtFilePath, NULL, NULL);
    if (!Status)
        return STATUS_INSUFFICIENT_RESOURCES;

    CreateOptions = FILE_SYNCHRONOUS_IO_NONALERT;
    if(Access & GENERIC_ALL)
    {
        CreateOptions |= FILE_OPEN_FOR_BACKUP_INTENT | FILE_OPEN_REMOTE_INSTANCE;
    }
    else
    {
        if(Access & GENERIC_READ)
            CreateOptions |= FILE_OPEN_FOR_BACKUP_INTENT;

        if(Access & GENERIC_WRITE)
            CreateOptions |= FILE_OPEN_REMOTE_INSTANCE;
    }

    InitializeObjectAttributes(&ObjectAttributes, &NtFilePath, 0, NULL, NULL);

    Status = NtCreateFile(
                &m_FileHandle,
                Access | SYNCHRONIZE | FILE_READ_ATTRIBUTES,
                &ObjectAttributes,
                &IoStatusBlock,
                NULL,
                FILE_ATTRIBUTE_NORMAL,
                ShareMode,
                CreationDisposition,
                CreateOptions,
                NULL,
                0
             );

    if (CreationDisposition != FILE_OVERWRITE_IF)
        GetSizeInternal(&m_FileSize);
    else
        m_FileSize.QuadPart = 0;

    m_Position.QuadPart = 0;

    RtlFreeUnicodeString(&NtFilePath);

    return Status;
}

CGSTATUS CCGFileIo::GetSizeInternal(PLARGE_INTEGER pFileSize)
{    
    NTSTATUS Status;
    IO_STATUS_BLOCK IoStatusBlock;
    FILE_STANDARD_INFORMATION FileStandard;

    if (pFileSize == NULL)
        return STATUS_INVALID_PARAMETER;

    pFileSize->QuadPart = 0;

    Status = NtQueryInformationFile(
                m_FileHandle,
                &IoStatusBlock,
                &FileStandard,
                sizeof(FileStandard),
                FileStandardInformation
              );

    if (!NT_SUCCESS(Status))
        return Status;

    pFileSize->QuadPart = FileStandard.EndOfFile.QuadPart;

    return Status;
}

CGSTATUS CCGFileIo::Open(
    LPCWSTR         FileName,
    FileShareMode   ShareMode  /* = FileShareRead */,
    FileAccess      Access     /* = FileGenericRead */
)
{
    return CreateFileInternal(FileName, ShareMode, Access, FILE_OPEN);
}

CGSTATUS
CCGFileIo::
Create(
    LPCWSTR         FileName,
    FileShareMode   ShareMode  /* = FileShareRead */,
    FileAccess      Access     /* = FileGenericWrite */
)
{
    return CreateFileInternal(FileName, ShareMode, Access, FILE_OVERWRITE_IF);
}

CGSTATUS CCGFileIo::GetSize(PLARGE_INTEGER pFileSize)
{
    if (pFileSize == NULL)
        return STATUS_INVALID_PARAMETER;

    pFileSize->QuadPart = m_FileSize.QuadPart;

    return STATUS_SUCCESS;
}

CGSTATUS CCGFileIo::GetPosition(PLARGE_INTEGER pPosition)
{
    if (pPosition == NULL)
        return STATUS_INVALID_PARAMETER;

    pPosition->QuadPart = m_Position.QuadPart;

    return STATUS_SUCCESS;
}

CGSTATUS
CCGFileIo::
Seek(
    LARGE_INTEGER   Offset,
    ULONG           MoveMethod,
    PLARGE_INTEGER  pNewPosition /* = NULL */
)
{
    NTSTATUS                    Status;
    IO_STATUS_BLOCK             IoStatusBlock;
    FILE_POSITION_INFORMATION   FilePosition;
    FILE_STANDARD_INFORMATION   FileStandard;

    switch(MoveMethod)
    {
        case FILE_CURRENT:
            NtQueryInformationFile(m_FileHandle,
                &IoStatusBlock,
                &FilePosition,
                sizeof(FilePosition),
                FilePositionInformation);

            FilePosition.CurrentByteOffset.QuadPart += Offset.QuadPart;
            break;

        case FILE_END:
            NtQueryInformationFile(
                m_FileHandle,
                &IoStatusBlock,
                &FileStandard,
                sizeof(FileStandard),
                FileStandardInformation);

            FilePosition.CurrentByteOffset.QuadPart = FileStandard.EndOfFile.QuadPart + Offset.QuadPart;
            break;

        case FILE_BEGIN:
            FilePosition.CurrentByteOffset.QuadPart = Offset.QuadPart;
            break;

        default:
            return STATUS_INVALID_PARAMETER_2;
    }

    if(FilePosition.CurrentByteOffset.QuadPart < 0)
        return STATUS_INVALID_PARAMETER_1;

    Status = NtSetInformationFile(
                m_FileHandle,
                &IoStatusBlock,
                &FilePosition,
                sizeof(FILE_POSITION_INFORMATION),
                FilePositionInformation);

    if (!NT_SUCCESS(Status))
        return Status;

    m_Position.QuadPart = FilePosition.CurrentByteOffset.QuadPart;
    if (m_Position.QuadPart > m_FileSize.QuadPart)
        m_FileSize.QuadPart = m_Position.QuadPart;

    if (pNewPosition != NULL)
    {
        pNewPosition->QuadPart = FilePosition.CurrentByteOffset.QuadPart;
    }

    return Status;
}

CGSTATUS CCGFileIo::Read(PVOID Buffer, ULONG Size, PLARGE_INTEGER pBytesRead /* = NULL */)
{
    NTSTATUS        Status;
    IO_STATUS_BLOCK IoStatusBlock;

    if (pBytesRead != NULL)
        pBytesRead->QuadPart = 0;

    Status = NtReadFile(
                m_FileHandle,
                NULL,
                NULL,
                NULL,
                &IoStatusBlock,
                Buffer,
                Size,
                NULL,
                NULL
             );

    if (Status == STATUS_PENDING)
    {
        Status = NtWaitForSingleObject(m_FileHandle, FALSE, NULL);
        if (NT_SUCCESS(Status))
            Status = IoStatusBlock.Status;
    }

    if (!NT_SUCCESS(Status))
        return Status;

    m_Position.QuadPart += IoStatusBlock.Information;

    if (pBytesRead != NULL)
        pBytesRead->QuadPart = IoStatusBlock.Information;

    return Status;
}

CGSTATUS CCGFileIo::Write(PVOID Buffer, ULONG Size, PLARGE_INTEGER pBytesWritten /* = NULL */)
{
    NTSTATUS        Status;
    IO_STATUS_BLOCK IoStatusBlock;

    if (pBytesWritten != NULL)
        pBytesWritten->QuadPart = 0;

    Status = NtWriteFile(
                m_FileHandle,
                NULL,
                NULL,
                NULL,
                &IoStatusBlock,
                Buffer,
                Size,
                NULL,
                NULL
             );

    if (Status == STATUS_PENDING)
    {
        Status = NtWaitForSingleObject(m_FileHandle, FALSE, NULL);
        if (NT_SUCCESS(Status))
            Status = IoStatusBlock.Status;
    }

    if (!NT_SUCCESS(Status))
        return Status;

    if (IoStatusBlock.Information + m_Position.QuadPart > m_FileSize.QuadPart)
        m_FileSize.QuadPart = IoStatusBlock.Information + m_Position.QuadPart;

    if (pBytesWritten != NULL)
        pBytesWritten->QuadPart = IoStatusBlock.Information;

    return Status;
}
