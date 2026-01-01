// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rare.h"

extern EInit D_us_801807CC;
extern EInit D_us_801807D8;
extern EInit g_EInitWerewolfRARE;
extern EInit g_EInitInteractable;
extern s16* sprites_rare_4[];

static s16 D_us_80181CFC[] = {0, 27, 4, 0};
static s16 D_us_80181D04[] = {0, 27, 0, 4, 4, -4, -8, 0};

static u8 D_us_80181D14[] = {
    0x06, 0x01, 0x06, 0x02, 0x06, 0x03, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00};
static u8 D_us_80181D20[] = {
    0x04, 0x04, 0x04, 0x05, 0x06, 0x06, 0x04, 0x05,
    0x06, 0x04, 0x10, 0x02, 0x02, 0x04, 0x00, 0x00,
};
static u8 D_us_80181D30[] = {
    0x08, 0x0B, 0x04, 0x0D, 0x06, 0x0F, 0x04, 0x0D, 0x06, 0x0F, 0x07,
    0x0D, 0x08, 0x0B, 0x03, 0x0C, 0x02, 0x0E, 0x02, 0x10, 0x01, 0x11,
    0x01, 0x12, 0x01, 0x13, 0x02, 0x14, 0x02, 0x0B, 0xFF, 0x00,
};
static u8 D_us_80181D50[] = {
    0x01, 0x01, 0x04, 0x24, 0x06, 0x25, 0xFF, 0x00,
};
static u8 D_us_80181D58[] = {
    0x08, 0x1A, 0x06, 0x1B, 0x07, 0x1C, 0x06, 0x1D,
    0x09, 0x1E, 0x0C, 0x1F, 0xFF, 0x00, 0x00, 0x00,
};
static u8 D_us_80181D68[] = {
    0x03, 0x0A, 0x03, 0x22, 0x03, 0x21, 0x11, 0x20, 0x09, 0x21,
    0x09, 0x22, 0x09, 0x23, 0x05, 0x0A, 0xFF, 0x00, 0x00, 0x00,
};
static u8 D_us_80181D7C[] = {
    0x0C, 0x02, 0x06, 0x24, 0x01, 0x3F, 0x01, 0x25, 0x01, 0x3F,
    0x01, 0x25, 0x01, 0x3F, 0x01, 0x25, 0x01, 0x3F, 0x01, 0x25,
    0x01, 0x3F, 0x01, 0x25, 0xFF, 0x00, 0x00, 0x00,
};
static u8 D_us_80181D98[] = {
    0x03, 0x26, 0x03, 0x27, 0x02, 0x28, 0x08, 0x29, 0x04, 0x28, 0x04, 0x27,
    0x03, 0x2A, 0x04, 0x2B, 0x05, 0x2C, 0x04, 0x2D, 0x1B, 0x0A, 0xFF, 0x00,
};
static u8 D_us_80181DB0[] = {
    0x0F, 0x0A, 0x05, 0x25, 0x05, 0x24, 0x04, 0x0B, 0x2A, 0x2E, 0xFF, 0x00,
};
static u8 D_us_80181DBC[] = {
    0x07, 0x2E, 0x03, 0x2F, 0x05, 0x2E, 0x06, 0x2F, 0x0A, 0x30,
    0x0A, 0x35, 0x04, 0x31, 0x18, 0x35, 0x09, 0x31, 0x08, 0x32,
    0x06, 0x33, 0x4D, 0x34, 0xFF, 0x00, 0x00, 0x00,
};
static u8 D_us_80181DD8[] = {
    0x04, 0x0C, 0x02, 0x0B, 0x02, 0x0A, 0x01, 0x09, 0xFF, 0x00, 0x00, 0x00,
};

static u8 unused[] = {
    0x03, 0x01, 0x03, 0x02, 0x03, 0x03, 0x03, 0x04, 0x03, 0x05,
    0x03, 0x06, 0x03, 0x07, 0x03, 0x08, 0x03, 0x09, 0x03, 0x0A,
    0x03, 0x0B, 0x03, 0x0C, 0x03, 0x0D, 0xFF, 0x00,
};

