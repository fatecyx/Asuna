#encoding=utf-8

import os, sys, struct, shutil, zlib, io

indir = 'fuckxxx\\'
output = 'th135_pak\\'
codepage = '932'

files = os.listdir(indir)
shutil.rmtree(output, ignore_errors = True)
os.mkdir(output)

def ulong(x):
    return int(x) & 0xFFFFFFFF

def HashName(name):
    name = name.replace('/', '\\')
    name = name.encode(codepage)
    hash = 0x811C9DC5
    for ch in name:
        if ch >= 0x80:
            ch = ch | 0xFFFFFF00
        hash = hash * 0x1000193
        hash = ulong(hash ^ ch)

    return ulong(hash)

def BuildBmpHeader(width, height, bpp):
    stride = (int(width * bpp / 8) + 3) & ~3
    size = stride * height + 0x36
    header = struct.pack('<HIIIIIIHHIIIIII', 0x4D42, size, 0, 0x36, 0x28, width, height, 1, bpp, 0, 0, 0, 0, 0, 0)
    return header

names = open('xxxxxxxxxxx.txt', 'rb').read().decode(codepage).replace('\r\n', '\n').replace('\r', '\n').split('\n')

index = 0

for name in names:
    if len(name) == 0:
        continue

    hash = hex(HashName(name)).upper()[2:]

    src = indir + hash
    dst = output + name

    print('%08X %s %s' % (index, src, dst))
    index = index + 1

    os.makedirs(os.path.dirname(dst), exist_ok = True)

    try:
        os.remove(dst)
    except:
        pass

    try:
        shutil.copy(src, dst)
    except:
        continue

#input()
