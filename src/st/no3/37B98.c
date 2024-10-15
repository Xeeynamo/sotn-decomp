// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"

#include "../entrance_stage_entities.h"

extern CVECTOR D_8018136C;
extern s16 D_80181370[];

// See also: UnkRecursivePrimFunc1. Strong overlap, but also some different
// logic.
Primitive* func_801BB548(
    SVECTOR* arg0, SVECTOR* arg1, SVECTOR* arg2, SVECTOR* arg3, Primitive* arg4,
    s32 arg5, Primitive* arg6, u8* arg7) {
    s32 i;
    Primitive* prim1;
    s32 vecIdx1;
    s32 vecIdx2;
    s32 vecIdx3;
    s32 vecIdx4;
    s16* vecIndices;
    SVECTOR* vectors;
    uvPair* uv_values;

    long unused;
    long interp;
    s32 rotTransResult;
    Primitive* nextArg6;

    if (arg6 == NULL) {
        return NULL;
    }
    prim1 = (Primitive*)arg7;
    arg7 += sizeof(Primitive);
    vectors = (SVECTOR*)arg7;
    arg7 += sizeof(SVECTOR) * 9;
    uv_values = (uvPair*)arg7;
    arg7 += sizeof(uvPair) * 10; // This is effectively arg7 = arg7->next, since
                                 // this covers the full size of arg7.

    vectors[0] = *arg0;
    vectors[2] = *arg1;
    vectors[6] = *arg2;
    vectors[8] = *arg3;

    vectors[1].vx = (vectors[0].vx + vectors[2].vx + 1) >> 1;
    vectors[1].vy = (vectors[0].vy + vectors[2].vy + 1) >> 1;
    vectors[1].vz = (vectors[0].vz + vectors[2].vz + 1) >> 1;
    vectors[7].vx = (vectors[6].vx + vectors[8].vx + 1) >> 1;
    vectors[7].vy = (vectors[6].vy + vectors[8].vy + 1) >> 1;
    vectors[7].vz = (vectors[6].vz + vectors[8].vz + 1) >> 1;
    vectors[3].vx = (vectors[0].vx + vectors[6].vx + 1) >> 1;
    vectors[3].vy = (vectors[0].vy + vectors[6].vy + 1) >> 1;
    vectors[3].vz = (vectors[0].vz + vectors[6].vz + 1) >> 1;
    vectors[5].vx = (vectors[2].vx + vectors[8].vx + 1) >> 1;
    vectors[5].vy = (vectors[2].vy + vectors[8].vy + 1) >> 1;
    vectors[5].vz = (vectors[2].vz + vectors[8].vz + 1) >> 1;
    vectors[4].vx = (vectors[3].vx + vectors[5].vx + 1) >> 1;
    vectors[4].vy = (vectors[3].vy + vectors[5].vy + 1) >> 1;
    vectors[4].vz = (vectors[3].vz + vectors[5].vz + 1) >> 1;

    uv_values[0] = *(uvPair*)&arg4->u0;
    uv_values[2] = *(uvPair*)&arg4->u1;
    uv_values[6] = *(uvPair*)&arg4->u2;
    uv_values[8] = *(uvPair*)&arg4->u3;
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

    *prim1 = *arg4;
    D_8018136C.cd = arg4->type;
    vecIndices = &D_80181370[0];
    for (i = 0; i < 4; i++) {
        vecIdx1 = *vecIndices++;
        vecIdx2 = *vecIndices++;
        vecIdx3 = *vecIndices++;
        vecIdx4 = *vecIndices++;

        RotTransPers(&vectors[vecIdx1], (long*)&prim1->x0, &interp, &unused);
        DpqColor(&D_8018136C, interp, &prim1->r0);

        RotTransPers(&vectors[vecIdx2], (long*)&prim1->x1, &interp, &unused);
        DpqColor(&D_8018136C, interp, &prim1->r1);

        RotTransPers(&vectors[vecIdx3], (long*)&prim1->x2, &interp, &unused);
        DpqColor(&D_8018136C, interp, &prim1->r2);

        rotTransResult = RotTransPers(
            &vectors[vecIdx4], (long*)&prim1->x3, &interp, &unused);
        DpqColor(&D_8018136C, interp, &prim1->r3);

        *(uvPair*)&prim1->u0 = uv_values[vecIdx1];
        *(uvPair*)&prim1->u1 = uv_values[vecIdx2];
        *(uvPair*)&prim1->u2 = uv_values[vecIdx3];
        *(uvPair*)&prim1->u3 = uv_values[vecIdx4];
        if (arg5 == 1) {
            if (rotTransResult > 0) {
                nextArg6 = arg6->next;
                *arg6 = *prim1;
                arg6->next = nextArg6;
                arg6 = arg6->next;
                if (arg6 == NULL) {
                    return NULL;
                }
            }
        } else {
            arg6 = func_801BB548(
                &vectors[vecIdx1], &vectors[vecIdx2], &vectors[vecIdx3],
                &vectors[vecIdx4], prim1, arg5 - 1, arg6, arg7);
        }
    }
    return arg6;
}

