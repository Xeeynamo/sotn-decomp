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
#define STAGE_ENTITY_START 64
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

// Flags for entity->flags
typedef enum {
    FLAG_UNK_10 = 0x10,
    FLAG_UNK_20 = 0x20,
    FLAG_UNK_40 = 0x40,
    FLAG_UNK_80 = 0x80,
    FLAG_DEAD = 0x100, // entity must execute its death routine
    FLAG_UNK_200 = 0x200,
    FLAG_UNK_400 = 0x400,
    FLAG_UNK_800 = 0x800,
    FLAG_UNK_1000 = 0x1000,
    FLAG_UNK_2000 = 0x2000,
    FLAG_UNK_4000 = 0x4000,
    FLAG_UNK_8000 = 0x8000,
    FLAG_UNK_10000 = 0x10000,
    FLAG_UNK_20000 = 0x20000,         // func_8011A9D8 will destroy if not set
    FLAG_POS_PLAYER_LOCKED = 0x40000, // entity follows player position
    FLAG_UNK_80000 = 0x80000,
    FLAG_UNK_100000 = 0x100000,
    FLAG_UNK_00200000 = 0x00200000,
    FLAG_SUPPRESS_STUN = 0x400000, // disable invincibility frames
    FLAG_HAS_PRIMS = 0x800000,     // call FreePrimitives on DestroyEntity
    FLAG_NOT_AN_ENEMY = 0x01000000,
    FLAG_UNK_02000000 = 0x02000000,
    FLAG_KEEP_ALIVE_OFFCAMERA = 0x04000000, // don't destroy entity off-screen
    FLAG_POS_CAMERA_LOCKED = 0x08000000,    // entity follows camera position
    FLAG_UNK_10000000 = 0x10000000,         // CHI func_801A169C: "Is Airborne"?
    FLAG_UNK_20000000 = 0x20000000,
    FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA = 0x40000000,
    FLAG_DESTROY_IF_OUT_OF_CAMERA = 0x80000000,
} EntityFlag;

typedef struct {
    u8 disableFlag;
    u8 resetFlag;
    u8 index;
    u8 timer;
} ET_AfterImage;

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

typedef struct {
    /* 0x78 */ s32 : 32;
    /* 0x7C */ s32 : 32;
    /* 0x80 */ s32 : 32;
    /* 0x84 */ s32 : 32;
    /* 0x88 */ struct Entity* parent;
} ET_BatFamBlueTrail;

typedef struct {
    /* 0x78 */ s32 : 32;
    /* 0x7C */ s32 : 32;
    /* 0x80 */ s32 : 32;
    /* 0x84 */ s32 : 32;
    /* 0x88 */ s32 : 32;
    /* 0x8C */ s32 : 32;
    /* 0x90 */ s32 : 32;
    /* 0x94 */ s32 : 32;
    /* 0x98 */ s32 : 32;
    /* 0x9C */ s32 : 32;
    /* 0xA0 */ s32 : 32;
    /* 0xA4 */ s32 : 32;
    /* 0xA8 */ s16 cameraX;
    /* 0xAA */ s16 cameraY;
    /* 0xAC */ s16 lastPlayerPosX;
    /* 0xAE */ s16 lastPlayerPosY;
} ET_Bat;

typedef union { // offset=0x78
    u8 base[0x38];
    ET_AfterImage afterImage; // g_Entities[1], not entityID 1
    ET_ExplosionPuffOpaque opaquePuff;
    ET_Subweapon subweapon;
    ET_BatFamBlueTrail batFamBlueTrail;
    ET_Bat bat;
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
    /* 0x3C */ s16 hitPoints;
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
    /* 0x52 */ s16 animCurFrame;
    /* 0x54 */ char pad_54[0xC];
    /* 0x60 */ s16 primIndex;
    /* 0x62 */ u16 zPriority;
    /* 0x64 */ u16 unk68;
    /* 0x66 */ char pad_66[0xE];
    /* 0x74 */ u16 entityId;
    /* 0x76 */ char pad_76[0x2];
    /* 0x78 */ Ext ext;
    /* 0xB0 */ char pad_B0[0x4];
    /* 0xB4 */ struct UnkStruct_060e8350* unkB4;
} Entity; // size = 0xB8

typedef struct Unk0600B344 {
    /* 0x00 */ u16 unk0;
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
    s32 level;
    s32 exp;
    s32 unk8; // Possibly the number of times loaded
} FamiliarStats;

