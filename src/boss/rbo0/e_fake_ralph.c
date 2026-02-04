// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo0.h"

static s32 func_us_801946F4(void) {
    s32 ret;
    s32 status;

    status = GetSideToPlayer() & 1;
    if (g_CurrentEntity->facingLeft != status) {
        return false;
    }
    ret = 0;
    status = g_Player.status;
    if (status & 0x800) {
        if (status & 0x20) {
            ret = 0x12;
        } else {
            ret = 9;
        }
    }
    if (status & 0x400) {
        if (GetDistanceToPlayerX() < 0x40) {
            if (status & 0x20) {
                ret = 0x11;
            } else {
                ret = 9;
            }
        } else if (status & 0x2000) {
            ret = 0x13;
        }
    }
    return ret;
}

static s16 D_us_80180958[] = {
    0x0000, 0x0018, 0x0000, 0x0004, 0x0008, 0xFFFC, 0xFFF0, 0x0000,
};
static AnimateEntityFrame D_us_80180968[] = {
    {0x02, 0x09}, {0x04, 0x08}, {0x04, 0x07}, {0x04, 0x08}, {0x04, 0x09},
    {0x04, 0x0A}, {0x04, 0x0B}, {0x04, 0x0A}, {0x02, 0x09}, {0x00, 0x00},
};
static AnimateEntityFrame D_us_8018097C[] ALIGNED4 = {
    {0x03, 0x0C}, {0x06, 0x0D}, {0x05, 0x0E}, {0x06, 0x0F}, {0x07, 0x10},
    {0x06, 0x11}, {0x05, 0x12}, {0x06, 0x13}, {0x04, 0x0C}, {0x00, 0x00},
};
static AnimateEntityFrame __unused_anim0[] ALIGNED4 UNUSED = {
    {0x03, 0x14}, {0x03, 0x15}, {0x03, 0x16}, {0x03, 0x15}, {0x03, 0x16},
    {0x03, 0x17}, {0x03, 0x16}, {0x03, 0x17}, {0x03, 0x18}, {0x03, 0x17},
    {0x03, 0x18}, {0x03, 0x19}, {0x03, 0x18}, {0x03, 0x19}, {0x03, 0x1A},
    {0x03, 0x19}, {0x03, 0x1A}, {0x03, 0x1B}, {0x03, 0x1A}, {0x03, 0x1B},
    {0x03, 0x14}, {0x03, 0x1B}, {0x03, 0x14}, {0x03, 0x15}, {0x00, 0x00},
    {0x00, 0x00},
};
static AnimateEntityFrame D_us_801809C4[] ALIGNED4 = {
    {0x01, 0x09}, {0x04, 0x1C}, {0x20, 0x1D},
    {0x04, 0x1C}, {0x01, 0x09}, {0xFF, 0x00},
};
static AnimateEntityFrame __unused_anim1[] ALIGNED4 UNUSED = {
    {0x05, 0x1E}, {0x03, 0x20}, {0x08, 0x21},
    {0x03, 0x20}, {0x08, 0x1E}, {0xFF, 0x00},
};
static AnimateEntityFrame D_us_801809DC[] = {
    {0x05, 0x1E},
    {0x03, 0x20},
    {0xFF, 0x00},
    {0x00, 0x00},
};

static AnimateEntityFrame D_us_801809E4[] ALIGNED4 = {
    {0x03, 0x20},
    {0x08, 0x1E},
    {0xFF, 0x00},
};
static AnimateEntityFrame __unused_anim3[] ALIGNED4 UNUSED = {
    {0x05, 0x1F}, {0x03, 0x20}, {0x08, 0x21},
    {0x03, 0x20}, {0x08, 0x1E}, {0xFF, 0x00},
};

static AnimateEntityFrame D_us_801809F8[] = {
    {0x05, 0x1F}, {0x03, 0x20}, {0xFF, 0x00}};

static AnimateEntityFrame D_us_80180A00[] = {
    {0x03, 0x20},
    {0x08, 0x1E},
    {0xFF, 0x00},
};

