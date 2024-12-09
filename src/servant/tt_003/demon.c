// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "demon.h"
#include "sfx.h"
#include "../servant_private.h"

static s32 s_TargetMatch[0x80];
static s32 s_TargetLocationX;
static s32 s_TargetLocationY;
static s16 s_TargetLocationX_calc;
STATIC_PAD_BSS(2);
static s16 s_TargetLocationY_calc;
STATIC_PAD_BSS(2);
static s16 s_AngleToTarget;
STATIC_PAD_BSS(2);
static s16 s_AllowedAngle;
STATIC_PAD_BSS(2);
static s16 s_DistToTargetLocation;
STATIC_PAD_BSS(2);
static s16 s_TargetLocOffset_calc;
STATIC_PAD_BSS(2);
static s32 s_DeltaX;
static s32 s_DeltaY;
static s32 s_DistToTargetLocation2;
static s32 s_AttackTargetLocationX;
static s32 s_AttackTargetLocationY;
static s32 s_AttackLocationDeltaX;
static s32 s_AttackLocationDeltaY;
static u32 s_AttackAnimationStatus;
static s32 s_IsTargetFacingLeft;
static s32 s_TempRand;
static s32 s_SpecialAttackTargetPosX;
static s32 s_SpecialAttackTargetPosY;
static s32 s_SpecialAttackLocationDeltaX;
static s32 s_SpecialAttackLocationDeltaY;
static s32 s_SpecialAttackAnimationStatus;
static s32 s_IsSpecialAttackTargetFacingLeft;
static s32 s_SpecialAttackIdx;
static s32 s_SwitchPoxX;
static s32 s_SwitchPoxY;
STATIC_PAD_BSS(4);
static ServantSfxEventDesc* s_SwitchSfxEvent;
static s16 s_CurrentSwitchSfxFlag;
STATIC_PAD_BSS(2);
static s32 D_us_8017863C;
static s32 D_us_80178640;
static s16 D_us_80178644;
STATIC_PAD_BSS(2);
static s16 D_us_80178648;
STATIC_PAD_BSS(2);
static s16 D_us_8017864C;
STATIC_PAD_BSS(2);
static s16 D_us_80178650;
STATIC_PAD_BSS(2);
static s16 D_us_80178654;
STATIC_PAD_BSS(2);
static s16 D_us_80178658;
STATIC_PAD_BSS(2);
static s32 D_us_8017865C;
static s32 D_us_80178660;
static s32 D_us_80178664;
static ServantSfxEventDesc* s_CurrentIntroEvent;
static s16 s_CurrentIntroSfxFlag;
STATIC_PAD_BSS(2);
static s32 D_us_80178670;
static s32 D_us_80178674;
static s32 D_us_80178678;
static s32 D_us_8017867C;
static s32 D_us_80178680;
static s32 D_us_80178684;
static s32 D_us_80178688;
static s32 D_us_8017868C;
static s32 s_ServantId;
static FamiliarStats s_DemonStats;
static s16 D_us_801786A0[3][8];
static s32 D_us_801786D0;
static s32 D_us_801786D4;
static Entity* s_CurrentSwitch;
static s32 D_us_801786DC;
static s32 s_LastTargetedEntityIndex;

extern DemonAbilityStats g_DemonAbilityStats[10];
extern AnimationFrame* g_DemonAnimationFrames[];
extern u16 g_DemonClut[80];
extern SpriteParts* g_DemonSpriteParts[];
extern ServantEvent g_Events[];
extern s8 g_DemonFrameProps[40];
extern s16 g_DemonAttackSelector[10][6];
extern s32 g_DemonSfxMap[8];
extern u32 D_us_80171B74[8][4];
extern u32 D_us_80171BF4[][4];
extern s16 D_us_80171B44[3][8];
extern DemonAttackInfo g_DemonAttackIdSfxLookup[5];
extern s32 g_SfxDemonSwitchRandomizer[];
extern s32 g_SfxDemonIntroPrevSummoned[];
extern s32 g_SfxDemonIntroNewSummoned[];
extern AnimationFrame D_us_80171CD8;
// Horizontal offsets for positioning primitives
extern u16 D_us_80171D10[];

extern void (*g_AttackFunctions[])(Entity*);

static void ServantInit(InitializeMode);
static void UpdateServantDefault(Entity*);
static void UpdateServantBasicAttack(Entity*);
static void UpdateServantSpecialAttack(Entity*);
static void unused_5800(Entity*);
static void unused_5808(Entity*);
static void UpdateServantPressSwitch(Entity*);
static void UpdateSubentitySwitch(Entity*);
static void UpdateServantAdditionalInit(Entity*);
static void UpdateServantSfxPassthrough(Entity*);
static void UpdateEventAttack(Entity*);
static void func_us_801765A0(Entity*);
static void func_us_80176814(Entity*);
static void func_us_80176C1C(Entity*);
static void func_us_801771B0(Entity*);
static void func_us_80177690(Entity*);

ServantDesc demon_ServantDesc = {
    ServantInit,
    UpdateServantDefault,
    UpdateServantBasicAttack,
    UpdateServantSpecialAttack,
    unused_5800,
    unused_5808,
    UpdateServantPressSwitch,
    UpdateSubentitySwitch,
    UpdateServantAdditionalInit,
    UpdateServantSfxPassthrough,
    UpdateEventAttack,
    func_us_801765A0,
    func_us_80176814,
    func_us_80176C1C,
    func_us_801771B0,
    func_us_80177690,
};

static void SetAnimationFrame(Entity* self, s32 animationIndex) {
    if (self->anim != g_DemonAnimationFrames[animationIndex]) {
        self->anim = g_DemonAnimationFrames[animationIndex];
        self->animFrameIdx = 0;
        self->animFrameDuration = 0;
    }
}

static Entity* FindValidTarget(Entity* self) {
    const int EntitySearchCount = 128;
    s32 foundIndex;
    s32 i;
    u32 found;
    Entity* entity;
    s32 distance;

    found = 0;
    entity = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < EntitySearchCount; i++, entity++) {
        s_TargetMatch[i] = 0;
        if (!entity->entityId) {
            continue;
        }
        if (entity->hitboxState == 0) {
            continue;
        }
        if (entity->flags & FLAG_UNK_00200000) {
            continue;
        }
        if (entity->posX.i.hi < -16) {
            continue;
        }
        if (entity->posX.i.hi > 272) {
            continue;
        }
        if (entity->posY.i.hi > 240) {
            continue;
        }
        if (entity->posY.i.hi < 0) {
            continue;
        }
        if (!g_DemonAbilityStats[s_DemonStats.level / 10].makeBadAttacks &&
            entity->hitboxState & 8) {
            continue;
        }

        if (abs(self->posX.i.hi - entity->posX.i.hi) >
                g_DemonAbilityStats[s_DemonStats.level / 10]
                    .maxEnemyAxisDelta ||
            abs(self->posY.i.hi - entity->posY.i.hi) >
                g_DemonAbilityStats[s_DemonStats.level / 10]
                    .maxEnemyAxisDelta) {
            continue;
        }
        if (self->facingLeft && self->posX.i.hi < entity->posX.i.hi) {
            continue;
        }
        if (!self->facingLeft && self->posX.i.hi > entity->posX.i.hi) {
            continue;
        }
        if (entity->hitPoints >= 0x7000) {
            continue;
        }

        if (entity->flags & FLAG_UNK_80000) {
            if (entity->hitPoints >=
                g_DemonAbilityStats[s_DemonStats.level / 10].minimumEnemyHp) {
                found++;
                s_TargetMatch[i] = 1;
            }
        } else {
            entity->flags |= FLAG_UNK_80000;
            return entity;
        }
    }

    if (found > 0) {
        foundIndex = s_LastTargetedEntityIndex % EntitySearchCount;
        for (i = 0; i < EntitySearchCount; i++) {
            if (s_TargetMatch[foundIndex]) {
                entity = &g_Entities[STAGE_ENTITY_START + foundIndex];
                s_LastTargetedEntityIndex =
                    (foundIndex + 1) % EntitySearchCount;
                return entity;
            }
            foundIndex = (foundIndex + 1) % EntitySearchCount;
        }
    }

    return NULL;
}

#include "../check_entity_valid.h"

void unused_2DBC(Entity* self) {}

