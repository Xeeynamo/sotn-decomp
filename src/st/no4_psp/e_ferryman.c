// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no4/no4.h"

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

INCLUDE_ASM("st/no4_psp/nonmatchings/no4_psp/e_ferryman", func_pspeu_0923B378);

INCLUDE_ASM("st/no4_psp/nonmatchings/no4_psp/e_ferryman", func_pspeu_0923BAB0);

INCLUDE_ASM("st/no4_psp/nonmatchings/no4_psp/e_ferryman", func_pspeu_0923BB30);

INCLUDE_ASM("st/no4_psp/nonmatchings/no4_psp/e_ferryman", func_pspeu_0923C460);

INCLUDE_ASM("st/no4_psp/nonmatchings/no4_psp/e_ferryman", func_pspeu_0923D0B8);

INCLUDE_ASM("st/no4_psp/nonmatchings/no4_psp/e_ferryman", func_pspeu_0923D0C8);

INCLUDE_ASM("st/no4_psp/nonmatchings/no4_psp/e_ferryman", func_pspeu_0923D180);

INCLUDE_ASM("st/no4_psp/nonmatchings/no4_psp/e_ferryman", func_pspeu_0923D428);

INCLUDE_ASM("st/no4_psp/nonmatchings/no4_psp/e_ferryman", func_pspeu_0923D4A0);
