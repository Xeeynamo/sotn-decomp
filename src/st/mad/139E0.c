#include "mad.h"

extern u16 D_801804FC[];
extern u16 D_80180D4C[];
extern u8* D_80180DB0[];
extern u16 D_80180E10[];
void DestroyCurrentEntity();
void func_80192EF8(u16*, s32);
void func_801934D0(u32);
void CollectSubweapon();
extern void (*D_8003C7B4)(s32);
extern s16 (*D_8003C7B8)(s32 type, s32 count);
extern void (*D_8003C7BC)(s32 x, s32 y, Collider* res, s32 unk);

void EntityPrizeDrop(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 firstPrimIndex;
    s16 var_a2;
    u16 itemId;
    s16 temp_a0;

    itemId = self->subId & 0x7FFF;
    if (self->step != 0) {
        AnimateEntity(D_80180DB0[itemId], self);
        if (self->step && self->step < 5 && self->unk48 != 0) {
            self->step = 5;
        }
    }
    self->palette = 0;
    if ((u8)self->unk6D >= 0x18 && !(D_8003C8C4 & 2) && self->subId != 1) {
        self->palette = 0x815F;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_801804FC);
        self->zPriority = g_zEntityCenter.S16.unk0 - 0x14;
        self->blendMode = 0;
        if (itemId >= 0x18) {
            self->subId = 0;
            itemId = 0;
        }
        if (itemId > 13 && itemId < 23 &&
            itemId == D_80180D4C[g_Status.subWeapon]) {
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
            self->ext.generic.unk84.unk = -0x10000;
            self->ext.generic.unk88.S16.unk0 = 0x800;
        }
        break;

    case 2:
        if (self->accelerationY < 0) {
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
                self->posY.i.hi += collider.unk18;
                self->ext.generic.unk80.modeS8.unk0 = 0xF0;
                self->step++;
            } else {
                FallEntity();
            }
            func_80192EF8(D_80180E10, 2);
            return;
        }
        if (collider.unk0 & 5) {
            self->posY.i.hi += collider.unk18;
            self->ext.generic.unk80.modeS8.unk0 = 0x60;
            self->step++;
        } else {
            func_8019344C();
        }
        break;

    case 3:
        func_801934D0(itemId);
        if (!(self->subId & 0x8000) &&
            --self->ext.generic.unk80.modeS8.unk0 == 0) {
            self->ext.generic.unk80.modeS8.unk0 = itemId == 0 ? 0x40 : 0x50;
            self->step++;
        }
        break;

    case 4:
        func_801934D0(itemId);
        if (--self->ext.generic.unk80.modeS8.unk0) {
            if (self->ext.generic.unk80.modeS8.unk0 & 2) {
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
        } else if (itemId == 12) {
            CollectHeartVessel();
        } else if (itemId < 14) {
            DestroyCurrentEntity();
        } else if (itemId < 23) {
            CollectSubweapon(itemId);
        } else if (itemId == 23) {
            CollectLifeVessel();
        } else {
            DestroyEntity(self);
            return;
        }
        break;

    case 7:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0;
            if (itemId > 13 && itemId < 23) {
                if (itemId == D_80180D4C[g_Status.subWeapon]) {
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
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi + 7,
                                 &collider, 0);
            if (collider.unk0 & 5 && self->accelerationY > 0) {
                self->accelerationX = 0;
                self->accelerationY = 0;
                self->posY.i.hi += collider.unk18;
                self->step_s++;
            } else {
                FallEntity();
            }
            func_80192EF8(D_80180E10, 2);
            self->animCurFrame = 0;
            if (self->ext.generic.unk88.S16.unk2 != 0) {
                self->ext.generic.unk88.S16.unk2--;
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
            func_801934D0(itemId);
            prim = &g_PrimBuf[self->firstPolygonIndex];
            self->ext.generic.unk88.S16.unk2++;
            if (self->ext.generic.unk88.S16.unk2 < 0x11) {
                var_a2 = self->ext.generic.unk88.S16.unk2;
                self->animCurFrame = 0;
            } else {
                var_a2 = 0x20 - self->ext.generic.unk88.S16.unk2;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->r3 - 8;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = prim->g3 - 8;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = prim->b3 - 8;
            }
            prim->x0 = prim->x2 = self->posX.i.hi - var_a2;
            prim->x1 = prim->x3 = self->posX.i.hi + var_a2;
            prim->y0 = prim->y1 = self->posY.i.hi - var_a2;
            prim->y2 = prim->y3 = self->posY.i.hi + var_a2;
            if (self->ext.generic.unk88.S16.unk2 == 0x20) {
                g_api.FreePrimitives(self->firstPolygonIndex);
                self->ext.generic.unk80.modeS8.unk0 = 0xD0;
                self->step = 3;
                self->step_s = 0;
                self->flags &= ~0x800000;
            }
            break;
        }
        break;
    }
}

