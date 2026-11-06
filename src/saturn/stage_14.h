// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_STAGE_14_H
#define SATURN_STAGE_14_H

#include "game.h"
#include "sattypes.h"
#include "shared_sprite_banks.h"
#include <saturn_sprite.h>
#include "stage_data.h"

void SyncSpriteObjectPosUnchecked(Entity* self, s16* offset);
void CheckCollision(s32 x, s32 y, Collider* result, u16 flags);
void MoveEntity(Entity* self);
void FallEntity(Entity* self);
void SyncSpriteObjectPos(Entity* self);
void func_0600B004(SpriteObject* sprite, void* frame);
void PlaySfx(s32 sfxId);
void SetStep(u8 step);
void DestroyEntity(Entity* entity);

typedef struct {
    u16 indices[9];
    u16 padding;
} Stage14SubweaponIndices;
extern Stage14SubweaponIndices g_Stage14AlucardSubweaponIndices;

void func_060DC06C(Entity* self);
void func_060DC5A0(Entity* self);
void func_060DC66C(Entity* self);
void func_060DC920(Entity* self);
void func_060DDC64(Entity* self);
void func_060DE578(Entity* self);
void func_060DE850(Entity* self);
void func_060DE970(Entity* self);
void func_060DEAE4(Entity* self);
void func_060DEDF8(Entity* self);
void func_060DF654(Entity* self);
void func_060DFB40(Entity* self);
void func_060E0674(Entity* self);
void func_060E0774(Entity* self);
void func_060E0C88(Entity* self);
void func_060E1790(Entity* self);
void func_060E1E64(Entity* self);
void func_060E1FCC(Entity* self);
void func_060E2134(Entity* self);
void EntityDestructAnim(Entity* self);
void func_060E238C(Entity* self);
void func_060E26BC(Entity* self);
void func_060E29A8(Entity* self);
void func_060E2E80(Entity* self);
void func_060E2F8C(Entity* self);
void func_060E32AC(Entity* self);
void func_060E5190(Entity* self);
void func_060E5A30(Entity* self);
void func_060E5DF0(Entity* self);
void func_060E5F50(Entity* self);
void func_060E615C(Entity* self);
void func_060E6300(Entity* self);
void func_060E6498(Entity* self);
void func_060E664C(Entity* self);

extern EntityEntry g_Stage14EntityEntry01;
extern EntityEntry g_Stage14EntityEntry02;
extern EntityEntry g_Stage14EntityEntry03;
extern EntityEntry g_Stage14EntityEntry04;
extern EntityEntry g_Stage14EntityEntry05;
extern EntityEntry g_Stage14EntityEntry06;
extern EntityEntry g_Stage14EntityEntry08;
extern EntityEntry g_Stage14EntityEntry09;
extern EntityEntry g_Stage14EntityEntry10;
extern EntityEntry g_Stage14EntityEntry11;
extern EntityEntry g_Stage14EntityEntry12;
extern EntityEntry g_Stage14EntityEntry13;
extern EntityEntry g_Stage14EntityEntry14;
extern EntityEntry g_Stage14EntityEntry16;
extern EntityEntry g_Stage14EntityEntry17;
extern EntityEntry g_Stage14EntityEntry18;
extern EntityEntry g_Stage14EntityEntry19;
extern EntityEntry g_Stage14EntityEntry20;
extern EntityEntry g_Stage14EntityEntry21;
extern EntityEntry g_Stage14EntityEntry22;
extern EntityEntry g_Stage14EntityEntry24;
extern EntityEntry g_Stage14EntityEntry25;
extern EntityEntry g_Stage14EntityEntry26;
extern EntityEntry g_Stage14EntityEntry27;
extern EntityEntry g_Stage14EntityEntry29;
extern EntityEntry g_Stage14EntityEntry30;
extern EntityEntry g_Stage14EntityEntry31;
extern EntityEntry g_Stage14EntityEntry32;
extern EntityEntry g_Stage14EntityEntry33;
extern EntityEntry g_Stage14EntityEntry34;
extern EntityEntry g_Stage14EntityEntry35;
extern EntityEntry g_Stage14EntityEntry36;
extern EntityEntry g_Stage14EntityMariaBoss;
extern EntityEntry g_Stage14EntityMariaCutscene;

extern SaturnSpriteResource g_Stage14SpriteBank16;
extern SaturnSpriteResource g_Stage14SpriteBank17;
extern SaturnSpriteResource g_Stage14SpriteBank18;
extern SaturnSpriteResource g_Stage14SpriteBank19;
extern SaturnSpriteResource g_Stage14SpriteBank20;
extern SaturnSpriteResource g_Stage14SpriteBank21;
extern SaturnSpriteResource g_Stage14SpriteBank22;
extern SaturnSpriteFrameHeader* g_Stage14SpriteBank16Frames[];
extern SaturnSpriteFrameHeader* g_Stage14SpriteBank17Frames[];
extern SaturnSpriteFrameHeader* g_Stage14SpriteBank20Frames[];
extern SaturnSpriteFrameHeader* g_Stage14SpriteBank21Frames[];
extern SaturnSpriteFrameHeader* g_Stage14SpriteBank22Frames[];
extern u16 g_Stage14SpriteBank21Palette[];
extern SaturnSpriteImage g_Stage14SpriteBank21Images[];
extern u16 g_Stage14SpriteBank22Palette[];
extern SaturnSpriteImage g_Stage14SpriteBank22Images[];
extern u16 g_Stage14SpriteBank18PortraitColors[];
extern u16 g_Stage14SpriteBank19PortraitColors[];