static AnimateEntityFrame D_us_80180A08[] = {
    {0x08, 0x09}, {0x02, 0x08}, {0x04, 0x07}, {0x02, 0x08}, {0x01, 0x09},
    {0x01, 0x0A}, {0x02, 0x0B}, {0x05, 0x23}, {0x04, 0x24}, {0x04, 0x25},
    {0x01, 0x26}, {0x01, 0x27}, {0x01, 0x28}, {0x01, 0x29}, {0x01, 0x2A},
    {0x01, 0x2B}, {0x01, 0x2C}, {0x01, 0x2A}, {0x01, 0x2B}, {0x01, 0x2C},
    {0x01, 0x2A}, {0x01, 0x2B}, {0x01, 0x2C}, {0x02, 0x2D}, {0x02, 0x2E},
    {0x00, 0x00},
};

static AnimateEntityFrame D_us_80180A3C[] = {
    {0x02, 0x1B}, {0x02, 0x1C}, {0x0C, 0x1D}, {0x07, 0x35}, {0x05, 0x36},
    {0x04, 0x37}, {0x04, 0x38}, {0x01, 0x39}, {0x01, 0x3A}, {0x01, 0x3B},
    {0x01, 0x3C}, {0x01, 0x3D}, {0x01, 0x3E}, {0x01, 0x3F}, {0x01, 0x3D},
    {0x01, 0x3E}, {0x01, 0x3F}, {0x02, 0x40}, {0x02, 0x41}, {0x08, 0x1C},
    {0xFF, 0x00},
};

static AnimateEntityFrame D_us_80180A68[] = {
    {0x03, 0x45}, {0x04, 0x44}, {0x04, 0x24}, {0x04, 0x25}, {0x01, 0x26},
    {0x01, 0x27}, {0x01, 0x28}, {0x01, 0x29}, {0x01, 0x2A}, {0x01, 0x2B},
    {0x01, 0x2C}, {0x01, 0x2A}, {0x01, 0x2B}, {0x01, 0x2C}, {0x01, 0x2A},
    {0x01, 0x2B}, {0x01, 0x2C}, {0x01, 0x2A}, {0x01, 0x2B}, {0x01, 0x2C},
    {0xFF, 0x00},
};

static AnimateEntityFrame D_us_80180A94[] = {
    {0x02, 0x09}, {0x02, 0x2F}, {0x02, 0x30}, {0x02, 0x31},
    {0x03, 0x32}, {0x10, 0x33}, {0x06, 0x34}, {0xFF, 0x00},
};

static AnimateEntityFrame D_us_80180AA4[] = {
    {0x02, 0x45}, {0x02, 0x46}, {0x02, 0x30}, {0x02, 0x31},
    {0x03, 0x32}, {0x10, 0x33}, {0x06, 0x34}, {0xFF, 0x00},
};

static AnimateEntityFrame D_us_80180AB4[] = {
    {0x02, 0x09}, {0x02, 0x47}, {0x04, 0x48}, {0x06, 0x49},
    {0x06, 0x4A}, {0x38, 0x4B}, {0x50, 0x4C}, {0x00, 0x00},
};

static AnimateEntityFrame D_us_80180AC4[] = {
    {0x02, 0x09},
    {0x02, 0x2F},
    {0x02, 0x30},
    {0xFF, 0x00},
};

static AnimateEntityFrame D_us_80180ACC[] = {
    {0x02, 0x31}, {0x02, 0x32}, {0x02, 0x33}, {0x02, 0x34}, {0x02, 0x1C},
    {0x02, 0x42}, {0x02, 0x43}, {0x02, 0x1C}, {0x00, 0x00}, {0x00, 0x00},
};

static AnimateEntityFrame D_us_80180AE0[] = {
    {0x08, 0x09}, {0x08, 0x2F}, {0x01, 0x51}, {0x01, 0x52}, {0x01, 0x53},
    {0x01, 0x54}, {0x02, 0x55}, {0x02, 0x56}, {0x02, 0x57}, {0x02, 0x58},
    {0x02, 0x59}, {0x02, 0x5A}, {0x02, 0x5B}, {0x02, 0x54}, {0x01, 0x4D},
    {0x01, 0x4E}, {0x01, 0x4F}, {0x01, 0x50}, {0x10, 0x2F}, {0xFF, 0x00},
};

static AnimateEntityFrame D_us_80180B08[] = {
    {0x04, 0x60}, {0x04, 0x61}, {0x04, 0x62},
    {0x04, 0x63}, {0x04, 0x64}, {0xFF, 0x00},
};

