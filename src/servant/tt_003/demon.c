// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "servant.h"
#include "sfx.h"

typedef enum {
    DEMON_MODE_DEFAULT_UPDATE = ENTITY_ID_SERVANT,
    DEMON_MODE_UNK_D2,
    DEMON_MODE_UNK_D3,
    DEMON_MODE_UNK_D4,
    DEMON_MODE_UNK_D5,
    DEMON_MODE_UNK_D6,
    DEMON_SUBENTITY_UNK_D7,
    DEMON_MODE_UNK_D8,
    DEMON_EVENT_SFX_PASSTHROUGH,
} EntityIds;

extern ServantEvent g_Events[];

extern s32 s_TargetMatch[0x80];
extern s32 g_DemonAbilityStats[10][4];
extern FamiliarStats s_DemonStats;
extern s32 s_LastTargetedEntityIndex;
extern AnimationFrame* g_DemonAnimationFrames[];
extern s32 s_ServantId;
extern u16 g_DemonClut[64];
extern SpriteParts* g_DemonSpriteParts[];
extern s32 D_us_801786D0;
extern s32 D_us_801786D4;

extern s8 D_us_80171FE8;
extern s16 g_DemonAttackStats[10][6];
extern s32 s_TargetLocationX;
extern s32 s_TargetLocationY;
extern s16 s_TargetLocationX_calc;
extern s16 s_TargetLocationY_calc;
extern s16 s_AngleToTarget;
extern s16 s_AllowedAngle;
extern s16 s_DistToTargetLocation;
extern s16 s_TargetLocOffset_calc;
extern s32 s_DeltaX;
extern s32 s_DeltaY;
extern s32 s_DistToTargetLocation2;

extern Entity* D_us_801786D8;
extern s32 D_us_801786DC;

extern void (*s_PassthroughFunctions[])(Entity*);

// These are all in servant_private, but we need to have more decomped before we
// can include that
s16 CalculateAngleToEntity(Entity* entity, s16 targetX, s16 targetY);
s16 GetTargetPositionWithDistanceBuffer(
    s16 currentX, s16 targetX, s16 distanceBuffer);
void SetAnimationFrame(Entity* self, s32 animationIndex);
Entity* FindValidTarget(Entity* self);
s32 IsMovementAllowed(s32 arg0);
s32 CheckAllEntitiesValid(void);
void CreateEventEntity(Entity* entityParent, s32 entityId, s32 params);
void ProcessEvent(Entity* self, bool resetEvent);
u32 ServantUpdateAnim(Entity* self, s8* frameProps, AnimationFrame** frames);

void ServantInit(InitializeMode);
void UpdateServantDefault(Entity*);
void func_us_80174FD0(Entity*);
void func_us_8017540C(Entity*);
void unused_5800(Entity*);
void unused_5808(Entity*);
void func_us_80175810(Entity*);
void func_us_80175C08(Entity*);
void func_us_80175D20(Entity*);
void UpdateServantSfxPassthrough(Entity*);
void FunctionPointerPassthrough(Entity*);
void func_us_801765A0(Entity*);
void func_us_80176814(Entity*);
void func_us_80176C1C(Entity*);
void func_us_801771B0(Entity*);
void func_us_80177690(Entity*);

ServantDesc demon_ServantDesc = {
    ServantInit,
    UpdateServantDefault,
    func_us_80174FD0,
    func_us_8017540C,
    unused_5800,
    unused_5808,
    func_us_80175810,
    func_us_80175C08,
    func_us_80175D20,
    UpdateServantSfxPassthrough,
    FunctionPointerPassthrough,
    func_us_801765A0,
    func_us_80176814,
    func_us_80176C1C,
    func_us_801771B0,
    func_us_80177690,
};

static void SetAnimationFrame(Entity* self, s32 animationIndex) {
    if (self->anim != g_DemonAnimationFrames[animationIndex]) {
        self->anim = g_DemonAnimationFrames[animationIndex];
        self->animFrameIdx = 0;
        self->animFrameDuration = 0;
    }
}

