// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

#include "../../st/pfn_entity_update.h"

extern EInit g_EInitUnkId13;
extern EInit g_EInitParticle;

extern void EntityExplosionVariants(Entity* entity);
extern void EntityGreyPuff(Entity* entity);

// arg0 is a pointer to X and Y offsets from the current entity.
// iterates through those locations, running CheckCollision on
// each location, returning a set of bit flags indicating which
// offset X,Y locations resulted in a collision (with EFFECT_SOLID)

static s16 explosionVariantSizes[] = {
    0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x00};
INCLUDE_ASM("boss/bo3/nonmatchings/e_misc", CheckColliderOffsets);
INCLUDE_ASM("boss/bo3/nonmatchings/e_misc", EntityUnkId13);
void EntityExplosionVariantsSpawner(
    Entity* self, u8 count, u8 params, s16 x, s16 y, u8 index, s16 xGap) {
    Entity* newEntity;
    s32 i;
    s16 newX = self->posX.i.hi + x;
    s16 newY = self->posY.i.hi + y;

    for (i = 0; i < count; i++) {
        newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEntity != NULL) {
            newEntity->entityId = E_EXPLOSION_VARIANTS;
            newEntity->pfnUpdate = EntityExplosionVariants;
            newEntity->params = params;
            newEntity->posX.i.hi = newX + i * xGap;
            newEntity->posY.i.hi = newY;
            newEntity->ext.destructAnim.index = i + index;
            newEntity->scaleX = explosionVariantSizes[i + index];
            newEntity->scaleY = newEntity->scaleX;
            newEntity->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
            newEntity->zPriority = self->zPriority + 1;
        }
    }
}
void EntityGreyPuffSpawner(
    Entity* self, u8 count, u8 params, s16 x, s16 y, u8 index, s16 xGap) {
    Entity* newEntity;
    s32 i;
    s16 newX = self->posX.i.hi + x;
    s16 newY = self->posY.i.hi + y;

    for (i = 0; i < count; i++) {
        newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEntity != NULL) {
            newEntity->entityId = E_GREY_PUFF;
            newEntity->pfnUpdate = EntityGreyPuff;
            newEntity->posX.i.hi = newX + i * xGap;
            newEntity->posY.i.hi = newY;
            newEntity->params = i;
            newEntity->zPriority = self->zPriority + 1;
        }
    }
}
INCLUDE_ASM("boss/bo3/nonmatchings/e_misc", EntityExplosionVariants);
INCLUDE_ASM("boss/bo3/nonmatchings/e_misc", EntityGreyPuff);
INCLUDE_ASM("boss/bo3/nonmatchings/e_misc", EntityOlroxDrool);
bool UnkCollisionFunc5(s16* pointXY) {
    Collider collider;

    FallEntity();
    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;

    if (g_CurrentEntity->velocityY >= 0) {
        s16 posX = g_CurrentEntity->posX.i.hi;
        s16 posY = g_CurrentEntity->posY.i.hi;
        posX += *pointXY++;
        posY += *pointXY++;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_CurrentEntity->posY.i.hi += collider.unk18;
            g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY / 2;
            if (g_CurrentEntity->velocityY > FIX(-1.0)) {
                return true;
            }
        }
    }
    return false;
}
u8 UnkCollisionFunc4(u8 arg0) {
    Collider collider;
    u8 bits_45;
    u8 bits_23;
    u8 bits_67;
    u16 collEff;
    s16 posX;
    s16 posY;
    u8 bits_01;

    MoveEntity();
    bits_67 = 0;
    bits_23 = 0;
    bits_45 = 0;
    collEff = 0;
    bits_01 = arg0 & 3;
    switch (bits_01) {
    case 0:
        g_CurrentEntity->posY.i.hi += 3;
        posX = g_CurrentEntity->posX.i.hi;
        posY = g_CurrentEntity->posY.i.hi;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects != EFFECT_NONE) {
            collEff = collider.effects;
            g_CurrentEntity->posY.i.hi += collider.unk18;
            posX = g_CurrentEntity->posX.i.hi;
            posY = g_CurrentEntity->posY.i.hi - 4;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_UNK_0002) {
                bits_67 = 0x40;
                if (g_CurrentEntity->velocityX > 0) {
                    bits_01 = 2;
                } else {
                    bits_01 = 3;
                    g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
                }
                g_CurrentEntity->velocityY = -g_CurrentEntity->velocityX;
                g_CurrentEntity->velocityX = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
            if (g_CurrentEntity->velocityX > 0) {
                bits_01 = 3;
            } else {
                bits_01 = 2;
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
            }
            g_CurrentEntity->velocityY = g_CurrentEntity->velocityX;
            g_CurrentEntity->velocityX = 0;
        }
        break;

    case 1:
        g_CurrentEntity->posY.i.hi -= 3;
        posX = g_CurrentEntity->posX.i.hi;
        posY = g_CurrentEntity->posY.i.hi;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects != EFFECT_NONE) {
            collEff = collider.effects;
            g_CurrentEntity->posY.i.hi += collider.unk20;
            posX = g_CurrentEntity->posX.i.hi;
            posY = g_CurrentEntity->posY.i.hi + 4;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_UNK_0002) {
                bits_67 = 0x40;
                if (g_CurrentEntity->velocityX > 0) {
                    bits_01 = 2;
                } else {
                    bits_01 = 3;
                    g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
                }
                g_CurrentEntity->velocityY = g_CurrentEntity->velocityX;
                g_CurrentEntity->velocityX = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posX.val -= g_CurrentEntity->velocityX;
            if (g_CurrentEntity->velocityX > 0) {
                bits_01 = 3;
            } else {
                bits_01 = 2;
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
            }
            g_CurrentEntity->velocityY = -g_CurrentEntity->velocityX;
            g_CurrentEntity->velocityX = 0;
        }
        break;

    case 2:
        g_CurrentEntity->posX.i.hi += 3;
        posX = g_CurrentEntity->posX.i.hi;
        posY = g_CurrentEntity->posY.i.hi;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects != EFFECT_NONE) {
            collEff = collider.effects;
            g_CurrentEntity->posX.i.hi += collider.unk14;
            posX = g_CurrentEntity->posX.i.hi - 4;
            posY = g_CurrentEntity->posY.i.hi;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                bits_67 = 0x40;
                if (g_CurrentEntity->velocityY > 0) {
                    bits_01 = 0;
                } else {
                    bits_01 = 1;
                    g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
                }
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityY;
                g_CurrentEntity->velocityY = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posY.val -= g_CurrentEntity->velocityY;
            if (g_CurrentEntity->velocityY > 0) {
                bits_01 = 1;
            } else {
                bits_01 = 0;
                g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
            }
            g_CurrentEntity->velocityX = g_CurrentEntity->velocityY;
            g_CurrentEntity->velocityY = 0;
        }
        break;

    case 3:
        g_CurrentEntity->posX.i.hi -= 3;
        posX = g_CurrentEntity->posX.i.hi;
        posY = g_CurrentEntity->posY.i.hi;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects != EFFECT_NONE) {
            collEff = collider.effects;
            g_CurrentEntity->posX.i.hi += collider.unk1C;
            posX = g_CurrentEntity->posX.i.hi + 4;
            posY = g_CurrentEntity->posY.i.hi;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                bits_67 = 0x40;
                if (g_CurrentEntity->velocityY > 0) {
                    bits_01 = 0;
                } else {
                    bits_01 = 1;
                    g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
                }
                g_CurrentEntity->velocityX = g_CurrentEntity->velocityY;
                g_CurrentEntity->velocityY = 0;
            }
        } else {
            bits_67 = 0x80;
            g_CurrentEntity->posY.val -= g_CurrentEntity->velocityY;
            if (g_CurrentEntity->velocityY > 0) {
                bits_01 = 1;
            } else {
                bits_01 = 0;
                g_CurrentEntity->velocityY = -g_CurrentEntity->velocityY;
            }
            g_CurrentEntity->velocityX = -g_CurrentEntity->velocityY;
            g_CurrentEntity->velocityY = 0;
        }
    }

    if (collEff & EFFECT_UNK_8000) {
        bits_23 = 4;
    }
    if (collEff & EFFECT_UNK_1000) {
        bits_23 = 8;
    }
    if (collEff & EFFECT_UNK_2000) {
        bits_23 = 0xC;
    }
    if (collEff & EFFECT_UNK_0800) {
        bits_45 = 0x20;
    }
    if (collEff & EFFECT_UNK_4000) {
        bits_45 = 0x10;
    }
    bits_01 = (bits_45 + (bits_23 + (bits_01 + bits_67)));
    return bits_01;
}
void EntityIntenseExplosion(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->palette = PAL_FLAG(PAL_UNK_170);
        self->animSet = ANIMSET_DRA(5);
        self->animCurFrame = 1;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(PAL_UNK_195);
            self->blendMode = BLEND_TRANSP;
        }

        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        self->zPriority += 8;
    } else {
        self->poseTimer++;
        self->posY.val -= FIX(0.25);
        if ((self->poseTimer % 2) == 0) {
            self->animCurFrame++;
        }

        if (self->poseTimer > 36) {
            DestroyEntity(self);
        }
    }
}
INCLUDE_ASM("boss/bo3/nonmatchings/e_misc", InitializeUnkEntity);
void MakeEntityFromId(u16 entityId, Entity* src, Entity* dst) {
    DestroyEntity(dst);
    dst->entityId = entityId;
    dst->pfnUpdate = EntityUpdates[entityId - 1];
    dst->posX.i.hi = src->posX.i.hi;
    dst->posY.i.hi = src->posY.i.hi;
    dst->unk5A = src->unk5A;
    dst->zPriority = src->zPriority;
    dst->animSet = src->animSet;
    dst->flags = FLAG_UNK_2000 | FLAG_NOT_AN_ENEMY | FLAG_KEEP_ALIVE_OFFCAMERA |
                 FLAG_POS_CAMERA_LOCKED | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                 FLAG_DESTROY_IF_OUT_OF_CAMERA;

    if (src->palette & PAL_UNK_FLAG) {
        dst->palette = src->hitEffect;
    } else {
        dst->palette = src->palette;
    }
}
void MakeExplosions(void) {
    u8 temp_s4;
    s16 temp_s3;
    Entity* entity;
    s32 i;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
#if defined(STAGE_IS_NO2) || defined(STAGE_IS_CAT)
            CreateEntityFromEntity(E_BIG_RED_FIREBALL, g_CurrentEntity, entity);
#else
            CreateEntityFromEntity(E_EXPLOSION, g_CurrentEntity, entity);
#endif
            // EntityExplosion does not seem to use these values.
            entity->ext.destructAnim.unk85 = 6 - i;
            entity->ext.destructAnim.unk80 = temp_s3;
            entity->ext.destructAnim.unk84 = temp_s4;
        }
    }
}
extern AnimateEntityFrame g_bigRedFireballAnim[];

