import os, sys, struct, traceback

def InvokeSafe(method, values = None):
    try:
        return method(*values) if values != None else method()
    except Exception as e:
        traceback.print_exception(type(e), e, e.__traceback__)
        input()

    return None
