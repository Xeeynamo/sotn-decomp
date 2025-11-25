// SPDX-License-Identifier: AGPL-3.0-or-later
//
// Section Sizes:
//
//         | Data  | RO Data | Text   | BSS  |
// --------+-------+---------+--------+------+
//  PSX US | 0x2F0 | 0x88    | 0x1AC0 | 0x40 |
//  PSX HD | 0x200 | 0x88    | 0x1570 | 0x40 |
//
#include <stage.h>

#if defined(VERSION_PSP)
#include "blit_char_psp.h"
#endif

#if STAGE == STAGE_ST0
static u8 D_80180C94[] = {
    0x02, 0x1A, 0x02, 0x1B, 0x02, 0x1C, 0x02, 0x1D, 0x02, 0x1E,
    0x02, 0x1F, 0x02, 0x20, 0x02, 0x21, 0x02, 0x20, 0x02, 0x1F,
    0x02, 0x1E, 0x02, 0x1D, 0x02, 0x1C, 0x02, 0x1B, 0x02, 0x1A};

static u8 D_80180C98[] = {
    0x02, 0x22, 0x02, 0x23, 0x02, 0x24, 0x02, 0x25, 0x02, 0x26,
    0x02, 0x27, 0x02, 0x28, 0x02, 0x29, 0x02, 0x28, 0x02, 0x27,
    0x02, 0x26, 0x02, 0x25, 0x02, 0x24, 0x02, 0x23, 0x00};
#else
static u8 D_80180C94[] = {0x01, 0x0E, 0x00, 0x00};
static u8 D_80180C98[] = {
    0x02, 0x03, 0x06, 0x04, 0x05, 0x05, 0x05, 0x06, 0x04, 0x07, 0x03,
    0x08, 0x04, 0x09, 0x05, 0x0A, 0x05, 0x0B, 0x06, 0x0C, 0x07, 0x03,
    0x06, 0x04, 0x05, 0x05, 0x05, 0x06, 0x04, 0x07, 0x03, 0x08, 0x04,
    0x09, 0x05, 0x0A, 0x05, 0x0B, 0x06, 0x0C, 0x02, 0x0D, 0x00, 0x00};
#endif
static u8 D_80180CC4[] = {0x04, 0x14, 0x07, 0x15, 0x06, 0x16, 0x03, 0x17,
                          0x03, 0x18, 0x06, 0x19, 0x02, 0x15, 0x00, 0x00};
static u8 D_80180CD4[] = {0x01, 0x1A, 0x00, 0x00};
static u8 D_80180CD8[] = {0x01, 0x1B, 0x00, 0x00};
static u8 D_80180CDC[] = {0x01, 0x1C, 0x00, 0x00};
static u8 D_80180CE0[] = {0x01, 0x1D, 0x00, 0x00};
static u8 D_80180CE4[] = {0x01, 0x1E, 0x00, 0x00};
static u8 D_80180CE8[] = {0x01, 0x1F, 0x00, 0x00};
static u8 D_80180CEC[] = {0x01, 0x20, 0x00, 0x00};
static u8 D_80180CF0[] = {0x01, 0x21, 0x00, 0x00};
static u8 D_80180CF4[] = {0x02, 0x22, 0x02, 0x23, 0x02, 0x24, 0x02, 0x25, 0x02,
                          0x26, 0x02, 0x27, 0x02, 0x28, 0x02, 0x29, 0x00, 0x00};
static u8 D_80180D08[] = {0x1A, 0x0F, 0x06, 0x10, 0x04, 0x11, 0x02,
                          0x12, 0x04, 0x11, 0x06, 0x10, 0x00, 0x00};
static u8 D_80180D18[] = {0x01, 0x13, 0x00, 0x00};
#if STAGE != STAGE_ST0
static u8 D_80180D1C[] = {0x05, 0x2A, 0x05, 0x2B, 0x05, 0x2C, 0x05, 0x2D, 0x05,
                          0x2E, 0x05, 0x2F, 0x05, 0x30, 0x05, 0x31, 0x00, 0x00};
static u8 D_80180D30[] = {0x05, 0x32, 0x05, 0x33, 0x05, 0x34, 0x05, 0x35, 0x05,
                          0x36, 0x05, 0x37, 0x05, 0x38, 0x05, 0x39, 0x00, 0x00};
#else
static u8 D_80180D1C[] = {0x05, 0x19, 0x00, 0x00};
static u8 D_80180D30[] = {0x05, 0x18, 0x00, 0x00};
#endif
static u8 D_80180D44[] = {0x05, 0x3A, 0x05, 0x3B, 0x05, 0x3C, 0x05, 0x3D, 0x05,
                          0x3E, 0x05, 0x3F, 0x05, 0x40, 0x05, 0x41, 0x00, 0x00};
static u8 D_80180D58[] = {0x05, 0x42, 0x05, 0x43, 0x05, 0x44, 0x05, 0x45, 0x05,
                          0x46, 0x05, 0x47, 0x05, 0x48, 0x05, 0x49, 0x00, 0x00};
static u8 D_80180D6C[] = {0x05, 0x4A, 0x05, 0x4B, 0x05, 0x4C, 0x05, 0x4D, 0x05,
                          0x4E, 0x05, 0x4F, 0x05, 0x50, 0x05, 0x51, 0x00, 0x00};
static u8 D_80180D80[] = {0x05, 0x52, 0x05, 0x53, 0x05, 0x54, 0x05, 0x55, 0x05,
                          0x56, 0x05, 0x57, 0x05, 0x58, 0x05, 0x59, 0x00, 0x00};
static u8 D_80180D94[] = {0x05, 0x5A, 0x05, 0x5B, 0x05, 0x5C, 0x05, 0x5D, 0x05,
                          0x5E, 0x05, 0x5F, 0x05, 0x60, 0x05, 0x61, 0x00, 0x00};
static u8 D_80180DA8[] = {0x05, 0x62, 0x05, 0x63, 0x05, 0x64, 0x05, 0x65, 0x05,
                          0x66, 0x05, 0x67, 0x05, 0x68, 0x05, 0x69, 0x00, 0x00};
static u8 D_80180DBC[] = {0x05, 0x6A, 0x05, 0x6B, 0x05, 0x6C, 0x05, 0x6D, 0x05,
                          0x6E, 0x05, 0x6F, 0x05, 0x70, 0x05, 0x71, 0x00, 0x00};
#if STAGE != STAGE_ST0
static u8 D_80180DD0[] = {0x01, 0x8F, 0x00, 0x00};
#endif
static s8 unusedStuff[] = {-4, -4, 4, -4, -4, 4, 4, 4, 0x80, 0x00};
static u16 aluric_subweapons_idx[] = {1, 2, 4, 3, 6, 5, 7, 8, 9};
static u16 aluric_subweapons_id[] = {0, 14, 15, 17, 16, 19, 18, 20, 21, 22};

// Gold appears up here on PSX, down lower on VERSION_PSP
#if !defined(VERSION_PSP) && (STAGE != STAGE_ST0)
const char* g_goldCollectTexts[] = {
    _S("$1"),   _S("$25"),  _S("$50"),   _S("$100"),  _S("$250"),
    _S("$400"), _S("$700"), _S("$1000"), _S("$2000"), _S("$5000"),
};
static u32 c_GoldPrizes[] = {1, 25, 50, 100, 250, 400, 700, 1000, 2000, 5000};
#endif

#if STAGE == STAGE_ST0
static u32 c_GoldPrizes[] = {1, 5, 10, 20, 40, 70, 100, 200, 400, 1000};
#endif

// 1D18

