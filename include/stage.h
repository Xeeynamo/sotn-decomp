#ifndef STAGE_H
#define STAGE_H
#define STAGE 0xCC

#include "common.h"
#include "game.h"
#include "items.h"
#include "objects.h"
#include "sfx.h"

typedef enum {
    EXPLOSION_SMALL,
    EXPLOSION_FIREBALL,
    EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_BIG,
    EXPLOSION_UNK_4
} ExplosionTypes;

// used by InitializeEntity to pre-fill certain entity fields
// cannot be declared as a struct, field order:
// animSet, animCurFrame, unk5A, palette, enemyID
typedef u16 EInit[5];

typedef struct {
    u8 duration;
    u8 pose;
} AnimateEntityFrame;

typedef struct {
    /* 0x0 */ u16 posX;
    /* 0x2 */ u16 posY;
    /* 0x4 */ u16 entityId;
    /* 0x6 */ u16 entityRoomIndex;
    /* 0x8 */ u16 params;
} LayoutEntity; // size = 0xA

// Used in e_clock_tower.h, e_clouds.h, st0/3AB08, rbo3/e_clouds
typedef struct {
    u8* unkPtr;
    s16 unk4;
    u16 priority;
} cloudData;

// Used in e_clock_tower.h, st0/3AB08
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
} cloudStructUnk;

// Used in rbo3/e_clouds, e_clouds.h
typedef struct {
    u16 u0, u1, u2, u3;
} MedusaCloudsUVal;

// Used in st0/3AB08, e_clock_tower.h
typedef struct {
    u8 u0, v0, u1, v1, u2, v2;
    u16 clut;
} ClockTowerData;

// Used in st0/3AB08, e_clock_tower.h
typedef struct {
    u8 u, v, w, h;
    u16 clut;
} ClockTowerData2;

// Used in e_blade.h, e_gurkha.h, no2/hammer, giantbro_helpers.h
typedef struct {
    s16 unk0;
    s16* unk4;
} unkStr_801CDD80;

// Used in e_blade, e_gurkha, no2/hammer
// note on member types: length and zOffset definitely look signed
// in the data, but psp uses lhu instead of lh.
typedef struct {
    s16 eArrayOffset;
    s16 eArrayParentOffset;
    u16 length;
    u16 params;
    u16 zOffset;
} giantBroBodyPartsInit;

// Used in e_bone_archer.h
typedef struct {
    u8* animation;
    u8 frameA;
    u8 frameB;
    s16 xOffset;
    s16 yOffset;
    s16 pad;
} unk_801D0598; /* size=0xC */

// Used by no2/372E8, rbo3/rbo3, e_explosion_puff_opaque
typedef struct {
    u16 animSet;
    u16 unk5A;
    u16 palette;
    u16 drawMode;
    u8* animData;
} EntityConfig;

/*******/
/* CAT */
/*******/
// Used in cat/e_slime
typedef struct {
    s16 top;
    s16 bottom;
    s16 left;
    s16 right;
} TileCollision;

/*******/
/* DAI */
/*******/
// Used in dai/e_confessional
typedef struct {
    /* 0x00 */ u8* anim1;
    /* 0x04 */ u8* anim2;
    /* 0x08 */ u8* anim3;
    /* 0x0C */ u8* anim4;
} ConfessionalGhostAnimSet;

// Used in dai/e_confessional
typedef struct {
    /* 0x00 */ s16 x0;
    /* 0x02 */ s16 x1;
    /* 0x04 */ s16 x2;
    /* 0x06 */ s16 xVal;
    /* 0x08 */ s16 xHi;
    /* 0x0A */ s16 x3;
    /* 0x0C */ ConfessionalGhostAnimSet* animations;
} ConfessionalGhostParams;

// Used in dai/e_bell
typedef struct {
    s16 segments;
    s16 length;
    s16 priority;
} bellRopeParams;

// Used in dai/e_hunting_girl
typedef struct {
    s16 x;
    s16 y;
    s16 rotate;
    s16 frames;
} huntingGirlAttackStep;

/*******/
/* LIB */
/*******/
// Used in lib/e_dhuron
typedef struct {
    s32 velocityX;
    s32 velocityY;
    s16 rotate;
    s16 unkA;
} dhuronUnkStruct;

// Used in lib/e_spellbook_magic_tome
typedef struct {
    EInit* unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    u8 unkC;
} unkBookStruct;

/*******/
/* NO1 */
/*******/
// Used in no1/e_medusa_head
typedef struct {
    s16 yMax;
    s16 yMin;
    s16 spawnDelay;
    s16 spawnCount;
    s16 yellowChance; // chance out of 16 that medusa head will be yellow
    s16 zPriority;
} MedusaHeadSpawnerParams;

// Used in no1/e_medusa_head
typedef struct {
    s32 velocityX;
    s16 posX;
    s16 facingLeft;
} MedusaHeadInitParams;

// Used in no1/unk_35E20
typedef struct {
    s32 animSet;
    AnimationFrame* anim;
    s32 count;
    CVECTOR color;
} AnimParam;

/*******/
/* NO2 */
/*******/
// Used in no2/e_valhalla_knight
typedef struct {
    u32 velocityX;
    u32 velocityY;
    s16 rotate;
} unkStr_80182100;

/*******/
/* NZ0 */
/*******/
// Used in nz0/e_subweapon_container
typedef struct SubWpnContDebris {
    s16 velX;
    s16 velY;
    u16 params;
    u16 facingLeft;
} SubWpnContDebris;

/*******/
/* ST0 */
/*******/
// Used in st0/3D8F0
typedef struct {
    Point16 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s32 unk10;
    s16 unk14;
} unkstr_801C06B0;

/***************/
/* Scratchpads */
/***************/
// Used in no4/e_frozen_shade
typedef struct {
    SVECTOR points[4];
    Point16 sxy[4];
    long p;
    long flag;
    CVECTOR primaryColor;
    CVECTOR color;
    MATRIX mat;
} NO4_SCRATCHPAD;

// Used in st0/3C5C0
typedef struct {
    MATRIX m[2];
    SVECTOR vec[1];
    SVECTOR sp4c[2];
    s32 var_s3[18];
    s32 sp5c[9];
    CVECTOR sp50;
    u8 var_s5[1];
} ST0_SCRATCHPAD;

extern u16 g_ItemIconSlots[ICON_SLOT_NUM];

/*
 * Sets up layout arrays and initializes stage state to
 * initial values.
 *
 * - Parameters:
 *   - objLayoutId - the room to initialize
 */
void InitRoomEntities(s32 objLayoutId);

/*
 * An callback for notifying the stage that the
 * viewport has changed.
 */
void UpdateRoomPosition();

void Update(void);
void UpdateStageEntities();
void HitDetection(void);

s32 Random();
#ifdef VERSION_PC
void CreateEntityFromEntity(u16 entityId, Entity* source, Entity* entity);
#endif
void DestroyEntity(Entity*);
void DestroyEntitiesFromIndex(s16 index);
void FallEntity(void);
Entity* AllocEntity(Entity* start, Entity* end);

// InitializeEntity takes a EInit but treats it as a `u16[]`
void InitializeEntity(u16 arg0[]);

#endif
