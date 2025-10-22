// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

// This is part of a different water effects data segment
extern s16 D_us_80180F1A[];

#ifdef VERSION_PSP
extern s32 E_ID(SURFACING_WATER);
#endif

// Generates water effect in front of the boat as it travels forward
void GenerateBowWave(Entity* self, s16 xOffset) {
    Entity* newEntity;

    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
    if (newEntity != NULL) {
        CreateEntityFromCurrentEntity(E_ID(SURFACING_WATER), newEntity);

        if (self->ext.et_surfacingWater.unk90 & 2) {
            newEntity->posY.i.hi = 288 - g_Tilemap.scrollY.i.hi;
        } else {
            newEntity->posY.i.hi = 176 - g_Tilemap.scrollY.i.hi;
        }

        if (self->facingLeft) {
            newEntity->posX.i.hi += xOffset;
        } else {
            newEntity->posX.i.hi -= xOffset;
        }

        newEntity->params = 0x8000;
        newEntity->params |= D_us_80180F1A[0] << 8;
        newEntity->ext.et_surfacingWater.origPosX = 0x17;
        newEntity->zPriority = 0x9B;
        self->ext.et_surfacingWater.unk8C = 8;
    }
}

void MoveBoat(u16 playerInBoat, Entity* entity) {
    Entity* tempEntity;
    s16 posX;
    s16 posY;

    entity->ext.et_surfacingWater.origPosX = entity->posX.i.hi;
    entity->ext.et_surfacingWater.origPosY = entity->posY.i.hi;

    if (!entity->ext.et_surfacingWater.unk94) {
        MoveEntity();
    } else {
        entity->posX.i.hi = entity->ext.et_surfacingWater.newPosX;
        entity->posY.i.hi = entity->ext.et_surfacingWater.newPosY;
        entity->posX.i.lo = entity->posY.i.lo = 0;
    }
    posX = entity->posX.i.hi - entity->ext.et_surfacingWater.origPosX;
    posY = entity->posY.i.hi - entity->ext.et_surfacingWater.origPosY;
    if (posX && !entity->ext.et_surfacingWater.unk94) {
        if (!entity->ext.et_surfacingWater.unk8C) {
            if (!(entity->ext.et_surfacingWater.unk90 & 1)) {
                GenerateBowWave(entity, 40);
                tempEntity = entity + 1;
                if (tempEntity->animCurFrame == 0x1E ||
                    tempEntity->animCurFrame == 0x1F) {
                    GenerateBowWave(entity, -56);
                }
            }
        } else {
            entity->ext.et_surfacingWater.unk8C--;
        }
    }

    tempEntity = &PLAYER;
    if (playerInBoat) {
        if (posX > 0) {
            if (!(g_Player.vram_flag & TOUCHING_R_WALL)) {
                tempEntity->posX.i.hi += posX;
                D_80097488.x.i.hi += posX;
            }
        } else if (!(g_Player.vram_flag & TOUCHING_L_WALL)) {
            tempEntity->posX.i.hi += posX;
            D_80097488.x.i.hi += posX;
        }
        tempEntity->posY.i.hi += posY;
        D_80097488.y.i.hi += posY;
    }
}

extern u32 g_CutsceneFlags;
static u8 anim_row[] = {
    0x18, 0x1C, 0x10, 0x1D, 0x10, 0x1E, 0x10, 0x1F, 0x10, 0x20, 0x00, 0x00};
static u8 anim_stationary[] = {0x18, 0x1C, 0x10, 0x1D, 0x10, 0x1E, 0x10, 0x1F,
                               0x10, 0x20, 0x10, 0x1C, 0xFF, 0x00, 0x00, 0x00};
