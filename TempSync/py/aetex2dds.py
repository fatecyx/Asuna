from MyLibrary import *

'''

0x10: Width
0x12: Height
0x1C: MipLevels
0x28: MetaSize

MetaSize + 0x00: HeaderSize
MetaSize + 0x04: SrcDataSize
MetaSize + 0x08: SrcData

'''

def main():
    aetex = open(sys.argv[1], 'rb').read()

    MetaSize = struct.unpack('<L', aetex[0x28:0x2C])[0]
    HeaderSize, SrcDataSize = struct.unpack('<LL', aetex[MetaSize:MetaSize + 8])

    Magic = aetex[HeaderSize: HeaderSize + 3]
    if Magic != b'DDS':
        print('%s not dds' % sys.argv[1])
        return

    dds = open(os.path.splitext(sys.argv[1])[0] + '.dds', 'wb').write(aetex[HeaderSize:HeaderSize + SrcDataSize])

InvokeSafe(main)

