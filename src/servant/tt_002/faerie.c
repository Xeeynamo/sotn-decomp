// SPDX-License-Identifier: AGPL-3.0-or-later
#include "faerie.h"
#include "items.h"
#include "../servant_private.h"

static s32 s_ServantId;
static s32 s_zPriority;
static FamiliarStats s_FaerieStats;
static s32 s_ElementalDamageStatus;
static s32 s_UseResistDelayTimer;
static s32 s_UseResistClearTimer;
static s32 s_HpDifferenceHistory[5];
static s32 s_CachedHp;
static s16 s_HpDifferenceIndex;
STATIC_PAD_BSS(2);
static s16 s_HpCacheResetTimer;
STATIC_PAD_BSS(2);
static s32 s_RoomSpecialState;
static bool D_us_80179320; // Possibly when player is sitting
static s32 s_TargetLocationX;
static s32 s_TargetLocationY;
static s32 s_TargetLocationX_calc;
static s32 s_TargetLocationY_calc;
static s32 s_AngleToTarget;
static s32 s_AllowedAngle;
static s32 s_DistToTargetLocation;
static s16 s_TargetLocOffset_calc;

extern SpriteParts* g_FaerieSpriteParts[];
extern u16 g_FaerieClut[64];
static s32 g_PlaySfxStep;
extern s32 g_AlucardChairSleepTimer;

