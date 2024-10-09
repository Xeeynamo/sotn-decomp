// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <sfx.h>
#include <servant.h>
#include "../servant_private.h"

#define ABILITY_STATS_DELAY_FRAMES 0
#define ABILITY_STATS_SPELL_ID 1
#define ABILITY_STATS_BAD_ATTACKS 2

// These variables are only used in UpdateEntityVelocityTowardsTarget
static s16 DeltaX;
STATIC_PAD_BSS(2);
static s16 DeltaY;
STATIC_PAD_BSS(2);
static s16 AngleToTarget;
STATIC_PAD_BSS(2);
static s16 AllowedAngle;
STATIC_PAD_BSS(2);
static s16 DistanceToTarget;
STATIC_PAD_BSS(2);

static u32 D_us_801735C4[128];

static s16 TargetLocationX;
STATIC_PAD_BSS(2);
static s16 TargetLocationY;
STATIC_PAD_BSS(2);

static s32 D_us_801737CC;
STATIC_PAD_BSS(8);
static s32 TargetLocationX_calc;
static s32 TargetLocationY_calc;
static s32 D_us_801737E0;
static s32 D_us_801737E4;
static s32 D_us_801737E8;
static s32 D_us_801737EC;
static Primitive* D_us_801737F0;
static s32 D_us_801737F4;
static s32 D_us_801737F8;
static Primitive*
    D_us_801737FC;        // Pointer to the current primitive being manipulated
static s32 D_us_80173800; // Index for the current primitive being manipulated
static s32 D_us_80173804; // Effect timer used to control steps and timing
static s16 D_us_80173808;
STATIC_PAD_BSS(2); // Temporary storage for X position of the
                   // entity or primitive
static s16 D_us_8017380C;
STATIC_PAD_BSS(2); // Temporary storage for Y position of the
                   // entity or primitive
static FamiliarStats GhostStats;
static s32 g_IsServantDestroyed;
static s32 D_us_80173820;

extern s32 DefaultGhostAnimationFrame[];
extern AnimationFrame* D_us_80170500[];
extern s32 AbilityStats[][3];
extern u16 GhostClut[];

extern s16
    D_us_801705A0[]; // Array of X-axis offsets for positioning primitives
extern s16
    D_us_801705A8[]; // Array of Y-axis offsets for positioning primitives

void unused_20A4(Entity* self);
void unused_20AC(void);
void unused_20B4(void);
void unused_20BC(void);
void unused_20C4(void);
void unused_20CC(void);
void unused_20D4(void);
void unused_20DC(void);
void func_us_801720E4(Entity* self);
void func_us_8017246C(Entity* self);
void unused_28EC(void);
void unused_28F4(void);
void unused_28FC(void);

ServantDesc ghost_ServantDesc = {
    ServantInit,         UpdateServantDefault, unused_20A4,
    unused_20AC,    unused_20B4,     unused_20BC,
    unused_20C4,    unused_20CC,     unused_20D4,
    unused_20DC,    func_us_801720E4,     func_us_8017246C,
    unused_28EC,    unused_28F4,     unused_28FC,
    DestroyServantEntity};

#include "../set_entity_animation.h"

