// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcen.h"
#include "sfx.h"

extern u32 g_CutsceneFlags;
extern EInit g_EInitCommon;
extern EInit g_EInitInteractable;

static u16 tileLayout[] = {
    0x014C, 0x014D, 0x0150, 0x0151, 0x014A, 0x014B, 0x014E, 0x014F,
    0x00FC, 0x00FD, 0x012F, 0x0130, 0x00F5, 0x00F6, 0x012B, 0x012C};

static u8 glassAnimation[] = {
    0x04, 0x03, 0x04, 0x02, 0x08, 0x01, 0x04, 0x02, 0x04, 0x03, 0x18,
    0x04, 0x02, 0x03, 0x02, 0x02, 0x02, 0x01, 0x18, 0x05, 0xFF};

static u8 unused[] = {0x7F, 0x60, 0x58, 0x50, 0x40};

static void func_8018F8EC(u16 index) {
    u16* tileLayoutPtr;
    Tilemap* tilemap = &g_Tilemap;
    u16 tilePos = 0x316;
    s32 i;
    s32 j;

    tileLayoutPtr = &tileLayout[index * 8];

    for (i = 0; i < 2; tilePos += 0x2C, i++) {
        for (j = 0; j < 4; tilePos++, j++) {
            tilemap->fg[tilePos] = *tileLayoutPtr++;
        }
    }
}
void func_us_8019F148(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* player = &PLAYER;
    s16 posX;
    s16 posY;

    GetPlayerCollisionWith(self, 0x20, 0x11, 2);
    posX = player->posX.i.hi + g_Tilemap.scrollX.i.hi;
    posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        func_8018F8EC(0);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 9;
        self->zPriority = 0x80;
        self->drawFlags = ENTITY_ROTATE;
        self->rotate = 0x800;
        g_api.TimeAttackController(
            NUM_TIMEATTACK_EVENTS, TIMEATTACK_SET_VISITED);
        break;

    case 1:
#ifdef VERSION_PSP
        if ((GetDistanceToPlayerX() < 0x20) &&
            ((player->posY.i.hi - self->posY.i.hi) < 0x50)) {
#else
        if ((GetDistanceToPlayerX() < 0x20) &&
            ((player->posY.i.hi - self->posY.i.hi) < 0x70)) {
#endif
            g_PauseAllowed = 0;
            g_unkGraphicsStruct.pauseEnemies = 1;
            if (posX > 0x180) {
                g_Player.padSim = PAD_LEFT;
            } else if (posX < 0x180) {
                g_Player.padSim = PAD_RIGHT;
            } else {
                g_Player.padSim = PAD_NONE;
            }
            if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
                g_Player.padSim = PAD_BAT;
            } else if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
#ifdef VERSION_PSP
                g_Player.padSim = PAD_NONE;
#else
                g_Player.padSim = PAD_MIST;
#endif
            } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
                g_Player.padSim = PAD_WOLF;
            }
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 0;
            g_Player.demo_timer = 1;
#ifndef VERSION_PSP
            g_Tilemap.height = 0x200;
#endif
            self->step++;
        }
        break;

    case 2:
        g_Player.padSim = PAD_NONE;
        if (g_Player.status & PLAYER_STATUS_TRANSFORM) {
            g_Player.padSim = PAD_NONE;
            if (g_Timer & 1) {
                if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
                    g_Player.padSim = PAD_BAT;
                } else if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
#ifdef VERSION_PSP
                    g_Player.padSim = PAD_NONE;
#else
                    g_Player.padSim = PAD_MIST;
#endif
                } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
                    g_Player.padSim = PAD_WOLF;
                }
            }
        } else {
            if (posX > 0x180) {
                g_Player.padSim = PAD_LEFT;
            } else if (posX < 0x180) {
                g_Player.padSim = PAD_RIGHT;
            }
            self->step++;
        }
        g_Player.demo_timer = 1;
        break;

    case 3:
        if (g_Player.padSim == PAD_LEFT) {
            if (posX < 0x181) {
                g_Player.padSim = PAD_NONE;
            }
        } else if ((g_Player.padSim == PAD_RIGHT) && (posX >= 0x180)) {
            g_Player.padSim = PAD_NONE;
        }
        if (g_Player.padSim == PAD_NONE) {
            player->posX.i.hi = 0x180 - g_Tilemap.scrollX.i.hi;
            self->step++;
#ifndef VERSION_PSP
            g_Tilemap.x = 0x100;
            g_Tilemap.width = 0x200;
#endif
        }
        g_Player.demo_timer = 1;
        break;

    case 4:
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        player->posX.i.hi = 0x180 - g_Tilemap.scrollX.i.hi;
        if (g_Player.vram_flag & TOUCHING_GROUND) {
            if (player->facingLeft) {
                g_Player.padSim = PAD_RIGHT;
            }
            func_8018F8EC(1);
#ifndef VERSION_PSP
            g_Tilemap.y = 0x100;
#endif
            g_CutsceneFlags |= 1;
            self->step++;
        }
        break;

    case 5:
        if (posY < 0x108) {
            self->posY.i.hi++;
        } else {
            g_api.PlaySfx(SFX_METAL_CLANG_A);
            self->step++;
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;

    case 6:
        if (g_CutsceneFlags & 2) {
            self->step++;
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;

    case 7:
#ifdef VERSION_PSP
        g_PauseAllowed = 1;
        g_unkGraphicsStruct.pauseEnemies = 0;
        g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
        self->step++;
#else
        if (g_CutsceneFlags & 4) {
            self->step++;
        }
        break;

    case 8:
        g_unkGraphicsStruct.pauseEnemies = 0;
        g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
        g_PauseAllowed = 1;
        self->step++;
#endif
        break;
    }
}

