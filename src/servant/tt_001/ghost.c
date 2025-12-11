// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ghost.h"
#include "../servant_private.h"
#include <sfx.h>

#define ENTITY_ID_ATTACK_CLOUD SERVANT_ID(10)
#define ENTITY_ID_CONFUSION SERVANT_ID(11)

static FamiliarStats s_GhostStats;
static s32 s_IsServantDestroyed;
static s32 s_LastTargetedEntityIndex;

extern ServantDesc ghost_ServantDesc;

static AnimationFrame g_DefaultGhostAnimationFrame[] = {
    {2, 0x201}, {2, 0x202}, {2, 0x203}, {2, 0x204}, {2, 0x205},
    {2, 0x206}, {2, 0x207}, {2, 0x208}, {0, 0x000}};

static AnimationFrame D_us_801704CC[] = {
    {2, 0x209}, {2, 0x20A}, {2, 0x20B}, {2, 0x20C}, {2, 0x20D},
    {2, 0x20E}, {2, 0x20F}, {2, 0x210}, {2, 0x211}, {2, 0x212},
    {2, 0x213}, {2, 0x214}, {0, 0x000}};

static AnimationFrame* g_GhostAnimationFrames[] = {
    g_DefaultGhostAnimationFrame, D_us_801704CC};

static GhostAbilityValues g_GhostAbilityStats[] = {
    {120, FAM_ABILITY_GHOST_ATTACK, 1},
    {120, FAM_ABILITY_GHOST_ATTACK, 1},
    {100, FAM_ABILITY_GHOST_ATTACK, 1},
    {100, FAM_ABILITY_GHOST_ATTACK, 1},
    {90, FAM_ABILITY_GHOST_ATTACK, 0},
    {90, FAM_ABILITY_GHOST_ATTACK, 0},
    {75, FAM_ABILITY_GHOST_ATTACK, 0},
    {75, FAM_ABILITY_GHOST_ATTACK_SOULSTEAL, 0},
    {60, FAM_ABILITY_GHOST_ATTACK_SOULSTEAL, 0},
    {60, FAM_ABILITY_GHOST_ATTACK_SOULSTEAL, 0},
};

static u16 g_GhostClut[] = {
    0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x7FFF, 0x8000,
    0x8000, 0x8000, 0xFCE7, 0xFDEF, 0xFEF7, 0xFFFF, 0x8000, 0x8000,
};

// offsets for positioning question marks for confused ghost
static s16 g_ConfusedOffsetsX[] = {6, 3, 8};
static s16 g_ConfusedOffsetsY[] = {-20, -18, -15};

#include "../set_entity_animation.h"

