// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo0.h"

static s16 func_us_801AD26C(s16 maxRotation, s16 angle1, s16 angle2) {
    s16 diff;

    angle1 &= 0xFFF;
    angle2 &= 0xFFF;
    diff = angle2 - angle1;
    if (diff > ROT(180)) {
        diff = diff - ROT(360);
    }
    if (diff < ROT(-180)) {
        diff = diff + ROT(360);
    }
    if (diff < -maxRotation) {
        diff = -maxRotation;
    }
    if (diff > maxRotation) {
        diff = maxRotation;
    }
    angle2 = angle1 + diff;
    angle2 &= 0xFFF;
    return angle2;
}

static bool func_us_801AD2F0(s16 x, s16 y) {
    Collider collider;
    g_api.CheckCollision(x, y, &collider, 0);
    if (collider.effects & EFFECT_SOLID) {
        return true;
    } else {
        return false;
    }
}

extern EInit g_EInitOlroxAfterImage;

static s32 D_us_80180BA8 = 0;
static u8 D_us_80180BAC[] = {
    8, 9, 8, 8, 10, 8, 11, 8, 10, 9, 10, 11, 10, 10, 10, 11,
};
static s16 D_us_80180BBC[] = {
    0, 31, 0, 4, 8, -4, -16,
};
static s16 D_us_80180BCC[] = {
    0,
    31,
    8,
    0,
};
static s16 D_us_80180BD4[] = {
    -32, 128, -32, 64,  -32, 0,   64, -32,    128,
    -32, 192, -32, 288, 0,   288, 64, 0x0120, 128,
};
static s16 D_us_80180BF8[] = {
    0,
    16,
    32,
    48,
};
static u8 anim_0[] = {
    0x08, 0x0E, 0x08, 0x0F, 0x48, 0x10, 0x08, 0x0F, 0x10, 0x0E, 0xFF,
};
static u8 anim_1[] = {
    0x10, 0x0E, 0x08, 0x11, 0x08, 0x12, 0x0C, 0x13, 0x10, 0x14, 0x08,
    0x15, 0x08, 0x16, 0x14, 0x17, 0x14, 0x18, 0x08, 0x19, 0xFF,
};
static u8 anim_2[] = {
    0x08, 0x19, 0x06, 0x1A, 0x18, 0x1B, 0x0C, 0x1C, 0x01, 0x1D,
    0x06, 0x1E, 0x06, 0x1F, 0x10, 0x20, 0x06, 0x21, 0x10, 0x1B,
    0x06, 0x1A, 0x04, 0x19, 0xFF, 0x00, 0x00, 0x00,
};

static u8 anim_3[] = {
    0x04, 0x19, 0x08, 0x21, 0x06, 0x30, 0x06, 0x31, 0x04, 0x32, 0xFF, 0x00,
};

static u8 anim_4[] = {
    0x04, 0x32, 0x06, 0x31, 0x06, 0x30, 0x08, 0x21, 0x04, 0x19, 0xFF, 0x00,
};

static u8 anim_5[] = {
    0x04, 0x19, 0x04, 0x22, 0x04, 0x23, 0x04, 0x24, 0x04, 0x27,
    0x04, 0x28, 0x04, 0x2A, 0x04, 0x2B, 0x04, 0x2C, 0xFF, 0x00,
};

static u8 anim_6[] = {
    0x08, 0x19, 0x08, 0x22, 0x10, 0x23, 0x06, 0x24, 0x08, 0x25,
    0x18, 0x26, 0x06, 0x27, 0x06, 0x22, 0x06, 0x19, 0xFF, 0x00,
};

static u8 anim_7[] = {
    0x08, 0x19, 0x08, 0x22, 0x18, 0x27, 0x01, 0x28, 0x01, 0x27, 0x01,
    0x28, 0x01, 0x27, 0x01, 0x28, 0x01, 0x27, 0x01, 0x28, 0x0C, 0x27,
    0x08, 0x29, 0x01, 0x27, 0x01, 0x2A, 0x01, 0x2B, 0x08, 0x2C, 0x28,
    0x2B, 0x08, 0x2A, 0x08, 0x27, 0x08, 0x22, 0x04, 0x19, 0xFF, 0x00,
};

static u8 anim_8[] = {
    0x06, 0x19, 0x01, 0x27, 0x01, 0x2A, 0x01, 0x60,
    0x01, 0x61, 0x08, 0x60, 0xFF, 0x00, 0x00, 0x00,
};

static u8 anim_9[] = {
    0x06, 0x2A, 0x06, 0x27, 0x10, 0x19, 0xFF, 0x00,
};

static u8 anim_10[] = {
    0x10, 0x19, 0x04, 0x36, 0x01, 0x37, 0x02, 0x38, 0xFF, 0x00, 0x00, 0x00,
};

static u8 anim_11[] = {
    0x04, 0x39, 0x02, 0x38, 0x01, 0x37, 0x04, 0x36, 0x10, 0x19, 0xFF, 0x00,
};

static u8 anim_12[] = {
    0x02, 0x19, 0x06, 0x21, 0x04, 0x30, 0x08, 0x31,
    0x02, 0x30, 0x02, 0x2F, 0x02, 0x2E, 0xFF, 0x00,
};

static u8 anim_13[] = {
    0x02, 0x2D, 0x04, 0x2E, 0x08, 0x2F, 0x08, 0x30, 0x10, 0x31,
    0x03, 0x30, 0x04, 0x21, 0x04, 0x19, 0xFF, 0x00, 0x00, 0x00,
};

static u8 anim_14[] = {
    0x02, 0x19, 0x0A, 0x21, 0x0A, 0x30, 0x10, 0x31,
    0x03, 0x30, 0x06, 0x21, 0xFF, 0x00, 0x00, 0x00,
};

static u8 anim_15[] = {
    0x04, 0x21, 0x03, 0x30, 0x10, 0x31, 0x0A, 0x30,
    0x0A, 0x21, 0x04, 0x19, 0xFF, 0x00, 0x00, 0x00,
};

static u8 anim_16[] = {
    0x01, 0x19, 0x08, 0x33, 0x0C, 0x34, 0x08, 0x35, 0x02, 0x19, 0xFF, 0x00,
};

static u8 anim_17[] = {
    0x04, 0x19, 0x0A, 0x21, 0x08, 0x30, 0x08, 0x31, 0x20, 0x32, 0xFF, 0x00,
};

