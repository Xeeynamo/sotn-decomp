// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "no0.h"

typedef enum Statues {
    /* 0 */ RIGHT_STATUE,
    /* 1 */ LEFT_STATUE,
} Statues;

extern u16 g_Statues[];

#ifdef VERSION_PSP
extern u32 D_psp_092A1D00;
extern u32 D_psp_092A1D08;
#endif

void func_us_801CCAAC(Entity* self) {
    s32 minute;
    s32 hour;

    if (!(self->ext.clockRoom.unk88 & 0x1F)) {
        g_api.PlaySfxVolPan(SFX_STONE_MOVE_A, 0x40, 0);
    }
    self->ext.clockRoom.unk88++;

    // Minute hand
    minute =
        (self->ext.clockRoom.unk88 * LOW((self + 5)->ext.clockRoom.bellTimer)) /
        512;
    (self + 5)->ext.clockRoom.hand =
        (s16)((self + 5)->ext.clockRoom.unk80 + minute) % 3600;

    // Hour hand
    hour =
        (self->ext.clockRoom.unk88 * LOW((self + 6)->ext.clockRoom.bellTimer)) /
        512;
    (self + 6)->ext.clockRoom.hand =
        (s16)((self + 6)->ext.clockRoom.unk80 - hour) % 3600;
}

void UpdateBirdcages(Entity* self, u32 timerMinutes) {
    // self + 7 is birdcage door 1
    self += 7;
    if (timerMinutes >= 10 && timerMinutes < 30) {
        self->ext.birdcage.state = true;
    } else {
        self->ext.birdcage.state = false;
    }

    // self + 8 is birdcage door 2
    self += 1;
    if (timerMinutes >= 30 && timerMinutes < 50) {
        self->ext.birdcage.state = true;
    } else {
        self->ext.birdcage.state = false;
    }
}

void UpdateClockHands(Entity* self, PlayerStatus* status) {
    // self + 5 is the minute hand
    self += 5;
    self->ext.clockRoom.hand = status->timerMinutes * 60;

    // self + 6 is the hour hand
    self += 1;
    self->ext.clockRoom.hand =
        (status->timerHours * 300) + (status->timerMinutes * 5);
}

