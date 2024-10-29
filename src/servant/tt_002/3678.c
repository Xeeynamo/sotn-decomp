// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>

extern s32 s_ServantId;
extern u16 D_us_801722E8[];
// During cleanup, rename this.  May not actually be this familiar, unknown
// where it's set
extern Entity thisFamiliar;
extern s32 s_zPriority;
extern FamiliarStats s_FaerieStats;
extern s32 D_us_8017931C;
extern s32 D_us_80179320;
extern s32 D_us_80179310;
extern s16 D_us_80179314;
extern s16 D_us_80179318;
extern s32 s_AllowedAngle;
extern s32 s_AngleToTarget;
extern s32 s_DistToTargetLocation;
extern s16 s_TargetLocOffset_calc;
extern s32 s_TargetLocationX;
extern s32 s_TargetLocationX_calc;
extern s32 s_TargetLocationY;
extern s32 s_TargetLocationY_calc;

// this may actually be a multi dimensional array instead of a struct
typedef struct {
    s16 unk0;
    s16 unk2;
} UnkFaerieStruct;

extern UnkFaerieStruct D_us_80172368[];
extern AnimationFrame* D_us_80172B14[];

void func_us_801739C8(Entity*);
void func_us_80173D60(Entity*);
void func_us_80173994(Entity*, s32);

static s16 CalculateAngleToEntity(Entity* entity, s16 targetX, s16 targetY);
static s32 CalculateDistance(Entity* entity, s32 targetX, s32 targetY);
static s16 GetTargetPositionWithDistanceBuffer(
    s16 currentX, s16 targetX, s16 distanceBuffer);

void func_us_801739D0(Entity* arg0) {
    if (!arg0->ext.faerie.unk7E) {

        switch (arg0->entityId) {
        case 0xD1:
        case 0xD8:
            arg0->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;

            func_us_80173994(arg0, 0xE);

            arg0->ext.faerie.randomMovementAngle = rand() % 4096;
            arg0->ext.faerie.targetAngle = 0;
            arg0->ext.faerie.unk88 = 8;
            arg0->ext.faerie.maxAngle = 0x20;
            arg0->step++;
            break;
        case 0xD9:
            // loc 0xD8
            arg0->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;
            arg0->step++;
            break;
        }
    } else {
        switch (arg0->entityId) {
        case 0xD1:
            arg0->ext.faerie.unk96 = 0x78;
            // fallthrough
        case 0xD2:
        case 0xD3:
        case 0xD4:
        case 0xD5:
        case 0xD6:
        case 0xD7:
        case 0xDA:
        case 0xDB:
            arg0->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;
            func_us_80173994(arg0, 0xE);
            arg0->step++;
            break;
        case 0xD9:
            arg0->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;
            arg0->step++;
        }
    }
    arg0->ext.faerie.unk7E = arg0->entityId;
    D_us_8017931C = 0;
}

// This is a duplicate CreateEventEntity which is lower in the file, but we need
// both to match the binary for PSX
void CreateEventEntity_Dupe(Entity* entityParent, s32 entityId, s32 params) {
    Entity* entity;
    s32 i;

    for (i = 0; i < 3; i++) {
        entity = &g_Entities[5 + i];
        if (!entity->entityId) {
            break;
        }
    }

    if (!entity->entityId) {
        DestroyEntity(entity);
        entity->entityId = entityId;
        entity->zPriority = entityParent->zPriority;
        entity->facingLeft = entityParent->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX.val = entityParent->posX.val;
        entity->posY.val = entityParent->posY.val;
        // Not necessarily making batFamBlueTrail here, but
        // that's an Ext that works. Just needs parent at 0x8C.
        entity->ext.batFamBlueTrail.parent = entityParent;
        entity->params = params;
    }
}

