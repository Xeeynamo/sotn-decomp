#include "nz0.h"

// moves around on walls and drips poison
void EntitySpittleBone(Entity* self) {
    Entity* newEntity;
    s32 i;

    if ((self->flags & 0x100) && (self->step < 3)) {
        self->step = 3;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180CAC);
        self->unk19 = 4;
        self->unk1E = 0;
        self->flags &= ~0x2200;
        self->facing = self->subId;
        break;

    case 1:
        if (func_801BCCFC(&D_801824CC) & 1) {
            newEntity = &self[1];
            self->unk7C.S8.unk0 = 0;
            CreateEntityFromEntity(0x32, self, newEntity);
            newEntity->facing = self->facing;
            newEntity->unk7C.S8.unk0 = self->unk7C.S8.unk0;
            if (self->facing != 0) {
                self->accelerationX = 0x10000;
                newEntity->posX.i.hi += 16;
            } else {
                self->accelerationX = -0x10000;
                newEntity->posX.i.hi -= 16;
            }
            newEntity->accelerationX = self->accelerationX;
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(&D_80182524, self);
        self->unk7C.U8.unk0 = func_801C1034(self->unk7C.U8.unk0);
        if (self->unk80.modeS16.unk2 != 0) {
            self->unk1E += self->unk80.modeS16.unk0;
            self->unk80.modeS16.unk2--;
            if (self->unk80.modeS16.unk2 == 0) {
                self->unk1E = self[1].unk1E;
            }
        }
        if (((self->unk7C.U8.unk0 & 0x3F) == 1) && (!(Random() & 0x1F))) {
            newEntity = AllocEntity(D_8007A958, &D_8007A958[32]);
            if (newEntity != 0) {
                CreateEntityFromEntity(0x33, self, newEntity);
                newEntity->unk84.unk = self;
                newEntity->posY.i.hi += 24;
            }
        }
        self->unk10 = (u32)rsin(self->unk1E) >> 8;
        self->unk12 = -(rcos(self->unk1E) * 16) >> 0xC;
        return;

    case 3:
        for (i = 0; i < 6; i++) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                func_801C1780(0x31, self, newEntity);
                newEntity->facing = self->facing;
                newEntity->flags = -0x37FFE000;
                newEntity->palette = 0x20D;
                newEntity->animCurFrame = i + 0x3A;
                newEntity->unk19 |= 4;
                newEntity->unk1E = self->unk1E;
                newEntity->step = 4;
                newEntity->accelerationX = D_80182504[i];
                newEntity->accelerationY = 0xFFFD0000 - ((Random() & 3) << 0xF);
                newEntity->unk80.modeS16.unk2 = D_801824E2[i + 0x3A];
            }
        }

        newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(2, self, newEntity);
            newEntity->subId = 1;
            newEntity->posX.i.hi += -(rsin(self->unk1E) * 0x10) >> 0xC;
            newEntity->posY.i.hi += -(rcos(self->unk1E) * 0x10) >> 0xC;
        }
        func_801C29B0(0x62B);
        DestroyEntity(self);
        break;

    case 4:
        MoveEntity();
        self->accelerationY += 0x2800;
        self->unk80.modeS16.unk2--;
        if (self->unk80.modeS16.unk2 == 0) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(2, self, newEntity);
                newEntity->subId = 0;
            }
            DestroyEntity(self);
        }
        break;
    }
}

const u32 rodataPadding_801B08B0 = 0;

// DECOMP_ME_WIP func_801C6B24 https://decomp.me/scratch/T0T7K mostly regalloc
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/4672C", func_801C6B24);

// spit projectile from spittle bone
// Unique
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/4672C", EntitySpittleBoneSpit);

