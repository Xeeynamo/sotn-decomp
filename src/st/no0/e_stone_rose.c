// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"
#include "../pfn_entity_update.h"

static s16 D_us_80182268[][4] = {{0x03E, 0x101, 0x001, 0x000},
                                 {0x03F, 0x106, 0x006, 0x000},
                                 {0x040, 0x020, 0x008, 0x106}};
static AnimationFrame D_us_80182280[] = {{2, 2}, {2, 3}, {0, 0}};
static AnimationFrame D_us_8018228C[] = {
    {2, 2}, {3, 3}, {2, 2},  {2, 3},  {2, 2},
    {2, 3}, {2, 2}, {16, 3}, {48, 2}, {-1, 0}};
static AnimationFrame D_us_801822B4[] = {
    {2, 2}, {3, 3}, {3, 2}, {4, 3},  {4, 2}, {5, 3}, {5, 2},
    {5, 3}, {5, 2}, {5, 3}, {5, 2},  {5, 3}, {5, 2}, {5, 3},
    {5, 2}, {5, 3}, {5, 2}, {16, 3}, {-1, 0}};
static AnimationFrame D_us_80182300[] = {
    {5, 8}, {5, 7}, {5, 6}, {5, 5}, {5, 4}, {0, 0}};
static AnimationFrame D_us_80182318[] = {{4, 10}, {4, 11}, {0, 0}};
static u16 stone_rose_sway_table[] = {
    0, 2, 4, 6, 8, 6, 4, 2, 0, -2, -4, -6, -8, -6, -2};
static s16 D_us_80182344[] = {0, 40, 8, 0};

// spawn seed
Entity* func_us_801D7D00(u16 arg0) {
    Entity* newEntity;

    newEntity = g_api.GetFreeEntity(0xA0, 0xC0);
    if (newEntity != NULL) {
        DestroyEntity(newEntity);

        newEntity->entityId = E_STONEROSE_SEED;
        newEntity->pfnUpdate = PfnEntityUpdates[E_STONEROSE_SEED - 1];
        newEntity->ext.stoneRose.parent = g_CurrentEntity;
        newEntity->params = arg0;
        newEntity->posX.val = g_CurrentEntity->posX.val;
        newEntity->posY.val = g_CurrentEntity->posY.val;
        newEntity->facingLeft = g_CurrentEntity->facingLeft;
        newEntity->flags = g_CurrentEntity->flags & (FLAG_UNK_2000 | FLAG_DEAD);
        return newEntity;
    }
    return NULL;
}

// seed update function
void func_us_801D7DAC(Entity* self) {
    Entity* newEntity;
    s32 params;
    s32 i;
    s32 rotate;

    params = self->params;
    if (self->step == 0) {
        self->scaleX = D_us_80182268[params][0] & 0xFF;
        self->scaleY = D_us_80182268[params][1] & 0xFF;
        self->rotate = D_us_80182268[params][2] & 0x7F;
        self->rotPivotX = D_us_80182268[params][3] & 0x7F;
        if (D_us_80182268[params][3] & 0x80) {
            self->attackElement = self->rotPivotX;
        }
        self->hitPoints = D_us_80182268[params][3] >> 8;
        self->hitParams = D_us_80182268[params][2] >> 8;
        self->entityRoomIndex = (D_us_80182268[params][2] >> 7) & 1;
        self->hitEffect = D_us_80182268[params][0] & 0xFF00;
        self->hitboxOffX = D_us_80182268[params][1] >> 8;
        self->rotPivotY = 0;
        self->step++;
        switch (self->hitParams) {
        case 0:
            self->flags |= FLAG_POS_CAMERA_LOCKED;
            break;
        case 1:
            break;
        case 2:
            newEntity = self->ext.stoneRose.parent;
            self->posX.val = newEntity->posX.val;
            self->posY.val = newEntity->posY.val;
        }
    } else {
        switch (self->hitParams) {
        case 0:
        case 1:
            break;
        case 2:
            newEntity = self->ext.stoneRose.parent;
            self->posX.val = newEntity->posX.val;
            self->posY.val = newEntity->posY.val;
        }
    }
    if (self->attackElement) {
        if (--self->attackElement) {
            return;
        }
        self->attackElement = self->rotPivotX;
    }
    rotate = self->rotate;
    for (i = 0; i < rotate; i++) {
        if (self->hitPoints == 0) {
            newEntity = g_api.GetFreeEntity(0xA0, 0xC0);
        }
        if (self->hitPoints == 1) {
            newEntity = g_api.GetFreeEntity(0xE0, 0x100);
        }
        if (newEntity == NULL) {
            if (self->hitboxOffX == 1) {
                DestroyEntity(self);
            }
            return;
        }
        DestroyEntity(newEntity);
        newEntity->entityId = self->scaleX;
        if (self->scaleX == 0) {
            while (true) {
                i++;
            }
        }
        newEntity->pfnUpdate = PfnEntityUpdates[newEntity->entityId - 1];
        newEntity->params = self->hitEffect;
        newEntity->ext.stoneRose.parent = self->ext.stoneRose.parent;
        newEntity->posX.val = self->posX.val;
        newEntity->posY.val = self->posY.val;
        newEntity->facingLeft = self->facingLeft;
        if (self->entityRoomIndex) {
            newEntity->params += self->rotPivotY;
        } else {
            newEntity->params += i;
        }
        self->rotPivotY++;
        if (self->rotPivotY == self->scaleY) {
            DestroyEntity(self);
            return;
        }
    }
    self->attackElement = self->rotPivotX;
}

