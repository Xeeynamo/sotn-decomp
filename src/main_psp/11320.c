// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include <game_psp.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspgu.h>
#include <pspgecmd.h>

typedef struct {
    s32* unk0;
    s32* unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
} Unk08B1F140;

// BSS
static s32 D_psp_08B1F1D0[19][0x20];
static u8 D_psp_08B1F1C4[0xC] UNUSED;
static s32 D_psp_08B1F1C0;
static s32 D_psp_08B1F1BC; // texture pattern format
static s32 D_psp_08B1F1B8;
static s32 D_psp_08B1F1B4;
static s32 D_psp_08B1F1B0;
static s32 D_psp_08B1F1AC;
static s32 D_psp_08B1F1A8;
static s32* D_psp_08B1F1A4;
static s32 D_psp_08B1F1A0;
static s32* D_psp_08B1F19C;
static s32 D_psp_08B1F198;
static s32* D_psp_08B1F194;
static Unk08B1F140 D_psp_08B1F140[3];
static s32 D_psp_08A1F140[2][0x20000];
u8 D_psp_089B7140[2][0x34000];
static s32 D_psp_089B6940[2][0x100];
static u8 disp_list[0x400];

extern s32 D_psp_08B41FC0;

void func_psp_08910088(void);
u32 func_psp_08910098(s32, s32);
void func_psp_0891034C(void);
void func_psp_08910360(Unk08B1F140*);
void func_psp_0891036C(s32);
void func_psp_08910410(void);
void func_psp_08910978(u8, u8, u8, u8);

void func_psp_0890FC2C(void) {
    func_psp_08910088();
    D_psp_08B1F140[0].unk0 = NULL;
    D_psp_08B1F140[0].unk4 = NULL;
    D_psp_08B1F140[1].unk0 = NULL;
    D_psp_08B1F140[1].unk4 = NULL;
    D_psp_08B1F140[2].unk0 = NULL;
    D_psp_08B1F140[2].unk4 = NULL;
    D_psp_08B1F198 = -1;
    D_psp_08A1F140[D_psp_08B41FC0][0] = GE_SET_RET();
    D_psp_08B1F194 = D_psp_089B6940[D_psp_08B41FC0];
    func_psp_08910978(0xFF, 0x40, 0x40, 0x40);
}