void func_us_80173BD0(Entity* arg0) {
    if (abs(arg0->velocityY) > abs(arg0->velocityX)) {
        if (abs(arg0->velocityY) < FIX(0.5)) {
            if (arg0->ext.faerie.unk80 == 1) {
                arg0->ext.faerie.unk80 = 0;
                func_us_80173994(arg0, 0x29);
            } else if (arg0->ext.faerie.unk80 == 2) {
                arg0->ext.faerie.unk80 = 0;
                func_us_80173994(arg0, 0xE);
            }
        } else if (abs(arg0->velocityY) > FIX(1)) {
            if (arg0->velocityY >= 0) {
                arg0->ext.faerie.unk80 = 2;
                func_us_80173994(arg0, 0xB);
            } else {
                arg0->ext.faerie.unk80 = 2;
                func_us_80173994(arg0, 0xC);
            }
        }
    } else {
        if (abs(arg0->velocityX) > FIX(0.5625)) {
            if (arg0->ext.faerie.unk80 == 0) {
                arg0->ext.faerie.unk80 = 1;
                func_us_80173994(arg0, 0xF);
            } else if (arg0->ext.faerie.unk80 == 2) {
                arg0->ext.faerie.unk80 = 0;
                func_us_80173994(arg0, 0xE);
            }
        } else if (abs(arg0->velocityX) < FIX(0.375)) {
            if (arg0->ext.faerie.unk80 == 1) {
                arg0->ext.faerie.unk80 = 0;
                func_us_80173994(arg0, 0x29);
            } else if (arg0->ext.faerie.unk80 == 2) {
                arg0->ext.faerie.unk80 = 0;
                func_us_80173994(arg0, 0xE);
            }
        }
        if (abs(arg0->velocityX) > FIX(0.5)) {
            if (arg0->velocityX >= 0) {
                arg0->facingLeft = 1;
            } else {
                arg0->facingLeft = 0;
            }
        }
    }
}

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80173D60);

