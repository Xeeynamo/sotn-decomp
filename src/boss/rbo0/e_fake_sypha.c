// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo0.h"

extern EInit D_us_801804C4;
extern s8 D_us_801806B8[];
extern u8 D_us_80180718[];
static s32 D_us_80180C60 = 0;
static s16 D_us_80180C64[] = {
    0,
    24,
    8,
    0,
};
static s16 D_us_80180C6C[] = {
    0x0000, 0x0018, 0x0000, 0x0004, 0x0008, 0xFFFC, 0xFFF0, 0x0000,
};
static AnimateEntityFrame D_us_80180C7C[] = {
    {0x06, 0xA9}, {0x06, 0xAA}, {0x06, 0xAB}, {0x06, 0xAC},
    {0x06, 0xAD}, {0x06, 0xAE}, {0x00, 0x00}, {0x00, 0x00},
};

static AnimateEntityFrame D_us_80180C8C[] = {
    {0x06, 0xAF}, {0x06, 0xB0}, {0x06, 0xB7}, {0x06, 0xB8},
    {0x06, 0xB9}, {0x06, 0xBA}, {0xFF, 0x00}, {0x00, 0x00},
};

static AnimateEntityFrame D_us_80180C9C[] = {
    {0x06, 0xB5}, {0x06, 0xB6}, {0x06, 0xB7}, {0x06, 0xB8},
    {0x06, 0xB9}, {0x06, 0xBA}, {0x00, 0x00}, {0x00, 0x00},
};

static AnimateEntityFrame D_us_80180CAC[] = {
    {0x06, 0xB5}, {0x06, 0xB6}, {0x06, 0xB1}, {0x06, 0xB2},
    {0x06, 0xB3}, {0x06, 0xB4}, {0xFF, 0x00}, {0x00, 0x00},
};

static AnimateEntityFrame D_us_80180CBC[] = {
    {0x06, 0xBB},
    {0x06, 0xBC},
    {0x06, 0xBD},
    {0xFF, 0x00},
};

static AnimateEntityFrame D_us_80180CC4[] = {
    {0x02, 0xBE},
    {0x02, 0xBF},
    {0x00, 0x00},
    {0x00, 0x00},
};

static AnimateEntityFrame D_us_80180CCC[] = {
    {0x40, 0xC0}, {0x06, 0xC1}, {0x06, 0xC2},
    {0x06, 0xC3}, {0xFF, 0x00}, {0x00, 0x00},
};

static AnimateEntityFrame D_us_80180CD8[] = {
    {0x03, 0x01}, {0x03, 0x02}, {0x03, 0x03}, {0x03, 0x04}, {0x03, 0x05},
    {0x03, 0x06}, {0x03, 0x07}, {0x03, 0x08}, {0x03, 0x09}, {0x03, 0x0A},
    {0x03, 0x0B}, {0x03, 0x0C}, {0x03, 0x0D}, {0xFF, 0x00},
};

static AnimateEntityFrame D_us_80180CF4[] = {
    {0x04, 0x01}, {0x04, 0x02}, {0x04, 0x03}, {0x04, 0x04}, {0x04, 0x05},
    {0x04, 0x06}, {0x04, 0x07}, {0x04, 0x08}, {0x04, 0x09}, {0x04, 0x0A},
    {0x03, 0x0B}, {0x02, 0x0C}, {0x01, 0x0D}, {0xFF, 0x00},
};

static AnimateEntityFrame D_us_80180D10[] = {
    {0x02, 0x02}, {0x02, 0x03}, {0x02, 0x04}, {0x02, 0x05},
    {0x02, 0x06}, {0x02, 0x07}, {0x02, 0x06}, {0x02, 0x05},
    {0x02, 0x04}, {0x02, 0x03}, {0x00, 0x00}, {0x00, 0x00},
};