// Main Stone Rose entity
void func_us_801D8150(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s32 posX;
    s32 posY;
    s16 angle;
    u32 params;
    Entity* entity;

    params = self->params;
    if (self->step < 7) {
        entity = self - params;
        if ((entity->posX.i.hi > 0x180) || (entity->posX.i.hi < -0x80) ||
            (entity->posY.i.hi > 0x180) || (entity->posY.i.hi < 0)) {
            return;
        }
    }

    entity = self - self->params + 0xB;
    if (self->step == 1) {
        if (self->params == 0) {
            self->unk60 = entity;
        } else {
            self->unk60 = self - 1;
        }
    }
    if ((entity->hitFlags & 0xF) && (self->step < 7)) {
        if (entity->flags & FLAG_DEAD) {
            PlaySfxPositional(SFX_STONE_ROSE_DEATH);
            entity -= 0xB;
            for (i = 0; i < 0xC; i++, entity++) {
                entity->hitboxState = 0;
                entity->step = 7;
                entity->ext.stoneRose.timer = 0xC0;
                entity->flags |= FLAG_DEAD;
            }
        } else if (
            (entity->step != 3) && (entity->step != 5) && (entity->step != 6)) {
            if ((entity->hitPoints >= 0x1F) || (params != 0xB) ||
                self->ext.stoneRose.hasBeenHit) {
                PlaySfxPositional(SFX_STONE_ROSE_PAIN);
                if ((self->step != 6) && (self->step != 5)) {
                    self->step_s = self->step;
                }
                self->step = 5;
                self->ext.stoneRose.timer = 0x28;
                if ((entity->hitPoints >= 0x1F) && (params == 0xB)) {
                    self->pose = 0;
                    self->poseTimer = 0;
                    self->anim = D_us_80182280;
                }
            } else {
                self->ext.stoneRose.hasBeenHit = true;
                self->pose = 0;
                self->poseTimer = 0;
                self->anim = D_us_801822B4;
                self->step = 3;
                self->drawFlags |= FLAG_DRAW_ROTATE;
            }
        }
    }
    switch (self->step) {
    case 0:
        if (params == 0) {
            entity = self + 1;
            for (i = 1; i < 0xC; i++, entity++) {
                CreateEntityFromCurrentEntity(E_ID_3D, entity);
                entity->params = i;
                entity->facingLeft = self->facingLeft;
            }
        }
        self->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
        InitializeEntity(g_EInitStoneRose);
        if (params == 0xB) {
            self->flags &= ~FLAG_KEEP_ALIVE_OFFCAMERA;
        }

        if (params == 0) {
            self->animCurFrame = 1;
        } else if (params == 0xB) {
            self->animCurFrame = 2;
        } else {
            self->animCurFrame = 9;
        }
        self->zPriority = PLAYER.zPriority - 0x20 + (params * 2);
        self->facingLeft = GetSideToPlayer() & 1;
        if (params == 0) {
            self->hitboxWidth = 0xC;
            self->hitboxHeight = 0xC;
            self->hitboxOffX = -8;
            self->hitboxOffY = 8;
        }
        if (params == 0xB) {
            self->hitboxWidth = 0x10;
            self->hitboxHeight = 8;
            self->hitboxOffX = 0x10;
            self->hitboxOffY = 0;
        } else {
            self->hitPoints = 0x7FFF;
        }
        self->ext.stoneRose.wavePhase = params * 0x180;
        self->ext.stoneRose.waveBase = 0x480;
        self->ext.stoneRose.waveAmplitude = params * 0x40 + 0x100;
        if (params == 0) {
            self->ext.stoneRose.waveAmplitude =
                self->ext.stoneRose.waveAmplitude * 1 / 4;
        }
        if (params == 1) {
            self->ext.stoneRose.waveAmplitude =
                self->ext.stoneRose.waveAmplitude * 2 / 4;
        }
        if (params == 2) {
            self->ext.stoneRose.waveAmplitude =
                self->ext.stoneRose.waveAmplitude * 3 / 4;
        }
        break;
    case 1:
        if ((self->posX.i.hi < 0x120) || (self->posX.i.hi >= -0x1F) ||
            (self->posY.i.hi < 0xE8)) {
            self->ext.stoneRose.seedTimer++;
        }
        self->ext.stoneRose.wavePhase += 0x30;
        if (((self->ext.stoneRose.seedTimer & 0x1F) == 0x1F) &&
            (params == 0xB)) {
            self->pose = 0;
            self->poseTimer = 0;
            self->anim = D_us_8018228C;
            PlaySfxPositional(SFX_SEED_SPIT);
            self->step = 2;
        }
        break;
    case 2:
        self->ext.stoneRose.wavePhase += 0x30;
        g_api.UpdateAnim(NULL, NULL);
        if (self->pose == 0x8 && self->poseTimer == 0x2F) {
            PlaySfxPositional(SFX_STONE_ROSE_SEED);
            func_us_801D7D00(0U);
        }
        if (self->poseTimer < 0) {
            self->step = 1;
            self->animCurFrame = 2;
        }
        break;
    case 3:
        self->ext.stoneRose.wavePhase += 0x100;
        self->ext.stoneRose.recoilAngle += ROT(33.75);
        self->rotate = rsin(self->ext.stoneRose.recoilAngle) >> 3;
        if (self->ext.stoneRose.recoilAngle >= FLT(6)) {
            self->drawFlags &= ~FLAG_DRAW_ROTATE;
        }
        g_api.UpdateAnim(NULL, NULL);
        if (self->poseTimer < 0) {
            self->pose = 0;
            self->poseTimer = 0;
            self->anim = D_us_80182300;
            PlaySfxPositional(SFX_SEED_SPIT);
            self->step++;
        }
        break;
    case 4:
        self->hitboxWidth = 8;
        self->hitboxHeight = 0x1C;
        self->hitboxOffX = 8;
        self->hitboxOffY = 0;
        self->ext.stoneRose.wavePhase += 0x30;
        g_api.UpdateAnim(NULL, NULL);
        --self->ext.stoneRose.seedTimer;
        if ((self->ext.stoneRose.seedTimer & 0x3F) == 0x1F) {
            PlaySfxPositional(SFX_STONE_ROSE_SEED);
            func_us_801D7D00(1U);
        }
        break;
    case 5:
        if (params == 0xB) {
            g_api.UpdateAnim(NULL, NULL);
        }
        self->ext.stoneRose.waveBase -= 8;
        self->ext.stoneRose.wavePhase += 0xC0;
        if (--self->ext.stoneRose.timer == 0) {
            self->ext.stoneRose.timer = 0xC;
            self->step++;
        }
        break;
    case 6:
        if (params == 0xB) {
            g_api.UpdateAnim(NULL, NULL);
        }
        if (!self->ext.stoneRose.timer) {
            self->ext.stoneRose.wavePhase += 0x30;
            self->ext.stoneRose.waveBase += 0x10;

            if (self->ext.stoneRose.waveBase >= 0x480) {
                self->ext.stoneRose.waveBase = 0x480;
                self->step = self->step_s;
                if (params == 0xB && (self->step == 2 || self->step == 1)) {
                    self->pose = 7;
                    self->poseTimer = 1;
                    self->anim = D_us_8018228C;
                    self->step = 2;
                }
            }
        } else {
            self->ext.stoneRose.timer--;
        }
        break;
    case 7:
        if (!(g_Timer & 7)) {
            PlaySfxPositional(SFX_EXPLODE_B);
        }
        self->ext.stoneRose.wavePhase += 0x180;
        if ((params == 0xB) && !(self->ext.stoneRose.timer & 1)) {
            entity = g_api.GetFreeEntity(0xE0, 0x100);
            if (entity != NULL) {
                DestroyEntity(entity);
                CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
                entity->params = 1;
                entity->zPriority = self->zPriority + 2;
                if (self->facingLeft) {
                    entity->posX.i.hi =
                        self->posX.i.hi + (rand() & 0x1F) - 0x1F;
                } else {
                    entity->posX.i.hi = self->posX.i.hi + (rand() & 0x1F) - 0xF;
                }
                entity->posY.i.hi = self->posY.i.hi + (rand() & 0x1F) - 0x10;
            }
        }
        if (--self->ext.stoneRose.timer == 0) {
            self->step++;
            self->ext.stoneRose.timer = (0xC - params) * 2;
        }
        break;
    case 8:
        if (--self->ext.stoneRose.timer == 0) {
            if (params == 0xB) {
                PlaySfxPositional(SFX_STUTTER_EXPLODE_B);
            }
            self->step++;
            if (params != 0) {
                self->posY.i.hi += 8;
                EntityExplosionSpawn(1, 0);
                return;
            }
            func_us_801D7D00(2U);
            self->animSet = 0;
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (self->primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                prim = &g_PrimBuf[self->primIndex];
                prim->tpage = 0x1A;
                prim->clut = PAL_FILL_WHITE;
                prim->u0 = prim->u2 = 0;
                prim->u1 = prim->u3 = 0x3F;
                prim->v0 = prim->v1 = 0xC0;
                prim->v2 = prim->v3 = 0xFF;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
                prim->priority = self->zPriority - 2;

                PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) =
                    PGREY(prim, 3) = 0x80;

                prim->x0 = prim->x2 = posX - self->ext.stoneRose.blastRadius;
                prim->x1 = prim->x3 = posX + self->ext.stoneRose.blastRadius;
                prim->y0 = prim->y1 = posY - self->ext.stoneRose.blastRadius;
                prim->y2 = prim->y3 = posY + self->ext.stoneRose.blastRadius;
            }
            self->ext.stoneRose.timer = 0x18;
            return;
        }
        break;
    case 9:
        if (--self->ext.stoneRose.timer) {
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            if (self->primIndex != -1) {
                prim = &g_PrimBuf[self->primIndex];
                if (prim->b3 > 8) {
                    prim->b3 -= 6;
                }
                PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) = prim->r3 =
                    prim->g3 = prim->b3;
                self->ext.stoneRose.blastRadius += 4;
                prim->x0 = prim->x2 = posX - self->ext.stoneRose.blastRadius;
                prim->x1 = prim->x3 = posX + self->ext.stoneRose.blastRadius;
                prim->y0 = prim->y1 = posY - self->ext.stoneRose.blastRadius;
                prim->y2 = prim->y3 = posY + self->ext.stoneRose.blastRadius;
            }
        } else {
            DestroyEntity(self);
        }
        return;
    }

    if ((self->step < 7) && (params != 0) && (params != 0xB)) {
        if ((params ^ g_GameTimer) & 1) {
            self->hitboxState = 0;
        } else {
            self->hitboxState = 3;
        }
    }
    self->ext.stoneRose.segmentAngle =
        self->ext.stoneRose.waveBase +
        ((rsin(self->ext.stoneRose.wavePhase) *
          self->ext.stoneRose.waveAmplitude) >>
         0xC);
    if (!(g_GameTimer & 7) || (self->step > 6)) {
        self->ext.stoneRose.swayIndex++;
        self->ext.stoneRose.swayIndex &= 0xF;
    }
    i = 0;
    if (params == 0) {
        i = stone_rose_sway_table[self->ext.stoneRose.swayIndex];
    }
    if (params == 1) {
        i = 0x30;
    }
    if (params == 2) {
        i = 0x20;
    }
    if (params == 3) {
        i = 0x10;
    }
    if (params == 4) {
        i = 0x8;
    }
    i += 0x100;

    self->scaleY = self->scaleX = i;
    if ((params != 0) && (self->step < 8)) {
        self--;
        posX = self->posX.val;
        posY = self->posY.val;
        angle = self->ext.stoneRose.segmentAngle;
        self++;
        if (params == 0xB) {
            self->posX.val = posX;
            self->posY.val = posY;
        } else {
            self->posX.val = posX + (rcos(angle) << 4) * 7;
            self->posY.val = posY - (rsin(angle) << 4) * 7;
        }
    }
}

