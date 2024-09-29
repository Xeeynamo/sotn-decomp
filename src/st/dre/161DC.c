// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dre.h"

void func_801961DC(s16 arg0) {
    s16 temp_v0 = arg0 - g_unkGraphicsStruct.unkC;

    if (temp_v0 > 1) {
        g_unkGraphicsStruct.unkC++;
    } else if (temp_v0 < -1) {
        g_unkGraphicsStruct.unkC--;
    } else {
        g_unkGraphicsStruct.unkC = arg0;
    }
}

void EntityCSMoveAlucard(Entity* self) {
    Tilemap* currentRoomTileLayout = &g_Tilemap;
    Entity* player = &PLAYER;
    s16 posX;

    FntPrint("step %x\n", self->step);
    if (g_SkipCutscene && (self->step < 8)) {
        SetStep(8);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_8018047C);
        D_8003C8B8 = 0;
        g_unkGraphicsStruct.unk0 = 1;
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        if (g_DemoMode != Demo_None) {
            self->ext.generic.unk7C.s = 64;
        } else {
            self->ext.generic.unk7C.s = 128;
        }
        break;

    case 1:
        g_Player.padSim = 0;
        if (self->ext.generic.unk7C.u != 0) {
            self->ext.generic.unk7C.u--;
        }
        if (g_Player.unk0C & 7) {
            if (g_Timer & 1) {
                if (g_Player.unk0C & 1) {
                    g_Player.padSim = 8;
                } else if (g_Player.unk0C & 2) {
                    g_Player.padSim = 4;
                } else if (g_Player.unk0C & 4) {
                    g_Player.padSim = 2;
                }
            }
        } else if (self->ext.generic.unk7C.u == 0) {
            self->step++;
            g_Player.padSim = 0x2000;
        }
        g_Player.D_80072EFC = 1;
        break;

    case 2: // Alucard walks forward
        g_Player.padSim = 0x2000;
        posX = player->posX.i.hi + currentRoomTileLayout->scrollX.i.hi;
        if (posX > 256) {
            if (!(g_CutsceneFlags & 1)) {
                g_CutsceneFlags |= 1;
            }
        }
        if (posX > 288) {
            g_Player.padSim = 0;
            player->posX.i.hi = 288 - currentRoomTileLayout->scrollX.i.hi;
            self->step++;
        }
        g_Player.D_80072EFC = 1;
        break;

    case 3: // Alucard stops walking
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        func_801961DC(0x20);
        if (g_CutsceneFlags & 2) {
            self->step++;
        }
        break;

    case 4:
        g_Player.padSim = 0x2000;
        posX = player->posX.i.hi + currentRoomTileLayout->scrollX.i.hi;
        if (posX > 256) {
            if (!(g_CutsceneFlags & 1)) {
                g_CutsceneFlags |= 1;
            }
        }
        if (posX > 352) {
            g_Player.padSim = 0;
            player->posX.i.hi = 352 - currentRoomTileLayout->scrollX.i.hi;
            posX = 352;
            self->step++;
        }
        g_unkGraphicsStruct.unkC = posX - 256;
        g_Player.D_80072EFC = 1;
        break;

    case 5: // Conversation with fake lisa
        g_Player.D_80072EFC = 1;
        if (g_CutsceneFlags & 8) {
            SetStep(6);
        }
        break;

    case 6: // Alucard's reaction to realizing she's not his mother
        g_Player.D_80072EFC = 1;
        if (AnimateEntity(D_80180944, self) == 0) {
            SetStep(7);
        } else {
            player->animCurFrame = self->animCurFrame;
        }
        break;

    case 7:
        g_Player.D_80072EFC = 1;
        if (g_CutsceneFlags & 0x200) {
            SetStep(8);
        }
        break;

    case 8:
        func_801961DC(0x80);
        if (g_unkGraphicsStruct.unkC == 0x80) {
            D_8003C8B8 = 1;
            if (g_unkGraphicsStruct.unk0 != 0) {
                g_unkGraphicsStruct.unk0 = 0;
            }
            DestroyEntity(self);
        }
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        break;
    }
}

// appears to load from the CD and freeze the game
void EntityUnkId23(Entity* self) {
    Entity* player = &PLAYER;
    Entity* ent = &g_Entities[80];
    s16 diff;

    switch (self->step) {
    case 0:
        InitializeEntity(D_8018047C);
        D_8003C8B8 = 0;
        g_unkGraphicsStruct.unk0 = 1;
        g_Player.padSim = 0;
        if (g_Player.unk0C & PLAYER_STATUS_BAT_FORM) {
            g_Player.padSim = PAD_R1;
        } else if (g_Player.unk0C & PLAYER_STATUS_MIST_FORM) {
            g_Player.padSim = PAD_L1;
        } else if (g_Player.unk0C & PLAYER_STATUS_WOLF_FORM) {
            g_Player.padSim = PAD_R2;
        }
        g_Player.D_80072EFC = PAD_L2;
        break;

    case 1:
        g_Player.padSim = 0;
        if (g_Player.unk0C & PLAYER_STATUS_TRANSFORM) {
            if (g_Timer & 1) {
                if (g_Player.unk0C & PLAYER_STATUS_BAT_FORM) {
                    g_Player.padSim = PAD_R1;
                } else if (g_Player.unk0C & PLAYER_STATUS_MIST_FORM) {
                    g_Player.padSim = PAD_L1;
                } else if (g_Player.unk0C & PLAYER_STATUS_WOLF_FORM) {
                    g_Player.padSim = PAD_R2;
                }
            }
        } else if ((g_Player.pl_vram_flag & 1) && (g_CutsceneFlags & 2)) {
            diff = player->posX.i.hi - ent->posX.i.hi;
            if (diff < -0x50) {
                g_Player.padSim = PAD_RIGHT;
                D_801816C0 = 0;
                self->step += 3;
            } else if (diff >= 0x51) {
                g_Player.padSim = PAD_LEFT;
                D_801816C0 = 1;
                self->step += 3;
            } else if (ent->facingLeft) {
                g_Player.padSim = PAD_RIGHT;
                self->step++;
            } else {
                g_Player.padSim = PAD_LEFT;
                self->step += 2;
            }
        }
        g_Player.D_80072EFC = 1;
        break;

    case 2:
        g_Player.padSim = PAD_RIGHT;
        diff = player->posX.i.hi - ent->posX.i.hi;
        if (diff > 64) {
            g_Player.padSim = PAD_LEFT;
            D_801816C0 = 1;
            self->step += 2;
        }
        g_Player.D_80072EFC = 1;
        break;

    case 3:
        g_Player.padSim = PAD_LEFT;
        diff = player->posX.i.hi - ent->posX.i.hi;
        if (diff < -64) {
            g_Player.padSim = PAD_RIGHT;
            D_801816C0 = 0;
            self->step++;
        }
        g_Player.D_80072EFC = 1;
        break;

    case 4:
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        g_CutsceneFlags |= 1;
        if (g_CutsceneFlags & 0x20) {
            self->step++;
        }
        break;

    case 5:
        D_8003C8B8 = 1;
        if (g_unkGraphicsStruct.unk0 != 0) {
            g_unkGraphicsStruct.unk0 = 0;
        }
        player->posY.i.hi = player->posY.i.hi + 0x100;
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        break;
    }
}