static Entity* FindValidTarget(Entity* self) {
    const int EntitySearchCount = 128;
    s32 foundIndex;
    s32 i;
    u32 found;
    Entity* entity;
    s32 distance;

    found = 0;
    entity = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < EntitySearchCount; i++, entity++) {
        s_TargetMatch[i] = 0;
        if (!entity->entityId) {
            continue;
        }
        if (entity->hitboxState == 0) {
            continue;
        }
        if (entity->flags & FLAG_UNK_00200000) {
            continue;
        }
        if (entity->posX.i.hi < -16) {
            continue;
        }
        if (entity->posX.i.hi > 272) {
            continue;
        }
        if (entity->posY.i.hi > 240) {
            continue;
        }
        if (entity->posY.i.hi < 0) {
            continue;
        }
        if (!g_DemonAbilityStats[s_DemonStats.level / 10][2] &&
            entity->hitboxState & 8) {
            continue;
        }

        if (abs(self->posX.i.hi - entity->posX.i.hi) >
                g_DemonAbilityStats[s_DemonStats.level / 10][3] ||
            abs(self->posY.i.hi - entity->posY.i.hi) >
                g_DemonAbilityStats[s_DemonStats.level / 10][3]) {
            continue;
        }
        if (self->facingLeft && self->posX.i.hi < entity->posX.i.hi) {
            continue;
        }
        if (!self->facingLeft && self->posX.i.hi > entity->posX.i.hi) {
            continue;
        }
        if (entity->hitPoints >= 0x7000) {
            continue;
        }

        if (entity->flags & FLAG_UNK_80000) {
            if (entity->hitPoints >=
                g_DemonAbilityStats[s_DemonStats.level / 10][1]) {
                found++;
                s_TargetMatch[i] = 1;
            }
        } else {
            entity->flags |= FLAG_UNK_80000;
            return entity;
        }
    }

    if (found > 0) {
        foundIndex = s_LastTargetedEntityIndex % EntitySearchCount;
        for (i = 0; i < EntitySearchCount; i++) {
            if (s_TargetMatch[foundIndex]) {
                entity = &g_Entities[STAGE_ENTITY_START + foundIndex];
                s_LastTargetedEntityIndex =
                    (foundIndex + 1) % EntitySearchCount;
                return entity;
            }
            foundIndex = (foundIndex + 1) % EntitySearchCount;
        }
    }

    return NULL;
}

#include "../check_entity_valid.h"

void unused_2DBC(Entity* self) {}

// This is likey the analog to Faerie.ExecuteAbilityInitialize
void func_us_80172DC4(Entity* self) {
    if (!self->ext.demon.isAbilityInitialized) {
        if ((self->entityId == DEMON_MODE_DEFAULT_UPDATE) ||
            (self->entityId == DEMON_MODE_UNK_D8)) {
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;
            SetAnimationFrame(self, 0);

            self->ext.demon.randomMovementAngle = rand() % 4096;
            self->ext.demon.defaultDistToTargetLoc = 8;
            self->ext.demon.targetAngle = 0;
            self->ext.demon.maxAngle = 0x20;
            self->step++;
        }
    } else {
        switch (self->entityId) {
        case DEMON_MODE_DEFAULT_UPDATE:
        case DEMON_MODE_UNK_D2:
        case DEMON_MODE_UNK_D3:
        case DEMON_MODE_UNK_D6:
        case DEMON_MODE_UNK_D8:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;
            SetAnimationFrame(self, 0);
            self->step++;
            break;
        }
    }
    D_us_801786D0 = 0;
    self->ext.demon.isAbilityInitialized = self->entityId;
}

void DestroyEntityPassthrough(Entity* self) { DestroyEntity(self); }

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80172EF8);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80173348);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_801737F0);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80173D14);

