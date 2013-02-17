import pefile, debugger, os, sys, struct, traceback
from immlib import *
from wintypes2 import *
from libhook import *

class Debugger2(Debugger):
    def __init__(self):
        Debugger.__init__(self)

    def Detach2(self):
        return debugger.asuna_detach()

    def sendshortcut(self, where, msg, ctrl, shift, vk):
        return debugger.sendshortcut(int(where), int(msg), int(ctrl), int(shift), int(vk))

    def erun(self):
        return self.sendshortcut(PM_MAIN, WM_KEYDOWN, 0, 1, VK_F9)

    def asuna_log(self, msg, address = 0xbadf00d ,highlight = False, gray = False , focus = 0):
        """
            Adds a single line of ASCII text to the log window.  

            @type  msg: STRING
            @param msg: Message (max size is 255 bytes)

            @type  address: DWORD
            @param address: Address associated with the message

            @type  highlight: BOOLEAN
            @param highlight: Set highlight text

            @type  gray: BOOLEAN
            @param gray: Set gray text
            """
        if gray and not highlight:
            highlight = -1
        return debugger.add_to_list( address, int(highlight), str(msg)[:255], focus)

    def deleteHbIndex(self, index):
        return debugger.DeleteHardBreakpointByIndex(index)

    def deleteHbAddr(self, addr, type = HB_FREE):
        """ 
            if type equal HB_FREE, ignore type
            """
        return debugger.DeleteHardBreakpointByAddr(addr, type)

    def clearHardbreakpoints(self):
        for index in range(0, 4):
            debugger.DeleteHardBreakpointByIndex(index)

    def refreshModules(self):
        debugger.RefreshModules()

    log = asuna_log
    Detach = Detach2
