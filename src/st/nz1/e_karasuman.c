// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

extern EInit g_EInitKarasuman;
extern s32 D_us_80181138;

static s16 D_us_8018115C[] = {
    0, 32, 0, 4, 4, -4, -8, 0,
};

static s16 D_us_8018116C[] UNUSED = {
    0,
    32,
    4,
    0,
};

static u8 D_us_80181174[] = {
    0x1E, 0x01, 0x1E, 0x02, 0x00, 0x00, 0x00, 0x00,
};

static u8 D_us_8018117C[] = {
    0x08, 0x01, 0x06, 0x03, 0x04, 0x04, 0x04, 0x2F, 0x01, 0x0A, 0x01,
    0x30, 0x10, 0x0A, 0x06, 0x09, 0x06, 0x2F, 0x04, 0x04, 0xFF,
};

static u8 D_us_80181194[] = {
    2, 4, 8, 5, 8, 6, 3, 5, 0xFF,
};

static u8 D_us_801811A0[] = {
    8, 7, 8, 8, 2, 15, 0xFF,
};

static u8 D_us_801811A8[] = {
    8, 15, 8, 16, 8, 17, 8, 18, 8, 19, 8, 20, 8, 21, 0, 0,
};

static u8 D_us_801811B8[] = {
    8, 15, 8, 7, 0xFF,
};

static u8 D_us_801811C0[] = {
    0x08, 0x05, 0x08, 0x06, 0x08, 0x05, 0x08, 0x04, 0xFF,
};

static u8 D_us_801811CC[] = {
    0x04, 0x0B, 0x02, 0x0C, 0x01, 0x0D, 0x01, 0x0C, 0xFF,
};

static u8 D_us_801811D8[] = {
    0x04, 0x0B, 0x04, 0x07, 0xFF,
};

static u8 D_us_801811E0[] = {
    0x10, 0x0F, 0x04, 0x16, 0x02, 0x17, 0xFF,
};

static u8 D_us_801811E8[] = {
    0x01, 0x17, 0x01, 0x18, 0x01, 0x19, 0x00,
};

static u8 D_us_801811F0[] = {
    0x04, 0x17, 0x04, 0x1A, 0x04, 0x1B, 0x06,
    0x1C, 0x10, 0x1D, 0x08, 0x15, 0xFF,
};

static u8 D_us_80181200[] = {
    0x0A, 0x1E, 0x01, 0x1F, 0x01, 0x20, 0x01, 0x21, 0x01, 0x22, 0x01,
    0x1E, 0x01, 0x23, 0x01, 0x24, 0x01, 0x25, 0x01, 0x26, 0x01, 0x1E,
    0x01, 0x27, 0x01, 0x28, 0x01, 0x29, 0x01, 0x2A, 0x01, 0x1E, 0x01,
    0x2B, 0x01, 0x2C, 0x01, 0x2D, 0x01, 0x2E, 0x00,
};

static u8 D_us_8018122C[] = {
    0x18, 0x04, 0x08, 0x2F, 0x01, 0x0A, 0x01, 0x30, 0x01, 0x0A, 0xFF,
};

static u8 D_us_80181238[] = {
    0x08, 0x09, 0x08, 0x2F, 0xFF,
};

static u8 D_us_80181240[] = {
    0x10, 0x0F, 0x08, 0x0E, 0x20, 0x31, 0x02, 0x32, 0x02, 0x33, 0xFF,
};

static u8 D_us_8018124C[] = {
    0x08, 0x34, 0x08, 0x35, 0x08, 0x0E, 0xFF,
};

static u8 D_us_80181254[] = {
    0x04, 0x36, 0x04, 0x37, 0x04, 0x38, 0x04, 0x39,
    0x04, 0x3A, 0x04, 0x38, 0x00, 0x00, 0x00, 0x00,
};

static u8 D_us_80181264[] = {
    0x01, 0x35, 0x03, 0x31, 0x02, 0x34, 0x01,
    0x32, 0x01, 0x33, 0x18, 0x3C, 0xFF,
};

static u8 D_us_80181274[] = {
    0x04, 0x33, 0x18, 0x3C, 0xFF,
};

