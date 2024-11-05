// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>
#include "sfx.h"
#include "items.h"

extern s32 s_ServantId;
extern u16 g_FaerieClut[];
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

extern u8 D_80097A1A[];
extern s32 D_us_80172BCC;
extern s32 D_us_80172BD8;

extern s32 D_us_80172BE4[];
extern s16 D_us_80172494[];
extern s16 D_us_801724C4[];
extern s32 D_us_80172BD0;

extern s32 D_800973FC;
// this is likely incorrect typing
extern s32 D_80097420[];
extern Unkstruct_801724CC D_us_801724CC[];
extern s32 D_us_80172BD4;
extern s32 D_us_80172BDC;

// this may actually be a multi dimensional array instead of a struct
typedef struct {
    s16 unk0;
    s16 unk2;
} UnkFaerieStruct;

extern UnkFaerieStruct D_us_80172368[];
extern AnimationFrame* D_us_80172B14[];

void func_us_80173994(Entity*, s32);
void func_us_801739C8(Entity*);
void func_us_80173D60(Entity*);

static void ServantInit(InitializeMode mode);
static void func_us_80174998(Entity* self);
static void func_us_80174F0C(Entity* self);
static void func_us_801753E4(Entity* self);
static void func_us_80175730(Entity* self);
static void func_us_80175A78(Entity* self);
static void func_us_80175DBC(Entity* self);
static void func_us_80176178(Entity* self);
static void func_us_80176504(Entity* self);
static void func_us_80176B6C(Entity* self);
static void func_us_80176C98(Entity* self);
static void func_us_80177380(Entity* self);
static void func_us_80177958(Entity* self);
static void func_us_80177AC4(Entity* self);
static void func_us_80177F64(Entity* self);
static void func_us_80177F84(Entity* self);

ServantDesc faerie_ServantDesc = {
    ServantInit,      func_us_80174998, func_us_80174F0C, func_us_801753E4,
    func_us_80175730, func_us_80175A78, func_us_80175DBC, func_us_80176178,
    func_us_80176504, func_us_80176B6C, func_us_80176C98, func_us_80177380,
    func_us_80177958, func_us_80177AC4, func_us_80177F64, func_us_80177F84};

static s16 CalculateAngleToEntity(Entity* entity, s16 targetX, s16 targetY);
static s32 CalculateDistance(Entity* entity, s32 targetX, s32 targetY);
static s16 GetTargetPositionWithDistanceBuffer(
    s16 currentX, s16 targetX, s16 distanceBuffer);

static void SetAnimationFrame(Entity* self, s32 animationIndex) {
    if (self->anim != D_us_80172B14[animationIndex]) {
        self->anim = D_us_80172B14[animationIndex];
        self->animFrameIdx = 0;
        self->animFrameDuration = 0;
    }
}

void func_us_801739C8(Entity* arg0) {}

