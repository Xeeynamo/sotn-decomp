// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo2/rbo2.h"

INCLUDE_ASM("boss/rbo2_psp/nonmatchings/rbo2_psp/unk_12AE8", func_pspeu_0924A168);

INCLUDE_ASM("boss/rbo2_psp/nonmatchings/rbo2_psp/unk_12AE8", func_us_801A17C8);

typedef struct {
    s16 eArrayOffset;
    s16 eArrayParentOffset;
    u16 length;
    s16 unk6;
    u16 zOffset;
    u16 unkA;
} Death2PartsInit;

extern EInit g_EInitDeath2;
extern s32 g_BossMgrState;
extern s32 D_us_80180784;
extern s32 D_us_80180788;
extern Death2PartsInit D_us_8018078C[];
extern s16 D_us_8018081C[];
extern s16 D_us_80180834[];
extern s16 D_us_80180844[];
extern unkStr_801CDD80 D_us_801808A4[];
extern unkStr_801CDD80 D_us_801808E4[];
extern unkStr_801CDD80 D_us_8018095C[];
extern unkStr_801CDD80 D_us_801809E4[];
extern unkStr_801CDD80 D_us_80180A34[];
extern unkStr_801CDD80 D_us_80180A84[];
extern s16 D_us_80180A9C[];
extern unkStr_801CDD80 D_us_80180AB8[];

void func_801CE1E8(s32 step);
void func_801CDF1C(s16 entIndices[], unkStr_801CDD80* arg1, s32 arg2);
void polarPlacePartsWithAngvel(s16* entOffsets);
void polarPlacePartsList(s16* offsets);
s32 _LimitAngleChange(s32 delta, s32 base, s32 target);

