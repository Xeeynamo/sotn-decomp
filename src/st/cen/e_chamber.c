// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"
#include "game.h"
#include "sfx.h"

extern u32 OVL_EXPORT(CutsceneFlags);

static u16 tile_layout[] = {
    0x014A, 0x014B, 0x014E, 0x014F, 0x014C, 0x014D, 0x0150, 0x0151,
    0x00F5, 0x00F6, 0x012B, 0x012C, 0x00FC, 0x00FD, 0x012F, 0x0130};

static u16 unused[] = {
    0x0101, 0x00FF, 0x0201, 0x00FF, 0x0201, 0x0307, 0x0407, 0x0507, 0x0607,
    0x0707, 0x0807, 0x0907, 0x0A10, 0x00FF, 0x0A01, 0x0B06, 0x0C06, 0x0D06,
    0x0E10, 0x0F0A, 0x0E0A, 0x0F0A, 0x0E20, 0x00FF, 0x0E01, 0x1004, 0x1104,
    0x120B, 0x00FF, 0x0000, 0x1301, 0x00FF, 0x1201, 0x00FF, 0x1220, 0x1103,
    0x1003, 0x1403, 0x1503, 0x1640, 0x1506, 0x0D05, 0x0C05, 0x0B05, 0x0A20,
    0x00FF, 0x0A10, 0x1710, 0x0A08, 0x00FF, 0x0A01, 0x0B02, 0x0C02, 0x1806,
    0x1906, 0x1850, 0x0C03, 0x0B03, 0x0A08, 0x00FF, 0x0A01, 0x0B03, 0x0C03,
    0x0D03, 0x0E03, 0x1B06, 0x1A10, 0x1B20, 0x0E03, 0x0D03, 0x0C03, 0x00FF,
    0x1C04, 0x1D04, 0x1E04, 0x1F04, 0x00FF, 0x0000, 0x2002, 0x2104, 0x2204,
    0x2304, 0x2404, 0x2504, 0x2604, 0x2704, 0x2002, 0x0000, 0x2808, 0x2908,
    0x2A60, 0x00FF, 0x0C01, 0x00FF,
};

static void CutsceneCameraPan(s16 arg0) {
    s16 delta = arg0 - g_Tilemap.height;

    if (delta > 1) {
        g_Tilemap.height++;
    } else if (delta < -1) {
        g_Tilemap.height--;
    } else {
        g_Tilemap.height = arg0;
    }

#ifdef VERSION_PSP
    g_Tilemap.x = 0;
    g_Tilemap.width = 0x300;
#endif
}

#ifdef VERSION_PSP
extern s32 E_ID(CUTSCENE);

static void SetTilemap(void) {
    g_Tilemap.y = 0x100;
    g_Tilemap.height = 0x200;
    g_Tilemap.x = 0x100;
    g_Tilemap.width = 0x200;
}
#endif

static void func_8018F8EC(u16 index) {
    u16* tileLayoutPtr;
    Tilemap* tilemap = &g_Tilemap;
    u16 tilePos = 0x5B6;
    s32 i, j;

    tileLayoutPtr = &tile_layout[index * 8];

    for (i = 0; i < 2; tilePos += 0x2C, i++) {
        for (j = 0; j < 4; tilePos++, j++) {
            tilemap->fg[tilePos] = *tileLayoutPtr++;
        }
    }
}

