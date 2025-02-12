// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "faerie.h"
#include "sfx.h"
#include "items.h"
#include "../servant_private.h"

static u32 s_AnimationStatus;
static s32 s_HintTargetX;
static s32 s_HintTargetY;
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
static s32 D_us_80179320; // Possibly when player is sitting
static s32 s_TargetLocationX;
static s32 s_TargetLocationY;
static s32 s_TargetLocationX_calc;
static s32 s_TargetLocationY_calc;
static s32 s_AngleToTarget;
static s32 s_AllowedAngle;
static s32 s_DistToTargetLocation;
static s16 s_TargetLocOffset_calc;

extern u16 g_FaerieClut[64];

extern FaerieAbilityStats g_FaerieAbilityStats[];
extern FaerieSfx g_FaerieSfx;
extern s16 g_ResistItemsParamMap[];
extern s16 g_PotionItemsParamMap[];
extern unkGraphicsStruct g_unkGraphicsStruct;
extern ItemPrimitiveParams g_ItemPrimitiveParams[];
extern u16 g_FaerieFrameCount1;
extern u16 g_FaerieFrameCount2;

extern s32 g_SfxRandomizerGrunt[];
extern s32 g_SfxRandomizerHammerResist[];

extern HintTriggerMap g_FaerieHints[];

extern FaerieWingAnimationParams g_WingAnimationParams[];
extern AnimationFrame* g_FaerieAnimationFrames[];

void unused_39C8(Entity*);
void CheckForValidAbility(Entity*);

static void UpdateServantUseLifeApple(Entity* self);
static void UpdateServantUseHammer(Entity* self);
static void UpdateServantUseUncurse(Entity* self);
static void UpdateServantUseAntivenom(Entity* self);
static void UpdateServantUseElementalResist(Entity* self);
static void UpdateServantUsePotion(Entity* self);
static void UpdateServantAdditionalInit(Entity* self);
static void UpdateSubEntityWings(Entity* self);
static void UpdateServantSitOnShoulder(Entity* self);
static void UpdateServantOfferHint(Entity* self);
static void UpdateEntitySetRoomSpecialState(Entity* self);
static void UpdateSubEntityUseLifeApple(Entity* self);
static void UpdateServantSfxPassthrough(Entity* self);
static void UpdateSubEntityUseItem(Entity* self);

ServantDesc faerie_ServantDesc = {
    ServantInit,
    UpdateServantDefault,
    UpdateServantUseLifeApple,
    UpdateServantUseHammer,
    UpdateServantUseUncurse,
    UpdateServantUseAntivenom,
    UpdateServantUseElementalResist,
    UpdateServantUsePotion,
    UpdateServantAdditionalInit,
    UpdateSubEntityWings,
    UpdateServantSitOnShoulder,
    UpdateServantOfferHint,
    UpdateEntitySetRoomSpecialState,
    UpdateSubEntityUseLifeApple,
    UpdateServantSfxPassthrough,
    UpdateSubEntityUseItem};

static void SetAnimationFrame(Entity* self, s32 animationIndex) {
    if (self->anim != g_FaerieAnimationFrames[animationIndex]) {
        self->anim = g_FaerieAnimationFrames[animationIndex];
        self->animFrameIdx = 0;
        self->animFrameDuration = 0;
    }
}

void unused_39C8(Entity* arg0) {}

void ExecuteAbilityInitialize(Entity* self) {
    if (!self->ext.faerie.isAbilityInitialized) {

        switch (self->entityId) {
        case FAERIE_MODE_DEFAULT_UPDATE:
        case FAERIE_MODE_ADDITIONAL_INIT:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;

            SetAnimationFrame(self, 0xE);

            self->ext.faerie.randomMovementAngle = rand() % 4096;
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
            SetAnimationFrame(self, 0xE);
            self->step++;
            break;
        case FAERIE_SUBENTITY_WINGS:
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_UNK_20000;
            self->step++;
        }
    }
    self->ext.faerie.isAbilityInitialized = self->entityId;
    s_RoomSpecialState = 0;
}

