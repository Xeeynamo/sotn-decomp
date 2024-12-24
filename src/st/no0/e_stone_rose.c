// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"
#include "../pfn_entity_update.h"

// spawn seed
Entity* func_us_801D7D00(u16 arg0) {
    Entity* newEntity;

    newEntity = g_api.GetFreeEntity(0xA0, 0xC0);
    if (newEntity != NULL) {
        DestroyEntity(newEntity);

        newEntity->entityId = E_STONEROSE_SEED;
        newEntity->pfnUpdate = PfnEntityUpdates[E_STONEROSE_SEED - 1];
        newEntity->ext.stoneRose.unk8C = g_CurrentEntity;
        newEntity->params = arg0;
        newEntity->posX.val = g_CurrentEntity->posX.val;
        newEntity->posY.val = g_CurrentEntity->posY.val;
        newEntity->facingLeft = g_CurrentEntity->facingLeft;
        newEntity->flags = g_CurrentEntity->flags & (FLAG_UNK_2000 | FLAG_DEAD);
        return newEntity;
    }
    return NULL;
}

extern PfnEntityUpdate D_us_8018091C[];

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} Unk_D_us_80182268;

extern Unk_D_us_80182268 D_us_80182268[];

// seed update function
void func_us_801D7DAC(Entity* self) {
    Entity* newEntity;
    s32 params;
    s32 i;
    s32 rotZ;

    params = self->params;
    if (self->step == 0) {
        self->rotX = D_us_80182268[params].unk0 & 0xFF;
        self->rotY = D_us_80182268[params].unk2 & 0xFF;
        self->rotZ = D_us_80182268[params].unk4 & 0x7F;
        self->rotPivotX = D_us_80182268[params].unk6 & 0x7F;
        if (D_us_80182268[params].unk6 & 0x80) {
            self->attackElement = self->rotPivotX;
        }
        self->hitPoints = D_us_80182268[params].unk6 >> 0x8;
        self->hitParams = D_us_80182268[params].unk4 >> 0x8;
        self->entityRoomIndex = (D_us_80182268[params].unk4 >> 7) & 1;
        self->hitEffect = D_us_80182268[params].unk0 & 0xFF00;
        self->hitboxOffX = D_us_80182268[params].unk2 >> 0x8;
        self->rotPivotY = 0;
        self->step++;
        switch (self->hitParams) {
        case 0:
            self->flags |= FLAG_POS_CAMERA_LOCKED;
            break;
        case 1:
            break;
        case 2:
            newEntity = self->ext.stoneRose.unk8C;
            self->posX.val = newEntity->posX.val;
            self->posY.val = newEntity->posY.val;
        }
    } else {
        switch (self->hitParams) {
        case 0:
        case 1:
            break;
        case 2:
            newEntity = self->ext.stoneRose.unk8C;
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
    rotZ = self->rotZ;
    for (i = 0; i < rotZ; i++) {
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
        newEntity->entityId = self->rotX;
        if (self->rotX == 0) {
            while (true) {
                i++;
            }
        }
#ifdef VERSION_PSP
        newEntity->pfnUpdate = D_us_8018091C[newEntity->entityId - 1];
#else
        newEntity->pfnUpdate = D_us_8018091C[newEntity->entityId];
#endif
        newEntity->params = self->hitEffect;
        newEntity->ext.stoneRose.unk8C = self->ext.stoneRose.unk8C;
        newEntity->posX.val = self->posX.val;
        newEntity->posY.val = self->posY.val;
        newEntity->facingLeft = self->facingLeft;
        if (self->entityRoomIndex) {
            newEntity->params += self->rotPivotY;
        } else {
            newEntity->params += i;
        }
        self->rotPivotY++;
        if (self->rotPivotY == self->rotY) {
            DestroyEntity(self);
            return;
        }
    }
    self->attackElement = self->rotPivotX;
}

extern u16 D_us_80180AF4[];
extern AnimationFrame D_us_80182280;
extern AnimationFrame D_us_8018228C;
extern AnimationFrame D_us_801822B4;
extern AnimationFrame D_us_80182300;
extern u16 D_us_80182324[];

// Main Stone Rose entity
void func_us_801D8150(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s32 posX;
    s32 posY;
    s16 temp_s0;
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
            PlaySfxPositional(0x731);
            entity -= 0xB;
            for (i = 0; i < 0xC; i++, entity++) {
                entity->hitboxState = 0;
                entity->step = 7;
                entity->ext.stoneRose.unk86 = 0xC0;
                entity->flags |= FLAG_DEAD;
            }
        } else if (
            (entity->step != 3) && (entity->step != 5) && (entity->step != 6)) {
            if ((entity->hitPoints >= 0x1F) || (params != 0xB) ||
                self->ext.stoneRose.unk8A) {
                PlaySfxPositional(0x730);
                if ((self->step != 6) && (self->step != 5)) {
                    self->step_s = self->step;
                }
                self->step = 5;
                self->ext.stoneRose.unk86 = 0x28;
                if ((entity->hitPoints >= 0x1F) && (params == 0xB)) {
                    self->animFrameIdx = 0;
                    self->animFrameDuration = 0;
                    self->anim = &D_us_80182280;
                }
            } else {
                self->ext.stoneRose.unk8A = true;
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->anim = &D_us_801822B4;
                self->step = 3;
                self->drawFlags |= FLAG_DRAW_ROTZ;
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
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        InitializeEntity(D_us_80180AF4);
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
        self->ext.stoneRose.unk7E = params * 0x180;
        self->ext.stoneRose.unk88 = 0x480;
        self->ext.stoneRose.unk82 = params * 0x40 + 0x100;
        if (params == 0) {
            self->ext.stoneRose.unk82 = self->ext.stoneRose.unk82 * 1 / 4;
        }
        if (params == 1) {
            self->ext.stoneRose.unk82 = self->ext.stoneRose.unk82 * 2 / 4;
        }
        if (params == 2) {
            self->ext.stoneRose.unk82 = self->ext.stoneRose.unk82 * 3 / 4;
        }
        break;
    case 1:
        if ((self->posX.i.hi < 0x120) || (self->posX.i.hi >= -0x1F) ||
            (self->posY.i.hi < 0xE8)) {
            self->ext.stoneRose.unk84++;
        }
        self->ext.stoneRose.unk7E += 0x30;
        if (((self->ext.stoneRose.unk84 & 0x1F) == 0x1F) && (params == 0xB)) {
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->anim = &D_us_8018228C;
            PlaySfxPositional(SFX_SEED_SPIT);
            self->step = 2;
        }
        break;
    case 2:
        self->ext.stoneRose.unk7E += 0x30;
        g_api.UpdateAnim(NULL, NULL);
        if (self->animFrameIdx == 0x8 && self->animFrameDuration == 0x2F) {
            PlaySfxPositional(SFX_SEED_BLIP);
            func_us_801D7D00(0U);
        }
        if (self->animFrameDuration < 0) {
            self->step = 1;
            self->animCurFrame = 2;
        }
        break;
    case 3:
        self->ext.stoneRose.unk7E += 0x100;
        self->ext.stoneRose.unk90 += 0x180;
        self->rotZ = rsin(self->ext.stoneRose.unk90) >> 3;
        if (self->ext.stoneRose.unk90 >= 0x6000) {
            self->drawFlags &= ~FLAG_DRAW_ROTZ;
        }
        g_api.UpdateAnim(NULL, NULL);
        if (self->animFrameDuration < 0) {
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->anim = &D_us_80182300;
            PlaySfxPositional(SFX_SEED_SPIT);
            self->step++;
        }
        break;
    case 4:
        self->hitboxWidth = 8;
        self->hitboxHeight = 0x1C;
        self->hitboxOffX = 8;
        self->hitboxOffY = 0;
        self->ext.stoneRose.unk7E += 0x30;
        g_api.UpdateAnim(NULL, NULL);
        --self->ext.stoneRose.unk84;
        if ((self->ext.stoneRose.unk84 & 0x3F) == 0x1F) {
            PlaySfxPositional(SFX_SEED_BLIP);
            func_us_801D7D00(1U);
        }
        break;
    case 5:
        if (params == 0xB) {
            g_api.UpdateAnim(NULL, NULL);
        }
        self->ext.stoneRose.unk88 -= 8;
        self->ext.stoneRose.unk7E += 0xC0;
        if (--self->ext.stoneRose.unk86 == 0) {
            self->ext.stoneRose.unk86 = 0xC;
            self->step++;
        }
        break;
    case 6:
        if (params == 0xB) {
            g_api.UpdateAnim(NULL, NULL);
        }
        if (!self->ext.stoneRose.unk86) {
            self->ext.stoneRose.unk7E += 0x30;
            self->ext.stoneRose.unk88 += 0x10;

            if (self->ext.stoneRose.unk88 >= 0x480) {
                self->ext.stoneRose.unk88 = 0x480;
                self->step = self->step_s;
                if (params == 0xB && (self->step == 2 || self->step == 1)) {
                    self->animFrameIdx = 7;
                    self->animFrameDuration = 1;
                    self->anim = &D_us_8018228C;
                    self->step = 2;
                }
            }
        } else {
            self->ext.stoneRose.unk86--;
        }
        break;
    case 7:
        if (!(g_Timer & 7)) {
            PlaySfxPositional(SFX_EXPLODE_B);
        }
        self->ext.stoneRose.unk7E += 0x180;
        if ((params == 0xB) && !(self->ext.stoneRose.unk86 & 1)) {
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
        if (--self->ext.stoneRose.unk86 == 0) {
            self->step++;
            self->ext.stoneRose.unk86 = (0xC - params) * 2;
        }
        break;
    case 8:
        if (--self->ext.stoneRose.unk86 == 0) {
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
                prim->clut = 0x15F;
                prim->u0 = prim->u2 = 0;
                prim->u1 = prim->u3 = 0x3F;
                prim->v0 = prim->v1 = 0xC0;
                prim->v2 = prim->v3 = 0xFF;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
                prim->priority = self->zPriority - 2;

                PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) =
                    PGREY(prim, 3) = 0x80;

                prim->x0 = prim->x2 = posX - self->ext.stoneRose.unk94;
                prim->x1 = prim->x3 = posX + self->ext.stoneRose.unk94;
                prim->y0 = prim->y1 = posY - self->ext.stoneRose.unk94;
                prim->y2 = prim->y3 = posY + self->ext.stoneRose.unk94;
            }
            self->ext.stoneRose.unk86 = 0x18;
            return;
        }
        break;
    case 9:
        if (--self->ext.stoneRose.unk86) {
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            if (self->primIndex != -1) {
                prim = &g_PrimBuf[self->primIndex];
                if (prim->b3 > 8) {
                    prim->b3 -= 6;
                }
                PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) = prim->r3 =
                    prim->g3 = prim->b3;
                self->ext.stoneRose.unk94 += 4;
                prim->x0 = prim->x2 = posX - self->ext.stoneRose.unk94;
                prim->x1 = prim->x3 = posX + self->ext.stoneRose.unk94;
                prim->y0 = prim->y1 = posY - self->ext.stoneRose.unk94;
                prim->y2 = prim->y3 = posY + self->ext.stoneRose.unk94;
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
    self->ext.stoneRose.unk7C =
        self->ext.stoneRose.unk88 +
        ((rsin(self->ext.stoneRose.unk7E) * self->ext.stoneRose.unk82) >> 0xC);
    if (!(g_GameTimer & 7) || (self->step > 6)) {
        self->ext.stoneRose.unk80++;
        self->ext.stoneRose.unk80 &= 0xF;
    }
    i = 0;
    if (params == 0) {
        i = D_us_80182324[self->ext.stoneRose.unk80];
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

    self->rotY = self->rotX = i;
    if ((params != 0) && (self->step < 8)) {
        self--;
        posX = self->posX.val;
        posY = self->posY.val;
        temp_s0 = self->ext.stoneRose.unk7C;
        self++;
        if (params == 0xB) {
            self->posX.val = posX;
            self->posY.val = posY;
        } else {
            self->posX.val = posX + (rcos(temp_s0) << 4) * 7;
            self->posY.val = posY - (rsin(temp_s0) << 4) * 7;
        }
    }
}

// Seed entity
extern u16 D_us_80180B00[];

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
        self->ext.stoneRose.unk86 = 2;
        self->posX.i.hi = spawnXOffset + self->posX.i.hi;
        break;
    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 4, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (self->ext.stoneRose.unk86 == 0) {
                EntityExplosionSpawn(0, 0);
                return;
            }
            self->posY.i.hi += collider.unk18;
            self->velocityX = self->velocityX >> 1;
            self->velocityY = FIX(-2.0);
            self->ext.stoneRose.unk86--;

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
    self->drawFlags = FLAG_DRAW_ROTZ;
    self->rotZ = zRotation;
}

extern u16 D_us_80180B0C[];
extern AnimationFrame D_us_80182318;

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
        self->anim = &D_us_80182318;
        self->ext.stoneRose.unk86 = rand();
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
        yOffset = rsin(self->ext.stoneRose.unk86) * 4;
        self->ext.stoneRose.unk86 += 0x60;
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