void EntityExplosion(Entity* entity) {
    u32 temp_v0;

    if (entity->step == 0) {
        InitializeEntity(D_80180508);
        entity->animSet = 2;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->blendMode = 0x30;

        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        temp_v0 = entity->subId & 0xFF00;
        if (temp_v0) {
            entity->zPriority = temp_v0 >> 8;
        }

        entity->subId = entity->subId & 0xF;
        entity->accelerationY = D_80180E18[entity->subId];
        return;
    }

    entity->posY.val += entity->accelerationY;
    if (!AnimateEntity((const u8*)D_80180EC4[entity->subId], entity)) {
        DestroyEntity(entity);
    }
}

void func_80194314(Entity* entity) {
    if (entity->step != 0) {
        if (entity->posY.i.hi >= 0xF1) {
            DestroyEntity(entity);
            return;
        }
        FallEntity();
        MoveEntity();
        return;
    }

    InitializeEntity(g_eBreakableInit);
    entity->animCurFrame = entity->ext.generic.unk7C.U8.unk0;
    entity->accelerationX =
        D_80180ED8[entity->ext.generic.unk80.modeS8.unk0 * 2];
    entity->accelerationY =
        D_80180EDA[entity->ext.generic.unk80.modeS8.unk0 * 2];

    if (entity->subId != 0) {
        entity->zPriority -= 1;
    }
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", EntityEquipItemDrop);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", EntityRelicOrb);

// v1 -> a0 reg swap
// branching
// signature conflict
// DECOMP_ME_WIP EntityHeartDrop https://decomp.me/scratch/h3CVU
#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", EntityHeartDrop);
#else
void EntityHeartDrop(Entity* entity, u32 arg1) {
    u16 temp_v0_2;
    u16 temp_v1;
    u16 var_v1;
    u32 temp_a0;

    if (entity->step == 0) {
        temp_v0_2 = entity->subId;
        temp_a0 = temp_v0_2 & 0xFFFF;
        var_v1 = temp_v0_2;
        entity->ext.generic.unkB4 = var_v1;

        if ((D_8003BEE8[temp_a0 >> 3] >> (var_v1 & 7)) & 1) {
            DestroyEntity(entity);
            return;
        }

        var_v1 = D_80180F5C[temp_a0];

        if (var_v1 < 0x80) {
            entity->ext.generic.uunkB8.unkFuncB8 = EntityPrizeDrop;
        } else {
            entity->ext.generic.uunkB8.unkFuncB8 = EntityEquipItemDrop;
            var_v1 -= 0x80;
        }

        entity->subId = var_v1 + 0x8000;
        return;
    }

    temp_v1 = entity->ext.generic.unkB4;

    if (entity->step < 5) {
        arg1 = temp_v1 / 8;
        if (entity->unk48 != 0) {
            D_8003BEE8[arg1] |= (1 << (temp_v1 & 7));
            entity->step = 5;
        }
    }
    entity->ext.generic.uunkB8.unkFuncB8(entity, arg1, entity);
}
#endif

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_8019563C);

