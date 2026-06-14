// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef MSL_RUNTIME_EXCEPTIONHANDLER_H
#define MSL_RUNTIME_EXCEPTIONHANDLER_H

#include <common.h>

#include "ExceptionTables.h"
#include "MWException.h"

typedef struct TargetContext {
    /* 0x00 */ unsigned long GPR[0x20];
    /* 0x84 */ unsigned long unk84;
    /* 0x88 */ unsigned long unk88;
    /* 0x8C */ s32 unk8C;
    /* 0x90 */ s32 unk90;
    /* 0x94 */ bool unk94;
    /* 0x98 */ unsigned long unk98;
    /* 0x9C */ unsigned long FPR[0x20];
} TargetContext; // size: 0x118

typedef struct ThrowContext {
    /* 0x00 */ s8* throwtype;
    /* 0x04 */ void* location;
    /* 0x08 */ void* dtor;
    /* 0x0C */ CatchInfo* catchinfo;
    /* 0x10 */ char* returnaddr;
    /* 0x14 */ char* SP;
    /* 0x18 */ char* FP;
    /* 0x1C */ char* throwSP;
    /* 0x20 */ TargetContext target;
} ThrowContext; // size: 0x138

typedef struct TargetExceptionInfo {
    float dummy;
} TargetExceptionInfo;

typedef struct ExceptionInfo {
    char* current_function;
    char* exception_record;
    char* action_pointer;
    ExceptionTableIndex* exception_table_start;
    ExceptionTableIndex* exception_table_end;
    TargetExceptionInfo target;
} ExceptionInfo;

#define __FunctionPointer(info, context, fp) (fp)
#define __AdjustReturnAddress(info, context, retaddr)                          \
    ((char*)((u32)(retaddr) & 0xFFFFFFFE))
#define __LocalVariable(context, offset) ((context)->FP + (offset))
#define __Register(context, regno) ((context)->target.GPR[regno])

extern char* __SkipUnwindInfo(char* p);

extern char* __PopStackFrame(ThrowContext* context, ExceptionInfo* info);

#endif // MSL_RUNTIME_EXCEPTIONHANDLER_H