static u8 anim_18[] = {
    0x04, 0x3A, 0x04, 0x3B, 0x04, 0x3C, 0x04, 0x3D,
    0x04, 0x3E, 0x04, 0x3C, 0x00, 0x00, 0x00, 0x00,
};

static u8 anim_19[] = {
    0x06, 0x3F, 0x06, 0x40, 0x06, 0x41, 0xFF, 0x00,
};

static u8 anim_20[] = {
    0x06, 0x42, 0x06, 0x43, 0x06, 0x44, 0x06, 0x45, 0x06, 0x46, 0x06, 0x47,
    0x06, 0x48, 0x06, 0x49, 0x06, 0x4A, 0x06, 0x4B, 0x00, 0x00, 0x00, 0x00,
};

static u8 anim_21[] = {
    0x0A, 0x4C, 0x0A, 0x4D, 0x0A, 0x4E, 0x0A, 0x4F, 0x00, 0x00, 0x00, 0x00,
};

static u8 anim_22[] = {
    0x16, 0x50, 0x36, 0x51, 0x00, 0x00, 0x00, 0x00,
};

static u8 anim_23[] = {
    0x03, 0x54, 0x03, 0x55, 0x03, 0x56, 0x03, 0x57, 0x03, 0x58, 0x03, 0x59,
    0x03, 0x5A, 0x03, 0x5B, 0x03, 0x5C, 0x03, 0x5D, 0x03, 0x5E, 0x00, 0x00,
};

typedef struct Unk8 {
    s16 a, b, c, d;
} Unk8;
#ifdef VERSION_PSP
static Unk8 D_us_801A9344 =
#else
static const Unk8 D_us_801A9344 =
#endif
    {0, 256, 128, 256};