void func_psp_0890FCD0(void) {
    sceGuStart(GU_IMMEDIATE, disp_list, sizeof(disp_list));
    sceGuDrawBuffer(GU_PSM_5551, GU_VRAM_BP_0, GU_VRAM_WIDTH);
    sceGuDispBuffer(GU_SCR_WIDTH, GU_SCR_HEIGHT, GU_VRAM_BP_1, GU_VRAM_WIDTH);
    sceGuDepthBuffer(GU_VRAM_BP_2, GU_VRAM_WIDTH);
    sceGuOffset(GU_SCR_OFFSETX, GU_SCR_OFFSETY);
    sceGuViewport(0x800, 0x800, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    sceGuScissor(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuDepthRange(1, 0xFFFF);
    sceGuColorFunc(GU_ALWAYS, 0, 0xFFFFFF);
    sceGuAlphaFunc(GU_GREATER, 1, 0xFF);
    sceGuStencilOp(GU_KEEP, GU_KEEP, GU_REPLACE);
    sceGuStencilFunc(GU_ALWAYS, 0x80, 0x80);
    sceGuDepthFunc(GU_LEQUAL);
    sceGuDepthMask(GU_TRUE);
    sceGuDisable(GU_BLEND);
    sceGuBlendFunc(GU_ADD, GU_FIX, GU_FIX, 0x00000000, 0xFFFFFFFF);
    sceGuBlendFunc(
        GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0x00000000, 0x00000000);
    sceGuBlendFunc(
        GU_REVERSE_SUBTRACT, GU_SRC_ALPHA, GU_FIX, 0x00000000, 0xFFFFFFFF);
    sceGuBlendFunc(GU_ADD, GU_SRC_COLOR, GU_FIX, 0x00000000, 0x00000000);
    sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_FIX, 0x00000000, 0xFFFFFFFF);
    sceGuEnable(GU_BLEND);
    sceGuDisable(GU_COLOR_LOGIC_OP);
    sceGuShadeModel(GU_FLAT);
    sceGuClearColor(0x00000000);
    sceGuClearStencil(0);
    sceGuClearDepth(0xFFFF);
    sceGuClear(GU_CLEAR_ALL);
    sceGuTexOffset(0.0f, 0.0f);
    sceGuFinish();
}

void func_psp_0890FE98(void) {
    sceGuStart(GU_IMMEDIATE, disp_list, sizeof(disp_list));
    sceGuCallList(D_psp_089B6940[D_psp_08B41FC0]);
    sceGuCallList(D_psp_08A1F140[D_psp_08B41FC0]);
    sceGuCallList(D_psp_089B7140[D_psp_08B41FC0]);
    sceGuFinish();
}

s32 func_psp_0890FF2C(void) {
    s32 ret;

    ret = sceGuFinish();
    *D_psp_08B1F194++ = GE_SET_RET();
    func_psp_08910098(1, 1);
    return ret;
}

void func_psp_0890FF84(void) {
    sceGuStart(
        GU_CALL, D_psp_089B7140[D_psp_08B41FC0], sizeof(D_psp_089B7140[0]));
    sceGuClearColor(0xFFFFFFFF);
    sceGuDisable(GU_COLOR_TEST);
    sceGuDisable(GU_ALPHA_TEST);
    sceGuDisable(GU_STENCIL_TEST);
    sceGuDisable(GU_COLOR_LOGIC_OP);
    sceGuTexWrap(GU_CLAMP, GU_CLAMP);
    sceGuTexFilter(GU_NEAREST, GU_NEAREST);
    sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
    sceGuShadeModel(GU_FLAT);
    sceGuDisable(GU_LIGHTING);
    sceGuDisable(GU_FOG);
    sceGuDisable(GU_CULL_FACE);
    sceGuDisable(GU_CLIP_PLANES);
}

void func_psp_08910044(void) {
    func_psp_0890FCD0();
    D_psp_08B41FC0 = 0;
    D_psp_08B1F1A0 = 0;
    D_psp_08B1F19C = 0;
    D_psp_08B1F198 = -1;
    func_psp_0891034C();
}

void func_psp_08910088(void) { D_psp_08B1F1B0 = -1; }

u32 func_psp_08910098(s32 arg0, s32 arg1) {
    Unk08B1F140* temp_s2;
    s32 var_s1;
    u32 var_s0;

    var_s1 = -1;
    if (D_psp_08B1F198 != arg0) {
        temp_s2 = &D_psp_08B1F140[arg0];
        if (temp_s2->unk0 != NULL) {
            if (D_psp_08B1F198 != -1) {
                var_s1 = D_psp_08B1F198;
                func_psp_08910410();
            }
            func_psp_0891036C(arg0);
            if (arg1 != 0) {
                *D_psp_08B1F19C++ = GE_SET_RET();
                *D_psp_08B1F19C++ = GE_SET_NOP();
            }
            var_s0 = ((u32)D_psp_08B1F19C - (u32)D_psp_08B1F1A4) / 4;
            D_psp_08B1F1AC = var_s0;
            func_psp_08910360(temp_s2);
            if (var_s1 != -1) {
                func_psp_0891036C(var_s1);
            }
        }
    } else {
        D_psp_08B1F198 = -1;
        if (arg1 != 0) {
            *D_psp_08B1F19C++ = GE_SET_RET();
            *D_psp_08B1F19C++ = GE_SET_NOP();
        }
        var_s0 = ((u32)D_psp_08B1F19C - (u32)D_psp_08B1F1A4) / 4;
        D_psp_08B1F1AC = var_s0;
    }
    return var_s0;
}

void func_psp_08910220(s32* arg0, s32 arg1, s32 arg2) {
    if (arg2 != D_psp_08B1F198 && D_psp_08B1F198 != -1) {
        func_psp_08910410();
    }
    D_psp_08B1F1A4 = arg0;
    D_psp_08B1F1A8 = arg1;
    D_psp_08B1F19C = arg0;
    D_psp_08B1F198 = arg2;
}

void func_psp_08910298(s32 arg0) {
    s32 var_a1;
    s32* var_a0;

    switch (arg0) {
    case 0:
        var_a1 = 0x100;
        var_a0 = D_psp_089B6940[D_psp_08B41FC0];
        break;
    case 1:
        var_a1 = 0x20000;
        var_a0 = D_psp_08A1F140[D_psp_08B41FC0];
        break;
    }
    if (arg0 != D_psp_08B1F198) {
        if (D_psp_08B1F140[arg0].unk0 != NULL) {
            func_psp_0891036C(arg0);
        } else {
            func_psp_08910220(var_a0, var_a1, arg0);
        }
    }
}

void func_psp_0891034C(void) {
    memset(D_psp_08B1F140, 0, sizeof(Unk08B1F140) * 3);
}

void func_psp_08910360(Unk08B1F140* arg0) {
    memset(arg0, 0, sizeof(Unk08B1F140));
}

void func_psp_0891036C(s32 arg0) {
    Unk08B1F140* temp_a0;

    if (arg0 != -1) {
        temp_a0 = &D_psp_08B1F140[arg0];
        D_psp_08B1F1A4 = temp_a0->unk0;
        D_psp_08B1F1A8 = temp_a0->unk10;
        D_psp_08B1F1AC = temp_a0->unkC;
        D_psp_08B1F1A0 = temp_a0->unk8;
        D_psp_08B1F19C = temp_a0->unk4;
        D_psp_08B1F1B0 = temp_a0->unk14;
        D_psp_08B1F1B4 = temp_a0->unk18;
        func_psp_08910360(temp_a0);
        D_psp_08B1F198 = arg0;
    }
}

void func_psp_08910410(void) {
    Unk08B1F140* temp_a2;

    if (D_psp_08B1F198 != -1) {
        temp_a2 = &D_psp_08B1F140[D_psp_08B1F198];
        temp_a2->unk0 = D_psp_08B1F1A4;
        temp_a2->unk10 = D_psp_08B1F1A8;
        temp_a2->unkC = D_psp_08B1F1AC;
        temp_a2->unk8 = D_psp_08B1F1A0;
        temp_a2->unk4 = D_psp_08B1F19C;
        temp_a2->unk14 = D_psp_08B1F1B0;
        temp_a2->unk18 = D_psp_08B1F1B4;
    }
}

s32* func_psp_08910498(s32 arg0) {
    s32* temp_a0 = D_psp_08B1F19C;
    D_psp_08B1F19C += arg0;
    return temp_a0;
}

s32* func_psp_089104B4(s32 arg0) {
    s32* temp_a2;
    s32* temp_v0;

    temp_v0 = func_psp_08910498(2);
    temp_a2 = D_psp_08B1F19C;
    D_psp_08B1F19C += arg0;
    *temp_v0++ = GE_SET_BASE_BASE8(D_psp_08B1F19C);
    *temp_v0++ = GE_SET_JUMP_ADDR24(D_psp_08B1F19C);
    return temp_a2;
}

void func_psp_0891052C(s32 arg0) { *D_psp_08B1F19C++ = GE_SET_SHADE(arg0); }

void func_psp_08910558(s32 arg0) { *D_psp_08B1F19C++ = GE_SET_LTE(arg0); }

void func_psp_08910584(s32 arg0) { *D_psp_08B1F19C++ = GE_SET_CLE(arg0); }

void func_psp_089105B0(s32 arg0) { *D_psp_08B1F19C++ = GE_SET_BCE(arg0); }

void func_psp_089105DC(s32 arg0) { *D_psp_08B1F19C++ = GE_SET_TME(arg0); }

void func_psp_08910608(s32 arg0) { *D_psp_08B1F19C++ = GE_SET_FGE(arg0); }

void func_psp_08910634(s32 arg0) { *D_psp_08B1F19C++ = GE_SET_DTE(arg0); }

void func_psp_08910660(s32 arg0) { *D_psp_08B1F19C++ = GE_SET_ABE(arg0); }

void func_psp_0891068C(s32 arg0) { *D_psp_08B1F19C++ = GE_SET_ATE(arg0); }

void func_psp_089106B8(s32 arg0, s32 arg1, s32 arg2) {
    *D_psp_08B1F19C++ = GE_SET_ATEST(arg0, arg1, arg2);
}

void func_psp_089106F4(s32 arg0) { *D_psp_08B1F19C++ = GE_SET_ZTE(arg0); }

void func_psp_08910720(s32 arg0) { *D_psp_08B1F19C++ = GE_SET_STE(arg0); }

void func_psp_0891074C(s32 arg0) { *D_psp_08B1F19C++ = GE_SET_AAE(arg0); }

void func_psp_08910778(s32 arg0) { *D_psp_08B1F19C++ = GE_SET_CTE(arg0); }

void func_psp_089107A4(s32 arg0) {
    *D_psp_08B1F19C++ = GE_SET_ZMSK((1 - arg0) & 1);
}

void func_psp_089107DC(s32 arg0, s32 arg1) {
    *D_psp_08B1F19C++ = GE_SET_TWRAP(arg0, arg1);
}

void func_psp_08910810(s32 op, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    *D_psp_08B1F19C++ = GE_SET_BLEND(arg1, arg2, op);
    *D_psp_08B1F19C++ = GE_SET_FIXA_RGB24(arg3);
    *D_psp_08B1F19C++ = GE_SET_FIXB_RGB24(arg4);
}

void func_psp_0891089C(s32 x1, s32 y1, s32 x2, s32 y2) {
    *D_psp_08B1F19C++ = GE_SET_SCISSOR1(x1, y1);
    *D_psp_08B1F19C++ = GE_SET_SCISSOR2(x2, y2);
}

void func_psp_089108F8(s32 x, s32 y) {
    *D_psp_08B1F19C++ = GE_SET_OFFSETX(x);
    *D_psp_08B1F19C++ = GE_SET_OFFSETY(y);
}

void func_psp_08910944(s32 min, s32 max) {
    *D_psp_08B1F19C++ = GE_SET_TFILTER(min, max);
}

void func_psp_08910978(u8 a, u8 r, u8 b, u8 g) {
    *D_psp_08B1F194++ = GE_SET_AC(r, g, b);
    *D_psp_08B1F194++ = GE_SET_AA(a);
}

void func_psp_089109E4(s32 tfx, s32 tcc, s32 arg2) {
    *D_psp_08B1F19C++ = GE_SET_TFUNC(tfx, tcc, arg2);
}

void func_psp_08910A20(s32 arg0, s32 arg1) {
    *D_psp_08B1F19C++ = GE_SET_FBP_ADDR24(arg0);
    *D_psp_08B1F19C++ = GE_SET_FBW_BASE8(arg1, arg0);
}

s32 func_psp_08910A80(
    s32* vertices, u32 nVerts, u32 vertexSize, s32 primType, s32 vType) {
    s32* temp_s1;
    s32* temp_s2;
    s32* temp_v0;
    s32* temp_a1;
    s32 i;

    *D_psp_08B1F19C++ = GE_SET_VTYPE(vType);
    temp_s2 = func_psp_08910498(2);
    *D_psp_08B1F19C++ = GE_SET_PRIM(nVerts, primType);

    temp_s1 = func_psp_08910498(2);
    temp_v0 = func_psp_08910498((vertexSize * nVerts) / 4);

    *temp_s1++ = GE_SET_BASE_BASE8(D_psp_08B1F19C);
    *temp_s1++ = GE_SET_JUMP_ADDR24(D_psp_08B1F19C);

    temp_a1 = temp_v0;
    for (i = (vertexSize * nVerts) / 4; i > 0; i--) {
        *temp_a1++ = *vertices++;
    }

    *temp_s2++ = GE_SET_BASE_BASE8(temp_v0);
    *temp_s2++ = GE_SET_VADR_ADDR24(temp_v0);
    return 2;
}

s32 func_psp_08910C74(s32 arg0, s32 arg1, s32 arg3, s32 arg4, s32 arg5) {
    *D_psp_08B1F19C++ = GE_SET_VTYPE(arg5);
    *D_psp_08B1F19C++ = GE_SET_BASE_BASE8(arg0);
    *D_psp_08B1F19C++ = GE_SET_VADR_ADDR24(arg0);
    *D_psp_08B1F19C++ = GE_SET_PRIM(arg1, arg4);
    return 2;
}

void func_psp_08910D28(void) {
    D_psp_08B1F1B8 = 0;
    D_psp_08B1F1BC = 0;
    D_psp_08B1F1C0 = 0;
}

s32 func_psp_08910D44(s32 arg0, s32 arg1, s32 tpf) {
    ScePspVector3 formats = {.i = {GU_PSM_T4, GU_PSM_T8, GU_PSM_5551}};
    ScePspVector3 sp18 = {.i = {0x100, 0x80, 0x40}};

    if (D_psp_08B1F1B8 == arg0 && D_psp_08B1F1BC == tpf) {
        arg0 = 0;
    }
    if (D_psp_08B1F1C0 == arg1) {
        arg1 = 0;
    }
    if (arg1 != 0) {
        *D_psp_08B1F19C++ = GE_SET_CLUT(GU_PSM_5551, 0, 0xFF, 0);
        *D_psp_08B1F19C++ = GE_SET_CBP_ADDR24(arg1);
        *D_psp_08B1F19C++ = GE_SET_CBW_BASE8(arg1);
        if (tpf == 1) {
            *D_psp_08B1F19C = GE_SET_CLOAD(16);
        } else {
            *D_psp_08B1F19C = GE_SET_CLOAD(1);
        }
        D_psp_08B1F19C++;
        D_psp_08B1F1C0 = arg1;
    }
    if (arg0 != 0) {
        *D_psp_08B1F19C++ = GE_SET_TMODE(GU_TEXBUF_NORMAL, GU_SINGLE_CLUT, 0);
        *D_psp_08B1F19C++ = GE_SET_TPF(formats.i[tpf], 0);
        *D_psp_08B1F19C++ = GE_SET_TBP0_ADDR24(arg0);
        *D_psp_08B1F19C++ = GE_SET_TBW0_BASE8(sp18.i[tpf], arg0);
        *D_psp_08B1F19C++ = GE_SET_TSIZE0(8 - tpf, 9);
        D_psp_08B1F1B8 = arg0;
        D_psp_08B1F1BC = tpf;
    }
    if (arg0 != 0) {
        *D_psp_08B1F19C++ = GE_SET_TFLUSH();
        ResetGraph(1);
    }
    return arg1 | arg0;
}

s32 func_psp_08910FD8(
    s32 arg0, s32 arg1, s32 tpf, s32 arg3, s32 width, s32 height) {
    if (arg1 != 0) {
        *D_psp_08B1F19C++ = GE_SET_CLUT(GU_PSM_5551, 0, 0xFF, 0);
        *D_psp_08B1F19C++ = GE_SET_CBP_ADDR24(arg1);
        *D_psp_08B1F19C++ = GE_SET_CBW_BASE8(arg1);
        *D_psp_08B1F19C++ = GE_SET_CLOAD(16);
        D_psp_08B1F1C0 = arg1;
    }
    if (arg0 != 0) {
        *D_psp_08B1F19C++ = GE_SET_TMODE(GU_TEXBUF_NORMAL, GU_SINGLE_CLUT, 0);
        *D_psp_08B1F19C++ = GE_SET_TPF(tpf, 0);
        *D_psp_08B1F19C++ = GE_SET_TBP0_ADDR24(arg0);
        *D_psp_08B1F19C++ = GE_SET_TBW0_BASE8(arg3, arg0);
        *D_psp_08B1F19C++ = GE_SET_TSIZE0(width, height);
        D_psp_08B1F1B8 = arg0;
        D_psp_08B1F1BC = tpf;
    }
    if (arg0 != 0) {
        *D_psp_08B1F19C++ = GE_SET_TFLUSH();
        ResetGraph(1);
    }
    return arg1 | arg0;
}

s32 func_psp_089111C0(
    s32 arg0, s32 arg1, s32 tpf, s32 arg3, s32 width, s32 height) {
    if (arg1 != 0) {
        *D_psp_08B1F19C++ = GE_SET_CLUT(GU_PSM_8888, 0, 0xFF, 0);
        *D_psp_08B1F19C++ = GE_SET_CBP_ADDR24(arg1);
        *D_psp_08B1F19C++ = GE_SET_CBW_BASE8(arg1);
        *D_psp_08B1F19C++ = GE_SET_CLOAD(16);
        D_psp_08B1F1C0 = arg1;
    }
    if (arg0 != 0) {
        *D_psp_08B1F19C++ = GE_SET_TMODE(GU_TEXBUF_NORMAL, GU_SINGLE_CLUT, 0);
        *D_psp_08B1F19C++ = GE_SET_TPF(tpf, 0);
        *D_psp_08B1F19C++ = GE_SET_TBP0_ADDR24(arg0);
        *D_psp_08B1F19C++ = GE_SET_TBW0_BASE8(arg3, arg0);
        *D_psp_08B1F19C++ = GE_SET_TSIZE0(width, height);
        D_psp_08B1F1B8 = arg0;
        D_psp_08B1F1BC = tpf;
    }
    if (arg0 != 0) {
        *D_psp_08B1F19C++ = GE_SET_TFLUSH();
        ResetGraph(1);
    }
    return arg1 | arg0;
}

void func_psp_089113A8(s32 arg0) {
    switch (arg0) {
    case 0:
        func_psp_08910660(1);
        func_psp_08910810(GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
        break;
    case 1:
        func_psp_08910660(1);
        func_psp_08910810(GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
        break;
    case 2:
        func_psp_08910660(1);
        func_psp_08910810(
            GU_REVERSE_SUBTRACT, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
        break;
    case 3:
        func_psp_08910660(1);
        func_psp_08910810(GU_ADD, GU_FIX, GU_FIX, 0xFF404040, 0xFFFFFFFF);
        break;
    default:
        func_psp_08910660(0);
        break;
    }
}

s32 func_psp_0891149C(s32 arg0, u32 arg1, u32 arg2, s32 arg3, s32 tpf) {
    ScePspVector3 formats = {.i = {GU_PSM_T4, GU_PSM_T8, GU_PSM_5551}};
    bool var_v0;
    s32 tbw;
    s32 tw, th;

    var_v0 = false;
    if (arg3 != 0 && D_psp_08B1F1C0 != arg3) {
        *D_psp_08B1F19C++ = GE_SET_CLUT(GU_PSM_5551, 0, 0xFF, 0);
        *D_psp_08B1F19C++ = GE_SET_CBP_ADDR24(arg3);
        *D_psp_08B1F19C++ = GE_SET_CBW_BASE8(arg3);
        if (tpf == 1) {
            *D_psp_08B1F19C = GE_SET_CLOAD(16);
        } else {
            *D_psp_08B1F19C = GE_SET_CLOAD(1);
        }
        D_psp_08B1F19C++;
        D_psp_08B1F1C0 = arg3;
    }
    if (arg0 != 0 && D_psp_08B1F1B8 != arg0) {
        tbw = 0;
        switch (tpf) {
        case 0:
            arg1 = (arg1 + 0x1F) & ~0x1F;
            tbw = arg1;
            break;
        case 1:
            arg1 = (arg1 + 0xF) & ~0xF;
            tbw = arg1;
            break;
        case 2:
            arg1 = (arg1 + 7) & ~7;
            tbw = arg1;
            break;
        }

        if (arg1 > 0x100) {
            tw = 9;
        } else if (arg1 > 0x80) {
            tw = 8;
        } else if (arg1 > 0x40) {
            tw = 7;
        } else if (arg1 > 0x20) {
            tw = 6;
        } else if (arg1 > 0x10) {
            tw = 5;
        } else if (arg1 > 8) {
            tw = 4;
        } else {
            tw = 3;
        }

        if (arg2 > 0x100) {
            th = 9;
        } else if (arg2 > 0x80) {
            th = 8;
        } else if (arg2 > 0x40) {
            th = 7;
        } else if (arg2 > 0x20) {
            th = 6;
        } else if (arg2 > 0x10) {
            th = 5;
        } else if (arg2 > 8) {
            th = 4;
        } else {
            th = 3;
        }
        *D_psp_08B1F19C++ = GE_SET_TMODE(GU_TEXBUF_NORMAL, GU_SINGLE_CLUT, 0);
        *D_psp_08B1F19C++ = GE_SET_TPF(formats.i[tpf], 0);
        *D_psp_08B1F19C++ = GE_SET_TBP0_ADDR24(arg0);
        *D_psp_08B1F19C++ = GE_SET_TBW0_BASE8(tbw, arg0);
        *D_psp_08B1F19C++ = GE_SET_TSIZE0(tw, th);
        D_psp_08B1F1B8 = arg0;
        D_psp_08B1F1BC = tpf;
        var_v0 = true;
    }
    if (var_v0) {
        *D_psp_08B1F19C++ = GE_SET_TFLUSH();
        ResetGraph(1);
    }
    return 0;
}

void func_psp_089117F4(s32 mode, s32 sx, s32 sy, s32 height, s32 width, s32 sbw,
                       u8* sbp, s32 dx, s32 dy, s32 dbw, u8* dbp) {
    *D_psp_08B1F19C++ = GE_SET_TSYNC();
    *D_psp_08B1F19C++ = GE_SET_XBP1_ADDR24(sbp);
    *D_psp_08B1F19C++ = GE_SET_XBW1_BASE8(sbw, sbp);
    *D_psp_08B1F19C++ = GE_SET_XPOS1(sx, sy);
    *D_psp_08B1F19C++ = GE_SET_XBP2_ADDR24(dbp);
    *D_psp_08B1F19C++ = GE_SET_XBW2_BASE8(dbw, dbp);
    *D_psp_08B1F19C++ = GE_SET_XPOS2(dx, dy);
    *D_psp_08B1F19C++ = GE_SET_XSIZE(height - 1, width - 1);
    *D_psp_08B1F19C++ = GE_SET_XSTART(mode == 3);
    *D_psp_08B1F19C++ = GE_SET_TSYNC();
}

s32 func_psp_08911990(s32 arg0, s32 arg1) {

    s32 tw = (arg1 == 0x100) ? 8 : 9;

    *D_psp_08B1F19C++ = GE_SET_TMODE(GU_TEXBUF_NORMAL, GU_SINGLE_CLUT, 0);
    *D_psp_08B1F19C++ = GE_SET_TPF(GU_PSM_5551, 0);
    *D_psp_08B1F19C++ = GE_SET_TBP0_ADDR24(arg0);
    *D_psp_08B1F19C++ = GE_SET_TBW0_BASE8(arg1, arg0);
    *D_psp_08B1F19C++ = GE_SET_TSIZE0(tw, 9);
    *D_psp_08B1F19C++ = GE_SET_TFLUSH();
    ResetGraph(1);
    D_psp_08B1F1B8 = 0;
    D_psp_08B1F1BC = 0;
    D_psp_08B1F1C0 = 0;
    return 0;
}

void func_psp_08911AB8(u8 r, u8 g, u8 b) {
    func_psp_08910778(1);
    *D_psp_08B1F19C++ = GE_SET_CREF(r, g, b);
    *D_psp_08B1F19C++ = GE_SET_CMSK(0xFF, 0xFF, 0xFF);
    *D_psp_08B1F19C++ = GE_SET_CTEST(GU_NOTEQUAL);
}

void func_psp_08911B7C(void) { func_psp_08910778(0); }

void func_psp_08911B84(
    s32 arg0, s32 op, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    *D_psp_08B1F19C++ = GE_SET_ABE(arg0);
    if (arg0 == 1) {
        *D_psp_08B1F19C++ = GE_SET_BLEND(arg2, arg3, op);
        *D_psp_08B1F19C++ = GE_SET_FIXA_RGB24(arg4);
        *D_psp_08B1F19C++ = GE_SET_FIXB_RGB24(arg5);
    }
}

void func_psp_08911C3C(u8 r, u8 g, u8 b) {
    s32* ptr;

    ptr = D_psp_08B1F1D0[0];
    *ptr++ = GE_SET_ATE(GU_FALSE);
    *ptr++ = GE_SET_TME(GU_TRUE);
    *ptr++ = GE_SET_CTE(GU_FALSE);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[1];
    *ptr++ = GE_SET_ATE(GU_FALSE);
    *ptr++ = GE_SET_TME(GU_TRUE);
    *ptr++ = GE_SET_CTE(GU_TRUE);
    *ptr++ = GE_SET_CREF(r, g, b);
    *ptr++ = GE_SET_CMSK(0xFF, 0xFF, 0xFF);
    *ptr++ = GE_SET_CTEST(GU_NOTEQUAL);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[2];
    *ptr++ = GE_SET_ATE(GU_TRUE);
    *ptr++ = GE_SET_ATEST(GU_GEQUAL, 1, 0xFF);
    *ptr++ = GE_SET_TME(GU_TRUE);
    *ptr++ = GE_SET_CTE(GU_FALSE);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[3];
    *ptr++ = GE_SET_ATE(GU_TRUE);
    *ptr++ = GE_SET_ATEST(GU_GEQUAL, 1, 0xFF);
    *ptr++ = GE_SET_TME(GU_TRUE);
    *ptr++ = GE_SET_CTE(GU_TRUE);
    *ptr++ = GE_SET_CREF(r, g, b);
    *ptr++ = GE_SET_CMSK(0xFF, 0xFF, 0xFF);
    *ptr++ = GE_SET_CTEST(GU_NOTEQUAL);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[4];
    *ptr++ = GE_SET_ATE(GU_TRUE);
    *ptr++ = GE_SET_ATEST(GU_EQUAL, 0, 0xFF);
    *ptr++ = GE_SET_ABE(GU_TRUE);
    *ptr++ = GE_SET_BLEND(GU_ONE_MINUS_SRC_ALPHA, GU_FIX, GU_ADD);
    *ptr++ = GE_SET_FIXA_RGB24(0x00000000);
    *ptr++ = GE_SET_FIXB_RGB24(0x00000000);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[5];
    *ptr++ = GE_SET_ATE(GU_FALSE);
    *ptr++ = GE_SET_TME(GU_TRUE);
    *ptr++ = GE_SET_CTE(GU_FALSE);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[6];
    *ptr++ = GE_SET_ATE(GU_FALSE);
    *ptr++ = GE_SET_TME(GU_TRUE);
    *ptr++ = GE_SET_CTE(GU_TRUE);
    *ptr++ = GE_SET_CREF(r, g, b);
    *ptr++ = GE_SET_CMSK(0xFF, 0xFF, 0xFF);
    *ptr++ = GE_SET_CTEST(GU_NOTEQUAL);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[7];
    *ptr++ = GE_SET_ATE(GU_TRUE);
    *ptr++ = GE_SET_ATEST(GU_GEQUAL, 1, 0xFF);
    *ptr++ = GE_SET_TME(GU_TRUE);
    *ptr++ = GE_SET_CTE(GU_FALSE);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[8];
    *ptr++ = GE_SET_ATE(GU_TRUE);
    *ptr++ = GE_SET_ATEST(GU_GEQUAL, 1, 0xFF);
    *ptr++ = GE_SET_TME(GU_TRUE);
    *ptr++ = GE_SET_CTE(GU_TRUE);
    *ptr++ = GE_SET_CREF(r, g, b);
    *ptr++ = GE_SET_CMSK(0xFF, 0xFF, 0xFF);
    *ptr++ = GE_SET_CTEST(GU_NOTEQUAL);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[9];
    *ptr++ = GE_SET_ATE(GU_TRUE);
    *ptr++ = GE_SET_ATEST(GU_EQUAL, 0, 0xFF);
    *ptr++ = GE_SET_ABE(GU_TRUE);
    *ptr++ = GE_SET_BLEND(GU_ONE_MINUS_SRC_ALPHA, GU_FIX, GU_ADD);
    *ptr++ = GE_SET_FIXA_RGB24(0x00000000);
    *ptr++ = GE_SET_FIXB_RGB24(0x00000000);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[10];
    *ptr++ = GE_SET_ATE(GU_FALSE);
    *ptr++ = GE_SET_CTE(GU_FALSE);
    *ptr++ = GE_SET_TME(GU_FALSE);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[15];
    *ptr++ = GE_SET_ABE(GU_TRUE);
    *ptr++ = GE_SET_BLEND(GU_FIX, GU_FIX, GU_ADD);
    *ptr++ = GE_SET_FIXA_RGB24(0xFF808080);
    *ptr++ = GE_SET_FIXB_RGB24(0xFF808080);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[16];
    *ptr++ = GE_SET_ABE(GU_TRUE);
    *ptr++ = GE_SET_BLEND(GU_FIX, GU_FIX, GU_ADD);
    *ptr++ = GE_SET_FIXA_RGB24(0xFFFFFFFF);
    *ptr++ = GE_SET_FIXB_RGB24(0xFFFFFFFF);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[17];
    *ptr++ = GE_SET_ABE(GU_TRUE);
    *ptr++ = GE_SET_BLEND(GU_FIX, GU_FIX, GU_REVERSE_SUBTRACT);
    *ptr++ = GE_SET_FIXA_RGB24(0xFFFFFFFF);
    *ptr++ = GE_SET_FIXB_RGB24(0xFFFFFFFF);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[18];
    *ptr++ = GE_SET_ABE(GU_TRUE);
    *ptr++ = GE_SET_BLEND(GU_FIX, GU_FIX, GU_ADD);
    *ptr++ = GE_SET_FIXA_RGB24(0xFF404040);
    *ptr++ = GE_SET_FIXB_RGB24(0xFFFFFFFF);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[11];
    *ptr++ = GE_SET_ABE(GU_FALSE);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[12];
    *ptr++ = GE_SET_ABE(GU_FALSE);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[13];
    *ptr++ = GE_SET_ABE(GU_FALSE);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[14];
    *ptr++ = GE_SET_ABE(GU_FALSE);
    *ptr++ = GE_SET_RET();
}

void func_psp_08911F24(s32 arg0, s32 arg1) {
    *D_psp_08B1F19C++ =
        GE_SET_BASE_BASE8(D_psp_08B1F1D0[arg1 + ((arg0 * 2) + 5)]);
    *D_psp_08B1F19C++ =
        GE_SET_CALL_ADDR24(D_psp_08B1F1D0[arg1 + ((arg0 * 2) + 5)]);
}

void func_psp_08911FA0(void) {
    *D_psp_08B1F19C++ = GE_SET_BASE_BASE8(D_psp_08B1F1D0[9]);
    *D_psp_08B1F19C++ = GE_SET_CALL_ADDR24(D_psp_08B1F1D0[9]);
}

void func_psp_08912008(void) {
    *D_psp_08B1F19C++ = GE_SET_BASE_BASE8(D_psp_08B1F1D0[10]);
    *D_psp_08B1F19C++ = GE_SET_CALL_ADDR24(D_psp_08B1F1D0[10]);
}

void func_psp_08912070(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    *D_psp_08B1F19C++ = GE_SET_BASE_BASE8(D_psp_08B1F1D0[arg0 + 2]);
    *D_psp_08B1F19C++ = GE_SET_CALL_ADDR24(D_psp_08B1F1D0[arg0 + 2]);
}

void func_psp_089120E4(void) {
    *D_psp_08B1F19C++ = GE_SET_BASE_BASE8(D_psp_08B1F1D0[4]);
    *D_psp_08B1F19C++ = GE_SET_CALL_ADDR24(D_psp_08B1F1D0[4]);
}

void func_psp_0891214C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    *D_psp_08B1F19C++ = GE_SET_BASE_BASE8(D_psp_08B1F1D0[arg0]);
    *D_psp_08B1F19C++ = GE_SET_CALL_ADDR24(D_psp_08B1F1D0[arg0]);
}