extern LayoutEntity g_Stage14LayoutHorizontal00[];
extern LayoutEntity g_Stage14LayoutHorizontal01[];
extern LayoutEntity g_Stage14LayoutHorizontal02[];
extern LayoutEntity g_Stage14LayoutHorizontal48[];
extern LayoutEntity g_Stage14LayoutHorizontal49[];
extern LayoutEntity g_Stage14LayoutHorizontal50[];
extern LayoutEntity g_Stage14LayoutHorizontal51[];
extern LayoutEntity g_Stage14LayoutHorizontal52[];
extern LayoutEntity g_Stage14LayoutHorizontalUnused1[];
extern LayoutEntity g_Stage14LayoutHorizontalUnused2[];
extern LayoutEntity g_Stage14LayoutHorizontalUnused3[];
extern LayoutEntity g_Stage14LayoutHorizontalUnused4[];
extern LayoutEntity g_Stage14LayoutHorizontalUnused5[];
extern LayoutEntity g_Stage14LayoutVertical00[];
extern LayoutEntity g_Stage14LayoutVertical01[];
extern LayoutEntity g_Stage14LayoutVertical02[];
extern LayoutEntity g_Stage14LayoutVertical48[];
extern LayoutEntity g_Stage14LayoutVertical49[];
extern LayoutEntity g_Stage14LayoutVertical50[];
extern LayoutEntity g_Stage14LayoutVertical51[];
extern LayoutEntity g_Stage14LayoutVertical52[];
extern LayoutEntity g_Stage14LayoutVerticalUnused1[];
extern LayoutEntity g_Stage14LayoutVerticalUnused2[];
extern LayoutEntity g_Stage14LayoutVerticalUnused3[];
extern LayoutEntity g_Stage14LayoutVerticalUnused4[];
extern LayoutEntity g_Stage14LayoutVerticalUnused5[];

extern EntityEntry* g_Stage14EntityUpdates[];
extern void* g_Stage14SpriteBanks[];
extern LayoutEntity* g_Stage14LayoutHorizontal[];
extern LayoutEntity* g_Stage14LayoutVertical[];
extern u8 g_Stage14Rooms[];
extern SaturnLayerCompressedSizes g_Stage14LayerCompressedSizes[];
extern SaturnLayerMapOffsets g_Stage14LayerMapOffsets[];
extern SaturnRoomLayerSetup g_Stage14LayerSetup[];
extern SaturnRoomGraphics g_Stage14RoomGraphics[];
extern SaturnRoomPriorities g_Stage14RoomPriorities[];

extern char g_Stage14ObtainedText[];
extern char g_Stage14GoldText1[];
extern char g_Stage14GoldText25[];
extern char g_Stage14GoldText50[];
extern char g_Stage14GoldText100[];
extern char g_Stage14GoldText250[];
extern char g_Stage14GoldText400[];
extern char g_Stage14GoldText700[];
extern char g_Stage14GoldText1000[];
extern char g_Stage14GoldText2000[];
extern char g_Stage14GoldText5000[];

void SetEntityCollisionTiles(Entity* arg0);
void EntityDestructAnim(Entity* self);
void SpawnDestructAnim(
    Entity* self, u8 count, u8 params, s16 x, s16 y, u8 variant, s16 xStep);
extern s16 g_ExplosionVariantSizes[];
extern u16 g_Stage14AlucardSubweaponIds[];
extern s16 g_Stage14MariaBossSensors[];
s32 func_060E12F8(Entity* entity);
void func_060DEC10(u16 arg0);
void func_060DED1C(u16 cardIndex);
void func_060E302C(StatusFlagContext* context);
void func_060E6130(StatusFlagContext* context);

typedef struct {
    u8 frameHitbox[290];
    u16 anim_060E8DFA[25];
    u16 anim_060E8E2C[9];
    u16 anim_060E8E3E[19];
    u16 anim_060E8E64[21];
    u16 anim_060E8E8E[11];
    u16 anim_060E8EA4[19];
    u16 anim_060E8ECA[13];
    u16 anim_060E8EE4[7];
    u16 anim_060E8EF2[11];
    u16 anim_060E8F08[13];
    u16 anim_060E8F22[27];
    u16 anim_060E8F58[17];
    u16 anim_060E8F7A[23];
    u16 anim_060E8FA8[13];
    u16 anim_060E8FC2[21];
    u16 anim_060E8FEC[17];
    u16 anim_060E900E[19];
    u16 anim_060E9034[13];
    u16 anim_060E904E[9];
    u16 anim_060E9060[86];
    u16 anim_060E910C[57];
    u16 anim_060E917E[21];
    u16 anim_060E91A8[73];
    u16 anim_060E923A[89];
    u16 anim_060E92EC[17];
    u16 anim_060E930E[89];
    u16 anim_060E93C0[16];
    u16 anim_060E93E0[21];
    u16 anim_060E940A[29];
} Stage14MariaBossAnims;

extern Stage14MariaBossAnims g_Stage14MariaBossAnims;
extern s16 g_Stage14MariaBossData_060E8B24[4];
extern s16 g_Stage14MariaBossData_060E8B2C[12];
extern s16 g_Stage14MariaBossData_060E8B44[6];
extern s8 g_Stage14MariaBossHitboxes[][4];

extern u32 g_Stage14MariaBossTrigger[];

#endif
