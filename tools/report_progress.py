#!/usr/bin/env python3

import argparse
import glob
import json
import os

parser = argparse.ArgumentParser(description="Report progress for a specific decompiled file")
parser.add_argument('name', metavar='name', type=str,
                    help='Name of the original file')
parser.add_argument('count', metavar='count', type=int,
                    help='Total function count to calculate the percentage progress')
parser.add_argument('source', metavar='src', type=str,
                    help='file name or directory that contains the source code')
args = parser.parse_args()

def fileLineCount(filePath, funcGetLineScore):
    n = 0
    with open(filePath, "rt") as f:
        for line in f:
            n += funcGetLineScore(line)
    return n


def getSourceFilepaths(path):
    if os.path.isfile(path):
        return [path]
    else:
        return glob.glob(path + '/**/*.c', recursive = True)

def getPercentage(totalFuncCount, remainingFuncCount):
    ratio = 1 - (remainingFuncCount / totalFuncCount)
    return repr(round(ratio * 100, 1)) + "%"

def getColor(totalFuncCount, remainingFuncCount):
    if remainingFuncCount == 0:
        return "brightgreen"
    else:
        return "yellow"

def isIncludeAsm(line): return "INCLUDE_ASM" in line
def isPartiallyDecompiled(line): return "#ifndef NON_MATCHING" in line
def getLineScore(line):
    if isIncludeAsm(line) == True: return 1.0
    if isPartiallyDecompiled(line) == True: return -0.25
    return 0.0

remainingNonmatchingFuncCount = 0
for filePath in getSourceFilepaths(args.source):
    remainingNonmatchingFuncCount += fileLineCount(filePath, getLineScore)

report = {
    "schemaVersion": 1,
    "label": args.name,
    "message": getPercentage(args.count, remainingNonmatchingFuncCount),
    "color": getColor(args.count, remainingNonmatchingFuncCount),
}

print(json.dumps(report))
