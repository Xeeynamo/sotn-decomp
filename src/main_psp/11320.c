// SPDX-License-Identifier: AGPL-3.0-or-later
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

extern float D_psp_0893CCFC;
extern float D_psp_0893CD00;
extern float D_psp_0893CD04;
extern float D_psp_0893CD08;
extern float D_psp_0893CD0C;
extern float D_psp_0893CD10;
extern float D_psp_0893CD14;
extern float D_psp_0893CD18;
extern float D_psp_0893CD1C;
extern u8 D_psp_089B6540[0x400];
extern s32 D_psp_089B6940[2][0x100];
extern u8 D_psp_089B7140[2][0x34000];
extern s32 D_psp_08A1F140[2][0x20000];
extern Unk08B1F140 D_psp_08B1F140[3];
extern s32* D_psp_08B1F194;
extern s32 D_psp_08B1F198;
extern s32* D_psp_08B1F19C;
extern s32 D_psp_08B1F1A0;
extern s32* D_psp_08B1F1A4;
extern s32 D_psp_08B1F1A8;
extern s32 D_psp_08B1F1AC;
extern s32 D_psp_08B1F1B0;
extern s32 D_psp_08B1F1B4;
extern s32 D_psp_08B1F1B8;
extern s32 D_psp_08B1F1BC;
extern s32 D_psp_08B1F1C0;
extern s32 D_psp_08B1F1D0[][0x20];
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
    sceGuStart(GU_IMMEDIATE, D_psp_089B6540, sizeof(D_psp_089B6540));
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
    sceGuBlendFunc(GU_ADD, GU_FIX, GU_FIX, 0, -1);
    sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
    sceGuBlendFunc(GU_REVERSE_SUBTRACT, GU_SRC_ALPHA, GU_FIX, 0, -1);
    sceGuBlendFunc(GU_ADD, GU_SRC_COLOR, GU_FIX, 0, 0);
    sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_FIX, 0, -1);
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
    sceGuStart(GU_IMMEDIATE, D_psp_089B6540, sizeof(D_psp_089B6540));
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
        if (D_psp_08B1F140[arg0].unk0 != 0) {
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

void func_psp_08910810(s32 op, s32 arg1, s32 arg2, ScePspRGBA8888 arg3, ScePspRGBA8888 arg4) {
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

s32 func_psp_08910A80(s32* arg0, u32 nVerts, u32 arg2, s32 arg3, s32 arg4) {
    s32* temp_s1;
    s32* temp_s2;
    s32* temp_v0;
    s32* temp_a1;
    s32 i;

    *D_psp_08B1F19C++ = GE_SET_VTYPE(arg4);
    temp_s2 = func_psp_08910498(2);
    *D_psp_08B1F19C++ = GE_SET_PRIM(nVerts, arg3);

    temp_s1 = func_psp_08910498(2);
    temp_v0 = func_psp_08910498((arg2 * nVerts) / 4);

    *temp_s1++ = GE_SET_BASE_BASE8(D_psp_08B1F19C);
    *temp_s1++ = GE_SET_JUMP_ADDR24(D_psp_08B1F19C);

    temp_a1 = temp_v0;
    for (i = (arg2 * nVerts) / 4; i > 0; i--) {
        *temp_a1++ = *arg0++;
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

s32 func_psp_08910D44(s32 arg0, s32 arg1, s32 arg2) {
    ScePspVector3 sp24;
    ScePspVector3 sp18;

    sp24.f[0] = D_psp_0893CCFC;
    sp24.f[1] = D_psp_0893CD00;
    sp24.f[2] = D_psp_0893CD04;
    sp18.f[0] = D_psp_0893CD08;
    sp18.f[1] = D_psp_0893CD0C;
    sp18.f[2] = D_psp_0893CD10;
    if ((D_psp_08B1F1B8 == arg0) && (D_psp_08B1F1BC == arg2)) {
        arg0 = 0;
    }
    if (D_psp_08B1F1C0 == arg1) {
        arg1 = 0;
    }
    if (arg1 != 0) {
        *D_psp_08B1F19C++ = GE_SET_CLUT(GU_PSM_5551, 0, 0xFF, 0);
        *D_psp_08B1F19C++ = GE_SET_CBP_ADDR24(arg1);
        *D_psp_08B1F19C++ = GE_SET_CBW_BASE8(arg1);
        if (arg2 == 1) {
            *D_psp_08B1F19C = GE_SET_CLOAD(16);
        } else {
            *D_psp_08B1F19C = GE_SET_CLOAD(1);
        }
        D_psp_08B1F19C++;
        D_psp_08B1F1C0 = arg1;
    }
    if (arg0 != 0) {
        *D_psp_08B1F19C++ = GE_SET_TMODE(GU_TEXBUF_NORMAL, GU_SINGLE_CLUT, 0);
        *D_psp_08B1F19C++ = GE_SET_TPF(sp24.i[arg2], 0);
        *D_psp_08B1F19C++ = GE_SET_TBP0_ADDR24(arg0);
        *D_psp_08B1F19C++ = GE_SET_TBW0_BASE8(sp18.i[arg2], arg0);
        *D_psp_08B1F19C++ = GE_SET_TSIZE0(8 - arg2, 9);
        D_psp_08B1F1B8 = arg0;
        D_psp_08B1F1BC = arg2;
    }
    if (arg0 != 0) {
        *D_psp_08B1F19C++ = GE_SET_TFLUSH();
        ResetGraph(1);
    }
    return arg1 | arg0;
}

s32 func_psp_08910FD8(
    s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 width, s32 height) {
    if (arg1 != 0) {
        *D_psp_08B1F19C++ = GE_SET_CLUT(GU_PSM_5551, 0, 0xFF, 0);
        *D_psp_08B1F19C++ = GE_SET_CBP_ADDR24(arg1);
        *D_psp_08B1F19C++ = GE_SET_CBW_BASE8(arg1);
        *D_psp_08B1F19C++ = GE_SET_CLOAD(16);
        D_psp_08B1F1C0 = arg1;
    }
    if (arg0 != 0) {
        *D_psp_08B1F19C++ = GE_SET_TMODE(GU_TEXBUF_NORMAL, GU_SINGLE_CLUT, 0);
        *D_psp_08B1F19C++ = GE_SET_TPF(arg2, 0);
        *D_psp_08B1F19C++ = GE_SET_TBP0_ADDR24(arg0);
        *D_psp_08B1F19C++ = GE_SET_TBW0_BASE8(arg3, arg0);
        *D_psp_08B1F19C++ = GE_SET_TSIZE0(width, height);
        D_psp_08B1F1B8 = arg0;
        D_psp_08B1F1BC = arg2;
    }
    if (arg0 != 0) {
        *D_psp_08B1F19C++ = GE_SET_TFLUSH();
        ResetGraph(1);
    }
    return arg1 | arg0;
}

s32 func_psp_089111C0(
    s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 width, s32 height) {
    if (arg1 != 0) {
        *D_psp_08B1F19C++ = GE_SET_CLUT(GU_PSM_8888, 0, 0xFF, 0);
        *D_psp_08B1F19C++ = GE_SET_CBP_ADDR24(arg1);
        *D_psp_08B1F19C++ = GE_SET_CBW_BASE8(arg1);
        *D_psp_08B1F19C++ = GE_SET_CLOAD(16);
        D_psp_08B1F1C0 = arg1;
    }
    if (arg0 != 0) {
        *D_psp_08B1F19C++ = GE_SET_TMODE(GU_TEXBUF_NORMAL, GU_SINGLE_CLUT, 0);
        *D_psp_08B1F19C++ = GE_SET_TPF(arg2, 0);
        *D_psp_08B1F19C++ = GE_SET_TBP0_ADDR24(arg0);
        *D_psp_08B1F19C++ = GE_SET_TBW0_BASE8(arg3, arg0);
        *D_psp_08B1F19C++ = GE_SET_TSIZE0(width, height);
        D_psp_08B1F1B8 = arg0;
        D_psp_08B1F1BC = arg2;
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
        func_psp_08910810(GU_REVERSE_SUBTRACT, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
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

s32 func_psp_0891149C(s32 arg0, u32 arg1, u32 arg2, s32 arg3, s32 arg4) {
    ScePspVector3 sp14;
    s32 var_v0;
    s32 var_v1_2;
    s32 tw, th;

    sp14.f[0] = D_psp_0893CD14;
    sp14.f[1] = D_psp_0893CD18;
    sp14.f[2] = D_psp_0893CD1C;
    var_v0 = 0;
    if ((arg3 != 0) && (D_psp_08B1F1C0 != arg3)) {
        *D_psp_08B1F19C++ = GE_SET_CLUT(GU_PSM_5551, 0, 0xFF, 0);
        *D_psp_08B1F19C++ = GE_SET_CBP_ADDR24(arg3);
        *D_psp_08B1F19C++ = GE_SET_CBW_BASE8(arg3);
        if (arg4 == 1) {
            *D_psp_08B1F19C = GE_SET_CLOAD(16);
        } else {
            *D_psp_08B1F19C = GE_SET_CLOAD(1);
        }
        D_psp_08B1F19C++;
        D_psp_08B1F1C0 = arg3;
    }
    if ((arg0 != 0) && (D_psp_08B1F1B8 != arg0)) {
        var_v1_2 = 0;
        switch (arg4) {
        case 0:
            arg1 = (arg1 + 0x1F) & ~0x1F;
            var_v1_2 = arg1;
            break;
        case 1:
            arg1 = (arg1 + 0xF) & ~0xF;
            var_v1_2 = arg1;
            break;
        case 2:
            arg1 = (arg1 + 7) & ~7;
            var_v1_2 = arg1;
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
        *D_psp_08B1F19C++ = GE_SET_TPF(sp14.i[arg4], 0);
        *D_psp_08B1F19C++ = GE_SET_TBP0_ADDR24(arg0);
        *D_psp_08B1F19C++ = GE_SET_TBW0_BASE8(var_v1_2, arg0);
        *D_psp_08B1F19C++ = GE_SET_TSIZE0(tw, th);
        D_psp_08B1F1B8 = arg0;
        D_psp_08B1F1BC = arg4;
        var_v0 = 1;
    }
    if (var_v0 != 0) {
        *D_psp_08B1F19C++ = GE_SET_TFLUSH();
        ResetGraph(1);
    }
    return 0;
}

void func_psp_089117F4(s32 mode, s32 sx, s32 sy, s32 height, s32 width, s32 sbw,
                       s32 sbp, s32 dx, s32 dy, s32 dbw, s32 dbp) {
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
    s32 arg0, s32 op, s32 arg2, s32 arg3, ScePspRGBA8888 arg4, ScePspRGBA8888 arg5) {
    *D_psp_08B1F19C++ = GE_SET_ABE(arg0);
    if (arg0 == 1) {
        *D_psp_08B1F19C++ = GE_SET_BLEND(arg2, arg3, op);
        *D_psp_08B1F19C++ = GE_SET_FIXA_RGB24(arg4);
        *D_psp_08B1F19C++ = GE_SET_FIXB_RGB24(arg5);
    }
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08911C3C);

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

void func_psp_08912070(s32 arg0) {
    *D_psp_08B1F19C++ = GE_SET_BASE_BASE8(D_psp_08B1F1D0[arg0 + 2]);
    *D_psp_08B1F19C++ = GE_SET_CALL_ADDR24(D_psp_08B1F1D0[arg0 + 2]);
}

void func_psp_089120E4(void) {
    *D_psp_08B1F19C++ = GE_SET_BASE_BASE8(D_psp_08B1F1D0[4]);
    *D_psp_08B1F19C++ = GE_SET_CALL_ADDR24(D_psp_08B1F1D0[4]);
}

void func_psp_0891214C(s32 arg0) {
    *D_psp_08B1F19C++ = GE_SET_BASE_BASE8(D_psp_08B1F1D0[arg0]);
    *D_psp_08B1F19C++ = GE_SET_CALL_ADDR24(D_psp_08B1F1D0[arg0]);
}
