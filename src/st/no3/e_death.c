// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"

#ifdef VERSION_PSP
extern s32 E_ID(BG_LIGHTNING);
extern s32 E_ID(DEATH_STOLEN_ITEM);
#endif

extern s32 g_CutsceneFlags;
void EntityDeathCutsceneManager(Entity* self) {
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
#if !defined(VERSION_PSP)
        g_CutsceneFlags |= 0x100;
#endif
        break;

    case 1:
        // other ent is player right now
        if (otherEnt->posX.i.hi < 52) {
            g_Entities[E_AFTERIMAGE_1]
                .ext.alucardController.disableAfterImageFlag = 1;
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
                CreateEntityFromEntity(
                    E_ID(DEATH_STOLEN_ITEM), otherEnt, newEntity);
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
                // Ugh, RBG
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
        PGREY(prim, 0) += 8;
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
        PGREY(prim, 0) -= 8;
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

static u16 stolenItemIDs[] = {123, 16, 184, 214, 225, 247};
static u16 stolenItemTimers[] = {48, 56, 40, 64, 32, 72};
// Slope and speed that get called into UnkEntityFunc0
#define SS(sl, sp) sl, sp
static s16 stolenItemVels[] = {SS(-256, 1024), SS(-640, 640), SS(512, 768),
                               SS(-896, 1024), SS(0, 512),    SS(256, 896)};

// Displays items took by Death in the cutscene
void EntityDeathStolenItem(Entity* self) {
    u16 params = self->params;
    u16 itemId = stolenItemIDs[params];
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
        UnkEntityFunc0(
            stolenItemVels[params * 2], stolenItemVels[params * 2 + 1]);
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
            self->ext.utimer.t = stolenItemTimers[params];
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

#ifdef VERSION_PSP
extern s32 E_ID(DEATH_SCYTHE_SHADOW);
extern s32 E_ID(DEATH_SCYTHE);
#endif

static u8 deathAnim1[] = {
    8, 1,  8, 2, 8,  3,  6, 4, 6,  5, 10, 11, 11, 6, 8, 4,   8,
    2, 10, 8, 6, 10, 56, 9, 3, 10, 9, 8,  6,  7,  1, 1, 255, 0};
static u8 deathAnim2[] = {6, 12, 5, 13, 5, 14, 4, 15, 0};
static u8 deathAnim3[] = {5, 16, 5, 17, 5, 18, 4, 19, 0};
static u8 deathAnim4[] = {5, 20, 5, 21, 5, 22, 4, 23, 0};
static u8 deathAnim5[] = {5, 24, 5, 25, 5, 26, 4, 27, 0};
static u8 deathAnim6[] = {8, 1, 7, 2, 5, 3, 5, 4, 6, 5, 4, 6, 4, 4, 255, 0};
static u8 deathAnim7[] = {14, 28, 9, 29, 4, 30, 255, 0};
static u8 deathAnim8[] = {16, 30, 255, 0};
static u8 deathAnim9[] = {
    16, 30, 11, 34, 8, 35, 7, 4, 7, 3, 11, 2, 2, 1, 255, 0};
static u8 deathAnim10[] = {9, 1, 11, 8, 22, 10, 255, 0};
static u8 deathAnim11[] = {20, 10, 11, 8, 2, 1, 255, 0}; // Array skips this one
static u8 deathAnim12[] = {
    5,  1, 10, 36, 12, 1,  5,  37, 3,  38, 4,  37, 5, 1, 10,  36,
    12, 2, 8,  43, 9,  42, 35, 44, 10, 39, 12, 2,  2, 1, 255, 0};
static u8 deathAnim13[] = {
    8, 1, 9, 2, 9, 39, 5, 40, 49, 41, 7, 39, 10, 2, 2, 1, 255, 0};
static u8 deathAnim14[] = {2, 45, 6, 51, 3, 46, 4, 47, 2,  48, 5,   51,
                           3, 49, 4, 50, 5, 51, 5, 52, 16, 53, 255, 0};
static u8 deathAnim15[] = {5, 56, 16, 55, 255, 0};
// Unused array.
static u8* deathAnims[] = {
    deathAnim1,  deathAnim2,  deathAnim3,  deathAnim4, deathAnim5,
    deathAnim6,  deathAnim7,  deathAnim8,  deathAnim9, deathAnim10,
    deathAnim12, deathAnim13, deathAnim14, deathAnim15};

void EntityDeath(Entity* self) {
    Entity* newEntity = self + 1;
    Primitive* prim;
    s32 primIndex;
    s32 i;

    if ((self->step >= 4) && (self->step < 13)) {
        if (self->ext.death.moveTimer) {
            self->ext.death.moveTimer--;
        } else {
            if (self->ext.death.moveDirection) {
                self->ext.death.moveDirection = 0;
            } else {
                self->ext.death.moveDirection = 1;
            }
            self->ext.death.moveTimer = 127;
        }

        if (self->ext.death.moveDirection) {
            self->velocityY += 0x200;
        } else {
            self->velocityY -= 0x200;
        }
        MoveEntity();
    }

    if ((self->step >= 13) && (self->step < 18)) {
        if (self->velocityY != 0) {
            if (self->velocityY < 0) {
                self->velocityY += 0x200;
            } else {
                self->velocityY -= 0x200;
            }
            MoveEntity();
        }
    }

    if (self->step >= 19) {
        self->velocityX -= 0xC00;
        self->velocityY -= FIX(0.15625);
        MoveEntity();
    }

    switch (self->step) {
    case 0:
        if (g_CutsceneFlags & 0x80) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
                InitializeEntity(g_EInitCommon);
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                self->animSet = ANIMSET_OVL(8);
                self->animCurFrame = 0;
                self->palette = 0x2D6;
                self->unk5A = 0x44;
                self->ext.death.unk7C = 0;
                DestroyEntity(newEntity);
                CreateEntityFromCurrentEntity(E_ID(DEATH_SCYTHE), newEntity);
                prim = &g_PrimBuf[primIndex];

                for (i = 0; prim != NULL; i++) {
                    if (i != 0) {
                        prim->clut = self->palette;
                        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE |
                                         DRAW_COLORS | DRAW_TRANSP;
                    } else {
                        prim->clut = PAL_FILL_WHITE;
                        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE |
                                         DRAW_COLORS | DRAW_TRANSP;
                    }
                    prim->tpage = self->unk5A / 4;
                    prim->u0 = prim->u2 = 0x10;
                    prim->u1 = prim->u3 = 0x38;
                    prim->v0 = prim->v1 = 0xB0;
                    prim->v2 = prim->v3 = 0xFF;
                    PCOL(prim) = 0;
                    prim->priority = self->zPriority + i + 1;
                    prim = prim->next;
                }
            }
        }
        break;

    case 1:
        if (AnimateEntity(deathAnim14, self) == 0) {
            SetStep(2);
            self->drawFlags = FLAG_DRAW_ROTATE;
            self->rotate = 0x1000;
            self->posY.i.hi += 16;
            self->animCurFrame = 0x3A;
            self->ext.death.posX = self->posX.i.hi;
            self->ext.death.posY = self->posY.i.hi;
        }
        break;

    case 2:
        self->rotate -= 0x40;
        if (!self->rotate) {
            SetStep(3);
            self->drawFlags = FLAG_DRAW_DEFAULT;
        }

        self->posX.i.hi =
            self->ext.death.posX + (0x1000 - self->rotate) * 0x1D / 0x1000;
        self->posY.i.hi =
            self->ext.death.posY - (0x1000 - self->rotate) * 0x28 / 0x1000;

        if (!(self->rotate & 0x70)) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != 0) {
                CreateEntityFromCurrentEntity(
                    E_ID(DEATH_SCYTHE_SHADOW), newEntity);
                newEntity->rotate = self->rotate;
                newEntity->animCurFrame = 0x3A;
            }
        }
        break;

    case 3:
        if (AnimateEntity(deathAnim15, self) == 0) {
            SetStep(4);
            g_api.PlaySfx(SE_VO_DEATH_LAUGH);
            self->ext.death.moveTimer = 64;
            self->ext.death.moveDirection = 0;
        }
        self->posX.i.hi = self->ext.death.posX;
        self->posY.i.hi = self->ext.death.posY - 16;
        break;

    case 4:
        prim = &g_PrimBuf[self->primIndex];
        self->ext.death.unk7C += 4;
        if (self->ext.death.unk7C == 96) {
            g_CutsceneFlags |= 1;
        }

        if (self->ext.death.unk7C == 128) {
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            self->animCurFrame = 16;
            self->ext.death.unk7C = 32;
            SetStep(5);
            break;
        }

        while (prim != NULL) {
            prim->x0 = prim->x2 = self->posX.i.hi - 14;
            prim->x1 = prim->x3 = prim->x0 + 40;
            prim->y0 = prim->y1 = self->posY.i.hi - 40;
            prim->y2 = prim->y3 = prim->y0 + 79;
            PCOL(prim) = self->ext.death.unk7C;
            prim = prim->next;
        }
        break;

    case 5:
        AnimateEntity(deathAnim3, self);
        if (!--self->ext.death.unk7C) {
            SetStep(6);
        }
        break;

    case 6:
        AnimateEntity(deathAnim2, self);
        if (g_CutsceneFlags & 2) {
            SetStep(7);
        }
        break;

    case 7:
        if (AnimateEntity(deathAnim1, self) == 0) {
            SetStep(8);
        }
        if ((self->animCurFrame >= 7) && (self->animCurFrame < 11)) {
            newEntity->ext.death.unk7C = 2;
        } else {
            newEntity->ext.death.unk7C = 1;
        }

        if (g_CutsceneFlags & 4) {
            SetStep(9);
        }
        break;

    case 8:
        AnimateEntity(deathAnim2, self);
        if (g_CutsceneFlags & 4) {
            SetStep(9);
        }
        break;

    case 9:
        if (AnimateEntity(deathAnim13, self) == 0) {
            SetStep(10);
        }
        newEntity->ext.death.unk7C = 1;

        if (g_CutsceneFlags & 8) {
            SetStep(11);
        }
        break;

    case 10:
        AnimateEntity(deathAnim2, self);
        if (g_CutsceneFlags & 8) {
            SetStep(11);
        }
        break;

    case 11:
        if (AnimateEntity(deathAnim12, self) == 0) {
            SetStep(12);
        }
        newEntity->ext.death.unk7C = 1;

        if (g_CutsceneFlags & 0x10) {
            SetStep(13);
        }
        break;

    case 12:
        AnimateEntity(deathAnim2, self);
        if (g_CutsceneFlags & 0x10) {
            SetStep(13);
        }
        break;

    case 13:
        if (AnimateEntity(deathAnim6, self) == 0) {
            SetStep(14);
        }
        newEntity->ext.death.unk7C = 1;
        break;

    case 14:
        if (AnimateEntity(deathAnim7, self) == 0) {
            g_api.PlaySfx(SE_VO_DEATH_STEALS);
            SetStep(15);
        }
        break;

    case 15:
        if (AnimateEntity(deathAnim8, self) == 0) {
            SetStep(16);
            g_CutsceneFlags |= 0x20;
        }
        break;

    case 16:
        if (AnimateEntity(deathAnim9, self) == 0) {
            SetStep(18);
        }

        if (self->animCurFrame != 30) {
            newEntity->ext.death.unk7C = 1;
        }
        break;

    case 18:
        if (AnimateEntity(deathAnim10, self) == 0) {
            SetStep(19);
            g_api.PlaySfx(SE_VO_DEATH_LAUGH);
            self->velocityX = FIX(1.0);
            self->velocityY = FIX(5.0);
            self->ext.death.moveTimer = 0;
        }

        if (self->animCurFrame != 1) {
            newEntity->ext.death.unk7C = 2;
        } else {
            newEntity->ext.death.unk7C = 1;
        }
        break;

    case 19:
        AnimateEntity(deathAnim11, self);
        if (self->animCurFrame != 1) {
            newEntity->ext.death.unk7C = 2;
        } else {
            newEntity->ext.death.unk7C = 1;
        }

        if ((self->ext.death.moveTimer & 3) == 0) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(
                    E_ID(DEATH_SCYTHE_SHADOW), newEntity);
                newEntity->animCurFrame = self->animCurFrame;
                newEntity->params = 1;
            }
            newEntity->ext.death.unk7C = 3;
        }
        self->ext.death.moveTimer++;

        if (self->posY.i.hi < -32) {
            g_CutsceneFlags |= 0x40;
            DestroyEntity(self);
            DestroyEntity(self + 1);
        }
        break;
    }
}

