// SPDX-License-Identifier: AGPL-3.0-or-later

// arg0 is a pointer to X and Y offsets from the current entity.
// iterates through those locations, running CheckCollision on
// each location, returning a set of bit flags indicating which
// offset X,Y locations resulted in a collision (with EFFECT_SOLID)

u8 CheckColliderOffsets(s16* arg0, u8 facing) {
    u8 ret = 0;
    Collider collider;
    s16 posX, posY;

    while (*arg0 != 0xFF) {
        ret <<= 1;

        if (facing) {
            posX = g_CurrentEntity->posX.i.hi + *arg0++;
        } else {
            posX = g_CurrentEntity->posX.i.hi - *arg0++;
        }
        posY = g_CurrentEntity->posY.i.hi + *arg0++;

        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            ret |= 1;
        }
    }

    return ret;
}

extern u16 g_EInitUnkId13[];

// EntityParticleTrail as a possible name here?
// params: The E_EXPLOSION params to use for the trail
void EntityUnkId13(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitUnkId13);
        self->ext.ent13.parentId = self->ext.ent13.parent->entityId;
    case 1:
        if (self->ext.ent13.fiveFrameCounter++ > 4) {
            Entity* newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->entityId = E_EXPLOSION;
                newEntity->pfnUpdate = EntityExplosion;
                newEntity->params = self->params;
            }
            self->ext.ent13.fiveFrameCounter = 0;
        }
        // We just follow the location of our parent
        self->posX.i.hi = self->ext.ent13.parent->posX.i.hi;
        self->posY.i.hi = self->ext.ent13.parent->posY.i.hi;
        // Tests if the parent's ID is different from what it was when we were
        // created. I suspect this is to check for the parent being destroyed.
        if (self->ext.ent13.parent->entityId != self->ext.ent13.parentId) {
            DestroyEntity(self);
        }
        break;
    }
}


static s16 explosionVariantSizes[] = {
    /* FE8 */ 0x0010,
    /* FEA */ 0x0020,
    /* FEC */ 0x0030,
    /* FEE */ 0x0040,
    /* FF0 */ 0x0050,
    /* FF2 */ 0x0060,
    /* FF4 */ 0x0070,
    /* FF6 */ 0x0000,
};
extern void EntityExplosionVariants(Entity* entity);
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
            newEntity->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
            newEntity->zPriority = self->zPriority + 1;
        }
    }
}

extern void EntityGreyPuff(Entity* entity);

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


// NOTE: This entity data is slightly out of order.
// Grey puff data comes before explosion variants data,
// but explosion variant entity comes before grey puff entity.

static s16 greyPuff_rot[] = {
    /* FF8 */ 0x0030,
    /* FFA */ 0x0050,
    /* FFC */ 0x0080,
    /* FFE */ 0x00B0,
    /* 1000 */ 0x00D0,
    /* 1002 */ 0x0100,
    /* 1004 */ 0x0100,
    /* 1006 */ 0x0000,
};

static s32 greyPuff_yVel[] = {
    /* 1008 */ FIX(2.0 / 128),
    /* 100C */ FIX(18.0 / 128),
    /* 1010 */ FIX(30.0 / 128),
    /* 1014 */ FIX(48.0 / 128),
    /* 1018 */ FIX(60.0 / 128),
    /* 101C */ FIX(96.0 / 128),
};

static s32 explode_yVel[] = {
    /* 1020 */ FIX(4.0 / 128),
    /* 1024 */ FIX(20.0 / 128),
    /* 1028 */ FIX(36.0 / 128),
    /* 102C */ FIX(56.0 / 128),
    /* 1030 */ FIX(112.0 / 128),
    /* 1034 */ FIX(144.0 / 128),
};

static u8 explode_startFrame[] = {
    /* 1038 */ 1,
    /* 1039 */ 9,
    /* 103A */ 21,
    /* 103B */ 43,
};

static u16 explode_lifetime[] = {
    /* 103C */ 0x0010,
    /* 103E */ 0x0018,
    /* 1040 */ 0x002A,
    /* 1042 */ 0x002F,
};

// ID is 0x14.

// Creates 4 different explosion animations for when objects or enemies are
// destroyed or killed. The animations are more intense as self->params
// increases (from 0 to 3).

void EntityExplosionVariants(Entity* self) {
    if (!self->step) {
        self->velocityY = explode_yVel[self->ext.destructAnim.index];
        self->flags =
            FLAG_UNK_2000 | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
        self->palette = PAL_OVL(0x195);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = explode_startFrame[self->params];
        self->drawMode = DRAW_TPAGE;
        self->step++;
    } else {
        self->posY.val -= self->velocityY;
        ++self->poseTimer;
        if (!(self->poseTimer % 2)) {
            self->animCurFrame++;
        }

        if (self->poseTimer > explode_lifetime[self->params]) {
            DestroyEntity(self);
        }
    }
}

// looks like a particle of dust fading away
// params: Index of scaleX and velocityY to use
void EntityGreyPuff(Entity* self) {
    if (!self->step) {
        self->flags =
            FLAG_UNK_2000 | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
        self->palette = PAL_OVL(0x195);
        self->animSet = ANIMSET_DRA(5);
        self->animCurFrame = 1;
        self->drawMode = DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
        self->scaleX = greyPuff_rot[self->params];
        self->scaleY = self->scaleX;
        self->velocityY = greyPuff_yVel[self->params];
        self->step++;
    } else {
        self->posY.val -= self->velocityY;
        self->poseTimer++;
        if (!(self->poseTimer % 2)) {
            self->animCurFrame++;
        }
        if (self->poseTimer > 36) {
            DestroyEntity(self);
        }
    }
}