void func_us_801746E8(InitializeMode mode) {
    u16* src;
    u16* dst;
    RECT rect;
    s32 i;
    SpriteParts** spriteBanks;
    Entity* entity;

    s_ServantId = g_Servant;

    if ((mode == MENU_SWITCH_SERVANT) || (mode == MENU_SAME_SERVANT)) {
        ProcessEvent(NULL, true);
        if (mode == MENU_SAME_SERVANT) {
            return;
        }
    }

    dst = &g_Clut[CLUT_INDEX_SERVANT];
    src = D_us_801722E8; // clut data for faerie, will rename at data import
    for (i = 0; i < 0x100; i++) {
        *dst++ = *src++;
    }

    rect.x = 0;
    rect.w = 0x100;
    rect.h = 1;
    rect.y = 0xF4;

    dst = &g_Clut[CLUT_INDEX_SERVANT];
    LoadImage(&rect, (u_long*)dst);

    spriteBanks = g_api.o.spriteBanks;
    spriteBanks += 20;
    *spriteBanks = (SpriteParts*)g_ServantSpriteParts;

    entity = &thisFamiliar;

    DestroyEntity(entity);
    entity->unk5A = 0x6C;
    entity->palette = 0x140;
    entity->animSet = ANIMSET_OVL(20);
    entity->zPriority = PLAYER.zPriority - 2;
    entity->facingLeft = PLAYER.facingLeft;
    entity->params = 0;

    if (mode == MENU_SWITCH_SERVANT) {

// PSP version does this in 2 chunks, the PSX version uses an lw instruction
#ifdef VERSION_PSP
        if (D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_20 ||
            D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_40) {
#else
        if (LOW(D_8003C708.flags) &
            (LAYOUT_RECT_PARAMS_UNKNOWN_20 | LAYOUT_RECT_PARAMS_UNKNOWN_40)) {
#endif

            entity->entityId = ENTITY_ID_SERVANT;
        } else {
            entity->entityId = 0xD8;
        }
        entity->posX.val = FIX(128);
        entity->posY.val = FIX(-32);
    } else {
        entity->entityId = ENTITY_ID_SERVANT;
        if (D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_20) {
            if (ServantUnk0()) {
                entity->posX.val = FIX(192);
            } else {
                entity->posX.val = FIX(64);
            }
            entity->posY.val = FIX(160);
        } else {
            entity->posX.val =
                PLAYER.posX.val + (PLAYER.facingLeft ? FIX(24) : FIX(-24));
            entity->posY.val = PLAYER.posY.val + FIX(-32);
        }
    }

    s_zPriority = (s32)entity->zPriority;
    g_api.GetServantStats(entity, 0, 0, &s_FaerieStats);

    entity++;
    DestroyEntity(entity);
    entity->entityId = 0xD9;
    entity->unk5A = 0x6C;
    entity->palette = 0x140;
    entity->animSet = ANIMSET_OVL(20);
    entity->zPriority = PLAYER.zPriority - 3;
    entity->facingLeft = PLAYER.facingLeft;
    entity->params = 0;

    D_us_8017931C = 0;
    D_us_80179320 = 0;
    g_api.GetServantStats(entity, 0, 0, &s_FaerieStats);
}

void func_us_80174998(Entity* self) {
    g_api.GetServantStats(self, 0, 0, &s_FaerieStats);

    if (D_us_80179320) {
        self->zPriority = PLAYER.zPriority - 2;
        s_zPriority = self->zPriority;
    }

    if (D_8003C708.flags & FLAG_UNK_20) {
        switch (ServantUnk0()) {
        case 0:
            s_TargetLocationX = 0x40;
            break;
        case 1:
            s_TargetLocationX = 0xC0;
            break;
        case 2:
            s_TargetLocationX = self->posX.i.hi > 0x80 ? 0xC0 : 0x40;
            break;
        }
        s_TargetLocationY = 0xA0;
    } else {
        s_TargetLocOffset_calc = -0x18;
        if (PLAYER.facingLeft) {
            s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
        }
        s_TargetLocationX_calc = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
        s_TargetLocationY_calc = PLAYER.posY.i.hi - 0x20;
        s_AngleToTarget = self->ext.faerie.randomMovementAngle;

        self->ext.faerie.randomMovementAngle += 0x10;
        self->ext.faerie.randomMovementAngle &= 0xfff;
        s_DistToTargetLocation = self->ext.faerie.unk88;

        s_TargetLocationX =
            s_TargetLocationX_calc +
            ((rcos(s_AngleToTarget / 2) * s_DistToTargetLocation) >> 0xC);
        s_TargetLocationY =
            s_TargetLocationY_calc -
            ((rsin(s_AngleToTarget) * (s_DistToTargetLocation / 2)) >> 0xC);
    }
    switch (self->step) {
    case 0:
        func_us_801739D0(self);
        self->ext.faerie.unk80 = 0;
        func_us_80173994(self, 0xE);

        D_us_80179310 = g_Status.hp;
        D_us_80179314 = 0;
        D_us_80179318 = 0;
        self->ext.faerie.unkCounter = 0;
        break;
    case 1:
        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = GetTargetPositionWithDistanceBuffer(
            s_AngleToTarget, self->ext.faerie.targetAngle,
            self->ext.faerie.maxAngle);
        self->ext.faerie.targetAngle = s_AllowedAngle;

        s_DistToTargetLocation =
            CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);

        if (s_DistToTargetLocation < 0x28) {
            self->velocityY = -(rsin(s_AllowedAngle) << 3);
            self->velocityX = rcos(s_AllowedAngle) << 3;
            self->ext.faerie.maxAngle = 0x20;
        } else if (s_DistToTargetLocation < 0x3C) {
            self->velocityY = -(rsin(s_AllowedAngle) << 4);
            self->velocityX = rcos(s_AllowedAngle) << 4;
            self->ext.faerie.maxAngle = 0x40;
        } else if (s_DistToTargetLocation < 0x64) {
            self->velocityY = -(rsin(s_AllowedAngle) << 5);
            self->velocityX = rcos(s_AllowedAngle) << 5;
            self->ext.faerie.maxAngle = 0x60;
        } else if (s_DistToTargetLocation < 0x100) {
            self->velocityY = -(rsin(s_AllowedAngle) << 6);
            self->velocityX = rcos(s_AllowedAngle) << 6;
            self->ext.faerie.maxAngle = 0x80;
        } else {
            self->velocityX = (s_TargetLocationX - self->posX.i.hi) << 0xE;
            self->velocityY = (s_TargetLocationY - self->posY.i.hi) << 0xE;
            self->ext.faerie.maxAngle = 0x80;
        }

        func_us_80173BD0(self);

        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;

        if (!g_CutsceneHasControl && !IsMovementAllowed(1) &&
            !CheckAllEntitiesValid() && !(D_8003C708.flags & FLAG_UNK_20)) {
            self->ext.faerie.unkCounter += 1;
        } else {
            self->ext.faerie.unkCounter = 0;
        }
        if (self->ext.faerie.unkCounter > 0x708) {
            self->entityId = 0xDA;
            self->step = 0;
            return;
        }
        if (D_us_8017931C >= 2) {
            self->entityId = 0xDB;
            self->step = 0;
            self->params = D_us_8017931C - 2;
        }
        break;
    }

    ProcessEvent(self, false);

    if (!g_CutsceneHasControl) {
        func_us_80173D60(self);
    }
    func_us_801739C8(self);
    ServantUpdateAnim(self, NULL, D_us_80172B14);
}

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80174F0C);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_801753E4);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80175730);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80175A78);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80175DBC);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80176178);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80176504);