void ExecuteAbilityInitialize(Entity* self) {
    if (!self->ext.demon.isAbilityInitialized) {
        if ((self->entityId == DEMON_MODE_DEFAULT_UPDATE) ||
            (self->entityId == DEMON_MODE_ADDITIONAL_INIT)) {
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;
            SetAnimationFrame(self, 0);

            self->ext.demon.randomMovementAngle = rand() % 4096;
            self->ext.demon.defaultDistToTargetLoc = 8;
            self->ext.demon.targetAngle = 0;
            self->ext.demon.maxAngle = 0x20;
            self->step++;
        }
    } else {
        switch (self->entityId) {
        case DEMON_MODE_DEFAULT_UPDATE:
        case DEMON_MODE_BASIC_ATTACK:
        case DEMON_MODE_SPECIAL_ATTACK:
        case DEMON_MODE_PRESS_SWITCH:
        case DEMON_MODE_ADDITIONAL_INIT:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;
            SetAnimationFrame(self, 0);
            self->step++;
            break;
        }
    }
    D_us_801786D0 = 0;
    self->ext.demon.isAbilityInitialized = self->entityId;
}

void DestroyEntityPassthrough(Entity* self) { DestroyEntity(self); }

void func_us_80172EF8(Entity* self) {
    Primitive* prim;
    s32 posX, posY;

    self->posX.val = self->ext.et_801737F0.parent->posX.val;
    self->posY.val = self->ext.et_801737F0.parent->posY.val;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1A;
        prim->clut = 0x143;
        prim->priority = self->zPriority + 1;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        PCOL(prim) = 0xC0;

        prim = prim->next;
        prim->tpage = 0x1A;
        prim->clut = 0x143;
        prim->priority = self->zPriority + 1;
        prim->drawMode =
            DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;

        self->ext.et_801737F0.animationTriggerCount = 0;
        self->ext.et_801737F0.animationTimer = 0;
        self->step++;
        break;
    case 1:
        self->ext.et_801737F0.animationTriggerCount++;
        self->ext.et_801737F0.animationTriggerCount &= 7;
        self->ext.et_801737F0.animationTimer += 8;
        if (self->ext.et_801737F0.animationTimer >= 0x100) {
            self->step++;
        }
        self->ext.et_801737F0.stepCounter++;
        break;
    case 2:
        self->ext.et_801737F0.animationTriggerCount++;
        self->ext.et_801737F0.animationTriggerCount &= 7;
        self->ext.et_801737F0.stepCounter++;
        if (self->ext.et_801737F0.stepCounter > 50) {
            CreateEventEntity(self, DEMON_MODE_UNK_DB, 0);
            DestroyEntity(self);
            return;
        }
        break;
    }
    posX = self->posX.i.hi + (self->facingLeft ? 6 : -6);
    posY = self->posY.i.hi - 0xC;
    prim = &g_PrimBuf[self->primIndex];

    prim->u0 = prim->u1 =
        D_us_80171B74[self->ext.et_801737F0.animationTriggerCount][0];
    prim->u2 = prim->u3 =
        D_us_80171B74[self->ext.et_801737F0.animationTriggerCount][1];
    prim->v0 = prim->v2 =
        D_us_80171B74[self->ext.et_801737F0.animationTriggerCount][2];
    prim->v1 = prim->v3 =
        D_us_80171B74[self->ext.et_801737F0.animationTriggerCount][3];
    prim->x0 = prim->x2 = posX - self->ext.et_801737F0.animationTimer * 8 / 256;
    prim->x1 = prim->x3 = posX + self->ext.et_801737F0.animationTimer * 8 / 256;
    prim->y0 = prim->y1 =
        posY - self->ext.et_801737F0.animationTimer * 32 / 256;
    prim->y2 = prim->y3 = posY;
    prim = prim->next;
    PCOL(prim) = self->ext.et_801737F0.animationTimer / 2;
    prim->x0 = prim->x2 =
        posX - (0x100 - self->ext.et_801737F0.animationTimer) * 32 / 256;
    prim->x1 = prim->x3 =
        posX + (0x100 - self->ext.et_801737F0.animationTimer) * 32 / 256;
    prim->y0 = prim->y1 =
        posY - (0x100 - self->ext.et_801737F0.animationTimer) * 32 / 256;
    prim->y2 = prim->y3 =
        posY + (0x100 - self->ext.et_801737F0.animationTimer) * 32 / 256;
}

void func_us_80173348(Entity* self) {
    Primitive* prim;
    s32 posX, posY;

    self->posX.val = self->ext.et_801737F0.parent->posX.val;
    self->posY.val = self->ext.et_801737F0.parent->posY.val;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1A;
        prim->clut = 0x146;
        prim->priority = self->zPriority + 1;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        PCOL(prim) = 0x80;

        prim = prim->next;
        prim->tpage = 0x1A;
        prim->clut = 0x145;
        prim->priority = self->zPriority + 1;
        prim->drawMode =
            DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;

        self->ext.et_801737F0.animationTriggerCount = 0;
        self->ext.et_801737F0.animationTimer = 0;
        self->step++;
        break;

    case 1:
        self->ext.et_801737F0.stepCounter++;
        if ((self->ext.et_801737F0.stepCounter % 10) == 0 &&
            self->ext.et_801737F0.animationTriggerCount < 2) {
            self->ext.et_801737F0.animationTriggerCount++;
        }

        self->ext.et_801737F0.animationTimer += 8;
        if (self->ext.et_801737F0.animationTimer >= 0x100) {
            self->step++;
        }
        break;

    case 2:
        self->ext.et_801737F0.stepCounter++;
        if (self->ext.et_801737F0.stepCounter > 0x32) {
            CreateEventEntity(self, DEMON_MODE_UNK_DC, 0);
            DestroyEntity(self);
            return;
        }
        break;
    }

    posX = self->posX.i.hi + (self->facingLeft ? 6 : -6);
    posY = self->posY.i.hi - 0xC;

    prim = &g_PrimBuf[self->primIndex];
    prim->u0 = prim->u2 =
        D_us_80171BF4[self->ext.et_801737F0.animationTriggerCount][0];
    prim->u1 = prim->u3 =
        D_us_80171BF4[self->ext.et_801737F0.animationTriggerCount][1];
    prim->v0 = prim->v1 =
        D_us_80171BF4[self->ext.et_801737F0.animationTriggerCount][2];
    prim->v2 = prim->v3 =
        D_us_80171BF4[self->ext.et_801737F0.animationTriggerCount][3];
    prim->x0 = prim->x2 =
        posX - self->ext.et_801737F0.animationTimer * 16 / 256;
    prim->x1 = prim->x3 =
        posX + self->ext.et_801737F0.animationTimer * 16 / 256;
    prim->y0 = prim->y1 =
        posY - self->ext.et_801737F0.animationTimer * 16 / 256;
    prim->y2 = prim->y3 =
        posY + self->ext.et_801737F0.animationTimer * 16 / 256;

    prim = prim->next;
    PCOL(prim) = self->ext.et_801737F0.animationTimer / 2;
    prim->x0 = prim->x2 =
        posX - (256 - self->ext.et_801737F0.animationTimer) * 32 / 256;
    prim->x1 = prim->x3 =
        posX + (256 - self->ext.et_801737F0.animationTimer) * 32 / 256;
    prim->y0 = prim->y1 =
        posY - (256 - self->ext.et_801737F0.animationTimer) * 32 / 256;
    prim->y2 = prim->y3 =
        posY + (256 - self->ext.et_801737F0.animationTimer) * 32 / 256;
}

