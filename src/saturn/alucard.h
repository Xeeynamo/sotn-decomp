// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_ALUCARD_H
#define SATURN_ALUCARD_H

#include "game.h"
#include "sattypes.h"
#include <saturn_player.h>
#include <saturn_sprite.h>
#include "inc_asm.h"

void func_0600A330(void);
void* func_0600BD4C(SpriteObject* sprite);
typedef s32 (*Callback)();

// D_800ACF4C on PSX
typedef struct {
    u8 unk0;
    u8 pad1[3];
    s32 unk4;
} AlucardStateInitData;

typedef struct {
    u16 countAndFlags;
    u16 colors[3][16];
} AlucardSubPaletteData;

extern AlucardStateInitData g_AlucardStateInitData[];
extern Callback DAT_060D6018;
extern Callback DAT_060D9018;
void func_0600A31C(void);
extern s16 DAT_060CE4B2;
extern s16 DAT_060CE4B4;
extern s16 DAT_060CE972;
extern s32 DAT_060C85C4[];
extern s16 DAT_060CBE3C;
extern u8 g_AlucardFactoryAnimationLookup[];
extern u8 DAT_060C8574;
extern s16 DAT_060CBE02;
extern SaturnSpriteResource AlucardSpriteResources[13];
void LookupTblNoToVramAddr(u16 tableNo, u8* destination);
s32 func_060B9610(s16 arg0, s16 arg1);
s32 func_060B9610Healing(u16 amount, s32 kind) __asm__("_func_060B9610");
s32 func_060B9610Internal(s32 amount, s32 kind) __asm__("_func_060B9610");

/* Declarations moved here by tools/saturn/move_declarations.py */
extern const SaturnAnimationFrame g_AlucardAnimationData[];
extern SaturnPlayerGraphicsRecord g_AlucardPlayerGraphicsRecords[];
extern u8 AlucardSpriteResourceTable[];
void func_060AF654(void);
void func_060AF4A0(void);
void func_060B9340(Entity* entity);
void func_060B2E40(void);
Entity* func_060BAF44(Entity* source, u32 factoryParams, s32 arg2);
void func_060AB3A8(s32 arg);
void func_060ADD74(void);
void func_060AB44C(s32 kind, s16 invincibilityFrames);
void func_060A7D68(s32 resetAnims, s32 arg1);
void func_060B2DE4(Collider* collider);
void func_060BAE70(void);
void func_060BAD84(void);
void func_060BAB00(void);
void func_060AFA20(void);
void func_060ADF3C(u16 params);
extern u16 AlucardPkg10Palette[];
extern u16 AlucardPkg9Palette[];
extern u16 AlucardPkg8Palette[];
extern u16 AlucardPkg7Palette[];
extern u16 AlucardPkg6Palette[];
extern u16 AlucardPkg5Palette[];
extern u16 AlucardPkg4Palette[];
extern u16 AlucardPkg3Palette[];
extern u16 AlucardFx2Palette[];
extern u16 AlucardFxPalette[];
extern AlucardSubPaletteData AlucardSubPalette;
extern u16 g_AlucardPaletteShades[];
extern u16 g_AlucardPalettes[];
extern SaturnSpriteImage AlucardPkg10Images[];
extern SaturnSpriteImage AlucardPkg9Images[];
extern SaturnSpriteImage AlucardPkg8Images[];
extern SaturnSpriteImage AlucardPkg7Images[];
extern SaturnSpriteImage AlucardPkg6Images[];
extern SaturnSpriteImage AlucardPkg5Images[];
extern SaturnSpriteImage AlucardPkg4Images[];
extern SaturnSpriteImage AlucardPkg3Images[];
extern SaturnSpriteImage AlucardFx2Images[];
extern SaturnSpriteImage AlucardFxImages[];
extern SaturnSpriteImage AlucardSubImages[];
extern SaturnSpriteImage AlucardImages[];
extern s8 D_060B24B0[];
extern u16* g_AlucardEffectAnimTable[];
void func_060AF1BC(int);
void SetPlayerStep(PlayerSteps step);
void CheckCollision(s32 x, s32 y, Collider* res, u16 unk);
s32 func_060A5060(void);
s32 func_060A50E0(s32 arg0);
void func_060A55B4(s32 arg0);
void func_060A59E0(s32 arg0);
void func_060A5AF0(void);
void func_060A5B94(s32 arg0);
void SetPlayerStepNoInline(PlayerSteps step) __asm__("_func_060A5558");
void SetSpeedXNoInline(s32 velocityX) __asm__("_func_060A5574");
void func_060A56E4NoInline(s32 arg0, s32 arg1) __asm__("_func_060A56E4");
void func_060A5674NoInline(s32 anim) __asm__("_func_060A5674");
void func_060A5574(s32 velocityX);
void func_060A5674(s32 anim);
void func_060A580C(s32 arg0);
void func_0600FB0C(s32 arg0);
void PlaySfx(s32 sfxId);
void DestroyEntity();
void func_060B95C8(s32 arg0);
s32 func_060AB78C(void);
void func_060ABFA4(void);
void func_060AEFBC(void);
void func_060B071C(void);
s32 func_060BA9A0(Entity* entity, s32 arg);
void func_060B7994(void);
void func_060B7A6C(void);
long ratan2(long dx, long dy);
s32 func_0606FFC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

typedef struct {
    u32 unk0;
    s16* unk4;
    AnimationFrame* unk8;
    u32 unkC;
} EntryS060CE980;

typedef struct {
    s8 f0;
    s8 f1;
    s8 f2;
    s8 f3;
} Rec060CC9BD;

extern Point32 g_AlucardSensorsWall[];
extern Point32 g_AlucardSensorsFloor[];
extern Point32 g_AlucardSensorsCeiling[];
extern EntryS060CE980 DAT_060CE980[];
extern EntryS060CE980 DAT_060CEA70[];
extern EntryS060CE980 DAT_060CEA80[];
extern AnimationFrame AlucardFrames[];
extern u8 DAT_0607C266[];
extern s8 DAT_060CC9BC;
extern Rec060CC9BD DAT_060CC9BD[];
extern s32 DAT_060CE4F0[];
extern s8 DAT_060CE51C;
extern s8 DAT_060CE51D;
extern s8 DAT_060CE51E;
extern s32 DAT_060C84F8;
extern s32 DAT_060CC774;
extern s32 DAT_060CE490;
extern s32 DAT_060CE494;
extern s32 DAT_060CE4B8;
extern s32 DAT_060CE4BC;
extern s32 DAT_060CE4C0;
extern s16 DAT_060CC98E[];
s32 func_0607003C(void* arg0, s32 arg1, s32 arg2, s32 arg3);
void func_060B8B40(void* arg0, s16 arg1, s16 arg2);
extern s16 DAT_060CE4B0;
/* End moved declarations */

#endif
