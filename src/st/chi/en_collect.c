/*
 * File: en_collect.c
 * Overlay: CHI
 * Description: ENTITY - Prize Collection
 */

#include "chi.h"

//TODO: Use ../e_collect.h

// [Duplicate]
// func_801A273C
void func_801A273C() {
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
// [Duplicate]
// func_801A27C0
void func_801A27C0(u16 arg0) {
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
        func_801A273C();
    }
}

// D_80181024
static u8 D_80181024[] = {0x01, 0x0E, 0x00};
// D_80181028
static u8 D_80181028[] = {
    0x02, 0x03, 0x06, 0x04, 0x05, 0x05, 0x05, 0x06, 0x04, 0x07, 0x03,
    0x08, 0x04, 0x09, 0x05, 0x0A, 0x05, 0x0B, 0x06, 0x0C, 0x07, 0x03,
    0x06, 0x04, 0x05, 0x05, 0x05, 0x06, 0x04, 0x07, 0x03, 0x08, 0x04,
    0x09, 0x05, 0x0A, 0x05, 0x0B, 0x06, 0x0C, 0x02, 0x0D, 0x00};
// D_80181054
static u8 D_80181054[] = {0x04, 0x14, 0x07, 0x15, 0x06, 0x16, 0x03, 0x17,
                          0x03, 0x18, 0x06, 0x19, 0x02, 0x15, 0x00, 0x00};
// D_80181064
static u8 D_80181064[] = {0x01, 0x1A, 0x00, 0x00};
// D_80181068
static u8 D_80181068[] = {0x01, 0x1B, 0x00, 0x00};
// D_8018106C
static u8 D_8018106C[] = {0x01, 0x1C, 0x00, 0x00};
// D_80181070
static u8 D_80181070[] = {0x01, 0x1D, 0x00, 0x00};
// D_80181074
static u8 D_80181074[] = {0x01, 0x1E, 0x00, 0x00};
// D_80181078
static u8 D_80181078[] = {0x01, 0x1F, 0x00, 0x00};
// D_8018107C
static u8 D_8018107C[] = {0x01, 0x20, 0x00, 0x00};
// D_80181080
static u8 D_80181080[] = {0x01, 0x21, 0x00, 0x00};
// D_80181084
static u8 D_80181084[] = {0x02, 0x22, 0x02, 0x23, 0x02, 0x24, 0x02, 0x25, 0x02,
                          0x26, 0x02, 0x27, 0x02, 0x28, 0x02, 0x29, 0x00, 0x00};
// D_80181098
static u8 D_80181098[] = {0x1A, 0x0F, 0x06, 0x10, 0x04, 0x11, 0x02,
                          0x12, 0x04, 0x11, 0x06, 0x10, 0x00, 0x00};
// D_801810A8
static u8 D_801810A8[] = {0x01, 0x13, 0x00, 0x00};
// D_801810AC
static u8 D_801810AC[] = {0x05, 0x2A, 0x05, 0x2B, 0x05, 0x2C, 0x05, 0x2D, 0x05,
                          0x2E, 0x05, 0x2F, 0x05, 0x30, 0x05, 0x31, 0x00, 0x00};
// D_801810C0
static u8 D_801810C0[] = {0x05, 0x32, 0x05, 0x33, 0x05, 0x34, 0x05, 0x35, 0x05,
                          0x36, 0x05, 0x37, 0x05, 0x38, 0x05, 0x39, 0x00, 0x00};
// D_801810D4
static u8 D_801810D4[] = {0x05, 0x3A, 0x05, 0x3B, 0x05, 0x3C, 0x05, 0x3D, 0x05,
                          0x3E, 0x05, 0x3F, 0x05, 0x40, 0x05, 0x41, 0x00, 0x00};
// D_801810E8
static u8 D_801810E8[] = {0x05, 0x42, 0x05, 0x43, 0x05, 0x44, 0x05, 0x45, 0x05,
                          0x46, 0x05, 0x47, 0x05, 0x48, 0x05, 0x49, 0x00, 0x00};
// D_801810FC
static u8 D_801810FC[] = {0x05, 0x4A, 0x05, 0x4B, 0x05, 0x4C, 0x05, 0x4D, 0x05,
                          0x4E, 0x05, 0x4F, 0x05, 0x50, 0x05, 0x51, 0x00, 0x00};
