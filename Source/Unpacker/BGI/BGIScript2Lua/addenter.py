#encoding=utf-8

import os
import sys
import pdb


if len(sys.argv)!=3:
    print '''用法：
addenter <-f|-l:ext-name> <files|folder>
-f 对单个或复数文件操作，files使用','分割，文件名中若有空格需要使用引号括起来
-l 对文件夹中的所有扩展名为ext-name的文件操作，folder指定文件夹
'''
    exit(0)

if sys.argv[1]=='-f':
    files=sys.argv[2].split(',')
    for f in files:
        fs=open(f.strip('"'),'rb')
        lines=fs.read().split('\r\n')
        fs.close()
        for i in range(len(lines)):
            lines[i]=lines[i]+'\\r\\n\\'
        if '\\' in f:
            path, sep, fname=f.strip('"').rpartition('\\')
            newf=path+sep+'$_'+fname
        else:
            newf=f.strip('"')
        fs=open(newf,'wb')
        fs.write('\r\n'.join(lines))
        fs.close()
elif sys.argv[1][:3]=='-l:':
    ext=sys.argv[1][3:]
    fdr=sys.argv[2]
    if fdr[-1]=='\\': del fdr[-1]
    files=os.listdir(fdr)
    newfdr='$_'+fdr
    if newfdr not in os.listdir('.'):
        os.mkdir(newfdr)
    for f in files:
        if f.endswith('.'+ext):
            fs=open(fdr+os.sep+f,'rb')
            lines=fs.read().split('\r\n')
            fs.close()
            for i in range(len(lines)):
                lines[i]=lines[i]+'\\r\\n'
            fs=open(newfdr+os.sep+f,'wb')
            fs.write('\r\n'.join(lines))
            fs.close()