void EntityBigRedFireball(Entity* self) {
    s32 speedTemp;

    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->animSet = ANIMSET_DRA(2);
        self->palette = PAL_FLAG(PAL_UNK_1B6);
        self->drawFlags |= (ENTITY_ROTATE + ENTITY_OPACITY);
        self->blendMode |= (BLEND_TRANSP + BLEND_ADD);
        self->opacity = 0x70;
        self->zPriority = 192;

        switch (self->ext.bigredfireball.switch_control) {
        case 1:
            if (self->ext.bigredfireball.speed > 3) {
                self->ext.bigredfireball.speed -= 3;
                self->ext.bigredfireball.angle =
                    self->ext.bigredfireball.angle - 0x800;
            }
            break;

        case 2:
            self->ext.bigredfireball.angle +=
                self->ext.bigredfireball.speed * 192;
            break;
        }

        self->ext.bigredfireball.angle &= 0xFFF;
        self->rotate = self->ext.bigredfireball.angle;
        speedTemp = self->ext.bigredfireball.speed * 320 / 24;
        self->velocityX = speedTemp * rsin(self->ext.bigredfireball.angle);
        self->velocityY = -(speedTemp * rcos(self->ext.bigredfireball.angle));
    }

    if (self->pose > 12) {
        self->velocityX /= 4;
        self->velocityX *= 3;
        self->velocityY /= 4;
        self->velocityY *= 3;
    }

    MoveEntity();

    if (!AnimateEntity(g_bigRedFireballAnim, self)) {
        DestroyEntity(self);
    }
}
INCLUDE_ASM("boss/bo3/nonmatchings/e_misc", UnkRecursivePrimFunc1);
INCLUDE_ASM("boss/bo3/nonmatchings/e_misc", UnkRecursivePrimFunc2);
void ClutLerp(RECT* rect, u16 palIdxA, u16 palIdxB, s32 steps, u16 offset) {
    u16 buf[COLORS_PER_PAL];
    RECT bufRect;
    s32 t;
    u32 r, g, b, a;
    s32 i, j;
    u16 *palA, *palB;

    bufRect.x = rect->x;
    bufRect.w = COLORS_PER_PAL;
    bufRect.h = 1;

    palA = &g_Clut[0][palIdxA * COLORS_PER_PAL];
    palB = &g_Clut[0][palIdxB * COLORS_PER_PAL];

    for (i = 0; i < steps; i++) {
        t = i * FLT(1) / steps;
        for (j = 0; j < COLORS_PER_PAL; j++) {
            r = GET_RED(palA[j]) * (FLT(1) - t) + GET_RED(palB[j]) * t;
            g = GET_GREEN(palA[j]) * (FLT(1) - t) + GET_GREEN(palB[j]) * t;
            b = GET_BLUE(palA[j]) * (FLT(1) - t) + GET_BLUE(palB[j]) * t;

            a = palA[j] & ALPHA_MASK;
            a |= palB[j] & ALPHA_MASK;

            buf[j] = a | (r >> 12) | ((g >> 12) << 5) | ((b >> 12) << 10);
        }

        bufRect.y = rect->y + i;
        LoadImage(&bufRect, (u_long*)buf);
        g_ClutIds[offset + i] = GetClut(bufRect.x, bufRect.y);
    }
}
void PlaySfxPositional(s16 sfxId) {
    s32 posX, posY;
    s16 sfxPan;
    s16 sfxVol;

    posX = g_CurrentEntity->posX.i.hi - 128;
    sfxPan = (abs(posX) - 32) >> 5;
    if (sfxPan > 8) {
        sfxPan = 8;
    } else if (sfxPan < 0) {
        sfxPan = 0;
    }
    if (posX < 0) {
        sfxPan = -sfxPan;
    }
    sfxVol = abs(posX) - 96;
    posY = abs(g_CurrentEntity->posY.i.hi - 128) - 112;
    if (posY > 0) {
        sfxVol += posY;
    }
    if (sfxVol < 0) {
        sfxVol = 0;
    }
    sfxVol = 127 - (sfxVol >> 1);
    if (sfxVol > 0) {
        g_api.PlaySfxVolPan(sfxId, sfxVol, sfxPan);
    }
}
