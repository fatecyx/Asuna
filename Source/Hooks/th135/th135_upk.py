#encoding=utf-8

import os, sys, struct, zlib, io

output = 'th135_pakx\\'

os.chdir(os.path.dirname(sys.argv[0]))

def unpackTFCS(buf):
    buf = buf[1:]
    compsize = struct.unpack('<I', buf[:4])[0]
    uncompsize = buf[4:8]

    uncomp = zlib.decompress(buf[8:])
    return uncomp


def BuildBmpHeader(width, height, bpp):
    stride = (int(width * bpp / 8) + 3) & ~3
    size = stride * height + 0x36
    header = struct.pack('<HIIIIIIHHIIIIII', 0x4D42, size, 0, 0x36, 0x28, width, height, 1, bpp, 0, 0, 0, 0, 0, 0)
    return header

def unpackTFBM(buf):
    unknown, bpp, width, height, scanlines, length = struct.unpack('<BBIIII', buf[:0x12])

    unp = zlib.decompress(buf[0x12:])

    hdr = BuildBmpHeader(width, height, bpp)

    pitch = width * int(bpp / 8)
    stride = (width * int(bpp / 8) + 3) & ~3

    offset = height * pitch
    while offset >= 0:
        offset = offset - pitch
        hdr += unp[offset:offset + stride]

    return hdr


def unpackTFPA(buf):
    unknown, compsize = struct.unpack('<BI', buf[:5])
    return zlib.decompress(buf[5:5 + compsize])

def unpackTFWA(buf):
    pass


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


filenames = open('filenames.bin', 'rb').read().decode('932').replace('\r\n', '\n').replace('\r', '\n').split('\n')
dirlist = open('dir.bin', 'rb').read()
fileentry = open('files.bin', 'rb').read()


DIR_FILE_COUNT  = 0
DIR_FILE_LIST   = 1
dirmap = {}

nameindex = 0

while len(dirlist) > 0:
    dirhash, filecount = struct.unpack('<II', dirlist[0:8])
    dirlist = dirlist[0x20:]

    dirmap[dirhash] = (filecount, filenames[nameindex:nameindex + filecount])
    nameindex += filecount

FILE_HASH       = 0
FILE_OFFSET     = 1
FILE_SIZE       = 2
FILE_DEC_KEY    = 3

filemap = {}

while len(fileentry) > 0:
    key, pakindex, hash, crc, offset, size = struct.unpack('<IIIIII', fileentry[0:0x18])
    deckey = fileentry[0x18:0x28]
    filemap[hash] = (hash, offset, size, deckey)

    fileentry = fileentry[0x28:]


pak = open('th135.pak', 'rb')

os.makedirs(output, exist_ok = True)

filters = ['.nut', '.act', '.csv']
#filters = ['.png']

for dirhash, dirinfo in dirmap.items():
    #os.makedirs(output + '%08X' % dirhash, exist_ok = True)

    for file in dirinfo[DIR_FILE_LIST]:
        fullpath = output + '%08X_%s' % (dirhash, file)

        filehash = HashFileNamePartial(file, dirhash)
        #print('%08X @ %08X %s' % (filehash, dirhash, file))
        if not filehash in filemap:
            print("can't find %s in %08X" % (file, dirhash))
            continue

        if not os.path.splitext(fullpath)[1] in filters:
            continue

        fileentry = filemap[filehash]
        deckey = fileentry[FILE_DEC_KEY]

        pak.seek(fileentry[FILE_OFFSET])
        buf = bytearray(pak.read(fileentry[FILE_SIZE]))

        index = 0
        for i in range(len(buf)):
            buf[i] ^= deckey[index]
            index = (index + 1) & 0xF

        unpackFunc = {}
        unpackFunc[b'TFCS'] = unpackTFCS
        unpackFunc[b'TFBM'] = unpackTFBM
        unpackFunc[b'TFPA'] = unpackTFPA

        magic = bytes(buf[:4])

        if magic in unpackFunc:
            buf = unpackFunc[magic](buf[4:])

        open(fullpath, 'wb').write(buf)
        print(fullpath)