void func_us_801AD338(Entity* self) {
    Entity* entity;
    s32 i;
    s16 posX;
    s16 temp_v0_5;
    s16* var_s4_3;
    s16 posY;
    Entity* player;
    u8 var_s4;
    s16 roomPosX;

    GpuBuffer* currentBuffer;
    DR_ENV* env;
    DRAWENV unused;
    Unk8 unk8;

    env = &g_CurrentBuffer->env[g_GpuUsage.env];
    unk8 = D_us_801A9344;

    g_api.func_8010DFF0(1, 2);
    if (self->flags & FLAG_DEAD && self->step < 14) {
        self->hitboxState = 0;
        SetStep(14);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitOlroxAfterImage);
        self->animCurFrame = 14;
        self->hitboxState = 0;
        break;
    case 1:
        if (GetDistanceToPlayerX() < 0x60 &&
            g_Player.vram_flag == TOUCHING_GROUND) {
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_OLROX_DEFEAT, TIMEATTACK_SET_VISITED);
            SetStep(2);
            self->ext.olrox.timer = 192;
        }
        entity = self - 1;
        if (entity->flags & FLAG_DEAD) {
            stopMusicFlag = 0;
            currentMusicId = MU_DEATH_BALLAD;
            g_api.PlaySfx(currentMusicId);
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_OLROX_DEFEAT, TIMEATTACK_SET_VISITED);
            SetStep(13);
            self->hitboxState = 3;
        }
        break;
    case 2:
        entity = self - 1;
        if (entity->flags & FLAG_DEAD) {
            stopMusicFlag = 0;
            currentMusicId = MU_DEATH_BALLAD;
            g_api.PlaySfx(currentMusicId);
            SetStep(13);
            self->hitboxState = 3;
        } else {
            switch (self->step_s) {
            case 0:
                if (!AnimateEntity(anim_0, self)) {
                    SetSubStep(1);
                }
                break;
            case 1:
                if (!AnimateEntity(anim_1, self)) {
                    stopMusicFlag = 0;
                    currentMusicId = MU_DEATH_BALLAD;
                    g_api.PlaySfx(currentMusicId);
                    self->hitboxState = 3;
                    SetStep(3);
                }
                break;
            }
        }
        break;
    case 3:
        player = &PLAYER;
        posX = player->posX.i.hi - self->posX.i.hi;
        posY = player->posY.i.hi - self->posY.i.hi;
        roomPosX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (roomPosX < 80 && (u16)posX < 64) {
            SetStep(13);
        } else if (roomPosX > 432 && (u16)posX > (u16)-65) {
            SetStep(13);
        } else if (abs(posX) < 36) {
            self->facingLeft = GetSideToPlayer() & 1;
            SetStep(5);
        } else if (roomPosX < 128 && (u16)posX < (u16)112) {
            SetStep(4);
        } else if (roomPosX > 384 && (u16)posX > (u16)-113) {
            SetStep(4);
        } else if (abs(posX) < 64) {
            self->facingLeft = GetSideToPlayer() & 1;
            SetStep(6);
            self->step_s = 1;
        } else if (abs(posX) > 176) {
            self->facingLeft = GetSideToPlayer() & 1;
            SetStep(6);
        } else {
            self->facingLeft = GetSideToPlayer() & 1;
            if (self->hitPoints <
                (g_api.enemyDefs[ENEMY_OLROX].hitPoints * 3 / 4)) {
                self->ext.olrox.unk88 |= 8;
            }
            SetStep(D_us_80180BAC[self->ext.olrox.unk88]);
            self->ext.olrox.unk88++;
            self->ext.olrox.unk88 &= 7;
        }
        break;
    case 13:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_10, self)) {
                SetSubStep(1);
                self->drawFlags |= ENTITY_SCALEY;
                self->scaleY = 0x100;
                PlaySfxPositional(SFX_BOSS_CLONE_DISAPPEAR);
            }
            if (self->pose > 1) {
                self->hitboxState = 0;
            }
            break;
        case 1:
            self->scaleY -= 32;
            if (!self->scaleY) {
                self->drawFlags = ENTITY_DEFAULT;
                self->animCurFrame = 0;
                SetSubStep(2);
            }
            break;
        case 2:
            roomPosX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            player = &PLAYER;
            if (roomPosX < 256) {
                self->posX.i.hi = player->posX.i.hi + 32 + (Random() & 0x3F);
            } else {
                self->posX.i.hi = player->posX.i.hi - 32 - (Random() & 0x3F);
            }
            roomPosX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (roomPosX < 48) {
                self->posX.i.hi = 0x30;
            }
            if (roomPosX > 0x1D0) {
                self->posX.i.hi = 0xD0;
            }
            self->facingLeft = GetSideToPlayer() & 1;
            SetSubStep(3);
            break;
        case 3:
            if (!AnimateEntity(anim_11, self)) {
                SetStep(3);
            }
            if (self->pose > 4) {
                self->hitboxState = 3;
            }
            break;
        }
        break;
    case 12:
        if (!self->step_s) {
            self->velocityX = FIX(-0.5);
            if (self->facingLeft) {
                // BUG: when facing left velocity doesn't change
                self->velocityX = self->velocityX;
            }
        }
        UnkCollisionFunc2(D_us_80180BCC);
        if (!AnimateEntity(anim_16, self)) {
            SetStep(3);
        }
        break;
    case 11:
        switch (self->step_s) {
        case 0:
            entity = self + 11;
            if (entity->entityId) {
                SetStep(3);
            } else {
                temp_v0_5 = 32;
                roomPosX = temp_v0_5 + g_Tilemap.scrollX.i.hi;
                if (roomPosX < 80) {
                    temp_v0_5 = 80;
                }

                if (roomPosX > 272) {
                    temp_v0_5 = 272 - g_Tilemap.scrollX.i.hi;
                }
                var_s4 = Random() & 3;
                for (i = 0; i < 3; i++, entity++) {
                    CreateEntityFromCurrentEntity(E_ID(GROUND_BLAST), entity);
                    entity->posX.i.hi = temp_v0_5 + (i * 0x50);
                    entity->posY.i.hi = self->posY.i.hi + 30;
                    entity->ext.olroxGroundBlast.parent = self;
                    entity->params = var_s4;
                    var_s4++;
                    var_s4 &= 3;
                }
                self->ext.olrox.unk86 = false;
                self->step_s++;
                g_api.PlaySfx(SFX_FM_THUNDER_EXPLODE);
            }
            break;
        case 1:
            if (!AnimateEntity(anim_7, self)) {
                SetStep(3);
            }
            if (self->pose == 16 && !self->poseTimer) {
                self->ext.olrox.unk86 = true;
            }
            break;
        }
        break;
    case 10:
        if (!self->step_s) {
            if (self->posX.i.hi & 0x100) {
                SetStep(3);
                break;
            }
            self->step_s++;
        }
        if (!AnimateEntity(anim_2, self)) {
            SetStep(3);
        }
        if (self->pose == 4 && !self->poseTimer) {
            PlaySfxPositional(SFX_SCIFI_BLAST);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(BLAST_ATTACK), self, entity);
                entity->facingLeft = self->facingLeft;
            }
        }
        break;

    // creating the interdimensional portal
    case 9:
        switch (self->step_s) {
        case 0:
            var_s4 = 0;
            entity = &g_Entities[160];
            for (i = 0; i < 8; i++, entity++) {
                if (entity->entityId) {
                    var_s4++;
                }
            }
            if (var_s4 > 4) {
                SetStep(3);
            } else {
                if (!AnimateEntity(anim_8, self)) {
                    SetSubStep(1);
                }
            }
            break;
        case 1:
            entity = self + 10;
            CreateEntityFromEntity(E_ID(PORTAL), self, entity);
            entity->posY.i.hi -= 0x46;
            entity->ext.olroxPortal.parent = self;
            self->ext.olrox.unk85 = false;
            self->ext.olrox.timer = 0x60;
            self->step_s++;
            PlaySfxPositional(SFX_TELEPORT_BANG_B);
            break;
        case 2:
            if (!--self->ext.olrox.timer) {
                self->ext.olrox.unk85 = true;
                self->step_s++;
            }
            break;
        case 3:
            if (!AnimateEntity(anim_9, self)) {
                SetStep(3);
            }
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_5, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            entity = self + 1;
            var_s4_3 = D_us_80180BD4;
            for (i = 0; i < 9; i++, entity++) {
                if (!entity->entityId) {
                    CreateEntityFromCurrentEntity(E_ID(UNK_2D), entity);
                    entity->posX.i.hi = *var_s4_3++;
                    entity->posY.i.hi = *var_s4_3++;
                    entity->ext.olroxAfterImage.parent = self;
                    entity->params = i;
                }
            }
            self->ext.olrox.unk84 = false;
            self->step_s++;
            PlaySfxPositional(SFX_OLROX_BAT_ATTACK);
            break;
        case 2:
            entity = self + 1;
            var_s4 = true;
            for (i = 0; i < 9; i++, entity++) {
                if (entity->entityId && !entity->hitboxState) {
                    var_s4 = false;
                }
            }

            if (var_s4) {
                self->step_s++;
            }
            break;
        case 3:
            if (!AnimateEntity(anim_6, self)) {
                self->step_s++;
            }
            if (self->pose == 5) {
                if (!self->poseTimer) {
                    PlaySfxPositional(SFX_OLROX_ATTACK);
                }
                self->ext.olrox.unk84 = true;
            }
            break;
        case 4:
            SetStep(3);
            break;
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_3, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            self->step_s++;
            break;
        case 2:
            if (!AnimateEntity(anim_4, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            self->velocityX = FIX(2.25);
            if (self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            self->animCurFrame = 0x19;
            self->ext.olrox.timer = 8;
            self->step_s = 2;
            break;
        case 1:
            self->velocityX = FIX(-2.25);
            if (self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            self->animCurFrame = 45;
            self->ext.olrox.timer = 8;
            self->step_s = 2;
            break;
        case 2:
            UnkCollisionFunc2(D_us_80180BCC);
            if (!--self->ext.olrox.timer) {
                self->ext.olrox.timer = 8;
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(OLROX_AFTER_IMAGE), self, entity);
                    entity->params = self->animCurFrame;
                    entity->facingLeft = self->facingLeft;
                }
            }
            if (self->animCurFrame == 45) {
                if (self->velocityX == FIX(0) || GetDistanceToPlayerX() > 96) {
                    self->facingLeft = GetSideToPlayer() & 1;
                    SetStep(3);
                }
            }
            if (self->animCurFrame == 25) {
                if (self->velocityX == 0 || GetDistanceToPlayerX() < 112) {
                    self->facingLeft = GetSideToPlayer() & 1;
                    SetStep(3);
                }
            }
            break;
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            roomPosX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if (roomPosX < 0x60 && self->facingLeft) {
                SetStep(3);
            } else if (roomPosX > 0x1B0 && !self->facingLeft) {
                SetStep(3);
            } else {
                if (!AnimateEntity(anim_14, self)) {
                    self->velocityX = 0;
                    self->velocityY = FIX(-4.5);
                    self->animCurFrame = 0x19;

                    player = &PLAYER;
                    if (self->posX.i.hi > player->posX.i.hi) {
                        self->ext.olrox.unk87 = true;
                    } else {
                        self->ext.olrox.unk87 = false;
                    }
                    SetSubStep(1);
                }
            }
            break;
        case 1:
            MoveEntity();
            if (self->velocityY > FIX(-1.5)) {
                self->velocityY += FIX(0.0625);
            } else {
                self->velocityY += FIX(0.125);
            }
            if (self->velocityY >= 0) {
                player = &PLAYER;
                if (self->ext.olrox.unk87) {
                    self->velocityX = FIX(-3);
                } else {
                    self->velocityX = FIX(3);
                }
                if (self->facingLeft == self->ext.olrox.unk87) {
                    self->animCurFrame = 0x19;
                } else {
                    self->animCurFrame = 0x2D;
                }
                self->ext.olrox.timer = 0x18;
                self->step_s++;
            }
            break;
        case 2:
            if (!--self->ext.olrox.timer) {
                self->ext.olrox.timer = 8;
                self->step_s++;
            }
            break;
        case 3:
            if (!--self->ext.olrox.timer) {
                self->ext.olrox.timer = 8;
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(OLROX_AFTER_IMAGE), self, entity);
                    entity->params = (u16)self->animCurFrame;
                    entity->facingLeft = self->facingLeft;
                }
            }
            MoveEntity();
            self->facingLeft = GetSideToPlayer() & 1;
            if (self->ext.olrox.unk87 == self->facingLeft) {
                self->animCurFrame = 0x19;
            } else {
                self->animCurFrame = 0x2D;
            }

            roomPosX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if (roomPosX < 0x38) {
                if (self->velocityX < 0) {
                    self->step_s++;
                }
            }
            if (roomPosX > 0x1C8 && self->velocityX > FIX(0)) {
                self->step_s++;
            }
            if (GetDistanceToPlayerX() > 0x50) {
                if (self->ext.olrox.unk87 != (GetSideToPlayer() & 1)) {
                    self->step_s++;
                }
            }
            break;
        case 4:
            roomPosX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if (roomPosX < 0x38) {
                self->velocityX = 0;
                self->posX.i.hi = 0x38 - g_Tilemap.scrollX.i.hi;
            }
            if (roomPosX > 0x1C8) {
                self->velocityX = 0;
                self->posX.i.hi = 0x1C8 - g_Tilemap.scrollX.i.hi;
            }
            self->velocityY -= FIX(0.125);
            if (UnkCollisionFunc3(D_us_80180BBC) & 1) {
                self->step_s++;
                PlaySfxPositional(SFX_STOMP_HARD_B);
            }
            break;
        case 5:
            if (!AnimateEntity(anim_15, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(anim_12, self)) {
                self->velocityX = FIX(-4);
                if (self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
                self->velocityY = FIX(-3);
                self->animCurFrame = 0x2D;
                self->ext.olrox.timer = 8;
                SetSubStep(1);
            }
            break;
        case 1:
            if (!--self->ext.olrox.timer) {
                self->ext.olrox.timer = 8;
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(OLROX_AFTER_IMAGE), self, entity);
                    entity->params = (u16)self->animCurFrame;
                    entity->facingLeft = self->facingLeft;
                }
            }
            roomPosX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if (roomPosX < 0x38) {
                self->posX.i.hi = 0x38 - g_Tilemap.scrollX.i.hi;
            }
            if (roomPosX > 0x1C8) {
                self->posX.i.hi = 0x1C8 - g_Tilemap.scrollX.i.hi;
            }
            if (UnkCollisionFunc3(D_us_80180BBC) & 1) {
                self->step_s++;
                PlaySfxPositional(SFX_STOMP_HARD_B);
            }
            break;
        case 2:
            if (!AnimateEntity(anim_13, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 14:
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            if (UnkCollisionFunc3(D_us_80180BBC) & 1) {
                self->step_s++;
            }
            break;
        case 1:
            entity = self - 16;
            for (i = 0; i < 16; i++, entity++) {
                entity->flags |= FLAG_DEAD;
            }
            SetSubStep(4);
            roomPosX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if (roomPosX < 0x60 || roomPosX > 0x1a0) {
                self->drawFlags |= ENTITY_SCALEY;
                self->scaleY = 0x100;
                SetSubStep(2);
            }
            break;
        case 2:
            if (!AnimateEntity(anim_10, self)) {
                self->scaleY -= 32;
                if (!self->scaleY) {
                    self->drawFlags = ENTITY_DEFAULT;
                    self->animCurFrame = 0;
                    roomPosX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
                    if (roomPosX < 0x60) {
                        self->posX.i.hi += 0x60;
                    } else {
                        self->posX.i.hi -= 0x60;
                    }
                    SetSubStep(3);
                }
            }
            break;
        case 3:
            if (!AnimateEntity(anim_11, self)) {
                SetSubStep(4);
            }
            break;
        case 4:
            D_us_80180BA8 |= 1;
            if (!AnimateEntity(anim_17, self)) {
                self->step_s++;
            }
            break;
        case 5:
            entity = self + 1;
            DestroyEntity(entity);
            CreateEntityFromEntity(E_ID(UNK_32), self, entity);
            entity->posY.i.hi = 0x1D0 - g_Tilemap.scrollY.i.hi;
            entity->facingLeft = self->facingLeft ^ 1;
            self->ext.olrox.timer = 3;
            self->step_s++;
            self->ext.olrox.timer = 0xA0;
            break;
        case 6:
            if (!--self->ext.olrox.timer) {
                self->animCurFrame = 0;
                self->step = 0x40;
            }
            break;
        }
        break;

    case 0x20:
#include "../../st/pad2_anim_debug.h"
        break;
    }
    self->hitboxOffX = 1;
    self->hitboxOffY = 1;
    self->hitboxWidth = 5;
    self->hitboxHeight = 0x1C;
    if (self->animCurFrame == 45 || self->animCurFrame == 46) {
        self->hitboxOffX = 0;
        self->hitboxOffY = 1;
        self->hitboxWidth = 4;
        self->hitboxHeight = 0x12;
    }
    if (self->animCurFrame >= 48 && self->animCurFrame <= 50) {
        self->hitboxOffX = 0;
        self->hitboxOffY = 0xA;
        self->hitboxWidth = 4;
        self->hitboxHeight = 0xD;
    }
}

