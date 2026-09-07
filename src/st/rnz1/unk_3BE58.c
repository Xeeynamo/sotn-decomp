// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz1.h"

extern s16 D_pspeu_09257C00[] = {0, 37, 0, 4, 8, -4, -16, 0};
extern s16 D_pspeu_09257C10[] = {0, 37, 8, 0};
static s16 unused_sensors[] = {0, 8, 0, 4, 4, -4, -8, 0};
static AnimateEntityFrame anim1[] = {{14, 1}, {14, 2}, {11, 3}, {10, 2}, POSE_LOOP(0)};
static AnimateEntityFrame anim2[] = {{16, 1}, {8, 2}, {30, 1}, {4, 4}, {3, 5}, {2, 6}, {2, 7}, {2, 8}, {1, 9}, {1, 8}, {3, 10}, {33, 8}, {6, 7}, {5, 6}, {5, 17}, {4, 18}, {4, 19}, {3, 20}, {14, 21}, {6, 24}, {6, 22}, {6, 23}, {4, 1}, {6, 2}, {8, 1}, POSE_END};
static AnimateEntityFrame anim3[] = {{8, 1}, {5, 11}, {9, 12}, {8, 13}, POSE_END};
static AnimateEntityFrame anim4[] = {{8, 14}, {8, 15}, {19, 16}, {5, 15}, POSE_END};
static AnimateEntityFrame anim5[] = {{5, 1}, {3, 4}, {2, 5}, {2, 6}, {1, 7}, {7, 6}, {6, 17}, {5, 18}, {4, 19}, {2, 20}, {3, 21}, {8, 24}, {7, 22}, {7, 23}, {3, 1}, {6, 2}, {8, 1}, POSE_END};
static AnimateEntityFrame D_us_801821C4[] = {{4, 37}, {4, 38}, {4, 39}, {4, 40}, POSE_LOOP(0)};

static AnimateEntityFrame anim7[] = {{14, 41}, {14, 42}, {11, 43}, {10, 42}, POSE_LOOP(0)};
static AnimateEntityFrame anim8[] = {{14, 41}, {8, 42}, {26, 41}, {3, 44}, {2, 45}, {2, 46}, {2, 47}, {2, 48}, {1, 49}, {1, 48}, {3, 50}, {33, 48}, {6, 47}, {5, 46}, {5, 57}, {4, 58}, {4, 59}, {3, 60}, {6, 61}, {10, 64}, {8, 62}, {6, 63}, {3, 41}, {6, 42}, {4, 41}, POSE_END};
static AnimateEntityFrame anim9[] = {{8, 41}, {5, 51}, {9, 52}, {8, 53}, POSE_END};
static AnimateEntityFrame anim10[] = {{8, 54}, {8, 55}, {19, 56}, {5, 55}, POSE_END};
static AnimateEntityFrame anim11[] = {{5, 41}, {3, 44}, {2, 45}, {2, 46}, {1, 47}, {7, 46}, {6, 57}, {5, 58}, {4, 59}, {4, 60}, {3, 61}, {10, 64}, {8, 62}, {6, 63}, {3, 41}, {6, 42}, {4, 41}, POSE_END};
static AnimateEntityFrame D_us_8018224C[] = {{1, 69}, {1, 70}, {1, 71}, POSE_END};

