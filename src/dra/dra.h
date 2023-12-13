#ifndef DRA_H
#define DRA_H
#define INCLUDE_ASM_NEW

#include "game.h"
#include "weapon.h"
#include "items.h"

#define DAMAGE_FLAG_NORMAL 0x0000
#define DAMAGE_FLAG_CRITICAL 0x4000
#define DAMAGE_FLAG_ABSORB 0x8000
#define DAMAGE_FLAG_IMMUNE 0xC000

#define SFX_START (0x600)
#define SFX_LAST (0x8E0)
#define MAX_SND_COUNT (0x100)

#define SEQ_TABLE_S_MAX 0x10
#define SEQ_TABLE_T_MAX 1

#define RED_MASK 0x1F
#define GREEN_MASK 0x3E0
#define BLUE_MASK 0x7C00

#define GET_RED(x) ((x)&RED_MASK)
#define GET_GREEN(x) ((x)&GREEN_MASK)
#define GET_BLUE(x) ((x)&BLUE_MASK)

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
    u8* addr;         // where to load the file to
    s32 size;         // file size
    SimKind kind;
} SimFile;

typedef enum {
    CdStep_None,
    CdStep_LoadInit,
    CdStep_SetSpeed,
    CdStep_SetPos,
    CdStep_Seek,
    CdStep_5,
    CdStep_6,
    CdStep_Complete = 10,
    CdStep_DmaErr = 0xC0,
    CdStep_SdHeaderErr = 0xC1,
    CdStep_DiskErr = 0xC2,
    CdStep_Retry = 0xD0,
    CdStep_RetryXa = 0xD1,
    CdStep_CdShellOpenErr = 0xF0,
    CdStep_F1 = 0xF1,
    CdStep_F2 = 0xF2,
    CdStep_F3 = 0xF3,
} CdStep;

typedef enum {
    CdFile_None,
    CdFile_Sel,
    CdFile_GameChr,
    CdFile_StageChr,
    CdFile_4,
    CdFile_RichterPrg,
    CdFile_Seq = 12,
    CdFile_StageSfx,
    CdFile_14,
    CdFile_15,
    CdFile_16,
    CdFile_Weapon0,
    CdFile_Weapon1,
    CdFile_AlucardPrg,
    CdFile_24 = 24,
    CdFile_25,
    CdFile_26,
    CdFile_ServantChr,
    CdFile_Monster,
    CdFile_ServantPrg,
    CdFile_30,
    CdFile_31,
    CdFile_DemoKey,
    CdFile_NoNext = 0xFF,
    CdFile_StagePrg = 0x100,
} CdFileType;

typedef enum {
    CdCallback_0,        // func_801080DC
    CdCallback_1,        // func_801080DC
    CdCallback_2,        // func_801080DC
    CdCallback_3,        // func_801080DC
    CdCallback_4,        // CopyStageOvlCallback
    CdCallback_5,        // func_801080DC
    CdCallback_6,        // func_801080DC
    CdCallback_7,        // func_801080DC
    CdCallback_StagePrg, // CopyStageOvlCallback
    CdCallback_9,        // CopyStageOvlCallback
    CdCallback_Ric,      // CopyRicOvlCallback
    CdCallback_11,       // func_801080DC
    CdCallback_12,       // func_801078C4
    CdCallback_13,       // func_801078C4
    CdCallback_Monster,  // CopyMonsterPreviewCallback
    CdCallback_Familiar, // func_801078C4
    CdCallback_16,       // func_80107DB4
    CdCallback_17,       // func_80107C6C
    CdCallback_Seq,      // func_80107DB4
    CdCallback_Vh,       // func_80107EF0
} CdCallbacks;

typedef enum {
    E_NONE,
    E_ENTITYFACTORY,

    ENTITY_13 = 0x13,
    E_UNK_22 = 0x22,
} EntityIDs;

