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

// entity layout is different somehow
typedef struct Entity {
    s16 temp;
    s16 pad1;
    s16 posX;
    s16 pad3;
    s16 posY;
    s8 pad[0x25];
    u16 subId;
} Entity;

typedef struct {
    /* 8003C7F4 */ Entity* (*func_8011AAFC)(Entity* self, u32 flags, s32 arg2);
} GameApi; /* size=0x140 */
extern GameApi g_api;
void PlaySfx(s16 sfxId);
#define NA_SE_PL_COLLECT_HEART 0x67A

#define ABS(x) ((x) < 0 ? -(x) : (x))

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
    UNK_ENTITY_10 = 0x10,
    UNK_ENTITY_13 = 0x13,
    UNK_ENTITY_20 = 0x20,
    UNK_ENTITY_51 = 0x51, // SubWeapons container falling liquid
    UNK_ENTITY_100 = 0x100
} EntityTypes;

#define TOTAL_ENTITY_COUNT 256
#define PLAYER g_Entities[PLAYER_CHARACTER]
extern Entity g_Entities[TOTAL_ENTITY_COUNT];

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} Unkstruct_800FD5BC;

// offsets are not the same
typedef struct {
    u8 relics[30];
    u8 pad4[0xc];
    u8 equipHandCount[176];
    u8 equipBodyCount[26];
    u8 pad5[0x42];
    u8 equipHandOrder[176];
    u8 equipBodyOrder[26];
    u8 pad2[0x4E];
    s32 hp;
    s32 hpMax;
    s32 hearts;
    s32 heartsMax;
    s32 mp;
    u8 pad[35];
    s32 statsTotal[4];
    u8 pad3[0x18];
    u32 equipment[7];
} PlayerStatus;

typedef struct {
    char pad_0[0x1B];
    s8 unk1C;
} Unkstruct_800A841C;
extern Unkstruct_800A841C D_800A841C[]; // related to player MP

extern PlayerStatus g_Status;

#define true 1
#define false 0
#define bool s32

extern u16 g_StageId; // u32 in psx

typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ const char* description;
    /* 0x08 */ s16 attack;
    /* 0x0A */ s16 defense;
    /* 0x0C */ u16 element;
    /* 0x0E */ u8 damageScale;
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

// Not 100% sure about address, gcc seems to added the offset within
// the struct to the base address
extern Equipment D_800A4B04[];

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

extern Accessory D_800A7718[];

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
extern SpellDef g_SpellDefs[];

extern int rand(void);
u32 CheckEquipmentItemCount(u32 itemId, u32 equipType);

// layout is different
typedef struct Unkstruct_800A7734 {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ char unk02[0x19];
    u16 unk03;
    char unk04[0x1];
} Unkstruct_800A7734; // size = 0x20

extern Unkstruct_800A7734 D_800A7734[];

extern s32 D_80137960;
extern s32 D_80137964;
extern s32 D_80137968;

extern s32 D_80139828[];

extern s32 D_8013B5E8;

#endif
