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
static const char* g_goldCollectTexts[] = {
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
#if defined VERSION_BETA || STAGE == STAGE_ST0
// This is weird, the values have to go in later.
// Note that this array is in rodata. Other overlays have it in data.
static const s8 c_HeartPrizes[2][2];
#else
static s8 c_HeartPrizes[] = {1, 5};
#endif

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

// from another file
extern u16 g_InitializeData0[];

static void func_8018CAB0(void) {
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

static void func_8018CB34(u16 arg0) {
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
        } else {
            g_CurrentEntity->posY.i.hi += collider.unk18;
        }
    } else {
        if (!(collider.effects & EFFECT_NOTHROUGH)) {
            MoveEntity();
            func_8018CAB0();
        }
    }
}
#include "collect_heart.h"

#if defined VERSION_BETA || STAGE == STAGE_ST0
// For some reason need to declare the values AFTER the function.
static const s8 c_HeartPrizes[2][2] = {{1, 5}, {0, 0}, {1, 2}, {0, 0}};
#endif

#include "collect_gold.h"

#if defined VERSION_BETA || STAGE == STAGE_ST0
void func_801937BC(void) {}
void UnusedDestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }
#endif

static void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(SFX_ITEM_PICKUP);
    subWeapon = g_Status.subWeapon;
    g_Status.subWeapon = aluric_subweapons_idx[subWeaponIdx - 14];

    if (subWeapon == g_Status.subWeapon) {
        subWeapon = 1;
        g_CurrentEntity->unk6D[0] = 0x10;
    } else {
        subWeapon = aluric_subweapons_id[subWeapon];
        g_CurrentEntity->unk6D[0] = 0x60;
    }

    if (subWeapon) {
        g_CurrentEntity->params = subWeapon;
        g_CurrentEntity->posY.i.hi = player->posY.i.hi + 12;
#if defined VERSION_BETA || STAGE == STAGE_ST0
        g_CurrentEntity->step = 7;
        g_CurrentEntity->step_s = 0;
#else
        SetStep(7);
#endif
        g_CurrentEntity->velocityY = FIX(-2.5);
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->ext.equipItemDrop.unk8A = 5;
        if (player->facingLeft != 1) {
            g_CurrentEntity->velocityX = FIX(-2);
            return;
        }
        g_CurrentEntity->velocityX = FIX(2);
        return;
    }
    DestroyEntity(g_CurrentEntity);
}

#if STAGE != STAGE_ST0
#include "collect_heart_vessel.h"

static void CollectLifeVessel(void) {
    g_api.PlaySfx(SFX_HEART_PICKUP);
    g_api.func_800FE044(LIFE_VESSEL_INCREASE, 0x8000);
    DestroyEntity(g_CurrentEntity);
}
#endif

// MAD doesn't take an argument, others do
#if defined VERSION_BETA || STAGE == STAGE_ST0
static void DestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }
// Extra unused function, putting it in this same if-block.
Entity* func_801939C4(void) {
    g_CurrentEntity->step = 3;
    g_CurrentEntity->params = 4;
    return g_CurrentEntity;
}
#else
static void DestroyCurrentEntity(u16 id) { DestroyEntity(g_CurrentEntity); }
#endif