void func_us_8019DA04(Entity* self) {
    Collider collider; // unused
    Entity* ent;
    Entity* part;
    Death2PartsInit* parts;
    s16* ptr;
    s32 i;
    s32 x;
    s32 facing;
    s32 y;
    s16 angle;
    s32 temp;

    if ((self->flags & FLAG_DEAD) && (self->step != 6)) {
        func_801CE1E8(6);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDeath2);
        self->animCurFrame = 2;
        self->hitboxHeight = 12;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        for (parts = D_us_8018078C, part = self, i = 0; parts->eArrayOffset;
             parts++, i++) {
            ent = self + parts->eArrayOffset;
            CreateEntityFromCurrentEntity(E_ID(UNK_1C), ent);
            ent->ext.death2.length = parts->length;
            ent->ext.death2.parent = self + parts->eArrayParentOffset;
            ent->ext.death2.unkAC = parts->unkA;
            ent->params = i;
            ent->zPriority = self->zPriority + parts->zOffset;
            ent->parent = self;
            ent->nextPart = part;
            part = ent;
        }
        self->parent = NULL;
        self->nextPart = part;
        polarPlacePartsList(D_us_8018081C);
        self->ext.death2.targetAngle = ROT(45);
        func_801CE1E8(1);
        /* fallthrough */
    case 1:
        ptr = D_us_80180844;
        func_801CDF1C(ptr, D_us_801808A4, 0);
        polarPlacePartsWithAngvel(ptr);
        if (!self->ext.death2.unkB4[0] && !self->ext.death2.unkB0[0]) {
            func_801CE1E8(2);
        }
        break;
    case 2:
        if (!self->step_s) {
            self->ext.death2.timer = ((Random() & 3) << 5) + 0x40;
            self->step_s++;
        }
        MoveEntity();
        facing = (GetSideToPlayer() & 1) ^ 1;
        if (self->facingLeft != facing) {
            if (self->facingLeft) {
                self->posX.i.hi += 12;
            } else {
                self->posX.i.hi -= 12;
            }
            self->facingLeft = facing;
        }
        ent = &PLAYER;
        angle = self->ext.death2.targetAngle;
        x = ent->posX.i.hi + ((rcos(angle) * 0x60) >> 12);
        y = ent->posY.i.hi - ((rsin(angle) * 0x60) >> 12);
        x -= self->posX.i.hi;
        y = y - self->posY.i.hi;
        angle = ratan2(y, x);
        angle = _LimitAngleChange(0x30, self->ext.death2.angle, angle);
        self->velocityX = (rcos(angle) << 16) >> 12;
        self->velocityY = (rsin(angle) << 16) >> 12;
        self->ext.death2.angle = angle;
        x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (x > 0x180) {
            self->ext.death2.targetAngle = ROT(135);
        }
        if (x < 0x80) {
            self->ext.death2.targetAngle = ROT(45);
        }
        ptr = D_us_80180834;
        func_801CDF1C(ptr, D_us_801808E4, 0);
        polarPlacePartsWithAngvel(ptr);
        ptr = D_us_80180A9C;
        func_801CDF1C(ptr, D_us_80180AB8, 1);
        polarPlacePartsWithAngvel(ptr);
        polarPlacePartsList(D_us_8018081C);
        if (!self->ext.death2.timer) {
            facing = (GetSideToPlayer() & 1) ^ 1;
            if (facing == self->facingLeft && GetDistanceToPlayerX() > 0x50) {
                func_801CE1E8(4);
            } else {
                func_801CE1E8(3);
            }
        } else {
            self->ext.death2.timer--;
            if (self->hitFlags & 3) {
                func_801CE1E8(5);
            }
        }
        break;
    case 3:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY -= self->velocityY / 16;
        ptr = D_us_80180834;
        func_801CDF1C(ptr, D_us_8018095C, 0);
        polarPlacePartsWithAngvel(ptr);
        ptr = D_us_80180A9C;
        func_801CDF1C(ptr, D_us_80180AB8, 1);
        polarPlacePartsWithAngvel(ptr);
        polarPlacePartsList(D_us_8018081C);
        temp = self->ext.death2.unkB0[0];
        if (temp > 1 && temp < 5) {
            D_us_80180788 = 1;
        } else {
            D_us_80180788 = 0;
        }
        if (!self->ext.death2.unkB4[0] && self->ext.death2.unkB0[0] == 2) {
            self->velocityY = FIX(4);
            PlaySfxPositional(SFX_BONE_SWORD_SWISH_A);
        }
        if (!self->ext.death2.unkB4[0] && !self->ext.death2.unkB0[0]) {
            func_801CE1E8(2);
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            ptr = D_us_80180834;
            func_801CDF1C(ptr, D_us_801809E4, 0);
            polarPlacePartsWithAngvel(ptr);
            if (!self->ext.death2.unkB4[0] && !self->ext.death2.unkB0[0]) {
                self->step_s++;
            }
            if (!self->ext.death2.unkB4[0] && self->ext.death2.unkB0[0] == 3) {
                D_us_80180784 = 1;
            }
            break;
        case 1:
            if (!D_us_80180784) {
                func_801CE1E8(2);
            }
            break;
        }
        ptr = D_us_80180A9C;
        func_801CDF1C(ptr, D_us_80180AB8, 1);
        polarPlacePartsWithAngvel(ptr);
        polarPlacePartsList(D_us_8018081C);
        break;
    case 5:
        if (!self->step_s) {
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(2);
            } else {
                self->velocityX = FIX(-2);
            }
            self->velocityY = 0;
            self->step_s++;
        }
        MoveEntity();
        self->velocityX -= self->velocityX >> 4;
        ptr = D_us_80180834;
        func_801CDF1C(ptr, D_us_80180A34, 0);
        polarPlacePartsWithAngvel(ptr);
        polarPlacePartsList(D_us_8018081C);
        if (!self->ext.death2.unkB4[0] && !self->ext.death2.unkB0[0]) {
            func_801CE1E8(2);
            facing = (GetSideToPlayer() & 1) ^ 1;
            if (facing == self->facingLeft && GetDistanceToPlayerX() > 0x50) {
                func_801CE1E8(4);
            } else {
                func_801CE1E8(3);
            }
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            g_BossMgrState |= BOSS_MGR_DEATH_DEFEAT;
            self->hitboxState = 0;
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(2);
            } else {
                self->velocityX = FIX(-2);
            }
            self->velocityY = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityX -= self->velocityX >> 4;
            ptr = D_us_80180834;
            func_801CDF1C(ptr, D_us_80180A34, 0);
            polarPlacePartsWithAngvel(ptr);
            polarPlacePartsList(D_us_8018081C);
            if (!self->ext.death2.unkB4[0] && !self->ext.death2.unkB0[0]) {
                self->step_s++;
            }
            break;
        case 2:
            ptr = D_us_80180844;
            func_801CDF1C(ptr, D_us_80180A84, 0);
            polarPlacePartsWithAngvel(ptr);
            if (!self->ext.death2.unkB4[0] && !self->ext.death2.unkB0[0]) {
                self->ext.death2.timer = 0x40;
                g_BossMgrState |= BOSS_MGR_DEATH_UNK_20;
                self->velocityX = 0;
                self->step_s++;
            }
            break;
        case 3:
            if (!--self->ext.death2.timer) {
                self->step_s++;
                self->ext.death2.timer = 0x80;
                g_api.PlaySfx(SFX_BOSS_LARGE_FLAMES);
            }
            break;
        case 4:
            ent = AllocEntity(&g_Entities[64], &g_Entities[256]);
            if (ent != NULL) {
                CreateEntityFromEntity(E_ID(UNK_1F), self, ent);
                ent->params = 1;
                ent->posY.i.hi = 0xF0;
                ent->posX.i.hi += (rand() & 0x1F) - 0x10;
                ent->zPriority =
                    self->zPriority + 8 - (self->ext.death2.timer >> 4);
            }
            if (!--self->ext.death2.timer) {
                self->animCurFrame = 0;
                self->hitboxState = 0;
                g_BossMgrState |= BOSS_MGR_DEATH_REWARD_READY;
                self->step_s++;
            }
            break;
        case 5:
            break;
        }
        break;
    case 0xFF:
#include "../../st/pad2_anim_debug.h"
    }
    for (ptr = D_us_8018081C; *ptr; ptr++) {
        ent = self + *ptr;
        ent->facingLeft = self->facingLeft;
        ent->ext.death2.unkA8 = 0;
    }
    x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (self->velocityX < 0) {
        if (x < 0x20) {
            self->posX.i.hi = 0x20 - g_Tilemap.scrollX.i.hi;
        }
    } else if (x > 0x1E0) {
        self->posX.i.hi = 0x1E0 - g_Tilemap.scrollX.i.hi;
    }
    if (self->velocityY < 0) {
        if (y < 0x30) {
            self->posY.i.hi = 0x30 - g_Tilemap.scrollY.i.hi;
        }
    } else if (y > 0xB0) {
        self->posY.i.hi = 0xB0 - g_Tilemap.scrollY.i.hi;
    }
}

INCLUDE_ASM("boss/rbo2_psp/nonmatchings/rbo2_psp/unk_12AE8", func_us_8019E558);

INCLUDE_ASM("boss/rbo2_psp/nonmatchings/rbo2_psp/unk_12AE8", func_us_8019E920);

INCLUDE_ASM("boss/rbo2_psp/nonmatchings/rbo2_psp/unk_12AE8", func_us_8019ECCC);
