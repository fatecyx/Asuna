from ml import *

'''

typedef struct
{
    ULONG   Unknown1;
    ULONG   Version;      // 0x28
    ULONG   DataSize;
    CHAR    Description[0x20];
    ULONG   RequiredFileOffset;
    ULONG   RequiredFileCount;
    ULONG   TextOffset;
    ULONG   TextCount;
    ULONG   OpOffset;
    ULONG   OpCount;
    ULONG   FontOffset;
    ULONG   FontCount;

} AEMENU_HEADER;

typedef struct  // 0x7C
{
    ULONG   Unknown1;
    ULONG   Unknown3;
    ULONG   ChunkSize;          // always 0x7C
    CHAR    FileName[0x40];

} AEMENU_REQUIRED_FILE;

typedef enum
{
    AeMenuText_Type1    = 1,
    AeMenuText_Type2    = 2,
    AeMenuText_Type3    = 3,
    AeMenuText_Text     = 4,
    AeMenuText_Type5    = 5,
    AeMenuText_Type6    = 6,
    AeMenuText_Type7    = 7,
};

typedef struct  // 0x84
{
    USHORT  Type;               // 0x04: Text
    USHORT  Unknown1;
    ULONG   Unknown2[0xF];
    CHAR    Text[0x40];
    ULONG   Unknown2;

} AEMENU_TEXT;

typedef struct  // 0x30
{
    CHAR    Description[0x20];
    ULONG   Unknown[4];

} AEMENU_OP;

typedef struct  // 0x20
{
    CHAR Font[0x20];

} AEMENU_FONT;

'''

def main():

InvokeSafe(main)