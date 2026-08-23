// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_MARIA_H
#define SATURN_MARIA_H

// Overlays run on top of the resident zero and game modules.
#include "game.h"

#include "inc_asm.h"
#include "sattypes.h"
#include <saturn_player.h>
#include <saturn_sprite.h>
#include "shared_sprite_banks.h"

extern SubweaponDef DAT_060C1B02[];
extern s8* DAT_06085DE8[];
extern s8* DAT_06085E14[];
void func_0600B0B8(SpritePart* part, void* arg1, s32 arg2, void* arg3);

enum MariaBlueprints {
    MARIA_BP_SKID_SMOKE,
    MARIA_BP_SMOKE_PUFF,
    MARIA_BP_SUBWPN_CROSS,
    MARIA_BP_SUBWPN_CROSS_PARTICLES,
    MARIA_BP_EMBERS,
    MARIA_BP_5,
    MARIA_BP_SUBWPN_HOLYWATER,
    MARIA_BP_HOLYWATER_FIRE,
    MARIA_BP_HIT_BY_FIRE,
    MARIA_BP_HOLYWATER_FLAMES,
    MARIA_BP_WHIP,
    MARIA_BP_MULTIPLE_EMBERS,
    MARIA_BP_HYDROSTORM,
    MARIA_BP_CRASH_CROSS,
    MARIA_BP_CRASH_CROSSES_ONLY,
    MARIA_BP_NOT_IMPLEMENTED_1,
    // 0x10
    MARIA_BP_NOT_IMPLEMENTED_2,
    MARIA_BP_ARM_BRANDISH_WHIP,
    MARIA_BP_18,
    MARIA_BP_AXE,
    MARIA_BP_20,
    MARIA_BP_NOT_IMPLEMENTED_3,
    MARIA_BP_REVIVAL_COLUMN,
    MARIA_BP_MARIA_POWERS_APPLIED,
    MARIA_BP_SLIDE,
    MARIA_BP_25,
    MARIA_BP_BLADE_DASH,
    MARIA_BP_BLUE_CIRCLE,
    MARIA_BP_BLUE_SPHERE,
    MARIA_BP_MARIA,
    MARIA_BP_MARIA_POWERS_INVOKED,
    MARIA_BP_31,
    // 0x20
    MARIA_BP_NOT_IMPLEMENTED_4,
    MARIA_BP_RIC_BLINK,
    MARIA_BP_CRASH_CROSS_PARTICLES,
    MARIA_BP_35,
    MARIA_BP_36,
    MARIA_BP_37,
    MARIA_BP_38,
    MARIA_BP_39,
    MARIA_BP_HOLYWATER_GLASS,
    MARIA_BP_CRASH_AXE,
    MARIA_BP_42,
    MARIA_BP_SUBWPN_DAGGER,
    MARIA_BP_CRASH_DAGGER,
    MARIA_BP_HIGH_JUMP,
    MARIA_BP_HIT_BY_CUT,
    MARIA_BP_HIT_BY_ICE,
    // 0x30
    MARIA_BP_HIT_BY_THUNDER,
    MARIA_BP_VIBHUTI,
    MARIA_BP_REBOUND_STONE,
    MARIA_BP_AGUNEA,
    MARIA_BP_AGUNEA_HIT_ENEMY,
    MARIA_BP_DEATH_BY_FIRE,
    MARIA_BP_CRASH_VITHUBI,
    MARIA_BP_VITHUBI_CRASH_CLOUD,
    MARIA_BP_CRASH_REBOUND_STONE,
    MARIA_BP_57,
    MARIA_BP_CRASH_REBOUND_STONE_EXPLOSION,
    MARIA_BP_CRASH_BIBLE,
    MARIA_BP_CRASH_BIBLE_BEAM,
    MARIA_BP_BIBLE,
    MARIA_BP_BIBLE_TRAIL,
    MARIA_BP_SUBWPN_STOPWATCH,
    // 0x40
    MARIA_BP_STOPWATCH_CIRCLE,
    MARIA_BP_CRASH_STOPWATCH,
    MARIA_BP_66,
    MARIA_BP_CRASH_AGUNEA,
    MARIA_BP_CRASH_AGUNEA_THUNDER,
    MARIA_BP_CRASH_REBOUND_STONE_PARTICLES,
    MARIA_BP_HIT_BY_DARK,
    MARIA_BP_HIT_BY_HOLY,
    MARIA_BP_AGUNEA_THUNDER,
    MARIA_BP_CRASH_STOPWATCH_LIGHTNING,
    MARIA_BP_SMOKE_PUFF_2,
    MARIA_BP_SKID_SMOKE_2,
    MARIA_BP_SKID_SMOKE_3,
    MARIA_BP_TELEPORT,
    NUM_BLUEPRINTS,
};

