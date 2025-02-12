// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "no0.h"

extern SVECTOR D_us_80181FC0;

void func_us_801D542C(Entity* self) {
    long unusedA;
    long unusedB;
    long pos;
    s32 primIndex;
    s32 z;
    s32 tempPosX;
    s32 tempPosY;
    s32 unks32A;
    s32 unks32B;
    s32 unks32C;
    s32 attack;
    Collider collider;
    Entity* tempEntity2;
    SVECTOR rotA;
    SVECTOR rotB;
    VECTOR trans;
    MATRIX m;

    s32 sp90;
    Primitive* prim;
    s32 posX;
    s32 posY;
    s32 var_fp;
    s32 var_s3;
    s32 var_s6;
    s32 i;
    Entity* tempEntity;

    tempEntity = self - 5;
    self->facingLeft = tempEntity->facingLeft;
    tempEntity = self + 4;
    tempEntity->attack = 1;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitPlateLord);
        self->animCurFrame = 7;
        self->zPriority = 0xB4;
        self->drawFlags |= FLAG_DRAW_ROTZ;
        primIndex = g_api.AllocPrimBuffers(PRIM_GT4, 0xA);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;

        while (prim != NULL) {
            prim->tpage = 0x13;
            prim->clut = 0x22C;
            prim->u0 = prim->u2 = 0x68;
            prim->u1 = prim->u3 = 0x6E;
            prim->v0 = prim->v1 = 0x48;
            prim->v2 = prim->v3 = 0x4E;
            prim->p2 = 0;
            prim->x0 = self->posX.i.hi;
            prim->y0 = 0x80;
            LOW(prim->x1) = LOW(prim->x0);
            LOW(prim->x2) = LOW(prim->x0);
            LOW(prim->x3) = LOW(prim->x0);
            prim->priority = 0xB6;
            prim->drawMode = DRAW_UNK02;
            self->ext.plateLordUnknown.unkA0 = prim;
            prim = prim->next;
        }
        break;
    case 1:
    case 3:
        func_us_801D4E30();
        func_us_801D4E94(0x100);
        func_us_801D5074(0x100);
        func_us_801D5250();
        func_us_801D51EC();
        func_us_801D5384();
        return;
    case 8:
        func_us_801D4E30();
        func_us_801D5250();
        func_us_801D4E94(0x800);
        func_us_801D5074(0x200);
        func_us_801D5250();
        func_us_801D51EC();
        func_us_801D5384();
        return;
    case 12:
        func_us_801D4E30();
        func_us_801D4FCC();
        func_us_801D5250();
        prim = self->ext.plateLordUnknown.unkA0;
        posX = prim->x0;
        posY = prim->y0;
        tempEntity = self + 4;
        g_api.CheckCollision(posX, posY + 0xA, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            posY += collider.unk18;
            tempEntity->velocityY = FIX(-4);
            if (self->facingLeft) {
                tempEntity->velocityX = FIX(-0.375);
            } else {
                tempEntity->velocityX = FIX(0.375);
            }
            self->ext.plateLordUnknown.unk9C = 0;
            PlaySfxPositional(0x761);
            g_api.func_80102CD8(1);
            self->step = 0xD;
        } else {
            if (self->facingLeft) {
                self->ext.plateLordUnknown.unk84 += 0x80;
            } else {
                self->ext.plateLordUnknown.unk84 -= 0x80;
            }
        }
        tempEntity->posX.i.hi = posX;
        tempEntity->posY.i.hi = posY;
        tempEntity->attack = g_api.enemyDefs[98].attack;
        func_us_801D51EC();
        return;
    case 13:
        tempEntity = self + 4;
        tempEntity->posX.val += tempEntity->velocityX;
        tempEntity->posY.val += tempEntity->velocityY;
        tempEntity->velocityY += FIX(0.25);
        tempPosX = tempEntity->posX.i.hi;
        tempPosY = tempEntity->posY.i.hi + 0xA;
        g_api.CheckCollision(tempPosX, tempPosY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            PlaySfxPositional(0x761);
            tempEntity->posY.i.hi += collider.unk18;
            if (!self->ext.plateLordUnknown.unk9C) {
                tempEntity->velocityY = -(tempEntity->velocityY) / 2;
                self->ext.plateLordUnknown.unk9C++;
            } else {
                tempEntity = self - 5;
                tempEntity->step_s = 0;
                tempEntity->step = 0xE;
                self->step = 0xE;
                self->ext.plateLordUnknown.unk9C = 0;
            }
        }
        func_us_801D4E30();

        if (self->ext.plateLordUnknown.unk9C) {
            func_us_801D5074(0x180);
        } else {
            func_us_801D5074(0);
        }
        func_us_801D5250();
        func_us_801D51EC();
        return;
    case 14:
        func_us_801D4E30();
        unks32A = func_us_801D52E0();
        if (unks32A != 0) {
            self->ext.plateLordUnknown.unk84 = unks32A;
            func_us_801D4FCC();
        }
        func_us_801D4E94(0x180);
        func_us_801D5074(0x100);
        func_us_801D5250();
        func_us_801D51EC();
        func_us_801D5384();
        if (!(self->ext.plateLordUnknown.unk9C & g_Timer)) {
            self->ext.plateLordUnknown.unk9C++;
            tempEntity = self + 4;
            tempEntity2 = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity2 != NULL) {
                CreateEntityFromEntity(6U, tempEntity, tempEntity2);
                tempEntity2->zPriority = tempEntity->zPriority + 2;
                tempEntity2->params = 0x10;
                tempEntity2->posY.i.hi += 0xA;
            }
        }
        return;
    case 16:
        tempEntity = self + 4;
        tempPosY = self->posY.i.hi - tempEntity->posY.i.hi;
        tempEntity->velocityY = FIX(-12);
        self->step = 0x11;
        /* fallthrough */
    case 17:
        tempEntity = self + 4;
        tempEntity->posY.val += tempEntity->velocityY;
        tempEntity->velocityY += FIX(0.125);
        tempPosY = self->posY.i.hi - tempEntity->posY.i.hi;
        if (tempPosY >= 0x39) {
            tempEntity = self - 5;
            tempEntity->ext.plateLord.unk87 = 1;
            self->step = 0x12;
        }
        func_us_801D4E30();
        func_us_801D5074(0);
        func_us_801D5074(0);
        func_us_801D4E94(-0x400);
        func_us_801D51EC();
        func_us_801D5384();
        break;
    case 18:
        tempEntity = self + 4;
        tempEntity->velocityY = 0;
        tempEntity->step = 0x10;
        self->step = 0x13;
        /* fallthrough */
    case 19:
        func_us_801D4E30();
        func_us_801D5074(0x200);
        func_us_801D4E94(0);
        func_us_801D5250();
        func_us_801D51EC();
        break;
    case 9:
        if (!self->step_s) {
            self->ext.plateLordUnknown.unk88 = -0x100;
            self->ext.plateLordUnknown.unk8A = 0;
            self->ext.plateLordUnknown.unk8C = 0;
            self->ext.plateLordUnknown.unk80 = 0;
            self->ext.plateLordUnknown.unk82 = 0xC00;
            self->ext.plateLordUnknown.unk90 = 0x10;
            self->step_s++;
        }
        tempEntity = self - 2;
        if (self->ext.plateLordUnknown.unk9D == 0) {
            if (tempEntity->ext.plateLordUnknown.unk82 & 0xF000) {
                PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
                self->ext.plateLordUnknown.unk9D = 1;
                tempEntity->ext.plateLordUnknown.unk82 &= 0xFFF;
            }
        } else {
            self->ext.plateLordUnknown.unk9D = 0;
        }
        attack = (tempEntity->ext.plateLordUnknown.unk84 *
                  g_api.enemyDefs[98].attack) >>
                 8;
        if (g_api.enemyDefs[98].attack < attack) {
            attack = g_api.enemyDefs[98].attack;
        }
        tempEntity = self + 4;
        tempEntity->attack = attack;
        tempEntity = self - 2;
        unks32B = (tempEntity->ext.plateLordUnknown.unk84 << 0xF) >> 0xC;
        self->ext.plateLordUnknown.unk80 = unks32B + 0x100;
        if (self->ext.plateLordUnknown.unk80 > 0x400) {
            self->ext.plateLordUnknown.unk80 = 0x400;
        }
        unks32C = tempEntity->ext.plateLordUnknown.unk84 << 5;
        if (unks32C > 0x1000) {
            unks32C = 0x1000;
        }
        self->ext.plateLordUnknown.unk82 =
            tempEntity->ext.plateLordUnknown.unk82;
        sp90 = (0x1000 - (tempEntity->ext.plateLordUnknown.unk84 * 0xD)) >> 4;
        if (sp90 < 0) {
            sp90 = 0;
        }
        if (tempEntity->ext.plateLordUnknown.unk84 > 0xA0) {
            self->ext.plateLordUnknown.unk8C +=
                self->ext.plateLordUnknown.unk90;
            if ((self->ext.plateLordUnknown.unk8C > 0x100) ||
                (self->ext.plateLordUnknown.unk8C < -0x100)) {
                self->ext.plateLordUnknown.unk90 =
                    -self->ext.plateLordUnknown.unk90;
            }
        }
        if (((self->ext.plateLordUnknown.unk82 & 0xFFF) > 0xD00) &&
            ((self->ext.plateLordUnknown.unk82 & 0xFFF) < 0xF00) &&
            (tempEntity->ext.plateLordUnknown.unk84 > 0x100)) {
            tempEntity->ext.plateLordUnknown.unk82 =
                tempEntity->ext.plateLordUnknown.unk82 & 0xFFF;
            tempEntity->ext.plateLordUnknown.unk82 =
                -(0x1000 - tempEntity->ext.plateLordUnknown.unk82);
            self->ext.plateLordUnknown.unk8E =
                tempEntity->ext.plateLordUnknown.unk82;
            tempEntity = self - 5;
            PlaySfxPositional(SFX_WEAPON_SWISH_C);
            PlaySfxPositional(0x75E);
            tempEntity->step = 0xB;
            tempEntity->step_s = 0;
            self->step = 0xB;
            self->step_s = 0;
        }
        break;
    case 11:
        tempEntity = self - 2;
        self->ext.plateLordUnknown.unk8C = 0;
        tempEntity->ext.plateLordUnknown.unk86 = 0;
        tempEntity->ext.plateLordUnknown.unk84 = 0xF0;
        if (tempEntity->ext.plateLordUnknown.unk82 > 0xE00) {
            tempEntity->ext.plateLordUnknown.unk82 = 0xE00;
        }

        self->ext.plateLordUnknown.unk8E =
            tempEntity->ext.plateLordUnknown.unk82;
        sp90 = 0x60;
        self->ext.plateLordUnknown.unk82 = self->ext.plateLordUnknown.unk8E;
        if (self->ext.plateLordUnknown.unk82 > 0x800) {
            self->ext.plateLordUnknown.unk82 = 0x800;
        }
        tempEntity = self + 4;
        tempEntity->attack = g_api.enemyDefs[98].attack;
        break;
    }
    if ((self->step == 9) || (self->step == 0xB)) {
        SetGeomScreen(0x400);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        var_s6 = self->ext.plateLordUnknown.unk80;
        var_s3 = self->ext.plateLordUnknown.unk82;
        var_fp = self->ext.plateLordUnknown.unk8E;
        prim = self->ext.prim;
        for (i = 0; i < 0xA; i++) {
            switch (self->step) {
            case 9:
                var_s6 = (var_s6 * unks32C) >> 0xC;
                var_s3 -= sp90;
                break;
            case 11:
                var_s6 = 0x400;
                var_fp -= sp90;
                var_s3 = var_fp;
                if (var_s3 > 0x800) {
                    var_s3 = 0x800;
                }
                break;
            }
            rotB.vx = self->ext.plateLordUnknown.unk88;
            rotB.vy = -var_s3 + self->ext.plateLordUnknown.unk8A;
            rotB.vz = var_s6;
            RotMatrix(&D_us_80181FC0, &m);
            RotMatrixZ(rotB.vz, &m);
            RotMatrixY(rotB.vy, &m);
            RotMatrixX(rotB.vx, &m);
            RotMatrixZ(self->ext.plateLordUnknown.unk8C, &m);
            if (!self->facingLeft) {
                RotMatrixY(0x800, &m);
            }
            trans.vx = 0;
            trans.vy = 0;
            trans.vz = 0x400;
            TransMatrix(&m, &trans);
            SetRotMatrix(&m);
            SetTransMatrix(&m);
            rotA.vx = 0;
            rotA.vy = i * 8;
            rotA.vz = 0;
            z = RotTransPers(&rotA, &pos, &unusedA, &unusedB);
            prim->priority = self->zPriority + 0x10 + (z - 0x100);
            posX = pos & 0xFFFF;
            posY = pos >> 0x10;
            prim->x0 = prim->x2 = posX - 3;
            prim->x1 = prim->x3 = posX + 3;
            prim->y0 = prim->y1 = posY - 3;
            prim->y2 = prim->y3 = posY + 3;
            prim = prim->next;
        }
        tempEntity = self + 4;
        tempEntity->posX.i.hi = posX;
        tempEntity->posY.i.hi = posY;
        tempEntity->zPriority = self->zPriority + 0x10 + (z - 0x100);
        if ((self->step == 0xB) && (var_s3 == 0x800)) {
            tempEntity = self - 2;
            tempEntity->step = 3;
            if (self->facingLeft) {
                self->ext.plateLordUnknown.unk84 = -0x400;
            } else {
                self->ext.plateLordUnknown.unk84 = 0x400;
            }
            self->step = 0xC;
        }
    }
}