// Map is used in the wing animation selector. The Z index param is used
// because sometimes the wings are in front of the faerie like when
// her back it toward the player.
static FaerieWingAnimationParams g_WingAnimationParams[] = {
    {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {4, 1}, {4, 1}, {0, 0},
    {4, 1}, {4, 1}, {3, 0}, {5, 0}, {0, 0}, {0, 0}, {0, 0}, {4, 1},
    {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {4, 1}, {0, 0},
    {0, 0}, {4, 1}, {4, 1}, {4, 1}, {4, 1}, {4, 1}, {4, 1}, {4, 1},
    {4, 1}, {4, 1}, {4, 1}, {4, 1}, {4, 1}, {4, 1}, {4, 1}, {4, 1},
};

static FaerieAbilityStats g_FaerieAbilityStats[] = {
    {0x1E, 0xFF, 0x20, 0x10, 0x10, 0x10, 0xC0}, // lvl 0-9
    {0x14, 0xFF, 0x20, 0x10, 0x10, 0x20, 0xC0}, // lvl 10-19
    {0x0F, 0xFF, 0x40, 0x20, 0x20, 0x20, 0xD0}, // lvl 20-29
    {0x0A, 0xFF, 0x40, 0x20, 0x20, 0x40, 0xD0}, // lvl 30-39
    {0x0A, 0xFF, 0x60, 0x20, 0x30, 0x40, 0xE0}, // lvl 40-49
    {0x05, 0xFF, 0x60, 0x40, 0x30, 0x40, 0xE0}, // lvl 50-59
    {0x03, 0xFF, 0x80, 0x40, 0x40, 0x60, 0xE0}, // lvl 60-69
    {0x02, 0xFF, 0xA0, 0x60, 0x50, 0x60, 0xFF}, // lvl 70-79
    {0x01, 0xFF, 0xC0, 0x60, 0x60, 0x80, 0xFF}, // lvl 80-89
    {0x00, 0xFF, 0xC0, 0x60, 0x60, 0x80, 0xFF}, // lvl 90-99
};

// This may be able to be broken into a 4 short struct
// unknown param for g_StatBuffTimers, ItemId, FactoryParam, EventParam
static s16 g_ResistItemsParamMap[] = {
    5,  ITEM_RESIST_FIRE, 9,  5, 7,  ITEM_RESIST_THUNDER, 10, 6,
    6,  ITEM_RESIST_ICE,  11, 7, 9,  ITEM_RESIST_HOLY,    14, 8,
    11, ITEM_RESIST_DARK, 15, 9, 10, ITEM_RESIST_STONE,   12, 10,
};

// itemId, FACTORY() param
// check if can be made struct, but PSP may be a problem.
static s16 g_PotionItemsParamMap[] = {ITEM_POTION, 16, ITEM_HIGH_POTION, 17};

extern AnimationFrame* g_FaerieAnimationFrames[];
extern FaerieSfx g_FaerieSfx;
extern s32 g_SfxRandomizerHammerResist[];
extern s32* g_FaerieIntroRandomizer[];
extern s32* g_SfxEventRandomizer[];

static void SetAnimationFrame(Entity* self, s32 animationIndex) {
    if (self->anim != g_FaerieAnimationFrames[animationIndex]) {
        self->anim = g_FaerieAnimationFrames[animationIndex];
        self->pose = 0;
        self->poseTimer = 0;
    }
}

void unused_39C8(Entity* self) {}

void ExecuteAbilityInitialize(Entity* self) {
    if (!self->ext.faerie.abilityId) {
        switch (self->entityId) {
        case FAERIE_MODE_DEFAULT_UPDATE:
        case FAERIE_MODE_ADDITIONAL_INIT:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;

            SetAnimationFrame(self, 14);

            self->ext.faerie.randomMovementAngle = rand() % 0x1000;
            self->ext.faerie.targetAngle = 0;
            self->ext.faerie.defaultDistToTargetLoc = 8;
            self->ext.faerie.maxAngle = 0x20;
            self->step++;
            break;

        case FAERIE_SUBENTITY_WINGS:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;
            self->step++;
            break;
        }
    } else {
        switch (self->entityId) {
        case FAERIE_MODE_DEFAULT_UPDATE:
            self->ext.faerie.timer = 120;
            // fallthrough
        case FAERIE_MODE_USE_LIFE_APPLE:
        case FAERIE_MODE_USE_HAMMER:
        case FAERIE_MODE_USE_UNCURSE:
        case FAERIE_MODE_USE_ANTIVENOM:
        case FAERIE_MODE_USE_ELEMENTAL_RESIST:
        case FAERIE_MODE_USE_POTION:
        case FAERIE_MODE_SIT_ON_SHOULDER:
        case FAERIE_MODE_OFFER_HINT:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;
            SetAnimationFrame(self, 14);
            self->step++;
            break;

        case FAERIE_SUBENTITY_WINGS:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;
            self->step++;
            break;
        }
    }
    self->ext.faerie.abilityId = self->entityId;
    s_RoomSpecialState = 0;
}

// This is a duplicate CreateEventEntity which is lower in the file, but we need
// both to match the binary for PSX.  They are identical, but faerie uses this
// one.
void CreateEventEntity_Local(Entity* parent, s32 entityId, s32 params) {
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
        entity->zPriority = parent->zPriority;
        entity->facingLeft = parent->facingLeft;
        entity->flags = FLAG_KEEP_ALIVE_OFFCAMERA;
        entity->posX.val = parent->posX.val;
        entity->posY.val = parent->posY.val;
        entity->ext.factory.parent = parent;
        entity->params = params;
    }
}

void SelectAnimationFrame(Entity* self) {
    if (abs(self->velocityY) > abs(self->velocityX)) {
        if (abs(self->velocityY) < FIX(0.5)) {
            if (self->ext.faerie.animationFlag == 1) {
                self->ext.faerie.animationFlag = 0;
                SetAnimationFrame(self, 41);
            } else if (self->ext.faerie.animationFlag == 2) {
                self->ext.faerie.animationFlag = 0;
                SetAnimationFrame(self, 14);
            }
        } else if (abs(self->velocityY) > FIX(1)) {
            if (self->velocityY >= 0) {
                self->ext.faerie.animationFlag = 2;
                SetAnimationFrame(self, 11);
            } else {
                self->ext.faerie.animationFlag = 2;
                SetAnimationFrame(self, 12);
            }
        }
    } else {
        if (abs(self->velocityX) > FIX(0.5625)) {
            if (self->ext.faerie.animationFlag == 0) {
                self->ext.faerie.animationFlag = 1;
                SetAnimationFrame(self, 15);
            } else if (self->ext.faerie.animationFlag == 2) {
                self->ext.faerie.animationFlag = 0;
                SetAnimationFrame(self, 14);
            }
        } else if (abs(self->velocityX) < FIX(0.375)) {
            if (self->ext.faerie.animationFlag == 1) {
                self->ext.faerie.animationFlag = 0;
                SetAnimationFrame(self, 41);
            } else if (self->ext.faerie.animationFlag == 2) {
                self->ext.faerie.animationFlag = 0;
                SetAnimationFrame(self, 14);
            }
        }
        if (abs(self->velocityX) > FIX(0.5)) {
            if (self->velocityX >= 0) {
                self->facingLeft = true;
            } else {
                self->facingLeft = false;
            }
        }
    }
}

void CheckForValidAbility(Entity* self) {
    s32 i;
    s32 params;
    s32 rnd;
    s32 unkHpSum;
    s32 playerUnk18Flag;

    g_api.GetServantStats(self, 0, 0, &s_FaerieStats);
    playerUnk18Flag = g_Player.unk18 & 0xFA00;
    if (playerUnk18Flag) {
        if ((s_ElementalDamageStatus & playerUnk18Flag) == playerUnk18Flag) {
            s_UseResistClearTimer = 0;
            s_UseResistDelayTimer++;
            s_ElementalDamageStatus = playerUnk18Flag & s_ElementalDamageStatus;
        } else {
            s_UseResistDelayTimer = 0;
            s_ElementalDamageStatus |= playerUnk18Flag;
        }
    } else {
        s_UseResistClearTimer++;
        if (s_UseResistClearTimer > 3600) {
            s_ElementalDamageStatus = s_UseResistDelayTimer =
                s_UseResistClearTimer = 0;
        }
    }

    if (s_CachedHp > g_Status.hp) {
        s_HpDifferenceHistory[s_HpDifferenceIndex++] = s_CachedHp - g_Status.hp;
        if (s_HpDifferenceIndex > 4) {
            s_HpDifferenceIndex = 0;
        }
        s_CachedHp = g_Status.hp;
        s_HpCacheResetTimer = 0;
    } else {
        s_HpCacheResetTimer++;
        if (s_HpCacheResetTimer > 120) {
            s_HpDifferenceIndex = 0;
            s_HpCacheResetTimer = 0;
            s_CachedHp = g_Status.hp;
            for (i = 0; i < 5; i++) {
                s_HpDifferenceHistory[i] = 0;
            }
        }
    }
    if (g_Player.status & PLAYER_STATUS_DEAD) {
        rnd = rand() % 100;
        // for faerie, always true. stats table.lifeAppleChance is 0x00FF
        if (rnd <=
            g_FaerieAbilityStats[s_FaerieStats.level / 10].lifeAppleChance) {
            self->entityId = FAERIE_MODE_USE_LIFE_APPLE;
            self->step = 0;
            return;
        }
    }

    if (self->ext.faerie.timer < 0) {
        return;
    }

    if (self->ext.faerie.timer) {
        self->ext.faerie.timer--;
        return;
    }

    self->ext.faerie.timer =
        g_FaerieAbilityStats[s_FaerieStats.level / 10].timer;

    if (self->entityId == FAERIE_MODE_USE_HAMMER) {
        return;
    }

    if (PLAYER.step == 0xB && (!IsMovementAllowed(0)) &&
        g_Status.equipHandCount[ITEM_HAMMER]) {
        rnd = rand() % 100;
        if (rnd <=
            g_FaerieAbilityStats[(s_FaerieStats.level / 10)].hammerChance) {
            self->ext.faerie.unk8E = 0;
            self->entityId = FAERIE_MODE_USE_HAMMER;
            self->step = 0;
            return;
        }
    }

    if (self->entityId == FAERIE_MODE_USE_UNCURSE) {
        return;
    }

    if (g_Player.status & PLAYER_STATUS_CURSE) {
        if (g_Status.equipHandCount[ITEM_UNCURSE]) {
            rnd = rand() % 100;
            if (rnd <= g_FaerieAbilityStats[(s_FaerieStats.level / 10)]
                           .uncurseChance) {
                self->ext.faerie.requireUncurseLuckCheck = false;
                self->entityId = FAERIE_MODE_USE_UNCURSE;
                self->step = 0;
                return;
            }
        }
        if (!self->ext.faerie.requireUncurseLuckCheck) {
            self->ext.faerie.requireUncurseLuckCheck = true;
            self->entityId = FAERIE_MODE_USE_UNCURSE;
            self->step = 0;
            return;
        }
    }

    if (self->entityId == FAERIE_MODE_USE_ANTIVENOM) {
        return;
    }

    if (g_Player.status & PLAYER_STATUS_POISON) {
        if (g_Status.equipHandCount[ITEM_ANTIVENOM]) {
            rnd = rand() % 100;
            if (rnd <= g_FaerieAbilityStats[s_FaerieStats.level / 10]
                           .antivenomChance) {
                self->ext.faerie.requireAntivenomLuckCheck = false;
                self->entityId = FAERIE_MODE_USE_ANTIVENOM;
                self->step = 0;
                return;
            }
        }
        if (!self->ext.faerie.requireAntivenomLuckCheck) {
            self->ext.faerie.requireAntivenomLuckCheck = true;
            self->entityId = FAERIE_MODE_USE_ANTIVENOM;
            self->step = 0;
            return;
        }
    }

    if (s_UseResistDelayTimer >= 10) {
        if (s_ElementalDamageStatus & ELEMENT_FIRE) {
            params = 0;
        } else if (s_ElementalDamageStatus & ELEMENT_THUNDER) {
            params = 1;
        } else if (s_ElementalDamageStatus & ELEMENT_ICE) {
            params = 2;
        } else if (s_ElementalDamageStatus & ELEMENT_HOLY) {
            params = 3;
        } else if (s_ElementalDamageStatus & ELEMENT_DARK) {
            params = 4;
        } else if (s_ElementalDamageStatus & ELEMENT_STONE) {
            params = 5;
        }

        if (!g_api.GetStatBuffTimer(g_ResistItemsParamMap[params * 4]) &&
            g_Status.equipHandCount[g_ResistItemsParamMap[(params * 4) + 1]]) {
            rnd = rand() % 100;
            if (rnd <=
                g_FaerieAbilityStats[s_FaerieStats.level / 10].resistChance) {
                self->entityId = FAERIE_MODE_USE_ELEMENTAL_RESIST;
                self->step = 0;
                self->params = params;
                s_UseResistClearTimer = 0;
                s_UseResistDelayTimer = 0;
                return;
            }
        }
    }

    if (self->entityId == FAERIE_MODE_USE_POTION) {
        return;
    }

    unkHpSum = 0;
    params = 0;
    for (i = 0; i < 5; i++) {
        unkHpSum += s_HpDifferenceHistory[i];
    }

    if (unkHpSum >= (g_Status.hpMax / 2)) {
        if (g_Status.hpMax < 100) {
            params = 1;
        } else {
            params = 2;
        }
    }

    if (g_Status.hp <= (g_Status.hpMax / 10)) {
        if (g_Status.hpMax < 100) {
            params = 1;
        } else {
            params = 2;
        }
    }

    // if health greater than 1/4 max
    if (!(g_Status.hp > (g_Status.hpMax >> 2))) {
        if (unkHpSum >= (g_Status.hpMax / 8)) {
            params = 2;
        } else if (unkHpSum >= (g_Status.hpMax / 16)) {
            params = 1;
        }
    }

    if (!params) {
        return;
    }

    if (g_Status.equipHandCount[ITEM_POTION] |
        g_Status.equipHandCount[ITEM_HIGH_POTION]) {
        rnd = rand() % 100;
        if (rnd <= g_FaerieAbilityStats[s_FaerieStats.level / 10].healChance) {
            // This is likely a bug as it breaks the pattern.
            // variable also only ever gets set and never cleared
            self->ext.faerie.requirePotionLuckCheck = true;
            self->entityId = FAERIE_MODE_USE_POTION;
            self->step = 0;
            self->params = params - 1;
            s_HpDifferenceIndex = 0;
            s_HpCacheResetTimer = 0;
            s_CachedHp = g_Status.hp;

            for (i = 0; i < 5; i++) {
                s_HpDifferenceHistory[i] = 0;
            }
        }
    } else {
        if (!self->ext.faerie.requirePotionLuckCheck) {
            self->ext.faerie.requirePotionLuckCheck = true;
            self->entityId = FAERIE_MODE_USE_POTION;
            self->step = 0;
            self->params = params - 1;
            s_HpDifferenceIndex = 0;
            s_HpCacheResetTimer = 0;
            s_CachedHp = g_Status.hp;

            for (i = 0; i < 5; i++) {
                s_HpDifferenceHistory[i] = 0;
            }
        }
    }
}

void OVL_EXPORT(ServantInit)(InitializeMode mode) {
    u16* src;
    u16* dst;
    RECT rect;
    s32 i;
    SpriteParts** spriteBanks;
    Entity* entity;

#ifdef VERSION_PC
    const int len = LEN(g_FaerieClut);
#else
    const int len = 256;
#endif

    s_ServantId = g_Servant;

    if ((mode == MENU_SWITCH_SERVANT) || (mode == MENU_SAME_SERVANT)) {
        ProcessEvent(NULL, true);
        if (mode == MENU_SAME_SERVANT) {
            return;
        }
    }

    dst = &g_Clut[1][CLUT_INDEX_SERVANT];
    src = g_FaerieClut;
    for (i = 0; i < len; i++) {
        *dst++ = *src++;
    }

    rect.x = 0;
    rect.w = 0x100;
    rect.h = 1;
    rect.y = 0xF4;

    dst = &g_Clut[1][CLUT_INDEX_SERVANT];
    LoadImage(&rect, (u_long*)dst);

    spriteBanks = g_api.o.spriteBanks;
    spriteBanks += 20;
    *spriteBanks = (SpriteParts*)g_FaerieSpriteParts;

    entity = &g_Entities[SERVANT_ENTITY_INDEX];

    DestroyEntity(entity);
    entity->unk5A = 0x6C;
    entity->palette = PAL_SERVANT;
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

            entity->entityId = FAERIE_MODE_DEFAULT_UPDATE;
        } else {
            entity->entityId = FAERIE_MODE_ADDITIONAL_INIT;
        }
        entity->posX.val = FIX(128);
        entity->posY.val = FIX(-32);
    } else {
        entity->entityId = FAERIE_MODE_DEFAULT_UPDATE;
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

    s_zPriority = entity->zPriority;
    g_api.GetServantStats(entity, 0, 0, &s_FaerieStats);

    entity++;
    DestroyEntity(entity);
    entity->entityId = FAERIE_SUBENTITY_WINGS;
    entity->unk5A = 0x6C;
    entity->palette = PAL_SERVANT;
    entity->animSet = ANIMSET_OVL(20);
    entity->zPriority = PLAYER.zPriority - 3;
    entity->facingLeft = PLAYER.facingLeft;
    entity->params = 0;

    s_RoomSpecialState = 0;
    D_us_80179320 = false;
    g_api.GetServantStats(entity, 0, 0, &s_FaerieStats);
}

