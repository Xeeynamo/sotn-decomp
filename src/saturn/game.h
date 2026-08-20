// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef GAME_H
#define GAME_H

// game runs on top of the resident zero module.
#include "zero.h"
#include "sattypes.h"
#include <saturn_sprite.h>
#include "inc_asm.h"

#define DAMAGE_FLAG_NORMAL 0x0000
#define DAMAGE_FLAG_CRITICAL 0x4000
#define DAMAGE_FLAG_ABSORB 0x8000
#define DAMAGE_FLAG_IMMUNE 0xC000

#define E_EXPLOSION 2
#define E_PRIZE_DROP 3
#define E_SOUL_STEAL_ORB 7
#define E_EQUIP_ITEM_DROP 10
#define E_ENEMY_BLOOD 13

extern EnemyDef g_EnemyDefs[];

typedef enum {
    DAMAGEKIND_0,
    DAMAGEKIND_1,
    DAMAGEKIND_2,
    DAMAGEKIND_3,
    DAMAGEKIND_4,
    DAMAGEKIND_5,
    DAMAGEKIND_6,
    DAMAGEKIND_7,
    DAMAGEKIND_8,
    DAMAGEKIND_9,
    DAMAGEKIND_10,
    DAMAGEKIND_11,
    DAMAGEKIND_12,
    DAMAGEKIND_13,
    DAMAGEKIND_14,
    DAMAGEKIND_15,
    DAMAGEKIND_16,
    DAMAGEKIND_17,
    DAMAGEKIND_18,
} DamageKind;

typedef struct {
    u32 effects;    // Curse, poison, fire, ice, etc.
    u32 damageKind; // informed by "dam_kind:%04x\n"
    s32 damageTaken;
    u32 unkC;
} DamageParam;

// items.h
typedef enum ItemSlots {
    LEFT_HAND_SLOT,
    RIGHT_HAND_SLOT,
    HEAD_SLOT,
    ARMOR_SLOT,
    CAPE_SLOT,
    ACCESSORY_1_SLOT,
    ACCESSORY_2_SLOT,
    NUM_ITEM_SLOTS,
} ItemSlots;

typedef enum {
    NUM_HAND_ITEMS = 0xB0,
} HandItems;

typedef enum {
    NUM_BODY_ITEMS = 92,
} BodyItems;

