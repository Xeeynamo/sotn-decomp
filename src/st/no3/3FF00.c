#include "no3.h"

void EntityRoomTransition2(Entity* self) {
    Entity* newEntity;
    Primitive* prim;
    // Used as both a loop variable and a temp
    s32 localVar;
    Entity* gents = g_Entities;
    Unkstruct8* layout = &g_CurrentRoomTileLayout;

    if (self->ext.roomTransition2.unk80 == 0 && self->step < 4) {
        g_api.PlaySfx(0x631);
        self->ext.roomTransition2.unk80 = 0x200;
    }
    self->ext.roomTransition2.unk80--;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180AD0);
        layout->unk40 = 0xFC;
        g_Player.D_80072EF4 = 0x2000;
        D_8003C8B8 = 0;
        g_Player.D_80072EFC = 1;
        D_801D7DD0 |= 0x100;
        break;

    case 1:
        // Evil use of local 'gents' instead of PLAYER
        if (gents->posX.i.hi < 52) {
            g_Entities[UNK_ENTITY_1].ext.alucardController.unk7C = 1;
            g_Player.D_80072EF4 = 0x2000;
        } else {
            g_Player.D_80072EF4 = 0;
            D_801D7DD0 |= 0x80;
            self->step++;
        }
        g_Player.D_80072EFC = 1;
        break;

    case 2:
        if (D_801D7DD0 & 0x20) {
            g_api.InitStatsAndGear(1);
            g_api.PlaySfx(0x6A2);
            for (localVar = 0; localVar < 6; localVar++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity == NULL) {
                    break;
                }
                CreateEntityFromEntity(E_ID_59, gents, newEntity);
                newEntity->params = localVar;
            }
            g_Player.D_80072EF4 = 0x10000;
            self->ext.roomTransition2.timer = 16;
            self->step++;
        }
        g_Player.D_80072EFC = 1;
        break;

    case 3:
        if (D_801D7DD0 & 0x40 && !(--self->ext.roomTransition2.timer)) {
            localVar = g_api.AllocPrimitives(PRIM_TILE, 1);
            if (localVar != -1) {
                prim = &g_PrimBuf[localVar];
                self->primIndex = localVar;
                self->flags |= FLAG_HAS_PRIMS;
                prim->u0 = 0xFF;
                prim->v0 = 0xFF;
                prim->priority = 0x50;
                prim->x0 = 0;
                prim->y0 = 0;
                prim->r0 = prim->b0 = prim->g0 = 0;
                prim->blendMode = 0x35;
                self->step++;
            } else {
                self->ext.roomTransition2.timer++;
            }
        }
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;
        break;

    case 4:
        prim = &g_PrimBuf[self->primIndex];
        prim->r0 = prim->g0 = prim->b0 = prim->b0 + 8;
        if (prim->r0 >= 240) {
            self->step++;
            DestroyEntity(&g_Entities[208]);
            g_CurrentRoom.bg[0].D_800730F4 |= 1;
            g_api.PlaySfx(0xA1);
            g_api.PlaySfx(0x30F);
        }
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;
        break;

    case 5:
        prim = &g_PrimBuf[self->primIndex];
        prim->r0 = prim->g0 = prim->b0 = prim->b0 - 8;
        if (prim->r0 == 0) {
            DestroyEntity(self);
            gents = &g_Entities[192];
            layout->unk40 = 0;
            D_8003C8B8 = 1;
            DestroyEntity(gents);
            CreateEntityFromCurrentEntity(E_ID_17, gents);
        }
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;
        break;
    }
}

/*
 * Shows the sword taken from you by Death.
 * Using a different params shows the other items?
 */
