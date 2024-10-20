// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"
#include "game.h"
#include "sfx.h"

extern u32 g_CutsceneFlags;
extern s32 D_8019D428;

// tile layout
static s16 D_8018068C[] = {
    0x014A, 0x014B, 0x014E, 0x014F, 0x014C, 0x014D, 0x0150, 0x0151, 0x00F5,
    0x00F6, 0x012B, 0x012C, 0x00FC, 0x00FD, 0x012F, 0x0130, 0x0101, 0x00FF,
    0x0201, 0x00FF, 0x0201, 0x0307, 0x0407, 0x0507, 0x0607, 0x0707, 0x0807,
    0x0907, 0x0A10, 0x00FF, 0x0A01, 0x0B06, 0x0C06, 0x0D06, 0x0E10, 0x0F0A,
    0x0E0A, 0x0F0A, 0x0E20, 0x00FF, 0x0E01, 0x1004, 0x1104, 0x120B, 0x00FF,
    0x0000, 0x1301, 0x00FF, 0x1201, 0x00FF, 0x1220, 0x1103, 0x1003, 0x1403,
    0x1503, 0x1640, 0x1506, 0x0D05, 0x0C05, 0x0B05, 0x0A20, 0x00FF, 0x0A10,
    0x1710, 0x0A08, 0x00FF, 0x0A01, 0x0B02, 0x0C02, 0x1806, 0x1906, 0x1850,
    0x0C03, 0x0B03, 0x0A08, 0x00FF, 0x0A01, 0x0B03, 0x0C03, 0x0D03, 0x0E03,
    0x1B06, 0x1A10, 0x1B20, 0x0E03, 0x0D03, 0x0C03, 0x00FF, 0x1C04, 0x1D04,
    0x1E04, 0x1F04, 0x00FF, 0x0000, 0x2002, 0x2104, 0x2204, 0x2304, 0x2404,
    0x2504, 0x2604, 0x2704, 0x2002, 0x0000, 0x2808, 0x2908, 0x2A60, 0x00FF,
    0x0C01, 0x00FF,
};

static u8 D_80180768[] = {
    0x08, 0x03, 0x04, 0x04, 0x04, 0x05, 0x04, 0x06, 0x04, 0x07, 0x04, 0x08,
    0x04, 0x09, 0x02, 0x0A, 0x01, 0x0B, 0x10, 0x0A, 0xFF, 0x00, 0x00, 0x00,
};

static u8 D_80180780[] = {
    0x04, 0x0A, 0x04, 0x09, 0x04, 0x08, 0x04, 0x07, 0x04, 0x06, 0x04, 0x05,
    0x04, 0x04, 0x04, 0x03, 0x02, 0x0C, 0x04, 0x03, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00,
    0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01,
};

void func_8018F890(s16 arg0) {
    s16 temp_v0 = arg0 - g_Tilemap.height;

    if (temp_v0 > 1) {
        g_Tilemap.height++;
    } else if (temp_v0 < -1) {
        g_Tilemap.height--;
    } else {
        g_Tilemap.height = arg0;
    }
}

void func_8018F8EC(u16 index) {
    Tilemap* tilemap = &g_Tilemap;
    u16 tilePos = 0x5B6;
    u16* tileLayoutPtr = &D_8018068C[index * 8];
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            tilemap->fg[tilePos] = *tileLayoutPtr;
            tileLayoutPtr++;
            tilePos++;
        }
        tilePos += 0x2C;
    }
}