// offsets are not the same as psx
typedef struct {
    u8 relics[32];
    char pad[2];
    u8 spells[8];
    u8 equipHandCount[176];
    u8 equipBodyCount[92];
    u8 equipHandOrder[176];
    u8 equipBodyOrder[92];
    u8 saveName[8];
    u32 spellsLearnt;
    s32 hp;
    s32 hpMax;
    s32 hearts;
    s32 heartsMax;
    s32 mp;
    s32 mpMax;
    s32 statsBase[4];
    s32 statsEquip[4];
    s32 statsTotal[4];
    s32 level;
    u32 exp;
    s32 gold;
    s32 killCount;
    u32 D_80097BF8;
    u32 subWeapon;
    u32 equipment[8];
    u32 attackHands[2];
    s32 defenseEquip;
    u16 elementsWeakTo;
    u16 elementsResist;
    u16 elementsImmune;
    u16 elementsAbsorb;
    s32 timerHours;
    s32 timerMinutes;
    s32 timerSeconds;
    s32 timerFrames;
    u32 D_80097C40;
    FamiliarStats statsFamiliars[7];
} PlayerStatus;

typedef struct {
    /* 0x00 */ s16 attack;
    /* 0x02 */ s16 heartCost;
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
    /* 0x1C */ u32 comboSub;
    /* 0x20 */ u32 comboMain;
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
    /* 0x08 */ s16 attBonus;
    /* 0x0A */ s16 defBonus;
    /* 0x0C */ u8 statsBonus[4];
    /* 0x10 */ u16 weakToElements;
    /* 0x12 */ u16 resistElements;
    /* 0x14 */ u16 immuneElements;
    /* 0x16 */ u16 absorbElements;
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
    /* 0x0C */ u16 hitboxState;
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
    /* 0x24 */ s32 flags;
} EnemyDef; /* size=0x28 */

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
    char pad0[0x320];
    u16 unk320;
    u16 unk322;
    char pad324[0x8C];
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

typedef struct {
    s32 : 32;
    s32 D_800973FC;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    u32 D_80097428[8];
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s16 unk90;
    s16 unk92;
    s16 unk94;
} unkGraphicsStruct;

typedef struct {
    const char* name;
    s32 : 32;
    u16 : 16;
    u16 : 16;
    s32 unk0C;
} RelicDesc;

typedef struct {
    s32 buttonConfig[8];
    u16 buttonMask[8];
    s32 timeAttackRecords[32];
    s32 cloakColors[6];
    s32 windowColors[3];
    s32 equipOrderTypes[11];
    s32 isCloakLiningReversed;
    s32 isSoundMono;
    s32 D_8003CB00;
    s32 D_8003CB04;
} GameSettings;

typedef struct {
    u16 flags;
    u16 unk2;
    u16 unk4;
    s16 zPriority;
} FgLayer;

typedef struct {
    /* 0x00 */ s32 cursorMain;
    /* 0x04 */ s32 cursorRelic;
    /* 0x08 */ s32 cursorEquip;
    /* 0x0C */ s32 cursorHandEquipType;
    /* 0x10 */ s32 cursorEquipType[4];
    /* 0x20 */ s32 scrollEquipType[5];
    /* 0x34 */ s32 cursorSpells;
    /* 0x38 */ s32 cursorSettings;
    /* 0x3C */ s32 cursorCloak;
    /* 0x40 */ s32 cursorButtons;
    /* 0x44 */ s32 cursorWindowColors;
    /* 0x48 */ s32 cursorTimeAttack;
} MenuNavigation; /* size=0x4C */

typedef struct {
    u32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    u32 : 32;
    s32 : 32;
    u32 : 32;
    u32 : 32;
    u32 : 32;
    u32 unk24;
    s32 : 32;
    s32 : 32;
} PlayerHud;

typedef struct {
    s16 : 16;
    s16 : 16;
    s16 : 16;
    s16 : 16;
    s16 : 16;
    s16 : 16;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    s16 x3;
    s16 y3;
    s16 : 16;
    s16 : 16;
    s32 : 32;
} Primitive;

typedef struct {
    /* 0x0 */ u16 pressed;
    /* 0x2 */ u16 previous;
    /* 0x4 */ u16 tapped;
    /* 0x6 */ u16 repeat;
} Pad; // size = 0x8

typedef struct {
    SotnFixed32 scrollX;
    SotnFixed32 scrollY;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 left;
    s32 top;
} Tilemap;

typedef struct {
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 : 32;
    s32 g_ScrollDeltaX;
    s32 : 32;
    s32 g_ScrollDeltaY;
} UNK_0605c680;

