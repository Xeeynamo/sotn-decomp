// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

static s8 D_us_8018336C[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x01, 0x1D, 0x01, 0x00, 0x0D, 0x05,
    0xFB, 0x00, 0x06, 0x05, 0xFF, 0x02, 0x0C, 0x06, 0x06, 0x07, 0x0C, 0x0C,
    0xFF, 0x01, 0x0B, 0x04, 0x01, 0x09, 0x09, 0x0C, 0xFF, 0x01, 0x0C, 0x04,
    0x00, 0x00, 0x0C, 0x0C, 0xFD, 0x08, 0x04, 0x0F, 0xFA, 0x07, 0x0A, 0x09,
    0x01, 0x00, 0x0A, 0x0A, 0x00, 0x02, 0x01, 0x0F, 0x00, 0x02, 0x03, 0x15,
    0xFE, 0xFB, 0x0A, 0x06, 0x00, 0x01, 0x06, 0x03};
static s8 D_us_801833B0[][2] = {
    {0, 0}, {8, 4},  {8, 6},  {12, 6}, {0, 8}, {8, 3},  {16, 4}, {8, 4},
    {0, 8}, {16, 4}, {12, 6}, {8, 4},  {8, 4}, {12, 6}, {8, 4},  {4, 2}};
static s16 D_us_801833D0[] = {
    0x800, 0x700, 0x740, 0x780, 0x4C0, 0x800,  0x540,  0x700,
    0x200, 0x500, 0x700, 0x640, 0x400, -0x400, -0x7C0, 0x800};
STATIC_PAD_DATA(8);

#include "../step_towards.h"

