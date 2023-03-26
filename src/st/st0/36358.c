#include "st0.h"

u16 D_80180580[];
u16 D_80181CDC[];
u8* D_80181D18[];
u16 D_80181D74[];

// if self->subId & 0x8000 then the item will not disappear
// self->unk80.modeS8.unk0: frames left before the prize disappear
void EntityPrizeDrop(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 firstPrimIndex;
    s16 var_a2;
    u16 itemId;
    s16 temp_a0;

    itemId = self->subId & 0x7FFF;
    if (self->step != 0) {
        AnimateEntity(D_80181D18[itemId], self);
        if (self->step && self->step < 5 && self->unk48 != 0) {
            self->step = 5;
        }
    }
    self->palette = 0x100;
    if ((u8)self->unk6D >= 0x18 && !(D_8003C8C4 & 2) && self->subId != 1) {
        self->palette = 0x815F;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180580);
        self->zPriority = g_zEntityCenter.S16.unk0 - 0x14;
        self->blendMode = 0;
        if (itemId >= 0x17) {
            self->subId = 0;
            itemId = 0;
        }
        if (itemId > 13 && itemId < 23 && itemId == D_80181CDC[D_80097BFC]) {
            self->subId = itemId = 1;
        }
        if (itemId == 0 || itemId == 2) {
            self->hitboxWidth = 4;
        }
        break;

    case 1:
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);
        if (collider.unk0 & 7) {
            DestroyEntity(self);
        } else {
            self->step++;
        }
        if (itemId == 0) {
            self->unk84.unk = -0x10000;
            self->unk88.S16.unk0 = 0x800;
        }
        break;

    case 2:
        if (self->accelerationX < 0) {
            g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi - 7,
                                 &collider, 0);
            if (collider.unk0 & 5) {
                self->accelerationY = 0;
            }
        }
        MoveEntity();
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi + 7, &collider,
                             0);
        if (itemId != 0) {
            if (collider.unk0 & 5 && self->accelerationY > 0) {
                self->accelerationX = 0;
                self->accelerationY = 0;
                self->posY.i.hi += LOH(collider.unk18);
                self->unk80.modeS8.unk0 = 0xF0;
                self->step++;
            } else {
                FallEntity();
            }
            func_801B5A98(D_80181D74, 2);
            return;
        }
        if (collider.unk0 & 5) {
            self->posY.i.hi += LOH(collider.unk18);
            self->unk80.modeS8.unk0 = 0x60;
            self->step++;
        } else {
            func_801B5EC8();
        }
        break;

    case 3:
        func_801B5F4C(itemId);
        if (!(self->subId & 0x8000) && --self->unk80.modeS8.unk0 == 0) {
            self->unk80.modeS8.unk0 = itemId == 0 ? 0x40 : 0x50;
            self->step++;
        }
        break;

    case 4:
        func_801B5F4C(itemId);
        if (--self->unk80.modeS8.unk0) {
            if (self->unk80.modeS8.unk0 & 2) {
                self->animCurFrame = 0;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        break;

    case 5:
        if (itemId == 0 || itemId == 1) {
            CollectHeart(itemId);
        } else if (itemId < 12) {
            CollectGold(itemId);
        } else if (itemId < 14) {
            CollectDummy();
        } else if (itemId < 23) {
            CollectSubweapon(itemId);
        } else {
            DestroyEntity(self);
            return;
        }
        break;

    case 7:
        switch (self->unk2E) {
        case 0:
            self->animCurFrame = 0;
            if (itemId > 13 && itemId < 23) {
                if (itemId == D_80181CDC[D_80097BFC]) {
                    self->subId = itemId = 1;
                }
            }
            firstPrimIndex = g_api.AllocPrimitives(4, 1);
            if (firstPrimIndex != -1) {
                self->firstPolygonIndex = firstPrimIndex;
                self->flags |= 0x800000;
                prim = &g_PrimBuf[firstPrimIndex];
                prim->tpage = 0x1A;
                prim->clut = 0x170;
                prim->u0 = prim->u2 = 0;
                prim->v0 = prim->v1 = 0;
                prim->u1 = prim->u3 = 0x20;
                prim->v2 = prim->v3 = 0x20;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0x80;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                prim->blendMode = 8;
                prim->priority = self->zPriority + 1;
                self->unk2E++;
            }
            break;
        case 1:
            MoveEntity();
            g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi + 7,
                                 &collider, 0);
            if (collider.unk0 & 5 && self->accelerationY > 0) {
                self->accelerationX = 0;
                self->accelerationY = 0;
                self->posY.i.hi += LOH(collider.unk18);
                self->unk2E++;
            } else {
                FallEntity();
            }
            func_801B5A98(D_80181D74, 2);
            self->animCurFrame = 0;
            if (self->unk88.S16.unk2 != 0) {
                self->unk88.S16.unk2--;
            } else {
                prim = &g_PrimBuf[self->firstPolygonIndex];
                prim->x0 = prim->x2 = self->posX.i.hi - 1;
                prim->x1 = prim->x3 = self->posX.i.hi + 1;
                prim->y0 = prim->y1 = self->posY.i.hi - 1;
                prim->y2 = prim->y3 = self->posY.i.hi + 1;
                prim->blendMode = 0x37;
            }
            break;

        case 2:
            func_801B5F4C(itemId);
            prim = &g_PrimBuf[self->firstPolygonIndex];
            self->unk88.S16.unk2++;
            if (self->unk88.S16.unk2 < 0x11) {
                var_a2 = self->unk88.S16.unk2;
                self->animCurFrame = 0;
            } else {
                var_a2 = 0x20 - self->unk88.S16.unk2;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->r3 - 8;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = prim->g3 - 8;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->b3 - 8;
            }
            prim->x0 = prim->x2 = self->posX.i.hi - var_a2;
            prim->x1 = prim->x3 = self->posX.i.hi + var_a2;
            prim->y0 = prim->y1 = self->posY.i.hi - var_a2;
            prim->y2 = prim->y3 = self->posY.i.hi + var_a2;
            if (self->unk88.S16.unk2 == 0x20) {
                g_api.FreePrimitives(self->firstPolygonIndex);
                self->unk80.modeS8.unk0 = 0xD0;
                self->step = 3;
                self->unk2E = 0;
                self->flags &= ~0x800000;
            }
            break;
        }
        break;
    }
}
// #endif