// D_80181110
static u8 D_80181110[] = {0x05, 0x52, 0x05, 0x53, 0x05, 0x54, 0x05, 0x55, 0x05,
                          0x56, 0x05, 0x57, 0x05, 0x58, 0x05, 0x59, 0x00, 0x00};
// D_80181124
static u8 D_80181124[] = {0x05, 0x5A, 0x05, 0x5B, 0x05, 0x5C, 0x05, 0x5D, 0x05,
                          0x5E, 0x05, 0x5F, 0x05, 0x60, 0x05, 0x61, 0x00, 0x00};
// D_80181138
static u8 D_80181138[] = {0x05, 0x62, 0x05, 0x63, 0x05, 0x64, 0x05, 0x65, 0x05,
                          0x66, 0x05, 0x67, 0x05, 0x68, 0x05, 0x69, 0x00, 0x00};
// D_8018114C
static u8 D_8018114C[] = {0x05, 0x6A, 0x05, 0x6B, 0x05, 0x6C, 0x05, 0x6D};
// Used in func_801A2A78
// D_80181154
static u16 D_80181154[] = {0x6E05, 0x6F05, 0x7005, 0x7105, 0};
// Used in func_801A2A78
// D_80181160
static u8 D_80181160[] = {
    0x01, 0x8F, 0x00, 0x00, 0xFC, 0xFC, 0x04, 0xFC, 0xFC, 0x04, 0x04, 0x04,
    0x80, 0x00, 0x00, 0x00 };

// D_80181170
static u16 aluric_subweapons_idx[] = {
    0x0001, 0x0002, 0x0004, 0x0003, 0x0006, 0x0005, 0x0007, 0x0008, 0x0009};

// Used in func_801A2A78
// Used in func_801A2CAC
// D_80181184
static u16 aluric_subweapons_id[] = {
    0x0000, 0x000E, 0x000F, 0x0011, 0x0010, 0x0013, 0x0012, 0x0014,
    0x0015, 0x0016
};

// D_80181198
const char* g_goldCollectTexts[] = {
    _S("$1"), _S("$25"), _S("$50"), _S("$100"),
    _S("$250"), _S("$400"), _S("$700"), _S("$1000"),
    _S("$2000"), _S("$5000"),
};

// D_801811C0
static u32 c_GoldPrizes[] = {
    0x00000001, 0x00000019, 0x00000032, 0x00000064,
    0x000000FA, 0x00000190, 0x000002BC, 0x000003E8,
    0x000007D0, 0x00001388
};
// Used in func_801A2CAC
// D_801811E8
static u8* g_SubweaponAnimPrizeDrop[] = {
    &D_80181024, &D_80181028, &D_80181054, &D_80181064,
    &D_80181068, &D_8018106C, &D_80181070, &D_80181074,
    &D_80181078, &D_8018107C, &D_80181080, &D_80181084,
    &D_80181098, &D_801810A8, &D_801810E8, &D_801810D4,
    &D_801810AC, &D_801810C0, &D_801810FC, &D_80181110,
    &D_80181124, &D_80181138, &D_8018114C, &D_80181160
};

// Used in func_801A2CAC
// Used in func_801A36C0
// D_80181248
static u8 D_80181248[] = {
    0xFA, 0xFF, 0x04, 0x00, 0x00, 0x00, 0xF8, 0xFF
};

// D_80181250
static s8 c_HeartPrizes[] = {
    0x01, 0x05, 0x00, 0x00
};

// Used in func_801A3520
// D_80181254
static s32 g_ExplosionYVelocities[] = {
    0xFFFF0000, 0xFFFE8000, 0xFFFE8000, 0xFFFE8000,
    0xFFFD0000, 0x02020102, 0x04020302, 0x06020502,
    0x08020702, 0x00000000
};