static s8 D_us_80181E00[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0A, 0x12, 0x00, 0x06, 0x07, 0x12,
    0x00, 0x06, 0x06, 0x13, 0x00, 0x05, 0x06, 0x14, 0xFF, 0x04, 0x05, 0x14,
    0x00, 0x03, 0x04, 0x15, 0x00, 0xFF, 0x07, 0x10, 0x02, 0x0C, 0x09, 0x0C,
    0x01, 0x07, 0x08, 0x11, 0x00, 0x08, 0x08, 0x11, 0xFF, 0x08, 0x08, 0x11,
    0x00, 0x01, 0x07, 0x08, 0x00, 0x03, 0x0D, 0x0C, 0x00, 0x02, 0x0C, 0x0F,
    0x00, 0x05, 0x08, 0x16, 0x06, 0x08, 0x0A, 0x10, 0x07, 0x0E, 0x07, 0x11,
    0xF9, 0x0D, 0x07, 0x10, 0xFC, 0x02, 0x0A, 0x0B, 0xFC, 0x04, 0x09, 0x0B,
    0x0A, 0x0F, 0x0A, 0x0D, 0x07, 0x0E, 0x07, 0x0C, 0x05, 0x0D, 0x09, 0x0C,
    0x01, 0x0C, 0x09, 0x0C, 0x03, 0x06, 0x07, 0x12, 0x02, 0x0B, 0x07, 0x0F,
    0x02, 0x01, 0x0B, 0x0E, 0x01, 0xFC, 0x0E, 0x08, 0x06, 0x00, 0x12, 0x0A,
    0x05, 0xFB, 0x13, 0x0A, 0x05, 0x00, 0x0D, 0x07, 0x00, 0x00, 0x08, 0x09,
    0xFF, 0x02, 0x06, 0x0D, 0xF0, 0xEB, 0x00, 0x00, 0xEF, 0xF6, 0x00, 0x00,
    0xF0, 0xF1, 0x00, 0x00};
static u8 D_us_80181E94[] = {
    0x00, 0x01, 0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x09, 0x09, 0x09, 0x0A, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0C,
    0x0C, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
    0x20, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x23,
    0x23, 0x23, 0x23, 0x23, 0x24, 0x24, 0x24, 0x24, 0x1A};
static s8 D_us_80181ED4[] = {
    0x00, 0x00, 0x00, 0x00, 0xF0, 0xEB, 0x00, 0x00, 0xED, 0xFD, 0x07, 0x04,
    0xED, 0xFD, 0x06, 0x09, 0xEC, 0xFD, 0x0A, 0x07, 0xE4, 0xFD, 0x0C, 0x04,
    0xE0, 0xFD, 0x12, 0x04, 0xD0, 0xFD, 0x07, 0x04, 0x19, 0x08, 0x06, 0x09,
    0x14, 0xFA, 0x08, 0x08, 0xE7, 0x0E, 0x04, 0x07, 0x0A, 0x16, 0x04, 0x05,
    0x0A, 0x17, 0x04, 0x06, 0x01, 0x17, 0x18, 0x04, 0xF8, 0x17, 0x15, 0x04,
    0xEF, 0xF6, 0x00, 0x00, 0xF0, 0xF1, 0x00, 0x00};
static u8 D_us_80181F18[] = {
    0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,
    0x0E, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x0F,
    0x0F, 0x0F, 0x0F, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x01};

