#include "no3.h"

void EntityRoomTransition2(Entity* self) {
    Entity* newEntity;
    Primitive* prim;
    // Used as both a loop variable and a temp
    s32 localVar;

    // These are weird fake vars needed for matching
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
        return;
    case 1:
        // Evil use of local 'gents' instead of PLAYER
        if (gents[0].posX.i.hi < 0x34) {
            // Using generic here because I don't know what g_Entities[1] is
            g_Entities[1].ext.generic.unk7C.S8.unk0 = 1;
            g_Player.D_80072EF4 = 0x2000;
        } else {
            g_Player.D_80072EF4 = 0;
            D_801D7DD0 |= 0x80;
            self->step++;
        }
        g_Player.D_80072EFC = 1;
        return;
    case 2:
        if (D_801D7DD0 & 0x20) {
            g_api.InitStatsAndGear(1);
            g_api.PlaySfx(0x6A2);
            for (localVar = 0; localVar < 6; localVar++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity == NULL) {
                    break;
                }
                CreateEntityFromEntity(0x59, gents, newEntity);
                newEntity->params = localVar;
            }
            g_Player.D_80072EF4 = 0x10000;
            self->ext.roomTransition2.unk7C = 0x10;
            self->step++;
        }
        g_Player.D_80072EFC = 1;
        return;
    case 3:
        if (D_801D7DD0 & 0x40 &&
            !(--self->ext.roomTransition2.unk7C & 0xFFFF)) {
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
                self->ext.roomTransition2.unk7C++;
            }
        }
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;
        return;
    case 4:
        prim = &g_PrimBuf[self->primIndex];
        prim->r0 = prim->g0 = prim->b0 = prim->b0 + 8;
        if (prim->r0 >= 0xF0) {
            self->step++;
            DestroyEntity(&g_Entities[208]);
            g_CurrentRoom.bg[0].D_800730F4 |= 1;
            g_api.PlaySfx(0xA1);
            g_api.PlaySfx(0x30F);
        }
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;
        return;
    case 5:
        prim = &g_PrimBuf[self->primIndex];
        prim->r0 = prim->g0 = prim->b0 = prim->b0 - 8;
        if (prim->r0 == 0) {
            DestroyEntity(self);
            gents = &g_Entities[192];
            layout->unk40 = 0;
            D_8003C8B8 = 1;
            DestroyEntity(gents);
            CreateEntityFromCurrentEntity(0x17, gents);
        }
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 1;
        return;
    }
}

// shows the sword taken from you by Death. Using a different params shows
// the other items?
INCLUDE_ASM("asm/us/st/no3/nonmatchings/3FF00", EntityDeathStolenItem);

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
                newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
                if (newEntity == NULL) {
                    break;
                }
                CreateEntityFromCurrentEntity(0x5E, newEntity);
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
    s32 i;
    s8 temp_s4;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
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