// Purpose is not 100% clear. Creates a falling blue droplet that sizzles after
// hitting the ground. In existing overlays, this entity is not used. But looks
// like Olrox's drool, so using that until we find any other uses.

static u32 g_olroxDroolCollOffsets[] = {
    /* 1044 */ 0x00000000,
    /* 1048 */ 0x000000FF,
};

extern u16 g_EInitParticle[];
void EntityOlroxDrool(Entity* self) {
    s16 primIndex;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (primIndex == -1) {
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->hitboxState = 0;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->x0 = prim->x1 = self->posX.i.hi;
            prim->y0 = prim->y1 = self->posY.i.hi;
            prim->r0 = 64;
            prim->r1 = 0;
            prim->g0 = 64;
            prim->g1 = 0;
            prim->b0 = 255;
            prim->b1 = 16;
            prim->priority = self->zPriority + 1;
            prim->drawMode |= (DRAW_TPAGE2 + DRAW_TPAGE + DRAW_COLORS +
                               DRAW_UNK02 + DRAW_TRANSP);
            prim = prim->next;
        }
        break;

    case 1:
        prim = self->ext.prim;
        if (CheckColliderOffsets((s16*)g_olroxDroolCollOffsets, 0)) {
            prim->y1 += 2;
            if (self->step_s == 0) {
                // When hitting the ground, a sizzling effect is made
                EntityExplosionVariantsSpawner(self, 1, 2, 0, 0, 3, 0);
                self->step_s = 1;
            }
        } else {
            self->velocityY += FIX(0.015625);
            self->posY.val += self->velocityY;
            if ((prim->y0 - prim->y1) > 8) {
                prim->y1 = prim->y0 - 8;
            }
        }

        prim->x0 = self->posX.i.hi;
        prim->x1 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;

        if (prim->y0 < prim->y1) {
            g_api.FreePrimitives(self->primIndex);
            DestroyEntity(self);
        }
        break;
    }
}

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

#if !defined(STAGE_IS_NO0)
u8 UnkCollisionFunc4(s32 arg0) {
    Collider collider;
    u32 bits_67;
    u32 bits_45;
    u32 bits_23;
    u8 bits_01;
    u16 collEff;

    MoveEntity();
    bits_67 = 0;
    bits_23 = 0;
    bits_45 = 0;
    bits_01 = arg0 & 3;
    collEff = 0;
    switch (bits_01) {
    case 0:
        g_CurrentEntity->posY.i.hi += 3;
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != EFFECT_NONE) {
            collEff = collider.effects;
            g_CurrentEntity->posY.i.hi += collider.unk18;
            g_api.CheckCollision(
                g_CurrentEntity->posX.i.hi,
                (s16)(g_CurrentEntity->posY.i.hi - 4), &collider, 0);
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
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != EFFECT_NONE) {
            collEff = collider.effects;
            g_CurrentEntity->posY.i.hi += collider.unk20;
            g_api.CheckCollision(
                g_CurrentEntity->posX.i.hi,
                (s16)(g_CurrentEntity->posY.i.hi + 4), &collider, 0);
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
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != EFFECT_NONE) {
            collEff = collider.effects;
            g_CurrentEntity->posX.i.hi += collider.unk14;
            g_api.CheckCollision((s16)(g_CurrentEntity->posX.i.hi - 4),
                                 g_CurrentEntity->posY.i.hi, &collider, 0);
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
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi, &collider, 0);
        if (collider.effects != EFFECT_NONE) {
            collEff = collider.effects;
            g_CurrentEntity->posX.i.hi += collider.unk1C;
            g_api.CheckCollision((s16)(g_CurrentEntity->posX.i.hi + 4),
                                 g_CurrentEntity->posY.i.hi, &collider, 0);
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
    bits_01 = (bits_45 + (bits_23 + (bits_67 + bits_01)));
    return bits_01;
}

#endif

#include "entity_intense_explosion.h"

#include "initialize_unk_entity.h"

#if defined(VERSION_BETA)
void func_801966B0(u16* sensors) {
    switch (g_CurrentEntity->step_s) {
    case 0:
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->hitboxState = 0;
        g_CurrentEntity->zPriority -= 0x10;
        g_CurrentEntity->drawFlags |= DRAW_HIDE;
        g_CurrentEntity->opacity = 0;
        g_CurrentEntity->step_s++;
        break;
    case 1:
        if (UnkCollisionFunc3(sensors) & 1) {
            g_CurrentEntity->animCurFrame = 1;
            g_CurrentEntity->step_s++;
        }
        break;
    case 2:
        g_CurrentEntity->opacity += 2;
        if (g_CurrentEntity->opacity == 0xC0) {
            g_CurrentEntity->drawFlags = FLAG_DRAW_DEFAULT;
            g_CurrentEntity->drawMode = DRAW_DEFAULT;
            g_CurrentEntity->hitEffect = g_CurrentEntity->palette;
            g_CurrentEntity->step_s++;
            D_80199DE8 = 64;
        }
        break;
    case 3:
        if (D_80199DE8 & 1) {
            g_CurrentEntity->palette = g_CurrentEntity->hitEffect;
        } else {
            g_CurrentEntity->palette = PAL_OVL(0x19F);
        }
        if (!--D_80199DE8) {
            g_CurrentEntity->hitboxState = 3;
            g_CurrentEntity->palette = g_CurrentEntity->hitEffect;
            SetStep(1);
        }
        break;
    }
}
#endif

#include "make_entity_from_id.h"

#include "make_explosions.h"

#include "entity_big_red_fireball.h"

#if !defined(STAGE_IS_NO0)
#include "unk_recursive_primfunc_1.h"
#include "unk_recursive_primfunc_2.h"
#endif

#include "clut_lerp.h"

#include "play_sfx_positional.h"