// [Does this need to be static after new file splits?]
// Used in func_801A62A0
// D_8018127C
u8 g_bigRedFireballAnim[] = {
    0x01, 0x09, 0x02, 0x0A, 0x02, 0x0B, 0x02, 0x0C, 0x02, 0x0D, 0x02, 0x0E, 0x02, 0x0F, 0x02, 0x10,
    0x02, 0x11, 0x02, 0x12, 0x03, 0x13, 0x04, 0x14, 0x00, 0x00, 0x00, 0x00, 0x02, 0x15, 0x02, 0x16,
    0x02, 0x17, 0x02, 0x18, 0x02, 0x19, 0x02, 0x1A, 0x02, 0x1B, 0x02, 0x1C, 0x02, 0x1D, 0x02, 0x1E,
    0x02, 0x1F, 0x02, 0x20, 0x02, 0x21, 0x02, 0x22, 0x02, 0x23, 0x02, 0x24, 0x02, 0x25, 0x02, 0x26,
    0x02, 0x27, 0x02, 0x28, 0x02, 0x29, 0x02, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x02, 0x2B, 0x02, 0x2C,
    0x02, 0x2D, 0x02, 0x2E, 0x02, 0x2F, 0x02, 0x30, 0x02, 0x31, 0x02, 0x32, 0x02, 0x33, 0x02, 0x34,
    0x02, 0x35, 0x02, 0x36, 0x02, 0x37, 0x02, 0x38, 0x02, 0x39, 0x02, 0x3A, 0x02, 0x3B, 0x02, 0x3C,
    0x02, 0x3D, 0x02, 0x3E, 0x02, 0x3F, 0x02, 0x40, 0x02, 0x41, 0x02, 0x42, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x43, 0x00, 0x00
};

// Used in func_801A3520
// D_80181300
static u8* g_ExplosionAnimations[] = {
    0x80181268, 0x8018127C, 0x80181298, 0x801812C8,
    0x801812FC
};

// [Duplicate]
// func_801A291C: CollectHeart
#include "../collect_heart.h"
// [Duplicate]
// func_801A299C: CollectGold
#include "../collect_gold.h"
// [Duplicate]
// [D_80181154 is supposed to be aluric_subweapons_idx?]
// func_801A2A78
void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(NA_SE_PL_IT_PICKUP);
    subWeapon = g_Status.subWeapon;
    g_Status.subWeapon = D_80181154[subWeaponIdx];

    if (subWeapon == g_Status.subWeapon) {
        subWeapon = 1;
        g_CurrentEntity->unk6D[0] = 0x10;
    } else {
        subWeapon = aluric_subweapons_id[subWeapon];
        g_CurrentEntity->unk6D[0] = 0x60;
    }

    if (subWeapon != 0) {
        g_CurrentEntity->params = subWeapon;
        g_CurrentEntity->posY.i.hi = player->posY.i.hi + 12;
        SetStep(7);
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
// [Duplicate]
// func_801A2B90: CollectHeartVessel
#include "../collect_heart_vessel.h"
// [Duplicate]
// func_801A2C34
void CollectLifeVessel(void) {
    g_api.PlaySfx(SFX_HEART_PICKUP);
    g_api.func_800FE044(LIFE_VESSEL_INCREASE, 0x8000);
    DestroyEntity(g_CurrentEntity);
}
// [Duplicate]
// func_801A2C84
void DestroyCurrentEntity(u16 id) { DestroyEntity(g_CurrentEntity); }

extern u16 g_InitializeData0[];

// [Duplicate]
// E_PRIZE_DROP
// func_801A2CAC
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
                g_CastleFlags[(index >> 3) + COLLECT_FLAGS_START] |=
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
            CheckFieldCollision(D_80181248, 2);
        } else if (collider.effects & EFFECT_NOTHROUGH) {
            self->posY.i.hi += collider.unk18;
            self->ext.equipItemDrop.aliveTimer = 0x60;
            self->step++;
        } else {
            func_801A273C();
        }
        break;
    case 3:
        func_801A27C0(itemId);
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
        func_801A27C0(itemId);
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
            CheckFieldCollision(D_80181248, 2);
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
            func_801A27C0(itemId);
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
// [Duplicate]
// func_801A3520: [E_EXPLOSION] EntityExplosion
#include "../entity_explosion.h"
// func_801A361C: BlinkItem
#include "../blink_item.h"
extern s32 D_80097410;
extern s32 D_80097414;
extern u16 g_ItemIconSlots[];
//u16 g_ItemIconSlots[ICON_SLOT_NUM];
// [Duplicate]
// E_EQUIP_ITEM_DROP
// func_801A36C0
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
            g_CastleFlags[(index >> 3) + COLLECT_FLAGS_START] |=
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
        CheckFieldCollision(D_80181248, 2);
        break;
    case 3:
        func_801A27C0(1);
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
        func_801A27C0(1);
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
//TODO: I think the above SHOULD all match e_collect.h, but e_collect.h contains D_######## (and func_########?) symbol names that need to be named better
//#include "../e_collect.h"