typedef enum {
    Player_Stand,
    Player_Walk,
    Player_Crouch,
    Player_Fall,
    Player_Jump,
    Player_MorphBat,
    Player_AlucardStuck,
    Player_MorphMist,
    Player_HighJump,
    Player_UnmorphBat,
    Player_Hit,
    Player_StatusStone,
    Player_BossGrab, // Darkwing Bat and Akmodan II
    Player_KillWater,
    Player_UnmorphMist,
    Player_SwordWarp, // Alucard Sword and Osafune Katana
    Player_Kill,
    Player_Unk17,
    Player_Teleport, // also Grand Cross and Spiral Axe
    Player_FlameWhip,
    Player_Hydrostorm,
    Player_ThousandBlades,
    Player_RichterFourHolyBeasts,
    Player_Slide,
    Player_Unk24, // MorphWolf and Richter's Tackle
    Player_Unk25, // UnMorphWolf and Sprint
    Player_SlideKick,
    Player_Unk27, // other item crashes
    Player_SpellDarkMetamorphosis = 32,
    Player_SpellSummonSpirit,
    Player_SpellHellfire,
    Player_SpellTetraSpirit,
    Player_Spell36,
    Player_SpellSoulSteal,
    Player_Unk38,
    Player_SpellSwordBrothers,
    Player_AxearmorStand,
    Player_AxearmorWalk,
    Player_AxearmorJump,
    Player_AxearmorHit,
} PlayerSteps;

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
    RECT D_800ACD80;
    RECT D_800ACD88;
    RECT D_800ACD90;
    RECT D_800ACD98;
    RECT D_800ACDA0;
    RECT D_800ACDA8;
    RECT D_800ACDB0;
    RECT D_800ACDB8;
    RECT D_800ACDC0;
    RECT D_800ACDC8;
    RECT D_800ACDD0;
    RECT D_800ACDD8;
    RECT D_800ACDE0;
    RECT D_800ACDE8;
    RECT D_800ACDF0;
} Vram;

typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ const char* combo;
    /* 0x08 */ const char* description;
    /* 0x0C */ u8 mpUsage;
    /* 0x0D */ s8 nFramesInvincibility;
    /* 0x0E */ s16 stunFrames;
    /* 0x10 */ s16 hitboxState;
    /* 0x12 */ s16 hitEffect;
    /* 0x14 */ s16 entityRoomIndex;
    /* 0x16 */ u16 attackElement;
    /* 0x18 */ s16 attack;
    /* 0x1A */ s16 unk1A;
} SpellDef;

typedef struct {
    u32 unk0;
    u32 damageKind;
    s32 damageTaken;
    s32 unkC;
} DamageParam;

typedef struct {
    /* 8013761C */ MenuContext menus[0x10]; // 761C, 763A, 7658, 7676
} MenuData;

// All the Joseph's Cloak color fields are in RGB555 format
typedef struct {
    u16 liningDark;
    u16 liningLight;
    u16 exteriorDark;
    u16 exteriorLight;
} JosephsCloak;

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
} ButtonComboIdx;

typedef struct {
    s16 buttonsCorrect;
    s16 timer;
} ButtonComboState;

struct SeqData {
    u8 volume;
    u8 reverb_depth;
    union unk2 {
        struct {
            u8 one_shot : 4;
            u8 vab_id : 4;
        } info;
    } unk2;
};

struct XaMusicConfig {
    u32 cd_addr;
    s32 unk228;
    u8 filter_file;
    u8 filter_channel_id;
    u8 volume;
    u8 unk22f;
    u8 unk230;
    u8 pad[3];
};

struct Cmd14 {
    u8 unk0[8];
    s32 unk8;
    s16 unkc;
    s8 unke;
};

// Used for the button combos to signal successfully completing the sequence
#define COMBO_COMPLETE 0xFF

// File list:
extern u8 aPqes[];   // TODO: extract file
extern u8 aPqes_0[]; // TODO: extract file
extern u8 aPqes_1[]; // TODO: extract file
extern u8 aPbav[];   // TODO: extract file
extern u8 aPbav_0[]; // TODO: extract file
extern u8 aPbav_1[]; // TODO: extract file
extern u8 aPbav_2[]; // TODO: extract file

extern u16 g_ButtonMask[];
extern u8 g_StageSelectOrder[];
extern u16 D_800A04CC[];
extern u32 D_800A04F8;
extern s32 D_800A2438;
extern u8 D_800A2EE8[];
extern u8 D_800A2EED;
extern u8 D_800A2EF8[];
extern u8 D_800A2EFD;
extern u8 D_800A2F08[];
extern u8 D_800A2F18[];
extern u8 D_800A2F28[];
extern u8 D_800A2F2D;
extern u8 D_800A2F38[];
extern u8 D_800A2F3D;
extern u16 D_800A2F48[];
extern u16 D_800A2F64[];
extern s16 D_800A2F7E[];
extern u8 D_800A2F9B[];
extern s32 D_800A2FBC[];
extern s32 D_800A2FC0[];