void func_us_801B7290(Entity* self) {
    Entity* entity; // s0
    s8* ptr;        // s1
    s32 var_s2;     // s2

    if (self->flags & FLAG_DEAD && self->step < 0x18) {
        SetStep(0x18);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitWerewolfRARE);
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_CORNER_GUARD_ATTACK, entity);
        // fallthrough
    case 1:
        if (UnkCollisionFunc3(D_us_80181D04) & 1) {
            SetStep(2);
        }
        break;
    case 0x2:
        AnimateEntity(D_us_80181D14, self);
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(3);
        }
        break;
    case 3:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (!self->ext.werewolf.unk82) {
                self->ext.werewolf.unk82 = 0x20;
            }
            self->step_s++;
        }
        if (!AnimateEntity(&D_us_80181D14, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }

        if (self->ext.werewolf.unk82) {
            self->ext.werewolf.unk82--;
        } else {
            SetStep(5);
        }

        entity = &PLAYER;
        var_s2 = entity->velocityX;
        if (self->facingLeft) {
            var_s2 = -var_s2;
        }
        if (self->facingLeft == entity->facingLeft &&
            GetDistanceToPlayerX() < 0x38 && var_s2 > 0) {
            SetStep(6);
        }
        break;
    case 5:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.werewolf.unk84 = false;
            self->ext.werewolf.unk80 = 0x20;
            self->step_s++;
        }

        if (!AnimateEntity(&D_us_80181D20, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }

        if (self->facingLeft ^ self->ext.werewolf.unk84) {
            self->velocityX = FIX(1.0);
        } else {
            self->velocityX = FIX(-1.0);
        }

        UnkCollisionFunc2(D_us_80181CFC);
        if (GetDistanceToPlayerX() > 0x70) {
            self->ext.werewolf.unk84 = false;
        }

        if (GetDistanceToPlayerX() < 0x30) {
            self->ext.werewolf.unk84 = true;
        }

        if (!--self->ext.werewolf.unk80) {
            SetStep(4);
        }
        break;
    case 4:
        if (!AnimateEntity(&D_us_80181D14, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }

        switch (self->step_s) {
        case 0:
            self->ext.werewolf.unk80 = 0x20;
            self->step_s++;
            break;
        case 1:
            if (!--self->ext.werewolf.unk80) {
                self->step_s++;
            }
            break;
        case 2:
            entity = &PLAYER;
            if (self->facingLeft == entity->facingLeft) {
                if (GetDistanceToPlayerX() < 0x40) {
                    if (Random() & 3) {
                        SetStep(10);
                    } else {
                        SetStep(6);
                    }
                } else if (Random() & 1) {
                    SetStep(12);
                } else {
                    SetStep(8);
                }
            } else if (GetDistanceToPlayerX() < 0x38) {
                if (Random() & 1) {
                    SetStep(10);
                } else {
                    SetStep(8);
                }
            } else if (Random() & 1) {
                SetStep(12);
            } else {
                SetStep(14);
            }
            break;
        }
        break;
    case 6:
        if (!AnimateEntity(&D_us_80181D30, self)) {
            SetStep(3);
        }

        if (!self->poseTimer && self->pose == 8) {
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
        }

        break;
    case 8:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(&D_us_80181D50, self)) {
                self->animCurFrame = 0x2D;
                self->velocityX = FIX(-2.0);
                if (self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
                self->velocityY = FIX(-2.0);
                SetSubStep(1);
            }
            break;
        case 1:
            if (UnkCollisionFunc3(&D_us_80181D04) & 1) {
                self->step_s++;
            }
            break;
        case 2:
            if (!AnimateEntity(&D_us_80181D58, self)) {
                SetStep(3);
            }

            if (!self->poseTimer && self->pose == 4) {
                PlaySfxPositional(SFX_OUIJA_TABLE_DEATH);
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_1C, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->posY.i.hi -= 0x10;
                }
            }
            break;
        }
        break;
    case 10:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
        }

        UnkCollisionFunc2(D_us_80181CFC);
        if (!AnimateEntity(&D_us_80181D68, self)) {
            SetStep(3);
        }

        self->velocityX -= self->velocityX / 16;
        if (!self->poseTimer && self->pose == 3) {
            PlaySfxPositional(SFX_SCRAPE_B);
            if (self->facingLeft) {
                self->velocityX = FIX(4.0);
            } else {
                self->velocityX = FIX(-4.0);
            }
        }
        break;
    case 12:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(&D_us_80181D7C, self)) {
                SetSubStep(2);
            }
            break;
        case 2:
            if (self->facingLeft) {
                self->velocityX = FIX(6.0);
            } else {
                self->velocityX = FIX(-6.0);
            }

            PlaySfxPositional(SFX_ARROW_SHOT_A);
            self->step_s++;
            // fallthrough
        case 3:
            UnkCollisionFunc2(D_us_80181CFC);
            self->velocityX -= self->velocityX / 32;
            if (!AnimateEntity(&D_us_80181D98, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 14:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(4.5);
            } else {
                self->velocityX = FIX(-4.5);
            }
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (!AnimateEntity(&D_us_80181DD8, self)) {
                self->ext.werewolf.unk80 = 0x20;
                self->animCurFrame = 0x15;
                self->drawFlags |= FLAG_DRAW_ROTATE;
                self->step_s++;
                self->velocityY = FIX(-4.0);
                self->step_s = 3;
            }
            break;
        case 2:
            UnkCollisionFunc2(D_us_80181CFC);
            self->rotate -= 0x100;
            if (!(g_Timer & 8)) {
                PlaySfxPositional(SFX_WEREWOLF_SPIN_ATTACK);
            }

            if (!(self->ext.werewolf.unk80 & 3)) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_1D, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                    entity->params = self->animCurFrame;
                }
            }

            if (!--self->ext.werewolf.unk80) {
                self->drawFlags = FLAG_DRAW_DEFAULT;
                self->animCurFrame = 0xA;
                self->ext.werewolf.unk80 = 0x10;
                self->step_s = 4;
            }
            break;
        case 3:
            self->rotate -= 0x100;
            if (!(g_Timer & 8)) {
                PlaySfxPositional(SFX_WEREWOLF_SPIN_ATTACK);
            }

            if (!(g_Timer & 3)) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_1D, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                    entity->params = self->animCurFrame;
                }
            }

            if (UnkCollisionFunc3(D_us_80181D04) & 1) {
                self->drawFlags = FLAG_DRAW_DEFAULT;
                self->animCurFrame = 0xA;
                self->ext.werewolf.unk80 = 0x10;
                self->step_s = 4;
            }
            break;
        case 4:
            if (!--self->ext.werewolf.unk80) {
                SetStep(3);
            }
            break;
        }
        break;
    case 24:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->velocityX = FIX(2.0);
            if (self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            self->velocityY = FIX(-2.0);
            self->rotate = 0;
            self->animCurFrame = 7;
            self->step_s++;
            // fallthrough
        case 1:
            if (UnkCollisionFunc3(D_us_80181D04) & 1) {
                self->step_s++;
            }
            break;
        case 2:
            if (!AnimateEntity(&D_us_80181DB0, self)) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_1E, self, entity);
                    entity->posY.i.hi += 0x1B;
                    entity->zPriority = self->zPriority;
                }
                SetSubStep(3);
            }
            break;
        case 3:
            if (!AnimateEntity(&D_us_80181DBC, self)) {
                SetSubStep(4);
            }
            break;
        case 4:
            self->animCurFrame = 0;
            DestroyEntity(self);
            return;
        }
        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
    }

    ptr = D_us_80181E00;
    ptr += D_us_80181E94[self->animCurFrame] * 4;
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;
}