u8* g_SubweaponAnimPrizeDrop[] = {
    D_80180C94, D_80180C98, D_80180CC4, D_80180CD4, D_80180CD8,
    D_80180CDC, D_80180CE0, D_80180CE4, D_80180CE8, D_80180CEC,
    D_80180CF0, D_80180CF4, D_80180D08, D_80180D18,
#if STAGE != STAGE_ST0
    D_80180D58, D_80180D44, D_80180D1C, D_80180D30, D_80180D6C,
    D_80180D80, D_80180D94, D_80180DA8, D_80180DBC, D_80180DD0,
#else
    D_80180D1C, D_80180D1C, D_80180D1C, D_80180D30, D_80180D1C,
    D_80180D1C, D_80180D1C, D_80180D1C, D_80180D1C,
#endif
};

#if defined(VERSION_PSP) && (STAGE != STAGE_ST0)
static u16 maria_subweapons_idx[] = {1, 2, 4, 3, 0, 0, 0, 0, 0};
static u16 maria_subweapons_id[] = {19, 14, 15, 17, 16};
static u8 D_psp_09246398[] = {
    0x05, 0xA1, 0x05, 0xA2, 0x05, 0xA3, 0x05, 0xA4, 0x05,
    0xA5, 0x05, 0xA6, 0x05, 0xA7, 0x05, 0xA8, 0x00};
static u8 D_psp_092463B0[] = {
    0x05, 0xA9, 0x05, 0xAA, 0x05, 0xAB, 0x05, 0xAC, 0x05,
    0xAD, 0x05, 0xAE, 0x05, 0xAF, 0x05, 0xB0, 0x00};
static u8 D_psp_092463C8[] = {
    0x05, 0xB1, 0x05, 0xB2, 0x05, 0xB3, 0x05, 0xB4, 0x05,
    0xB5, 0x05, 0xB6, 0x05, 0xB7, 0x05, 0xB8, 0x00};
static u8 D_psp_092463E0[] = {
    0x05, 0xB9, 0x05, 0xBA, 0x05, 0xBB, 0x05, 0xBC, 0x05,
    0xBD, 0x05, 0xBE, 0x05, 0xBF, 0x05, 0xC0, 0x00};
static u8* g_MariaSubweaponAnimPrizeDrop[] = {
    D_80180C94,     D_80180C98,     D_80180CC4,     D_80180CD4, D_80180CD8,
    D_80180CDC,     D_80180CE0,     D_80180CE4,     D_80180CE8, D_80180CEC,
    D_80180CF0,     D_80180CF4,     D_80180D08,     D_80180D18, D_psp_09246398,
    D_psp_092463B0, D_psp_092463E0, D_psp_092463C8, D_80180C94, D_80180D80,
    D_80180C94,     D_80180C94,     D_80180C94,     D_80180DD0,
};

#if STAGE != STAGE_ST0
const char* g_goldCollectTexts[] = {GOLD_COLLECT_TEXT};
static u32 c_GoldPrizes[] = {1, 25, 50, 100, 250, 400, 700, 1000, 2000, 5000};
#else
static u32 c_GoldPrizes[] = {1, 5, 10, 20, 40, 70, 100, 200, 400, 1000};
#endif

#endif

static s16 D_80180EB8[] = {-6, 4, 0, -8};
#if !defined(VERSION_BETA) && STAGE != STAGE_ST0
// Note that this array is in data. MAD/ST0 have it in rodata.
s8 c_HeartPrizes[] = {1, 5};
#endif

// from another file
extern u16 g_EInitObtainable[];

static void PrizeDropFall(void) {
    if (g_CurrentEntity->velocityY >= 0) {
        g_CurrentEntity->ext.equipItemDrop.fallSpeed +=
            g_CurrentEntity->ext.equipItemDrop.gravity;
        g_CurrentEntity->velocityX =
            g_CurrentEntity->ext.equipItemDrop.fallSpeed;
        if (g_CurrentEntity->velocityX == FIX(1) ||
            g_CurrentEntity->velocityX == FIX(-1)) {
            g_CurrentEntity->ext.equipItemDrop.gravity =
                -g_CurrentEntity->ext.equipItemDrop.gravity;
        }
    }

    if (g_CurrentEntity->velocityY < FIX(0.25)) {
        g_CurrentEntity->velocityY += FIX(0.125);
    }
}

static void PrizeDropFall2(u16 arg0) {
    Collider collider;

    if (g_CurrentEntity->velocityX < 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi - 7, &collider, 0);
        if (collider.effects & EFFECT_NOTHROUGH) {
            g_CurrentEntity->velocityY = 0;
        }
    }

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                         g_CurrentEntity->posY.i.hi + 7, &collider, 0);

    if (arg0) {
        if (!(collider.effects & EFFECT_NOTHROUGH)) {
            MoveEntity();
            FallEntity();
            return;
        }

        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;

        if (collider.effects & EFFECT_QUICKSAND) {
            g_CurrentEntity->posY.val += FIX(0.125);
            return;
        }

        g_CurrentEntity->posY.i.hi += collider.unk18;
        return;
    }

    if (!(collider.effects & EFFECT_NOTHROUGH)) {
        MoveEntity();
        PrizeDropFall();
    }
}

// This function is messy, maybe there's a better way.
void CollectHeart(u16 arg0) {
#if defined VERSION_BETA || STAGE == STAGE_ST0
    s8 heartPrizes[2] = {0x01, 0x05};
    s8 mad_unknown[2] = {0x01, 0x02};
#else
#define heartPrizes c_HeartPrizes
#endif

    g_api.PlaySfx(SFX_HEART_PICKUP);
    g_Status.hearts += heartPrizes[arg0];

    if (g_Status.hearts > g_Status.heartsMax) {
        g_Status.hearts = g_Status.heartsMax;
    }

    DestroyEntity(g_CurrentEntity);
}

static s32 g_ExplosionYVelocities[] = {
    FIX(-1.0), FIX(-1.5), FIX(-1.5), FIX(-1.5), FIX(-3.0)};

static u8 anim_small[] = {
    0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x02, 0x05,
    0x02, 0x06, 0x02, 0x07, 0x02, 0x08, 0x00, 0x00, 0x00, 0x00,
};
u8 g_bigRedFireballAnim[] = {
    0x01, 0x09, 0x02, 0x0A, 0x02, 0x0B, 0x02, 0x0C, 0x02, 0x0D,
    0x02, 0x0E, 0x02, 0x0F, 0x02, 0x10, 0x02, 0x11, 0x02, 0x12,
    0x03, 0x13, 0x04, 0x14, 0x00, 0x00, 0x00, 0x00,
};
static u8 anim_small_multiple[] = {
    0x02, 0x15, 0x02, 0x16, 0x02, 0x17, 0x02, 0x18, 0x02, 0x19, 0x02, 0x1A,
    0x02, 0x1B, 0x02, 0x1C, 0x02, 0x1D, 0x02, 0x1E, 0x02, 0x1F, 0x02, 0x20,
    0x02, 0x21, 0x02, 0x22, 0x02, 0x23, 0x02, 0x24, 0x02, 0x25, 0x02, 0x26,
    0x02, 0x27, 0x02, 0x28, 0x02, 0x29, 0x02, 0x2A, 0x00, 0x00, 0x00, 0x00,
};
u8 g_explosionBigAnim[] = {
    0x02, 0x2B, 0x02, 0x2C, 0x02, 0x2D, 0x02, 0x2E, 0x02, 0x2F, 0x02,
    0x30, 0x02, 0x31, 0x02, 0x32, 0x02, 0x33, 0x02, 0x34, 0x02, 0x35,
    0x02, 0x36, 0x02, 0x37, 0x02, 0x38, 0x02, 0x39, 0x02, 0x3A, 0x02,
    0x3B, 0x02, 0x3C, 0x02, 0x3D, 0x02, 0x3E, 0x02, 0x3F, 0x02, 0x40,
    0x02, 0x41, 0x02, 0x42, 0x00, 0x00, 0x00, 0x00,
};
// This doesn't seem to be used in any of the currently decompiled code.
static u8 D_80180F6C[] = {0x01, 0x43, 0x00, 0x00};