extern RoomTeleport D_800A245C[];
extern u32 D_800A2D24;
extern const char* c_strALUCARD[];
extern const char** c_strSTR;
extern const char* c_strCON;
extern const char* c_strINT;
extern const char* c_strLCK;
extern const char* c_strEXP;
extern const char* c_strNEXT;
extern const char* c_strGOLD[];
extern const char* c_strLEVEL;
extern const char* c_strTIME;
extern const char* c_strROOMS;
extern const char* c_strKILLS;
extern const char* c_strHP;
extern const char* c_strMP;
extern const char* c_strHEART;
extern const char* c_strSTATUS;
extern const char* c_strButton;
extern const char* c_strCloak;
extern const char* c_strCloak2;
extern const char* c_strExterior;
extern const char* c_strLining;
extern const char* c_strButtonRightHand[];
extern const char* c_strButtonLeftHand;
extern const char* c_strButtonJump;
extern const char* c_strButtonSpecial;
extern const char* c_strButtonWolf;
extern const char* c_strButtonMist;
extern const char* c_strButtonBat;
extern const char* c_strNormal;
extern const char* c_strReversal;
extern const char* c_strSound;
extern const char* c_strStereo;
extern const char* c_strMono;
extern const char* c_strWindow;
extern const char* c_strTime;
extern const char* c_strALUCART;
extern const char* D_800A83AC[];
extern const char* c_strSSword;
extern s32 D_800A3194[];
extern Unkstruct_801092E8 D_800A37D8;
extern JosephsCloak g_JosephsCloak;
extern Lba g_StagesLba[];
extern GfxBank** g_GfxSharedBank[];
extern UnkStructClut* D_800A3BB8[];
extern SubweaponDef g_SubwpnDefs[];
extern SpellDef g_SpellDefs[];
extern const char* g_WingSmashComboStr;
extern EnemyDef g_EnemyDefs[];
extern s32 g_ExpNext[];
extern Equipment g_EquipDefs[];
extern Accessory g_AccessoryDefs[];
extern RelicDesc g_RelicDefs[];
extern u8* c_strTimeAttackHiddenEntry;
extern s32 c_strTimeAttackEntries[];
extern u32 D_800AC90C;
extern u16 D_800AC958[];
extern s32 D_800ACC64[]; // probably a struct
extern Vram g_Vram;
extern CdFile* D_800ACC74[];
extern u8 D_800ACF54[];
extern u8 D_800ACFB4[][4];
#if defined(VERSION_HD)
extern s32 D_800ACEDC_hd;
#endif
extern s32 D_800ACE44;
extern s32 D_800ACE48[];
extern RECT D_800ACE60;
extern s16 D_800ACE88[];
extern s16 D_800ACE90[];
extern s16_pair D_800ACEC0[4];
extern Unkstruct_800ACED0 D_800ACED0;
extern u8 D_800ACF4C[];
extern s32 D_800ACF74; // These two might...
extern s32 D_800ACF78; // ...be an array
extern unkstruct_800ACF7C D_800ACF7C[];
extern s16 D_800ACF8A[]; // collection of sounds?
extern s16 D_800ACF60[]; // collection of sounds?
extern s16 D_800ACF6C[];
extern s16 D_800ACF94[];
extern u8 D_800AD094[];
extern PfnEntityUpdate D_800AD0C4[];
extern FactoryBlueprint g_FactoryBlueprints[];
extern u8 D_800AD4B8[];
extern AnimSoundEvent* D_800AD53C[];
extern AnimationFrame D_800AD57C[];
extern AnimationFrame D_800AD5FC[];
extern AnimationFrame D_800ADBD4[];
extern AnimationFrame D_800ADC10[];
extern s32 D_800ADC44;
extern RECT D_800AE130;
extern s32 D_800AE270[];
extern AnimationFrame* D_800AE294;
extern s16 D_800AFDA6[];
extern unkStr_8011E4BC* D_800ADB98[];
extern const char* c_strEquip;
extern const char* c_strSpells;
extern const char* c_strRelics;
extern const char* c_strSystem;
extern const char* c_strFamiliars;
extern const char* c_strFamiliar;
extern const char* c_strSpecial2;
extern RECT c_backbufferClear;
extern s16 D_800AFFB8[];
extern s32 D_800B0130[];
extern s32 D_800B01B8[];
extern u8 D_800B0608[];
extern u32 D_800B06C8;
extern u32 D_800B0728;
extern RECT D_800B0788;
extern RECT D_800B0790;
extern AnimationFrame D_800B0798[];
extern s32 D_800B07C8;
extern s32 D_800B0830[];
extern s32 D_800B083C[];
extern unk_800B08CC D_800B08CC[];
extern s32 D_800B0914;
extern s32 D_800B0918;
extern s32 D_800B091C;
extern s32 D_800B0920;
extern u8 D_800B0F94[][5];
extern SVECTOR* D_800B0CB4[][4];
extern s16 g_CdVolumeTable[];
extern s16 g_VolumeTable[];
extern struct SeqData g_SeqInfo[];
extern struct XaMusicConfig g_XaMusicConfigs[];
extern s32 g_DebugEnabled;
extern s32 D_800BD1C4;
extern s32 g_VabAddrs[6];
extern s32 D_800C1ECC[];
extern PixPattern* D_800C52F8[];
extern const char D_800DB524[];
extern const char a0104x04x;
extern const char a2304x04x;
extern const char aBlue;
extern u8 g_GfxEquipIcon[32][16 * 16 / 2];
extern s16 g_PalEquipIcon[32];
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

