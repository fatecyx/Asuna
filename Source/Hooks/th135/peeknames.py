#encoding=utf-8

import os, sys, struct

indir = 'th135_pakx\\'

files = os.listdir(indir)

names = {}

def PeekNames(file):
    file = open(file, 'rb').read()
    size = len(file)
    offset = 0
    while offset < size:
        index = file.find(b'data/')
        if index == -1:
            break

        offset = offset + index + 1

        length = struct.unpack('<I', file[index - 4:index])[0]
        name = file[index:index + length]
        name = name.decode('932')
        name = os.path.dirname(name)
        names[name] = 0

        file = file[index + 1:]

for file in files:
    PeekNames(indir + file)

namelist = []
for name in names:
    namelist.append(name)

open('names.txt', 'wb').write('\r\n'.join(namelist).encode('U16'))
