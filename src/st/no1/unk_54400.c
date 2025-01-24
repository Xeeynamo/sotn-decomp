// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

INCLUDE_ASM("st/no1/nonmatchings/unk_54400", func_us_801D4400);

extern u8 D_us_801831E0[];
extern s16 D_us_801831F4[];
extern s16 D_us_80183204[];

void func_us_801D4558(Entity* self) {
    Entity* tempEntity;
    s16 tempVar;
    s16 posX, posY;

    if (self->flags & FLAG_DEAD) {
        EntityExplosionSpawn(0, 0);
        return;
    }
    if (self->hitParams && self->step != 4) {
        self->step = 4;
        self->step_s = 0;
    }
    tempEntity = &PLAYER;
    if ((tempEntity->posX.i.hi - self->posX.i.hi) > 0) {
        self->facingLeft = 1;
    } else {
        self->facingLeft = 0;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B18);
        self->ext.et_801D4558.unk80 = self->hitboxState;
        self->hitboxState = 0;
        self->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;

        self->rotX = 0;
        self->rotY = 0;
        self->ext.et_801D4558.unk7D = 0;
        self->drawMode = DRAW_TPAGE;
        break;

    case 1:
        tempVar = (s16)self->params & 0xF8;
        if (tempVar > GetDistanceToPlayerX() &&
            tempVar > GetDistanceToPlayerY()) {
            self->step++;
            self->ext.et_801D4558.unk7C = 0;
        }
        break;

    case 2:
        AnimateEntity(D_us_801831E0, self);
        self->ext.et_801D4558.unk7C++;
        self->rotX += 8;
        self->rotY += 8;
        if (self->ext.et_801D4558.unk7C == 0x20) {
            self->hitboxState = 2;
            self->drawFlags = FLAG_DRAW_DEFAULT;
        }
        if (self->ext.et_801D4558.unk7C == 0x28) {
            self->hitboxState = self->ext.et_801D4558.unk80;
            SetStep(3);
            self->ext.et_801D4558.unk82 = 0;
            self->drawFlags = FLAG_DRAW_DEFAULT;
        }
        break;

    case 3:
        AnimateEntity(D_us_801831E0, self);
        SetEntityVelocityFromAngle(
            self->ext.et_801D4558.unkAC, self->ext.et_801D4558.unkB0);
        self->velocityX >>= 8;
        self->velocityY >>= 8;
        MoveEntity();
        if (!self->ext.et_801D4558.unk82) {
            self->ext.et_801D4558.unk84 = D_us_80183204[Random() & 7];
            self->ext.et_801D4558.unk86 = D_us_80183204[Random() & 7];
            self->ext.et_801D4558.unk82 = (Random() & 0x1F) + 0x20;
        } else {
            self->ext.et_801D4558.unk82--;
        }
        posX = tempEntity->posX.i.hi + self->ext.et_801D4558.unk84;
        posY = tempEntity->posY.i.hi + self->ext.et_801D4558.unk86;
        self->ext.et_801D4558.unkAC = AdjustValueWithinThreshold(
            1, self->ext.et_801D4558.unkAC,
            GetAnglePointToEntityShifted(posX, posY));
        self->ext.et_801D4558.unkB0 += 0x40;
        if (self->ext.et_801D4558.unkB0 > 0x1800) {
            self->ext.et_801D4558.unkB0 = 0x1800;
        }
        break;

    case 4:
        AnimateEntity(D_us_801831E0, self);
        if (self->step_s) {
            MoveEntity();
            if (!--self->ext.et_801D4558.unk7C) {
                self->step = 3;
                self->ext.et_801D4558.unkB0 = 0;
            }
        } else {
            self->ext.et_801D4558.unkAC =
                GetAngleBetweenEntitiesShifted(tempEntity, self);
            SetEntityVelocityFromAngle(self->ext.et_801D4558.unkAC, 0x18);
            self->ext.et_801D4558.unk7C = 0x14;
            self->step_s++;
        }
        break;
    }
    if (self->step > 1) {
        self->ext.et_801D4558.unk7D++;
        if ((self->ext.et_801D4558.unk7D & 3) == 0) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromCurrentEntity(E_ID_52, tempEntity);
                tempVar = Random();
                tempEntity->posX.i.hi += D_us_801831F4[tempVar & 7];
                tempEntity->posY.i.hi += D_us_801831F4[(tempVar - 2) & 7];
            }
        }
    }
}

INCLUDE_ASM("st/no1/nonmatchings/unk_54400", func_us_801D4950);