extern char* aErrorStep;
extern char* aAtariNuki;
extern char* aLightTimer02x;
extern SVECTOR D_800E2024;
extern SVECTOR D_800E202C;
extern s32 g_DebugFreeze;
extern s32 g_DebugHitboxViewMode;
extern u32 D_801362B4;
extern s32 D_801362B8;
extern s32 D_801362BC;
extern s32 g_DebugPalIdx;
extern DebugColorChannel g_DebugColorChannel;
extern u32 D_801362C8;
extern u32* g_CurrentOT;
extern s32 D_801362D0[];
extern s32 D_801362D4;
extern s32 g_DebugIsRecordingVideo;
extern GpuUsage g_GpuMaxUsage;
extern s32 g_softResetTimer;
extern s32 g_DebugWaitInfoTimer;
extern s32 g_DebugRecordVideoFid;
extern s16 D_80136308[];
extern s32 D_8013640C;
extern s32 D_80136410;
extern s32 D_80136414[];
extern SimFile* g_SimFile;
extern SimFile D_80136450;
extern s16 D_80136460[];
extern s16 D_80136C60[];
extern u8 g_PadsRepeatTimer[BUTTON_COUNT * PAD_COUNT];
extern s32 D_80137428[];
extern s32 g_MemcardRetryCount;
extern s32 g_MemcardFd;
extern u16 D_80137478[0x20];
extern u16 D_801374B8[0x20];
extern u16 D_801374F8[0x20];
extern u16 D_80137538[0x20];
extern u8* g_DecSrcPtr;
extern u8* g_DecDstPtr;
extern s32 g_DecReadNibbleFlag;
extern s32 g_DecWriteNibbleFlag;
extern u8* D_80137590;
extern s32 D_80137594; // g_DemoKeyIdx
extern s32 D_80137598;
extern s32 D_8013759C;
extern s32 D_801375A0;
// Note that these overlap; these should be f32's for X and Y.
extern s32 D_801375A4;
extern s16 D_801375A6;
extern s32 D_801375A8;
extern s16 D_801375AA;

