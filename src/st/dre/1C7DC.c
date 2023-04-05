#include "dre.h"

void EntityEquipItemDrop(Entity* self) {
    u16 itemId = self->subId & 0x7FFF;
    s32 firstPolygonIndex;
    Collider collider;
    POLY_GT4* poly;
    s32* itemName;
    s16 index;
    s32 vramX;
    s32 vramY;
    u8 left;
    u8 right;
    u16 top;
    u8 bottom;
    u8 temp_v0_6;
    s16 temp_a0;
    s32* unk;

    if (((self->step - 2) < 3U) && (self->unk48 != 0)) {
        self->step = 5;
    }

    switch (self->step) {
    case 0:
        if (g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
            self->pfnUpdate = EntityPrizeDrop;
            self->subId = 0;
            self->objectId = 3;
            func_8019AFE8(0);
            EntityPrizeDrop(self);
            return;
        }
        InitializeEntity(D_80180464);
        self->unk7C.s = 0;
        break;

    case 1:
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);

        if (!(collider.unk0 & 7)) {
            for (index = 0; index < 32; index++) {
                if (D_801A3F8C[index] == 0) {
                    break;
                }
            }

            if (index >= 32) {
                DestroyEntity(self);
                return;
            }

            if (LOH(self->unk94) != 0) {
                temp_a0 = LOH(self->unk94);
                temp_a0--;
                D_8003BF9C[temp_a0 >> 3] |= 1 << (temp_a0 & 7);
            }

            firstPolygonIndex = g_api.AllocPrimitives(4, 1);
            if (firstPolygonIndex == (-1)) {
                DestroyEntity(self);
                return;
            }

            self->flags |= FLAG_FREE_POLYGONS;
            self->firstPolygonIndex = firstPolygonIndex;
            D_801A3F8C[index] = 0x1E0;
            self->unk8C.modeU16.unk0 = index;

            if (itemId < 169) {
                g_api.func_800EB534(g_api.D_800A4B04[itemId].icon,
                                    g_api.D_800A4B04[itemId].palette, index);
            } else {
                itemId -= 169;
                g_api.func_800EB534(g_api.D_800A7718[itemId].icon,
                                    g_api.D_800A7718[itemId].palette, index);
            }

            poly = &g_PrimBuf[firstPolygonIndex];
            vramX = ((temp_v0_6 = index) & 7) * 0x10;
            vramY = (temp_v0_6 & 0x18) * 2;

            left = vramX | 1;
            right = vramX | 0xF;
            top = 0x81;
            top = vramY | top;
            bottom = vramY | 0x8F;

            poly->tpage = 0x1A;
            poly->v3 = bottom;
            poly->clut = index + 464;
            poly->u0 = poly->u2 = left;
            poly->u1 = poly->u3 = right;
            poly->v1 = top;
            poly->v2 = bottom;
            poly->v0 = top;
            poly->pad2 = 0x80;
            poly->pad3 = 6;

            self->unk7C.s = 128;
            self->step++;
            break;
        }
        DestroyEntity(self);
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

        if ((collider.unk0 & 5) && (self->accelerationY > 0)) {
            self->accelerationX = 0;
            self->accelerationY = 0;
            self->posY.i.hi += *(u16*)&collider.unk18;
            self->unk80.modeS8.unk0 = 240;
            self->step++;
        } else {
            FallEntity();
        }

        func_8019B304(D_801811A4, 2);
        break;

    case 3:
        func_8019B8DC(1);
        if (!(self->subId & 0x8000)) {
            if (!(--self->unk80.modeS8.unk0 & 255)) {
                self->unk80.modeS8.unk0 = 0x50;
                self->step++;
            }
        } else {
            D_801A3F8C[self->unk8C.modeS16.unk0] = 0x10;
        }
        break;

    case 4:
        func_8019B8DC(1);
        if (self->unk80.modeS8.unk0 += 255) {
            poly = &g_PrimBuf[self->firstPolygonIndex];
            if (self->unk80.modeS8.unk0 & 2) {
                poly->pad3 = 8;
            } else {
                poly->pad3 = 2;
            }
        } else {
            DestroyEntity(self);
        }
        break;

    case 5:
        unk = &D_80097410;
        if (*unk != 0) {
            g_api.FreePrimitives(D_80097414);
            *unk = 0;
        }

        g_api.PlaySfx(NA_SE_PL_IT_PICKUP);

        if (itemId < 169) {
            itemName = g_api.D_800A4B04[itemId].name;
            g_api.AddToInventory(itemId, 0);
        } else {
            itemId -= 169;
            itemName = g_api.D_800A7718[itemId].name;
            g_api.AddToInventory(itemId, 2);
        }

        func_801A1CE8(itemName, 1);
        DestroyEntity(self);
        break;
    }

    if (self->step >= 2) {
        if (self->unk7C.u != 0) {
            self->unk7C.u--;
        }
        func_8019C738(self, self->unk7C.u);
    }
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_8019CDC4);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", EntityRelicOrb);