void OVL_EXPORT(UpdateServantDefault)(Entity* self) {
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
        self->ext.faerie.randomMovementAngle &= 0xFFF;
        s_DistToTargetLocation = self->ext.faerie.defaultDistToTargetLoc;

        s_TargetLocationX =
            s_TargetLocationX_calc +
            ((rcos(s_AngleToTarget / 2) * s_DistToTargetLocation) >> 12);
        s_TargetLocationY =
            s_TargetLocationY_calc -
            ((rsin(s_AngleToTarget) * (s_DistToTargetLocation / 2)) >> 12);
    }
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        self->ext.faerie.animationFlag = 0;
        SetAnimationFrame(self, 14);

        s_CachedHp = g_Status.hp;
        s_HpDifferenceIndex = 0;
        s_HpCacheResetTimer = 0;
        self->ext.faerie.idleFrameCounter = 0;
        break;

    case 1:
        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle =
            StepAngleTowards(s_AngleToTarget, self->ext.faerie.targetAngle,
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

        SelectAnimationFrame(self);

        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;

        if (!g_CutsceneHasControl && !IsMovementAllowed(1) &&
            !CheckAllEntitiesValid() && !(D_8003C708.flags & FLAG_UNK_20)) {
            self->ext.faerie.idleFrameCounter++;
        } else {
            self->ext.faerie.idleFrameCounter = 0;
        }
        if (self->ext.faerie.idleFrameCounter > 0x708) {
            self->entityId = FAERIE_MODE_SIT_ON_SHOULDER;
            self->step = 0;
            return;
        }
        if (s_RoomSpecialState >= 2) {
            self->entityId = FAERIE_MODE_OFFER_HINT;
            self->step = 0;
            self->params = s_RoomSpecialState - ROOM_STATE_TO_HINT_OFFSET;
        }
        break;
    }

    ProcessEvent(self, false);

    if (!g_CutsceneHasControl) {
        CheckForValidAbility(self);
    }
    unused_39C8(self);
    ServantUpdateAnim(self, NULL, g_FaerieAnimationFrames);
}

void UpdateServantUseLifeApple(Entity* self) {
    s32 i;

    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
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
            self->step = 90;
            break;
        }
        self->step++;
        // fallthrough
    case 3:
        if (!g_unkGraphicsStruct.unk20) {
            g_Status.equipHandCount[ITEM_LIFE_APPLE]--;
            g_unkGraphicsStruct.unk20 = 0xFFF;
            self->step++;
        }
        break;

    case 4:
        s_TargetLocationX_calc = PLAYER.posX.i.hi;
        s_TargetLocationY_calc = PLAYER.posY.i.hi - 0x20;
        s_AngleToTarget = self->ext.faerie.randomMovementAngle;
        self->ext.faerie.randomMovementAngle += 0x10;
        self->ext.faerie.randomMovementAngle &= 0xFFF;
        s_DistToTargetLocation = self->ext.faerie.defaultDistToTargetLoc;
        s_TargetLocationX =
            s_TargetLocationX_calc +
            ((rcos(s_AngleToTarget / 2) * s_DistToTargetLocation) >> 0xC);
        s_TargetLocationY =
            s_TargetLocationY_calc -
            ((rsin(s_AngleToTarget) * (s_DistToTargetLocation / 2)) >> 0xC);
        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = StepAngleTowards(
            s_AngleToTarget, self->ext.faerie.targetAngle, 0x180);
        self->ext.faerie.targetAngle = s_AllowedAngle;
        self->velocityY = -(rsin(s_AllowedAngle) << 5);
        self->velocityX = rcos(s_AllowedAngle) << 5;
        SelectAnimationFrame(self);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        s_DistToTargetLocation =
            CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);
        if (s_DistToTargetLocation < 2) {
            self->step++;
        }
        break;

    case 5:
        self->facingLeft = PLAYER.facingLeft;
        SetAnimationFrame(self, 19);
        if (s_ServantId == FAM_ACTIVE_YOUSEI) {
            g_api.PlaySfx(g_FaerieSfx.regeneration);
        }
        self->step++;
        break;

    case 6:
        if (self->pose == 10) {
            if (s_ServantId == FAM_ACTIVE_FAERIE) {
                g_api.PlaySfx(g_FaerieSfx.regeneration);
            }
            self->step++;
        }
        break;

    case 7:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            CreateEventEntity_Local(self, FAERIE_SUBENTITY_ITEM, 0);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;

    case 8:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            CreateEventEntity_Local(self, FAERIE_SUBENTITY_LIFE_APPLE, 0);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;

    case 9:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 90) {
            if (SearchForEntityInRange(1, 0x29)) {
                g_unkGraphicsStruct.D_800973FC = 0;
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

    case 10:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 90) {
            g_unkGraphicsStruct.unk20 = 0;
            self->step++;
        }
        break;

    case 11:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }
        break;

    case 90: // Only get here when you are dead and have no life apple
        SetAnimationFrame(self, 32);
        g_api.PlaySfx(g_FaerieSfx.ohNo);
        self->step++;
        break;

    case 91:
        break;
    }

    ServantUpdateAnim(self, NULL, g_FaerieAnimationFrames);
}