// This gets called from the update function called by the engine
// g_CurrentEntity should be the Familiar entity
// Unsure where the target angle gets set initially
s32 UpdateEntityVelocityTowardsTarget(
    Entity* unused, s32 targetX, s32 targetY) {
    static s16 x;
    STATIC_PAD_BSS(2);
    static s16 y;
    STATIC_PAD_BSS(2);
    static s16 angle;
    STATIC_PAD_BSS(2);
    static s16 dAngle;
    STATIC_PAD_BSS(2);
    static s16 distance;
    STATIC_PAD_BSS(2);

    angle = CalculateAngleToEntity(g_CurrentEntity, targetX, targetY);
    dAngle = GetTargetPositionWithDistanceBuffer(
        angle, g_CurrentEntity->ext.ghost.targetAngle,
        g_CurrentEntity->ext.ghost.maxAngle);
    g_CurrentEntity->ext.ghost.targetAngle = dAngle;

    x = targetX - g_CurrentEntity->posX.i.hi;
    y = targetY - g_CurrentEntity->posY.i.hi;
    distance = SquareRoot12((x * x + y * y) << 12) >> 12;

    switch (g_CurrentEntity->step) {
    case 2:
        g_CurrentEntity->velocityX = rcos(dAngle) * distance * 2;
        g_CurrentEntity->velocityY = -(rsin(dAngle) * distance * 2);
        break;
    case 3:
        g_CurrentEntity->velocityX = rcos(dAngle) * distance * 8;
        g_CurrentEntity->velocityY = -(rsin(dAngle) * distance * 8);
        break;
    default:
        g_CurrentEntity->velocityX = (rcos(dAngle) * distance) >> 2;
        g_CurrentEntity->velocityY = -((rsin(dAngle) * distance) >> 2);
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

    if (distance > 0x100) {
        g_CurrentEntity->velocityX =
            (targetX - g_CurrentEntity->posX.i.hi) << 0xE;
        g_CurrentEntity->velocityY =
            (targetY - g_CurrentEntity->posY.i.hi) << 0xE;
    }

    // Return the distance between entity and target
    return distance;
}

static Entity* FindValidTarget(Entity* self) {
    static bool s_TargetMatch[0x80];

    const s32 EntitySearchCount = 128;
    Entity* entity;
    s32 i;
    s32 index;
    u32 matches = 0;

    // Hunt through these entities looking for ones that match all criteria.
    // Call them a success and increment successes.
    entity = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < EntitySearchCount; i++, entity++) {
        s_TargetMatch[i] = false;

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
            g_GhostAbilityStats[s_GhostStats.level / 10].makeBadAttacks == 0)
            continue;
        if (abs(self->posX.i.hi - entity->posX.i.hi) >= 49)
            continue;

        if (abs(self->posY.i.hi - entity->posY.i.hi) >= 49)
            continue;

        if (!self->facingLeft && self->posX.i.hi < entity->posX.i.hi)
            continue;
        if (self->facingLeft && self->posX.i.hi > entity->posX.i.hi)
            continue;
        if (entity->hitPoints >= 0x7000)
            continue;

        if (entity->flags & FLAG_UNK_80000) {
            matches += 1;
            s_TargetMatch[i] = true;
        } else {
            entity->flags |= FLAG_UNK_80000;
            return entity;
        }
    }

    if (matches != 0) {
        index = s_LastTargetedEntityIndex % EntitySearchCount;

        for (i = 0; i < EntitySearchCount; i++) {
            if (s_TargetMatch[index]) {
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

Entity* CreateChildEntity(Entity* parent, s32 entityType) {
    Entity* entity;
    s32 i;

    for (i = 0; i < 3; i++) {
        entity = &g_Entities[i + 5];
        if (!entity->entityId) {
            break;
        }
    }

    if (entity->entityId) {
#ifdef VERSION_PSP
        return NULL;
#else
        return;
#endif
    }
    DestroyEntity(entity);
    entity->entityId =
        entityType ? ENTITY_ID_CONFUSION : ENTITY_ID_ATTACK_CLOUD;
    entity->zPriority = parent->zPriority;
    entity->facingLeft = parent->facingLeft;
    entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
    entity->posX.val = parent->posX.val;
    entity->posY.val = parent->posY.val;
    entity->ext.factory.parent = parent;
    return entity;
}

void ServantInit(InitializeMode mode) {
    RECT rect;
    u16* dst;
    u16* src;
    s32 i;
    SpriteParts** spriteBanks;
    Entity* e;
#ifdef VERSION_PC
    const int lenServantClut = LEN(g_ServantClut);
    const int leng_GhostClut = LEN(g_GhostClut);
#else
    const int lenServantClut = 256;
    const int leng_GhostClut = 32;
#endif

    if (mode != MENU_SAME_SERVANT) {
        dst = &g_Clut[1][CLUT_INDEX_SERVANT];
        src = g_ServantClut;

        for (i = 0; i < lenServantClut; i++) {
            *dst = *src++;
            if (i % 0x10) {
                *dst |= 0x8000;
            }
            dst++;
        }

        // overwrite part of the clut for this servant
        dst = &g_Clut[1][CLUT_INDEX_SERVANT_OVERWRITE];
        src = g_GhostClut;

        for (i = 0; i < leng_GhostClut; i++) {
            *dst++ = *src++;
        }

        rect.x = 0;
        rect.w = 0x100;
        rect.h = 1;
        rect.y = 0xF4;

        dst = &g_Clut[1][CLUT_INDEX_SERVANT];
        LoadImage(&rect, (u_long*)dst);

        spriteBanks = g_api.o.spriteBanks;
        spriteBanks += 20;
        *spriteBanks = (SpriteParts*)g_ServantSpriteParts;

        e = &g_Entities[SERVANT_ENTITY_INDEX];
        DestroyEntity(e);
        e->entityId = ENTITY_ID_SERVANT;
        e->unk5A = 0x6C;
        e->palette = PAL_SERVANT;
        e->animSet = ANIMSET_OVL(20);
        e->zPriority = PLAYER.zPriority - 2;
        e->facingLeft = (PLAYER.facingLeft + 1) & 1;
        e->posX.val = PLAYER.posX.val;
        e->posY.val = PLAYER.posY.val;
        e->params = 0;

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
                    PLAYER.posX.val + (PLAYER.facingLeft ? FIX(18) : FIX(-18));
                e->posY.val = PLAYER.posY.val - FIX(32);
            }
        }
        g_api.GetServantStats(e, 0, 0, &s_GhostStats);
        s_IsServantDestroyed = false;
    }
}

void UpdateServantDefault(Entity* self) {
    static s16 targetX;
    STATIC_PAD_BSS(2);
    static s16 targetY;
    STATIC_PAD_BSS(2);
    static s32 distance;
    STATIC_PAD_BSS(8);
    static s32 x;
    static s32 y;

    g_api.GetServantStats(self, 0, 0, &s_GhostStats);
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
                x = 0x40;
                break;
            case 1:
                x = 0xC0;
                break;
            case 2:
                x = (self->posX.i.hi > 0x80) ? 0xC0 : 0x40;
                break;
            }
            y = 0xA0;
        } else {
            if (PLAYER.facingLeft) {
                x = PLAYER.posX.i.hi + 18;
            } else {
                x = PLAYER.posX.i.hi - 18;
            }
            y = PLAYER.posY.i.hi - 32;
        }
    }
    targetX = x;
    targetY = y + (rsin(self->ext.ghost.bobCounterY) >> 10);
    self->ext.ghost.bobCounterY += 32;
    self->ext.ghost.bobCounterY &= 0xFFF;
    switch (self->step) {
    case 0:
        self->ext.ghost.unk7E = self->params;
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_20000;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_OPACITY;
        SetEntityAnimation(self, g_DefaultGhostAnimationFrame);
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
                self->facingLeft = true;
            else
                self->facingLeft = false;
        } else {
            if (PLAYER.facingLeft == self->facingLeft) {
                if (abs(targetX - self->posX.i.hi) <= 0) {
                    self->facingLeft = PLAYER.facingLeft ? false : true;
                } else if (self->facingLeft && targetX < self->posX.i.hi) {
                    self->facingLeft = PLAYER.facingLeft ? false : true;
                } else if (!self->facingLeft && targetX > self->posX.i.hi) {
                    self->facingLeft = PLAYER.facingLeft ? false : true;
                }
            } else {
                if (self->facingLeft && (self->posX.i.hi - targetX) > 0x1F) {
                    self->facingLeft = PLAYER.facingLeft;
                } else if (
                    !self->facingLeft && (targetX - self->posX.i.hi) > 0x1F) {
                    self->facingLeft = PLAYER.facingLeft;
                }
            }
        }
        UpdateEntityVelocityTowardsTarget(self, targetX, targetY);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (!g_CutsceneHasControl) {
            // Note: this is an assignment, not an equality check
            if (self->ext.ghost.attackTarget = FindValidTarget(self)) {
                self->step++;
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

        targetX = self->ext.ghost.attackTarget->posX.i.hi;
        targetY = self->ext.ghost.attackTarget->posY.i.hi;
        if (self->velocityX > 0) {
            self->facingLeft = true;
        }
        if (self->velocityX < 0) {
            self->facingLeft = false;
        }

        distance = UpdateEntityVelocityTowardsTarget(self, targetX, targetY);
        if (self->step == 2) {
            if (distance < 8) {
                self->ext.ghost.frameCounter = 0;
                self->step++;
            }
        } else if (distance < 8) {
            self->ext.ghost.frameCounter++;
            if (self->ext.ghost.frameCounter ==
                g_GhostAbilityStats[s_GhostStats.level / 10].delayFrames - 30) {
                self->ext.ghost.attackEntity = CreateChildEntity(self, 0);
            } else if (
                self->ext.ghost.frameCounter >
                g_GhostAbilityStats[s_GhostStats.level / 10].delayFrames) {
                self->ext.ghost.frameCounter = 0;
                g_api.GetServantStats(
                    self, g_GhostAbilityStats[s_GhostStats.level / 10].spellId,
                    1, &s_GhostStats);
                self->hitboxWidth = 8;
                self->hitboxHeight = 8;
            }
        } else {
            self->ext.ghost.frameCounter = 0;
            if (
#ifdef VERSION_PSP
                self->ext.ghost.attackEntity != NULL &&
#endif
                self->ext.ghost.attackEntity->entityId ==
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
            if (
#ifdef VERSION_PSP
                self->ext.ghost.confusedEntity != NULL &&
#endif
                self->ext.ghost.confusedEntity->entityId ==
                    ENTITY_ID_CONFUSION) {
                self->ext.ghost.confusedEntity->params = 1;
                // this is calling UpdateConfusedEntites
                ghost_ServantDesc.Unk2C(self->ext.ghost.confusedEntity);
            }
            self->step = 1;
            break;
        }
        UpdateEntityVelocityTowardsTarget(self, targetX, targetY);
        self->posY.val += self->velocityY;
        switch (self->ext.ghost.confusedSubStep) {
        case 0:
            self->ext.ghost.frameCounter = 0;
            self->ext.ghost.confusedSubStep++;
            break;

        case 1:
            self->ext.ghost.frameCounter++;
            if (self->ext.ghost.frameCounter > 60) {
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
                self->facingLeft = self->facingLeft ? false : true;
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
            break;
        }
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
        break;

    case 6:
        if (!(g_Player.status &
              (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_AXEARMOR))) {
            self->step = 1;
            break;
        }
        self->posX.val = FIX(128.0);
        self->posY.val = FIX(-16.0);
        break;
    }

    // controls the pulsing fade
    self->ext.ghost.opacity += self->ext.ghost.opacityAdjustmentAmount;
    if (!(self->ext.ghost.opacity > 0x20 && self->ext.ghost.opacity < 0x80)) {
        self->ext.ghost.opacityAdjustmentAmount *= -1;
    }

    // opacity is used in conjunction with self->drawFlags = FLAG_DRAW_OPACITY
    // to set the alpha/saturation. Zero means fully transparent. 0x80 shows
    // the raw sprite. Values over 0x80 make it "over-bright".
    self->opacity = self->ext.ghost.opacity;
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
    static s32 i;
    static s32 angle;
    static s32 x;
    static s32 y;
    static Primitive* prim;
    static s32 timer;
    static s32 dAngle;

    if (self->params) {
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

        prim = &g_PrimBuf[self->primIndex];

        for (i = 0; i < 8; i++) {
            prim->tpage = 0x1A;
            prim->clut = 0x143;

            prim->u0 = prim->u2 = 0x78;
            prim->u1 = prim->u3 = 0x80;

            prim->v0 = prim->v1 = 0x30;
            prim->v2 = prim->v3 = 0x38;

            PCOL(prim) = 0x80;

            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;

            prim = prim->next;
        }

        timer = 30;
        dAngle = 0;
        g_api.PlaySfx(SFX_GLASS_SHARDS);
        self->step++;

    case 1:
        dAngle = (dAngle + 50) & 0xFFF;
        timer--;
        if (timer < 0) {
            DestroyEntity(self);
            return;
        }
    }
    self->posX.i.hi = self->ext.factory.parent->posX.i.hi;
    self->posY.i.hi = self->ext.factory.parent->posY.i.hi;

    angle = dAngle;
    prim = &g_PrimBuf[self->primIndex];

    for (i = 0; i < 8; i++) {
        x = self->posX.i.hi + ((rcos(angle + (i << 9)) * timer) >> 12);
        y = self->posY.i.hi - ((rsin(angle + (i << 9)) * timer) >> 12);
        prim->x0 = prim->x2 = x - 4;
        prim->x1 = prim->x3 = x + 4;
        prim->y0 = prim->y1 = y - 4;
        prim->y2 = prim->y3 = y + 4;
        prim = prim->next;
    }
}

// This creates and handles the updates for the question marks
// that appear above Ghost when you turn into a bat while
// Ghost is summoned.
void UpdateConfusedEntites(Entity* self) {
    static Primitive* prim;
    static s32 i;
    static s32 frameCounter;
    static s16 x;
    STATIC_PAD_BSS(2);
    static s16 y;
    STATIC_PAD_BSS(2);

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

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 3; i++) {
            prim->clut = 0x143;
            prim->tpage = 0x1E;
            prim->u0 = prim->u2 = 0x78;
            prim->v0 = prim->v1 = 8;
            prim->u1 = prim->u3 = 0x80;
            prim->v2 = prim->v3 = 0x10;
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_UNK_100 | DRAW_UNK02;
            if (i != 0) { // Hide the 2nd and 3rd question mark
                prim->drawMode |= DRAW_HIDE;
            }
            prim = prim->next;
        }
        frameCounter = 0;
        self->step++;
        break;

    case 1: // after 10 frames, unhide a question mark
        frameCounter++;
        if (frameCounter > 10) {
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            frameCounter = 0;
            self->step++;
        }
        break;

    case 2: // after 10 frames, unhide another question mark
        frameCounter++;
        if (frameCounter > 10) {
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim = prim->next;
            prim->drawMode &= ~DRAW_HIDE;
            frameCounter = 0;
            self->step++;
        }
        break;

    case 3: // after 40 more frames (60 total), destroy entity
        frameCounter++;
        if (frameCounter > 40) {
            DestroyEntity(self);
            return;
        }
    }
    x = self->posX.i.hi = self->ext.factory.parent->posX.i.hi;
    y = self->posY.i.hi = self->ext.factory.parent->posY.i.hi;

    prim = &g_PrimBuf[self->primIndex];

    for (i = 0; i < 3; i++) {
        if (!self->facingLeft) {

            prim->x0 = prim->x2 = x + g_ConfusedOffsetsX[i];
            prim->x1 = prim->x3 = x + (g_ConfusedOffsetsX[i] + 8);
        } else {
            prim->x0 = prim->x2 = x - (g_ConfusedOffsetsX[i] + 8);
            prim->x1 = prim->x3 = x - g_ConfusedOffsetsX[i];
        }
        prim->y0 = prim->y1 = y + g_ConfusedOffsetsY[i];
        prim->y2 = prim->y3 = y + (g_ConfusedOffsetsY[i] + 8);
        prim = prim->next;
    }
    return;
}

void unused_28EC(void) {}

void unused_28F4(void) {}

void unused_28FC(void) {}

#include "../shared_events.h"
#include "../shared_globals.h"
#include "../destroy_servant_entity.h"
#include "../servant_update_anim.h"
#include "../../destroy_entity.h"
#include "../accumulate_toward_zero.h"
#include "../search_for_entity_in_range.h"
#include "../calculate_angle_to_entity.h"
#include "../get_target_position_with_distance_buffer.h"
#include "../calculate_distance.h"
#include "../play_sfx.h"
#include "../process_event.h"
#include "../create_event_entity.h"
#include "../is_movement_allowed.h"
#include "../check_all_entities_valid.h"
#include "../servant_unk0.h"
