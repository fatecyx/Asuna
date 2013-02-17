#encoding=gbk

import sys
import re

def extText(fname,txtname):
    index = 1
    fs=open(fname,'rb')
    lines=fs.read().decode('U16').replace('\r\n','\n').split('\n')
    fs.close()
    newl=[]
    for li in lines:
        if li.startswith('Say(') or li.startswith('AutoSay('):
            arg=li.split('"')
            if len(arg)==5:
                newl.append(ur'○' + str(index).rjust(4, '0') + '/' + arg[1] + ur'○' + ' ' + arg[3])
                newl.append(ur'●' + str(index).rjust(4, '0') + '/' + arg[1] + ur'●' + ' ' + arg[3] + '\r\n')
        elif li.startswith('Text(') or li.startswith('AutoText('):
            arg=li.split('"')
            if len(arg)==3:
#                if re.match(ur'^(?:喀啷喀啷|喀|咚|嘎|喀嚓|扑哧|咣)', arg[1]):
#                    continue
                newl.append(ur'○' + str(index).rjust(4, '0') + ur'○ ' + arg[1])
                newl.append(ur'●' + str(index).rjust(4, '0') + ur'● ' + arg[1] + '\r\n')
        elif li.startswith('Select('):
            arg=li.split('"')
            if len(arg)==3:
                newl.append(ur'○' + str(index).rjust(4, '0') + ur'/.Select○ ' + arg[1])
                newl.append(ur'●' + str(index).rjust(4, '0') + ur'/.Select● ' + arg[1] + '\r\n')
        else:
            continue
        index = index + 1
    if index == 1:
        return
    fs=open(txtname,'wb')
    fs.write('\r\n'.join(newl).encode('U16'))
    fs.close()

def packText(fname,txtname):
    fs=open(fname,'rb+')
    lines=fs.read().replace('\r\n','\n').split('\n')
    fst=open(txtname,'rb')
    linest=fst.read().replace('\r\n','\n').split('\n')
    tcount=0
    for i in range(len(lines)):
        if lines[i].startswith('Say('):
            arg=lines[i].split('"')
            if len(arg)==5:
                if tcount+1>=len(linest):
                    print txtname+" 行数不足"
                    sys.exit()
                lines[i]=arg[0]+linest[tcount]+arg[2]+linest[tcount+1]+arg[4]
                tcount+=2
        elif lines[i].startswith('Text('):
            arg=lines[i].split('"')
            if len(arg)==3:
                if tcount>=linest:
                    print txtname+" 行数不足"
                    sys.exit()
                lines[i]=arg[0]+linest[tcount]+arg[2]
                tcount+=1
    if tcount!=len(linest):
        print txtname+' 行数过多'
        sys.exit()
    fs.seek(0)
    fs.write('\r\n'.join(lines))

def thehelp():
    print '''
用法：
exttxt [-e|-p] [ori-filename] [new-filename]
-e 提取文本
-p 封装文本，会覆盖ori-filename的文件
'''
    sys.exit()

#main
if len(sys.argv)!=4:
    thehelp()
if sys.argv[1]=='-e':
    extText(sys.argv[2],sys.argv[3])
elif sys.argv[1]=='-f':
    packText(sys.argv[2],sys.argv[3])
else:
    thehelp()