void UpdateServantUseHammer(Entity* self) {
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
        ExecuteAbilityInitialize(self);
        SetAnimationFrame(self, 14);
        break;

    case 1:
        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = StepAngleTowards(
            s_AngleToTarget, self->ext.faerie.targetAngle, 0x180);
        self->ext.faerie.targetAngle = s_AllowedAngle;
        self->velocityY = -(rsin(s_AllowedAngle) << 5);
        self->velocityX = rcos(s_AllowedAngle) << 5;
        SelectAnimationFrame(self);
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
        if (g_Status.equipHandCount[ITEM_HAMMER]) {
            SetAnimationFrame(self, 23);

            rnd = rand() % 0x100;
            for (i = 0; true; i++) {
                if (rnd <= g_SfxRandomizerHammerResist[i * 2]) {
                    g_api.PlaySfx(g_SfxRandomizerHammerResist[i * 2 + 1]);
                    break;
                }
            }

            self->step++;
        } else {
            SetAnimationFrame(self, 16);
            g_api.PlaySfx(g_FaerieSfx.noMedicine);
            self->ext.faerie.frameCounter = 0;
            self->step += 2;
        }
        break;

    case 3:
        if (self->pose == 5) {
            g_Status.equipHandCount[ITEM_HAMMER]--;
            g_api.CreateEntFactoryFromEntity(self, FACTORY(0x37, 3), 0);
            CreateEventEntity_Local(self, FAERIE_SUBENTITY_ITEM, 1);
            g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            g_api.func_80102CD8(4);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;

    case 4:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }
        break;
    }

    CheckForValidAbility(self);
    ServantUpdateAnim(self, NULL, g_FaerieAnimationFrames);
}

void UpdateServantUseUncurse(Entity* self) {
    s_TargetLocOffset_calc = -0x18;
    if (!PLAYER.facingLeft) {
        s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
    }
    s_TargetLocationX = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
    s_TargetLocationY = PLAYER.posY.i.hi - 0x18;
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        SetAnimationFrame(self, 14);
        break;

    case 1:
        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = StepAngleTowards(
            s_AngleToTarget, self->ext.faerie.targetAngle, 0x180);
        self->ext.faerie.targetAngle = s_AllowedAngle;
        self->velocityY = -(rsin(s_AllowedAngle) << 5);
        self->velocityX = rcos(s_AllowedAngle) << 5;
        SelectAnimationFrame(self);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        s_DistToTargetLocation =
            CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);
        if (s_DistToTargetLocation < 2) {
            self->step++;
        }
        break;

    case 2:
        if (!g_Status.equipHandCount[ITEM_UNCURSE]) {
            SetAnimationFrame(self, 20);
            self->step = 5;
            break;
        }
        if (SearchForEntityInRange(1, 0x27)) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }
        SetAnimationFrame(self, 18);
        if (s_ServantId == FAM_ACTIVE_YOUSEI) {
            g_api.PlaySfx(g_FaerieSfx.healing);
        }
        self->step++;
        break;

    case 3:
        self->facingLeft = PLAYER.facingLeft ? false : true;
        if (self->pose == 11) {
            if (s_ServantId == FAM_ACTIVE_FAERIE) {
                g_api.PlaySfx(g_FaerieSfx.healing);
            }

            g_Status.equipHandCount[ITEM_UNCURSE]--;
            g_api.CreateEntFactoryFromEntity(self, FACTORY(0x37, 1), 0);

            CreateEventEntity_Local(self, FAERIE_SUBENTITY_ITEM, 4);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;

    case 4:
    case 6:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }
        break;

    case 5:
        self->facingLeft = PLAYER.facingLeft;
        if (self->pose == 32) {
            g_api.PlaySfx(g_FaerieSfx.noMedicine);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    }

    CheckForValidAbility(self);
    ServantUpdateAnim(self, NULL, g_FaerieAnimationFrames);
}

void UpdateServantUseAntivenom(Entity* self) {
    s_TargetLocOffset_calc = -0x18;
    if (!PLAYER.facingLeft) {
        s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
    }
    s_TargetLocationX = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
    s_TargetLocationY = PLAYER.posY.i.hi - 0x18;
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        SetAnimationFrame(self, 14);
        break;

    case 1:
        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = StepAngleTowards(
            s_AngleToTarget, self->ext.faerie.targetAngle, 0x180);
        self->ext.faerie.targetAngle = s_AllowedAngle;
        self->velocityY = -(rsin(s_AllowedAngle) << 5);
        self->velocityX = rcos(s_AllowedAngle) << 5;
        SelectAnimationFrame(self);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        s_DistToTargetLocation =
            CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);
        if (s_DistToTargetLocation < 2) {
            self->step++;
        }
        break;

    case 2:
        if (!g_Status.equipHandCount[ITEM_ANTIVENOM]) {
            SetAnimationFrame(self, 20);
            self->step = 5;
            break;
        }
        if (SearchForEntityInRange(1, 0x27)) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }
        SetAnimationFrame(self, 18);
        if (s_ServantId == FAM_ACTIVE_YOUSEI) {
            g_api.PlaySfx(g_FaerieSfx.healing);
        }
        self->step++;
        break;

    case 3:
        self->facingLeft = PLAYER.facingLeft ? false : true;
        if (self->pose == 11) {
            if (s_ServantId == FAM_ACTIVE_FAERIE) {
                g_api.PlaySfx(g_FaerieSfx.healing);
            }

            g_Status.equipHandCount[ITEM_ANTIVENOM]--;
            g_api.CreateEntFactoryFromEntity(self, FACTORY(0x37, 0), 0);

            CreateEventEntity_Local(self, FAERIE_SUBENTITY_ITEM, 3);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;

    case 4:
    case 6:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }
        break;

    case 5:
        self->facingLeft = PLAYER.facingLeft;
        if (self->pose == 32) {
            g_api.PlaySfx(g_FaerieSfx.noMedicine);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    }

    CheckForValidAbility(self);
    ServantUpdateAnim(self, NULL, g_FaerieAnimationFrames);
}

void UpdateServantUseElementalResist(Entity* self) {
    s32 i;
    s32 rnd;

    s_TargetLocOffset_calc = -0x18;
    if (!PLAYER.facingLeft) {
        s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
    }
    s_TargetLocationX = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
    s_TargetLocationY = PLAYER.posY.i.hi - 0x18;
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        SetAnimationFrame(self, 14);
        break;

    case 1:
        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = StepAngleTowards(
            s_AngleToTarget, self->ext.faerie.targetAngle, 0x180);
        self->ext.faerie.targetAngle = s_AllowedAngle;
        self->velocityY = -(rsin(s_AllowedAngle) << 5);
        self->velocityX = rcos(s_AllowedAngle) << 5;
        SelectAnimationFrame(self);
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
        if (!g_Status
                 .equipHandCount[g_ResistItemsParamMap[self->params * 4 + 1]]) {
            SetAnimationFrame(self, 16);
            self->step = 5;
            break;
        }
        if (SearchForEntityInRange(1, 0x27)) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }

        SetAnimationFrame(self, 18);
        self->step++;
        break;

    case 3:
        self->facingLeft = PLAYER.facingLeft ? false : true;

        if (self->pose == 11) {
            rnd = rand() % 0x100;
            for (i = 0; true; i++) {
                if (rnd <= g_SfxRandomizerHammerResist[i * 2]) {
                    g_api.PlaySfx(g_SfxRandomizerHammerResist[i * 2 + 1]);
                    break;
                }
            }

            g_Status
                .equipHandCount[g_ResistItemsParamMap[self->params * 4 + 1]]--;

            g_api.CreateEntFactoryFromEntity(
                self,
                FACTORY(0x37, g_ResistItemsParamMap[self->params * 4 + 2]), 0);
            CreateEventEntity_Local(
                self, FAERIE_SUBENTITY_ITEM,
                g_ResistItemsParamMap[self->params * 4 + 3]);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;

    case 4:
    case 6:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }
        break;

    case 5:
        self->facingLeft = PLAYER.facingLeft;
        if (self->pose == 32) {
            g_api.PlaySfx(g_FaerieSfx.noMedicine);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    }

    CheckForValidAbility(self);
    ServantUpdateAnim(self, NULL, g_FaerieAnimationFrames);
}