void func_8019572C(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_8018052C);
        entity->ext.generic.unk8C.modeU16.unk0 =
            entity->ext.generic.unk80.entityPtr->objectId;
    case 1:
        if (entity->ext.generic.unk7C.U8.unk0++ >= 5) {
            Entity* newEntity =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, entity, newEntity);
                newEntity->objectId = E_EXPLOSION;
                newEntity->pfnUpdate = EntityExplosion;
                newEntity->subId = entity->subId;
            }
            entity->ext.generic.unk7C.U8.unk0 = 0;
        }
        entity->posX.i.hi = entity->ext.generic.unk80.entityPtr->posX.i.hi;
        entity->posY.i.hi = entity->ext.generic.unk80.entityPtr->posY.i.hi;
        if (entity->ext.generic.unk80.entityPtr->objectId !=
            entity->ext.generic.unk8C.modeU16.unk0) {
            DestroyEntity(entity);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_8019583C);

// DECOMP_ME_WIP func_8019596C https://decomp.me/scratch/3IMus
INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_8019596C);

void func_80195A54(Entity* entity) {
    if (entity->step == 0) {
        entity->accelerationY = D_80180FE4[entity->ext.generic.unk94];
        entity->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = 2;
        entity->animCurFrame = D_80180FFC[entity->subId];
        entity->blendMode = 0x10;
        entity->step++;
        return;
    }

    entity->animFrameDuration++;
    entity->posY.val -= entity->accelerationY;

    if (!(entity->animFrameDuration & 1)) {
        entity->animCurFrame++;
    }

    if (D_80181000[entity->subId] < (s32)entity->animFrameDuration) {
        DestroyEntity(entity);
    }
}

void func_80195B44(Entity* entity) {
    u16 temp_v0;

    if (entity->step == 0) {
        entity->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = 5;
        entity->animCurFrame = 1;
        entity->blendMode = 0x10;
        entity->unk19 = 3;
        temp_v0 = D_80180FBC[entity->subId];
        entity->unk1A = temp_v0;
        entity->unk1C = temp_v0;
        entity->accelerationY = D_80180FCC[entity->subId];
        entity->step++;
        return;
    }

    entity->animFrameDuration++;
    entity->posY.val -= entity->accelerationY;

    if (!(entity->animFrameDuration & 1)) {
        entity->animCurFrame++;
    }

    if (entity->animFrameDuration >= 37) {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_80195C38);

bool func_80195E68(Unkstruct6* unk) {
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
            g_CurrentEntity->posY.i.hi += res.unk18;
            g_CurrentEntity->accelerationY =
                -g_CurrentEntity->accelerationY / 2;
            if (g_CurrentEntity->accelerationY > -0x10000) {
                return true;
            }
        }
    }
    return false;
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_80195F64);

void EntityIntenseExplosion(Entity* entity) {
    u32 zPriority;

    if (entity->step == 0) {
        InitializeEntity(D_80180508);
        entity->palette = 0x8170;
        entity->animSet = 5;
        entity->animCurFrame = 1;
        entity->blendMode = 0x30;
        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        zPriority = entity->subId & 0xFF00;
        if (zPriority != 0) {
            entity->zPriority = zPriority >> 8;
        }

        entity->zPriority += 8;
        return;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= 0x4000;

        if (!(entity->animFrameDuration & 1)) {
            entity->animCurFrame++;
        }

        if (entity->animFrameDuration >= 0x25) {
            DestroyEntity(entity);
        }
    }
}

void func_801965E4(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_80180508);
        entity->unk6C = 0xF0;
        entity->unk1A = 0x1A0;
        entity->unk1C = 0x1A0;
        entity->animSet = 8;
        entity->animCurFrame = 1;
        entity->zPriority += 0x10;

        if (entity->subId != 0) {
            entity->palette = entity->subId;
        } else {
            entity->palette = 0x8160;
        }

        entity->step++;
        return;
    }

    MoveEntity();

    if (!AnimateEntity(D_80181010, entity)) {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_801966B0);