void EntityCornerGuardAttack(Entity* self) {
    s32 animCurFrame;
    s8* hitboxPtr;
    Entity* werewolf;

    if (!self->step) {
        InitializeEntity(D_us_801807CC);
        self->animCurFrame = 0;
    }
    werewolf = self - 1;
    if (werewolf->entityId != 0x1A) {
        DestroyEntity(self);
        return;
    }
    animCurFrame = werewolf->animCurFrame;
    self->facingLeft = werewolf->facingLeft;
    self->posX.val = werewolf->posX.val;
    self->posY.val = werewolf->posY.val;
    hitboxPtr = D_us_80181ED4;
    hitboxPtr += D_us_80181F18[animCurFrame] * 4;
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}

void func_us_801B7FF8(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801807D8);
        self->animCurFrame = 0x39;
        if (self->facingLeft) {
            self->velocityX = FIX(4.5);
        } else {
            self->velocityX = FIX(-4.5);
        }
        self->velocityY = 0;
        // fallthrough
    case 1:
        MoveEntity();
        self->velocityY -= 0x1400;
        angle = ratan2(-self->velocityY, abs(self->velocityX));
        self->animCurFrame = 0x36;
        if (angle > 0x80) {
            self->animCurFrame = 0x37;
        }
        if (angle > 0x140) {
            self->animCurFrame = 0x38;
        }
        if (angle > 0x180) {
            self->animCurFrame = 0x39;
        }
        break;
    }
}

void func_us_801B80E8(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitWerewolfRARE);
        self->palette = g_EInitWerewolfRARE[3] + PAL_FLAG(9);
        self->hitboxState = 0;
        self->flags |= FLAG_UNK_00200000 | FLAG_UNK_2000;
        self->drawFlags = FLAG_DRAW_OPACITY | FLAG_DRAW_ROTATE;
        self->animCurFrame = (s16)self->params;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->opacity = 0x60;
    }
    self->ext.werewolf.unk80++;
    if ((!self->ext.werewolf.unk80) & 1) {
        self->animCurFrame = 0;
    } else {
        self->animCurFrame = self->params;
    }

    self->opacity -= 8;
    if (!self->opacity) {
        DestroyEntity(self);
    }
}