void ServantInit(InitializeMode mode) {
    u16* src;
    u16* dst;
    RECT rect;
    s32 i;
    SpriteParts** spriteBanks;
    Entity* entity;

#ifdef VERSION_PC
    const int lenServant = LEN(g_ServantClut);
    const int lenDemon = LEN(g_DemonClut);
#else
    const int lenServant = 256;
    const int lenDemon = 80;
#endif

    s_ServantId = g_Servant;

    if ((mode == MENU_SWITCH_SERVANT) || (mode == MENU_SAME_SERVANT)) {
        ProcessEvent(NULL, true);
        if (mode == MENU_SAME_SERVANT) {
            return;
        }
    }

    dst = &g_Clut[CLUT_INDEX_SERVANT];
    src = g_ServantClut;
    for (i = 0; i < lenServant; i++) {
        *dst++ = *src++;
    }

    dst = &g_Clut[CLUT_INDEX_SERVANT_OVERWRITE];
    src = g_DemonClut;

    for (i = 0; i < lenDemon; i++) {
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
    *spriteBanks = (SpriteParts*)g_DemonSpriteParts;

    entity = &g_Entities[SERVANT_ENTITY_INDEX];

    DestroyEntity(entity);
    entity->unk5A = 0x6C;
    entity->palette = 0x140;
    entity->animSet = ANIMSET_OVL(20);
    entity->zPriority = PLAYER.zPriority - 2;
    entity->facingLeft = PLAYER.facingLeft;
    entity->params = 0;

    if (mode == MENU_SWITCH_SERVANT) {
        if (LOW(D_8003C708.flags) &
            (LAYOUT_RECT_PARAMS_UNKNOWN_20 | LAYOUT_RECT_PARAMS_UNKNOWN_40)) {
            entity->entityId = DEMON_MODE_DEFAULT_UPDATE;
        } else {
            entity->entityId = DEMON_MODE_UNK_D8;
        }
        entity->posX.val = FIX(128);
        entity->posY.val = FIX(-32);
    } else {
        entity->entityId = DEMON_MODE_DEFAULT_UPDATE;
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

    D_us_801786D0 = 0;
    D_us_801786D4 = 0;
    g_api.GetServantStats(entity, 0, 0, &s_DemonStats);
}

void UpdateServantDefault(Entity* self) {
    s32 temp;
    s32 i;
    s32 rnd;

    g_api.GetServantStats(self, 0, 0, &s_DemonStats);
    if (D_us_801786D4) {
        self->zPriority = PLAYER.zPriority - 2;
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

            if (self->posX.i.hi > 0x80) {
                temp = 0xC0;
            } else {
                temp = 0x40;
            }
            s_TargetLocationX = temp;
            break;
        }
        s_TargetLocationY = 0xA0;
    } else {
        s_TargetLocOffset_calc = -0x18;
        if (PLAYER.facingLeft) {
            s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
        }
        s_TargetLocationX_calc = g_Entities->posX.i.hi + s_TargetLocOffset_calc;
        s_TargetLocationY_calc = PLAYER.posY.i.hi - 0x20;

        s_AngleToTarget = self->ext.demon.randomMovementAngle;
        self->ext.demon.randomMovementAngle += 0x10;
        self->ext.demon.randomMovementAngle &= 0xFFF;
        s_DistToTargetLocation = self->ext.demon.defaultDistToTargetLoc;

        s_TargetLocationX =
            s_TargetLocationX_calc +
            ((rcos(s_AngleToTarget / 2) * s_DistToTargetLocation) >> 0xC);
        s_TargetLocationY =
            s_TargetLocationY_calc -
            ((rsin(s_AngleToTarget) * (s_DistToTargetLocation / 2)) >> 0xC);
    }
    switch (self->step) {
    case 0:
        func_us_80172DC4(self);
        break;
    case 1:
        if (D_8003C708.flags & FLAG_UNK_20) {
            if (PLAYER.posX.i.hi >= self->posX.i.hi) {
                self->facingLeft = 0;
            } else {
                self->facingLeft = 1;
            }
        } else {
            if (PLAYER.facingLeft != self->facingLeft) {
                if (abs(s_TargetLocationX - self->posX.i.hi) <= 0) {
                    self->facingLeft = PLAYER.facingLeft;
                } else if (
                    !self->facingLeft && s_TargetLocationX < self->posX.i.hi) {
                    self->facingLeft = PLAYER.facingLeft;
                } else if (
                    self->facingLeft && s_TargetLocationX > self->posX.i.hi) {
                    self->facingLeft = PLAYER.facingLeft;
                }
            } else if (!self->facingLeft &&
                       (self->posX.i.hi - s_TargetLocationX) > 0x28) {
                self->facingLeft = PLAYER.facingLeft ? 0 : 1;
            } else if (self->facingLeft &&
                       (s_TargetLocationX - self->posX.i.hi) > 0x28) {
                self->facingLeft = PLAYER.facingLeft ? 0 : 1;
            }
        }

        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = GetTargetPositionWithDistanceBuffer(
            s_AngleToTarget, self->ext.demon.targetAngle,
            self->ext.demon.maxAngle);
        self->ext.demon.targetAngle = s_AllowedAngle;
        s_TargetLocationX_calc = s_TargetLocationX - self->posX.i.hi;
        s_TargetLocationY_calc = s_TargetLocationY - self->posY.i.hi;
        s_DistToTargetLocation =
            SquareRoot12(((s_TargetLocationX_calc * s_TargetLocationX_calc) +
                          (s_TargetLocationY_calc * s_TargetLocationY_calc))
                         << 0xC) >>
            0xC;
        if (s_DistToTargetLocation < 0x28) {
            self->velocityY = -(rsin((s32)s_AllowedAngle) * 8);
            self->velocityX = rcos((s32)s_AllowedAngle) * 8;
            self->ext.demon.maxAngle = 0x20;
        } else if (s_DistToTargetLocation < 0x3C) {
            self->velocityY = -(rsin((s32)s_AllowedAngle) * 0x10);
            self->velocityX = rcos((s32)s_AllowedAngle) * 0x10;
            self->ext.demon.maxAngle = 0x40;
        } else if (s_DistToTargetLocation < 0x64) {
            self->velocityY = -(rsin((s32)s_AllowedAngle) << 5);
            self->velocityX = rcos((s32)s_AllowedAngle) << 5;
            self->ext.demon.maxAngle = 0x60;
        } else if (s_DistToTargetLocation < 0x100) {
            self->velocityY = -(rsin((s32)s_AllowedAngle) << 6);
            self->velocityX = rcos((s32)s_AllowedAngle) << 6;
            self->ext.demon.maxAngle = 0x80;
        } else {
            self->velocityX = (s_TargetLocationX - self->posX.i.hi) << 0xE;
            self->velocityY = (s_TargetLocationY - self->posY.i.hi) << 0xE;
            self->ext.demon.maxAngle = 0x80;
        }
        if (self->velocityY > FIX(1.0)) {
            SetAnimationFrame(self, 0xA);
        } else if (s_DistToTargetLocation < 0x3C) {
            SetAnimationFrame(self, 0);

        } else if (s_DistToTargetLocation > 0x64) {
            SetAnimationFrame(self, 0xB);
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (!g_CutsceneHasControl) {
            s_DeltaX = s_TargetLocationX - self->posX.i.hi;
            s_DeltaY = s_TargetLocationY - self->posY.i.hi;

            s_DistToTargetLocation2 =
                SquareRoot12(
                    ((s_DeltaX * s_DeltaX) + (s_DeltaY * s_DeltaY)) << 0xC) >>
                0xC;

            if (s_DistToTargetLocation2 < 0x20) {
                self->ext.demon.abilityTimer++;
                if (self->ext.demon.abilityTimer >
                    g_DemonAbilityStats[s_DemonStats.level / 10][0]) {
                    self->ext.demon.abilityTimer = 0;

                    if (self->ext.demon.target = FindValidTarget(self)) {
                        if (rand() % 0x100 <=
                            g_DemonAttackStats[s_DemonStats.level / 10][0]) {
                            self->entityId = DEMON_MODE_UNK_D2;
                        } else {
                            self->entityId = DEMON_MODE_UNK_D3;
                        }
                        self->step = 0;
                    }
                }
            }
            // This is likely dead code and not actually valid as it's doing
            // some weird stuff with g_Events that doesn't make any sense.  And
            // it only does it with the N Demon, which was stripped out anyway
            if (s_ServantId == FAM_ACTIVE_NOSE_DEMON) {
                if (!g_CutsceneHasControl && !IsMovementAllowed(1) &&
                    !CheckAllEntitiesValid() &&
                    !(D_8003C708.flags & FLAG_UNK_20) && !D_us_801786D0) {
                    if (self->ext.demon.unkCounter <= 18000) {
                        self->ext.demon.unkCounter++;
                    }
                } else {
                    self->ext.demon.unkCounter = 0;
                }
                if (self->ext.demon.unkCounter == 18000) {

                    for (rnd = rand() % 0x100, i = 0; true; i++) {
                        if (rnd <= ((s16*)g_Events)[i * 2]) {
                            CreateEventEntity(self, DEMON_EVENT_SFX_PASSTHROUGH,
                                              ((s16*)g_Events)[i * 2 + 1]);
                            break;
                        }
                    }
                }
            }
            if (D_us_801786D0 == 2) {
                D_us_801786D8 = 0;
                CreateEventEntity(self, DEMON_SUBENTITY_UNK_D7, 0);
                self->entityId = DEMON_MODE_UNK_D6;
                self->step = 0;
            }
        }
        break;
    }
    ProcessEvent(self, false);
    unused_2DBC(self);
    ServantUpdateAnim(self, &D_us_80171FE8, g_DemonAnimationFrames);
}

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80174FD0);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_8017540C);