extern s32 D_801375AC;
extern s32 D_801375B0;
extern s32 D_801375B4;
extern s32 D_801375B8;
// clues indicate being in a struct, unclear what else is with it though.
extern RoomLoadDefHolder D_801375BC;
extern s32 D_801375C0;
extern s32 D_801375C4;
extern s32 D_801375C8;
extern ItemTypes D_801375CC;
extern s32 D_801375D0;
extern s32 D_801375D4;
extern s32* D_801375D8;
extern s32 D_801375DC[0];
extern s32 D_801375E0[8];
extern s32 D_801375FC;
extern s32 D_80137608;
extern s32 g_IsCloakLiningUnlocked;
extern s32 g_IsCloakColorUnlocked;
extern s32 g_IsSelectingEquipment;
extern s32 g_EquipmentCursor;
extern s32 D_80137614;
extern s32 D_80137618;
extern MenuData g_MenuData;
extern u8 D_801376B0;
extern s16 D_801376C4;
extern s16 D_801376C8;
extern MenuContext g_JosephsCloakContext;
extern s32 D_8013783C;
extern s32 D_801377FC[0x10];
extern s32 D_80137840;
extern s32 D_80137844[];
extern s32 D_80137848[];
extern s32 D_8013784C;
extern s16 g_RelicMenuFadeTimer;
extern s32 g_TimeAttackEntryTimes[];
extern s32 c_strTimeAttackEntry[];
extern s32 c_strTimeAttackGoals[];
extern s32 g_NewAttackRightHand;
extern s32 g_NewAttackLeftHand;
extern s32 g_NewDefenseEquip;
extern s32 g_NewPlayerStatsTotal[];
extern s32 D_80137948;
extern s8* D_8013794C; // Pointer to texture pattern
extern s32 D_80137950;
extern s32 D_80137954;
extern s32 D_80137958;
extern s32 g_ServantPrevious;
extern s32 D_80137960;
extern s32 D_80137964;
extern s32 D_80137968;
// not actually an array, likely a struct member
extern u32 g_DisplayHP[];
extern s32 D_80137970;
extern s32 D_80137974;
extern u32 D_80137978;
extern u32 D_8013797C;
extern s32 D_80137980;
extern s32 D_80137984;
extern u32 D_80137988;
extern u32 D_8013798C;
extern Unkstruct_80137990 D_80137990;
extern s32 D_80137994;
// not actually an array, likely a struct member
extern s32 g_HealingMailTimer[];
extern u32 D_8013799C;
extern s32 D_801379A0;
extern s32 D_801379A4;
extern s32 D_801379A8;
extern Unkstruct_80102CD8 D_801379AC;
extern s32 D_801379B0;
extern s32 D_80137E40;
extern s32 D_80137E44;
extern s32 D_80137E48;
extern s32 D_80137E4C;
extern s32 D_80137E50;
extern s32 D_80137E54;
extern s32 D_80137E58;
extern s32 D_80137E5C;
extern s32 D_80137E60; // most likely part of the g_Cd struct
extern s32 D_80137E64; // most likely part of the g_Cd struct
extern s32 D_80137E68; // most likely part of the g_Cd struct
extern s32 D_80137E6C;
extern s32 D_80137F6C; // most likely part of the g_Cd struct
extern void* D_80137F7C;
extern s32 D_80137F9C;
extern s32 D_80137FB4;
extern s32 D_80137FB8;
extern s32 D_80137FBC;
extern s16 g_WasFacingLeft;  // for QCF to tell what's "forward"
extern s16 g_WasFacingLeft2; // for BF to tell what's "forward"
extern s32 g_WasFacingLeft3; // for dark metamorphosis "" ""
extern s32 g_WasFacingLeft4; // for summon spirit "" ""
extern s16 g_WasFacingLeft5; // for hellfire "" ""
extern s32 g_WasFacingLeft6; // for tetra spirit "" ""
extern s32 g_WasFacingLeft7; // for soul steal "" ""
extern s32 D_80137FDC;
extern s32 D_80137FE0;
extern s32 D_80137FE4;
extern s32 D_80137FE8;
extern u32 g_WingSmashButtonCounter;
extern s32 g_WingSmashButtonTimer;
extern s32 g_WingSmashTimer;
extern s32 g_BatScreechDone;
extern s32 g_MistTimer; // remaining time in mist transformation
extern s32 D_80138008;
extern s32 D_8013800C[];
extern s32 D_80138038;
extern u8 D_8013803C;
extern u8 D_80138040;
extern u8 D_80138044;
extern u8 D_80138048;
extern s16_pair D_8013804C[];
extern s32 D_8013808C;
extern Unkstruct_80138094 D_80138094[];
extern s32 D_8013841C;
extern s32 D_8013842C;
extern s32 D_80138430;
extern s32 D_80138438;
extern s32 D_80138440;
extern s32 D_80138444;
extern s32 D_80138454;
extern char g_SeqTable[SS_SEQ_TABSIZ * SEQ_TABLE_S_MAX * SEQ_TABLE_T_MAX];
extern const char* D_80138784[]; // 487?
extern s32 g_CurCdPos;
extern u8 g_CdMode[];
extern u8 g_CdCommandResult[];
extern s32 g_KeyOffChannels;
extern s32 D_80138F7C;
extern s16 D_80138F80;
extern s32 g_SeqPointers[];
extern s16 g_SfxRingBufferReadPos;
extern DebugMode g_DebugMode;
extern s16 g_VolL; // vol_l
extern SpuVoiceAttr* D_80138FB4;
extern s16 D_80138FBC;
extern s32 D_80139060;
extern SpuVoiceAttr* D_801390C8;
extern SpuVoiceAttr* D_801390CC;
extern ButtonComboState g_ButtonCombo[16];
extern s16 D_80138FC8;
extern s16 D_80138FCA;
extern s16 g_sfxRingBufferWritePos; // D_80139000
extern s16 g_VolR;                  // vol_r
extern s32 D_80139008;
extern s16 D_80139010;
extern u8 D_80139014;
extern s8 D_80139018[];
extern u32 g_DebugCurPal;
extern s16 D_8013901C;
extern u8 g_MuteCd;
extern s8 D_80139058[];
extern s32 g_PrevEquippedWeapons[2];
extern s16 g_SeqVolume1;
extern u8 D_801390A0;
extern s16 D_801390A4;
extern u8 D_801390A8;
extern s16 D_801390AC[];
extern s32 D_801390B4[];
extern s8 D_801390C4;
extern GpuBuffer* g_BackBuffer;
extern u8 D_801390D8;
extern SfxRingBufferItem g_SfxRingBuffer[MAX_SND_COUNT];
extern u16 D_801396E0;
extern u16 D_801396E4;
extern Multi D_801396E6;
extern u16 D_801396E8;
extern s16 D_801396EA;
extern u16 D_801396EC;
extern s32 g_CdCommandStatus;
extern volatile s16 g_CdSoundCommandQueuePos;
extern s32 D_801396F8[0x20];
extern s32 D_80139778[0x20];
extern s32 D_801397FC;
extern s16 D_80139800;
extern s16 D_80139804;
extern s32 D_8013980C;
extern u8 g_SeqPlayingId;
extern s16 D_80139814[];
extern s16 g_XaMusicVolume;
extern s32 D_80139824;
extern s32 D_80139828[];
extern s32 D_8013982C;
extern s32 D_80139830[];
extern s32 D_8013983C;
extern s32 D_80139840;
extern s32 D_80139844;
extern s32 D_80139848;
extern s32 D_8013984C;
extern s32 D_80139850;
extern s32 D_80139854;
extern s16 g_CdSoundCommandQueue[MAX_SND_COUNT];
extern s16 g_SoundCommandRingBufferReadPos;
extern s16 D_80139A6C;
extern s16 g_SoundCommandRingBufferWritePos; // D_80139A70
extern s16 D_80139A74;
extern s16 D_80139A78;
extern u_long* D_80139A7C;
extern u16 D_8013AE7C;
extern volatile unsigned char g_CdSoundCommandStep;
extern s16 g_UnkChannelSetting2[];
extern s16 D_8013AE8C;
extern s16 D_8013AEA0[];
extern s16 D_8013AE94;
extern u8 g_ReverbDepth;
extern s32 D_8013AE9C;
extern s32 D_8013AECC;
extern s32 D_8013AED0;
extern s16 D_8013AED4[];
extern s32 D_8013AEE4;
extern s16 g_volumeL;
extern s16 g_volumeR;
extern s16 D_8013B678[];
extern s16 D_8013B698;
extern u8 D_8013B6A0[]; // VAB file
extern u8 D_8017D350[]; // VAB file
extern u8 D_8018B4E0[]; // VAB file
extern u8 D_801A9C80[]; // VAB file
extern u16 D_8013AEE0;
extern s8 D_8013AEE8;
extern u8 g_SoundInitialized;
extern s16 g_SeqVolume2;
extern s32 D_8013B158;
extern s32 D_8013B3D0;
extern s16 g_SoundCommandRingBuffer[MAX_SND_COUNT]; // D_8013B3E8
extern s32 D_8013B5E8;
extern u8 D_8013B5EC[];
extern s8 g_UnkChannelSetting1[];
extern s8 D_8013B618;
extern s32 D_8013B61C;
extern s16 g_ChannelGroupVolume[];
extern s32 D_8013B628[];
extern s16 D_8013B648[];
extern s16 D_8013B650[];
extern s16 g_SeqAccessNum;
extern s32 g_MemcardStep;
extern s16 D_8013B664;
extern s16 g_CdVolume;
extern s16 D_8013B66C[];
extern u8 D_8013B680;
extern u8 g_CdSoundCommand16;
extern s8 D_8013B690;
extern s32 D_8013B694;
extern s32 D_8013B69C;
extern s32 D_8016FCC0[];
extern void (*D_8013C000)(void);
extern void (*D_8013C004)(s32);
extern void (*D_8013C008)(void);
extern void (*D_8013C00C)(void);
extern PfnEntityUpdate D_80179C80[];
extern Weapon D_8017A000;
extern PfnEntityUpdate D_8017CC40[];
extern Weapon D_8017D000;
extern void (*D_80170000)(s32 arg0);
extern ImgSrc* g_imgUnk8013C200;
extern ImgSrc* g_imgUnk8013C270;
extern u8 D_801EC000[];
extern u8 D_8013B688[];
extern struct Cmd14 D_8013B5F4[];

