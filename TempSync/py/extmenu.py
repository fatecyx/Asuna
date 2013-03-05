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
    USHORT  Unknown1[3];
    ULONG   Offset;
    UCHAR   Unknown2[0x34];
    CHAR    Description[0x40];
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
    aemenu = open(sys.argv[1], 'rb').read()

    textoffset, textcount = struct.unpack('<LL', aemenu[0x34:0x3C])
    thunksize = textcount * 0x84
    textthunk = aemenu[textoffset:textoffset + thunksize]
    while len(textthunk) > 0:
        type, dummy, dummy, dummy, offset = struct.unpack('<HHHHL', textthunk[0:0xC])
        textthunk = textthunk[0x84:]

        if type != 4:
            continue

        text = aemenu[offset:]
        text = text[0:text.find(b'\x00')].decode('936')
        print('%08X, %s' % (offset, text))

    input()


InvokeSafe(main)
