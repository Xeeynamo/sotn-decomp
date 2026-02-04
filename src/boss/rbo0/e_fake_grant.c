// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo0.h"

static bool func_us_80196838(s16* self) {
    s32 posY;

    self++;

    posY = g_CurrentEntity->posY.i.hi + self[0] + g_Tilemap.scrollY.i.hi;
    posY = 48 - posY;
    if (posY >= 0) {
        g_CurrentEntity->posY.i.hi += posY;
        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;
        return true;
    }
    return false;
}

extern EInit D_us_801804B8;
extern s8 D_us_801806B8[];
extern u8 D_us_80180718[];
static s16 D_us_80180B58[] = {
    0, 24, 0, 4, 8, -4, -16, 0,
};
static s16 D_us_80180B68[] = {
    0, -8, 0, 4, 8, -4, -16, 0,
};
static AnimateEntityFrame D_us_80180B78[] = {
    {0x08, 0x6D}, {0x04, 0x6E}, {0x04, 0x6F}, {0x04, 0x70}, {0x08, 0x71},
    {0x04, 0x70}, {0x04, 0x6F}, {0x04, 0x6E}, {0, 0},
};
static AnimateEntityFrame D_us_80180B8C[] = {
    {0x10, 0x6D}, {0x02, 0x6E}, {0x02, 0x6F}, {0x07, 0x72}, {0x07, 0x73},
    {0x05, 0x74}, {0x05, 0x75}, {0x10, 0x76}, {0xFF, 0x00},
};
static AnimateEntityFrame D_us_80180BA0[] = {
    {0x10, 0x6D}, {0x10, 0x77}, {0x02, 0x78}, {0x02, 0x79},
    {0x20, 0x7A}, {0x06, 0x7B}, {0x06, 0x7C}, {0xFF, 0x00},
};
static AnimateEntityFrame D_us_80180BB0[] = {
    {0x08, 0x6D}, {0x05, 0x7D}, {0x05, 0x7E}, {0x28, 0x7F}, {0x01, 0x80},
    {0x02, 0x81}, {0x02, 0x82}, {0x02, 0x83}, {0x02, 0x84}, {0x02, 0x85},
    {0x02, 0x86}, {0x02, 0x87}, {0x10, 0x88}, {0xFF, 0x00},
};
static AnimateEntityFrame D_us_80180BCC[] = {
    {0x02, 0x89},
    {0x02, 0x8A},
    {0x00, 0x00},
    {0x00, 0x00},
};
static AnimateEntityFrame D_us_80180BD4[] = {
    {0x01, 0x8B},
    {0x01, 0x8C},
    {0x40, 0x8D},
    {0xFF, 0x00},
};
static AnimateEntityFrame D_us_80180BDC[] = {
    {0x10, 0x8E}, {0x18, 0x8F}, {0x20, 0x90},
    {0x08, 0x91}, {0x10, 0x92}, {0xFF, 0x00},
};
static AnimateEntityFrame D_us_80180BE8[] = {
    {0x06, 0x94}, {0x06, 0x95}, {0x08, 0x7E},
    {0x08, 0x7D}, {0x10, 0x6D}, {0xFF, 0x00},
};
static AnimateEntityFrame D_us_80180BF4[] = {
    {0x0C, 0x97}, {0x05, 0x98}, {0x05, 0x99},
    {0x05, 0x9A}, {0x05, 0x9B}, {0xFF, 0x00},
};
static AnimateEntityFrame D_us_80180C00[] = {
    {0x10, 0x98}, {0x04, 0x99}, {0x04, 0x9A},
    {0x04, 0x9B}, {0xFF, 0x00}, {0x00, 0x00},
};
static AnimateEntityFrame D_us_80180C0C[] = {
    {0x02, 0x9C},
    {0x02, 0x9D},
    {0x00, 0x00},
    {0x00, 0x00},
};
static AnimateEntityFrame D_us_80180C14[] = {
    {0x10, 0x91}, {0x04, 0xA1}, {0x01, 0xA2}, {0x02, 0xA3}, {0x08, 0xA2},
    {0x04, 0xA4}, {0x01, 0xA5}, {0x02, 0xA6}, {0x0C, 0xA5}, {0x08, 0xA7},
    {0x04, 0xA1}, {0x01, 0xA2}, {0x02, 0xA3}, {0x08, 0xA2}, {0x04, 0xA4},
    {0x01, 0xA5}, {0x02, 0xA6}, {0x0C, 0xA5}, {0x08, 0xA7}, {0x14, 0x91},
    {0x18, 0x92}, {-1, 0x00},
};
static AnimateEntityFrame D_us_80180C40[] = {
    {0x08, 0x9E}, {2, 0x9F},    {0x02, 0xA0}, {32, 0x91},
    {0x04, 0xA1}, {1, 0xA2},    {0x02, 0xA3}, {8, 0xA2},
    {0x04, 0xA4}, {1, 0xA5},    {0x02, 0xA6}, {0x0C, 0xA5},
    {0x08, 0xA7}, {0x14, 0x91}, {0x18, 0x92}, {-1, 0x00},
};

