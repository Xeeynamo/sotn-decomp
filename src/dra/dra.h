// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef DRA_H
#define DRA_H

#include "disk.h"
#include "game.h"
#include "weapon.h"
#include "items.h"

#define DAMAGE_FLAG_NORMAL 0x0000
#define DAMAGE_FLAG_CRITICAL 0x4000
#define DAMAGE_FLAG_ABSORB 0x8000
#define DAMAGE_FLAG_IMMUNE 0xC000

#define SFX_START (0x600)
#ifdef VERSION_PSP
#define SFX_LAST (0x90B)
#else
#define SFX_LAST (0x8E0)
#endif
#define MAX_SND_COUNT (0x100)

#define SEQ_TABLE_S_MAX 0x10
#define SEQ_TABLE_T_MAX 1

#define VSYNC_UNK_LEN 1024

#define NUM_CH 4
#define NUM_CH_2 4 // not sure if this is related to NUM_CH

typedef enum {
    MENU_DG_MAIN,
    MENU_DG_BG,
    MENU_DG_EQUIP_OVERVIEW,
    MENU_DG_EQUIP_SELECTOR,
    MENU_DG_INFO_BAR,
    MENU_DG_RELICS,
    MENU_DG_SPELLS,
    MENU_DG_SETTINGS,
    MENU_DG_CLOAK_COLOR,
    MENU_DG_CFG_BUTTONS,
    MENU_DG_CLOAK_LINING,
    MENU_DG_CFG_SOUND,
    MENU_DG_WINDOW_COLORS,
    MENU_DG_TIME_ATTACK,
    MENU_DG_EQUIP_SORT,
    MENU_DG_FAMILIARS,
#if defined(VERSION_PSP)
    MENU_PSP_EXTRA_1,
    MENU_PSP_EXTRA_2,
    MENU_PSP_EXTRA_3,
#endif
    NUM_MENU,
} MenuDialogue;

typedef enum {
    DEBUG_NORMAL,
    DEBUG_TEXTURE_VIEWER,
    DEBUG_TILESET_VIEWER,
    DEBUG_PALETTE_VIEWER,
    DEBUG_END,
} DebugMode;

typedef enum {
    DEBUG_COLOR_CHANNEL_RED,
    DEBUG_COLOR_CHANNEL_GREEN,
    DEBUG_COLOR_CHANNEL_BLUE,
} DebugColorChannel;

typedef enum {
    SimFileType_System,
    SimFileType_StagePrg,
    SimFileType_Vh,
    SimFileType_Vb,
    SimFileType_Seq,
    SimFileType_StageChr,
    SimFileType_Unused6,
    SimFileType_Weapon0Prg,
    SimFileType_Weapon1Prg,
    SimFileType_Weapon0Chr,
    SimFileType_Weapon1Chr,
    SimFileType_FamiliarPrg,
    SimFileType_FamiliarChr,
    SimFileType_Monster,
} SimFileType;

typedef enum {
    SIM_STAGE_PRG,
    SIM_1,
    SIM_STAGE_CHR,
    SIM_3,
    SIM_VH,
    SIM_VB,
    SIM_6,
    SIM_SEQ,
    SIM_WEAPON_PRG,
    SIM_WEAPON0_CHR,
    SIM_WEAPON1_CHR,
    SIM_11,
    SIM_12,
    SIM_13,
    SIM_14,
    SIM_15,
    SIM_16,
    SIM_17,
    SIM_FAMILIAR_PRG,
    SIM_FAMILIAR_CHR,
    SIM_MONSTER,
    SIM_21,
} SimKind;

typedef struct {
    const char* path; // file name
    void* addr;       // where to load the file to
    size_t size;      // file size
    SimKind kind;
} SimFile;