void func_8019686C(u16 objectId, Entity* src, Entity* dst) {
    DestroyEntity(dst);
    dst->objectId = objectId;
    dst->pfnUpdate = PfnEntityUpdates[objectId];
    dst->posX.i.hi = src->posX.i.hi;
    dst->posY.i.hi = src->posY.i.hi;
    dst->unk5A = src->unk5A;
    dst->zPriority = src->zPriority;
    dst->animSet = src->animSet;
    dst->flags = 0x45002000 | FLAG_UNK_08000000 | FLAG_DESTROY_IF_OUT_OF_CAMERA;

    if (src->palette & 0x8000) {
        dst->palette = src->unk6A;
    } else {
        dst->palette = (s16)src->palette;
    }
}

// DECOMP_ME_WIP func_80196934 https://decomp.me/scratch/fA367 TODO: 0x80 entity
// member unconfirmed
void func_80196934(void) {
    Entity* entity;
    s16 temp_s3;
    s32 i;
    u8 temp_s4;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
        if (entity != NULL) {
            CreateEntityFromEntity(2, g_CurrentEntity, entity);
            entity->ext.generic.unk84.U8.unk1 = 6 - i;
            entity->ext.generic.unk80.modeS16.unk0 = temp_s3;
            entity->ext.generic.unk84.U8.unk0 = temp_s4;
        }
    }
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_801969EC);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_80196BC4);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_801971A4);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_801978A4);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_80197A9C);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_80197B94);

// TODO(sestren): Move external declarations to header file
extern u16 D_80181068[];
extern u16 D_80181078[];
extern u8 D_801810D8;
void EntityAbsorbOrb(Entity* self) {
    Primitive* prim;
    s32 firstPrimIndex;
    u16 *temp_d, temp_e;
    s32 temp_a, temp_b;
    u16 angle;

    switch (self->step) {
    case 0:
        firstPrimIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (firstPrimIndex == -1) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(D_801804FC);
        D_8008701E[firstPrimIndex * 0x1a] = 8;
        self->firstPolygonIndex = firstPrimIndex;
        self->animSet = 0;
        self->flags |= 0x800000;
        angle = func_80192AF0(self, &PLAYER);
        temp_a = self->posY.i.hi < 113;
        temp_b = temp_a ^ 1;
        if (self->posX.i.hi < PLAYER.posX.i.hi) {
            temp_b = temp_a;
        }
        if (temp_b & 0xFFFF) {
            self->ext.absorbOrb.angle = angle - D_80181068[Random() & 7];
        } else {
            angle += D_80181068[Random() & 7];
            self->ext.absorbOrb.angle = angle;
        }
        self->ext.absorbOrb.unk80 = 0x400;
        self->ext.absorbOrb.unk7E = 0;
        self->unk3C = 0;
        break;

    case 1:
        self->ext.absorbOrb.unk82++;
        if (self->ext.absorbOrb.unk82 == 16) {
            self->unk3C = 1;
        }
        if (self->unk48 != 0) {
            if (g_Player.unk56 == 0) {
                g_Player.unk56 = 1;
                g_Player.unk58 = 8;
            }
            DestroyEntity(self);
            return;
        }
        if (self->unk1A < 0x100) {
            self->unk1A = self->unk1C += 0x10;
        }
        if (self->ext.absorbOrb.unk7E < 0x200) {
            self->ext.absorbOrb.unk7E += 2;
        }
        if (self->ext.absorbOrb.unk80 < 0x800) {
            self->ext.absorbOrb.unk80 += 4;
        }
        self->ext.absorbOrb.angle = func_80192B70(
            self->ext.absorbOrb.unk7E, (u16)self->ext.absorbOrb.angle,
            0xffff & func_80192AF0(self, &PLAYER));
        func_80192A34(self->ext.absorbOrb.angle & 0xFFFF,
                      self->ext.absorbOrb.unk80);
        MoveEntity(self); // argument pass necessary to match
        prim = &g_PrimBuf[self->firstPolygonIndex];
        AnimateEntity(&D_801810D8, self);
        angle = (float)(u32)self; // !FAKE
        prim->tpage = 0x18;
        prim->clut = 0x194;
        temp_d = &D_80181078[(u16)((8 * (u16)self->animCurFrame) - 8)];
        prim->x0 = prim->x2 = self->posX.i.hi + *(temp_d++);
        prim->y0 = prim->y1 = self->posY.i.hi + *(temp_d++);
        prim->x1 = prim->x3 = prim->x0 + *(temp_d++);
        prim->y2 = prim->y3 = prim->y0 + *(temp_d++);
        prim->u0 = prim->u2 = *(temp_d++);
        prim->v0 = prim->v1 = *(temp_d++);
        prim->u1 = prim->u3 = *(temp_d++);
        prim->v2 = prim->v3 = *(temp_d++);
        prim->priority = self->zPriority;
        prim->blendMode = 0;
        break;
    }
}

