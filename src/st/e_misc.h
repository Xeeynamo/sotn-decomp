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
        self->palette = PAL_FLAG(PAL_UNK_195);
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
        self->palette = PAL_FLAG(PAL_UNK_195);
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

#endif

// params: (& 0xF0) Use an alternate set of hardcoded palette and drawMode
//         (& 0xFF00) if non-zero, uses ((& 0xFF00) >> 8) as the zPriority
void EntityIntenseExplosion(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->palette = PAL_FLAG(PAL_UNK_170);
        self->animSet = ANIMSET_DRA(5);
        self->animCurFrame = 1;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(PAL_UNK_195);
            self->drawMode = DRAW_TPAGE;
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

static u8 g_UnkEntityAnimData[] = {
    2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 4, 6, -1,
};

void InitializeUnkEntity(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->zPriority += 16;
        self->opacity = 0xF0;
        self->scaleX = 0x01A0;
        self->scaleY = 0x01A0;
        self->animSet = ANIMSET_DRA(8);
        self->animCurFrame = 1;

        if (self->params) {
            self->palette = self->params;
        } else {
            self->palette = PAL_FLAG(PAL_CC_FIRE_EFFECT);
        }

        self->step++;
    } else {
        MoveEntity();
        if (!AnimateEntity(g_UnkEntityAnimData, self)) {
            DestroyEntity(self);
        }
    }
}

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
            g_CurrentEntity->palette = PAL_FLAG(PAL_UNK_19F);
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

extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];
void MakeEntityFromId(u16 entityId, Entity* src, Entity* dst) {
    DestroyEntity(dst);
    dst->entityId = entityId;
    dst->pfnUpdate = OVL_EXPORT(EntityUpdates)[entityId - 1];
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

// Not used in any current overlays. Seems to resemble Gaibon's big fireball,
// but is not actually called in NZ0. Will need to check future overlays for
// any actual uses.

extern u8 g_bigRedFireballAnim[];

void EntityBigRedFireball(Entity* self) {
    s32 speedTemp;

    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->animSet = ANIMSET_DRA(2);
        self->palette = PAL_FLAG(PAL_UNK_1B6);
        self->drawFlags |= (FLAG_DRAW_ROTATE + FLAG_DRAW_OPACITY);
        self->drawMode |= (DRAW_TPAGE + DRAW_TPAGE2);
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
        speedTemp = self->ext.bigredfireball.speed * 320 / 24; // = 13.333
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

#if !defined(STAGE_IS_NO0)
// 0------1------2
// |             |
// |             |
// 3      4      5
// |             |
// |             |
// 6------7------8

// clang-format off
static s16 g_QuadIndices1[] = {
    0, 1, 3, 4, //top left quad
    1, 2, 4, 5, //top right quad
    3, 4, 6, 7, //bottom left quad
    4, 5, 7, 8, //bottom right quad
};
// clang-format on

// dataPtr holds, in order:
// a Primitive, an array of 9 SVECTORs, an array of 10 uvPairs, and a pointer to
// another of dataPtr. Pointer type on dataPtr is
// fake, but needed for Windows.

// dataPtr gets filled up with scratch data used to split srcPrim into 4 smaller
// quads

Primitive* UnkRecursivePrimFunc1(
    SVECTOR* p0, SVECTOR* p1, SVECTOR* p2, SVECTOR* p3, Primitive* srcPrim,
    s32 iterations, Primitive* dstPrim, u8* dataPtr) {
    long flag, p;
    s32 i;
    Primitive* tempPrim;
    s16* indices;
    s32 rotTransResult;
    SVECTOR* points;
    uvPair* uv_values;

    if (dstPrim == NULL) {
        return NULL;
    }
    tempPrim = (Primitive*)dataPtr;
    dataPtr += sizeof(Primitive);
    points = (SVECTOR*)dataPtr;
    dataPtr += sizeof(SVECTOR) * 9;
    uv_values = (uvPair*)dataPtr;
    dataPtr += sizeof(uvPair) * 10;

    points[0] = *p0;
    points[2] = *p1;
    points[6] = *p2;
    points[8] = *p3;

    points[1].vx = (points[0].vx + points[2].vx + 1) >> 1;
    points[1].vy = (points[0].vy + points[2].vy + 1) >> 1;
    points[1].vz = (points[0].vz + points[2].vz + 1) >> 1;
    points[7].vx = (points[6].vx + points[8].vx + 1) >> 1;
    points[7].vy = (points[6].vy + points[8].vy + 1) >> 1;
    points[7].vz = (points[6].vz + points[8].vz + 1) >> 1;
    points[3].vx = (points[0].vx + points[6].vx + 1) >> 1;
    points[3].vy = (points[0].vy + points[6].vy + 1) >> 1;
    points[3].vz = (points[0].vz + points[6].vz + 1) >> 1;
    points[5].vx = (points[2].vx + points[8].vx + 1) >> 1;
    points[5].vy = (points[2].vy + points[8].vy + 1) >> 1;
    points[5].vz = (points[2].vz + points[8].vz + 1) >> 1;
    points[4].vx = (points[3].vx + points[5].vx + 1) >> 1;
    points[4].vy = (points[3].vy + points[5].vy + 1) >> 1;
    points[4].vz = (points[3].vz + points[5].vz + 1) >> 1;

    uv_values[0] = *(uvPair*)&srcPrim->u0;
    uv_values[2] = *(uvPair*)&srcPrim->u1;
    uv_values[6] = *(uvPair*)&srcPrim->u2;
    uv_values[8] = *(uvPair*)&srcPrim->u3;
    uv_values[1].u = (uv_values[0].u + uv_values[2].u + 1) >> 1;
    uv_values[1].v = (uv_values[0].v + uv_values[2].v + 1) >> 1;
    uv_values[7].u = (uv_values[6].u + uv_values[8].u + 1) >> 1;
    uv_values[7].v = (uv_values[6].v + uv_values[8].v + 1) >> 1;
    uv_values[3].u = (uv_values[0].u + uv_values[6].u + 1) >> 1;
    uv_values[3].v = (uv_values[0].v + uv_values[6].v + 1) >> 1;
    uv_values[5].u = (uv_values[2].u + uv_values[8].u + 1) >> 1;
    uv_values[5].v = (uv_values[2].v + uv_values[8].v + 1) >> 1;
    uv_values[4].u = (uv_values[3].u + uv_values[5].u + 1) >> 1;
    uv_values[4].v = (uv_values[3].v + uv_values[5].v + 1) >> 1;

    *tempPrim = *srcPrim;
    indices = g_QuadIndices1;
    for (i = 0; i < 4; i++) {
        s32 idx1 = *indices++;
        s32 idx2 = *indices++;
        s32 idx3 = *indices++;
        s32 idx4 = *indices++;
        rotTransResult = RotTransPers4(
            &points[idx1], &points[idx2], &points[idx3], &points[idx4],
            (long*)&tempPrim->x0, (long*)&tempPrim->x1, (long*)&tempPrim->x2,
            (long*)&tempPrim->x3, &p, &flag);
        *(uvPair*)&tempPrim->u0 = uv_values[idx1];
        *(uvPair*)&tempPrim->u1 = uv_values[idx2];
        *(uvPair*)&tempPrim->u2 = uv_values[idx3];
        *(uvPair*)&tempPrim->u3 = uv_values[idx4];
        if (iterations == 1) {
            if (rotTransResult > 0) {
                Primitive* origNext = dstPrim->next;
                *dstPrim = *tempPrim;
                dstPrim->next = origNext;
                dstPrim = dstPrim->next;
                if (dstPrim == NULL) {
                    return NULL;
                }
            }
        } else {
            dstPrim = UnkRecursivePrimFunc1(
                &points[idx1], &points[idx2], &points[idx3], &points[idx4],
                tempPrim, iterations - 1, dstPrim, dataPtr);
        }
    }
    return dstPrim;
}

// 0------1------2
// |             |
// |             |
// 3      4      5
// |             |
// |             |
// 6------7------8

// clang-format off
static s16 g_QuadIndices2[] = {
    0, 1, 3, 4, //top left quad
    1, 2, 4, 5, //top right quad
    3, 4, 6, 7, //bottom left quad
    4, 5, 7, 8, //bottom right quad
#if !defined(STAGE_IS_NZ0) && !defined(STAGE_IS_NO1) &&                        \
    !defined(STAGE_IS_CHI) && STAGE != STAGE_ST0 && !defined(STAGE_IS_LIB) && !defined(STAGE_IS_CAT)
    0, 0,
#endif
#if defined(VERSION_BETA)
    0, 0
#endif
};
// clang-format on

// dataPtr holds, in order:
// A Primitive, an array of 9 CVECTORs, an array of 9 Point16s, an array of 10
// uvPairs, and a pointer to another of dataPtr. Pointer type on dataPtr is
// fake, but needed for Windows.

// dataPtr gets filled up with scratch data used to split srcPrim into 4 smaller
// quads

Primitive* UnkRecursivePrimFunc2(
    Primitive* srcPrim, s32 iterations, Primitive* dstPrim, u8* dataPtr) {
    s32 i;
    Primitive* tempPrim;
    Point16* points;
    CVECTOR* colors;
    uvPair* uv_values;
    s16* indices;

    if (dstPrim == NULL) {
        return NULL;
    }
    tempPrim = (Primitive*)dataPtr;
    dataPtr += sizeof(Primitive);
    colors = (CVECTOR*)dataPtr;
    dataPtr += sizeof(CVECTOR) * 9;

    points = (Point16*)dataPtr;
    dataPtr += sizeof(Point16) * 9;
    uv_values = (uvPair*)dataPtr;
    dataPtr += sizeof(uvPair) * 10;

    colors[0] = *(CVECTOR*)&srcPrim->r0;
    colors[2] = *(CVECTOR*)&srcPrim->r1;
    colors[6] = *(CVECTOR*)&srcPrim->r2;
    colors[8] = *(CVECTOR*)&srcPrim->r3;
    colors[1].r = ((colors[0].r + colors[2].r + 1) >> 1);
    colors[1].g = ((colors[0].g + colors[2].g + 1) >> 1);
    colors[1].b = ((colors[0].b + colors[2].b + 1) >> 1);
    colors[7].r = ((colors[6].r + colors[8].r + 1) >> 1);
    colors[7].g = ((colors[6].g + colors[8].g + 1) >> 1);
    colors[7].b = ((colors[6].b + colors[8].b + 1) >> 1);
    colors[3].r = ((colors[0].r + colors[6].r + 1) >> 1);
    colors[3].g = ((colors[0].g + colors[6].g + 1) >> 1);
    colors[3].b = ((colors[0].b + colors[6].b + 1) >> 1);
    colors[5].r = ((colors[2].r + colors[8].r + 1) >> 1);
    colors[5].g = ((colors[2].g + colors[8].g + 1) >> 1);
    colors[5].b = ((colors[2].b + colors[8].b + 1) >> 1);
    colors[4].r = ((colors[3].r + colors[5].r + 1) >> 1);
    colors[4].g = ((colors[3].g + colors[5].g + 1) >> 1);
    colors[4].b = ((colors[3].b + colors[5].b + 1) >> 1);

    uv_values[0] = *(uvPair*)&srcPrim->u0;
    uv_values[2] = *(uvPair*)&srcPrim->u1;
    uv_values[6] = *(uvPair*)&srcPrim->u2;
    uv_values[8] = *(uvPair*)&srcPrim->u3;
    uv_values[1].u = (uv_values[0].u + uv_values[2].u + 1) >> 1;
    uv_values[1].v = (uv_values[0].v + uv_values[2].v + 1) >> 1;
    uv_values[7].u = (uv_values[6].u + uv_values[8].u + 1) >> 1;
    uv_values[7].v = (uv_values[6].v + uv_values[8].v + 1) >> 1;
    uv_values[3].u = (uv_values[0].u + uv_values[6].u + 1) >> 1;
    uv_values[3].v = (uv_values[0].v + uv_values[6].v + 1) >> 1;
    uv_values[5].u = (uv_values[2].u + uv_values[8].u + 1) >> 1;
    uv_values[5].v = (uv_values[2].v + uv_values[8].v + 1) >> 1;
    uv_values[4].u = (uv_values[3].u + uv_values[5].u + 1) >> 1;
    uv_values[4].v = (uv_values[3].v + uv_values[5].v + 1) >> 1;

    points[0] = *(Point16*)&srcPrim->x0;
    points[2] = *(Point16*)&srcPrim->x1;
    points[6] = *(Point16*)&srcPrim->x2;
    points[8] = *(Point16*)&srcPrim->x3;
    points[1].x = ((points[0].x + points[2].x + 1) >> 1);
    points[1].y = ((points[0].y + points[2].y + 1) >> 1);
    points[7].x = ((points[6].x + points[8].x + 1) >> 1);
    points[7].y = ((points[6].y + points[8].y + 1) >> 1);
    points[3].x = ((points[0].x + points[6].x + 1) >> 1);
    points[3].y = ((points[0].y + points[6].y + 1) >> 1);
    points[5].x = ((points[2].x + points[8].x + 1) >> 1);
    points[5].y = ((points[2].y + points[8].y + 1) >> 1);
    points[4].x = ((points[3].x + points[5].x + 1) >> 1);
    points[4].y = ((points[3].y + points[5].y + 1) >> 1);

    *tempPrim = *srcPrim;
    indices = g_QuadIndices2;
    for (i = 0; i < 4; i++) {
        s32 idx1 = *indices++;
        s32 idx2 = *indices++;
        s32 idx3 = *indices++;
        s32 idx4 = *indices++;
        *(uvPair*)&tempPrim->u0 = uv_values[idx1];
        *(uvPair*)&tempPrim->u1 = uv_values[idx2];
        *(uvPair*)&tempPrim->u2 = uv_values[idx3];
        *(uvPair*)&tempPrim->u3 = uv_values[idx4];
        *(Point16*)&tempPrim->x0 = points[idx1];
        *(Point16*)&tempPrim->x1 = points[idx2];
        *(Point16*)&tempPrim->x2 = points[idx3];
        *(Point16*)&tempPrim->x3 = points[idx4];
        *(CVECTOR*)&tempPrim->r0 = colors[idx1];
        *(CVECTOR*)&tempPrim->r1 = colors[idx2];
        *(CVECTOR*)&tempPrim->r2 = colors[idx3];
        *(CVECTOR*)&tempPrim->r3 = colors[idx4];

        tempPrim->type = srcPrim->type;
        if (iterations == 1) {
            Primitive* origNext = dstPrim->next;
            *dstPrim = *tempPrim;
            dstPrim->next = origNext;
            dstPrim = dstPrim->next;
            if (dstPrim == NULL) {
                return NULL;
            }
        } else {
            dstPrim = UnkRecursivePrimFunc2(
                tempPrim, iterations - 1, dstPrim, dataPtr);
        }
    }
    return dstPrim;
}

#endif

void ClutLerp(RECT* rect, u16 palIdxA, u16 palIdxB, s32 steps, u16 offset) {
    u16 buf[COLORS_PER_PAL];
    RECT bufRect;
    s32 factor;
    u32 t;
    u32 r, g, b;
    s32 i, j;
    u16 *palA, *palB;

    bufRect.x = rect->x;
    bufRect.w = COLORS_PER_PAL;
    bufRect.h = 1;

    palA = &g_Clut[0][palIdxA * COLORS_PER_PAL];
    palB = &g_Clut[0][palIdxB * COLORS_PER_PAL];

    for (i = 0; i < steps; i++) {
        factor = i * 4096 / steps;
        for (j = 0; j < COLORS_PER_PAL; j++) {
            r = (palA[j] & 0x1F) * (4096 - factor) + (palB[j] & 0x1F) * factor;
            g = ((palA[j] >> 5) & 0x1F) * (4096 - factor) +
                ((palB[j] >> 5) & 0x1F) * factor;
            b = ((palA[j] >> 10) & 0x1F) * (4096 - factor) +
                ((palB[j] >> 10) & 0x1F) * factor;

            t = palA[j] & 0x8000;
            t |= palB[j] & 0x8000;

            buf[j] = t | (r >> 12) | ((g >> 12) << 5) | ((b >> 12) << 10);
        }

        bufRect.y = rect->y + i;
        LoadImage(&bufRect, (u_long*)buf);
        g_ClutIds[offset + i] = GetClut(bufRect.x, bufRect.y);
    }
}

void PlaySfxPositional(s16 sfxId) {
    s32 posX;
    s32 posY;
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