void unused_5800(Entity* self) {}

void unused_5808(Entity* self) {}

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80175810);

void func_us_80175C08(Entity* self) {

    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        D_us_801786D8 = self;
        D_us_801786DC = 0;

        if (g_StageId < STAGE_RNO0 || g_StageId >= STAGE_RNZ1_DEMO) {
            self->posX.i.hi = 200;
            self->posY.i.hi = 36;
            self->facingLeft = 0;
        } else {
            self->posX.i.hi = 56;
            self->posY.i.hi = 196;
            self->facingLeft = 1;
        }

        self->step++;
        break;

    case 1:
        if (D_us_801786DC != 0) {
            self->hitboxOffX = 0x18;
            self->hitboxOffY = 4;
            self->hitboxWidth = 2;
            self->hitboxHeight = 2;
            self->attackElement = 0x20;
            self->hitboxState = 2;
            self->attack = 0;
            self->nFramesInvincibility = 0;
            self->stunFrames = 0;
            self->hitEffect = 7;
            self->entityRoomIndex = 0;

            g_api.func_80118894(self);

            self->step++;
        }
    case 2:
        return;
    }
}

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80175D20);

void UpdateServantSfxPassthrough(Entity* self) { ProcessSfxState(self); }

void FunctionPointerPassthrough(Entity* self) {
    s_PassthroughFunctions[self->params](self);
}