void func_us_801739D0(Entity* arg0) {
    if (!arg0->ext.faerie.unk7E) {

        switch (arg0->entityId) {
        case ENTITY_ID_SERVANT:
        case 0xD8:
            arg0->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;

            SetAnimationFrame(arg0, 0xE);

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
        case ENTITY_ID_SERVANT:
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
            SetAnimationFrame(arg0, 0xE);
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
// both to match the binary for PSX.
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
                SetAnimationFrame(arg0, 0x29);
            } else if (arg0->ext.faerie.unk80 == 2) {
                arg0->ext.faerie.unk80 = 0;
                SetAnimationFrame(arg0, 0xE);
            }
        } else if (abs(arg0->velocityY) > FIX(1)) {
            if (arg0->velocityY >= 0) {
                arg0->ext.faerie.unk80 = 2;
                SetAnimationFrame(arg0, 0xB);
            } else {
                arg0->ext.faerie.unk80 = 2;
                SetAnimationFrame(arg0, 0xC);
            }
        }
    } else {
        if (abs(arg0->velocityX) > FIX(0.5625)) {
            if (arg0->ext.faerie.unk80 == 0) {
                arg0->ext.faerie.unk80 = 1;
                SetAnimationFrame(arg0, 0xF);
            } else if (arg0->ext.faerie.unk80 == 2) {
                arg0->ext.faerie.unk80 = 0;
                SetAnimationFrame(arg0, 0xE);
            }
        } else if (abs(arg0->velocityX) < FIX(0.375)) {
            if (arg0->ext.faerie.unk80 == 1) {
                arg0->ext.faerie.unk80 = 0;
                SetAnimationFrame(arg0, 0x29);
            } else if (arg0->ext.faerie.unk80 == 2) {
                arg0->ext.faerie.unk80 = 0;
                SetAnimationFrame(arg0, 0xE);
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

void ServantInit(InitializeMode mode) {
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
    src = g_FaerieClut; // clut data for faerie, will rename at data import
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
        SetAnimationFrame(self, 0xE);

        D_us_80179310 = g_Status.hp;
        D_us_80179314 = 0;
        D_us_80179318 = 0;
        self->ext.faerie.unkCounterA0 = 0;
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
            self->ext.faerie.unkCounterA0 += 1;
        } else {
            self->ext.faerie.unkCounterA0 = 0;
        }
        if (self->ext.faerie.unkCounterA0 > 0x708) {
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

void func_us_80174F0C(Entity* self) {
    s32 i;

    switch (self->step) {
    case 0:
        func_us_801739D0(self);
        self->ext.faerie.frameCounter = 0;
        break;
    case 1:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter <= 24) {
            break;
        }
        self->step++;
        // fallthrough
    case 2:
        if (!g_Status.equipHandCount[ITEM_LIFE_APPLE]) {
            self->step = 0x5A;
            break;
        }
        self->step++;
        // fallthrough
    case 3:
        if (!g_unkGraphicsStruct.unk20) {
            g_Status.equipHandCount[ITEM_LIFE_APPLE]--;
            g_unkGraphicsStruct.unk20 = 0xfff;
            self->step++;
        }
        break;
    case 4:
        s_TargetLocationX_calc = PLAYER.posX.i.hi;
        s_TargetLocationY_calc = PLAYER.posY.i.hi - 0x20;
        s_AngleToTarget = self->ext.faerie.randomMovementAngle;
        self->ext.faerie.randomMovementAngle += 0x10;
        self->ext.faerie.randomMovementAngle &= 0xFFF;
        s_DistToTargetLocation = self->ext.faerie.unk88;
        s_TargetLocationX =
            s_TargetLocationX_calc +
            ((rcos(s_AngleToTarget / 2) * s_DistToTargetLocation) >> 0xC);
        s_TargetLocationY =
            s_TargetLocationY_calc -
            ((rsin(s_AngleToTarget) * (s_DistToTargetLocation / 2)) >> 0xC);
        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = GetTargetPositionWithDistanceBuffer(
            s_AngleToTarget, self->ext.faerie.targetAngle, 0x180);
        self->ext.faerie.targetAngle = s_AllowedAngle;
        self->velocityY = -(rsin(s_AllowedAngle) << 5);
        self->velocityX = rcos(s_AllowedAngle) << 5;
        func_us_80173BD0(self);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        s_DistToTargetLocation =
            CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);
        if (s_DistToTargetLocation < 2) {
            self->step++;
        }
        break;
    case 0x5:
        self->facingLeft = PLAYER.facingLeft;
        SetAnimationFrame(self, 0x13);
        if (s_ServantId == FAM_ACTIVE_YOUSEI) {
            g_api.PlaySfx(D_us_80172BD4);
        }
        self->step++;
        break;
    case 0x6:
        if (self->animFrameIdx == 0xA) {
            if (s_ServantId == FAM_ACTIVE_FAERIE) {
                g_api.PlaySfx(D_us_80172BD4);
            }
            self->step++;
        }
        break;
    case 0x7:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            CreateEventEntity_Dupe(self, 0xDF, 0);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    case 0x8:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            CreateEventEntity_Dupe(self, 0xDD, 0);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    case 0x9:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 90) {
            if (SearchForEntityInRange(1, 0x29)) {
                D_800973FC = 0;
            }

            for (i = 8; i < 0x40; i++) {
                DestroyEntity(&g_Entities[i]);
            }

            g_Status.hp = g_Status.hpMax;
            g_Status.mp = g_Status.mpMax;
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    case 0xA:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 90) {
            D_80097420[0] = 0;
            self->step++;
        }
        break;
    case 0xB:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            self->entityId = ENTITY_ID_SERVANT;
            self->step = 0;
            return;
        }
        break;

    case 0x5A:
        SetAnimationFrame(self, 0x20);
        g_api.PlaySfx(D_us_80172BDC);
        self->step++;
        break;
    case 0x5B:
        break;
    }

    ServantUpdateAnim(self, NULL, D_us_80172B14);
}

