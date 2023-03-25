#include "mad.h"

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", EntityPrizeDrop);

void EntityExplosion(Entity* entity) {
    u32 temp_v0;

    if (entity->step == 0) {
        InitializeEntity(&D_80180508);
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
    entity->animCurFrame = entity->unk7C.U8.unk0;
    entity->accelerationX = D_80180ED8[entity->unk80.modeS8.unk0 * 2];
    entity->accelerationY = D_80180EDA[entity->unk80.modeS8.unk0 * 2];

    if (entity->subId != 0) {
        entity->zPriority -= 1;
    }
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", EntityInventoryDrop);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", EntityRelicOrb);

// v1 -> a0 reg swap
// branching
// signature conflict
// https://decomp.me/scratch/h3CVU
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
        entity->unkB4 = var_v1;

        if ((D_8003BEE8[temp_a0 >> 3] >> (var_v1 & 7)) & 1) {
            DestroyEntity(entity);
            return;
        }

        var_v1 = D_80180F5C[temp_a0];

        if (var_v1 < 0x80) {
            entity->unkB8.unkFuncB8 = EntityPrizeDrop;
        } else {
            entity->unkB8.unkFuncB8 = EntityInventoryDrop;
            var_v1 -= 0x80;
        }

        entity->subId = var_v1 + 0x8000;
        return;
    }

    temp_v1 = entity->unkB4;

    if (entity->step < 5) {
        arg1 = temp_v1 / 8;
        if (entity->unk48 != 0) {
            D_8003BEE8[arg1] |= (1 << (temp_v1 & 7));
            entity->step = 5;
        }
    }
    entity->unkB8.unkFuncB8(entity, arg1, entity);
}
#endif

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_8019563C);

void func_8019572C(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_8018052C);
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

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_8019583C);

// https://decomp.me/scratch/3IMus
INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_8019596C);

void func_80195A54(Entity* entity) {
    if (entity->step == 0) {
        entity->accelerationY = D_80180FE4[entity->unk94];
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

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_80195F64);

void EntityIntenseExplosion(Entity* entity) {
    u32 zPriority;

    if (entity->step == 0) {
        InitializeEntity(&D_80180508);
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
        InitializeEntity(&D_80180508);
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

    if (!AnimateEntity(&D_80181010, entity)) {
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

// https://decomp.me/scratch/fA367 TODO: 0x80 entity member unconfirmed
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
            entity->unk84.U8.unk1 = 6 - i;
            entity->unk80.modeS16.unk0 = temp_s3;
            entity->unk84.U8.unk0 = temp_s4;
        }
    }
}

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_801969EC);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_80196BC4);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_801971A4);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_801978A4);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_80197A9C);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", func_80197B94);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", EntityAbsorbOrb);

INCLUDE_ASM("asm/us/st/mad/nonmatchings/139E0", EntityEnemyBlood);

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
