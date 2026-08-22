// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"

#include "stage_16.h"
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DC040, func_060DC040);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DC1A8, func_060DC1A8);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DC318, func_060DC318);
typedef struct {
    s32 unk0;
    s32 unk4;
    u16 unk8;
    u16 unkA;
} Stage16SpriteBank;

extern Stage16SpriteBank g_Stage16SpriteBank16;
extern void TekiInit(Entity* self, s32 arg);
extern void func_0600AFA8(SpriteObject* sprite, SaturnSpriteFrameHeader* frame);

void func_060DC418(Entity* self) {
    SpriteObject* sprite;

    if (self->step == 0) {
        TekiInit(self, 5);
        self->step++;
        sprite = CreateSpriteObject(
            g_Stage16SpriteBank16.unk8, g_Stage16SpriteBank16.unkA,
            g_Stage16SpriteBank16.unk0, 1);
        self->unk0 = sprite;
        if (self->params == 0) {
            self->animCurFrame = 10;
        } else {
            self->animCurFrame = 5;
        }
        func_0600AFA8(sprite, g_Stage16SpriteBank16Frames[self->animCurFrame]);
        sprite->zPriority = 0x6A;
        self->step = 0x100;
        func_06079BB4(self);
    }
}
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DC4C0, func_060DC4C0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DC60C, func_060DC60C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DC734, func_060DC734);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DC894, func_060DC894);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DC9E0, func_060DC9E0);
void func_060DCC58(void) {}

const u16 pad_060DCC62[] = {
    0x0000, 0x0415, 0x1010, 0x10FF, 0x0000, 0x0412, 0x1010, 0x10FF,
    0x0000, 0x0411, 0x1010, 0x10FF, 0x0000, 0x0417, 0x1010, 0xFF00,
    0x0009, 0x0414, 0x1010, 0xFF00, 0x0009, 0x0412, 0x1510, 0xFF00,
    0x0009, 0x0411, 0x1010, 0xFF00, 0x0009, 0x0415, 0x10FF, 0x0000,
    0x0009, 0x0412, 0x15FF, 0x0000, 0x0009, 0x0411, 0xFF00,
};
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DCCB0, func_060DCCB0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DCDBC, func_060DCDBC);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DCE98, func_060DCE98);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DD6F4, func_060DD6F4);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DE3D4, func_060DE3D4);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DE714, func_060DE714);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DED28, func_060DED28);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DF398, func_060DF398);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DF3F0, func_060DF3F0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DF7A8, func_060DF7A8);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DF830, func_060DF830);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60DFF04, func_060DFF04);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E006C, func_060E006C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E01D4, func_060E01D4);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E02C0, func_060E02C0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E042C, func_060E042C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E0560, func_060E0560);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E067C, func_060E067C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E075C, func_060E075C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E0A48, func_060E0A48);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E0F20, func_060E0F20);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E102C, func_060E102C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E1434, func_060E1434);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E17EC, func_060E17EC);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E1928, func_060E1928);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E25F4, func_060E25F4);
u16 func_060E270C(s32 arg0, s32 arg1) {
    u16 var_r0;

    g_Player.unk7A = 1;
    if (((u16)(s16)g_Entities->step != 0) ||
        (var_r0 = (u16)(s16)g_Entities->step_s, var_r0 != 1) ||
        (g_Entities->posX.i.hi < arg0) || (g_Entities->posX.i.hi > arg1)) {
        var_r0 = 0;
    }
    return var_r0;
}
void func_060E2750(void) {
    g_Player.padSim = PAD_UP;
    g_Player.demo_timer = 1;
}
void func_060E2770(Entity* self) {
    Primitive* prim = self->ext.save.unk10;
    s32 i;

    for (i = 0; i < 9; i++) {
        prim->x3 = 0;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E279C, func_060E279C);
extern void func_060E2BF0(s32, s32);
extern void func_060E2DB0(s32, s32, s32);
extern void func_060E2EFC(s32, s32, s32);

void func_060E2BA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_060E2BF0(arg1, arg3);
    func_060E2DB0(arg1, arg2, arg3);
    func_060E2EFC(arg0, arg1, arg3);
}
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E2BF0, func_060E2BF0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E2DB0, func_060E2DB0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E2EFC, func_060E2EFC);
extern void func_060E323C(s32 arg0, s32 arg1);
extern void func_060E330C(s32 arg0, s32 arg1, s32 arg2);

void func_060E3200(s32 arg0, s32 arg1, s32 arg2) {
    func_060E323C(arg1, arg2);
    func_060E330C(arg0, arg1, arg2);
}
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E323C, func_060E323C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E330C, func_060E330C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E3478, func_060E3478);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E34CC, func_060E34CC);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E3D00, func_060E3D00);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E3FC8, func_060E3FC8);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E401C, func_060E401C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E40F4, func_060E40F4);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E411C, func_060E411C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E4210, func_060E4210);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E49F0, func_060E49F0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E4AEC, func_060E4AEC);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E4C74, func_060E4C74);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E4CF4, func_060E4CF4);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E5258, func_060E5258);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E53E0, func_060E53E0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E558C, func_060E558C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E55B0, func_060E55B0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E636C, func_060E636C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E63A8, func_060E63A8);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E6A6C, func_060E6A6C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E6C88, func_060E6C88);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E6D90, func_060E6D90);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E6DB8, func_060E6DB8);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E6DDC, func_060E6DDC);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E72FC, func_060E72FC);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E73FC, func_060E73FC);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E7C60, func_060E7C60);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E7EA8, func_060E7EA8);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E7ED0, func_060E7ED0);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E7FC4, func_060E7FC4);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E86BC, func_060E86BC);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E887C, func_060E887C);
INCLUDE_ASM("asm/saturn/stage_16/f_nonmat", f60E8AC0, func_060E8AC0);
