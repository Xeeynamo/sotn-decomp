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

extern EInit g_EInitObtainable;
extern EInit g_EInitParticle;

#if !defined(E_COLLECT_ONLY_PRIZE_DROP) &&                                  \
    !defined(E_COLLECT_ONLY_RELIC_ORB)

#if defined(VERSION_PSP)
#include "blit_char_psp.h"
#endif

#if STAGE == STAGE_ST0
static AnimateEntityFrame D_80180C94[] = {
    POSE(2, 0x1A, 0), POSE(2, 0x1B, 0), POSE(2, 0x1C, 0), POSE(2, 0x1D, 0),
    POSE(2, 0x1E, 0), POSE(2, 0x1F, 0), POSE(2, 0x20, 0), POSE(2, 0x21, 0),
    POSE(2, 0x20, 0), POSE(2, 0x1F, 0), POSE(2, 0x1E, 0), POSE(2, 0x1D, 0),
    POSE(2, 0x1C, 0), POSE(2, 0x1B, 0), POSE(2, 0x1A, 0), POSE_LOOP(0)};

static AnimateEntityFrame D_80180C98[] = {
    POSE(2, 0x22, 0), POSE(2, 0x23, 0), POSE(2, 0x24, 0), POSE(2, 0x25, 0),
    POSE(2, 0x26, 0), POSE(2, 0x27, 0), POSE(2, 0x28, 0), POSE(2, 0x29, 0),
    POSE(2, 0x28, 0), POSE(2, 0x27, 0), POSE(2, 0x26, 0), POSE(2, 0x25, 0),
    POSE(2, 0x24, 0), POSE(2, 0x23, 0), POSE_LOOP(0)};