static s32 y_offsets[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

#ifdef VERSION_PSP
extern s32 E_ID(SPLASH_WATER);
extern s32 E_ID(FERRYMAN);
extern s32 E_ID(ID_4F);
#endif

// Ferryman boat travel logic
void EntityFerrymanController(Entity* self) {
    Entity* ferrymanEntity;
    Entity* tempEntity;
    s16 offset;
    u16 playerInBoat;

    /* Check that the player is on the boat */
    tempEntity = &PLAYER;
    playerInBoat = GetPlayerCollisionWith(self, 0x24, 5, 4);
    if (playerInBoat) {
        self->posX.i.hi += 0x28;
        GetPlayerCollisionWith(self, 4, 9, 9);
        self->posX.i.hi -= 0x50;
        GetPlayerCollisionWith(self, 4, 9, 9);
        self->posX.i.hi += 0x28;
        g_Entities[E_AFTERIMAGE_1].ext.alucardController.disableAfterImageFlag =
            true;
    } else {
        g_Entities[E_AFTERIMAGE_1].ext.alucardController.disableAfterImageFlag =
            false;
    }

    if (self->step && !self->ext.ferrymanBoat.unk94) {
        if (playerInBoat && !self->ext.ferrymanBoat.unk80 &&
            !self->ext.ferrymanBoat.playerInBoat) {
            self->ext.ferrymanBoat.unk80 = 8;
        }
        if (self->ext.ferrymanBoat.unk80 != 0) {
            self->ext.ferrymanBoat.unk80--;
            offset = y_offsets[self->ext.ferrymanBoat.unk80];
            self->posY.i.hi += offset;
            if (playerInBoat) {
                tempEntity->posY.i.hi += offset;
                D_80097488.y.i.hi += offset;
            }
        }
    }

    self->ext.ferrymanBoat.playerInBoat = playerInBoat;
    ferrymanEntity = self + 1;
    switch (self->step) {
    case 0:
        // If we don't have the Merman statue yet, ferryman only appears in one
        // location, delete the other instance.
        if (!self->params && !(g_Status.relics[RELIC_MERMAN_STATUE] & 2)) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(g_EInitInteractable);
        if (PLAYER.posX.i.hi < self->posX.i.hi) {
            self->facingLeft = true;
        } else {
            self->facingLeft = false;
        }

        self->ext.ferrymanBoat.unk80 = 0;
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 0x21;
        self->zPriority = 0x9A;
        self->flags |= FLAG_POS_CAMERA_LOCKED;
        self->drawFlags = FLAG_DRAW_ROTATE;
        CreateEntityFromCurrentEntity(E_ID(FERRYMAN), ferrymanEntity);
        ferrymanEntity->facingLeft = self->facingLeft;
        break;
    case 1:
        if (playerInBoat) {
            self->step++;
            tempEntity = &g_Entities[172];
            CreateEntityFromCurrentEntity(E_ID(ID_4F), tempEntity);
            tempEntity->params = self->params;
        }
        break;
    case 2:
        // If we already met the ferryman we can skip straight to rowing
        if (g_CutsceneFlags & 0x80) {
            self->step += 2;
        } else {
            // Otherwise pause world state and put Alucard into human form
            g_Entities[E_AFTERIMAGE_1]
                .ext.alucardController.disableAfterImageFlag = true;
            g_PauseAllowed = false;
            g_unkGraphicsStruct.pauseEnemies = true;
            g_Player.demo_timer = 1;
            if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
                g_Player.padSim = BTN_WOLF;
            } else {
                g_Player.padSim = PAD_NONE;
            }
            self->step++;
        }
        break;
    case 3:
        g_Player.demo_timer = 1;
        g_Player.padSim = PAD_NONE;
        if (g_CutsceneFlags & 0x80) {
            // Unpause world state once meeting ferryman cutscene is over
            g_PauseAllowed = true;
            g_unkGraphicsStruct.pauseEnemies = false;
            self->step++;
        }
        break;
    case 4:
        // Begin rowing
        if ((AnimateEntity(anim_row, ferrymanEntity) & 0x80) &&
            (ferrymanEntity->pose == 2)) {
            PlaySfxPositional(SFX_OAR_ROW);
        }
        if (ferrymanEntity->pose > 1 && ferrymanEntity->pose < 5) {
            if (self->ext.ferrymanBoat.accelerationX > FIX(-1.5)) {
                self->ext.ferrymanBoat.accelerationX -= FIX(0.09375);
            }
        } else {
            if (self->ext.ferrymanBoat.accelerationX != 0) {
                self->ext.ferrymanBoat.accelerationX += FIX(0.0234375);
            }
            if (!self->params) {
                if (ferrymanEntity->pose == 5) {
                    offset = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                    if (self->facingLeft) {
                        if (offset > 0xAA0 &&
                            !g_CastleFlags[FERRYMAN_GATE_OPEN]) {
                            g_CastleFlags[FERRYMAN_GATE_OPEN] = true;
                        }
                        if (offset > 0xBE0) {
                            self->step++;
                        }
                    } else if (offset < 0x120) {
                        self->step++;
                    }
                }
            } else if (ferrymanEntity->pose == 5) {
                offset = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                if (self->facingLeft) {
                    if (offset > 480) {
                        self->step += 2;
                    }
                } else if (offset < 1232) {
                    self->step += 2;
                }
            }
        }
        if (self->facingLeft) {
            self->velocityX = -self->ext.ferrymanBoat.accelerationX;
        } else {
            self->velocityX = self->ext.ferrymanBoat.accelerationX;
        }
        MoveBoat(playerInBoat, self);
        break;
    case 5:
        if ((AnimateEntity(anim_stationary, ferrymanEntity) & 0x80) &&
            ferrymanEntity->pose == 2) {
            g_api.PlaySfx(SFX_OAR_ROW);
        }

        if (ferrymanEntity->pose > 1 && ferrymanEntity->pose < 5) {
            if (self->ext.ferrymanBoat.accelerationX > FIX(-1.5)) {
                self->ext.ferrymanBoat.accelerationX -= FIX(0.09375);
            }
        } else if (self->ext.ferrymanBoat.accelerationX != 0) {
            self->ext.ferrymanBoat.accelerationX += FIX(0.01171875);
        }

        if (self->facingLeft) {
            self->velocityX = -self->ext.ferrymanBoat.accelerationX;
        } else {
            self->velocityX = self->ext.ferrymanBoat.accelerationX;
        }

        MoveBoat(playerInBoat, self);
        break;
    case 6:
        AnimateEntity(anim_stationary, ferrymanEntity);
        if (ferrymanEntity->pose > 1 && ferrymanEntity->pose < 5) {
            if (self->ext.ferrymanBoat.accelerationX > FIX(-1.5)) {
                self->ext.ferrymanBoat.accelerationX -= FIX(0.09375);
            }
        } else if (self->ext.ferrymanBoat.accelerationX < FIX(-1)) {
            self->ext.ferrymanBoat.accelerationX += FIX(0.01171875);
        }
        offset = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (self->facingLeft) {
            self->velocityX = -self->ext.ferrymanBoat.accelerationX;
            if (offset > 560) {
                self->ext.ferrymanBoat.flags |= 1;
            }
            if (offset > 624) {
                self->step++;
            }
        } else {
            self->velocityX = self->ext.ferrymanBoat.accelerationX;
            if (offset <= 1215) {
                self->ext.ferrymanBoat.flags |= 1;
            }
            if (offset < 0x480) {
                self->step++;
            }
        }
        MoveBoat(playerInBoat, self);
        break;
    case 7:
        // Heading off the edge of a waterfall
        offset = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX += FIX(0.03125);
            } else {
                self->velocityX -= FIX(0.03125);
            }
            if (self->velocityY <= FIX(3.99999)) {
                self->velocityY += FIX(0.25);
            }
            if (offset > 264) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_ID(SPLASH_WATER), tempEntity);
                    tempEntity->posY.i.hi = 0x120 - g_Tilemap.scrollY.i.hi;
                    tempEntity->zPriority = 0x9B;
                    if (self->facingLeft) {
                        tempEntity->posX.i.hi = self->posX.i.hi + 0x28;
                    } else {
                        tempEntity->posX.i.hi = self->posX.i.hi - 0x28;
                    }
                    tempEntity->params = 0;
                }
                self->ext.ferrymanBoat.splashTimer = 3;
                self->rotate += 0x30;
                self->step_s++;
            } else if (self->rotate > -0x400) {
                self->rotate -= 8;
            }
            break;
        case 1:
            if (self->ext.ferrymanBoat.splashTimer) {
                self->ext.ferrymanBoat.splashTimer--;
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_ID(SPLASH_WATER), tempEntity);
                    tempEntity->posY.i.hi = 0x120 - g_Tilemap.scrollY.i.hi;
                    tempEntity->zPriority = 0x9B;
                    if (self->facingLeft) {
                        tempEntity->posX.i.hi =
                            (self->posX.i.hi - 0x1A) +
                            (self->ext.ferrymanBoat.splashTimer * 0x16);
                    } else {
                        tempEntity->posX.i.hi =
                            (self->posX.i.hi + 0x1A) -
                            (self->ext.ferrymanBoat.splashTimer * 0x16);
                    }
                    tempEntity->params = 0;
                }
            }
            if (offset >= 288) {
                self->velocityX = 0;
                self->velocityY -= FIX(0.625);
                self->step_s++;
            }
            self->rotate += 0x30;
            break;
        case 2:
            self->velocityY -= FIX(0.625);
            if (offset < 0x121) {
                self->posY.i.hi = 0x120 - g_Tilemap.scrollY.i.hi;
                self->velocityY = 0;
                self->ext.ferrymanBoat.accelerationX = 0;
                self->ext.ferrymanBoat.flags = 2;
                self->step++;
                self->step_s = 0;
                ferrymanEntity->pose = 0;
                ferrymanEntity->poseTimer = 0;
            }
            self->rotate -= 8;
            if (self->rotate < 0) {
                self->rotate = 0;
            }
            break;
        }
        MoveBoat(playerInBoat, self);
        break;
    case 8:
        // Begin rowing again after falling off waterfall
        if ((AnimateEntity(anim_row, ferrymanEntity) & 0x80) &&
            (ferrymanEntity->pose == 2)) {
            g_api.PlaySfx(SFX_OAR_ROW);
        }
        if (ferrymanEntity->pose > 1 && ferrymanEntity->pose < 5) {
            if (self->ext.ferrymanBoat.accelerationX > FIX(-1.5)) {
                self->ext.ferrymanBoat.accelerationX -= FIX(0.09375);
            }
        } else {
            if (self->ext.ferrymanBoat.accelerationX != 0) {
                self->ext.ferrymanBoat.accelerationX += FIX(0.02345);
            }
            if (ferrymanEntity->pose == 5) {
                offset = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                if (self->facingLeft) {
                    if (offset > 928) {
                        self->step++;
                    }
                } else if (offset < 864) {
                    self->step++;
                }
            }
        }
        if (self->facingLeft) {
            self->velocityX = -self->ext.ferrymanBoat.accelerationX;
        } else {
            self->velocityX = self->ext.ferrymanBoat.accelerationX;
        }
        MoveBoat(playerInBoat, self);
        break;
    case 9:
        if ((AnimateEntity(anim_stationary, ferrymanEntity) & 0x80) &&
            (ferrymanEntity->pose == 2)) {
            g_api.PlaySfx(SFX_OAR_ROW);
        }
        if (ferrymanEntity->pose > 1 && ferrymanEntity->pose < 5) {
            if (self->ext.ferrymanBoat.accelerationX > FIX(-1.5)) {
                self->ext.ferrymanBoat.accelerationX -= FIX(0.09375);
            }
        } else {
            self->ext.ferrymanBoat.accelerationX += FIX(0.0127);
            if (self->ext.ferrymanBoat.accelerationX > 0) {
                self->ext.ferrymanBoat.accelerationX = 0;
                self->step++;

                if (self->facingLeft) {
                    ferrymanEntity = self - 4;
                } else {
                    ferrymanEntity = self - 3;
                }
                // take note! this is no longer referencing the ferryman
                ferrymanEntity->ext.boatElevator.unk7C = 1;
            }
        }
        if (self->facingLeft) {
            self->velocityX = -self->ext.ferrymanBoat.accelerationX;
        } else {
            self->velocityX = self->ext.ferrymanBoat.accelerationX;
        }
        MoveBoat(playerInBoat, self);
        break;
    case 10:
        MoveBoat(playerInBoat, self);
        if (self->ext.ferrymanBoat.unk94) {
            self->step++;
        }
        break;
    case 11:
        MoveBoat(playerInBoat, self);
        if (!self->ext.ferrymanBoat.unk94) {
            self->step++;
        }
        break;
    case 12:
        // Getting moved by boat elevator
        offset = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        switch (self->step_s) {
        case 0:
            if (self->velocityY < FIX(4.0)) {
                self->velocityY += FIX(0.25);
            }
            if (offset > 0xA0) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_ID(SPLASH_WATER), tempEntity);
                    tempEntity->posY.i.hi = 176 - g_Tilemap.scrollY.i.hi;
                    tempEntity->zPriority = 155;
                    if (self->facingLeft) {
                        tempEntity->posX.i.hi = self->posX.i.hi + 40;
                    } else {
                        tempEntity->posX.i.hi = self->posX.i.hi - 40;
                    }
                    tempEntity->params = 2;
                }
                self->ext.ferrymanBoat.splashTimer = 3;
                self->step_s++;
            }
            break;
        case 1:
            if (self->ext.ferrymanBoat.splashTimer) {
                self->ext.ferrymanBoat.splashTimer--;
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_ID(SPLASH_WATER), tempEntity);
                    tempEntity->posY.i.hi = 176 - g_Tilemap.scrollY.i.hi;
                    tempEntity->zPriority = 155;
                    if (self->facingLeft) {
                        tempEntity->posX.i.hi =
                            (self->posX.i.hi - 0x1A) +
                            (self->ext.ferrymanBoat.splashTimer * 0x16);
                    } else {
                        tempEntity->posX.i.hi =
                            (self->posX.i.hi + 0x1A) -
                            (self->ext.ferrymanBoat.splashTimer * 0x16);
                    }
                    tempEntity->params = 2;
                }
            }
            if (offset >= 176) {
                self->velocityX = 0;
                self->velocityY -= FIX(0.625);
                self->step_s++;
            }
            break;
        case 2:
            self->velocityY -= FIX(0.625);
            if (offset < 177) {
                self->posY.i.hi = 0xB0 - g_Tilemap.scrollY.i.hi;
                self->velocityY = 0;
                self->ext.ferrymanBoat.accelerationX = 0;
                self->ext.ferrymanBoat.flags = 0;
                self->step++;
                self->step_s = 0;
                ferrymanEntity->pose = 0;
                ferrymanEntity->poseTimer = 0;
            }
            break;
        }
        MoveBoat(playerInBoat, self);
        break;
    case 13:
        // Begin rowing animation after being lifted by elevator
        if ((AnimateEntity(anim_row, ferrymanEntity) & 0x80) &&
            (ferrymanEntity->pose == 2)) {
            g_api.PlaySfx(SFX_OAR_ROW);
        }
        if (ferrymanEntity->pose > 1 && ferrymanEntity->pose < 5) {
            if (self->ext.ferrymanBoat.accelerationX > FIX(-1.5)) {
                self->ext.ferrymanBoat.accelerationX -= FIX(0.09375);
            }
        } else {
            if (self->ext.ferrymanBoat.accelerationX != 0) {
                self->ext.ferrymanBoat.accelerationX += FIX(0.02345);
            }
            if (ferrymanEntity->pose == 5) {
                offset = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                if (self->facingLeft) {
                    if (offset > 1792) {
                        self->step++;
                    }
                } else if (offset < 864) {
                    self->step++;
                }
            }
        }
        if (self->facingLeft) {
            self->velocityX = -self->ext.ferrymanBoat.accelerationX;
        } else {
            self->velocityX = self->ext.ferrymanBoat.accelerationX;
        }
        MoveBoat(playerInBoat, self);
        break;
    case 14:
        // Finshed our journey
        if ((AnimateEntity(anim_stationary, ferrymanEntity) & 0x80) &&
            (ferrymanEntity->pose == 2)) {
            g_api.PlaySfx(SFX_OAR_ROW);
        }
        if (ferrymanEntity->pose > 1 && ferrymanEntity->pose < 5) {
            if (self->ext.ferrymanBoat.accelerationX > FIX(-1.5)) {
                self->ext.ferrymanBoat.accelerationX -= FIX(0.09375);
            }
        } else {
            if (self->facingLeft) {
                self->ext.ferrymanBoat.accelerationX += FIX(0.0068359375);
            } else {
                self->ext.ferrymanBoat.accelerationX += FIX(0.0126953125);
            }
            if (self->ext.ferrymanBoat.accelerationX > 0) {
                self->ext.ferrymanBoat.accelerationX = 0;
            }
        }
        if (self->facingLeft) {
            self->velocityX = -self->ext.ferrymanBoat.accelerationX;
        } else {
            self->velocityX = self->ext.ferrymanBoat.accelerationX;
        }
        MoveBoat(playerInBoat, self);
        break;
    }
    self->ext.ferrymanBoat.unk94 = false;
}

