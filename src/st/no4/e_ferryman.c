// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

extern s16 D_us_80180F1A[];
#ifdef VERSION_PSP
extern s32 E_ID(SURFACING_WATER);
#endif

void func_us_801C59E0(Entity* self, s16 xOffset) {
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

void func_us_801C5AD4(u16 collision, Entity* entity) {
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
                func_us_801C59E0(entity, 40);
                tempEntity = entity + 1;
                if (tempEntity->animCurFrame == 0x1E ||
                    tempEntity->animCurFrame == 0x1F) {
                    func_us_801C59E0(entity, -56);
                }
            }
        } else {
            entity->ext.et_surfacingWater.unk8C--;
        }
    }

    tempEntity = &PLAYER;
    if (collision) {
        if (posX > 0) {
            if (!(g_Player.vram_flag & 4)) {
                tempEntity->posX.i.hi += posX;
                D_80097488.x.i.hi += posX;
            }
        } else if (!(g_Player.vram_flag & 8)) {
            tempEntity->posX.i.hi += posX;
            D_80097488.x.i.hi += posX;
        }
        tempEntity->posY.i.hi += posY;
        D_80097488.y.i.hi += posY;
    }
}

extern u32 g_CutsceneFlags;
static u8 D_us_80181678[] = {0x18, 0x1C, 0x10, 0x1D, 0x10, 0x1E,
                             0x10, 0x1F, 0x10, 0x20, 0x00, 0x00}; // anim
static u8 D_us_80181684[] = {
    0x18, 0x1C, 0x10, 0x1D, 0x10, 0x1E, 0x10, 0x1F,
    0x10, 0x20, 0x10, 0x1C, 0xFF, 0x00, 0x00, 0x00}; // anim