// platform that lifts you into chamber, starts cutscene, gives you holy glasses
void EntityPlatform(Entity* self) {
    Primitive* prim;
    Tilemap* tilemap = &g_Tilemap;
    Entity* player = &PLAYER;
    s16 posX;
    s16 posY;
    Entity* cutsceneEntity;
    u16 var_s5;
    Entity* holyGlassesEntity;
    u16 isPlayerTouching;
    s32 primIndex;

    self->posY.i.hi -= 8;
    isPlayerTouching = GetPlayerCollisionWith(self, 0x20, 0x11, 4);
    posX = player->posX.i.hi + tilemap->scrollX.i.hi;
    posY = self->posY.i.hi + tilemap->scrollY.i.hi;

    switch (self->step) {
    case 0:
#ifdef VERSION_PSP
        g_api.TimeAttackController(
            TIMEATTACK_EVENT_FIRST_MARIA_MEET, TIMEATTACK_SET_VISITED);
#endif
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            InitializeEntity(OVL_EXPORT(EInitInteractable));
            self->animSet = ANIMSET_OVL(2);
            self->animCurFrame = 9;
            self->zPriority = 0x80;

#ifndef VERSION_PSP
            if (g_CastleFlags[MET_MARIA_IN_CEN]) {
                self->step = 9;
            }
#endif

            func_8018F8EC(0);
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            prim->tpage = 0xF;
            prim->clut = 2;
            prim->u0 = prim->u2 = 0xA0;
            prim->u1 = prim->u3 = 0xB0;
            prim->v0 = prim->v1 = 0xA1;
            prim->v2 = prim->v3 = 0xA7;
            prim->priority = 0x7F;
            prim->drawMode = DRAW_UNK02;

#ifdef VERSION_PSP
            if (g_CastleFlags[INVERTED_CASTLE_UNLOCKED]) {
                self->step = 9;
            } else if (PlayerAlucardMetMaria()) {
                OVL_EXPORT(CutsceneFlags) |= 8;
            } else if (g_PlayableCharacter != PLAYER_ALUCARD) {
                self->step = 9;
            }
#endif
        }
        break;

    case 1:
        if ((GetDistanceToPlayerX() < 32) &&
            ((self->posY.i.hi - player->posY.i.hi) < 80)) {
            g_PauseAllowed = false;
            g_unkGraphicsStruct.pauseEnemies = 1;
            if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
                g_Player.padSim = PAD_BAT;
            } else if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
                // Strange difference here on PSP, is this a bug?
#ifdef VERSION_PSP
                g_Player.padSim = PAD_NONE;
#else
                g_Player.padSim = PAD_MIST;
#endif
            } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
                g_Player.padSim = PAD_WOLF;
            } else if (posX > 384) {
                g_Player.padSim = PAD_LEFT;
            } else if (posX < 384) {
                g_Player.padSim = PAD_RIGHT;
            } else {
                g_Player.padSim = PAD_NONE;
            }
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 0;
            g_Player.demo_timer = 1;
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
                    g_Player.padSim = PAD_MIST;
                } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
                    g_Player.padSim = PAD_WOLF;
                }
            }
        } else {
            if (isPlayerTouching || (g_Player.vram_flag & TOUCHING_GROUND)) {
                if (posX > 384) {
                    g_Player.padSim = PAD_LEFT;
                } else if (posX < 384) {
                    g_Player.padSim = PAD_RIGHT;
                }
                self->step++;
            }
        }
        g_Player.demo_timer = 1;
        break;

    case 3:
        if (g_Player.padSim == PAD_LEFT) {
            if (posX <= 384) {
                g_Player.padSim = PAD_NONE;
            }
        } else if (g_Player.padSim == PAD_RIGHT && posX >= 384) {
            g_Player.padSim = PAD_NONE;
        }

        if (g_Player.padSim == PAD_NONE) {
            player->posX.i.hi = 384 - tilemap->scrollX.i.hi;
            g_Player.padSim = PAD_LEFT;
            self->step++;
            g_api.PlaySfx(SFX_METAL_CLANG_A);
            OVL_EXPORT(CutsceneFlags) |= 1;
            tilemap->height = ((s16)tilemap->scrollY.i.hi + 0x100);
#ifndef VERSION_PSP
            func_8018F8EC(0);
#endif
        }

        g_Player.demo_timer = 1;
        break;

    case 4:
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        player->posX.i.hi = 384 - tilemap->scrollX.i.hi;
        if (posY > 496) {
            self->posY.i.hi--;
            player->posY.i.hi--;
            g_unkGraphicsStruct.shoveY.i.hi--;
        } else {
#ifdef VERSION_PSP
            func_8018F8EC(1);
#endif
            g_api.PlaySfx(SFX_DOOR_CLOSE_A);
            if (!player->facingLeft) {
                g_Player.padSim = PAD_LEFT;
            }
            OVL_EXPORT(CutsceneFlags) |= 4;
#ifdef VERSION_PSP
            self->ext.platformUnk.unk7C = 0;
#endif
            self->step++;
        }
        CutsceneCameraPan(0x200);
        break;

    case 5:
        CutsceneCameraPan(0x200);
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
#ifdef VERSION_PSP
        if (g_Tilemap.height == 0x200 && OVL_EXPORT(CutsceneFlags) & 8) {
            self->ext.platformUnk.unk7C++;
            if (self->ext.platformUnk.unk7C > 3) {
                g_PauseAllowed = true;
                if (PlayerAlucardMetMaria()) {
                    self->step = 20;
                } else {
                    OVL_EXPORT(CutsceneFlags) |= 0x10;
                    self->step++;
                }
            }
        }
#else
        if (OVL_EXPORT(CutsceneFlags) & 8) {
            CreateEntityFromCurrentEntity(E_EQUIP_ITEM_DROP, &g_Entities[204]);
            g_Entities[204].params = NUM_HAND_ITEMS + ITEM_HOLY_GLASSES;
            g_Entities[204].step = 5;
            g_Entities[204].flags = 0;
            self->step++;
        }
