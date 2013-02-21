import os, sys, traceback

if len(sys.argv) < 2:
    print('feed me path of git.exe')
    input()
    sys.exit(0)

def main():
    git = sys.argv[1]
    if os.path.isdir(git):
        git += '\\git.exe'

    hookdll = b'gitfuck.dll\x00'

    git = open(git, 'rb+')

    offset = git.read().find(b'libiconv-2.dll\x00')
    if offset == -1:
        print("can't find libiconv-2.dll from imported dll")
        return

    git.seek(offset)
    git.write(hookdll)
    git.close()

    print('patch %s @ %08X success' % (git.name, offset))

try:
    main()
except Exception as e:
    traceback.print_exception(type(e), e, e.__traceback__)
    input()

input()