void EntityEnemyBlood(Entity* self) {
    int fakeTemp; // !TODO: !FAKE
    Primitive* prim;
    s32 var_a0_2;
    u16 subId;
    s16 posX;
    s32 rnd;
    s32 i;

    switch (self->step) {
    case 0:
        i = g_api.func_800EDB58(17, 12);
        if (i != -1) {
            InitializeEntity(D_801804FC);
            prim = &g_PrimBuf[i];
            self->firstPolygonIndex = i;
            self->animSet = 0;
            subId = self->subId;
            self->unk3C = 1;
            self->ext.generic.unk7C.s = 48;
            self->hitboxHeight = 8;
            self->zPriority = 0xC0;
            self->hitboxWidth = 0;
            self->flags |= FLAG_FREE_POLYGONS;

            for (i = 12; i != 0;) {
                prim->x0 = self->posX.i.hi + ((Random() & (fakeTemp = 7)) - 5);
                rnd = (Random() & 7) - 5;
                prim->y0 = self->posY.i.hi + rnd;
                *(s32*)&prim->r1 = 0;
                *(s32*)&prim->x1 = 0;
                prim->u0 = 4;
                prim->v0 = 4;

                if (subId != 0) {
                    func_80192A34(0xCC0 + i * 64,
                                  ((Random() & 0xF) * 0x10) + 0x180);
                } else {
                    func_80192A34(0xB40 - i * 64,
                                  ((Random() & 0xF) * 0x10) + 0x180);
                }

                *(s32*)&prim->u1 = self->accelerationX;
                *(s32*)&prim->r2 = self->accelerationY;

                var_a0_2 = *(s32*)&prim->u1;
                if (var_a0_2 <= -1) {
                    var_a0_2 += 0x3F;
                }

                *(s32*)&prim->r3 = -(var_a0_2 >> 6);
                *(s32*)&prim->x3 = -(*(s32*)&prim->r2 / 48) + 0xC00;

                prim->x2 = prim->y2 = (Random() & 7) + 7;
                prim->r0 = 128;
                prim->b0 = 16;
                prim->g0 = 0;
                prim->priority = self->zPriority;
                prim->blendMode = 2;
                i--;
                if (i != 0) {
                    prim++;
                }
            }

            if (subId != 0) {
                self->accelerationX = 0x14000;
                self->ext.generic.unk80.modeS32 = -0x200;
            } else {
                self->accelerationX = -0x14000;
                self->ext.generic.unk80.modeS32 = 0x200;
            }
            self->accelerationY = 0;
            break;
        }
        DestroyEntity(self);
        break;

    case 1:
        if (!(--self->ext.generic.unk7C.u)) {
            DestroyEntity(self);
            break;
        }

        if (self->unk3C != 0) {
            if (g_Player.unk0C & 0x02000000) {
                posX = self->posX.i.hi;
                self->accelerationX += self->ext.generic.unk80.modeS32;

                MoveEntity(self); // argument pass necessary to match

                posX -= self->posX.i.hi;
                if (posX < 0) {
                    posX = -posX;
                }

                if (self->ext.generic.unk7C.u > 16) {
                    self->ext.generic.unk7E.modeU16 += posX;
                    self->hitboxWidth = self->ext.generic.unk7E.modeU16 / 2;
                    self->hitboxHeight =
                        (self->ext.generic.unk7E.modeU16 / 4) + 8;
                } else {
                    self->unk3C = 0;
                }

                if (self->unk48 != 0) {
                    if (g_Player.unk56 == 0) {
                        g_Player.unk56 = 1;
                        g_Player.unk58 = 8;
                        if (g_api.CheckEquipmentItemCount(0x3C, 4)) {
                            g_Player.unk58 *= 2;
                        }
                    }
                    g_Player.unk10++;
                    self->unk3C = 0;
                }
            } else {
                self->unk3C = 0;
            }
        }

        prim = &g_PrimBuf[self->firstPolygonIndex];
        for (i = 12; i != 0; i--, prim++) {
            *(u16*)&prim->b1 = prim->x0;
            prim->y1 = prim->y0;
            *(s32*)&prim->u1 += *(s32*)&prim->r3;
            *(s32*)&prim->r2 += *(s32*)&prim->x3;
            *(s32*)&prim->r1 += *(s32*)&prim->u1;
            *(s32*)&prim->x1 += *(s32*)&prim->r2;
            *(s16*)&prim->x0 = *(s16*)&prim->b1;
            prim->y0 = prim->y1;
            prim->x2--;

            if ((prim->x2 == 0) && (prim->u0 != 0)) {
                prim->v0--;
                prim->u0--;
                if (!(prim->u0 & 1)) {
                    prim->x0++;
                    prim->y0++;
                }
                prim->x2 = *(s32*)&prim->y2;
            }
        }
    }
}

