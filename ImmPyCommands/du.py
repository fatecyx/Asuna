import os, sys, immlib, libhook, pefile
from immlib import *

get_api = 0x14CCD262
write_iat = 0x14D29AD1

def GetRoutineByAddress(address):
    try:
        mod = imm.getModuleByAddress(address)
        rva = address - mod.baseaddress

        pe = pefile.PE(mod.getPath())
        exports = pe.parse_export_directory(mod.getEdatatable() - mod.baseaddress, mod.getEdatasize())

        for func in exports.symbols:
            if not func.name or func.address != rva:
                continue

            func.address = address
            func.module = mod
            return func
    except:
        pass

    return None

class PrintLog(LogBpHook):
    def __init__(self, api_init):
        LogBpHook.__init__(self)
        self.imm = Debugger()
        self.api = api_init

    def run(self, regs):
        eip = regs['EIP']
        self.imm.log('ooxx %X' % self.api)
        self.api = self.api + 1
        if eip == get_api:
            self.api = regs['EAX']
            func = GetRoutineByAddress(self.api)
            if func:
                self.imm.log('%s @ %s: %08X' % (func.name, func.module.getName(), func.address))
            return

        if eip != write_iat or self.api == 0:
            return

        func = GetRoutineByAddress(self.api)
        if not func:
            return

        self.mod = imm.getModuleByAddress(self.api)
        rva = regs['EAX'] - 0x10000000
        offset = regs['EDX'] - self.api
        str = '%s: rva = %08X, offset = %08X, mod = %s' % (func.name, rva, offset, mod.getName())
        self.imm.log(str)

def main(args):
    imm = Debugger()

    global get_api
    get_api = imm.getRegs()['EIP']

    addr = get_api
    imm.writeMemory(addr, imm.assemble('jmp %X' % get_api, addr))
    fuck = PrintLog(0x8888888)

    fuck.add('fuck dll', get_api)
    #fuck.add('fuck dll', write_iat)

    return ''
