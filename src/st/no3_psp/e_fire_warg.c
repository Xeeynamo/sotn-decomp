// SPDX-License-Identifier: AGPL-3.0-or-later

#include "../no3/no3.h"

static void func_801CC5A4(Entity* entity, u8 count, u8 params, s16 xDist,
                          s16 yDist, u8 arg5, s16 xOfst) {
    s32 i;
    s16 x = entity->posX.i.hi + xDist;
    s16 y = entity->posY.i.hi + yDist;

    for (i = 0; i < count; ++i) {
        Entity* newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEnt != NULL) {
            newEnt->entityId = E_EXPLOSION_VARIANTS;
            newEnt->pfnUpdate = EntityExplosionVariants;
            newEnt->params = params;
            newEnt->posX.i.hi = x + i * xOfst;
            newEnt->posY.i.hi = y;
            newEnt->ext.destructAnim.index = D_80182A48[i];
            newEnt->rotX = D_80182A38[D_80182A48[i] + arg5];
            newEnt->rotY = newEnt->rotX;
            newEnt->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
            newEnt->zPriority = entity->zPriority + 1;
        }
    }
}

static void func_801CC6F8(Entity* self) {
    u16 distance = GetDistanceToPlayerX();
    bool buttNearScreenEdge;

    self->velocityX = 0;
    self->ext.fireWarg.unk86 = 0x100;

    if (self->params) {
        SetStep(12);
        return;
    }

    // This will test if we're facing left, with high X, or facing right with
    // low X.
    buttNearScreenEdge = false;
    if (self->facingLeft) {
        if (self->posX.i.hi > 0x70) {
            buttNearScreenEdge = true;
        }
    } else {
        if (self->posX.i.hi < 0x90) {
            buttNearScreenEdge = true;
        }
    }

    if (distance < 0x70) {
        if (!(Random() & 3) && !buttNearScreenEdge) {
            SetStep(9);
        } else {
            SetStep(6);
            PlaySfxPositional(SFX_WARG_GROWL);
            self->ext.fireWarg.unk80 = 0x20;
        }
    } else {
        if ((Random() & 3) && !buttNearScreenEdge) {
            SetStep(9);
            if (!(Random() & 3)) {
                self->ext.fireWarg.unk86 = 0;
            }
        } else {
            SetStep(6);
            PlaySfxPositional(SFX_WARG_GROWL);
            self->ext.fireWarg.unk80 = 0x20;
        }
    }
}

// Only called by the EntityFireWarg
static void func_801CC820(Entity* self) {
    u16 distance;

    if ((self->facingLeft == GetSideToPlayer()) & 1) {
        if (self->params) {
            SetStep(4);
        } else {
            SetStep(5);
        }
        return;
    }
    if (!self->ext.fireWarg.unk86) {
        func_801CC6F8(self);
        return;
    }
    distance = GetDistanceToPlayerX();
    if ((distance < 0x48) && (self->step != 4)) {
        SetStep(4);
        return;
    }
    SetStep(3);
    if (distance < 0x60) {
        self->ext.fireWarg.unk7C = 1;
    } else {
        self->ext.fireWarg.unk7C = 0;
    }
    self->ext.fireWarg.unk80 = 0;
    self->ext.fireWarg.unk82 = 0x20;
}

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", func_pspeu_09249878);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityFireWarg);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityUnkId30);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityUnkId31);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityExplosion3);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", func_pspeu_0924C7A8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityFireWargWaveAttack);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityUnkId2F);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityFireWargDeathBeams);
