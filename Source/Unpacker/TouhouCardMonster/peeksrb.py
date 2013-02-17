#encoding=utf-8

#中

import os, sys, re, struct, traceback
from ctypes import windll

if len(sys.argv) < 2:
    sys.exit(0)

txtpat = re.compile(b'\\\x2A...\x06', re.DOTALL)
txtpat = re.compile(b'\x45.\x00\\\x2A.\x00\x06', re.DOTALL)

def HashString(str):
    hash = 0
    for ch in str:
        ch = ord(ch)
        if ch in range(ord('A'), ord('Z') + 1):
            ch |= 0x20

        hash = hash * 0x1003F + ch

        hash &= 0xFFFFFFFF

    return hash

charfilters = \
[
    ('・・・', '……'),
    ('・', '·'),
    ('．', '.'),
]

textfilters = \
[
    'img\\'
]

def PeekText(ps2):
    infile = ps2
    outfile = os.path.splitext(infile)[0] + '.txt'
    binfile = os.path.splitext(infile)[0] + '.xml'

    ps = open(infile, 'rb').read()
    offset = 0

    bytessize = struct.unpack('<H', ps[0xA:0xC])[0]
    ps = ps[0x12 + bytessize:]

    offset += 0x12 + bytessize
    print('step 1 %08X' % offset)

    offsetsize = struct.unpack('<H', ps[:2])[0]
    ps = ps[2 + offsetsize * 4:]

    offset += 2 + offsetsize * 4
    print('step 2 %08X' % offset)

    unknownsize = struct.unpack('<I', ps[:4])[0]
    ps = ps[4 + unknownsize:]

    offset += 4 + unknownsize
    print('step 3 %08X' % offset)
    codepage = '932'
    texts = []

    size = len(ps)
    offset = 0

    while offset < size:
        tmp = ps[offset:]
        mr = txtpat.search(tmp)
        if not mr:
            break

        beg = mr.start()
        end = mr.end()
        offset = end + offset

        tmp = tmp[end:]
        txt = tmp[0:tmp.find(b'\x00')].decode(codepage)

        if txt == '' or any(txt.find(ext) != -1 for ext in ['.ogg', '.png']):
            continue

        isansi = True
        for ch in txt:
            if ord(ch) > 0x80:
                isansi = False
                break

        if isansi:
            continue

        ispath = False
        for sub in textfilters:
            if txt.lower().find(sub) != -1:
                ispath = True
                break

        if ispath:
            continue

        try:
            print('%08X %s' % (offset, txt))
        except:
            pass

        texts.append((offset, txt))

    if len(texts) == 0:
        return

    xml = []

    xml.append('<?xml version="1.0" encoding="utf-8"?>')
    xml.append('<SRB Hash = "%08X">' % HashString(os.path.basename(infile)))

    for text in texts:
        xml.append('    <Text Offset = "%08X">' % text[0])

        text = text[1]
        for ch in charfilters:
            text = text.replace(ch[0], ch[1])

        xml.append('        <jp><![CDATA[%s]]></jp>' % text)
        xml.append('        <sc><![CDATA[%s]]></sc>' % text)
        xml.append('    </Text>')

    xml.append('</SRB>')

    open(binfile, 'wb').write('\r\n'.join(xml).encode('UTF8'))

i = 1
n = len(sys.argv) - 1
while i <= n:
    print('({1:03} / {2:03}) {0}'.format(sys.argv[i], i, n))
    windll.kernel32.SetConsoleTitleW(sys.argv[i])
    
    try:
        PeekText(sys.argv[i])
    except Exception as e:
        traceback.print_exception(type(e), e, e.__traceback__)
        input()

    i = i + 1

