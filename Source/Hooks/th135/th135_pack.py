#encoding=utf-8

import os, sys, struct, traceback, zlib

def HashFileNamePartial(name, partial):
    local = ''
    for ch in name:
        if ord(ch) in range(ord('A'), ord('Z') + 1):
            ch = ch.lower()
        local += ch

    name = local
    name = name.replace('/', '\\').encode('932')
    for ch in name:
        if ch >= 0x80:
            ch |= 0xFFFFFF00

        partial = partial * 0x1000193
        partial ^= ch
        partial = partial & 0xFFFFFFFF

    return partial

def CompressTFBM(buf):
    rawoffset = struct.unpack('<I', buf[0xA:0xE])[0]
    width, height, layer, bpp = struct.unpack('<IIHH', buf[0x12:0x12 + 0xC])

    stride = (width * int(bpp / 8) + 3) & ~3
    pitch = width * int(bpp / 8)

    rev = b''
    buf = buf[rawoffset:rawoffset + height * 4 * width]

    offset = height * stride
    while offset >= 0:
        offset = offset - stride
        rev += buf[offset:offset + pitch]

    buf = zlib.compress(rev, 9)
    hdr = struct.pack('<BBIIII', 0, bpp, width, height, width, len(buf))

    return b'TFBM' + hdr + buf

def CompressTFCS(buf):
    uncompsize = len(buf)
    buf = zlib.compress(buf, 9)
    hdr = struct.pack('<BII', 0, len(buf), uncompsize)

    return b'TFCS' + hdr + buf

os.chdir(os.path.dirname(sys.argv[0]))

indir = 'th135cn\\'
outpak = os.path.dirname(indir) + '.pak'

def main():
    files = os.listdir(indir)
    indexsize = len(files) * 0x20 + 0x10
    offset = indexsize

    pakcn = open(outpak, 'wb+')
    pakcn.seek(indexsize)

    CompressRoutine = {}

    CompressRoutine['.png'] = CompressTFBM
    CompressRoutine['.csv'] = CompressTFCS

    entry = b''

    for file in files:
        fullpath = indir + file
        print(fullpath)

        dirhash, filename = file.split('_', 1)
        dirhash = int(dirhash, 16)

        buf = open(fullpath, 'rb').read()

        filename, ext = os.path.splitext(filename)
        if ext.lower() == '.bmp':
            ext = '.png'

        hash = HashFileNamePartial(filename + ext, dirhash)

        ext = ext.lower()
        if ext in CompressRoutine:
            buf = CompressRoutine[ext](buf)


        entry += struct.pack('<IIII', hash, offset, len(buf), 0)
        entry += b'\x00' * 0x10

        offset += len(buf)

        pakcn.write(buf)
        pakcn.flush()

    pakcn.seek(0)
    pakcn.write(struct.pack('<IIII', int(len(entry) / 0x20), 0, 0, 0))
    pakcn.write(entry)

try:
    main()
except Exception as e:
    traceback.print_exception(type(e), e, e.__traceback__)
    input()