static FrameProperty D_us_8018127C[] = {
    {0x00, 0x00, 0x00, 0x00}, {0x00, 0x08, 0x04, 0x17},
    {0x00, 0x0C, 0x04, 0x13}, {0x00, 0x0D, 0x04, 0x12},
    {0x00, 0x07, 0x04, 0x12}, {0x00, 0x04, 0x04, 0x13},
    {0x00, 0x07, 0x04, 0x17}, {0x00, 0x05, 0x04, 0x13},
    {0x00, 0x00, 0x08, 0x08}, {0xFF, 0x01, 0x08, 0x08},
    {0x02, 0x03, 0x04, 0x13}, {0x00, 0x00, 0x04, 0x06},
    {0x00, 0x00, 0x0E, 0x02}, {0xC0, 0xB8, 0x00, 0x00},
    {0xF8, 0xF8, 0x00, 0x00},
};

static u8 D_us_801812B8[] = {
    0, 1, 1, 1, 1, 2,  3, 1, 4, 1, 1,  1,  1,  1,  5,  6,  7,  7,  7,  7,  7, 7,
    7, 7, 7, 7, 7, 7,  7, 7, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  9,  8,  8, 8,
    8, 8, 8, 1, 1, 10, 7, 7, 7, 5, 11, 11, 11, 11, 11, 12, 10, 13, 13, 14,
};

static u8 __unused[] UNUSED = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
    1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1,
};

#ifdef VERSION_PSP
extern s32 E_ID(EXPLODE_PUFF_OPAQUE);
extern s32 E_ID(KARASUMAN_FEATHER_ATTACK);
extern s32 E_ID(KARASUMAN_ORB_ATTACK);
extern s32 E_ID(KARASUMAN_RAVEN_ATTACK);
extern s32 E_ID(KARASUMAN_FEATHER);
extern s32 E_ID(KARASUMAN_RAVEN_ABSORB);
#endif