#endif
        break;

    case 6:
#ifdef VERSION_PSP
        SetTilemap();
        if (OVL_EXPORT(CutsceneFlags) & 0x200) {
            g_Player.padSim = PAD_NONE;
            g_Player.demo_timer = 1;
        }

        if (OVL_EXPORT(CutsceneFlags) & 0x20) {
            if (g_DemoMode != Demo_None) {
                self->step = 1000;
            } else {
                self->step = 11;
                cutsceneEntity = &g_Entities[200];
                OVL_EXPORT(CutsceneFlags) = 1;
                CreateEntityFromCurrentEntity(E_ID(CUTSCENE), cutsceneEntity);
                cutsceneEntity->params = 1;
                g_PauseAllowed = false;
                g_Player.padSim = PAD_NONE;
                g_Player.demo_timer = 1;
            }
        }
#else
        if (OVL_EXPORT(CutsceneFlags) & 2) {
            self->step++;
            g_api.PlaySfx(SFX_METAL_CLANG_A);
        }
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
#endif
        break;

#ifdef VERSION_PSP
    case 10:
        g_Player.padSim = PAD_NONE;
        if (g_Player.status &
            (PLAYER_STATUS_WOLF_FORM | PLAYER_STATUS_MIST_FORM |
             PLAYER_STATUS_BAT_FORM)) {
            g_Player.padSim = PAD_NONE;
            if (g_Timer & 1) {
                if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
                    g_Player.padSim = PAD_BAT;
                } else if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
                    g_Player.padSim = PAD_MIST;
                } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
                    g_Player.padSim = PAD_WOLF;
                }
            }
        } else if (isPlayerTouching || (g_Player.vram_flag & TOUCHING_GROUND)) {
            if (posX > 0x180) {
                g_Player.padSim = PAD_LEFT;
            } else if (posX < 0x180) {
                g_Player.padSim = PAD_RIGHT;
            }
        }
        g_Player.demo_timer = 1;
        if (g_Player.padSim == PAD_LEFT) {
            if (posX < 0x182) {
                g_Player.padSim = PAD_NONE;
            }
        } else {
            if (g_Player.padSim == PAD_RIGHT && posX >= 0x17F) {
                g_Player.padSim = PAD_NONE;
            }
        }
        if (g_Player.padSim == PAD_NONE) {
            func_8018F8EC(0);
            player->posX.i.hi = 0x180 - tilemap->scrollX.i.hi;
            g_Player.padSim = PAD_LEFT;
            self->step = 7;
            g_api.PlaySfx(SFX_METAL_CLANG_A);
            OVL_EXPORT(CutsceneFlags) |= 1;
            tilemap->height = tilemap->scrollY.i.hi + 0x100;
            g_Player.padSim = PAD_NONE;
            g_Player.demo_timer = 1;
            g_api.PlaySfx(SFX_METAL_CLANG_A);
        }
        g_Player.demo_timer = 1;
        break;
    case 11:
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        if (OVL_EXPORT(CutsceneFlags) & 0x80) {
            var_s5 = g_Entities[64].posX.i.hi + tilemap->scrollX.i.hi;
            g_Player.padSim = PAD_NONE;
            if (g_Player.status &
                (PLAYER_STATUS_WOLF_FORM | PLAYER_STATUS_MIST_FORM |
                 PLAYER_STATUS_BAT_FORM)) {
                g_Player.padSim = PAD_NONE;
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
                isPlayerTouching || (g_Player.vram_flag & TOUCHING_GROUND)) {
                if (posX > (var_s5 + 0x1B)) {
                    g_Player.padSim = PAD_LEFT;
                } else if (posX < (var_s5 - 0x1B)) {
                    g_Player.padSim = PAD_RIGHT;
                }
            }
            g_Player.demo_timer = 1;
            if (g_Player.padSim == PAD_LEFT) {
                if (posX <= (var_s5 + 0x1B)) {
                    g_Player.padSim = PAD_NONE;
                }
            } else if (
                g_Player.padSim == PAD_RIGHT && posX >= (var_s5 - 0x1B)) {
                g_Player.padSim = PAD_NONE;
            }

            if (g_Player.padSim == PAD_NONE) {
                g_Player.padSim = PAD_LEFT;
                self->step = 12;
                tilemap->height = tilemap->scrollY.i.hi + 0x100;
                g_Player.padSim = PAD_NONE;
                g_Player.demo_timer = 1;
                OVL_EXPORT(CutsceneFlags) |= 0x100;
                OVL_EXPORT(CutsceneFlags) = 1;

                cutsceneEntity = &g_Entities[200];
                CreateEntityFromCurrentEntity(E_ID(CUTSCENE), cutsceneEntity);
                cutsceneEntity->params = 2;

                holyGlassesEntity = &g_Entities[204];
                CreateEntityFromCurrentEntity(
                    E_EQUIP_ITEM_DROP, holyGlassesEntity);
                holyGlassesEntity->params = NUM_HAND_ITEMS + ITEM_HOLY_GLASSES;
                holyGlassesEntity->step = 5;
                holyGlassesEntity->flags = 0;
            }
            g_Player.demo_timer = 1;
        }
        break;
    case 12:
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        if ((OVL_EXPORT(CutsceneFlags) & 0x60) == 0x60) {
            self->step = 10;
        }
        break;
