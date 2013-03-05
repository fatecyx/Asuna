from ml import *

def main():
    aetexfile = os.path.splitext(sys.argv[1])[0] + '.aetex'
    aetex = open(aetexfile, 'rb').read()

    MetaSize = struct.unpack('<L', aetex[0x28:0x2C])[0]
    HeaderSize, SrcDataSize = struct.unpack('<LL', aetex[MetaSize:MetaSize + 8])

    Magic = aetex[HeaderSize: HeaderSize + 3]
    if Magic != b'DDS':
        print('%s not dds' % aetexfile)
        return

    Header = bytearray(aetex[0:HeaderSize])
    Tail = aetex[HeaderSize + SrcDataSize:]

    dds = open(sys.argv[1], 'rb').read()

    Header[MetaSize + 4:MetaSize + 8] = struct.pack('<L', os.path.getsize(sys.argv[1]))
    data = Header + dds + Tail

    open(aetexfile + '.new', 'wb').write(data)


InvokeSafe(main)
