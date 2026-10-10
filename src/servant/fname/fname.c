// SPDX-License-Identifier: AGPL-3.0-or-later

// An early version of the TT_000 Bat familiar, only found in the HD version.
// Gameplay differences to TT_000:
// * no levelling, as GetServantStats is never called
// * base LV1 attack, spawns no extra bats unlike the final version
// * the seek mode sets up its attack hitbox once, using ELEMENT_HIT
// * targets any enemy, while TT_000 does only attack enemies below level 30
// * after a hit, it resets its heading and turns back four times faster
// * no fast catch-up when far away, speed is fixed
// * keeps looking for targets even during a cutscene
// * no familiar events, and no sound effects
// * always spawns next to Alucard, no matter how it was summoned

#define VERSION_BETA
#include <servant.h>
#include <sfx.h>
#include "../tt_000/bat.h"

#define ENTITY_ID_SEEK_MODE ENTITY_ID_SERVANT
#define ENTITY_ID_ATTACK_MODE SERVANT_ID(2)
#define ENTITY_ID_BLUE_TRAIL SERVANT_ID(10)

typedef struct {
    s32 attack;
    s32 delayFrames;
    s32 angleStep;
    s32 additionalBatCount;
    s32 minimumEnemyHp;
} BetaBatAbilityValues;

extern SpriteParts* g_ServantSpriteParts[];
extern u16 g_ServantClut[];

static Point16 s_BatPathingPoints[4][16];
static s32 s_LastTargetedEntityIndex;

static AnimationFrame g_DefaultBatAnimationFrame[] = {
    POSE(4, 0x15, 2), POSE(1, 0x16, 2), POSE(1, 0x17, 2), POSE(1, 0x1E, 2),
    POSE(1, 0x18, 2), POSE(1, 0x19, 2), POSE(4, 0x1A, 2), POSE(2, 0x1B, 2),
    POSE(2, 0x1C, 2), POSE(2, 0x1D, 2), POSE(1, 0x1E, 2), POSE(2, 0x17, 2),
    POSE(2, 0x16, 2), POSE_LOOP(0),
};

static AnimationFrame g_BatAlternateAnimationFrame[] = {
    POSE(5, 0x1F, 2), POSE(5, 0x20, 2), POSE(5, 0x1F, 2), POSE(5, 0x20, 2),
    POSE(5, 0x1F, 2), POSE(5, 0x20, 2), POSE(4, 0x1F, 2), POSE(4, 0x20, 2),
    POSE(3, 0x1F, 2), POSE(3, 0x20, 2), POSE(2, 0x1F, 2), POSE(16, 0x20, 2),
    POSE_LOOP(0),
};

static AnimationFrame g_BatFarFromTargetAnimationFrame[] = {
    POSE(1, 0x15, 2), POSE(1, 0x16, 2), POSE(1, 0x17, 2), POSE(1, 0x1E, 2),
    POSE(1, 0x18, 2), POSE(1, 0x19, 2), POSE(1, 0x1A, 2), POSE(1, 0x1B, 2),
    POSE(1, 0x1C, 2), POSE(1, 0x1D, 2), POSE(1, 0x1E, 2), POSE(1, 0x17, 2),
    POSE(1, 0x16, 2), POSE_LOOP(0),
};

static AnimationFrame g_BatCloseToTargetAnimationFrame[] = {
    POSE(1, 0x15, 2), POSE(1, 0x16, 2), POSE(1, 0x17, 2), POSE(1, 0x1E, 2),
    POSE(1, 0x18, 2), POSE(1, 0x19, 2), POSE(1, 0x1A, 2), POSE(1, 0x1B, 2),
    POSE(1, 0x1C, 2), POSE(1, 0x1D, 2), POSE(1, 0x1E, 2), POSE(1, 0x17, 2),
    POSE(1, 0x16, 2), POSE(1, 0x15, 2), POSE(1, 0x16, 2), POSE(1, 0x17, 2),
    POSE(1, 0x1E, 2), POSE(1, 0x18, 2), POSE(1, 0x19, 2), POSE(2, 0x1A, 2),
    POSE(2, 0x1B, 2), POSE(2, 0x1C, 2), POSE(2, 0x1D, 2), POSE(2, 0x1E, 2),
    POSE(2, 0x17, 2), POSE(2, 0x16, 2), POSE(2, 0x15, 2), POSE(2, 0x16, 2),
    POSE(2, 0x17, 2), POSE(2, 0x1E, 2), POSE(2, 0x18, 2), POSE(2, 0x19, 2),
    POSE(3, 0x1A, 2), POSE(3, 0x1B, 2), POSE(3, 0x1C, 2), POSE(3, 0x1D, 2),
    POSE(3, 0x1E, 2), POSE(3, 0x17, 2), POSE(3, 0x16, 2), POSE_JUMP(0),
};