// platform that lifts you into chamber, starts cutscene, gives you holy glasses
void EntityPlatform(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* player = &PLAYER;
    Primitive* prim;
    s16 primIndex;
    s16 temp_a0;
    s16 temp_s1;
    s16 temp_v0;
    s16 temp_v1_4;
    u16 temp_a1;

    self->posY.i.hi -= 8;
    temp_a1 = GetPlayerCollisionWith(self, 0x20, 0x11, 4);
    temp_s1 = player->posX.i.hi + g_Tilemap.scrollX.i.hi;
    temp_v0 = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            InitializeEntity(g_EInitGeneric);
            self->animSet = ANIMSET_OVL(2);
            self->animCurFrame = 9;
            self->zPriority = 0x80;

            if (g_CastleFlags[HG_CS_DONE] != 0) {
                self->step = 9;
            }

            func_8018F8EC(0);
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->flags |= FLAG_HAS_PRIMS;
            prim->tpage = 0xF;
            prim->clut = 2;
            prim->u0 = prim->u2 = 0xA0;
            prim->u1 = prim->u3 = 0xB0;
            prim->v0 = prim->v1 = 0xA1;
            prim->v2 = prim->v3 = 0xA7;
            prim->priority = 0x7F;
            prim->drawMode = DRAW_UNK02;
        }
        break;

    case 1:
        if ((GetDistanceToPlayerX() < 32) &&
            ((self->posY.i.hi - player->posY.i.hi) < 80)) {
            D_8003C8B8 = 0;
            g_unkGraphicsStruct.unk0 = 1;
            if (g_Player.unk0C & PLAYER_STATUS_BAT_FORM) {
                g_Player.padSim = PAD_R1;
            } else if (g_Player.unk0C & PLAYER_STATUS_MIST_FORM) {
                g_Player.padSim = PAD_L1;
            } else if (g_Player.unk0C & PLAYER_STATUS_WOLF_FORM) {
                g_Player.padSim = PAD_R2;
            } else if (temp_s1 > 384) {
                g_Player.padSim = PAD_LEFT;
            } else if (temp_s1 < 384) {
                g_Player.padSim = PAD_RIGHT;
            } else {
                g_Player.padSim = 0;
            }
            g_Entities[1].ext.generic.unk7C.S8.unk0 = 0;
            g_Player.D_80072EFC = 1;
            self->step++;
        }
        break;

    case 2:
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
        } else {
            if ((temp_a1 != 0) || (g_Player.pl_vram_flag & 1)) {
                if (temp_s1 > 384) {
                    g_Player.padSim = PAD_LEFT;
                } else if (temp_s1 < 384) {
                    g_Player.padSim = PAD_RIGHT;
                }
                self->step++;
            }
        }
        g_Player.D_80072EFC = 1;
        break;

    case 3:
        if (g_Player.padSim == 0x8000) {
            if (temp_s1 <= 384) {
                g_Player.padSim = 0;
            }
        } else if ((g_Player.padSim == 0x2000) && (temp_s1 >= 384)) {
            g_Player.padSim = 0;
        }
        if (g_Player.padSim == 0) {
            g_Player.padSim = PAD_LEFT;
            player->posX.i.hi = 384 - tilemap->scrollX.i.hi;
            self->step++;
            g_api.PlaySfx(SFX_METAL_CLANG_A);
            g_CutsceneFlags |= 1;
            tilemap->height = ((s16)tilemap->scrollY.i.hi + 0x100);
            func_8018F8EC(0);
        }
        g_Player.D_80072EFC = 1;
        break;

    case 4:
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        player->posX.i.hi = 384 - tilemap->scrollX.i.hi;
        if (temp_v0 > 496) {
            self->posY.i.hi--;
            player->posY.i.hi--;
            D_80097488.y.i.hi--;
        } else {
            g_api.PlaySfx(SFX_DOOR_CLOSE_A);
            if (player->facingLeft == 0) {
                g_Player.padSim = PAD_LEFT;
            }
            g_CutsceneFlags |= 4;
            self->step++;
        }
        func_8018F890(0x200);
        break;

    case 5:
        func_8018F890(0x200);
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;

        if (g_CutsceneFlags & 8) {
            CreateEntityFromCurrentEntity(E_EQUIP_ITEM_DROP, &g_Entities[204]);
            g_Entities[204].params = NUM_HAND_ITEMS + ITEM_HOLY_GLASSES;
            g_Entities[204].step = 5;
            g_Entities[204].flags = 0;
            self->step++;
        }
        break;

    case 6:
        if (g_CutsceneFlags & 2) {
            self->step++;
            g_api.PlaySfx(SFX_METAL_CLANG_A);
        }
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        break;

    case 7:
        if (temp_v0 < 592) {
            self->posY.i.hi++;
            player->posY.i.hi++;
            D_80097488.x.i.hi++;
        } else {
            D_8003C8B8 = 1;
            if (g_unkGraphicsStruct.unk0 != 0) {
                g_unkGraphicsStruct.unk0 = 0;
            }
            g_Entities[1].ext.generic.unk7C.S8.unk0 = 1;
            self->step++;
            g_api.PlaySfx(SFX_DOOR_CLOSE_A);
        }
        func_8018F890(0x300);
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        break;

    case 8:
        func_8018F890(0x300);
        if (tilemap->height == 0x300) {
            self->step++;
        }
        break;

    case 9:
        break;
    }

    prim = &g_PrimBuf[self->primIndex];
    temp_a0 = self->posX.i.hi - 8;
    temp_v1_4 = self->posX.i.hi + 8;
    self->posY.i.hi += 8;
    prim->x0 = prim->x2 = temp_a0;
    prim->x1 = prim->x3 = temp_v1_4;
    prim->y0 = prim->y1 = self->posY.i.hi + 15;
    prim->y2 = prim->y3 = 0x268 - tilemap->scrollY.i.hi;
}