void EntityExplosion(Entity* entity) {
    if (entity->step == 0) {
        u32 zPriority;

        InitializeEntity(D_8018058C);
        entity->animSet = 2;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->blendMode = 0x30;

        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        zPriority = entity->subId & 0xFF00;
        if (zPriority != 0) {
            entity->zPriority = zPriority >> 8;
        }

        entity->subId = entity->subId & 0xF;
        entity->accelerationY = D_80181D7C[entity->subId];
    } else {
        entity->posY.val += entity->accelerationY;
        if (!AnimateEntity(D_80181E28[entity->subId], entity)) {
            DestroyEntity(entity);
        }
    }
}

void func_801B6C5C(Entity* entity) {
    if (entity->step != 0) {
        if (entity->posY.i.hi >= 0xF1) {
            DestroyEntity(entity);
            return;
        }
        FallEntity();
        MoveEntity();
        return;
    }

    InitializeEntity(D_80180574);
    entity->animCurFrame = entity->unk7C.U8.unk0;
    entity->accelerationX = D_80181E3C[entity->unk80.modeS8.unk0 * 2];
    entity->accelerationY = D_80181E3E[entity->unk80.modeS8.unk0 * 2];

    if (entity->subId != 0) {
        entity->zPriority -= 1;
    }
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", EntityEquipItemDrop);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", func_801B7308);