enum AluEntities {
    E_NONE,                         // EntityNull
    E_FACTORY,                      // EntityFactory
    E_SMOKE_PUFF,                   // EntitySmokePuff
    E_GRAVITY_BOOT_BEAM,            // EntityGravityBootBeam
    E_KNIFE,                        // EntitySubwpnKnife
    E_UNK_5,                        // func_8011E4BC
    E_UNK_6,                        // EntityDiveKickAttack
    E_UNK_7,                        // EntityGiantSpinningCross
    E_CRASH_CROSS_ROTATING,         // EntitySubwpnCrashCross
    E_SUBWPN_CRASH_CROSS_PARTICLES, // EntitySubwpnCrashCrossParticles
    E_SUBWPN_AXE,                   // EntitySubwpnThrownAxe
    E_BLINK_WHITE,                  // EntityPlayerBlinkWhite
    E_SUBWPN_VIBHUTI,               // EntitySubwpnThrownVibhuti
    E_UNK_13,                       // func_8011E0E4
    E_UNK_14,                       // func_8011EDA0
    E_UNK_15,                       // EntityUnarmedAttack
    E_UNK_16,                       // func_8011EDA8
    E_SUBWPN_AGUNEA,                // EntitySubwpnAgunea
    E_SUBWPN_AGUNEA_HIT_ENEMY,      // EntityAguneaHitEnemy
    E_UNK_19,                       // EntityNumberMovesToHpMeter
    E_SUBWPN_REBOUND_STONE,         // EntitySubwpnReboundStone
    E_UNK_21,                       // EntityLevelUpAnimation
    E_SUBWPN_HOLY_WATER,            // EntitySubwpnHolyWater
    E_SUBWPN_HOLY_WATER_FLAME,      // EntitySubwpnHolyWaterFlame
    E_UNK_24,                       // EntityUnkId24
    E_HELLFIRE,                     // EntityHellfire
    E_HELLFIRE_SMALL_FIREBALL,      // EntityHellfireNormalFireball
    E_HELLFIRE_BIG_FIREBALL,        // EntityHellfireBigFireball
    E_UNK_28,                       // EntityExpandingCircle
    E_UNK_29,                       // func_80127CC8
    E_HIT_BY_LIGHTNING,             // EntityHitByLightning
    E_PLAYER_OUTLINE,               // EntityPlayerOutline
    E_UNK_32,                       // EntityPlayerDissolves
    E_HIT_BY_ICE,                   // EntityHitByIce
    E_MIST,                         // EntityMist
    E_WING_SMASH_TRAIL,             // EntityWingSmashTrail
    E_UNK_36,                       // func_8011B480
    E_UNK_37,                       // EntityGuardText
    E_UNK_38,                       // EntityTransparentWhiteCircle
    E_UNK_39,                       // EntityPlayerPinkEffect
    E_HOLYWATER_BREAK_GLASS,        // EntitySubwpnHolyWaterBreakGlass
    E_SUBWPN_STOPWATCH,             // EntityStopWatch
    E_SUBWPN_STOPWATCH_CIRCLE,      // EntityStopWatchExpandingCircle
    E_SUBWPN_BIBLE,                 // EntitySubwpnBible
    E_SUBWPN_BIBLE_TRAIL,           // EntitySubwpnBibleTrail
    E_BAT_FIREBALL,                 // EntityBatFireball
    E_UNK_46,                       // func_80123B40
    E_UNK_47,                       // func_80119F70
    E_UNK_48,                       // UnknownEntId48
    E_UNK_49,                       // UnknownEntId49
    E_UNK_50,                       // func_80123A60
    E_SMALL_RISING_HEART,           // EntitySmallRisingHeart
    E_BAT_ECHO,                     // EntityBatEcho
    E_UNK_53,                       // func_8011B530
    E_UNK_54,                       // func_8011F074
    E_UNK_55,                       // func_80130264
    E_UNK_56,                       // func_8012F894
    E_UNK_57,                       // func_80130618
    E_UNK_58,                       // func_801309B4
    E_UNK_59,                       // func_80130E94
    E_UNK_60,                       // func_8013136C
    E_UNK_61,                       // func_80129864
    E_UNK_62,                       // EntityNull
    E_SUMMON_SPIRIT,                // EntitySummonSpirit
    E_UNK_64,                       // func_80123F78
    E_TELEPORT,                     // EntityTeleport
    E_SLEEP_ZZZ,                    // EntityPlayerSleepZ
    E_UNK_67,                       // EntityNull
    NUM_ENTITIES,

    E_UNK_238 = 238, // ???
    E_UNK_254 = 254, // ???

};