void EntityFerryman(Entity* self) {
    Entity* boatEntity = self - 1;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 0x1C;
        self->flags |= FLAG_POS_CAMERA_LOCKED;
        self->drawFlags = FLAG_DRAW_ROTATE;
        self->zPriority = 0x9A;
    }

    self->posX.i.hi = boatEntity->posX.i.hi;
    self->rotate = boatEntity->rotate;

    if (self->facingLeft) {
        self->posX.i.hi += 4;
    } else {
        self->posX.i.hi -= 4;
    }

    self->posY.i.hi = boatEntity->posY.i.hi;
}

static u16 arr_indexes[] = {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
// 2 elements of prim values { u0/2, u1/3, v0/1, v2/3 }
static u8 D_us_801816D4[2][4] = {
    {0xC1, 0xDF, 0xE1, 0xFF}, {0xF4, 0xFC, 0x9C, 0xFC}};

// clang-format off
// 6 elements of { xOffset, yOffset }
static s16 D_us_801816DC[] = {
    1040, 48,
    1040, 416,
    1280, 48,
    736, 48,
    736, 416,
    496, 48
};


// 30 elements of { case, xOffset, yOffset }
static s16 D_us_801816F4[] = {
    0, 1058, -16,
    0, 1058, 80,
    0, 1058, 176,
    0, 1058, 272,
    1, 1022, 0,
    1, 1022, 96,
    1, 1022, 192,
    1, 1022, 288,
    2, 1080, 66,
    2, 1176, 66,
    0, 718, -16,
    0, 718, 80,
    0, 718, 176,
    0, 718, 272,
    1, 754, 0,
    1, 754, 96,
    1, 754, 192,
    1, 754, 288,
    3, 512, 64,
    3, 608, 64
};
// clang-format on

// Controls drawing of the boat elevator chains and rotating gear mechanism
void EntityBoatElevatorChains(Entity* self) {
    u32 primIndex;
    u32 scrollX;

    u32 scrollY;
    s16 cos;
    u8* ptr;
    s32 i;
    s16* ptrTwo;
    s16 sin;
    s16 xOffset;
    s16 yOffset;
    Primitive* prim;

    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 13);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];

            i = 0;
            while (prim != NULL) {
                prim->tpage = 0xF;
                prim->clut = 0x5F;
                ptr = *D_us_801816D4;
                ptr += arr_indexes[i] * 4;
                prim->u0 = prim->u2 = *ptr++;
                prim->u1 = prim->u3 = *ptr++;
                prim->v0 = prim->v1 = *ptr++;
                prim->v2 = prim->v3 = *ptr;
                prim->priority = 0x80;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
                i++;
            }
            self->rotate = 0x200;
        } else {
            self->step = 0;
            return;
        }
    }

    if (self->ext.boatElevator_child.unk7C) {
        if (self->ext.boatElevator_child.unk7C < 0) {
            self->ext.boatElevator_child.unk7E++;
            self->rotate += 0x10;
        } else {
            self->ext.boatElevator_child.unk7E--;
            self->rotate -= 0x10;
        }
    }
    self->ext.boatElevator_child.unk7E &= 0xF;
    prim = &g_PrimBuf[self->primIndex];
    i = 0;
    while (prim != NULL) {
        if (i < 3) {
            ptrTwo = &D_us_801816DC[(self->params * 6) + (i * 2)];
            xOffset = *ptrTwo++ - scrollX;
            yOffset = *ptrTwo - scrollY;
            if (self->params) {
                sin = (rsin(-self->rotate) * 0x1A) >> 0xC;
                cos = (rcos(-self->rotate) * 0x1A) >> 0xC;
            } else {
                sin = (rsin(self->rotate) * 0x1A) >> 0xC;
                cos = (rcos(self->rotate) * 0x1A) >> 0xC;
            }

            prim->x0 = xOffset - cos;
            prim->x1 = xOffset + sin;
            prim->x2 = xOffset - sin;
            prim->x3 = xOffset + cos;
            prim->y0 = yOffset - sin;
            prim->y1 = yOffset - cos;
            prim->y2 = yOffset + cos;
            prim->y3 = yOffset + sin;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        } else {
            ptrTwo = &D_us_801816F4[(self->params * 3) * 10 + ((i - 3) * 3)];
            sin = *ptrTwo++;
            xOffset = *ptrTwo++ - scrollX;
            yOffset = *ptrTwo - scrollY;
            switch (sin) {
            case 0:
                prim->x0 = prim->x2 = xOffset - 4;
                prim->x1 = prim->x3 = xOffset + 4;
                yOffset += self->ext.boatElevator_child.unk7E;
                prim->y0 = prim->y1 = yOffset;
                prim->y2 = prim->y3 = yOffset + 0x60;
                break;
            case 1:
                prim->x0 = prim->x2 = xOffset - 4;
                prim->x1 = prim->x3 = xOffset + 4;
                yOffset -= self->ext.boatElevator_child.unk7E;
                prim->y0 = prim->y1 = yOffset;
                prim->y2 = prim->y3 = yOffset + 0x60;
                break;
            case 2:
                xOffset -= self->ext.boatElevator_child.unk7E;
                prim->x0 = prim->x1 = xOffset;
                prim->x2 = prim->x3 = xOffset + 0x60;
                prim->y1 = prim->y3 = yOffset - 4;
                prim->y0 = prim->y2 = yOffset + 4;
                break;
            case 3:
                xOffset += self->ext.boatElevator_child.unk7E;
                prim->x0 = prim->x1 = xOffset;
                prim->x2 = prim->x3 = xOffset + 0x60;
                prim->y1 = prim->y3 = yOffset - 4;
                prim->y0 = prim->y2 = yOffset + 4;
                break;
            }
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
        i++;
    }
}