extern AnimationFrame D_us_80171CD8;
extern s32 D_us_80178670;
extern s32 D_us_80178674;
extern FamiliarStats s_DemonStats;

void func_us_801765A0(Entity* self) {
    s32 velocityX;
    s32 posX_hi;
    s16 step;
    switch (self->step) {
    case 0: {
        if (self->params == 0) {
            D_us_80178670 = self->posX.val;
            D_us_80178674 = self->posY.val;
        } else {
            self->posX.val = D_us_80178670;
            self->posY.val = D_us_80178674;
        }

        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        self->palette = 0x8143;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->animSet = 0xE;
        self->unk5A = 0x79;
        self->anim = &D_us_80171CD8;
        self->animFrameIdx = 0;
        self->animFrameDuration = 0;
        self->drawFlags |= FLAG_DRAW_ROTY;
        self->rotY = 0xC0;

        // velocityX = 0xC0;
        if (self->facingLeft != 0) {
            velocityX = -0xC000;

        } else {
            velocityX = 0xC000;
        }
        self->velocityX = velocityX;

        switch (self->params) {
        case 2:
            self->posY.i.hi += 8;
        case 1:
            self->posY.i.hi += 8;
        case 0:
            self->posX.i.hi += (self->facingLeft ? -0x20 : 0x20);
        }

        g_api.GetServantStats(self, 0x18, 1, &s_DemonStats);

        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->hitboxWidth = 0xC;
        self->hitboxHeight = 0xA;

        self->step++;
        if (self->params >= 2) {
            self->step += 1;
        }
        break;
    }

    case 1: {

        self->posX.val += self->velocityX;

        self->ext.et_80176814.frameCounter[1] += 1;

        if ((s16)self->ext.et_80176814.frameCounter[1] >= 7) {
            CreateEventEntity(self, 0xDB, self->params + 1);
            self->step += 1;
        }

        break;
    }

    case 2: {
        self->posX.val += self->velocityX;

        if ((s16)self->ext.et_80176814.frameCounter[0] == -1) {
            DestroyEntity(self);
            return;
        }
    }
    default:
        break;
    }

    self->ext.et_80176814.frameCounter[0] = ServantUpdateAnim(self, NULL, NULL);
}

// PSX: https://decomp.me/scratch/NMQwa
// PSP: https://decomp.me/scratch/6hM5K

// Horizontal offsets for positioning primitives
typedef struct {
    u16 xOffsets[14];
} D_us_80171D10_t;

extern D_us_80171D10_t D_us_80171D10;
extern s32 D_us_80178678;
extern s32 D_us_8017867C;