void UpdateServantUsePotion(Entity* self) {
    s_TargetLocOffset_calc = -0x18;
    if (!PLAYER.facingLeft) {
        s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
    }
    s_TargetLocationX = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
    s_TargetLocationY = PLAYER.posY.i.hi - 0x18;
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        SetAnimationFrame(self, 14);
        break;

    case 1:
        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = StepAngleTowards(
            s_AngleToTarget, self->ext.faerie.targetAngle, 0x180);
        self->ext.faerie.targetAngle = s_AllowedAngle;
        self->velocityY = -(rsin(s_AllowedAngle) << 5);
        self->velocityX = rcos(s_AllowedAngle) << 5;
        SelectAnimationFrame(self);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        s_DistToTargetLocation =
            CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);
        if (s_DistToTargetLocation < 2) {
            self->step++;
        }
        break;

    case 2:
        if (!g_Status.equipHandCount[g_PotionItemsParamMap[self->params * 2]]) {
            self->params = self->params ? 0 : 1;
            if (!g_Status
                     .equipHandCount[g_PotionItemsParamMap[self->params * 2]]) {
                SetAnimationFrame(self, 20);
                self->step = 5;
                break;
            }
        }

        if (SearchForEntityInRange(1, 0x27)) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }

        SetAnimationFrame(self, 18);
        self->step++;
        break;

    case 3:
        self->facingLeft = PLAYER.facingLeft ? false : true;
        if (self->pose == 11) {
            g_api.PlaySfx(g_FaerieSfx.potion);
            g_Status.equipHandCount[g_PotionItemsParamMap[self->params * 2]]--;
            g_api.CreateEntFactoryFromEntity(
                self,
                FACTORY(0x37, g_PotionItemsParamMap[self->params * 2 + 1]), 0);
            CreateEventEntity_Local(self, FAERIE_SUBENTITY_ITEM, 2);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;

    case 4:
    case 6:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }
        break;

    case 5:
        self->facingLeft = PLAYER.facingLeft;
        if (self->pose == 32) {
            g_api.PlaySfx(g_FaerieSfx.noMedicine);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    }

    CheckForValidAbility(self);
    ServantUpdateAnim(self, NULL, g_FaerieAnimationFrames);
}

void UpdateServantAdditionalInit(Entity* self) {
    s16 rnd;
    s32 i;

    g_api.GetServantStats(self, 0, 0, &s_FaerieStats);
    if (D_us_80179320) {
        self->zPriority = PLAYER.zPriority - 2;
        s_zPriority = self->zPriority;
    }
    s_TargetLocOffset_calc = -0x18;
    if (!PLAYER.facingLeft) {
        s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
    }
    s_TargetLocationX_calc = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
    s_TargetLocationY_calc = PLAYER.posY.i.hi - 0x20;
    s_AngleToTarget = self->ext.faerie.randomMovementAngle;
    self->ext.faerie.randomMovementAngle += 0x10;
    self->ext.faerie.randomMovementAngle &= 0xFFF;
    s_DistToTargetLocation = self->ext.faerie.defaultDistToTargetLoc;

    s_TargetLocationX =
        s_TargetLocationX_calc +
        ((rcos(s_AngleToTarget / 2) * s_DistToTargetLocation) >> 0xC);
    s_TargetLocationY =
        s_TargetLocationY_calc -
        ((rsin(s_AngleToTarget) * (s_DistToTargetLocation / 2)) >> 0xC);

    s_AngleToTarget =
        CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
    s_AllowedAngle =
        StepAngleTowards(s_AngleToTarget, self->ext.faerie.targetAngle,
                         self->ext.faerie.maxAngle);
    self->ext.faerie.targetAngle = s_AllowedAngle;

    s_DistToTargetLocation =
        CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);

    if (s_DistToTargetLocation < 0x3C) {
        self->velocityY = -(rsin(s_AllowedAngle) << 3);
        self->velocityX = rcos(s_AllowedAngle) << 3;
        self->ext.faerie.maxAngle = 0x40;
    } else if (s_DistToTargetLocation < 0x64) {
        self->velocityY = -(rsin(s_AllowedAngle) << 4);
        self->velocityX = rcos(s_AllowedAngle) << 4;
        self->ext.faerie.maxAngle = 0x60;
    } else {
        self->velocityY = -(rsin(s_AllowedAngle) << 5);
        self->velocityX = rcos(s_AllowedAngle) << 5;
        self->ext.faerie.maxAngle = 0x80;
    }
    self->posX.val += self->velocityX;
    self->posY.val += self->velocityY;
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        self->ext.faerie.timer = -1;
        break;

    case 1:
        SelectAnimationFrame(self);
        if (IsMovementAllowed(1) || CheckAllEntitiesValid() ||
            s_RoomSpecialState == ROOM_SPECIAL_STATE_UNK1 ||
            g_CutsceneHasControl || g_unkGraphicsStruct.D_800973FC) {
            SetAnimationFrame(self, 14);
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }
        s_DistToTargetLocation =
            CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);
        if (s_DistToTargetLocation < 0x20) {
            self->facingLeft = PLAYER.facingLeft;
            self->step++;
        }
        break;

    case 2:
        rnd = rand() % 0x100;
        if (s_FaerieStats.unk8 == 1) {
            for (i = 0; true; i++) {
                if (rnd <= (s32)g_FaerieIntroRandomizer[i * 2]) {
                    self->ext.faerie.currentSfxEvent = (ServantSfxEventDesc*)
                        g_FaerieIntroRandomizer[i * 2 + 1];
                    break;
                }
            }
        } else {
            for (i = 0; true; i++) {
                if (rnd <= (s32)g_SfxEventRandomizer[i * 2]) {
                    self->ext.faerie.currentSfxEvent =
                        (ServantSfxEventDesc*)g_SfxEventRandomizer[i * 2 + 1];
                    break;
                }
            }
        }
        self->ext.faerie.sfxEventFlag =
            ((s16*)self->ext.faerie.currentSfxEvent)[0];
        pauseAllowed = false;
        self->step++;
        break;

    case 3:
        if (PLAYER.posX.i.hi >= self->posX.i.hi) {
            self->facingLeft = true;
        } else {
            self->facingLeft = false;
        }
        if (self->ext.faerie.sfxEventFlag < 0) {
            if (g_PlaySfxStep > 4) {
                SetAnimationFrame(
                    self, self->ext.faerie.currentSfxEvent->animIndex);
                self->step++;
            }
        } else {
            if (g_PlaySfxStep == 4 || g_PlaySfxStep >= 99) {
                self->ext.faerie.sfxEventFlag--;
            }
            if (self->ext.faerie.sfxEventFlag < 0) {
                SetAnimationFrame(
                    self, self->ext.faerie.currentSfxEvent->animIndex);
                if (self->ext.faerie.currentSfxEvent->sfxId != 0 &&
                    (SearchForEntityInRange(0, FAERIE_EVENT_SFX_PASSTHROUGH) ==
                     NULL)) {
                    CreateEventEntity_Local(
                        self, FAERIE_EVENT_SFX_PASSTHROUGH,
                        self->ext.faerie.currentSfxEvent->sfxId);
                }
                self->ext.faerie.currentSfxEvent++;
                self->ext.faerie.sfxEventFlag =
                    self->ext.faerie.currentSfxEvent->flag;
            }
        }
        break;

    case 4:
        if (g_PlaySfxStep == 99) {
            self->step++;
        }
        break;

    case 5:
        SetAnimationFrame(self, 14);
        pauseAllowed = true;
        self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
        self->step = 0;
        break;
    }

    ProcessEvent(self, false);
    CheckForValidAbility(self);
    ServantUpdateAnim(self, NULL, g_FaerieAnimationFrames);
    FntPrint("sts = %d\n", g_PlaySfxStep);
}

// This data needs to come after the string in FntPrint
#include "faerie_data.h"

void UpdateSubEntityWings(Entity* self) {
    s32 animIndex;
    s32 wingsInBackZ;
    s32 i;

    if (!self->step) {
        ExecuteAbilityInitialize(self);
        self->ext.faerieWings.parent = &g_Entities[SERVANT_ENTITY_INDEX];
        self->step++;
    }
    self->posX.val = self->ext.faerieWings.parent->posX.val;
    self->posY.val = self->ext.faerieWings.parent->posY.val;
    self->facingLeft = self->ext.faerieWings.parent->facingLeft;

    for (i = 6; i <= 0x2D; i++) {
        if (self->ext.faerieWings.parent->anim == g_FaerieAnimationFrames[i])
            break;
    }

    animIndex = abs(g_WingAnimationParams[i - 6].animIndex);
    wingsInBackZ = g_WingAnimationParams[i - 6].wingsInBackZ;

    SetAnimationFrame(self, animIndex);

    self->zPriority = wingsInBackZ ? (s_zPriority - 1) : (s_zPriority + 1);

    ServantUpdateAnim(self, 0, g_FaerieAnimationFrames);
}

