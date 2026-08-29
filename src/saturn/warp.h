// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_WARP_H
#define SATURN_WARP_H

// Overlays run on top of the resident zero and game modules.
#include "game.h"
#include "stage_data.h"
#include "sattypes.h"
#include "shared_sprite_banks.h"
#include <saturn_sprite.h>

typedef struct {
    SaturnRoomHeader rooms[18];
    u8 terminator[4];
} WarpRoomTable;

typedef struct {
    SaturnRoomLayerSetup rooms[6];
    u8 padding[2];
} WarpLayerProperties;

/* Declarations moved here by tools/saturn/move_declarations.py */
extern char g_WarpGoldText5000[];
extern char g_WarpGoldText2000[];
extern char g_WarpGoldText1000[];
extern char g_WarpGoldText700[];
extern char g_WarpGoldText400[];
extern char g_WarpGoldText250[];
extern char g_WarpGoldText100[];
extern char g_WarpGoldText50[];
extern char g_WarpGoldText25[];
extern char g_WarpGoldText1[];
void EntityWarpEnemyBlood(Entity* self);
void EntityWarpSoulStealOrb(Entity* self);
void EntityWarpGreyPuff(Entity* self);
void EntityDestructAnim(Entity* self);
void EntityWarpUnkId13(Entity* self);
void EntityWarpIntenseExplosion(Entity* self);
void EntityWarpExplosion(Entity* self);
void EntityWarpMessageBox(Entity* self);
void EntityWarpHeartDrop(Entity* self);
void EntityWarpRelicOrb(Entity* self);
void func_060DD894(Entity* self);
void func_060DD038(Entity* self);
extern EntityEntry g_WarpSmallRocksEntry;
extern EntityEntry g_WarpRoomEntry;
extern EntityEntry g_WarpGreyPuffEntry;
extern EntityEntry g_WarpExplosionVariantsEntry;
extern EntityEntry g_WarpUnkId13Entry;
extern EntityEntry g_WarpDummyEntry;
extern EntityEntry g_WarpMessageBoxEntry;
extern EntityEntry g_WarpEnemyBloodEntry;
extern EntityEntry g_WarpHeartDropEntry;
extern EntityEntry g_WarpRelicOrbEntry;
extern EntityEntry g_WarpEquipItemDropEntry;
extern EntityEntry g_WarpStageNamePopupEntry;
extern EntityEntry g_WarpSoulStealOrbEntry;
extern EntityEntry g_WarpIntenseExplosionEntry;
extern EntityEntry g_WarpRedDoorEntry;
extern EntityEntry g_WarpDamageDisplayEntry;
extern EntityEntry g_WarpPrizeDropEntry;
extern EntityEntry g_WarpExplosionEntry;
void EntityWarpDamageDisplay(Entity* self);
extern SaturnRoomPriorities g_WarpRoomPriorities[32];
extern SaturnRoomGraphics g_WarpRoomGraphics[6];
extern WarpLayerProperties g_WarpLayerProperties;
extern SaturnLayerMapOffsets g_WarpLayerMapOffsets[6];
extern SaturnLayerCompressedSizes g_WarpLayerCompressedSizes[6];
extern WarpRoomTable g_WarpRooms;
extern LayoutEntity* g_WarpLayoutVertical[53];
extern LayoutEntity* g_WarpLayoutHorizontal[53];
extern void* g_WarpSpriteBanks[18];
extern EntityEntry* g_WarpEntityUpdates[];
extern LayoutEntity g_WarpVLayout52[];
extern LayoutEntity g_WarpVLayout51[];
extern LayoutEntity g_WarpVLayout50[];
extern LayoutEntity g_WarpVLayout49[];
extern LayoutEntity g_WarpVLayout48[];
extern LayoutEntity g_WarpVLayout06[];
extern LayoutEntity g_WarpVLayout05[];
extern LayoutEntity g_WarpVLayout04[];
extern LayoutEntity g_WarpVLayout03[];
extern LayoutEntity g_WarpVLayout02[];
extern LayoutEntity g_WarpVLayout01[];
extern LayoutEntity g_WarpVLayoutEmpty[];
extern LayoutEntity g_WarpHLayout52[];
extern LayoutEntity g_WarpHLayout51[];
extern LayoutEntity g_WarpHLayout50[];
extern LayoutEntity g_WarpHLayout49[];
extern LayoutEntity g_WarpHLayout48[];
extern LayoutEntity g_WarpHLayout06[];
extern LayoutEntity g_WarpHLayout05[];
extern LayoutEntity g_WarpHLayout04[];
extern LayoutEntity g_WarpHLayout03[];
extern LayoutEntity g_WarpHLayout02[];
extern LayoutEntity g_WarpHLayout01[];
extern LayoutEntity g_WarpHLayoutEmpty[];
extern SaturnSpritePalette2 g_WarpSpriteBank16Palettes;
extern SaturnSpriteImage g_WarpSpriteBank16Images[];
extern struct SpriteParts* g_WarpSpriteBank16[];
void func_060DCAFC(Entity* self);
void func_060DC040(Entity* self);
void EntityWarpStageNamePopup(Entity* self);
void InitSolidProp(Entity* self);
void EntityWarpRedDoor(Entity* self);
extern char g_WarpObtainedText[];
extern s16 DAT_060E2218[];
extern u16 DAT_060E1FFC[];
void CheckCollision(s32 x, s32 y, Collider* res, u16 unk);
void MoveEntity(Entity* self);
void PlaySfx(s32 sfxId);
void SetStep(u8 step);
void DestroyEntity(Entity* entity);
void func_06079BE4(Entity* self);
void func_060DCE50(u16 arg0);
void func_060DCF5C(u16 arg0);
extern u8 DAT_0605CB50[];
extern u8 DAT_0608FFF8[];
extern Tilemap g_Tilemap;
void func_060DE8B4(Entity* self);
void func_060DF938(Entity* self);
void func_060E0364(Entity* self);
/* End moved declarations */

extern s16 g_ExplosionVariantSizes[];

#endif
