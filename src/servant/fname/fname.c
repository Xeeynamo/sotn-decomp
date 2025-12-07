// SPDX-License-Identifier: AGPL-3.0-or-later
#define VERSION_BETA
#include <servant.h>
#include <sfx.h>
#include "../tt_000/bat.h"

#define ENTITY_ID_SEEK_MODE ENTITY_ID_SERVANT
#define ENTITY_ID_ATTACK_MODE SERVANT_ID(2)
#define ENTITY_ID_BLUE_TRAIL SERVANT_ID(10)

extern SpriteParts* g_ServantSpriteParts[];
extern u16 g_ServantClut;
extern u16 g_BatClut;
extern Collider s_UnusedCollider;
extern Primitive* s_CurrentPrim;
extern s32 s_TrailEntityIsAlive[16];
extern s32 s_BlueTrailIndex;
extern Point16 s_TrailLocationPoints[16];
extern s16 s_TrailFacingLeftCache[16];
extern s16 s_TrailUpdateOffsets[16];
extern s16 s_TrailUpdateFadeAmounts[16];
extern s16 s_PointAdjustX;
extern s16 s_PointAdjustY;
extern s32 s_PointIndex;
extern Point16 s_BatPathingPoints[4][16];
extern FamiliarStats s_BatStats;
extern s32 s_IsServantDestroyed;
extern BatAbilityValues g_BatAbilityStats[];
extern s16 s_MoveToPositionX;
extern s16 s_MoveToPositionY;
extern AnimationFrame g_DefaultBatAnimationFrame[];
extern AnimationFrame g_BatHighVelocityAnimationFrame[];
extern AnimationFrame g_BatCloseToTargetAnimationFrame[];
extern AnimationFrame* g_BatAnimationFrames[];
extern s32 s_DistanceToFollowTarget;

extern Sprite g_BatSpriteData[];

#include "../../destroy_entity.h"
#include "../../decelerate.h"
#include "../../set_speed_x.h"
#include "../set_entity_animation.h"
#include "../calculate_angle_to_entity.h"
#include "../get_target_position_with_distance_buffer.h"

// new function
INCLUDE_ASM("servant/fname/nonmatchings/fname", func_80170914);

#include "../check_entity_valid.h"

// identical to TT_000
bool Unused_CheckCollision(s16 x, s16 y, s16* outX, s16* outY) {
    s32 curY;

    g_api.CheckCollision(x, y, &s_UnusedCollider, 0);
    if (s_UnusedCollider.effects & EFFECT_SOLID) {
        return 0;
    }

    for (curY = y - 16; curY > 0; curY -= 16) {
        g_api.CheckCollision(x, curY, &s_UnusedCollider, 0);
        switch (s_UnusedCollider.effects & (EFFECT_UNK_0800 | EFFECT_SOLID)) {
        case 0:
            break;
        case 1:
            *outX = x;
            *outY = curY + s_UnusedCollider.unk10;
            return 1;
        default:
            return 0;
        }
    }
    return 0;
}

void unused_1560(Entity* self) {}

