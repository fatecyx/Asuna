#encoding=utf-8

import os, sys, struct, traceback
from ctypes import windll
import xml.etree.ElementTree as ET

if len(sys.argv) < 2:
    sys.exit(0)

def ConvertTHCSToXml(csvfile):
    csv = open(csvfile, 'rb')

    textblock = []

    rows = struct.unpack('<I', csv.read(4))[0]
    for i in range(rows):
        columes = struct.unpack('<I', csv.read(4))[0]
        textlist = []
        for j in range(columes):
            length = struct.unpack('<I', csv.read(4))[0]
            text = csv.read(length).decode('932')
            textlist.append(text)

        textblock.append(textlist)

    xml = []
    xml.append('<?xml version="1.0" encoding="utf-8"?>')
    xml.append('<THCsv>')

    for block in textblock:
        xml.append('    <Row>')
        for text in block:
            xml.append('        <Text>')
            xml.append('            <jp><![CDATA[%s]]></jp>' % text)
            xml.append('            <sc><![CDATA[%s]]></sc>' % text)
            xml.append('        </Text>')

        xml.append('    </Row>')

    xml.append('</THCsv>')

    open(csvfile + '.xml', 'wb').write('\r\n'.join(xml).encode('UTF8'))

n = len(sys.argv) - 1

for i in range(1, len(sys.argv)):
    print('({1:03} / {2:03}) {0}'.format(sys.argv[i], i, n))
    windll.kernel32.SetConsoleTitleW(sys.argv[i])

    try:
        ConvertTHCSToXml(sys.argv[i])
    except Exception as e:
        traceback.print_exception(type(e), e, e.__traceback__)
        input()