static AnimateEntityFrame D_us_80180B14[] ALIGNED4 = {
    {0x03, 0x65}, {0x03, 0x66}, {0x03, 0x67},
    {0x03, 0x68}, {0x03, 0x69}, {0xFF, 0x00},
};
static AnimateEntityFrame __unused_anim4[] ALIGNED4 UNUSED = {
    {0x05, 0x6A}, {0x05, 0x6B}, {0x40, 0x6C},
    {0x04, 0x6B}, {0x04, 0x6A}, {0xFF, 0x00},
};

static AnimateEntityFrame D_us_80180B2C[] = {
    {0x03, 0x01}, {0x03, 0x02}, {0x03, 0x03}, {0x03, 0x04}, {0x03, 0x05},
    {0x03, 0x06}, {0x03, 0x07}, {0x03, 0x08}, {0x03, 0x09}, {0x03, 0x0A},
    {0x03, 0x0B}, {0x03, 0x0C}, {0x03, 0x0D}, {0xFF, 0x00},
};
static u16 D_us_80180B48[] = {
    0x001E,
    0x0021,
    0x0022,
    0x0020,
};
static u16 __unused[] UNUSED = {
    0x0000,
    0x0018,
    0x0008,
    0x0000,
};

extern EInit D_us_801804AC;
extern s8 D_us_801806B8[];
extern u8 D_us_80180718[];