#endif

    case 7:
        if (posY < 592) {
            self->posY.i.hi++;
            player->posY.i.hi++;
            g_unkGraphicsStruct.shoveX.i.hi++;
        } else {
            g_PauseAllowed = true;
            if (g_unkGraphicsStruct.pauseEnemies != 0) {
                g_unkGraphicsStruct.pauseEnemies = 0;
            }
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
            self->step++;
            g_api.PlaySfx(SFX_DOOR_CLOSE_A);
        }
        CutsceneCameraPan(0x300);
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        break;

    case 8:
        CutsceneCameraPan(0x300);
        if (tilemap->height == 0x300) {
#ifdef VERSION_PSP
            g_Tilemap.y = 0;
#endif
            self->step++;
        }
        break;

#ifdef VERSION_PSP
    case 20:
        g_PauseAllowed = false;
        if (PlayerAlucardMetMaria()) {
            OVL_EXPORT(CutsceneFlags) |= 0x80;
        }
        self->step++;
        break;
    case 21:
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        if (OVL_EXPORT(CutsceneFlags) & 0x80) {
            var_s5 = g_Entities[64].posX.i.hi + tilemap->scrollX.i.hi;
            g_Player.padSim = PAD_NONE;
            if (g_Player.status &
                (PLAYER_STATUS_WOLF_FORM | PLAYER_STATUS_MIST_FORM |
                 PLAYER_STATUS_BAT_FORM)) {
                g_Player.padSim = PAD_NONE;
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
                isPlayerTouching || (g_Player.vram_flag & TOUCHING_GROUND)) {
                if (posX > (var_s5 + 0x1B)) {
                    g_Player.padSim = PAD_LEFT;
                } else if (posX < (var_s5 - 0x1B)) {
                    g_Player.padSim = PAD_RIGHT;
                }
            }
            g_Player.demo_timer = 1;
            if (g_Player.padSim == PAD_LEFT) {
                if (posX <= (var_s5 + 0x1B)) {
                    g_Player.padSim = PAD_NONE;
                }
            } else if (
                g_Player.padSim == PAD_RIGHT && posX >= (var_s5 - 0x1B)) {
                g_Player.padSim = PAD_NONE;
            }

            if (g_Player.padSim == PAD_NONE) {
                g_Player.padSim = PAD_LEFT;
                self->step++;
                g_api.PlaySfx(SFX_METAL_CLANG_A);
                tilemap->height = tilemap->scrollY.i.hi + 0x100;
                g_Player.padSim = PAD_NONE;
                g_Player.demo_timer = 1;
                OVL_EXPORT(CutsceneFlags) = 1;

                cutsceneEntity = &g_Entities[200];
                CreateEntityFromCurrentEntity(E_ID(CUTSCENE), cutsceneEntity);
                cutsceneEntity->params = 3;
            }
            g_Player.demo_timer = 1;
        }
        break;
    case 22:
        g_Player.padSim = PAD_NONE;
        g_Player.demo_timer = 1;
        if ((OVL_EXPORT(CutsceneFlags) & 0x40) == 0x40) {
            self->step++;
        }
        break;
    case 23:
        g_Player.padSim = PAD_NONE;
        if (g_Player.status &
            (PLAYER_STATUS_WOLF_FORM | PLAYER_STATUS_MIST_FORM |
             PLAYER_STATUS_BAT_FORM)) {
            g_Player.padSim = PAD_NONE;
            if (g_Timer & 1) {
                if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
                    g_Player.padSim = PAD_BAT;
                } else if (g_Player.status & PLAYER_STATUS_MIST_FORM) {
                    g_Player.padSim = PAD_MIST;
                } else if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
                    g_Player.padSim = PAD_WOLF;
                }
            }
        } else if (isPlayerTouching || (g_Player.vram_flag & TOUCHING_GROUND)) {
            if (posX > 0x180) {
                g_Player.padSim = PAD_LEFT;
            } else if (posX < 0x180) {
                g_Player.padSim = PAD_RIGHT;
            }
        }
        g_Player.demo_timer = 1;
        if (g_Player.padSim == PAD_LEFT) {
            if (posX < 0x182) {
                g_Player.padSim = PAD_NONE;
            }
        } else {
            if (g_Player.padSim == PAD_RIGHT && posX >= 0x17F) {
                g_Player.padSim = PAD_NONE;
            }
        }
        if (g_Player.padSim == PAD_NONE) {
            func_8018F8EC(0);
            player->posX.i.hi = 0x180 - tilemap->scrollX.i.hi;
            g_Player.padSim = PAD_LEFT;
            self->step = 7;
            g_api.PlaySfx(SFX_METAL_CLANG_A);
            OVL_EXPORT(CutsceneFlags) |= 1;
            tilemap->height = tilemap->scrollY.i.hi + 0x100;
            g_Player.padSim = PAD_NONE;
            g_Player.demo_timer = 1;
            g_api.PlaySfx(SFX_METAL_CLANG_A);
        }
        g_Player.demo_timer = 1;
        break;
