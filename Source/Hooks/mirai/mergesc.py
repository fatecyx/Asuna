#encoding=utf-8

#中

import os, sys, re, struct, hashlib
from ctypes import windll

if len(sys.argv) < 2:
    sys.exit(0)

def Sha256(buf):
    n = hashlib.sha256(open('ntoskrnl.exe', 'rb').read()).hexdigest().upper()
    h1, h2, h3, h4, h5, h6, h7, h8 = int(n[0:8], 16), int(n[0x8:0x10], 16), int(n[0x10:0x18], 16), int(n[0x18:0x20], 16), int(n[0x20:0x28], 16), int(n[0x28:0x30], 16), int(n[0x30:0x38], 16), int(n[0x38:0x40], 16)
    return [h1, h2, h3, h4, h5, h6, h7, h8]

def OpenText(file):
    return open(file, 'rb').read().decode('U16').replace('\r\n', '\n').replace('\r', '\n').replace('\n\n', '\n').split('\n')

def MergeText(ps2):
    infile = ps2
    outfile = infile.replace('.txt', '.sc.txt')
    binfile = infile.replace('.txt', '.psbin')

    jpsep = '    '

    jptext = OpenText(infile.replace('.txt', '.bin.txt'))
    lines = OpenText(infile)

    sctext = []
    crc = int(jptext.pop(0), 16)

    i = 1
    jpi = 0
    while i < len(lines):
        if lines[i] == '':
            break

        jp = jptext[jpi].split(jpsep, 1)
        sc = lines[i].split('　「', 1)
        if len(sc) == 2:
            sc = lines[i].split('　', 1)
            char = sc[0]
            text = sc[1]
            offset = int(jp[0], 16)

            sctext.append((offset, text))

            jpi = jpi + 1
            jp = jptext[jpi].split(jpsep, 1)
            offset = int(jp[0], 16)
            sctext.append((offset, char))
        else:
            text = sc[0]
            offset = int(jp[0], 16)
            sctext.append((offset, text))

        i = i + 2
        jpi = jpi + 1

    if len(sctext) == 0:
        return

    bin = open(binfile, 'wb')
    bin.write(struct.pack('<II', len(sctext), crc))
    for offset, text in sctext:
        text = text.replace('♪', '⊙').replace('・', '·').encode('936')
        bin.write(struct.pack('<II', offset, len(text)))
        bin.write(text)

    bin.close()

    '''
    fs = open(outfile, 'wb')
    fs.write('{0:08X}\r\n'.format(crc).encode('U16'))
    for offset, text in sctext:
        fs.write('{0:08X}    {1}\r\n'.format(offset, text).encode('UTF-16LE'))
    fs.close()
    #'''

i = 1
n = len(sys.argv) - 1
while i <= n:
    print('({1:03} / {2:03}) {0}'.format(sys.argv[i], i, n))
    windll.kernel32.SetConsoleTitleW(sys.argv[i])
    MergeText(sys.argv[i])
    i = i + 1