static u8* g_ExplosionAnimations[] = {
    anim_small,         g_bigRedFireballAnim, anim_small_multiple,
    g_explosionBigAnim, D_80180F6C,
};

void CollectGold(u16 goldSize) {
    g_api.PlaySfx(SFX_GOLD_PICKUP);
    goldSize -= 2;
    g_Status.gold += c_GoldPrizes[goldSize];
    if (g_Status.gold > MAX_GOLD) {
        g_Status.gold = MAX_GOLD;
    }
#if STAGE != STAGE_ST0
    if (g_unkGraphicsStruct.BottomCornerTextTimer) {
        g_api.FreePrimitives(g_unkGraphicsStruct.BottomCornerTextPrims);
        g_unkGraphicsStruct.BottomCornerTextTimer = 0;
    }

    BottomCornerText(g_goldCollectTexts[goldSize], 1);
    DestroyEntity(g_CurrentEntity);
#endif
}

#if defined VERSION_BETA || STAGE == STAGE_ST0
void func_801937BC(void) {}
void UnusedDestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }
#endif

#if defined(VERSION_PSP) && (STAGE != STAGE_ST0)
#include "collect_subweapon_psp.h"
#else
#include "collect_subweapon.h"
#endif

#if STAGE != STAGE_ST0
void CollectHeartVessel(void) {
#ifdef VERSION_BETA
    if (0) { // MAD doesn't need to test character, is always alucard
#else
    if (g_PlayableCharacter != PLAYER_ALUCARD) {
#endif
        g_api.PlaySfx(SFX_HEART_PICKUP);
        g_Status.hearts += HEART_VESSEL_RICHTER;

        if (g_Status.hearts > g_Status.heartsMax) {
            g_Status.hearts = g_Status.heartsMax;
        }
    } else {
        // Alucard's version
        g_api.PlaySfx(SFX_HEART_PICKUP);
        g_api.func_800FE044(HEART_VESSEL_INCREASE, 0x4000);
    }
    DestroyEntity(g_CurrentEntity);
}

static void CollectLifeVessel(void) {
    g_api.PlaySfx(SFX_HEART_PICKUP);
    g_api.func_800FE044(LIFE_VESSEL_INCREASE, 0x8000);
    DestroyEntity(g_CurrentEntity);
}
#endif

// MAD doesn't take an argument, others do
#if defined VERSION_BETA || (STAGE == STAGE_ST0 && !defined(VERSION_PSP))
static void CollectDummy(void) { DestroyEntity(g_CurrentEntity); }
// Extra unused function, putting it in this same if-block.
Entity* func_801939C4(void) {
    g_CurrentEntity->step = 3;
    g_CurrentEntity->params = 4;
    return g_CurrentEntity;
}
#else
static void CollectDummy(u16 id) { DestroyEntity(g_CurrentEntity); }
#endif

// if self->params & 0x8000 then the item will not disappear
// ST0 seems to contain the earliest known version of this entity.
// MAD has some very minor enhancements that brings it closer to the US build,
// such as Life/Heart upgrade drops.
// US essentially adds castle flags for unique drops
// PSP iterates on top of the US version by adding drops for Maria
// PSP ST0 iterates on top of ST0 with the only change on CollectDummy params
void EntityPrizeDrop(Entity* self) {
    Primitive* prim;
    u16 itemId;
    s16 index;
    s32 primIndex;
    Collider collider;

    // if self->params & 0x8000 then the item will not disappear
    itemId = self->params & 0x7FFF;
    if (self->step) {
#if defined(VERSION_PSP) && STAGE != STAGE_ST0
        if (g_PlayableCharacter == PLAYER_MARIA) {
            AnimateEntity(g_MariaSubweaponAnimPrizeDrop[itemId], self);
        } else {
            AnimateEntity(g_SubweaponAnimPrizeDrop[itemId], self);
        }
#else
        AnimateEntity(g_SubweaponAnimPrizeDrop[itemId], self);
#endif
    }
#if defined(VERSION_US) && STAGE != STAGE_ST0
    if (self->step > 1 && self->step < 5 && self->hitFlags) {
#else
    if (self->step && self->step < 5 && self->hitFlags) {
#endif
        self->step = 5;
    }
#if STAGE == STAGE_ST0
    self->palette = 0x100;
#else
    self->palette = 0;
#endif
    if (self->unk6D[0] >= 0x18 && !(g_GameTimer & 2) && self->params != 1) {
        self->palette = 0x815F;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitObtainable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        self->drawMode = DRAW_DEFAULT;
#if STAGE == STAGE_ST0
        if (itemId > 22) {
#else
        if (itemId > 23) {
#endif
            itemId = self->params = 0;
        }

#if defined(VERSION_PSP) && STAGE != STAGE_ST0
        if (g_PlayableCharacter == PLAYER_MARIA && itemId >= 0xE &&
            itemId < 23) {
            switch (itemId) {
            case 14:
                itemId = self->params = 15;
                break;
            case 15:
                itemId = self->params = 14;
                break;
            case 21:
                itemId = self->params = 16;
                break;
            case 17:
                itemId = self->params = 17;
                break;
            case 19:
                itemId = 19;
                self->params = 19;
                break;
            default:
                itemId = self->params = 0;
                break;
            }
        }
#endif

#if defined(VERSION_PSP) && STAGE != STAGE_ST0
        if (itemId >= 14 && itemId < 23 &&
            g_PlayableCharacter != PLAYER_MARIA) {
            s32 subWeaponId = aluric_subweapons_id[g_Status.subWeapon];
            if (itemId == subWeaponId) {
                itemId = 1;
                self->params = 1;
            }
        }
#else
        if (itemId >= 14 && itemId < 23 &&
            itemId == aluric_subweapons_id[g_Status.subWeapon]) {
            itemId = 1;
            self->params = 1;
        }
#endif
        if (!itemId || itemId == 2) {
            self->hitboxWidth = 4;
        }
        break;
    case 1:
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);
        if (collider.effects & EFFECT_NOTHROUGH_PLUS) {
            DestroyEntity(self);
        } else {
            self->step++;
#if !defined(VERSION_BETA) && STAGE != STAGE_ST0
            index = self->ext.equipItemDrop.castleFlag;
            if (index) {
                index--;
                g_CastleFlags[(index >> 3) + ENEMY_LIST_RAREDROP_1B0] |=
                    1 << (index & 7);
            }
#endif
        }
        if (!itemId) {
            self->ext.equipItemDrop.fallSpeed = FIX(-1);
            self->ext.equipItemDrop.gravity = 0x800;
        }
        break;
    case 2:
#if STAGE == STAGE_ST0
        if (self->velocityX < 0) {
#else
        if (self->velocityY < 0) {
#endif
            g_api.CheckCollision(
                self->posX.i.hi, self->posY.i.hi - 7, &collider, 0);
            if (collider.effects & EFFECT_NOTHROUGH) {
                self->velocityY = 0;
            }
        }
        MoveEntity();
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 7, &collider, 0);
        if (itemId) {
            if (collider.effects & EFFECT_NOTHROUGH && self->velocityY > 0) {
                self->velocityX = 0;
                self->velocityY = 0;
                self->posY.i.hi += collider.unk18;
                self->ext.equipItemDrop.aliveTimer = 0xF0;
                self->step++;
            } else {
                FallEntity();
            }
            CheckFieldCollision(D_80180EB8, 2);
        } else if (collider.effects & EFFECT_NOTHROUGH) {
            self->posY.i.hi += collider.unk18;
            self->ext.equipItemDrop.aliveTimer = 0x60;
            self->step++;
        } else {
            PrizeDropFall();
        }
        break;
    case 3:
        PrizeDropFall2(itemId);
        if (!(self->params & 0x8000) && !--self->ext.equipItemDrop.aliveTimer) {
            if (itemId) {
                self->ext.equipItemDrop.aliveTimer = 80;
            } else {
                self->ext.equipItemDrop.aliveTimer = 64;
            }
            self->step++;
        }
        break;
    case 4:
        PrizeDropFall2(itemId);
        if (--self->ext.equipItemDrop.aliveTimer) {
            if (self->ext.equipItemDrop.aliveTimer & 2) {
                self->animCurFrame = 0;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        break;
    case 5:
        if (itemId < 2) {
            CollectHeart(itemId);
        } else if (itemId < 12) {
            CollectGold(itemId);
#if STAGE != STAGE_ST0
        } else if (itemId == 12) {
            CollectHeartVessel();
#endif
        } else if (itemId < 14) {
#if defined VERSION_BETA || (STAGE == STAGE_ST0 && !defined(VERSION_PSP))
            // this is only allowed in BETA PSX and ST0 PSX, not on ST0 PSP
            // probably due to a compilation error fix
            CollectDummy();
#else
            CollectDummy(itemId);
#endif
        } else if (itemId < 23) {
            CollectSubweapon(itemId);
#if STAGE != STAGE_ST0
        } else if (itemId == 23) {
            CollectLifeVessel();
#endif
        } else {
            DestroyEntity(self);
            return;
        }
        break;
#if !defined(VERSION_BETA) && STAGE != STAGE_ST0
    case 6:
#endif
    case 7:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0;
#if defined(VERSION_PSP) && STAGE != STAGE_ST0
            if (itemId >= 14 && itemId < 23) {
                s32 subWeaponId;
                if (g_PlayableCharacter == PLAYER_MARIA) {
                    subWeaponId = maria_subweapons_id[g_Status.D_80097C40];
                    if (itemId == subWeaponId) {
                        itemId = 1;
                        self->params = 1;
                    }
                } else {
                    subWeaponId = aluric_subweapons_id[g_Status.subWeapon];
                    if (itemId == subWeaponId) {
                        itemId = 1;
                        self->params = 1;
                    }
                }
            }
#else
            if (itemId >= 14 && itemId < 23 &&
                itemId == aluric_subweapons_id[g_Status.subWeapon]) {
                itemId = 1;
                self->params = 1;
            }
#endif
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (primIndex != -1) {
                self->primIndex = primIndex;
                self->flags |= FLAG_HAS_PRIMS;
                prim = &g_PrimBuf[primIndex];
                prim->tpage = 0x1A;
                prim->clut = 0x170;
#if defined VERSION_BETA || STAGE == STAGE_ST0
                prim->u0 = prim->u2 = 0;
                prim->u1 = prim->u3 = 0x20;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 0x20;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 128;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 128;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 128;
#else
                prim->u0 = prim->u2 = prim->v0 = prim->v1 = 0;
                prim->u1 = prim->u3 = prim->v2 = prim->v3 = 0x20;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = 128;
#endif
                prim->drawMode = DRAW_HIDE;
                prim->priority = self->zPriority + 1;
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            g_api.CheckCollision(
                self->posX.i.hi, self->posY.i.hi + 7, &collider, 0);
            if (collider.effects & EFFECT_NOTHROUGH && self->velocityY > 0) {
                self->velocityX = 0;
                self->velocityY = 0;
                self->posY.i.hi += collider.unk18;
                self->step_s++;
            } else {
                FallEntity();
            }
            CheckFieldCollision(D_80180EB8, 2);
            self->animCurFrame = 0;
            if (self->ext.equipItemDrop.unk8A) {
                self->ext.equipItemDrop.unk8A--;
            } else {
                prim = &g_PrimBuf[self->primIndex];
                prim->x0 = prim->x2 = self->posX.i.hi - 1;
                prim->x1 = prim->x3 = self->posX.i.hi + 1;
                prim->y0 = prim->y1 = self->posY.i.hi - 1;
                prim->y2 = prim->y3 = self->posY.i.hi + 1;
                prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                 DRAW_UNK02 | DRAW_TRANSP;
            }
            break;
        case 2:
            PrizeDropFall2(itemId);
            prim = &g_PrimBuf[self->primIndex];
            self->ext.equipItemDrop.unk8A++;
            if (self->ext.equipItemDrop.unk8A < 17) {
                index = self->ext.equipItemDrop.unk8A;
                self->animCurFrame = 0;
            } else {
                index = 32 - self->ext.equipItemDrop.unk8A;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 -= 8;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 -= 8;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 -= 8;
            }
            prim->x0 = prim->x2 = self->posX.i.hi - index;
            prim->x1 = prim->x3 = self->posX.i.hi + index;
            prim->y0 = prim->y1 = self->posY.i.hi - index;
            prim->y2 = prim->y3 = self->posY.i.hi + index;
            if (self->ext.equipItemDrop.unk8A == 32) {
                g_api.FreePrimitives(self->primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
                self->ext.equipItemDrop.aliveTimer = 208;
                self->step = 3;
                self->step_s = 0;
            }
            break;
        }
        break;
    }
}

extern EInit g_EInitParticle;

// params: (& 0xFF) The explosion type
//         (& 0xF0) These explosion types use a different (hardcoded) palette
//                  and drawMode
//         (& 0xFF00) If non-zero, ((& 0xFF00) >> 8) will override zPriority
void EntityExplosion(Entity* entity) {
    if (!entity->step) {
        InitializeEntity(g_EInitParticle);
        entity->pose = 0;
        entity->poseTimer = 0;
        entity->animSet = ANIMSET_DRA(2);
        entity->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        if (entity->params & 0xF0) {
            entity->palette = PAL_FLAG(PAL_UNK_195);
            entity->drawMode = DRAW_TPAGE;
        }

        if (entity->params & 0xFF00) {
            entity->zPriority = (entity->params & 0xFF00) >> 8;
        }
        entity->params &= 15;
        entity->velocityY = g_ExplosionYVelocities[entity->params];
    } else {
        entity->posY.val += entity->velocityY;

        if (!AnimateEntity(g_ExplosionAnimations[entity->params], entity)) {
            DestroyEntity(entity);
        }
    }
}

// Weird difference here. These functions are not related.
// But MAD has one and not the other.
#if !(defined VERSION_BETA || STAGE == STAGE_ST0)
static void BlinkItem(Entity* self, u16 renderFlags) {
    Primitive* prim;
    s32 temp;
    prim = &g_PrimBuf[self->primIndex];

    prim->x0 = prim->x2 = self->posX.i.hi - 7;
    prim->x1 = prim->x3 = prim->x0 + 14;

    prim->y0 = prim->y1 = self->posY.i.hi - 7;
    prim->y2 = prim->y3 = prim->y0 + 14;

    if (renderFlags & RENDERFLAGS_NOSHADOW) {
        PCOL(prim) = 255;
    } else {
        PCOL(prim) = 128;
    }
}
#else
static Point16 g_collectVelocity[] = {
    {0x0160, 0xFD20}, {0xFE80, 0xFC90}, {0x00E0, 0xFC20}, {0xFF40, 0xFD30},
    {0x0020, 0xFB60}, {0xFFC0, 0xFCC0}, {0x0090, 0xFC40}, {0xFFA0, 0xFC30},
};
// Also, this function is never called.
void Unreferenced_MAD_ST0_func(Entity* self) {
    if (self->step != 0) {
        if (self->posY.i.hi >= 0xF1) {
            DestroyEntity(self);
            return;
        }
        FallEntity();
        MoveEntity();
        return;
    }

    InitializeEntity(OVL_EXPORT(EInitBreakable));
    self->animCurFrame = self->ext.unusedMadST0.animframe;
    self->velocityX = g_collectVelocity[self->ext.unusedMadST0.velIndex].x;
    self->velocityY = g_collectVelocity[self->ext.unusedMadST0.velIndex].y;

    if (self->params != 0) {
        self->zPriority -= 1;
    }
}
#endif

#ifdef VERSION_PSP
char* obtainedStr;
#endif
u16 g_ItemIconSlots[ICON_SLOT_NUM];

void EntityEquipItemDrop(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 i;
    u16 itemId;
    s16 index;
    s32 primIndex;
    const char* name;

    itemId = self->params & 0x7FFF;
    if (
#if defined(VERSION_US) && STAGE != STAGE_ST0
        self->step >= 2 &&
#else
        self->step &&
#endif
        self->step < 5 && self->hitFlags) {
        self->step = 5;
    }

    switch (self->step) {
    case 0:
#if !(defined VERSION_BETA || STAGE == STAGE_ST0)
        if (g_PlayableCharacter != PLAYER_ALUCARD) {
            self->params = 0;
            self->pfnUpdate = EntityPrizeDrop;
            self->entityId = 3;
            SetStep(0);
            EntityPrizeDrop(self);
            return;
        }
#endif
        InitializeEntity(g_EInitObtainable);
        self->ext.equipItemDrop.timer = 0;
        break;
    case 1:
        g_api.CheckCollision(self->posX.i.hi, self->posY.i.hi, &collider, 0);
        if (collider.effects & EFFECT_NOTHROUGH_PLUS) {
            DestroyEntity(self);
            break;
        }

        for (i = 0; i < LEN(g_ItemIconSlots); i++) {
            if (!g_ItemIconSlots[i]) {
                break;
            }
        }
        if (i >= LEN(g_ItemIconSlots)) {
            DestroyEntity(self);
            return;
        }
#if !(defined VERSION_BETA || STAGE == STAGE_ST0)
        index = self->ext.equipItemDrop.castleFlag;
        if (index) {
            index--;
            g_CastleFlags[(index >> 3) + ENEMY_LIST_RAREDROP_1B0] |=
                1 << (index & 7);
        }
#endif
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        g_ItemIconSlots[i] = 0x1E0;
#if !(defined VERSION_BETA || STAGE == STAGE_ST0)
        self->ext.equipItemDrop.iconSlot = i;
#endif
        if (itemId < NUM_HAND_ITEMS) {
            g_api.LoadEquipIcon(g_api.equipDefs[itemId].icon,
                                g_api.equipDefs[itemId].iconPalette, i);
        } else {
            itemId -= NUM_HAND_ITEMS;
            g_api.LoadEquipIcon(g_api.accessoryDefs[itemId].icon,
                                g_api.accessoryDefs[itemId].iconPalette, i);
        }

        prim = &g_PrimBuf[primIndex];
        prim->tpage = 0x1A;
        prim->clut = i + 464;

#ifdef VERSION_PSP
        prim->u0 = prim->u2 = (i & 7) * 0x10 + 1;
#else
        prim->u0 = prim->u2 = (u8)(i & 7) * 0x10 + 1;
#endif
        prim->u1 = prim->u3 = prim->u0 + 0xE;

#ifdef VERSION_PSP
        prim->v0 = prim->v1 = (i & 0x18) * 2 + 0x81;
#else
        prim->v0 = prim->v1 = (u8)(i & 0x18) * 2 + 0x81;
#endif
        prim->v2 = prim->v3 = prim->v0 + 0xE;

        prim->priority = 0x80;
        prim->drawMode = DRAW_UNK02 | DRAW_COLORS;

        self->ext.equipItemDrop.timer = 128;
        self->step++;
        break;
    case 2:
#if defined VERSION_BETA || STAGE == STAGE_ST0
        if (self->velocityX < 0) {
#else
        if (self->velocityY < 0) {
#endif
            g_api.CheckCollision(
                self->posX.i.hi, self->posY.i.hi - 7, &collider, 0);
            if (collider.effects & EFFECT_NOTHROUGH) {
                self->velocityY = 0;
            }
        }
        MoveEntity();
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 7, &collider, 0);
        if ((collider.effects & EFFECT_NOTHROUGH) && self->velocityY > 0) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->posY.i.hi += collider.unk18;
            self->ext.equipItemDrop.aliveTimer = 240;
            self->step++;
        } else {
            FallEntity();
        }
        CheckFieldCollision(D_80180EB8, 2);
        break;
    case 3:
        PrizeDropFall2(1);
        if (!(self->params & 0x8000)) {
            if (!(--self->ext.equipItemDrop.aliveTimer)) {
                self->ext.equipItemDrop.aliveTimer = 80;
                self->step++;
            }
#if !(defined VERSION_BETA || STAGE == STAGE_ST0)
        } else {
            i = self->ext.equipItemDrop.iconSlot;
            g_ItemIconSlots[i] = 0x10;
#endif
        }
        break;
    case 4:
        PrizeDropFall2(1);
        if (--self->ext.equipItemDrop.aliveTimer) {
            prim = &g_PrimBuf[self->primIndex];
            if (self->ext.equipItemDrop.aliveTimer & 2) {
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->drawMode = DRAW_UNK02;
            }
        } else {
            DestroyEntity(self);
        }
        break;
    case 5:
        if (g_unkGraphicsStruct.BottomCornerTextTimer) {
            g_api.FreePrimitives(g_unkGraphicsStruct.BottomCornerTextPrims);
            g_unkGraphicsStruct.BottomCornerTextTimer = 0;
        }
        g_api.PlaySfx(SFX_ITEM_PICKUP);
        if (itemId < NUM_HAND_ITEMS) {
            name = g_api.equipDefs[itemId].name;
            g_api.AddToInventory(itemId, EQUIP_HAND);
        } else {
            itemId -= NUM_HAND_ITEMS;
            name = g_api.accessoryDefs[itemId].name;
            g_api.AddToInventory(itemId, EQUIP_ARMOR);
        }
        BottomCornerText(name, 1);
        DestroyEntity(self);
        break;
    }

    if (self->step > 1) {
#if !(defined VERSION_BETA || STAGE == STAGE_ST0)
        if (self->ext.equipItemDrop.timer) {
            self->ext.equipItemDrop.timer--;
        }
        BlinkItem(self, self->ext.equipItemDrop.timer);
#else
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = prim->x2 = self->posX.i.hi - 7;
        prim->x1 = prim->x3 = prim->x0 + 0xE;
        prim->y0 = prim->y1 = self->posY.i.hi - 7;
        prim->y2 = prim->y3 = prim->y0 + 0xE;
        if (self->ext.equipItemDrop.timer) {
            self->ext.equipItemDrop.timer--;
            if (self->ext.equipItemDrop.timer & 2) {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = 0xFF;
            } else {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = 0x80;
            }
        }
#endif
    }
}

#if !(defined VERSION_BETA || STAGE == STAGE_ST0 || defined(VERSION_PSP) ||    \
      defined(VERSION_HD))
#include "blit_char.h"
#endif

#if defined(VERSION_PSP) && STAGE != STAGE_ST0
extern s32 g_UserLanguage;
extern char* obtainedStr; // BSS
#else
const char* g_RelicOrbTexts[] = {
#if !defined(VERSION_US) || STAGE == STAGE_ST0
    "を入手した"
#else
    "Obtained ",
#endif
};
#endif

s16 g_RelicOrbTextBg1EY[] = {16, 12, 8, 4, 0, -4, -8, -12};
s16 g_RelicOrbTextBg1SY[] = {-32, -26, -20, -13, -7, -1, 5, 12};
s16 g_RelicOrbTextBg2SY[] = {-16, -12, -8, -4, 0, 4, 8, 12};
s16 g_RelicOrbTextBg2EY[] = {32, 26, 20, 13, 7, 1, -5, -12};
#if STAGE != STAGE_ST0
s16 g_RelicOrbSparkleX[] = {-8, 4, -2, 8, 0, 4, -4, 2};
s16 g_RelicOrbSparkleY[] = {-2, 2, 4, -3, 0, 2, -4, 3};
#endif

extern u16 msgBoxTpage[0x600];

void BlinkItem(Entity* entity, u16 blinkFlag);
// params: (& 0x7FFF) Relic ID
void EntityRelicOrb(Entity* self) {
#if STAGE == STAGE_ST0
    const int PrimCount = 3;
#else
    const int PrimCount = 7;
#endif
    // prim 0: green rectangle for Obtained text bg
    // prim 1: blue rectangle for Obtained text bg

#if defined(VERSION_BETA) || STAGE == STAGE_ST0
    const int MaxItemSlots = LEN(g_ItemIconSlots);
#else
    const int MaxItemSlots = LEN(g_ItemIconSlots) - 1;
#endif
    u16 relicId;
#if defined(VERSION_PSP) || STAGE == STAGE_ST0
    u16 isObtainedTextStored;
#else
    bool isObtainedTextStored;
#endif
    RECT rect;
    Primitive* prim;
    const char* msg;
    s32 primIndex;
    s16 iconSlot;
    s32 i;
    u8* chPix;
    u16 var_s8;
    u16 msgLen;

    // unnamed variables
    u8* var_v0_5;
    u16 var_s2;
#if defined(VERSION_PSP)
    char sp34[0x100];
#endif

// The unk7C variable matches different other variables
// in different versions. We use this as a hack to match everywhere.
#if STAGE == STAGE_ST0
#define orbUnk7C isObtainedTextStored
#else
#define orbUnk7C var_s2
#endif

#if !defined(VERSION_US) || STAGE == STAGE_ST0
    u16 vramX;
    u16* chPixSrc;
    u16* chPixDst;
    u16 ch;
#endif

    relicId = self->params & 0x7FFF;
    if (self->step && self->step < 5 && self->hitFlags) {
        self->step = 5;
    }

    switch (self->step) {
    case 0:
#if STAGE != STAGE_ST0
        // If the relic was previously obtained, do not spawn it.
        if (g_Status.relics[relicId] & RELIC_FLAG_FOUND) {
            DestroyEntity(self);
            return;
        }
#endif
        InitializeEntity(g_EInitObtainable);
        for (iconSlot = 0; iconSlot < MaxItemSlots; iconSlot++) {
            if (!g_ItemIconSlots[iconSlot]) {
                break;
            }
        }

        if (iconSlot >= MaxItemSlots) {
            self->step = 0;
            return;
        }

        primIndex = g_api.AllocPrimitives(PRIM_GT4, PrimCount);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
#if STAGE == STAGE_ST0
        g_api.LoadEquipIcon(g_api.equipDefs[relicId].icon,
                            g_api.equipDefs[relicId].iconPalette, iconSlot);
#else
        self->ext.relicOrb.iconSlot = iconSlot;
#if !defined(VERSION_BETA)
        g_ItemIconSlots[iconSlot] = 0x10;
#endif
        g_api.LoadEquipIcon(g_api.relicDefs[relicId].icon,
                            g_api.relicDefs[relicId].iconPalette, iconSlot);
#endif
        prim = &g_PrimBuf[primIndex];
        for (i = 0; prim != NULL; i++) {
            if (i != 0) {
#if STAGE == STAGE_ST0
                prim->type = PRIM_G4;
#endif
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->tpage = 0x1A;
                prim->clut = iconSlot + 0x1D0;
                // Pulls iconSlot & 0b00111
                prim->u0 = prim->u2 = ((iconSlot & 7) << 4) + 1;
                prim->u1 = prim->u3 = prim->u0 + 14;
                // Pulls iconSlot & 0b11000
                prim->v0 = prim->v1 = ((iconSlot & 24) << 1) + 0x81;
                prim->v2 = prim->v3 = prim->v0 + 14;
#if STAGE != STAGE_ST0
                prim->drawMode = DRAW_COLORS | DRAW_UNK02;
#else
                prim->drawMode = DRAW_UNK02;
#endif
            }
#if STAGE == STAGE_ST0
            prim->priority = 0xC0;
#else
            prim->priority = 0x7E;
#endif
            prim = prim->next;
        }
#if STAGE != STAGE_ST0
        self->posY.i.lo = 0x8000;
        self->velocityY = FIX(0.25);
        self->ext.relicOrb.floatTimer = 64;
        self->ext.relicOrb.yFloatSpeed = -FIX(0.0078125);
#endif
        break;
#if STAGE != STAGE_ST0
    case 1:
        // The relic floats in the air
        self->velocityY += self->ext.relicOrb.yFloatSpeed;
        if (!--self->ext.relicOrb.floatTimer) {
            self->ext.relicOrb.floatTimer = 64;
            self->ext.relicOrb.yFloatSpeed = -self->ext.relicOrb.yFloatSpeed;
        }
        MoveEntity();
        iconSlot = self->ext.relicOrb.iconSlot;
        g_ItemIconSlots[iconSlot] = 0x10;
        break;
#endif
    case 5:
#if STAGE != STAGE_ST0
        g_api.func_800FE044(relicId, 0x2000);
#if !defined(VERSION_BETA)
        msg = g_api.relicDefs[relicId].name;
        if (relicId >= RELIC_SWORD_CARD && relicId < RELIC_FAERIE_CARD) {
            g_Status.relics[relicId] ^= RELIC_FLAG_ACTIVE;
        }
#endif
        self->flags |= FLAG_UNK_10000;
#else
        g_api.PlaySfx(SFX_UNK_618);

        g_Status.relics[relicId] = 3;
#endif

        // Reserve space in the VRAM to store the pre-render texture with the
        // "obtained" relic message
        rect.x = 0;
        rect.y = 256;
        rect.w = 64;
        rect.h = 16;
        ClearImage(&rect, 0, 0, 0);

        prim = &g_PrimBuf[self->primIndex];
#if STAGE == STAGE_ST0
        for (i = 0; prim != NULL; prim = prim->next, i++) {
#else
        for (i = 0; i < 3; prim = prim->next, i++) {
#endif
            if (i == 0) {
                prim->type = PRIM_SPRT;
                prim->tpage = 0x10;
                prim->x0 = 0x10;
                prim->y0 = 0xA0;
                prim->u0 = 0;
                prim->v0 = 0;
                prim->u1 = 0xF0;
                prim->v1 = 0x10;
#if STAGE == STAGE_ST0
                prim->clut = 0x1F8;
#else
                prim->clut = PAL_UNK_1A1;
#endif
                prim->priority = 0x1FE;
                prim->drawMode = DRAW_HIDE;
            } else {
#if STAGE != STAGE_ST0
                prim->type = PRIM_G4;
#endif
                prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 = 0xA7;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;

                if (i == 1) {
                    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                } else {
                    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                }
                prim->priority = 0x1FD;
                prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
            }
        }

        self->step++;
        break;

    case 6:
        // This case creates the texture "Obtained RELIC_NAME" and stores it
        // in the VRAM
#if defined(VERSION_PSP) && STAGE != STAGE_ST0
        msgLen = 0;
        var_s2 = 0;
        isObtainedTextStored = false;
        msg = g_api.relicDefs[relicId].name;
        switch (g_UserLanguage) {
        case LANG_EN:
        default:
            obtainedStr = "Obtained";
            break;
        case LANG_FR:
            obtainedStr = "Obtenu \xB1 ";
            break;
        case LANG_SP:
            obtainedStr = "Tienes";
            break;
        case LANG_GE:
            obtainedStr = "erhalten";
            break;
        case LANG_IT:
            obtainedStr = "Ottenuto";
            break;
        }

        if (g_UserLanguage != LANG_GE) {
            sprintf(&sp34, "%s %s", obtainedStr, msg);
        } else {
            sprintf(&sp34, "%s %s", msg, obtainedStr);
        }
        msgLen = strlen(sp34);
        BlitChar(&sp34[0], 0, 12, 0x100);
        self->ext.relicOrb.unk7E = msgLen;
        self->ext.relicOrb.unk7C = 0;
#elif !defined(VERSION_US) || STAGE == STAGE_ST0
        msgLen = 0;
        isObtainedTextStored = false;
        vramX = 0;
        msg = g_api.relicDefs[relicId].name;
        while (true) {
            ch = *msg++;
            if (ch == 0) {
                if (isObtainedTextStored) {
                    break;
                }
                isObtainedTextStored = true;
                msg = g_RelicOrbTexts[0];
            } else {
                ch = (ch << 8) | *msg++;
                chPixSrc = g_api.func_80106A28(ch, 1);
                if (chPixSrc != NULL) {
                    chPixDst = &msgBoxTpage[msgLen * 0x30];
                    for (i = 0; i < 0x30; i++) {
                        *chPixDst++ = *chPixSrc++;
                    }
                    LoadTPage((u_long*)&msgBoxTpage[msgLen * 0x30], 0, 0, vramX,
                              0x100, 0xC, 0x10);
                    vramX += 3;
                    msgLen++;
                }
            }
        }
        self->ext.relicOrb.unk7E = msgLen;
        self->ext.relicOrb.unk7C = 0;
#else
    msgLen = 0;
    isObtainedTextStored = false;
    msg = g_RelicOrbTexts[0];
    chPix = g_Pix[0];
    var_v0_5 = (u8*)chPix;
    for (i = 0; i < 0xC00; i++) {
        *var_v0_5++ = 0;
    }

    msgLen = 0;
    while (true) {
        if (*msg == 0) {
            if (isObtainedTextStored) {
                break;
            }
            msg = g_api.relicDefs[relicId].name;
            isObtainedTextStored = true;
        } else {
            msg = BlitChar(msg, &msgLen, chPix, 0xC0);
        }
    }

    LoadTPage(chPix, 0, 0, 0, 0x100, 0x180, 0x10);
    self->ext.relicOrb.unk7C = 0;
    self->ext.relicOrb.unk7E = msgLen;
#endif
        self->step++;
        break;
    case 7:
        // Animates the blue/green rectangle for the Obtain text bg
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
#if STAGE == STAGE_ST0
        for (i = 0; prim != NULL; prim = prim->next, i++) {
#else
        for (i = 0; i < 2; prim = prim->next, i++) {
#endif
            if (i == 0) {
                prim->x2 -= 3;
                prim->x3 += 3;
                prim->y0 = prim->y1 -= 4;
                prim->y2 = prim->y3 += 2;
            } else {
                prim->x0 -= 3;
                prim->x1 += 3;
                prim->y0 = prim->y1 -= 2;
                prim->y2 = prim->y3 += 4;
            }
        }

        if (++self->ext.relicOrb.unk7C == 8) {
            self->ext.relicOrb.unk7C = 0;
            self->step++;
        }
        break;

    case 8:
        orbUnk7C = self->ext.relicOrb.unk7C;
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
#if STAGE == STAGE_ST0
        for (i = 0; prim != NULL; prim = prim->next, i++) {
#else
        for (i = 0; i < 3; prim = prim->next, i++) {
#endif
            if (i == 0) {
                prim->x1 = 0x80 - (orbUnk7C + 1) * 0xC;
                prim->x0 = 0x80 + (orbUnk7C + 1) * 0xC;
                prim->x2 = 0x68 + (orbUnk7C * 0x78) / 7;
                prim->x3 = 0x98 - (orbUnk7C * 0x78) / 7;
                prim->y0 = prim->y1 = g_RelicOrbTextBg1SY[orbUnk7C] + 0xA7;
                prim->y2 = prim->y3 = g_RelicOrbTextBg1EY[orbUnk7C] + 0xA7;
                prim->b2 = prim->b3 -= 0x10;
            } else {
                prim->x0 = 0x68 + (orbUnk7C * 0x78) / 7;
                prim->x1 = 0x98 - (orbUnk7C * 0x78) / 7;
                prim->x3 = 0x80 - (orbUnk7C + 1) * 0xC;
                prim->x2 = 0x80 + (orbUnk7C + 1) * 0xC;
                prim->y0 = prim->y1 = g_RelicOrbTextBg2SY[orbUnk7C] + 0xA7;
                prim->y2 = prim->y3 = g_RelicOrbTextBg2EY[orbUnk7C] + 0xA7;
                prim->g0 = prim->g1 -= 0x10;
            }
        }

        if (++self->ext.relicOrb.unk7C == 8) {
            self->step++;
            self->ext.relicOrb.unk7C = 0;
        }
        break;

    case 9:
        prim = &g_PrimBuf[self->primIndex];
#if defined(VERSION_US) && !defined(VERSION_PSP) && STAGE != STAGE_ST0
        prim->x0 = 0x80 - self->ext.relicOrb.unk7E;
#else
        prim->x0 = 0x80 - self->ext.relicOrb.unk7E * 6;
#endif
        prim->drawMode = DRAW_DEFAULT;
        self->ext.relicOrb.unk7C++;
#if STAGE == STAGE_ST0
        if (self->ext.relicOrb.unk7C > 0x100) {
#else
        if (self->ext.relicOrb.unk7C > 0x60) {
#endif
            DestroyEntity(self);
            return;
        }
        break;
    }

    if (self->step < 2) {
#if STAGE == STAGE_ST0
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = prim->x2 = self->posX.i.hi - 7;
        prim->x1 = prim->x3 = prim->x0 + 14;
        prim->y0 = prim->y1 = self->posY.i.hi - 7;
        prim->y2 = prim->y3 = prim->y0 + 14;
#elif defined(VERSION_BETA)
        // This is just the function BlinkItem inlined
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = prim->x2 = self->posX.i.hi - 7;
        prim->x1 = prim->x3 = prim->x0 + 14;
        prim->y0 = prim->y1 = self->posY.i.hi - 7;
        prim->y2 = prim->y3 = prim->y0 + 14;

        if (g_Timer & RENDERFLAGS_NOSHADOW) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = 255;
        } else {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = 128;
        }
#else
    BlinkItem(self, g_Timer);
    prim = &g_PrimBuf[self->primIndex];
#endif
#if STAGE != STAGE_ST0
        // Animates the four sparkles while the relic is floating
        for (i = 0; i < 3; i++) { // Skip the first three primitives
            prim = prim->next;
        }

        if (!self->ext.relicOrb.sparkleCycle) {
            for (i = 0; i < 4; i++) {
                if (prim->drawMode == DRAW_HIDE) {
                    prim->tpage = 0x1A;
                    prim->clut = PAL_UNK_1B1;
                    prim->u0 = prim->u2 = 0;
                    prim->u1 = prim->u3 = 0x10;
                    prim->v0 = prim->v1 = 0x50;
                    prim->v2 = prim->v3 = 0x60;

                    var_s8 = self->ext.relicOrb.sparkleAnim & 7;
                    iconSlot = self->posX.i.hi;
                    iconSlot += g_RelicOrbSparkleX[var_s8];
                    prim->x0 = prim->x2 = iconSlot - 6;
                    prim->x1 = prim->x3 = iconSlot + 6;

                    iconSlot = self->posY.i.hi;
                    iconSlot += g_RelicOrbSparkleY[var_s8];
                    prim->y0 = prim->y1 = iconSlot - 6;
                    prim->y2 = prim->y3 = iconSlot + 6;

                    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0x80;
                    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                    prim->p1 = 0;
                    prim->priority = 0x7F;
                    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                     DRAW_UNK02 | DRAW_TRANSP;
                    break;
                }
                prim = prim->next;
            }

            self->ext.relicOrb.sparkleCycle = 4;
            self->ext.relicOrb.sparkleAnim++;
        } else {
            self->ext.relicOrb.sparkleCycle--;
        }
    }

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 3; i++) {
        prim = prim->next;
    }

    for (; prim != NULL; prim = prim->next) {
        if (prim->drawMode != DRAW_HIDE) {
            if (prim->p1 & 3) {
                prim->y0 = prim->y1--;
                prim->y2 = prim->y3--;
            } else {
                prim->y2 = prim->y3 -= 2;
                prim->x0 = prim->x2++;
                prim->x1 = prim->x3--;
            }
            prim->r0 = prim->r1 = prim->r2 = prim->r3 -= 6;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 -= 6;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 -= 6;
            prim->p1++;
            if (prim->p1 > 0x10) {
                prim->drawMode = DRAW_HIDE;
            }
        }
#endif
    }
}

#if STAGE != STAGE_ST0
#if defined(VERSION_BETA)
static u16 OVL_EXPORT(PrizeDrops)[] = {
    0x000C, 0x0017, 0x00D8, 0x012F, 0x000C, 0x0085, 0x0017, 0x00E5,
    0x014A, 0x00EE, 0x013A, 0x0017, 0x000C, 0x00C9, 0x008B, 0x00C8,
    0x0098, 0x0099, 0x0142, 0x0161, 0x008F, 0x011A, 0x011F, 0x0099,
    0x00C9, 0x00F2, 0x0133, 0x0103, 0x0150, 0x013E, 0x000C, 0x0017,
    0x0103, 0x00D6, 0x00E6, 0x0017, 0x0017, 0x0089, 0x0139, 0x0000};
#else
// defined in d_prize_drops.c
extern u16 OVL_EXPORT(PrizeDrops)[];
#endif

// params: Local index of this drop
void EntityHeartDrop(Entity* self) {
    u16 index;
    u8 value;
    PfnEntityUpdate update;

    if (!self->step) {
        index = self->ext.heartDrop.unkB4 =
            self->params + HEART_DROP_CASTLE_FLAG;
        value = g_CastleFlags[(index >> 3) + CASTLE_COLLECTIBLES_100] >>
                (index & 7);
        if (value & 1) {
            DestroyEntity(self);
            return;
        }

        index -= HEART_DROP_CASTLE_FLAG;
        index = OVL_EXPORT(PrizeDrops)[index];
        if (index < 128) {
            self->unkB8 = (Entity*)EntityPrizeDrop;
        } else {
            self->unkB8 = (Entity*)EntityEquipItemDrop;
            index -= 128;
        }
        self->params = index + 0x8000;
    } else {
        index = self->ext.heartDrop.unkB4;
        if (self->step < 5) {
            if (self->hitFlags) {
                g_CastleFlags[(index >> 3) + CASTLE_COLLECTIBLES_100] |=
                    1 << (index & 7);
                self->step = 5;
            }
        }
    }
    update = (PfnEntityUpdate)self->unkB8;
    update(self);
}

#if !defined(VERSION_BETA)
// params: message box duration, in frames
// ext.messageBox.label: box size and text to render
void EntityMessageBox(Entity* self) {
    const u16 VramX = 0;
    const u16 VramY = 0x180;
    const int FontW = 12;
    const int FontH = 16;
    const int FontLen = FontW * FontH / 2 / sizeof(u16); // 4bpp

    Primitive* prim;
    s32 i;
    char* str;
    s32 primIndex;
    u16 xOffset;
    u8* chPix;
    u8* dstPix;
    u8 ch;
    RECT rect;

    u16 x;
    u16 y;
    u16 nCh;

    u16 chjp;
    u16* srcJpPix;
    u16* dstJpPix;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitObtainable);
        self->flags |= FLAG_UNK_10000;
        self->flags ^= FLAG_POS_CAMERA_LOCKED;
        if (!self->params) {
            self->params = 96; // default to 96 frames, or 1.5 seconds
        }

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        str = self->ext.messageBox.label;
        self->ext.messageBox.width = *str++;
        self->ext.messageBox.height = *str++;
        self->ext.messageBox.label += 2;
        break;
    case 1:
        rect.x = 0;
        rect.y = 0x180;
        rect.w = 64;
        rect.h = self->ext.messageBox.height;
        ClearImage(&rect, 0, 0, 0);

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; prim = prim->next, i++) {
            if (i == 0) {
                prim->type = PRIM_SPRT;
                prim->tpage = 0x10;
                prim->x0 = self->posX.i.hi - self->ext.messageBox.width / 2;
                prim->y0 = self->posY.i.hi - self->ext.messageBox.height / 2;
                prim->u0 = 0;
                prim->v0 = 0x80;
                prim->u1 = self->ext.messageBox.width;
                prim->v1 = self->ext.messageBox.height;
                prim->clut = PAL_UNK_1A1;
                prim->priority = 0x1FD;
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->type = PRIM_G4;
                prim->x0 = prim->x2 =
                    self->posX.i.hi - self->ext.messageBox.width / 2 - 4;
                prim->x1 = prim->x3 =
                    self->posX.i.hi + self->ext.messageBox.width / 2 + 4;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
                if (i == 1) {
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        self->posY.i.hi - self->ext.messageBox.height / 2 - 4;
                    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                } else {
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        self->posY.i.hi + self->ext.messageBox.height / 2 + 4;
                    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                }
                prim->priority = 0x1FC;
                prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
            }
        }
        self->step++;
        break;
    case 2:
#if defined(VERSION_US)
        dstPix = g_Pix[0];
        chPix = dstPix;
        str = self->ext.messageBox.label;
        xOffset = 0;
        for (i = 0;
             i < self->ext.messageBox.width / 2 * self->ext.messageBox.height;
             i++) {
            *chPix++ = 0;
        }

        chPix = dstPix;
        while (true) {
            if (*str == 0) {
                break;
            }
            if (*str == 1) {
                str++;
                xOffset = 0;
                chPix = &dstPix[self->ext.messageBox.width * 8];
            } else {
                str = BlitChar(
                    str, &xOffset, chPix, self->ext.messageBox.width >> 1);
            }
        }
        LoadTPage((u_long*)dstPix, 0, 0, VramX, VramY,
                  self->ext.messageBox.width, self->ext.messageBox.height);
#elif defined(VERSION_PSP)
        nCh = 0;
        x = VramX;
        y = VramY;
        str = self->ext.messageBox.label;
        BlitChar(str, 0, 0, 0x180);
#elif defined(VERSION_HD)
        nCh = 0;
        x = VramX;
        y = VramY;
        str = self->ext.messageBox.label;
        while (true) {
            chjp = *str++;
            if (!chjp) {
                break;
            }
            if (chjp == 1) {
                y += FontH;
                x = 0;
            } else {
                chjp = (*str++ | (chjp << 8));
                srcJpPix = g_api.func_80106A28(chjp, 1);
                if (srcJpPix) {
                    dstJpPix = &msgBoxTpage[nCh * FontLen];
                    for (i = 0; i < FontLen; i++) {
                        *dstJpPix++ = *srcJpPix++;
                    }
                    LoadTPage(
                        &msgBoxTpage[nCh * FontLen], 0, 0, x, y, FontW, FontH);
                    x += 3;
                    nCh++;
                }
            }
        }
#endif
        self->ext.messageBox.duration = 0;
        self->step++;
        break;
    case 3:
        self->ext.messageBox.duration++;
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        for (i = 0; prim != NULL; prim = prim->next, i++) {
            if (i == 0) {
                prim->y2 = prim->y3 =
                    prim->y0 + (self->ext.messageBox.height + 8) *
                                   self->ext.messageBox.duration / 8;
                prim->b0 = prim->b1 -= 0x10;
            } else {
                prim->y0 = prim->y1 =
                    prim->y2 - (self->ext.messageBox.height + 8) *
                                   self->ext.messageBox.duration / 8;
                prim->g2 = prim->g3 -= 0x10;
            }
        }
        if (self->ext.messageBox.duration == 8) {
            self->ext.messageBox.duration = 0;
            self->step++;
        }
        break;
    case 4:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode = DRAW_DEFAULT;
        self->ext.messageBox.duration++;
        if (self->ext.messageBox.duration > self->params) {
            DestroyEntity(self);
        }
        break;
    }
}

#endif

#endif