void func_us_801C7204(Entity* entity, s32 arg1) {
    if (entity->ext.boatElevator.unk7E) {
        return;
    }

    PlaySfxPositional(SFX_LEVER_METAL_BANG);
    entity->ext.boatElevator.unk88 = arg1;
    entity->ext.boatElevator.unk8C = -(entity->ext.boatElevator.unk88 / 16);
    entity->ext.boatElevator.unk7E = 1;
}

// 5 elements of prim values { u0/2, u1/3, v0/1, v2/3, priority }
static u8 D_us_8018176C[5][5] = {
    {0xE4, 0xEC, 0xC4, 0xD6, 0x85},
    {0xE2, 0xEE, 0xE1, 0xFF, 0x84},
    {0xE4, 0xEC, 0xC4, 0xD6, 0x83},
    {0xE2, 0xEE, 0xE1, 0xFF, 0x82},
    {0x80, 0xC0, 0xE1, 0xFF, 0x81}};
static s16 D_us_80181788[5][8] = {
    {-4, -12, 4, -12, -4, 6, 4, 6},
    {-6, -2, 6, -2, -6, 28, 6, 28},
    {-4, -4, 4, -4, -4, 14, 4, 14},
    {-6, -2, 6, -2, -6, 28, 6, 28},
    {-32, -3, 32, -3, -32, 27, 32, 27}};

