// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

// if the player is transformed, transform alucard back
// into alucard form
bool func_us_801A8FC0(void) {
    if (g_Player.status & PLAYER_STATUS_TRANSFORM) {
        g_Player.padSim = PAD_NONE;
        if (g_Timer & 1) {
            if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
                g_Player.padSim = PAD_R1;
            } else if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
                g_Player.padSim = PAD_L1;
            } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
                g_Player.padSim = PAD_R2;
            }
        }
        return true;
    }
    return false;
}

void func_801961DC(s16 arg0) {
    s16 tileOffset;

    tileOffset = arg0 - g_Tilemap.height;
    if (tileOffset >= 2) {
        g_Tilemap.height++;
    } else if (tileOffset < -1) {
        g_Tilemap.height--;
    } else {
        g_Tilemap.height = arg0;
    }
}


extern s32 g_CutsceneFlags;
extern EInit g_EInitInteractable;

void func_us_801A9084(Entity* self) {
    s16 playerGlobalX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        g_PauseAllowed = false;
        g_unkGraphicsStruct.pauseEnemies = true;
        g_Player.padSim = 0x8000;
        g_Entities[1].ext.entSlot1.unk0 = 0;
        g_Player.demo_timer = 1;
        break;

    case 1:
        if (playerGlobalX > 0xC0) {
            g_Player.padSim = 0x8000;
        } else {
            g_Player.padSim = 0;
            g_CutsceneFlags = 1;
            self->step++;
        }
        g_Player.demo_timer = 1;
        break;

    case 2:
        if (g_CutsceneFlags & 2) {
            self->step++;
        }
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        break;

    case 3:
        g_PauseAllowed = true;
        if (g_unkGraphicsStruct.pauseEnemies != false) {
            g_unkGraphicsStruct.pauseEnemies = false;
        }
        g_Entities[1].ext.entSlot1.unk0 = 1;
        DestroyEntity(self);
        break;
    }
}


extern s32 g_CutsceneFlags;
extern EInit g_EInitInteractable;

void func_us_801A9208(Entity* self) {
    Primitive* prim;
    s16 primIndex;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex != -1) {
            InitializeEntity(g_EInitInteractable);
            prim = &g_PrimBuf[primIndex];
            g_unkGraphicsStruct.pauseEnemies = true;
            g_PauseAllowed = false;
            self->primIndex = primIndex;
            self->animSet = 0;
            self->flags |= FLAG_HAS_PRIMS;

            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 0x100;
            prim->y0 = prim->y1 = 4;
            prim->y2 = prim->y3 = 0xE8;

            prim->r0 = prim->r1 = prim->r2 = prim->r3 =
                prim->g0 = prim->g1 = prim->g2 = prim->g3 =
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;

            prim->priority = 0x1F8;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            self->ext.utimer.t = 0;
            g_api.PlaySfx(0x62F);
        }
        self->flags |= FLAG_UNK_10000;
        break;
    case 1:
        self->ext.utimer.t++;
        prim = &g_PrimBuf[self->primIndex];
        if (self->ext.utimer.t > 8) {
            self->step++;
            prim->drawMode = DRAW_HIDE;
        } else  if (self->ext.utimer.t & 1) {
            prim->drawMode = DRAW_HIDE;
        } else {
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        }
        break;
    case 2:
        if (g_CutsceneFlags & 0x100) {
            g_unkGraphicsStruct.unk20 = 0;
            self->step++;
            self->ext.utimer.t = 0;
            prim = &g_PrimBuf[self->primIndex];
            prim->r0 = prim->r1 = prim->r2 = prim->r3 =
                prim->g0 = prim->g1 = prim->g2 = prim->g3 =
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            
        }
        break;
    case 3:
        prim = &g_PrimBuf[self->primIndex];
        prim->r0 = prim->r1 = prim->r2 = prim->r3 =
            prim->g0 = prim->g1 = prim->g2 = prim->g3 =
            prim->b0 = prim->b1 = prim->b2 = prim->b3 += 1;

        if (prim->r0 == 0xFF) {
            prim->drawMode = DRAW_COLORS;
            self->step++;
        }
        break;
    case 4:
        prim = &g_PrimBuf[self->primIndex];
        prim->r0 = prim->r1 = prim->r2 = prim->r3 =
            prim->g0 = prim->g1 = prim->g2 = prim->g3 =
            prim->b0 = prim->b1 = prim->b2 = prim->b3 -= 4;

        if (prim->r0 < 5) {
            g_PauseAllowed = true;
            if (g_unkGraphicsStruct.pauseEnemies != false) {
                g_unkGraphicsStruct.pauseEnemies = false;
            }
            if (g_CastleFlags[0xD8] != 0) {
                D_800978B4 = 2;
            } else {
                D_800978B4 = 1;
            }
            g_GameState = Game_Ending;
            g_GameStep = 0;
            self->step++;
        }
        break;
    }
}