void func_us_801753E4(Entity* self) {
    const int paramOffset = 3;

    s32 rnd;
    s32 i;

    s_TargetLocOffset_calc = -0x18;
    if (!PLAYER.facingLeft) {
        s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
    }
    s_TargetLocationX = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
    s_TargetLocationY = PLAYER.posY.i.hi - 0x18;
    switch (self->step) {
    case 0:
        func_us_801739D0(self);
        SetAnimationFrame(self, 0xE);
        break;
    case 1:
        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = GetTargetPositionWithDistanceBuffer(
            s_AngleToTarget, self->ext.faerie.targetAngle, 0x180);
        self->ext.faerie.targetAngle = s_AllowedAngle;
        self->velocityY = -(rsin(s_AllowedAngle) << 5);
        self->velocityX = rcos(s_AllowedAngle) << 5;
        func_us_80173BD0(self);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        s_DistToTargetLocation =
            CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);
        if (s_DistToTargetLocation < 2) {
            self->step++;
        }
        break;
    case 2:
        self->facingLeft = PLAYER.facingLeft;
        if (D_80097A1A[paramOffset]) {
            SetAnimationFrame(self, 0x17);

            for (rnd = rand() % 0x100, i = 0; true; i++) {
                if (rnd <= D_us_80172BE4[i * 2]) {
                    g_api.PlaySfx(D_us_80172BE4[(i * 2) + 1]);
                    break;
                }
            }

            self->step++;
        } else {
            SetAnimationFrame(self, 0x10);
            g_api.PlaySfx(D_us_80172BD8);
            self->ext.faerie.frameCounter = 0;
            self->step += 2;
        }
        break;
    case 3:
        if (self->animFrameIdx == 5) {
            D_80097A1A[paramOffset]--;
            g_api.CreateEntFactoryFromEntity(
                self, FACTORY(0x37, paramOffset), 0);
            CreateEventEntity_Dupe(self, 0xDF, 1);
            g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            g_api.func_80102CD8(4);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    case 4:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            self->entityId = ENTITY_ID_SERVANT;
            self->step = 0;
            return;
        }
        break;
    }

    func_us_80173D60(self);
    ServantUpdateAnim(self, NULL, D_us_80172B14);
}

// This is a dupe of func_us_80175A78 with a slightly different offset
// for the create entity params
void func_us_80175730(Entity* self) {
    const int paramOffset = 1;

    s_TargetLocOffset_calc = -0x18;
    if (!PLAYER.facingLeft) {
        s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
    }
    s_TargetLocationX = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
    s_TargetLocationY = PLAYER.posY.i.hi - 0x18;
    switch (self->step) {
    case 0:
        func_us_801739D0(self);
        SetAnimationFrame(self, 0xE);
        break;

    case 1:
        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = GetTargetPositionWithDistanceBuffer(
            s_AngleToTarget, self->ext.faerie.targetAngle, 0x180);
        self->ext.faerie.targetAngle = s_AllowedAngle;
        self->velocityY = -(rsin(s_AllowedAngle) << 5);
        self->velocityX = rcos(s_AllowedAngle) << 5;
        func_us_80173BD0(self);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        s_DistToTargetLocation =
            CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);
        if (s_DistToTargetLocation < 2) {
            self->step++;
        }
        break;
    case 2:
        if (!D_80097A1A[paramOffset]) {
            SetAnimationFrame(self, 0x14);
            self->step = 5;
            break;
        }
        if (SearchForEntityInRange(1, 0x27)) {
            self->entityId = ENTITY_ID_SERVANT;
            self->step = 0;
            return;
        }
        SetAnimationFrame(self, 0x12);
        if (s_ServantId == FAM_ACTIVE_YOUSEI) {
            g_api.PlaySfx(D_us_80172BCC);
        }
        self->step++;
        break;

    case 3:
        self->facingLeft = PLAYER.facingLeft ? 0 : 1;
        if (self->animFrameIdx == 0xB) {
            if (s_ServantId == FAM_ACTIVE_FAERIE) {
                g_api.PlaySfx(D_us_80172BCC);
            }

            D_80097A1A[paramOffset]--;
            g_api.CreateEntFactoryFromEntity(
                self, FACTORY(0x37, paramOffset), 0);

            CreateEventEntity_Dupe(self, 0xDF, paramOffset + 3);
            self->ext.faerie.frameCounter = 0;
            self->step++;
            break;
        }
        break;
    case 4:
    case 6:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            self->entityId = ENTITY_ID_SERVANT;
            self->step = 0;
            return;
        }
        break;
    case 5:
        self->facingLeft = PLAYER.facingLeft;
        if (self->animFrameIdx == 0x20) {
            g_api.PlaySfx(D_us_80172BD8);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    }

    func_us_80173D60(self);
    ServantUpdateAnim(self, NULL, D_us_80172B14);
}