enum MariaTimers {
    MARIA_PL_T_POISON,
    MARIA_PL_T_CURSE,
    MARIA_PL_T_2,
    MARIA_PL_T_3,
    MARIA_PL_T_4,
    MARIA_PL_T_5,
    MARIA_PL_T_6,
    MARIA_PL_T_7,
    MARIA_PL_T_8,
    MARIA_PL_T_ATTACK,
    MARIA_PL_T_10,
    MARIA_PL_T_RUN,
    MARIA_PL_T_12,
    MARIA_PL_T_INVINCIBLE_SCENE, // "dying" in the prologue
    MARIA_PL_T_INVINCIBLE,
    MARIA_PL_T_AFTERIMAGE_DISABLE,
};

enum MariaSteps {
    MARIA_PL_S_STAND,
    MARIA_PL_S_WALK,
    MARIA_PL_S_CROUCH,
    MARIA_PL_S_FALL,
    MARIA_PL_S_JUMP,
    MARIA_PL_S_5, // unused
    MARIA_PL_S_6, // unused
    MARIA_PL_S_7, // unused
    MARIA_PL_S_HIGHJUMP,
    MARIA_PL_S_9, // unused
    MARIA_PL_S_HIT,
    MARIA_PL_S_11, // unused
    MARIA_PL_S_BOSS_GRAB,
    MARIA_PL_S_13, // unused
    MARIA_PL_S_14, // unused
    MARIA_PL_S_15, // unused
    MARIA_PL_S_DEAD,
    MARIA_PL_S_17, // unused
    MARIA_PL_S_STAND_IN_AIR,
    MARIA_PL_S_FLAME_WHIP,
    MARIA_PL_S_HYDROSTORM,
    MARIA_PL_S_THROW_DAGGERS,
    MARIA_PL_S_DEAD_PROLOGUE,
    MARIA_PL_S_SLIDE,
    MARIA_PL_S_BLADEDASH,
    MARIA_PL_S_RUN,
    MARIA_PL_S_SLIDE_KICK,
    MARIA_PL_S_SUBWPN_CRASH,
    MARIA_PL_S_28, // unused
    MARIA_PL_S_29, // unused
    MARIA_PL_S_30, // unused
    MARIA_PL_S_31, // unused
    MARIA_PL_S_INIT,
    MARIA_PL_S_DEBUG = 0xF0,
};