/* Declarations moved here by tools/saturn/move_declarations.py */
void func_0606F1C8(Entity* entity);
void func_0606C594(void);
void func_0606C774(void);
void func_06074470(void);
void func_0606C064(void);
void func_0606BEE4(void);
void func_0606BB4C(void);
void func_0606B760(void);
void LoadSubDisplayFiles(void);
void func_8011A9D8(void);
void ModeGame(void);
void func_0607AC40(Entity* self);
extern const char g_StatusMenuUnknown[];
extern const char g_StatusMenuButtonAssignment[];
extern const char g_StatusMenuReversibleCloak[];
extern const char g_StatusMenuCustomColor[];
extern const char g_StatusMenuWindowColor[];
extern const char g_StatusMenuElapsedTime[];
extern const char g_StatusMenuAttack[];
extern const char g_StatusMenuDefense[];
extern const char g_StatusMenuSpecialMoveList[];
extern const char g_StatusMenuEquipment[];
extern const char g_StatusMenuSpecialMoves[];
extern const char g_StatusMenuRelics[];
extern const char g_StatusMenuSystem[];
extern const char g_StatusMenuDagger[];
extern const char g_StatusMenuSword[];
extern const char g_StatusMenuThrowingSword[];
extern const char g_StatusMenuFist[];
extern const char g_StatusMenuClub[];
extern const char g_StatusMenuTwoHandedSword[];
extern const char g_StatusMenuFood[];
extern const char g_StatusMenuBomb[];
extern const char g_StatusMenuProjectile[];
extern const char g_StatusMenuShield[];
extern const char g_StatusMenuMedicine[];
extern const char g_StatusMenuRightHandWeapon[];
extern const char g_StatusMenuLeftHandWeapon[];
extern const char g_StatusMenuHolder[];
extern const char g_StatusMenuHelm[];
extern const char g_StatusMenuArmor[];
extern const char g_StatusMenuCape[];
extern const char g_StatusMenuOther[];
extern const char g_StatusMenuFamiliar[];
extern const char g_StatusMenuFamiliarList[];
extern s32 g_CapePaletteDefs[];
extern u16 D_800A37F4[][4];
extern u16 g_EquippedCapePalette[4];
extern u32 g_FontGlyphDataSizes[];
extern s32 DAT_06086210;
extern s32 g_EquipOrderType;
extern s32 g_NewDefenseEquip;
extern s32 g_NewAttackLeftHand;
extern s32 g_NewAttackRightHand;
extern s32 g_NewPlayerStatsTotal[];
extern s32 g_MenuPageScrollActive;
void SetVdp2DisplayMode(s32);
extern s16 DAT_06086220[];
extern s16 DAT_060862a4;
extern s16 g_ButtonMask[];
void CheckWeaponCombo(void);
void func_06073280(void);
extern s32 DAT_0608629c;
extern s32 DAT_06086288;
extern s32 DAT_06086270;
extern s32 DAT_06086258;
extern s32 prevMusicId;
extern s32 g_StatusWindowColorBlue;
extern s32 g_StatusWindowColorGreen;
extern s32 g_StatusWindowColorRed;
void func_800F2404(s32);
void SetDefaultSCLPriority(s32);
void InitRoomEntities(s32);
extern s32 D_801375A4;
extern s32 D_8013759C;
extern RoomLoadDefHolder D_801375BC;
extern s32 D_801375A0;
extern s32 D_801375A8;
extern s32 DAT_060860c0;
extern s32 DAT_060860bc;
extern u8 g_LayoutObjPosVertical;
extern u8 g_LayoutObjPosHorizontal;
extern u16* g_LayoutObjVertical;
extern u16* g_LayoutObjHorizontal;
extern u16 g_HudSpriteBlend[];
extern u8 g_HudSpriteH[];
extern u8 g_HudSpriteW[];
extern u8 g_HudSpriteY[];
extern u8 g_HudSpriteX[];
extern u8 DAT_06085d3c[];
extern SaturnSpriteResource* DAT_06086388;
void func_0607672C(void);
void func_06075838(void);
extern s32 TimeAttackController(s32 eventId, s32 action);
extern char* g_GTIClubCode;
extern char* g_AxeArmorCode;
extern char* g_LuckCode;
extern s32 D_80139008;
extern s32 D_801397FC;
extern u8 g_JewelSwordAttackBonus[];
extern RoomTeleport g_RoomTeleports[];
extern RoomBossTeleport g_RoomBossTeleports[];
void func_0606D6DC(void);
void func_0606D798(void);
extern s32 g_ExpNext[];
extern s32 g_LevelHPIncrease[];
void ApplyJosephsCloakPalette(void);
void ResetNewGameSettings(void);
extern s32 DAT_0608609c;
void func_060728B4(void);
void SubDisp(void);
void RunMainEngine(void);
void UpdatePlayTimer(void);
void ResetPlayState(u16);
s32 CalcAttack(s32 equipId, s32 otherEquipId);
void UpdateEquipStatBonuses(void);
extern void SyncSpriteObjectPos(Entity* self);
extern u32* d_06086250;
extern u32* d_06086234;
s32 func_0606F21C(s32 eventId, s32 action);
extern s32 func_0606F328(s32 arg0);
extern Primitive g_PrimBuf[];
extern PlayerHud g_PlayerHud;
extern RelicDesc g_RelicDefs[];
extern s32 D_801375C8;
extern SubweaponDef g_SubwpnDefs[];
extern s32* D_801375D8;
extern s32 D_801375D4;
extern s32 D_801375CC;
extern s32 D_8013B5E8;
extern s32 g_StatBuffTimers[];
extern s32 D_80137968;
extern s32 D_80137964;
extern s32 D_80137960;
extern Accessory g_AccessoryDefs[];
extern SpellDef g_SpellDefs[];
extern Equipment g_EquipDefs[];
extern void func_06079BB4(Entity* self);
extern s32 DAT_06086134;
extern s32 DAT_06086130;
extern s32 DAT_0608612c;
extern s32 DAT_06086128;
extern u8 DAT_0608FFF8[];
extern s16 g_SineTable[];
void CreateEntityFromEntity(u16 entityId, Entity* source, Entity* entity);
extern s32 DAT_06086390;
extern SpritePart g_SpritePartPool[SPRITE_PART_MAX];       /* 0x0608D7F8 */
extern SpriteObject g_SpriteObjectPool[SPRITE_OBJECT_MAX]; /* 0x0608AFF8 */
/* End moved declarations */

#endif
