#encoding=utf-8

#中

import os, sys, re, struct
from ctypes import windll

if len(sys.argv) < 2:
    sys.exit(0)

def PeekText(ps2):
    infile = ps2
    outfile = infile.replace('.bin.txt', '.txt')

    jpsep = '    '

    lines = open(infile, 'rb').read().decode('U16').replace('\r\n', '\n').replace('\r', '\n').split('\n')

    fs = open(outfile, 'wb')
    fs.write(''.encode('U16'))

    lines.pop(0)

    i = 0

    while i < len(lines):
        if lines[i] == '':
            break

        text = lines[i].split(jpsep, 1)[1]
        if text[0] == '「' and i + 1 < len(lines):
            char = lines[i + 1].split(jpsep, 1)[1]
            text = '{0}　{1}'.format(char, text)
            i = i + 1

        fs.write('{0}\r\n{0}\r\n\r\n'.format(text).encode('UTF-16LE'))
        i = i + 1

    fs.close()

i = 1
n = len(sys.argv) - 1
while i <= n:
    print('({1:03} / {2:03}) {0}'.format(sys.argv[i], i, n))
    windll.kernel32.SetConsoleTitleW(sys.argv[i])
    PeekText(sys.argv[i])
    i = i + 1

