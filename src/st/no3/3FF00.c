#include "no3.h"
#include "sfx.h"

void EntityRoomTransition2(Entity* self) {
    Entity* newEntity;
    Primitive* prim;
    // Used as both a loop variable and a temp
    s32 localVar;
    Entity* gents = g_Entities;
    Tilemap* tilemap = &g_Tilemap;

    if (self->ext.roomTransition2.unk80 == 0 && self->step < 4) {
        g_api.PlaySfx(SFX_DEATH_AMBIENCE);
        self->ext.roomTransition2.unk80 = 0x200;
    }
    self->ext.roomTransition2.unk80--;

REDACTED
    case 0:
        InitializeEntity(D_80180AD0);
        tilemap->y = 0xFC;
        g_Player.padSim = PAD_RIGHT;
        D_8003C8B8 = 0;
        g_Player.D_80072EFC = 1;
        D_801D7DD0 |= 0x100;
REDACTED
REDACTED
    case 1:
        // Evil use of local 'gents' instead of PLAYER
REDACTED
REDACTED
            g_Player.padSim = PAD_RIGHT;
        } else {
            g_Player.padSim = 0;
            D_801D7DD0 |= 0x80;
            self->step++;
        }
        g_Player.D_80072EFC = 1;
REDACTED
REDACTED
    case 2:
        if (D_801D7DD0 & 0x20) {
            g_api.InitStatsAndGear(1);
            g_api.PlaySfx(SE_DEATH_SWIPES);
            for (localVar = 0; localVar < 6; localVar++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity == NULL) {
                    break;
                }
REDACTED
                newEntity->params = localVar;
            }
            g_Player.padSim = 0x10000;
REDACTED
            self->step++;
        }
        g_Player.D_80072EFC = 1;
REDACTED
REDACTED
    case 3:
REDACTED
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
                prim->drawMode = 0x35;
                self->step++;
            } else {
REDACTED
            }
        }
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
REDACTED
REDACTED
    case 4:
        prim = &g_PrimBuf[self->primIndex];
        prim->r0 = prim->g0 = prim->b0 = prim->b0 + 8;
REDACTED
            self->step++;
            DestroyEntity(&g_Entities[208]);
            g_BgLayers[0].flags |= 1;
            g_api.PlaySfx(0xA1);
            g_api.PlaySfx(0x30F);
        }
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
REDACTED
REDACTED
    case 5:
        prim = &g_PrimBuf[self->primIndex];
        prim->r0 = prim->g0 = prim->b0 = prim->b0 - 8;
        if (prim->r0 == 0) {
            DestroyEntity(self);
            gents = &g_Entities[192];
            tilemap->y = 0;
            D_8003C8B8 = 1;
            DestroyEntity(gents);
            CreateEntityFromCurrentEntity(E_BG_LIGHTNING, gents);
        }
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
REDACTED
    }
}

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_eInitGeneric2);
REDACTED
REDACTED
REDACTED
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_api.LoadEquipIcon(g_api.equipDefs[itemId].icon,
                                g_api.equipDefs[itemId].iconPalette, params);
REDACTED
REDACTED
            g_api.LoadEquipIcon(
                g_api.accessoryDefs[itemId].icon,
                g_api.accessoryDefs[itemId].iconPalette, params);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = 8;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        prim->drawMode = 6;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_api.PlaySfx(SE_ITEM_YOINK);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                InitializeEntity(g_eInitGeneric2);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                self->flags |= FLAG_HAS_PRIMS;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                        prim->drawMode = 0x35;
