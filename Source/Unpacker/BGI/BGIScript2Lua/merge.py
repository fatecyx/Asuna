#encoding=gbk

import sys
import re

def GetText(text):
    sep = text[0]
    if text[5] == '/':
        type = text[6:]
        text = type.split(sep)
        type = ur'/' + text[0]
        text = text[1][1:]
    else:
        type = ''
        text = text[7:]

    return [type, text]

def GetHead(Text):
    if Text[0] == '':
        head = ['Text(', 'AutoText(']
    elif Text[0] == '/.Select':
        head = ['Select(']
    else:
        head = ['Say(', 'AutoSay(']
    return head


def MakeText(text, head):
    if text[0] == '' or text[0] == '/.Select':
        text = head + '"' + text[1] + '")'
    else:
        text = head + '"' + text[0][1:] + '", "' + text[1] + '")'
    return text

def merge2():
    if len(sys.argv) < 3:
        sys.exit()

    fs = open(sys.argv[2], 'rb')
    trans = fs.read().decode('U16').replace('\r\n','\n').split('\n')
    fs.close()

    fs = open(sys.argv[1], 'rb+')
    script = fs.read().decode('U16').replace('\r\n','\n').split('\n')
    fs.close()

    ScriptLines = len(script)
    TransLines  = len(trans)

    transline   = 0
    scrline     = 0

    Text = GetText(trans[transline])
    head = GetHead(Text)
    Chs  = GetText(trans[transline + 1])

    for i in range(0, ScriptLines, 1):
        line = script[i]
        h = line.split('"')[0]
        if h not in head:
            continue

        Text = MakeText(Text, h)
        if Text != line:
            print '\n' + sys.argv[1] + ': mismatch at line ' + str(i + 1) + '\n'
            print 'text in script(' + str(i + 1) + '): ' + line
            print 'text in trans(' + str(transline + 1) + '): ' + Text
            sys.exit()

        script[i] = MakeText(GetText(trans[transline + 1]), h)
    #    print script[i]
        transline = transline + 3
        if transline >= TransLines:
            break

        Text = trans[transline]
        if Text == '':
            if transline + 1 == TransLines:
                break
            print 'corrupt trans file at line ' + str(transline + 1)
            sys.exit()

        Text = GetText(Text)
        head = GetHead(Text)
        Chs  = GetText(trans[transline + 1])

    fs = open(sys.argv[1], 'wb')
    fs.write('\r\n'.join(script).encode('U16'))
    fs.close()

    sys.exit()

merge2()
sys.exit()
if len(sys.argv) < 4:
    sys.exit()

fs = open(sys.argv[1], 'rb')
jp = fs.read().decode('U16').replace('\r\n','\n').split('\n')
fs.close()

fs = open(sys.argv[2], 'rb')
cn = fs.read().decode('U16').replace('\r\n','\n').split('\n')
fs.close()

textline = len(jp)

if textline != len(cn):
    sys.exit()

new = []
index = 1

for i in range(0, textline, 3):
    text = GetText(jp[i])
    t1 = ur'○' + str(index).rjust(4, '0') + text[0] + ur'○ ' + text[1] + '\r\n'
    text = GetText(cn[i + 1])
    t2 = ur'●' + str(index).rjust(4, '0') + text[0] + ur'● ' + text[1] + '\r\n'

    if t1 == t2:
        print sys.argv[1] + '??'

    new.append(t1)
    new.append(t2)
    new.append('\r\n')
    index = index + 1

fs = open(sys.argv[3], 'wb')
fs.write(''.join(new).encode('U16'))
fs.close()

