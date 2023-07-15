try:
    from ghidra.ghidra_builtins import *
except:
    pass

import argparse
import os

from ghidra.app.util.cparser.CPP import PreProcessor
from ghidra.app.util.cparser.C import CParser

raw_args = list(str(a) for a in getScriptArgs())
print "Raw arguments: {}".format(raw_args)

parser = argparse.ArgumentParser()
parser.add_argument("rec2_root", help="Root path or rec2")
args = parser.parse_args(raw_args)
print "Arguments: {}".format(args)
rec2_root = args.rec2_root

print("++++++++++++++++++++++++++rec2_root", rec2_root)

dtMgr = currentProgram.getDataTypeManager()

cpp = PreProcessor()
bos = java.io.ByteArrayOutputStream()
# cpp.setArgs([
#     "-D_SRE_",
#     "-DC2_HOOKS_ENABLED",
#     "-I{}".format(os.path.join(rec2_root, "scripts/include-sre")),
#     "-I{}".format(os.path.join(rec2_root, "src/hooks")),
#     "-I{}".format(os.path.join(rec2_root, "src/brender/include")),
#     "-I{}".format(os.path.join(rec2_root, "src/carma2/hooks")),
#     "-I{}".format(os.path.join(rec2_root, "src/carma2/common")),
#     "-I{}".format(os.path.join(rec2_root, "src/carma2/s3/include")),
# ])
cpp.setOutputStream(bos)
cpp.parse(format(os.path.join(rec2_root, "src/saturn/sattypes.h")))
cpp.parse(format(os.path.join(rec2_root, "src/saturn/stage_02.h")))
cpp.parse(format(os.path.join(rec2_root, "src/saturn/zero.h")))

cpp.getDefinitions().populateDefineEquates([dtMgr], dtMgr)

cParser = CParser(dtMgr, True, [dtMgr])
bis = java.io.ByteArrayInputStream(bos.toByteArray())
cParser.parse(bis)
