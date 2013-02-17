#encoding=utf-8

from ctypes import windll
import os, sys, struct, traceback
import xml.etree.ElementTree as ET

if len(sys.argv) < 2:
    sys.exit(0)

def ConvertXmlToTHCsv(xmlfile):
    tree = ET.parse(xmlfile)
    THCsv = tree.getroot()

    if THCsv.tag != 'THCsv':
        return

    blockcount = len(THCsv)
    rows = []

    for row in THCsv:
        textlist = []

        for text in row:
            textlist.append(text.find('sc').text)

        rows.append(textlist)

    csv = open(os.path.splitext(xmlfile)[0], 'wb')
    csv.write(struct.pack('<I', len(rows)))
    for row in rows:
        csv.write(struct.pack('<I', len(row)))
        for text in row:
            text = text.encode('936')
            csv.write(struct.pack('<I', len(text)))
            csv.write(text)


n = len(sys.argv) - 1
for i in range(1, len(sys.argv)):
    print('({1:03} / {2:03}) {0}'.format(sys.argv[i], i, n))
    windll.kernel32.SetConsoleTitleW(sys.argv[i])

    try:
        ConvertXmlToTHCsv(sys.argv[i])
    except Exception as e:
        traceback.print_exception(type(e), e, e.__traceback__)
        input()