// SubWeapons floating in the breakable container
void EntitySubWeaponContainer(Entity* self) {
    SubWpnContDebris* glassPieceTBL;
    Entity* newEntity;
    Primitive* prim;
    s16 firstPrimIndex;
    s32 rnd;
    s32 rndPosX;
    s32 rndPosY;
    s32 absRnd;
    s32 i;
    s32 pad[23];

    switch (self->step) {
    case SUBWPNCONT_INIT:
        InitializeEntity(D_80180CE8);
        self->blendMode = 0x10;
        self->animCurFrame = 1;
        self->zPriority = 0x70;
        self->hitboxWidth = 14;
        self->hitboxHeight = 32;
        self->unk12 = -0x38;
        self->unk10 = 0;
        self->unk3C = 2;
        self->palette += self->subId;
        CreateEntityFromEntity(0x3D, self, &self[1]); // Create SubWeapon
        self[1].posY.i.hi -= 72;
        self[1].subId = D_801825CC[self->subId];
        self[1].zPriority = self->zPriority - 2;

        firstPrimIndex = g_api.AllocPrimitives(4, 2);
        if (firstPrimIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->firstPolygonIndex = firstPrimIndex;
        prim = &g_PrimBuf[firstPrimIndex];
        *(s32*)&self->unk7C = prim;
        self->flags |= FLAG_FREE_POLYGONS;
        while (prim != NULL) {
            prim->priority = self->zPriority + 0xFFFF;
            prim->blendMode = 8;
            prim = prim->next;
        }
        break;

    case SUBWPNCONT_IDLE: // Spawn Liquid bubbles
        if (!(g_blinkTimer & 0xF)) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x3C, self, newEntity);
                rnd = (Random() & 0x18) - 12;
                newEntity->posX.i.hi += rnd;
                newEntity->posY.i.hi -= 30;
                newEntity->subId = Random() & 3;
                if (newEntity->subId == 0) {
                    absRnd = ABS(rnd);
                    if (absRnd >= 9) {
                        newEntity->subId = 1;
                    }
                }
                newEntity->zPriority = self->zPriority - 1;
            }
        }

        if (self->unk48 != 0) { // container got hit!
            self->step++;
        }
        break;

    case SUBWPNCONT_BREAK: // Break container into pieces
        // Spawn falling glass pieces
        glassPieceTBL = D_80182584;
        i = 0;
        g_api.FreePrimitives(self->firstPolygonIndex);
        self->flags &= ~FLAG_FREE_POLYGONS;
        g_api.PlaySfx(NA_SE_EV_GLASS_BREAK);
        while (i < ENTITY_SUBWPNCONT_DEBRIS_COUNT) {
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x3A, self, newEntity);
                newEntity->posX.i.hi += glassPieceTBL->posX;
                newEntity->posY.i.hi += glassPieceTBL->posY;
                newEntity->unk84.S16.unk0 = glassPieceTBL->posX;
                newEntity->subId = glassPieceTBL->subId;
                newEntity->facing = glassPieceTBL->facing;
                newEntity->unk84.S16.unk2 = self->subId;
            }
            glassPieceTBL++;
            i++;
        }

        for (i = 0; i < 96; i++) { // Spawn falling liquid
            newEntity = AllocEntity(&g_EntityArray[UNK_ENTITY_51],
                                    &g_EntityArray[UNK_ENTITY_100]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(0x3B, self, newEntity);
                rndPosX = (Random() & 0x1F) - 16;
                rndPosY = -(Random() & 0x3F) - 16;
                newEntity->posX.i.hi += rndPosX;
                newEntity->posY.i.hi += rndPosY;
                newEntity->unk1E = ratan2(rndPosY, rndPosX);
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        func_801C29B0(NA_SE_EV_VASE_BREAK);
        self->unk3C = 0;
        self->animCurFrame = 2;
        self->step++;
        break;

    case SUBWPNCONT_DEBUG:
        /**
         * Debug: Press SQUARE / CIRCLE on the second controller
         * to advance/rewind current animation frame
         */
        FntPrint(D_801B08C8, self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->subId == 0) {
                newEntity->animCurFrame++;
                self->subId |= 1;
            } else {
                break;
            }
        } else {
            self->subId = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->unk2E == 0) {
                newEntity->animCurFrame--;
                self->unk2E |= 1;
                break;
            }
        } else {
            self->unk2E = 0;
        }
        break;
    }
}

