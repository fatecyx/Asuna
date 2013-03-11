from ml import *

'''

char magic[0x10];
char name[0x80];
char path[0x80];
ulong filenum;  // max 0x400

struct
{
    char name[0x20];
    byte indexbeg;
    byte;
    byte;
    ulong;

} FileEntry[filenum];

ulong imgnum;

struct
{
    pvoid buf;
    ulong w;
    ulong h;
    boolean haspalette : 1;
    ulong imgsize;  // if == 0, then imgsize = w * h + haspalette ? 0x400 : 0
                    // imgsize == 0 if not compressed

    byte imgbuf[imgsize];

} ImageEntry[imgnum];

'''

def decompress(inbuf):
    offset = 0
    outbuf = bytearray()
    while offset < len(inbuf):
        ch = inbuf[offset]
        offset += 1

        method = ch >> 6
        length = ch & 0x3F

        #print('method %d, length = %8X, inlen = %X, offset = %8X, %8X' % (method, length, len(inbuf), offset - 1, len(outbuf)))

        if length == 0:
            length = inbuf[offset]
            offset += 1
            if length != 0:
                length += 0x3F
            else:
                length = inbuf[offset] | (inbuf[offset + 1] << 8)
                length = (inbuf[offset + 2] << 0x10) + length + 0x13F
                offset += 3

        if method == 0:

            outbuf += b'\x00' * length

        elif method == 1:

            outbuf += inbuf[offset:offset + length]
            offset += length

        elif method == 2:

            outbuf += inbuf[offset:offset + 1] * length
            offset += 1

        elif method == 3:

            back = inbuf[offset]
            offset += 1
            if back == 0:
                back = (inbuf[offset] + 1) << 8
                offset += 1

            #print('back = %08X' % back)

            back = len(outbuf) - back
            for i in range(length):
                outbuf += outbuf[back:back+1]
                back += 1

        else:
            pass

    return outbuf

def readdw(fs):
    return struct.unpack('<L', fs.read(4))[0]

def BuildBmpHeader(width, height, bpp):
    stride = (int(width * bpp / 8) + 3) & ~3
    rawoffset = 0x36 if bpp != 8 else 0x436
    size = stride * height + rawoffset
    header = struct.pack('<HIIIIIIHHIIIIII', 0x4D42, size, 0, rawoffset, 0x28, width, height, 1, bpp, 0, 0, 0, 0, 0, 0)
    return header

def unpack(filename):
    pak = open(filename, 'rb')
    magic = pak.read(7)
    if magic != b'2DKGT2K':
        return

    dirname = os.path.splitext(filename)[0]
    filename = os.path.basename(filename)

    os.system('rd /s/q "' + dirname + '" >NUL 2>NUL')
    os.system('md "' + dirname + '" >NUL 2>NUL')

    pak.seek(0x110, SEEK_SET)

    scenenum = readdw(pak)
    pak.seek(scenenum * 0x27, SEEK_CUR)

    posdatanum = readdw(pak)
    pak.seek(posdatanum * 0x10, SEEK_CUR)

    imgnum = readdw(pak)

    offset = pak.tell()

    for index in range(imgnum):
        buf, w, h, haspalette, compressedsize = struct.unpack('<LLLLL', pak.read(0x14))
        haspalette &= 1
        imgsize = compressedsize if compressedsize != 0 else w * h + 0x400 * haspalette
        pak.seek(imgsize, SEEK_CUR)

    defpalette = pak.read(0x2100)
    pak.seek(offset, SEEK_SET)

    for index in range(imgnum):
        #print('%X' % pak.tell())

        buf, w, h, haspalette, compressedsize = struct.unpack('<LLLLL', pak.read(0x14))
        haspalette &= 1
        imgsize = compressedsize if compressedsize != 0 else w * h + 0x400 * haspalette

        if imgsize == 0:
            continue

        imgbuf = pak.read(imgsize)

        if compressedsize != 0:
            imgbuf = decompress(imgbuf)

        header = BuildBmpHeader(w, h, 8)
        bmp = header
        if not haspalette:
            bmp += defpalette[0:0x400]
        else:
            bmp += imgbuf[0:0x400]
            imgbuf = imgbuf[0x400:]

        stride = (w + 3) & ~3
        pad = b'\x00' * (stride - w)
        offset = h * w
        for i in range(h):
            offset -= w
            bmp += imgbuf[offset:offset + w] + pad

        open('%s\\%s%d.bmp' % (dirname, filename, index), 'wb').write(bmp)

def main():
    for pak in sys.argv[1:]:
        unpack(pak)

TryInvoke(main)
