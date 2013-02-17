import os, sys, struct
from ctypes import windll

if len(sys.argv) < 2:
    sys.exit(0)

pyhdr = '''\
#encoding=utf-8
import os, sys
from py2srsdb import *

db = CreateSrsdatabase(r'%s')
'''

class ImageBlock:
    def __init__(self):
        self.name = ''
        self.value = ''

class TextBlock:
    def __init__(self):
        self.name = ''
        self.valuelist = []

class CommentBlock:
    def __init__(self):
        self.name = ''
        self.value = ''

def ReadDword(fs):
    return struct.unpack('<I', fs.read(4))[0]

charfilters = \
[
    ('・・・', '……'),
    ('・', '·'),
    ('．', '.'),
]

def ReadText(fs, len, strip = True):
    txt = fs.read(len).decode('932')
    if strip:
        txt = txt.rstrip('\x00')

    for ch in charfilters:
        txt = txt.replace(ch[0], ch[1])

    return txt

def ParseSrsdb(dbfilename):
    ImageBlockList = []
    TextBlockList = []
    CommentBlockList = []

    db = open(dbfilename, 'rb')

    hdr = ReadText(db, 0xC)
    if hdr != 'SRSDATABASE':
        return 'invalid srs db header'

    # parse image block

    imgcount = ReadDword(db)

    for index in range(imgcount):
        imgblk = ImageBlock()
        namelen = ReadDword(db)
        imgblk.name = ReadText(db, namelen)
        imgblk.value = db.read(ReadDword(db) * 4)
        ImageBlockList.append(imgblk)

    # parse text block

    txtcount = ReadDword(db)
    for index in range(txtcount):
        txtblk = TextBlock()
        namelen = ReadDword(db)
        txtblk.name = ReadText(db, namelen)

        subtxtblockcount = ReadDword(db)
        for idx in range(subtxtblockcount):
            txtlen = ReadDword(db)
            text = ReadText(db, txtlen)
            txtblk.valuelist.append(text)

        TextBlockList.append(txtblk)

    # parse comment block

    cmtcount = ReadDword(db)
    for index in range(cmtcount):
        cmtblk = CommentBlock()

        cmtblk.name = ReadText(db, ReadDword(db))
        #cmtblk.value = ReadText(db, ReadDword(db), False)
        cmtblk.value = db.read(ReadDword(db))

        CommentBlockList.append(cmtblk)

    lines = []

    lines.append(pyhdr % (os.path.basename(dbfilename)))

    for block in ImageBlockList:
        lines.append('db.AppendImageBlock(r\'%s\', %s)' % (block.name, block.value))

    lines.append('')

    for block in TextBlockList:
        lines.append('db.AppendTextBlock(')
        lines.append('    r\'%s\',' % block.name)
        lines.append('    [')
        for value in block.valuelist:
            lines.append('        r\'%s\',' % value)

        lines.append('    ]')
        lines.append(')')
        lines.append('')

    for block in CommentBlockList:
        lines.append('db.AppendCommentBlock(r\'%s\', %s)' % (block.name, block.value))

    lines.append('')
    lines.append('db.Flush()')
    lines.append('')

    if len(lines) != 0:
        outfile = os.path.splitext(dbfilename)[0] + '.py'
        txt = open(outfile, 'wb')
        txt.write('\r\n'.join(lines).encode('UTF8'))
        txt.close()

i = 1
n = len(sys.argv) - 1
while i <= n:
    try:
        windll.kernel32.SetConsoleTitleW(sys.argv[i])
        msg = ParseSrsdb(sys.argv[i])
        msg = msg if msg else 'done'
        print('%s: %s' % (sys.argv[i], msg))
    except Exception as e:
        print(sys.argv[i] + ': ' + str(e))
        input()

    i = i + 1

