// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"

#include "stage_15.h"
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC040, func_060DC040);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC1A8, func_060DC1A8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC328, func_060DC328);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC428, func_060DC428);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC4B8, func_060DC4B8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC604, func_060DC604);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC7E4, func_060DC7E4);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DC838, func_060DC838);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DCDF8, func_060DCDF8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DCF90, func_060DCF90);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DD37C, func_060DD37C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DD524, func_060DD524);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DD698, func_060DD698);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DD898, func_060DD898);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DDA10, func_060DDA10);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DDB74, func_060DDB74);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DDCE8, func_060DDCE8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DDD94, func_060DDD94);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DDE44, func_060DDE44);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DDFB0, func_060DDFB0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE058, func_060DE058);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE140, func_060DE140);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE264, func_060DE264);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE2F4, func_060DE2F4);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE464, func_060DE464);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE500, func_060DE500);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE58C, func_060DE58C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE670, func_060DE670);
extern void func_06079BB4(Entity* self);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);
extern u32 g_Stage15SpriteBank16Frames[];

void func_060DE6CC(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, g_Stage15SpriteBank16Frames[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE704, func_060DE704);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DE964, func_060DE964);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DEC48, func_060DEC48);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DECE0, func_060DECE0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DF160, func_060DF160);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DF204, func_060DF204);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DF354, func_060DF354);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DF62C, func_060DF62C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DF77C, func_060DF77C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DF938, func_060DF938);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DF9B0, func_060DF9B0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DFA1C, func_060DFA1C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DFA98, func_060DFA98);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DFB74, func_060DFB74);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DFC08, func_060DFC08);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DFCE8, func_060DFCE8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DFDF4, func_060DFDF4);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60DFED0, func_060DFED0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E072C, func_060E072C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E140C, func_060E140C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E174C, func_060E174C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E1D60, func_060E1D60);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E23D0, func_060E23D0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E2428, func_060E2428);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E27E0, func_060E27E0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E2868, func_060E2868);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E2F3C, func_060E2F3C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E30A4, func_060E30A4);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E320C, func_060E320C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E32F8, func_060E32F8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E3464, func_060E3464);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E3598, func_060E3598);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E36B4, func_060E36B4);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E3794, func_060E3794);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E3A80, func_060E3A80);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E3F58, func_060E3F58);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E4064, func_060E4064);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E458C, func_060E458C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E4918, func_060E4918);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E49D4, func_060E49D4);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E49FC, func_060E49FC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E56C8, func_060E56C8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E57E0, func_060E57E0);
void func_060E5824(void) {
    g_Player.padSim = 0x1000;
    g_Player.demo_timer = 1;
}
void func_060E5844(Entity* self) {
    Primitive* prim = self->ext.save.unk10;
    s32 i;

    for (i = 0; i < 9; i++) {
        prim->x3 = 0;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E5870, func_060E5870);
extern void func_060E5CC4(s32 arg0, s32 arg1);
extern void func_060E5E84(s32 arg0, s32 arg1, s32 arg2);
extern void func_060E5FD0(s32 arg0, s32 arg1, s32 arg2);

void func_060E5C74(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_060E5CC4(arg1, arg3);
    func_060E5E84(arg1, arg2, arg3);
    func_060E5FD0(arg0, arg1, arg3);
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E5CC4, func_060E5CC4);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E5E84, func_060E5E84);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E5FD0, func_060E5FD0);
extern void func_060E6310(s32 arg0, s32 arg1);
extern void func_060E63E0(s32 arg0, s32 arg1, s32 arg2);

void func_060E62D4(s32 arg0, s32 arg1, s32 arg2) {
    func_060E6310(arg1, arg2);
    func_060E63E0(arg0, arg1, arg2);
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E6310, func_060E6310);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E63E0, func_060E63E0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E654C, func_060E654C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E65CC, func_060E65CC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E6B30, func_060E6B30);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E6CB8, func_060E6CB8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E6E64, func_060E6E64);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E6EA0, func_060E6EA0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E7564, func_060E7564);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E7780, func_060E7780);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E7888, func_060E7888);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E78B8, func_060E78B8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E8A7C, func_060E8A7C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E8BBC, func_060E8BBC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E8D50, func_060E8D50);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E8FD4, func_060E8FD4);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E9144, func_060E9144);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E94A0, func_060E94A0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E95E8, func_060E95E8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E991C, func_060E991C);
extern void func_06079BB4(Entity* self);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);
extern u32 DAT_060F7EFC[];

void func_060E996C(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F7EFC[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E99A4, func_060E99A4);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E9A14, func_060E9A14);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E9AAC, func_060E9AAC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E9AEC, func_060E9AEC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E9CA0, func_060E9CA0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E9D38, func_060E9D38);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60E9E44, func_060E9E44);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EAA68, func_060EAA68);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EAAA8, func_060EAAA8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EACDC, func_060EACDC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EB2B8, func_060EB2B8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EB728, func_060EB728);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EB7EC, func_060EB7EC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EB824, func_060EB824);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EB9AC, func_060EB9AC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EBA00, func_060EBA00);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EBA98, func_060EBA98);
extern void func_06079BB4(Entity* self);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);
extern u32 DAT_060F86CC[];

void func_060EBAF4(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F86CC[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EBB2C, func_060EBB2C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EBC24, func_060EBC24);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60ECB7C, func_060ECB7C);
void func_060ECCE8(StatusFlagContext* context) {
    if (context->enabled != 0) {
        *context->flags |= FLAG_UNK_10;
    } else {
        *context->flags &= ~FLAG_UNK_10;
    }
}
extern void func_06079BB4(Entity* self);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);
extern u32 DAT_060F8B10[];

void func_060ECD14(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F8B10[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60ECD4C, func_060ECD4C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60ECDBC, func_060ECDBC);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60ECE0C, func_060ECE0C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60ED1C0, func_060ED1C0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60ED848, func_060ED848);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EDA88, func_060EDA88);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EDD10, func_060EDD10);
extern void func_06079BB4(Entity* self);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);
extern u32 DAT_060F9470[];

void func_060EDF48(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060F9470[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EDF80, func_060EDF80);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EE4B8, func_060EE4B8);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EE5F4, func_060EE5F4);
extern void func_0600B004(SpriteObject* sprite, u32 imageIndex);

void func_060EE644(Entity* self) {
    func_06079BB4(self);
    func_0600B004(self->unk0, DAT_060FA59C[self->animCurFrame]);
}
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EE67C, func_060EE67C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EE6C4, func_060EE6C4);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EEE20, func_060EEE20);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EEEE4, func_060EEEE4);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EF074, func_060EF074);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EF09C, func_060EF09C);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EF0C0, func_060EF0C0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EF5E0, func_060EF5E0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EF6E0, func_060EF6E0);
INCLUDE_ASM("asm/saturn/stage_15/f_nonmat", f60EFF44, func_060EFF44);
