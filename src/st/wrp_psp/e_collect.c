#include "../wrp/wrp.h"
#include <sfx.h>

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
void CollectHeart(u16 arg0) {
    s32* hearts;

    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_Status.hearts += c_HeartPrizes[arg0];

    if (g_Status.hearts > g_Status.heartsMax) {
        g_Status.hearts = g_Status.heartsMax;
    }

    DestroyEntity(g_CurrentEntity);
}

#include "../collect_gold.h"

extern u16 D_80180DC4[];
extern u16 D_80180DF4[];
extern s32 D_091CF020;
extern u32 D_091CF6DC;
extern u32 D_091CF698;
extern u16 D_psp_09246370[];
extern u16 D_psp_092462E0[];
extern u16 D_psp_09246388[];
extern u16 D_psp_092462F8[];
void CollectSubweapon(u16 subWeaponIdx) {
    Entity* player = &PLAYER;
    u16 subWeapon;

    g_api.PlaySfx(NA_SE_PL_IT_PICKUP);

    if (D_091CF020 == 2) {
        subWeapon = D_091CF6DC;
    } else {
        subWeapon = D_091CF698;
    }

    if (D_091CF020 == 2) {
        D_091CF6DC = D_psp_09246370[subWeaponIdx - 0xe];
        func_90E4C90();
    } else {
        D_091CF698 = D_psp_092462E0[subWeaponIdx - 0xe];
    }

    if (D_091CF020 != 2 && subWeapon == D_091CF698 ||
        D_091CF020 == 2 && subWeapon == D_091CF6DC) {
        subWeapon = 1;
        g_CurrentEntity->unk6D[0] = 0x10;
    } else {
        if (D_091CF020 == 2) {
            subWeapon = D_psp_09246388[subWeapon];
        } else {
            subWeapon = D_psp_092462F8[subWeapon];
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

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", DestroyCurrentEntity);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", EntityPrizeDrop);

extern u16 D_80180458[];
extern s32 D_80180EC4[];
extern u8* D_80180F70[];
void EntityExplosion(Entity* entity) {
    if (!entity->step) {
        InitializeEntity(D_80180458);
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->animSet = ANIMSET_DRA(2);
        entity->drawMode = 0x30;
        if (entity->params & 0xF0) {
            entity->palette = 0x8195;
            entity->drawMode = DRAW_TPAGE;
        }

        if (entity->params & 0xFF00) {
            entity->zPriority = (entity->params & 0xFF00) >> 8;
        }
        entity->params &= 15;
        entity->velocityY = D_80180EC4[entity->params];
    } else {
        entity->posY.val += entity->velocityY;
        if (!AnimateEntity(D_80180F70[entity->params], entity)) {
            DestroyEntity(entity);
        }
    }
}

void BlinkItem(Entity* self, u16 renderFlags) {
    Primitive* prim;
    s32 temp;
    prim = &g_PrimBuf[self->primIndex];

    prim->x0 = prim->x2 = self->posX.i.hi - 7;
    prim->x1 = prim->x3 = prim->x0 + 14;

    prim->y0 = prim->y1 = self->posY.i.hi - 7;
    prim->y2 = prim->y3 = prim->y0 + 14;

    if (renderFlags & RENDERFLAGS_NOSHADOW) {
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 =
                255;
    } else {
        prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
            prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 =
                128;
    }
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_collect", EntityEquipItemDrop);
