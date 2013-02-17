#encoding=utf-8

#中

import os, sys, re, struct
from ctypes import windll

if len(sys.argv) < 2:
    sys.exit(0)

txtpat = re.compile(b'\x01\x02\x20\x01(.{4})', re.DOTALL)

def PeekText(ps2):
    infile = ps2
    outfile = os.path.splitext(infile)[0] + '.txt'
    binfile = os.path.splitext(infile)[0] + '.bin.txt'

    ps = open(infile, 'rb').read()
    size = len(ps)
    offset = 0

    magic, headersize, unk1, crc, nthunk, opsize, unk2size = struct.unpack('<IIIIIII', ps[0:0x1C])

    if magic != 0x41325350:
        return

    textoffset = headersize + nthunk * 4 + opsize + unk2size
    codepage = '932'
    lines = []

    fs = open(binfile, 'wb')
    fs.write('{0:08X}\r\n'.format(crc).encode('U16'))

    while offset < size:
        mr = txtpat.search(ps[offset:])
        if not mr:
            break

        beg = mr.start() + offset
        end = mr.end() + offset
        offset = end

        txtpos = struct.unpack('<L', mr.group(1))[0]
        txt = ps[txtpos + textoffset:].split(b'\0')[0].decode(codepage)

        if txt == '' or any(txt.find(ext) != -1 for ext in ['.ogg', '.pb3', '.ps2', '.cmv']):
            continue

        fs.write('{0:08X}    {1}\r\n'.format(txtpos, txt).encode('UTF-16LE'))

        lines.append(txt)

    fs.close()

i = 1
n = len(sys.argv) - 1
while i <= n:
    print('({1:03} / {2:03}) {0}'.format(sys.argv[i], i, n))
    windll.kernel32.SetConsoleTitleW(sys.argv[i])
    PeekText(sys.argv[i])
    i = i + 1