void func_801C7538(Entity* entity) {
    s32 new_var;
    s16 var_v0;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180CF4);
        entity->unk19 = 4;
        entity->animCurFrame = entity->subId;
        entity->palette += entity->unk84.S16.unk2;
        entity->accelerationX = entity->unk84.S16.unk0 << 12;
        entity->accelerationX += 0x8000 - (Random() << 8);
        entity->accelerationY -= (Random() & 0x1F) << 12;
        break;

    case 1:
        MoveEntity();
        entity->accelerationY += 0x2000;

        if (entity->accelerationX != 0) {
            if (entity->facing == 0) {
                new_var = (u16)entity->unk1E - 16;
                var_v0 = new_var;
            } else {
                var_v0 = entity->unk1E + 16;
            }
        } else if (entity->facing != 0) {
            var_v0 = entity->unk1E - 16;
        } else {
            var_v0 = entity->unk1E + 16;
        }

        entity->unk1E = var_v0;
        break;
    }
}

void func_801C7654(Entity* entity) {
    Collider res;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180BE0);
        entity->animSet = 2;
        entity->palette = 0x816D;
        entity->blendMode = 0x70;
        entity->accelerationX = rcos(entity->unk1E) * 0x10;
        entity->accelerationY = rsin(entity->unk1E) * 0x10;
        break;

    case 1:
        AnimateEntity(&D_801825F0, entity);
        MoveEntity();
        entity->accelerationY += 0x2000;

        g_api.CheckCollision(entity->posX.i.hi, entity->posY.i.hi + 8,
                             &res.unk0, 0);

        if (res.unk0 & 1) {
            entity->unk19 = 2;
            entity->unk1C = 0x100;
            entity->accelerationY = 0x4000;
            entity->accelerationX *= 8;
            entity->step++;
        }
        break;

    case 2:
        MoveEntity();
        entity->unk1C -= 8;
        if (!(entity->unk1C << 0x10)) {
            DestroyEntity(entity);
        }
        break;
    }
}

