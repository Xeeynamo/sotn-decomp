// SPDX-License-Identifier: AGPL-3.0-or-later
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
#define FIX(x) ((s32)((x) * 65536.0))

#define PAD_RIGHT 0x8000
#define PAD_LEFT 0x4000

#define STAGE_INVERTEDCASTLE_MASK 0x1F
#define STAGE_INVERTEDCASTLE_FLAG 0x20
#define STAGE_ST0 0x1F
#define TOTAL_ENTITY_COUNT 256
#define FACTORY(id, param) ((id) + (param << 16))

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

#define POSE(duration, frameNo, hitboxNo)                                      \
    {(duration), (((frameNo) & 0x1FF) | (((hitboxNo) & 0x7F) << 9))}
#define POSE_LOOP(frame) {0, frame}
#define POSE_END {-1, 0}
#define POSE_JUMP(anim) {-2, anim}
typedef struct {
    u16 duration;
    u16 unk2;
} AnimationFrame;

typedef struct Collider {
    /* 0x00 */ u32 effects;
    /* 0x04 */ s32 unk4; // possibly an x offset
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14; // Left edge of queried tile collision
    /* 0x18 */ s32 unk18; // Top edge of queried tile collision
    /* 0x1C */ s32 unk1C; // Right edge of queried tile collision
    /* 0x20 */ s32 unk20; // Bottom edge of queried tile collision
} Collider;               /* size=0x24 */

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
    Player_Unk20,
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

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} ET_EntitySlot1;

typedef struct {
    /* 0x7C */ u8 pad0[0x4];
    /* 0x80 */ u8* anim;
    /* 0x84 */ s16 unk84;
    /* 0x86 */ u8 pad86[2];
    /* 0x88 */ u8 unk88;
    /* 0x89 */ u8 unk89;
} ET_ExplosionPuffOpaque;

typedef struct {
#ifdef PLATFORM_64BIT
    s32 _align_parent[2];
#endif
    /* 0x7C */ s16 timer;
    /* 0x7E */ s16 : 16;
    /* 0x80 */ s32 : 32;
    /* 0x84 */ s32 : 32;
    /* 0x88 */ s32 : 32;
    /* 0x8C */ struct Entity* parent;
    /* 0x90 */ s32 : 32;
    /* 0x94 */ s32 : 32;
    /* 0x98 */ s32 : 32;
    /* 0x9C */ s32 : 32;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s32 : 32;
    /* 0xAC */ s32 : 32;
    /* 0xB0 */ s16 subweaponId;
    /* 0xB2 */ s16 unkB2;
} ET_Subweapon;

typedef union { // offset=0x7C
    u8 base[0x38];
    ET_EntitySlot1 entSlot1; // g_Entities[1], not entityID 1
    ET_ExplosionPuffOpaque opaquePuff;
    ET_Subweapon subweapon;
} Ext;

typedef struct Entity {
    /* 0x00 */ struct Unk0600B344* unk0;
    /* 0x04 */ SotnFixed32 posX;
    /* 0x08 */ SotnFixed32 posY;
    /* 0x0c */ s32 velocityX;
    /* 0x10 */ s32 velocityY;
    /* 0x14 */ u16 hitboxOffX;
    /* 0x16 */ s16 hitboxOffY;
    /* 0x18 */ u16 facingLeft;
    /* 0x1A */ char pad_1A[0x4];
    /* 0x1E */ s16 rotate;
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
    /* 0x48 */ AnimationFrame* anim;
    /* 0x4c */ u16 pose;
    /* 0x4e */ s16 poseTimer;
    /* 0x50 */ char pad_50[0x2];
    /* 0x52 */ s16 unk52;
    /* 0x54 */ char pad_54[0xC];
    /* 0x60 */ s16 primIndex;
    /* 0x62 */ char pad_62[0x12];
    /* 0x74 */ u16 entityId;
    /* 0x76 */ char pad_76[0x1];
    /* 0x80 */ Ext ext;
    /* 0x88 */ char pad_88[0x2];
    /* 0x8A */ struct UnkStruct_060e8350* unk8A;
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
} Equipment; /* size=0x32 */