extern EInit g_EInitGroundBlast;

void EntityGroundBlast(Entity* self) {
    s32 i;
    s32 j;
    s16 u;
    s16 posX;
    s16 posY;
    s16 unk8A;
    u16 tpage;
    Primitive* prim;
    s32 primIndex;
    Primitive* prim2;
    s16* var_fp;
    Entity* olrox;
    DRAWENV* drawPtr;
    s16 var_s6;
    s16 var_s5;
    s16 var_s7;
    s16 var_s8;
    DRAWENV draw;

    olrox = self->ext.olroxGroundBlast.parent;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGroundBlast);
        self->hitboxHeight = 0;
        self->hitboxWidth = 16;
        self->drawFlags |= ENTITY_SCALEX;
        self->drawFlags |= ENTITY_SCALEY;
        self->scaleY = 0;
        self->scaleX = 256;
        self->zPriority = self->zPriority + 12;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x18);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.olroxGroundBlast.prim7C = prim;
            for (i = 0; i < 2; i++) {
                prim->tpage = 0x13;
                prim->clut = 0x214;
                prim->u0 = prim->u2 = i * 24;
                prim->u1 = prim->u3 = prim->u0 + 23;
                prim->v0 = prim->v1 = 0x40;
                prim->v2 = prim->v3 = prim->v0 + 0x1E;
                prim->priority = self->zPriority + 0xA;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
            }

            posY += 32;

            for (i = 0; i < 8; i++) {
                prim->tpage = 0x12;
                prim->clut = 0x214;
                prim->u0 = prim->u2 = (i % 2) * 24 + 208;
                prim->u1 = prim->u3 = prim->u0 + 23;
                prim->v0 = prim->v1 = (i / 2) * 31 + 128;
                if (i < 2) {
                    prim->v0 += 1;
                    prim->v1 += 1;
                }

                prim->v2 = prim->v3 = prim->v0 + 31;
                prim->priority = self->zPriority + 0xA;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
            }

            posY += 128;

            for (i = 0; i < 2; i++) {
                prim->tpage = 0x13;
                prim->clut = 0x214;
                prim->u0 = prim->u2 = i * 24;
                prim->u1 = prim->u3 = prim->u0 + 23;
                prim->v0 = prim->v1 = 0x5E;
                prim->v2 = prim->v3 = prim->v0 - 0x1E;
                prim->priority = self->zPriority + 0xA;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
                prim = prim->next;
            }
            prim = self->ext.olroxGroundBlast.prim7C;
            for (i = 0; i < 6; i++) {
                prim = prim->next;
                u = prim->u0;
                prim->u0 = prim->u1;
                prim->u1 = u;
                u = prim->u2;
                prim->u2 = prim->u3;
                prim->u3 = u;
                prim = prim->next;
            }
            self->ext.olroxGroundBlast.prim = prim;
            while (prim != NULL) {
                prim->priority = self->zPriority + 8;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        self->ext.olroxGroundBlast.timer = D_us_80180BF8[self->params];
        self->ext.olroxGroundBlast.timer2 = 24;
        self->ext.olroxGroundBlast.height = 0;
        break;

    case 1:
        if (!AnimateEntity(anim_19, self)) {
            SetStep(2);
            self->pose = Random() & 7;
        }

        if (self->scaleY < 256) {
            self->scaleY += 16;
        }
        break;

    case 2:
        AnimateEntity(anim_20, self);
        if (olrox->ext.olrox.unk86) {
            if (self->ext.olroxGroundBlast.timer) {
                self->ext.olroxGroundBlast.timer--;
                return;
            }
            self->step++;
        }

        if (self->scaleY < 0x100) {
            self->scaleY += 16;
        }
        if (D_us_80180BA8) {
            DestroyEntity(self);
            return;
        }
        break;

    case 3:
        draw = g_CurrentBuffer->draw;

#ifndef VERSION_PSP
        tpage = 0x100;
        if (draw.ofs[0]) {
#endif
            tpage = 0x104;
#ifndef VERSION_PSP
        }
#endif

        prim = self->ext.olroxGroundBlast.prim;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        if (posY > 240) {
            posY = 240;
        }

        if (self->ext.olroxGroundBlast.timer2) {
            self->ext.olroxGroundBlast.timer2--;
            self->ext.olroxGroundBlast.height += 2;
        }
        prim->tpage = tpage;
        prim->u0 = prim->u2 = posX - 24;
        prim->u1 = prim->u3 = posX;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = posY;
        prim->x0 = prim->x2 = posX - self->ext.olroxGroundBlast.timer2;
        prim->x1 = prim->x3 = posX;
        prim->y0 = prim->y1 = -self->ext.olroxGroundBlast.height;
        prim->y2 = prim->y3 = posY;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;

        prim->tpage = tpage;
        prim->u0 = prim->u2 = posX;
        prim->u1 = prim->u3 = posX + 0x18;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = posY;
        prim->x0 = prim->x2 = posX;
        prim->x1 = prim->x3 = posX + self->ext.olroxGroundBlast.timer2;
        prim->y0 = prim->y1 = -self->ext.olroxGroundBlast.height;
        prim->y2 = prim->y3 = posY;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;

        if (!self->ext.olroxGroundBlast.timer2) {
            g_api.PlaySfx(SFX_BO0_UNK_7CA);
            self->ext.olroxGroundBlast.unk94 = 0;
            self->ext.olroxGroundBlast.unk96 = -0x20;
            self->ext.olroxGroundBlast.unk98 = -0x40;
            self->ext.olroxGroundBlast.unk9A = -0x60;
            self->ext.olroxGroundBlast.unk9C = -0x80;
            self->ext.olroxGroundBlast.unk9E = -0xA0;
            self->ext.olroxGroundBlast.unkA0 = -0xC0;
            self->step++;
        }
        break;
    case 4:
        AnimateEntity(anim_20, self);
        self->ext.olroxGroundBlast.unk94 += 8;
        self->ext.olroxGroundBlast.unk96 += 7;
        self->ext.olroxGroundBlast.unk98 += 6;
        self->ext.olroxGroundBlast.unk9A += 5;
        self->ext.olroxGroundBlast.unk9C += 4;
        self->ext.olroxGroundBlast.unk9E += 3;
        self->ext.olroxGroundBlast.unkA0 += 2;
        var_fp = &self->ext.olroxGroundBlast.unk94;
        for (i = 0; i < 7; i++, var_fp++) {
            if (*var_fp > 0x280) {
                *var_fp = 0x280;
            }
        }
        var_fp = &self->ext.olroxGroundBlast.unk94;
        prim = self->ext.olroxGroundBlast.prim7C;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        draw = g_CurrentBuffer->draw;

#ifndef VERSION_PSP
        tpage = 0x100;
        if (draw.ofs[0]) {
#endif
            tpage = 0x104;
#ifndef VERSION_PSP
        }
#endif

        prim2 = self->ext.olroxGroundBlast.prim;
        for (i = 0; i < 6; i++) {
            unk8A = *var_fp;
            var_fp++;
            var_s6 = posY - unk8A;
            if (var_s6 > self->posY.i.hi) {
                var_s6 = self->posY.i.hi;
            }
            var_s8 = *var_fp;
            var_s5 = posY - var_s8;
            if (var_s5 > self->posY.i.hi) {
                var_s5 = self->posY.i.hi;
            }
            var_s7 = self->posX.i.hi;
            u = var_s7 - 0x18;
            for (j = 0; j < 2; j++) {
                prim->y0 = prim->y1 = var_s6;
                prim->y2 = prim->y3 = var_s5;
                prim->x1 = prim->x3 = var_s7;
                prim->x0 =
                    u + (4 * rcos((unk8A * 24) + j * ROT(180))) / ROT(360);
                prim->x2 =
                    u + (4 * rcos((var_s8 * 24) + j * ROT(180))) / ROT(360);
                prim2->tpage = tpage;
                prim2->u0 = prim2->u2 = u;
                prim2->u1 = prim2->u3 = var_s7;
                prim2->v0 = prim2->v1 = var_s6;
                prim2->v2 = prim2->v3 = var_s5;
                LOW(prim2->x0) = LOW(prim->x0);
                LOW(prim2->x1) = LOW(prim->x1);
                LOW(prim2->x2) = LOW(prim->x2);
                LOW(prim2->x3) = LOW(prim->x3);
                if (var_s6 < 0) {
                    prim2->v0 = prim2->v1 = 0;
                    prim2->y0 = prim2->y1 = 0;
                }
                if (var_s5 > 0xF0) {
                    prim2->v2 = prim2->v3 = 0xF0;
                    prim2->y2 = prim2->y3 = 0xF0;
                }
                if (prim2->x0 > 0x100) {
                    prim2->x0 = prim2->x2 = 0x100;
                    prim2->u0 = prim2->u2 = 0xFF;
                }
                if (prim2->x1 > 0x100) {
                    prim2->x1 = prim2->x3 = 0x100;
                    prim2->u1 = prim2->u3 = 0xFF;
                }
                if (prim2->x0 < 0) {
                    prim2->x0 = prim2->x2 = 0;
                    prim2->u0 = prim2->u2 = 0;
                }
                if (prim2->x1 < 0) {
                    prim2->x1 = prim2->x3 = 0;
                    prim2->u1 = prim2->u3 = 0;
                }
                prim2->drawMode = DRAW_DEFAULT;
                if (i == 5) {
                    prim2->drawMode = DRAW_HIDE;
                }
                prim2 = prim2->next;
                prim = prim->next;
                u += 48;
            }
        }

        if (self->ext.olroxGroundBlast.unk96 > 0) {
            if (self->ext.olroxGroundBlast.unk9E > 0) {
                posY = self->ext.olroxGroundBlast.unk96 -
                       self->ext.olroxGroundBlast.unk9E;
                if (self->ext.olroxGroundBlast.unkA0 > 0) {
                    posY += (self->ext.olroxGroundBlast.unk9E -
                             self->ext.olroxGroundBlast.unkA0) /
                            2;
                }
            } else {
                posY = self->ext.olroxGroundBlast.unk96;
            }
            posY /= 2;

            if (posY > 0x100) {
                posY = 0xFF;
            }
            self->hitboxHeight = posY;
            self->hitboxOffY =
                -self->ext.olroxGroundBlast.unk96 + self->hitboxHeight;
        }
        if (self->ext.olroxGroundBlast.unkA0 > 0) {
            if (self->scaleX) {
                self->scaleX -= 2;
            }
        }
        if (self->ext.olroxGroundBlast.unkA0 > 0x200) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

extern EInit g_EInitBlastAttack;

void EntityBlastAttack(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBlastAttack);
        if (self->facingLeft) {
            self->posX.i.hi += 0x1C;
        } else {
            self->posX.i.hi -= 0x1C;
        }
        self->posY.i.hi -= 12;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.olroxBlast.prim = prim;
            prim->tpage = 0x12;
            prim->clut = 0x212;
            prim->u0 = prim->u2 = 0xA0;
            prim->u1 = prim->u3 = 0xD0;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0x10;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = prim->x0;
            prim->y0 = prim->y1 = self->posY.i.hi;
            prim->y2 = prim->y3 = prim->y0;
            prim->r0 = prim->g0 = prim->b0 = 0;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = 0xA0;
            LOW(prim->r3) = LOW(prim->r1);
            prim->priority = self->zPriority + 4;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
        } else {
            DestroyEntity(self);
            return;
        }

        self->velocityY = 0;
        if (self->facingLeft) {
            self->velocityX = FIX(-0.5);
            self->ext.olroxBlast.unkAA.i.hi = -0x30U;
        } else {
            self->velocityX = FIX(0.5);
            self->ext.olroxBlast.unkAA.i.hi = 0x30;
        }
        self->hitboxWidth = 0;
        self->hitboxHeight = 5;
        PlaySfxPositional(SFX_SCIFI_BLAST);
        break;

    case 1:
        MoveEntity();
        if (self->facingLeft) {
            self->velocityX -= FIX(0.125);
            self->ext.olroxBlast.unkAA.val -= FIX(5);
        } else {
            self->velocityX += FIX(0.125);
            self->ext.olroxBlast.unkAA.val += FIX(5);
        }
        prim = self->ext.olroxBlast.prim;
        prim->x1 = prim->x3 = self->posX.i.hi + self->ext.olroxBlast.unkAA.i.hi;
        prim->x0 = prim->x2 = self->posX.i.hi;
        prim->y0 = prim->y1 = self->posY.i.hi - 8;
        prim->y2 = prim->y3 = prim->y0 + 16;

        self->hitboxWidth = abs(self->ext.olroxBlast.unkAA.i.hi) / 4;
        self->hitboxOffX =
            abs(self->ext.olroxBlast.unkAA.i.hi) - self->hitboxWidth - 4;
        break;
    }

    if (abs(self->posX.i.hi) > 0x280) {
        DestroyEntity(self);
    }
}

