#encoding=utf-8
import os, sys, struct, traceback
import xml.etree.ElementTree as ET

BLOCK_NAME      = 0
BLOCK_VALUE     = 1

def WriteDword(fs, value):
    fs.write(struct.pack('<I', value))

def WriteText(fs, text, cp = '932'):
    text = text.encode(cp)
    WriteDword(fs, len(text))
    fs.write(text)

def WriteBytesArray(fs, bin):
    WriteDword(fs, len(bin))
    fs.write(bin)

def WriteDwordArray(fs, bin):
    WriteDword(fs, int(len(bin) / 4))
    fs.write(bin)

class Srsdatabase:
    def __init__(self):
        self.fs = None
        self.ImageBlockList = []
        self.TextBlockList = []
        self.CommentBlockList = []

        self.TranslatedBlock = {}
        self.TranslatedBlock['msg'] = {}
        self.TranslatedBlock['name'] = {}

    def Create(self, filename):
        self.fs = open(filename, 'wb')
        fs = self.fs
        fs.write('SRSDATABASE\x00'.encode('932'))

        xml = filename[:filename.find('srsdb')] + 'xml'

        try:
            tree = ET.parse(xml)
        except Exception as e:
            traceback.print_exception(type(e), e, e.__traceback__)
            input()
            return

        srsdb = tree.getroot()
        for text in srsdb:
            index = int(text.attrib['Index'])
            sc = text.find('sc').text
            if text.attrib['Type'] == 'Name':
                self.TranslatedBlock['name'][index] = sc
            elif text.attrib['Type'] == 'Message':
                self.TranslatedBlock['msg'][index] = sc

    def AppendImageBlock(self, blockname, blockvalue):
        block = [BLOCK_NAME, BLOCK_VALUE]
        block[BLOCK_NAME] = blockname
        block[BLOCK_VALUE] = blockvalue

        self.ImageBlockList.append(block)

    def AppendTextBlock(self, blockname, valuelist):
        if blockname in self.TranslatedBlock:
            for index, text in self.TranslatedBlock[blockname].items():
                if valuelist[index] == text:
                    continue
                valuelist[index] = text

        block = [BLOCK_NAME, BLOCK_VALUE]
        block[BLOCK_NAME] = blockname
        block[BLOCK_VALUE] = valuelist

        self.TextBlockList.append(block)

    def AppendCommentBlock(self, blockname, blockvalue):
        block = [BLOCK_NAME, BLOCK_VALUE]
        block[BLOCK_NAME] = blockname
        block[BLOCK_VALUE] = blockvalue

        self.CommentBlockList.append(block)

    def Flush(self):
        fs = self.fs

        WriteDword(fs, len(self.ImageBlockList))
        for block in self.ImageBlockList:
            WriteText(fs, block[BLOCK_NAME] + '\x00')
            WriteDwordArray(fs, block[BLOCK_VALUE])

        WriteDword(fs, len(self.TextBlockList))
        for block in self.TextBlockList:
            WriteText(fs, block[BLOCK_NAME] + '\x00')
            WriteDword(fs, len(block[BLOCK_VALUE]))
            for value in block[BLOCK_VALUE]:
                WriteText(fs, value + '\x00', '936')

        WriteDword(fs, len(self.CommentBlockList))
        for block in self.CommentBlockList:
            WriteText(fs, block[BLOCK_NAME] + '\x00')
            WriteBytesArray(fs, block[BLOCK_VALUE])

def CreateSrsdatabase(filename):
    db = Srsdatabase()
    db.Create(filename)
    return db