void EntityKarasuman(Entity* self) {
    Entity* entity;
    s32 i;
    s32 offsetX;
    s32 offsetY;
    s8* frameProperty;

    if (self->hitFlags & 3 && self->step & 1) {
        SetStep(14);
    }
    if (self->flags & FLAG_DEAD && self->step < 16) {
        SetStep(16);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitKarasuman);
        self->flags &= ~(FLAG_UNK_800 | FLAG_UNK_400);
        self->animCurFrame = 1;
        // fallthrough

    case 1:
        if (UnkCollisionFunc3(D_us_8018115C) & 1) {
            SetStep(2);
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            AnimateEntity(D_us_80181174, self);
            if (D_us_80181138 & 1) {
                SetSubStep(1);
            }
            break;
        case 1:
            if (AnimateEntity(D_us_8018117C, self) == 0) {
                SetStep(4);
            }
            break;
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_us_80181194, self) == 0) {
                self->velocityX = 0;
                self->velocityY = FIX(-4);
                SetSubStep(1);
            }
            break;
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (AnimateEntity(D_us_801811A0, self) == 0) {
                SetStep(3);
                if (self->ext.karasuman.flag2) {
                    SetStep(0xC);
                }
            }
            break;
        }
        break;

    case 3:
        if (!self->step_s) {
            self->ext.karasuman.timer = 48;
            self->velocityY = 0;
            self->step_s++;
        }
        AnimateEntity(D_us_801811A8, self);
        MoveEntity();
        if (GetSideToPlayer() & 1) {
            self->velocityX -= FIX(1.0 / 64.0);
            if (self->velocityX < FIX(-0.75)) {
                self->velocityX = FIX(-0.75);
            }
        } else {
            self->velocityX += FIX(1.0 / 64.0);
            if (self->velocityX > FIX(0.75)) {
                self->velocityX = FIX(0.75);
            }
        }
        if (!self->poseTimer && self->pose == 1) {
            PlaySfxPositional(SFX_UNK_NZ1_722);
        }

        if (!--self->ext.karasuman.timer) {
            if (self->ext.karasuman.flag0) {
                SetStep(8);
            } else {
                SetStep(6);
            }
            self->ext.karasuman.flag0 ^= 1;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_us_801811CC, self) == 0) {
                self->ext.karasuman.timer = 48;
                SetSubStep(1);
            }
            break;
        case 1:
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_BAT_ECHO_C);
                for (i = 0; i < 8; i++) {
                    entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(
                            E_ID(KARASUMAN_FEATHER_ATTACK), self, entity);
                        entity->posY.i.hi -= 28;
                    }
                }
            }
            if (!--self->ext.karasuman.timer) {
                self->step_s++;
            }
            break;
        case 2:
            if (AnimateEntity(D_us_801811D8, self) == 0) {
                SetStep(7);
                self->step_s = 2;
            }
            break;
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (AnimateEntity(D_us_801811B8, self) == 0) {
                SetSubStep(2);
            }
            break;
        case 2:
            if (UnkCollisionFunc3(D_us_8018115C) & 1) {
                self->step_s++;
            } else {
                self->velocityY -= FIX(0.09375);
            }
            break;
        case 3:
            if (AnimateEntity(D_us_801811C0, self) == 0) {
                SetStep(4);
                SetStep(0xA);
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            self->ext.karasuman.flag1 = 0;
            if (AnimateEntity(D_us_801811E0, self) == 0) {
                SetSubStep(1);
            }
            break;
        case 1:
            for (i = 0; i < 4; i++) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(KARASUMAN_ORB_ATTACK), self, entity);
                    entity->params = i;
                    entity->ext.karasuman.parent = self;
                    entity->zPriority = self->zPriority + 1;
                }
            }
            self->ext.karasuman.timer = 64;
            self->step_s++;
            // fallthrough
        case 2:
            AnimateEntity(D_us_801811E8, self);
            if (!(self->ext.karasuman.timer & 7)) {
                PlaySfxPositional(SFX_RAPID_SYNTH_BUBBLE_SHORT);
            }
            if (!--self->ext.karasuman.timer) {
                PlaySfxPositional(SFX_TELEPORT_BANG_A);
                self->ext.karasuman.flag1 = 1;
                self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
                self->scaleX = self->scaleY = 256;
                self->velocityY = FIX(-6.0);
                self->velocityX = 0;
                SetSubStep(3);
            }
            break;
        case 3:
            if (AnimateEntity(D_us_801811F0, self) == 0) {
                self->step_s++;
            }
            // fallthrough
        case 4:
            MoveEntity();
            self->velocityY -= self->velocityY / 8;
            if (self->scaleX > 224) {
                self->scaleX = self->scaleY -= 4;
            } else if (self->step_s == 4) {
                self->step_s++;
            }
            break;
        case 5:
            self->scaleX = self->scaleY += 8;
            if (self->scaleX > 256) {
                self->drawFlags = FLAG_DRAW_DEFAULT;
                SetStep(7);
            }
            break;
        }
        break;
    case 10:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_us_8018122C, self) == 0) {
                SetSubStep(1);
            }
            break;
        case 1:
            self->ext.karasuman.timer = 64;
            self->ext.karasuman.flag2 = 1;
            self->step_s++;
            // fallthrough
        case 2:
            if (!(self->ext.karasuman.timer & 3)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(KARASUMAN_RAVEN_ATTACK), self, entity);
                    entity->ext.karasuman.parent = self;
                    entity->params = 1;
                }
            }
            if (!(self->ext.karasuman.timer & 7)) {
                g_api.PlaySfx(SFX_WING_FLAP_A);
            }

            if (!--self->ext.karasuman.timer) {
                self->ext.karasuman.timer = 64;
                self->step_s++;
            }
            break;
        case 3:
            if (AnimateEntity(D_us_80181238, self) == 0) {
                SetStep(4);
            }
        }
        break;
    case 12:
        switch (self->step_s) {
        case 0:
            self->ext.karasuman.flag2 = 0;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            // fallthrough
        case 1:
            if (AnimateEntity(D_us_80181240, self) == 0) {
                self->ext.karasuman.timer = 96;
                if (self->facingLeft) {
                    self->velocityX = FIX(-2.0);
                } else {
                    self->velocityX = FIX(2.0);
                }
                self->velocityY = FIX(-2.0);
                self->step_s++;
            }
            break;
        case 2:
            if (self->ext.karasuman.timer > 0x48) {
                MoveEntity();
                self->velocityX -= self->velocityX / 8;
                self->velocityY -= self->velocityY / 8;
            }
            if (!(self->ext.karasuman.timer & 7)) {
                g_api.PlaySfx(SFX_WING_FLAP_A);
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(KARASUMAN_RAVEN_ATTACK), self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->ext.karasuman.parent = self;
                }
            }

            if (!--self->ext.karasuman.timer) {
                SetSubStep(3);
            }
            break;
        case 3:
            if (AnimateEntity(D_us_8018124C, self) == 0) {
                SetStep(3);
            }
            break;
        }
        break;
    case 14:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(-4.0);
            } else {
                self->velocityX = FIX(4.0);
            }
            self->velocityY = FIX(-2.0);
            for (i = 0; i < 8; i++) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(KARASUMAN_FEATHER), self, entity);
                    if (Random() & 1) {
                        entity->zPriority = self->zPriority + 1;
                    } else {
                        entity->zPriority = self->zPriority - 1;
                    }
                }
            };
            self->step_s++;
        }
        MoveEntity();

        self->velocityX -= self->velocityX / 16;
        self->velocityY -= self->velocityY / 16;

        if (AnimateEntity(D_us_80181264, self) == 0) {
            SetStep(7);
        }
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            D_us_80181138 |= 2;
            self->hitboxState = 0;
            for (i = 0; i < 32; i++) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(KARASUMAN_FEATHER), self, entity);
                    if (Random() & 1) {
                        entity->zPriority = self->zPriority + 1;
                    } else {
                        entity->zPriority = self->zPriority - 1;
                    }
                }
            }
            PlaySfxPositional(SFX_UNK_NZ1_723);
            self->step_s++;
            // fallthrough
        case 1:
            if ((AnimateEntity(D_us_80181274, self) == 0) &&
                (UnkCollisionFunc3(D_us_8018115C) & 1)) {
                self->step_s++;
            }
            break;
        case 2:
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(
                    E_ID(KARASUMAN_RAVEN_ABSORB), self, entity);
                entity->params = 1;
                entity->zPriority = self->zPriority + 1;
            }
            self->ext.karasuman.timer = 64;
            self->step_s++;
            // fallthrough
        case 3:
            entity = AllocEntity(&g_Entities[160], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(
                    E_ID(KARASUMAN_RAVEN_ABSORB), self, entity);
                entity->facingLeft = Random() & 1;
                entity->params = 0;
                entity->zPriority = self->zPriority + 1;
            }

            if (!(self->ext.karasuman.timer & 7)) {
                g_api.PlaySfx(SFX_UNK_NZ1_721);
            }

            if (!--self->ext.karasuman.timer) {
                self->palette = PAL_FLAG(0x2E4);
                self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
                self->drawFlags |= FLAG_DRAW_OPACITY;
                self->opacity = 0x80;
                self->ext.karasuman.timer = 64;
                self->step_s++;
            }
            break;
        case 4:
            for (i = 0; i < 4; i++) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(EXPLODE_PUFF_OPAQUE), self, entity);
                    entity->facingLeft = Random() & 1;
                    entity->zPriority = self->zPriority + 1;
                    entity->posY.i.hi += 32;
                    entity->params = 3;
                }
            }
            if (self->opacity) {
                self->opacity -= 2;
            }
            if (!(self->ext.karasuman.timer & 0xF)) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_A);
            }

            if (!--self->ext.karasuman.timer) {
                self->animCurFrame = 0;
                D_us_80181138 |= 4;
                self->step++;
            }
            break;
        case 5:
            break;
        }
        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
        break;
    }

    frameProperty = (s8*)D_us_8018127C;
    frameProperty += D_us_801812B8[self->animCurFrame] * sizeof(FrameProperty);
    self->hitboxOffX = *frameProperty++;
    self->hitboxOffY = *frameProperty++;
    self->hitboxWidth = *frameProperty++;
    self->hitboxHeight = *frameProperty++;

    offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (self->velocityX < 0) {
        if (offsetX < 36) {
            self->posX.i.hi = 36 - g_Tilemap.scrollX.i.hi;
        }
    } else if (offsetX > 0xDC) {
        self->posX.i.hi = 0xDC - g_Tilemap.scrollX.i.hi;
    }