// identical to TT_000
void CreateBlueTrailEntity(Entity* parent) {
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
void CreateAdditionalBats(s32 amount, s32 entityId) {
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
            entity->palette = 0x140;
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
void UpdatePrimitives(Entity* entity, s32 frameIndex) {
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

// has some differences with TT_000
INCLUDE_ASM("servant/fname/nonmatchings/fname", SwitchModeInitialize);

#include "../is_movement_allowed.h"

void ServantInit(void) {
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
    e->palette = 0x140;
    e->animSet = ANIMSET_OVL(20);
    e->zPriority = PLAYER.zPriority - 2;
    e->facingLeft = (PLAYER.facingLeft + 1) & 1;
    e->posX.val = PLAYER.posX.val;
    e->posY.val = PLAYER.posY.val;
    e->params = 0;
    e->ext.bat.cameraX = g_Tilemap.scrollX.i.hi;
    e->ext.bat.cameraY = g_Tilemap.scrollY.i.hi;
}

INCLUDE_ASM("servant/fname/nonmatchings/fname", UpdateServantDefault);

// has some differences with TT_000
void UpdateBatAttackMode(Entity* self) {
    if (self->step == 1 && self->flags & FLAG_UNK_00200000) {
        s_PointAdjustX = (self->ext.bat.cameraX - g_Tilemap.scrollX.i.hi) +
                         (self->ext.bat.lastPlayerPosX - PLAYER.posX.i.hi);
        s_PointAdjustY = (self->ext.bat.cameraY - g_Tilemap.scrollY.i.hi) +
                         (self->ext.bat.lastPlayerPosY - PLAYER.posY.i.hi);

        for (s_PointIndex = 0; s_PointIndex < 16; s_PointIndex++) {
            s_BatPathingPoints[self->ext.bat.batIndex][s_PointIndex].x -=
                s_PointAdjustX;
            s_BatPathingPoints[self->ext.bat.batIndex][s_PointIndex].y -=
                s_PointAdjustY;
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
        s_MoveToPositionX = s_BatPathingPoints[self->ext.bat.batIndex][0].x -
                            self->ext.bat.cameraX;
        s_MoveToPositionY = s_BatPathingPoints[self->ext.bat.batIndex][0].y -
                            self->ext.bat.cameraY;
        self->velocityX = (s_MoveToPositionX - self->posX.i.hi) << 0xC;
        self->velocityY = (s_MoveToPositionY - self->posY.i.hi) << 0xC;
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
            (g_Player.status & PLAYER_STATUS_UNK800)) {
            // This causes the bat familiar to shoot a fireball when the
            // player does so in bat form.
            g_api.CreateEntFactoryFromEntity(self, FACTORY(81, 1), 0);
            self->ext.bat.hasShotFireball = true;
        } else if (self->ext.bat.hasShotFireball &&
                   !(g_Player.status & PLAYER_STATUS_UNK800)) {
            self->ext.bat.hasShotFireball = false;
        }

        // It looks like the use of the variables was largely arbitrary
        s_PointAdjustX = self->ext.bat.follow->posX.i.hi - self->posX.i.hi;
        s_PointAdjustY = self->ext.bat.follow->posY.i.hi - self->posY.i.hi;
        s_DistanceToFollowTarget =
            SquareRoot12(((s_PointAdjustX * s_PointAdjustX) +
                          (s_PointAdjustY * s_PointAdjustY))
                         << 0xC) >>
            0xC;
        if (IsMovementAllowed() || s_DistanceToFollowTarget > 0x18) {
            for (s_PointIndex = 0; s_PointIndex < 0xF; s_PointIndex++) {
                s_BatPathingPoints[self->ext.bat.batIndex][s_PointIndex].x =
                    s_BatPathingPoints[self->ext.bat.batIndex][s_PointIndex + 1]
                        .x;
                s_BatPathingPoints[self->ext.bat.batIndex][s_PointIndex].y =
                    s_BatPathingPoints[self->ext.bat.batIndex][s_PointIndex + 1]
                        .y;
            }
            s_BatPathingPoints[self->ext.bat.batIndex][s_PointIndex].x =
                self->ext.bat.follow->posX.i.hi + self->ext.bat.cameraX;
            s_BatPathingPoints[self->ext.bat.batIndex][s_PointIndex].y =
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
        s_MoveToPositionX = s_BatPathingPoints[self->ext.bat.batIndex][0].x;
        s_MoveToPositionY = s_BatPathingPoints[self->ext.bat.batIndex][0].y;
        self->velocityX = (s_MoveToPositionX - self->posX.i.hi) << 0xA;
        self->velocityY = (s_MoveToPositionY - self->posY.i.hi) << 0xA;
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
            s_CurrentPrim = &g_PrimBuf[self->primIndex];
            for (trailIndex = 0; trailIndex < nPrim; trailIndex++) {
                s_CurrentPrim->tpage = 0x1B;
                s_CurrentPrim->clut = 0x143;
                s_CurrentPrim->u0 = s_CurrentPrim->u2 = 64;
                s_CurrentPrim->v0 = s_CurrentPrim->v1 = 0;
                s_CurrentPrim->u1 = s_CurrentPrim->u3 = 88;
                s_CurrentPrim->v2 = s_CurrentPrim->v3 = 32;
                s_CurrentPrim->priority = self->zPriority;
                s_CurrentPrim->drawMode =
                    DRAW_TRANSP | DRAW_COLORS | DRAW_HIDE | DRAW_TPAGE;
                s_CurrentPrim = s_CurrentPrim->next;
                s_TrailEntityIsAlive[trailIndex] = 0;
            }
            s_BlueTrailIndex = 0;
            self->step++;
        }
        break;
    case 1:
        if (self->ext.batFamBlueTrail.parent->step != 3) {
            self->step++;
        }
        s_TrailLocationPoints[s_BlueTrailIndex].x =
            self->ext.batFamBlueTrail.parent->posX.i.hi;
        s_TrailLocationPoints[s_BlueTrailIndex].y =
            self->ext.batFamBlueTrail.parent->posY.i.hi;
        s_TrailFacingLeftCache[s_BlueTrailIndex] =
            self->ext.batFamBlueTrail.parent->facingLeft;
        s_TrailUpdateOffsets[s_BlueTrailIndex] = 256;
        s_TrailUpdateFadeAmounts[s_BlueTrailIndex] = 192;
        s_TrailEntityIsAlive[s_BlueTrailIndex] = true;

        s_BlueTrailIndex = ++s_BlueTrailIndex >= nPrim ? 0 : s_BlueTrailIndex;

        s_CurrentPrim = &g_PrimBuf[self->primIndex];
        for (trailIndex = 0; trailIndex < nPrim; trailIndex++) {
            if (s_TrailEntityIsAlive[trailIndex]) {
                if (s_TrailFacingLeftCache[trailIndex]) {
                    s_CurrentPrim->x0 = s_CurrentPrim->x2 =
                        s_TrailLocationPoints[trailIndex].x +
                        s_TrailUpdateOffsets[trailIndex] * XS / 256;
                    s_CurrentPrim->x1 = s_CurrentPrim->x3 =
                        s_TrailLocationPoints[trailIndex].x -
                        s_TrailUpdateOffsets[trailIndex] * XE / 256;
                } else {
                    s_CurrentPrim->x0 = s_CurrentPrim->x2 =
                        s_TrailLocationPoints[trailIndex].x -
                        s_TrailUpdateOffsets[trailIndex] * XS / 256;
                    s_CurrentPrim->x1 = s_CurrentPrim->x3 =
                        s_TrailLocationPoints[trailIndex].x +
                        s_TrailUpdateOffsets[trailIndex] * XE / 256;
                }
                s_CurrentPrim->y0 = s_CurrentPrim->y1 =
                    s_TrailLocationPoints[trailIndex].y -
                    s_TrailUpdateOffsets[trailIndex] * YS / 256;
                s_CurrentPrim->y2 = s_CurrentPrim->y3 =
                    s_TrailLocationPoints[trailIndex].y +
                    s_TrailUpdateOffsets[trailIndex] * YE / 256;
                s_CurrentPrim->r0 = s_CurrentPrim->r1 = s_CurrentPrim->r2 =
                    s_CurrentPrim->r3 = s_CurrentPrim->g0 = s_CurrentPrim->g1 =
                        s_CurrentPrim->g2 = s_CurrentPrim->g3 =
                            s_CurrentPrim->b0 = s_CurrentPrim->b1 =
                                s_CurrentPrim->b2 = s_CurrentPrim->b3 =
                                    s_TrailUpdateFadeAmounts[trailIndex];
                s_TrailUpdateOffsets[trailIndex] -= 8;
                s_TrailUpdateFadeAmounts[trailIndex] -= 8;
                if (s_TrailUpdateFadeAmounts[trailIndex] < 81) {
                    s_CurrentPrim->drawMode |= DRAW_HIDE;
                    s_TrailEntityIsAlive[trailIndex] = false;
                } else {
                    s_CurrentPrim->drawMode ^= DRAW_HIDE;
                }
            }
            s_CurrentPrim = s_CurrentPrim->next;
        }
        break;
    case 2:
        isEntityAlive = false;
        s_CurrentPrim = &g_PrimBuf[self->primIndex];
        for (trailIndex = 0; trailIndex < nPrim; trailIndex++) {
            if (s_TrailEntityIsAlive[trailIndex]) {
                if (s_TrailFacingLeftCache[trailIndex]) {
                    s_CurrentPrim->x0 = s_CurrentPrim->x2 =
                        s_TrailLocationPoints[trailIndex].x +
                        s_TrailUpdateOffsets[trailIndex] * XS / 256;
                    s_CurrentPrim->x1 = s_CurrentPrim->x3 =
                        s_TrailLocationPoints[trailIndex].x -
                        s_TrailUpdateOffsets[trailIndex] * XE / 256;
                } else {
                    s_CurrentPrim->x0 = s_CurrentPrim->x2 =
                        s_TrailLocationPoints[trailIndex].x -
                        s_TrailUpdateOffsets[trailIndex] * XS / 256;
                    s_CurrentPrim->x1 = s_CurrentPrim->x3 =
                        s_TrailLocationPoints[trailIndex].x +
                        s_TrailUpdateOffsets[trailIndex] * XE / 256;
                }
                s_CurrentPrim->y0 = s_CurrentPrim->y1 =
                    s_TrailLocationPoints[trailIndex].y -
                    s_TrailUpdateOffsets[trailIndex] * YS / 256;
                s_CurrentPrim->y2 = s_CurrentPrim->y3 =
                    s_TrailLocationPoints[trailIndex].y +
                    s_TrailUpdateOffsets[trailIndex] * YE / 256;
                s_CurrentPrim->r0 = s_CurrentPrim->r1 = s_CurrentPrim->r2 =
                    s_CurrentPrim->r3 = s_CurrentPrim->g0 = s_CurrentPrim->g1 =
                        s_CurrentPrim->g2 = s_CurrentPrim->g3 =
                            s_CurrentPrim->b0 = s_CurrentPrim->b1 =
                                s_CurrentPrim->b2 = s_CurrentPrim->b3 =
                                    s_TrailUpdateFadeAmounts[trailIndex];
                // BUG - This is the same as the line above.  Sets these all
                // again
                s_CurrentPrim->r0 = s_CurrentPrim->r1 = s_CurrentPrim->r2 =
                    s_CurrentPrim->r3 = s_CurrentPrim->g0 = s_CurrentPrim->g1 =
                        s_CurrentPrim->g2 = s_CurrentPrim->g3 =
                            s_CurrentPrim->b0 = s_CurrentPrim->b1 =
                                s_CurrentPrim->b2 = s_CurrentPrim->b3 =
                                    s_TrailUpdateFadeAmounts[trailIndex];
                s_TrailUpdateOffsets[trailIndex] -= 8;
                s_TrailUpdateFadeAmounts[trailIndex] -= 8;
                if (s_TrailUpdateFadeAmounts[trailIndex] < 81) {
                    s_CurrentPrim->drawMode |= DRAW_HIDE;
                    s_TrailEntityIsAlive[trailIndex] = false;
                } else {
                    s_CurrentPrim->drawMode ^= DRAW_HIDE;
                }
            }
            isEntityAlive |= s_TrailEntityIsAlive[trailIndex];
            s_CurrentPrim = s_CurrentPrim->next;
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

extern s32 D_80170658[];

void func_80173164(Entity* entity) {
    s16 index;

    index = entity->params & ((u16)entity->params >> 8) & 0x7F;
    LOH(entity->ext) = index;
    entity->attack = D_80170658[index * 5];
}