// Black layer that covers room interior and lights up when cutscene starts
void EntityRoomDarkness(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_t0;
    s16 temp_a0;
    s16 temp_v0;
    s16 temp_v1;

    switch (self->step) {
    case 0:
        /* Has player seen Maria Holy Glasses Cutscene? */
        if (g_CastleFlags[HG_CS_DONE] != 0) {
            DestroyEntity(self);
            return;
        }

        primIndex = g_api.AllocPrimitives(PRIM_G4, 2);
        if (primIndex != -1) {
            InitializeEntity(g_EInitGeneric);
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->animSet = 0;
            temp_a2 = self->posX.i.hi - 112;
            temp_a3 = self->posX.i.hi + 112;
            temp_t0 = self->posX.i.hi - 32;
            temp_a0 = self->posX.i.hi + 32;
            self->flags |= FLAG_HAS_PRIMS;
            temp_v1 = 0x178 - g_Tilemap.scrollY.i.hi;
            temp_v0 = temp_v1 - 0x58;
            temp_a1 = temp_v1 + 0x68;
            self->posY.i.hi = temp_v1;
            prim->y0 = prim->y1 = temp_v0;
            prim->x0 = prim->x2 = temp_a2;
            prim->x1 = prim->x3 = temp_a3;
            prim->y2 = prim->y3 = temp_a1;
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = 255;
            prim->priority = 0x88;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
            prim->x0 = prim->x2 = temp_t0;
            prim->x1 = prim->x3 = temp_a0;
            prim->y0 = prim->y1 = temp_a1;
            prim->y2 = prim->y3 = temp_v1 + 0x88;
            prim->r0 = prim->r1 = prim->g0 = prim->g1 = prim->b0 = prim->b1 =
                255;
            prim->r2 = prim->r3 = prim->g2 = prim->g3 = prim->b2 = prim->b3 = 0;
            prim->priority = 0x88;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
        }
        break;

    case 1:
        if (g_CutsceneFlags & 4) {
            prim = &g_PrimBuf[self->primIndex];
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 -= 1;
            prim = prim->next;
            prim->r1 = prim->g0 = prim->g1 = prim->b0 = prim->b1 = prim->r0 =
                prim->b1 - 1;
            if (prim->r0 == 0) {
                self->step++;
            }
        }
        break;

    case 2:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        prim->drawMode = DRAW_HIDE;
        self->step++;
        break;
    }
}

void EntityMaria(Entity* self) {
    if (self->step == 0) {
        /* Has player seen Maria Holy Glasses Cutscene? */
        if (g_CastleFlags[HG_CS_DONE] != 0) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(D_80180428);
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 10;
        self->unk5A = 0x48;
        self->palette = 0x210;
        self->zPriority = 0x80;
    }
}