enum AluBlueprints {
    BP_0,
    BP_1,
    BP_GRAVITY_BOOT_BEAM,
    BP_3,
    BP_4,
    BP_5,
    BP_6,
    BP_7,
    BP_8,
    BP_9,
    BP_10,
    BP_11,
    BP_12,
    BP_13,
    BP_14,
    BP_15,
    BP_16,
    BP_17,
    BP_18,
    BP_19,
    BP_20,
    BP_21,
    BP_22,
    BP_23,
    BP_24,
    BP_25,
    BP_26,
    BP_27,
    BP_28,
    BP_29,
    BP_30,
    BP_31,
    BP_32,
    BP_HELLFIRE,
    BP_HELLFIRE_SMALL_FIREBALL,
    BP_HELLFIRE_BIG_FIREBALL,
    BP_36,
    BP_37,
    BP_38,
    BP_39,
    BP_RIPPLE_OUTLINE,
    BP_41,
    BP_42,
    BP_43,
    BP_BLINK_WHITE,
    BP_45,
    BP_HIT_BY_ICE,
    BP_47,
    BP_48,
    BP_49,
    BP_50,
    BP_51,
    BP_52,
    BP_53,
    BP_54,
    BP_55,
    BP_56,
    BP_57,
    BP_58,
    BP_59,
    BP_60,
    BP_61,
    BP_62,
    BP_63,
    BP_64,
    BP_WING_SMASH_TRAIL,
    BP_66,
    BP_67,
    BP_68,
    BP_69,
    BP_70,
    BP_71,
    BP_72,
    BP_73,
    BP_74,
    BP_STOPWATCH_ACTIVATE,
    BP_76,
    BP_77,
    BP_78,
    BP_79,
    BP_80,
    BP_BAT_FIREBALL,
    BP_82,
    BP_83,
    BP_84,
    BP_85,
    BP_86,
    BP_87,
    BP_88,
    BP_89,
    BP_90,
    BP_91,
    BP_92,
    BP_93,
    BP_94,
    BP_95,
    BP_96,
    BP_97,
    BP_98,
    BP_SMALL_RISING_HEART,
    BP_100,
    BP_101,
    BP_102,
    BP_BAT_ECHO,
    BP_104,
    BP_105,
    BP_106,
    BP_107,
    BP_108,
    BP_109,
    BP_110,
    BP_111,
    BP_112,
    BP_113,
    BP_114,
    BP_115,
    BP_116,
    BP_SUMMON_SPIRIT,
    BP_118,
    BP_119,
    BP_120,
    BP_TELEPORT,
    BP_SLEEP_ZZZ,
    NUM_BLUEPRINTS,
};

// NOTE: B_MAKE from DRA is different than RIC or MARIA!
// Parsing is done in EntityFactory
// entityId: what entity to spawn based on the Entity Set
// amount: How many entities to spawn in total
// nPerCycle: how many entities to spawn at once without waiting for tCycle
// isNonCritical: 'true' for particles, 'false' for gameplay related entities
//   false: keep searching for a free entity slot every frame to make the entity
//   true: when there are no entities available then just forgets about it
// incParamsKind: the technique used to set the self->params to the new entity
//   false: it is set from 0 to 'nPerCycle'
//   true: it is set from 0 to 'amount'
// timerCycle: wait frames per cycle until 'amount' of entities are made
// kind: refer to `BlueprintKind` for a list of options
// origin: position where the entity will spawn from
// timerDelay: how many frames to wait before starting to make the first entity
#define B_MAKE(entityId, amount, nPerCycle, isNonCritical, incParamsKind,      \
               timerCycle, kind, origin, timerDelay)                           \
    {(entityId),                                                               \
     (amount),                                                                 \
     ((nPerCycle) & 0x3F) | ((!!(incParamsKind)) << 6) |                       \
         ((!!(isNonCritical)) << 7),                                           \
     (timerCycle),                                                             \
     ((kind) & 15) | (((origin) & 15) << 4),                                   \
     timerDelay}
enum BlueprintKind {
    B_KIND_0,
    B_KIND_1,
    B_KIND_2,
    B_KIND_3,
    B_KIND_4,
    B_KIND_5,
    B_KIND_6,
    B_KIND_7,
    B_KIND_8,
    B_KIND_9,
    NUM_BLUEPRINT_KIND,
};
enum BlueprintOrigin {
    // Spawned entities have a life-cycle on their own and
    B_ORIGIN_DEFAULT,

    B_ORIGIN_1,
    B_ORIGIN_2,
    B_ORIGIN_3,
    B_ORIGIN_4,
    B_ORIGIN_5,
    B_ORIGIN_6,
    B_ORIGIN_7,
    B_ORIGIN_8,
    B_ORIGIN_9,
    B_ORIGIN_10,
    B_ORIGIN_11,
    B_ORIGIN_12,
    B_ORIGIN_13,
    B_ORIGIN_14,
};