// This gets called from the update function called by the engine
// g_CurrentEntity should be the Familiar entity
// Unsure where the target angle gets set initially
s32 UpdateEntityVelocityTowardsTarget(Entity* unused, s32 targetX, s32 targetY) {
    AngleToTarget = CalculateAngleToEntity(g_CurrentEntity, targetX, targetY);
    AllowedAngle = GetTargetPositionWithDistanceBuffer(
        AngleToTarget, g_CurrentEntity->ext.ghost.TargetAngle,
        g_CurrentEntity->ext.ghost.MaxAngle);
    g_CurrentEntity->ext.ghost.TargetAngle = AllowedAngle;
    // DeltaX
    DeltaX = targetX - g_CurrentEntity->posX.i.hi;
    // DeltaY
    DeltaY = targetY - g_CurrentEntity->posY.i.hi;
    // DistanceToTarget
    DistanceToTarget =
        SquareRoot12(
            ((DeltaX * DeltaX) + (DeltaY * DeltaY))
            << 0xC) >>
        0xC;

    switch (g_CurrentEntity->step) {
    case 2:
        g_CurrentEntity->velocityX = rcos(AllowedAngle) * DistanceToTarget * 2;
        g_CurrentEntity->velocityY = -(rsin(AllowedAngle) * DistanceToTarget * 2);
        break;
    case 3:
        g_CurrentEntity->velocityX = rcos(AllowedAngle) * DistanceToTarget * 8;
        g_CurrentEntity->velocityY = -(rsin(AllowedAngle) * DistanceToTarget * 8);
        break;
    default:
        g_CurrentEntity->velocityX = (rcos(AllowedAngle) * DistanceToTarget) >> 2;
        g_CurrentEntity->velocityY =
            -((rsin(AllowedAngle) * DistanceToTarget) >> 2);
        break;
    }

    // Clamp velocity so it cannot go too low/high
    if (g_CurrentEntity->velocityX > 0 &&
        g_CurrentEntity->velocityX < FIX(0.25)) {
        g_CurrentEntity->velocityX = FIX(0.25);
    } else if (g_CurrentEntity->velocityX < 0 &&
               g_CurrentEntity->velocityX > FIX(-0.25)) {
        g_CurrentEntity->velocityX = FIX(-0.25);
    }

    if (g_CurrentEntity->velocityY > 0 &&
        g_CurrentEntity->velocityY < FIX(0.25)) {
        g_CurrentEntity->velocityY = FIX(0.25);
    } else if (g_CurrentEntity->velocityY < 0 &&
               g_CurrentEntity->velocityY > FIX(-0.25)) {
        g_CurrentEntity->velocityY = FIX(-0.25);
    }

    if (DistanceToTarget > 0x100) {
        g_CurrentEntity->velocityX =
            (targetX - g_CurrentEntity->posX.i.hi) << 0xE;
        g_CurrentEntity->velocityY =
            (targetY - g_CurrentEntity->posY.i.hi) << 0xE;
    }

    // Return the distance between entity and target
    return DistanceToTarget;
}

Entity* func_us_80171284(
    Entity* self) { // Assume self is also an Entity pointer
    Entity* entity;
    s32 i;
    s32 index;
    u32 matches = 0;
#if !defined(VERSION_PSP)
    s32 posDelta;
#endif

    // Hunt through these entities looking for ones that match all criteria.
    // Call them a success and increment successes.
    entity = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < 128; i++, entity++) {
        D_us_801735C4[i] = 0;

        // Very similar code to CheckAllEntitiesValid
        if (!entity->entityId)
            continue;
        if (entity->hitboxState == 0)
            continue;
        if (entity->flags & FLAG_UNK_00200000)
            continue;
        if (entity->posX.i.hi < -16)
            continue;
        if (entity->posX.i.hi > 272)
            continue;
        if (entity->posY.i.hi > 240)
            continue;
        if (entity->posY.i.hi < 0)
            continue;
        // Differs from here
        if (entity->hitboxState & 8 &&
            AbilityStats[GhostStats.level / 10][ABILITY_STATS_BAD_ATTACKS] == 0)
            continue;
#if defined(VERSION_PSP)
        if (abs(self->posX.i.hi - entity->posX.i.hi) >= 49)
            continue;
#else
        posDelta = self->posX.i.hi - entity->posX.i.hi;
        if (ABS(posDelta) >= 49)
            continue;
#endif

#if defined(VERSION_PSP)
        if (abs(self->posY.i.hi - entity->posY.i.hi) >= 49)
            continue;
#else
        posDelta = self->posY.i.hi - entity->posY.i.hi;
        if (ABS(posDelta) >= 49)
            continue;
#endif

        if (!self->facingLeft && self->posX.i.hi < entity->posX.i.hi)
            continue;
        if (self->facingLeft && self->posX.i.hi > entity->posX.i.hi)
            continue;
        if (entity->hitPoints >= 0x7000)
            continue;

        if (entity->flags & FLAG_UNK_80000) {
            matches += 1;
            D_us_801735C4[i] = 1;
        } else {
            entity->flags |= FLAG_UNK_80000;
            return entity;
        }
    }

    if (matches != 0) {
        index = D_us_80173820 % 128;

        for (i = 0; i < 128; i++) {
            if (D_us_801735C4[index] != 0) {
                entity = &g_Entities[index + STAGE_ENTITY_START];
                D_us_80173820 = (index + 1) % 128;
                return entity;
            }

            index = (index + 1) % 128;
        }
    }

    return NULL;
}