static AnimateEntityFrame D_us_80180D28[] = {
    {0x03, 0x14}, {0x03, 0x15}, {0x03, 0x16}, {0x03, 0x15}, {0x03, 0x16},
    {0x03, 0x17}, {0x03, 0x16}, {0x03, 0x17}, {0x03, 0x18}, {0x03, 0x17},
    {0x03, 0x18}, {0x03, 0x19}, {0x03, 0x18}, {0x03, 0x19}, {0x03, 0x1A},
    {0x03, 0x19}, {0x03, 0x1A}, {0x03, 0x1B}, {0x03, 0x1A}, {0x03, 0x1B},
    {0x03, 0x14}, {0x03, 0x1B}, {0x03, 0x14}, {0x03, 0x15}, {0x00, 0x00},
    {0x00, 0x00},
};

void EntityFakeSypha(Entity* self) {
    Entity* entity;
    s32 i;
    s32 facingLeft;
    s32 posX;
    s32 posY;
    s8* temp_v1_15;
    s32 sideToPlayer;

    if (self->hitFlags & 3 && self->step < 8) {
        SetStep(8);
    }
    if (self->flags & FLAG_DEAD && self->step != 0xE) {
        SetStep(14);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804C4);
        self->hitboxState = 0;
        entity = self - 1;
        CreateEntityFromCurrentEntity(E_ID(COFFIN), entity);
        entity->posY.i.hi = 0xBA - g_Tilemap.scrollY.i.hi;
        SetStep(1);
        // fallthrough

    case 1:
        self->animCurFrame = 5;
        if (D_us_801806B0 & 1) {
            SetStep(2);
        }
        break;

    case 2:
        entity = self - 1;
        switch (self->step_s) {
        case 0:
            if (entity->ext.sypha.unk8C) {
                self->animCurFrame = 0;
                self->step_s++;
            }
            break;
        case 1:
            if (!entity->ext.sypha.unk8C) {
                self->animCurFrame = 6;
                self->step_s++;
            }
            break;
        case 2:
            if (D_us_801806B0 & 2) {
                self->hitboxState = 3;
                SetStep(3);
            }
            break;
        }
        break;

    case 3:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->animCurFrame = 0xC0;
            posY = 0x80 - g_Tilemap.scrollY.i.hi;
            self->velocityY = FIX(-0.75);
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            AnimateEntity(D_us_80180CCC, self);
            posY = 0x80 - g_Tilemap.scrollY.i.hi;
            posY -= self->posY.i.hi;
            if (posY > 0) {
                SetStep(5);
            }
            break;
        }
        break;
    case 4:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
        }
        AnimateEntity(D_us_80180C7C, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            self->velocityY = 0;
            self->ext.sypha.timer =
                (Random() & 0x1F) + (3 - D_us_801806B4) * 0x10;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            AnimateEntity(D_us_80180C7C, self);
            posY = 0x80 - self->posY.i.hi;
            if (posY < -4) {
                self->velocityY -= FIX(1.0 / 128.0);
                if (self->velocityY <= FIX(-0.375)) {
                    self->velocityY = FIX(-0.375);
                }
            }
            if (posY > 4) {
                self->velocityY += FIX(1.0 / 64.0);
                if (self->velocityY >= FIX(0.375)) {
                    self->velocityY = FIX(0.375);
                }
            }
            if (self->facingLeft) {
                self->velocityX += FIX(1.0 / 64.0);
                if (self->velocityX >= FIX(0.75)) {
                    self->velocityX = FIX(0.75);
                }
            } else {
                self->velocityX -= FIX(1.0 / 64.0);
                if (self->velocityX <= FIX(-0.75)) {
                    self->velocityX = FIX(-0.75);
                }
            }
            sideToPlayer = (GetSideToPlayer() & 1) ^ 1;
            if ((self->facingLeft != sideToPlayer) &&
                GetDistanceToPlayerX() > 0x40) {
                SetSubStep(2);
            }

            if (!--self->ext.sypha.timer) {
                SetSubStep(3);
            }
            break;
        case 2:
            MoveEntity();
            self->velocityX -= self->velocityX >> 5;
            self->velocityY -= self->velocityY >> 5;
            if (AnimateEntity(D_us_80180CBC, self) == 0) {
                self->facingLeft ^= 1;
                self->animCurFrame = 0xBB;
                SetSubStep(1);
            }
            break;
        case 3:
            MoveEntity();
            AnimateEntity(D_us_80180C7C, self);
            self->velocityX -= self->velocityX / 16;
            self->velocityY -= self->velocityY / 16;
            if (abs(self->velocityX) < FIX(0.125)) {
                SetStep(9);
            }
            break;
        }
        break;
    case 6:
        MoveEntity();
        self->velocityX -= self->velocityX >> 5;
        self->velocityY -= self->velocityY >> 5;
        if (AnimateEntity(D_us_80180CBC, self) == 0) {
            self->facingLeft ^= 1;
            self->animCurFrame = 0xBB;
            SetStep(5);
        }
        break;

    case 9:
        switch (self->step_s) {
        case 0:
            facingLeft = self->facingLeft;
            if (facingLeft == ((GetSideToPlayer() & 1) ^ 1)) {
                SetSubStep(2);
            } else {
                self->step_s++;
            }
            // fallthrough
        case 1:
            if (AnimateEntity(D_us_80180CBC, self) == 0) {
                self->facingLeft ^= 1;
                self->animCurFrame = 0xBB;
                SetSubStep(2);
            }
            break;
        case 2:
            if (AnimateEntity(D_us_80180C8C, self) == 0) {
                SetStep(11);
                if (D_us_801806B4 >= 1) {
                    sideToPlayer = GetSideToPlayer();
                    if ((g_Player.status & PLAYER_STATUS_BAT_FORM) ||
                        (GetDistanceToPlayerX() > 0x40) || (sideToPlayer & 2)) {
                        SetStep(10);
                    }
                    if (D_us_801806B4 >= 2) {
                        sideToPlayer = ((sideToPlayer & 1) ^ 1);
                        if (GetDistanceToPlayerX() > 0x50 &&
                            self->facingLeft == sideToPlayer) {
                            SetStep(12);
                        }
                        if (D_us_80180C60 == 0) {
                            SetStep(13);
                        }
                    }
                }
            }
            break;
        }
        break;

    case 10:
        switch (self->step_s) {
        case 0:
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(DEATH_FLAMES), self, entity);
                if (self->facingLeft) {
                    entity->posX.i.hi += 0xA;
                } else {
                    entity->posX.i.hi -= 0xA;
                }
                entity->posY.i.hi -= 4;
                entity->facingLeft = self->facingLeft;
                entity->zPriority = self->zPriority + 1;
                entity->params = 3;
            }
            self->ext.sypha.timer = 0x20;
            PlaySfxPositional(SFX_EXPLODE_SMALL);
            self->step_s++;
            // fallthrough
        case 1:
            AnimateEntity(D_us_80180C9C, self);
            if (!--self->ext.sypha.timer) {
                self->step_s++;
            }
            break;

        case 2:
            self->ext.sypha.timer = 0x80;

            PlaySfxPositional(SFX_DRACULA_FLY_IN);
            self->step_s++;
            // fallthrough

        case 3:
            if (!(self->ext.sypha.timer & 3)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(HOLY_FLAME), self, entity);
                    if (self->facingLeft) {
                        entity->posX.i.hi += 0xA;
                    } else {
                        entity->posX.i.hi -= 0xA;
                    }
                    entity->posY.i.hi -= 4;
                    entity->params = (self->ext.sypha.timer & 4) >> 2;
                    entity->facingLeft = self->facingLeft;
                    entity->zPriority = self->zPriority + 1;
                }
            }

            AnimateEntity(D_us_80180C9C, self);
            if (!--self->ext.sypha.timer) {
                SetStep(7);
            }
            break;
        }
        break;
    case 11:
        switch (self->step_s) {
        case 0:
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(DEATH_FLAMES), self, entity);
                if (self->facingLeft) {
                    entity->posX.i.hi += 0xA;
                } else {
                    entity->posX.i.hi -= 0xA;
                }
                entity->posY.i.hi -= 4;
                entity->facingLeft = self->facingLeft;
                entity->zPriority = self->zPriority + 1;
                entity->params = 4;
            }
            self->ext.sypha.timer = 0x20;
            self->step_s++;
            // fallthrough
        case 1:
            AnimateEntity(D_us_80180C9C, self);
            if (!--self->ext.sypha.timer) {
                self->step_s++;
            }
            break;
        case 2:
            self->ext.sypha.timer = 0x50;
            PlaySfxPositional(SFX_FAKE_SYPHA_ATTACK);
            self->step_s++;
            // fallthrough
        case 3:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(PETRIFY_CLOUD), self, entity);
                if (self->facingLeft) {
                    entity->posX.i.hi += 8;
                } else {
                    entity->posX.i.hi -= 8;
                }
                entity->posY.i.hi -= 6;
                entity->facingLeft = self->facingLeft;
                entity->zPriority = self->zPriority + 1;
            }
            if (!(self->ext.sypha.timer & 7)) {
                PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
            }
            AnimateEntity(D_us_80180C9C, self);
            if (!--self->ext.sypha.timer) {
                SetStep(7);
            }
            break;
        }
        break;
    case 12:
        switch (self->step_s) {
        case 0:
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(DEATH_FLAMES), self, entity);
                if (self->facingLeft) {
                    entity->posX.i.hi += 10;
                } else {
                    entity->posX.i.hi -= 10;
                }
                entity->posY.i.hi -= 4;
                entity->facingLeft = self->facingLeft;
                entity->zPriority = self->zPriority + 1;
                entity->params = 5;
            }
            self->ext.sypha.timer = 0x20;
            PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
            self->step_s++;
            // fallthrough
        case 1:
            AnimateEntity(D_us_80180C9C, self);
            if (!--self->ext.sypha.timer) {
                self->step_s++;
            }
            break;
        case 2:
            for (i = 0; i < 3; i++) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(HOLY_LIGHTNING), self, entity);
                    if (self->facingLeft) {
                        entity->posX.i.hi += 8;
                    } else {
                        entity->posX.i.hi -= 8;
                    }
                    entity->posY.i.hi -= 6;
                    entity->facingLeft = self->facingLeft;
                    entity->zPriority = self->zPriority + 1;
                    entity->rotate = (i * ROT(45)) - ROT(45);
                    if (!self->facingLeft) {
                        entity->rotate += ROT(180);
                    }
                }
            }
            PlaySfxPositional(SFX_OUIJA_TABLE_DEATH);
            self->ext.sypha.timer = 0x40;
            self->step_s++;
            // fallthrough
        case 3:
            AnimateEntity(D_us_80180C9C, self);
            if (!--self->ext.sypha.timer) {
                SetStep(7);
            }
            break;
        }
        break;
    case 13:
        switch (self->step_s) {
        case 0:
            self->ext.sypha.timer = 0x20;
            PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
            self->step_s++;
            // fallthrough
        case 1:
            if (!(self->ext.sypha.timer & 3)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(DEATH_FLAMES), self, entity);
                    entity->posY.i.hi += (Random() & 0x1F);
                    entity->zPriority = self->zPriority - 1;
                    entity->params = 6;
                }
            }
            AnimateEntity(D_us_80180C9C, self);
            if (!--self->ext.sypha.timer) {
                self->step_s++;
            }
            break;
        case 2:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(RESURRECT), self, entity);
                entity->posX.i.hi = self->posX.i.hi;
                entity->posY.i.hi = 0xC8 - g_Tilemap.scrollY.i.hi;
            }

            self->ext.sypha.timer = 0x80;
            self->step_s++;
            // fallthrough
        case 3:
            AnimateEntity(D_us_80180C9C, self);
            if (!--self->ext.sypha.timer) {
                SetStep(7);
            }
            break;
        }
        break;
    case 8:
        if (!self->step_s) {
            PlaySfxPositional(SFX_FAKE_SYPHA_PAIN);
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
            self->velocityY = FIX(-2.5);
            self->ext.sypha.timer = 0x10;
            self->step_s++;
        }
        AnimateEntity(D_us_80180CC4, self);
        MoveEntity();
        self->velocityX -= self->velocityX >> 5;
        self->velocityY += FIX(0.09375);
        func_us_80194338(D_us_80180C6C);
        if (!--self->ext.sypha.timer) {
            SetStep(9);
        }
        break;
    case 14: // death
        switch (self->step_s) {
        case 0:
            D_us_801806B4++;
            self->hitboxState = 0;
            self->velocityX = 0;
            self->velocityY = FIX(-2.5);
            self->ext.sypha.timer = 0x20;
            PlaySfxPositional(SFX_FAKE_SYPHA_DEATH);
            self->step_s++;
            // fallthrough
        case 1:
            AnimateEntity(D_us_80180CC4, self);
            MoveEntity();
            self->velocityY -= self->velocityY >> 4;
            if (!--self->ext.sypha.timer) {
                PlaySfxPositional(SFX_DRACULA_FLY_IN);
                self->ext.sypha.timer = 0x40;
                self->step_s++;
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.0625);
            if (!(g_Timer & 3)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(DEATH_FLAMES), self, entity);
                    entity->zPriority = self->zPriority + 1;
                    entity->params = 9;
                    entity->posY.i.hi += 12;
                }
            }
            func_us_80194338(D_us_80180C6C);
            if (!--self->ext.sypha.timer) {
                self->step_s++;
            }
            break;
        case 3:
            self->animCurFrame = 0;
            return;
        }
        break;

    case 7:
        if (AnimateEntity(D_us_80180CAC, self) == 0) {
            SetStep(5);
        }
        break;
    case 0xFF:
#include "../../st/pad2_anim_debug.h"
        break;
    }

    temp_v1_15 = D_us_801806B8;
    temp_v1_15 += D_us_80180718[self->animCurFrame] * 4;
    self->hitboxOffX = *temp_v1_15++;
    self->hitboxOffY = *temp_v1_15++;
    self->hitboxWidth = *temp_v1_15++;
    self->hitboxHeight = *temp_v1_15++;

    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (self->velocityX < 0) {
        if (posX < 0x50) {
            self->posX.i.hi = 0x50 - g_Tilemap.scrollX.i.hi;
        }
    } else if (posX > 0x1B0) {
        self->posX.i.hi = 0x1B0 - g_Tilemap.scrollX.i.hi;
    }
    if (self->velocityY < FIX(0) && posY < 64) {
        self->posY.i.hi = 0x40 - g_Tilemap.scrollY.i.hi;
    }
}

extern EInit D_us_80180530;

void EntityFlameAttack(Entity* self) {
    if (D_us_801806B0 & 4) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180530);
        self->drawFlags = ENTITY_ROTATE | ENTITY_SCALEY | ENTITY_SCALEX;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->rotate = ROT(-90);
        self->scaleX = 64;
        self->scaleY = 128;

        if (self->facingLeft) {
            self->velocityX = FIX(2.5);
        } else {
            self->velocityX = FIX(-2.5);
        }

        if (self->params) {
            self->velocityY = FIX(-0.25);
        } else {
            self->velocityY = FIX(0.25);
        }
        self->hitboxState = 1;
        self->hitboxWidth = self->hitboxHeight = 3;
        // fallthrough

    case 1:
        if (self->params) {
            if (self->rotate < ROT(-33.75)) {
                self->rotate += 32;
            }
        } else {
            if (self->rotate > ROT(-157.5)) {
                self->rotate -= ROT(5.625);
            } else {
                self->rotate -= ROT(2.8125);
            }
            self->velocityY -= FIX(1.0 / 32.0);
        }
        self->scaleX += 2;
        self->scaleY += 1;
        MoveEntity();
        self->velocityY -= FIX(1.0 / 128.0);
        if (self->pose > 6) {
            self->velocityX -= (self->velocityX >> 5);
        }
        if (!AnimateEntity(D_us_80180CD8, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_8018053C;

void EntityPetrifyCloud(Entity* self) {
    s16 angle;
    s32 offsetY;

    if (D_us_801806B0 & 4) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018053C);
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->palette = 0x2E9;
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = 0x40;
        self->drawFlags |= ENTITY_ROTATE | ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0x80;
        self->rotate = (Random() * 2) - ROT(22.5);
        angle = self->rotate + ROT(90.0);
        self->velocityX = rcos(angle) * 18;
        self->velocityY = rsin(angle) * 20;
        self->hitboxState = 1;
        self->hitboxWidth = self->hitboxHeight = 4;
        // fallthrough
    case 1:
        MoveEntity();
        self->velocityY += self->velocityY >> 5;
        self->velocityX += self->velocityX >> 4;
        offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (offsetY > 0xD8) {
            self->drawFlags &=
                ENTITY_BLINK | ENTITY_MASK_B | ENTITY_MASK_G | ENTITY_MASK_R |
                ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX;
            if (offsetY > 0xE0) {
                self->posY.i.hi = 0xE0 - g_Tilemap.scrollY.i.hi;
            }

            self->velocityY -= self->velocityY >> 2;
            self->velocityX += self->velocityX >> 6;
            if (self->scaleX < 0x180) {
                self->scaleX++;
            }
            if (self->scaleY > 0x40) {
                self->scaleY -= 2;
            }
        } else {
            if (self->scaleY < 0x100) {
                self->scaleX = self->scaleY += 2;
            }
        }
        if (self->opacity < 0xA0) {
            self->opacity += 2;
        }
        if (!AnimateEntity(D_us_80180CF4, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_80180548;

void EntityHolyLightning(Entity* self) {
    s32 i;
    Primitive* prim;
    Entity* player;
    Point16* var_s1;
    s32 primIndex;
    s16 angle;

    s32 posX;
    s32 posY;
    s32 offsetX;
    s32 offsetY;

    if (D_us_801806B0 & 4) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180548);
        self->hitboxWidth = self->hitboxHeight = 4;
        self->drawFlags |= ENTITY_ROTATE | ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0x80;
        self->opacity = 0xC0;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 13);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        for (i = 0; i < 13; i++) {
            prim->tpage = 0x1A;
            prim->clut = self->palette;
            prim->u0 = prim->u2 = 0xC0;
            prim->u1 = prim->u3 = 0xE0;
            prim->v0 = prim->v1 = (i * 2);
            prim->v2 = prim->v3 = ((i * 2) + 2);
            prim->r0 = prim->g0 = prim->b0 = (0xC0 - (i * 0x10));
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        var_s1 = (Point16*)&self->ext.sypha.red;
        for (i = 0; i < 14; i++) {
            var_s1->x = self->posX.i.hi;
            var_s1->y = self->posY.i.hi;
            var_s1++;
        }
        angle = self->rotate;
        self->velocityX = rcos(angle) << 6;
        self->velocityY = rsin(angle) << 6;
        self->ext.sypha.angle = angle;
        self->ext.sypha.timer = 64;

        // fallthrough
    case 1:
        MoveEntity();
        AnimateEntity(D_us_80180D10, self);
        player = &PLAYER;
        angle = GetAngleBetweenEntities(self, player);
        angle = GetNormalizedAngle(0x10, self->ext.sypha.angle, angle);
        self->velocityX = rcos(angle) << 6;
        self->velocityY = rsin(angle) << 6;
        self->ext.sypha.angle = angle;
        if (!--self->ext.sypha.timer) {
            self->step++;
        }
        break;
    case 2:
        MoveEntity();
        AnimateEntity(D_us_80180D10, self);
        offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (offsetX < -0x40 || offsetY < -0x40 || offsetX > 0x240 ||
            offsetY > 0x140) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    var_s1 = (Point16*)&self->unkB8;
    for (i = 0; i < 13; i++) {
        var_s1->x = (var_s1 - 1)->x - g_ScrollDeltaX;
        var_s1->y = (var_s1 - 1)->y - g_ScrollDeltaY;
        var_s1--;
    }
    var_s1 = (Point16*)&self->ext.sypha.red;
    var_s1->x = self->posX.i.hi;
    var_s1->y = self->posY.i.hi;
    var_s1 = (Point16*)&self->ext.sypha.red;
    prim = self->ext.prim;
    posX = var_s1->x;
    posY = var_s1->y;
    prim = self->ext.prim;
    offsetX = var_s1[1].x - posX;
    offsetY = var_s1[1].y - posY;
    angle = ratan2(offsetY, offsetX);
    angle -= 0x400;
    offsetX = (rcos(angle) * 5) >> 0xC;
    offsetY = (rsin(angle) * 5) >> 0xC;
    prim->x0 = posX + offsetX;
    prim->y0 = posY + offsetY;
    prim->x1 = posX - offsetX;
    prim->y1 = posY - offsetY;
    prim->priority = self->zPriority;
    var_s1++;

    for (i = 0; i < 11; i++) {
        offsetX = var_s1->x - posX;
        offsetY = var_s1->y - posY;
        angle = ratan2(offsetY, offsetX);
        angle -= 0x400;
        posX = (var_s1->x + posX) / 2;
        posY = (var_s1->y + posY) / 2;

        offsetX = ((0xC - i) * rcos(angle)) >> 0xC;
        offsetY = ((0xC - i) * rsin(angle)) >> 0xC;
        prim->x2 = posX + offsetX;
        prim->y2 = posY + offsetY;
        prim->x3 = posX - offsetX;
        prim->y3 = posY - offsetY;
        prim->priority = self->zPriority;
        prim = prim->next;
        prim->x0 = posX + offsetX;
        prim->y0 = posY + offsetY;
        prim->x1 = posX - offsetX;
        prim->y1 = posY - offsetY;
        posX = var_s1->x;
        posY = var_s1->y;
        var_s1++;
    }
    prim->x1 = prim->x2 = var_s1->x;
    prim->y2 = prim->y3 = var_s1->y;
    prim->priority = self->zPriority;

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
    prim = self->ext.prim;
    while (prim != NULL) {
        if (g_Timer & 1) {
            prim->u0 = prim->u2 = 0xC0;
            prim->u1 = prim->u3 = 0xE0;
        } else {
            prim->u0 = prim->u2 = 0xE0;
            prim->u1 = prim->u3 = 0xC0;
        }
        prim = prim->next;
    }
    return;
}

extern EInit D_us_80180554;
extern s32 D_us_80180C60;

void EntitySummonAttack(Entity* self) {
    Entity* entity;  // s7
    Primitive* prim; // s0
    s32 posX;        // s4
    s32 posY;        // s6
    s32 primIndex;   // s8

    s32 brightness;
    s16 red;
    s16 green;
    s16 blue;

    if (D_us_801806B0 & 4) {
        self->flags |= FLAG_DEAD;
    }
    if (self->flags & FLAG_DEAD) {
        D_us_80180C60 = 0;
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 3;
        }
        PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_A);
        DestroyEntity(self);
        return;
    }

    D_us_80180C60 = 1;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180554);
        self->animCurFrame = 0;
        self->hitboxState = 0;
        self->hitboxOffY = 3;
        primIndex = g_api.AllocPrimitives(PRIM_G4, 0x10);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        posX = self->posX.i.hi - 0x10;
        posY = 0xE0 - g_Tilemap.scrollY.i.hi;
        while (prim != NULL) {
            prim->x0 = prim->x2 = posX;
            posX += 2;
            prim->x1 = prim->x3 = posX;
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = posY;
            prim->r0 = prim->g0 = prim->b0 = 0x10;
            LOW(prim->r1) = LOW(prim->r0);
            prim->r2 = prim->g2 = prim->b2 = 0xE0;
            LOW(prim->r3) = LOW(prim->r2);
            prim->priority = self->zPriority + 1;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        // fallthrough
    case 1:
        switch (self->step_s) {
        case 0:
            self->ext.sypha.timer = 48;
            PlaySfxPositional(SFX_TELEPORT_BANG_B);
            self->step_s++;
            // fallthrough
        case 1:
            prim = self->ext.prim;
            brightness = 0;
            while (prim != NULL) {
                prim->y0 = prim->y1 -= 4;
                prim = prim->next;
            }

            if (!--self->ext.sypha.timer) {
                self->step_s++;
            }

            prim = self->ext.prim;
            while (prim != NULL) {
                if (Random() & 1) {
                    prim->y0 = prim->y1 += 4;
                } else {
                    prim->y0 = prim->y1 -= 4;
                }
                prim = prim->next;
            }

            prim = self->ext.prim;
            red = self->ext.sypha.red += 0x70;
            green = self->ext.sypha.green += 0x40;
            blue = self->ext.sypha.blue += 0x10;

            while (prim != NULL) {
                prim->r2 = ((rcos(red) << 6) >> 0xC) + 0xA0;
                prim->g2 = ((rsin(green) << 6) >> 0xC) + 0xA0;
                prim->b2 = ((rcos(blue) << 6) >> 0xC) + 0xA0;
                red += 0x10;
                green += 0x24;
                red += 0x100;
                prim->r3 = ((rcos(red) << 6) >> 0xC) + 0xA0;
                prim->g3 = ((rsin(green) << 6) >> 0xC) + 0xA0;
                prim->b3 = ((rcos(blue) << 6) >> 0xC) + 0xA0;
                prim = prim->next;
            }
            break;
        case 2:
            self->animCurFrame = 0x5C;
            self->facingLeft = GetSideToPlayer() & 1;
            self->ext.sypha.timer = 32;
            self->step_s++;
            // fallthrough
        case 3:
            prim = self->ext.prim;
            while (prim != NULL) {
                if (Random() & 1) {
                    prim->y0 = prim->y1 += 4;
                } else {
                    prim->y0 = prim->y1 -= 4;
                }
                prim = prim->next;
            }

            if (!--self->ext.sypha.timer) {
                self->step_s++;
            }
            prim = self->ext.prim;
            red = self->ext.sypha.red += 0x70;
            green = self->ext.sypha.green += 0x40;
            blue = self->ext.sypha.blue += 0x10;
            while (prim != NULL) {
                prim->r2 = ((rcos(red) << 6) >> 0xC) + 0xA0;
                prim->g2 = ((rsin(green) << 6) >> 0xC) + 0xA0;
                prim->b2 = ((rcos(blue) << 6) >> 0xC) + 0xA0;
                red += 0x10;
                green += 0x24;
                red += 0x100;
                prim->r3 = ((rcos(red) << 6) >> 0xC) + 0xA0;
                prim->g3 = ((rsin(green) << 6) >> 0xC) + 0xA0;
                prim->b3 = ((rcos(blue) << 6) >> 0xC) + 0xA0;
                prim = prim->next;
            }
            break;
        case 4:
            prim = self->ext.prim;
            brightness = 0;
            while (prim != NULL) {
                brightness = PrimDecreaseBrightness(prim, 10);
                prim = prim->next;
            }
            if (brightness == 0) {
                self->hitboxState = 3;
                g_api.FreePrimitives(self->primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
                SetStep(2);
            }
            break;
        }
        break;
    case 2:
        if (AnimateEntity(D_us_80180D28, self) == 0) {
            self->facingLeft = GetSideToPlayer() & 1;
        }
        if (self->facingLeft) {
            self->velocityX = FIX(-0.5);
        } else {
            self->velocityX = FIX(0.5);
        }
        MoveEntity();
        break;
    }

    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (self->velocityX < 0) {
        if (posX < 0x50) {
            self->posX.i.hi = 0x50 - g_Tilemap.scrollX.i.hi;
        }
    } else if (posX > 0x1B0) {
        self->posX.i.hi = 0x1B0 - g_Tilemap.scrollX.i.hi;
    }
}

static void CreateExplosionPuff() {
    Entity* puff;
    s32 rand3 = Random() & 3; // Random puff style 0, 1, 2
    s16 initAngle = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        puff = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (puff != NULL) {
            CreateEntityFromEntity(E_ID(DEATH_FLAMES), g_CurrentEntity, puff);
            puff->params = 2;
            puff->ext.opaquePuff.speed = 6 - i;
            puff->ext.opaquePuff.angle = initAngle;
            puff->ext.opaquePuff.puffStyle = rand3;
        }
    }
}
