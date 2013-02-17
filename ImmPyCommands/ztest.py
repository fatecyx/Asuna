#encoding=utf-8

import pefile
import debugger
import os, sys, struct
from immlib2 import *
from libhook import *
from wintypes2 import *

imm = Debugger2()

def ulong(x):
    return x & 0xFFFFFFFF

class DumpIAT(LogBpHook):
    def __init__(self, getaddr, writeaddr):
        LogBpHook.__init__(self)
        self.dllbase = imm.getModule('09sa.dll').baseaddress
        self.api = 0
        self.getaddr = getaddr
        self.writeaddr = writeaddr
        self.logfile = open('e:/desktop/iatlog.txt', 'wb')

        self.logfile.write(''.encode('U16'))

        self.add2('get api', getaddr)
        self.add2('write iat', writeaddr)

        self.lastmodule = None
        self.lastmoduleexport = None

    def GetRoutineByAddress(self, address):
        try:
            mod = imm.getModuleByAddress(address)
            rva = address - mod.baseaddress

            if not self.lastmodule or mod.baseaddress != self.lastmodule.baseaddress or mod.getPath() != self.lastmodule.getPath():
                imm.log('new module: %s' % mod.getPath())
                pe = pefile.PE(mod.getPath())
                exports = pe.parse_export_directory(mod.getEdatatable() - mod.baseaddress, mod.getEdatasize())
                self.lastmodule = mod
                self.lastmoduleexport = exports

            for func in self.lastmoduleexport.symbols:
                if not func.name or func.address != rva:
                    continue

                func.address = address
                func.module = mod
                return func
        except:
            pass

        return None

    def run(self, regs):
        eip = regs['EIP']
        if eip == self.getaddr:
            self.api = regs['EAX']
            self.unhook2()
        elif eip == self.writeaddr and self.api != 0:
            api = self.api
            self.api = 0
            func = self.GetRoutineByAddress(api)
            if not func:
                return

            iat = ulong(regs['EAX'] - self.dllbase)
            const = ulong(api - regs['EDX'])

            modname = func.module.getName()
            str = 'iat = %08X, cnt = %08X, dll = %s, api = %s' % (iat, const, modname, func.name)
            self.logfile.write((str + '\r\n').encode('UTF-16LE'))
            self.logfile.flush()
            imm.log(str)

#logfile = open('e:/desktop/fucklog.txt', 'wb')
addrlist = {}

def IndexOf(list, value):
    try:
        return list.index(value)
    except:
        return -1

class exitproc(ExitProcessHook):
    def __init__(self):
        ExitProcessHook.__init__(self)

    def run(self, regs):
        imm.log('exit')
        logfile = open('e:/desktop/fucklog.txt', 'wb')
        for addr, ret in addrlist.iteritems():
            addr = ulong(addr)
            ret = ulong(ret)

            mod = imm.getModuleByAddress(ret)
            if mod:
                module = 'VA = %08X, RVA = %08X, Name = %s' % (ret, ret - mod.baseaddress, mod.getPath())
                txt = '%08X @ %s' % (addr, module)
            else:
                txt = '%08X @ %08X' % (addr, ret)
            logfile.write(txt + '\r\n')

pak = None

def DecryptBuffer(buf, keybuf):
    index = 0
    for i in range(len(buf)):
        buf[i] = buf[i] ^ keybuf[index]
        index = (index + 1) & 0xF

def fuckfiles():
    base = 0x12FE80
    base = 0x18FE78
    filelist = imm.readLong(base + 0x28)
    filecount = imm.readLong(base + 0x2C)

    output = r'E:\Desktop\yx\Hopeless Masquerade\fuckxxx'

    filelist = filelist - 0x28
    for index in range(filecount):
        filelist = filelist + 0x28
        buf = imm.readMemory(filelist, 0x28)
        key, pakindex, hash, unk, offset, size = struct.unpack('<IIIIII', buf[:0x18])
        deckey = buf[0x18:]

        imm.log('unpacking %d' % index)

        pak.seek(offset)
        buf = pak.read(size)
        #DecryptBuffer(buf, deckey)

        index = 0
        fs = open('%s\\%08X' % (output, hash), 'wb')
        for ch in buf:
            byte = (ord(ch) ^ ord(deckey[index])) & 0xFF
            index = (index + 1) & 0xF
            fs.write(struct.pack('<B', byte))

        fs.close()

class ExportHooks(LogBpHook):
    def __init__(self):
        LogBpHook.__init__(self)
        engine = imm.getModule('Engine.dll')
        self.add2('load file', engine.baseaddress + 0xD1BA1)

    def run(self, regs):
        addr = regs['EAX']
        size = imm.readLong(regs['ESP'] + 4)
        if addr == 0 or size != 0x10:
            return

        imm.log('p = %08X, len = %08X' % (addr, size))

def main(args):
    ExportHooks()
    return ''

    global pak
    pak = open(r"E:\Desktop\yx\Hopeless Masquerade\th135.pak", 'rb')
    try:
        fuckfiles()
    except Exception as e:
        imm.log(e)

    debugger.pyresetall()
    return ''

    imm.clearHardbreakpoints()
    imm.deleteBreakpoint(0, -1)

    mod = imm.getModule('09sa.dll')

    # 开始解压代码
    codebase = mod.baseaddress + 0x1000
    imm.setHardwareBreakpoint(codebase, HB_WRITE)
    imm.run()
    imm.deleteHbIndex(0)

    # 解压完成
    imm.setHardwareBreakpoint(imm.getAddress('kernel32.LocalAlloc'), HB_ONESHOT)
    imm.run()
    imm.deleteHbIndex(0)

    oep = mod.baseaddress + 0x165C3
    getaddr = mod.baseaddress + 0x4CCD262
    writeaddr = mod.baseaddress + 0x4D29AD1

    imm.setHardwareBreakpoint(oep, HB_CODE)

    DumpIAT(getaddr, writeaddr)

    imm.erun()

    return ''