// if self->params & 0x8000 then the item will not disappear
void EntityPrizeDrop(Entity* self) {
    Collider collider;
    Primitive* prim;
    u16 itemId;
    s16 index;
    s32 primIndex;
    s32 subWeaponId;
    s32 subWeaponId_;

    // if self->params & 0x8000 then the item will not disappear
    itemId = self->params & 0x7FFF;
    if (self->step) {
#if defined(VERSION_PSP)
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
    if ((u8)self->unk6D[0] >= 0x18 && !(g_GameTimer & 2) && self->params != 1) {
        self->palette = 0x815F;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeData0);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        self->drawMode = DRAW_DEFAULT;
#if STAGE == STAGE_ST0
        if (itemId >= 23) {
#else
        if (itemId > 23) {
#endif
            itemId = self->params = 0;
        }

#if defined(VERSION_PSP)
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
                itemId = 19; // causes a lot of regswaps
                self->params = 19;
                break;
            default:
                itemId = self->params = 0;
                break;
            }
        }
#endif
        if (itemId >= 14 && itemId < 23
#if defined(VERSION_PSP)
            && g_PlayableCharacter != PLAYER_MARIA
#endif
        ) {
            subWeaponId_ = aluric_subweapons_id[g_Status.subWeapon];
            if (itemId == subWeaponId_) {
                itemId = 1;
                self->params = 1;
            }
        }
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
#if !(defined VERSION_BETA || STAGE == STAGE_ST0)
            index = self->ext.equipItemDrop.castleFlag;
            if (index) {
                index--;
                g_CastleFlags[(index >> 3) + COLLECT_FLAGS_START] |= 1 << (index & 7);
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
            func_8018CAB0();
        }
        break;
    case 3:
        func_8018CB34(itemId);
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
        func_8018CB34(itemId);
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
#if defined VERSION_BETA || STAGE == STAGE_ST0
            DestroyCurrentEntity();
#else
            DestroyCurrentEntity(itemId);
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
#if !(defined VERSION_BETA || STAGE == STAGE_ST0)
    case 6:
#endif
    case 7:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0;
            if (itemId >= 14 && itemId < 23) {
#if defined(VERSION_PSP)
                if (g_PlayableCharacter == PLAYER_MARIA) {
                    subWeaponId = maria_subweapons_id[g_Status.mariaSubWeapon];
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
#else
                subWeaponId = aluric_subweapons_id[g_Status.subWeapon];
                if (itemId == subWeaponId) {
                    itemId = 1;
                    self->params = 1;
                }
#endif
            }
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (primIndex != -1) {
                self->primIndex = primIndex;
                self->flags |= FLAG_HAS_PRIMS;
                prim = &g_PrimBuf[primIndex];
                prim->tpage = 0x1A;
                prim->clut = 0x170;
#if defined VERSION_BETA || STAGE == STAGE_ST0
                prim->u0 = prim->u2 = 0;
                prim->v0 = prim->v1 = 0;
                prim->u1 = prim->u3 = 0x20;
                prim->v2 = prim->v3 = 0x20;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0x80;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
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
            func_8018CB34(itemId);
            prim = &g_PrimBuf[self->primIndex];
            self->ext.equipItemDrop.unk8A++;
            if (self->ext.equipItemDrop.unk8A < 17) {
                index = self->ext.equipItemDrop.unk8A;
                self->animCurFrame = 0;
            } else {
                index = 32 - self->ext.equipItemDrop.unk8A;
                prim->r0 = (prim->r1 = (prim->r2 = (prim->r3 -= 8)));
                prim->g0 = (prim->g1 = (prim->g2 = (prim->g3 -= 8)));
                prim->b0 = (prim->b1 = (prim->b2 = (prim->b3 -= 8)));
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

extern u16 g_InitializeEntityData0[];

#include "entity_explosion.h"

// Weird difference here. These functions are not related.
// But MAD has one and not the other.
#if !(defined VERSION_BETA || STAGE == STAGE_ST0)
#include "blink_item.h"
#else
// Also, this function is never called.
void func_80194314(Entity* entity) {
    if (entity->step != 0) {
        if (entity->posY.i.hi >= 0xF1) {
            DestroyEntity(entity);
            return;
        }
        FallEntity();
        MoveEntity();
        return;
    }

    InitializeEntity(g_eBreakableInit);
    entity->animCurFrame = entity->ext.generic.unk7C.U8.unk0;
    entity->velocityX =
        g_collectXVelTable[entity->ext.generic.unk80.modeS8.unk0 * 2];
    entity->velocityY =
        g_collectYVelTable[entity->ext.generic.unk80.modeS8.unk0 * 2];

    if (entity->params != 0) {
        entity->zPriority -= 1;
    }
}
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
    s32 xPos, yPos; // only used in MAD

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
        InitializeEntity(g_InitializeData0);
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
            g_CastleFlags[(index >> 3) + COLLECT_FLAGS_START] |= 1 << (index & 7);
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
        prim->u0 = prim->u2 = (u8)(i & 7) * 0x10 + 1;
        prim->u1 = prim->u3 = prim->u0 + 0xE;
        prim->v0 = prim->v1 = (u8)(i & 0x18) * 2 + 0x81;
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
        func_8018CB34(1);
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
        func_8018CB34(1);
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
        xPos = (u16)self->posX.i.hi;
        prim->x0 = prim->x2 = xPos - 7;
        prim->x1 = prim->x3 = xPos + 7;
        yPos = (u16)self->posY.i.hi;
        prim->y0 = prim->y1 = yPos - 7;
        prim->y2 = prim->y3 = yPos + 7;
        if (self->ext.equipItemDrop.timer) {
            self->ext.equipItemDrop.timer--;
            if (!(self->ext.equipItemDrop.timer & 2)) {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = 0x80;
            } else {
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = 0xFF;
            }
        }
#endif
    }
}
