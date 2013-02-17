#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "MyLibraryUser.h"

_MY_C_HEAD_

TAGID
WINAPI
SdbBeginWriteListTag(
    IN  PDB Db,
    IN  TAG Tag
)
{
    return 0;
}

VOID
WINAPI
SdbCloseDatabase(
    IN  PDB pdb
)
{
}

VOID
WINAPI
SdbCloseDatabaseWrite(
    IN  PDB Db
)
{
}

BOOL
WINAPI
SdbCommitIndexes(
    IN  PDB pdb
)
{
    return 0;
}

PDB
WINAPI
SdbCreateDatabase(
    IN  LPCWSTR     pwszPath,
    IN  PATH_TYPE   eType
)
{
    return 0;
}

BOOL
WINAPI
SdbDeclareIndex(
    IN  PDB pdb,
    IN  TAG tWhich,
    IN  TAG tKey,
    IN  DWORD dwEntries,
    IN  BOOL bUniqueKey,
    OUT INDEXID *piiIndex
)
{
    return 0;
}

BOOL
WINAPI
SdbEndWriteListTag(
    IN OUT  PDB pdb,
    IN      TAGID tiList
)
{
    return 0;
}

TAGID
WINAPI
SdbFindFirstDWORDIndexedTag(
    IN  PDB pdb,
    IN  TAG tWhich,
    IN  TAG tKey,
    IN  DWORD dwName,
    OUT FIND_INFO *pFindInfo
)
{
    return 0;
}

TAGID
WINAPI
SdbFindFirstTag(
    IN  PDB pdb,
    IN  TAGID tiParent,
    IN  TAG tTag
)
{
    return 0;
}

TAGID
WINAPI
SdbFindNextTag(
    IN  PDB pdb,
    IN  TAGID tiParent,
    IN  TAGID tiPrev
)
{
    return 0;
}

BOOL
WINAPI
SdbFormatAttribute(
    IN  PATTRINFO pAttrInfo,
    OUT LPWSTR pchBuffer,
    IN  DWORD dwBufferSize
)
{
    return 0;
}

BOOL
WINAPI
SdbFreeFileAttributes(
    IN  PATTRINFO pFileAttributes
)
{
    return 0;
}

VOID
WINAPI
SdbGetAppPatchDir(
    IN  HSDB hSDB OPTIONAL,
    OUT LPWSTR szAppPatchPath,
    IN  ULONG cchSize
)
{
}

PVOID
WINAPI
SdbGetBinaryTagData(
    IN  PDB pdb,
    IN  TAGID tiWhich
)
{
    return 0;
}

BOOL
WINAPI
SdbGetDatabaseID(
    IN  PDB     Db,
    OUT GUID   *Guid
)
{
    return 0;
}

BOOL
WINAPI
SdbGetDatabaseGUID(
    IN  PDB     Db,
    OUT GUID   *Guid
)
{
    return 0;
}

BOOL
WINAPI
SdbGetDatabaseInformation(
    IN  PDB                         Db,
    OUT PSDB_DATABASE_INFORMATION   DatabaseInformation
)
{
    return 0;
}

BOOL
WINAPI
SdbGetFileAttributes(
    IN  LPCWSTR lpwszFileName,
    OUT PATTRINFO *ppAttrInfo,
    OUT LPDWORD lpdwAttrCount
)
{
    return 0;
}

TAGID
WINAPI
SdbGetFirstChild(
    IN  PDB pdb,
    IN  TAGID tiParent
)
{
    return 0;
}

TAGID
WINAPI
SdbGetIndex(
    IN  PDB pdb,
    IN  TAG tWhich,
    IN  TAG tKey,
    OUT LPDWORD lpdwFlags OPTIONAL
)
{
    return 0;
}

BOOL
WINAPI
SdbGetMatchingExe(
    IN  HSDB hSDB OPTIONAL,
    IN  LPCWSTR szPath,
    IN  LPCWSTR szModuleName OPTIONAL,
    IN  LPCWSTR pszEnvironment OPTIONAL,
    IN  DWORD dwFlags,
    OUT PSDBQUERYRESULT pQueryResult
)
{
    return 0;
}

TAGID
WINAPI
SdbGetNextChild(
    IN  PDB pdb,
    IN  TAGID tiParent,
    IN  TAGID tiPrev
)
{
    return 0;
}

LPWSTR
WINAPI
SdbGetStringTagPtr(
    IN  PDB pdb,
    IN  TAGID tiWhich
)
{
    return 0;
}

TAG
WINAPI
SdbGetTagFromTagID(
    IN  PDB pdb,
    IN  TAGID tiWhich
)
{
    return 0;
}

HSDB
WINAPI
SdbInitDatabase(
    IN  ULONG   Flags,
    IN  PCWSTR  DatabasePath
)
{
    return 0;
}

BOOL
WINAPI
SdbIsStandardDatabase(
    IN  GUID GuidDB
)
{
    return 0;
}

ULONGLONG
WINAPI
SdbMakeIndexKeyFromString(
    IN  LPCWSTR pwszKey
)
{
    return 0;
}