// PSX: https://decomp.me/scratch/QGDMn
// PSP: https://decomp.me/scratch/TKY2r
void func_us_801737F0(Entity* self) {
    Primitive* prim;
    s32 sine;
    s32 cosine;
    s32 posXOffset;
    s32 posYOffset;
    s32 scaledCounter;

    self->posX.val = self->ext.et_801737F0.parent->posX.val;
    self->posY.val = self->ext.et_801737F0.parent->posY.val;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;

        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1A;
        prim->clut = 0x147;
        prim->priority = self->zPriority + 1;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim->u0 = prim->u2 = 0xE0;
        prim->u1 = prim->u3 = 0xFF;
        prim->v0 = prim->v1 = 0x80;
        prim->v2 = prim->v3 = 0x9F;
        PCOL(prim) = 0x80;

        prim = prim->next;
        prim->tpage = 0x1A;
        prim->clut = 0x147;
        prim->priority = self->zPriority + 1;
        prim->drawMode =
            DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;

        self->ext.et_801737F0.animationTriggerCount = 0;
        self->ext.et_801737F0.animationTimer = 0;
        self->ext.et_801737F0.angle = 0;

        self->step++;
        break;

    case 1:
        self->ext.et_801737F0.stepCounter++;
        if ((self->ext.et_801737F0.stepCounter % 10 == 0) &&
            (self->ext.et_801737F0.animationTriggerCount < 2)) {
            self->ext.et_801737F0.animationTriggerCount++;
        }

        self->ext.et_801737F0.animationTimer += 8;

        if (self->ext.et_801737F0.animationTimer >= 0x100) {
            self->step++;
        }
        break;

    case 2:
        self->ext.et_801737F0.stepCounter++;

        if (self->ext.et_801737F0.stepCounter > 50) {
            CreateEventEntity(self, DEMON_MODE_UNK_DD, 0);
            DestroyEntity(self);
            return;
        }
        break;
    }

    self->ext.et_801737F0.angle += 0x400;
    self->ext.et_801737F0.angle &= 0xFFF;

    sine = rsin(self->ext.et_801737F0.angle);
    cosine = rcos(self->ext.et_801737F0.angle);

    posXOffset = (self->posX.i.hi) + ((self->facingLeft) ? (6) : (-6));
    posYOffset = self->posY.i.hi - 0xC;
    prim = &g_PrimBuf[self->primIndex];

    scaledCounter = (self->ext.et_801737F0.animationTimer * 16) / 256;

    prim->x0 = posXOffset +
               ((cosine * -(scaledCounter)-sine * -(scaledCounter)) >> 12);
    prim->y0 = posYOffset +
               ((sine * -(scaledCounter) + cosine * -(scaledCounter)) >> 12);

    prim->x1 =
        posXOffset + ((cosine * (scaledCounter)-sine * -(scaledCounter)) >> 12);
    prim->y1 = posYOffset +
               ((sine * (scaledCounter) + cosine * -(scaledCounter)) >> 12);

    prim->x2 =
        posXOffset + ((cosine * -(scaledCounter)-sine * (scaledCounter)) >> 12);
    prim->y2 = posYOffset +
               ((sine * -(scaledCounter) + cosine * (scaledCounter)) >> 12);

    prim->x3 =
        posXOffset + ((cosine * (scaledCounter)-sine * (scaledCounter)) >> 12);
    prim->y3 = posYOffset +
               ((sine * (scaledCounter) + cosine * (scaledCounter)) >> 12);
    PCOL(prim) = (self->ext.et_801737F0.stepCounter & 1) * 128;

    prim = prim->next;

    PCOL(prim) = self->ext.et_801737F0.animationTimer / 2;

    prim->x0 = prim->x2 =
        posXOffset - (256 - self->ext.et_801737F0.animationTimer) * 32 / 256;
    prim->x1 = prim->x3 =
        posXOffset + (256 - self->ext.et_801737F0.animationTimer) * 32 / 256;
    prim->y0 = prim->y1 =
        posYOffset - (256 - self->ext.et_801737F0.animationTimer) * 32 / 256;
    prim->y2 = prim->y3 =
        posYOffset + (256 - self->ext.et_801737F0.animationTimer) * 32 / 256;
}

void func_us_80173D14(Entity* self) {
    Primitive* prim;
    s32 x0, x1, x2, x3;
    s32 y0, y1, y2, y3;
    s32 posX, posY;
    s32 s, c;
    s32 i;

    self->posX.val = self->ext.et_801737F0.parent->posX.val;
    self->posY.val = self->ext.et_801737F0.parent->posY.val;
    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        if (self->facingLeft) {
            s = rsin(0xE00);
            c = rcos(0xE00);
        } else {
            s = rsin(0xA00);
            c = rcos(0xA00);
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 3; i++) {
            prim->tpage = 0x1A;
            prim->clut = 0x147;
            prim->priority = self->zPriority + 1;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim->u0 = prim->u2 = 0xB;
            prim->u1 = prim->u3 = 0x35;
            prim->v0 = prim->v1 = 0xCB;
            prim->v2 = prim->v3 = 0xF5;
            PCOL(prim) = 0x80;
            x0 = D_us_80171B44[i][0];
            y0 = D_us_80171B44[i][1];
            x1 = D_us_80171B44[i][2];
            y1 = D_us_80171B44[i][3];
            x2 = D_us_80171B44[i][4];
            y2 = D_us_80171B44[i][5];
            x3 = D_us_80171B44[i][6];
            y3 = D_us_80171B44[i][7];
            D_us_801786A0[i][0] = ((c * x0) - (s * y0)) >> 0xC;
            D_us_801786A0[i][1] = ((s * x0) + (c * y0)) >> 0xC;
            D_us_801786A0[i][2] = ((c * x1) - (s * y1)) >> 0xC;
            D_us_801786A0[i][3] = ((s * x1) + (c * y1)) >> 0xC;
            D_us_801786A0[i][4] = ((c * x2) - (s * y2)) >> 0xC;
            D_us_801786A0[i][5] = ((s * x2) + (c * y2)) >> 0xC;
            D_us_801786A0[i][6] = ((c * x3) - (s * y3)) >> 0xC;
            D_us_801786A0[i][7] = ((s * x3) + (c * y3)) >> 0xC;
            prim = prim->next;
        }
        prim->tpage = 0x1A;
        prim->clut = 0x147;
        prim->priority = self->zPriority + 1;
        prim->drawMode =
            DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xFF;
        self->step++;
        break;
    case 1:
        self->ext.et_801737F0.animationTriggerCount++;
        self->ext.et_801737F0.animationTimer += 8;
        if (self->ext.et_801737F0.animationTimer >= 0x100) {
            self->step++;
        }
        break;
    case 2:
        self->ext.et_801737F0.animationTriggerCount++;
        if (self->ext.et_801737F0.animationTriggerCount > 50) {
            CreateEventEntity(self, DEMON_MODE_UNK_DE, 0);
            DestroyEntity(self);
            return;
        }
        break;
    }

    posX = self->posX.i.hi + (self->facingLeft ? 2 : -2);
    posY = self->posY.i.hi - 0xC;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 3; i++) {
        prim->x0 = posX + D_us_801786A0[i][0] *
                              self->ext.et_801737F0.animationTimer / 256;
        prim->y0 = posY + D_us_801786A0[i][1] *
                              self->ext.et_801737F0.animationTimer / 256;
        prim->x1 = posX + D_us_801786A0[i][2] *
                              self->ext.et_801737F0.animationTimer / 256;
        prim->y1 = posY + D_us_801786A0[i][3] *
                              self->ext.et_801737F0.animationTimer / 256;
        prim->x2 = posX + D_us_801786A0[i][4] *
                              self->ext.et_801737F0.animationTimer / 256;
        prim->y2 = posY + D_us_801786A0[i][5] *
                              self->ext.et_801737F0.animationTimer / 256;
        prim->x3 = posX + D_us_801786A0[i][6] *
                              self->ext.et_801737F0.animationTimer / 256;
        prim->y3 = posY + D_us_801786A0[i][7] *
                              self->ext.et_801737F0.animationTimer / 256;
        PCOL(prim) =
            ((self->ext.et_801737F0.animationTriggerCount & 1) * 64) + 0x40;
        prim = prim->next;
    }

    posX = self->posX.i.hi + (self->facingLeft ? 4 : -4);
    PCOL(prim) = self->ext.et_801737F0.animationTimer / 2;
    prim->x0 = prim->x2 =
        posX - (0x100 - self->ext.et_801737F0.animationTimer) * 32 / 256;
    prim->x1 = prim->x3 =
        posX + (0x100 - self->ext.et_801737F0.animationTimer) * 32 / 256;
    prim->y0 = prim->y1 =
        posY - (0x100 - self->ext.et_801737F0.animationTimer) * 32 / 256;
    prim->y2 = prim->y3 =
        posY + (0x100 - self->ext.et_801737F0.animationTimer) * 32 / 256;
}