// This is a dupe of func_us_80175730 with a slightly different offset
// for the create entity params
void func_us_80175A78(Entity* self) {
    const int paramOffset = 0;

    s_TargetLocOffset_calc = -0x18;
    if (!PLAYER.facingLeft) {
        s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
    }
    s_TargetLocationX = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
    s_TargetLocationY = PLAYER.posY.i.hi - 0x18;
    switch (self->step) {
    case 0:
        func_us_801739D0(self);
        SetAnimationFrame(self, 0xE);
        break;

    case 1:
        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = GetTargetPositionWithDistanceBuffer(
            s_AngleToTarget, self->ext.faerie.targetAngle, 0x180);
        self->ext.faerie.targetAngle = s_AllowedAngle;
        self->velocityY = -(rsin(s_AllowedAngle) << 5);
        self->velocityX = rcos(s_AllowedAngle) << 5;
        func_us_80173BD0(self);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        s_DistToTargetLocation =
            CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);
        if (s_DistToTargetLocation < 2) {
            self->step++;
        }
        break;
    case 2:
        if (!D_80097A1A[paramOffset]) {
            SetAnimationFrame(self, 0x14);
            self->step = 5;
            break;
        }
        if (SearchForEntityInRange(1, 0x27)) {
            self->entityId = ENTITY_ID_SERVANT;
            self->step = 0;
            return;
        }
        SetAnimationFrame(self, 0x12);
        if (s_ServantId == FAM_ACTIVE_YOUSEI) {
            g_api.PlaySfx(D_us_80172BCC);
        }
        self->step++;
        break;

    case 3:
        self->facingLeft = PLAYER.facingLeft ? 0 : 1;
        if (self->animFrameIdx == 0xB) {
            if (s_ServantId == FAM_ACTIVE_FAERIE) {
                g_api.PlaySfx(D_us_80172BCC);
            }

            D_80097A1A[paramOffset]--;
            g_api.CreateEntFactoryFromEntity(
                self, FACTORY(0x37, paramOffset), 0);

            CreateEventEntity_Dupe(self, 0xDF, paramOffset + 3);
            self->ext.faerie.frameCounter = 0;
            self->step++;
            break;
        }
        break;
    case 4:
    case 6:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            self->entityId = ENTITY_ID_SERVANT;
            self->step = 0;
            return;
        }
        break;
    case 5:
        self->facingLeft = PLAYER.facingLeft;
        if (self->animFrameIdx == 0x20) {
            g_api.PlaySfx(D_us_80172BD8);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    }

    func_us_80173D60(self);
    ServantUpdateAnim(self, NULL, D_us_80172B14);
}