// This is a duplicate CreateEventEntity which is lower in the file, but we need
// both to match the binary for PSX.  They are identical, but faerie uses this
// one.
void CreateEventEntity_Local(Entity* entityParent, s32 entityId, s32 params) {
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

void SelectAnimationFrame(Entity* self) {
    if (abs(self->velocityY) > abs(self->velocityX)) {
        if (abs(self->velocityY) < FIX(0.5)) {
            if (self->ext.faerie.animationFlag == 1) {
                self->ext.faerie.animationFlag = 0;
                SetAnimationFrame(self, 0x29);
            } else if (self->ext.faerie.animationFlag == 2) {
                self->ext.faerie.animationFlag = 0;
                SetAnimationFrame(self, 0xE);
            }
        } else if (abs(self->velocityY) > FIX(1)) {
            if (self->velocityY >= 0) {
                self->ext.faerie.animationFlag = 2;
                SetAnimationFrame(self, 0xB);
            } else {
                self->ext.faerie.animationFlag = 2;
                SetAnimationFrame(self, 0xC);
            }
        }
    } else {
        if (abs(self->velocityX) > FIX(0.5625)) {
            if (self->ext.faerie.animationFlag == 0) {
                self->ext.faerie.animationFlag = 1;
                SetAnimationFrame(self, 0xF);
            } else if (self->ext.faerie.animationFlag == 2) {
                self->ext.faerie.animationFlag = 0;
                SetAnimationFrame(self, 0xE);
            }
        } else if (abs(self->velocityX) < FIX(0.375)) {
            if (self->ext.faerie.animationFlag == 1) {
                self->ext.faerie.animationFlag = 0;
                SetAnimationFrame(self, 0x29);
            } else if (self->ext.faerie.animationFlag == 2) {
                self->ext.faerie.animationFlag = 0;
                SetAnimationFrame(self, 0xE);
            }
        }
        if (abs(self->velocityX) > FIX(0.5)) {
            if (self->velocityX >= 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
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

    for (unkHpSum = 0, params = 0, i = 0; i < 5; i++) {
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

    // if health greater than ¼ max
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

void ServantInit(InitializeMode mode) {
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

    dst = &g_Clut[CLUT_INDEX_SERVANT];
    src = g_FaerieClut;
    for (i = 0; i < len; i++) {
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
    *spriteBanks = (SpriteParts*)g_FaerieSpriteParts;

    entity = &g_Entities[SERVANT_ENTITY_INDEX];

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

    s_zPriority = (s32)entity->zPriority;
    g_api.GetServantStats(entity, 0, 0, &s_FaerieStats);

    entity++;
    DestroyEntity(entity);
    entity->entityId = FAERIE_SUBENTITY_WINGS;
    entity->unk5A = 0x6C;
    entity->palette = 0x140;
    entity->animSet = ANIMSET_OVL(20);
    entity->zPriority = PLAYER.zPriority - 3;
    entity->facingLeft = PLAYER.facingLeft;
    entity->params = 0;

    s_RoomSpecialState = 0;
    D_us_80179320 = 0;
    g_api.GetServantStats(entity, 0, 0, &s_FaerieStats);
}

void UpdateServantDefault(Entity* self) {
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
        s_DistToTargetLocation = self->ext.faerie.defaultDistToTargetLoc;

        s_TargetLocationX =
            s_TargetLocationX_calc +
            ((rcos(s_AngleToTarget / 2) * s_DistToTargetLocation) >> 0xC);
        s_TargetLocationY =
            s_TargetLocationY_calc -
            ((rsin(s_AngleToTarget) * (s_DistToTargetLocation / 2)) >> 0xC);
    }
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        self->ext.faerie.animationFlag = 0;
        SetAnimationFrame(self, 0xE);

        s_CachedHp = g_Status.hp;
        s_HpDifferenceIndex = 0;
        s_HpCacheResetTimer = 0;
        self->ext.faerie.idleFrameCounter = 0;
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

        SelectAnimationFrame(self);

        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;

        if (!g_CutsceneHasControl && !IsMovementAllowed(1) &&
            !CheckAllEntitiesValid() && !(D_8003C708.flags & FLAG_UNK_20)) {
            self->ext.faerie.idleFrameCounter += 1;
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
        s_DistToTargetLocation = self->ext.faerie.defaultDistToTargetLoc;
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
        SelectAnimationFrame(self);
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
            g_api.PlaySfx(g_FaerieSfx.regeneration);
        }
        self->step++;
        break;
    case 0x6:
        if (self->animFrameIdx == 0xA) {
            if (s_ServantId == FAM_ACTIVE_FAERIE) {
                g_api.PlaySfx(g_FaerieSfx.regeneration);
            }
            self->step++;
        }
        break;
    case 0x7:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            CreateEventEntity_Local(self, FAERIE_SUBENTITY_ITEM, 0);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    case 0x8:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            CreateEventEntity_Local(self, FAERIE_SUBENTITY_LIFE_APPLE, 0);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    case 0x9:
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
    case 0xA:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 90) {
            g_unkGraphicsStruct.unk20 = 0;
            self->step++;
        }
        break;
    case 0xB:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 60) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }
        break;

    case 0x5A: // Only get here when you are dead and have no life apple
        SetAnimationFrame(self, 0x20);
        g_api.PlaySfx(g_FaerieSfx.ohNo);
        self->step++;
        break;
    case 0x5B:
        break;
    }

    ServantUpdateAnim(self, NULL, g_FaerieAnimationFrames);
}

void UpdateServantUseHammer(Entity* self) {
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
        ExecuteAbilityInitialize(self);
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
            SetAnimationFrame(self, 0x17);

            for (rnd = rand() % 0x100, i = 0; true; i++) {
                if (rnd <= g_SfxRandomizerHammerResist[i * 2]) {
                    g_api.PlaySfx(g_SfxRandomizerHammerResist[i * 2 + 1]);
                    break;
                }
            }

            self->step++;
        } else {
            SetAnimationFrame(self, 0x10);
            g_api.PlaySfx(g_FaerieSfx.noMedicine);
            self->ext.faerie.frameCounter = 0;
            self->step += 2;
        }
        break;
    case 3:
        if (self->animFrameIdx == 5) {
            g_Status.equipHandCount[ITEM_HAMMER]--;
            g_api.CreateEntFactoryFromEntity(
                self, FACTORY(0x37, paramOffset), 0);
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
    const int paramOffset = 1;

    s_TargetLocOffset_calc = -0x18;
    if (!PLAYER.facingLeft) {
        s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
    }
    s_TargetLocationX = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
    s_TargetLocationY = PLAYER.posY.i.hi - 0x18;
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
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
            SetAnimationFrame(self, 0x14);
            self->step = 5;
            break;
        }
        if (SearchForEntityInRange(1, 0x27)) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }
        SetAnimationFrame(self, 0x12);
        if (s_ServantId == FAM_ACTIVE_YOUSEI) {
            g_api.PlaySfx(g_FaerieSfx.healing);
        }
        self->step++;
        break;

    case 3:
        self->facingLeft = PLAYER.facingLeft ? 0 : 1;
        if (self->animFrameIdx == 0xB) {
            if (s_ServantId == FAM_ACTIVE_FAERIE) {
                g_api.PlaySfx(g_FaerieSfx.healing);
            }

            g_Status.equipHandCount[ITEM_UNCURSE]--;
            g_api.CreateEntFactoryFromEntity(
                self, FACTORY(0x37, paramOffset), 0);

            CreateEventEntity_Local(
                self, FAERIE_SUBENTITY_ITEM, paramOffset + 3);
            self->ext.faerie.frameCounter = 0;
            self->step++;
            break;
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
        if (self->animFrameIdx == 0x20) {
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
    const int paramOffset = 0;

    s_TargetLocOffset_calc = -0x18;
    if (!PLAYER.facingLeft) {
        s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
    }
    s_TargetLocationX = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
    s_TargetLocationY = PLAYER.posY.i.hi - 0x18;
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
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
            SetAnimationFrame(self, 0x14);
            self->step = 5;
            break;
        }
        if (SearchForEntityInRange(1, 0x27)) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }
        SetAnimationFrame(self, 0x12);
        if (s_ServantId == FAM_ACTIVE_YOUSEI) {
            g_api.PlaySfx(g_FaerieSfx.healing);
        }
        self->step++;
        break;

    case 3:
        self->facingLeft = PLAYER.facingLeft ? 0 : 1;
        if (self->animFrameIdx == 0xB) {
            if (s_ServantId == FAM_ACTIVE_FAERIE) {
                g_api.PlaySfx(g_FaerieSfx.healing);
            }

            g_Status.equipHandCount[ITEM_ANTIVENOM]--;
            g_api.CreateEntFactoryFromEntity(
                self, FACTORY(0x37, paramOffset), 0);

            CreateEventEntity_Local(
                self, FAERIE_SUBENTITY_ITEM, paramOffset + 3);
            self->ext.faerie.frameCounter = 0;
            self->step++;
            break;
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
        if (self->animFrameIdx == 0x20) {
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
    s32 temp;

    s_TargetLocOffset_calc = -0x18;
    if (!PLAYER.facingLeft) {
        s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
    }
    s_TargetLocationX = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
    s_TargetLocationY = PLAYER.posY.i.hi - 0x18;
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
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
            SetAnimationFrame(self, 0x10);
            self->step = 5;
            break;
        }
        if (SearchForEntityInRange(1, 0x27)) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
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
        if (self->animFrameIdx == 0x20) {
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
    s32 temp;

    s_TargetLocOffset_calc = -0x18;
    if (!PLAYER.facingLeft) {
        s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
    }
    s_TargetLocationX = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
    s_TargetLocationY = PLAYER.posY.i.hi - 0x18;
    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
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
            if (self->params) {
                temp = 0;
            } else {
                temp = 1;
            }
            self->params = temp;
            if (!g_Status
                     .equipHandCount[g_PotionItemsParamMap[self->params * 2]]) {
                SetAnimationFrame(self, 0x14);
                self->step = 5;
                break;
            }
        }

        if (SearchForEntityInRange(1, 0x27)) {
            self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            self->step = 0;
            return;
        }

        SetAnimationFrame(self, 0x12);
        self->step++;
        break;
    case 3:
        self->facingLeft = PLAYER.facingLeft ? 0 : 1;
        if (self->animFrameIdx == 0xB) {
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
        if (self->animFrameIdx == 0x20) {
            g_api.PlaySfx(g_FaerieSfx.noMedicine);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    }

    CheckForValidAbility(self);
    ServantUpdateAnim(self, NULL, g_FaerieAnimationFrames);
}

void UpdateServantAdditionalInit(Entity* arg0) {
    s16 rnd;
    s32 i;

    g_api.GetServantStats(arg0, 0, 0, &s_FaerieStats);
    if (D_us_80179320) {
        arg0->zPriority = PLAYER.zPriority - 2;
        s_zPriority = arg0->zPriority;
    }
    s_TargetLocOffset_calc = -0x18;
    if (!PLAYER.facingLeft) {
        s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
    }
    s_TargetLocationX_calc = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
    s_TargetLocationY_calc = PLAYER.posY.i.hi - 0x20;
    s_AngleToTarget = arg0->ext.faerie.randomMovementAngle;
    arg0->ext.faerie.randomMovementAngle += 0x10;
    arg0->ext.faerie.randomMovementAngle &= 0xfff;
    s_DistToTargetLocation = arg0->ext.faerie.defaultDistToTargetLoc;

    s_TargetLocationX =
        s_TargetLocationX_calc +
        ((rcos(s_AngleToTarget / 2) * s_DistToTargetLocation) >> 0xC);
    s_TargetLocationY =
        s_TargetLocationY_calc -
        ((rsin(s_AngleToTarget) * (s_DistToTargetLocation / 2)) >> 0xC);

    s_AngleToTarget =
        CalculateAngleToEntity(arg0, s_TargetLocationX, s_TargetLocationY);
    s_AllowedAngle = GetTargetPositionWithDistanceBuffer(
        s_AngleToTarget, arg0->ext.faerie.targetAngle,
        arg0->ext.faerie.maxAngle);
    arg0->ext.faerie.targetAngle = s_AllowedAngle;

    s_DistToTargetLocation =
        CalculateDistance(arg0, s_TargetLocationX, s_TargetLocationY);

    if (s_DistToTargetLocation < 0x3C) {
        arg0->velocityY = -(rsin(s_AllowedAngle) << 3);
        arg0->velocityX = rcos(s_AllowedAngle) << 3;
        arg0->ext.faerie.maxAngle = 0x40;
    } else if (s_DistToTargetLocation < 0x64) {
        arg0->velocityY = -(rsin(s_AllowedAngle) << 4);
        arg0->velocityX = rcos(s_AllowedAngle) << 4;
        arg0->ext.faerie.maxAngle = 0x60;
    } else {
        arg0->velocityY = -(rsin(s_AllowedAngle) << 5);
        arg0->velocityX = rcos(s_AllowedAngle) << 5;
        arg0->ext.faerie.maxAngle = 0x80;
    }
    arg0->posX.val += arg0->velocityX;
    arg0->posY.val += arg0->velocityY;
    switch (arg0->step) {
    case 0:
        ExecuteAbilityInitialize(arg0);
        arg0->ext.faerie.timer = -1;
        break;
    case 1:
        SelectAnimationFrame(arg0);
        if (IsMovementAllowed(1) || CheckAllEntitiesValid() ||
            s_RoomSpecialState == 1 || g_CutsceneHasControl ||
            g_unkGraphicsStruct.D_800973FC) {
            SetAnimationFrame(arg0, 0xE);
            arg0->entityId = FAERIE_MODE_DEFAULT_UPDATE;
            arg0->step = 0;
            return;
        }
        s_DistToTargetLocation =
            CalculateDistance(arg0, s_TargetLocationX, s_TargetLocationY);
        if (s_DistToTargetLocation < 0x20) {
            arg0->facingLeft = PLAYER.facingLeft;
            arg0->step++;
        }
        break;
    case 2:
        rnd = rand() % 0x100;
        if (s_FaerieStats.unk8 == 1) {
            for (i = 0; true; i++) {
                if (rnd <= (s32)g_FaerieIntroRandomizer[i * 2]) {
                    arg0->ext.faerie.currentSfxEvent = (ServantSfxEventDesc*)
                        g_FaerieIntroRandomizer[i * 2 + 1];
                    break;
                }
            }
        } else {
            for (i = 0; true; i++) {
                if (rnd <= (s32)g_SfxEventRandomizer[i * 2]) {
                    arg0->ext.faerie.currentSfxEvent =
                        (ServantSfxEventDesc*)g_SfxEventRandomizer[i * 2 + 1];
                    break;
                }
            }
        }
        arg0->ext.faerie.sfxEventFlag =
            ((s16*)arg0->ext.faerie.currentSfxEvent)[0];
        g_PauseAllowed = false;
        arg0->step++;

        break;
    case 3:
        if (PLAYER.posX.i.hi >= arg0->posX.i.hi) {
            arg0->facingLeft = 1;
        } else {
            arg0->facingLeft = 0;
        }
        if (arg0->ext.faerie.sfxEventFlag < 0) {
            if (g_PlaySfxStep > 4) {
                SetAnimationFrame(
                    arg0, arg0->ext.faerie.currentSfxEvent->animIndex);
                arg0->step++;
            }
        } else {
            if ((g_PlaySfxStep == 4) || (g_PlaySfxStep >= 0x63)) {
                arg0->ext.faerie.sfxEventFlag--;
            }
            if (arg0->ext.faerie.sfxEventFlag < 0) {
                SetAnimationFrame(
                    arg0, arg0->ext.faerie.currentSfxEvent->animIndex);
                if (arg0->ext.faerie.currentSfxEvent->sfxId &&
                    (SearchForEntityInRange(0, FAERIE_EVENT_SFX_PASSTHROUGH) ==
                     NULL)) {
                    CreateEventEntity_Local(
                        arg0, FAERIE_EVENT_SFX_PASSTHROUGH,
                        arg0->ext.faerie.currentSfxEvent->sfxId);
                }
                arg0->ext.faerie.currentSfxEvent++;
                arg0->ext.faerie.sfxEventFlag =
                    arg0->ext.faerie.currentSfxEvent->flag;
            }
        }
        break;
    case 4:
        if (g_PlaySfxStep == 0x63) {
            arg0->step++;
        }
        break;
    case 5:
        SetAnimationFrame(arg0, 0xE);
        g_PauseAllowed = true;
        arg0->entityId = FAERIE_MODE_DEFAULT_UPDATE;
        arg0->step = 0;
        break;
    }

    ProcessEvent(arg0, false);
    CheckForValidAbility(arg0);
    ServantUpdateAnim(arg0, NULL, g_FaerieAnimationFrames);
    FntPrint("sts = %d\n", g_PlaySfxStep);
}

void UpdateSubEntityWings(Entity* self) {
    s32 animIndex;
    s32 wingsInBackZ;
    s32 i;
#ifdef VERSION_PSP
    s32 temp_zPriority;
#else
    s16 temp_zPriority;
#endif

    if (!self->step) {
        ExecuteAbilityInitialize(self);
        self->ext.faerieWings.parent = &g_Entities[SERVANT_ENTITY_INDEX];
        self->step += 1;
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

    if (wingsInBackZ) {
        temp_zPriority = s_zPriority - 1;
    } else {
        temp_zPriority = s_zPriority + 1;
    }

    self->zPriority = temp_zPriority;

    ServantUpdateAnim(self, 0, g_FaerieAnimationFrames);
}

void UpdateServantSitOnShoulder(Entity* self) {
    s32 rnd;
    s32 i;

    g_api.GetServantStats(self, 0, 0, &s_FaerieStats);
    if (D_us_80179320 != 0) {
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
        SetAnimationFrame(self, 0xE);
        break;
    case 1:
        s_AngleToTarget =
            CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
        s_AllowedAngle = GetTargetPositionWithDistanceBuffer(
            s_AngleToTarget, self->ext.faerie.targetAngle, 0x180);
        self->ext.faerie.targetAngle = s_AllowedAngle;
        self->velocityY = -(rsin(s_AllowedAngle) << 3);
        self->velocityX = (rcos(s_AllowedAngle) << 3);
        SelectAnimationFrame(self);
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        s_DistToTargetLocation =
            CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);
        if (s_DistToTargetLocation < 2) {
            if (PLAYER.step_s == 0) {
                self->facingLeft = PLAYER.facingLeft;
            } else {
                self->facingLeft = PLAYER.facingLeft ? 0 : 1;
            }
            SetAnimationFrame(self, 0x18);
            self->ext.faerie.frameCounter = 0;

            self->flags |= FLAG_POS_PLAYER_LOCKED;
            self->flags &= ~FLAG_POS_CAMERA_LOCKED;

#ifdef VERSION_PSP
            if (D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_20 ||
                D_8003C708.flags & LAYOUT_RECT_PARAMS_UNKNOWN_40 ||
                (s_RoomSpecialState == 1) || s_FaerieStats.level < 5) {
                self->step = 5;
            } else if (s_ServantId != FAM_ACTIVE_YOUSEI || PLAYER.step_s != 4) {
                self->step = 5;
            } else if (s_FaerieStats.level > 9 || g_Timer & 1 ||
                       s_FaerieStats.level > 4 || (g_Timer & 7)) {
                self->step = 5;
            } else {
                self->ext.faerie.unkB4 = 0;
                if (s_FaerieStats.level < 16) {
                    self->ext.faerie.frameCounter = 0x708;
                } else {
                    self->ext.faerie.frameCounter =
                        0x7a8 - (s_FaerieStats.level << 0x4);
                }
                self->step++;
            }
#else
            if ((*((FgLayer32*)&D_8003C708)).flags &
                    (LAYOUT_RECT_PARAMS_UNKNOWN_20 |
                     LAYOUT_RECT_PARAMS_UNKNOWN_40) ||
                (s_RoomSpecialState == 1) || s_FaerieStats.level < 5) {
                self->step = 5;
            } else if (s_ServantId != FAM_ACTIVE_YOUSEI ||
                       s_FaerieStats.level < 0x32 || PLAYER.step_s != 4) {
                self->step = 5;
            } else if (s_FaerieStats.level < 0x5A && rand() % 8) {
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
                SetAnimationFrame(self, 0x19);
                self->ext.faerie.unkB4 = 1;
                self->step++;
            }
        }
        break;
    case 3:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 0x420) {
            SetAnimationFrame(self, 0x1A);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    case 4:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 0x15E0) {
            SetAnimationFrame(self, 0x19);
            self->ext.faerie.frameCounter = 0;
            self->step++;
        }
        break;
    case 5:
        self->ext.faerie.frameCounter++;
        if (self->ext.faerie.frameCounter > 0x500) {
            SetAnimationFrame(self, 0x18);
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
            SetAnimationFrame(self, 0x19);
            self->step++;
        }
        break;
    case 8:
        self->ext.faerie.frameCounter--;
        if (self->ext.faerie.frameCounter < 0) {
            SetAnimationFrame(self, 0x18);
            self->step = 6;
        }
        break;
    case 9: // Happens when the faerie falls off your shoulder
        if (self->ext.faerie.unkB4) {
            g_api.func_800F27F4(1);
        }
        self->flags &= ~FLAG_POS_PLAYER_LOCKED;
        self->flags |= FLAG_POS_CAMERA_LOCKED;
        SetAnimationFrame(self, 0x1B);
        self->velocityX = self->facingLeft ? FIX(-0.25) : FIX(0.25);
        self->velocityY = FIX(1);
        for (rnd = rand() % 0x100, i = 0; true; i++) {
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
    if ((self->step == 3 || self->step == 4) && *((s32*)0x9234CB8) < 0x200) {
        *((s32*)0x9234CB8) = 0x200;
    }
#endif
    unused_39C8(self);
    s_AnimationStatus = ServantUpdateAnim(self, NULL, g_FaerieAnimationFrames);
}

// self->param is index for g_FaerieHints for the type of hint
void UpdateServantOfferHint(Entity* self) {
    char pad[2];

    self->ext.faerie.tileMapX = (g_Tilemap.left << 8) + g_Tilemap.scrollX.i.hi;
    self->ext.faerie.tileMapY = (g_Tilemap.top << 8) + g_Tilemap.scrollY.i.hi;

    if (D_us_80179320) {
        self->zPriority = PLAYER.zPriority - 2;
        s_zPriority = self->zPriority;
    }

    if ((g_FaerieHints[self->params].left == -1) || (self->step == 0)) {
        s_TargetLocOffset_calc = -24;
        if (!PLAYER.facingLeft) {
            s_TargetLocOffset_calc = -s_TargetLocOffset_calc;
        }
        s_TargetLocationX_calc = PLAYER.posX.i.hi + s_TargetLocOffset_calc;
        s_TargetLocationY_calc = PLAYER.posY.i.hi - 32;
    } else {
        s_TargetLocationX_calc = s_HintTargetX - self->ext.faerie.tileMapX;
        s_TargetLocationY_calc = s_HintTargetY - self->ext.faerie.tileMapY;
    }

    s_AngleToTarget = self->ext.faerie.randomMovementAngle;
    self->ext.faerie.randomMovementAngle =
        (self->ext.faerie.randomMovementAngle + 0x10) & 0xFFF;
    s_DistToTargetLocation = self->ext.faerie.defaultDistToTargetLoc;

    s_TargetLocationX =
        ((rcos(s_AngleToTarget / 2) * s_DistToTargetLocation) >> 12) +
        s_TargetLocationX_calc;

    s_TargetLocationY =
        s_TargetLocationY_calc -
        ((rsin(s_AngleToTarget) * (s_DistToTargetLocation / 2)) >> 12);
    s_AngleToTarget =
        CalculateAngleToEntity(self, s_TargetLocationX, s_TargetLocationY);
    s_AllowedAngle = GetTargetPositionWithDistanceBuffer(
        s_AngleToTarget, self->ext.faerie.targetAngle,
        self->ext.faerie.maxAngle);
    self->ext.faerie.targetAngle = s_AllowedAngle;
    s_DistToTargetLocation =
        CalculateDistance(self, s_TargetLocationX, s_TargetLocationY);

    if (s_DistToTargetLocation < 60) {
        self->velocityY = -(rsin(s_AllowedAngle) * 8);
        self->velocityX = rcos(s_AllowedAngle) * 8;
        self->ext.faerie.maxAngle = 64;
    } else if (s_DistToTargetLocation < 100) {
        self->velocityY = -(rsin(s_AllowedAngle) * 16);
        self->velocityX = rcos(s_AllowedAngle) * 16;
        self->ext.faerie.maxAngle = 96;
    } else {
        self->velocityY = -(rsin(s_AllowedAngle) * 32);
        self->velocityX = rcos(s_AllowedAngle) * 32;
        self->ext.faerie.maxAngle = 128;
    }

    self->posX.val += self->velocityX;
    self->posY.val += self->velocityY;

    switch (self->step) {
    case 0:
        ExecuteAbilityInitialize(self);
        s_HintTargetX =
            g_FaerieHints[self->params].left + self->ext.faerie.tileMapX;
        s_HintTargetY =
            g_FaerieHints[self->params].top + self->ext.faerie.tileMapY;
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
        self->ext.faerie.currentSfxEvent = g_FaerieHints[self->params].hint;
        // This is self->ext.faerie.currentSfxEvent->flag, but the weird cast is
        // needed for match
        self->ext.faerie.sfxEventFlag =
            *((s16*)self->ext.faerie.currentSfxEvent);
        g_PauseAllowed = 0;
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
            if ((g_PlaySfxStep == 4) || (g_PlaySfxStep >= 99)) {
                self->ext.faerie.sfxEventFlag--;
            }

            if (self->ext.faerie.sfxEventFlag < 0) {
                SetAnimationFrame(
                    self, self->ext.faerie.currentSfxEvent->animIndex);
                if ((self->ext.faerie.currentSfxEvent->sfxId != 0) &&
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
        SetAnimationFrame(self, 14);
        g_PauseAllowed = 1;
        self->entityId = FAERIE_MODE_DEFAULT_UPDATE;
        self->step = 0;
        break;
    }

    unused_39C8(self);
    ServantUpdateAnim(self, NULL, &g_FaerieAnimationFrames);
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
        entity = SearchForEntityInRange(0, 222);
        if (entity && entity->step < 5) {
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
        D_us_80179320 = 1;
        break;
    }
    DestroyEntity(self);
}

void UpdateSubEntityUseLifeApple(Entity* arg0) {
    Primitive* currentPrim;
    s32 i;
    s32 temp_x;

    switch (arg0->step) {
    case 0:
        arg0->primIndex = g_api.AllocPrimBuffers(PRIM_G4, 10);
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
        arg0->ext.faerieLifeApple.primX = 0x10;
        arg0->ext.faerieLifeApple.primY = 0;
        arg0->ext.faerieLifeApple.opacity = 0x40;
        arg0->ext.faerieLifeApple.effectOpacity = 0;
        arg0->step++;
        break;
    case 1:
        arg0->ext.faerieLifeApple.effectOpacity += 4;
        arg0->ext.faerieLifeApple.primY += 0x10;

        if (arg0->ext.faerieLifeApple.primY >= 0x100) {
            arg0->step++;
        }
        break;
    case 2:
        arg0->ext.faerieLifeApple.lifeAppleTimer++;
        if (arg0->ext.faerieLifeApple.lifeAppleTimer > 0xF) {
            arg0->step++;
        }
        break;
    case 3:
        arg0->ext.faerieLifeApple.opacity += 4;
        if (arg0->ext.faerieLifeApple.opacity >= 0x100) {
            arg0->ext.faerieLifeApple.opacity = 0xFF;
        }

        arg0->ext.faerieLifeApple.primX += 4;
        if (arg0->ext.faerieLifeApple.primX >= 0x100) {
            arg0->ext.faerieLifeApple.lifeAppleTimer = 0;
            arg0->step++;
        }
        break;
    case 4:
        arg0->ext.faerieLifeApple.lifeAppleTimer++;
        if (arg0->ext.faerieLifeApple.lifeAppleTimer > 60) {
            arg0->step++;
        }
        break;
    case 5:
        arg0->ext.faerieLifeApple.effectOpacity--;
        if (arg0->ext.faerieLifeApple.effectOpacity < 0) {
            arg0->ext.faerieLifeApple.effectOpacity = 0;
        }

        arg0->ext.faerieLifeApple.opacity -= 4;
        if (arg0->ext.faerieLifeApple.opacity <= 0x40) {
            arg0->ext.faerieLifeApple.opacity = 0x40;
        }

        arg0->ext.faerieLifeApple.primX -= 8;
        if (arg0->ext.faerieLifeApple.primX <= 0) {
            DestroyEntity(arg0);
            return;
        }
        break;
    }
    currentPrim = &g_PrimBuf[arg0->primIndex];

    temp_x = arg0->posX.i.hi - arg0->ext.faerieLifeApple.primX;
    if (temp_x < 0) {
        temp_x = 0;
    }
    currentPrim->x0 = currentPrim->x2 = temp_x;
    currentPrim->x1 = currentPrim->x3 = arg0->posX.i.hi;
    currentPrim->y0 = currentPrim->y1 = 0;
    currentPrim->y2 = currentPrim->y3 = arg0->ext.faerieLifeApple.primY;
    currentPrim->r0 = currentPrim->r2 = currentPrim->g0 = currentPrim->g2 =
        currentPrim->b0 = currentPrim->b2 = arg0->ext.faerieLifeApple.opacity;

    currentPrim = currentPrim->next;

    temp_x = arg0->posX.i.hi + arg0->ext.faerieLifeApple.primX;
    if (temp_x > 0x100) {
        temp_x = 0x100;
    }
    currentPrim->x0 = currentPrim->x2 = temp_x;
    currentPrim->x1 = currentPrim->x3 = arg0->posX.i.hi;
    currentPrim->y0 = currentPrim->y1 = 0;
    currentPrim->y2 = currentPrim->y3 = arg0->ext.faerieLifeApple.primY;
    currentPrim->r0 = currentPrim->r2 = currentPrim->g0 = currentPrim->g2 =
        currentPrim->b0 = currentPrim->b2 = arg0->ext.faerieLifeApple.opacity;

    for (i = 0; i < 8; i++) {
        currentPrim = currentPrim->next;

        currentPrim->r0 = currentPrim->r1 = currentPrim->g0 = currentPrim->g1 =
            currentPrim->b0 = currentPrim->b1 =
                arg0->ext.faerieLifeApple.effectOpacity;
        currentPrim->r2 = currentPrim->r3 = currentPrim->g2 = currentPrim->g3 =
            currentPrim->b2 = currentPrim->b3 = 0;
    }
}

void UpdateServantSfxPassthrough(Entity* self) { ProcessSfxState(self); }

// self->params is the item being used
void UpdateSubEntityUseItem(Entity* self) {
    FakePrim* fakePrim;
    s32 i;
    u16 posY2;
    s16 posX3;
    s32 posX;
    s16 posY;
    s16 posX2;
    u16 posX4;
    ItemPrimitiveParams* primitiveParams;

    posX2 = self->posX.i.hi;
    posY = self->posY.i.hi;

    primitiveParams = &g_ItemPrimitiveParams[(s16)self->params];
    switch (self->step) {
    case 0:
        self->primIndex =
            g_api.AllocatePrimitives(PRIM_TILE_ALT, primitiveParams->count + 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        posX = posX2;
        self->flags = primitiveParams->flags;
        fakePrim = (FakePrim*)&g_PrimBuf[self->primIndex];

        while (true) {
            fakePrim->drawMode = primitiveParams->drawMode + DRAW_HIDE;
            fakePrim->priority = primitiveParams->priority + PLAYER.zPriority;
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
            switch (primitiveParams->unk6) {
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
            fakePrim->r0 = primitiveParams->r;
            fakePrim->g0 = primitiveParams->g;
            fakePrim->b0 = primitiveParams->b;
            fakePrim->w = primitiveParams->w;
            fakePrim->h = primitiveParams->h;
            fakePrim = fakePrim->next;
        }
        self->step++;
        // fallthrough
    case 1: // The hammer runs this code more than once, the other items only
            // once
        if (--self->ext.faerieItem.unkFlag <= 0) {
            fakePrim = (FakePrim*)&g_PrimBuf[self->primIndex];
            for (i = 0; i < self->ext.faerieItem.unkAccumulator; i++) {
                fakePrim = fakePrim->next;
            }
            for (i = 0; i < primitiveParams->unk2; i++) {
                fakePrim->drawMode &= ~DRAW_HIDE;
                fakePrim = fakePrim->next;
            }
            self->ext.faerieItem.unkAccumulator += primitiveParams->unk2;
            if (self->ext.faerieItem.unkAccumulator >= primitiveParams->count) {
                self->step++;
            }
            self->ext.faerieItem.unkFlag = primitiveParams->unk4;
        }
        // fallthrough
    case 2:
        self->ext.faerieItem.drawMode = DRAW_DEFAULT;
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
            switch (primitiveParams->unk6) {
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
            self->ext.faerieItem.drawMode |= !(fakePrim->drawMode & DRAW_HIDE);
            fakePrim = fakePrim->next;
        }
        if (self->ext.faerieItem.drawMode == DRAW_DEFAULT) {
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

#include "../play_sfx.h"
#endif

#include "../process_event.h"

#include "../create_event_entity.h"

#include "../is_movement_allowed.h"

#ifndef VERSION_PSP
#include "../check_all_entities_valid.h"
#endif

#include "../servant_unk0.h"