void func_801C77B8(Entity* entity) {
    s16 temp_v1_2;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180CF4);
        entity->unk19 = 3;
        entity->unk1C = 0x100;
        entity->unk1A = 0x100;
        entity->accelerationX = 0;
        entity->animCurFrame = entity->subId + 8;
        entity->accelerationY = D_80182600[entity->subId];
        break;

    case 1:
        MoveEntity();
        temp_v1_2 = entity->unk1C - 8;
        entity->accelerationY -= 0x400;
        entity->unk1C = temp_v1_2;
        entity->unk1A = temp_v1_2;

        if ((temp_v1_2 << 0x10) == 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

void func_801C7884(Entity* entity) {
    u16 subId = entity->subId;

    switch (entity->step) {
    case 0:
        InitializeEntity(&D_80180BD4);
        entity->unk3C = 0;

    case 1:
        MoveEntity();
        AnimateEntity(D_80181D3C[subId], entity);

        entity->accelerationY = rsin(entity->unk1E) * 2;
        entity->unk1E += 0x20;

        if (entity[-1].step != 1) {
            entity->objectId = ENTITY_PRICE_DROP;
            entity->pfnUpdate = EntityPrizeDrop;
            entity->animFrameDuration = 0;
            entity->animFrameIdx = 0;
            entity->step = 0;
            entity->unk3C = 1;
        }
    }
}

// DECOMP_ME_WIP EntityBloodSkeleton https://decomp.me/scratch/rZ64F
// instruction reorder, functionally equivalent, tested in-game.
// switch case rodata needs a file split.
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/4672C", EntityBloodSkeleton);
#else
extern u16 D_80180C40[];
extern u8 D_80182610;
extern s16 D_80182624[];
extern u8 D_80182638;
extern u8 D_80182654;
extern u8 D_80182670;
extern s32 D_80182694;
extern s32 D_801826AC;
extern s32* D_8003C808;

void EntityBloodSkeleton(Entity* self) {
    const char* animation;

    if ((self->flags & 0x100) && (self->step < 3)) {
        func_801C29B0(0x6CB);
        self->unk3C = 0;
        func_801BD52C(3);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180C40);
        self->facing = (u32)Random() % 2;
        self->animCurFrame = 1;
        self->flags &= 0x1FFFFFFF;
        self->palette += self->subId;
        break;

    case 1:
        if (func_801BCCFC(&D_80182694) % 2) {
            self->unk2E = 0;
            self->step++;
        }
        break;

    case 2:
        if (self->animFrameDuration == 0) {
            if (self->facing != 0) {
                self->posX.i.hi += D_80182624[self->animFrameIdx];
            } else {
                self->posX.i.hi -= D_80182624[self->animFrameIdx];
            }
        }

        if ((AnimateEntity(&D_80182610, self) == 0) &&
            (func_801BCC28() < 0x30) && (Random() % 4) == 0) {
            self->facing = func_801BCC5C() % 2 == 0;
        }
        /*
         * The need for the cast may indicate func_801C070C is in the same file.
         */
        if ((u8)func_801C070C(&D_801826AC, self->facing) != 2) {
            self->facing ^= 1;
        }
        break;

    case 3:
        if (AnimateEntity(&D_80182638, self) == 0) {
            self->unk80.modeS16.unk0 = 0xF0;
            self->flags &= ~0x100;
            if (self->subId != 0) {
                self->unk80.modeS16.unk0 = 4;
            }
            func_801BD52C(4);
        }
        break;

    case 4:
        switch (self->unk2E) {
        case 0:
            if (--self->unk80.modeS16.unk0 == 0) {
                self->unk1E = 0;
                self->unk19 |= 4;
                func_801C29B0(0x6CC);
                self->unk2E++;
                return;
            }
            break;

        case 1:
            if ((g_blinkTimer % 3) == 0) {
                self->unk80.modeS16.unk0++;
                if (self->unk80.modeS16.unk0 % 2 != 0) {
                    self->unk1E = 0x10;
                } else {
                    self->unk1E = -0x10;
                }
            }

            if (self->unk80.modeS16.unk0 >= 9) {
                self->unk19 = 0;
                self->unk1E = 0;
                self->unk2E++;
            }
            break;

        case 2:
            if (self->subId == 0) {
                animation = &D_80182654;
            } else {
                animation = &D_80182670;
            }

            if (AnimateEntity(animation, self) == 0) {
                self->hitPoints = 0;
                self->unk3C = 3;
                self->flags = D_8003C808[0x2c5] & 0x1FFFFFFF;
                func_801BD52C(2);
            }
        }
        break;
    }
}
#endif

s32 func_801C7CF0(Entity* e) {
    s16 diff;

    diff = PLAYER.posX.i.hi - e->posX.i.hi;
    diff = ABS(diff);

    if (diff >= 25) {
        diff = 0;
    } else {
        diff = PLAYER.posY.i.hi - e->posY.i.hi;
        diff = ABS(diff);
        diff = diff < 33;
    }

    return diff;
}

// sealed door that displays "Magically Sealed" prompt
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/4672C", EntityMagicallySealedDoor);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/4672C", func_801C8ADC);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/4672C", EntityStageNamePopup);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/4672C", func_801C9930);

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/4672C", func_801C9D18);

POLY_GT4* func_801C9E68(POLY_GT4* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = (POLY_GT4*)poly->tag;
        } else {
            return poly;
        }
    }
    return NULL;
}