void func_us_80175DBC(Entity* self) {
    s32 i;
    s32 rnd;
    s32 temp;

    s_TargetLocOffset_calc = -0x18;
    if (!PLAYER.facingLeft) {
        s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
    }
    s_TargetLocationX = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
    s_TargetLocationY = PLAYER.posY.i.hi - 0x18;
    switch (self->step) {
    case 0:
        func_us_801739D0(self);
        SetAnimationFrame(self, 0xE);
        break;
    case 1:
        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = GetTargetPositionWithDistanceBuffer(
            s_AngleToTarget, self->ext.faerie.targetAngle, 0x180);
        self->ext.faerie.targetAngle = s_AllowedAngle;
        self->velocityY = -(rsin(s_AllowedAngle) << 5);
        self->velocityX = rcos(s_AllowedAngle) << 5;
        func_us_80173BD0(self);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        s_DistToTargetLocation =
            CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);
        if (s_DistToTargetLocation < 2) {
            self->step++;
        }
        break;
    case 2:
        self->facingLeft = PLAYER.facingLeft;
        if (!g_Status.equipHandCount[D_us_80172494[self->params * 4 + 1]]) {
            SetAnimationFrame(self, 0x10);
            self->step = 5;
            break;
        }
        if (SearchForEntityInRange(1, 0x27)) {
            self->entityId = ENTITY_ID_SERVANT;
            self->step = 0;
            return;
        }

        SetAnimationFrame(self, 0x12);
        self->step++;
        break;
    case 3:
        if (PLAYER.facingLeft)
            temp = 0;
        else
            temp = 1;
        self->facingLeft = temp;

        if (self->animFrameIdx == 0xB) {
            for (rnd = rand() % 0x100, i = 0; true; i++) {
                if (rnd <= D_us_80172BE4[i * 2]) {
                    g_api.PlaySfx(D_us_80172BE4[(i * 2) + 1]);
                    break;
                }
            }

            g_Status.equipHandCount[D_us_80172494[self->params * 4 + 1]]--;

            g_api.CreateEntFactoryFromEntity(
                self, FACTORY(0x37, D_us_80172494[self->params * 4 + 2]), 0);
            CreateEventEntity_Dupe(
                self, 0xDF, D_us_80172494[self->params * 4 + 3]);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    case 4:
    case 6:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            self->entityId = ENTITY_ID_SERVANT;
            self->step = 0;
            return;
        }
        break;
    case 5:
        self->facingLeft = PLAYER.facingLeft;
        if (self->animFrameIdx == 0x20) {
            g_api.PlaySfx(D_us_80172BD8);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    }

    func_us_80173D60(self);
    ServantUpdateAnim(self, NULL, D_us_80172B14);
}

void func_us_80176178(Entity* self) {
    s32 temp;

    s_TargetLocOffset_calc = -0x18;
    if (!PLAYER.facingLeft) {
        s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
    }
    s_TargetLocationX = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
    s_TargetLocationY = PLAYER.posY.i.hi - 0x18;
    switch (self->step) {
    case 0:
        func_us_801739D0(self);
        SetAnimationFrame(self, 0xE);
        break;
    case 1:
        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = GetTargetPositionWithDistanceBuffer(
            s_AngleToTarget, self->ext.faerie.targetAngle, 0x180);
        self->ext.faerie.targetAngle = s_AllowedAngle;
        self->velocityY = -(rsin(s_AllowedAngle) << 5);
        self->velocityX = rcos(s_AllowedAngle) << 5;
        func_us_80173BD0(self);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        s_DistToTargetLocation =
            CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);
        if (s_DistToTargetLocation < 2) {
            self->step++;
        }
        break;
    case 2:
        if (!g_Status.equipHandCount[D_us_801724C4[self->params * 2]]) {
            if (self->params) {
                temp = 0;
            } else {
                temp = 1;
            }
            self->params = temp;
            if (!g_Status.equipHandCount[D_us_801724C4[self->params * 2]]) {
                SetAnimationFrame(self, 0x14);
                self->step = 5;
                break;
            }
        }

        if (SearchForEntityInRange(1, 0x27)) {
            self->entityId = ENTITY_ID_SERVANT;
            self->step = 0;
            return;
        }

        SetAnimationFrame(self, 0x12);
        self->step++;
        break;
    case 3:
        self->facingLeft = PLAYER.facingLeft ? 0 : 1;
        if (self->animFrameIdx == 0xB) {
            g_api.PlaySfx(D_us_80172BD0);
            g_Status.equipHandCount[D_us_801724C4[self->params * 2]]--;
            g_api.CreateEntFactoryFromEntity(
                self, FACTORY(0x37, D_us_801724C4[self->params * 2 + 1]), 0);
            CreateEventEntity_Dupe(self, 0xDF, 2);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    case 4:
    case 6:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            self->entityId = ENTITY_ID_SERVANT;
            self->step = 0;
            return;
        }
        break;
    case 5:
        self->facingLeft = PLAYER.facingLeft;
        if (self->animFrameIdx == 0x20) {
            g_api.PlaySfx(D_us_80172BD8);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    }

    func_us_80173D60(self);
    ServantUpdateAnim(self, NULL, D_us_80172B14);
}

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

    SetAnimationFrame(self, temp_unk0);

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