// Seed entity
void func_us_801D8DF0(Entity* self) {
    Collider collider;
    s16 xOffset;
    s32 spawnXOffset;
    s32 zRotation;

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
        EntityExplosionSpawn(0, 0);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B00);
        self->animCurFrame = 0x2C;
        if (self->facingLeft) {
            self->velocityX = FIX(-1.75);
        } else {
            self->velocityX = FIX(1.75);
        }

        if (!self->facingLeft) {
            spawnXOffset = 0x28;
        } else {
            spawnXOffset = -0x28;
        }
        self->ext.stoneRose.timer = 2;
        self->posX.i.hi = spawnXOffset + self->posX.i.hi;
        break;
    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 4, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (self->ext.stoneRose.timer == 0) {
                EntityExplosionSpawn(0, 0);
                return;
            }
            self->posY.i.hi += collider.unk18;
            self->velocityX = self->velocityX >> 1;
            self->velocityY = FIX(-2.0);
            self->ext.stoneRose.timer--;

            self->drawFlags |= FLAG_BLINK;
        }

        if (self->velocityX < 0) {
            xOffset = -6;
        } else {
            xOffset = 8;
        }
        g_api.CheckCollision(
            self->posX.i.hi + xOffset, self->posY.i.hi, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->velocityY = 0;
            self->velocityX = -self->velocityX;
        }
        break;
    }
    self->velocityY += FIX(1.5 / 16);
    zRotation = (ratan2(-self->velocityY, self->velocityX) + 0x600) & 0xFFF;
    self->drawFlags = FLAG_DRAW_ROTATE;
    self->rotate = zRotation;
}