void EntitySpectralSword(Entity* self) {
    s32 primIndex;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    Primitive* prim;
    SVECTOR* vec;
    SVECTOR* rot;
    MATRIX* m;
    Entity* ent;
    s32 mag;
    s32 dx;
    s32 dy;
    s32 angle;
    s32* var_fp;
    s32 i;
    s32* var_s7;
    Pos* temp_s3;

    if (self->flags & FLAG_DEAD) {
        if (self->step < 8) {
            SetStep(8);
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpectralSword);
        self->animCurFrame = 1;
#ifdef VERSION_PSP
        self->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE;
#else
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
#endif
        self->hitboxOffX = 0;
        self->hitboxOffY = 4;
        self->zPriority = 0xB0;
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.spectralSword.prim = prim;
        prim->u0 = prim->v0 = 2;
        prim->r0 = prim->g0 = prim->b0 = 0xC0;
        prim->priority = 0xC0;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        ent = self + 1;
        for (i = 1; i < 16; i++, ent++) {
            CreateEntityFromEntity(E_POLTERGEIST, self, ent);
            ent->posY.i.hi = 0x120;
            ent->posY.i.hi = 0x580;
            ent->params = i;
            ent->zPriority = self->zPriority;
        }
        self->step = 1;
        self->ext.spectralSword.hasWeapons = 0;
        self->ext.spectralSword.weaponCount = 0xF;
        break;

    case 1:
        if (GetDistanceToPlayerX() < 0x40 && GetDistanceToPlayerY() < 0x60) {
            SetStep(2);
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->ext.spectralSword.timer = 0x100;
            self->ext.spectralSword.hasWeapons = 1;
            ent = self + 1;
            for (i = 0; i < 15; i++, ent++) {
                ent->posY.i.hi = 0x120;
                ent->step = 2;
            }
            self->step_s++;
            /* fallthrough */
        case 1:
            if (!--self->ext.spectralSword.timer) {
                SetStep(4);
            }
            break;
        }
        break;

    case 3:
        SetStep(4);
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            self->ext.spectralSword.moveTimer = 0x200;
            self->ext.spectralSword.hasWeapons = 3;
            ent = self + 1;
            for (i = 0; i < 15; i++, ent++) {
                if ((ent->flags & FLAG_DEAD) == 0) {
                    ent->step = 2;
                }
            }
            self->step_s++;
            /* fallthrough */
        case 1:
            angle = Random() * 8;
            dx = (rcos(angle) * 0x60) >> 0xC;
            dy = (rsin(angle) * -0x60) >> 0xC;
            ent = &PLAYER;
            prim = self->ext.spectralSword.prim;
            prim->x0 = ent->posX.i.hi + dx;
            prim->y0 = ent->posY.i.hi + dy;
            self->ext.spectralSword.timer = 0x80;
            self->step_s++;
            /* fallthrough */
        case 2:
            if (!--self->ext.spectralSword.timer) {
                self->step_s = 1;
            }
            prim = self->ext.spectralSword.prim;
            dx = prim->x0 - self->posX.i.hi;
            dy = prim->y0 - self->posY.i.hi;
            dx = abs(dx);
            dy = abs(dy);
            if (dx < 8 && dy < 8) {
                self->step_s = 1;
            }
            if (!--self->ext.spectralSword.moveTimer) {
                SetStep(5);
            }
            break;
        }
        MoveEntity();
        prim = self->ext.spectralSword.prim;
        dx = prim->x0 - self->posX.i.hi;
        dy = prim->y0 - self->posY.i.hi;
        angle = ratan2(dy, dx);
        angle = GetNormalizedAngle(0x20, self->ext.spectralSword.angle, angle);
        self->velocityX = rcos(angle) * 0x10;
        self->velocityY = rsin(angle) * 0x10;
        self->ext.spectralSword.angle = angle;
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            self->ext.spectralSword.hasWeapons = 2;
            self->ext.spectralSword.timer = 0x100;
            ent = self + 1;
            for (i = 0; i < 15; i++, ent++) {
                if ((ent->flags & FLAG_DEAD) == 0) {
                    ent->step = 2;
                }
            }
            self->step_s++;
            /* fallthrough */
        case 1:
            if (!--self->ext.spectralSword.timer) {
                if (GetDistanceToPlayerX() < 0x40) {
                    self->step_s++;
                } else {
                    SetStep(4);
                }
            }
            break;

        case 2:
            ent = self + 1;
            for (i = 0; i < 15; i++, ent++) {
                if ((ent->flags & FLAG_DEAD) == 0) {
                    ent->step = 1;
                }
            }
            self->ext.spectralSword.hasWeapons = 1;
            self->ext.spectralSword.moveTimer = 0x20;
            self->ext.spectralSword.weaponIndex = 0;
            self->step_s++;
            /* fallthrough */
        case 3:
            if (!--self->ext.spectralSword.moveTimer) {
                self->ext.spectralSword.moveTimer = 0x20;
                do {
                    self->ext.spectralSword.weaponIndex++;
                    ent = self + self->ext.spectralSword.weaponIndex;
                    if (self->ext.spectralSword.weaponIndex > 15) {
                        ent = NULL;
                        break;
                    }
                } while (ent->flags & FLAG_DEAD);
                if (ent != NULL) {
                    ent = self + self->ext.spectralSword.weaponIndex;
                    ent->ext.spectralSword.weaponIndex |= 1;
                } else {
                    self->ext.spectralSword.timer = 0x40;
                    self->step_s++;
                }
            }
            break;

        case 4:
            if (!--self->ext.spectralSword.timer) {
                SetStep(4);
            }
            break;
        }
        MoveEntity();
        ent = &PLAYER;
        dx = 0x80;
        dy = ent->posY.i.hi - 0x60;
        dx -= self->posX.i.hi;
        dy -= self->posY.i.hi;
        mag = (dx * dx) + (dy * dy);
        mag = SquareRoot0(mag);
        sp48 = mag / 2;
        if (sp48 > 0x30) {
            sp48 = 0x30;
        }
        angle = ratan2(dy, dx);
        self->velocityX = sp48 * rcos(angle);
        self->velocityY = sp48 * rsin(angle);
        break;

    case 8:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            ent = self + 1;
            for (i = 0; i < 15; i++, ent++) {
                ent->flags |= FLAG_DEAD;
            }
            self->drawFlags |= FLAG_DRAW_ROTATE;
            self->rotate = 0;
            PlaySfxPositional(SFX_STUTTER_EXPLODE_A);
            self->step_s++;
            break;

        case 1:
            MoveEntity();
            self->velocityY += FIX(3.0 / 32);
            self->rotate -= 4;
            if ((g_Timer & 7) == 0) {
                ent = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (ent != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, ent);
                    ent->params = 3;
                }
            }
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            break;

        case 2:
            break;
        }
        break;

    case 0xFF:
