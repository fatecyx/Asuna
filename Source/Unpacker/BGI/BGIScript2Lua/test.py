#encoding=gbk

import sys

fs = open(sys.argv[1], 'rb')
chslines = fs.read().decode('U16').replace('\r\n','\n').split('\n')
fs.close()

fs = open(sys.argv[2], 'rb')
jplines = fs.read().decode('U16').replace('\r\n','\n').split('\n')
fs.close()

if len(chslines) != len(jplines):
    print sys.argv[1]