void func_us_8019F5F0(Entity* self) {
    Entity* player;
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex != -1) {
            InitializeEntity(g_EInitInteractable);
            g_PauseAllowed = 0;
            g_unkGraphicsStruct.pauseEnemies = 1;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            self->animSet = 0;
            prim = &g_PrimBuf[primIndex];
            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 0x100;
            prim->y0 = prim->y1 = 4;
            prim->y2 = prim->y3 = 0xE8;
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = 0x80;
            prim->priority = 0x1F8;
            prim->drawMode =
                DRAW_TRANSP | DRAW_COLORS | DRAW_TPAGE | DRAW_TPAGE2;
            self->ext.utimer.t = 0;
            g_api.PlaySfx(SFX_WEAPON_APPEAR);
        }
        self->flags |= FLAG_UNK_10000;
        break;

    case 1:
        prim = &g_PrimBuf[self->primIndex];
        self->ext.utimer.t++;
        if (self->ext.utimer.t > 8) {
            g_unkGraphicsStruct.unk20 = 0xFF;
            self->step++;
            prim->drawMode = DRAW_HIDE;
        } else if (self->ext.utimer.t & 1) {
            prim->drawMode = DRAW_HIDE;
        } else {
            prim->drawMode =
                DRAW_TRANSP | DRAW_COLORS | DRAW_TPAGE | DRAW_TPAGE2;
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;

    case 2:
        if (g_CutsceneFlags & 0x100) {
            g_unkGraphicsStruct.unk20 = 0;
            self->step++;
            self->ext.utimer.t = 0;
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;

    case 3:
        self->ext.utimer.t++;
        if (self->ext.utimer.t > 0x180) {
            g_CutsceneFlags |= 0x400;
            self->step++;
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;

    case 4:
        if (g_CutsceneFlags & 0x800) {
            prim = &g_PrimBuf[self->primIndex];
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = 0;
            prim->drawMode =
                DRAW_TRANSP | DRAW_COLORS | DRAW_TPAGE | DRAW_TPAGE2;
            prim->drawMode =
                DRAW_TRANSP | DRAW_COLORS | DRAW_TPAGE | DRAW_UNK_40;
            self->step++;
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;

    case 5:
        prim = &g_PrimBuf[self->primIndex];
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 = ++prim->b3;
        if (prim->r0 == 0xFF) {
            if (g_PlayableCharacter != PLAYER_ALUCARD) {
                D_800978B4 = 4;
                g_GameState = Game_Ending;
                g_GameStep = 0;
            } else {
                player = &PLAYER;
                player->posX.i.hi -= 0x200;
            }
            self->step++;
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;

    case 6:
    case 7:
        break;
    }
}

void func_us_8019F9C0(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 animResult;

    switch (self->step) {
    case 0:
        primIndex = (s16)g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            InitializeEntity(g_EInitCommon);
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            prim->tpage = 0x1A;
            prim->clut = 0x19F;
            prim->u0 = prim->u2 = 1;
            prim->u1 = prim->u3 = 0x3F;
            prim->v0 = prim->v1 = 0xC1;
            prim->v2 = prim->v3 = 0xFF;
            prim->x0 = prim->x1 = prim->x2 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = self->posY.i.hi;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02 | DRAW_HIDE;
            self->animSet = ANIMSET_OVL(1);
            self->animCurFrame = 4;
#ifdef VERSION_PSP
            self->zPriority--;
#else
            self->zPriority = 0x64;
#endif
        }
        break;

    case 1:
        if (g_CutsceneFlags & 0x400) {
            SetStep(2);
        }
        break;

    case 2:
        if (g_PlayableCharacter != PLAYER_ALUCARD) {
            g_CutsceneFlags |= 0x800;
        } else {
            animResult = AnimateEntity(glassAnimation, self);
            if ((animResult & 0x80) && (self->pose == 7)) {
                g_api.PlaySfx(SFX_RCEN_GLASS_BREAKS);
            }
            if (animResult == 0) {
                g_CutsceneFlags |= 0x800;
                SetStep(3);
                self->ext.utimer.t = 0;
            }
        }
        break;

    case 3:
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = --prim->x2;
        prim->x1 = ++prim->x3;
        prim->y0 = --prim->y1;
        prim->y2 = ++prim->y3;
        prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_UNK_40;
        if (prim->x0 < -0x40) {
            self->step++;
        }
        break;

    case 4:
        break;
    }
}

void func_us_801B4148_from_bo0(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 6;
#ifdef VERSION_PSP
        self->zPriority -= 2;
#else
        self->zPriority = 0x63;
#endif
    case 1:
        break;
    }
}

void func_us_801C123C_from_no4(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 7;
        self->drawFlags = ENTITY_ROTATE;
        self->rotate = 0x800;
        self->zPriority++;
    case 1:
        break;
    }
}