// It's likely that this Entity uses a different extension as
// randomMovementAngle and targetAngle don't make sense
// but I need more context to get it right.
void func_us_80177AC4(Entity* arg0) {
    Primitive* currentPrim;
    s32 i;
    s32 var_v1;

    switch (arg0->step) {
    case 0:
        arg0->primIndex = g_api.AllocPrimitives(PRIM_G4, 10);
        if (arg0->primIndex == -1) {
            DestroyEntity(arg0);
            return;
        }
        arg0->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        arg0->posX.i.hi += arg0->facingLeft ? -4 : 4;

        currentPrim = &g_PrimBuf[arg0->primIndex];

        currentPrim->r1 = currentPrim->r3 = currentPrim->g1 = currentPrim->g3 =
            currentPrim->b1 = currentPrim->b3 = 0xFF;
        currentPrim->priority = 0x1C0;
        currentPrim->drawMode =
            FLAG_DRAW_UNK400 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK10 |
            FLAG_DRAW_ROTZ | FLAG_DRAW_ROTX;

        currentPrim = currentPrim->next;

        currentPrim->r1 = currentPrim->r3 = currentPrim->g1 = currentPrim->g3 =
            currentPrim->b1 = currentPrim->b3 = 0xFF;
        currentPrim->priority = 0x1C0;
        currentPrim->drawMode =
            FLAG_DRAW_UNK400 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK10 |
            FLAG_DRAW_ROTZ | FLAG_DRAW_ROTX;

        for (i = 0; i < 8; i++) {
            currentPrim = currentPrim->next;
            currentPrim->x0 = currentPrim->x1 = arg0->posX.i.hi;
            currentPrim->y0 = currentPrim->y1 = 0;
            currentPrim->x2 = arg0->posX.i.hi + ((rcos(i << 8) * 0x60) >> 0xC);
            currentPrim->x3 =
                arg0->posX.i.hi + ((rcos((i + 1) << 8) * 0x60) >> 0xC);
            currentPrim->y2 = (rsin(i << 8) * 3) << 5 >> 0xC;
            currentPrim->y3 = (rsin((i + 1) << 8) * 3) << 5 >> 0xC;
            currentPrim->priority = 0x1C0;
            currentPrim->drawMode =
                FLAG_DRAW_UNK400 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK10 |
                FLAG_DRAW_ROTZ | FLAG_DRAW_ROTX;
        }
        arg0->ext.faerie.unk80 = 0x10;
        arg0->ext.faerie.unk82 = 0;
        arg0->ext.faerie.randomMovementAngle = 0x40;
        arg0->ext.faerie.targetAngle = 0;
        arg0->step++;
        break;
    case 1:
        arg0->ext.faerie.targetAngle += 4;
        arg0->ext.faerie.unk82 += 0x10;

        if (arg0->ext.faerie.unk82 >= 0x100) {
            arg0->step++;
        }
        break;
    case 2:
        arg0->ext.faerie.unk7c++;
        if (arg0->ext.faerie.unk7c > 0xF) {
            arg0->step++;
        }
        break;
    case 3:
        arg0->ext.faerie.randomMovementAngle += 4;
        if (arg0->ext.faerie.randomMovementAngle >= 0x100) {
            arg0->ext.faerie.randomMovementAngle = 0xFF;
        }

        arg0->ext.faerie.unk80 += 4;
        if (arg0->ext.faerie.unk80 >= 0x100) {
            arg0->ext.faerie.unk7c = 0;
            arg0->step++;
        }
        break;
    case 4:
        arg0->ext.faerie.unk7c++;
        if (arg0->ext.faerie.unk7c > 60) {
            arg0->step++;
        }
        break;
    case 5:
        arg0->ext.faerie.targetAngle--;
        if (arg0->ext.faerie.targetAngle < 0) {
            arg0->ext.faerie.targetAngle = 0;
        }

        arg0->ext.faerie.randomMovementAngle -= 4;
        if (arg0->ext.faerie.randomMovementAngle <= 0x40) {
            arg0->ext.faerie.randomMovementAngle = 0x40;
        }

        arg0->ext.faerie.unk80 -= 8;
        if (arg0->ext.faerie.unk80 <= 0) {
            DestroyEntity(arg0);
            return;
        }
        break;
    }
    currentPrim = &g_PrimBuf[arg0->primIndex];

    var_v1 = arg0->posX.i.hi - arg0->ext.faerie.unk80;
    if (var_v1 < 0) {
        var_v1 = 0;
    }
    currentPrim->x0 = currentPrim->x2 = var_v1;
    currentPrim->x1 = currentPrim->x3 = arg0->posX.i.hi;
    currentPrim->y0 = currentPrim->y1 = 0;
    currentPrim->y2 = currentPrim->y3 = arg0->ext.faerie.unk82;
    currentPrim->r0 = currentPrim->r2 = currentPrim->g0 = currentPrim->g2 =
        currentPrim->b0 = currentPrim->b2 =
            arg0->ext.faerie.randomMovementAngle;

    currentPrim = currentPrim->next;

    var_v1 = arg0->posX.i.hi + arg0->ext.faerie.unk80;
    if (var_v1 > 0x100) {
        var_v1 = 0x100;
    }
    currentPrim->x0 = currentPrim->x2 = var_v1;
    currentPrim->x1 = currentPrim->x3 = arg0->posX.i.hi;
    currentPrim->y0 = currentPrim->y1 = 0;
    currentPrim->y2 = currentPrim->y3 = arg0->ext.faerie.unk82;
    currentPrim->r0 = currentPrim->r2 = currentPrim->g0 = currentPrim->g2 =
        currentPrim->b0 = currentPrim->b2 =
            arg0->ext.faerie.randomMovementAngle;

    for (i = 0; i < 8; i++) {
        currentPrim = currentPrim->next;

        currentPrim->r0 = currentPrim->r1 = currentPrim->g0 = currentPrim->g1 =
            currentPrim->b0 = currentPrim->b1 = arg0->ext.faerie.targetAngle;
        currentPrim->r2 = currentPrim->r3 = currentPrim->g2 = currentPrim->g3 =
            currentPrim->b2 = currentPrim->b3 = 0;
    }
}