typedef enum {
    STATUS_AILMENT_POISON,
    STATUS_AILMENT_CURSE,
    STATUS_AILMENT_PETRIFIED,
    STATUS_AILMENT_DARK_METAMORPHOSIS,
    STATUS_AILMENT_UNK04,
    STATUS_AILMENT_UNK05, // used by EntityPlayerPinkEffect
} StatusAilments;

// Used in HandleTransformationMP, maybe elsewhere
typedef enum { FORM_BAT, FORM_MIST, FORM_WOLF } TransformationForm;

// Used for many functions which do things like testing and decrementing a value
typedef enum { CHECK_ONLY, REDUCE } CallMode;

// Info necessary to load a file from the Cd in UpdateCd
typedef struct {
    s32 loc;        // lba offset, might be a s32
    CdCallbacks cb; // sets g_CdCallback
    s32 size;       // file size
    u8 vabId;       // index for g_VabAddrs, between 0 and 5?
    u8 unkD;        // index for D_800ACD10, between 0 and 6?
    u8 nextCdFileType;
    u8 unkF;
} CdFile;

// Used for SEQ_LIB.SEQ and SEQ_DAI.SEQ
typedef struct {
    s32 loc;
    s32 size;
    u32 unk8;
} CdFileSeq;

typedef struct {
    CdCallbacks cb;
    CdlLOC loc;
} CdMgr;

typedef struct {
    RECT dstRect;
    s32 D_80137F68;
    s32 D_80137F6C;
    s32 D_80137F70;
    s32 D_80137F74;
    s32 D_80137F78;
    s32 D_80137F7C;
    u8* overlayCopySrc;
    u8* overlayCopyDst;
    s8* addr;
    s32 overlayBlockCount;
    s32 overlayLastBlockSize;
} CdThing;

#define NOW_LOADING_PRIM_COUNT 16
typedef struct {
    /* 0x00 */ s32 step;
    /* 0x04 */ s32 primIndex;
    /* 0x08 */ s16 x;
    /* 0x0A */ s16 y;
    /* 0x0C */ s16 unkC; // unused
    /* 0x0E */ s16 verticalWave;
    /* 0x10 */ s16 horizontalWave;
    /* 0x12 */ u16 unk12; // unused
    /* 0x14 */ s16 speed;
    /* 0x16 */ s16 waveTable[NOW_LOADING_PRIM_COUNT];
} NowLoadingModel; // size=0x36

typedef struct {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    s32 u;
    s32 v;
    s32 tpage;
    s32 clut;
} RicSubwpnIconParams;

typedef struct {
    u32 displayHP;
    s32 primIndex1;
    s32 primIndex2;
    s32 unk0C;
    u32 unk10;
    s32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    u32 unk24;
    s32 unk28;
    s32 g_HealingMailTimer;
} PlayerHud;

// g_ButtonCombo is an array of 16, here is what each index is for
// Names should be updated as each one is decompiled.
typedef enum {
    COMBO_GRAVITY_BOOTS,
    COMBO_QCF, // Quarter circle forward (down, down+forward, forward)
    COMBO_BF,  // Back forward
    COMBO_HELLFIRE,
    COMBO_TETRA_SPIRIT,
    COMBO_UNK5,
    COMBO_SOUL_STEAL,
    COMBO_UNK7,
    COMBO_UNK8,
    COMBO_SWORD_BROTHERS,
    COMBO_UNK10,
    COMBO_UNK11,
    COMBO_UNK12,
    COMBO_UNK13,
    COMBO_SUMMON_SPIRIT,
    COMBO_DARK_METAMORPH,
    COMBO_NUM,
} ButtonComboIdx;

typedef struct SeqData {
    u8 volume;
    u8 reverb_depth;
    u8 unk2;
} SeqData;

typedef struct Cmd14 {
    u8 unk0[8];
    s32 unk8;
    s16 unkc;
    u8 unke;
} Cmd14;

// Used in dra/7E4BC, dra/bss, rbo5/unk_4648C, bo4/unk_46E7C
typedef struct {
    f32 posX;
    f32 posY;
    s16 angle1;
    s16 angle2;
    s16 size;
    s16 xOffset;
    s16 yOffset;
    s16 pad;
} mistStruct; // size = 0x14

// Used in dra/menu, dra_psp/menu
typedef struct EquipMenuHelper {
    EquipKind equipTypeFilter;
    s32 index;
    s32 isAccessory;
} EquipMenuHelper;

