// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dre.h"

extern EInit D_8018047C;

extern s32 g_CutsceneFlags;
extern s32 g_SkipCutscene;

#ifdef VERSION_PSP
extern u8* D_801816C0; // defined in st_init_psp
#else
extern u8 D_801816C0; // defined in cutscene_data
#endif
// Animation, EntityCSMoveAlucard
static AnimateEntityFrame D_80180944[] = {
    {4, 185},  {4, 186}, {4, 187}, {4, 188}, {4, 189}, {4, 190},
    {16, 191}, {8, 192}, {8, 193}, {8, 194}, {8, 195}, POSE_END};

// Pans the camera until Alucard's screen X coordinate matches the target value
static void CutsceneCameraPan(s16 arg0) {
    s16 target = arg0;
    s16 delta;

    delta = target - g_unkGraphicsStruct.unkC;

    if (delta > 1) { // pan left
        // Appears to be Alucard's X coordinates in screen space
        g_unkGraphicsStruct.unkC++;
    } else if (delta < -1) { // pan right
        g_unkGraphicsStruct.unkC--;
    } else {
        g_unkGraphicsStruct.unkC = target;
    }
}

void EntityCSMoveAlucard(Entity* self) {
    Tilemap* currentRoomTileLayout = &g_Tilemap;
    Entity* player = &PLAYER;
    s16 posX;

#ifndef VERSION_PSP
    FntPrint("step %x\n", self->step);
#endif

    if (g_SkipCutscene && (self->step < 8)) {
        SetStep(8);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_8018047C);
        g_PauseAllowed = false;
        g_unkGraphicsStruct.pauseEnemies = 1;
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
#ifdef VERSION_PSP
        self->ext.utimer.t = 128;
#else
        if (g_DemoMode != Demo_None) {
            self->ext.utimer.t = 64;
        } else {
            self->ext.utimer.t = 128;
        }
#endif
        break;
    case 1:
        g_Player.padSim = PAD_NONE;
        if (self->ext.utimer.t) {
            self->ext.utimer.t--;
        }
        if (g_Player.status & PLAYER_STATUS_TRANSFORM) {
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
        } else if (!self->ext.utimer.t) {
            self->step++;
            g_Player.padSim = PAD_RIGHT;
        }
        g_Player.demo_timer = 1;
        break;

    case 2: // Alucard walks forward
        g_Player.padSim = PAD_RIGHT;
        posX = player->posX.i.hi + currentRoomTileLayout->scrollX.i.hi;
        if (posX > 256) {
            if (!(g_CutsceneFlags & 1)) {
                g_CutsceneFlags |= 1;
            }
        }
        if (posX > 288) {
            g_Player.padSim = PAD_NONE;
            player->posX.i.hi = 288 - currentRoomTileLayout->scrollX.i.hi;
            self->step++;
        }
        g_Player.demo_timer = 1;
        break;

    case 3: // Alucard stops walking
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        CutsceneCameraPan(0x20);
        if (g_CutsceneFlags & 2) {
            self->step++;
        }
        break;

    case 4:
        g_Player.padSim = PAD_RIGHT;
        posX = player->posX.i.hi + currentRoomTileLayout->scrollX.i.hi;
        if (posX > 256) {
            if (!(g_CutsceneFlags & 1)) {
                g_CutsceneFlags |= 1;
            }
        }
        if (posX > 352) {
            g_Player.padSim = PAD_NONE;
            player->posX.i.hi = 352 - currentRoomTileLayout->scrollX.i.hi;
            posX = 352;
            self->step++;
        }
        g_unkGraphicsStruct.unkC = posX - 256;
        g_Player.demo_timer = 1;
        break;

    case 5: // Conversation with fake lisa
        g_Player.demo_timer = 1;
        if (g_CutsceneFlags & 8) {
            SetStep(6);
        }
        break;

    case 6: // Alucard's reaction to realizing she's not his mother
        g_Player.demo_timer = 1;
        if (!AnimateEntity(D_80180944, self)) {
            SetStep(7);
        } else {
            player->animCurFrame = self->animCurFrame;
        }
        break;

    case 7:
        g_Player.demo_timer = 1;
        if (g_CutsceneFlags & 0x200) {
            SetStep(8);
        }
        break;

    case 8:
        CutsceneCameraPan(0x80);
        if (g_unkGraphicsStruct.unkC == 0x80) {
            g_PauseAllowed = true;
            if (g_unkGraphicsStruct.pauseEnemies) {
                g_unkGraphicsStruct.pauseEnemies = 0;
            }
            DestroyEntity(self);
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;
    }
}