// sky animation during death cutscene
void EntityDeathSkySwirl(Entity* self) {
    Primitive* prim;
    Primitive* prim2;
    s16 primIndex;
    SVECTOR sVec;
    VECTOR vec;
    MATRIX mtx;

    if (self->step == 0) {
        if (g_CastleFlags[CASTLE_FLAG_53]) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(g_EInitGeneric);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 65);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.deathSkySwirl.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->tpage = 0x12;
        prim->clut = 0x1F;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0xFF;
        prim->v0 = prim->v1 = 0x80;
        prim->v2 = prim->v3 = 0xFF;
        prim->priority = 0x1F;
        prim->drawMode = DRAW_DEFAULT;
    }
    g_BgLayers[0].flags &= 0xFFFE;
    self->ext.deathSkySwirl.unk84 -= 32;
    SetGeomScreen(256);
    SetGeomOffset(128, 192);
    SetFogNear(256, 256);
    SetFarColor(96, 96, 96);
    sVec.vx = 0;
    sVec.vy = self->ext.deathSkySwirl.unk84;
    sVec.vz = 0;
    RotMatrix(&sVec, &mtx);
    vec.vy = -0xC0;
    vec.vx = 0;
    vec.vz = 0x200;
    TransMatrix(&mtx, &vec);
    SetRotMatrix(&mtx);
    SetTransMatrix(&mtx);
    prim = self->ext.deathSkySwirl.prim;
    prim->drawMode = DRAW_COLORS;

    prim2 = prim->next;
    prim2 = func_801BB548(&D_8018134C, &D_80181354, &D_8018135C, &D_80181364,
                          prim, 3, prim2, 0x1F800000);
    prim->drawMode = DRAW_HIDE;
    while (prim2 != NULL) {
        prim2->drawMode = DRAW_HIDE;
        prim2 = prim2->next;
    }
}

void EntityLightningThunder(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_eInitGeneric3);
        self->zPriority = 0x2A;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        self->facingLeft = Random() & 1;
        g_api.PlaySfxVolPan(SFX_THUNDER_B, 0x40, (self->posX.i.hi >> 0x4) - 8);
    }
    if (AnimateEntity(D_80181390, self) == 0) {
        DestroyEntity(self);
    }
}

// When lightning strikes, we get a bright bolt, but it is against a cloud
// as a background. It's subtle and hard to see, but it's there.
void EntityLightningCloud(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_eInitGeneric3);
        self->zPriority = 0x29;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        // There are 3 shapes of cloud, this picks which one.
        self->animCurFrame = self->params + 0x22;
        self->posX.i.hi = D_8018139C[self->params << 1];
        self->posY.i.hi = D_8018139E[self->params << 1];
        self->ext.backgroundLightning.timer = 5;
    }

    if (--self->ext.backgroundLightning.timer == 0) {
        DestroyEntity(self);
    }
}

// switch that goes downwards when you stand on it
void EntitySwitch(Entity* entity) {
    s32 temp_a0 = GetPlayerCollisionWith(entity, 8, 4, 4);
    Entity* player = &PLAYER;

    switch (entity->step) {
    case 0:
        InitializeEntity(g_eInitGeneric3);
        entity->animCurFrame = 9;
        entity->zPriority = 0x5E;
        if (g_CastleFlags[CASTLE_FLAG_50] != 0) {
            entity->step = 2;
            entity->posY.i.hi += 4;
        }
        break;

    case 1:
        if (temp_a0 != 0) {
            player->posY.i.hi++;
            entity->posY.val += FIX(0.25);
            if ((g_Tilemap.scrollY.i.hi + entity->posY.i.hi) > 193) {
                entity->posY.i.hi = 193 - g_Tilemap.scrollY.i.hi;
                g_CastleFlags[CASTLE_FLAG_50] = 1;
                g_api.PlaySfx(SFX_STONE_MOVE_B);
                entity->step++;
            }
        }
        break;
    }
}