void InitializePads(void);
void ReadPads(void);
void ClearBackbuffer(void);
void SetRoomForegroundLayer(LayerDef* layerDef);
void SetRoomBackgroundLayer(s32 index, LayerDef* layerDef);
void CheckCollision(s32 x, s32 y, Collider* res, s32 unk);
void DemoInit(s32 arg0);
void DemoUpdate(void);
void func_800E346C(void);
void func_800E34A4(u8 arg0);
void func_800E34DC(s32 arg0);
void SetGameState(GameState gameState);
void func_800E4970(void);
s32 LoadFileSim(s32 id, SimFileType type);
void ResetPadsRepeat(void);
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
void DestroyPrimitive(Primitive* prim);
void DestroyAllPrimitives(void);
void func_800EDAE4(void);
s32 AllocPrimitives(u8 type, s32 count);
s32 func_800EDD9C(u8 primitives, s32 count);
void DemoGameInit(s32 arg0);
void FreePrimitives(s32 index);
void DemoOpenFile(s32);
void DemoInit(s32 arg0);
s32 func_800F087C(u32, u32);
s32 SetNextRoomToLoad(u32 chunkX, u32 chunkY);
s32 func_800F0CD8(s32 arg0);
s32 func_800F16D0(void);
void func_800F1868(s32, s32, u8*);
void func_800F18C4(s32, s32);
void func_800F1954(s32, s32, s32);
void func_800F1EB0(s32, s32, s32);
void func_800F2120(void);
void func_800F223C(void);
void func_800F4994(void);
s32 CalcAttack(s32, s32);
void func_800F4F48(void);
void CalcDefense(void);
bool IsAlucart(void);
void func_800F53A4(void);
bool ScissorSprite(SPRT* arg0, MenuContext* arg1);
void DrawMenuImg(MenuContext* ctx, s32 x, s32 y, s32 w, u32 h, s32 u, s32 v,
                 s32 idx, s32 unk2, bool disableTexShade, s32 unk4);