#ifndef VERSION_PSP
    if (self->velocityY < 0) {
        if (offsetY < 80) {
            self->posY.i.hi = 80 - g_Tilemap.scrollY.i.hi;
        }
    }
#endif
}

extern EInit g_EInitKarasumanFeatherAttack;

void EntityKarasumanFeatherAttack(Entity* self) {
    Entity* entity;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitKarasumanFeatherAttack);
        self->animCurFrame = 59;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        if (Random() & 1) {
            self->facingLeft = true;
        }

        angle = (Random() * 4) - FLT(0.125);
        self->rotate = angle;
        angle = self->rotate;
        if (!self->facingLeft) {
            angle = FLT(0.5) - angle;
        }
        self->velocityX = 96 * rcos(angle);
        self->velocityY = -96 * rsin(angle);
        self->posX.i.hi += FLT_TO_I(32 * rcos(angle));
        self->posY.i.hi += FLT_TO_I(-32 * rsin(angle));
        // fallthrough
    case 1:
        MoveEntity();
        if (self->flags & FLAG_DEAD) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 1;
            }
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit g_EInitKarasumanOrbAttack;

void EntityKarasumanOrbAttack(Entity* self) {
    Entity* entity;
    s16 angle;
    s16 angleBetweenEntities;

#ifndef VERSION_PSP
    if (D_us_80181138 & 2) {
        DestroyEntity(self);
        return;
    }
#endif

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitKarasumanOrbAttack);
        self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        self->scaleX = self->scaleY = 0;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        // fallthrough

    case 1:
        self->scaleX = self->scaleY += 6;
        if (self->scaleX > 0xA0) {
            self->step++;
        }
        // fallthrough

    case 2:
        AnimateEntity(D_us_80181200, self);
        entity = self->ext.karasuman.parent;
        if (entity->ext.karasuman.flag1) {
            self->step++;
        }
        break;

    case 3:
        angle = (self->params << 9) + ROT(22.5);
        self->velocityX = rcos(angle) << 6;
        self->velocityY = rsin(angle) << 6;
        self->ext.karasuman.angle = angle;
        self->ext.karasuman.timer = 128;
        self->step++;
        // fallthrough

    case 4:
        entity = &PLAYER;
        angle = GetAngleBetweenEntities(self, entity);
        angle = GetNormalizedAngle(24, self->ext.karasuman.angle, angle);
        self->velocityX = 64 * rcos(angle);
        self->velocityY = 64 * rsin(angle);
        self->ext.karasuman.angle = angle;
        if (self->hitFlags & 0x80) {
            self->ext.karasuman.timer = 16;
            self->step = 6;
        }

        if (!--self->ext.karasuman.timer) {
            self->step++;
        }
        // fallthrough

    case 5:
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        AnimateEntity(D_us_80181200, self);
        MoveEntity();
        break;

    case 6:
        AnimateEntity(D_us_80181200, self);
        entity = &PLAYER;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        if (!--self->ext.karasuman.timer) {
            self->step = 5;
        }
        break;
    }
}