static AnimationFrame g_BatHighVelocityAnimationFrame[] = {
    POSE(1, 0x15, 2), POSE_END};

static AnimationFrame* g_BatAnimationFrames[] = {
    g_DefaultBatAnimationFrame,       g_BatAlternateAnimationFrame,
    g_BatFarFromTargetAnimationFrame, g_BatCloseToTargetAnimationFrame,
    g_BatHighVelocityAnimationFrame,
};

static BatSpriteData g_BatSpriteData[] = {
    {-4, -4, 8, 8, 0x144, 0x78, 8, 0, 16, 8},
    {-4, -4, 8, 8, 0x144, 0x78, 120, 8, 128, 16},
    {-4, -4, 8, 8, 0x144, 0x78, 228, 135, 236, 143},
    {-4, -4, 8, 8, 0x144, 0x78, 80, 0, 88, 8},
};

static BetaBatAbilityValues g_BatAbilityStats[] = {
    {5, 90, 256, 0, 128}, {6, 90, 320, 1, 128}, {7, 60, 256, 2, 64},
    {8, 60, 320, 2, 64},  {10, 30, 384, 3, 16},
};

static u16 g_BatClut[] = {
    0x0000, 0xFC00, 0xF400, 0xEC00, 0xE400, 0xDC00, 0xD400, 0xCC00,
    0xC400, 0xBC00, 0xB400, 0xAC00, 0xA400, 0x9C00, 0x9400, 0x8C00,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7FFF, 0x0000,
    0x0000, 0x000C, 0x0C76, 0x14BF, 0x295F, 0x39FF, 0x463F, 0x7BDE,
};

#include "../../destroy_entity.h"
#include "../../decelerate.h"
#include "../../set_speed_x.h"
#include "../set_entity_animation.h"
#include "../calculate_angle_to_entity.h"
#include "../step_angle_towards.h"