// Seed entity
void func_us_801D8FFC(Entity* self) {
    Collider collider;
    s32 angle;
    s32 xOffset;
    s32 yOffset;

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
        EntityExplosionSpawn(0, 0);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B0C);
        self->zPriority = PLAYER.zPriority + 0x10;
        self->anim = D_us_80182318;
        self->ext.stoneRose.timer = rand();
        angle = (rand() & 0x1FF) + 0x700;
        self->velocityX = rcos(angle) * 0x10;
        if (!self->facingLeft) {
            self->velocityX = -self->velocityX;
        }

        self->velocityY = rsin(angle) * 0x10;
        if (!self->facingLeft) {
            xOffset = 0xC;
        } else {
            xOffset = -0xC;
        }
        self->posX.i.hi = xOffset + self->posX.i.hi;
        self->posX.i.hi += (rand() & 7) - 4;
        self->posY.i.hi += (rand() & 7) - 4;
        return;
    case 1:
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            EntityExplosionSpawn(0, 0);
            return;
        }
        g_api.UpdateAnim(NULL, NULL);
        yOffset = rsin(self->ext.stoneRose.timer) * 4;
        self->ext.stoneRose.timer += 0x60;
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->posY.val += yOffset;
        return;
    }
}

// Death explosion
void func_us_801D91C4(Entity* self) {
    s16 random;
    Entity* fakeEntity = self; // !FAKE

    if (self->step == 0) {
        self->params = 1;
        EntityExplosion(fakeEntity);
        self->zPriority = PLAYER.zPriority + 0x20;
        random = rand() & 0x7FF;
        self->velocityX = rcos(random) << 4 << 2;
        self->velocityY = -(rsin(random) << 4) << 2;
    } else {
        self->posX.val += self->velocityX;
        EntityExplosion(fakeEntity);
    }
}
