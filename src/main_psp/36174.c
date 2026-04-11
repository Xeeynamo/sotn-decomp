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

void* const D_psp_0893C080[] = {
    (void*)D_psp_0893C06C,
    NULL,
    NULL,
};

void* const D_psp_0893C08C[] = {
    (void*)"std::bad_alloc",
    (void*)D_psp_0893C080,
};

const char D_psp_0893C094[] = "bad_alloc";

const char* func_psp_08934DFC(s32 arg0) { return D_psp_0893C074; }

INCLUDE_ASM("main_psp/nonmatchings/main_psp/36174", func_psp_08934E14);

extern s32 D_psp_089AD7E8[];

s32** func_psp_08934EB0(s32** arg0) {
    func_psp_08934DD4(arg0);
    *arg0 = D_psp_089AD7E8;
    return arg0;
}

const char* func_psp_08934EEC(s32 arg0) { return D_psp_0893C094; }

// MSL/Runtime/MWException.cpp

typedef void (*unexpected_handler)();
typedef void (*terminate_handler)();
void terminate();

static void dthandler() { abort(); }

static terminate_handler thandler = dthandler;

static void duhandler() { terminate(); }

static unexpected_handler uhandler = duhandler;

void terminate(void) { thandler(); }

void unexpected(void) { uhandler(); }

#define CONST_CHAR 'C'

s32 __throw_catch_compare(s8* throwtype, s8* catchtype, s32* offset_result) {
    s8* cptr1;
    s8* cptr2;
    s8* var_s3;

    *offset_result = 0;
    if ((cptr2 = catchtype) == 0) {
        return true;
    }
    cptr1 = throwtype;

    if (*cptr2 == 'P') {
        cptr2++;

        if (*cptr2 == CONST_CHAR)
            cptr2++;
        if (*cptr2 == 'V')
            cptr2++;
        if (*cptr2 == 'v') {
            if (*cptr1 == 'P' || *cptr1 == '*') {
                return true;
            }
        }
        cptr2 = catchtype;
    }

    switch (*cptr1) {
    case '*':
    case '!':
        if (*cptr1++ != *cptr2++) {
            return false;
        }
        for (;;) {
            if (*cptr1 == *cptr2++) {
                if (*cptr1++ == '!') {
                    s32 offset;

                    for (offset = 0; *cptr1 != '!';) {
                        offset = (offset * 10) + *cptr1++ - '0';
                    }
                    *offset_result = offset;
                    return true;
                }
            } else {
                while (*cptr1++ != '!')
                    ;
                while (*cptr1++ != '!')
                    ;
                if (*cptr1 == 0) {
                    return false;
                }
                cptr2 = catchtype + 1;
            }
        }
        return false;
    }
    while ((*cptr1 == 'P' || *cptr1 == 'R') && *cptr1 == *cptr2) {
        cptr1++;
        cptr2++;
        if (*cptr2 == CONST_CHAR) {
            if (*cptr1 == CONST_CHAR)
                cptr1++;
            cptr2++;
        }
        if (*cptr1 == CONST_CHAR) {
            return false;
        }
        if (*cptr2 == 'V') {
            if (*cptr1 == 'V')
                cptr1++;
            cptr2++;
        }
        if (*cptr1 == 'V') {
            return false;
        }
    }
    while (*cptr1 == *cptr2) {
        if (*cptr1 == 0) {
            return true;
        }
        cptr1++;
        var_s3 = cptr2;
        cptr2 = var_s3 + 1;
    }
    return false;
}

// end MSL/Runtime/MWException.cpp

INCLUDE_ASM("main_psp/nonmatchings/main_psp/36174", func_psp_08935318);

// MSL/Runtime/CompressedNumbers.cpp

u8* __DecodeSignedNumber(u8* p, s32* pnum) {
    s32 x, y, z, w;

    x = *((s8*)&p[0]);
    if ((x & 1) == 0) {
        *pnum = x >> 1;
        return p + 1;
    }
    y = p[1];
    if ((x & 2) == 0) {
        *pnum = ((x >> 2) << 8) | y;
        return p + 2;
    }
    z = p[2];
    if ((x & 4) == 0) {
        *pnum = ((x >> 3) << 0x10) | (y << 8) | z;
        return p + 3;
    }
    w = p[3];
    *pnum = ((x >> 3) << 0x18) | (y << 0x10) | (z << 8) | w;
    return p + 4;
}

u8* __DecodeUnsignedNumber(u8* p, u32* pnum) {
    u32 x, y, z, w;

    x = p[0];
    if ((x & 1) == 0) {
        *pnum = x >> 1;
        return p + 1;
    }
    y = p[1];
    if ((x & 2) == 0) {
        *pnum = ((x >> 2) << 8) | y;
        return p + 2;
    }
    z = p[2];
    if ((x & 4) == 0) {
        *pnum = (((x >> 3) << 0x10) | (y << 8)) | z;
        return p + 3;
    }
    w = p[3];
    *pnum = ((x >> 3) << 0x18) | (y << 0x10) | (z << 8) | w;
    return p + 4;
}

// end MSL/Runtime/CompressedNumbers.cpp

typedef struct {
    s32 (*unk0)(void);
} unk_08935640;

void func_psp_08935640(unk_08935640* arg0, s32 arg1) {
    s32 (* volatile sp1C)(void);

    while ((u32)arg0 < arg1) {
        sp1C = arg0->unk0;
        sp1C();
        arg0++;
    }
}

void func_psp_089356A0(unk_08935640* arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_psp_08935640(arg0, arg1);
    func_psp_08937228(arg2, arg3);
}

extern s32* D_psp_090DC8E0;

s32 func_psp_089356E8(s32 arg0, s32 arg1, s32* arg2) {
    arg2[0] = (s32)D_psp_090DC8E0;
    arg2[1] = arg1;
    arg2[2] = arg0;
    D_psp_090DC8E0 = arg2;
    return arg0;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/36174", func_psp_0893573C);