static s32 D_us_80181694[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

#ifdef VERSION_PSP
extern s32 E_ID(SPLASH_WATER);
extern s32 E_ID(ID_2E);
extern s32 E_ID(ID_4F);
#endif

// Ferryman boat travel logic
void func_us_801C5C7C(Entity* self) {
    Entity* childEntity;
    Entity* tempEntity;
    s16 offset;
    u16 collision;

    /* Check that the player is on the boat */
    tempEntity = &PLAYER;
    collision = GetPlayerCollisionWith(self, 0x24, 5, 4);
    if (collision) {
        self->posX.i.hi += 0x28;
        GetPlayerCollisionWith(self, 4, 9, 9);
        self->posX.i.hi -= 0x50;
        GetPlayerCollisionWith(self, 4, 9, 9);
        self->posX.i.hi += 0x28;
        g_Entities[UNK_ENTITY_1].ext.alucardController.unk7C = true;
    } else {
        g_Entities[UNK_ENTITY_1].ext.alucardController.unk7C = false;
    }

    if (self->step && !self->ext.ferrymanBoat.unk94) {
        if (collision && !self->ext.ferrymanBoat.unk80 &&
            !self->ext.ferrymanBoat.collision) {
            self->ext.ferrymanBoat.unk80 = 8;
        }
        if (self->ext.ferrymanBoat.unk80 != 0) {
            self->ext.ferrymanBoat.unk80--;
            offset = D_us_80181694[self->ext.ferrymanBoat.unk80];
            self->posY.i.hi += offset;
            if (collision) {
                tempEntity->posY.i.hi += offset;
                D_80097488.y.i.hi += offset;
            }
        }
    }

    self->ext.ferrymanBoat.collision = collision;
    childEntity = self + 1;
    switch (self->step) {
    case 0:
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
        CreateEntityFromCurrentEntity(E_ID(ID_2E), childEntity);
        childEntity->facingLeft = self->facingLeft;
        break;
    case 1:
        if (collision) {
            self->step++;
            tempEntity = &g_Entities[172];
            CreateEntityFromCurrentEntity(E_ID(ID_4F), tempEntity);
            tempEntity->params = self->params;
        }
        break;
    case 2:
        if (g_CutsceneFlags & 0x80) {
            self->step += 2;
        } else {
            g_Entities[UNK_ENTITY_1].ext.alucardController.unk7C = 1;
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
            g_PauseAllowed = true;
            g_unkGraphicsStruct.pauseEnemies = false;
            self->step++;
        }
        break;
    case 4:
        if ((AnimateEntity(D_us_80181678, childEntity) & 0x80) &&
            (childEntity->pose == 2)) {
            PlaySfxPositional(SFX_OAR_ROW);
        }
        if (childEntity->pose > 1 && childEntity->pose < 5) {
            if (self->ext.ferrymanBoat.accelerationX > FIX(-1.5)) {
                self->ext.ferrymanBoat.accelerationX -= 0x1800;
            }
        } else {
            if (self->ext.ferrymanBoat.accelerationX != 0) {
                self->ext.ferrymanBoat.accelerationX += 0x600;
            }
            if (!self->params) {
                if (childEntity->pose == 5) {
                    offset = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                    if (self->facingLeft) {
                        if (offset > 0xAA0 && !g_CastleFlags[0xC2]) {
                            g_CastleFlags[0xC2] = true;
                        }
                        if (offset > 0xBE0) {
                            self->step++;
                        }
                    } else if (offset < 0x120) {
                        self->step++;
                    }
                }
            } else if (childEntity->pose == 5) {
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
        func_us_801C5AD4(collision, self);
        break;
    case 5:
        if ((AnimateEntity(D_us_80181684, childEntity) & 0x80) &&
            childEntity->pose == 2) {
            g_api.PlaySfx(SFX_OAR_ROW);
        }

        if (childEntity->pose > 1 && childEntity->pose < 5) {
            if (self->ext.ferrymanBoat.accelerationX > FIX(-1.5)) {
                self->ext.ferrymanBoat.accelerationX -= 0x1800;
            }
        } else if (self->ext.ferrymanBoat.accelerationX != 0) {
            self->ext.ferrymanBoat.accelerationX += 0x300;
        }

        if (self->facingLeft) {
            self->velocityX = -self->ext.ferrymanBoat.accelerationX;
        } else {
            self->velocityX = self->ext.ferrymanBoat.accelerationX;
        }

        func_us_801C5AD4(collision, self);
        break;
    case 6:
        AnimateEntity(D_us_80181684, childEntity);
        if (childEntity->pose > 1 && childEntity->pose < 5) {
            if (self->ext.ferrymanBoat.accelerationX > FIX(-1.5)) {
                self->ext.ferrymanBoat.accelerationX -= 0x1800;
            }
        } else if (self->ext.ferrymanBoat.accelerationX < FIX(-1)) {
            self->ext.ferrymanBoat.accelerationX += 0x300;
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
        func_us_801C5AD4(collision, self);
        break;
    case 7:
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
                childEntity->pose = 0;
                childEntity->poseTimer = 0;
            }
            self->rotate -= 8;
            if (self->rotate < 0) {
                self->rotate = 0;
            }
            break;
        }
        func_us_801C5AD4(collision, self);
        break;
    case 8:
        if ((AnimateEntity(D_us_80181678, childEntity) & 0x80) &&
            (childEntity->pose == 2)) {
            g_api.PlaySfx(SFX_OAR_ROW);
        }
        if (childEntity->pose > 1 && childEntity->pose < 5) {
            if (self->ext.ferrymanBoat.accelerationX > FIX(-1.5)) {
                self->ext.ferrymanBoat.accelerationX -= 0x1800; // FIX(0.09375)
            }
        } else {
            if (self->ext.ferrymanBoat.accelerationX != 0) {
                self->ext.ferrymanBoat.accelerationX += 0x600; // FIX(0.02345)
            }
            if (childEntity->pose == 5) {
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
        func_us_801C5AD4(collision, self);
        break;
    case 9:
        if ((AnimateEntity(D_us_80181684, childEntity) & 0x80) &&
            (childEntity->pose == 2)) {
            g_api.PlaySfx(SFX_OAR_ROW);
        }
        if (childEntity->pose > 1 && childEntity->pose < 5) {
            if (self->ext.ferrymanBoat.accelerationX > FIX(-1.5)) {
                self->ext.ferrymanBoat.accelerationX -= 0x1800; // FIX(0.09375)
            }
        } else {
            self->ext.ferrymanBoat.accelerationX += 0x340; // FIX(0.0127)
            if (self->ext.ferrymanBoat.accelerationX > 0) {
                self->ext.ferrymanBoat.accelerationX = 0;
                self->step++;
                if (self->facingLeft) {
                    childEntity = self - 4;
                } else {
                    childEntity = self - 3;
                }
                childEntity->ext.ILLEGAL.s16[0] = 1; // TODO
            }
        }
        if (self->facingLeft) {
            self->velocityX = -self->ext.ferrymanBoat.accelerationX;
        } else {
            self->velocityX = self->ext.ferrymanBoat.accelerationX;
        }
        func_us_801C5AD4(collision, self);
        break;
    case 10:
        func_us_801C5AD4(collision, self);
        if (self->ext.ferrymanBoat.unk94) {
            self->step++;
        }
        break;
    case 11:
        func_us_801C5AD4(collision, self);
        if (!self->ext.ferrymanBoat.unk94) {
            self->step++;
        }
        break;
    case 12:
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
                childEntity->pose = 0;
                childEntity->poseTimer = 0;
            }
            break;
        }
        func_us_801C5AD4(collision, self);
        break;
    case 13:
        if ((AnimateEntity(D_us_80181678, childEntity) & 0x80) &&
            (childEntity->pose == 2)) {
            g_api.PlaySfx(SFX_OAR_ROW);
        }
        if (childEntity->pose > 1 && childEntity->pose < 5) {
            if (self->ext.ferrymanBoat.accelerationX > FIX(-1.5)) {
                self->ext.ferrymanBoat.accelerationX -= 0x1800; // FIX(0.09375)
            }
        } else {
            if (self->ext.ferrymanBoat.accelerationX != 0) {
                self->ext.ferrymanBoat.accelerationX += 0x600; // FIX(0.02345)
            }
            if (childEntity->pose == 5) {
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
        func_us_801C5AD4(collision, self);
        break;
    case 14:
        if ((AnimateEntity(D_us_80181684, childEntity) & 0x80) &&
            (childEntity->pose == 2)) {
            g_api.PlaySfx(SFX_OAR_ROW);
        }
        if (childEntity->pose > 1 && childEntity->pose < 5) {
            if (self->ext.ferrymanBoat.accelerationX > FIX(-1.5)) {
                self->ext.ferrymanBoat.accelerationX -= 0x1800;
            }
        } else {
            if (self->facingLeft) {
                self->ext.ferrymanBoat.accelerationX += 0x1C0;
            } else {
                self->ext.ferrymanBoat.accelerationX += 0x340;
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
        func_us_801C5AD4(collision, self);
        break;
    }
    self->ext.ferrymanBoat.unk94 = false;
}

void func_us_801C6CEC(Entity* self) {
    Entity* prev = self - 1;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 0x1C;
        self->flags |= FLAG_POS_CAMERA_LOCKED;
        self->drawFlags = FLAG_DRAW_ROTATE;
        self->zPriority = 0x9A;
    }

    self->posX.i.hi = prev->posX.i.hi;
    self->rotate = prev->rotate;

    if (self->facingLeft) {
        self->posX.i.hi += 4;
    } else {
        self->posX.i.hi -= 4;
    }

    self->posY.i.hi = prev->posY.i.hi;
}

static u16 D_us_801816B4[] = {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
static u8 D_us_801816D4[2][4] = {
    {0xC1, 0xDF, 0xE1, 0xFF}, {0xF4, 0xFC, 0x9C, 0xFC}};
static s16 D_us_801816DC[] = {0x0410, 0x0030, 0x0410, 0x01A0, 0x0500, 0x0030,
                              0x02E0, 0x0030, 0x02E0, 0x01A0, 0x01F0, 0x0030};
static s16 D_us_801816F4[] = {
    0x0000, 0x0422, 0xFFF0, 0x0000, 0x0422, 0x0050, 0x0000, 0x0422, 0x00B0,
    0x0000, 0x0422, 0x0110, 0x0001, 0x03FE, 0x0000, 0x0001, 0x03FE, 0x0060,
    0x0001, 0x03FE, 0x00C0, 0x0001, 0x03FE, 0x0120, 0x0002, 0x0438, 0x0042,
    0x0002, 0x0498, 0x0042, 0x0000, 0x02CE, 0xFFF0, 0x0000, 0x02CE, 0x0050,
    0x0000, 0x02CE, 0x00B0, 0x0000, 0x02CE, 0x0110, 0x0001, 0x02F2, 0x0000,
    0x0001, 0x02F2, 0x0060, 0x0001, 0x02F2, 0x00C0, 0x0001, 0x02F2, 0x0120,
    0x0003, 0x0200, 0x0040, 0x0003, 0x0260, 0x0040};

void func_us_801C6DA8(Entity* self) {
    u32 primIndex; // sp3C
    u32 scrollX;   // sp38

    u32 scrollY;     // s8
    s16 cos;         // s7
    u8* ptr;         // s6
    s32 i;           // s5
    s16* ptrTwo;     // s4
    s16 sin;         // s3
    s16 var_s2;      // s2
    s16 var_s1;      // s1
    Primitive* prim; // s0

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
                ptr = D_us_801816D4[0];
                ptr += D_us_801816B4[i] * 4;
                prim->u0 = prim->u2 = *ptr++;
                prim->u1 = prim->u3 = *ptr++;
                prim->v0 = prim->v1 = *ptr++;
                prim->v2 = prim->v3 = *ptr;
                prim->priority = 0x80;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
                i++;
            }
            self->rotate = 0x200U;
        } else {
            self->step = 0;
            return;
        }
    }

    if (self->ext.ferrymanUnk.unk7C) {
        if (self->ext.ferrymanUnk.unk7C < 0) {
            self->ext.ferrymanUnk.unk7E++;
            self->rotate += 0x10;
        } else {
            self->ext.ferrymanUnk.unk7E--;
            self->rotate -= 0x10;
        }
    }
    self->ext.ferrymanUnk.unk7E &= 0xF;
    prim = &g_PrimBuf[self->primIndex];
    i = 0;
    while (prim != NULL) {
        if (i < 3) {
            ptrTwo = &D_us_801816DC[(self->params * 6) + (i * 2)];
            var_s2 = *ptrTwo++ - scrollX;
            var_s1 = *ptrTwo - scrollY;
            if (self->params) {
                sin = (rsin(-self->rotate) * 0x1A) >> 0xC;
                cos = (rcos(-self->rotate) * 0x1A) >> 0xC;
            } else {
                sin = (rsin(self->rotate) * 0x1A) >> 0xC;
                cos = (rcos(self->rotate) * 0x1A) >> 0xC;
            }

            prim->x0 = var_s2 - cos;
            prim->x1 = var_s2 + sin;
            prim->x2 = var_s2 - sin;
            prim->x3 = var_s2 + cos;
            prim->y0 = var_s1 - sin;
            prim->y1 = var_s1 - cos;
            prim->y2 = var_s1 + cos;
            prim->y3 = var_s1 + sin;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        } else {
            ptrTwo = &D_us_801816F4[(self->params * 3) * 10 + ((i - 3) * 3)];
            sin = *ptrTwo++;
            var_s2 = *ptrTwo++ - scrollX;
            var_s1 = *ptrTwo - scrollY;
            switch (sin) {
            case 0:
                prim->x0 = prim->x2 = var_s2 - 4;
                prim->x1 = prim->x3 = var_s2 + 4;
                var_s1 += self->ext.ferrymanUnk.unk7E;
                prim->y0 = prim->y1 = var_s1;
                prim->y2 = prim->y3 = var_s1 + 0x60;
                break;
            case 1:
                prim->x0 = prim->x2 = var_s2 - 4;
                prim->x1 = prim->x3 = var_s2 + 4;
                var_s1 -= self->ext.ferrymanUnk.unk7E;
                prim->y0 = prim->y1 = var_s1;
                prim->y2 = prim->y3 = var_s1 + 0x60;
                break;
            case 2:
                var_s2 -= self->ext.ferrymanUnk.unk7E;
                prim->x0 = prim->x1 = var_s2;
                prim->x2 = prim->x3 = var_s2 + 0x60;
                prim->y1 = prim->y3 = var_s1 - 4;
                prim->y0 = prim->y2 = var_s1 + 4;
                break;
            case 3:
                var_s2 += self->ext.ferrymanUnk.unk7E;
                prim->x0 = prim->x1 = var_s2;
                prim->x2 = prim->x3 = var_s2 + 0x60;
                prim->y1 = prim->y3 = var_s1 - 4;
                prim->y0 = prim->y2 = var_s1 + 4;
                break;
            }
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
        i += 1;
    }
}

void func_us_801C7204(Entity* entity, s32 arg1) {
    s32 var_a1;

    if (entity->ext.ferrymanUnk.unk7E) {
        return;
    }

    PlaySfxPositional(SFX_LEVER_METAL_BANG);
    entity->ext.ferrymanUnk.unk88 = arg1;
    entity->ext.ferrymanUnk.unk8C = -(entity->ext.ferrymanUnk.unk88 / 16);
    entity->ext.ferrymanUnk.unk7E = 1;
}

static u8 D_us_8018176C[] = {
    0xE4, 0xEC, 0xC4, 0xD6, 0x85, 0xE2, 0xEE, 0xE1, 0xFF, 0x84,
    0xE4, 0xEC, 0xC4, 0xD6, 0x83, 0xE2, 0xEE, 0xE1, 0xFF, 0x82,
    0x80, 0xC0, 0xE1, 0xFF, 0x81, 0x00, 0x00, 0x00};
static s16 D_us_80181788[] = {
    0xFFFC, 0xFFF4, 0x0004, 0xFFF4, 0xFFFC, 0x0006, 0x0004, 0x0006,
    0xFFFA, 0xFFFE, 0x0006, 0xFFFE, 0xFFFA, 0x001C, 0x0006, 0x001C,
    0xFFFC, 0xFFFC, 0x0004, 0xFFFC, 0xFFFC, 0x000E, 0x0004, 0x000E,
    0xFFFA, 0xFFFE, 0x0006, 0xFFFE, 0xFFFA, 0x001C, 0x0006, 0x001C,
    0xFFE0, 0xFFFD, 0x0020, 0xFFFD, 0xFFE0, 0x001B, 0x0020, 0x001B};

void func_us_801C726C(Entity* entity, s32 arg1, s16 posX, s16 posY, u16 arg4) {
    u32 i;              // sp3C
    s16* sp38;          // sp38
    Entity* player;     // sp34
    Entity* tempEntity; // s8
    s16 var_s7;         // s7
    s16 var_s6;         // s6
    s16 var_s5;         // s5
    s16 var_s4;         // s4
    Primitive* prim;    // s3
    u16 var_s2;         // s2
    long var_s1;        // s1
    long var_s0;        // s0

    player = &PLAYER;
    if (!entity->ext.et_801C726C.unk7C) {
        arg1 = 0;
    }

    if (entity->ext.et_801C726C.unk7E) {
        entity->ext.et_801C726C.unk88 += entity->ext.et_801C726C.unk8C;
        var_s0 = entity->ext.et_801C726C.unk84;
        entity->ext.et_801C726C.unk84 += entity->ext.et_801C726C.unk88;

        if ((var_s0 < 0 && entity->ext.et_801C726C.unk84 >= 0) ||
            (var_s0 > 0 && entity->ext.et_801C726C.unk84 <= 0)) {
            entity->ext.et_801C726C.unk88 /= 2;
            if (entity->ext.et_801C726C.unk88 < 0x20000 &&
                entity->ext.et_801C726C.unk88 > -0x20000) {
                entity->ext.et_801C726C.unk84 = 0;
                entity->ext.et_801C726C.unk7E = 0;
            } else {
                entity->ext.et_801C726C.unk8C =
                    -entity->ext.et_801C726C.unk8C / 2; // TODO: negative
            }
        }
    }
    var_s2 = entity->ext.et_801C726C_child.unk86;
    sp38 = D_us_80181788;
    var_s6 = posX;
    var_s7 = posY;

    for (i = 0, prim = &g_PrimBuf[entity->primIndex]; prim != NULL; i++) {
        switch (i) {
        case 0:
            var_s0 = 0;
            var_s1 = 0x1000;
            break;
        case 1:
            var_s0 = rsin(var_s2 / 2);
            var_s1 = rcos(var_s2 / 2);
            break;
        case 2:
            var_s0 = rsin(var_s2 / 2);
            var_s1 = rcos(var_s2 / 2);
            var_s6 -= (var_s0 * 0x16) >> 0xC;
            var_s7 += (var_s1 * 0x16) >> 0xC;
            break;
        case 3:
            var_s0 = rsin(var_s2);
            var_s1 = rcos(var_s2);
            var_s6 -= (rsin(var_s2 / 2) * 8) >> 0xC;
            var_s7 += (rcos(var_s2 / 2) * 8) >> 0xC;
            break;
        case 4:
            var_s0 = rsin(var_s2);
            var_s1 = rcos(var_s2);
            posX = var_s6 - ((var_s0 * 4) >> 0xC);
            posY = var_s7 + ((var_s1 * 4) >> 0xC);
            if (entity->params) {
                tempEntity = entity + 3;
            } else {
                tempEntity = entity + 4;
            }
            tempEntity->ext.et_801C726C_child.unk94 |= arg1;
            if (arg1) {
                if (tempEntity->facingLeft) {
                    tempEntity->rotate = -var_s2 & 0xFFF;
                    tempEntity->ext.et_801C726C_child.unk98 =
                        var_s6 + (((var_s1 * 2) - (var_s0 * 0x22)) >> 0xC);
                    tempEntity->ext.et_801C726C_child.unk9A =
                        var_s7 + (((var_s0 * 2) + (var_s1 * 0x22)) >> 0xC);
                } else {
                    tempEntity->rotate = var_s2;
                    tempEntity->ext.et_801C726C_child.unk98 =
                        var_s6 + (((var_s1 * -3) - (var_s0 * 0x22)) >> 0xC);
                    tempEntity->ext.et_801C726C_child.unk9A =
                        var_s7 + (((var_s0 * -3) + (var_s1 * 0x22)) >> 0xC);
                }
            }
            var_s6 -= (var_s0 * 0x16) >> 0xC;
            var_s7 += (var_s1 * 0x16) >> 0xC;
            break;
        }

        var_s5 = *sp38++;
        var_s4 = *sp38++;
        prim->x0 = var_s6 + (((var_s5 * var_s1) - (var_s4 * var_s0)) >> 0xC);
        prim->y0 = var_s7 + (((var_s5 * var_s0) + (var_s4 * var_s1)) >> 0xC);

        var_s5 = *sp38++;
        var_s4 = *sp38++;
        prim->x1 = var_s6 + (((var_s5 * var_s1) - (var_s4 * var_s0)) >> 0xC);
        prim->y1 = var_s7 + (((var_s5 * var_s0) + (var_s4 * var_s1)) >> 0xC);

        var_s5 = *sp38++;
        var_s4 = *sp38++;
        prim->x2 = var_s6 + (((var_s5 * var_s1) - (var_s4 * var_s0)) >> 0xC);
        prim->y2 = var_s7 + (((var_s5 * var_s0) + (var_s4 * var_s1)) >> 0xC);

        var_s5 = *sp38++;
        var_s4 = *sp38++;
        prim->x3 = var_s6 + (((var_s5 * var_s1) - (var_s4 * var_s0)) >> 0xC);
        prim->y3 = var_s7 + (((var_s5 * var_s0) + (var_s4 * var_s1)) >> 0xC);

        prim = prim->next;
    }

    if (arg4) {
        var_s6 = posX - entity->posX.i.hi;
        var_s7 = posY - entity->posY.i.hi;
        if (var_s6 > 0) {
            if (!(g_Player.vram_flag & 4)) {
                player->posX.i.hi += var_s6;
                D_80097488.x.i.hi += var_s6;
            }
        } else if (!(g_Player.vram_flag & 8)) {
            player->posX.i.hi += var_s6;
            D_80097488.x.i.hi += var_s6;
        }
        player->posY.i.hi += var_s7;
        D_80097488.y.i.hi += var_s7;
    }
    entity->posX.i.hi = posX;
    entity->posY.i.hi = posY;
    entity->rotate = var_s2;
}

static u8 D_us_801817D8[] = {0x04, 0x23, 0x84, 0x24, 0xFF, 0x00, 0x00, 0x00};
static u8 D_us_801817E0[] = {0x04, 0x23, 0x04, 0x05, 0xFF, 0x00, 0x00, 0x00};

#ifdef VERSION_PSP
#define COLLISION_WIDTH 0x24
#else
#define COLLISION_WIDTH 0x20
#endif

void func_us_801C789C(Entity* self) {
    s32 primIndex; // sp3C
    s32 sp38;      // sp38
    s32 sp34;      // sp34

    u16 var_s8;      // s8
    u32 scrollY;     // s7
    u16 var_s6;      // s6
    Entity* entity;  // s5
    u32 scrollX;     // s4
    s16 var_s3;      // s3
    s16 var_s2;      // s2
    u8* var_s1;      // s1
    Primitive* prim; // s0

    scrollX = g_Tilemap.scrollX.i.hi;
    scrollY = g_Tilemap.scrollY.i.hi;
    if (self->step && self->ext.et_801C726C.unk90 == 0) {
        self->posY.i.hi += 0x2C;
        if (self->ext.et_801C726C.unk9A) {
            self->ext.et_801C726C.unk9A -= 1;
            var_s6 = 0;
        } else {
            var_s6 = GetPlayerCollisionWith(self, COLLISION_WIDTH, 5, 4);
            // Possible !BUG: duplicate && condition here
            if (!var_s6 && self->ext.et_801C726C.unk98 &&
                self->ext.et_801C726C.unk98) {
                self->ext.et_801C726C.unk9A = 4;
            }
        }
        self->ext.et_801C726C.unk98 = var_s6;
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
            var_s1 = D_us_8018176C;

            while (prim != NULL) {
                prim->clut = 0x5F;
                prim->tpage = 0xF;
                prim->u0 = prim->u2 = *var_s1++;
                prim->u1 = prim->u3 = *var_s1++;
                prim->v0 = prim->v1 = *var_s1++;
                prim->v2 = prim->v3 = *var_s1++;
                prim->priority = *var_s1++;
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
            }
            self->animSet = -0x7FFF;
            self->animCurFrame = 5;
            self->zPriority = 0x9C;
            self->ext.et_801C726C.unk80 = 0;
            self->ext.et_801C726C.unk84 = 0x8000;
            return;
        }
        break;
    case 1:
        entity = self + 2;
        entity->ext.et_801C726C_child.unk7C = 0;
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
        if ((var_s8 && var_s6) || self->ext.et_801C726C.unk7C) {
            self->step++;
            func_us_801C7204(self, 0xFFFC0000);
        }

        var_s3 = 0xF0 - scrollY;
        if (self->params) {
            var_s2 = 0x2CE - scrollX;
        } else {
            var_s2 = 0x422 - scrollX;
        }
        func_us_801C726C(self, 0, var_s2, var_s3, var_s6);
        return;
    case 2:
        entity = self + 2;
        entity->ext.et_801C726C_child.unk7C = 1;
        self->ext.et_801C726C.unk80++;
        if (self->ext.et_801C726C.unk80 > 0xA2) {
            var_s3 = 0x4E;
            if (self->params) {
                var_s2 = (0x2CE - scrollX) - self->ext.et_801C726C.unk80 + 0xA2;
            } else {
                var_s2 = (0x2CE - scrollX) + self->ext.et_801C726C.unk80 + 0xB2;
            }
            if (self->ext.et_801C726C.unk80 == 0x188) {
                if (self->params) {
                    func_us_801C7204(self, 0x80000);
                } else {
                    func_us_801C7204(self, -0x80000);
                }
                self->step++;
                self->ext.et_801C726C.unk82 = 0x80;
            }
        } else {
            var_s3 = 0xF0 - (self->ext.et_801C726C.unk80);
            if (self->params) {
                var_s2 = 0x2CE - scrollX;
                if (self->ext.et_801C726C.unk80 == 0xA2) {
                    func_us_801C7204(self, -0x80000);
                }
            } else {
                var_s2 = 0x422 - scrollX;
                if (self->ext.et_801C726C.unk80 == 0xA2) {
                    func_us_801C7204(self, 0x80000);
                }
            }
        }
        if (var_s3 < 0xDF && self->ext.et_801C726C.unk7C) {
            if (var_s3 == 0xDE) {
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
        var_s3 -= scrollY;
        func_us_801C726C(self, sp34, var_s2, var_s3, var_s6);
        if (!(self->ext.et_801C726C.unk94 % 10)) {
            self->ext.et_801C726C.unk94 = 0;
            PlaySfxPositional(0x6DA);
        }
        self->ext.et_801C726C.unk94++;
        break;
    case 3:
        entity = self + 2;
        entity->ext.et_801C726C_child.unk7C = 0;
        if (!--self->ext.et_801C726C.unk82) {
            self->step++;
            PlaySfxPositional(0x675);
        }

        var_s3 = 0x4E - scrollY;
        if (self->params) {
            var_s2 = 0x1E8 - scrollX;
        } else {
            var_s2 = 0x508 - scrollX;
        }
        func_us_801C726C(self, 1, var_s2, var_s3, var_s6);
        break;
    case 4:
        self->zPriority = 0x82;
        self->ext.et_801C726C.unk90 = 1;
        self->ext.et_801C726C.unk7C = 0;
        if (!AnimateEntity(D_us_801817D8, self)) {
            self->pose = 0;
            self->poseTimer = 0;
            self->step++;
        }

        var_s3 = 0x4E - scrollY;
        if (self->params) {
            var_s2 = 0x1E8 - scrollX;
        } else {
            var_s2 = 0x508 - scrollX;
        }
        func_us_801C726C(self, 0, var_s2, var_s3, var_s6);
        break;
    case 5:
        if (!AnimateEntity(D_us_801817E0, self)) {
            if (self->params) {
                func_us_801C7204(self, -0x50000);
            } else {
                func_us_801C7204(self, 0x50000);
            }
            self->step++;
            self->ext.et_801C726C.unk82 = 0x40;
        }
        if (self->pose == 2) {
            self->ext.et_801C726C.unk90 = 0;
            self->zPriority = 0x9C;
        }

        var_s3 = 0x4E - scrollY;
        if (self->params) {
            var_s2 = 0x1E8 - scrollX;
        } else {
            var_s2 = 0x508 - scrollX;
        }
        func_us_801C726C(self, 0, var_s2, var_s3, var_s6);
        break;
    case 6:
        if (!--self->ext.et_801C726C.unk82) {
            if (self->params) {
                func_us_801C7204(self, 0x80000);
            } else {
                func_us_801C7204(self, -0x80000);
            }
            self->step++;
        }

        var_s3 = 0x4E - scrollY;
        if (self->params) {
            var_s2 = 0x1E8 - scrollX;
        } else {
            var_s2 = 0x508 - scrollX;
        }
        func_us_801C726C(self, 0, var_s2, var_s3, var_s6);
        break;
    case 7:
        entity = self + 2;
        entity->ext.et_801C726C_child.unk7C = -1;
        if (!--self->ext.et_801C726C.unk80) {
            SetStep(1);
        }

        if (self->ext.et_801C726C.unk80 > 0xA2) {
            var_s3 = 0x4E;
            if (self->params) {
                var_s2 = (0x2CE - scrollX) - self->ext.et_801C726C.unk80 + 0xA2;
                if (self->ext.et_801C726C.unk80 == 0xA3) {
                    func_us_801C7204(self, -0x80000);
                }
            } else {
                var_s2 = (0x2CE - scrollX) + self->ext.et_801C726C.unk80 + 0xB2;
                if (self->ext.et_801C726C.unk80 == 0xA3) {
                    func_us_801C7204(self, 0x80000);
                }
            }
        } else {
            var_s3 = 0xF0 - (self->ext.et_801C726C.unk80);
            if (self->params) {
                var_s2 = 0x2CE - scrollX;
            } else {
                var_s2 = 0x422 - scrollX;
            }
        }
        var_s3 -= scrollY;
        func_us_801C726C(self, 0, var_s2, var_s3, var_s6);

        if (!(self->ext.et_801C726C.unk94 % 10)) {
            self->ext.et_801C726C.unk94 = 0;
            PlaySfxPositional(0x6DA);
        }
        self->ext.et_801C726C.unk94++;
        break;
    }
}

void func_us_801C7FA4(Entity* self) {}

extern u16 D_us_801817E8;

void func_us_801C7FAC(void) {
    s32 i;
    Tilemap* tileMap = &g_Tilemap;
    s16 offset = 0x595;
    u16* var_a2 = &D_us_801817E8;

    for (i = 0; i < 7; i++) {
        *(tileMap->fg + offset) = *var_a2++;
        offset++;
        *(tileMap->fg + offset) = *var_a2++;
        offset = offset + 0xCF;
    }
}

void func_us_801C801C(Entity* self) {
    Entity* newEnt;
    s16 offsetY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        if (g_CastleFlags[BOATMAN_GATE_OPEN]) {
            func_us_801C7FAC();
            DestroyEntity(self);
            return;
        }
        self->animCurFrame = 24;
        return;
    case 1:
        if (g_CastleFlags[BOATMAN_GATE_OPEN]) {
            GetPlayerCollisionWith(self, 16, 56, 3);
            func_us_801C7FAC();
            self->ext.et_surfacingWater.unk80 = 0;
            self->step++;
            return;
        }
        break;
    case 2:
        if (!(self->ext.et_surfacingWater.unk80++ & 15)) {
            PlaySfxPositional(SFX_STONE_MOVE_C);
        }

        self->posY.i.hi--;
        offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;

        if (offsetY >= 125) {
            if (self->ext.et_surfacingWater.unk7C) {
                self->ext.et_surfacingWater.unk7C--;
            } else {
                newEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEnt != NULL) {
                    CreateEntityFromCurrentEntity(E_SURFACING_WATER, newEnt);
                    newEnt->posY.i.hi = 176 - g_Tilemap.scrollY.i.hi;
                    newEnt->posX.i.hi = (s16)(newEnt->posX.i.hi - 16) +
                                        (self->ext.et_surfacingWater.unk7E * 8);
                    newEnt->params = 0x8000;
                    newEnt->ext.et_surfacingWater.origPosX = 23;
                    newEnt->zPriority = 155;
                }

                self->ext.et_surfacingWater.unk7E++;
                if (self->ext.et_surfacingWater.unk7E >= 5) {
                    self->ext.et_surfacingWater.unk7E = 0;
                }
                self->ext.et_surfacingWater.unk7C = 1;
            }
        }

        GetPlayerCollisionWith(self, 16, 60, 3);

        if (offsetY < 36) {
            DestroyEntity(self);
        }
    }
}

void func_us_801C8248(Entity* self) {
    s32 posX;
    s32 posY;

    if (g_api.TimeAttackController(
            TIMEATTACK_EVENT_SUCCUBUS_DEFEAT, TIMEATTACK_GET_RECORD)) {
        posX = self->posX.val;
        posY = self->posY.val;
        CreateEntityFromCurrentEntity(E_HEART_DROP, self);
        self->params = 10;
        self->posX.val = posX;
        self->posY.val = posY;
    }
}
