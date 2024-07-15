#include "../wrp/wrp.h"
#include <sfx.h>

extern u8* g_MariaSubweaponAnimPrizeDrop[];
extern u8* g_SubweaponAnimPrizeDrop[];
extern s16 D_80180EB8[];

void func_8018CAB0(void) {
    if (g_CurrentEntity->velocityY >= 0) {
        g_CurrentEntity->ext.generic.unk84.unk +=
            g_CurrentEntity->ext.generic.unk88.S16.unk0;
        g_CurrentEntity->velocityX = g_CurrentEntity->ext.generic.unk84.unk;
        if (g_CurrentEntity->velocityX == FIX(1) ||
            g_CurrentEntity->velocityX == FIX(-1)) {
            g_CurrentEntity->ext.generic.unk88.S16.unk0 =
                -g_CurrentEntity->ext.generic.unk88.S16.unk0;
        }
    }

    if (g_CurrentEntity->velocityY < FIX(0.25)) {
        g_CurrentEntity->velocityY += FIX(0.125);
    }
}

void func_8018CB34(u16 arg0) {
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
        func_8018CAB0();
    }
}

extern s8 c_HeartPrizes[];

#include "../collect_heart.h"

#include "../collect_gold.h"

extern u16 D_80180DC4[];
extern u16 D_80180DF4[];
extern u32 D_091CF6DC;
extern u32 D_091CF698;
extern u16 g_MariaWeaponData1[];
extern u16 D_psp_092462E0[];
extern u16 g_MariaWeaponData0[];
extern u16 D_80180DF4[];
void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(NA_SE_PL_IT_PICKUP);

    if (g_PlayableCharacter == PLAYER_MARIA) {
        subWeapon = D_091CF6DC;
    } else {
        subWeapon = D_091CF698;
    }

    if (g_PlayableCharacter == PLAYER_MARIA) {
        D_091CF6DC = g_MariaWeaponData0[subWeaponIdx - 0xe];
        func_90E4C90();
    } else {
        D_091CF698 = D_psp_092462E0[subWeaponIdx - 0xe];
    }

    if (g_PlayableCharacter != PLAYER_MARIA && subWeapon == D_091CF698 ||
        g_PlayableCharacter == PLAYER_MARIA && subWeapon == D_091CF6DC) {
        subWeapon = 1;
        g_CurrentEntity->unk6D[0] = 0x10;
    } else {
        if (g_PlayableCharacter == PLAYER_MARIA) {
            subWeapon = g_MariaWeaponData1[subWeapon];
        } else {
            subWeapon = D_80180DF4[subWeapon];
        }
        g_CurrentEntity->unk6D[0] = 0x60;
    }

    if (subWeapon) {
        g_CurrentEntity->params = subWeapon;
        g_CurrentEntity->posY.i.hi = player->posY.i.hi + 12;
        SetStep(7);
        g_CurrentEntity->velocityY = FIX(-2.5);
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->ext.generic.unk88.S16.unk2 = 5;
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

void CollectLifeVessel(void) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api.func_800FE044(5, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void DestroyCurrentEntity(u16 id) { DestroyEntity(g_CurrentEntity); }

void EntityPrizeDrop(Entity* self) {
    Collider collider;
    Primitive* prim;
    u16 itemId;
    s16 index;
    s32 primIndex;
    s32 subWeaponId;
    s32 subWeaponId_;

    // if self->params & 0x8000 then the item will not disappear
    // self->ext.generic.unk80.modeS8.unk0: frames left before the prize
    // disappear
    itemId = self->params & 0x7FFF;
    if (self->step) {
        if (g_PlayableCharacter == PLAYER_MARIA) {
            AnimateEntity(g_MariaSubweaponAnimPrizeDrop[itemId], self);
        } else {
            AnimateEntity(g_SubweaponAnimPrizeDrop[itemId], self);
        }
    }
    if (self->step && self->step < 5 && self->hitFlags) {
        self->step = 5;
    }
    self->palette = 0;
    if ((u8)self->unk6D[0] >= 0x18 && !(g_GameTimer & 2) && self->params != 1) {
        self->palette = 0x815F;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_InitializeData0);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter.unk - 0x14;
        self->drawMode = DRAW_DEFAULT;
        if (itemId > 23) {
            itemId = self->params = 0;
        }

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
        if (itemId >= 14 && itemId < 23 &&
            g_PlayableCharacter != PLAYER_MARIA) {
            subWeaponId_ = D_80180DF4[g_Status.subWeapon];
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
            index = LOW(self->ext.generic.unk94);
            if (index) {
                index--;
                g_CastleFlags[(index >> 3) + 0x1b0] |= 1 << (index & 7);
            }
        }
        if (!itemId) {
            self->ext.generic.unk84.unk = -0x10000;
            self->ext.generic.unk88.S16.unk0 = 0x800;
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
                self->ext.generic.unk80.modeS8.unk0 = 0xF0;
                self->step++;
            } else {
                FallEntity();
            }
            CheckFieldCollision(D_80180EB8, 2);
        } else if (collider.effects & EFFECT_NOTHROUGH) {
            self->posY.i.hi += collider.unk18;
            self->ext.generic.unk80.modeS8.unk0 = 0x60;
            self->step++;
        } else {
            func_8018CAB0();
        }
        break;
    case 3:
        func_8018CB34(itemId);
        if (!(self->params & 0x8000) &&
            !--self->ext.generic.unk80.modeS8.unk0) {
            if (itemId) {
                self->ext.generic.unk80.modeS8.unk0 = 0x50;
            } else {
                self->ext.generic.unk80.modeS8.unk0 = 0x40;
            }
            self->step++;
        }
        break;
    case 4:
        func_8018CB34(itemId);
        if (--self->ext.generic.unk80.modeS8.unk0) {
            if (self->ext.generic.unk80.modeS8.unk0 & 2) {
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
            DestroyCurrentEntity(itemId);
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
                if (g_PlayableCharacter == PLAYER_MARIA) {
                    subWeaponId = g_MariaWeaponData1[g_Status.mariaSubWeapon];
                    if (itemId == subWeaponId) {
                        itemId = 1;
                        self->params = 1;
                    }
                } else {
                    subWeaponId = D_80180DF4[g_Status.subWeapon];
                    if (itemId == subWeaponId) {
                        itemId = 1;
                        self->params = 1;
                    }
                }
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
            if (self->ext.generic.unk88.S16.unk2) {
                self->ext.generic.unk88.S16.unk2--;
            } else {
                prim = &g_PrimBuf[self->primIndex];
                prim->x0 = prim->x2 = self->posX.i.hi - 1;
                prim->x1 = prim->x3 = self->posX.i.hi + 1;
                prim->y0 = prim->y1 = self->posY.i.hi - 1;
                prim->y2 = prim->y3 = self->posY.i.hi + 1;
                prim->drawMode = 0x37;
            }
            break;
        case 2:
            func_8018CB34(itemId);
            prim = &g_PrimBuf[self->primIndex];
            self->ext.generic.unk88.S16.unk2++;
            if (self->ext.generic.unk88.S16.unk2 < 0x11) {
                index = self->ext.generic.unk88.S16.unk2;
                self->animCurFrame = 0;
            } else {
                index = 0x20 - self->ext.generic.unk88.S16.unk2;
                prim->r0 = (prim->r1 = (prim->r2 = (prim->r3 -= 8)));
                prim->g0 = (prim->g1 = (prim->g2 = (prim->g3 -= 8)));
                prim->b0 = (prim->b1 = (prim->b2 = (prim->b3 -= 8)));
            }
            prim->x0 = prim->x2 = self->posX.i.hi - index;
            prim->x1 = prim->x3 = self->posX.i.hi + index;
            prim->y0 = prim->y1 = self->posY.i.hi - index;
            prim->y2 = prim->y3 = self->posY.i.hi + index;
            if (self->ext.generic.unk88.S16.unk2 == 0x20) {
                g_api.FreePrimitives(self->primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
                self->ext.generic.unk80.modeS8.unk0 = 0xD0;
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

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", EntityEquipItemDrop);