void func_us_80176B6C(Entity* self) {
    s32 temp_unk0;
    s32 temp_unk2;
    s32 i;
#ifdef VERSION_PSP
    s32 temp_zPriority;
#else
    s16 temp_zPriority;
#endif

    if (!self->step) {
        func_us_801739D0(self);
        self->ext.faerieUnk0.unk7C = &thisFamiliar;
        self->step += 1;
    }
    self->posX.val = self->ext.faerieUnk0.unk7C->posX.val;
    self->posY.val = self->ext.faerieUnk0.unk7C->posY.val;
    self->facingLeft = self->ext.faerieUnk0.unk7C->facingLeft;

    for (i = 6; i <= 0x2D; i++) {
        if (self->ext.faerieUnk0.unk7C->anim == D_us_80172B14[i])
            break;
    }

    temp_unk0 = abs(D_us_80172368[i - 6].unk0);
    temp_unk2 = D_us_80172368[i - 6].unk2;

    func_us_80173994(self, temp_unk0);

    if (temp_unk2) {
        temp_zPriority = s_zPriority - 1;
    } else {
        temp_zPriority = s_zPriority + 1;
    }

    self->zPriority = temp_zPriority;

    ServantUpdateAnim(self, 0, D_us_80172B14);
}

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80176C98);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80177380);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80177958);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80177AC4);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80177F64);

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80177F84);

#ifndef VERSION_PSP
#include "../servant_update_anim.h"
#endif

#include "../../destroy_entity.h"

#ifndef VERSION_PSP
#include "../accumulate_toward_zero.h"
#include "../search_for_entity_in_range.h"
#endif

#include "../calculate_angle_to_entity.h"

#include "../get_target_position_with_distance_buffer.h"

#ifndef VERSION_PSP
#include "../calculate_distance.h"

// There is some .rodata jumptable stuff going on with ProcessSfxState
// where the table is in the middle of the .rodata function
INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80178A30);
// #include "../play_sfx.h"
#endif

#include "../process_event.h"

#include "../create_event_entity.h"

#include "../is_movement_allowed.h"

#ifndef VERSION_PSP
#include "../check_all_entities_valid.h"
#endif

#include "../servant_unk0.h"

INCLUDE_RODATA("servant/tt_002/nonmatchings/3678", func_us_80173994);

INCLUDE_RODATA("servant/tt_002/nonmatchings/3678", func_us_801739C8);