void ServantInit(InitializeMode mode) {
    u16* src;
    u16* dst;
    RECT rect;
    s32 i;
    SpriteParts** spriteBanks;
    Entity* entity;

#ifdef VERSION_PC
    const int lenServant = LEN(g_ServantClut);
    const int lenDemon = LEN(g_DemonClut);
#else
    const int lenServant = 256;
    const int lenDemon = 80;
#endif

    s_ServantId = g_Servant;

    if ((mode == MENU_SWITCH_SERVANT) || (mode == MENU_SAME_SERVANT)) {
        ProcessEvent(NULL, true);
        if (mode == MENU_SAME_SERVANT) {
            return;
        }
    }

    dst = &g_Clut[CLUT_INDEX_SERVANT];
    src = g_ServantClut;
    for (i = 0; i < lenServant; i++) {
        *dst++ = *src++;
    }

    dst = &g_Clut[CLUT_INDEX_SERVANT_OVERWRITE];
    src = g_DemonClut;

    for (i = 0; i < lenDemon; i++) {
        *dst++ = *src++;
    }

    rect.x = 0;
    rect.w = 0x100;
    rect.h = 1;
    rect.y = 0xF4;

    dst = &g_Clut[CLUT_INDEX_SERVANT];
    LoadImage(&rect, (u_long*)dst);

    spriteBanks = g_api.o.spriteBanks;
    spriteBanks += 20;
    *spriteBanks = (SpriteParts*)g_DemonSpriteParts;

    entity = &g_Entities[SERVANT_ENTITY_INDEX];

    DestroyEntity(entity);
    entity->unk5A = 0x6C;
    entity->palette = 0x140;
    entity->animSet = ANIMSET_OVL(20);
    entity->zPriority = PLAYER.zPriority - 2;
    entity->facingLeft = PLAYER.facingLeft;
    entity->params = 0;

    if (mode == MENU_SWITCH_SERVANT) {
        if (LOW(D_8003C708.flags) &
            (LAYOUT_RECT_PARAMS_UNKNOWN_20 | LAYOUT_RECT_PARAMS_UNKNOWN_40)) {
            entity->entityId = DEMON_MODE_DEFAULT_UPDATE;
        } else {
            entity->entityId = DEMON_MODE_ADDITIONAL_INIT;
        }
        entity->posX.val = FIX(128);
        entity->posY.val = FIX(-32);
    } else {
        entity->entityId = DEMON_MODE_DEFAULT_UPDATE;
        if (D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_20) {
            if (ServantUnk0()) {
                entity->posX.val = FIX(192);
            } else {
                entity->posX.val = FIX(64);
            }
            entity->posY.val = FIX(160);
        } else {
            entity->posX.val =
                PLAYER.posX.val + (PLAYER.facingLeft ? FIX(24) : FIX(-24));
            entity->posY.val = PLAYER.posY.val + FIX(-32);
        }
    }

    D_us_801786D0 = 0;
    D_us_801786D4 = 0;
    g_api.GetServantStats(entity, 0, 0, &s_DemonStats);
}

void UpdateServantDefault(Entity* self) {
    s32 temp;
    s32 i;
    s32 rnd;

    g_api.GetServantStats(self, 0, 0, &s_DemonStats);
    if (D_us_801786D4) {
        self->zPriority = PLAYER.zPriority - 2;
    }

    if (D_8003C708.flags & FLAG_UNK_20) {
        switch (ServantUnk0()) {
        case 0:
            s_TargetLocationX = 0x40;
            break;
        case 1:
            s_TargetLocationX = 0xC0;
            break;
        case 2:

            if (self->posX.i.hi > 0x80) {
                temp = 0xC0;
            } else {
                temp = 0x40;
            }
            s_TargetLocationX = temp;
            break;
        }
        s_TargetLocationY = 0xA0;
    } else {
        s_TargetLocOffset_calc = -0x18;
        if (PLAYER.facingLeft) {
            s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
        }
        s_TargetLocationX_calc = g_Entities->posX.i.hi + s_TargetLocOffset_calc;
        s_TargetLocationY_calc = PLAYER.posY.i.hi - 0x20;

        s_AngleToTarget = self->ext.demon.randomMovementAngle;
        self->ext.demon.randomMovementAngle += 0x10;
        self->ext.demon.randomMovementAngle &= 0xFFF;
        s_DistToTargetLocation = self->ext.demon.defaultDistToTargetLoc;

        s_TargetLocationX =
            s_TargetLocationX_calc +
            ((rcos(s_AngleToTarget / 2) * s_DistToTargetLocation) >> 0xC);
        s_TargetLocationY =
            s_TargetLocationY_calc -
            ((rsin(s_AngleToTarget) * (s_DistToTargetLocation / 2)) >> 0xC);
    }
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        break;
    case 1:
        if (D_8003C708.flags & FLAG_UNK_20) {
            if (PLAYER.posX.i.hi >= self->posX.i.hi) {
                self->facingLeft = 0;
            } else {
                self->facingLeft = 1;
            }
        } else {
            if (PLAYER.facingLeft != self->facingLeft) {
                if (abs(s_TargetLocationX - self->posX.i.hi) <= 0) {
                    self->facingLeft = PLAYER.facingLeft;
                } else if (
                    !self->facingLeft && s_TargetLocationX < self->posX.i.hi) {
                    self->facingLeft = PLAYER.facingLeft;
                } else if (
                    self->facingLeft && s_TargetLocationX > self->posX.i.hi) {
                    self->facingLeft = PLAYER.facingLeft;
                }
            } else if (!self->facingLeft &&
                       (self->posX.i.hi - s_TargetLocationX) > 0x28) {
                self->facingLeft = PLAYER.facingLeft ? 0 : 1;
            } else if (self->facingLeft &&
                       (s_TargetLocationX - self->posX.i.hi) > 0x28) {
                self->facingLeft = PLAYER.facingLeft ? 0 : 1;
            }
        }

        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = GetTargetPositionWithDistanceBuffer(
            s_AngleToTarget, self->ext.demon.targetAngle,
            self->ext.demon.maxAngle);
        self->ext.demon.targetAngle = s_AllowedAngle;
        s_TargetLocationX_calc = s_TargetLocationX - self->posX.i.hi;
        s_TargetLocationY_calc = s_TargetLocationY - self->posY.i.hi;
        s_DistToTargetLocation =
            SquareRoot12(((s_TargetLocationX_calc * s_TargetLocationX_calc) +
                          (s_TargetLocationY_calc * s_TargetLocationY_calc))
                         << 0xC) >>
            0xC;
        if (s_DistToTargetLocation < 0x28) {
            self->velocityY = -(rsin((s32)s_AllowedAngle) << 3);
            self->velocityX = rcos((s32)s_AllowedAngle) << 3;
            self->ext.demon.maxAngle = 0x20;
        } else if (s_DistToTargetLocation < 0x3C) {
            self->velocityY = -(rsin((s32)s_AllowedAngle) << 4);
            self->velocityX = rcos((s32)s_AllowedAngle) << 4;
            self->ext.demon.maxAngle = 0x40;
        } else if (s_DistToTargetLocation < 0x64) {
            self->velocityY = -(rsin((s32)s_AllowedAngle) << 5);
            self->velocityX = rcos((s32)s_AllowedAngle) << 5;
            self->ext.demon.maxAngle = 0x60;
        } else if (s_DistToTargetLocation < 0x100) {
            self->velocityY = -(rsin((s32)s_AllowedAngle) << 6);
            self->velocityX = rcos((s32)s_AllowedAngle) << 6;
            self->ext.demon.maxAngle = 0x80;
        } else {
            self->velocityX = (s_TargetLocationX - self->posX.i.hi) << 0xE;
            self->velocityY = (s_TargetLocationY - self->posY.i.hi) << 0xE;
            self->ext.demon.maxAngle = 0x80;
        }
        if (self->velocityY > FIX(1.0)) {
            SetAnimationFrame(self, 0xA);
        } else if (s_DistToTargetLocation < 0x3C) {
            SetAnimationFrame(self, 0);

        } else if (s_DistToTargetLocation > 0x64) {
            SetAnimationFrame(self, 0xB);
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (!g_CutsceneHasControl) {
            s_DeltaX = s_TargetLocationX - self->posX.i.hi;
            s_DeltaY = s_TargetLocationY - self->posY.i.hi;

            s_DistToTargetLocation2 =
                SquareRoot12(
                    ((s_DeltaX * s_DeltaX) + (s_DeltaY * s_DeltaY)) << 0xC) >>
                0xC;

            if (s_DistToTargetLocation2 < 0x20) {
                self->ext.demon.abilityTimer++;
                if (self->ext.demon.abilityTimer >
                    g_DemonAbilityStats[s_DemonStats.level / 10].timer) {
                    self->ext.demon.abilityTimer = 0;

                    if (self->ext.demon.target = FindValidTarget(self)) {
                        if (rand() % 0x100 <=
                            g_DemonAttackSelector[s_DemonStats.level / 10][0]) {
                            self->entityId = DEMON_MODE_BASIC_ATTACK;
                        } else {
                            self->entityId = DEMON_MODE_SPECIAL_ATTACK;
                        }
                        self->step = 0;
                    }
                }
            }
            // This is likely dead code and not actually valid as it's doing
            // some weird stuff with g_Events that doesn't make any sense.  And
            // it only does it with the N Demon, which was stripped out anyway
            if (s_ServantId == FAM_ACTIVE_NOSE_DEMON) {
                if (!g_CutsceneHasControl && !IsMovementAllowed(1) &&
                    !CheckAllEntitiesValid() &&
                    !(D_8003C708.flags & FLAG_UNK_20) && !D_us_801786D0) {
                    if (self->ext.demon.unkCounter <= 18000) {
                        self->ext.demon.unkCounter++;
                    }
                } else {
                    self->ext.demon.unkCounter = 0;
                }
                if (self->ext.demon.unkCounter == 18000) {

                    for (rnd = rand() % 0x100, i = 0; true; i++) {
                        if (rnd <= ((s16*)g_Events)[i * 2]) {
                            CreateEventEntity(self, DEMON_EVENT_SFX_PASSTHROUGH,
                                              ((s16*)g_Events)[i * 2 + 1]);
                            break;
                        }
                    }
                }
            }
            if (D_us_801786D0 == 2) {
                s_CurrentSwitch = 0;
                CreateEventEntity(self, DEMON_SUBENTITY_SWITCH, 0);
                self->entityId = DEMON_MODE_PRESS_SWITCH;
                self->step = 0;
            }
        }
        break;
    }
    ProcessEvent(self, false);
    unused_2DBC(self);
    ServantUpdateAnim(self, g_DemonFrameProps, g_DemonAnimationFrames);
}