#include "../pad2_anim_debug.h"
    }

    if ((self->flags & FLAG_DEAD) == 0) {
        if (!self->ext.spectralSword.weaponCount) {
            self->ext.spectralSword.hasWeapons = 0;
        }
        switch (self->ext.spectralSword.hasWeapons) {
        case 0:
            break;

        case 1:
            mag = 0xF - self->ext.spectralSword.weaponCount;
            self->rotate += (mag * 4) + 8;
            sp40 = (mag * 8) + 0x40;
            ent = self + 1;
            angle = 0x1000 / self->ext.spectralSword.weaponCount;
            for (i = 0; i < 15; i++, ent++) {
                if ((ent->flags & FLAG_DEAD) == 0) {
                    dx = self->posX.val;
                    dy = self->posY.val;
                    dx += sp40 * rcos((i * angle) + self->rotate) * 0x10;
                    dy += sp40 * rsin((i * angle) + self->rotate) * 0x10;
                    temp_s3 = &ent->ext.spectralSword.weaponPos;
                    temp_s3->x.val = dx;
                    temp_s3->y.val = dy;
                }
            }
            break;

        case 3:
            m = (MATRIX*)SP(0);
            rot = (SVECTOR*)SP(0x30);
            vec = (SVECTOR*)SP(0x38);
            SetGeomScreen(0x400);
            SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
            gte_ldtr(0, 0, 0x400);
            mag = 0xF - self->ext.spectralSword.weaponCount;
            self->ext.spectralSword.rotX += 8;
            self->ext.spectralSword.rotateTarget += (mag * 4) + 8;
            vec->vx = 0;
            vec->vy = (mag * 8) + 0x40;
            vec->vz = 0;
            gte_ldv0(vec);
            rot->vx = self->ext.spectralSword.rotX;
            rot->vy = self->ext.spectralSword.rotY;
            var_s7 = (s32*)SP(0x80);
            var_fp = (s32*)SP(0x40);
            sp44 = self->ext.spectralSword.rotateTarget;
            angle = 0x1000 / self->ext.spectralSword.weaponCount;
            for (i = 0; i < 15;) {
                rot->vz = sp44 + (angle * i);
                RotMatrix(rot, m);
                gte_SetRotMatrix(m);
                gte_rtps();
                gte_stsxy((long*)var_fp);
                gte_stszotz((long*)var_s7);
                *var_s7 -= 0x100;
                i++;
                var_fp++;
                var_s7++;
            }
            var_fp = (s32*)SP(0x40);
            var_s7 = (s32*)SP(0x80);
            ent = self + 1;
            dx = self->zPriority;
            for (i = 0; i < 15; i++, ent++) {
                if ((ent->flags & FLAG_DEAD) == 0) {
                    temp_s3 = &ent->ext.spectralSword.weaponPos;
                    temp_s3->x.i.hi = *var_fp & 0xFFFF;
                    temp_s3->y.i.hi = *var_fp >> 0x10;
                    mag = dx - *var_s7;
                    if (mag < 0xAA) {
                        mag = 0xAA;
                    }
                    ent->zPriority = mag;
                    var_fp++;
                    var_s7++;
                }
            }
            break;

        case 2:
            ent = self + 1;
            dx = self->posX.i.hi -
                 ((self->ext.spectralSword.weaponCount / 2 + 1) * 0x10);
            dy = self->posY.i.hi;
            for (i = 0; i < 15; i++, ent++) {
                if ((ent->flags & FLAG_DEAD) == 0) {
                    dx += 0x10;
                    if (self->posX.i.hi == dx) {
                        dx += 0x10;
                    }
                    temp_s3 = &ent->ext.spectralSword.weaponPos;
                    temp_s3->x.i.hi = dx;
                    temp_s3->y.i.hi = dy;
                }
            }
            break;
        }
        if ((self->flags & 0xF) == 0) {
            if (g_Timer & 1) {
                self->palette = PAL_SPECTRAL_SWORD;
            } else {
                self->palette = PAL_UNK_242;
            }
        }
        if ((g_Timer & 0xF) == 0) {
            ent = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (ent != NULL) {
                CreateEntityFromEntity(E_UNK_3F, self, ent);
                ent->ext.et_801CEB08.unk80 = self;
            }
        }
    }
}

void func_us_801CEB08(Entity* self) {
    Entity* tempEntity;

    if (!self->step) {
        InitializeEntity(D_us_8018097C);
        self->animCurFrame = 1;
        self->palette += 2;
        self->drawFlags |=
            FLAG_DRAW_OPACITY | FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->scaleX = self->scaleY = 0x100;
        self->opacity = 0x80;
    }
    tempEntity = self->ext.et_801CEB08.unk80;
    self->posX.val = tempEntity->posX.val;
    self->posY.val = tempEntity->posY.val;
    self->scaleX += 6;
    self->scaleY += 6;
    self->opacity -= 4;
    if (self->opacity < 0x20) {
        DestroyEntity(self);
    }
}