void EntityClockRoomController(Entity* self) {
    PlayerStatus* status = &g_Status;
    Primitive* prim;
    Entity* entity;
    s32 primIndex;
    u16 i;
    s16 posX;

    // Plays the clock bell
    if (self->ext.clockRoom.bellTimer) {
        if (!self->ext.clockRoom.bellDuration) {
            g_api.PlaySfx(SFX_CLOCK_BELL);
            if (--self->ext.clockRoom.bellTimer) {
                self->ext.clockRoom.bellDuration = 64;
            }
        } else {
            self->ext.clockRoom.bellDuration--;
        }
    }

    // Controls the statues
    entity = &PLAYER;
    if (g_unkGraphicsStruct.D_800973FC == 0) {
        if (entity->posY.i.hi > 128) {
            g_Statues[RIGHT_STATUE] = false;
        }
    } else if (!self->ext.clockRoom.unk8A) {
        g_Statues[RIGHT_STATUE] = true;
    }

    self->ext.clockRoom.unk8A = g_unkGraphicsStruct.D_800973FC;

    // Every other minute the top left statue opens
    if (status->timerMinutes & 1) {
        if (entity->posY.i.hi > 128) {
            g_Statues[LEFT_STATUE] = false;
        }
    } else {
        g_Statues[LEFT_STATUE] = true;
    }

    switch (self->step) {
    case 0:
        if (!(g_Timer % 60)) {
            g_api.PlaySfx(SFX_CLOCK_ROOM_TICK);
        }

        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex == -1) {
            return;
        }
        InitializeEntity(g_EInitCommon);
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        prim->x0 = prim->x2 = prim->y0 = prim->y1 = 0;
        prim->x1 = prim->x3 = prim->y2 = prim->y3 = 256;
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x1F0;
        prim->drawMode = DRAW_HIDE;

        g_api.PlaySfx(SET_STOP_MUSIC);
        D_80097928 = 1;
        D_80097910 = 0;
        entity = &PLAYER;
        g_Statues[RIGHT_STATUE] = false; // right statue closed

        if (entity->posY.i.hi < 64) {
            if (entity->posX.i.hi < 64) {
                g_Statues[LEFT_STATUE] = true;
            } else if (entity->posX.i.hi > 0xC0) {
                g_Statues[RIGHT_STATUE] = true;
            }
        }

        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 23;
        self->zPriority = 0x40;

        // Create clock hands
        entity = self + 5;
        for (i = 0; i < 2; i++, entity++) {
            CreateEntityFromCurrentEntity(E_CLOCK_HANDS, entity);
            entity->params = i;
        }
        UpdateClockHands(self, status);

        // Create Birdcage doors
        entity = self + 7;
        for (i = 0; i < 2; i++, entity++) {
            CreateEntityFromCurrentEntity(E_BIRDCAGE_DOOR, entity);
            entity->params = i;
        }
        UpdateBirdcages(self, status->timerMinutes);

        // Shadow for the Bighorn sheep head on the center
        entity = self + 9;
        CreateEntityFromCurrentEntity(E_CLOCK_ROOM_SHADOW, entity);
        entity->animSet = ANIMSET_OVL(1);
        entity->animCurFrame = 23;
        entity->zPriority = 0x40;
        entity->palette = PAL_OVL(0x4B);
        entity->drawFlags = FLAG_DRAW_UNK8;
        entity->drawMode = DRAW_TPAGE;
        entity->posY.i.hi += 4;

        // Create path blocking statues
        entity = self + 1;
        for (i = 0; i < 2; i++, entity++) {
            CreateEntityFromCurrentEntity(E_STATUE, entity);
            entity->params = i;
        }

        // Create the gears that drive the statues
        entity = self + 12;
        for (i = 0; i < 2; i++, entity++) {
            CreateEntityFromCurrentEntity(E_STATUE_GEAR, entity);
            entity->params = i;
        }

        // Create the stones on the floor
        entity = self + 14;
        for (i = 0; i < 2; i++, entity++) {
            CreateEntityFromCurrentEntity(E_STONE_DOOR, entity);
            entity->params = i;
        }
        break;
    case 1:
        if (!status->timerFrames) {
            g_api.PlaySfx(SFX_CLOCK_ROOM_TICK);
        }

        UpdateClockHands(self, status);
        if (status->timerSeconds == 0 && status->timerFrames == 0) {
            if (status->timerMinutes == 0) {
                self->ext.clockRoom.bellTimer =
                    ((status->timerHours + 11) % 12) + 1;
                if (!self->ext.clockRoom.bellTimer) {
                    self->ext.clockRoom.bellTimer = 12;
                }
            } else if (((status->timerMinutes != 0) ^ 1) == 30) {
                self->ext.clockRoom.bellTimer = 1;
            }
        }

        UpdateBirdcages(self, status->timerMinutes);

        if (!g_CastleFlags[CLOCK_ROOM_DOORS]) {
            entity = &PLAYER;
            if (entity->posX.i.hi >= 48 && entity->posX.i.hi < 209) {
                i = g_Status.equipment[ACCESSORY_1_SLOT];
                // Wearing silver and gold ring opens the stone floor
                if (i == ITEM_GOLD_RING || i == ITEM_SILVER_RING) {
                    i = g_Status.equipment[ACCESSORY_2_SLOT];
                    if (i == ITEM_GOLD_RING || i == ITEM_SILVER_RING) {
                        SetStep(2);
                    }
                }
            }
        }
        break;
    case 2:
        g_Statues[RIGHT_STATUE] = false;
        g_Statues[LEFT_STATUE] = false;
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        entity = &PLAYER;
        posX = entity->posX.i.hi;
#ifdef VERSION_PSP
        FntPrint("step=%d\n", self->step_s);
#endif
        switch (self->step_s) {
        case 0:
#ifndef VERSION_PSP
            primIndex = g_Player.status; // FAKE
            if (g_Player.status & PLAYER_STATUS_TRANSFORM) {
                if (g_Timer & 1) {
#endif
                    if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
                        g_Player.padSim = PAD_R1;
                    } else if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
#ifdef VERSION_PSP
                        g_Player.padSim = 0;
#else
                g_Player.padSim = PAD_L1;
#endif
                    } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
#ifdef VERSION_PSP
                        g_Player.padSim = PAD_L1;
#else
                g_Player.padSim = PAD_R2;
#endif
                    }
#ifndef VERSION_PSP
                }
            } else {
#else
            {
#endif
                self->ext.clockRoom.unk88 = 0;
                self->step_s++;
            }

            break;
        case 1:
            if (g_Player.pl_vram_flag & 1) {
                self->step_s++;
                if (posX < 73 && posX > 183) {
                    self->step_s++;
                }
            }
            break;
        case 2:
            if (posX > 64 && posX < 128) {
                g_Player.padSim = PAD_LEFT | PAD_CROSS;
            } else if (posX >= 128 && posX < 192) {
                g_Player.padSim = PAD_RIGHT | PAD_CROSS;
            } else if (g_Player.pl_vram_flag & 1) {
                self->step_s++;
            }

#ifdef VERSION_PSP
            if (D_psp_092A1D00 == PLAYER.posX.i.hi &&
                D_psp_092A1D08 == PLAYER.posY.i.hi) {
                g_Player.padSim &= ~PAD_CROSS;
                D_psp_092A1D08 = NULL;
                D_psp_092A1D00 = NULL;
                return;
            }

            D_psp_092A1D08 = PLAYER.posX.i.hi;
            D_psp_092A1D08 = PLAYER.posY.i.hi;
#endif

            break;
        case 3:
            if (posX < 73) {
                if (entity->facingLeft) {
                    g_Player.padSim = PAD_RIGHT;
                }
            } else if (!entity->facingLeft) {
                g_Player.padSim = PAD_LEFT;
            }

            self->step_s++;
            break;
        case 4:
            prim = &g_PrimBuf[self->primIndex];
            prim->r0 = prim->g0 = prim->b0 += 16;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2;
            if (prim->r0 > 192) {
                self->step_s++;
            }
            break;
        case 5:
            prim = &g_PrimBuf[self->primIndex];
            prim->r0 = prim->g0 = prim->b0 -= 4;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            if (prim->r0 < 8) {
                prim->drawMode = DRAW_HIDE;
                self->step_s++;
            }
            break;
        case 6:
            entity = self + 7;
            LOH(entity->ext.clockRoom.unk80) = 1;

            entity++;
            LOH(entity->ext.clockRoom.unk80) = 1;

            self->ext.clockRoom.unk88 = 0x80;
            self->ext.clockRoom.unk88 = 1;
            self->step_s++;
            break;
        case 7:
            if (!--self->ext.clockRoom.unk88) {
                // Minute hand
                entity = self + 5;
                posX = LOW(entity->ext.clockRoom.unk80) =
                    entity->ext.clockRoom.hand;
                LOW(entity->ext.clockRoom.bellTimer) =
                    (0x1518 - (s16)(posX % 3600));

                // Hour hand
                entity++;
                posX = LOW(entity->ext.clockRoom.unk80) =
                    entity->ext.clockRoom.hand;
                LOW(entity->ext.clockRoom.bellTimer) =
                    ((s16)(posX % 3600) + 0x708);

                self->ext.clockRoom.unk88 = 0;
                self->step_s++;
            }
            break;
        case 8:
            func_us_801CCAAC(self);
            if (self->ext.clockRoom.unk88 >= 0x200) {
                self->step_s++;
                self->ext.clockRoom.bellTimer = 13;
                self->ext.clockRoom.unk88 = 0x380;
            }
            break;
        case 9:
            if (!(--self->ext.clockRoom.unk88)) {
                g_CastleFlags[CLOCK_ROOM_DOORS] = 1;
                g_api.func_800F1FC4(0);
                SetStep(3);
                self->ext.clockRoom.unk88 = 0x140;
            }
        }
        break;
    case 3:
        g_Statues[RIGHT_STATUE] = false;
        g_Statues[LEFT_STATUE] = false;
        switch (self->step_s) {
        case 0:
            if (!(--self->ext.clockRoom.unk88)) {
                // Minute hand
                entity = self + 5;
                LOW(entity->ext.clockRoom.unk80) = entity->ext.clockRoom.hand;
                LOW(entity->ext.clockRoom.bellTimer) =
                    ((s16)(status->timerMinutes * 60) + 0x708);

                // Hour hand
                entity++;
                LOW(entity->ext.clockRoom.unk80) = entity->ext.clockRoom.hand;
                LOW(entity->ext.clockRoom.bellTimer) =
                    0x1518 - (s16)((status->timerHours * 300) +
                                   (status->timerMinutes * 5));

                self->ext.clockRoom.unk88 = 0;
                self->step_s++;
            }
            break;
        case 1:
            func_us_801CCAAC(self);
            if (self->ext.clockRoom.unk88 >= 0x200) {
                SetStep(1);
            }
        }
        break;
    }
}

#include "../clock_room_entities.h"