void EntityFakeGrant(Entity* self) {
    Entity* entity;
    s8* index;
    s32 offsetX;
    s32 offsetY;
    bool onLeftSide;

    if ((self->hitFlags & 3) && self->step < 8) {
        SetStep(8);
    }
    if (self->flags & FLAG_DEAD && self->step != 11) {
        SetStep(11);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804B8);
        self->hitboxState = 0;
        entity = self - 1;
        CreateEntityFromCurrentEntity(E_ID(COFFIN), entity);
        entity->posY.i.hi = 0xBA - g_Tilemap.scrollY.i.hi;
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_ID(UNK_26), entity);
        SetStep(1);
        // fallthrough

    case 1:
        self->animCurFrame = 3;
        if (D_us_801806B0 & 1) {
            SetStep(2);
        }
        break;

    case 2:
        entity = self - 1;
        switch (self->step_s) {
        case 0:
            if (entity->ext.grant.unk8C) {
                self->animCurFrame = 0;
                self->step_s++;
            }
            break;
        case 1:
            if (!entity->ext.grant.unk8C) {
                self->animCurFrame = 4;
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
            self->animCurFrame = 0x93;
            self->velocityX = 0;
            self->velocityY = FIX(-8.0);
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.09375);
            if (func_us_80196838(D_us_80180B68) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_B);
                SetSubStep(2);
            }
            break;
        case 2:
            MoveEntity();
            if (!AnimateEntity(D_us_80180BE8, self)) {
                SetStep(4);
            }
            break;
        }
        break;
    case 4:
        if (!self->step_s) {
            if (D_us_801806B4 > 1) {
                self->ext.grant.timer = 32;
            }
            self->step_s++;
        }
        AnimateEntity(D_us_80180B78, self);
        if (self->facingLeft) {
            self->velocityX = FIX(1.0);
        } else {
            self->velocityX = FIX(-1.0);
        }
        MoveEntity();
        if (!--self->ext.grant.timer) {
            SetStep(4);
            if (D_us_801806B4 > 1) {
                SetStep(6);
            }
        }
        onLeftSide = ((GetSideToPlayer() & 1) ^ 1);
        if (self->facingLeft != onLeftSide && GetDistanceToPlayerX() > 0x40) {
            SetStep(7);
        }
        if (GetDistanceToPlayerX() < 4) {
            SetStep(5);
            if ((D_us_801806B4 > 0) && (Random() & 1)) {
                SetStep(6);
            }
        }
        break;
    case 7:
        if (AnimateEntity(D_us_80180B8C, self) == 0) {
            self->facingLeft ^= 1;
            self->animCurFrame = 0x6D;
            SetStep(4);
        }
        break;
    case 5:
        if (AnimateEntity(D_us_80180BA0, self) == 0) {
            SetStep(4);
        }
        if (!self->poseTimer && self->pose == 2) {
            PlaySfxPositional(SFX_ARROW_SHOT_A);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                // BUG! additional arg
                CreateEntityFromEntity(E_ID(VERTICAL_DAGGER), self, entity);
            }
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_us_80180BB0, self) == 0) {
                SetSubStep(1);
            }
            if (!self->poseTimer && self->pose == 0xC) {
                PlaySfxPositional(SFX_UI_SUBWEAPON_TINK);
            }
            break;
        case 1:
            self->velocityX = 0;
            self->velocityY = FIX(3.5);
            self->rotate = 0;
            self->step_s++;
            // fallthrough
        case 2:
            self->rotate -= ROT(33.75);
            AnimateEntity(D_us_80180BCC, self);
            if (self->hitFlags & 0x80) {
                self->drawFlags = ENTITY_DEFAULT;
                SetSubStep(3);
            }
            MoveEntity();
            self->velocityY += FIX(0.0625);
            if (func_us_80194338(D_us_80180B58) & 1) {
                self->drawFlags = ENTITY_DEFAULT;
                SetSubStep(4);
                if (D_us_801806B4 > 1) {
                    SetStep(0xA);
                }
            }
            break;
        case 3:
            AnimateEntity(D_us_80180BD4, self);
            MoveEntity();
            if (func_us_80194338(D_us_80180B58) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_B);
                self->drawFlags = ENTITY_DEFAULT;
                SetSubStep(4);
            }
            break;
        case 4:
            if (AnimateEntity(D_us_80180BDC, self) == 0) {
                SetStep(9);
            }
            break;
        }
        break;
    case 9:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0x93;
            self->velocityX = 0;
            self->velocityY = FIX(-8.0);
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.09375);
            if (func_us_80196838(D_us_80180B68) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_B);
                SetSubStep(2);
            }
            break;
        case 2:
            MoveEntity();
            if (!AnimateEntity(D_us_80180BE8, self)) {
                SetStep(4);
            }
            break;
        }
        break;
    case 10:
        switch (self->step_s) {
        case 0:
            if (((GetSideToPlayer() & 1) ^ 1) == self->facingLeft) {
                SetSubStep(2);
                break;
            }
            SetSubStep(1);
            self->facingLeft ^= 1;
        case 1:
            if (AnimateEntity(D_us_80180C40, self) == 0) {
                SetStep(9);
            }

            if (!self->poseTimer && self->pose == 9) {
                PlaySfxPositional(SFX_ARROW_SHOT_A);
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(HORIZONTAL_DAGGER), self, entity);
                    entity->facingLeft = self->facingLeft;
                }
            }
            break;
        case 2:
            if (AnimateEntity(D_us_80180C14, self) == 0) {
                SetStep(9);
            }
            if (!self->poseTimer && (self->pose == 6 || self->pose == 15)) {
                PlaySfxPositional(SFX_ARROW_SHOT_A);
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(HORIZONTAL_DAGGER), self, entity);
                    entity->facingLeft = self->facingLeft;
                }
            }
            break;
        }
        break;
    case 8:
    case 11:
        switch (self->step_s) {
        case 0:
            self->drawFlags = ENTITY_DEFAULT;
            if (self->step == 0xB) {
                self->hitboxState = 0;
                D_us_801806B4++;
            }
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
            self->posY.i.hi--;
            if (func_us_80196838(D_us_80180B68) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_B);
                SetSubStep(2);
            } else {
                self->velocityY = FIX(-2.0);
                SetSubStep(1);
            }
            // fallthrough
        case 1:
            if (AnimateEntity(D_us_80180BF4, self) == 0) {
                SetSubStep(3);
            }
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (func_us_80194338(D_us_80180B58) & 1) {
                SetSubStep(4);
            }
            break;
        case 2:
            if (AnimateEntity(D_us_80180C00, self) == 0) {
                SetSubStep(3);
            }
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (func_us_80194338(D_us_80180B58) & 1) {
                SetSubStep(4);
            }
            break;
        case 3:
            AnimateEntity(D_us_80180C0C, self);
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (func_us_80194338(D_us_80180B58) & 1) {
                SetSubStep(4);
            }
            break;
        case 4:
            if (self->step == 11) {
                self->ext.grant.timer = 64;
                PlaySfxPositional(SFX_BOSS_LARGE_FLAMES);
                self->step_s++;
            } else if (D_us_801806B4 > 1) {
                SetStep(0xA);
            } else if (AnimateEntity(D_us_80180BDC, self) == 0) {
                SetStep(9);
            }
            break;
        case 5:
            if (!(g_Timer & 3)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(DEATH_FLAMES), self, entity);
                    entity->zPriority = self->zPriority + 1;
                    entity->params = 8;
                    entity->posY.i.hi += 0xC;
                }
            }

            if (!--self->ext.grant.timer) {
                self->animCurFrame = 0;
                self->step_s++;
            }
            break;
        case 6:
            return;
        }
        break;

    case 0xFF:
#include "../../st/pad2_anim_debug.h"
        break;
    }

    index = D_us_801806B8;
    index = &index[D_us_80180718[self->animCurFrame] * 4];
    self->hitboxOffX = *index++;
    self->hitboxOffY = *index++;
    self->hitboxWidth = *index++;
    self->hitboxHeight = *index++;

    offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (self->velocityX < 0) {
        if (offsetX < 0x58) {
            self->posX.i.hi = 0x58 - g_Tilemap.scrollX.i.hi;
        }
    } else if (offsetX > 0x1A8) {
        self->posX.i.hi = 0x1A8 - g_Tilemap.scrollX.i.hi;
    }
}

extern EInit D_us_80180518;

// vertical dagger
void EntityVerticalDagger(Entity* self) {
    if (D_us_801806B0 & 4) {
        self->flags |= FLAG_DEAD;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180518);
        self->animCurFrame = 0xA8;
        self->velocityY = FIX(3.0);
        self->hitboxOffY = 5;
        // fallthrough
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.03125);
        if (self->flags & FLAG_DEAD) {
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
            self->velocityY = FIX(-2.0);
            self->hitboxState = 0;
            self->step += 1;
        }
        break;
    case 2:
        MoveEntity();
        self->velocityY += FIX(0.25);
        self->rotate += ROT(11.25);
        if (g_Timer & 1) {
            self->animCurFrame = 0xA8;
        } else {
            self->animCurFrame = 0;
        }
        break;
    }
    if (self->posY.i.hi > 256) {
        DestroyEntity(self);
    }
}