void EntityPoltergeist(Entity* self) {
    Entity* tempEntity;
    s16 angle;
    s32 dx, dy;
    Pos* pos;
    s32 mag, mag2, mag3;
    s8* hitboxPtr;

    if ((self->flags & FLAG_DEAD) && self->step < 16) {
        SetStep(16);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitPoltergeist);
        self->animCurFrame = self->params + 1;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        hitboxPtr = D_us_8018336C;
        hitboxPtr += self->animCurFrame * 4;
        self->hitboxOffX = *hitboxPtr++;
        self->hitboxOffY = *hitboxPtr++;
        self->hitboxWidth = *hitboxPtr++;
        self->hitboxHeight = *hitboxPtr++;
        self->hitboxState = 0;
        self->ext.spectralSword.timer = 0x40;
        self->step = 1;
        break;

    case 1:
        if (self->ext.spectralSword.weaponIndex) {
            self->ext.spectralSword.weaponIndex = 0;
            SetStep(3);
        }
        break;

    case 2:
        MoveEntity();
        StepTowards(&self->rotate, 0, 8);
        pos = &self->ext.spectralSword.weaponPos;
        dx = pos->x.i.hi - self->posX.i.hi;
        dy = pos->y.i.hi - self->posY.i.hi;
        mag = (dx * dx) + (dy * dy);
        mag = SquareRoot0(mag);
        mag2 = mag / 2; // ????
        mag2 = mag;
        if (!--self->ext.spectralSword.timer) {
            self->hitboxState = 3;
        }
        if (mag2 > 0x38) {
            mag2 = 0x38;
        }
        angle = ratan2(dy, dx);
        self->velocityX = mag2 * rcos(angle);
        self->velocityY = mag2 * rsin(angle);
        if (self->ext.spectralSword.weaponIndex) {
            PlaySfxPositional(SFX_BONE_SWORD_SWISH_B);
            self->ext.spectralSword.weaponIndex = 0;
            SetStep(3);
        }
        break;

    case 3:
        switch (self->step_s) {
        case 0:
            tempEntity = &PLAYER;
            angle = GetAngleBetweenEntities(self, tempEntity);
            self->ext.spectralSword.angle = angle + 0x1000;
            self->step_s++;
            /* fallthrough */
        case 1:
            angle = self->ext.spectralSword.angle - D_us_801833D0[self->params];
            if (StepTowards(&self->rotate, angle, 0x100)) {
                self->step_s++;
            }
            break;

        case 2:
            self->ext.spectralSword.angle &= 0xFFF;
            self->rotate &= 0xFFF;
            self->velocityX = rcos(self->ext.spectralSword.angle) << 6;
            self->velocityY = rsin(self->ext.spectralSword.angle) << 6;
            self->ext.spectralSword.timer = 0x30;
            PlaySfxPositional(SFX_BONE_THROW);
            self->step_s++;
            /* fallthrough */
        case 3:
            MoveEntity();
            if (!--self->ext.spectralSword.timer) {
                SetStep(2);
            }
            if (self->posY.i.hi > 0xE0) {
                SetStep(2);
            }
            break;
        }
        break;

    case 16:
        switch (self->step_s) {
        case 0:
            tempEntity = self - self->params;
            tempEntity->ext.spectralSword.weaponCount--;
            self->hitboxState = 0;
            PlaySfxPositional(SFX_EXPLODE_B);
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if ((g_Timer & 7) == 0) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                    tempEntity->params = 1;
                }
            }
            if (self->posY.i.hi > 0x140) {
                self->step_s++;
                self->animCurFrame = 0;
            }
            break;

        case 2:
            self->animCurFrame = 0;
            break;
        }
        break;
    }
    if (self->rotate) {
        self->drawFlags |= FLAG_DRAW_ROTATE;
    } else {
        self->drawFlags = FLAG_DRAW_DEFAULT;
    }
    angle = self->rotate + D_us_801833D0[self->params];
    hitboxPtr = D_us_801833B0[self->params];
    mag3 = *hitboxPtr++;
    self->hitboxWidth = self->hitboxHeight = *hitboxPtr;
    self->hitboxOffX = (mag3 * rcos(angle)) >> 0xC;
    self->hitboxOffY = (mag3 * rsin(angle)) >> 0xC;
}