void UpdateServantBasicAttack(Entity* self) {
    if (D_us_801786D4) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        break;
    case 1:
        s_IsTargetFacingLeft = self->ext.demon.target->facingLeft;
        self->step++;
        // fallthrough
    case 2:
        if (!CheckEntityValid(self->ext.demon.target) &&
            !(self->ext.demon.target = FindValidTarget(self))) {
            self->entityId = DEMON_MODE_DEFAULT_UPDATE;
            self->step = 0;
        } else {
            s_AttackTargetLocationX = self->ext.demon.target->posX.val;
            s_AttackTargetLocationX +=
                s_IsTargetFacingLeft ? FIX(32) : FIX(-32);

            s_AttackTargetLocationY = self->ext.demon.target->posY.val;
            self->velocityX = (s_AttackTargetLocationX - self->posX.val) >> 3;
            self->velocityY = (s_AttackTargetLocationY - self->posY.val) >> 3;

            self->facingLeft = self->velocityX > 0 ? 0 : 1;
            self->posX.val += self->velocityX;

            self->posY.val += self->velocityY;
            s_AttackLocationDeltaX =
                abs(s_AttackTargetLocationX - self->posX.val);
            s_AttackLocationDeltaY =
                abs(s_AttackTargetLocationY - self->posY.val);
            if ((s_AttackLocationDeltaX < FIX(8)) &&
                (s_AttackLocationDeltaY < FIX(1))) {
                self->facingLeft = s_IsTargetFacingLeft;
                self->step++;
            }
        }
        break;
    case 3:
        s_TempRand = rand() % 2;
        SetAnimationFrame(self, s_TempRand ? 1 : 3);

        g_api.GetServantStats(
            self,
            s_TempRand ? FAM_ABILITY_DEMON_UNK21 : FAM_ABILITY_DEMON_UNK22, 1,
            &s_DemonStats);

        s_TempRand = rand() % 8;
        switch (s_TempRand) {
        case 0:
            g_api.PlaySfx(g_DemonSfxMap[0]);
            break;
        case 1:
            g_api.PlaySfx(g_DemonSfxMap[1]);
            break;
        case 2:
            g_api.PlaySfx(g_DemonSfxMap[2]);
            break;
        }
        self->step++;
        break;
    case 4:
        if (s_AttackAnimationStatus == -2) {
            self->ext.demon.abilityTimer = 0;
            self->step++;
        }
        break;
    case 5:
        self->velocityX = self->facingLeft ? FIX(0.125) : FIX(-0.125);
        self->velocityY = FIX(-0.25);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->ext.demon.abilityTimer++;
        if (self->ext.demon.abilityTimer > 30) {
            self->step++;
        }
        break;
    case 6:
        if (g_CutsceneHasControl ||
            !(self->ext.demon.target = FindValidTarget(self))) {
            self->entityId = DEMON_MODE_DEFAULT_UPDATE;
            self->step = 0;
            break;
        }
        if ((rand() % 0x100) <=
            g_DemonAttackSelector[s_DemonStats.level / 10][0]) {
            self->step = 1;
        } else {
            self->entityId = DEMON_MODE_SPECIAL_ATTACK;
            self->step = 0;
        }

        break;
    }
    s_AttackAnimationStatus =
        ServantUpdateAnim(self, g_DemonFrameProps, g_DemonAnimationFrames);
}

// PSX: https://decomp.me/scratch/vbedA
// PSP: https://decomp.me/scratch/mRGqb
void UpdateServantSpecialAttack(Entity* self) {
    s32 i;

    if (D_us_801786D4) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        break;
    case 1:
        s_IsSpecialAttackTargetFacingLeft = self->ext.demon.target->facingLeft;
        self->step++;

    case 2:
        if (!CheckEntityValid(self->ext.demon.target) &&
            !(self->ext.demon.target = FindValidTarget(self))) {
            self->entityId = DEMON_MODE_DEFAULT_UPDATE;
            self->step = 0;
        } else {
            s_SpecialAttackTargetPosX = self->ext.demon.target->posX.val;
            s_SpecialAttackTargetPosX +=
                s_IsSpecialAttackTargetFacingLeft ? FIX(32) : FIX(-32);

            s_SpecialAttackTargetPosY = self->ext.demon.target->posY.val;
            self->velocityX = (s_SpecialAttackTargetPosX - self->posX.val) >> 3;
            self->velocityY = (s_SpecialAttackTargetPosY - self->posY.val) >> 3;
            self->facingLeft = self->velocityX > 0 ? 0 : 1;

            self->posX.val += self->velocityX;
            self->posY.val += self->velocityY;

            s_SpecialAttackLocationDeltaX =
                abs(s_SpecialAttackTargetPosX - self->posX.val);
            s_SpecialAttackLocationDeltaY =
                abs(s_SpecialAttackTargetPosY - self->posY.val);
            if ((s_SpecialAttackLocationDeltaX < FIX(8)) &&
                (s_SpecialAttackLocationDeltaY < FIX(1))) {
                self->facingLeft = s_IsSpecialAttackTargetFacingLeft;
                self->step++;
            }
        }
        break;
    case 3:
        s_SpecialAttackIdx = rand() % 256;

        for (i = 1; i < 6; i++) {
            if (s_SpecialAttackIdx <=
                g_DemonAttackSelector[s_DemonStats.level / 10][i]) {
                s_SpecialAttackIdx = i - 1;
                break;
            }
        }

        SetAnimationFrame(
            self, g_DemonAttackIdSfxLookup[s_SpecialAttackIdx].animationIndex);
        g_api.PlaySfx(g_DemonSfxMap[g_DemonAttackIdSfxLookup[s_SpecialAttackIdx]
                                        .sfxIndex]);

        g_api.GetServantStats(
            self, g_DemonAttackIdSfxLookup[s_SpecialAttackIdx].abilityId, 1,
            &s_DemonStats);
        // This is for the different Attack types.  Param selects update
        // function from passthrough array
        CreateEventEntity(
            self, DEMON_SPECIAL_ATTACK_UPDATE, s_SpecialAttackIdx);

        self->step++;
        break;
    case 4:
        if (s_SpecialAttackAnimationStatus == -2) {
            self->ext.demon.abilityTimer = 0;
            self->step++;
        }
        break;
    case 5:
        self->velocityX = self->facingLeft ? FIX(0.125) : FIX(-0.125);
        self->velocityY = FIX(-0.25);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;

        self->ext.demon.abilityTimer++;

        if (self->ext.demon.abilityTimer > 30) {
            self->entityId = DEMON_MODE_DEFAULT_UPDATE;
            self->step = 0;
        }
        break;
    }
    s_SpecialAttackAnimationStatus =
        ServantUpdateAnim(self, g_DemonFrameProps, g_DemonAnimationFrames);
}

void unused_5800(Entity* self) {}
void unused_5808(Entity* self) {}