void EntityFakeRalph(Entity* self) {
    Entity* entity;
    s8* temp_v1_10;
    s32 distanceX;
    s32 distanceY;
    s32 temp_s2_3;
    s32 itemID;

    FntPrint("step %x\n", self->step);
    FntPrint("item %x\n", self->ext.ralph.itemEntityId);
    if ((g_Player.status & PLAYER_STATUS_DEAD) && self->step < 16) {
        SetStep(16);
    }
    if ((self->hitFlags & 3) && self->step < 11) {
        SetStep(11);
    }
    if (self->flags & FLAG_DEAD && self->step != 21) {
        SetStep(21);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804AC);
        self->hitboxState = 0;
        entity = self - 1;
        CreateEntityFromCurrentEntity(E_COFFIN, entity);
        entity->posY.i.hi = 0xBA - g_Tilemap.scrollY.i.hi;
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_UNK_27, entity);
        self->ext.ralph.itemEntityId = E_BONE_CROSS;
        SetStep(1);
        // fallthrough
    case 1:
        self->animCurFrame = 1;
        if (D_us_801806B0 & 1) {
            SetStep(2);
        }
        break;
    case 2:
        entity = self - 1;
        switch (self->step_s) {
        case 0:
            if (entity->ext.ralph.unk8C) {
                self->animCurFrame = 0;
                self->step_s++;
            }
            break;
        case 1:
            if (!entity->ext.ralph.unk8C) {
                self->animCurFrame = 2;
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
            if (UnkCollisionFunc3(D_us_80180958) & 1) {
                self->step_s++;
            }
            break;
        case 1:
            distanceX = DISP_STAGE_W - g_Tilemap.scrollX.i.hi;
            distanceY = 0xC0 - g_Tilemap.scrollY.i.hi;
            if (distanceX < self->posX.i.hi) {
                self->facingLeft = true;
            } else {
                self->facingLeft = false;
            }
            self->velocityX = FIX(1);
            if (self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            self->step_s++;
            // fallthrough
        case 2:
            MoveEntity();
            AnimateEntity(D_us_8018097C, self);
            distanceX = 0x100 - g_Tilemap.scrollX.i.hi;
            distanceX -= self->posX.i.hi;
            if (self->facingLeft) {
                distanceX = -distanceX;
            }
            if (distanceX < 0) {
                SetSubStep(3);
            }
            break;
        case 3:
            SetStep(4);
            break;
        }
        break;

    case 7:
        SetStep(4);
        if (D_us_801806B4 > 1) {
            SetStep(5);
        }
        break;

    case 6:
        SetStep(12);
        if (!(Random() & 7)) {
            SetStep(14);
        }
        if (g_Player.status & PLAYER_STATUS_SUBWPN) {
            SetStep(13);
        }
        if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            SetStep(13);
        }
        if (GetDistanceToPlayerX() > 80) {
            SetStep(14);
        }
        if (!(Random() & 0xF)) {
            SetStep(10);
        }
        if (D_us_801806B4 > 0) {
            if (g_Player.status & PLAYER_STATUS_UNK2000) {
                SetStep(20);
                if (GetDistanceToPlayerX() > 80) {
                    SetStep(8);
                }
            }
            if (g_Player.status & PLAYER_STATUS_BAT_FORM) {
                SetStep(19);
            }
            if (D_us_801806B4 >= 2 && GetDistanceToPlayerX() > 80 &&
                self->ext.ralph.itemEntityId == 33 && !(Random() & 3)) {
                SetStep(15);
            }
        }
        break;
    case 4:
        if (!self->step_s) {
            self->ext.ralph.timer = 64;
            self->step_s++;
        }
        if (AnimateEntity(D_us_80180968, self) == 0) {
            self->facingLeft = GetSideToPlayer() & 1;
        }

        if (!--self->ext.ralph.timer) {
            SetStep(5);
        }
        if (D_us_801806B4 > 0) {
            temp_s2_3 = func_us_801946F4();
        }
        break;
    case 5:
        if (!self->step_s) {
            self->ext.ralph.timer = 128;
            distanceX = GetDistanceToPlayerX();
            temp_s2_3 = GetSideToPlayer() & 1;
            if (distanceX < 0x50) {
                self->facingLeft = temp_s2_3 ^ 1;
            } else {
                self->facingLeft = temp_s2_3;
            }
            self->step_s++;
        }
        AnimateEntity(D_us_8018097C, self);
        if (self->facingLeft) {
            self->velocityX = FIX(-1);
        } else {
            self->velocityX = FIX(1);
        }
        MoveEntity();
        temp_s2_3 = GetSideToPlayer() & 1;
        distanceX = GetDistanceToPlayerX();
        if (self->facingLeft == temp_s2_3) {
            if (distanceX < 0x50) {
                SetStep(6);
                break;
            }
        } else if (distanceX > 80) {
            SetStep(6);
            break;
        }

        if (!--self->ext.ralph.timer) {
            SetStep(6);
        }
        if (D_us_801806B4 > 0) {
            temp_s2_3 = func_us_801946F4();
        }

        break;

    case 12:
        if (!self->step_s) {
            self->facingLeft = GetSideToPlayer() & 1;
            self->step_s++;
        }
        if (AnimateEntity(D_us_80180A08, self) == 0) {
            SetStep(7);
        }
        if (!self->poseTimer && self->pose == 11) {
            PlaySfxPositional(SFX_BOSS_RIC_ATTACK_A);
            PlaySfxPositional(SFX_BOSS_RIC_WHIP_ATTACK);
        }
        break;
    case 13:
        if (!self->step_s) {
            PlaySfxPositional(SFX_BOSS_RIC_ATTACK_A);
            self->facingLeft = GetSideToPlayer() & 1;
            self->step_s++;
        }
        if (!AnimateEntity(D_us_80180A3C, self)) {
            SetStep(7);
        }
        break;

    case 18:
    case 17:
        switch (self->step_s) {
        case 0:
            self->velocityY = FIX(-4.75);
            if (self->step == 0x12) {
                if (self->facingLeft) {
                    self->velocityX = FIX(-1);
                } else {
                    self->velocityX = FIX(1);
                }
            } else {
                self->velocityX = 0;
            }
            self->step_s++;
            // fallthrough
        case 1:
            if (self->step == 0x12) {
                AnimateEntity(D_us_801809F8, self);
            } else {
                AnimateEntity(D_us_801809DC, self);
            }
            MoveEntity();
            self->velocityY += FIX(0.1875);
            if (self->velocityY < FIX(-1)) {
                self->step_s++;
            }
            break;
        case 2:
            self->animCurFrame = 0x21;
            MoveEntity();
            func_us_80194338(D_us_80180958);
            self->velocityY += FIX(0.1875);
            if (self->velocityY > FIX(-1)) {
                SetSubStep(3);
            }
            break;
        case 3:
            if (self->step == 18) {
                AnimateEntity(D_us_80180A00, self);
            } else {
                AnimateEntity(D_us_801809E4, self);
            }
            MoveEntity();
            self->velocityY += FIX(0.1875);
            if (func_us_80194338(D_us_80180958) & 1) {
                SetStep(6);
            }
        }
        break;

    case 20:
    case 19:
        switch (self->step_s) {
        case 0:
            self->facingLeft = GetSideToPlayer() & 1;
            if (GetDistanceToPlayerX() > 0x70) {
                self->step = 19;
            }
            self->velocityY = FIX(-4.75);
            if (self->step == 19) {
                if (self->facingLeft) {
                    self->velocityX = FIX(-1);
                } else {
                    self->velocityX = FIX(1);
                }
            } else {
                self->velocityX = 0;
            }
            self->step_s++;
            // fallthrough
        case 1:
            if (self->step == 0x12) {
                AnimateEntity(D_us_801809F8, self);
            } else {
                AnimateEntity(D_us_801809DC, self);
            }
            MoveEntity();
            self->velocityY += FIX(0.1875);
            if (self->velocityY < FIX(-1)) {
                self->step_s++;
            }
            break;
        case 2:
            self->animCurFrame = 0x21;
            MoveEntity();
            func_us_80194338(D_us_80180958);
            self->velocityY += FIX(0.1875);
            if (self->velocityY > FIX(0)) {
                self->step_s++;
            }
            break;
        case 3:
            if (AnimateEntity(D_us_80180A68, self) == 0) {
                SetSubStep(4);
            }
            if (!self->poseTimer && self->pose == 5) {
                PlaySfxPositional(SFX_BOSS_RIC_WHIP_ATTACK);
            }
            // fallthrough
        case 4:
            if (self->step_s == 4) {
                if (self->velocityX) {
                    AnimateEntity(D_us_80180A00, self);
                } else {
                    AnimateEntity(D_us_801809E4, self);
                }
            }
            MoveEntity();
            self->velocityY += FIX(0.1875);
            if (func_us_80194338(D_us_80180958) & 1) {
                if (self->step_s == 4) {
                    SetStep(7);
                }
            }
            break;
        }
        break;

    case 8:
        switch (self->step_s) {
        case 0:
            self->facingLeft = GetSideToPlayer() & 1;
            self->velocityY = FIX(-4.75);
            self->velocityX = 0;
            self->step_s++;
            // fallthrough

        case 1:
            AnimateEntity(D_us_801809DC, self);
            MoveEntity();
            self->velocityY += FIX(0.1875);
            if (self->velocityY < FIX(-1)) {
                self->step_s++;
            }
            break;
        case 2:
            self->animCurFrame = 0x21;
            MoveEntity();
            func_us_80194338(D_us_80180958);
            self->velocityY += FIX(0.1875);
            if (self->velocityY > FIX(0)) {
                PlaySfxPositional(SFX_BOSS_RIC_ATTACK_B);
                self->step_s++;
            }
            break;
        case 3:
            if (AnimateEntity(D_us_80180AA4, self) == 0) {
                SetSubStep(4);
            }
            if (!self->poseTimer && self->pose == 5) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        self->ext.ralph.itemEntityId, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->posY.i.hi -= 0xC;
                }
            }
            // fallthrough
        case 4:
            if (self->step_s == 4) {
                AnimateEntity(D_us_801809E4, self);
            }
            MoveEntity();
            self->velocityY += FIX(0.1875);
            if ((func_us_80194338(D_us_80180958) & 1) && self->step_s == 4) {
                SetStep(7);
            }
            break;
        }
        break;

    case 14:
        if (!self->step_s) {
            self->facingLeft = GetSideToPlayer() & 1;
            self->step_s++;
        }
        if (AnimateEntity(D_us_80180A94, self) == 0) {
            SetStep(7);
        }
        if (!self->poseTimer && self->pose == 5) {
            PlaySfxPositional(SFX_BOSS_RIC_ATTACK_B);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(
                    self->ext.ralph.itemEntityId, self, entity);
                entity->facingLeft = self->facingLeft;
                entity->posY.i.hi -= 12;
            }
        }
        break;

    case 9:
        if (AnimateEntity(D_us_801809C4, self) == 0) {
            if (Random() & 1) {
                SetStep(7);
            } else {
                SetStep(6);
            }
        }
        break;
    case 10:
        if (!self->step_s) {
            self->facingLeft = GetSideToPlayer() & 1;
            self->step_s++;
        }
        if (AnimateEntity(D_us_80180AE0, self) == 0) {
            temp_s2_3 = Random() & 3;
            if (temp_s2_3 == 3 && D_us_801806B4 < 2) {
                temp_s2_3 = 0;
            }
            itemID = D_us_80180B48[temp_s2_3];
            self->ext.ralph.itemEntityId = itemID;
            SetStep(14);
        }
        if (!self->poseTimer && self->pose == 3) {
            PlaySfxPositional(SFX_UI_SUBWEAPON_TINK);
        }
        break;

    case 15:
        switch (self->step_s) {
        case 0:
            self->facingLeft = GetSideToPlayer() & 1;
            self->ext.ralph.timer = 8;
            self->step_s++;
            // fallthrough
        case 1:
            if (AnimateEntity(D_us_80180AC4, self) == 0) {
                SetSubStep(2);
            }
            break;
        case 2:
            if (AnimateEntity(D_us_80180ACC, self) == 0) {
                if (!--self->ext.ralph.timer) {
                    SetStep(7);
                    break;
                }
            }
            if (!self->poseTimer && (self->pose == 2 || self->pose == 6)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_DAGGER, self, entity);
                    if (self->pose == 2) {
                        entity->posY.i.hi -= 9;
                    } else {
                        entity->posY.i.hi += 9;
                    }
                    entity->facingLeft = self->facingLeft;
                }
            }
            break;
        }
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            MoveEntity();
            self->velocityX = 0;
            self->velocityY += FIX(0.1875);
            if (func_us_80194338(D_us_80180958) & 1) {
                self->facingLeft = GetSideToPlayer() & 1;
                self->step_s++;
            }
            break;
        case 1:
            AnimateEntity(D_us_80180AB4, self);
            if (!(g_Player.status & PLAYER_STATUS_DEAD)) {
                SetStep(4);
            }
            break;
        }
        break;

    case 11:
        if (!self->step_s) {
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(2);
            } else {
                self->velocityX = FIX(-2);
            }
            self->velocityY = FIX(-2);
            self->ext.ralph.timer = 0x10;
            self->animCurFrame = 0x22;
            self->step_s++;
        }
        MoveEntity();
        self->velocityX -= self->velocityX >> 5;
        self->velocityY += FIX(0.1875);
        temp_s2_3 = func_us_80194338(D_us_80180958);
        if (!self->ext.ralph.timer) {
            if (temp_s2_3 & 1) {
                SetStep(6);
            }
        } else {
            self->ext.ralph.timer--;
        }
        break;

    case 21:
        switch (self->step_s) {
        case 0:
            D_us_801806B4++;
            self->hitboxState = 0;
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(2);
            } else {
                self->velocityX = FIX(-2);
            }
            self->ext.ralph.timer = 0x10;
            self->animCurFrame = 0x22;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityX -= self->velocityX >> 5;
            self->velocityY += FIX(0.1875);
            if (self->ext.ralph.timer) {
                self->ext.ralph.timer--;
            }
            if ((func_us_80194338(D_us_80180958) & 1) &&
                !self->ext.ralph.timer) {
                self->ext.ralph.timer = 0x40;
                PlaySfxPositional(SFX_BOSS_LARGE_FLAMES);
                self->step_s++;
            }
            break;
        case 2:
            if (!(g_Timer & 3)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_DEATH_FLAMES, self, entity);
                    entity->zPriority = self->zPriority + 1;
                    entity->params = 7;
                    entity->posY.i.hi += 12;
                }
            }
            if (!--self->ext.ralph.timer) {
                self->animCurFrame = 0;
                self->step_s++;
            }
            break;
        case 3:
            return;
        }
        break;
    case 0xFF:
#include "../../st/pad2_anim_debug.h"
        break;
    }

    temp_v1_10 = D_us_801806B8;
    temp_v1_10 += D_us_80180718[self->animCurFrame] * 4;

    self->hitboxOffX = *temp_v1_10++;
    self->hitboxOffY = *temp_v1_10++;
    self->hitboxWidth = *temp_v1_10++;
    self->hitboxHeight = *temp_v1_10++;

    distanceX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    distanceY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (self->velocityX < 0) {
        if (distanceX < 80) {
            self->posX.i.hi = 80 - g_Tilemap.scrollX.i.hi;
        }
    } else if (distanceX > 0x1B0) {
        self->posX.i.hi = 0x1B0 - g_Tilemap.scrollX.i.hi;
    }
}

extern EInit D_us_801804DC;

void EntityBoneCross(Entity* self) {
    Entity* entity;
    s32 offsetX;
    s32 offsetY;

    if (D_us_801806B0 & 4) {
        self->flags |= FLAG_DEAD;
    }
    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {

            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 1;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804DC);
        self->animCurFrame = 0x5D;
        self->drawFlags = ENTITY_ROTATE;
        if (self->facingLeft) {
            self->velocityX = FIX(-2.5);
        } else {
            self->velocityX = FIX(2.5);
        }
        PlaySfxPositional(SFX_FAKE_TREVOR_BLOOD_CROSS);
        // fallthrough
    case 1:
        MoveEntity();
        if (self->facingLeft) {
            if (self->velocityX < FIX(2.5)) {
                self->velocityX += FIX(0.03125);
            }
        } else {
            if (self->velocityX > FIX(-2.5)) {
                self->velocityX -= FIX(0.03125);
            }
        }

        offsetX = abs(self->velocityX >> 13);
        self->rotate -= ROT(22.5) - offsetX;

        if (!(g_Timer & 7)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_BONE_CROSS_AFTER_IMAGE, self, entity);
                entity->params = self->animCurFrame;
                entity->rotate = self->rotate;
                entity->zPriority = self->zPriority - 1;
                entity->facingLeft = self->facingLeft;
            }
        }
        if (!(g_Timer & 3)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_BONE_CROSS_AFTER_IMAGE, self, entity);
                entity->params = 0;
                entity->zPriority = self->zPriority + 1;
                entity->facingLeft = self->facingLeft;
                entity->posY.i.hi += 8;
                entity->posX.i.hi += (Random() & 0xF) - 8;
            }
        }
        break;
    }

    offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;

    if (self->velocityX < 0) {
        if (offsetX < -0x20) {
            DestroyEntity(self);
        }
    } else if (offsetX > 0x220) {
        DestroyEntity(self);
    }
}