extern EInit g_EInitKarasumanRavenAttack;

void EntityKarasumanRavenAttack(Entity* self) {
    Entity* entity;
    s32 offsetX;
    s32 offsetY;
    s32 opacity;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitKarasumanRavenAttack);
        if (self->params) {
            self->hitboxState = 0;
            self->step = 8;
            return;
        }
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        angle = ((Random() & 0x1F) * 0x10) + ROT(22.5);
        self->rotate = -angle;
        if (!self->facingLeft) {
            angle = FLT(0.5) - angle;
        }
        self->velocityX = rcos(angle) * 0x38;
        self->velocityY = rsin(angle) * 0x38;
        // fallthrough

    case 1:
        MoveEntity();
        AnimateEntity(D_us_80181254, self);
        entity = &PLAYER;
        if (entity->posY.i.hi < self->posY.i.hi) {
            self->velocityY -= FIX(1.0 / 32.0);
        }
        if (self->flags & FLAG_DEAD) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 1;
            }
            DestroyEntity(self);
        }
        break;

    case 8:
        self->palette = PAL_FLAG(0x15F);
        self->drawFlags = FLAG_DRAW_OPACITY;
        self->opacity = 0;
        self->drawMode = DRAW_UNK_40 | DRAW_TPAGE;
        entity = self->ext.karasuman.parent;
        angle = Random() * 16;
        self->posX.i.hi += FLT_TO_I(128 * rcos(angle));
        self->posY.i.hi += FLT_TO_I(128 * rsin(angle));
        self->step++;
        // fallthrough

    case 9:
        if (self->opacity < 32) {
            self->opacity += 2;
        } else {
            self->step++;
        }
        break;

    case 10:
        entity = self->ext.karasuman.parent;
        if (entity->entityId != E_ID(KARASUMAN)) {
            DestroyEntity(self);
            return;
        }
        angle = GetAngleBetweenEntities(self, entity);
        angle = GetNormalizedAngle(64, self->ext.karasuman.angle, angle);
        self->velocityX = 64 * rcos(angle);
        self->velocityY = 64 * rsin(angle);
        self->ext.karasuman.angle = angle;
        if (self->velocityX > 0) {
            self->facingLeft = 1;
        } else {
            self->facingLeft = 0;
        }
        MoveEntity();
        AnimateEntity(D_us_80181254, self);
        offsetX = entity->posX.i.hi - self->posX.i.hi;
        offsetY = entity->posY.i.hi - self->posY.i.hi;
        opacity = SquareRoot0(SQ(offsetX) + SQ(offsetY));

        self->opacity = opacity / 4;
        if (opacity < 16) {
            DestroyEntity(self);
            return;
        }

        if (!entity->ext.karasuman.flag2) {
            self->step++;
        }
        break;

    case 11:
        self->opacity -= 8;
        if (self->opacity > 240) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit g_EInitKarasumanFeather;