void UpdateServantPressSwitch(Entity* self) {
    Entity* sfxEntity;
    s32 xCalc;
    s32 yCalc;
    s32 facingLeft;

    if (D_us_801786D4) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    if (s_CurrentSwitch) {
        s_SwitchPoxX = s_CurrentSwitch->posX.val;
        s_SwitchPoxY = s_CurrentSwitch->posY.val;
        self->ext.demon.switchPressVelocityOffset += 0x40;
        self->ext.demon.switchPressVelocityOffset &= 0xFFF;
        s_SwitchPoxY =
            (rsin((s32)self->ext.demon.switchPressVelocityOffset) << 3 << 4) +
            s_SwitchPoxY;

        self->velocityX = (s_SwitchPoxX - self->posX.val) >> 5;
        self->velocityY = (s_SwitchPoxY - self->posY.val) >> 5;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
    }
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        break;
    case 1:
        if (self->velocityX > 0) {
            facingLeft = false;
        } else {
            facingLeft = true;
        }
        self->facingLeft = facingLeft;

        xCalc = (s_SwitchPoxX - self->posX.val) >> 0x10;
        yCalc = (s_SwitchPoxY - self->posY.val) >> 0x10;
        if ((SquareRoot12((SQ(xCalc) + SQ(yCalc)) << 0xC) >> 0xC) < 0x10) {
            if (g_StageId < STAGE_RNO0 || g_StageId >= STAGE_RNZ1_DEMO) {
                self->facingLeft = 0;
                s_SwitchSfxEvent =
                    (ServantSfxEventDesc*)g_SfxDemonSwitchRandomizer[1];
            } else {
                self->facingLeft = 1;
                s_SwitchSfxEvent =
                    (ServantSfxEventDesc*)g_SfxDemonSwitchRandomizer[3];
            }
            self->step++;
        }
        break;
    case 2:
        s_CurrentSwitchSfxFlag = ((s16*)s_SwitchSfxEvent)[0];
#ifndef VERSION_PSP
        g_PauseAllowed = false;
#endif
        self->step++;
        // fallthrough
    case 3:

        if (s_CurrentSwitchSfxFlag < 0) {
            if (g_PlaySfxStep > 4) {

                SetAnimationFrame(self, s_SwitchSfxEvent->animIndex);
#ifndef VERSION_PSP
                g_PauseAllowed = true;
#endif
                self->step++;
            }
        } else {
            if ((g_PlaySfxStep == 4) || (g_PlaySfxStep >= 0x63)) {
                s_CurrentSwitchSfxFlag--;
            }
            if (s_CurrentSwitchSfxFlag < 0) {
                SetAnimationFrame(self, s_SwitchSfxEvent->animIndex);
                if (s_SwitchSfxEvent->sfxId != 0 &&
                    !SearchForEntityInRange(0, DEMON_EVENT_SFX_PASSTHROUGH)) {
                    CreateEventEntity(self, DEMON_EVENT_SFX_PASSTHROUGH,
                                      s_SwitchSfxEvent->sfxId);
                }
                s_SwitchSfxEvent++;
                s_CurrentSwitchSfxFlag = ((s16*)s_SwitchSfxEvent)[0];
            }
        }
        break;
    case 4:
        self->ext.demon.attackEndCounter++;
        if (self->ext.demon.attackEndCounter > 120) {
            self->entityId = DEMON_MODE_DEFAULT_UPDATE;
            self->step = 0;
        }
        break;
    }

    if (s_CurrentSwitch && !s_CurrentSwitch->entityId) {
#ifndef VERSION_PSP
        g_PauseAllowed = true;
#endif
        self->entityId = DEMON_MODE_DEFAULT_UPDATE;
        self->step = 0;

        if ((sfxEntity =
                 SearchForEntityInRange(0, DEMON_EVENT_SFX_PASSTHROUGH)) &&
            sfxEntity->step < 5) {
            sfxEntity->step = 7;
        }
    }
    if ((self->anim == g_DemonAnimationFrames[7]) &&
        (self->animFrameIdx == 8)) {
        D_us_801786DC = 1;
    }
    ServantUpdateAnim(self, NULL, g_DemonAnimationFrames);
}

void UpdateSubentitySwitch(Entity* self) {

    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        s_CurrentSwitch = self;
        D_us_801786DC = 0;

        if (g_StageId < STAGE_RNO0 || g_StageId >= STAGE_RNZ1_DEMO) {
            self->posX.i.hi = 200;
            self->posY.i.hi = 36;
            self->facingLeft = 0;
        } else {
            self->posX.i.hi = 56;
            self->posY.i.hi = 196;
            self->facingLeft = 1;
        }

        self->step++;
        break;

    case 1:
        if (D_us_801786DC != 0) {
            self->hitboxOffX = 0x18;
            self->hitboxOffY = 4;
            self->hitboxWidth = 2;
            self->hitboxHeight = 2;
            self->attackElement = 0x20;
            self->hitboxState = 2;
            self->attack = 0;
            self->nFramesInvincibility = 0;
            self->stunFrames = 0;
            self->hitEffect = 7;
            self->entityRoomIndex = 0;

            g_api.func_80118894(self);

            self->step++;
        }
    case 2:
        return;
    }
}

void UpdateServantAdditionalInit(Entity* self) {
    s16 rnd;
    s32 i;

    g_api.GetServantStats(self, 0, 0, &s_DemonStats);
    if (D_us_801786D4) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    D_us_80178658 = -0x18;
    if (!PLAYER.facingLeft) {
        D_us_80178658 = -D_us_80178658;
    }

    D_us_80178644 = PLAYER.posX.i.hi + D_us_80178658;
    D_us_80178648 = PLAYER.posY.i.hi - 0x20;
    D_us_8017864C = self->ext.demon.randomMovementAngle;
    self->ext.demon.randomMovementAngle += 0x10;
    self->ext.demon.randomMovementAngle &= 0xFFF;
    D_us_80178654 = self->ext.demon.defaultDistToTargetLoc;

    D_us_8017863C =
        D_us_80178644 + (rcos(D_us_8017864C / 2) * (D_us_80178654) >> 0xC);
    D_us_80178640 =
        D_us_80178648 - (rsin(D_us_8017864C) * (D_us_80178654 / 2) >> 0xC);

    D_us_8017864C = CalculateAngleToEntity(self, D_us_8017863C, D_us_80178640);
    D_us_80178650 = GetTargetPositionWithDistanceBuffer(
        D_us_8017864C, self->ext.demon.targetAngle, self->ext.demon.maxAngle);
    self->ext.demon.targetAngle = D_us_80178650;
    D_us_80178644 = D_us_8017863C - self->posX.i.hi;
    D_us_80178648 = D_us_80178640 - self->posY.i.hi;
    D_us_80178654 =
        SquareRoot12(
            ((D_us_80178644 * D_us_80178644) + (D_us_80178648 * D_us_80178648))
            << 0xC) >>
        0xC;
    if (D_us_80178654 < 0x3C) {
        self->velocityY = -(rsin(D_us_80178650) << 3);
        self->velocityX = (rcos(D_us_80178650) << 3);
        self->ext.demon.maxAngle = 0x40;
    } else if (D_us_80178654 < 0x64) {
        self->velocityY = -(rsin(D_us_80178650) << 4);
        self->velocityX = (rcos(D_us_80178650) << 4);
        self->ext.demon.maxAngle = 0x60;
    } else {
        self->velocityY = -(rsin(D_us_80178650) << 5);
        self->velocityX = (rcos(D_us_80178650) << 5);
        self->ext.demon.maxAngle = 0x80;
    }
    self->posX.val += self->velocityX;
    self->posY.val += self->velocityY;
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        break;
    case 1:
        if (PLAYER.facingLeft != self->facingLeft) {
            if (abs(D_us_8017863C - self->posX.i.hi) <= 0) {
                self->facingLeft = PLAYER.facingLeft;
            } else if (!self->facingLeft && D_us_8017863C < self->posX.i.hi) {
                self->facingLeft = PLAYER.facingLeft;
            } else if (self->facingLeft && D_us_8017863C > self->posX.i.hi) {
                self->facingLeft = PLAYER.facingLeft;
            }
        } else if (
            !self->facingLeft && (self->posX.i.hi - D_us_8017863C) > 40) {
            self->facingLeft = PLAYER.facingLeft ? 0 : 1;
        } else if (self->facingLeft && (D_us_8017863C - self->posX.i.hi) > 40) {
            self->facingLeft = PLAYER.facingLeft ? 0 : 1;
        }
        if (self->velocityY > FIX(1.0)) {
            SetAnimationFrame(self, 10);
        } else if (D_us_80178654 < 60) {
            SetAnimationFrame(self, 0);
        } else if (D_us_80178654 > 100) {
            SetAnimationFrame(self, 11);
        }
        if (IsMovementAllowed(1) || CheckAllEntitiesValid() ||
            D_us_801786D0 == 1 || g_CutsceneHasControl ||
            g_unkGraphicsStruct.D_800973FC) {
            SetAnimationFrame(self, 0);
            self->entityId = DEMON_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }
        D_us_8017865C = D_us_8017863C - self->posX.i.hi;
        D_us_80178660 = D_us_80178640 - self->posY.i.hi;
        D_us_80178664 = SquareRoot12(((D_us_8017865C * D_us_8017865C) +
                                      (D_us_80178660 * D_us_80178660))
                                     << 0xC) >>
                        0xC;
        if (D_us_80178664 < 0x20) {
            self->facingLeft = PLAYER.facingLeft ? 0 : 1;
            self->step++;
        }
        break;
    case 2:
        rnd = rand() % 0x100;
        if (s_DemonStats.unk8 == true) {
            for (i = 0; true; i++) {
                if (rnd <= g_SfxDemonIntroPrevSummoned[i * 2]) {
                    s_CurrentIntroEvent = (ServantSfxEventDesc*)
                        g_SfxDemonIntroPrevSummoned[i * 2 + 1];
                    break;
                }
            }
        } else {
            for (i = 0; true; i++) {
                if (rnd <= g_SfxDemonIntroNewSummoned[i * 2]) {
                    s_CurrentIntroEvent = (ServantSfxEventDesc*)
                        g_SfxDemonIntroNewSummoned[i * 2 + 1];
                    break;
                }
            }
        }
        s_CurrentIntroSfxFlag = ((s16*)s_CurrentIntroEvent)[0];
        g_PauseAllowed = false;
        self->step++;
        break;
    case 3:
        if (PLAYER.posX.i.hi >= self->posX.i.hi) {
            self->facingLeft = false;
        } else {
            self->facingLeft = true;
        }
        if (s_CurrentIntroSfxFlag < 0) {
            if (g_PlaySfxStep > 4) {
                SetAnimationFrame(self, s_CurrentIntroEvent->animIndex);
                self->step++;
            }
            break;
        }
        if ((g_PlaySfxStep == 4) || (g_PlaySfxStep >= 99)) {
            s_CurrentIntroSfxFlag--;
        }
        if (s_CurrentIntroSfxFlag < 0) {
            SetAnimationFrame(self, s_CurrentIntroEvent->animIndex);
            if ((s_CurrentIntroEvent->sfxId != 0) &&
                (SearchForEntityInRange(0, DEMON_EVENT_SFX_PASSTHROUGH) ==
                 NULL)) {
                CreateEventEntity(self, DEMON_EVENT_SFX_PASSTHROUGH,
                                  s_CurrentIntroEvent->sfxId);
            }
            s_CurrentIntroEvent++;
            s_CurrentIntroSfxFlag = ((s16*)s_CurrentIntroEvent)[0];
        }
        break;
    case 4:
        if (g_PlaySfxStep == 99) {
            self->step++;
        }
        break;
    case 5:
        SetAnimationFrame(self, 0);
        g_PauseAllowed = true;
        self->entityId = DEMON_MODE_DEFAULT_UPDATE;
        self->step = 0;
        break;
    }
    ProcessEvent(self, false);
    ServantUpdateAnim(self, g_DemonFrameProps, g_DemonAnimationFrames);
}

