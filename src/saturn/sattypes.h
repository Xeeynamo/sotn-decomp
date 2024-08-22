// SPDX-License-Identifier: AGPL-3.0-only
#ifndef SATURN_TYPES_H
#define SATURN_TYPES_H

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define true 1
#define false 0
#define bool s32

#define NULL 0

#define STAGE_INVERTEDCASTLE_MASK 0x1F
#define STAGE_INVERTEDCASTLE_FLAG 0x20
#define STAGE_ST0 0x1F
#define TOTAL_ENTITY_COUNT 256

#define SFX_HEART_PICKUP 0x67A

#define PLAYER g_Entities[PLAYER_CHARACTER]

#define LOW(x) (*(s32*)&(x))
#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef union {
    s32 val;
    struct {
        s16 hi;
        s16 lo;
    } i;
} SotnFixed32;

struct Entity;

typedef void (*PfnEntityUpdate)(struct Entity*);

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
    Player_Teleport,  // also Grand Cross and Spiral Axe
    Player_FlameWhip, // also Godspeed Shoes Sprint
    Player_Hydrostorm,
    Player_ThousandBlades,
    Player_RichterFourHolyBeasts,
    Player_Slide,
    Player_Unk24, // MorphWolf and Richter's Tackle
    Player_Unk25, // UnmorphWolf and Sprint
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
    Player_MariaSpellGuardianKnuckle = 48,
    Player_MariaSpellGenbu,
    Player_MariaSpellByakko,
    Player_MariaSpellSeiryuu,
    Player_MariaSpellSuzaku,
    Player_MariaSpellFourHolyBeasts,
} PlayerSteps;

typedef struct Entity {
    /* 0x00 */ struct Unk0600B344* unk0;
    /* 0x04 */ SotnFixed32 posX;
    /* 0x08 */ SotnFixed32 posY;
    /* 0x0c */ s32 velocityX;
    /* 0x10 */ s32 velocityY;
    /* 0x14 */ u16 hitboxOffX;
    /* 0x16 */ s16 hitboxOffY;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ char pad_1A[0x4];
    /* 0x1E */ s16 rotZ;
    /* 0x20 */ s16 unk1A;
    /* 0x22 */ s16 unk1C;
    /* 0x24 */ s16 ghidra_pad_24;
    /* 0x26 */ char pad_26[0x2];
    /* 0x28 */ PfnEntityUpdate pfnUpdate;
    /* 0x2c */ u16 step;
    /* 0x2e */ u16 step_s;
    /* 0x30 */ u16 params;
    /* 0x32 */ u16 entityRoomIndex;
    /* 0x34 */ u32 flags;
    /* 0x38 */ u16 enemyId;
    /* 0x3A */ u16 hitboxState; // hitbox state
    /* 0x3C */ char pad_3C[2];
    /* 0x3E */ s16 attack;
    /* 0x40 */ s16 attackElement;
    /* 0x42 */ s16 pad_42;
    /* 0x44 */ u8 hitboxWidth;
    /* 0x45 */ u8 hitboxHeight;
    /* 0x46 */ u8 hitFlags; // 1 = took hit
    /* 0x47 */ char pad6[0x4];
    /* 0x4c */ u16 animFrameIdx;
    /* 0x4e */ s16 animFrameDuration;
    /* 0x50 */ char pad_50[0x2];
    /* 0x52 */ s16 unk52;
    /* 0x54 */ char pad_54[0xC];
    /* 0x60 */ s16 primIndex;
    /* 0x62 */ char pad_62[0x12];
    /* 0x74 */ u16 unk74;
    /* 0x76 */ char pad_76[0xA];
    /* 0x80 */ s16 unk80;
    /* 0x82 */ char pad_82[0x2];
    /* 0x84 */ s8 unk84;
    /* 0x85 */ s8 unk85;
    /* 0x86 */ char pad_86[0x2];
    /* 0x88 */ struct UnkStruct_060e8350* unk88;
    /* 0x8C */ char pad[0x2C];
} Entity; // size = 0xB8

typedef struct Unk0600B344 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ char pad_02[0x6];
    /* 0x08 */ s16 unk8;
    /* 0x0A */ char pad_0A[0x4];
    /* 0x0E */ s16 zPriority;
    /* 0x10 */ char pad_10[0x1];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
} Unk0600B344;

typedef struct {
    // structure still unknown
} Collider;

typedef struct {
    /* 8003C7F4 */ Entity* (*CreateEntFactoryFromEntity)(
        Entity* self, u32 flags, s32 arg2);
} GameApi; /* size=0x140 */

typedef struct {
    s32 unk0;
    PfnEntityUpdate func;
} EntityEntry;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} Unkstruct_800FD5BC;

// offsets are not the same as psx
typedef struct {
    u8 relics[30];
    char pad4[0xc];
    u8 equipHandCount[176];
    u8 equipBodyCount[26];
    char pad5[0x42];
    u8 equipHandOrder[176];
    u8 equipBodyOrder[26];
    char pad2[0x4E];
    s32 hp;
    s32 hpMax;
    s32 hearts;
    s32 heartsMax;
    s32 mp;
    s32 mpMax;
    s32 statsBase[4];
    char pad[15];
    s32 statsTotal[4];
    char pad3[0x14];
    u32 subWeapon;
    u32 equipment[7];
} PlayerStatus;

typedef struct {
    /* 0x00 */ s16 attack;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u16 attackElement;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 sp17;
    /* 0x08 */ u16 sp18;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u16 sp1C;
    /* 0x0E */ u16 sp1E;
    /* 0x10 */ u8 sp20;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u16 sp22; // entity->entityRoomIndex
} SubweaponDef;          /* size=0x14 */

typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ const char* description;
    /* 0x08 */ s16 attack;
    /* 0x0A */ s16 defense;
    /* 0x0C */ u16 element;
    /* 0x0E */ u8 itemCategory;
    /* 0x0F */ u8 weaponId;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u8 playerAnim;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 lockDuration;
    /* 0x16 */ u16 chainable;
    /* 0x18 */ u8 specialMove;
    /* 0x19 */ u8 isConsumable;
    /* 0x1A */ u8 enemyInvincibilityFrames;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ u16 unk20;
    /* 0x22 */ u16 unk22;
    /* 0x24 */ u16 mpUsage;
    /* 0x26 */ u16 stunFrames;
    /* 0x28 */ u16 hitType;
    /* 0x2A */ u16 hitEffect;
    /* 0x2C */ u16 icon;
    /* 0x2E */ u16 palette;
    /* 0x30 */ u16 criticalRate;
    /* 0x32 */ u16 unk32;
} Equipment; /* size=0x34 */

// Defines armor, cloak and rings
typedef struct {
    /* 00 */ const char* name;
    /* 04 */ const char* description;
    /* 08 */ u32 unk08;
    /* 0C */ u32 unk0C;
    /* 10 */ u32 unk10;
    /* 14 */ u32 unk14;
    /* 18 */ u16 icon;
    /* 1A */ u16 palette;
    /* 1C */ u32 unk1C;
} Accessory; /* size=0x20 */

typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ const char* combo;
    /* 0x08 */ const char* description;
    /* 0x0C */ s8 mpUsage;
    /* 0x0D */ s8 unk0D;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u16 attackElement;
    /* 0x18 */ s16 attack;
    /* 0x1A */ s16 unk1A;
} SpellDef;

typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ s16 hitPoints;
    /* 0x06 */ u16 attack;
    /* 0x08 */ u16 attackElement;
    /* 0x0A */ s16 defense;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 weaknesses;
    /* 0x10 */ u16 strengths;
    /* 0x12 */ u16 immunes;
    /* 0x14 */ u16 absorbs;
    /* 0x16 */ s16 level;
    /* 0x18 */ s16 exp;
    /* 0x1A */ s16 rareItemId;
    /* 0x1C */ s16 uncommonItemId;
    /* 0x1E */ u16 rareItemDropRate;
    /* 0x20 */ u16 uncommonItemDropRate;
    /* 0x22 */ u8 hitboxWidth;
    /* 0x23 */ u8 hitboxHeight;
    /* 0x24 */ s32 unk24;
} EnemyDef; /* size=0x28 */

// layout is different
typedef struct Unkstruct_800A7734 {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ char pad_02[0x1A];
    /* 0x1C */ u16 unk03;
    /* 0x1E */ char pad_1E[0x2];
} Unkstruct_800A7734; // size = 0x20

typedef struct {
    char pad[0x3F8];
    u32 unk0C;
} PlayerState;

typedef enum {
    PLAYER_CHARACTER,
    UNK_ENTITY_1,
    UNK_ENTITY_2,
    UNK_ENTITY_3,
    UNK_ENTITY_4,
    UNK_ENTITY_5,
    UNK_ENTITY_6,
    UNK_ENTITY_7,
    UNK_ENTITY_8,
    E_WEAPON = 0x10,
    UNK_ENTITY_13 = 0x13,
    UNK_ENTITY_20 = 0x20,
    UNK_ENTITY_51 = 0x51,
    UNK_ENTITY_100 = 0x100
} EntityTypes;

typedef enum EquipKind {
    EQUIP_HAND,
    EQUIP_HEAD,
    EQUIP_ARMOR,
    EQUIP_CAPE,
    EQUIP_ACCESSORY,
    NUM_EQUIP_KINDS,
} EquipKind;

typedef enum {
    ITEM_S_SWORD,
    ITEM_SWORD,
    ITEM_THROW_1,
    ITEM_FIST,
    ITEM_CLUB,
    ITEM_TWOHAND,
    ITEM_FOOD,
    ITEM_BOMB,
    ITEM_THROW_2,
    ITEM_SHIELD,
    ITEM_MEDICINE
} ItemCategory;

typedef enum {
    SPELL_DARK_METAMORPHOSIS,
    SPELL_SUMMON_SPIRIT,
    SPELL_HELLFIRE,
    SPELL_TETRA_SPIRIT,
    SPELL_WOLF_CHARGE,
    SPELL_SOUL_STEAL,
    SPELL_WING_SMASH,
    SPELL_SWORD_BROTHERS,
    NUM_SPELLS,
} SpellIds;

s32 SquareRoot0(s32);
s32 func_800F4D38(s32, s32);
void func_800F4994(void);
void DestroyEntity(Entity* entity);
extern int rand(void);
u32 CheckEquipmentItemCount(u32 itemId, u32 equipType);
void PlaySfx(s16 sfxId);

// Not 100% sure about address, gcc seems to added the offset within
// the struct to the base address
extern Equipment g_EquipDefs[];

extern GameApi g_api;
extern Entity g_Entities[TOTAL_ENTITY_COUNT]; // 0x060997F8
extern EntityEntry** PfnEntityUpdates[];
extern u16 g_StageId; // u32 in psx
extern SpellDef g_SpellDefs[];
extern Accessory g_AccessoryDefs[];
extern Unkstruct_800A7734 D_800A7734[];
extern s32 D_80137960;
extern s32 D_80137964;
extern s32 D_80137968;
extern s32 D_80139828[];
extern s32 D_8013B5E8;
extern EquipKind D_801375CC;
extern PlayerState g_Player;
extern Entity* g_CurrentEntity;
extern PlayerStatus g_Status;
extern SubweaponDef g_SubwpnDefs[];

#endif