void EntityKarasumanFeather(Entity* self) {
    s16 angle;
    s32 scale;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitKarasumanFeather);
        self->animCurFrame = 63;
        self->drawFlags = FLAG_DRAW_ROTATE;
        self->facingLeft = Random() & 1;
        scale = (Random() & 0x1F) + 0x10;
        angle = (Random() * 6) + FLT(9.0 / 16.0);

        self->velocityX = scale * rcos(angle);
        self->velocityY = scale * rsin(angle);
        self->posX.val += 16 * self->velocityX;
        self->posY.val += 16 * self->velocityY;

        self->rotate = angle;
        self->ext.karasuman.timer = 64;
        // fallthrough

    case 1:
        MoveEntity();
        self->velocityX -= self->velocityX / 16;
        self->velocityY -= self->velocityY / 16;

        self->rotate += 64;
        if (!--self->ext.karasuman.timer) {
            self->velocityX = 0;
            self->step++;
        }
        break;

    case 2:
        MoveEntity();
        self->rotate += 32;
        if (self->velocityY < FIX(1.5)) {
            self->velocityY += FIX(1.0 / 32.0);
        }
        break;
    }
}

void EntityKarasumanRavenAbsorb(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitKarasumanRavenAttack);
        self->drawMode = DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_ROTATE;
        self->hitboxState = 0;

        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_UNK_2000;
        if (self->params) {
            self->animCurFrame = 0;
            self->step = 4;
            break;
        }
        angle = ROT(-22.5) - ((Random() & 0x3F) * 16);
        self->rotate = -angle;
        if (!self->facingLeft) {
            angle = FLT(0.5) - angle;
        }
        self->velocityX = 56 * rcos(angle);
        self->velocityY = 56 * rsin(angle);
        // fallthrough

    case 1:
        MoveEntity();
        AnimateEntity(D_us_80181254, self);
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            self->ext.karasuman.timer = 96;
            self->step_s++;
            // fallthrough

        case 1:
            if (self->ext.karasuman.timer & 1) {
                self->animCurFrame = 61;
            } else {
                self->animCurFrame = 0;
            }

            if (!--self->ext.karasuman.timer) {
                DestroyEntity(self);
            }
            break;
        }
        break;
    }
}
