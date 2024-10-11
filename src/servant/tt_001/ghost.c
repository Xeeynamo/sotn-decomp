// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <sfx.h>
#include <servant.h>
#include "../servant_private.h"

#define ABILITY_STATS_DELAY_FRAMES 0
#define ABILITY_STATS_SPELL_ID 1
#define ABILITY_STATS_BAD_ATTACKS 2

#define ENTITY_ID_ATTACK_CLOUD 0xDA
#define ENTITY_ID_CONFUSION 0xDB

typedef enum { ATTACK_CLOUD, CONFUSION } ChildEntityType;

// These variables are only used in UpdateEntityVelocityTowardsTarget
static s16 s_DeltaX;
STATIC_PAD_BSS(2);
static s16 s_DeltaY;
STATIC_PAD_BSS(2);
static s16 s_AngleToTarget;
STATIC_PAD_BSS(2);
static s16 s_AllowedAngle;
STATIC_PAD_BSS(2);
static s16 s_DistanceToTarget;
STATIC_PAD_BSS(2);

static u32 s_TargetMatch[128];

static s16 s_TargetLocationX;
STATIC_PAD_BSS(2);
static s16 s_TargetLocationY;
STATIC_PAD_BSS(2);

static s32 s_DistanceToTarget2;
STATIC_PAD_BSS(8);
static s32 s_TargetLocationX_calc;
static s32 s_TargetLocationY_calc;
static s32 s_AttackPrimIndex;
static s32 s_AttackPosOscillator;
static s32 D_us_801737E8;
static s32 D_us_801737EC;
static Primitive* s_CurrentAttackPrim;
static s32 s_AttackCloudTimer;
static s32 s_AttackPosOscillator_calc;
static Primitive*
    s_CurrentConfusedPrim; // Pointer to the current primitive being manipulated
static s32
    s_ConfusedPrimIndex; // Index for the current primitive being manipulated
static s32
    s_ConfusedFrameCounter; // Effect timer used to control steps and timing
static s16 s_ParentX;
STATIC_PAD_BSS(2); // Temporary storage for X position of the
                   // entity or primitive
static s16 s_ParentY;
STATIC_PAD_BSS(2); // Temporary storage for Y position of the
                   // entity or primitive
static FamiliarStats s_GhostStats;
static s32 s_IsServantDestroyed;
static s32 s_LastTargetedEntityIndex;

extern s32 g_DefaultGhostAnimationFrame[];
extern AnimationFrame* g_GhostAnimationFrames[];
extern s32 g_GhostAbilityStats[][3];
extern u16 g_GhostClut[];

extern s16
    g_ConfusedOffsetsX[]; // Array of X-axis offsets for positioning primitives
extern s16
    g_ConfusedOffsetsY[]; // Array of Y-axis offsets for positioning primitives

static void unused_20A4(Entity* self);
static void unused_20AC(void);
static void unused_20B4(void);
static void unused_20BC(void);
static void unused_20C4(void);
static void unused_20CC(void);
static void unused_20D4(void);
static void unused_20DC(void);
static void UpdateAttackEntites(Entity* self);
static void UpdateConfusedEntites(Entity* self);
static void unused_28EC(void);
static void unused_28F4(void);
static void unused_28FC(void);

ServantDesc ghost_ServantDesc = {
    ServantInit,         UpdateServantDefault, unused_20A4,
    unused_20AC,         unused_20B4,          unused_20BC,
    unused_20C4,         unused_20CC,          unused_20D4,
    unused_20DC,         UpdateAttackEntites,  UpdateConfusedEntites,
    unused_28EC,         unused_28F4,          unused_28FC,
    DestroyServantEntity};

#include "../set_entity_animation.h"