extern EInit g_EInitPortalSkulls;

void EntityPortalSkulls(Entity* self) {
    Entity* entity;
    Entity* player;
    s16 angle;
    s16 offX, offY;

    if (D_us_80180BA8 != 0) {
        self->flags |= FLAG_DEAD;
    }

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_EXPLODE_B);
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_ID(LASER_EXPLOSION), self, entity);
            entity->params = 2;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitPortalSkulls);
        self->hitboxState = 0;
        self->drawFlags |= ENTITY_OPACITY;
        self->hitboxOffY = -1;
        self->ext.olroxSkulls.unkAA = ((Random() & 0x3F) * 0x10) + 0x200;
        if (self->params) {
            self->step = 2;
            self->zPriority -= 1;
            self->hitboxState = 0;
            self->blendMode |= BLEND_ADD | BLEND_TRANSP;
            return;
        }
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_ID(PORTAL_SKULLS), self, entity);
            entity->params = 1;
            entity->ext.olroxSkulls.parent = self;
        }
        break;
    case 1:
        if (self->opacity < 0x80) {
            self->opacity += 4;
            self->hitboxState = 0;
        } else {
            self->hitboxState = 3;
        }
        AnimateEntity(anim_22, self);
        MoveEntity();
        if (self->velocityX > 0) {
            self->facingLeft = true;
        } else {
            self->facingLeft = false;
        }
        player = &PLAYER;
        offX = player->posX.i.hi - self->posX.i.hi;
        offY = player->posY.i.hi - self->posY.i.hi;
        offY -= 32;
        angle = ratan2(-offY, offX);
        angle = func_us_801AD26C(8, self->ext.olroxSkulls.unkAA, angle);
        self->velocityX = rcos(angle) * 16;
        self->velocityY = rsin(angle) * -16;
        self->ext.olroxSkulls.unkAA = angle;
        break;
    case 2:
        AnimateEntity(anim_21, self);
        entity = self->ext.olroxSkulls.parent;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        self->opacity = entity->opacity;
        if (!entity->entityId) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityPortal(Entity* self) {
    Entity* entity;

    entity = self->ext.olroxAfterImage.parent;
    if (entity->flags & FLAG_DEAD) {
        self->flags |= FLAG_DEAD;
        self->step = 3;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitOlroxAfterImage);
        self->animCurFrame = 0x54;
        self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0;
        self->zPriority -= 1;
        self->hitboxState = 0;
        break;
    case 1:
        AnimateEntity(anim_23, self);
        if (self->scaleX < 256) {
            self->scaleX = self->scaleY += 8;
        } else {
            self->scaleX = self->scaleY = 256;
            self->step++;
        }
        break;
    case 2:
        AnimateEntity(anim_23, self);
        if (g_Timer % 12 == 0) {
            entity = AllocEntity(&g_Entities[160], &g_Entities[168]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(PORTAL_SKULLS), self, entity);
                entity->ext.olroxAfterImage.parent = self;
                PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
            }
        }
        if (g_Timer % 5) {
            self->palette = PAL_FLAG(0x213);
        } else {
            self->palette = PAL_FLAG(0x215);
        }
        entity = self->ext.olroxAfterImage.parent;
        if (entity->ext.olroxAfterImage.unk85) {
            self->step++;
        }
        break;
    case 3:
        AnimateEntity(anim_23, self);
        self->scaleX = self->scaleY -= 8;
        if (self->scaleX < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_801806D8;

// OlroxAfterImage or something else?
void func_us_801AFAF4(Entity* self) {
    Entity* entity;
    u8 angle2;
    s32 distX;
    s32 distY;
    s32 posX;
    s16 angle;
    s16 offsetX;
    s16 offsetY;
    s32 distance;

    entity = self->ext.olroxAfterImage.parent;
    if (entity->flags & FLAG_DEAD) {
        self->flags |= FLAG_DEAD;
    }
    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 2;
        }
        DestroyEntity(self);
        PlaySfxPositional(SFX_BAT_SCREECH);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801806D8);
        self->hitboxState = 0;
        self->hitboxOffX = 1;
        self->hitboxOffY = 1;
        entity = self->ext.olroxAfterImage.parent;
        self->zPriority = entity->zPriority + 2;
        self->palette = 0x219;
        self->pose = (Random() & 3) * 2;
        self->ext.olroxAfterImage.timer = (self->params + 1) * 14;
        self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
        self->params = Random() & 3;
        break;

    case 1:
        AnimateEntity(anim_18, self);
        posX = self->posX.i.hi;
        entity = self->ext.olroxAfterImage.parent;

        offsetX = entity->posX.i.hi;
        offsetY = entity->posY.i.hi;
        offsetY -= 32;

        distX = self->posX.i.hi - offsetX;
        distY = self->posY.i.hi - offsetY;

        angle = ratan2(-distY, distX);
        if (entity->facingLeft) {
            angle += ROT(45.0 / 32.0);
        } else {
            angle -= ROT(45.0 / 32.0);
        }

        distance = SQ(distX) + SQ(distY);
        distance = SquareRoot0(distance);
        distance -= 2;
        self->posX.i.hi = offsetX + (distance * rcos(angle)) / 4096;
        self->posY.i.hi = offsetY - (distance * rsin(angle) / 4096);
        self->scaleX = (distance * self->params) + 0x100;
        if (self->scaleX > 0x300) {
            self->scaleX = 0x300;
        }
        self->scaleY = self->scaleX;
        posX = self->posX.i.hi - posX;
        if (posX > 0) {
            self->facingLeft = false;
        } else {
            self->facingLeft = true;
        }
        if (distance < 8) {
            self->ext.olroxAfterImage.unkA8 = Random();
            self->palette = 0x209;
            self->hitboxState = 3;
            self->drawFlags = ENTITY_DEFAULT;
            self->step++;
        }
        break;

    case 2:
        entity = self->ext.olroxAfterImage.parent;
        AnimateEntity(anim_18, self);
        MoveEntity();
        if (self->velocityX > 0) {
            self->facingLeft = true;
            self->zPriority = entity->zPriority + 2;
        } else {
            self->facingLeft = false;
            self->zPriority = entity->zPriority - 2;
        }
        offsetX = entity->posX.i.hi;
        offsetY = entity->posY.i.hi;
        offsetX = offsetX - self->posX.i.hi;
        offsetY = offsetY - self->posY.i.hi;
        angle2 = Ratan2Shifted(offsetX, offsetY);
        self->ext.olroxAfterImage.unkA8 = AdjustValueWithinThreshold(
            E_EXPLOSION, self->ext.olroxAfterImage.unkA8, angle2);
        SetEntityVelocityFromAngle(self->ext.olroxAfterImage.unkA8, 0x10);
        if (entity->ext.olroxAfterImage.unk84) {
            if (!--self->ext.olroxAfterImage.timer) {
                entity = &PLAYER;
                angle2 = GetAngleBetweenEntitiesShifted(self, entity);
                SetEntityVelocityFromAngle(angle2, 32);
                self->step++;
            }
        }
        break;

    case 3:
        AnimateEntity(anim_18, self);
        MoveEntity();
        if (self->velocityX > 0) {
            self->facingLeft = false;
        } else {
            self->facingLeft = true;
        }

        if (abs(self->posX.i.hi) > 0x200 || abs(self->posY.i.hi) > 0x200) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityOlroxAfterImage(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitOlroxAfterImage);
        self->hitboxState = 0;
        self->palette = 0x217;
        self->animCurFrame = self->params;
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = 0x80;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->zPriority -= 2;
    }
    self->opacity -= 2;
    if (!self->opacity) {
        DestroyEntity(self);
    }
}