void UpdateServantSfxPassthrough(Entity* self) { ProcessSfxState(self); }

void UpdateEventAttack(Entity* self) { g_AttackFunctions[self->params](self); }

void func_us_801765A0(Entity* self) {
    s32 velocityX;
    s32 posX_hi;
    s16 step;
    switch (self->step) {
    case 0: {
        if (self->params == 0) {
            D_us_80178670 = self->posX.val;
            D_us_80178674 = self->posY.val;
        } else {
            self->posX.val = D_us_80178670;
            self->posY.val = D_us_80178674;
        }

        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        self->palette = 0x8143;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->animSet = 0xE;
        self->unk5A = 0x79;
        self->anim = &D_us_80171CD8;
        self->animFrameIdx = 0;
        self->animFrameDuration = 0;
        self->drawFlags |= FLAG_DRAW_ROTY;
        self->rotY = 0xC0;

        // velocityX = 0xC0;
        if (self->facingLeft != 0) {
            velocityX = -0xC000;

        } else {
            velocityX = 0xC000;
        }
        self->velocityX = velocityX;

        switch (self->params) {
        case 2:
            self->posY.i.hi += 8;
        case 1:
            self->posY.i.hi += 8;
        case 0:
            self->posX.i.hi += (self->facingLeft ? -0x20 : 0x20);
        }

        g_api.GetServantStats(self, FAM_ABILITY_DEMON_UNK24, 1, &s_DemonStats);

        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->hitboxWidth = 0xC;
        self->hitboxHeight = 0xA;

        self->step++;
        if (self->params >= 2) {
            self->step++;
        }
        break;
    }

    case 1: {

        self->posX.val += self->velocityX;

        self->ext.et_80176814.frameCounter[1]++;

        if (self->ext.et_80176814.frameCounter[1] >= 7) {
            CreateEventEntity(self, DEMON_MODE_UNK_DB, self->params + 1);
            self->step++;
        }

        break;
    }

    case 2: {
        self->posX.val += self->velocityX;

        if (self->ext.et_80176814.frameCounter[0] == -1) {
            DestroyEntity(self);
            return;
        }
    }
    default:
        break;
    }

    self->ext.et_80176814.frameCounter[0] = ServantUpdateAnim(self, NULL, NULL);
}

// PSX: https://decomp.me/scratch/NMQwa
// PSP: https://decomp.me/scratch/6hM5K
void func_us_80176814(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 newX;
    s32 newY;
    s32 offset;

    switch (self->step) {
    case 0:
        if (self->params == 0) {
            D_us_80178678 = self->posX.val;
            D_us_8017867C = self->posY.val;
        } else {
            self->posX.val = D_us_80178678;
            self->posY.val = D_us_8017867C;
        }

        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0xC);

        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 12; i++) {
            prim->tpage = 0x1A;
            prim->clut = 0x146;
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;

            offset = (i % 4) * 4;
            prim->u0 = prim->u2 = offset + 8;
            prim->u1 = prim->u3 = (offset) + 0xC;
            prim->v0 = prim->v1 = 0x60;
            prim->v2 = prim->v3 = 0x80;
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = 0x80;
            prim = prim->next;
        }
        self->velocityX = self->facingLeft ? FIX(-4.0) : FIX(4.0);

        g_api.GetServantStats(self, FAM_ABILITY_DEMON_UNK25, 1, &s_DemonStats);

        self->hitboxOffX = 28;
        self->hitboxOffY = 0;
        self->hitboxWidth = 12;
        self->hitboxHeight = 10;

        self->step++;

        if (self->params >= 2) {
            self->step++;
        }
        break;

    case 1:
        self->posX.val += self->velocityX;
        self->ext.et_80176814.frameCounter[0]++;

        if (self->ext.et_80176814.frameCounter[0] >= 3) {
            CreateEventEntity(self, 220, self->params + 1);
            self->step++;
        }
        break;

    case 2:
        self->posX.val += self->velocityX;
        self->ext.et_80176814.frameCounter[0]++;
        if (self->ext.et_80176814.frameCounter[0] >= 9) {
            DestroyEntity(self);
            return;
        }
    }
    newX = self->posX.i.hi;
    newY = self->posY.i.hi - 12;
    prim = &g_PrimBuf[self->primIndex];

    for (i = 0; i < 12; i++) {
        if (self->facingLeft) {
            prim->x2 = newX - D_us_80171D10[i];
            prim->x3 = newX - D_us_80171D10[i + 1];
            if (i == 0) {
                prim->x0 = prim->x2 - 0x10;
            } else {
                prim->x0 = prim->x2 - 0x20;
            }
            if (i == 11) {
                prim->x1 = prim->x3 - 0x10;
            } else {
                prim->x1 = prim->x3 - 0x20;
            }

        } else {
            prim->x2 = newX + D_us_80171D10[i];
            prim->x3 = newX + D_us_80171D10[i + 1];

            if (i == 0) {
                prim->x0 = prim->x2 + 0x10;
            } else {
                prim->x0 = prim->x2 + 0x20;
            }
            if (i == 11) {
                prim->x1 = prim->x3 + 0x10;
            } else {
                prim->x1 = prim->x3 + 0x20;
            }
        }

        prim->y0 = prim->y2 = newY + (i * 2);
        prim->y1 = prim->y3 = newY + ((i + 1) * 2);

        prim = prim->next;
    }
}

