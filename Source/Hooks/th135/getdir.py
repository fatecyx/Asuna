import os, sys

names = open('xxxxxxxxxxx.txt', 'rb').read().decode('932').replace('\r\n', '\n').replace('\r', '\n').split('\n')

dirs = {}

for name in names:
    dir = os.path.dirname(name)
    if dir in dirs:
        continue

    dirs[dir] = 0

for x in dirs:
    print(x)

print(len(dirs))

input()