static SVECTOR D_us_80181F58[] = {
    {.vx = -16, .vy = -24, .vz = -18, .pad = 0},
    {.vx = 16, .vy = -24, .vz = -18, .pad = 0},
    {.vx = -16, .vy = 24, .vz = -18, .pad = 0},
    {.vx = 16, .vy = 24, .vz = -18, .pad = 0}};

Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index);
void func_us_801B81CC(Entity* self) {
    long sp6C;
    SVECTOR svecTwo;
    VECTOR vecTwo;
    MATRIX matrix;

    Primitive* prim; // s0
    s16* ptr;
    s32 var_s2;      // s2
    s32 i;           // s3
    SVECTOR* vector; // s4
    s32 var_s5;      // s5
    s32 primIndex;   // s6

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x80);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.werewolf.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0x17;
            prim->clut = 0x254;
            // BUG: this is set twice
            prim->clut = 0x2E4;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.werewolf.unk80 = 0x100;
    case 1:
        if (!(self->ext.werewolf.unk80 & 0x1F)) {
            PlaySfxPositional(SFX_FIREBALL_SHOT_B);
        }

        if (!--self->ext.werewolf.unk80) {
            DestroyEntity(self);
            return;
        }

        if (!(self->ext.werewolf.unk80 & 3)) {
            self->ext.werewolf.unk9C -= 0x20;
            var_s5 = self->ext.werewolf.unk80;
            if (var_s5 > 0x60) {
                var_s5 = 0x40;
            }

            for (i = 0; i < 3; i++) {
                prim = self->ext.werewolf.prim;
                prim = FindFirstUnkPrim2(prim, 2);
                if (prim != NULL) {
                    UnkPolyFunc2(prim);
                    prim->next->x2 = 0;
                    prim->next->y2 = 0;
                    prim->next->x1 =
                        self->ext.werewolf.unk9C + (i * 0x555) + Random();
                    prim->next->y1 = 0;
                    PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) =
                        PGREY(prim, 3) = var_s5;

                    prim = prim->next;
                    prim->drawMode = DRAW_HIDE;
                }
            }
        }

        SetGeomScreen(0x200);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        prim = self->ext.werewolf.prim;
        vector = D_us_80181F58;
        var_s2 = self->posY.i.hi + 8;
        while (prim != NULL) {
            if (prim->p3 == 8) {
                vecTwo.vx = 0;
                vecTwo.vy = prim->next->y1;
                vecTwo.vz = 0x200;
                TransMatrix(&matrix, &vecTwo);
                SetTransMatrix(&matrix);
                svecTwo.vx = 0;
                svecTwo.vy = prim->next->x1;
                svecTwo.vz = 0x180;
                RotMatrix(&svecTwo, &matrix);
                SetRotMatrix(&matrix);
                gte_ldv3c(vector);
                gte_rtpt();
                gte_stsxy3_gt3(prim);
                gte_ldv0(&vector[3]);
                gte_rtps();
                gte_stsxy((long*)&prim->x3);
                gte_avsz4();
#ifdef VERSION_US
                gte_stszotz(sp6C);
#else
                gte_stszotz(&sp6C);
#endif

                if (sp6C > 0x80) {
                    prim->priority = self->zPriority - 1;
                } else {
                    prim->priority = self->zPriority + 1;
                }

                if (var_s2 < prim->y2) {
                    prim->y2 = var_s2;
                }

                if (var_s2 < prim->y3) {
                    prim->y3 = var_s2;
                }
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
            }
            prim = prim->next;
        }

        prim = self->ext.werewolf.prim;
        while (prim != NULL) {
            if (prim->p3 == 8) {
                prim->next->y1 -= 3;
                prim->next->x1 += 0x30;
                prim->r0 -= 1;
                if (!prim->r0) {
                    UnkPolyFunc0(prim);
                    continue;
                }

                prim->g0 = prim->b0 = prim->r0;
                PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3) = prim->r0;
                if (!prim->next->y2) {
                    prim->next->x2++;
                    if (prim->next->x2 > 0xD) {
                        UnkPolyFunc0(prim);
                        continue;
                    }

                    ptr = sprites_rare_4[prim->next->x2];
                    ptr += 8;
                    prim->u0 = prim->u2 = *ptr++;
                    prim->v0 = prim->v1 = *ptr++;
                    prim->u1 = prim->u3 = *ptr++;
                    prim->v2 = prim->v3 = *ptr++;
                    prim->next->y2 = 2;
                } else {
                    prim->next->y2--;
                }
            }
            prim = prim->next;
        }
        break;
    }
}