extern EInit D_us_801804F4;

void EntityGiantBoneCross(Entity* self) {
    Entity* entity;
    s32 offsetX;

    if (D_us_801806B0 & 4) {
        self->flags |= FLAG_DEAD;
    }

    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 3;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804F4);
        self->animCurFrame = 0x5F;
        self->drawFlags = ENTITY_ROTATE;
        if (self->facingLeft) {
            self->velocityX = FIX(-3.0);
        } else {
            self->velocityX = FIX(3.0);
        }
        // fallthrough
    case 1:
        MoveEntity();
        if (self->facingLeft) {
            if (self->velocityX < FIX(3)) {
                self->velocityX += FIX(5.0 / 128.0);
            }
        } else {
            if (self->velocityX > FIX(-3)) {
                self->velocityX -= FIX(5.0 / 128.0);
            }
        }

        offsetX = abs(self->velocityX >> 13);
        self->rotate -= ROT(22.5) - offsetX;

        if (!(g_Timer & 0xF)) {
            PlaySfxPositional(SFX_FAST_SWORD_SWISHES);
        }
        if (!(g_Timer & 7)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_BONE_CROSS_AFTER_IMAGE, self, entity);
                entity->params = self->animCurFrame;
                entity->rotate = self->rotate;
                entity->zPriority = self->zPriority - 1;
                entity->facingLeft = self->facingLeft;
            }
        }
        break;
    }

    offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    if (self->velocityX < 0) {
        if (offsetX < -0x20) {
            DestroyEntity(self);
        }
    } else if (offsetX > 0x220) {
        DestroyEntity(self);
    }
}