/* Declarations moved here by tools/saturn/move_declarations.py */
extern void func_060BD474(Entity*);
extern void func_060BCFF4(Entity*);
extern void func_060BCCE8(Entity*);
extern void func_060BD244(Entity*);
extern void func_060BD150(Entity*);
extern void func_060B18C8(Entity*);
extern void func_060BD0D0(Entity*);
extern void func_060B99A8(Entity*);
extern void func_060B9D88(Entity*);
extern void func_060B9B88(Entity*);
extern void func_060BCBD8(Entity*);
extern void func_060BB724(Entity*);
extern void func_060BB868(Entity*);
extern void func_060BB334(Entity*);
extern void func_060BC320(Entity*);
extern void func_060BBEF8(Entity*);
extern void func_060BB4AC(Entity*);
extern void func_060BAFF0(Entity*);
extern void func_060BADA8(Entity*);
extern void func_060B96C0(Entity*);
extern void func_060AD248(Entity*);
extern void func_060AD0E8(Entity*);
extern void func_060B9404(Entity*);
extern void func_060B85C8(Entity*);
extern void func_060B0474(Entity*);
extern void MariaEntityStopwatchCrashLightning(Entity*);
extern void func_060B382C(Entity*);
extern void func_060AC1FC(Entity*);
extern void func_060AC458(Entity*);
extern void MariaEntityCrashReboundStoneParticles(Entity*);
extern void func_060B46A0(Entity*);
extern void func_060B46BC(Entity*);
extern void func_060B3684(Entity*);
extern void func_060B44E8(Entity*);
extern void func_060B4B80(Entity*);
extern void func_060B4CF4(Entity*);
extern void func_060B5C3C(Entity*);
extern void func_060B5E28(Entity*);
extern void func_060B30BC(Entity*);
extern void func_060B2E7C(Entity*);
extern void func_060B29D4(Entity*);
extern void func_060B2FC8(Entity*);
extern void func_060B2474(Entity*);
extern void func_060B2604(Entity*);
extern void func_060B1E78(Entity*);
extern void func_060B1A58(Entity*);
extern void func_060B1474(Entity*);
extern void func_060B09CC(Entity*);
extern void func_060AFBA4(Entity*);
extern void func_060AF444(Entity*);
extern void func_060ACE84(Entity*);
extern void func_060B626C(Entity*);
extern void func_060B6C94(Entity*);
extern void func_060B668C(Entity*);
extern void func_060B82B8(Entity*);
extern void func_060AF17C(Entity*);
extern void func_060AEFB4(Entity*);
extern void func_060B805C(Entity*);
extern void func_060AEB18(Entity*);
extern void func_060AD048(Entity*);
extern void func_060AE8D8(Entity*);
extern void func_060AE730(Entity*);
extern void func_060ACF8C(Entity*);
extern void func_060ACD98(Entity*);
extern void func_060AE3C0(Entity*);
extern void func_060B776C(Entity*);
extern void func_060AE2C8(Entity*);
extern void func_060B72B4(Entity*);
extern void func_060B868C(Entity*);
extern void func_060AE014(Entity*);
extern void func_060B9048(Entity*);
extern void func_060B8B24(Entity*);
extern void func_060B7F50(Entity*);
extern void func_060AD7D8(Entity*);
extern void func_060B7E08(Entity*);
extern void func_060B7A48(Entity*);
extern void func_060AD3A8(Entity*);
extern void func_060AC9E0(Entity*);
extern void func_060B099C(Entity*);
void func_060BE3D4(void);
void func_060C00B4(void);
void func_060BFD24(void);
void func_060C0428(void);
void func_060BF7B0(void);
void func_060C0AE4(void);
void func_060BF704(void);
void func_060BF35C(void);
void func_060BEE30(void);
void func_060BE700(void);
void func_060BE6D4(void);
void func_060BE618(void);
void func_060BE54C(void);
void func_060BE440(void);
void func_060BE414(void);
void func_060BE258(void);
void func_060BE064(void);
void func_060BD5F0(void);
void func_060BDED8(void);
extern SaturnPlayerGraphicsRecord g_MariaPlayerGraphicsRecords[346];
extern void* g_MariaSpriteBanks[18];
void func_8015F9F0(Entity* entity);
void func_060AB088(void);
Entity* RicCreateEntFactoryFromEntity(
    Entity* source, u32 factoryParams, s32 arg2);