#include "../check_entity_valid.h"

void unused_1560(Entity* self) {}

#if defined(VERSION_PSP)
void func_psp_092EA460(Entity* self, s32 entityId, s32 params) {
#else
Entity* func_us_80171568(Entity* self, s32 entityId) {
#endif
    Entity* entity;
    s32 i;

    for (i = 0; i < 3; i++) {
        entity = &g_Entities[i + 5];
        if (!entity->entityId) {
            break;
        }
    }

    if (!entity->entityId) {
        DestroyEntity(entity);
        /* This is interesting.  By changing the entityId of the
         * entity, this effectively changes the update function.
         * The update function that is called is set
         */
#if defined(VERSION_PSP)
        entity->entityId = entityId;
#else
        if (entityId == 0) {
            entity->entityId = 0xDA;
        } else {
            entity->entityId = 0xDB;
        }
#endif
        entity->zPriority = self->zPriority;
        entity->facingLeft = self->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX.val = self->posX.val;
        entity->posY.val = self->posY.val;
        entity->ext.factory.parent = self;
#if defined(VERSION_PSP)
        entity->params = params;
#else
        return entity;
#endif
    }
    // BUG? There is a fall-through case here with no return value on PSX
}

#ifdef VERSION_PC
extern u16 g_ServantClut[48];
extern u16 GhostClut[16];
#endif

void ServantInit(InitializeMode mode) {
    RECT rect;
    u16* dst;
    u16* src;
    s32 i;
    SpriteParts** spriteBanks;
    Entity* e;
    u16 temp;
#ifdef VERSION_PC
    const int lenServantClut = LEN(g_ServantClut);
    const int lenGhostClut = LEN(GhostClut);
#else
    const int lenServantClut = 256;
    const int lenGhostClut = 32;
#endif

    if (mode != MENU_SAME_SERVANT) {
        dst = &g_Clut[CLUT_INDEX_SERVANT];
        src = g_ServantClut;

        for (i = 0; i < lenServantClut; i++) {
            temp = *src++;
            *dst = temp;
            if (i & 0xF) {
                *dst = temp | 0x8000;
            }
            dst++;
        }

        // overwrite part of the clut for this servant
        dst = &g_Clut[CLUT_INDEX_SERVANT_OVERWRITE];
        src = GhostClut;

        for (i = 0; i < lenGhostClut; i++) {
            *dst++ = *src++;
        }

        rect.x = 0;
        rect.w = 0x100;
        rect.h = 1;
        rect.y = 0xF4;

        dst = &g_Clut[CLUT_INDEX_SERVANT];
        LoadImage(&rect, dst);

        spriteBanks = g_api.o.spriteBanks;
        spriteBanks += 20;
        *spriteBanks = (SpriteParts*)D_80170040;

        e = &g_Entities[4];
        DestroyEntity(e);
        e->unk5A = 0x6C;
        e->palette = 0x140;
        e->animSet = ANIMSET_OVL(20);
        e->entityId = ENTITY_ID_SERVANT;
        e->params = 0;
        e->zPriority = PLAYER.zPriority - 2;
        e->facingLeft = (PLAYER.facingLeft + 1) & 1;
        e->posX.val = PLAYER.posX.val;
        e->posY.val = PLAYER.posY.val;

        if (mode == MENU_SWITCH_SERVANT) {
            e->entityId = ENTITY_ID_SERVANT;
            e->posX.val = FIX(128);
            e->posY.val = FIX(-32);
        } else {
            e->entityId = ENTITY_ID_SERVANT;
            if (D_8003C708.flags & STAGE_INVERTEDCASTLE_FLAG) {
                if (ServantUnk0()) {
                    e->posX.val = FIX(192);
                } else {
                    e->posX.val = FIX(64);
                }
                e->posY.val = FIX(160);
            } else {
                e->posX.val =
                    (PLAYER.facingLeft ? FIX(18) : FIX(-18)) + PLAYER.posX.val;
                e->posY.val = PLAYER.posY.val - FIX(32);
            }
        }
        g_api.func_8011A3AC(e, 0, 0, &GhostStats);
        g_IsServantDestroyed = 0;
    }
}

void UpdateServantDefault(Entity* self) {
    s32 temp_s4;
    s32 temp_s3;
    s32 temp_s2;
    s32 temp_s1;

    g_api.func_8011A3AC(self, 0, 0, &GhostStats);
    if (g_IsServantDestroyed) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    self->hitboxWidth = 0;
    self->hitboxHeight = 0;

    // I think if step is < 2, the target the ghost is moving to is Alucard
    if (self->step < 2) {
        // I don't believe this is the correct flag.  This appears to be a flag
        // with the foreground layer, not the stage.
        if (D_8003C708.flags & STAGE_INVERTEDCASTLE_FLAG) {
            switch (ServantUnk0()) {
            case 0:
                TargetLocationX_calc = 0x40;
                break;
            case 1:
                TargetLocationX_calc = 0xC0;
                break;
            case 2:
                if (self->posX.i.hi > 0x80) {
                    temp_s4 = 0xC0;
                } else {
                    temp_s4 = 0x40;
                }
                TargetLocationX_calc = temp_s4;
                break;
            }
            TargetLocationY_calc = 0xA0;
        } else {
            if (PLAYER.facingLeft) {
                TargetLocationX_calc = PLAYER.posX.i.hi + 18;
            } else {
                TargetLocationX_calc = PLAYER.posX.i.hi - 18;
            }
            TargetLocationY_calc = PLAYER.posY.i.hi - 32;
        }
    }
    TargetLocationX = TargetLocationX_calc;
    TargetLocationY = TargetLocationY_calc + (rsin(self->ext.ghost.BobCounterY) >> 0xA);
    self->ext.ghost.BobCounterY += 32;
    self->ext.ghost.BobCounterY &= 0xfff;
    switch (self->step) {
    case 0:
        self->ext.ghost.unk7E = self->params;
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_20000;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_UNK8;
        SetEntityAnimation(self, &DefaultGhostAnimationFrame);
        self->ext.ghost.MaxAngle = 512;
        self->ext.ghost.unk88 = 128;
        self->ext.ghost.unk8A = -1;
        self->step++;
        break;
    case 1:
        if (g_Player.status &
            (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_AXEARMOR)) {
            self->step = 4;
            self->ext.ghost.unk8C = 0;
            break;
        }
        if (D_8003C708.flags & STAGE_INVERTEDCASTLE_FLAG) {
            if (PLAYER.posX.i.hi >= self->posX.i.hi)
                self->facingLeft = 1;
            else
                self->facingLeft = 0;
        } else {
            if (PLAYER.facingLeft == self->facingLeft) {
                if (abs(TargetLocationX - self->posX.i.hi) <= 0) {
                    if (PLAYER.facingLeft)
                        temp_s3 = 0;
                    else
                        temp_s3 = 1;
                    self->facingLeft = temp_s3;
                } else { // 3e0
                    if (self->facingLeft && TargetLocationX < self->posX.i.hi) {
                        if (PLAYER.facingLeft)
                            temp_s2 = 0;
                        else
                            temp_s2 = 1;
                        self->facingLeft = temp_s2;
                    } else if (!self->facingLeft) {
                        if (TargetLocationX > self->posX.i.hi) {
                            if (PLAYER.facingLeft)
                                temp_s1 = 0;
                            else
                                temp_s1 = 1;
                            self->facingLeft = temp_s1;
                        }
                    }
                }
            } else {
                if (self->facingLeft &&
                    self->posX.i.hi - TargetLocationX > 0x1F) {
                    self->facingLeft = PLAYER.facingLeft;
                } else if (!self->facingLeft) {
                    if (TargetLocationX - self->posX.i.hi > 0x1F) {
                        self->facingLeft = PLAYER.facingLeft;
                    }
                }
            }
        }
        UpdateEntityVelocityTowardsTarget(self, TargetLocationX, TargetLocationY);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (!g_CutsceneHasControl) {
            // Note: this is an assignment, not an equality check
            if (self->ext.ghost.unkA2 = func_us_80171284(self)) {
                self->step++;
                break;
            }
        }
        break;
    case 2:
    case 3:
        if (g_Player.status &
            (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_AXEARMOR)) {
            self->step = 4;
            self->ext.ghost.unk8C = 0;
            break;
        }
        if (g_CutsceneHasControl) {
            self->step = 1;
        }
        if (!CheckEntityValid(self->ext.ghost.unkA2)) {
            self->step = 1;
            break;
        }

        TargetLocationX = self->ext.ghost.unkA2->posX.i.hi;
        TargetLocationY = self->ext.ghost.unkA2->posY.i.hi;
        if (self->velocityX > 0) {
            self->facingLeft = 1;
        }
        if (self->velocityX < 0) {
            self->facingLeft = 0;
        }
        D_us_801737CC = UpdateEntityVelocityTowardsTarget(
            self, TargetLocationX, TargetLocationY);
        if (self->step == 2) {
            if (D_us_801737CC < 8) {
                self->ext.ghost.unk86 = 0;
                self->step += 1;
            }
        } else if (D_us_801737CC < 8) {
            self->ext.ghost.unk86++;
            if (self->ext.ghost.unk86 ==
                (AbilityStats[GhostStats.level / 10][ABILITY_STATS_DELAY_FRAMES] - 0x1E)) {
                self->ext.ghost.unk92 = func_us_80171568(self, 0);
            } else if (self->ext.ghost.unk86 >
                       AbilityStats[GhostStats.level / 10][ABILITY_STATS_DELAY_FRAMES]) {
                self->ext.ghost.unk86 = 0;
                g_api.func_8011A3AC(
                    self, AbilityStats[GhostStats.level / 10][ABILITY_STATS_SPELL_ID], 1,
                    &GhostStats);
                self->hitboxWidth = 8;
                self->hitboxHeight = 8;
            }
        } else {
            self->ext.ghost.unk86 = 0;
            if (self->ext.ghost.unk92->entityId == 0xDA) {
                self->ext.ghost.unk92->params = 1;
                ghost_ServantDesc.Unk28(self->ext.ghost.unk92);
            }
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        break;
    case 4:
        if (!(g_Player.status &
              (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_AXEARMOR))) {
            if (self->ext.ghost.unk96->entityId == 0xDB) {
                self->ext.ghost.unk96->params = 1;
                ghost_ServantDesc.Unk2C(self->ext.ghost.unk96);
            }
            self->step = 1;
            break;
        }
        UpdateEntityVelocityTowardsTarget(self, TargetLocationX, TargetLocationY);
        self->posY.val += self->velocityY;
        switch (self->ext.ghost.unk8C) {
        case 0:
            self->ext.ghost.unk86 = 0;
            self->ext.ghost.unk8C++;
            break;
        case 1:
            self->ext.ghost.unk86++;
            if (self->ext.ghost.unk86 > 0x3C) {
                self->ext.ghost.unk86 = 0;
                self->ext.ghost.unk8C++;
            }
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            self->ext.ghost.unk86++;
            if (self->ext.ghost.unk86 == 1) {
                self->facingLeft = self->facingLeft ? 0 : 1;
            } else if (self->ext.ghost.unk86 > 15) {
                self->ext.ghost.unk86 = 0;
                self->ext.ghost.unk8C++;
            }
            break;
        case 6:
            self->ext.ghost.unk86++;
            if (self->ext.ghost.unk86 > 0x3C) {
                self->ext.ghost.unk86 = 0;
                self->ext.ghost.unk8C++;
            }
            break;
        case 7:
            self->ext.ghost.unk86++;
            if (self->ext.ghost.unk86 == 1) {
                self->ext.ghost.unk96 = func_us_80171568(self, 1);
            } else if (self->ext.ghost.unk86 > 0x3C) {
                self->ext.ghost.unk86 = 0;
                self->step++;
            }
            break;
        }
        break;
    case 5:
        if (!(g_Player.status &
              (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_AXEARMOR))) {
            self->step = 1;

        } else {
            if (self->velocityY > FIX(-1.5)) {
                self->velocityY -= FIX(0.25);
            }
            self->posY.val += self->velocityY;
            if (self->posY.i.hi < -0x10) {
                self->velocityY = 0;
                self->posX.val = FIX(128.0);
                self->posY.val = FIX(-16.0);
                self->step++;
            }
        }
        break;
    case 6:
        if (!(g_Player.status &
              (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_AXEARMOR))) {
            self->step = 1;
        } else {
            self->posX.val = FIX(128.0);
            self->posY.val = FIX(-16.0);
        }
        break;
    }
    self->ext.ghost.unk88 += self->ext.ghost.unk8A;
    if (!(self->ext.ghost.unk88 > 0x20 &&
          self->ext.ghost.unk88 < 0x5F + 0x21)) {
        self->ext.ghost.unk8A *= -1;
    }
    self->unk6C = self->ext.ghost.unk88;
    ProcessEvent(self, 0);
    unused_1560(self);
    g_api.UpdateAnim(NULL, D_us_80170500);
}

void unused_20A4(Entity* self) {}

void unused_20AC(void) {}

void unused_20B4(void) {}

void unused_20BC(void) {}

void unused_20C4(void) {}

void unused_20CC(void) {}

void unused_20D4(void) {}

void unused_20DC(void) {}

void func_us_801720E4(Entity* self) {

    if (self->params != 0) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_20000;

        D_us_801737F0 = &g_PrimBuf[self->primIndex];

        for (D_us_801737E0 = 0; D_us_801737E0 < 8; D_us_801737E0++) {
            D_us_801737F0->tpage = 0x1A;
            D_us_801737F0->clut = 0x143;

            D_us_801737F0->u0 = D_us_801737F0->u2 = 0x78;
            D_us_801737F0->u1 = D_us_801737F0->u3 = 0x80;

            D_us_801737F0->v0 = D_us_801737F0->v1 = 0x30;
            D_us_801737F0->v2 = D_us_801737F0->v3 = 0x38;

            D_us_801737F0->r0 = D_us_801737F0->r1 = D_us_801737F0->r2 =
                D_us_801737F0->r3 = D_us_801737F0->g0 = D_us_801737F0->g1 =
                    D_us_801737F0->g2 = D_us_801737F0->g3 = D_us_801737F0->b0 =
                        D_us_801737F0->b1 = D_us_801737F0->b2 =
                            D_us_801737F0->b3 = 0x80;

            D_us_801737F0->priority = self->zPriority + 1;
            D_us_801737F0->drawMode = DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                                      DRAW_COLORS | DRAW_TRANSP;

            D_us_801737F0 = D_us_801737F0->next;
        }

        D_us_801737F4 = 0x1E;
        D_us_801737F8 = 0;
        g_api.PlaySfx(SFX_GLASS_SHARDS);
        self->step++;

    case 1:
        D_us_801737F8 = (D_us_801737F8 + 0x32) & 0xFFF;
        D_us_801737F4--;
        if (D_us_801737F4 < 0) {
            DestroyEntity(self);
            return;
        }
    }
    self->posX.i.hi = self->ext.ghostEvent.parent->posX.i.hi;
    self->posY.i.hi = self->ext.ghostEvent.parent->posY.i.hi;

    D_us_801737E4 = D_us_801737F8;
    D_us_801737F0 = &g_PrimBuf[self->primIndex];

    for (D_us_801737E0 = 0; D_us_801737E0 < 8; D_us_801737E0++) {
        D_us_801737E8 =
            self->posX.i.hi +
            ((rcos(D_us_801737E4 + (D_us_801737E0 << 9)) * D_us_801737F4) >>
             12);
        D_us_801737EC =
            self->posY.i.hi -
            ((rsin(D_us_801737E4 + (D_us_801737E0 << 9)) * D_us_801737F4) >>
             12);
        D_us_801737F0->x0 = D_us_801737F0->x2 = D_us_801737E8 - 4;
        D_us_801737F0->x1 = D_us_801737F0->x3 = D_us_801737E8 + 4;
        D_us_801737F0->y0 = D_us_801737F0->y1 = D_us_801737EC - 4;
        D_us_801737F0->y2 = D_us_801737F0->y3 = D_us_801737EC + 4;
        D_us_801737F0 = D_us_801737F0->next;
    }
}

void func_us_8017246C(Entity* self) {
    u16 temp;
    if (self->params) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_UNK_20000;

        D_us_801737FC = &g_PrimBuf[self->primIndex];
        for (D_us_80173800 = 0; D_us_80173800 < 3; D_us_80173800++) {
            D_us_801737FC->clut = 0x143;
            D_us_801737FC->tpage = 0x1E;
            D_us_801737FC->u0 = D_us_801737FC->u2 = 0x78;
            D_us_801737FC->v0 = D_us_801737FC->v1 = 8;
            D_us_801737FC->u1 = D_us_801737FC->u3 = 0x80;
            D_us_801737FC->v2 = D_us_801737FC->v3 = 0x10;
            D_us_801737FC->priority = self->zPriority + 1;
            D_us_801737FC->drawMode = DRAW_UNK_100 | DRAW_UNK02;
            if (D_us_80173800) {
                D_us_801737FC->drawMode |= DRAW_HIDE;
            }
            D_us_801737FC = D_us_801737FC->next;
        }
        D_us_80173804 = 0;
        self->step++;
        break;
    case 1:
        D_us_80173804++;
        if (D_us_80173804 > 0xA) {
            D_us_801737FC = &g_PrimBuf[self->primIndex];
            D_us_801737FC = D_us_801737FC->next;
            D_us_801737FC->drawMode &= ~DRAW_HIDE;
            D_us_80173804 = 0;
            self->step++;
        }
        break;
    case 2:
        D_us_80173804++;
        if (D_us_80173804 > 0xA) {
            D_us_801737FC = &g_PrimBuf[self->primIndex];
            D_us_801737FC = D_us_801737FC->next;
            D_us_801737FC = D_us_801737FC->next;
            D_us_801737FC->drawMode &= ~DRAW_HIDE;
            D_us_80173804 = 0;
            self->step++;
        }
        break;
    case 3:
        D_us_80173804++;
        if (D_us_80173804 > 0x28) {
            DestroyEntity(self);
            return;
        }
    }
    D_us_80173808 = self->posX.i.hi = self->ext.factory.parent->posX.i.hi;
    D_us_8017380C = self->posY.i.hi = self->ext.factory.parent->posY.i.hi;

    D_us_801737FC = &g_PrimBuf[self->primIndex];

    for (D_us_80173800 = 0; D_us_80173800 < 3; D_us_80173800++) {
        if (!self->facingLeft) {

            D_us_801737FC->x0 = D_us_801737FC->x2 =
                D_us_80173808 + D_us_801705A0[D_us_80173800];
            D_us_801737FC->x1 = D_us_801737FC->x3 =
                D_us_80173808 + (D_us_801705A0[D_us_80173800] + 8);
        } else {
            D_us_801737FC->x0 = D_us_801737FC->x2 =
                D_us_80173808 - (D_us_801705A0[D_us_80173800] + 8);
            D_us_801737FC->x1 = D_us_801737FC->x3 =
                D_us_80173808 - D_us_801705A0[D_us_80173800];
        }
        D_us_801737FC->y0 = D_us_801737FC->y1 =
            D_us_8017380C + D_us_801705A8[D_us_80173800];
        D_us_801737FC->y2 = D_us_801737FC->y3 =
            D_us_8017380C + (D_us_801705A8[D_us_80173800] + 8);
        D_us_801737FC = D_us_801737FC->next;
    }
    return;
}

void unused_28EC(void) {}

void unused_28F4(void) {}

void unused_28FC(void) {}

#include "../destroy_servant_entity.h"

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