void UpdateServantSitOnShoulder(Entity* self) {
    static u32 s_AnimationStatus;
    static s16 g_FaerieFrameCount1 = 5400;
    static s16 g_FaerieFrameCount2 = 2400;

    s32 rnd;
    s32 i;

    g_api.GetServantStats(self, 0, 0, &s_FaerieStats);
    if (D_us_80179320) {
        self->zPriority = PLAYER.zPriority - 2;
        s_zPriority = self->zPriority;
    }
    if (IsMovementAllowed(1)) {
        if (self->step < 2) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }

        if (self->step < 9) {
            self->step = 9;
        }
    }
    if (PLAYER.step_s == 0) {
        s_TargetLocOffset_calc = -6;
        if (PLAYER.facingLeft) {
            s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
        }
        s_TargetLocationX = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
        s_TargetLocationY = PLAYER.posY.i.hi - 12;
    } else {
        s_TargetLocOffset_calc = 16;
        if (PLAYER.facingLeft) {
            s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
        }
        s_TargetLocationX = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
        s_TargetLocationY = PLAYER.posY.i.hi - 8;
    }
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        SetAnimationFrame(self, 14);
        break;

    case 1:
        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = StepAngleTowards(
            s_AngleToTarget, self->ext.faerie.targetAngle, 0x180);
        self->ext.faerie.targetAngle = s_AllowedAngle;
        self->velocityY = -(rsin(s_AllowedAngle) << 3);
        self->velocityX = rcos(s_AllowedAngle) << 3;
        SelectAnimationFrame(self);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        s_DistToTargetLocation =
            CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);
        if (s_DistToTargetLocation < 2) {
            if (PLAYER.step_s == 0) {
                self->facingLeft = PLAYER.facingLeft;
            } else {
                self->facingLeft = PLAYER.facingLeft ? false : true;
            }
            SetAnimationFrame(self, 24);
            self->ext.faerie.frameCounter = 0;

            self->flags |= FLAG_POS_PLAYER_LOCKED;
            self->flags &= ~FLAG_POS_CAMERA_LOCKED;

#ifdef VERSION_PSP
            if (D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_20 ||
                D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_40 ||
                s_RoomSpecialState == ROOM_SPECIAL_STATE_UNK1 ||
                s_FaerieStats.level < 5) {
                self->step = 5;
            } else if (s_ServantId != FAM_ACTIVE_YOUSEI || PLAYER.step_s != 4) {
                self->step = 5;
            } else if (
                s_FaerieStats.level < 10 &&
                ((g_Timer & 1) || (s_FaerieStats.level < 5 && g_Timer & 7))) {
                self->step = 5;
            } else {
                self->ext.faerie.unkB4 = 0;
                if (s_FaerieStats.level < 16) {
                    self->ext.faerie.frameCounter = 0x708;
                } else {
                    self->ext.faerie.frameCounter =
                        0x7A8 - (s_FaerieStats.level << 0x4);
                }
                self->step++;
            }
#else
            if ((*((FgLayer32*)&D_8003C708)).flags &
                    (LAYOUT_RECT_PARAMS_UNKNOWN_20 |
                     LAYOUT_RECT_PARAMS_UNKNOWN_40) ||
                s_RoomSpecialState == ROOM_SPECIAL_STATE_UNK1 ||
                s_FaerieStats.level < 5) {
                self->step = 5;
            } else if (s_ServantId != FAM_ACTIVE_YOUSEI ||
                       s_FaerieStats.level < 50 || PLAYER.step_s != 4) {
                self->step = 5;
            } else if (s_FaerieStats.level < 90 && rand() % 8) {
                self->step = 5;
            } else {
                self->ext.faerie.unkB4 = 0;
                if (PLAYER.step_s == 4) {
                    self->ext.faerie.frameCounter = g_FaerieFrameCount2;
                } else {
                    self->ext.faerie.frameCounter = g_FaerieFrameCount1;
                }
                self->step++;
            }
#endif
        }
        break;

    case 2:
        self->ext.faerie.frameCounter--;
        if (self->ext.faerie.frameCounter < 0) {
            self->ext.faerie.frameCounter = 0;
            if (g_api.func_800F27F4(0)) {
                SetAnimationFrame(self, 25);
                self->ext.faerie.unkB4 = 1;
                self->step++;
            }
        }
        break;

    case 3:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 0x420) {
            SetAnimationFrame(self, 26);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;

    case 4:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 0x15E0) {
            SetAnimationFrame(self, 25);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;

    case 5:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 0x500) {
            SetAnimationFrame(self, 24);
            self->ext.faerie.frameCounter = 0;
            self->ext.faerie.unkB4 = 0;
            self->step++;
        }
        break;

    case 6:
        self->ext.faerie.frameCounter = (rand() % 0x800) + 0x400;
        self->step++;
        /* fallthrough */
    case 7:
        self->ext.faerie.frameCounter--;
        if (self->ext.faerie.frameCounter < 0) {
            self->ext.faerie.frameCounter = (rand() % 0x80) + 0x80;
            SetAnimationFrame(self, 25);
            self->step++;
        }
        break;

    case 8:
        self->ext.faerie.frameCounter--;
        if (self->ext.faerie.frameCounter < 0) {
            SetAnimationFrame(self, 24);
            self->step = 6;
        }
        break;

    case 9: // Happens when the faerie falls off your shoulder
        if (self->ext.faerie.unkB4) {
            g_api.func_800F27F4(1);
        }
        self->flags &= ~FLAG_POS_PLAYER_LOCKED;
        self->flags |= FLAG_POS_CAMERA_LOCKED;
        SetAnimationFrame(self, 27);
        self->velocityX = self->facingLeft ? FIX(-0.25) : FIX(0.25);
        self->velocityY = FIX(1);
        rnd = rand() % 0x100;
        for (i = 0; true; i++) {
            if (rnd <= g_SfxRandomizerGrunt[i * 2]) {
                g_api.PlaySfx(g_SfxRandomizerGrunt[i * 2 + 1]);
                break;
            }
        }

        self->step++;
        break;

    case 10: // performs the fall animation
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY -= FIX(0.03125);

        // fall animation is finished
        if (s_AnimationStatus == -1) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }
        break;
    }
    ProcessEvent(self, false);
    CheckForValidAbility(self);
#ifdef VERSION_PSP
    if ((self->step == 3 || self->step == 4) &&
        g_AlucardChairSleepTimer < 0x200) {
        g_AlucardChairSleepTimer = 0x200;
    }
#endif
    unused_39C8(self);
    s_AnimationStatus = ServantUpdateAnim(self, NULL, g_FaerieAnimationFrames);
}