void MoveBoatElevator(
    Entity* entity, s32 arg1, s16 posX, s16 posY, u16 collisionDetected) {
    u32 i;
    s16* ptr;
    Entity* player;
    Entity* tempEntity;
    s16 posYTemp;
    s16 posXTemp;
    s16 var_s5;
    s16 var_s4;
    Primitive* prim;
    u16 angle;
    long var_s1;
    long var_s0;

    player = &PLAYER;
    if (!entity->ext.boatElevator.unk7C) {
        arg1 = false;
    }

    if (entity->ext.boatElevator.unk7E) {
        entity->ext.boatElevator.unk88 += entity->ext.boatElevator.unk8C;
        var_s0 = entity->ext.boatElevator.unk84;
        entity->ext.boatElevator.unk84 += entity->ext.boatElevator.unk88;

        if ((var_s0 < 0 && entity->ext.boatElevator.unk84 >= 0) ||
            (var_s0 > 0 && entity->ext.boatElevator.unk84 <= 0)) {
            entity->ext.boatElevator.unk88 /= 2;
            if (entity->ext.boatElevator.unk88 < 0x20000 &&
                entity->ext.boatElevator.unk88 > -0x20000) {
                entity->ext.boatElevator.unk84 = 0;
                entity->ext.boatElevator.unk7E = 0;
            } else {
                entity->ext.boatElevator.unk8C =
                    -entity->ext.boatElevator.unk8C / 2;
            }
        }
    }
    angle = entity->ext.boatElevator_child.unk86;
    ptr = *D_us_80181788;
    posXTemp = posX;
    posYTemp = posY;

    for (i = 0, prim = &g_PrimBuf[entity->primIndex]; prim != NULL; i++) {
        switch (i) {
        case 0:
            var_s0 = 0;
            var_s1 = 0x1000;
            break;
        case 1:
            var_s0 = rsin(angle / 2);
            var_s1 = rcos(angle / 2);
            break;
        case 2:
            var_s0 = rsin(angle / 2);
            var_s1 = rcos(angle / 2);
            posXTemp -= (var_s0 * 0x16) >> 0xC;
            posYTemp += (var_s1 * 0x16) >> 0xC;
            break;
        case 3:
            var_s0 = rsin(angle);
            var_s1 = rcos(angle);
            posXTemp -= (rsin(angle / 2) * 8) >> 0xC;
            posYTemp += (rcos(angle / 2) * 8) >> 0xC;
            break;
        case 4:
            var_s0 = rsin(angle);
            var_s1 = rcos(angle);
            posX = posXTemp - ((var_s0 * 4) >> 0xC);
            posY = posYTemp + ((var_s1 * 4) >> 0xC);
            if (entity->params) {
                tempEntity = entity + 3;
            } else {
                tempEntity = entity + 4;
            }
            tempEntity->ext.boatElevator_child.unk94 |= arg1;
            if (arg1) {
                if (tempEntity->facingLeft) {
                    tempEntity->rotate = -angle & 0xFFF;
                    tempEntity->ext.boatElevator_child.unk98 =
                        posXTemp + (((var_s1 * 2) - (var_s0 * 0x22)) >> 0xC);
                    tempEntity->ext.boatElevator_child.unk9A =
                        posYTemp + (((var_s0 * 2) + (var_s1 * 0x22)) >> 0xC);
                } else {
                    tempEntity->rotate = angle;
                    tempEntity->ext.boatElevator_child.unk98 =
                        posXTemp + (((var_s1 * -3) - (var_s0 * 0x22)) >> 0xC);
                    tempEntity->ext.boatElevator_child.unk9A =
                        posYTemp + (((var_s0 * -3) + (var_s1 * 0x22)) >> 0xC);
                }
            }
            posXTemp -= (var_s0 * 0x16) >> 0xC;
            posYTemp += (var_s1 * 0x16) >> 0xC;
            break;
        }

        var_s5 = *ptr++;
        var_s4 = *ptr++;
        prim->x0 = posXTemp + (((var_s5 * var_s1) - (var_s4 * var_s0)) >> 0xC);
        prim->y0 = posYTemp + (((var_s5 * var_s0) + (var_s4 * var_s1)) >> 0xC);

        var_s5 = *ptr++;
        var_s4 = *ptr++;
        prim->x1 = posXTemp + (((var_s5 * var_s1) - (var_s4 * var_s0)) >> 0xC);
        prim->y1 = posYTemp + (((var_s5 * var_s0) + (var_s4 * var_s1)) >> 0xC);

        var_s5 = *ptr++;
        var_s4 = *ptr++;
        prim->x2 = posXTemp + (((var_s5 * var_s1) - (var_s4 * var_s0)) >> 0xC);
        prim->y2 = posYTemp + (((var_s5 * var_s0) + (var_s4 * var_s1)) >> 0xC);

        var_s5 = *ptr++;
        var_s4 = *ptr++;
        prim->x3 = posXTemp + (((var_s5 * var_s1) - (var_s4 * var_s0)) >> 0xC);
        prim->y3 = posYTemp + (((var_s5 * var_s0) + (var_s4 * var_s1)) >> 0xC);

        prim = prim->next;
    }

    if (collisionDetected) {
        posXTemp = posX - entity->posX.i.hi;
        posYTemp = posY - entity->posY.i.hi;
        if (posXTemp > 0) {
            if (!(g_Player.vram_flag & TOUCHING_R_WALL)) {
                player->posX.i.hi += posXTemp;
                D_80097488.x.i.hi += posXTemp;
            }
        } else if (!(g_Player.vram_flag & TOUCHING_L_WALL)) {
            player->posX.i.hi += posXTemp;
            D_80097488.x.i.hi += posXTemp;
        }
        player->posY.i.hi += posYTemp;
        D_80097488.y.i.hi += posYTemp;
    }
    entity->posX.i.hi = posX;
    entity->posY.i.hi = posY;
    entity->rotate = angle;
}

