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
#include "sfx.h"

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
static u8 D_80180C94[] = {0x01, 0x0E, 0x00};
static u8 D_80180C98[] = {
    0x02, 0x03, 0x06, 0x04, 0x05, 0x05, 0x05, 0x06, 0x04, 0x07, 0x03,
    0x08, 0x04, 0x09, 0x05, 0x0A, 0x05, 0x0B, 0x06, 0x0C, 0x07, 0x03,
    0x06, 0x04, 0x05, 0x05, 0x05, 0x06, 0x04, 0x07, 0x03, 0x08, 0x04,
    0x09, 0x05, 0x0A, 0x05, 0x0B, 0x06, 0x0C, 0x02, 0x0D, 0x00};
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
                          0x6E, 0x05, 0x6F, 0x05, 0x70, 0x05, 0x71, 0x00};
static u8 D_80180DD0[] = {
#if STAGE != STAGE_ST0
    0x01, 0x8F, 0x00, 0x00,
#endif
    0xFC, 0xFC, 0x04, 0xFC, 0xFC, 0x04, 0x04, 0x04, 0x80, 0x00};
static u16 aluric_subweapons_idx[] = {1, 2, 4, 3, 6, 5, 7, 8, 9};
static u16 aluric_subweapons_id[] = {0, 14, 15, 17, 16, 19, 18, 20, 21, 22};

#if STAGE != STAGE_ST0
const char* g_goldCollectTexts[] = {
    _S("$1"),   _S("$25"),  _S("$50"),   _S("$100"),  _S("$250"),
    _S("$400"), _S("$700"), _S("$1000"), _S("$2000"), _S("$5000"),
};
static u32 c_GoldPrizes[] = {1, 25, 50, 100, 250, 400, 700, 1000, 2000, 5000};
#else
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

static s16 D_80180EB8[] = {-6, 4, 0, -8};
#if !defined(VERSION_BETA) && STAGE != STAGE_ST0
// Note that this array is in data. MAD/ST0 have it in rodata.
s8 c_HeartPrizes[] = {1, 5};
#endif

// from another file
extern u16 g_EInitObtainable[];

#include "prize_drop_fall.h"

#include "prize_drop_fall2.h"

#include "collect_heart.h"

static s32 g_ExplosionYVelocities[] = {
    FIX(-1.0), FIX(-1.5), FIX(-1.5), FIX(-1.5), FIX(-3.0)};

static u8 D_80180ED8[] = {
    0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x02, 0x05,
    0x02, 0x06, 0x02, 0x07, 0x02, 0x08, 0x00, 0x00, 0x00, 0x00,
};
u8 g_bigRedFireballAnim[] = {
    0x01, 0x09, 0x02, 0x0A, 0x02, 0x0B, 0x02, 0x0C, 0x02, 0x0D,
    0x02, 0x0E, 0x02, 0x0F, 0x02, 0x10, 0x02, 0x11, 0x02, 0x12,
    0x03, 0x13, 0x04, 0x14, 0x00, 0x00, 0x00, 0x00,
};
static u8 D_80180F08[] = {
    0x02, 0x15, 0x02, 0x16, 0x02, 0x17, 0x02, 0x18, 0x02, 0x19, 0x02, 0x1A,
    0x02, 0x1B, 0x02, 0x1C, 0x02, 0x1D, 0x02, 0x1E, 0x02, 0x1F, 0x02, 0x20,
    0x02, 0x21, 0x02, 0x22, 0x02, 0x23, 0x02, 0x24, 0x02, 0x25, 0x02, 0x26,
    0x02, 0x27, 0x02, 0x28, 0x02, 0x29, 0x02, 0x2A, 0x00, 0x00, 0x00, 0x00,
};
static u8 D_80180F38[] = {
    0x02, 0x2B, 0x02, 0x2C, 0x02, 0x2D, 0x02, 0x2E, 0x02, 0x2F, 0x02,
    0x30, 0x02, 0x31, 0x02, 0x32, 0x02, 0x33, 0x02, 0x34, 0x02, 0x35,
    0x02, 0x36, 0x02, 0x37, 0x02, 0x38, 0x02, 0x39, 0x02, 0x3A, 0x02,
    0x3B, 0x02, 0x3C, 0x02, 0x3D, 0x02, 0x3E, 0x02, 0x3F, 0x02, 0x40,
    0x02, 0x41, 0x02, 0x42, 0x00, 0x00, 0x00, 0x00,
};
static u8 D_80180F6C[] = {0x01, 0x43, 0x00, 0x00};

static u8* g_ExplosionAnimations[] = {
    D_80180ED8, g_bigRedFireballAnim, D_80180F08, D_80180F38, D_80180F6C,
};

#include "collect_gold.h"

#if defined VERSION_BETA || STAGE == STAGE_ST0
void func_801937BC(void) {}
void UnusedDestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }
#endif

#include "collect_subweapon.h"

#if STAGE != STAGE_ST0
#include "collect_heart_vessel.h"

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
#include "collect_dummy.h"
#endif

#include "entity_prize_drop.h"

extern u16 g_EInitParticle[];

#include "entity_explosion.h"

// Weird difference here. These functions are not related.
// But MAD has one and not the other.
#if !(defined VERSION_BETA || STAGE == STAGE_ST0)
#include "blink_item.h"
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

u16 g_ItemIconSlots[ICON_SLOT_NUM];

#include "entity_equip_item_drop.h"