// appears to load from the CD and freeze the game
void EntityUnkId23(Entity* self) {
    Tilemap* currentRoomTileLayout = &g_Tilemap;
    Entity* player = &PLAYER;
    Entity* entity = &g_Entities[80];
    s16 delta;

    switch (self->step) {
    case 0:
        InitializeEntity(D_8018047C);
        g_PauseAllowed = false;
        g_unkGraphicsStruct.pauseEnemies = 1;
        g_Player.padSim = PAD_NONE;
        if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
            g_Player.padSim = PAD_BAT;
        } else if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
            g_Player.padSim = PAD_MIST;
        } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            g_Player.padSim = PAD_WOLF;
        }
        g_Player.demo_timer = 1;
        break;

    case 1:
        g_Player.padSim = PAD_NONE;
        if (g_Player.status & PLAYER_STATUS_TRANSFORM) {
            if (g_Timer & 1) {
                if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
                    g_Player.padSim = PAD_BAT;
                } else if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
                    g_Player.padSim = PAD_MIST;
                } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
                    g_Player.padSim = PAD_WOLF;
                }
            }
        } else if (
            (g_Player.vram_flag & TOUCHING_GROUND) && (g_CutsceneFlags & 2)) {
            delta = player->posX.i.hi - entity->posX.i.hi;
            if (delta < -0x50) {
                g_Player.padSim = PAD_RIGHT;
#ifdef VERSION_PSP
                *D_801816C0 = 0;
#else
                D_801816C0 = 0;
#endif
                self->step += 3;
            } else if (delta > 0x50) {
                g_Player.padSim = PAD_LEFT;
#ifdef VERSION_PSP
                *D_801816C0 = 1;
#else
                D_801816C0 = 1;
#endif
                self->step += 3;
            } else if (entity->facingLeft) {
                g_Player.padSim = PAD_RIGHT;
                self->step++;
            } else {
                g_Player.padSim = PAD_LEFT;
                self->step += 2;
            }
        }
        g_Player.demo_timer = 1;
        break;

    case 2:
        g_Player.padSim = PAD_RIGHT;
        delta = player->posX.i.hi - entity->posX.i.hi;
        if (delta > 64) {
            g_Player.padSim = PAD_LEFT;
#ifdef VERSION_PSP
            *D_801816C0 = 1;
#else
            D_801816C0 = 1;
#endif
            self->step += 2;
        }
        g_Player.demo_timer = 1;
        break;

    case 3:
        g_Player.padSim = PAD_LEFT;
        delta = player->posX.i.hi - entity->posX.i.hi;
        if (delta < -64) {
            g_Player.padSim = PAD_RIGHT;
#ifdef VERSION_PSP
            *D_801816C0 = 0;
#else
            D_801816C0 = 0;
#endif
            self->step++;
        }
        g_Player.demo_timer = 1;
        break;

    case 4:
        g_CutsceneFlags |= 1;
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        if (g_CutsceneFlags & 0x20) {
            self->step++;
        }
        break;

    case 5:
        g_PauseAllowed = true;
        if (g_unkGraphicsStruct.pauseEnemies) {
            g_unkGraphicsStruct.pauseEnemies = 0;
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        player->posY.i.hi += 0x100;
        break;
    }
}

void EntityFadeToWhite1(Entity* self) {
    Tilemap* currentRoomTileLayout = &g_Tilemap;
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex != -1) {
            InitializeEntity(D_8018047C);
            self->animSet = ANIMSET_DRA(0);
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 0x100;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0xE0;
            PRED(prim) = PGRN(prim) = PBLU(prim) = 0;
            prim->priority = 192;
            prim->drawMode = DRAW_HIDE;
        }
        break;

    case 1:
        if (g_CutsceneFlags & 0x10) {
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            g_api.PlaySfx(SFX_FM_EXPLODE_A); // Fade to white
            self->step++;
        }
        break;

    case 2:
        prim = &g_PrimBuf[self->primIndex];
        PRED(prim) = PGRN(prim) = PBLU(prim) += 4;
        if (prim->r0 > 240) {
            g_CutsceneFlags |= 0x20;
            self->ext.fadeToWhite.unk7C = 1;
            self->ext.fadeToWhite.unk7E = 0x200;
            self->ext.fadeToWhite.unk80 = 0;
            g_api.PlaySfx(SFX_SUC_APPEAR);
            self->step++;
        }
        break;

    case 3:
        prim = &g_PrimBuf[self->primIndex];
        PRED(prim) = PGRN(prim) = PBLU(prim) -= 2;
        if (prim->r0 < 4) {
            prim->drawMode = DRAW_HIDE;
            self->step++;
        }
        break;

    case 4:
        if (g_CutsceneFlags & 0x200) {
            self->ext.fadeToWhite.unk7C = 0;
            g_api.PlaySfx(0xA1);
            DestroyEntity(self);
        }
        break;
    }

    if (self->ext.fadeToWhite.unk7C) {
        if (!--self->ext.fadeToWhite.unk7E) {
            g_api.PlaySfx(SFX_SUC_APPEAR);
        }
    }
}

void EntityFadeToWhite2(Entity* self) {
    Tilemap* currentRoomTileLayout = &g_Tilemap;
    Primitive* prim;
    s32 primIndex;
    s32 i;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_G4, 2);
        if (primIndex != -1) {
            InitializeEntity(D_8018047C);
            self->animSet = ANIMSET_DRA(0);
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            for (i = 0; prim != NULL; i++) {
                prim->x0 = prim->x2 = 0;
                prim->x1 = prim->x3 = 256;
                prim->y0 = prim->y1 = 0;
                prim->y2 = prim->y3 = 224;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = 0;
                prim->priority = i + 192;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        }
        break;

    case 1:
        if (g_CutsceneFlags & 0x10) {
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            self->step++;
        }
        break;

    case 2:
        prim = &g_PrimBuf[self->primIndex];
        PRED(prim) = PGRN(prim) = PBLU(prim) += 2;
        if (prim->r0 > 252) {
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            self->step++;
        }
        break;

    case 3:
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        PRED(prim) = PGRN(prim) = PBLU(prim) += 8;
        if (prim->r0 > 240) {
            g_CutsceneFlags |= 0x40;
            self->step++;
        }
        break;

    case 4:
        break;
    }
}