static u8 anim_floor_open[] = {0x04, 0x23, 0x84, 0x24, 0xFF, 0x00, 0x00, 0x00};
static u8 anim_floor_close[] = {0x04, 0x23, 0x04, 0x05, 0xFF, 0x00, 0x00, 0x00};

#ifdef VERSION_PSP
#define COLLISION_WIDTH 0x24
#else
#define COLLISION_WIDTH 0x20
#endif

void EntityBoatElevatorController(Entity* self) {
    s32 primIndex;
    s32 sp38;
    s32 sp34;

    u16 var_s8;
    u32 scrollY;
    u16 collision;
    Entity* entity;
    u32 scrollX;
    s16 posY;
    s16 posX;
    u8* ptr;
    Primitive* prim;

    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    if (self->step && self->ext.boatElevator.unk90 == 0) {
        self->posY.i.hi += 0x2C;
        if (self->ext.boatElevator.unk9A) {
            self->ext.boatElevator.unk9A -= 1;
            collision = false;
        } else {
            collision = GetPlayerCollisionWith(self, COLLISION_WIDTH, 5, 4);
            // Possible !BUG: duplicate && condition here
            if (!collision && self->ext.boatElevator.collisionDetected &&
                self->ext.boatElevator.collisionDetected) {
                self->ext.boatElevator.unk9A = 4;
            }
        }
        self->ext.boatElevator.collisionDetected = collision;
        self->posY.i.hi -= 0x2C;
    }

    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 5);
        if (primIndex != -1) {
            InitializeEntity(g_EInitInteractable);
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            self->drawFlags = FLAG_DRAW_ROTATE;
            prim = &g_PrimBuf[primIndex];
            sp38 = 0;
            ptr = *D_us_8018176C;

            while (prim != NULL) {
                prim->clut = 0x5F;
                prim->tpage = 0xF;
                prim->u0 = prim->u2 = *ptr++;
                prim->u1 = prim->u3 = *ptr++;
                prim->v0 = prim->v1 = *ptr++;
                prim->v2 = prim->v3 = *ptr++;
                prim->priority = *ptr++;
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
            }
            self->animSet = ANIMSET_OVL(1);
            self->animCurFrame = 5;
            self->zPriority = 0x9C;
            self->ext.boatElevator.unk80 = 0;
            self->ext.boatElevator.unk84 = 0x8000;
            return;
        }
        break;
    case 1:
        entity = self + 2;
        entity->ext.boatElevator_child.unk7C = 0;
        var_s8 = true;
        if (self->params) {
            entity = self + 3;
            if (!entity->facingLeft) {
                var_s8 = false;
            }
        } else {
            entity = self + 4;
            if (entity->facingLeft) {
                var_s8 = false;
            }
        }
        if (!var_s8 && (entity->step < 4 || entity->step > 12)) {
            var_s8 = true;
        }
        if ((var_s8 && collision) || self->ext.boatElevator.unk7C) {
            self->step++;
            func_us_801C7204(self, 0xFFFC0000);
        }

        posY = 0xF0 - scrollY;
        if (self->params) {
            posX = 0x2CE - scrollX;
        } else {
            posX = 0x422 - scrollX;
        }
        MoveBoatElevator(self, false, posX, posY, collision);
        return;
    case 2:
        entity = self + 2;
        entity->ext.boatElevator_child.unk7C = 1;
        self->ext.boatElevator.unk80++;
        if (self->ext.boatElevator.unk80 > 0xA2) {
            posY = 0x4E;
            if (self->params) {
                posX = (0x2CE - scrollX) - self->ext.boatElevator.unk80 + 0xA2;
            } else {
                posX = (0x2CE - scrollX) + self->ext.boatElevator.unk80 + 0xB2;
            }
            if (self->ext.boatElevator.unk80 == 0x188) {
                if (self->params) {
                    func_us_801C7204(self, 0x80000);
                } else {
                    func_us_801C7204(self, -0x80000);
                }
                self->step++;
                self->ext.boatElevator.unk82 = 0x80;
            }
        } else {
            posY = 0xF0 - (self->ext.boatElevator.unk80);
            if (self->params) {
                posX = 0x2CE - scrollX;
                if (self->ext.boatElevator.unk80 == 0xA2) {
                    func_us_801C7204(self, -0x80000);
                }
            } else {
                posX = 0x422 - scrollX;
                if (self->ext.boatElevator.unk80 == 0xA2) {
                    func_us_801C7204(self, 0x80000);
                }
            }
        }
        if (posY < 0xDF && self->ext.boatElevator.unk7C) {
            if (posY == 0xDE) {
                if (self->params) {
                    func_us_801C7204(self, 0x50000);
                } else {
                    func_us_801C7204(self, -0x50000);
                }
            }
            sp34 = true;
        } else {
            sp34 = false;
        }
        posY -= scrollY;
        MoveBoatElevator(self, sp34, posX, posY, collision);
        if (!(self->ext.boatElevator.unk94 % 10)) {
            self->ext.boatElevator.unk94 = 0;
            PlaySfxPositional(SFX_METAL_RATTLE_A);
        }
        self->ext.boatElevator.unk94++;
        break;
    case 3:
        entity = self + 2;
        entity->ext.boatElevator_child.unk7C = 0;
        if (!--self->ext.boatElevator.unk82) {
            self->step++;
            PlaySfxPositional(SFX_LEVER_METAL_BANG);
        }

        posY = 0x4E - scrollY;
        if (self->params) {
            posX = 0x1E8 - scrollX;
        } else {
            posX = 0x508 - scrollX;
        }
        MoveBoatElevator(self, true, posX, posY, collision);
        break;
    case 4:
        // End of the line, drop the boat
        self->zPriority = 0x82;
        self->ext.boatElevator.unk90 = 1;
        self->ext.boatElevator.unk7C = 0;
        if (!AnimateEntity(anim_floor_open, self)) {
            self->pose = 0;
            self->poseTimer = 0;
            self->step++;
        }

        posY = 0x4E - scrollY;
        if (self->params) {
            posX = 0x1E8 - scrollX;
        } else {
            posX = 0x508 - scrollX;
        }
        MoveBoatElevator(self, false, posX, posY, collision);
        break;
    case 5:
        // Dropped the boat, now close the floor back up
        if (!AnimateEntity(anim_floor_close, self)) {
            if (self->params) {
                func_us_801C7204(self, -0x50000);
            } else {
                func_us_801C7204(self, 0x50000);
            }
            self->step++;
            self->ext.boatElevator.unk82 = 0x40;
        }
        if (self->pose == 2) {
            self->ext.boatElevator.unk90 = 0;
            self->zPriority = 0x9C;
        }

        posY = 0x4E - scrollY;
        if (self->params) {
            posX = 0x1E8 - scrollX;
        } else {
            posX = 0x508 - scrollX;
        }
        MoveBoatElevator(self, false, posX, posY, collision);
        break;
    case 6:
        if (!--self->ext.boatElevator.unk82) {
            if (self->params) {
                func_us_801C7204(self, 0x80000);
            } else {
                func_us_801C7204(self, -0x80000);
            }
            self->step++;
        }

        posY = 0x4E - scrollY;
        if (self->params) {
            posX = 0x1E8 - scrollX;
        } else {
            posX = 0x508 - scrollX;
        }
        MoveBoatElevator(self, false, posX, posY, collision);
        break;
    case 7:
        entity = self + 2;
        entity->ext.boatElevator_child.unk7C = -1;
        if (!--self->ext.boatElevator.unk80) {
            SetStep(1);
        }

        if (self->ext.boatElevator.unk80 > 0xA2) {
            posY = 0x4E;
            if (self->params) {
                posX = (0x2CE - scrollX) - self->ext.boatElevator.unk80 + 0xA2;
                if (self->ext.boatElevator.unk80 == 0xA3) {
                    func_us_801C7204(self, -0x80000);
                }
            } else {
                posX = (0x2CE - scrollX) + self->ext.boatElevator.unk80 + 0xB2;
                if (self->ext.boatElevator.unk80 == 0xA3) {
                    func_us_801C7204(self, 0x80000);
                }
            }
        } else {
            posY = 0xF0 - (self->ext.boatElevator.unk80);
            if (self->params) {
                posX = 0x2CE - scrollX;
            } else {
                posX = 0x422 - scrollX;
            }
        }
        posY -= scrollY;
        MoveBoatElevator(self, false, posX, posY, collision);

        if (!(self->ext.boatElevator.unk94 % 10)) {
            self->ext.boatElevator.unk94 = 0;
            PlaySfxPositional(SFX_METAL_RATTLE_A);
        }
        self->ext.boatElevator.unk94++;
        break;
    }
}