void EntityRoomForeground(Entity* entity) {
    ObjInit2* obj = &D_801810F4[entity->subId];

    if (entity->step == 0) {
        InitializeEntity(D_80180544);
        entity->animSet = obj->animSet;
        entity->zPriority = obj->zPriority;
        entity->unk5A = obj->unk4.s;
        entity->palette = obj->palette;
        entity->unk19 = obj->unk8;
        entity->blendMode = obj->blendMode;
        if (obj->unkC != 0) {
            entity->flags = obj->unkC;
        }
    }
    AnimateEntity(obj->unk10, entity);
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_80198BC8);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_80198FA0);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_80199388);

POLY_GT4* func_801994D8(POLY_GT4* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = (POLY_GT4*)poly->tag;
        } else {
            return poly;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_80199508);

POLY_GT4* func_80199584(POLY_GT4* startPoly, s32 count) {
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

void func_8019960C(POLY_GT4* arg0) {
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

void func_801996EC(POLY_GT4* arg0) {
    func_8019960C(arg0);
    arg0->p3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 1;
    ((POLY_GT4*)arg0->tag)->code = 2;
    ((POLY_GT4*)arg0->tag)->pad3 = 0xA;
}

void func_80199740(POLY_GT4* arg0) {
    arg0->p3 = 0;
    arg0->pad3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 0;
    ((POLY_GT4*)arg0->tag)->code = 4;
    ((POLY_GT4*)arg0->tag)->pad3 = 8;
}

s32 func_8019976C(Unkstruct_80128BBC* arg0, u8 value) {
    u8 ret = 0;
    s32 i;
    s32 j;
    Unkstruct_80128BBC_Sub* temp = arg0->unk04;

    for (i = 0; i < 4; i++, temp++) {
        for (j = 0; j < 3; j++) {
            temp->unk00[j] -= value;

            if (temp->unk00[j] > 248) {
                temp->unk00[j] = 0;
            } else {
                ret |= 1;
            }
        }
    }
    return ret;
}
