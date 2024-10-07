// SPDX-License-Identifier: AGPL-3.0-or-later
#include <servant.h>

s16 D_us_801735B0, D_us_801735B0_;
s16 D_us_801735B4, D_us_801735B4_;
s16 D_us_801735B8, D_us_801735B8_;
s16 D_us_801735BC, D_us_801735BC_;
s16 D_us_801735C0, D_us_801735C0_;

u32 D_us_801735C4[128];

s16 D_us_801737C4, D_us_801737C4_;
s16 D_us_801737C8, D_us_801737C8_;

s32 D_us_801737CC, D_us_801737CC_dummy, D_us_801737CC_dummy2;
s32 D_us_801737D8;
s32 D_us_801737DC;
s32 D_us_801737E0;
s32 D_us_801737E4;
s32 D_us_801737E8;
s32 D_us_801737EC;
Primitive* D_us_801737F0;
s32 D_us_801737F4;
s32 D_us_801737F8;
Primitive* D_us_801737FC; // Pointer to the current primitive being manipulated
s32 D_us_80173800;        // Index for the current primitive being manipulated
s32 D_us_80173804;        // Effect timer used to control steps and timing
s16 D_us_80173808, D_us_80173808_; // Temporary storage for X position of the
                                   // entity or primitive
s16 D_us_8017380C, D_us_8017380C_; // Temporary storage for Y position of the
                                   // entity or primitive
FamiliarStats D_us_80173810;
s32 g_IsServantDestroyed;
s32 D_us_80173820;

extern s32 D_us_801704A8;
extern AnimationFrame* D_us_80170500[];
extern s32 D_us_80170508[][3];
extern u16 D_us_80170580[32];

extern s16
    D_us_801705A0[]; // Array of X-axis offsets for positioning primitives
extern s16
    D_us_801705A8[]; // Array of Y-axis offsets for positioning primitives

void func_us_801720A4(Entity* self);
void func_us_801720AC(void);
void func_us_801720B4(void);
void func_us_801720BC(void);
void func_us_801720C4(void);
void func_us_801720CC(void);
void func_us_801720D4(void);
void func_us_801720DC(void);
void func_us_801720E4(Entity* self);
void func_us_8017246C(Entity* self);
void func_us_801728EC(void);
void func_us_801728F4(void);
void func_us_801728FC(void);
void DestroyServantEntity(Entity* self);

ServantDesc g_ServantDesc = {
    ServantInit,         UpdateServantDefault, func_us_801720A4,
    func_us_801720AC,    func_us_801720B4,     func_us_801720BC,
    func_us_801720C4,    func_us_801720CC,     func_us_801720D4,
    func_us_801720DC,    func_us_801720E4,     func_us_8017246C,
    func_us_801728EC,    func_us_801728F4,     func_us_801728FC,
    DestroyServantEntity};