void DrawMenuSprite(
    MenuContext* context, s32 x, s32 y, s32 width, s32 height, s32 u, s32 v,
    s32 clut, s32 tpage, s32 arg9, s32 colorIntensity, s32 argB);
void DrawMenuRect(MenuContext* context, s32 posX, s32 posY, s32 width,
                  s32 height, s32 r, s32 g, s32 b);
s32 func_800F62E8(s32 arg0);
void InitStatsAndGear(bool isDeathTakingItems);
void DrawMenuChar(u8 ch, int x, int y, MenuContext* context);
void DrawMenuStr(const u8* str, s32 x, s32 y, MenuContext* context);
void DrawMenuInt(s32 value, s32 x, s32 y, MenuContext*);
void DrawSettingsReverseCloak(MenuContext* context);
void DrawSettingsSound(MenuContext* context);
void DrawPauseMenu(s32 arg0);
void func_800F82F4(void);
void func_800F8858(MenuContext* context);
void CheckWeaponCombo(void);
void func_800FABEC(s32 arg0);
void func_800FAC30(void);
void func_800FAF44(s32);
s32 TimeAttackController(TimeAttackEvents eventId, TimeAttackActions action);
s32 func_800FD664(s32 arg0);
s32 func_800FD6C4(s32 equipTypeFilter);
u8* GetEquipOrder(s32 equipTypeFilter);
u8* GetEquipCount(s32 equipTypeFilter);
const char* GetEquipmentName(s32 equipTypeFilter, s32 equipId);
u32 CheckEquipmentItemCount(u32 itemId, u32 equipType);
void AddToInventory(u16 itemId, s32 itemCategory);
void func_800FD9D4(SpellDef* spell, s32 id);
s16 GetStatusAilmentTimer(StatusAilments statusAilment, s16 timer);
void LearnSpell(s32 spellId);
void func_800FDE00(void);
s32 func_800FE3C4(SubweaponDef* subwpn, s32 subweaponId, bool useHearts);
void GetEquipProperties(s32 handId, Equipment* res, s32 equipId);
s32 HandleDamage(DamageParam*, s32, s32 amount, s32);
s32 HandleTransformationMP(TransformationForm, CallMode);
void func_800FF0A0(s32 arg0);
bool func_8010183C(s32 arg0);
s32 func_801025F4(void);
void func_80102CD8(s32);
void func_80102DEC(s32 arg0);
void func_80103EAC(void);
void DestroyEntity(Entity*);
void DestroyEntities(s16 startIndex);
void func_801071CC(POLY_GT4* poly, u32 colorIntensity, s32 vertexIndex);
void func_80107250(POLY_GT4* poly, s32 colorIntensity);
void SetTexturedPrimRect(
    Primitive* poly, s32 x, s32 y, s32 width, s32 height, s32 u, s32 v);
