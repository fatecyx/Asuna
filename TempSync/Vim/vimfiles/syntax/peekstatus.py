from ml import *

def main():
    lines = ReadTextToList(r"E:\WinDDK\7600.16385.1\inc\api\ntstatus.h")

    status = ''

    for line in lines:
        if line.find('#define STATUS_') == -1:
            continue

        status += line.split(' ')[1] + ' '

    open('kw.h', 'w').write('syn keyword cppNumber ' + status.rstrip())

InvokeSafe(main)