// Defines armor, cloak and rings
typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ const char* description;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u32 unk0C;
    /* 0x10 */ u32 unk10;
    /* 0x14 */ u32 unk14;
    /* 0x18 */ u16 icon;
    /* 0x1A */ u16 palette;
    /* 0x1C */ u16 equipType;
} Accessory; /* size=0x1E */

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
    /* 0x1C */ u16 equipType;
    /* 0x1E */ char pad_1E[0x2];
} Unkstruct_800A7734; // size = 0x20

// Flags for g_Player.vram_flag
// 0x01: touching the ground
// 0x02: touching the ceiling
// 0x04: touching the right wall
// 0x08: touching the left wall
// 0x20: in-air or near the edge
// 0x0800: touching the ceiling slope
// 0x1000: touching a slightly ascending or descending slope
// 0x4000: touching a raising slope
// 0x8000: touching any slope
typedef enum {
    TOUCHING_GROUND = 1 << 0,
    TOUCHING_CEILING = 1 << 1,
    TOUCHING_R_WALL = 1 << 2,
    TOUCHING_L_WALL = 1 << 3,
    VRAM_FLAG_UNK10 = 1 << 4,
    IN_AIR_OR_EDGE = 1 << 5,
    VRAM_FLAG_UNK40 = 1 << 6,
    VRAM_FLAG_UNK80 = 1 << 7,
    VRAM_FLAG_UNK100 = 1 << 8,
    VRAM_FLAG_UNK200 = 1 << 9,
    VRAM_FLAG_UNK400 = 1 << 10,
    TOUCHING_CEILING_SLOPE = 1 << 11,
    TOUCHING_SLIGHT_SLOPE = 1 << 12,
    VRAM_FLAG_UNK2000 = 1 << 13,
    TOUCHING_RAISING_SLOPE = 1 << 14,
    TOUCHING_ANY_SLOPE = 1 << 15
} PlayerVramFlag;

typedef struct {
    char pad0[0x3B0];
    /* 0x3B0 */ u32 padPressed;
    char pad3B4[0x14];
    /* 0x3C8 */ s16 timers[16]; // the array is bigger than PSX
    char pad3E8[4];
    /* 0x3EC */ s32 vram_flag;
    char pad2[8];
    /* 0x3F8 */ u32 status;
    char pad3FC[0x34];
    /* 0x430 */ u16 unk44;
    /* 0x432 */ u16 unk46;
    /* 0x434 */ u16 unk48;
    /* 0x436 */ u16 unk4A;
    /* 0x438 */ u16 unk4C;
    /* 0x43A */ u16 unk4E;
    /* 0x43C */ u16 prev_step;
    /* 0x43E */ u16 prev_step_s;
    char pad43C[0x1C];
    /* 0x45C */ u16 unk70;
    /* 0x45E */ u16 unk72;
    /* 0x460 */ u32 unk74;
    /* 0x464 */ u16 unk78;
    /* 0x466 */ u16 unk7A;
    /* 0x468 */ u16 unk7C;
    /* 0x46A */ u16 unk7E;
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
extern s32 g_StatBuffTimers[];
extern s32 D_8013B5E8;
extern s32 D_801375CC;
extern PlayerState g_Player;
extern Entity* g_CurrentEntity;
extern PlayerStatus g_Status;
extern SubweaponDef g_SubwpnDefs[];

#define NUM_HORIZONTAL_SENSORS 4
#define NUM_VERTICAL_SENSORS 7

// changed to s32
typedef struct {
    /* 0x0 */ s32 x;
    /* 0x2 */ s32 y;
} Point16; // size = 0x4

#define FIX(x) (x << 16)

#endif