u8 func_801B7B0C(s16* arg0, u8 facing) {
    u8 ret = 0;
    Collider res;
    s16 posX, posY;

    while (*arg0 != 0xFF) {
        ret <<= 1;

        posX = facing ? (g_CurrentEntity->posX.i.hi + *arg0++)
                      : (g_CurrentEntity->posX.i.hi - *arg0++);
        posY = g_CurrentEntity->posY.i.hi + *arg0++;

        g_api.CheckCollision(posX, posY, &res, 0);

        if (res.unk0 & 1) {
            ret |= 1;
        }
    }

    return ret;
}

void func_801B7BFC(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805A4);
        entity->unk8C.modeU16.unk0 = entity->unk80.entityPtr->objectId;
    case 1:
        if (entity->unk7C.U8.unk0++ >= 5) {
            Entity* newEntity =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(ENTITY_EXPLOSION, entity, newEntity);
                newEntity->objectId = ENTITY_EXPLOSION;
                newEntity->pfnUpdate = EntityExplosion;
                newEntity->subId = entity->subId;
            }
            entity->unk7C.U8.unk0 = 0;
        }
        entity->posX.i.hi = entity->unk80.entityPtr->posX.i.hi;
        entity->posY.i.hi = entity->unk80.entityPtr->posY.i.hi;
        if (entity->unk80.entityPtr->objectId != entity->unk8C.modeU16.unk0) {
            DestroyEntity(entity);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", func_801B7D0C);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", func_801B7E3C);

void func_801B7F24(Entity* entity) {
    if (entity->step == 0) {
        entity->accelerationY = D_80181ED8[entity->unk94];
        entity->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = 2;
        entity->animCurFrame = D_80181EF0[entity->subId];
        entity->blendMode = 0x10;
        entity->step++;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= entity->accelerationY;

        if (!(entity->animFrameDuration & 1)) {
            entity->animCurFrame++;
        }

        if (D_80181EF4[entity->subId] < (s32)entity->animFrameDuration) {
            DestroyEntity(entity);
        }
    }
}

void func_801B8014(Entity* entity) {
    u16 temp_v0;
    u32 temp2;

    if (entity->step == 0) {
        entity->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = 5;
        entity->animCurFrame = 1;
        entity->blendMode = 0x10;
        entity->unk19 = 3;
        temp_v0 = D_80181EB0[entity->subId];
        entity->unk1A = temp_v0;
        entity->unk1C = temp_v0;
        temp2 = D_80181EC0[entity->subId];
        entity->step += 1;
        entity->accelerationY = temp2;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= entity->accelerationY;

        if (!(entity->animFrameDuration & 1)) {
            entity->animCurFrame++;
        }

        if (entity->animFrameDuration >= 0x25) {
            DestroyEntity(entity);
        }
    }
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", func_801B8108);

bool func_801B8338(Unkstruct6* unk) {
    Collider res;

    FallEntity();
    g_CurrentEntity->posX.val += g_CurrentEntity->accelerationX;
    g_CurrentEntity->posY.val += g_CurrentEntity->accelerationY;

    if (g_CurrentEntity->accelerationY >= 0) {
        s16 posX = g_CurrentEntity->posX.i.hi;
        s16 posY = g_CurrentEntity->posY.i.hi;
        posX += unk->x;
        posY += unk->y;
        g_api.CheckCollision(posX, posY, &res, 0);
        if (res.unk0 & 1) {
            g_CurrentEntity->posY.i.hi += LOH(res.unk18);
            g_CurrentEntity->accelerationY =
                -g_CurrentEntity->accelerationY / 2;
            if (g_CurrentEntity->accelerationY > -0x10000) {
                return true;
            }
        }
    }
    return false;
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", func_801B8434);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", EntityIntenseExplosion);

void func_801B8AB4(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_8018058C);
        entity->unk6C = 0xF0;
        entity->unk1A = 0x01A0;
        entity->unk1C = 0x01A0;
        entity->animSet = 8;
        entity->animCurFrame = 1;
        entity->zPriority += 16;
        if (entity->subId) {
            entity->palette = entity->subId;
        } else {
            entity->palette = 0x8160;
        }

        entity->step++;
    } else {
        MoveEntity();
        if (!AnimateEntity(D_80181F04, entity)) {
            DestroyEntity(entity);
        }
    }
}

