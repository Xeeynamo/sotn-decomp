// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_RSTAGE16_H
#define SATURN_RSTAGE16_H

// Overlays run on top of the resident zero and game modules.
#include "game.h"
#include "sattypes.h"
#include "stage_data.h"

void CheckCollision(s32 x, s32 y, Collider* result, u16 flags);
void MoveEntity(Entity* self);
void func_06079BE4(Entity* self);
#include "shared_sprite_banks.h"

/* Declarations moved here by tools/saturn/move_declarations.py */
extern EntityEntry g_RStage16EntityEntry41;
extern EntityEntry g_RStage16EntityEntry40;
extern EntityEntry g_RStage16EntityEntry39;
extern EntityEntry g_RStage16EntityEntry38;
extern EntityEntry g_RStage16EntityEntry37;
extern EntityEntry g_RStage16EntityEntry35;
extern EntityEntry g_RStage16EntityEntry36;
extern EntityEntry g_RStage16EntityEntry34;
extern EntityEntry g_RStage16EntityEntry33;
extern EntityEntry g_RStage16EntityEntry32;
extern EntityEntry g_RStage16EntityGargoyle;
extern EntityEntry g_RStage16EntityEntry30;
extern EntityEntry g_RStage16EntityEntry29;
extern EntityEntry g_RStage16EntityEntry28;
extern EntityEntry g_RStage16EntityWight;
extern EntityEntry g_RStage16EntityEntry26;
extern EntityEntry g_RStage16EntityEntry25;
extern EntityEntry g_RStage16EntityEntry24;
extern EntityEntry g_RStage16EntityWraith;
extern EntityEntry g_RStage16EntityEntry22;
extern EntityEntry g_RStage16EntityEntry21;
extern EntityEntry g_RStage16EntityEntry20;
extern EntityEntry g_RStage16EntityEntry15;
extern EntityEntry g_RStage16EntityEntry08;
extern EntityEntry g_RStage16EntityEntry14;
extern EntityEntry g_RStage16EntityEntry12;
extern EntityEntry g_RStage16EntityEntry06;
extern EntityEntry g_RStage16EntityEntry19;
extern EntityEntry g_RStage16EntityEntry18;
extern EntityEntry g_RStage16EntityEntry05;
extern EntityEntry g_RStage16EntityEntry01;
extern EntityEntry g_RStage16EntityEntry03;
extern EntityEntry g_RStage16EntityEntry04;
extern EntityEntry g_RStage16EntityEntry13;
extern EntityEntry g_RStage16EntityEntry11;
extern EntityEntry g_RStage16EntityEntry10;
extern EntityEntry g_RStage16EntityEntry09;
extern EntityEntry g_RStage16EntityEntry02;
extern EntityEntry g_RStage16EntityEntry16;
extern EntityEntry g_RStage16EntityEntry17;
extern EntityEntry g_RStage16EntityEntry00;
extern SaturnRoomPriorities g_RStage16RoomPriorities[];
extern SaturnRoomGraphics g_RStage16RoomGraphics[];
extern SaturnRoomLayerSetup g_RStage16LayerSetup[];
extern SaturnLayerMapOffsets g_RStage16LayerMapOffsets[];
extern SaturnLayerCompressedSizes g_RStage16LayerCompressedSizes[];
extern SaturnRoomHeader g_RStage16Rooms[];
extern LayoutEntity* g_RStage16LayoutVertical[];
extern LayoutEntity* g_RStage16LayoutHorizontal[];
extern void* g_RStage16SpriteBanks[];
extern EntityEntry* g_RStage16EntityUpdates[];
extern LayoutEntity g_RStage16LayoutHorizontal02[];
extern LayoutEntity g_RStage16LayoutHorizontal01[];
extern LayoutEntity g_RStage16LayoutHorizontal00[];
extern LayoutEntity g_RStage16LayoutHorizontal52[];
extern LayoutEntity g_RStage16LayoutHorizontal51[];
extern LayoutEntity g_RStage16LayoutHorizontal50[];
extern LayoutEntity g_RStage16LayoutHorizontal48[];
extern LayoutEntity g_RStage16LayoutHorizontal49[];
extern u8 g_RStage16SpriteBank23[];
extern u8 g_RStage16SpriteBank22[];
extern SaturnSpriteResource g_RStage16SpriteBankGargoyle[];
extern SaturnSpriteResource g_RStage16SpriteBankWight;
extern u8 g_RStage16SpriteBankWraith[];
extern u8 g_RStage16SpriteBank18[];
extern u8 g_RStage16SpriteBank17[];
extern SaturnSpriteResource g_RStage16SpriteBank16;
extern LayoutEntity g_RStage16LayoutVertical02[];
extern LayoutEntity g_RStage16LayoutVertical01[];
extern LayoutEntity g_RStage16LayoutVertical00[];
extern LayoutEntity g_RStage16LayoutVertical52[];
extern LayoutEntity g_RStage16LayoutVertical51[];
extern LayoutEntity g_RStage16LayoutVertical50[];
extern LayoutEntity g_RStage16LayoutVertical48[];
extern LayoutEntity g_RStage16LayoutVertical49[];
void DestroyEntity();
void PlaySfx(s32 sfxId);
void SetStep(u8 step);
void SyncSpriteObjectPosUnchecked(Entity* self, s16* offset);
void func_0600B004(SpriteObject* sprite, u32 imageIndex);
void func_06079BB4(Entity* self);
u8 func_06079DEC(void* self, void* sensors);
u16 func_06079F60(void* self, void* sensors, int count);
void func_060DF8AC(Entity* self);
void func_060E1CB4(s32 arg0, s32 arg1);
void func_060E1E74(s32 arg0, s32 arg1, s32 arg2);
void func_060E1FC0(s32 arg0, s32 arg1, s32 arg2);
void func_060E2300(s32 scale, s32 arg1);
void func_060E23D0(s32 arg0, s32 arg1, s32 arg2);
void SetCurrentMatrixBinAngle(s32* pos, s32* angle);
void TransformAndProjectPoints(
    s32* src, s32* dst, s32 count, MthMatrixTbl* matrixTbl);
extern MthMatrixTbl DAT_06061DF0;
extern s32 DAT_060485e0[];
extern s32 DAT_060EA000[];
extern s32 DAT_060EFCC0[];
extern s32 DAT_060EFCD0[];
extern SaturnSpriteFrameHeader* DAT_060E8898[];
extern s16 DAT_060E9AE0[];
extern s16 DAT_060E9CFC[];
extern s16 DAT_060ED9FA[2];
extern u32 DAT_060EDDE4[];
extern SaturnSpriteImage DAT_060EDE4C[];
extern u32 DAT_060EEFD0[];
extern u8 DAT_060EF0C0[];
extern s16 DAT_060EDEBC;
extern u32 DAT_060EF2B4;
extern u32 DAT_060EF2BC;
extern u8 DAT_060EDA34[];
extern s16 DAT_060EDA60[];
s32 AnimateEntityWithSpriteData(
    Entity* entity, const u8 frames[], const u32 spriteFrames[]);
SpriteObject* CreateSpriteObject(
    u16 charBase, u16 clutBase, SaturnSpriteImage* images, s32 maxParts);
/* End moved declarations */

void EntityDestructAnim(Entity* self);
extern s16 g_ExplosionVariantSizes[];

#endif