extern EInit D_us_801804E8;

// created by bone cross and giant bone cross attack
void EntityBoneCrossAfterImage(Entity* self) {
    if (D_us_801806B0 & 4) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804E8);
        if (!self->params) {
            if (Random() & 1) {
                self->step = 2;
                return;
            } else {
                self->step = 3;
                return;
            }
        }
        self->animCurFrame = self->params;
        self->drawFlags = ENTITY_OPACITY | ENTITY_ROTATE;
        self->opacity = 0x60;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        if (self->animCurFrame == 0x5F) {
            self->palette = PAL_FLAG(0x15D);
        }
    case 1:
        self->opacity -= 8;
        if (!self->opacity) {
            DestroyEntity(self);
            return;
        }
        break;
    case 2:
        self->velocityY += FIX(1.0 / 64.0);
        MoveEntity();
        if (!AnimateEntity(D_us_80180B08, self)) {
            DestroyEntity(self);
            return;
        }
        break;
    case 3:
        self->velocityY += FIX(9.0 / 512.0);
        MoveEntity();
        if (!AnimateEntity(D_us_80180B14, self)) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

extern EInit D_us_80180500;

void EntityDagger(Entity* self) {
    s32 offsetX;

    if (D_us_801806B0 & 4) {
        self->flags |= FLAG_DEAD;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180500);
        self->animCurFrame = 0xA8;
        self->drawFlags = ENTITY_ROTATE;
        self->rotate = ROT(-90);
        if (self->facingLeft) {
            self->velocityX = FIX(-5);
        } else {
            self->velocityX = FIX(5);
        }
        self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = 0xD0;
        self->scaleY = 0xC0;
        PlaySfxPositional(SFX_ARROW_SHOT_C);
        // fallthrough

    case 1:
        MoveEntity();
        if (self->flags & FLAG_DEAD) {
            self->hitboxState = 0;
            self->velocityX = -self->velocityX / 4;
            self->velocityY = FIX(-4.0);
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step++;
        }
        break;
    case 2:
        self->rotate -= ROT(5.625);
        if (g_Timer & 1) {
            self->animCurFrame = 0;
        } else {
            self->animCurFrame = 0xA8;
        }
        MoveEntity();
        self->velocityY += FIX(0.25);
        break;
    }

    if (self->posY.i.hi > DISP_STAGE_W) {

        DestroyEntity(self);
        return;
    }

    offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    if (self->velocityX < 0) {
        if (offsetX < -0x20) {
            DestroyEntity(self);
        }
    } else if (offsetX > 0x220) {
        DestroyEntity(self);
    }
}