PDB
WINAPI
SdbOpenApphelpDetailsDatabase(
    IN OUT  LPCWSTR pwsDetailsDatabasePath
)
{
    return 0;
}

HMODULE
WINAPI
SdbOpenApphelpResourceFile(
    IN  LPCWSTR pwszACResourceFile OPTIONAL
)
{
    return 0;
}

PDB
WINAPI
SdbOpenDatabase(
    IN  LPCWSTR pwszPath,
    IN  PATH_TYPE eType
)
{
    return 0;
}

DWORD
WINAPI
SdbQueryDataExTagID(
    IN      PDB pdb,
    IN      TAGID tiExe,
    IN      LPCWSTR lpszDataName OPTIONAL,
    OUT     LPDWORD lpdwDataType OPTIONAL,
    OUT     LPVOID lpBuffer OPTIONAL,
    IN OUT  LPDWORD lpcbBufferSize OPTIONAL,
    OUT     TAGID *ptiData OPTIONAL
)
{
    return 0;
}

BOOL
WINAPI
SdbReadApphelpDetailsData(
    IN  PDB pdb,
    OUT PAPPHELP_DATA pData
)
{
    return 0;
}

BOOL
WINAPI
SdbReadBinaryTag(
    IN  PDB pdb,
    IN  TAGID tiWhich,
    OUT PBYTE pBuffer,
    IN  DWORD dwBufferSize
)
{
    return 0;
}

DWORD
WINAPI
SdbReadDWORDTag(
    IN  PDB pdb,
    IN  TAGID tiWhich,
    IN  DWORD dwDefault
)
{
    return 0;
}

ULONGLONG
WINAPI
SdbReadQWORDTag(
    IN  PDB pdb,
    IN  TAGID tiWhich,
    IN  ULONGLONG qwDefault
)
{
    return 0;
}

BOOL
WINAPI
SdbReadStringTag(
    IN  PDB pdb,
    IN  TAGID tiWhich,
    OUT LPWSTR pwszBuffer,
    IN  DWORD cchBufferSize
)
{
    return 0;
}

BOOL
WINAPI
SdbRegisterDatabaseEx(
    IN  LPCWSTR pszDatabasePath,
    IN  DWORD dwDatabaseType,
    IN  PULONGLONG pTimeStamp OPTIONAL
)
{
    return 0;
}

VOID
WINAPI
SdbReleaseDatabase(
    IN  HSDB hSDB
)
{
}

VOID
WINAPI
SdbReleaseMatchingExe(
    IN  HSDB hSDB,
    IN  TAGREF trExe
)
{
}

BOOL
WINAPI
SdbStartIndexing(
    IN  PDB pdb,
    IN  INDEXID iiWhich
)
{
    return 0;
}

BOOL
WINAPI
SdbStopIndexing(
    IN  PDB pdb,
    IN  INDEXID iiWhich
)
{
    return 0;
}

BOOL
WINAPI
SdbTagRefToTagID(
    IN  HSDB hSDB,
    IN  TAGREF trWhich,
    OUT PDB *ppdb,
    OUT TAGID *ptiWhich
)
{
    return 0;
}

LPCWSTR
WINAPI
SdbTagToString(
    IN  TAG tag
)
{
    return 0;
}

BOOL
WINAPI
SdbUnregisterDatabase(
    IN  GUID *pguidDB
)
{
    return 0;
}

BOOL
WINAPI
SdbWriteBinaryTag(
    IN  PDB     Db,
    IN  TAG     Tag,
    IN  PVOID   Buffer,
    IN  ULONG   Size
)
{
    return 0;
}

BOOL
WINAPI
SdbWriteBinaryTagFromFile(
    IN  PDB pdb,
    IN  TAG tTag,
    IN  LPCWSTR pwszPath
)
{
    return 0;
}

BOOL
WINAPI
SdbWriteDWORDTag(
    IN  PDB pdb,
    IN  TAG tTag,
    IN  DWORD dwData
)
{
    return 0;
}

BOOL
WINAPI
SdbWriteNULLTag(
    IN  PDB pdb,
    IN  TAG tTag
)
{
    return 0;
}

BOOL
WINAPI
SdbWriteQWORDTag(
    IN  PDB pdb,
    IN  TAG tTag,
    IN  ULONGLONG qwData
)
{
    return 0;
}

BOOL
WINAPI
SdbWriteStringTag(
    IN  PDB pdb,
    IN  TAG tTag,
    IN  LPCWSTR pwszData
)
{
    return 0;
}

BOOL
WINAPI
SdbWriteWORDTag(
    IN  PDB pdb,
    IN  TAG tTag,
    IN  WORD wData
)
{
    return 0;
}

BOOL
WINAPI
ShimFlushCache(
    IN OUT  HWND hwnd,
    IN OUT  HINSTANCE hInstance,
    IN OUT  LPCSTR lpszCmdLine,
    IN      int nCmdShow
)
{
    return 0;
}

TAGID
WINAPI
SdbFindFirstNamedTag(
    IN  PDB     Db,
    IN  TAGID   TagId,
    IN  TAGID   Parent,
    IN  TAG     Tag
)
{
    return 0;
}

_MY_C_TAIL_
