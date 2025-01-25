// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef DRA_H
#define DRA_H

#include "disk.h"
#include "game.h"
#include "weapon.h"
#include "servant.h"
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
    u8* addr;         // where to load the file to
    s32 size;         // file size
    SimKind kind;
} SimFile;

typedef enum {
    E_NONE,
    E_ENTITYFACTORY,

    ENTITY_13 = 0x13,
    E_UNK_22 = 0x22,
} EntityIDs;

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
#ifdef VERSION_US
    RECT D_800ACDF0;
#endif
} Vram;

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
    /* 0x14 */ u16 speed;
    /* 0x16 */ s16 waveTable[NOW_LOADING_PRIM_COUNT];
} NowLoadingModel; // size=0x36

typedef struct {
    /* 8013761C */ MenuContext menus[NUM_MENU]; // 761C, 763A, 7658, 7676
} MenuData;

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
} PlayerHud;

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

typedef struct Cmd14 {
    u8 unk0[8];
    s32 unk8;
    s16 unkc;
    s8 unke;
} Cmd14;

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

extern u16 g_ButtonMask[];
extern u8 g_StageSelectOrder[];
extern u16 D_800A04CC[];
extern u32 D_800A04F8;
extern s32 D_800A2438;

extern RoomTeleport D_800A245C[];
extern u32 D_800A2D24;
extern const char* D_800A83AC[];

extern SVECTOR* D_800A3608[];
extern MATRIX D_800A37B8;
extern u16 D_800A37D8[2];
extern u16 g_JosephsCloakColors[4];
extern GfxBank** g_GfxSharedBank[];
extern s16** D_800A3B70[18];
extern u_long* D_800A3BB8[];
extern Lba g_StagesLba[80];

extern SubweaponDef g_SubwpnDefs[13];
// These are different on PSP since they have text that needs translating.
#if defined(VERSION_PSP)
extern RelicDesc* g_RelicDefs;
extern SpellDef* g_SpellDefs;
extern EnemyDef* g_EnemyDefs;
extern Accessory* g_AccessoryDefs;
extern Equipment* g_EquipDefs;
#else
extern RelicDesc g_RelicDefs[30];
extern SpellDef g_SpellDefs[28];
extern EnemyDef g_EnemyDefs[400];
extern Accessory g_AccessoryDefs[90];
extern Equipment g_EquipDefs[217];
#endif
extern const char* g_MenuStr[110];
extern s32 g_ExpNext[];
extern u16 D_800AC958[];
extern CdFile* D_800ACC74[];
extern s32 g_CurrentStream;
extern Vram g_Vram;
extern s32 D_800ACE44;
extern s16 g_SensorsCeilingDefault[];
extern s16 g_SensorsFloorDefault[];
extern s16 g_SensorsWallDefault[];
extern Point16 g_SensorsCeiling[];
extern Point16 g_SensorsFloor[];
extern Point16 g_SensorsWall[];
#if defined(VERSION_HD)
extern s32 D_800ACEDC_hd;
#endif
extern s32 D_800ACF74; // These two might...
extern s32 D_800ACF78; // ...be an array
extern s16 D_800ACF7C[4];
extern s16 g_SfxPainGrunts[8]; // Alucard's random pain sfx table
extern s16 D_800ACF94[16];
extern u8 D_800AD094[0x30];
extern u8 D_800ACFB4[][4]; // TODO AnimationFrames*[]
extern s16* D_800CF324[];
extern unkstr_800cfe48* D_800CFE48[18];
extern PfnEntityUpdate D_800AD0C4[];
extern FactoryBlueprint g_FactoryBlueprints[];
extern u8 D_800AD4B8[];
extern u16 D_800AD54C[6];
extern s32 D_800AD558[6];
extern u16 D_800AD570[6];
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
extern u8 D_800AE140[];
extern Unkstruct_800AE180 D_800AE180[];
extern u16 D_800AE190[];
extern s16 D_800AE1B0[];
extern s16 D_800AE1F0[];
extern u32 D_800AE230[8];
extern u32 D_800AE250[8];
extern s32 D_800AE270[9];
extern AnimationFrame D_800AE294[];
extern u16 D_800AFC50[];
extern s16 D_800AFDA4[];
extern RECT c_backbufferClear;
extern s16 D_800AFFB8[];
extern u8 D_800B0130[];
extern AnimationFrame* D_800B01B8[];
extern AnimationFrame* D_800B0594[];
extern u8 D_800B0608[];
extern u8 D_800B0628[][4];
extern s16 D_800B0658[4][6];
extern Point32 D_800B0688[];
extern u32 D_800B06C8[24];
extern u32 D_800B0728[24];
extern RECT D_800B0788;
extern RECT D_800B0790;
extern AnimationFrame D_800B0798[];
extern AnimationFrame D_800B07C8[];
extern s32 D_800B0830[];
extern s32 D_800B083C[];
extern u8 D_800B0848[];
extern u16 D_800B0858[];
extern s16 D_800B0860[];
extern s16 D_800B0884[];
extern s16 D_800B08A8[];

