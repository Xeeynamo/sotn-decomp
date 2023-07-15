try:
    from ghidra.ghidra_builtins import *
except:
    pass

import argparse
import json
import os

from ghidra.program.model.listing import Function
from ghidra.program.model.listing.Function import FunctionUpdateType

from sre_common import FunctionHookItem
from sre_common import VariableHookItem
from sre_common import VariableArrayHookItem
from ghidra.program.model.listing import Parameter
from ghidra.program.model.data import ParameterDefinitionImpl
from ghidra.program.model.listing import ParameterImpl
from ghidra.program.model.symbol import SourceType
from ghidra.program.model.data import GenericCallingConvention
from ghidra.util.data import DataTypeParser
from ghidra.app.util.cparser.C import CParserUtils
from ghidra.util.task import TaskMonitor
def create_mem(regionName, startAddress, endAddress, read, write, execute):
    program = getCurrentProgram()
    monitor = TaskMonitor.DUMMY
    addr = program.getAddressFactory().getDefaultAddressSpace().getAddress(startAddress)
    block = program.getMemory().createInitializedBlock(regionName, addr, endAddress-startAddress, 0x00, monitor, False)
    block.setRead(read)
    block.setWrite(write)
    block.setExecute(execute)

def get_file_bytes(file_path):
    # Read the file contents
    with open(file_path, "rb") as f:
        file_data = f.read()
    return file_data

def set_overlay(file_path, dest_addr):
    file_bytes = get_file_bytes(file_path)
    program = getCurrentProgram()
    dst_addr = program.getAddressFactory().getDefaultAddressSpace().getAddress(dest_addr)
    program.getMemory().setBytes(dst_addr, file_bytes)

start()
create_mem("Work RAM High", 0x06000000, 0x07FFFFFF, True, True, True)

program = getCurrentProgram()

# temp = program.getAddressFactory().getAllAddressSpaces()
# for t in temp:
#     print t

# src_addr = program.getAddressFactory().getDefaultAddressSpace().getAddress(0)
# dst_addr = program.getAddressFactory().getDefaultAddressSpace().getAddress(0x06004080)
# src_bytes = getBytes(src_addr, 312672)
# program.getMemory().setBytes(dst_addr, src_bytes)

# clear out inital import

# ghidra.program.model.mem.MemoryAccessException: ghidra.program.model.mem.MemoryAccessException: Memory change conflicts with instruction at 00000270
# program = getCurrentProgram()
# dst_addr = program.getAddressFactory().getDefaultAddressSpace().getAddress(0)
# program.getMemory().setBytes(dst_addr, bytearray(0x0004c560-1))

# todo un-hardcode these
set_overlay("../../disks/saturn/0.BIN", 0x06004080)
set_overlay("../../disks/saturn/GAME.PRG", 0x06066000)
set_overlay("../../disks/saturn/T_BAT.PRG", 0x060CF000)
set_overlay("../../disks/saturn/STAGE_02.PRG", 0x060DC000)

# game_bytes = get_file_bytes("../../disks/saturn/GAME.PRG")
# dst_addr = program.getAddressFactory().getDefaultAddressSpace().getAddress(0x06066000)
# program.getMemory().setBytes(dst_addr, game_bytes)
end(True)