// Used in dra/menu, dra_psp/menu
// Struct for table of values to intitialize MenuContext structs
typedef struct {
    /* 0x00 */ s16 cursorX;
    /* 0x02 */ s16 cursorY;
    /* 0x04 */ u16 cursorW;
    /* 0x06 */ u16 cursorH;
    /* 0x08 */ s32 otIdx;
} MenuContextInit; // size = 0x0C

// Used in dra/dra, dra/7E4BC, dra/d_DBD4
typedef struct {
    u16 palette;
    u8 unk2;
} Unkstruct_800AE180;

// Used in dra/7E4BC, dra/d_DBD4
typedef struct {
    u8 timers[8];
    u8 blueprints[8];
    u8 blueprintParams[8];
    u32 unk18;
} Unkstruct_800ADEF0; // size:0x1C

// Used in dra/d_10798, dra/8D3E8, dra/dra.h
// This appears to be a super miniature Entity or something
// All it has is a state, a timer, and a facing direction.
typedef struct {
    s32 state;
    s32 timer;
    s32 facingLeft;
} helper_8012F178;

// Used for the button combos to signal successfully completing the sequence
#define COMBO_COMPLETE 0xFF

// File list:
extern u8 aPqes[];         // TODO: extract file
extern u8 aPqes_0[];       // TODO: extract file
extern u8 aPqes_1[];       // TODO: extract file
extern u8 aPbav[0x3000];   // TODO: extract file
extern u8 aPbav_0[0x2000]; // TODO: extract file
extern u8 aPbav_1[0x2000]; // TODO: extract file
extern u8 aPbav_2[0x2000]; // TODO: extract file

extern s16 g_ButtonMask[];
extern u16 D_800A04CC[];
extern u32 D_800A04F8;
extern s32 D_800A2438;

extern RoomTeleport D_800A245C[];
extern u32 D_800A2D24;
extern const char* D_800A83AC[];

extern u16 D_800A37D8[2];
extern u16 g_JosephsCloakColors[4];
extern GfxBank** g_GfxSharedBank[];
extern s16** D_800A3B70[18];
extern u_long* D_800A3BB8[];
extern Lba g_StagesLba[80];

extern SubweaponDef g_SubwpnDefs[13];
// These are different on PSP since they have text that needs translating.
#if defined(VERSION_PSP)
extern char** g_SaveAreaNamesSecondPart;
extern char** g_SaveAreaNames;
extern RelicDesc* g_RelicDefs;
extern SpellDef* g_SpellDefs;
extern char** g_MenuStr;
extern EnemyDef* g_EnemyDefs;
extern Accessory* g_AccessoryDefs;
extern Equipment* g_EquipDefs;
#else
extern RelicDesc g_RelicDefs[30];
extern SpellDef g_SpellDefs[28];
extern const char* g_MenuStr[110];
extern EnemyDef g_EnemyDefs[400];
extern Accessory g_AccessoryDefs[90];
extern Equipment g_EquipDefs[217];
#endif
extern s32 g_ExpNext[];
extern s16 D_800AC958[];
extern CdFile* D_800ACC74[];
extern s32 g_CurrentStream;
extern s32 D_800ACE44;
extern s16 g_SensorsCeilingBat[];
extern s16 g_SensorsFloorBat[];
extern s16 g_SensorsWallBat[];
extern s16 g_SensorsCeilingDefault[];
extern s16 g_SensorsFloorDefault[];
extern s16 g_SensorsWallDefault[];
extern s16 g_SensorsCeilingCrouch[];
extern s16 g_SensorsWallCrouch[];

extern Point16 g_SensorsCeiling[];
extern Point16 g_SensorsFloor[];
extern Point16 g_SensorsWall[];

