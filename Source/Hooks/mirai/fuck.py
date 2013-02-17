#encoding=utf-8

#中

import os, sys, re, struct

if len(sys.argv) < 2:
    sys.exit(0)

txtpat = re.compile(b'\x01\x02\x20\x01(.{4})\x0F\x02\x30\x04\x01\x02\x20\x01.{4}\x0F\x02\x30\x04\x01\x02\x20\x01(.{4})\x0F\x02\x30\x04\x00\x02\x00\x01', re.DOTALL)
chppat = re.compile(b'\x01\x02\x20\x01(.{4})\x0F\x02\x30\x04\x10\x04\xA6\x00', re.DOTALL)

def PeekText(ps2):
    infile = ps2
    outfile = os.path.splitext(infile)[0] + '.txt'

    ps = open(infile, 'rb').read()

    size = len(ps)
    offset = 0

    magic, headersize, unk1, crc, nthunk, opsize, unk2 = struct.unpack('<IIIIIII', ps[0:0x1C])
    textoffset = headersize + nthunk * 4 + opsize + unk2

    codepage = '932'

    lines = []

    while offset < size:
        mr = txtpat.search(ps[offset:])
        mr2 = chppat.search(ps[offset:])
        if not mr and not mr2:
            break

        if mr2 and (not mr or mr2.start() < mr.start()):
            chapterpos = struct.unpack('<L', mr2.group(1))[0]

            chapter = ps[chapterpos + textoffset:].split(b'\0')[0].decode(codepage)
            lines.append(chapter)

            offset = mr2.end() + offset

            continue

        beg = mr.start() + offset
        end = mr.end() + offset
        offset = end

        chapos = struct.unpack('<L', mr.group(2))[0]
        txtpos = struct.unpack('<L', mr.group(1))[0]

        cha = ps[chapos + textoffset:].split(b'\0')[0].decode(codepage)
        txt = ps[txtpos + textoffset:].split(b'\0')[0].decode(codepage)

        if cha != '':
            txt = txt + '\r\n\r\n' + cha

        lines.append(txt)

        #print(txt)

    fs = open(outfile,'wb')
    fs.write('\r\n\r\n'.join(lines).encode('U16'))
    fs.close()

i = 1
while i < len(sys.argv):
    PeekText(sys.argv[i])
    i = i + 1