void EntityHeartDrop(Entity* self) {
    u16 temp_a0;
    u16 temp_a0_2;
    u16 var_a0;

    if (self->step == 0) {
        temp_a0 = self->subId + 0x118;
        self->unkB4 = temp_a0;
        if ((D_8003BEEC[temp_a0 >> 3] >> (temp_a0 & 7)) & 1) {
            DestroyEntity(self);
            return;
        }
        temp_a0_2 = temp_a0 - 0x118;
        var_a0 = D_80180660[temp_a0_2];
        if (var_a0 < 128) {
            self->unkB8.unkFuncB8 = EntityPrizeDrop;
        } else {
            self->unkB8.unkFuncB8 = EntityEquipItemDrop;
            var_a0 -= 128;
        }
        self->subId = var_a0 + 0x8000;
    } else {
        temp_a0_2 = self->unkB4;
        if (self->step < 5) {
            if (self->unk48 != 0) {
                var_a0 = self->unkB4;
                D_8003BEEC[temp_a0_2 >> 3] |= 1 << (var_a0 & 7);
                self->step = 5;
            }
        }
    }
    self->unkB8.unkFuncB8(self);
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", EntityUnkId0E);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_8019E1C8);

void EntityUnkId13(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180494);
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

// DECOMP_ME_WIP func_8019E3C8 https://decomp.me/scratch/lcx4I
INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_8019E3C8);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_8019E4F8);

// an explosion animation ID 0x14
void EntityExplosion14(Entity* entity) {
    u8 new_var2;
    u32 new_var;

    if (!entity->step) {
        new_var = D_8018130C[entity->unk94];
        entity->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = 2;
        entity->accelerationY = new_var;
        new_var2 = D_80181324[entity->subId];
        entity->blendMode = 0x10;
        entity->step++;
        entity->animCurFrame = new_var2;
        return;
    }

    entity->animFrameDuration++;
    entity->posY.val -= entity->accelerationY;

    if (!(entity->animFrameDuration & 1)) {
        entity->animCurFrame++;
    }

    if (D_80181328[entity->subId] < entity->animFrameDuration) {
        DestroyEntity(entity);
    }
}

// looks like a particle of dust fading away
void EntityUnkId15(Entity* entity) {
    u16 temp_v0;
    u32 temp2;

    if (!entity->step) {
        entity->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = 5;
        entity->animCurFrame = 1;
        entity->blendMode = 0x10;
        entity->unk19 = 3;
        temp_v0 = D_801812E4[entity->subId];
        entity->unk1A = temp_v0;
        entity->unk1C = temp_v0;
        temp2 = D_801812F4[entity->subId];
        entity->step += 1;
        entity->accelerationY = temp2;
        return;
    }

    entity->animFrameDuration++;
    entity->posY.val -= entity->accelerationY;

    if (!(entity->animFrameDuration & 1)) {
        entity->animCurFrame++;
    }

    if (entity->animFrameDuration >= 0x25) {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_8019E7C4);

bool func_8019E9F4(Unkstruct6* arg0) {
    Collider res;

    FallEntity();
    g_CurrentEntity->posX.val += g_CurrentEntity->accelerationX;
    g_CurrentEntity->posY.val += g_CurrentEntity->accelerationY;

    if (g_CurrentEntity->accelerationY >= 0) {
        s16 posX = g_CurrentEntity->posX.i.hi;
        s16 posY = g_CurrentEntity->posY.i.hi;
        posX += arg0->x;
        posY += arg0->y;

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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_8019EAF0);

void EntityIntenseExplosion(Entity* entity) {
    u32 temp_v0;

    if (entity->step == 0) {
        InitializeEntity(D_80180470);
        entity->palette = 0x8170;
        entity->animSet = 5;
        entity->animCurFrame = 1;
        entity->blendMode = 0x30;

        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        temp_v0 = entity->subId & 0xFF00;
        if (temp_v0 != 0) {
            entity->zPriority = temp_v0 >> 8;
        }

        entity->zPriority += 8;
        return;
    }

    entity->animFrameDuration++;
    entity->posY.val -= 0x4000;

    if (!(entity->animFrameDuration & 1)) {
        entity->animCurFrame++;
    }

    if (entity->animFrameDuration >= 0x25) {
        DestroyEntity(entity);
    }
}

void func_8019F170(Entity* entity) {
    if (!entity->step) {
        InitializeEntity(D_80180470);
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

    if (!AnimateEntity(&D_80181338, entity)) {
        DestroyEntity(entity);
    }
}

void func_8019F23C(u16 objectId, Entity* src, Entity* dst) {
    DestroyEntity(dst);
    dst->objectId = objectId;
    dst->pfnUpdate = D_801803C4[objectId];
    dst->posX.i.hi = src->posX.i.hi;
    dst->posY.i.hi = src->posY.i.hi;
    dst->unk5A = src->unk5A;
    dst->zPriority = src->zPriority;
    dst->animSet = src->animSet;
    dst->flags = 0x1002000 | FLAG_UNK_04000000 | FLAG_UNK_08000000 |
                 FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                 FLAG_DESTROY_IF_OUT_OF_CAMERA;

    if (src->palette & 0x8000) {
        dst->palette = src->unk6A;
    } else {
        dst->palette = src->palette;
    }
}

void func_8019F304(void) {
    Entity* entity;
    s8 temp_s4 = Random() & 3;
    s16 temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (entity != NULL) {
            CreateEntityFromEntity(2, g_CurrentEntity, entity);
            entity->unk84.U8.unk1 = 6 - i;
            entity->unk80.modeS16.unk0 = temp_s3;
            entity->unk84.U8.unk0 = temp_s4;
        }
    }
}

// DECOMP_ME_WIP func_8019F3BC https://decomp.me/scratch/Hfk9n
INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_8019F3BC);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_8019F594);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_8019FB74);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_801A0274);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_801A046C);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_801A0564);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", EntityStageNamePopup);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", EntityAbsorbOrb);