// self->param is index for g_FaerieHints for the type of hint
void UpdateServantOfferHint(Entity* self) {
    static s32 s_HintTargetX;
    static s32 s_HintTargetY;

    self->ext.faerie.tileMapX = g_Tilemap.left * 0x100 + g_Tilemap.scrollX.i.hi;
    self->ext.faerie.tileMapY = g_Tilemap.top * 0x100 + g_Tilemap.scrollY.i.hi;

    if (D_us_80179320) {
        self->zPriority = PLAYER.zPriority - 2;
        s_zPriority = self->zPriority;
    }

    if ((s32)g_FaerieHints[self->params * 3] == -1 || self->step <= 0) {
        s_TargetLocOffset_calc = -0x18;
        if (!PLAYER.facingLeft) {
            s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
        }
        s_TargetLocationX_calc = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
        s_TargetLocationY_calc = PLAYER.posY.i.hi - 0x20;
    } else {
        s_TargetLocationX_calc = s_HintTargetX - self->ext.faerie.tileMapX;
        s_TargetLocationY_calc = s_HintTargetY - self->ext.faerie.tileMapY;
    }

    s_AngleToTarget = self->ext.faerie.randomMovementAngle;
    self->ext.faerie.randomMovementAngle += 0x10;
    self->ext.faerie.randomMovementAngle &= 0xFFF;
    s_DistToTargetLocation = self->ext.faerie.defaultDistToTargetLoc;

    s_TargetLocationX =
        s_TargetLocationX_calc +
        ((rcos(s_AngleToTarget / 2) * s_DistToTargetLocation) >> 12);

    s_TargetLocationY =
        s_TargetLocationY_calc -
        ((rsin(s_AngleToTarget) * (s_DistToTargetLocation / 2)) >> 12);
    s_AngleToTarget =
        CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
    s_AllowedAngle =
        StepAngleTowards(s_AngleToTarget, self->ext.faerie.targetAngle,
                         self->ext.faerie.maxAngle);
    self->ext.faerie.targetAngle = s_AllowedAngle;
    s_DistToTargetLocation =
        CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);

    if (s_DistToTargetLocation < 60) {
        self->velocityY = -(rsin(s_AllowedAngle) * 8);
        self->velocityX = rcos(s_AllowedAngle) * 8;
        self->ext.faerie.maxAngle = 0x40;
    } else if (s_DistToTargetLocation < 100) {
        self->velocityY = -(rsin(s_AllowedAngle) * 16);
        self->velocityX = rcos(s_AllowedAngle) * 16;
        self->ext.faerie.maxAngle = 0x60;
    } else {
        self->velocityY = -(rsin(s_AllowedAngle) * 32);
        self->velocityX = rcos(s_AllowedAngle) * 32;
        self->ext.faerie.maxAngle = 0x80;
    }

    self->posX.val += self->velocityX;
    self->posY.val += self->velocityY;

    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        s_HintTargetX = (s32)g_FaerieHints[self->params * 3 + 0] +
                        self->ext.faerie.tileMapX;
        s_HintTargetY = (s32)g_FaerieHints[self->params * 3 + 1] +
                        self->ext.faerie.tileMapY;
        self->ext.faerie.timer = -1;
        break;

    case 1:
        SelectAnimationFrame(self);
        s_DistToTargetLocation =
            CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);
        if (s_DistToTargetLocation < 32) {
            self->facingLeft = PLAYER.facingLeft;
            self->step++;
        }
        break;

    case 2:
        self->ext.faerie.currentSfxEvent =
            (ServantSfxEventDesc*)g_FaerieHints[self->params * 3 + 2];
        // This is self->ext.faerie.currentSfxEvent->flag, but the weird cast is
        // needed for match
        self->ext.faerie.sfxEventFlag =
            *((s16*)self->ext.faerie.currentSfxEvent);
        pauseAllowed = false;
        self->step++;
        break;

    case 3:
        if (PLAYER.posX.i.hi >= self->posX.i.hi) {
            self->facingLeft = true;
        } else {
            self->facingLeft = false;
        }

        if (self->ext.faerie.sfxEventFlag < 0) {
            if (g_PlaySfxStep > 4) {
                SetAnimationFrame(
                    self, self->ext.faerie.currentSfxEvent->animIndex);
                self->step++;
            }
        } else {
            if (g_PlaySfxStep == 4 || g_PlaySfxStep >= 99) {
                self->ext.faerie.sfxEventFlag--;
            }

            if (self->ext.faerie.sfxEventFlag < 0) {
                SetAnimationFrame(
                    self, self->ext.faerie.currentSfxEvent->animIndex);
                if (self->ext.faerie.currentSfxEvent->sfxId != 0 &&
                    SearchForEntityInRange(0, FAERIE_EVENT_SFX_PASSTHROUGH) ==
                        NULL) {
                    CreateEventEntity_Local(
                        self, FAERIE_EVENT_SFX_PASSTHROUGH,
                        self->ext.faerie.currentSfxEvent->sfxId);
                }

                self->ext.faerie.currentSfxEvent++;
                self->ext.faerie.sfxEventFlag =
                    self->ext.faerie.currentSfxEvent->flag;
            }
        }
        break;

    case 4:
        SetAnimationFrame(self, 14);
        pauseAllowed = true;
        self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
        self->step = 0;
        break;
    }

    unused_39C8(self);
    ServantUpdateAnim(self, NULL, g_FaerieAnimationFrames);
}

// Unsure where this code is exectued from, but it would be where
// an entity is created with Entity ID DC
// It has to be from the engine somewhere as they are triggered
// from room states (for the most part)
void UpdateEntitySetRoomSpecialState(Entity* self) {
    Entity* entity;

    switch (self->params) {
    case 0:
        s_RoomSpecialState = ROOM_SPECIAL_STATE_UNK1;
        if ((entity = SearchForEntityInRange(
                 0, FAERIE_EVENT_SFX_PASSTHROUGH)) != NULL &&
            entity->step < 5) {
            entity->step = 8;
        }
        break;
    case 1:
        s_RoomSpecialState = ROOM_SPECIAL_STATE_DARKNESS;
        break;
    case 2:
        s_RoomSpecialState = ROOM_SPECIAL_STATE_MIST;
        break;
    case 3:
        s_RoomSpecialState = ROOM_SPECIAL_STATE_WALL_HINT1;
        break;
    case 4:
        s_RoomSpecialState = ROOM_SPECIAL_STATE_SUS_HINT1;
        break;
    case 5:
        s_RoomSpecialState = ROOM_SPECIAL_STATE_WALL_HINT2;
        break;
    case 6:
        s_RoomSpecialState = ROOM_SPECIAL_STATE_WALL_HINT3;
        break;
    case 7:
        s_RoomSpecialState = ROOM_SPECIAL_STATE_WALL_HINT4;
        break;
    case 8:
        s_RoomSpecialState = ROOM_SPECIAL_STATE_SUS_HINT2;
        break;
    case 9:
        s_RoomSpecialState = ROOM_SPECIAL_STATE_WALL_HINT5;
        break;
    case 10:
        s_RoomSpecialState = ROOM_SPECIAL_STATE_SUS_HINT3;
        break;
    case 15:
        D_us_80179320 = true;
        break;
    }
    DestroyEntity(self);
}

void UpdateSubEntityUseLifeApple(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 temp_x;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_G4, 10);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        self->posX.i.hi += self->facingLeft ? -4 : 4;

        prim = &g_PrimBuf[self->primIndex];

        prim->r1 = prim->r3 = prim->g1 = prim->g3 = prim->b1 = prim->b3 = 0xFF;
        prim->priority = 0x1C0;
        prim->drawMode = FLAG_DRAW_UNK400 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK10 |
                         FLAG_DRAW_ROTATE | FLAG_DRAW_SCALEX;

        prim = prim->next;

        prim->r1 = prim->r3 = prim->g1 = prim->g3 = prim->b1 = prim->b3 = 0xFF;
        prim->priority = 0x1C0;
        prim->drawMode = FLAG_DRAW_UNK400 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK10 |
                         FLAG_DRAW_ROTATE | FLAG_DRAW_SCALEX;

        for (i = 0; i < 8; i++) {
            prim = prim->next;
            prim->x0 = prim->x1 = self->posX.i.hi;
            prim->y0 = prim->y1 = 0;
            prim->x2 = self->posX.i.hi + ((rcos(i << 8) * 0x60) >> 0xC);
            prim->x3 = self->posX.i.hi + ((rcos((i + 1) << 8) * 0x60) >> 0xC);
            prim->y2 = (rsin(i << 8) * 3) << 5 >> 0xC;
            prim->y3 = (rsin((i + 1) << 8) * 3) << 5 >> 0xC;
            prim->priority = 0x1C0;
            prim->drawMode =
                FLAG_DRAW_UNK400 | FLAG_DRAW_UNK20 | FLAG_DRAW_UNK10 |
                FLAG_DRAW_ROTATE | FLAG_DRAW_SCALEX;
        }
        self->ext.faerieLifeApple.primX = 0x10;
        self->ext.faerieLifeApple.primY = 0;
        self->ext.faerieLifeApple.opacity = 0x40;
        self->ext.faerieLifeApple.effectOpacity = 0;
        self->step++;
        break;

    case 1:
        self->ext.faerieLifeApple.effectOpacity += 4;
        self->ext.faerieLifeApple.primY += 0x10;

        if (self->ext.faerieLifeApple.primY >= 0x100) {
            self->step++;
        }
        break;

    case 2:
        self->ext.faerieLifeApple.lifeAppleTimer++;
        if (self->ext.faerieLifeApple.lifeAppleTimer > 0xF) {
            self->step++;
        }
        break;

    case 3:
        self->ext.faerieLifeApple.opacity += 4;
        if (self->ext.faerieLifeApple.opacity >= 0x100) {
            self->ext.faerieLifeApple.opacity = 0xFF;
        }

        self->ext.faerieLifeApple.primX += 4;
        if (self->ext.faerieLifeApple.primX >= 0x100) {
            self->ext.faerieLifeApple.lifeAppleTimer = 0;
            self->step++;
        }
        break;

    case 4:
        self->ext.faerieLifeApple.lifeAppleTimer++;
        if (self->ext.faerieLifeApple.lifeAppleTimer > 60) {
            self->step++;
        }
        break;

    case 5:
        self->ext.faerieLifeApple.effectOpacity--;
        if (self->ext.faerieLifeApple.effectOpacity < 0) {
            self->ext.faerieLifeApple.effectOpacity = 0;
        }

        self->ext.faerieLifeApple.opacity -= 4;
        if (self->ext.faerieLifeApple.opacity <= 0x40) {
            self->ext.faerieLifeApple.opacity = 0x40;
        }

        self->ext.faerieLifeApple.primX -= 8;
        if (self->ext.faerieLifeApple.primX <= 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    prim = &g_PrimBuf[self->primIndex];

    temp_x = self->posX.i.hi - self->ext.faerieLifeApple.primX;
    if (temp_x < 0) {
        temp_x = 0;
    }
    prim->x0 = prim->x2 = temp_x;
    prim->x1 = prim->x3 = self->posX.i.hi;
    prim->y0 = prim->y1 = 0;
    prim->y2 = prim->y3 = self->ext.faerieLifeApple.primY;
    prim->r0 = prim->r2 = prim->g0 = prim->g2 = prim->b0 = prim->b2 =
        self->ext.faerieLifeApple.opacity;

    prim = prim->next;

    temp_x = self->posX.i.hi + self->ext.faerieLifeApple.primX;
    if (temp_x > 0x100) {
        temp_x = 0x100;
    }
    prim->x0 = prim->x2 = temp_x;
    prim->x1 = prim->x3 = self->posX.i.hi;
    prim->y0 = prim->y1 = 0;
    prim->y2 = prim->y3 = self->ext.faerieLifeApple.primY;
    prim->r0 = prim->r2 = prim->g0 = prim->g2 = prim->b0 = prim->b2 =
        self->ext.faerieLifeApple.opacity;

    for (i = 0; i < 8; i++) {
        prim = prim->next;

        prim->r0 = prim->r1 = prim->g0 = prim->g1 = prim->b0 = prim->b1 =
            self->ext.faerieLifeApple.effectOpacity;
        prim->r2 = prim->r3 = prim->g2 = prim->g3 = prim->b2 = prim->b3 = 0;
    }
}

