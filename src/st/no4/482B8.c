// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

#ifdef VERSION_PSP
extern s32 E_ID(SPEAR_GUARD_BLOCK);
#endif

static u8 D_us_80181804[] = {
    63, 60, 56, 52, 48, 44, 40, 36, 32, 28, 24, 20, 16, 12, 8, 4,
};

static Point16 D_us_80181814[] = {
    {-8, -4}, {8, -6},  {-12, 4},  {-1, -7}, {6, 16},   {11, -3},
    {10, 12}, {3, -2},  {-8, -8},  {10, -6}, {-12, 18}, {-8, -16},
    {6, 4},   {10, 20}, {-11, 22}, {8, -2},
};

// unused
static u8 D_us_80181854[] = {
    11, 5, 1, 5, 12, 4, 0, 0,
};

static u8 D_us_8018185C[] = {
    8, 62, 8, 63, 8, 64, 8, 63, 8, 64, 8, 63, 8, 64, -1, 0,
};

static u8 D_us_8018186C[] = {
    15, 41, 3, 42, 3, 43, 3, 44, 22, 45, 2, 44, 2, 43, 2, 42, 6, 41, 0, 0,
};

void func_us_801C82B8(Entity* self) {
    Entity* newEnt;
    u8 animStatus;
    u8 i;

    newEnt = self + 1;
    if (self->step && !self->ext.spearGuard.unk90) {
        newEnt->attack = self->attack;
        newEnt->attackElement = self->attackElement;
    }

    if (self->step && self->step < 5 &&
        (self->flags & FLAG_DEAD || g_CastleFlags[NO4_WATER_BLOCKED] > 2)) {
        DestroyEntity(newEnt);
        SetStep(5);
        self->hitboxState = 0;
        self->ext.spearGuard.unk7C = 64;
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = 0x7F;
    }

    if (self->step && self->step < 4 && g_CastleFlags[NO4_WATER_BLOCKED] > 1) {
        SetStep(4);
        self->animCurFrame = 31;
        self->ext.spearGuard.unk7C = 0;
    }

    switch (self->step) {
    case 0:
        if (g_CastleFlags[NO4_WATER_BLOCKED] > 2) {
            DestroyEntity(self);
            return;
        }
        InitializeEntity(g_EInitSpearGuard);
        self->ext.spearGuard.unk80 = 176;
        self->ext.spearGuard.unk7C = 64;
        self->palette += 2;
        self->hitboxOffY = 4;
        CreateEntityFromCurrentEntity(E_ID(SPEAR_GUARD_BLOCK), newEnt);
        self->ext.spearGuard.unk7C = self->params * 8;
        self->animCurFrame = 5;
        break;

    case 1:
        if (self->ext.spearGuard.unk7C) {
            self->ext.spearGuard.unk7C--;
        } else {
            self->step++;
            self->ext.spearGuard.unk7C = 1;
        }
        break;

    case 2:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (!--self->ext.spearGuard.unk7C) {
            SetStep(3);
        }
        break;

    case 3:
        animStatus = AnimateEntity(D_us_8018186C, self);
        newEnt->attack = g_api.enemyDefs[94].attack;
        newEnt->attackElement = g_api.enemyDefs[94].attackElement;
        if (!animStatus) {
            SetStep(2);
            self->ext.spearGuard.unk7C = 1;
        } else if (animStatus & 0x80 && self->animCurFrame == 45) {
            PlaySfxPositional(SFX_WEAPON_SWISH_B);
        }
        break;

    case 4:
        if (self->ext.spearGuard.unk7C) {
            self->ext.spearGuard.unk7C--;
        } else {
            self->facingLeft ^= 1;
            self->ext.spearGuard.unk7C = (rand() & 7) + 4;
        }
        break;

    case 5:
        AnimateEntity(D_us_8018185C, self);
        if (self->opacity) {
            self->opacity--;
        }

        if (self->opacity) {
            self->opacity--;
        }

        if (!--self->ext.spearGuard.unk7C) {
            DestroyEntity(self);
        }

        for (i = 0; i < 16; i++) {
            if (self->ext.spearGuard.unk7C != D_us_80181804[i]) {
                continue;
            }
            if (i == 14) {
                PlaySfxPositional(SFX_SPEAR_GUARD_DEATH);
            } else if ((i & 1) == 0) {
                PlaySfxPositional(SFX_EXPLODE_FAST_B);
            }

            newEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEnt != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, newEnt);
                newEnt->params = 2;
                newEnt->zPriority = self->zPriority - 1;
                newEnt->posX.i.hi += D_us_80181814[i].x;
                newEnt->posY.i.hi += D_us_80181814[i].y;
            }
        }
        break;
    }
}