void func_801B8B80(u16 objectId, Entity* source, Entity* entity) {
    u16 palette;

    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
    entity->unk5A = source->unk5A;
    entity->zPriority = source->zPriority;
    entity->animSet = source->animSet;
    entity->flags = 0x1002000 | FLAG_UNK_04000000 | FLAG_UNK_08000000 |
                    FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                    FLAG_DESTROY_IF_OUT_OF_CAMERA;

    palette = source->palette;
    entity->palette = palette & 0x8000 ? source->unk6A : palette;
}

void func_801B8C48(void) {
    s32 temp_s3;
    s8 temp_s4;
    Entity* entity;
    s32 i;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, D_8007D858 + MaxEntityCount);
        if (entity != NULL) {
            CreateEntityFromEntity(ENTITY_EXPLOSION, g_CurrentEntity, entity);
            entity->unk84.U8.unk1 = 6 - i;
            entity->unk80.modeS16.unk0 = temp_s3;
            entity->unk84.U8.unk0 = temp_s4;
        }
    }
}

void func_801B8D00(Entity* self) {
    s32 accelerationX;
    s32 accelerationY;
    s32 temp;

    if (self->step == 0) {
        InitializeEntity(D_8018058C);
        self->animSet = 2;
        self->palette = 0x81B6;
        self->unk6C = 0x70;
        self->zPriority = 192;
        self->unk19 |= 0xC;
        self->blendMode |= 0x30;

        switch (self->unk84.U8.unk0) {
        case 1:
            if (self->unk84.U8.unk1 >= 4) {
                self->unk84.U8.unk1 += 253;
                self->unk80.modeS16.unk0 -= 0x800;
            }
            break;

        case 2:
            self->unk80.modeS16.unk0 += self->unk84.U8.unk1 * 192;
            break;
        }

        self->unk1E = self->unk80.modeS16.unk0 &= 0xFFF;
        temp = (self->unk84.U8.unk1 * 320) / 24;
        self->accelerationX = temp * rsin(self->unk80.modeS16.unk0);
        self->accelerationY = -(temp * rcos(self->unk80.modeS16.unk0));
    }

    if (self->animFrameIdx >= 13) {
        accelerationX = self->accelerationX;
        if (accelerationX < 0) {
            accelerationX += 3;
        }

        accelerationY = self->accelerationY;
        self->accelerationX = (accelerationX >> 2) * 3;
        if (accelerationY < 0) {
            accelerationY += 3;
        }
        self->accelerationY = (accelerationY >> 2) * 3;
    }

    MoveEntity();

    if (AnimateEntity(D_80181DA4, self) == 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", func_801B8ED8);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", func_801B94B8);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", func_801B9BB8);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", func_801B9DB0);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", EntityAbsorbOrb);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", EntityEnemyBlood);

extern ObjInit2 D_80181FE8[];
void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_80181FE8[entity->subId];

    if (entity->step == 0) {
        InitializeEntity(D_801805BC);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.s;
        entity->palette = objInit->palette;
        entity->unk19 = objInit->unk8;
        entity->blendMode = objInit->blendMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->subId >= 5) {
            entity->unk1E = 0x800;
            entity->unk19 |= 4;
        }
    }
    AnimateEntity(objInit->unk10, entity);
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", func_801BA7D8);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", EntityClouds);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", EntityClockTower3D);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", EntityCutscenePhotograph);

