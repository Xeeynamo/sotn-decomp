// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspiofilemgr.h>

typedef struct {
    s32 unk0;
    u32 unk4;
    s32 unk8;
    s32 (*unkC)(s32, s32);
    u32 unk10;
} unk_08934A80;

unk_08934A80* func_psp_08934A80(unk_08934A80* arg0, s16 arg1) {
    s32 var_s0;

    if (arg0 != NULL) {
        if (arg0->unk10 < arg0->unk8 && arg0->unkC != NULL) {
            var_s0 = arg0->unk0 + (arg0->unk4 * arg0->unk10);
            while (arg0->unk10 != 0) {
                var_s0 -= arg0->unk4;
                arg0->unkC(var_s0, -1);
                arg0->unk10--;
            }
        }
        if (arg1 > 0) {
            func_psp_08934D20(arg0);
        }
    }
    return arg0;
}

unk_08934A80* func_psp_08934B70(
    unk_08934A80* arg0, s32 arg1, s32 arg2, s32 arg3, void* arg4) {
    arg0->unk0 = arg1;
    arg0->unk4 = arg2;
    arg0->unk8 = arg3;
    arg0->unkC = arg4;
    arg0->unk10 = arg0->unk8;
    return arg0;
}

void func_psp_08934BD8(
    s32 arg0, s32 (*arg1)(s32, s32), void* arg2, s32 arg3, s32 arg4) {
    unk_08934A80 sp1C;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;

    func_psp_08934B70(&sp1C, arg0, arg3, arg4, arg2);
    sp1C.unk10 = 0;
    var_s0 = arg0;
    var_s2 = var_s0;
    while (sp1C.unk10 < arg4) {
        arg1(var_s0, 1);
        sp1C.unk10++;
        var_s0 += arg3;
        var_s1 = var_s0;
    }
    func_psp_08934A80(&sp1C, -1);
}

void func_psp_08934C9C(s32 arg0, s32 (*arg1)(s32, s32), s32 arg2, s32 arg3) {
    s32 var_s0;

    var_s0 = arg0 + (arg2 * arg3);
    while (arg3 != 0) {
        var_s0 -= arg2;
        arg1(var_s0, -1);
        arg3 -= 1;
    }
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/36174", func_psp_08934D20);

extern s32 D_psp_089AD7D8[];

s32** func_psp_08934D78(s32** arg0, s16 arg1) {
    if (arg0 != NULL) {
        *arg0 = D_psp_089AD7D8;
        if (arg1 > 0) {
            func_psp_08934D20(arg0);
        }
    }
    return arg0;
}

s32** func_psp_08934DD4(s32** arg0) {
    *arg0 = D_psp_089AD7D8;
    return arg0;
}

char* const D_psp_0893C06C[] = {
    "std::exception",
    NULL,
};

const char D_psp_0893C074[] = "exception";

const char* func_psp_08934DFC(s32 arg0) { return D_psp_0893C074; }

void* const D_psp_0893C080[] = {
    (void*)D_psp_0893C06C,
    NULL,
    NULL,
};

void* const D_psp_0893C08C[] = {
    (void*)"std::bad_alloc",
    (void*)D_psp_0893C080,
};

INCLUDE_ASM("main_psp/nonmatchings/main_psp/36174", func_psp_08934E14);

extern s32 D_psp_089AD7E8[];

s32** func_psp_08934EB0(s32** arg0) {
    func_psp_08934DD4(arg0);
    *arg0 = D_psp_089AD7E8;
    return arg0;
}

const char D_psp_0893C094[] = "bad_alloc";

const char* func_psp_08934EEC(s32 arg0) { return D_psp_0893C094; }
