// SPDX-License-Identifier: AGPL-3.0-or-later
#include "CompressedNumbers.h"
#include "ExceptionHandler.h"

INCLUDE_ASM("main_psp/nonmatchings/main_psp/MSL/Runtime/ExceptionHandlerTS", __PopStackFrame);

void __SetupFrameInfo(ThrowContext* context, ExceptionInfo* info) {
    char* p = info->exception_record;
    bool var_s1;

    var_s1 = *((s8*)p) & 0x40;
    context->target.unk94 = *((s8*)p) & 0x20;
    context->target.unk90 = *((s8*)p) & 0x10;
    context->target.unk8C = *((s8*)p) & 0xF;

    p = __DecodeUnsignedNumber(p + 1, &context->target.unk84);
    p = __DecodeUnsignedNumber(p, &context->target.unk88);

    if (context->target.unk94) {
        context->FP = (char*)context->target.GPR[30];
    } else {
        context->FP = context->SP;
    }
    if (var_s1) {
        p = __DecodeUnsignedNumber(p, &context->target.unk98);
        return;
    }
    context->target.unk98 = 0;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/MSL/Runtime/ExceptionHandlerTS", func_psp_08937228);

typedef struct unkStruct {
    ExceptionTableIndex* exception_table_start;
    ExceptionTableIndex* exception_table_end;
} unkStruct;

extern unkStruct D_psp_090DC8E4[];

int __FindExceptionTable(ExceptionInfo* info, char* retaddr) {
    s32 i;

    for (i = 0; i < 0x10; i++) {
        if (D_psp_090DC8E4[i].exception_table_start == NULL) {
            continue;
        }
        if (D_psp_090DC8E4[i].exception_table_start->function_address >
            retaddr) {
            continue;
        }
        if (&D_psp_090DC8E4[i].exception_table_end->function_address
                 [D_psp_090DC8E4[i].exception_table_end->function_size & ~1] >
            retaddr) {
            info->exception_table_start =
                D_psp_090DC8E4[i].exception_table_start;
            info->exception_table_end = D_psp_090DC8E4[i].exception_table_end;
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/MSL/Runtime/ExceptionHandlerTS", __SkipUnwindInfo);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/MSL/Runtime/ExceptionHandlerTS", __TransferControl);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/MSL/Runtime/ExceptionHandlerTS", __throw);