void UpdateServantSfxPassthrough(Entity* self) { ProcessSfxState(self); }

void UpdateSubEntityUseItem(Entity* self) {
    s16 item = self->params;
    ItemPrimitiveParams* ptr = &g_ItemPrimitiveParams[item];
    s16 x0 = self->posX.i.hi;
    s16 y0 = self->posY.i.hi;
    s16 unusedX = PLAYER.posX.i.hi;
    s16 unusedY = PLAYER.posY.i.hi;

    FakePrim* prim;
    s32 i;
    s16 x1, y1;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.func_800EDB58(PRIM_TILE_ALT, ptr->count + 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = ptr->flags;
        prim = (FakePrim*)&g_PrimBuf[self->primIndex];

        for (i = 0; true; i++, prim = prim->next) {
            prim->drawMode = ptr->drawMode + DRAW_HIDE;
            prim->priority = ptr->priority + PLAYER.zPriority;
            if (prim->next == NULL) {
                prim->drawMode &= ~DRAW_HIDE;
                prim->y0 = prim->x0 = prim->w = 0;
                break;
            }

            prim->posX.i.hi = x0;
            prim->posY.i.hi = y0;
            prim->posX.i.lo = prim->posY.i.lo = 0;
            switch (ptr->unk6) {
            case 0:
                prim->posX.i.hi = x0 + (self->facingLeft ? -4 : 4);
                prim->posY.i.hi = y0 - 0x1A;
                prim->velocityX.val = ((rand() % 0x2000) - 0x1000) << 4;
                prim->velocityY.val = 0;
                break;

            case 1:
                x1 = x0 + (self->facingLeft ? 24 : -24);
                y1 = y0 + 0x10;
                prim->posX.i.hi = x1 + ((rand() % 16) - 8);
                prim->posY.i.hi = y1;
                prim->velocityX.val = ((rand() % 0x2000) - 0x1000) << 4;
                prim->velocityY.val = -((rand() % 0x1000) + 0x1800) << 4;
                prim->delay = 45;
                break;

            case 2:
                x1 = x0 + (self->facingLeft ? -14 : 14);
                y1 = y0 - 8;
                prim->posX.i.hi = x1;
                prim->posY.i.hi = y1;
                prim->velocityX.val = (rand() % 0x800) << 4;
                if (self->facingLeft) {
                    prim->velocityX.val = -prim->velocityX.val;
                }
                prim->velocityY.val = -((rand() % 0x1000) + 0x800) << 4;
                prim->delay = 40;
                break;
            }
            prim->x0 = prim->posX.i.hi;
            prim->y0 = prim->posY.i.hi;
            prim->r0 = ptr->r;
            prim->g0 = ptr->g;
            prim->b0 = ptr->b;
            prim->w = ptr->w;
            prim->h = ptr->h;
        }
        self->step++;
        // fallthrough
    case 1:
        // The hammer runs this code more than once, the other items only once
        self->ext.faerieItem.unkFlag--;
        if (self->ext.faerieItem.unkFlag <= 0) {
            prim = (FakePrim*)&g_PrimBuf[self->primIndex];
            for (i = 0; i < self->ext.faerieItem.unkAccumulator; i++) {
                prim = prim->next;
            }
            for (i = 0; i < ptr->unk2; i++) {
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            }
            self->ext.faerieItem.unkAccumulator += ptr->unk2;
            if (self->ext.faerieItem.unkAccumulator >= ptr->count) {
                self->step++;
            }
            self->ext.faerieItem.unkFlag = ptr->unk4;
        }
        // fallthrough
    case 2:
        prim = (FakePrim*)&g_PrimBuf[self->primIndex];
        i = 0;
        self->ext.faerieItem.unk7E = 0;
        while (true) {
            if (prim->next == NULL) {
                prim->drawMode &= ~DRAW_HIDE;
                prim->y0 = prim->x0 = prim->w = 0;
                break;
            }

            prim->posX.i.hi = prim->x0;
            prim->posY.i.hi = prim->y0;
            switch (ptr->unk6) {
            case 0:
                if (!(prim->drawMode & DRAW_HIDE)) {
                    prim->posX.val += prim->velocityX.val;
                    prim->posY.val += prim->velocityY.val;
                    prim->velocityX.val =
                        AccumulateTowardZero(prim->velocityX.val, 0x1000);
                    prim->velocityY.val -= FIX(2.0 / 16);
                    if (prim->posY.i.hi < 0) {
                        prim->drawMode |= DRAW_HIDE;
                    }
                }
                break;

            case 1:
                if (!(prim->drawMode & DRAW_HIDE)) {
                    prim->posX.val += prim->velocityX.val;
                    prim->posY.val += prim->velocityY.val;
                    prim->velocityY.val += FIX(2.0 / 16);
                    prim->delay--;
                    if (prim->delay < 0) {
                        prim->drawMode |= DRAW_HIDE;
                    }
                }
                break;

            case 2:
                if (!(prim->drawMode & DRAW_HIDE)) {
                    prim->posX.val += prim->velocityX.val;
                    prim->posY.val += prim->velocityY.val;
                    if (prim->r0) {
                        prim->r0--;
                    }
                    if (prim->g0) {
                        prim->g0--;
                    }
                    if (prim->b0) {
                        prim->b0--;
                    }
                    prim->velocityY.val += FIX(1.5 / 16);
                    prim->delay--;
                    if (prim->delay < 0) {
                        prim->drawMode |= DRAW_HIDE;
                    }
                }
                break;
            }
            prim->x0 = prim->posX.i.hi;
            prim->y0 = prim->posY.i.hi;
            i++;
            self->ext.faerieItem.unk7E |= (prim->drawMode & DRAW_HIDE) ? 0 : 1;
            prim = prim->next;
        }
        if (!self->ext.faerieItem.unk7E) {
            DestroyEntity(self);
        }
    }
}

#include "../shared_events.h"
#include "../shared_globals.h"
#include "../servant_update_anim.h"
#include "../../destroy_entity.h"
#include "../accumulate_toward_zero.h"
#include "../search_for_entity_in_range.h"
#include "../calculate_angle_to_entity.h"
#include "../step_angle_towards.h"
#include "../calculate_distance.h"
#include "../play_sfx.h"
#include "../process_event.h"
#include "../create_event_entity.h"
#include "../is_movement_allowed.h"
#include "../check_all_entities_valid.h"
#include "../servant_unk0.h"