extern EInit D_us_80180518;

void EntityHorizontalDagger(Entity* self) {
    s32 offsetX;
    s32 offsetY;

    if (D_us_801806B0 & 4) {
        self->flags |= FLAG_DEAD;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180518);
        self->animCurFrame = 0xA8;
        self->drawFlags = ENTITY_ROTATE;
        self->rotate = ROT(90);
        if (self->facingLeft) {
            self->velocityX = FIX(5.0);
        } else {
            self->velocityX = FIX(-5.0);
        }
        self->hitboxWidth = 2;
        self->hitboxHeight = 4;
        // fallthrough
    case 1:
        MoveEntity();
        if (self->flags & FLAG_DEAD) {
            self->hitboxState = 0;
            self->velocityX = -self->velocityX / 4;
            self->velocityY = FIX(-4);
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step++;
        }
        break;
    case 2:
        MoveEntity();
        self->velocityY += FIX(0.25);
        self->rotate += ROT(11.25);
        if (g_Timer & 1) {
            self->animCurFrame = 0xA8;
        } else {
            self->animCurFrame = 0;
        }
        break;
    }

    if (self->posY.i.hi > 256) {
        DestroyEntity(self);
        return;
    }

    offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    if (self->velocityX < 0) {
        if (offsetX < -32) {
            DestroyEntity(self);
        }
    } else if (offsetX > 0x220) {
        DestroyEntity(self);
    }
}

extern EInit D_us_80180524;

// created when Grant is initialized and
// never destroyed. doesn't do anything
// obvious.
void func_us_80197764(Entity* self) {
    Entity* parent;
    s32 animCurFrame;

    if (!self->step) {
        InitializeEntity(D_us_80180524);
        self->hitboxWidth = 0x10;
        self->hitboxHeight = 0x10;
        self->hitboxState = 0;
    }
    parent = self - 1;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;
    animCurFrame = parent->animCurFrame;
    if (animCurFrame == 0x8A || animCurFrame == 0x89) {
        self->hitboxState = 1;
    } else {
        self->hitboxState = 0;
    }
    if (parent->entityId != E_ID(FAKE_GRANT)) {
        DestroyEntity(self);
    }
}
