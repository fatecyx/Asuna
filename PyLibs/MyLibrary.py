import os, sys, struct, traceback
from io import *
from pdb import set_trace as bp

def TryInvoke(method, values = None):
    try:
        return method(*values) if values != None else method()
    except Exception as e:
        traceback.print_exception(type(e), e, e.__traceback__)
        input()

    return None

def ReadTextToList(filename):
    fs=open(filename,'rb')
    stm=fs.read()
    if stm[0:2]==b'\xff\xfe':
        stm=stm.decode('U16')
    elif stm[0:3]==b'\xef\xbb\xbf':
        stm=stm.decode('utf-8-sig')
    else:
        stm=stm.decode('936')

    return stm.replace('\r\n','\n').replace('\r','\n').split('\n')