void EntityFerrymanUnused(Entity* self) {}

static u16 tiles[7][2] = {
    {884, 884}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

void LoadFerrymanGateTiles(void) {
    u16* tileLayoutPtr;
    Tilemap* tileMap;
    s32 i;
    s16 offset;

    tileMap = &g_Tilemap;
    offset = 0x595;
    tileLayoutPtr = *tiles;

    for (i = 0; i < LEN(tiles); i++) {
        tileMap->fg[offset] = *tileLayoutPtr++;
        offset++;
        tileMap->fg[offset] = *tileLayoutPtr++;
        offset += 0xCF;
    }
}

#ifdef VERSION_PSP
extern s32 E_ID(SURFACING_WATER);
#endif

void EntityFerrymanGateController(Entity* self) {
    Entity* newEntity;
    s16 offsetY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        if (g_CastleFlags[FERRYMAN_GATE_OPEN]) {
            LoadFerrymanGateTiles();
            DestroyEntity(self);
            break;
        }
        self->animCurFrame = 24;
        break;
    case 1:
        if (g_CastleFlags[FERRYMAN_GATE_OPEN]) {
            GetPlayerCollisionWith(self, 16, 56, 3);
            LoadFerrymanGateTiles();
            self->step++;
            self->ext.et_surfacingWater.unk80 = 0;
            break;
        }
        break;
    case 2:
        if (!(self->ext.et_surfacingWater.unk80++ & 15)) {
            PlaySfxPositional(SFX_STONE_MOVE_C);
        }

        self->posY.i.hi--;
        offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

        if (offsetY > 124) {
            if (self->ext.et_surfacingWater.unk7C) {
                self->ext.et_surfacingWater.unk7C--;
            } else {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_ID(SURFACING_WATER), newEntity);
                    newEntity->posY.i.hi = 176 - g_Tilemap.scrollY.i.hi;
                    newEntity->posX.i.hi +=
                        (self->ext.et_surfacingWater.unk7E * 8) - 16;
                    newEntity->params = 0x8000;
                    newEntity->ext.et_surfacingWater.origPosX = 23;
                    newEntity->zPriority = 155;
                }

                self->ext.et_surfacingWater.unk7E++;
                if (self->ext.et_surfacingWater.unk7E > 4) {
                    self->ext.et_surfacingWater.unk7E = 0;
                }
                self->ext.et_surfacingWater.unk7C = 1;
            }
        }

        GetPlayerCollisionWith(self, 16, 60, 3);

        if (offsetY < 36) {
            DestroyEntity(self);
        }
        break;
    }
}
