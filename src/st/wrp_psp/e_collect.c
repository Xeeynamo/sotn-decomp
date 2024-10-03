// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../wrp/wrp.h"
#include <sfx.h>

static u8 D_80180C94[] = {0x01, 0x0E, 0x00};
static u8 D_80180C98[] = {
    0x02, 0x03, 0x06, 0x04, 0x05, 0x05, 0x05, 0x06, 0x04, 0x07, 0x03,
    0x08, 0x04, 0x09, 0x05, 0x0A, 0x05, 0x0B, 0x06, 0x0C, 0x07, 0x03,
    0x06, 0x04, 0x05, 0x05, 0x05, 0x06, 0x04, 0x07, 0x03, 0x08, 0x04,
    0x09, 0x05, 0x0A, 0x05, 0x0B, 0x06, 0x0C, 0x02, 0x0D, 0x00};
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
static u8 D_80180D1C[] = {0x05, 0x2A, 0x05, 0x2B, 0x05, 0x2C, 0x05, 0x2D, 0x05,
                          0x2E, 0x05, 0x2F, 0x05, 0x30, 0x05, 0x31, 0x00, 0x00};
static u8 D_80180D30[] = {0x05, 0x32, 0x05, 0x33, 0x05, 0x34, 0x05, 0x35, 0x05,
                          0x36, 0x05, 0x37, 0x05, 0x38, 0x05, 0x39, 0x00, 0x00};
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
static u8 D_80180DBC[] = {
    0x05, 0x6A, 0x05, 0x6B, 0x05, 0x6C, 0x05, 0x6D, 0x05, 0x6E, 0x05, 0x6F,
    0x05, 0x70, 0x05, 0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static u8 D_80180DD0[] = {0x01, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static u16 aluric_subweapons_idx[] = {1, 2, 4, 3, 6, 5, 7, 8, 9};
static u16 aluric_subweapons_id[] = {0, 14, 15, 17, 16, 19, 18, 20, 21, 22};
static u8* g_SubweaponAnimPrizeDrop[] = {
    D_80180C94, D_80180C98, D_80180CC4, D_80180CD4, D_80180CD8, D_80180CDC,
    D_80180CE0, D_80180CE4, D_80180CE8, D_80180CEC, D_80180CF0, D_80180CF4,
    D_80180D08, D_80180D18, D_80180D58, D_80180D44, D_80180D1C, D_80180D30,
    D_80180D6C, D_80180D80, D_80180D94, D_80180DA8, D_80180DBC, D_80180DD0,
};

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

static char D_psp_09246458[] = {0x04, 0x11, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00};
static u32 D_psp_09246460[] = {0xFF151204, 0x00000000};
static u32 D_psp_09246468[] = {0xFF101504, 0x00000000};
static u32 D_psp_09246470[] = {0x10101104, 0x000000FF};
static u32 D_psp_09246478[] = {0x10151204, 0x000000FF};
static u32 D_psp_09246480[] = {0x10101404, 0x000000FF};
static u32 D_psp_09246488[] = {0x10101704, 0x000000FF};
static u32 D_psp_09246490[] = {0x10101104, 0x0000FF10};
static u32 D_psp_09246498[] = {0x10101204, 0x0000FF10};
static u32 D_psp_092464A0[] = {0x10101504, 0x0000FF10};
static const char* g_goldCollectTexts[] = {
    (const char*)D_psp_09246458, (const char*)D_psp_09246460,
    (const char*)D_psp_09246468, (const char*)D_psp_09246470,
    (const char*)D_psp_09246478, (const char*)D_psp_09246480,
    (const char*)D_psp_09246488, (const char*)D_psp_09246490,
    (const char*)D_psp_09246498, (const char*)D_psp_092464A0,
};

static u32 c_GoldPrizes[] = {1, 25, 50, 100, 250, 400, 700, 1000, 2000, 5000};
static s16 D_80180EB8[] = {-6, 4, 0, -8};
static s8 c_HeartPrizes[] = {1, 5};
static s32 g_ExplosionYVelocities[] = {
    FIX(-1.0), FIX(-1.5), FIX(-1.5), FIX(-1.5), FIX(-3.0)};

#include "../prize_drop_fall.h"

#include "../prize_drop_fall2.h"

#include "../collect_heart.h"

#include "../collect_gold.h"

extern u16 D_80180DC4[];
extern u32 D_091CF6DC;
extern u32 D_091CF698;
static void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(SFX_ITEM_PICKUP);

    if (g_PlayableCharacter == PLAYER_MARIA) {
        subWeapon = D_091CF6DC;
    } else {
        subWeapon = D_091CF698;
    }

    if (g_PlayableCharacter == PLAYER_MARIA) {
        D_091CF6DC = maria_subweapons_idx[subWeaponIdx - 14];
        func_90E4C90();
    } else {
        D_091CF698 = aluric_subweapons_idx[subWeaponIdx - 14];
    }

    if (g_PlayableCharacter != PLAYER_MARIA && subWeapon == D_091CF698 ||
        g_PlayableCharacter == PLAYER_MARIA && subWeapon == D_091CF6DC) {
        subWeapon = 1;
        g_CurrentEntity->unk6D[0] = 0x10;
    } else {
        if (g_PlayableCharacter == PLAYER_MARIA) {
            subWeapon = maria_subweapons_id[subWeapon];
        } else {
            subWeapon = aluric_subweapons_id[subWeapon];
        }
        g_CurrentEntity->unk6D[0] = 0x60;
    }

    if (subWeapon) {
        g_CurrentEntity->params = subWeapon;
        g_CurrentEntity->posY.i.hi = player->posY.i.hi + 12;
        SetStep(7);
        g_CurrentEntity->velocityY = FIX(-2.5);
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->ext.equipItemDrop.unk8A = 5;
        if (player->facingLeft ^ 1) {
            g_CurrentEntity->velocityX = FIX(-2);
            return;
        }
        g_CurrentEntity->velocityX = FIX(2);
        return;
    }
    DestroyEntity(g_CurrentEntity);
}

#include "../collect_heart_vessel.h"

static void CollectLifeVessel(void) {
    g_api.PlaySfx(SFX_HEART_PICKUP);
    g_api.func_800FE044(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

static void CollectDummy(u16 id) { DestroyEntity(g_CurrentEntity); }

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
#if defined(VERSION_PSP)
    if (self->step && self->step < 5 && self->hitFlags) {
#else
    if (self->step > 1 && self->step < 5 && self->hitFlags) {
#endif
        self->step = 5;
    }
    self->palette = 0;
    if ((u8)self->unk6D[0] >= 0x18 && !(g_GameTimer & 2) && self->params != 1) {
        self->palette = 0x815F;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeData0);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        self->drawMode = DRAW_DEFAULT;
        if (itemId > 23) {
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
            index = self->ext.equipItemDrop.castleFlag;
            if (index) {
                index--;
                g_CastleFlags[(index >> 3) + COLLECT_FLAGS_START] |=
                    1 << (index & 7);
            }
        }
        if (!itemId) {
            self->ext.equipItemDrop.fallSpeed = FIX(-1);
            self->ext.equipItemDrop.gravity = 0x800;
        }
        break;
    case 2:
        if (self->velocityY < 0) {
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
        } else if (itemId == 12) {
            CollectHeartVessel();
        } else if (itemId < 14) {
            CollectDummy(itemId);
        } else if (itemId < 23) {
            CollectSubweapon(itemId);
        } else if (itemId == 23) {
            CollectLifeVessel();
        } else {
            DestroyEntity(self);
            return;
        }
        break;
    case 6:
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
                prim->u0 = prim->u2 = prim->v0 = prim->v1 = 0;
                prim->u1 = prim->u3 = prim->v2 = prim->v3 = 0x20;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 =
                    prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                        prim->b2 = prim->b3 = 128;
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

#include "../entity_explosion.h"

#include "../blink_item.h"

u16 g_ItemIconSlots[ICON_SLOT_NUM];

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", EntityEquipItemDrop);