#if !defined(VERSION_US)
extern s32 D_800ACEDC_hd;
#define TRANSFORM_LOCKOUT_TIMER D_800ACEDC_hd
#else
#define TRANSFORM_LOCKOUT_TIMER g_Player.unk20
#endif
extern s16 D_800ACF7C[4];
extern s16 g_SfxPainGrunts[8]; // Alucard's random pain sfx table
extern s16 D_800ACF94[16];
typedef union {
    u8 rawBytes[4];
    AnimationFrame af;
} unionD_800ACFB4;
extern unionD_800ACFB4 D_800ACFB4[];
extern s16* D_800CF324[];
extern s16* D_800CFE48[];
extern PfnEntityUpdate D_800AD0C4[];
extern s16 D_800AD54C[6];
extern s32 D_800AD558[6];
extern s16 D_800AD570[6];
extern AnimationFrame D_800AD57C[25];
extern u8 D_800AD5E0[14];
extern u8 D_800AD5F0[10];
extern AnimationFrame D_800AD5FC[];
extern s32 D_800AD630[];
extern s16 D_800AD670[42][10];
extern s16 D_800AD9B8[24][5];
extern AnimationFrame D_800ADBD4[];
extern AnimationFrame D_800ADC10[];
extern AnimationFrame D_800ADC44[];
extern u16 D_800ADC7C[2];
extern Point16* D_800ADCC8[];
extern s16 D_800ADDE8[][6];
extern u8 D_800AE120[];
extern RECT D_800AE130;
extern RECT D_800AE138;
extern u8 D_800AE140[][8];
extern Unkstruct_800AE180 D_800AE180[];
extern s16 D_800AE190[];
extern s16 D_800AE1B0[];
extern s16 D_800AE1F0[];
extern u32 D_800AE230[8];
extern u32 D_800AE250[8];
extern s32 D_800AE270;
extern s32 D_800AE274;
extern s32 D_800AE278;
extern s32 D_800AE27C;
extern s32 D_800AE280;
extern s32 D_800AE284;
extern s32 D_800AE288;
extern s32 D_800AE28C;
extern s32 D_800AE290;
extern AnimationFrame D_800AE294[];
extern AnimationFrame D_800AFC50[];
extern AnimationFrame D_800AFDA4[];
extern RECT c_backbufferClear;
extern AnimationFrame D_800AFFB8[];
extern s8 D_800B0130[];
extern AnimationFrame* D_800B01B8[];
extern u8 D_800B0608[];
extern s32 D_800B0688[];
extern u32 D_800B06C8[24];
extern u32 D_800B0728[24];
extern RECT D_800B0788;
extern RECT D_800B0790;
extern AnimationFrame D_800B0798[];
extern AnimationFrame D_800B07C8[];
extern s32 D_800B0830[];
extern s32 D_800B083C[];
extern u8 D_800B0848[];
extern s16 D_800B0858[];
extern s16 D_800B0860[];
extern s16 D_800B0884[];
extern s16 D_800B08A8[];

extern s16 g_CdVolumeTable[];
extern struct SeqData g_SeqInfo[];
extern struct XaMusicConfig g_XaMusicConfigs[];
extern s32 g_DebugEnabled;
extern s32 D_800BD1C4;
extern s32 g_VabAddrs[6];
extern s8* g_SfxScripts[172];
extern u8* D_800C52F8[];
extern const char D_800DB524[];
extern const char a0104x04x;
extern const char a2304x04x;
extern const char aBlue;
extern const char aDr03x;
extern const char aEff03x;
extern const char aEnv03x;
extern const char aG403x;
extern const char aGreen;
extern const char aGt303x;
extern const char aGt403x;
extern const char aHalfOff;
extern const char aHalfOn;
extern const char aLine03x;
extern const char aRed;
extern const char aRgb02x02x02x;
extern const char aSp03x;
extern const char aSp1603x;
extern const char aTile03x;
extern Unkstruct_800BF554 g_SfxData[];

extern char* aLightTimer02x;
extern SVECTOR D_800E2024;
extern SVECTOR D_800E202C;
extern helper_8012F178 D_800B08CC[6];
extern s32 D_800B0914;
extern s32 D_800B0918;
extern s32 D_800B091C;
extern s32 D_800B0920;