extern s32 g_CutsceneFlags;
extern EInit g_EInitInteractable;

void func_us_801A95F4(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    Entity* richter;

    richter = &RIC;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex != -1) {
            InitializeEntity(g_EInitInteractable);
            prim = &g_PrimBuf[primIndex];
            g_unkGraphicsStruct.pauseEnemies = true;
            g_PauseAllowed = false;
            self->primIndex = (s32) primIndex;
            self->animSet = 0;
            self->flags |= FLAG_HAS_PRIMS;
            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 0x100;
            prim->y0 = prim->y1 = 4;
            prim->y2 = prim->y3 = 0xE8;
            prim->priority = 0x1F8;
            prim->r0 = prim->r1 = prim->r2 = prim->r3 =
                prim->g0 = prim->g1 = prim->g2 = prim->g3 =
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        }
        break;
    case 1:
        g_Player.padSim = 0;
        if ((func_us_801A8FC0() == 0) &&
            (self->step_s == 0) && (g_Player.vram_flag & 1)) {
            if (self->posX.i.hi < richter->posX.i.hi) {
                g_Player.padSim = PAD_RIGHT;
            } else {
                g_Player.padSim = PAD_LEFT;

            }
            self->step_s++;
        }
        g_Player.demo_timer = 1;
        if (g_CutsceneFlags & 0x40) {
            self->step++;
        }
        break;
    case 2:
        g_Player.demo_timer = 1;
        prim = &g_PrimBuf[self->primIndex];
        prim->r0 = prim->r1 = prim->r2 = prim->r3 =
            prim->g0 = prim->g1 = prim->g2 = prim->g3 =
            prim->b0 = prim->b1 = prim->b2 = prim->b3 += 1;

        if (prim->r0 == 0xFF) {
            prim->drawMode = DRAW_COLORS;
            self->step++;
        }
        break;
    case 3:
        g_Player.demo_timer = 1;
        prim = &g_PrimBuf[self->primIndex];
        prim->r0 = prim->r1 = prim->r2 = prim->r3 =
            prim->g0 = prim->g1 = prim->g2 = prim->g3 =
            prim->b0 = prim->b1 = prim->b2 = prim->b3 -= 4;
        if ((u8) prim->r0 < 5U) {
            g_PauseAllowed = true;
            if (g_unkGraphicsStruct.pauseEnemies != false) {
                g_unkGraphicsStruct.pauseEnemies = false;
            }
            D_800978B4 = 0;
            g_GameState = Game_Ending;
            g_GameStep = 0;
            self->step++;
        }
        break;
    case 4:
        break;
    }
}

void func_us_801A9944(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        g_unkGraphicsStruct.pauseEnemies = true;
        self->animSet = 0;
        g_PauseAllowed = false;
        if (RIC.posX.i.hi < 0x80) {
            if (PLAYER.posX.i.hi < 0xC0) {
                g_Player.padSim = 0x2000;
            } else {
                g_Player.padSim = 0x8000;
            }
        } else {
            if (PLAYER.posX.i.hi > 0x40) {
                g_Player.padSim = 0x8000;
            } else {
                g_Player.padSim = 0x2000;
            }
        }
        break;

    case 1:
        g_Player.padSim = 0;
        if (func_us_801A8FC0() == false) {
            if (RIC.posX.i.hi < 0x80) {
                if (PLAYER.posX.i.hi < 0xC0) {
                    g_Player.padSim = 0x2000;
                } else {
                    if (PLAYER.facingLeft == 0) {
                        g_Player.padSim = 0x8000;
                    }
                    self->step++;
                }
            } else if (PLAYER.posX.i.hi > 0x40) {
                g_Player.padSim = 0x8000;
            } else {
                if (PLAYER.facingLeft != 0) {
                    g_Player.padSim = 0x2000;
                }
                self->step++;
            }
        }
        g_Player.demo_timer = 1;
        break;

    case 2:
        g_Player.padSim = 0;
        g_Player.demo_timer = 1;
        if (g_CutsceneFlags & 8) {
            g_PauseAllowed = true;
            if (g_unkGraphicsStruct.pauseEnemies != false) {
                g_unkGraphicsStruct.pauseEnemies = false;
            }
            DestroyEntity(self);
        }
        return;
    }
}