void func_060AA974(void);
void func_060AA9EC(void);
void RicSetInvincibilityFrames(s32 kind, s16 invincibilityFrames);
void func_060AA8AC(s32 resetAnims, s32 arg1);
void func_060AC850(void);
s32 func_060B09C0(void);
void func_060AC604(void);
void func_060A5BE8(void);
void func_060A5208(u16 params);
extern AnimationFrame ric_anim_walk[];
extern AnimationFrame ric_anim_crouch[];
void func_060A9304(void);
extern AnimationFrame g_MariaAnim_060C3284[];
extern AnimationFrame g_MariaAnim_060C33B0[];
extern AnimationFrame g_MariaAnim_060C3390[];
extern AnimationFrame g_MariaAnim_060C32F8[];
extern AnimationFrame g_MariaAnim_060C34F8[];
extern AnimationFrame g_MariaAnim_060C34D4[];
extern AnimationFrame g_MariaAnim_060C3438[];
extern AnimationFrame g_MariaAnim_060C31E8[];
extern AnimationFrame g_MariaAnim_060C2E20[];
extern AnimationFrame ric_anim_stand_alt[];
extern AnimationFrame ric_anim_stand[];
extern AnimationFrame ric_anim_land_from_air_run[];
extern AnimationFrame g_MariaAnim_060C2E64[];
extern SaturnSpriteResource g_MariaSpriteResources[13];
void func_060BF180(void);
extern s16 g_MariaMapRevealRowIndices[7];
void func_060BB9BC(s32*);
extern s32 g_MariaSavedMapPlaneConfig;
extern s32 g_MariaSavedMapVramBase;
extern s32 d_060cd74c;
extern s32 d_060cd748;
extern u8 g_MariaCastleMapBitmap[240][160];
extern u32 g_MariaCastleMapState;
void func_060BB330();
extern u8 D_80174FB8;
extern u8 D_80174FB4;
extern u8 D_80174FB0;
extern u8 g_MariaEmptyAnimMarker;
extern u8 g_MariaBlueprintColors[][4];
extern Point32 g_RicSensorsWall[NUM_VERTICAL_SENSORS * 2];
extern Point32 g_RicSensorsFloor[NUM_HORIZONTAL_SENSORS];
extern Point32 g_RicSensorsCeiling[NUM_HORIZONTAL_SENSORS];
extern AnimationFrame* g_MariaAnimationGroups[];
extern FrameProperty g_MariaFrameProperties[];
s32 func_060aa608(FrameProperty*, AnimationFrame**);
extern u8 g_MariaInitialAfterimageTimers[];
extern AnimationFrame D_8015591C[];
extern AnimationFrame D_80155950[];
typedef struct {
    /* 0x00 */ s16 attack;
    /* 0x02 */ u8 hitboxWidth;
    /* 0x03 */ u8 hitboxHeight;
    /* 0x04 */ s8 hitboxOffX;
    /* 0x05 */ s8 hitboxOffY;
    /* 0x06 */ s16 attackElement;
    /* 0x08 */ s16 hitboxState;
    /* 0x0A */ u8 nFramesInvincibility;
    /* 0x0B */ u8 stunFrames;
    /* 0x0C */ s16 hitEffect;
    /* 0x0E */ s16 entityRoomIndex;
} MariaAttackDef; /* size = 0x10 */

// PlaySfx, RicSetFall, RicSetStand, RicSetStep and RicSetAnimation
// intentionally missing
void func_060ABE94(Entity* entity);
void func_060BF3D0(void);
s32 func_060A9474(void);
u16 SPR_2LookupTblNoToVram(u16 tableNo);
extern Unk0605DB60 d_0605DB60[];
extern s32 DAT_060D2918;
extern s32 DAT_060D2A94[]; // fastest clear time per stage
extern s32 DAT_060D2B04[]; // stage id, sorted alongside DAT_060D2A94
extern AnimationFrame g_MariaAnimFall;
// src/saturn/maria/enddata.c
extern AnimationFrame g_MariaEntity060BD0D0Anim0[];
extern AnimationFrame g_MariaEntity060BD0D0Anim1[];
extern AnimationFrame g_MariaEntity060BD0D0Anim2[];
extern s32 MariaCheckFacing(void);
extern int MariaCheckInput(s32 checks);
s32 func_060A926C();
extern AnimationFrame g_MariaAnimWalkStopFacingBitSet[];
extern AnimationFrame g_MariaAnimWalkStopFacingBitClear[];
extern AnimationFrame DAT_060C2408;
extern u8 g_MariaMapRevealPattern[11];
extern u8 g_MariaMapIconIndices[8];
extern Point16 g_MariaMapUiPositionsA[12];
extern Point16 g_MariaMapUiPositionsB[5];
extern Point16 g_MariaMapUiPositionsC[21];
extern Point16 g_MariaMapUiPositionsD[14];
extern Point16 g_MariaMapUiPositionsE[16];
extern Point16 g_MariaMapUiPositionsF[11];
void func_060BD638(u8 walls, u8* dst);
void func_060BD81C(u8 walls, u8* dst);
void func_060BD9E8(u8 walls, u8* dst);
void func_060BDAD0(void);
void func_060BDC7C(void);
void func_060BEA54(void);
void func_06078550(s32 arg0, u8 code, Point16* pos);
void func_06078684(s32 arg0, s32 value, Point16* pos);
/* End moved declarations */

#endif