s16 func_8019040C(Primitive* prim, s16 arg1) {
    s16 ret = arg1;
    s16 temp_v0;

    prim->x2 = arg1;
    prim->x0 = arg1;
    ret += 0x20;
    prim->drawMode = DRAW_UNK02;
    prim->v0 = prim->v1 = 0x50;
    prim->v2 = prim->v3 = 0x60;
    prim->y0 = prim->y1 = 0x2C;
    prim->y2 = prim->y3 = 0x3C;
    prim->u0 = prim->u2 = 2;

    if (ret > 0xB0) {
        temp_v0 = 0xB2 - arg1;
        prim->u1 = prim->u3 = temp_v0;
        ret = 0;
        prim->x1 = prim->x3 = 0xB0;
    } else {
        prim->u1 = prim->u3 = 0x22;
        prim->x1 = prim->x3 = ret;
    }
    return ret;
}

s16 func_801904B8(Primitive* prim, s16 arg1) {
    prim->u0 = prim->u2 = 0x50;
    prim->u1 = prim->u3 = 0x60;
    prim->drawMode = DRAW_UNK02;
    prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - 8;
    prim->x1 = prim->x3 = g_CurrentEntity->posX.i.hi + 8;
    prim->y2 = prim->y3 = arg1;
    arg1 -= 32;
    prim->v2 = prim->v3 = 38;
    prim->v0 = prim->v1 = 6;
    prim->y0 = prim->y1 = arg1;
    return arg1;
}

// Elevator when not moving (ID 1A)
void EntityElevatorStationary(Entity* self) {
    Entity* player = &PLAYER;
    Primitive* prim;
    s16 primIndex;
    s16 posX, posY;
    s16 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(D_8018047C);
        self->animCurFrame = 3;
        self->zPriority = player->zPriority + 2;
        CreateEntityFromCurrentEntity(E_ID_1B, &self[-1]);
        self[-1].params = 1;
        CreateEntityFromCurrentEntity(E_ID_1B, &self[-2]);
        self[-2].params = 2;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 12);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->tpage = 0x12;
        prim->clut = 0x223;
        temp = prim->v1 = prim->u0 = prim->u2 = 0x28;
        prim->v2 = prim->v3 = prim->u1 = prim->u3 = 0x38;
        prim->v0 = temp;
        prim->priority = 0x6B;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;

        while (prim != NULL) {
            prim->tpage = 0x12;
            prim->clut = 0x223;
            prim->priority = 0x6A;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        if ((s16)(player->posY.i.hi + g_Tilemap.scrollY.i.hi) < 80) {
            self->posY.i.hi = player->posY.i.hi;
            player->posX.i.hi = self->posX.i.hi;
            self->animCurFrame = 10;
            g_Entities[1].ext.stub[0x00] = 1;
            SetStep(3);
        }
        break;

    case 1:
        if (*(u8*)&self[-1].ext.stub[0x4]) {
            posX = self->posX.i.hi - player->posX.i.hi;
            if (g_pads[0].pressed & PAD_UP) {
                if (abs(posX) < 8) {
                    g_Entities[1].ext.stub[0x00] = 1;
                    g_Player.D_80072EFC = 2;
                    g_Player.padSim = 0;
                    PLAYER.velocityX = 0;
                    PLAYER.velocityY = 0;
                    self->step = 2;
                }
            }
        }
        break;

    case 3:
        g_Player.D_80072EFC = 2;
        g_Player.padSim = 0;
        switch (self->step_s) {
        case 0:
            self->posY.val += FIX(0.5);
            player->posY.i.hi++;
            posY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if ((g_Timer % 16) == 0) {
                PlaySfxPositional(SFX_METAL_CLANG_A);
            }
            if (posY == 0x74) {
                self->step_s++;
            }
            break;

        case 1:
            if (AnimateEntity(D_80180780, self) == 0) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                g_Entities[1].ext.stub[0x00] = 0;
                self->step_s = 0;
                self->step = 1;
            }
            if (self->animFrameIdx == 4 && self->animFrameDuration == 0) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            }
        }
        break;

    case 2:
        g_Player.D_80072EFC = self->step;
        g_Player.padSim = 0;

        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_80180768, self) == 0) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            }
            if (self->animFrameIdx == 4 && self->animFrameDuration == 0) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            }
            break;

        case 1:
            self->posY.val -= FIX(0.5);
            if ((g_Timer % 16) == 0) {
                PlaySfxPositional(SFX_METAL_CLANG_A);
            }
            break;

        case 2:
            if (AnimateEntity(D_80180780, self) == 0) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                g_Entities[1].ext.stub[0x00] = 0;
                self->step_s = 0;
                self->step = 1;
            }
            break;
        }
    }
    prim = self->ext.prim;
    prim->x0 = prim->x2 = self->posX.i.hi - 8;
    prim->x1 = prim->x3 = self->posX.i.hi + 8;
    temp = self->posY.i.hi;
    prim->drawMode = DRAW_UNK02;
    prim->y2 = prim->y3 = temp - 0x1F;
    prim->y0 = prim->y1 = temp - 0x2F;
    prim = prim->next;

    posY = self->posY.i.hi - 40;
    while (prim != NULL) {
        posY = func_801904B8(prim, posY);
        prim = prim->next;
        if (posY <= 0) {
            break;
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }

    if (abs(self->posY.i.hi) > 384) {
        DestroyEntity(self);
    }
}