INCLUDE_ASM("servant/tt_002/nonmatchings/3678", func_us_80177F64);

void func_us_80177F84(Entity* self) {
    FakePrim* fakePrim;
    s32 i;
    u16 posY2;
    s16 posX3;
    s32 posX;
    s16 posY;
    s16 posX2;
    u16 posX4;
    Unkstruct_801724CC* unkStruct;

    posX2 = self->posX.i.hi;
    posY = self->posY.i.hi;
    unkStruct = &D_us_801724CC[LOH(self->params)];
    switch (self->step) {
    case 0:
        self->primIndex =
            g_api.func_800EDB58(PRIM_TILE_ALT, unkStruct->count + 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        posX = posX2;
        self->flags = unkStruct->flags;
        fakePrim = (FakePrim*)&g_PrimBuf[self->primIndex];

        while (true) {
            fakePrim->drawMode = unkStruct->drawMode + DRAW_HIDE;
            fakePrim->priority = unkStruct->priority + PLAYER.zPriority;
            if (fakePrim->next == NULL) {
                fakePrim->w = 0;
                fakePrim->y0 = fakePrim->x0 = 0;
                fakePrim->drawMode &= ~DRAW_HIDE;
                break;
            }

            fakePrim->posX.i.hi = posX2;
            fakePrim->posY.i.hi = posY;
            fakePrim->posY.i.lo = 0;
            fakePrim->posX.i.lo = 0;
            switch (unkStruct->unk6) {
            case 0:
                if (!self->facingLeft) {
                    fakePrim->posX.i.hi = posX + 4;
                } else {
                    fakePrim->posX.i.hi = posX - 4;
                }
                fakePrim->posY.i.hi = posY - 0x1A;
                fakePrim->velocityX.val = ((rand() % 0x2000) - 0x1000) << 4;
                fakePrim->velocityY.val = 0;
                break;
            case 1:
                if (!self->facingLeft) {
                    posX3 = posX - 0x18;
                } else {
                    posX3 = posX + 0x18;
                }
                posY2 = posY + 0x10;
                fakePrim->posX.i.hi = (u16)(posX3 - 8 + (rand() % 16));
                fakePrim->posY.i.hi = posY2;
                fakePrim->velocityX.val = ((rand() % 0x2000) - 0x1000) << 4;
                fakePrim->velocityY.val = -((rand() % 0x1000) + 0x1800) << 4;
                fakePrim->delay = 0x2D;
                break;
            case 2:
                if (!self->facingLeft) {
                    posX4 = posX + 0xE;
                } else {
                    posX4 = posX - 0xE;
                }
                posY2 = posY - 8;
                fakePrim->posX.i.hi = posX4;
                fakePrim->posY.i.hi = posY2;
                fakePrim->velocityX.val = (rand() % 0x800) << 4;
                if (self->facingLeft) {
                    fakePrim->velocityX.val = -fakePrim->velocityX.val;
                }
                fakePrim->velocityY.val = -((rand() % 0x1000) + 0x800) << 4;
                fakePrim->delay = 0x28;
                break;
            }
            fakePrim->x0 = fakePrim->posX.i.hi;
            fakePrim->y0 = fakePrim->posY.i.hi;
            fakePrim->r0 = unkStruct->r;
            fakePrim->g0 = unkStruct->g;
            fakePrim->b0 = unkStruct->b;
            fakePrim->w = unkStruct->w;
            fakePrim->h = unkStruct->h;
            fakePrim = fakePrim->next;
        }
        self->step++;
    case 1:
        if (--self->ext.faerie.unk82 <= 0) {
            fakePrim = (FakePrim*)&g_PrimBuf[self->primIndex];
            for (i = 0; i < self->ext.faerie.unk80; i++) {
                fakePrim = fakePrim->next;
            }
            for (i = 0; i < unkStruct->unk2; i++) {
                fakePrim->drawMode &= ~DRAW_HIDE;
                fakePrim = fakePrim->next;
            }
            self->ext.faerie.unk80 += unkStruct->unk2;
            if (self->ext.faerie.unk80 >= unkStruct->count) {
                self->step++;
            }
            self->ext.faerie.unk82 = unkStruct->unk4;
        }
    case 2:
        self->ext.faerie.unk7E = 0;
        fakePrim = (FakePrim*)&g_PrimBuf[self->primIndex];

        while (true) {
            if (fakePrim->next == NULL) {
                fakePrim->w = 0;
                fakePrim->y0 = fakePrim->x0 = 0;
                fakePrim->drawMode &= ~DRAW_HIDE;
                break;
            }

            fakePrim->posX.i.hi = fakePrim->x0;
            fakePrim->posY.i.hi = fakePrim->y0;
            switch (unkStruct->unk6) {
            case 0:
                if (!(fakePrim->drawMode & DRAW_HIDE)) {
                    fakePrim->posX.val += fakePrim->velocityX.val;
                    fakePrim->posY.val += fakePrim->velocityY.val;
                    fakePrim->velocityX.val =
                        AccumulateTowardZero(fakePrim->velocityX.val, 0x1000);
                    fakePrim->velocityY.val -= FIX(2.0 / 16);
                    if (fakePrim->posY.i.hi < 0) {
                        fakePrim->drawMode |= DRAW_HIDE;
                    }
                }
                break;
            case 1:
                if (!(fakePrim->drawMode & DRAW_HIDE)) {
                    fakePrim->posX.val += fakePrim->velocityX.val;
                    fakePrim->posY.val += fakePrim->velocityY.val;
                    fakePrim->velocityY.val += FIX(2.0 / 16);
                    if (--fakePrim->delay < 0) {
                        fakePrim->drawMode |= DRAW_HIDE;
                    }
                }
                break;
            case 2:
                if (!(fakePrim->drawMode & DRAW_HIDE)) {
                    fakePrim->posX.val += fakePrim->velocityX.val;
                    fakePrim->posY.val += fakePrim->velocityY.val;
                    if (fakePrim->r0 != 0) {
                        fakePrim->r0--;
                    }
                    if (fakePrim->g0 != 0) {
                        fakePrim->g0--;
                    }
                    if (fakePrim->b0 != 0) {
                        fakePrim->b0--;
                    }
                    fakePrim->velocityY.val += FIX(1.5 / 16);
                    if (--fakePrim->delay < 0) {
                        fakePrim->drawMode |= DRAW_HIDE;
                    }
                }
                break;
            }
            fakePrim->x0 = fakePrim->posX.i.hi;
            fakePrim->y0 = fakePrim->posY.i.hi;
            self->ext.faerie.unk7E |= !(fakePrim->drawMode & DRAW_HIDE);
            fakePrim = fakePrim->next;
        }
        if (self->ext.faerie.unk7E == 0) {
            DestroyEntity(self);
        }
    }
}

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