void func_801073C0(void);
void func_801092E8(s32);
void SetPrimRect(Primitive* poly, s32 x, s32 y, s32 width, s32 height);
void SetPlayerStep(PlayerSteps step);
u32 UpdateAnim(s8* frameProps, s32*);
void func_8010DFF0(s32, s32);
void func_8010E0A8(void);
void func_8010E0B8(void);
void func_8010E470(s32, s32);
void func_8010E570(s32);
void func_8010E83C(s32 arg0);
s32 func_801104D0();
bool CheckQuarterCircleForwardInput();
bool CheckBackForwardInput();
bool CheckDarkMetamorphosisInput();
bool CheckSummonSpiritInput();
void func_8010DBFC(s32*, s32*);
bool CheckHellfireInput();
bool CheckTetraSpiritInput();
bool CheckSoulStealInput();
bool CheckSwordBrothersInput();
void func_80111928(void);
void func_80111CC0(void);
bool func_80111D24(void);
void func_80115394(s32*, s16, s16);
void func_80115C50(void);
void func_80118894(Entity*);
void func_80118C28(s32 arg0);
void func_80118D0C(Entity* entity);
void func_80119588(Entity* entity);
void func_80119D3C(Entity* entity);
void func_80119F70(Entity* entity);
void func_8011A3AC(
    Entity* entity, s32 arg1, s32 arg2, Unkstruct_8011A3AC* arg3);
void func_8011A4C8(Entity* entity);
Entity* CreateEntFactoryFromEntity(Entity* entity, u32, s32);
void EntityEntFactory(Entity* entity);
void EntityUnarmedAttack(Entity* entity);
void func_8011B334(Entity* entity);
void func_8011B480(Entity* entity);
void func_8011B530(Entity* entity);
void func_8011B5A4(Entity* entity);
void EntityUnkId24(Entity* entity);
void func_8011BDA4(Entity* entity);
void func_8011D9F8(Entity* entity);
void func_8011E0E4(Entity* entity);
void EntityGravityBootBeam(Entity* entity);
void EntityWingSmashTrail(Entity* entity);
void func_8011E4BC(Entity* entity);
void func_8011EDA0(Entity* entity);
void func_8011EDA8(Entity* entity);
void func_8011F074(Entity* entity);
void func_8011F24C(Entity* entity);
void func_8011F934(Entity* entity);
void func_801200AC(Entity* entity);
void func_80120AF8(Entity* entity);
void func_80120DD0(Entity* entity);
void func_80121980(Entity* entity);
void func_8012231C(Entity* entity);
void func_80123788(Entity* entity);
void func_801238CC(Entity* entity);
void func_80123A60(Entity* entity);
void func_80123B40(Entity* entity);
void func_80123F78(Entity* entity);
void func_801243B0(Entity* entity);
void func_80124A8C(Entity* entity);
void func_80124B88(Entity* entity);
void func_80125330(Entity* entity);
void func_80125C2C(Entity* entity);
void func_80125E68(Entity* entity);
void func_801262AC(Entity* entity);
void func_801267B0(Entity* entity);
void func_80126C48(Entity* entity);
void EntityHellfireHandler(Entity* entity);
void func_801274DC(Entity* entity);
void EntityBatFireball(Entity* entity);
void func_80127840(Entity* entity);
void func_801279FC(Entity* entity);
void func_80127CC8(Entity* entity);
void func_80127F40(Entity* entity);
void func_80128714(Entity* entity);
void func_80128C2C(Entity* entity);
void func_801291C4(Entity* entity);
void func_80129864(Entity* entity);
void func_8012A0A4(Entity* entity);
void func_8012A528(Entity* entity);
void func_8012A89C(Entity* entity);
void func_8012B78C(Entity* entity);
void func_8012B990(Entity* entity);
void func_8012BEF8(Entity* entity);
// Can't have this here because func_8012D3E8 does a bad call
// which passes a 0 argument.
// void func_8012CA64(void);
void func_8012CB4C(void);
void func_8012CCE4(void);
void func_8012CFA8(void);
void func_8012F894(Entity* entity);
void func_80130264(Entity* entity);
void func_80130618(Entity* entity);
void func_801309B4(Entity* entity);
void func_80130E94(Entity* entity);
void func_8013136C(Entity* entity);
void EntityGiantSpinningCross(Entity* entity);
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
s32 func_801326D8(void);
void AddCdSoundCommand(s16);
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