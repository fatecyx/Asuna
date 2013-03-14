#encoding=utf-8

import os, sys, re, struct, traceback
from ctypes import windll
import xml.etree.ElementTree as ET

if len(sys.argv) < 2:
    sys.exit(0)

def PeekText(textdata, srbxml):
    srb = ET.parse(srbxml).getroot()

    if srb.tag != 'SRB':
        return

    textlist = []
    for text in srb:
        offset = int(text.attrib['Offset'], 16)
        jp = text.find('jp').text
        sc = text.find('sc').text

        #if jp == sc: continue

        textlist.append([offset, sc])

    if len(textlist) != 0:
        textdata[int(srb.attrib['Hash'], 16)] = textlist

textdata = {}
i = 1
n = len(sys.argv) - 1
while i <= n:
    print('({1:03} / {2:03}) {0}'.format(sys.argv[i], i, n))
    windll.kernel32.SetConsoleTitleW(sys.argv[i])

    try:
        PeekText(textdata, sys.argv[i])
    except Exception as e:
        traceback.print_exception(type(e), e, e.__traceback__)
        input()

    i = i + 1

if len(textdata) == 0:
    sys.exit(0)

buf = bytearray()
for hash, textlist in textdata.items():
    buf += struct.pack('<II', len(textlist), hash)
    for text in textlist:
        offset = text[0]
        text = text[1].encode('936') + b'\x00'
        length = len(text)
        buf += struct.pack('<II', offset, length - 1)
        buf += text
        buf += b'\x00' * (((length + 3) & ~3) - length)

open(os.path.dirname(sys.argv[1]) + '\\' + 'tcm.bin', 'wb').write(buf)
