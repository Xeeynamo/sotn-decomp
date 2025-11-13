// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspgu.h>

typedef struct {
    s32* unk0;
    s32* unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
} Unk08B1F140;

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
    D_psp_08A1F140[D_psp_08B41FC0][0] = 0x0B000000;
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
    *D_psp_08B1F194++ = 0x0B000000;
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
                *D_psp_08B1F19C++ = 0x0B000000;
                *D_psp_08B1F19C++ = 0;
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
            *D_psp_08B1F19C++ = 0x0B000000;
            *D_psp_08B1F19C++ = 0;
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
    *temp_v0++ = 0x10000000 | ((u32)D_psp_08B1F19C & 0xFF000000) >> 8;
    *temp_v0++ = 0x08000000 | (u32)D_psp_08B1F19C & 0x00FFFFFF;
    return temp_a2;
}

void func_psp_0891052C(s32 arg0) { *D_psp_08B1F19C++ = 0x50000000 | arg0; }

void func_psp_08910558(s32 arg0) { *D_psp_08B1F19C++ = 0x17000000 | arg0; }

void func_psp_08910584(s32 arg0) { *D_psp_08B1F19C++ = 0x1C000000 | arg0; }

void func_psp_089105B0(s32 arg0) { *D_psp_08B1F19C++ = 0x1D000000 | arg0; }

void func_psp_089105DC(s32 arg0) { *D_psp_08B1F19C++ = 0x1E000000 | arg0; }

void func_psp_08910608(s32 arg0) { *D_psp_08B1F19C++ = 0x1F000000 | arg0; }

void func_psp_08910634(s32 arg0) { *D_psp_08B1F19C++ = 0x20000000 | arg0; }

void func_psp_08910660(s32 arg0) { *D_psp_08B1F19C++ = 0x21000000 | arg0; }

void func_psp_0891068C(s32 arg0) { *D_psp_08B1F19C++ = 0x22000000 | arg0; }

void func_psp_089106B8(s32 arg0, s32 arg1, s32 arg2) {
    *D_psp_08B1F19C++ = 0xDB000000 | arg2 << 16 | arg1 << 8 | arg0;
}

void func_psp_089106F4(s32 arg0) { *D_psp_08B1F19C++ = 0x23000000 | arg0; }

void func_psp_08910720(s32 arg0) { *D_psp_08B1F19C++ = 0x24000000 | arg0; }

void func_psp_0891074C(s32 arg0) { *D_psp_08B1F19C++ = 0x25000000 | arg0; }

void func_psp_08910778(s32 arg0) { *D_psp_08B1F19C++ = 0x27000000 | arg0; }

void func_psp_089107A4(s32 arg0) {
    *D_psp_08B1F19C++ = 0xE7000000 | (1 - arg0) & 1;
}

void func_psp_089107DC(s32 arg0, s32 arg1) {
    *D_psp_08B1F19C++ = 0xC7000000 | arg1 << 8 | arg0;
}

void func_psp_08910810(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    *D_psp_08B1F19C++ = 0xDF000000 | arg0 << 8 | arg2 << 4 | arg1;
    *D_psp_08B1F19C++ = 0xE0000000 | arg3 & 0x00FFFFFF;
    *D_psp_08B1F19C++ = 0xE1000000 | arg4 & 0x00FFFFFF;
}

void func_psp_0891089C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    *D_psp_08B1F19C++ = 0xD4000000 | arg1 << 10 | arg0;
    *D_psp_08B1F19C++ = 0xD5000000 | arg3 << 10 | arg2;
}

void func_psp_089108F8(s32 arg0, s32 arg1) {
    *D_psp_08B1F19C++ = 0x4C000000 | arg0;
    *D_psp_08B1F19C++ = 0x4D000000 | arg1;
}

void func_psp_08910944(s32 arg0, s32 arg1) {
    *D_psp_08B1F19C++ = 0xC6000000 | arg1 << 8 | arg0;
}

void func_psp_08910978(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    *D_psp_08B1F194++ = 0x5C000000 | arg2 << 16 | arg3 << 8 | arg1;
    *D_psp_08B1F194++ = 0x5D000000 | arg0;
}

void func_psp_089109E4(s32 arg0, s32 arg1, s32 arg2) {
    *D_psp_08B1F19C++ = 0xC9000000 | arg2 << 16 | arg1 << 8 | arg0;
}

void func_psp_08910A20(s32 arg0, s32 arg1) {
    *D_psp_08B1F19C++ = 0x9C000000 | arg0 & 0x00FFFFFF;
    *D_psp_08B1F19C++ = 0x9D000000 | ((arg0 >> 24) & 0xF) << 16 | arg1;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08910A80);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08910C74);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08910D28);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08910D44);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08910FD8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089111C0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089113A8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_0891149C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089117F4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08911990);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08911AB8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08911B7C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08911B84);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08911C3C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08911F24);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08911FA0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08912008);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08912070);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089120E4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_0891214C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089121BC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", DVDUMDSampleStart);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08912398);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089123B8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_0891249C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08912530);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089125F8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08912608);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08912640);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_0891269C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_0891273C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_0891274C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_0891275C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089127D8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089127E8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08912814);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08912820);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089128C4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089132C8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08913314);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089133D4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08913A04);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08913B48);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08913B98);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08913C24);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08913C58);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08913CA0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08913CF0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08913D20);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08913DD4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08913E60);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08913F5C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089140DC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089144BC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08914638);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08914854);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_0891490C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_0891499C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08914A18);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08914AB8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08914AE8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08914B08);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08914B58);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08914BA4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08914BF4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08914C20);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", dispbuf_func);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08914E44);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08914E74);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08914EE0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08914F18);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08914FA8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08914FFC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_0891504C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08915070);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08915088);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08915228);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08915250);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_0891527C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08915294);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08915324);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08915340);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_0891535C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_0891539C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08915454);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08915470);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", read_func);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08915C70);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08915F5C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08915FD0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08916094);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08916110);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08916188);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089161D8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08916278);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089162A8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089162C8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089162F0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08916310);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", soundbuf_func);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08916550);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08916630);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08916724);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08916830);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_0891689C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_089168E8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_0891692C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/11320", func_psp_08916984);
