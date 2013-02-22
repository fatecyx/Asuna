import os, sys, traceback, ctypes

if len(sys.argv) < 2:
    print('feed me directory of git.exe or path of libiconv-2.dll')
    input()
    sys.exit(0)

def main():
    libiconv = sys.argv[1]
    if os.path.isdir(libiconv):
        libiconv += '\\libiconv-2.dll'

    hookdll = b'gitfuck.dll\x00'

    libiconv = open(libiconv, 'rb+')
    fs = libiconv.read()
    offset = fs.find(hookdll)
    if offset != -1:
        print('%s already patched @ %08X' % (libiconv.name, offset))
        return

    offset = fs.find(b'msvcrt.dll\x00')
    if offset == -1:
        print("can't find msvcrt.dll from IAT")
        return

    libiconv.seek(offset)
    libiconv.write(hookdll)
    print('patch %s @ %08X' % (libiconv.name, offset))

    libiconv.close()

try:
    main()
except Exception as e:
    traceback.print_exception(type(e), e, e.__traceback__)

input()
