import debugger

# reload all py module, and delete all py hooks added by Hook.add2()
def main(args):
    debugger.pyresetall()
    return 'reset py'