void EntityHolyWaterFlask(Entity* self) {
    Entity* entity;
    s32 offsetX;
    s32 offsetY;

    if (D_us_801806B0 & 4) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = 3;
        self->animCurFrame = 0x32;
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0x40;
        if (self->facingLeft) {
            self->velocityX = FIX(-2.0);
        } else {
            self->velocityX = FIX(2.0);
        }
        self->velocityY = FIX(2.0);
        PlaySfxPositional(SFX_ARROW_SHOT_A);
        // fallthrough
    case 1:
        MoveEntity();
        offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (offsetY > 0xE0) {
            PlaySfxPositional(SFX_RIC_HOLY_WATER_ATTACK);
            self->animCurFrame = 0;
            self->posY.i.hi = 0xE0 - (s16)g_Tilemap.scrollY.i.hi;
            self->ext.ralph.timer = 0x80;
            self->hitboxWidth = 4;
            self->hitboxHeight = 8;
            self->hitboxState = 4;
            if (self->facingLeft) {
                self->velocityX = FIX(-0.5);
            } else {
                self->velocityX = FIX(0.5);
            }
            self->velocityY = 0;
            self->step += 1;
        }
        break;
    case 2:
        if (self->hitFlags) {
            self->velocityX = 0;
        }
        MoveEntity();
        if (!(self->ext.ralph.timer & 7)) {
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HOLY_WATER_FLAME, self, entity);
                entity->facingLeft = self->facingLeft ^ 1;
                entity->posY.i.hi -= 8;
            }
        }
        if (!--self->ext.ralph.timer) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (self->velocityX < 0) {
        if (offsetX < 0x50) {
            self->posX.i.hi = 0x50 - (s16)g_Tilemap.scrollX.i.hi;
        }
    } else {
        if (offsetX > 0x1B0) {
            self->posX.i.hi = 0x1B0 - (s16)g_Tilemap.scrollX.i.hi;
        }
    }
}

extern EInit D_us_8018050C;

void EntityHolyWaterFlame(Entity* self) {
    if (D_us_801806B0 & 4) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018050C);
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = 0x80;
        self->scaleY = 0;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->hitboxWidth = 4;
        // fallthrough
    case 1:
        if (!AnimateEntity(D_us_80180B2C, self)) {
            DestroyEntity(self);
        }
        self->scaleY = abs(self->pose - 8) << 6;
        if (self->pose > 3 && self->pose < 10) {
            self->hitboxHeight = 8;
            self->hitboxOffY = -8;
            self->hitboxState = 1;
        } else {
            self->hitboxState = 0;
        }
        break;
    }
}

extern EInit D_us_801804D0;
extern s8 D_us_8018081C[];
extern u8 D_us_8018084C[];

// coffin related?
void func_us_80196768(Entity* self) {
    Entity* entity;
    s8* hitboxPtr;
    s32 index;

    if (!self->step) {
        InitializeEntity(D_us_801804D0);
    }
    entity = self - 1;
    self->posX.i.hi = entity->posX.i.hi;
    self->posY.i.hi = entity->posY.i.hi;
    self->facingLeft = entity->facingLeft;

    index = entity->animCurFrame;
    hitboxPtr = D_us_8018081C;
    hitboxPtr += D_us_8018084C[index] * 4;

    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;

    if (entity->entityId != E_FAKE_RALPH) {
        DestroyEntity(self);
    }
}