// door preventing access to warp room / heart
void EntityHeartRoomGoldDoor(Entity* self) {
    s16 primIndex;
    Entity* newEntity;
    POLY_GT4* poly;
    s32 tilePos;
    s32 temp;
    s32 temp2;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_eInitGeneric3);
        self->animCurFrame = 37;
        self->zPriority = 0x5E;

        if (g_CastleFlags[CASTLE_FLAG_50] != 0) {
            for (
                tilePos = 0x48, i = 7, self->step = 128, self->animCurFrame = 0;
                i >= 0; tilePos += 0x10, i--) {
                g_Tilemap.fg[tilePos] = 0;
            }
            break;
        }

        primIndex = g_api.AllocPrimitives(PRIM_TILE, 64);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        poly = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        *(s32*)&self->ext.generic.unk7C = poly;
        self->flags |= FLAG_HAS_PRIMS;
        while (poly != NULL) {
            poly->v0 = 1;
            poly->u0 = 1;
            poly->r0 = 64;
            poly->b0 = 128;
            poly->g0 = 96;
            poly->pad2 = self->zPriority + 0x18;
            poly->pad3 = 8;
            poly->p3 = 0;
            poly = (POLY_GT4*)poly->tag;
        }

        for (tilePos = 0x48, temp = 0x4FA, i = 7; i >= 0; tilePos += 0x10,
            i--) {
            g_Tilemap.fg[tilePos] = temp;
        }
        break;

    case 1:
        if (g_CastleFlags[CASTLE_FLAG_50] != 0) {
            g_api.PlaySfx(SFX_STONE_MOVE_A);
            self->step++;
        }
        break;

    case 2:
        self->posY.val += FIX(0.375);
        if (++self->ext.generic.unk80.modeS32 & 1) {
            self->posX.i.hi++;
        } else {
            self->posX.i.hi--;
        }

        temp = temp2 = self->posY.i.hi - 112;
        if (temp2 < 0) {
            temp2 = self->posY.i.hi - 97;
        }

        temp = temp2 >> 4;
        if (temp >= 9) {
            temp = 8;
            self->step = 3;
        }

        for (tilePos = 0x48, i = 0; i < temp; tilePos += 0x10, i++) {
            g_Tilemap.fg[tilePos] = 0;
        }

        if (!(g_Timer & 1)) {
            poly =
                FindFirstUnkPrim((POLY_GT4*)(*(s32*)&self->ext.generic.unk7C));
            if (poly != NULL) {
                poly->p3 = 1;
            }

            if (!(g_Timer & 0xF)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, newEntity);
                    newEntity->posY.i.hi = 188;
                    newEntity->posX.i.hi += -8 + (Random() & 0xF);
                    newEntity->params = 0x10;
                    newEntity->rotX = newEntity->rotY = 192;
                    newEntity->drawFlags |= FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
                }
            }
        }
        break;
    }

    if (self->flags & FLAG_HAS_PRIMS) {
        for (poly = *(s32*)&self->ext.generic.unk7C; poly != NULL;
             poly = (POLY_GT4*)poly->tag) {
            if (poly->p3 != 0) {
                DoorCascadePhysics(poly);
            }
        }
    }
}

void EntityUnkId49(Entity* entity) {
    u16 temp;

    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInitGeneric);
        break;
    case 1:
        temp = g_Tilemap.fg[9];
        g_Tilemap.fg[6] = temp;
        temp = g_Tilemap.fg[10];
        g_Tilemap.fg[7] = temp;
        temp = g_Tilemap.fg[0x39];
        g_Tilemap.fg[0x36] = temp;
        temp = g_Tilemap.fg[0x3A];
        g_Tilemap.fg[0x37] = temp;
        temp = g_Tilemap.fg[0x69];
        g_Tilemap.fg[0x66] = temp;
        temp = g_Tilemap.fg[0x6A];
        g_Tilemap.fg[0x67] = temp;
        entity->step++;
        break;
    }
}