void EntityUnkId1B(Entity* self) {
    Entity* entity = &self[self->params];
    s32 step = self->step;

    switch (self->step) {
    case 0:
        InitializeEntity(D_8018047C);
        if (self->params & 16) {
            self->animCurFrame = self->params & 15;
            self->zPriority = 0x6A;
            self->step = 2;
            return;
        }
        self->animCurFrame = 0;
        break;

    case 1:
        self->posX.i.hi = entity->posX.i.hi;
        if (self->params == step) {
            self->posY.i.hi = entity->posY.i.hi + 35;
            self->ext.generic.unk80.modeS8.unk0 =
                GetPlayerCollisionWith(self, 12, 8, 4);
        } else {
            self->posY.i.hi = entity->posY.i.hi - 24;
            self->ext.generic.unk80.modeS8.unk0 =
                GetPlayerCollisionWith(self, 12, 8, 6);
        }
        break;
    }
}

// Elevator when moving, fixes player into position (ID 1C)
void EntityMovingElevator(Entity* self) {
    Entity* player = &PLAYER;
    Primitive* prim;
    s16 primIndex;
    s32 step;
    s16 posY;
    s16 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(D_8018047C);
        self->animCurFrame = 3;
        self->zPriority = player->zPriority + 2;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 12);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->tpage = 0x12;
            prim->u0 = prim->u2 = 0x50;
            prim->u1 = prim->u3 = 0x60;
            prim->v0 = prim->v1 = 6;
            prim->v2 = prim->v3 = 0x26;
            prim->clut = 0x223;
            prim->priority = 0x6A;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        if (player->posY.i.hi > 192) {
            step = 2;
            self->posY.i.hi = player->posY.i.hi;
            player->posX.i.hi = self->posX.i.hi;
        } else {
            step = 3;
            self->posY.i.hi = player->posY.i.hi;
            player->posX.i.hi = self->posX.i.hi;
        }

        self->animCurFrame = 10;
        g_Entities[1].ext.stub[0x00] = 1;
        SetStep(step);
        break;

    case 3:
        g_Player.D_80072EFC = 2;
        g_Player.padSim = 0;
        self->posY.val += FIX(0.5);
        player->posY.i.hi = self->posY.i.hi + 4;
        g_Player.pl_vram_flag = 0x41;
        break;

    case 2:
        g_Player.D_80072EFC = self->step;
        g_Player.padSim = 0;
        self->posY.val -= FIX(0.5);
        player->posY.i.hi = self->posY.i.hi + 4;
        g_Player.pl_vram_flag = 0x41;
        break;
    }
    prim = self->ext.prim;
    prim->x0 = prim->x2 = self->posX.i.hi - 8;
    prim->x1 = prim->x3 = self->posX.i.hi + 8;
    temp = self->posY.i.hi;
    prim->drawMode = DRAW_UNK02;
    prim->y2 = prim->y3 = temp - 0x1F;
    prim->y0 = prim->y1 = temp - 0x2F;
    prim = prim->next;

    posY = self->posY.i.hi - 40;

    while (prim != NULL) {
        posY = func_801904B8(prim, posY);
        prim = prim->next;
        if (posY <= 0) {
            break;
        }
        prim = prim->next;
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }

    if (abs(self->posY.i.hi) > 384) {
        DestroyEntity(self);
    }
}