extern AnimateEntityFrame* D_pspeu_09257D50[] = {anim1, anim3, anim5, anim2, anim4, anim7, anim9, anim11, anim8, anim10};
extern s8 D_pspeu_09257D78[] = {0, 0, 0, 0, 1, 6, 15, 29, 1, 5, 15, 29, 1, 4, 15, 29};
static s8 D_us_8018228C[] = {0, 7, 15, 29, -5, 10, 13, 26, -10, 10, 14, 26, -11, 10, 14, 26, 0, 5, 12, 31, 0, 6, 14, 30, -1, 6, 14, 30, -5, 9, 12, 26, -1, 7, 14, 28, 1, 5, 14, 30};
extern u8 D_us_801822B4[] = {0, 1, 2, 3, 4, 5, 5, 5, 6, 7, 6, 8, 8, 8, 9, 9, 10, 11, 11, 12, 13, 13, 13, 13, 13};
static s8 D_us_801822D0[] = {0, 0, 0, 0, 17, -26, 4, 11, 16, -27, 4, 11, 15, -28, 4, 11, 13, -31, 4, 12, -3, -20, 8, 7, -79, -91, 0, 0, 9, 24, 4, 11, 8, 24, 4, 11, 15, -29, 4, 11, 18, -28, 4, 11, 17, -27, 4, 11, 13, -32, 4, 12, -84, -89, 0, 0, -87, -89, 0, 0, -92, -94, 0, 0, -90, -87, 0, 0, -85, -87, 0, 0, -88, -88, 0, 0, -87, -88, 0, 0, -83, -88, 0, 0, -83, -90, 0, 0, -87, -90, 0, 0, -91, -90, 0, 0, 16, -31, 7, 15, 15, -32, 7, 15, 14, -33, 7, 15, 10, -36, 7, 15, 8, 22, 4, 9, -14, -26, 7, 15, -14, -36, 7, 15, -16, -31, 7, 15, 14, -34, 7, 15};
static s8 D_us_80182354[] = {16, -33, 7, 15, 18, -4, 6, 9, 12, -39, 7, 15};
static u8 D_us_80182360[] = {0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 7, 6, 6, 6, 9, 10, 11, 6, 6, 6, 6, 6, 6, 12, 6};
static u8 D_pspeu_09257E80[] = {24, 25, 26, 27, 5, 6, 6, 7, 28, 7, 29, 30, 31, 32, 33, 25, 6, 6, 6, 6, 6, 34, 35, 6};
static AnimateEntityFrame D_us_80182394[] = {{4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {2, 7}, {2, 8}, POSE_END};

extern s32 D_pspeu_09257EB0[] = {32, 0, 0, 128, 64, 0, 0, 0};
static s16 D_us_801823C8[] = {12, 8, -12, 8, 0, -2};
extern s16 D_us_801823D4[];

extern EInit g_EInitBombKnight;
extern EInit g_EInitRockKnight;

void func_us_801BBE58(Entity* self) {
    Point16* deathOffset;
    Entity* other;
    s32 rock_knight_mode;
    s32 i;
    s32 offsetX;
    s8* hitbox;
    AnimateEntityFrame** animBlock;

    if ((self->flags & 0x100) && (self->step < 8)) {
        PlaySfxPositional(0x75D);
        SetStep(8);
    }
    rock_knight_mode = self->params & 1;
    animBlock = D_pspeu_09257D50 + (rock_knight_mode * 5);
    switch (self->step) {                              /* irregular */
    case 0x0:
        if (!self->params) {
            InitializeEntity(g_EInitBombKnight);
            self->animCurFrame = 1; // bomb knight holding bomb
        } else {
            InitializeEntity(g_EInitRockKnight);
            self->animCurFrame = 0x29; // rock knight holding rock
        }
        other = self + 1;
        CreateEntityFromCurrentEntity(0x47, other);
        other->params = self->params;
        if (rock_knight_mode == 0) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromCurrentEntity(0x44, other);
                other->ext.ILLEGAL.u32[3] = (u32) self;
                other->zPriority = ((self->zPriority) + 1);
            }
        }
        break;
    case 0x1:
        if (UnkCollisionFunc3(&D_pspeu_09257C00) & 1) {
            SetStep(2);
        }
        break;
    case 0x2:
        if (GetDistanceToPlayerX() < 0x80) {
            self->facingLeft = (( GetSideToPlayer() & 1) ^ 1);
            SetStep(3);
        }
        break;
    case 0x3:
        if (!self->step_s) {
            self->ext.ILLEGAL.s16[3] = D_pspeu_09257EB0[self->ext.ILLEGAL.u8[9]];
            self->ext.ILLEGAL.u8[9]++;
            self->ext.ILLEGAL.u8[9] &= 7;
            self->step_s++;
        }
        AnimateEntity(animBlock[0], self);
        if (self->facingLeft != ((GetSideToPlayer() & 1) ^ 1)) {
            SetStep(4);
        } else {
            UnkCollisionFunc2(&D_pspeu_09257C10);
            if ((self->facingLeft ^ (self->ext.ILLEGAL.u8[8])) != 0) {
                self->velocityX = 0x6000;
            } else {
                self->velocityX = -0x6000;
            }
            if (self->params & 0x100) {
                self->velocityX = 0;
            }
            if (self->ext.ILLEGAL.s16[3]) {
                self->ext.ILLEGAL.s16[3]--;
            }
            if (GetDistanceToPlayerX() < 0x40) {
                self->ext.ILLEGAL.u8[8] = 1;
            } else if (GetDistanceToPlayerX() > 0x70) {
                self->ext.ILLEGAL.u8[8] = 0;
            } else if (!self->ext.ILLEGAL.s16[3]) {
                if (rock_knight_mode == 0) {
                    PlaySfxPositional(0x75C);
                }
                if (GetDistanceToPlayerX() < 0x50) {
                    SetStep(5);
                } else {
                    SetStep(6);
                }
            }
            if (self->hitFlags & 3) {
                SetStep(7);
            }
        }
        break;
    case 0x4:
        if (AnimateEntity(animBlock[1], self) == 0) {
            self->facingLeft ^= 1;
            self->animCurFrame = 1;
            SetStep(3);
        }
        break;
    case 0x5:
        if (AnimateEntity(animBlock[2], self) == 0) {
            SetStep(3);
        }
        if ((!self->poseTimer) && ((self->pose) == 3)) {
            other = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (other != NULL) {
                if (rock_knight_mode != 0) {
                    CreateEntityFromEntity(0x45, self, other);
                    PlaySfxPositional(0x75A);
                } else {
                    CreateEntityFromEntity(0x42, self, other);
                    PlaySfxPositional(0x75B);
                }
                if (self->facingLeft) {
                    other->posX.i.hi -= 8;
                } else {
                    other->posX.i.hi += 8;
                }
                other->posY.i.hi -= 0x28;
                other->facingLeft = self->facingLeft;
                other->params = 0;
            }
        }
        break;
    case 0x6:
        if (AnimateEntity(animBlock[3], self) == 0) {
            SetStep(3);
        }
        if ((!self->poseTimer) && ((self->pose) == 4)) {
            other = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (other != NULL) {
                if (rock_knight_mode != 0) {
                    CreateEntityFromEntity(0x45, self, other);
                    PlaySfxPositional(0x75A);
                } else {
                    CreateEntityFromEntity(0x42, self, other);
                    PlaySfxPositional(0x75B);
                }
                if (self->facingLeft) {
                    other->posX.i.hi -= 8;
                } else {
                    other->posX.i.hi += 8;
                }
                other->posY.i.hi -= 0x28;
                other->facingLeft = self->facingLeft;
                other->params = 1;
            }
        }
        break;
    case 0x7:
        if (AnimateEntity(animBlock[4], self) == 0) {
            SetStep(3);
        }
        UnkCollisionFunc2(&D_pspeu_09257C10);
        if (self->facingLeft) {
            self->velocityX = -0x3000;
        } else {
            self->velocityX = 0x3000;
        }
        break;
    case 0x8:
        deathOffset = &D_us_801823D4;
        for(i = 0; i < 11; i++, deathOffset += 4) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(0x43, self, other);
                other->params = i;
                if (rock_knight_mode != 0) {
                    other->params |= 0x100;
                }
                other->facingLeft = self->facingLeft;
                if (self->facingLeft) {
                    other->posX.i.hi -= deathOffset->x;
                } else {
                    other->posX.i.hi += deathOffset->x;
                }
                other->posY.i.hi += deathOffset->y;
            }
        }
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(2, self, other);
            other->params = 3;
            other->zPriority = ((self->zPriority) + 4);
        }
        PlaySfxPositional(0x65B);
        DestroyEntity(self);
        return;
    case 0xFF:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
    if (self->params) {
        break;
    }
    self->animCurFrame++;
    self->params |= 1;
    } else {
        self->params = 0;
    }
    if (g_pads[1].pressed & PAD_CIRCLE) {
        if (self->step_s) {
            break;
        }
        self->animCurFrame--;
        self->step_s |= 1;
    } else {
        self->step_s = 0;
    }
    break;
    }
    hitbox = &D_pspeu_09257D78[0];
    if (rock_knight_mode != 0) {
        offsetX = D_us_801822B4[self->animCurFrame - 40];
    } else {
        offsetX = D_us_801822B4[self->animCurFrame];
    }
    hitbox += offsetX * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = *hitbox++;
    self->hitboxHeight = *hitbox++;
}

INCLUDE_ASM("st/rnz1/nonmatchings/unk_3BE58", func_us_801BC650);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_3BE58", func_us_801BCA5C);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_3BE58", func_us_801BCB9C);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_3BE58", func_us_801BCD80);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_3BE58", func_us_801BCE4C);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_3BE58", func_us_801BCFC8);