void EntityDeathScythe(Entity* self) {
    u16 tempstep;
    // this is Death.
    Entity* otherEntity = self - 1;
    self->posX.i.hi = otherEntity->posX.i.hi;
    self->posY.i.hi = otherEntity->posY.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(8);
        self->animCurFrame = 0;
        self->palette = 0x2D6;
        self->unk5A = 0x44;
        break;

    case 1:
        tempstep = self->ext.deathScythe.extStep;
        if (tempstep) {
            switch (tempstep) {
            case 1:
                AnimateEntity(deathAnim4, self);
                break;
            case 2:
                AnimateEntity(deathAnim5, self);
                break;
            case 3:
                AnimateEntity(deathAnim5, self);
                otherEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (otherEntity == NULL) {
                    break;
                }
                CreateEntityFromCurrentEntity(
                    E_ID(DEATH_SCYTHE_SHADOW), otherEntity);
                otherEntity->animCurFrame = self->animCurFrame;
                otherEntity->params = 1;
                break;
            }
        } else {
            self->animCurFrame = 0;
        }
    }
    self->ext.deathScythe.extStep = 0;
}

// When meeting Death, the scythe spins around, leaving behind semi-transparent
// copies of itself. This entity represents those semi-transparent copies.
// Identified through NOP-out in emulator.
void EntityDeathScytheShadow(Entity* self) {
    u16 animCurFrame;

    switch (self->step) {
    case 0:
        animCurFrame = self->animCurFrame;
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(8);
        self->animCurFrame = animCurFrame;
        self->palette = 0x2D6;
        self->unk5A = 0x44;
        if (self->params) {
            self->drawFlags = FLAG_DRAW_OPACITY;
            self->ext.deathScythe.timer = 0x40;
        } else {
            self->drawFlags = FLAG_DRAW_ROTATE | FLAG_DRAW_OPACITY;
            self->ext.deathScythe.timer = 0x20;
        }
        self->opacity = 0x40;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        break;

    case 1:
        if (!(--self->ext.deathScythe.timer)) {
            DestroyEntity(self);
            break;
        }
        if (self->params) {
            self->opacity--;
        } else {
            self->opacity -= 2;
        }
        break;
    }
}