void func_801072DC(Primitive* prim);
void InitializePads(void);
void ReadPads(void);
void ClearBackbuffer(void);
void CheckCollision(s32 x, s32 y, Collider* res, s32 unk);
void DemoInit(s32 arg0);
void DemoUpdate(void);
void SetGPUBuffRGBZero(void);
void SetGPUBuffRGB(u8 arg0);
void func_800E34DC(s32 arg0);
void SetGameState(GameState gameState);
void func_800E4970(void);
void func_800E8DF0(void);
s32 _peek_event(void);
s32 _card_event_x(void);
void _clear_event_x(void);
void MemcardInit(void);
void MemcardInfoInit(void);
s32 func_800EA5E4(u32);
void func_800EA538(s32);
void func_800EAD7C(void);
void ResetPendingGfxLoad(void);
void LoadEquipIcon(s32 equipIcon, s32 palette, s32 index);
bool func_800EB720(void);
void HideAllBackgroundLayers(void);
void DestroyAllPrimitives(void);
s32 func_800EDAE4(void);
DR_ENV* func_800EDB08(Primitive* prim);
void DemoGameInit(s32 arg0);
void FreePrimitives(s32 index);
void DemoOpenFile(s32);
void DemoInit(s32 arg0);
s32 func_800F087C(u32, u32);
s32 SetNextRoomToLoad(u32 chunkX, u32 chunkY);
s32 func_800F0CD8(s32 arg0);
s32 func_800F16D0(void);
void resetMapTileOnCastleBlueprint(s32, s32);
void paintMapTileOnCastleBlueprint(s32, s32, s32);
void RevealSecretPassageOnMap(s32, s32, s32);
void func_800F2120(void);
void func_800F223C(void);
void func_800F4994(void);
void func_800F4F48(void);
void CalcDefense(void);
bool IsAlucart(void);
void func_800F53A4(void);
bool ScissorSprite(SPRT* arg0, MenuContext* arg1);
void MenuDrawImg(MenuContext* ctx, s32 x, s32 y, s32 w, u32 h, s32 u, s32 v,
                 s32 idx, s32 unk2, bool disableTexShade, s32 unk4);
void MenuDrawSprite(
    MenuContext* context, s32 x, s32 y, s32 width, s32 height, s32 u, s32 v,
    s32 clut, s32 tpage, s32 arg9, s32 colorIntensity, s32 argB);
void MenuDrawRect(MenuContext* context, s32 posX, s32 posY, s32 width,
                  s32 height, s32 r, s32 g, s32 b);
s32 func_800F62E8(s32 arg0);
void InitStatsAndGear(bool isDeathTakingItems);

void InitFade(void);
s32 func_801025F4(void);
void SetFadeWidth(s32 fadeWidth);
void SetFadeMode(FadeModes fadeMode);
void UpdateFade(bool skipFollowup);
void HideMap(void);

s32 TimeAttackController(TimeAttackEvents eventId, TimeAttackActions action);
s32 func_800FD664(s32 arg0);
s32 func_800FD6C4(EquipKind equipTypeFilter);
u8* GetEquipOrder(EquipKind kind);
u8* GetEquipCount(EquipKind kind);
const char* GetEquipmentName(EquipKind kind, s32 equipId);
u32 CheckEquipmentItemCount(u32 itemId, u32 equipType);
void GetSpellDef(SpellDef* spell, s32 id);
void LearnSpell(s32 spellId);
void func_800FDE00(void);
s32 func_800FE3C4(SubweaponDef* subwpn, s32 subweaponId, bool useHearts);
void GetEquipProperties(s32 handId, Equipment* res, s32 equipId);
s32 HandleDamage(DamageParam*, s32, s32 amount, s32);
s32 HandleTransformationMP(TransformationForm, CallMode);
void ClearStatBuff(s32 arg0);
bool func_8010183C(s32 arg0);
s32 func_801025F4(void);
void func_80102CD8(s32);
Entity* GetFreeEntity(s16 start, s16 end);
Entity* GetFreeEntityReverse(s16 start, s16 end);
void DestroyEntitiesFromIndex(s16 startIndex);
void SetTexturedPrimRect(
    Primitive* poly, s32 x, s32 y, s32 width, s32 height, s32 u, s32 v);
void func_801073C0(void);
void func_801092E8(s32);
void SetPrimRect(Primitive* poly, s32 x, s32 y, s32 width, s32 height);
void SetPlayerStep(s16 step);
u32 UpdateAnim(s8* frameProps, AnimationFrame** anims);
void func_8010DFF0(s32 resetAnims, s32 arg1);
void ForceAfterImageOn(void);
void EnableAfterImage(void);
s32 func_8010E334(s32 xStart, s32 xEnd);
void func_8010E470(s32, s32);
void func_8010E570(s32);
void func_8010E83C(bool);
s32 func_801104D0();
bool CheckQuarterCircleForwardInput();
bool CheckBackForwardInput();
bool CheckDarkMetamorphosisInput();
bool CheckSummonSpiritInput();
void PlayAnimation(s8*, AnimationFrame** frames);
bool CheckHellfireInput();
bool CheckTetraSpiritInput();
bool CheckSoulStealInput();
bool CheckSwordBrothersInput();
void func_80111928(void);
void func_80111CC0(void);
bool func_80111D24(void);
void func_80118894(Entity*);
Entity* func_80118970(void);
void func_80118C28(s32 arg0);
void GetServantStats(Entity* entity, s32 spellId, s32 arg2, FamiliarStats* out);
bool func_8010FDF8(s32 branchFlags);