#endif

#ifdef VERSION_PSP
    case 1000:
        break;
#else
    case 9:
        break;
#endif
    }

    self->posY.i.hi += 8;
    prim = &g_PrimBuf[self->primIndex];
    prim->x0 = prim->x2 = self->posX.i.hi - 8;
    prim->x1 = prim->x3 = prim->x0 + 16;
    prim->y0 = prim->y1 = self->posY.i.hi + 15;
    prim->y2 = prim->y3 = 0x268 - tilemap->scrollY.i.hi;
}

// Black layer that covers room interior and lights up when cutscene starts
void EntityRoomDarkness(Entity* self) {
    Primitive* prim;
    s16 posX;
    s16 posY;
    s32 primIndex;
    Entity* player = &PLAYER;

    switch (self->step) {
    case 0:
#ifdef VERSION_PSP
        if (g_CastleFlags[INVERTED_CASTLE_UNLOCKED]) {
            DestroyEntity(self);
            return;
        }
#endif
        /* Has player seen Maria Holy Glasses Cutscene? */
        if (g_CastleFlags[MET_MARIA_IN_CEN]) {
            DestroyEntity(self);
            return;
        }

#ifdef VERSION_PSP
        if (g_PlayableCharacter != PLAYER_ALUCARD) {
            DestroyEntity(self);
            return;
        }
#endif

        primIndex = g_api.AllocPrimitives(PRIM_G4, 2);
        if (primIndex != -1) {
            InitializeEntity(OVL_EXPORT(EInitInteractable));
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            self->animSet = 0;
            self->posY.i.hi = 0x178 - g_Tilemap.scrollY.i.hi;
            prim = &g_PrimBuf[primIndex];
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            prim->x0 = prim->x2 = posX - 112;
            prim->x1 = prim->x3 = posX + 112;
            prim->y0 = prim->y1 = posY - 0x58;
            prim->y2 = prim->y3 = posY + 0x68;
            PCOL(prim) = 255;
            prim->priority = 0x88;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;

            prim->x0 = prim->x2 = posX - 32;
            prim->x1 = prim->x3 = posX + 32;
            prim->y0 = prim->y1 = posY + 0x68;
            prim->y2 = prim->y3 = posY + 0x88;
            prim->r0 = prim->r1 = prim->g0 = prim->g1 = prim->b0 = prim->b1 =
                255;
            prim->r2 = prim->r3 = prim->g2 = prim->g3 = prim->b2 = prim->b3 = 0;
            prim->priority = 0x88;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
        }
        break;

    case 1:
        if (OVL_EXPORT(CutsceneFlags) & 4) {
#ifdef VERSION_PSP
            if (OVL_EXPORT(CutsceneFlags) & 8) {
                self->step++;
                break;
            }
#endif
            prim = &g_PrimBuf[self->primIndex];
            PCOL(prim) -= 1;
            prim = prim->next;

            prim->r0 = prim->r1 = prim->g0 = prim->g1 = prim->b0 = prim->b1 -=
                1;
            if (prim->r0 <= 0) {
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

    case 3:
        break;
    }
}

#ifdef VERSION_PSP
static bool PlayerAlucardMetMaria(void) {
    if (g_CastleFlags[MET_MARIA_IN_CEN] &&
        g_PlayableCharacter == PLAYER_ALUCARD) {
        return true;
    }
    return false;
}
#endif
