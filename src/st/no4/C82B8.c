#include "no4.h"

extern u8 D_us_80181804[];
extern Point16 D_us_80181814[];
extern u8 D_us_8018185C;
extern u8 D_us_8018186C;

void func_us_801C82B8(Entity* self) {
    Entity* newEnt;
    u8 animStatus;
    u8 i;

    newEnt = self + 1;
    if (self->step && self->ext.spearGuard.unk90 == 0) {
        newEnt->attack = self->attack;
        newEnt->attackElement = self->attackElement;
    }

    if (self->step && self->step < 5 &&
        ((self->flags & FLAG_DEAD) || g_CastleFlags[NO4_WATER_BLOCKED] > 2)) {
        DestroyEntity(newEnt);
        SetStep(5);
        self->ext.spearGuard.unk7C = 64;
        self->drawFlags = FLAG_DRAW_OPACITY;
        self->hitboxState = 0;
        self->opacity = 127;
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
        self->hitboxOffY = 4;
        self->palette += 2;
        CreateEntityFromCurrentEntity(E_SPEAR_GUARD_BLOCK, newEnt);
        self->animCurFrame = 5;
        self->ext.spearGuard.unk7C = self->params * 8;
        break;

    case 1:
        if (self->ext.spearGuard.unk7C) {
            self->ext.spearGuard.unk7C--;
            return;
        }
        self->ext.spearGuard.unk7C = 1;
        self->step++;
        break;

    case 2:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (!--self->ext.spearGuard.unk7C) {
            SetStep(3);
            return;
        }

    default:
        break;

    case 3:
        animStatus = AnimateEntity(&D_us_8018186C, self);
        newEnt->attack = g_api.enemyDefs[94].attack;
        newEnt->attackElement = g_api.enemyDefs[94].attackElement;
        if (!animStatus) {
            SetStep(2);
            self->ext.spearGuard.unk7C = 1;
            break;
        }
        if ((animStatus & 128) && (self->animCurFrame == 45)) {
            PlaySfxPositional(SFX_WEAPON_SWISH_B);
            break;
        }
        break;

    case 4:
        if (self->ext.spearGuard.unk7C) {
            self->ext.spearGuard.unk7C--;
            break;
        }
        self->facingLeft ^= 1;
        self->ext.spearGuard.unk7C = (rand() & 7) + 4;
        break;

    case 5:
        AnimateEntity(&D_us_8018185C, self);
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
            if (self->ext.spearGuard.unk7C == D_us_80181804[i]) {
                if (i == 14) {
                    PlaySfxPositional(SFX_SPEAR_GUARD_DEATH);
                } else if (!(i & 1)) {
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
        }
        break;
    }
}