#ifndef CREATE_FACTORY_FAKE_ARGS
Entity* CreateEntFactoryFromEntity(Entity* entity, u32, s32);
#endif

// Forward declarations for all the entity updating functions
void EntityNull(Entity* self);
void EntityFactory(Entity* self);
void EntitySmokePuff(Entity* self);
void EntityGravityBootBeam(Entity* self);
void EntitySubwpnKnife(Entity* self);
void func_8011E4BC(Entity* self);
void EntityDiveKickAttack(Entity* self);
void EntityGiantSpinningCross(Entity* self);
void EntitySubwpnCrashCross(Entity* self);
void EntitySubwpnCrashCrossParticles(Entity* self);
void EntitySubwpnThrownAxe(Entity* self);
void EntityPlayerBlinkWhite(Entity* self);
void EntitySubwpnThrownVibhuti(Entity* self);
void func_8011E0E4(Entity* self);
void func_8011EDA0();
void EntityUnarmedAttack(Entity* self);
void func_8011EDA8(Entity* self);
void EntitySubwpnAgunea(Entity* self);
void EntityAguneaHitEnemy(Entity* self);
void EntityNumberMovesToHpMeter(Entity* self);
void EntitySubwpnReboundStone(Entity* self);
void EntityLevelUpAnimation(Entity* self);
void EntitySubwpnHolyWater(Entity* self);
void EntitySubwpnHolyWaterFlame(Entity* self);
void EntityUnkId24(Entity* self);
void EntityHellfire(Entity* self);
void EntityHellfireNormalFireball(Entity* self);
void EntityHellfireBigFireball(Entity* self);
void EntityExpandingCircle(Entity* self);
void func_80127CC8(Entity* self);
void EntityHitByLightning(Entity* self);
void EntityPlayerOutline(Entity* self);
void EntityPlayerDissolves(Entity* self);
void EntityHitByIce(Entity* self);
void EntityMist(Entity* self);
void EntityWingSmashTrail(Entity* self);
void func_8011B480(Entity* self);
void EntityGuardText(Entity* self);
void EntityTransparentWhiteCircle(Entity* self);
void EntityPlayerPinkEffect(Entity* self);
void EntitySubwpnHolyWaterBreakGlass(Entity* self);
void EntityStopWatch(Entity* self);
void EntityStopWatchExpandingCircle(Entity* self);
void EntitySubwpnBible(Entity* self);
void EntitySubwpnBibleTrail(Entity* self);
void EntityBatFireball(Entity* self);
void func_80123B40(Entity* self);
void func_80119F70(Entity* self);
void UnknownEntId48(Entity* self);
void UnknownEntId49(Entity* self);
void func_80123A60(Entity* self);
void EntitySmallRisingHeart(Entity* self);
void EntityBatEcho(Entity* self);
void func_8011B530(Entity* self);
void func_8011F074(Entity* self);
void func_80130264(Entity* self);
void func_8012F894(Entity* self);
void func_80130618(Entity* self);
void func_801309B4(Entity* self);
void func_80130E94(Entity* self);
void func_8013136C(Entity* self);
void func_80129864(Entity* self);
void EntitySummonSpirit(Entity* self);
void func_80123F78(Entity* self);
void EntityTeleport(Entity* self);
void EntityPlayerSleepZ(Entity* self);

// commented as a requirement for UpdateCd to match
// void func_80131EBC(const char* str, s16 arg1);
void SetCdPos(s32 value);
void MuteCd(void);
void UnMuteCd(void);
s32 func_80131F28(void);
u16 func_80131F38(void);
bool func_80131F68(void);
s16 func_80131F94(void);
void SetMaxVolume(void);
void InitSoundVars3(void);
void InitSoundVars2(void);
void InitSoundVars1(void);
static void AddCdSoundCommand(s16);
u8 DoCdCommand(u_char com, u_char* param, u_char* result);
void SoundWait(void);
void MuteSound(void);
void func_80132A04(s16 voice, s16 vabId, s16 prog, s16 tone, s16 note,
                   s16 volume, s16 distance);
void StopSeq(void);
bool CdSoundCommandQueueEmpty(void);
bool func_80133950(void);
void func_80133FCC(void);
void SetReleaseRate2(void);
void func_801361F8(void);

#endif