// This gets called from the update function called by the engine
// g_CurrentEntity should be the Familiar entity
// Unsure where the target angle gets set initially
s32 UpdateEntityVelocityTowardsTarget(
    Entity* unused, s32 targetX, s32 targetY) {
    s_AngleToTarget = CalculateAngleToEntity(g_CurrentEntity, targetX, targetY);
    s_AllowedAngle = GetTargetPositionWithDistanceBuffer(
        s_AngleToTarget, g_CurrentEntity->ext.ghost.targetAngle,
        g_CurrentEntity->ext.ghost.maxAngle);
    g_CurrentEntity->ext.ghost.targetAngle = s_AllowedAngle;

    s_DeltaX = targetX - g_CurrentEntity->posX.i.hi;
    s_DeltaY = targetY - g_CurrentEntity->posY.i.hi;
    s_DistanceToTarget =
        SquareRoot12(((s_DeltaX * s_DeltaX) + (s_DeltaY * s_DeltaY)) << 0xC) >>
        0xC;

    switch (g_CurrentEntity->step) {
    case 2:
        g_CurrentEntity->velocityX =
            rcos(s_AllowedAngle) * s_DistanceToTarget * 2;
        g_CurrentEntity->velocityY =
            -(rsin(s_AllowedAngle) * s_DistanceToTarget * 2);
        break;
    case 3:
        g_CurrentEntity->velocityX =
            rcos(s_AllowedAngle) * s_DistanceToTarget * 8;
        g_CurrentEntity->velocityY =
            -(rsin(s_AllowedAngle) * s_DistanceToTarget * 8);
        break;
    default:
        g_CurrentEntity->velocityX =
            (rcos(s_AllowedAngle) * s_DistanceToTarget) >> 2;
        g_CurrentEntity->velocityY =
            -((rsin(s_AllowedAngle) * s_DistanceToTarget) >> 2);
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

    if (s_DistanceToTarget > 0x100) {
        g_CurrentEntity->velocityX =
            (targetX - g_CurrentEntity->posX.i.hi) << 0xE;
        g_CurrentEntity->velocityY =
            (targetY - g_CurrentEntity->posY.i.hi) << 0xE;
    }

    // Return the distance between entity and target
    return s_DistanceToTarget;
}

static Entity* FindValidTarget(
    Entity* self) { // Assume self is also an Entity pointer
    const int EntitySearchCount = 128;
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
    for (i = 0; i < EntitySearchCount; i++, entity++) {
        s_TargetMatch[i] = 0;

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
            g_GhostAbilityStats[s_GhostStats.level / 10]
                               [ABILITY_STATS_BAD_ATTACKS] == 0)
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
            s_TargetMatch[i] = 1;
        } else {
            entity->flags |= FLAG_UNK_80000;
            return entity;
        }
    }

    if (matches != 0) {
        index = s_LastTargetedEntityIndex % EntitySearchCount;

        for (i = 0; i < EntitySearchCount; i++) {
            if (s_TargetMatch[index] != 0) {
                entity = &g_Entities[index + STAGE_ENTITY_START];
                s_LastTargetedEntityIndex = (index + 1) % EntitySearchCount;
                return entity;
            }

            index = (index + 1) % EntitySearchCount;
        }
    }

    return NULL;
}

#include "../check_entity_valid.h"

static void unused_1560(Entity* self) {}