Primitive* func_801C9E98(Primitive* prim, u8 index) {
    if (prim) {
        s32 index_ = index;
    loop_2:
        if (prim->p3 == 0) {
            Primitive* var_v0 = NULL;
            Primitive* firstPrim = prim;
            s32 i = 1;
            if (i < index_) {
                do {
                    prim = prim->next;
                    if (!prim)
                        return NULL;
                } while (prim->p3 == 0 && ++i < index);
            }
            var_v0 = firstPrim;
            if (i == index_)
                return var_v0;
        }
        prim = prim->next;
        if (prim) {
            goto loop_2;
        }
    }
    return NULL;
}

POLY_GT4* func_801C9F14(POLY_GT4* startPoly, s32 count) {
    POLY_GT4* poly;
    s8 unk;
    s32 i;

    if (startPoly->p3) {
        startPoly->p3 = 0;
    } else {
        startPoly->p3 = 1;
    }

    poly = startPoly;
    for (i = 0; i < count; i++) {
        if (poly->p3) {
            poly->pad3 &= ~8;
            unk = 0;
        } else {
            poly->pad3 |= 8;
            unk = 1;
        }

        poly = (POLY_GT4*)poly->tag;
        if (poly == NULL)
            return NULL;
        poly->p3 = unk;
    }

    return poly;
}

void func_801C9F9C(POLY_GT4* poly) {
    poly->p1 = 0;
    poly->p2 = 0;
    poly->p3 = 0;
    ((POLY_GT4*)poly->tag)->x1 = 0;
    ((POLY_GT4*)poly->tag)->y1 = 0;
    ((POLY_GT4*)poly->tag)->y0 = 0;
    ((POLY_GT4*)poly->tag)->x0 = 0;
    ((POLY_GT4*)poly->tag)->clut = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->u0 = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->b1 = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->r1 = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->u1 = 0;
    ((POLY_GT4*)poly->tag)->tpage = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->r2 = 0;
    *(u16*)&((POLY_GT4*)poly->tag)->b2 = 0;
    ((POLY_GT4*)poly->tag)->u2 = 0;
    ((POLY_GT4*)poly->tag)->v2 = 0;
    ((POLY_GT4*)poly->tag)->r3 = 0;
    ((POLY_GT4*)poly->tag)->b3 = 0;
    ((POLY_GT4*)poly->tag)->x2 = 0;
    ((POLY_GT4*)poly->tag)->y2 = 0;
}

void func_801CA07C(POLY_GT4* poly) {
    func_801C9F9C(poly);
    poly->p3 = 8;
    ((POLY_GT4*)poly->tag)->p3 = 1;
    ((POLY_GT4*)poly->tag)->code = 2;
    ((POLY_GT4*)poly->tag)->pad3 = 0xA;
}

void func_801CA0D0(POLY_GT4* poly) {
    poly->p3 = 0;
    poly->pad3 = 8;
    ((POLY_GT4*)poly->tag)->p3 = 0;
    ((POLY_GT4*)poly->tag)->code = 4;
    ((POLY_GT4*)poly->tag)->pad3 = 8;
}

//! FAKE
s32 func_801CA0FC(s32 arg0, u8 arg1) {
    s32 var_v0;
    s32 ret = 0;
    s32 j = arg0 + 4;
    u8* var_v1;
    s32 i;

    for (i = 0; i < 4; i++, j += 12) {
        var_v1 = (u8*)j;
        do {
            var_v0 = *var_v1 - arg1;

            if (var_v0 < 0) {
                var_v0 = 0;
            } else {
                ret |= 1;
            }

            *var_v1 = var_v0;
            var_v1++;
        } while ((s32)var_v1 < (s32)j + 3);
    }

    return ret;
}

// particle effect that spawns life up item
// Unique
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/4672C", EntityLifeUpSpawn);