extern s16 g_CdVolumeTable[];
extern struct SeqData g_SeqInfo[];
extern struct XaMusicConfig g_XaMusicConfigs[563];
extern s32 g_DebugEnabled;
extern s32 D_800BD1C4;
extern s32 g_VabAddrs[6];
extern u8* g_SfxScripts[172];
extern u8* D_800C52F8[];
extern const char D_800DB524[];
extern const char a0104x04x;
extern const char a2304x04x;
extern const char aBlue;
extern u8 g_GfxEquipIcon[320][16 * 16 / 2];
extern s16 g_PalEquipIcon[320 * 16];
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
extern Unkstruct_800BF554 g_SfxData[737];

extern char* aLightTimer02x;
extern SVECTOR D_800E2024;
extern SVECTOR D_800E202C;
// This appears to be a super miniature Entity or something
// All it has is a state, a timer, and a facing direction.
typedef struct {
    s32 state;
    s32 timer;
    s32 facingLeft;
} helper_8012F178;
extern helper_8012F178 D_800B08CC[6];
extern s32 D_800B0914;
extern s32 D_800B0918;
extern s32 D_800B091C;
extern s32 D_800B0920;

void func_801072DC(Primitive* prim);
void InitializePads(void);
void ReadPads(void);
void ClearBackbuffer(void);
void SetRoomForegroundLayer(LayerDef* layerDef);
void SetRoomBackgroundLayer(s32 index, LayerDef* layerDef);
void CheckCollision(s32 x, s32 y, Collider* res, s32 unk);
void DemoInit(s32 arg0);
void DemoUpdate(void);
void SetGPUBuffRGBZero(void);
void SetGPUBuffRGB(u8 arg0);
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
s32 func_800EDAE4(void);
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
s32 CalcAttack(s32, u32);
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

s32 TimeAttackController(TimeAttackEvents eventId, TimeAttackActions action);
s32 func_800FD664(s32 arg0);
s32 func_800FD6C4(s32 equipTypeFilter);
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
void func_800FF0A0(s32 arg0);
bool func_8010183C(s32 arg0);
s32 func_801025F4(void);
void func_80102CD8(s32);
void func_80103EAC(void);
Entity* GetFreeEntity(s16 start, s16 end);
Entity* GetFreeEntityReverse(s16 start, s16 end);
void DestroyEntity(Entity*);
void DestroyEntitiesFromIndex(s16 startIndex);
void func_801071CC(Primitive* prim, u32 colorIntensity, s32 vertexIndex);
void func_80107250(Primitive* prim, s32 colorIntensity);
void SetTexturedPrimRect(
    Primitive* poly, s32 x, s32 y, s32 width, s32 height, s32 u, s32 v);
void func_801073C0(void);
void func_801092E8(s32);
void SetPrimRect(Primitive* poly, s32 x, s32 y, s32 width, s32 height);
void SetPlayerStep(PlayerSteps step);
u32 UpdateAnim(s8* frameProps, AnimationFrame** anims);
void func_8010DFF0(s32 resetAnims, s32 arg1);
void func_8010E0A8(void);
void func_8010E0B8(void);
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
void func_80115394(DamageParam* damage, s16 arg1, s16 arg2);
void func_80115C50(void);
void func_80118894(Entity*);

void func_80118C28(s32 arg0);
void GetServantStats(Entity* entity, s32 spellId, s32 arg2, FamiliarStats* out);
Entity* CreateEntFactoryFromEntity(Entity* entity, u32, s32);

// Forward declarations for all the entity updating functions
void func_8011A4C8(Entity* self);
void EntityEntFactory(Entity* self);
void func_8011B5A4(Entity* self);
void EntityGravityBootBeam(Entity* self);
void EntitySubwpnThrownDagger(Entity* self);
void func_8011E4BC(Entity* self);
void EntityDiveKickAttack(Entity* self);
void EntityGiantSpinningCross(Entity* self);
void EntitySubwpnCrashCross(Entity* self);
void EntitySubwpnCrashCrossParticles(Entity* self);
void EntitySubwpnThrownAxe(Entity* self);
void EntityPlayerBlinkWhite(Entity* self);
void EntitySubwpnThrownVibhuti(Entity* self);
void func_8011E0E4(Entity* self);
void func_8011EDA0(Entity* self);
void EntityUnarmedAttack(Entity* self);
void func_8011EDA8(Entity* self);
void EntitySubwpnAgunea(Entity* self);
void EntityAguneaHitEnemy(Entity* self);
void EntityNumberMovesToHpMeter(Entity* self);
void EntitySubwpnReboundStone(Entity* self);
void EntityLevelUpAnimation(Entity* self);
void EntityHolyWater(Entity* self);
void EntityHolyWaterFlame(Entity* self);
void EntityUnkId24(Entity* self);
void EntityHellfireHandler(Entity* self);
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
void EntityHolyWaterBreakGlass(Entity* self);
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
void func_8011A4C8(Entity* self);
void EntitySummonSpirit(Entity* self);
void func_80123F78(Entity* self);
void EntityTeleport(Entity* self);
void func_80124A8C(Entity* self);
void func_8011A4C8(Entity* self);

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