#if defined(VERSION_PSP)
void func_psp_092EA460(Entity* parent, s32 entityType, s32 params) {
#else
Entity* CreateChildEntity(Entity* parent, ChildEntityType entityType) {
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
        if (entityType == ATTACK_CLOUD) {
            entity->entityId = ENTITY_ID_ATTACK_CLOUD;
        } else {
            entity->entityId = ENTITY_ID_CONFUSION;
        }
#endif
        entity->zPriority = parent->zPriority;
        entity->facingLeft = parent->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX.val = parent->posX.val;
        entity->posY.val = parent->posY.val;
        entity->ext.ghostEvent.parent = parent;
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
extern u16 g_GhostClut[16];
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
    const int leng_GhostClut = LEN(g_GhostClut);
#else
    const int lenServantClut = 256;
    const int leng_GhostClut = 32;
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
        src = g_GhostClut;

        for (i = 0; i < leng_GhostClut; i++) {
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
        *spriteBanks = (SpriteParts*)g_ServantSpriteParts;

        e = &g_Entities[SERVANT_ENTITY_INDEX];
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
            if (D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_20) {
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
        g_api.func_8011A3AC(e, 0, 0, &s_GhostStats);
        s_IsServantDestroyed = 0;
    }
}

void UpdateServantDefault(Entity* self) {
    s32 temp_s4;
    s32 temp_s3;
    s32 temp_s2;
    s32 temp_s1;

    g_api.func_8011A3AC(self, 0, 0, &s_GhostStats);
    if (s_IsServantDestroyed) {
        self->zPriority = PLAYER.zPriority - 2;
    }
    self->hitboxWidth = 0;
    self->hitboxHeight = 0;

    // I think if step is < 2, the target the ghost is moving to is Alucard
    if (self->step < 2) {
        // these flags are set in the SetRoomForegroundLayer and is set to
        // layerDef->rect.params
        if (D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_20) {
            switch (ServantUnk0()) {
            case 0:
                s_TargetLocationX_calc = 0x40;
                break;
            case 1:
                s_TargetLocationX_calc = 0xC0;
                break;
            case 2:
                if (self->posX.i.hi > 0x80) {
                    temp_s4 = 0xC0;
                } else {
                    temp_s4 = 0x40;
                }
                s_TargetLocationX_calc = temp_s4;
                break;
            }
            s_TargetLocationY_calc = 0xA0;
        } else {
            if (PLAYER.facingLeft) {
                s_TargetLocationX_calc = PLAYER.posX.i.hi + 18;
            } else {
                s_TargetLocationX_calc = PLAYER.posX.i.hi - 18;
            }
            s_TargetLocationY_calc = PLAYER.posY.i.hi - 32;
        }
    }
    s_TargetLocationX = s_TargetLocationX_calc;
    s_TargetLocationY =
        s_TargetLocationY_calc + (rsin(self->ext.ghost.bobCounterY) >> 0xA);
    self->ext.ghost.bobCounterY += 32;
    self->ext.ghost.bobCounterY &= 0xfff;
    switch (self->step) {
    case 0:
        self->ext.ghost.unk7E = self->params;
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_20000;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_UNK8;
        SetEntityAnimation(self, &g_DefaultGhostAnimationFrame);
        self->ext.ghost.maxAngle = 512;
        self->ext.ghost.opacity = 128;
        self->ext.ghost.opacityAdjustmentAmount = -1;
        self->step++;
        break;
    case 1:
        if (g_Player.status &
            (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_AXEARMOR)) {
            self->step = 4;
            self->ext.ghost.confusedSubStep = 0;
            break;
        }
        if (D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_20) {
            if (PLAYER.posX.i.hi >= self->posX.i.hi)
                self->facingLeft = 1;
            else
                self->facingLeft = 0;
        } else {
            if (PLAYER.facingLeft == self->facingLeft) {
                if (abs(s_TargetLocationX - self->posX.i.hi) <= 0) {
                    if (PLAYER.facingLeft)
                        temp_s3 = 0;
                    else
                        temp_s3 = 1;
                    self->facingLeft = temp_s3;
                } else { // 3e0
                    if (self->facingLeft &&
                        s_TargetLocationX < self->posX.i.hi) {
                        if (PLAYER.facingLeft)
                            temp_s2 = 0;
                        else
                            temp_s2 = 1;
                        self->facingLeft = temp_s2;
                    } else if (!self->facingLeft) {
                        if (s_TargetLocationX > self->posX.i.hi) {
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
                    self->posX.i.hi - s_TargetLocationX > 0x1F) {
                    self->facingLeft = PLAYER.facingLeft;
                } else if (!self->facingLeft) {
                    if (s_TargetLocationX - self->posX.i.hi > 0x1F) {
                        self->facingLeft = PLAYER.facingLeft;
                    }
                }
            }
        }
        UpdateEntityVelocityTowardsTarget(
            self, s_TargetLocationX, s_TargetLocationY);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (!g_CutsceneHasControl) {
            // Note: this is an assignment, not an equality check
            if (self->ext.ghost.attackTarget = FindValidTarget(self)) {
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
            self->ext.ghost.confusedSubStep = 0;
            break;
        }
        if (g_CutsceneHasControl) {
            self->step = 1;
        }
        if (!CheckEntityValid(self->ext.ghost.attackTarget)) {
            self->step = 1;
            break;
        }

        s_TargetLocationX = self->ext.ghost.attackTarget->posX.i.hi;
        s_TargetLocationY = self->ext.ghost.attackTarget->posY.i.hi;
        if (self->velocityX > 0) {
            self->facingLeft = 1;
        }
        if (self->velocityX < 0) {
            self->facingLeft = 0;
        }
        s_DistanceToTarget2 = UpdateEntityVelocityTowardsTarget(
            self, s_TargetLocationX, s_TargetLocationY);
        if (self->step == 2) {
            if (s_DistanceToTarget2 < 8) {
                self->ext.ghost.frameCounter = 0;
                self->step += 1;
            }
        } else if (s_DistanceToTarget2 < 8) {
            self->ext.ghost.frameCounter++;
            if (self->ext.ghost.frameCounter ==
                (g_GhostAbilityStats[s_GhostStats.level / 10]
                                    [ABILITY_STATS_DELAY_FRAMES] -
                 30)) {
                self->ext.ghost.attackEntity = CreateChildEntity(self, 0);
            } else if (self->ext.ghost.frameCounter >
                       g_GhostAbilityStats[s_GhostStats.level / 10]
                                          [ABILITY_STATS_DELAY_FRAMES]) {
                self->ext.ghost.frameCounter = 0;
                g_api.func_8011A3AC(self,
                                    g_GhostAbilityStats[s_GhostStats.level / 10]
                                                       [ABILITY_STATS_SPELL_ID],
                                    1, &s_GhostStats);
                self->hitboxWidth = 8;
                self->hitboxHeight = 8;
            }
        } else {
            self->ext.ghost.frameCounter = 0;
            if (self->ext.ghost.attackEntity->entityId ==
                ENTITY_ID_ATTACK_CLOUD) {
                self->ext.ghost.attackEntity->params = 1;
                // this is calling UpdateAttackEntites
                ghost_ServantDesc.Unk28(self->ext.ghost.attackEntity);
            }
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        break;
    case 4:
        if (!(g_Player.status &
              (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_AXEARMOR))) {
            if (self->ext.ghost.confusedEntity->entityId ==
                ENTITY_ID_CONFUSION) {
                self->ext.ghost.confusedEntity->params = 1;
                // this is calling UpdateConfusedEntites
                ghost_ServantDesc.Unk2C(self->ext.ghost.confusedEntity);
            }
            self->step = 1;
            break;
        }
        UpdateEntityVelocityTowardsTarget(
            self, s_TargetLocationX, s_TargetLocationY);
        self->posY.val += self->velocityY;
        switch (self->ext.ghost.confusedSubStep) {
        case 0:
            self->ext.ghost.frameCounter = 0;
            self->ext.ghost.confusedSubStep++;
            break;
        case 1:
            self->ext.ghost.frameCounter++;
            if (self->ext.ghost.frameCounter > 0x3C) {
                self->ext.ghost.frameCounter = 0;
                self->ext.ghost.confusedSubStep++;
            }
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            self->ext.ghost.frameCounter++;
            if (self->ext.ghost.frameCounter == 1) {
                self->facingLeft = self->facingLeft ? 0 : 1;
            } else if (self->ext.ghost.frameCounter > 15) {
                self->ext.ghost.frameCounter = 0;
                self->ext.ghost.confusedSubStep++;
            }
            break;
        case 6:
            self->ext.ghost.frameCounter++;
            if (self->ext.ghost.frameCounter > 60) {
                self->ext.ghost.frameCounter = 0;
                self->ext.ghost.confusedSubStep++;
            }
            break;
        case 7:
            self->ext.ghost.frameCounter++;
            if (self->ext.ghost.frameCounter == 1) {
                self->ext.ghost.confusedEntity = CreateChildEntity(self, 1);
            } else if (self->ext.ghost.frameCounter > 60) {
                self->ext.ghost.frameCounter = 0;
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

    // controls the pulsing fade
    self->ext.ghost.opacity += self->ext.ghost.opacityAdjustmentAmount;
    if (!(self->ext.ghost.opacity > 0x20 &&
          self->ext.ghost.opacity < 0x5F + 0x21)) {
        self->ext.ghost.opacityAdjustmentAmount *= -1;
    }

    // unk6C is used in conjunction with self->drawFlags = FLAG_DRAW_UNK8 to set
    // the alpha/saturation.  When it's zero, it's invisible, when it's 255,
    // it's at the opacity of the sprite itself and is "bright".
    self->unk6C = self->ext.ghost.opacity;
    ProcessEvent(self, 0);
    unused_1560(self);
    g_api.UpdateAnim(NULL, g_GhostAnimationFrames);
}

void unused_20A4(Entity* self) {}

void unused_20AC(void) {}

void unused_20B4(void) {}

void unused_20BC(void) {}

void unused_20C4(void) {}

void unused_20CC(void) {}

void unused_20D4(void) {}

void unused_20DC(void) {}

// This creates and handles the updates for the attack cloud
void UpdateAttackEntites(Entity* self) {

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

        s_CurrentAttackPrim = &g_PrimBuf[self->primIndex];

        for (s_AttackPrimIndex = 0; s_AttackPrimIndex < 8;
             s_AttackPrimIndex++) {
            s_CurrentAttackPrim->tpage = 0x1A;
            s_CurrentAttackPrim->clut = 0x143;

            s_CurrentAttackPrim->u0 = s_CurrentAttackPrim->u2 = 0x78;
            s_CurrentAttackPrim->u1 = s_CurrentAttackPrim->u3 = 0x80;

            s_CurrentAttackPrim->v0 = s_CurrentAttackPrim->v1 = 0x30;
            s_CurrentAttackPrim->v2 = s_CurrentAttackPrim->v3 = 0x38;

            s_CurrentAttackPrim->r0 = s_CurrentAttackPrim->r1 =
                s_CurrentAttackPrim->r2 = s_CurrentAttackPrim->r3 =
                    s_CurrentAttackPrim->g0 = s_CurrentAttackPrim->g1 =
                        s_CurrentAttackPrim->g2 = s_CurrentAttackPrim->g3 =
                            s_CurrentAttackPrim->b0 = s_CurrentAttackPrim->b1 =
                                s_CurrentAttackPrim->b2 =
                                    s_CurrentAttackPrim->b3 = 0x80;

            s_CurrentAttackPrim->priority = self->zPriority + 1;
            s_CurrentAttackPrim->drawMode =
                DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                DRAW_TRANSP;

            s_CurrentAttackPrim = s_CurrentAttackPrim->next;
        }

        s_AttackCloudTimer = 30;
        s_AttackPosOscillator_calc = 0;
        g_api.PlaySfx(SFX_GLASS_SHARDS);
        self->step++;

    case 1:
        s_AttackPosOscillator_calc = (s_AttackPosOscillator_calc + 50) & 0xFFF;
        s_AttackCloudTimer--;
        if (s_AttackCloudTimer < 0) {
            DestroyEntity(self);
            return;
        }
    }
    self->posX.i.hi = self->ext.ghostEvent.parent->posX.i.hi;
    self->posY.i.hi = self->ext.ghostEvent.parent->posY.i.hi;

    s_AttackPosOscillator = s_AttackPosOscillator_calc;
    s_CurrentAttackPrim = &g_PrimBuf[self->primIndex];

    for (s_AttackPrimIndex = 0; s_AttackPrimIndex < 8; s_AttackPrimIndex++) {
        D_us_801737E8 =
            self->posX.i.hi +
            ((rcos(s_AttackPosOscillator + (s_AttackPrimIndex << 9)) *
              s_AttackCloudTimer) >>
             12);
        D_us_801737EC =
            self->posY.i.hi -
            ((rsin(s_AttackPosOscillator + (s_AttackPrimIndex << 9)) *
              s_AttackCloudTimer) >>
             12);
        s_CurrentAttackPrim->x0 = s_CurrentAttackPrim->x2 = D_us_801737E8 - 4;
        s_CurrentAttackPrim->x1 = s_CurrentAttackPrim->x3 = D_us_801737E8 + 4;
        s_CurrentAttackPrim->y0 = s_CurrentAttackPrim->y1 = D_us_801737EC - 4;
        s_CurrentAttackPrim->y2 = s_CurrentAttackPrim->y3 = D_us_801737EC + 4;
        s_CurrentAttackPrim = s_CurrentAttackPrim->next;
    }
}

// This creates and handles the updates for the question marks
// that appear above Ghost when you turn into a bat while
// Ghost is summoned.
void UpdateConfusedEntites(Entity* self) {
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

        s_CurrentConfusedPrim = &g_PrimBuf[self->primIndex];
        for (s_ConfusedPrimIndex = 0; s_ConfusedPrimIndex < 3;
             s_ConfusedPrimIndex++) {
            s_CurrentConfusedPrim->clut = 0x143;
            s_CurrentConfusedPrim->tpage = 0x1E;
            s_CurrentConfusedPrim->u0 = s_CurrentConfusedPrim->u2 = 0x78;
            s_CurrentConfusedPrim->v0 = s_CurrentConfusedPrim->v1 = 8;
            s_CurrentConfusedPrim->u1 = s_CurrentConfusedPrim->u3 = 0x80;
            s_CurrentConfusedPrim->v2 = s_CurrentConfusedPrim->v3 = 0x10;
            s_CurrentConfusedPrim->priority = self->zPriority + 1;
            s_CurrentConfusedPrim->drawMode = DRAW_UNK_100 | DRAW_UNK02;
            if (s_ConfusedPrimIndex) { // Hide the 2nd and 3rd question mark
                s_CurrentConfusedPrim->drawMode |= DRAW_HIDE;
            }
            s_CurrentConfusedPrim = s_CurrentConfusedPrim->next;
        }
        s_ConfusedFrameCounter = 0;
        self->step++;
        break;
    case 1: // after 10 frames, unhide a question mark
        s_ConfusedFrameCounter++;
        if (s_ConfusedFrameCounter > 10) {
            s_CurrentConfusedPrim = &g_PrimBuf[self->primIndex];
            s_CurrentConfusedPrim = s_CurrentConfusedPrim->next;
            s_CurrentConfusedPrim->drawMode &= ~DRAW_HIDE;
            s_ConfusedFrameCounter = 0;
            self->step++;
        }
        break;
    case 2: // after 10 frames, unhide another question mark
        s_ConfusedFrameCounter++;
        if (s_ConfusedFrameCounter > 10) {
            s_CurrentConfusedPrim = &g_PrimBuf[self->primIndex];
            s_CurrentConfusedPrim = s_CurrentConfusedPrim->next;
            s_CurrentConfusedPrim = s_CurrentConfusedPrim->next;
            s_CurrentConfusedPrim->drawMode &= ~DRAW_HIDE;
            s_ConfusedFrameCounter = 0;
            self->step++;
        }
        break;
    case 3: // after 40 more frames (60 total), destroy entity
        s_ConfusedFrameCounter++;
        if (s_ConfusedFrameCounter > 40) {
            DestroyEntity(self);
            return;
        }
    }
    s_ParentX = self->posX.i.hi = self->ext.ghostEvent.parent->posX.i.hi;
    s_ParentY = self->posY.i.hi = self->ext.ghostEvent.parent->posY.i.hi;

    s_CurrentConfusedPrim = &g_PrimBuf[self->primIndex];

    for (s_ConfusedPrimIndex = 0; s_ConfusedPrimIndex < 3;
         s_ConfusedPrimIndex++) {
        if (!self->facingLeft) {

            s_CurrentConfusedPrim->x0 = s_CurrentConfusedPrim->x2 =
                s_ParentX + g_ConfusedOffsetsX[s_ConfusedPrimIndex];
            s_CurrentConfusedPrim->x1 = s_CurrentConfusedPrim->x3 =
                s_ParentX + (g_ConfusedOffsetsX[s_ConfusedPrimIndex] + 8);
        } else {
            s_CurrentConfusedPrim->x0 = s_CurrentConfusedPrim->x2 =
                s_ParentX - (g_ConfusedOffsetsX[s_ConfusedPrimIndex] + 8);
            s_CurrentConfusedPrim->x1 = s_CurrentConfusedPrim->x3 =
                s_ParentX - g_ConfusedOffsetsX[s_ConfusedPrimIndex];
        }
        s_CurrentConfusedPrim->y0 = s_CurrentConfusedPrim->y1 =
            s_ParentY + g_ConfusedOffsetsY[s_ConfusedPrimIndex];
        s_CurrentConfusedPrim->y2 = s_CurrentConfusedPrim->y3 =
            s_ParentY + (g_ConfusedOffsetsY[s_ConfusedPrimIndex] + 8);
        s_CurrentConfusedPrim = s_CurrentConfusedPrim->next;
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
