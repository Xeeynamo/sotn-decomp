// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"

#include "rstage15.h"

void DestroyEntity(void);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DC040, func_060DC040);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DC1A8, func_060DC1A8);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DC2A4, func_060DC2A4);
void func_060DC3A4(Entity* self) {
    SpriteObject* sprite;
    s32 frameOffset;

    if (self->step == 0) {
        TekiInit(self, 5);
        self->step++;
        sprite = CreateSpriteObject(
            g_RStage15SpriteBank16.allocationIndex,
            g_RStage15SpriteBank16.flags, g_RStage15SpriteBank16.images, 1);
        self->unk0 = sprite;
        self->animCurFrame = 0x2A;
        frameOffset = 0x2A * sizeof(SaturnSpriteFrameHeader*);
        func_0600AFA8(
            sprite,
            *(SaturnSpriteFrameHeader**)((u8*)g_RStage15SpriteBank16Frames +
                                         frameOffset));
        sprite->zPriority = 0x6A;
        self->step = 0x100;
        func_06079BB4(self);
    }
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DC434, func_060DC434);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DC580, func_060DC580);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DCA30, func_060DCA30);
void func_060DCC10(s32 unused, s16 amount) {
    g_unkGraphicsStruct.D_80097448 = amount;
    if (amount > 4) {
        g_unkGraphicsStruct.D_8009744C = amount - 4;
    } else {
        g_unkGraphicsStruct.D_8009744C = 0;
    }
    g_unkGraphicsStruct.D_80097450 = amount;
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DCC44, func_060DCC44);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DCCA4, func_060DCCA4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DCD58, func_060DCD58);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DCF08, func_060DCF08);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DD0A0, func_060DD0A0);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DD488, func_060DD488);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DD60C, func_060DD60C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DD780, func_060DD780);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DD988, func_060DD988);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DDA34, func_060DDA34);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DDB98, func_060DDB98);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DDD10, func_060DDD10);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DDDB8, func_060DDDB8);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DDE68, func_060DDE68);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DDFD4, func_060DDFD4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DE064, func_060DE064);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DE144, func_060DE144);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DE268, func_060DE268);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DE40C, func_060DE40C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DE4CC, func_060DE4CC);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DE560, func_060DE560);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DE654, func_060DE654);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DE6FC, func_060DE6FC);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DE808, func_060DE808);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DE8E4, func_060DE8E4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DF140, func_060DF140);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60DFE20, func_060DFE20);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E0160, func_060E0160);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E0774, func_060E0774);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E0DE4, func_060E0DE4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E0E3C, func_060E0E3C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E11F4, func_060E11F4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E127C, func_060E127C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E1950, func_060E1950);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E1AB8, func_060E1AB8);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E1C20, func_060E1C20);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E1D0C, func_060E1D0C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E1E78, func_060E1E78);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E1FAC, func_060E1FAC);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E20C8, func_060E20C8);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E21A8, func_060E21A8);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E2494, func_060E2494);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E296C, func_060E296C);
void func_060E2A78(void) { DestroyEntity(); }
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E2A90, func_060E2A90);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E375C, func_060E375C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E3874, func_060E3874);
void func_060E38B8(void) {
    g_Player.padSim = PAD_UP;
    g_Player.demo_timer = 1;
}
void func_060E38D8(Entity* self) {
    Primitive* prim = self->ext.save.unk10;
    s32 i;

    for (i = 0; i < 9; i++) {
        prim->x3 = 0;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E3904, func_060E3904);
extern void func_060E4064(s32 arg0, s32 arg1, s32 arg2);

void func_060E3D08(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_060E3D58(arg1, arg3);
    func_060E3F18(arg1, arg2, arg3);
    func_060E4064(arg0, arg1, arg3);
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E3D58, func_060E3D58);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E3F18, func_060E3F18);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E4064, func_060E4064);

void func_060E4368(s32 arg0, s32 arg1, s32 arg2) {
    func_060E43A4(arg1, arg2);
    func_060E4474(arg0, arg1, arg2);
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E43A4, func_060E43A4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E4474, func_060E4474);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E45E0, func_060E45E0);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);

void func_060E4630(Entity* self) {
    SyncSpriteObjectPos(self);
    func_0600B004(self->unk0, DAT_060EF1A8[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E4668, func_060E4668);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E519C, func_060E519C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E540C, func_060E540C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E56F4, func_060E56F4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E6750, func_060E6750);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E6878, func_060E6878);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E76C4, func_060E76C4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E78B4, func_060E78B4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E7AC4, func_060E7AC4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E7C3C, func_060E7C3C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E7E60, func_060E7E60);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E823C, func_060E823C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E854C, func_060E854C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E88A0, func_060E88A0);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E8A54, func_060E8A54);
extern void SyncSpriteObjectPos(Entity* self);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);
extern u32 DAT_060F2670[];

void func_060E8AA4(Entity* self) {
    SyncSpriteObjectPos(self);
    func_0600B004(self->unk0, DAT_060F2670[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E8ADC, func_060E8ADC);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E8EFC, func_060E8EFC);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E9104, func_060E9104);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E9284, func_060E9284);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E98F0, func_060E98F0);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60E9D28, func_060E9D28);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EA0B0, func_060EA0B0);
extern void func_06079BB4(Entity* self);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);
extern u32 DAT_060F2B4C[];

void func_060EA100(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F2B4C[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EA138, func_060EA138);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EA578, func_060EA578);
extern void func_06079BB4(Entity* self);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);
extern u32 DAT_060F2D68[];

void func_060EA5C8(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F2D68[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EA600, func_060EA600);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EAE6C, func_060EAE6C);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EAFF8, func_060EAFF8);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EB150, func_060EB150);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EB4A4, func_060EB4A4);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EB550, func_060EB550);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EC174, func_060EC174);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EC274, func_060EC274);
INCLUDE_ASM("asm/saturn/rstage15/f_nonmat", f60EC374, func_060EC374);