REDACTED
REDACTED
                        prim->drawMode = 0x55;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->drawFlags = FLAG_DRAW_ROTZ;
            self->rotZ = 0x1000;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        self->rotZ -= 0x40;
        if (self->rotZ == 0) {
REDACTED
            self->drawFlags = 0;
REDACTED
REDACTED
        x = (0x1000 - self->rotZ) * 0x1D;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        y = (0x1000 - self->rotZ) * 0x28;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (!(self->rotZ & 0x70)) {
REDACTED
REDACTED
REDACTED
                newEntity->rotZ = self->rotZ;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_api.PlaySfx(SE_VO_DEATH_LAUGH);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    case 4:
        prim = &g_PrimBuf[self->primIndex];
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                prim->drawMode = 8;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_api.PlaySfx(SE_VO_DEATH_STEALS);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            g_api.PlaySfx(SE_VO_DEATH_LAUGH);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = ANIMSET_OVL(8);
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
                AnimateEntity(D_80181B40, entity);
REDACTED
REDACTED
                AnimateEntity(D_80181B4C, entity);
REDACTED
REDACTED
                AnimateEntity(D_80181B4C, entity);
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity == NULL) {
                    break;
                }
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        InitializeEntity(g_eInitGeneric2);
REDACTED
        entity->animSet = ANIMSET_OVL(8);
REDACTED
REDACTED
REDACTED
            entity->drawFlags = FLAG_DRAW_UNK8;
            entity->ext.generic.unk84.U16.unk0 = 0x40;
        } else {
            entity->drawFlags = FLAG_DRAW_ROTZ | FLAG_DRAW_UNK8;
REDACTED
REDACTED
REDACTED
        entity->drawMode = 0x30;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
    s8 temp_s4;
REDACTED

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;
REDACTED
    for (i = 0; i < 6; i++) {
REDACTED
        if (entity != NULL) {
            // Make a EntityWargExplosionPuffOpaque
            CreateEntityFromEntity(E_WARG_EXP_OPAQUE, g_CurrentEntity, entity);
            entity->params = 2;
            entity->ext.wargpuff.unk89 = 6 - i;
            entity->ext.wargpuff.unk84 = temp_s3;
            entity->ext.wargpuff.unk88 = temp_s4;
        }
    }
}

// A single "puff" of the warg explosion animation, opaque
REDACTED
    Unkstruct_80180FE0* obj;
    s32 velocityX;
    s32 velocityY;
    s32 params;
    s32 temp_s0;
    s32 adjVelocityX;
    s32 adjVelocityY;
    u32 temp_v0;
    s32 rnd;

    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeEntityData0);
        params = self->params & 0xF;
REDACTED
REDACTED
        self->drawMode = obj->drawMode;
REDACTED
REDACTED
        self->ext.wargpuff.unk80 = obj->unk8;
        self->step = params + 1;

        temp_v0 = self->params & 0xFF00;
        if (temp_v0 != 0) {
            self->zPriority = temp_v0 >> 8;
        }

        if (self->params & 0xF0) {
            self->palette = 0x819F;
            self->drawMode = DRAW_TPAGE;
            self->facingLeft = 1;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (AnimateEntity((u8*)self->ext.wargpuff.unk80, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
        if (AnimateEntity((u8*)self->ext.wargpuff.unk80, self) != 0) {
REDACTED
REDACTED
                self->drawFlags = FLAG_DRAW_UNK8;
                self->unk6C = 0x80;
                self->step_s++;
                break;

            case 1:
                if (self->animFrameIdx == 5) {
                    self->step_s++;
                }
                break;

            case 2:
                self->unk6C += 0xFC;
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
            self->drawFlags |= 4;
            switch (self->ext.wargpuff.unk88) {
REDACTED
                if (self->ext.wargpuff.unk89 >= 0x4) {
                    self->ext.wargpuff.unk89 += 0xFD;
                    self->ext.wargpuff.unk84 -= 0x800;
REDACTED
REDACTED
REDACTED
REDACTED
                self->ext.wargpuff.unk84 =
                    (u16)self->ext.wargpuff.unk84 +
                    ((u8)self->ext.wargpuff.unk89 * 0xC0);
REDACTED
REDACTED
            self->ext.wargpuff.unk84 = self->ext.wargpuff.unk84 & 0xFFF;
            self->rotZ = self->ext.wargpuff.unk84 & 0xFFF;
            temp_s0 = self->ext.wargpuff.unk89 * 0x140;
REDACTED
            self->velocityX = temp_s0 * rsin(self->ext.wargpuff.unk84);
            self->velocityY = -(temp_s0 * rcos(self->ext.wargpuff.unk84));
            self->step_s++;
        }

        if (self->animFrameIdx >= 13) {
            velocityX = self->velocityX;
            if (velocityX < 0) {
                adjVelocityX = velocityX + 3;
            } else {
                adjVelocityX = velocityX;
            }
            self->velocityX = velocityX - (adjVelocityX >> 2);

            velocityY = self->velocityY;
            if (velocityY < 0) {
                adjVelocityY = velocityY + 3;
            } else {
                adjVelocityY = velocityY;
            }
            self->velocityY = velocityY - (adjVelocityY >> 2);
        }
        MoveEntity();
        if (AnimateEntity((u8*)self->ext.wargpuff.unk80, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
    case 4:
        if (self->step_s == 0) {
            rnd = Random();
            self->velocityY = FIX(-0.75);
            self->facingLeft = rnd & 1;
            self->rotX = 0xC0;
            self->drawFlags |= 1;
REDACTED
REDACTED
REDACTED
        if (AnimateEntity((u8*)self->ext.wargpuff.unk80, self) == 0) {
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