#ifndef NON_MATCHING // TODO fix 'li' opcode with ASPATCH
INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", EntityCutscenePhotographFire);
#else
extern u16 D_801805D4[];
extern u8 D_801824CC[];

void EntityCutscenePhotographFire(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805D4);
        entity->animSet = 0x8007;
        entity->unk5A = 0x57;
        entity->palette = 0x8285;
        entity->unk19 = 8;
        entity->unk6C = 0x40;
        entity->flags &= ~FLAG_UNK_08000000;
        if (entity->subId) {
            entity->unk6C = 0x10;
            entity->zPriority = 0x1FB;
            entity->blendMode = 0x50;
        } else {
            entity->zPriority = 0x1FE;
            entity->blendMode = 0x30;
        }
    case 1:
        entity->posY.val -= 0x10000;
        if (AnimateEntity(D_801824CC, entity) == 0) {
            DestroyEntity(entity);
        }
        break;
    }
}
#endif

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", func_801BC5C0);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", func_801BD0C0);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", func_801BD4A8);

POLY_GT4* func_801BD5F8(POLY_GT4* poly) {
    while (poly) {
        if (poly->p3 == 0)
            return poly;
        poly = (POLY_GT4*)poly->tag;
    }
    return NULL;
}

POLY_GT4* func_801BD628(POLY_GT4* poly, u8 index) {
    if (poly) {
        s32 index_ = index;
    loop_2:
        if (poly->p3 == 0) {
            POLY_GT4* var_v0 = NULL;
            POLY_GT4* firstPoly = poly;
            s32 i = 1;
            if (i < index_) {
                do {
                    poly = (POLY_GT4*)poly->tag;
                    if (!poly)
                        return NULL;
                } while (poly->p3 == 0 && ++i < index);
            }
            var_v0 = firstPoly;
            if (i == index_)
                return var_v0;
        }
        poly = (POLY_GT4*)poly->tag;
        if (poly) {
            goto loop_2;
        }
    }
    return NULL;
}

POLY_GT4* func_801BD6A4(POLY_GT4* startPoly, s32 count) {
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
        if (poly == 0)
            return 0;
        poly->p3 = unk;
    }

    return poly;
}

void func_801BD72C(POLY_GT4* arg0) {
    arg0->p1 = 0;
    arg0->p2 = 0;
    arg0->p3 = 0;
    ((POLY_GT4*)arg0->tag)->x1 = 0;
    ((POLY_GT4*)arg0->tag)->y1 = 0;
    ((POLY_GT4*)arg0->tag)->y0 = 0;
    ((POLY_GT4*)arg0->tag)->x0 = 0;
    ((POLY_GT4*)arg0->tag)->clut = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->u0 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->b1 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->r1 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->u1 = 0;
    ((POLY_GT4*)arg0->tag)->tpage = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->r2 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->b2 = 0;
    ((POLY_GT4*)arg0->tag)->u2 = 0;
    ((POLY_GT4*)arg0->tag)->v2 = 0;
    ((POLY_GT4*)arg0->tag)->r3 = 0;
    ((POLY_GT4*)arg0->tag)->b3 = 0;
    ((POLY_GT4*)arg0->tag)->x2 = 0;
    ((POLY_GT4*)arg0->tag)->y2 = 0;
}

void func_801BD80C(POLY_GT4* arg0) {
    func_801BD72C(arg0);
    arg0->p3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 1;
    ((POLY_GT4*)arg0->tag)->code = 2;
    ((POLY_GT4*)arg0->tag)->pad3 = 0xA;
}

void func_801BD860(POLY_GT4* arg0) {
    arg0->p3 = 0;
    arg0->pad3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 0;
    ((POLY_GT4*)arg0->tag)->code = 4;
    ((POLY_GT4*)arg0->tag)->pad3 = 8;
}

s32 func_801BD88C(s32 arg0, u8 arg1) {
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

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", func_801BD8F0);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/36358", EntityBackgroundVortex);
