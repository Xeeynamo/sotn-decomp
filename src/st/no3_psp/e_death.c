// SPDX-License-Identifier: AGPL-3.0-or-later

#include "../no3/no3.h"

extern s32 E_ID(BG_LIGHTNING);
extern s32 E_ID(DEATH_STOLEN_ITEM);

void EntityRoomTransition2(Entity* self) {
    Entity* newEntity;
    Primitive* prim;
    // Used as both a loop variable and a temp
    s32 localVar;
    Tilemap* tilemap = &g_Tilemap;
    Entity* otherEnt = &PLAYER;

    if (self->ext.roomTransition2.unk80 == 0 && self->step < 4) {
        g_api.PlaySfx(SFX_DEATH_AMBIENCE);
        self->ext.roomTransition2.unk80 = 0x200;
    }
    self->ext.roomTransition2.unk80--;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        tilemap->y = 0xFC;
        g_PauseAllowed = false;
        g_Player.padSim = PAD_RIGHT;
        g_Player.demo_timer = 1;
        break;

    case 1:
        // other ent is player right now
        if (otherEnt->posX.i.hi < 52) {
            g_Entities[UNK_ENTITY_1].ext.alucardController.unk7C = 1;
            g_Player.padSim = PAD_RIGHT;
        } else {
            g_CutsceneFlags |= 0x80;
            g_Player.padSim = 0;
            self->step++;
        }
        g_Player.demo_timer = 1;
        break;

    case 2:
        if (g_CutsceneFlags & 0x20) {
            g_api.InitStatsAndGear(1);
            g_api.PlaySfx(SFX_DEATH_SWISH);
            for (localVar = 0; localVar < 6; localVar++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity == NULL) {
                    break;
                }
                CreateEntityFromEntity(E_ID(DEATH_STOLEN_ITEM), otherEnt, newEntity);
                newEntity->params = localVar;
            }
            g_Player.padSim = PAD_SIM_UNK10000;
            self->ext.roomTransition2.timer = 16;
            self->step++;
        }
        g_Player.demo_timer = 1;
        break;

    case 3:
        if (g_CutsceneFlags & 0x40 && !(--self->ext.roomTransition2.timer)) {
            localVar = g_api.AllocPrimitives(PRIM_TILE, 1);
            if (localVar != -1) {
                self->primIndex = localVar;
                self->flags |= FLAG_HAS_PRIMS;
                prim = &g_PrimBuf[localVar];
                prim->x0 = 0;
                prim->y0 = 0;
                prim->u0 = 0xFF;
                prim->v0 = 0xFF;
                prim->r0 = prim->b0 = prim->g0 = 0;
                prim->priority = 0x50;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                self->step++;
            } else {
                self->ext.roomTransition2.timer++;
            }
        }
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        break;

    case 4:
        prim = &g_PrimBuf[self->primIndex];
        prim->r0 = prim->g0 = prim->b0 += 8;
        if (prim->r0 >= 240) {
            self->step++;
            DestroyEntity(&g_Entities[208]);
            g_BgLayers[0].flags |= 1;
            g_api.PlaySfx(SET_RELEASE_RATE_HIGH_20_21);
            g_api.PlaySfx(MU_DRACULAS_CASTLE);
        }
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        break;

    case 5:
        prim = &g_PrimBuf[self->primIndex];
        prim->r0 = prim->g0 = prim->b0 -= 8;
        if (!prim->r0) {
            DestroyEntity(self);
            tilemap->y = 0;
            g_PauseAllowed = true;
            otherEnt = &g_Entities[192];
            DestroyEntity(otherEnt);
            CreateEntityFromCurrentEntity(E_ID(BG_LIGHTNING), otherEnt);
        }
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        break;
    }
}

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_death", EntityDeathStolenItem);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_death", EntityDeath);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_death", EntityDeathScythe);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_death", EntityDeathScytheShadow);