static s16 D_us_80180D94[] = {
    0x0008, 0x0010, 0x0000, 0x0000, 0x0004, 0x006A, 0x0040, 0x0006,
    0x0000, 0xFFF8, 0x0010, 0x006A, 0x0004, 0x0004, 0x0000, 0x0000,
    0x0004, 0x006C, 0x0004, 0x0020, 0x0000, 0x0000, 0x0004, 0x006A,
};

typedef enum FurnitureType {
    FURNITURE_TABLE = 0x5,
    FURNITURE_FACING_LEFT = 0x100,
} FurnitureType;

void EntityFurniture(Entity* self) {
    s32 i;
    Entity* entity;
    s32 furnitureType;
    s16* furnitureInit;
    s32 posX;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = -0x7FFA;
        self->unk5A = 0x48;
        self->palette = 0x209;
        self->hitboxState = 2;
        if (self->params & 0x100) {
            self->facingLeft = true;
        }
        self->zPriority -= 4;
        if (self->params == 1) {
            D_us_80180BA8 = 0;
        }
        furnitureType = self->params & 0xFF;
        self->animCurFrame = furnitureType;
        if (furnitureType < 5) {
            furnitureInit = D_us_80180D94;
            furnitureInit += (furnitureType - 1) * 6;
            self->hitboxWidth = *furnitureInit++;
            self->hitboxHeight = *furnitureInit++;
            self->hitboxOffX = *furnitureInit++;
            self->hitboxOffY = *furnitureInit++;
            self->hitPoints = *furnitureInit++;
            self->zPriority = *furnitureInit++;
            return;
        }
        self->step += furnitureType;
        break;

    case 1:
        if (self->flags & FURNITURE_FACING_LEFT) {
            self->hitboxState = 0;
            self->step += self->params & 0xFF;
        }
        break;

    case 2:
        self->animCurFrame = 0xA;
        if (GetSideToPlayer() & 1) {
            self->velocityX = FIX(1.0);
        } else {
            self->velocityX = FIX(-1.0);
        }
        self->step = 11;
        break;
    case 3:
        // when table is destroyed?
        for (i = 0; i < 4; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(FURNITURE), self, entity);
                entity->params = i + 5;
                entity->posX.i.hi += i * -30 + 48;
            }
        }
        if (entity) {
            entity->params = FURNITURE_FACING_LEFT | FURNITURE_TABLE;
        }

        for (i = 0; i < 4; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 0x13;
                entity->posX.i.hi += i * -30 + 48;
            }
        }
        entity = self;
        entity++;
        for (i = 0; i < 3; i++, entity++) {
            entity->flags |= FLAG_DEAD;
        }
        self->animCurFrame = 0;
        self->step = 0x20;
        break;
    case 4:
        // chairs?
        for (i = 0; i < 2; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(FURNITURE), self, entity);
                entity->params = i + 8;
                entity->posY.i.hi += i * 8;
                if (i != 0) {
                    if (GetSideToPlayer() & 1) {
                        entity->velocityX = FIX(0.5);
                    } else {
                        entity->velocityX = FIX(-0.5);
                    }
                    entity->velocityY = FIX(-1);
                }
            }
        }
        PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
        self->animCurFrame = 0;
        self->step = 0x20;
        break;
    case 5:
        // candles?
        for (i = 0; i < 3; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(FURNITURE), self, entity);
                entity->params = i + 0xB;
                entity->posY.i.hi += i * 28 - 28;
            }
        }
        PlaySfxPositional(SFX_CANDLE_HIT_WHOOSH_B);
        self->animCurFrame = 0;
        self->step = 32;
        break;
    case 6:
        self->zPriority = 0x6A;
        break;
    case 7:
    case 8:
        self->zPriority = 0x6A;
        MoveEntity();
        self->velocityY += FIX(0.0625);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY += 8;
        if (func_us_801AD2F0(posX, posY)) {
            self->step = 32;
        }
        break;
    case 9:
        self->drawFlags |= ENTITY_ROTATE;
        self->rotate -= 16;
        self->zPriority = 0x6C;
        MoveEntity();
        self->velocityY += FIX(0.09375);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY += 4;
        if (func_us_801AD2F0(posX, posY)) {
            self->entityId = 2;
            self->pfnUpdate = EntityExplosion;
            self->params = 0;
            self->step = 0;
        }
        break;
    case 10:
        self->drawFlags |= ENTITY_ROTATE;
        self->rotate += ROT(11.25);
        self->zPriority = 0x6C;
        MoveEntity();
        self->velocityY += FIX(0.125);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        if (func_us_801AD2F0(posX, posY)) {
            self->entityId = 2;
            self->pfnUpdate = EntityExplosion;
            self->step = 0;
            self->params = 0;
        }
        break;
    case 11:
        self->zPriority = 0x6A;
        MoveEntity();
        self->velocityY += FIX(0.0625);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY += 10;
        if (func_us_801AD2F0(posX, posY)) {
            self->step = 0x20;
        }
        break;
    case 12:
        self->rotate -= ROT(4.21875);
        // fallthrough
    case 13:
        self->drawFlags |= ENTITY_ROTATE;
        self->rotate += 40;
        self->zPriority = 0x6B;
        MoveEntity();
        self->velocityY += FIX(0.09375);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY += 6;
        if (func_us_801AD2F0(posX, posY)) {
            self->entityId = 2;
            self->pfnUpdate = EntityExplosion;
            self->params = 0;
            self->step = 0;
        }
        break;
    case 14:
        self->zPriority = 0x6A;
        break;
    }
}