void func_us_80176814(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 newX;
    s32 newY;
    s32 offset;

    switch (self->step) {
        case 0:
            if (self->params == 0) {
                D_us_80178678 = self->posX.val;
                D_us_8017867C = self->posY.val;
            } else {
                self->posX.val = D_us_80178678;
                self->posY.val = D_us_8017867C;
            }

            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0xC);

            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
                self->flags = 0x0C800000;
                prim = &g_PrimBuf[self->primIndex];
                for (i = 0; i < 12; i++) {
                    prim->tpage = 0x1A;
                    prim->clut = 0x146;
                    prim->priority = self->zPriority + 1;
                    prim->drawMode = 0x37;

                    offset = (i % 4) * 4;
                    prim->u0 = prim->u2 = offset + 8;
                    prim->u1 = prim->u3 = (offset) + 0xC;
                    prim->v0 = prim->v1 = 0x60;
                    prim->v2 = prim->v3 = 0x80;
                    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 
                    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 
                    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                    prim = prim->next;
                }
                self->velocityX = self->facingLeft ? FIX(-4.0) : FIX(4.0);

                g_api.GetServantStats(self, 25, 1, &s_DemonStats);

                self->hitboxOffX = 28;
                self->hitboxOffY = 0;
                self->hitboxWidth = 12;
                self->hitboxHeight = 10;

                self->step++;

                if (self->params >= 2) {
                    self->step++; 
                }
            break;
             
        case 1:
            self->posX.val += self->velocityX;
            self->ext.et_80176814.frameCounter[0]++;


            if ((s16)self->ext.et_80176814.frameCounter[0] >= 3) {
                CreateEventEntity(self, 220, self->params + 1);
                self->step++;
            }
            break;

        case 2:           
            self->posX.val += self->velocityX;
            self->ext.et_80176814.frameCounter[0]++;
            if ((s16)self->ext.et_80176814.frameCounter[0] >= 9) {
                DestroyEntity(self);
                return;
            }


    }
        newX = self->posX.i.hi;
        newY = self->posY.i.hi - 12;
        prim = &g_PrimBuf[self->primIndex];
        
        for (i = 0; i < 12; i++) {
            if (self->facingLeft) {
                prim->x2 = newX - D_us_80171D10.xOffsets[i];
                prim->x3 = newX - D_us_80171D10.xOffsets[i + 1];
                if (i == 0) {
                    prim->x0 = prim->x2 - 0x10;
                } else {
                    prim->x0 = prim->x2 - 0x20;
                }
                if (i == 11) {
                    prim->x1 = prim->x3 - 0x10;
                } else {
                    prim->x1 = prim->x3 - 0x20;
                }

            } else {
                prim->x2 = newX + D_us_80171D10.xOffsets[i];
                prim->x3 = newX + D_us_80171D10.xOffsets[i + 1];

                if (i == 0) {
                    prim->x0 = prim->x2 + 0x10;
                } else {
                    prim->x0 = prim->x2 + 0x20;
                }
                if (i == 11) {
                    prim->x1 = prim->x3 + 0x10;
                } else {
                    prim->x1 = prim->x3 + 0x20;
                }
            }
            
            prim->y0 = prim->y2 = newY + (i * 2);
            prim->y1 = prim->y3 = newY + ((i + 1) * 2);

            prim = prim->next;
        }
    
}

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_80176C1C);

INCLUDE_ASM("servant/tt_003/nonmatchings/demon", func_us_801771B0);

extern s32 D_us_801786D0;
extern s32 D_us_801786D4;

void func_us_80177690(Entity* self) {
    Entity* entity;

    switch (self->params) {
    case 0:
        D_us_801786D0 = 1;
        entity = SearchForEntityInRange(0, 217);
        if ((entity != NULL) && (entity->step < 5)) {
            entity->step = 8;
        }
        break;
    case 1:
        D_us_801786D0 = 2;
        break;
    case 15:
        D_us_801786D4 = 1;
        break;
    }
    DestroyEntity(self);
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
#include "../play_sfx.h"
#endif

#include "../process_event.h"

#include "../create_event_entity.h"

#include "../is_movement_allowed.h"

#ifndef VERSION_PSP
#include "../check_all_entities_valid.h"
#endif

#include "../servant_unk0.h"