void EntityDeathStolenItem(Entity* self) {
    u16 params = self->params;
    u16 itemId = D_80181AD4[params];
    volatile char pad;
    Primitive* prim;
    s32 primIndex;
    u16 temp1;
    u16 temp3;
    u16 temp4;
    u16 temp6;
    s32 temp2;
    s32 temp8;
    u8 temp7;
    u8 temp5;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B00);
        break;

    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            break;
        }
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;

        if (itemId < NUM_HAND_ITEMS) {
            g_api.LoadEquipIcon(g_api.D_800A4B04[itemId].icon,
                                g_api.D_800A4B04[itemId].palette, params);
        } else {
            itemId -= NUM_HAND_ITEMS;
            g_api.LoadEquipIcon(g_api.D_800A7718[itemId].icon,
                                g_api.D_800A7718[itemId].palette, params);
        }

        prim = &g_PrimBuf[primIndex];
        prim->tpage = 0x1A;
        prim->clut = params + 0x1D0;
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 =
                128;
        prim->priority = 0x80;
        prim->u0 = prim->u2 = (params & 7) << 4 | 1;
        prim->u1 = prim->u3 = (params & 7) << 4 | 0xF;
        prim->v0 = prim->v1 = (params & 0x18) << 1 | 0x81;
        prim->v2 = prim->v3 = (params & 0x18) << 1 | 0x8F;
        prim->blendMode = 8;
        self->step++;
        break;

    case 2:
        UnkEntityFunc0(D_80181AEC[params].x, D_80181AEC[params].y);
        self->ext.deathStolenItems.unk7C = 16;
        self->step++;
        break;

    case 3:
        self->ext.deathStolenItems.unk7C--;
        temp6 = self->ext.deathStolenItems.unk7C;
        MoveEntity();
        temp8 = (16 - temp6) * 7;
        if (temp8 < 0) {
            temp8 += 15;
        }
        prim = &g_PrimBuf[self->primIndex];
        temp1 = temp8 >> 4;
        prim->x0 = prim->x2 = self->posX.i.hi - temp1;
        prim->y0 = prim->y1 = self->posY.i.hi - temp1;
        prim->blendMode = 6;
        temp2 = temp1 << 1;
        prim->x1 = prim->x3 = prim->x0 + temp2;
        prim->y2 = prim->y3 = prim->y0 + temp2;
        if (temp6 == 0) {
            self->ext.deathStolenItems.unk7C = D_80181AE0[params];
            self->step++;
        }
        break;

    case 4:
        if (--self->ext.deathStolenItems.unk7C == 0) {
            self->ext.deathStolenItems.unk7C = 8;
            g_api.PlaySfx(0x7A2);
            self->step++;
        }

        prim = &g_PrimBuf[self->primIndex];
        if (self->ext.deathStolenItems.unk7C & 2) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = 192;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                prim->b2 = prim->b3 = 64;
        } else {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = 128;
        }
        break;

    case 5:
        prim = &g_PrimBuf[self->primIndex];
        prim->y0 = prim->y1 = prim->y1 - 0x20;
        if (self->ext.deathStolenItems.unk7C >= 2) {
            temp3 = prim->x2;
            temp4 = prim->x3;
            prim->x2 = temp3 + 1;
            prim->x0 = temp3;
            prim->x3 = temp4 - 1;
            prim->x1 = temp4;
        }
        if (--self->ext.deathStolenItems.unk7C == 0) {
            self->ext.deathStolenItems.unk7C = 16;
            self->step++;
        }
        break;

    case 6:
        prim = &g_PrimBuf[self->primIndex];
        prim->y2 = prim->y3 = prim->y3 - 0x10;
        if (--self->ext.deathStolenItems.unk7C == 0) {
            self->step++;
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/no3/nonmatchings/3FF00", EntityUnkId5A);

void EntityUnkId5B(Entity* entity) {
    Entity* newEntity;

    entity->posX.i.hi = entity[-1].posX.i.hi;
    entity->posY.i.hi = entity[-1].posY.i.hi;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180B00);
        entity->animSet = ANIMSET_OVL(8);
        entity->palette = 0x2D6;
        entity->animCurFrame = 0;
        entity->unk5A = 0x44;
        break;

    case 1:
        if (entity->ext.generic.unk7C.u != 0) {
            switch (entity->ext.generic.unk7C.u) {
            case 1:
                AnimateEntity(D_80181B40, entity);
                break;
            case 2:
                AnimateEntity(D_80181B4C, entity);
                break;
            case 3:
                AnimateEntity(D_80181B4C, entity);
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity == NULL) {
                    break;
                }
                CreateEntityFromCurrentEntity(E_ID_5E, newEntity);
                newEntity->animCurFrame = entity->animCurFrame;
                newEntity->params = 1;
                break;
            }
        } else {
            entity->animCurFrame = 0;
        }
    }
    entity->ext.generic.unk7C.s = 0;
}

void EntityUnkId5E(Entity* entity) {
    s16 animCurFrame;

    switch (entity->step) {
    case 0:
        animCurFrame = entity->animCurFrame;
        InitializeEntity(D_80180B00);
        entity->animCurFrame = animCurFrame;
        entity->animSet = ANIMSET_OVL(8);
        entity->palette = 0x2D6;
        entity->unk5A = 0x44;
        if (entity->params != 0) {
            entity->unk19 = 8;
            entity->ext.generic.unk84.U16.unk0 = 0x40;
        } else {
            entity->unk19 = 0xC;
            entity->ext.generic.unk84.U16.unk0 = 0x20;
        }
        entity->unk6C = 0x40;
        entity->blendMode = 0x30;
        break;

    case 1:
        if (!(--entity->ext.generic.unk84.U16.unk0)) {
            DestroyEntity(entity);
            break;
        }
        if (entity->params != 0) {
            entity->unk6C = (s8)entity->unk6C - 1;
        } else {
            entity->unk6C += -2;
        }
        break;
    }
}

void func_801C13F8() {
    Entity* entity;
    s16 temp_s3;
    s8 temp_s4;
    s32 i;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(0x62, g_CurrentEntity, entity);
            entity->params = 2;
            entity->ext.generic.unk88.S8.unk1 = 6 - i;
            entity->ext.generic.unk84.S16.unk0 = temp_s3;
            entity->ext.generic.unk88.S8.unk0 = temp_s4;
        }
    }
}

// A single "puff" of the warg explosion animation, opaque
INCLUDE_ASM("asm/us/st/no3/nonmatchings/3FF00", EntityWargExplosionPuffOpaque);