// ID 0x0D
INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", EntityEnemyBlood);

extern ObjInit2 D_80181420[];
void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_80181420[entity->subId];

    if (entity->step == 0) {
        InitializeEntity(D_801804AC);
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

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_801A1CE8);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_801A2018);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_801A2400);

POLY_GT4* func_801A2550(POLY_GT4* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = (POLY_GT4*)poly->tag;
        } else {
            return poly;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_801A2580);

// DECOMP_ME_WIP func_801A25FC https://decomp.me/scratch/IIvQX a0 -> v0 register
// swap
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_801A25FC);
#else
POLY_GT4* func_801A25FC(POLY_GT4* poly, s32 arg1) {
    s32 i;
    s8 var_a2;

    if (poly->p3 != 0) {
        poly->p3 = 0;
    } else {
        poly->p3 = 1;
    }

    for (i = 0; i < arg1; i++) {
        if (poly->p3 != 0) {
            var_a2 = 0;
            poly->pad3 &= ~8;
        } else {
            var_a2 = 1;
            poly->pad3 |= 8;
        }

        if (poly->tag != NULL) {
            poly->p3 = var_a2;
        } else {
            return NULL;
        }
    }
    return poly;
}
#endif

void func_801A2684(POLY_GT4* poly) {
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

void func_801A2764(POLY_GT4* poly) {
    func_801A2684(poly);
    poly->p3 = 8;
    ((POLY_GT4*)poly->tag)->p3 = 1;
    ((POLY_GT4*)poly->tag)->code = 2;
    ((POLY_GT4*)poly->tag)->pad3 = 0xA;
}

void func_801A27B8(POLY_GT4* poly) {
    poly->p3 = 0;
    poly->pad3 = 8;
    ((POLY_GT4*)poly->tag)->p3 = 0;
    ((POLY_GT4*)poly->tag)->code = 4;
    ((POLY_GT4*)poly->tag)->pad3 = 8;
}

s32 func_801A27E4(s32 arg0, u8 arg1) {
    s32 var_v0;
    s32 ret = 0;
    u8* var_a0 = arg0 + 4;
    u8* var_v1;
    s32 i;

    for (i = 0; i < 4; i++) {
        var_v1 = var_a0;
        do {
            var_v0 = *var_v1 - arg1;

            if (var_v0 < 0) {
                var_v0 = 0;
            } else {
                ret |= 1;
            }

            *var_v1 = var_v0;
            var_v1++;
        } while (((s32)var_v1 < ((s32)var_a0 + 3)));

        var_a0 += 0xC;
    }

    return ret;
}

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_801A2848);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_801A2A58);

INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", func_801A2C9C);

// DECOMP_ME_WIP EntityUnkId17 https://decomp.me/scratch/nNfXk 95.28%
INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", EntityUnkId17);

// 3D house object in background ID 0x16
INCLUDE_ASM("asm/us/st/dre/nonmatchings/1C7DC", Entity3DBackgroundHouse);