#else
static AnimateEntityFrame D_80180C94[] = {POSE(1, 0x0E, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180C98[] = {
    POSE(2, 3, 0),    POSE(6, 4, 0),    POSE(5, 5, 0),    POSE(5, 6, 0),
    POSE(4, 7, 0),    POSE(3, 8, 0),    POSE(4, 9, 0),    POSE(5, 0x0A, 0),
    POSE(5, 0x0B, 0), POSE(6, 0x0C, 0), POSE(7, 3, 0),    POSE(6, 4, 0),
    POSE(5, 5, 0),    POSE(5, 6, 0),    POSE(4, 7, 0),    POSE(3, 8, 0),
    POSE(4, 9, 0),    POSE(5, 0x0A, 0), POSE(5, 0x0B, 0), POSE(6, 0x0C, 0),
    POSE(2, 0x0D, 0), POSE_LOOP(0)};
#endif
static AnimateEntityFrame D_80180CC4[] = {
    POSE(4, 0x14, 0), POSE(7, 0x15, 0), POSE(6, 0x16, 0), POSE(3, 0x17, 0),
    POSE(3, 0x18, 0), POSE(6, 0x19, 0), POSE(2, 0x15, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180CD4[] = {POSE(1, 0x1A, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180CD8[] = {POSE(1, 0x1B, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180CDC[] = {POSE(1, 0x1C, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180CE0[] = {POSE(1, 0x1D, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180CE4[] = {POSE(1, 0x1E, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180CE8[] = {POSE(1, 0x1F, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180CEC[] = {POSE(1, 0x20, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180CF0[] = {POSE(1, 0x21, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180CF4[] = {
    POSE(2, 0x22, 0), POSE(2, 0x23, 0), POSE(2, 0x24, 0),
    POSE(2, 0x25, 0), POSE(2, 0x26, 0), POSE(2, 0x27, 0),
    POSE(2, 0x28, 0), POSE(2, 0x29, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180D08[] = {
    POSE(0x1A, 0x0F, 0), POSE(6, 0x10, 0), POSE(4, 0x11, 0), POSE(2, 0x12, 0),
    POSE(4, 0x11, 0),    POSE(6, 0x10, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180D18[] = {POSE(1, 0x13, 0), POSE_LOOP(0)};
#if STAGE != STAGE_ST0
static AnimateEntityFrame D_80180D1C[] = {
    POSE(5, 0x2A, 0), POSE(5, 0x2B, 0), POSE(5, 0x2C, 0),
    POSE(5, 0x2D, 0), POSE(5, 0x2E, 0), POSE(5, 0x2F, 0),
    POSE(5, 0x30, 0), POSE(5, 0x31, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180D30[] = {
    POSE(5, 0x32, 0), POSE(5, 0x33, 0), POSE(5, 0x34, 0),
    POSE(5, 0x35, 0), POSE(5, 0x36, 0), POSE(5, 0x37, 0),
    POSE(5, 0x38, 0), POSE(5, 0x39, 0), POSE_LOOP(0)};
#else
static AnimateEntityFrame D_80180D1C[] = {POSE(5, 0x19, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180D30[] = {POSE(5, 0x18, 0), POSE_LOOP(0)};
#endif
static AnimateEntityFrame D_80180D44[] = {
    POSE(5, 0x3A, 0), POSE(5, 0x3B, 0), POSE(5, 0x3C, 0),
    POSE(5, 0x3D, 0), POSE(5, 0x3E, 0), POSE(5, 0x3F, 0),
    POSE(5, 0x40, 0), POSE(5, 0x41, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180D58[] = {
    POSE(5, 0x42, 0), POSE(5, 0x43, 0), POSE(5, 0x44, 0),
    POSE(5, 0x45, 0), POSE(5, 0x46, 0), POSE(5, 0x47, 0),
    POSE(5, 0x48, 0), POSE(5, 0x49, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180D6C[] = {
    POSE(5, 0x4A, 0), POSE(5, 0x4B, 0), POSE(5, 0x4C, 0),
    POSE(5, 0x4D, 0), POSE(5, 0x4E, 0), POSE(5, 0x4F, 0),
    POSE(5, 0x50, 0), POSE(5, 0x51, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180D80[] = {
    POSE(5, 0x52, 0), POSE(5, 0x53, 0), POSE(5, 0x54, 0),
    POSE(5, 0x55, 0), POSE(5, 0x56, 0), POSE(5, 0x57, 0),
    POSE(5, 0x58, 0), POSE(5, 0x59, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180D94[] = {
    POSE(5, 0x5A, 0), POSE(5, 0x5B, 0), POSE(5, 0x5C, 0),
    POSE(5, 0x5D, 0), POSE(5, 0x5E, 0), POSE(5, 0x5F, 0),
    POSE(5, 0x60, 0), POSE(5, 0x61, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180DA8[] = {
    POSE(5, 0x62, 0), POSE(5, 0x63, 0), POSE(5, 0x64, 0),
    POSE(5, 0x65, 0), POSE(5, 0x66, 0), POSE(5, 0x67, 0),
    POSE(5, 0x68, 0), POSE(5, 0x69, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_80180DBC[] = {
    POSE(5, 0x6A, 0), POSE(5, 0x6B, 0), POSE(5, 0x6C, 0),
    POSE(5, 0x6D, 0), POSE(5, 0x6E, 0), POSE(5, 0x6F, 0),
    POSE(5, 0x70, 0), POSE(5, 0x71, 0), POSE_LOOP(0)};
#if STAGE != STAGE_ST0
static AnimateEntityFrame D_80180DD0[] = {POSE(1, 0x8F, 0), POSE_LOOP(0)};
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

AnimateEntityFrame* g_SubweaponAnimPrizeDrop[] = {
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
static AnimateEntityFrame D_psp_09246398[] = {
    POSE(5, 0xA1, 0), POSE(5, 0xA2, 0), POSE(5, 0xA3, 0),
    POSE(5, 0xA4, 0), POSE(5, 0xA5, 0), POSE(5, 0xA6, 0),
    POSE(5, 0xA7, 0), POSE(5, 0xA8, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_psp_092463B0[] = {
    POSE(5, 0xA9, 0), POSE(5, 0xAA, 0), POSE(5, 0xAB, 0),
    POSE(5, 0xAC, 0), POSE(5, 0xAD, 0), POSE(5, 0xAE, 0),
    POSE(5, 0xAF, 0), POSE(5, 0xB0, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_psp_092463C8[] = {
    POSE(5, 0xB1, 0), POSE(5, 0xB2, 0), POSE(5, 0xB3, 0),
    POSE(5, 0xB4, 0), POSE(5, 0xB5, 0), POSE(5, 0xB6, 0),
    POSE(5, 0xB7, 0), POSE(5, 0xB8, 0), POSE_LOOP(0)};
static AnimateEntityFrame D_psp_092463E0[] = {
    POSE(5, 0xB9, 0), POSE(5, 0xBA, 0), POSE(5, 0xBB, 0),
    POSE(5, 0xBC, 0), POSE(5, 0xBD, 0), POSE(5, 0xBE, 0),
    POSE(5, 0xBF, 0), POSE(5, 0xC0, 0), POSE_LOOP(0)};
AnimateEntityFrame* g_MariaSubweaponAnimPrizeDrop[] = {
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

static s16 g_PrizeDropCollisionOffsets[] = {-6, 4, 0, -8};
#if !defined(VERSION_BETA) && STAGE != STAGE_ST0
// Note that this array is in data. MAD/ST0 have it in rodata.
s8 c_HeartPrizes[] = {1, 5};
#endif

#include "e_collect_fall.h"

#include "e_collect_heart.h"

static s32 g_ExplosionYVelocities[] = {
    FIX(-1.0), FIX(-1.5), FIX(-1.5), FIX(-1.5), FIX(-3.0)};

static AnimateEntityFrame anim_small[] = {
    POSE(2, 1, 0), POSE(2, 2, 0), POSE(2, 3, 0), POSE(2, 4, 0), POSE(2, 5, 0),
    POSE(2, 6, 0), POSE(2, 7, 0), POSE(2, 8, 0), POSE_LOOP(0)};

AnimateEntityFrame g_bigRedFireballAnim[] = {
    POSE(1, 9, 0),  POSE(2, 10, 0), POSE(2, 11, 0), POSE(2, 12, 0),
    POSE(2, 13, 0), POSE(2, 14, 0), POSE(2, 15, 0), POSE(2, 16, 0),
    POSE(2, 17, 0), POSE(2, 18, 0), POSE(3, 19, 0), POSE(4, 20, 0),
    POSE_LOOP(0)};

static AnimateEntityFrame anim_small_multiple[] = {
    POSE(2, 0x15, 0), POSE(2, 0x16, 0), POSE(2, 0x17, 0), POSE(2, 0x18, 0),
    POSE(2, 0x19, 0), POSE(2, 0x1A, 0), POSE(2, 0x1B, 0), POSE(2, 0x1C, 0),
    POSE(2, 0x1D, 0), POSE(2, 0x1E, 0), POSE(2, 0x1F, 0), POSE(2, 0x20, 0),
    POSE(2, 0x21, 0), POSE(2, 0x22, 0), POSE(2, 0x23, 0), POSE(2, 0x24, 0),
    POSE(2, 0x25, 0), POSE(2, 0x26, 0), POSE(2, 0x27, 0), POSE(2, 0x28, 0),
    POSE(2, 0x29, 0), POSE(2, 0x2A, 0), POSE_LOOP(0)};

AnimateEntityFrame g_explosionBigAnim[] = {
    POSE(2, 0x2B, 0), POSE(2, 0x2C, 0), POSE(2, 0x2D, 0), POSE(2, 0x2E, 0),
    POSE(2, 0x2F, 0), POSE(2, 0x30, 0), POSE(2, 0x31, 0), POSE(2, 0x32, 0),
    POSE(2, 0x33, 0), POSE(2, 0x34, 0), POSE(2, 0x35, 0), POSE(2, 0x36, 0),
    POSE(2, 0x37, 0), POSE(2, 0x38, 0), POSE(2, 0x39, 0), POSE(2, 0x3A, 0),
    POSE(2, 0x3B, 0), POSE(2, 0x3C, 0), POSE(2, 0x3D, 0), POSE(2, 0x3E, 0),
    POSE(2, 0x3F, 0), POSE(2, 0x40, 0), POSE(2, 0x41, 0), POSE(2, 0x42, 0),
    POSE_LOOP(0)};

// This doesn't seem to be used in any of the currently decompiled code.
static AnimateEntityFrame D_80180F6C[] = {POSE(1, 0x43, 0), POSE_LOOP(0)};

static AnimateEntityFrame* g_ExplosionAnimations[] = {
    anim_small,         g_bigRedFireballAnim, anim_small_multiple,
    g_explosionBigAnim, D_80180F6C,
};

#include "e_collect_gold.h"

#if defined VERSION_BETA || STAGE == STAGE_ST0
void func_801937BC(void) {}

void UnusedDestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }
#endif

#if defined(VERSION_PSP) && (STAGE != STAGE_ST0)
#include "collect_subweapon_psp.h"
#else
#include "collect_subweapon.h"
#endif

#include "e_collect_vessels.h"

#endif

#if !defined(E_COLLECT_ONLY_RELIC_ORB)

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
        self->palette = PAL_FLAG(PAL_FILL_WHITE);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitObtainable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        self->blendMode = BLEND_NO;
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
            CheckFieldCollision(g_PrizeDropCollisionOffsets, 2);
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
                PRED(prim) = 0x80;
                PGRN(prim) = 0x80;
                PBLU(prim) = 0x80;
#else
                prim->u0 = prim->u2 = prim->v0 = prim->v1 = 0;
                prim->u1 = prim->u3 = prim->v2 = prim->v3 = 0x20;
                PCOL(prim) = 0x80;
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
            CheckFieldCollision(g_PrizeDropCollisionOffsets, 2);
            self->animCurFrame = 0;
            if (self->ext.equipItemDrop.sparkleTimer) {
                self->ext.equipItemDrop.sparkleTimer--;
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
            self->ext.equipItemDrop.sparkleTimer++;
            if (self->ext.equipItemDrop.sparkleTimer < 17) {
                index = self->ext.equipItemDrop.sparkleTimer;
                self->animCurFrame = 0;
            } else {
                index = 32 - self->ext.equipItemDrop.sparkleTimer;
                PRED(prim) -= 8;
                PGRN(prim) -= 8;
                PBLU(prim) -= 8;
            }
            prim->x0 = prim->x2 = self->posX.i.hi - index;
            prim->x1 = prim->x3 = self->posX.i.hi + index;
            prim->y0 = prim->y1 = self->posY.i.hi - index;
            prim->y2 = prim->y3 = self->posY.i.hi + index;
            if (self->ext.equipItemDrop.sparkleTimer == 32) {
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

#endif

#if !defined(E_COLLECT_ONLY_PRIZE_DROP)

#if !defined(E_COLLECT_ONLY_RELIC_ORB)

#include "e_collect_explosion.h"

// Weird difference here. These functions are not related.
// But MAD has one and not the other.
#if !(defined VERSION_BETA || STAGE == STAGE_ST0)
#include "e_collect_blink.h"
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

    InitializeEntity(g_EInitBreakable);
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

#include "e_collect_equip_item_drop.h"

#if !(defined VERSION_BETA || STAGE == STAGE_ST0 || defined(VERSION_PSP) ||    \
      defined(VERSION_HD))
#include "blit_char.h"
#endif

#if defined(VERSION_PSP) && STAGE != STAGE_ST0
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

#endif

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
        for (i = 0; prim != NULL; i++) {
#else
        for (i = 0; i < 3; i++) {
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
                PRED(prim) = 0;
                PGRN(prim) = 0;
                PBLU(prim) = 0;

                if (i == 1) {
                    PBLU(prim) = 0x80;
                } else {
                    PGRN(prim) = 0x80;
                }
                prim->priority = 0x1FD;
                prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
            }
            prim = prim->next;
        }

        self->step++;
        break;

    case 6:
        // This case creates the texture "Obtained RELIC_NAME" and stores it
        // in the VRAM
        msgLen = 0;
        var_s2 = 0;
        isObtainedTextStored = false;
#if defined(VERSION_PSP) && STAGE != STAGE_ST0
        msg = g_api.relicDefs[relicId].name;
        switch (g_UserLanguage) {
        case LANG_EN:
        default:
#if defined(E_COLLECT_EXTERNAL_RELIC_STRINGS)
            obtainedStr = g_RelicObtainedEn;
#else
            obtainedStr = "Obtained";
#endif
            break;
        case LANG_FR:
#if defined(E_COLLECT_EXTERNAL_RELIC_STRINGS)
            obtainedStr = g_RelicObtainedFr;
#else
            obtainedStr = "Obtenu \xB1 ";
#endif
            break;
        case LANG_SP:
#if defined(E_COLLECT_EXTERNAL_RELIC_STRINGS)
            obtainedStr = g_RelicObtainedSp;
#else
            obtainedStr = "Tienes";
#endif
            break;
        case LANG_GE:
#if defined(E_COLLECT_EXTERNAL_RELIC_STRINGS)
            obtainedStr = g_RelicObtainedGe;
#else
            obtainedStr = "erhalten";
#endif
            break;
        case LANG_IT:
#if defined(E_COLLECT_EXTERNAL_RELIC_STRINGS)
            obtainedStr = g_RelicObtainedIt;
#else
            obtainedStr = "Ottenuto";
#endif
            break;
        }

        if (g_UserLanguage != LANG_GE) {
#if defined(E_COLLECT_EXTERNAL_RELIC_STRINGS)
            sprintf(&sp34, g_RelicObtainedFormat, obtainedStr, msg);
#else
            sprintf(&sp34, "%s %s", obtainedStr, msg);
#endif
        } else {
#if defined(E_COLLECT_EXTERNAL_RELIC_STRINGS)
            sprintf(&sp34, g_RelicObtainedFormat, msg, obtainedStr);
#else
            sprintf(&sp34, "%s %s", msg, obtainedStr);
#endif
        }
        msgLen = strlen(sp34);
        BlitChar(&sp34[0], 0, 12, 0x100);
#elif !defined(VERSION_US) || STAGE == STAGE_ST0
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
#else
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
#endif
        self->ext.relicOrb.unk7E = msgLen;
        self->ext.relicOrb.unk7C = 0;
        self->step++;
        break;
    case 7:
        // Animates the blue/green rectangle for the Obtain text bg
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
#if STAGE == STAGE_ST0
        for (i = 0; prim != NULL; i++) {
#else
        for (i = 0; i < 2; i++) {
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
            prim = prim->next;
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
        for (i = 0; prim != NULL; i++) {
#else
        for (i = 0; i < 3; i++) {
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
            prim = prim->next;
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

        if (g_Timer & 2) {
            PCOL(prim) = 0xFF;
        } else {
            PCOL(prim) = 0x80;
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

                    PRED(prim) = 0x80;
                    PGRN(prim) = 0x80;
                    PBLU(prim) = 0x80;
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

    while (prim != NULL) {
        if (prim->drawMode != DRAW_HIDE) {
            if (prim->p1 & 3) {
                prim->y0 = prim->y1--;
                prim->y2 = prim->y3--;
            } else {
                prim->y2 = prim->y3 -= 2;
                prim->x0 = prim->x2++;
                prim->x1 = prim->x3--;
            }
            PRED(prim) -= 6;
            PGRN(prim) -= 6;
            PBLU(prim) -= 6;
            prim->p1++;
            if (prim->p1 > 0x10) {
                prim->drawMode = DRAW_HIDE;
            }
        }
        prim = prim->next;
#endif
    }
}

#if !defined(E_COLLECT_ONLY_RELIC_ORB)

#if STAGE != STAGE_ST0
#include "e_collect_heart_drop.h"

#if !defined(VERSION_BETA)
#include "e_collect_message_box.h"
#endif

#endif

#endif

#endif