typedef struct {
    /* 0x0 */ u16 posX;
    /* 0x2 */ u16 posY;
    /* 0x4 */ u16 entityId;
    /* 0x6 */ u8 entityRoomIndex;
    /* 0x8 */ u16 params;
} LayoutEntity; // size = 0xA

typedef struct ServantEvent {
    /* 0x00 */ struct ServantEvent* next; // next event in the queue
    /* 0x04 */ u32 timer;     // internal timer from 'delay' to the activation 0
    /* 0x08 */ s32 servantId; // the familiar ID that can trigger the event
    /* 0x0C */ s32 roomX;     // only activate in the specified room coords...
    /* 0x10 */ s32 roomY;     // ... where on X negative is the inverted castle
    /* 0x14 */ s32 cameraX;   // only activate on the camera coordinate...
    /* 0x18 */ s32 cameraY;   // ...within the room
    /* 0x1C */ s32 condition; // condition for the event
    /* 0x20 */ u32 delay;     // after how many frames the event is triggered
    /* 0x24 */ s32 entityId;  // ID of the entity to spawn
    /* 0x28 */ s32 params;    // parameters of the entity to spawn
    /* 0x2C */ u32 unk2C;
} ServantEvent;

typedef enum {
    PLAYER_CHARACTER,
    E_AFTERIMAGE_1,
    E_AFTERIMAGE_2,
    E_AFTERIMAGE_3,
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

typedef enum {
    EFFECT_NONE = 0,
    EFFECT_SOLID = 1 << 0,
    EFFECT_UNK_0002 = 1 << 1,
    EFFECT_QUICKSAND = 1 << 2,
    EFFECT_WATER = 1 << 3,
    EFFECT_MIST_ONLY = 1 << 4,
    EFFECT_UNK_0020 = 1 << 5,
    // Used when you jump from below to a platform. You can drop below.
    EFFECT_SOLID_FROM_ABOVE = 1 << 6,
    // Doesn't collide when falling on it but you cannot go back up.
    EFFECT_SOLID_FROM_BELOW = 1 << 7,
    EFFECT_UNK_0100 = 1 << 8,
    EFFECT_UNK_0200 = 1 << 9,
    EFFECT_UNK_0400 = 1 << 10,
    EFFECT_UNK_0800 = 1 << 11,
    EFFECT_UNK_1000 = 1 << 12,
    EFFECT_UNK_2000 = 1 << 13,
    EFFECT_UNK_4000 = 1 << 14,
    EFFECT_UNK_8000 = 1 << 15,

    // Aggregate helpers below:
    EFFECT_NOTHROUGH = EFFECT_SOLID | EFFECT_QUICKSAND,
    EFFECT_NOTHROUGH_PLUS = EFFECT_SOLID | EFFECT_UNK_0002 | EFFECT_QUICKSAND,
    // Should be renamed once we know what 8000 and 4000 are
    EFFECT_UNK_C000 = EFFECT_UNK_8000 | EFFECT_UNK_4000
} ColliderEffectFlags;

u32 SquareRoot0(s32);
s32 func_800F4D38(s32, s32);
void func_800F4994(void);
extern int rand(void);
void PlaySfx(s32 sfxId);

// Not 100% sure about address, gcc seems to added the offset within
// the struct to the base address
extern Equipment g_EquipDefs[];

extern GameSettings g_Settings;
extern GameApi g_api;
extern Entity g_Entities[TOTAL_ENTITY_COUNT]; // 0x060997F8
extern EntityEntry** PfnEntityUpdates[];
extern u16 g_StageId; // u32 in psx
extern SpellDef g_SpellDefs[];
extern Accessory g_AccessoryDefs[];
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
extern unkGraphicsStruct g_unkGraphicsStruct;
extern u32 g_GameTimer;
extern FgLayer D_8003C708;
extern s32 D_801375C8;
extern s32 D_8006BB00;
extern s32 g_Servant;
extern RelicDesc g_RelicDefs[];
extern s32 currentMusicId;
extern u8 g_CastleFlags[];
extern s32 g_PlayableCharacter;
extern MenuNavigation g_MenuNavigation;
extern PlayerHud g_PlayerHud;
extern Pad g_pads[];
extern Tilemap g_Tilemap;
extern UNK_0605c680 DAT_0605c680;

#define NUM_HORIZONTAL_SENSORS 4
#define NUM_VERTICAL_SENSORS 7

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
} Point16; // size = 0x4

typedef struct {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
} Point32; // size = 0x8

#endif
