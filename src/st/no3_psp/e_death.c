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

static u16 D_80181AD4[] = {123, 16, 184, 214, 225, 247};
static u16 D_80181AE0[] = {48, 56, 40, 64, 32, 72};
static s16 D_80181AEC[] = {-256, 1024, -640, 640, 512, 768, -896, 1024, 0, 512, 256, 896};

// Displays items took by Death in the cutscene
void EntityDeathStolenItem(Entity* self) {
    u16 params = self->params;
    u16 itemId = D_80181AD4[params];
    Primitive* prim;
    s32 primIndex;
    u16 size;
    u16 timer;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        break;
    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            break;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;

        if (itemId < NUM_HAND_ITEMS) {
            g_api.LoadEquipIcon(g_api.equipDefs[itemId].icon,
                                g_api.equipDefs[itemId].iconPalette, params);
        } else {
            itemId -= NUM_HAND_ITEMS;
            g_api.LoadEquipIcon(
                g_api.accessoryDefs[itemId].icon,
                g_api.accessoryDefs[itemId].iconPalette, params);
        }

        prim = &g_PrimBuf[primIndex];
        prim->tpage = 0x1A;
        prim->clut = params + 0x1D0;
        
        prim->u0 = prim->u2 = ((params & 7) << 4) + 1;
        prim->u1 = prim->u3 = prim->u0 + 14;
        prim->v0 = prim->v1 = ((params & 0x18) << 1) + 0x81;
        prim->v2 = prim->v3 = prim->v0 + 14;
        PCOL(prim) = 128;
        prim->priority = 0x80;
        prim->drawMode = DRAW_HIDE;
        self->step++;
        break;
    case 2:
        UnkEntityFunc0(D_80181AEC[params * 2], D_80181AEC[params * 2 + 1]);
        self->ext.utimer.t = 16;
        self->step++;
        break;
    case 3:
        timer = --self->ext.utimer.t;
        MoveEntity();
        size = (16 - timer) * 7 / 16;
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = prim->x2 = self->posX.i.hi - size;
        prim->y0 = prim->y1 = self->posY.i.hi - size;
        size *= 2;
        prim->x1 = prim->x3 = prim->x0 + size;
        prim->y2 = prim->y3 = prim->y0 + size;
        prim->drawMode = DRAW_COLORS | DRAW_UNK02;
        if (!timer) {
            self->ext.utimer.t = D_80181AE0[params];
            self->step++;
        }
        break;
    case 4:
        if (!--self->ext.utimer.t) {
            self->ext.utimer.t = 8;
            g_api.PlaySfx(SE_ITEM_YOINK);
            self->step++;
        }
        prim = &g_PrimBuf[self->primIndex];
        if (self->ext.utimer.t & 2) {
            PRED(prim) = 192;
            PGRN(prim) = PBLU(prim) = 64;
        } else {
            PCOL(prim) = 128;
        }
        break;
    case 5:
        prim = &g_PrimBuf[self->primIndex];
        prim->y0 = prim->y1 -= 0x20;
        if (self->ext.utimer.t > 1) {
            prim->x0 = prim->x2++;
            prim->x1 = prim->x3--;
        }
        if (!--self->ext.utimer.t) {
            self->ext.utimer.t = 16;
            self->step++;
        }
        break;
    case 6:
        prim = &g_PrimBuf[self->primIndex];
        prim->y2 = prim->y3 -= 0x10;
        if (!--self->ext.utimer.t) {
            self->step++;
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_death", EntityDeath);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_death", EntityDeathScythe);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_death", EntityDeathScytheShadow);