void func_us_80176C1C(Entity* self) {
    Primitive* prim;
    s32 i;

    switch (self->step) {
    case 0:
        if (!self->params) {
            D_us_80178680 = self->posX.val;
            D_us_80178684 = self->posY.val;
        } else {
            self->posX.val = D_us_80178680;
            self->posY.val = D_us_80178684;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        switch (self->params) {
        case 0:
            self->posX.i.hi += self->facingLeft ? -0x20 : 0x20;
            break;
        case 1:
            self->posX.i.hi += self->facingLeft ? -0x18 : 0x18;
            self->posY.i.hi += 8;
            break;
        case 2:
            self->posX.i.hi += self->facingLeft ? -0x10 : 0x10;
            self->posY.i.hi += 0x10;
            break;
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 8; i++) {
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            prim->tpage = 0x1A;
            prim->clut = 0x194;

            prim->u0 = prim->u2 = (rand() % 5) * 0x10 + 0x90;
            prim->u1 = prim->u3 = prim->u0 + 0x10;
            prim->v0 = prim->v1 = 0xC0;
            prim->v2 = prim->v3 = 0xD0;
            if (self->facingLeft) {
                prim->x0 = prim->x2 = self->posX.i.hi - i * 8;
                prim->x1 = prim->x3 = self->posX.i.hi - (i + 1) * 8;
            } else {
                prim->x0 = prim->x2 = self->posX.i.hi + i * 8;
                prim->x1 = prim->x3 = self->posX.i.hi + (i + 1) * 8;
            }
            if (i < 7) {
                prim->y0 = prim->y1 = self->posY.i.hi - 6;
                prim->y2 = prim->y3 = self->posY.i.hi + 6;
            } else {
                prim->y0 = prim->y1 = self->posY.i.hi - 4;
                prim->y2 = prim->y3 = self->posY.i.hi + 4;
            }
            // this looks like a mistake but it is needed to get a match on PSP:
            // https://decomp.me/scratch/28GaG
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = 0;
            prim = prim->next;
        }
        g_api.GetServantStats(self, FAM_ABILITY_DEMON_UNK26, 1, &s_DemonStats);
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->hitboxWidth = 0;
        self->hitboxHeight = 4;

        self->step++;
        if (self->params >= 2) {
            self->step++;
        }
        break;
    case 1:
        self->ext.et_801737F0.animationTriggerCount++;
        if (self->ext.et_801737F0.animationTriggerCount > 2) {
            CreateEventEntity(self, DEMON_MODE_UNK_DD, self->params + 1);
            self->step++;
        }
        break;
    case 2:
        self->ext.et_801737F0.animationTriggerCount++;
        if (self->ext.et_801737F0.animationTriggerCount > 16) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    if (self->ext.et_801737F0.animationTimer < 8) {
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < self->ext.et_801737F0.animationTimer; i++) {
            prim = prim->next;
        }

        prim->drawMode &= ~DRAW_HIDE;
        prim->r0 = 0x80;
        self->hitboxOffX += 4;
        self->hitboxWidth += 4;
        self->ext.et_801737F0.animationTimer++;
    }
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 8; i++) {
        prim->r0 -= 8;
        if (prim->r0 < 0x20) {
            prim->drawMode |= DRAW_HIDE;
        } else {
            // this looks like a mistake but it is needed to get a match on PSP:
            // https://decomp.me/scratch/28GaG
            prim->r1 = prim->r2 = prim->r3 = prim->g1 = prim->g2 = prim->g2 =
                prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->r0;
            prim->u0 = prim->u2 = (rand() % 5) * 0x10 + 0x90;
            prim->u1 = prim->u3 = prim->u0 + 0x10;
        }
        prim = prim->next;
    }
}

// PSX: https://decomp.me/scratch/qDGTj
// PSP: https://decomp.me/scratch/D67x7
void func_us_801771B0(Entity* self) {
    Primitive* prim;
    s16 colorValue;
    s32 i;
    // s32 i;
    s32 posX_hi;
    s32 posY_hi;
    s16* uvCoords;

    switch (self->step) {
    case 0:
        if (self->params == 0) {
            D_us_80178688 = self->posX.val;
            D_us_8017868C = self->posY.val;
        } else {
            self->posX.val = D_us_80178688;
            self->posY.val = D_us_8017868C;
        }

        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        HIH(self->velocityX) = (self->facingLeft != 0) ? -0x10 : 0x10;

        switch (self->params) {
        case 2:
            self->posY.i.hi += 8;
        case 1:
            self->posY.i.hi += 8;
        case 0:
            self->posX.i.hi += (self->facingLeft != 0) ? -0x20 : 0x20;
        }

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 3; i++) {
            prim->tpage = 0x1A;
            prim->clut = 0x147;
            prim->priority = self->zPriority + 1;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim->u0 = prim->u2 = 0xB;
            prim->u1 = prim->u3 = 0x35;
            prim->v0 = prim->v1 = 0xCB;
            prim->v2 = prim->v3 = 0xF5;
            PCOL(prim) = 0x80;

            prim = prim->next;
        }

        g_api.GetServantStats(self, 0x1B, 1, &s_DemonStats);

        self->hitboxOffX = -4;
        self->hitboxOffY = 0;
        self->hitboxWidth = 0x1C;
        self->hitboxHeight = 4;

        self->step++;
        if (self->params >= 2) {
            self->step++;
        }
        break;

    case 1:
        self->ext.et_801737F0.animationTriggerCount++;
        self->posX.val += self->velocityX;

        if (self->ext.et_801737F0.animationTriggerCount >= 3) {
            CreateEventEntity(self, DEMON_MODE_UNK_DE, self->params + 1);
            self->step++;
        }
        break;

    case 2:
        self->posX.val += self->velocityX;
        self->ext.et_801737F0.animationTriggerCount++;

        if ((u16)(self->posX.i.hi + 0x20) > 0x140) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    posX_hi = self->posX.i.hi;
    posY_hi = self->posY.i.hi;

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 3; i++) {

        if (self->facingLeft) {
            prim->x0 = posX_hi - D_us_80171B44[i][0];
            prim->y0 = posY_hi - D_us_80171B44[i][1];
            prim->x1 = posX_hi - D_us_80171B44[i][2];
            prim->y1 = posY_hi - D_us_80171B44[i][3];
            prim->x2 = posX_hi - D_us_80171B44[i][4];
            prim->y2 = posY_hi - D_us_80171B44[i][5];
            prim->x3 = posX_hi - D_us_80171B44[i][6];
            prim->y3 = posY_hi - D_us_80171B44[i][7];
        } else {
            prim->x0 = posX_hi + D_us_80171B44[i][0];
            prim->y0 = posY_hi + D_us_80171B44[i][1];
            prim->x1 = posX_hi + D_us_80171B44[i][2];
            prim->y1 = posY_hi + D_us_80171B44[i][3];
            prim->x2 = posX_hi + D_us_80171B44[i][4];
            prim->y2 = posY_hi + D_us_80171B44[i][5];
            prim->x3 = posX_hi + D_us_80171B44[i][6];
            prim->y3 = posY_hi + D_us_80171B44[i][7];
        }

        PCOL(prim) =
            ((self->ext.et_801737F0.animationTriggerCount & 1) * 64) + 0x40;
        prim = prim->next;
    }
}

void func_us_80177690(Entity* self) {
    Entity* entity;

    switch (self->params) {
    case 0:
        D_us_801786D0 = 1;
        entity = SearchForEntityInRange(0, DEMON_EVENT_SFX_PASSTHROUGH);
        if ((entity != NULL) && (entity->step < 5)) {
            entity->step = 8;
        }
        break;
    case 1:
        D_us_801786D0 = 2;
        break;
    case 15:
        D_us_801786D4 = 1;
        break;
    }
    DestroyEntity(self);
}

#ifndef VERSION_PSP
#include "../servant_update_anim.h"
#endif

#include "../../destroy_entity.h"

#ifndef VERSION_PSP
#include "../accumulate_toward_zero.h"
#include "../search_for_entity_in_range.h"
#endif

#include "../calculate_angle_to_entity.h"

#include "../get_target_position_with_distance_buffer.h"

#ifndef VERSION_PSP
#include "../calculate_distance.h"
#include "../play_sfx.h"
#endif

#include "../process_event.h"

#include "../create_event_entity.h"

#include "../is_movement_allowed.h"

#ifndef VERSION_PSP
#include "../check_all_entities_valid.h"
#endif

#include "../servant_unk0.h"