static Entity* FindValidTarget(Entity* self) {
    static s32 s_TargetMatch[0x80];

    const s32 EntitySearchCount = 128;
    s32 foundIndex;
    s32 i;
    u32 found;
    Entity* entity;

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
        if (abs(self->posX.i.hi - entity->posX.i.hi) < 64 &&
            abs(self->posY.i.hi - entity->posY.i.hi) < 64) {
            continue;
        }
        if (!self->facingLeft && self->posX.i.hi < entity->posX.i.hi) {
            continue;
        }
        if (self->facingLeft && self->posX.i.hi > entity->posX.i.hi) {
            continue;
        }
        if (entity->hitPoints >= 0x7000) {
            continue;
        }

        if (entity->flags & FLAG_UNK_80000) {
            if (entity->hitPoints >=
                g_BatAbilityStats[g_CurrentEntity->ext.bat.unk7C]
                    .minimumEnemyHp) {
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

// identical to TT_000
static bool Unused_CheckCollision(s16 x, s16 y, s16* outX, s16* outY) {
    static Collider col;

    s32 curY;

    g_api.CheckCollision(x, y, &col, 0);
    if (col.effects & EFFECT_SOLID) {
        return 0;
    }

    for (curY = y - 16; curY > 0; curY -= 16) {
        g_api.CheckCollision(x, curY, &col, 0);
        switch (col.effects & (EFFECT_UNK_0800 | EFFECT_SOLID)) {
        case 0:
            break;
        case 1:
            *outX = x;
            *outY = curY + col.unk10;
            return 1;
        default:
            return 0;
        }
    }
    return 0;
}

static void unused_1560(Entity* self) {}

// identical to TT_000
static void CreateBlueTrailEntity(Entity* parent) {
    Entity* entity;
    s32 i;

    // Look for empty ent slot 5, 6, or 7
    for (i = 0; i < 3; i++) {
        entity = &g_Entities[5 + i];
        // if ID is zero, it's vacant and we'll use it.
        if (!entity->entityId) {
            break;
        }
    }
    // If we found a vacant entity in that loop, we use it.
    if (!entity->entityId) {
        // Make sure it's empty
        DestroyEntity(entity);
        // The entity we're making is the Servant function 0xA,
        // UpdateBatBlueTrailEntities
        entity->entityId = ENTITY_ID_BLUE_TRAIL;
        entity->zPriority = parent->zPriority;
        entity->facingLeft = parent->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX.val = parent->posX.val;
        entity->posY.val = parent->posY.val;
        entity->ext.batFamBlueTrail.parent = parent;
    }
}

// identical to TT_000
static void CreateAdditionalBats(s32 amount, s32 entityId) {
    s32 i;
    Entity* entity;
    u16 facing;

    amount = MIN(amount, 3);
    for (i = 0; i < amount; i++) {
        entity = &g_Entities[5 + i];
        if (entity->entityId == entityId) {
            entity->step = 0;
        } else {
            DestroyEntity(entity);
            entity->entityId = entityId;
            entity->unk5A = 0x6C;
            entity->palette = PAL_SERVANT;
            entity->animSet = ANIMSET_OVL(20);
            entity->zPriority = PLAYER.zPriority - 2;
            entity->facingLeft = (PLAYER.facingLeft + 1) & 1;
            // params is used as a bat index for additional bats
            // index 0 is the "main" bat, with others being the followers
            entity->params = i + 1;
        }
        entity->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
        entity->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;
    }
}

// Differences to TT_000:
// * prim->drawMode does not have DRAW_UNK_100
static void UpdatePrimitives(Entity* entity, s32 frameIndex) {
    Primitive* prim;
    s32 tpage;
    s32 x;
    s32 y;
    s32 index;

    prim = &g_PrimBuf[entity->primIndex];
    if (frameIndex == 0) {
        prim->drawMode = DRAW_HIDE;
        return;
    }
    index = frameIndex - 1;
    if (entity->facingLeft) {
        x = entity->posX.i.hi + 2;
    } else {
        x = entity->posX.i.hi - 16;
    }
    y = entity->posY.i.hi - 16;

    prim->x0 = prim->x2 = x - g_BatSpriteData[index].x;
    prim->y0 = prim->y1 = y - g_BatSpriteData[index].y;
    prim->x1 = prim->x3 = prim->x0 + g_BatSpriteData[index].width;
    prim->y2 = prim->y3 = prim->y0 + g_BatSpriteData[index].height;
    prim->clut = g_BatSpriteData[index].clut;
    prim->tpage = g_BatSpriteData[index].tpage / 4;
    prim->u0 = prim->u2 = g_BatSpriteData[index].texLeft;
    prim->v0 = prim->v1 = g_BatSpriteData[index].texTop;
    prim->u1 = prim->u3 = g_BatSpriteData[index].texRight;
    prim->v2 = prim->v3 = g_BatSpriteData[index].texBottom;
    prim->priority = entity->zPriority + 1;
    prim->drawMode = DRAW_UNK02;
}

// identical to TT_000
static void UpdatePrimWhenAlucardIsBat(Entity* entity) {
    Primitive* prim;
    s32 frame;
    s32 y;
    s32 x;

    frame = 2;
    if (entity->facingLeft) {
        x = entity->posX.i.hi + 2;
    } else {
        x = entity->posX.i.hi - 16;
    }
    y = entity->posY.i.hi - 16;

    x += (rsin(entity->ext.bat.frameCounter << 7) * 8) >> 12;
    y -= entity->ext.bat.frameCounter / 2;

    prim = &g_PrimBuf[entity->primIndex];
    prim->x0 = prim->x2 = x - g_BatSpriteData[frame].x;
    prim->y0 = prim->y1 = y - g_BatSpriteData[frame].y;
    prim->x1 = prim->x3 = prim->x0 + g_BatSpriteData[frame].width;
    prim->y2 = prim->y3 = prim->y0 + g_BatSpriteData[frame].height;
}

#define RandBeta(x) ((s32(*)(s32))rand)(x)

// has some differences with TT_000
static void SwitchModeInitialize(Entity* self) {
    s32 i;

    if (!self->ext.bat.previouslyInitialized) {
        self->ext.bat.batIndex = self->params;
        self->ext.bat.doUpdateCloseAnimation = false;
        switch (self->entityId) {
        case ENTITY_ID_SEEK_MODE:
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            UpdatePrimitives(self, 0);
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_HAS_PRIMS | FLAG_UNK_20000;
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
            self->attack = g_BatAbilityStats[self->ext.bat.unk7C].attack;
            self->attackElement = ELEMENT_HIT;
            self->hitboxState = 2;
            self->nFramesInvincibility = 2;
            self->stunFrames = 4;
            self->hitEffect = 1;
            self->entityRoomIndex = 0;
            g_api.func_80118894(self);
            self->ext.bat.randomMovementAngle = RandBeta(0xFFF);
            self->ext.bat.targetAngle = 0;
            self->ext.bat.randomMovementScaler = 12;
            self->ext.bat.frameCounter = RandBeta(0xFFF);
            self->ext.bat.angleStep = 0x20;
            self->step++;
            break;
        case ENTITY_ID_ATTACK_MODE:
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            UpdatePrimitives(self, 0);
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_02000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
            if (!self->ext.bat.batIndex) {
                self->ext.bat.follow = &PLAYER;
            } else {
                self->ext.bat.follow = &g_Entities[self->ext.bat.batIndex + 3];
            }
            self->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
            self->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;

            if (!self->ext.bat.batIndex) {
                for (i = 0; i < 16; i++) {
                    s_BatPathingPoints[self->ext.bat.batIndex][i].x =
                        self->ext.bat.follow->posX.i.hi + self->ext.bat.cameraX;
                    s_BatPathingPoints[self->ext.bat.batIndex][i].y =
                        self->ext.bat.follow->posY.i.hi + self->ext.bat.cameraY;
                }
            } else {
                for (i = 0; i < 16; i++) {
                    if (PLAYER.facingLeft) {
                        s_BatPathingPoints[self->ext.bat.batIndex][i].x =
                            PLAYER.posX.i.hi +
                            ((self->ext.bat.batIndex + 1) * 0x10) +
                            self->ext.bat.cameraX;

                    } else {
                        s_BatPathingPoints[self->ext.bat.batIndex][i].x =
                            PLAYER.posX.i.hi -
                            ((self->ext.bat.batIndex + 1) * 0x10) +
                            self->ext.bat.cameraX;
                    }
                    s_BatPathingPoints[self->ext.bat.batIndex][i].y =
                        PLAYER.posY.i.hi + self->ext.bat.cameraY;
                }
                self->posX.i.hi = PLAYER.facingLeft ? 0x180 : -0x80;
                self->posY.i.hi = rand() % 256;
            }
            self->ext.bat.hasShotFireball = false;
            self->step++;
            break;
        }
    } else {
        self->ext.bat.doUpdateCloseAnimation = false;
        switch (self->entityId) {
        case ENTITY_ID_SEEK_MODE:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_HAS_PRIMS | FLAG_UNK_20000;
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
            self->attack = g_BatAbilityStats[self->ext.bat.unk7C].attack;
            self->attackElement = ELEMENT_HIT;
            self->hitboxState = 2;
            self->nFramesInvincibility = 2;
            self->stunFrames = 4;
            self->hitEffect = 1;
            self->entityRoomIndex = 0;
            g_api.func_80118894(self);
            self->ext.bat.frameCounter = RandBeta(0xFFF);
            self->step++;
            break;
        case ENTITY_ID_ATTACK_MODE:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_02000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
            if (!self->ext.bat.batIndex) {
                self->ext.bat.follow = &PLAYER;
            } else {
                self->ext.bat.follow = &g_Entities[self->ext.bat.batIndex + 3];
            }
            self->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
            self->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;

            for (i = 0; i < 16; i++) {
                if (PLAYER.facingLeft) {
                    s_BatPathingPoints[self->ext.bat.batIndex][i].x =
                        PLAYER.posX.i.hi +
                        ((self->ext.bat.batIndex + 1) * 0x10) +
                        self->ext.bat.cameraX;
                } else {
                    s_BatPathingPoints[self->ext.bat.batIndex][i].x =
                        PLAYER.posX.i.hi -
                        ((self->ext.bat.batIndex + 1) * 0x10) +
                        self->ext.bat.cameraX;
                }
                s_BatPathingPoints[self->ext.bat.batIndex][i].y =
                    PLAYER.posY.i.hi + self->ext.bat.cameraY;
            }
            self->ext.bat.hasShotFireball = false;
            self->step++;
            break;
        }
    }
    self->ext.bat.previouslyInitialized = self->entityId;
}

#include "../is_movement_allowed.h"

void ServantInit(InitializeMode mode) {
    Entity* e;
    RECT rect;
    u16* dst;
    u16* src;
    s32 i;
    SpriteParts** spriteBanks;

    dst = &g_Clut[1][CLUT_INDEX_SERVANT];
    src = &g_ServantClut;
    for (i = 0; i < 0x100; i++) {
        *dst++ = *src++;
    }

    dst = &g_Clut[1][CLUT_INDEX_SERVANT_OVERWRITE];
    src = &g_BatClut;
    for (i = 0; i < 32; i++) {
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
    e->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
    e->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;
}

// has no g_CutsceneHasControl check, unlike TT_000. This means the bat keep
// looking for targets even during a cutscene.
void UpdateServantDefault(Entity* self) {
    static s16 targetX;
    STATIC_PAD_BSS(2);
    static s16 targetY;
    STATIC_PAD_BSS(2);
    static s16 dx0;
    STATIC_PAD_BSS(2);
    static s16 dy0;
    STATIC_PAD_BSS(2);
    static s16 angle;
    STATIC_PAD_BSS(2);
    static s16 dAngle;
    STATIC_PAD_BSS(2);
    static s16 distance0;
    STATIC_PAD_BSS(2);
    static s16 xOffset;
    STATIC_PAD_BSS(2);
    static s32 s_TargetPositionX;
    static s32 s_TargetPositionY;
    static s32 dx1;
    static s32 dy1;
    static s32 distance1;

    xOffset = -0x12 - self->ext.bat.batIndex * 16;
    if (PLAYER.facingLeft) {
        xOffset = -xOffset;
    }
    dx0 = PLAYER.posX.i.hi + xOffset;
    dy0 = PLAYER.posY.i.hi - 0x22;
    angle = self->ext.bat.randomMovementAngle;
    self->ext.bat.randomMovementAngle += 0x10;
    distance0 = self->ext.bat.randomMovementScaler;
    targetX = dx0 + ((rcos(angle) >> 4) * distance0 >> 8);
    targetY = dy0 - ((rsin(angle / 2) >> 4) * distance0 >> 8);
    switch (self->step) {
    case 0:
        SwitchModeInitialize(self);
        break;
    case 1:
        if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
            self->ext.bat.frameCounter = 0;
            self->step = 5;
            break;
        }
        if (PLAYER.facingLeft == self->facingLeft) {
            if (abs(targetX - self->posX.i.hi) <= 0) {
                self->facingLeft = PLAYER.facingLeft ? false : true;
            } else if (self->facingLeft && targetX < self->posX.i.hi) {
                self->facingLeft = PLAYER.facingLeft ? false : true;
            } else if (!self->facingLeft && targetX > self->posX.i.hi) {
                self->facingLeft = PLAYER.facingLeft ? false : true;
            }
        } else if (self->facingLeft && (self->posX.i.hi - targetX) > 0x1F) {
            self->facingLeft = PLAYER.facingLeft;
        } else if (!self->facingLeft && (targetX - self->posX.i.hi) > 0x1F) {
            self->facingLeft = PLAYER.facingLeft;
        }
        angle = CalculateAngleToEntity(self, targetX, targetY);
        dAngle = StepAngleTowards(
            angle, self->ext.bat.targetAngle, self->ext.bat.angleStep);
        self->ext.bat.targetAngle = dAngle;
        dx0 = targetX - self->posX.i.hi;
        dy0 = targetY - self->posY.i.hi;
        distance0 = SquareRoot12((dx0 * dx0 + dy0 * dy0) << 12) >> 12;
        if (distance0 < 30) {
            self->velocityY = -(rsin(dAngle) << 3);
            self->velocityX = rcos(dAngle) << 3;
            self->ext.bat.angleStep = 0x20;
        } else if (distance0 < 60) {
            self->velocityY = -(rsin(dAngle) << 4);
            self->velocityX = rcos(dAngle) << 4;
            self->ext.bat.angleStep = 0x40;
        } else if (distance0 < 100) {
            self->velocityY = -(rsin(dAngle) << 5);
            self->velocityX = rcos(dAngle) << 5;
            self->ext.bat.angleStep = 0x60;
        } else {
            self->velocityY = -(rsin(dAngle) << 6);
            self->velocityX = rcos(dAngle) << 6;
            self->ext.bat.angleStep = 0x80;
        }
        if (self->velocityY > FIX(1.0)) {
            SetEntityAnimation(self, g_BatHighVelocityAnimationFrame);
        } else if (distance0 < 60) {
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
        } else if (distance0 > 100) {
            SetEntityAnimation(self, g_BatFarFromTargetAnimationFrame);
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        dx1 = targetX - self->posX.i.hi;
        dy1 = targetY - self->posY.i.hi;
        distance1 = SquareRoot12((dx1 * dx1 + dy1 * dy1) << 12) >> 12;
        if (distance1 < 24) {
            if (self->ext.bat.doUpdateCloseAnimation) {
                self->ext.bat.doUpdateCloseAnimation = false;
                SetEntityAnimation(self, g_BatCloseToTargetAnimationFrame);
            }
            self->ext.bat.frameCounter++;
            if (self->ext.bat.frameCounter >
                g_BatAbilityStats[self->ext.bat.unk7C].delayFrames) {
                self->ext.bat.frameCounter = 0;
                if ((self->ext.bat.attackTarget = FindValidTarget(self)) !=
                    NULL) {
                    self->step++;
                }
            }
        } else {
            self->ext.bat.doUpdateCloseAnimation = true;
        }
        break;
    case 2:
        self->ext.bat.frameCounter++;
        if (self->ext.bat.frameCounter == 1) {
            UpdatePrimitives(self, 1);
        } else if (self->ext.bat.frameCounter > 30) {
            self->ext.bat.frameCounter = 0;
            UpdatePrimitives(self, 0);
            s_TargetPositionX = self->ext.bat.attackTarget->posX.i.hi;
            s_TargetPositionY = self->ext.bat.attackTarget->posY.i.hi;
            self->hitboxWidth = 5;
            self->hitboxHeight = 5;
            self->ext.bat.targetAngle = 0xC00;
            SetEntityAnimation(self, g_BatHighVelocityAnimationFrame);
            CreateBlueTrailEntity(self);
            self->step++;
        }
        break;
    case 3:
        s_TargetPositionX = self->ext.bat.attackTarget->posX.i.hi;
        s_TargetPositionY = self->ext.bat.attackTarget->posY.i.hi;
        angle =
            CalculateAngleToEntity(self, s_TargetPositionX, s_TargetPositionY);
        dAngle =
            StepAngleTowards(angle, self->ext.bat.targetAngle,
                             g_BatAbilityStats[self->ext.bat.unk7C].angleStep);
        self->ext.bat.targetAngle = dAngle;
        self->velocityX = rcos(dAngle) << 2 << 4;
        self->velocityY = -(rsin(dAngle) << 2 << 4);
        if (self->velocityX > 0) {
            self->facingLeft = true;
        }
        if (self->velocityX < 0) {
            self->facingLeft = false;
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        dx1 = s_TargetPositionX - self->posX.i.hi;
        dy1 = s_TargetPositionY - self->posY.i.hi;
        distance1 = SquareRoot12((dx1 * dx1 + dy1 * dy1) << 12) >> 12;
        if (!CheckEntityValid(self->ext.bat.attackTarget) || distance1 < 8) {
            self->ext.bat.frameCounter = 0;
            self->ext.bat.targetAngle = self->facingLeft ? 0 : 0x800;
            self->step++;
            SetEntityAnimation(self, g_BatCloseToTargetAnimationFrame);
        }
        break;
    case 4:
        angle = CalculateAngleToEntity(self, targetX, targetY);
        dAngle = StepAngleTowards(angle, self->ext.bat.targetAngle, 0x40);
        self->ext.bat.targetAngle = dAngle;
        self->velocityY = -(rsin(dAngle) << 6);
        self->velocityX = rcos(dAngle) << 6;
        self->facingLeft = (self->velocityX >= 0) ? true : false;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->ext.bat.frameCounter++;
        if (self->ext.bat.frameCounter > 30) {
            self->hitboxWidth = 0;
            self->hitboxHeight = 0;
            self->step = 1;
        }
        break;
    case 5:
        self->ext.bat.frameCounter++;
        if (self->ext.bat.frameCounter == 1) {
            UpdatePrimitives(self, 3);
        } else if (self->ext.bat.frameCounter > 30) {
            UpdatePrimitives(self, 0);
            self->entityId = ENTITY_ID_ATTACK_MODE;
            self->step = 0;
        }
        UpdatePrimWhenAlucardIsBat(self);
        break;
    }
    unused_1560(self);
    g_api.UpdateAnim(NULL, g_BatAnimationFrames);
}

// has minor differences with TT_000
void UpdateBatAttackMode(Entity* self) {
    static s32 i;
    static s32 distance;
    static s16 dx;
    STATIC_PAD_BSS(2);
    static s16 dy;
    STATIC_PAD_BSS(2);
    static s16 targetX;
    STATIC_PAD_BSS(2);
    static s16 targetY;
    STATIC_PAD_BSS(2);

    if (self->step == 1 && self->flags & FLAG_UNK_00200000) {
        dx = (self->ext.bat.cameraX - g_Tilemap.scrollX.i.hi) +
             (self->ext.bat.lastPlayerPosX - PLAYER.posX.i.hi);
        dy = (self->ext.bat.cameraY - g_Tilemap.scrollY.i.hi) +
             (self->ext.bat.lastPlayerPosY - PLAYER.posY.i.hi);

        for (i = 0; i < 16; i++) {
            s_BatPathingPoints[self->ext.bat.batIndex][i].x -= dx;
            s_BatPathingPoints[self->ext.bat.batIndex][i].y -= dy;
        }
        return;
    }

    switch (self->step) {
    case 0:
        SwitchModeInitialize(self);
        if (!self->ext.bat.batIndex) {
            CreateAdditionalBats(
                g_BatAbilityStats[self->ext.bat.unk7C].additionalBatCount,
                ENTITY_ID_ATTACK_MODE);
        }
        break;
    case 1:
        self->ext.bat.lastPlayerPosX = PLAYER.posX.i.hi;
        self->ext.bat.lastPlayerPosY = PLAYER.posY.i.hi;
        self->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
        self->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;
        targetX = s_BatPathingPoints[self->ext.bat.batIndex][0].x -
                  self->ext.bat.cameraX;
        targetY = s_BatPathingPoints[self->ext.bat.batIndex][0].y -
                  self->ext.bat.cameraY;
        self->velocityX = (targetX - self->posX.i.hi) << 0xC;
        self->velocityY = (targetY - self->posY.i.hi) << 0xC;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if ((self->velocityX == 0) && (self->velocityY == 0)) {
            if (self->ext.bat.doUpdateCloseAnimation) {
                SetEntityAnimation(self, g_BatCloseToTargetAnimationFrame);
                self->ext.bat.doUpdateCloseAnimation = false;
            }
        } else {
            if (self->velocityY > FIX(1)) {
                SetEntityAnimation(self, g_BatHighVelocityAnimationFrame);
            } else {
                SetEntityAnimation(self, g_DefaultBatAnimationFrame);
            }
            self->ext.bat.doUpdateCloseAnimation = true;
        }
        self->facingLeft = PLAYER.facingLeft ? false : true;
        if (!self->ext.bat.hasShotFireball &&
            (g_Player.status & PLAYER_STATUS_SUBWPN)) {
            // This causes the bat familiar to shoot a fireball when the
            // player does so in bat form.
            g_api.CreateEntFactoryFromEntity(self, FACTORY(81, 1), 0);
            self->ext.bat.hasShotFireball = true;
        } else if (self->ext.bat.hasShotFireball &&
                   !(g_Player.status & PLAYER_STATUS_SUBWPN)) {
            self->ext.bat.hasShotFireball = false;
        }

        // It looks like the use of the variables was largely arbitrary
        dx = self->ext.bat.follow->posX.i.hi - self->posX.i.hi;
        dy = self->ext.bat.follow->posY.i.hi - self->posY.i.hi;
        distance = SquareRoot12(((dx * dx) + (dy * dy)) << 0xC) >> 0xC;
        if (IsMovementAllowed() || distance > 0x18) {
            for (i = 0; i < 0xF; i++) {
                s_BatPathingPoints[self->ext.bat.batIndex][i].x =
                    s_BatPathingPoints[self->ext.bat.batIndex][i + 1].x;
                s_BatPathingPoints[self->ext.bat.batIndex][i].y =
                    s_BatPathingPoints[self->ext.bat.batIndex][i + 1].y;
            }
            s_BatPathingPoints[self->ext.bat.batIndex][i].x =
                self->ext.bat.follow->posX.i.hi + self->ext.bat.cameraX;
            s_BatPathingPoints[self->ext.bat.batIndex][i].y =
                self->ext.bat.follow->posY.i.hi + self->ext.bat.cameraY;
        }
        if (!(g_Player.status & PLAYER_STATUS_BAT_FORM)) {
            self->ext.bat.frameCounter = 0;
            self->step++;
        }
        break;
    case 2:
        self->ext.bat.frameCounter++;
        if (self->ext.bat.frameCounter == 1) {
            UpdatePrimitives(self, 2);
        } else if (self->ext.bat.frameCounter > 30) {
            UpdatePrimitives(self, 0);
            if (!self->ext.bat.batIndex) {
                self->entityId = ENTITY_ID_SEEK_MODE;
                self->step = 0;
                break;
            }
            self->step++;
            s_BatPathingPoints[self->ext.bat.batIndex][0].x =
                PLAYER.facingLeft ? -0x80 : 0x180;
            s_BatPathingPoints[self->ext.bat.batIndex][0].y = rand() % 256;
            SetEntityAnimation(self, g_DefaultBatAnimationFrame);
        }
        break;
    case 3:
        targetX = s_BatPathingPoints[self->ext.bat.batIndex][0].x;
        targetY = s_BatPathingPoints[self->ext.bat.batIndex][0].y;
        self->velocityX = (targetX - self->posX.i.hi) << 0xA;
        self->velocityY = (targetY - self->posY.i.hi) << 0xA;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->posX.i.hi < -0x20 || self->posX.i.hi > 0x120) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    unused_1560(self);
    g_api.UpdateAnim(NULL, g_BatAnimationFrames);
}

void func_801728D4(void) {}

void func_801728DC(void) {}

void func_801728E4(void) {}

void func_801728EC(void) {}

void func_801728F4(void) {}

void func_801728FC(void) {}

void func_80172904(void) {}

// identical to TT_000
void UpdateBatBlueTrailEntities(Entity* self) {
    static Primitive* prim;
    static bool isAlive[16];
    static Point16 positions[16];
    static s16 facingLeft[16];
    static s16 offsets[16];
    static s16 fade[16];
    static s32 idx;

    const s32 nPrim = 16;
    const s32 XS = 11; // X start, left
    const s32 XE = 13; // X end, right
    const s32 YS = 24; // Y start, top
    const s32 YE = 8;  // Y end, bottom
    s32 trailIndex;
    s32 isEntityAlive;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, nPrim);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        } else {
            self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[self->primIndex];
            for (trailIndex = 0; trailIndex < nPrim; trailIndex++) {
                prim->tpage = 0x1B;
                prim->clut = 0x143;
                prim->u0 = prim->u2 = 64;
                prim->v0 = prim->v1 = 0;
                prim->u1 = prim->u3 = 88;
                prim->v2 = prim->v3 = 32;
                prim->priority = self->zPriority;
                prim->drawMode =
                    DRAW_TRANSP | DRAW_COLORS | DRAW_HIDE | DRAW_TPAGE;
                prim = prim->next;
                isAlive[trailIndex] = 0;
            }
            idx = 0;
            self->step++;
        }
        break;
    case 1:
        if (self->ext.batFamBlueTrail.parent->step != 3) {
            self->step++;
        }
        positions[idx].x = self->ext.batFamBlueTrail.parent->posX.i.hi;
        positions[idx].y = self->ext.batFamBlueTrail.parent->posY.i.hi;
        facingLeft[idx] = self->ext.batFamBlueTrail.parent->facingLeft;
        offsets[idx] = 256;
        fade[idx] = 192;
        isAlive[idx] = true;

        idx = ++idx >= nPrim ? 0 : idx;

        prim = &g_PrimBuf[self->primIndex];
        for (trailIndex = 0; trailIndex < nPrim; trailIndex++) {
            if (isAlive[trailIndex]) {
                if (facingLeft[trailIndex]) {
                    prim->x0 = prim->x2 = positions[trailIndex].x +
                                          offsets[trailIndex] * XS / 256;
                    prim->x1 = prim->x3 = positions[trailIndex].x -
                                          offsets[trailIndex] * XE / 256;
                } else {
                    prim->x0 = prim->x2 = positions[trailIndex].x -
                                          offsets[trailIndex] * XS / 256;
                    prim->x1 = prim->x3 = positions[trailIndex].x +
                                          offsets[trailIndex] * XE / 256;
                }
                prim->y0 = prim->y1 =
                    positions[trailIndex].y - offsets[trailIndex] * YS / 256;
                prim->y2 = prim->y3 =
                    positions[trailIndex].y + offsets[trailIndex] * YE / 256;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = fade[trailIndex];
                offsets[trailIndex] -= 8;
                fade[trailIndex] -= 8;
                if (fade[trailIndex] < 81) {
                    prim->drawMode |= DRAW_HIDE;
                    isAlive[trailIndex] = false;
                } else {
                    prim->drawMode ^= DRAW_HIDE;
                }
            }
            prim = prim->next;
        }
        break;
    case 2:
        isEntityAlive = false;
        prim = &g_PrimBuf[self->primIndex];
        for (trailIndex = 0; trailIndex < nPrim; trailIndex++) {
            if (isAlive[trailIndex]) {
                if (facingLeft[trailIndex]) {
                    prim->x0 = prim->x2 = positions[trailIndex].x +
                                          offsets[trailIndex] * XS / 256;
                    prim->x1 = prim->x3 = positions[trailIndex].x -
                                          offsets[trailIndex] * XE / 256;
                } else {
                    prim->x0 = prim->x2 = positions[trailIndex].x -
                                          offsets[trailIndex] * XS / 256;
                    prim->x1 = prim->x3 = positions[trailIndex].x +
                                          offsets[trailIndex] * XE / 256;
                }
                prim->y0 = prim->y1 =
                    positions[trailIndex].y - offsets[trailIndex] * YS / 256;
                prim->y2 = prim->y3 =
                    positions[trailIndex].y + offsets[trailIndex] * YE / 256;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = fade[trailIndex];
                // BUG - This is the same as the line above.  Sets these all
                // again
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = fade[trailIndex];
                offsets[trailIndex] -= 8;
                fade[trailIndex] -= 8;
                if (fade[trailIndex] < 81) {
                    prim->drawMode |= DRAW_HIDE;
                    isAlive[trailIndex] = false;
                } else {
                    prim->drawMode ^= DRAW_HIDE;
                }
            }
            isEntityAlive |= isAlive[trailIndex];
            prim = prim->next;
        }

        if (isEntityAlive == false) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

void func_80173144(void) {}

void func_8017314C(void) {}

void func_80173154(void) {}

void func_8017315C(void) {}

void func_80173164(Entity* entity) {
    s16 index;

    index = entity->params & ((u16)entity->params >> 8) & 0x7F;
    LOH(entity->ext) = index;
    entity->attack = g_BatAbilityStats[index].attack;
}
