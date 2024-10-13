// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"
#include "sfx.h"

// The enemy called "Blade", his helper functions, and his swords

static void func_801D0A00(s16* arg0) {
    func_801CD91C(&g_CurrentEntity[arg0[1]]);
    func_801CD91C(&g_CurrentEntity[arg0[0]]);
    func_801CD91C(&g_CurrentEntity[18]);
    func_801CD83C(&g_CurrentEntity[arg0[2]]);
    func_801CD83C(&g_CurrentEntity[arg0[3]]);

    for (arg0 += 4; *arg0 != 0; arg0++) {
        if (*arg0 != 0xFF) {
            func_801CD83C(&g_CurrentEntity[*arg0]);
        }
    }
}

static void func_801D0B40(void) {
    s16* unk88 = g_CurrentEntity[15].ext.et_801D0B40.unk88;
    g_CurrentEntity[15].ext.et_801D0B40.unk84 = unk88[0x4E] - 0x600;

    unk88 = g_CurrentEntity[16].ext.et_801D0B40.unk88;
    g_CurrentEntity[16].ext.et_801D0B40.unk84 = unk88[0x4E] - 0x600;
}

// Function does not use the argument, but all calls in EntityBlade
// give one, so we include it here.
static s32 func_801D0B78(Entity* unused) {
    s32 ret;

    //! FAKE:
    do {
    } while (0);

    ret = 0;

    switch (g_CurrentEntity->step) {
    case 8:
        if (GetDistanceToPlayerX() < 64) {
            ret = 10;
        }
        if (GetDistanceToPlayerX() > 80) {
            ret = 6;
        }
        if (g_CurrentEntity->ext.et_801D0B78.unk88 != 0) {
            ret = 7;
        }
        break;

    case 10:
        if (GetDistanceToPlayerX() < 88) {
            ret = 8;
        }
        if (GetDistanceToPlayerX() < 56) {
            ret = 7;
        }
        if (GetDistanceToPlayerX() > 80) {
            ret = 6;
        }
        if (g_CurrentEntity->ext.et_801D0B78.unk88 != 0) {
            ret = 7;
        }
        break;

    case 12:
        if (GetDistanceToPlayerX() < 64) {
            ret = 10;
        }
        break;

    case 6:
        if (g_CurrentEntity->ext.et_801D0B78.unk88 != 0) {
            ret = 7;
        }
        if (GetDistanceToPlayerX() < 48) {
            ret = 10;
        }
        if (GetDistanceToPlayerX() < 80) {
            ret = 8;
        }
        break;

    default:
        if (GetDistanceToPlayerX() > 80) {
            ret = 6;
        }
        if (GetDistanceToPlayerX() < 64) {
            ret = 10;
        }
        if (g_CurrentEntity->ext.et_801D0B78.unk88 != 0) {
            ret = 7;
        }
        break;
    }

    if (g_CurrentEntity->facingLeft != ((GetSideToPlayer() & 1) ^ 1)) {
        ret = 12;
    }
    return ret;
}

void EntityBlade(Entity* self) {
    Collider collider;
    Entity* otherEnt;
    Entity* var_s3;
    s16* var_s2;
    s16* var_s4;
    s32 var_v0;
    u16 zPriority;

    if ((self->step & 1) && (self->hitFlags & 3)) {
        func_801CE1E8(0xE);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < 0x18U) &&
        (((self + 13)->ext.GH_Props.unk88 != 0) ||
         ((self + 10)->ext.GH_Props.unk88 != 0))) {
        PlaySfxPositional(0x750);
        func_801CE1E8(0x18);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGurkhaType2);
        self->animCurFrame = 0;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->facingLeft = self->params;
        /* fallthrough */
    case 1:
        if (UnkCollisionFunc3(D_801833E4) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step++;
        }
        break;
    case 2:
        var_s3 = self;
        for (var_s4 = &D_801833F4; *var_s4 != 0; var_s4 += 5) {
            otherEnt = self + var_s4[0];
            CreateEntityFromCurrentEntity(E_GURKHA_BODY_PARTS, otherEnt);
            otherEnt->ext.GH_Props.unk9E = var_s4[2];
            otherEnt->ext.GH_Props.parent = self + var_s4[1];
            otherEnt->params = var_s4[3] + 0x200;
            zPriority = self->zPriority + var_s4[4];
            otherEnt->unk60 = var_s3;
            var_s3 = otherEnt;
            var_s3->unk5C = self;
            var_s3->zPriority = zPriority;
        }
        self->unk60 = var_s3;
        self->unk5C = NULL;

        otherEnt = self + 15;
        CreateEntityFromCurrentEntity(E_BLADE_SWORD, otherEnt);
        otherEnt->ext.GH_Props.unk9E = 12;
        otherEnt->ext.GH_Props.parent = self + 5;
        otherEnt->zPriority = self->zPriority + 3;
        otherEnt->params = 19;

        otherEnt = self + 16;
        CreateEntityFromCurrentEntity(E_BLADE_SWORD, otherEnt);
        otherEnt->ext.GH_Props.unk9E = 12;
        otherEnt->ext.GH_Props.parent = self + 8;
        otherEnt->zPriority = self->zPriority - 4;
        otherEnt->params = 19;
        self->step++;
        /* fallthrough */
    case 3:
        func_801CE228();
        func_801CE1E8(5);
        /* fallthrough */
    case 5:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_80183530;
        } else {
            var_s2 = D_80183548;
        }
        func_801CDF1C(var_s2, &D_80183600, 0);
        func_801CDE10(var_s2);
        func_801D0A00(var_s2);
        func_801D0B40();
        func_801CE258(&D_80183494);
        if (self->ext.GH_Props.unkB0[0] > 1) {
            collider.unk18 = 9;
            otherEnt = &self[var_s2[3]];
            func_801CE04C(otherEnt, &collider);
            if (otherEnt->ext.GH_Props.unk88 != 0) {
                otherEnt->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                self->ext.GH_Props.unk88 =
                    func_801CE120(otherEnt, self->facingLeft);
                var_v0 = func_801D0B78(otherEnt);
                if (var_v0) {
                    func_801CE1E8(var_v0);
                }
            }
        }
        break;
    case 7:
        if (self->step_s == 0) {
            self->ext.GH_Props.unkB0[0] = 1;
            self->step_s++;
        }
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_80183560;
        } else {
            var_s2 = D_80183570;
        }
        func_801CDF1C(var_s2, &D_80183638, 0);
        func_801CDE10(var_s2);
        func_801D0A00(var_s2);
        func_801D0B40();
        func_801CE258(&D_80183494);
        if (self->ext.GH_Props.unkB0[0] > 1) {
            collider.unk18 = 9;
            otherEnt = &self[var_s2[3]];
            func_801CE04C(otherEnt, &collider);
            if (otherEnt->ext.GH_Props.unk88 != 0) {
                otherEnt->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                if (func_801CE120(otherEnt, self->facingLeft ^ 1) != 0) {
                    func_801CE1E8(6);
                }
                self->ext.GH_Props.unk88 =
                    func_801CE120(otherEnt, self->facingLeft);
                var_v0 = func_801D0B78(self);
                if (var_v0) {
                    func_801CE1E8(var_v0);
                }
            }
        }
        break;
    case 6:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_80183530;
        } else {
            var_s2 = D_80183548;
        }
        switch (self->step_s) {
        case 0:
            if (self->ext.GH_Props.unk84 == 1) {
                var_s2 = D_801834B8;
            } else {
                var_s2 = D_801834D8;
            }
            func_801CDF1C(var_s2, &D_801838C4, 0);
            func_801CDE10(var_s2);
            func_801D0A00(var_s2);
            func_801D0B40();
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB4[0] == 0)) {
                self->step_s++;
            }
            self->step_s++;
            break;
        case 1:
            func_801CDF1C(var_s2, &D_80183700, 0);
            func_801CDE10(var_s2);
            func_801D0A00(var_s2);
            func_801D0B40();
            if ((self->ext.GH_Props.unkB4[0] == 0) &&
                (self->ext.GH_Props.unkB0[0] == 0)) {
                self->step_s++;
            }
            break;
        case 2:
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-2.5);
            } else {
                self->velocityX = FIX(2.5);
            }
            self->velocityY = FIX(-1);
            func_801CE228();
            self->step_s++;
            /* fallthrough */
        case 3:
            MoveEntity();
            self->velocityY += FIX(11.0 / 128);
            func_801CDF1C(var_s2, &D_80183720, 0);
            func_801CDE10(var_s2);
            func_801CE3FC(var_s2);
            func_801D0B40();
            otherEnt = &self[var_s2[3]];
            collider.unk18 = 9;
            func_801CE04C(otherEnt, &collider);
            if (otherEnt->ext.GH_Props.unk88 != 0) {
                PlaySfxPositional(SFX_STOMP_HARD_C);
                otherEnt->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                self->ext.GH_Props.unk88 =
                    func_801CE120(otherEnt, self->facingLeft);
                var_v0 = func_801D0B78(otherEnt);
                if (var_v0 != 0) {
                    func_801CE1E8(var_v0);
                } else {
                    self->step_s = 1;
                }
            }
            break;
        }
        func_801CE258(&D_80183494);
        break;
    case 8:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_801834B8;
        } else {
            var_s2 = D_801834D8;
        }
        switch (self->step_s) {
        case 0:
            (self + 15)->ext.GH_Props.unk8D = 1;
            (self + 16)->ext.GH_Props.unk8D = 1;
            self->ext.GH_Props.unk8D = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            func_801CDF1C(var_s2, &D_8018386C, 0);
            func_801CDE10(var_s2);
            func_801D0A00(var_s2);
            func_801CE258(&D_80183494);
            if ((self + 16)->hitFlags) {
                self->ext.GH_Props.unk8D = 1;
            }
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB4[0] == 0)) {
                if (self->ext.GH_Props.unk8D != 0) {
                    self->step_s = 3;
                } else {
                    self->step_s = 2;
                }
            }
            break;
        case 2:
            func_801CDF1C(var_s2, &D_8018389C, 0);
            func_801CDE10(var_s2);
            func_801D0A00(var_s2);
            if ((self->ext.GH_Props.unkB0[0] == 1) &&
                (self->ext.GH_Props.unkB4[0] == 0)) {
                PlaySfxPositional(SFX_BONE_SWORD_SWISH_C);
            }
            func_801CE258(&D_80183494);
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB4[0] == 0)) {
                (self + 15)->ext.GH_Props.unk8D = 0;
                (self + 16)->ext.GH_Props.unk8D = 0;
                self->step_s++;
            }
            break;
        case 3:
            func_801CDF1C(var_s2, &D_801835A8, 0);
            func_801CDE10(var_s2);
            func_801D0A00(var_s2);
            func_801CE258(&D_80183494);
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB4[0] == 0)) {
                var_v0 = func_801D0B78(self);
                if (var_v0 != 0) {
                    func_801CE1E8(var_v0);
                } else {
                    func_801CE1E8(5);
                }
            }
            break;
        }
        break;
    case 10:
        if (self->step_s == 0) {
            PlaySfxPositional(0x74E);
            self->step_s++;
        }
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_801834F8;
        } else {
            var_s2 = D_80183514;
        }
        func_801CDF1C(var_s2, &D_80183934, 0);
        func_801CDE10(var_s2);
        func_801D0A00(var_s2);
        func_801D0B40();
        func_801CE258(&D_80183494);
        otherEnt = self + var_s2[5];
        otherEnt->ext.GH_Props.unk8D = 1;
        if ((self->ext.GH_Props.unkB0[0] == 0) &&
            (self->ext.GH_Props.unkB4[0] == 0)) {
            otherEnt =
                self + var_s2[5]; // repeated line, surprised it gets compiled
            otherEnt->ext.GH_Props.unk8D = 0;
            var_v0 = func_801D0B78(self);
            if (var_v0 != 0) {
                func_801CE1E8(var_v0);
            } else {
                func_801CE1E8(5);
            }
        }
        break;
    case 12:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_80183530;
        } else {
            var_s2 = D_80183548;
        }
        func_801CDF1C(var_s2, &D_80183760, 0);
        func_801CDE10(var_s2);
        func_801D0A00(var_s2);
        func_801D0B40();
        func_801CE258(&D_80183494);
        if (self->ext.GH_Props.unkB4[0] == 0) {
            self->ext.GH_Props.unk88 = 0;
            self->facingLeft ^= 1;
            var_v0 = func_801D0B78(self);
            if (var_v0 != 0) {
                func_801CE1E8(var_v0);
            } else {
                func_801CE1E8(5);
            }
        }
        break;
    case 14:
        if (self->step_s == 0) {
            PlaySfxPositional(0x74F);
            self->step_s++;
        }
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_801834B8;
        } else {
            var_s2 = D_801834D8;
        }
        func_801CDF1C(var_s2, &D_80183990, 0);
        func_801CDE10(var_s2);
        func_801D0A00(var_s2);
        func_801CE258(&D_80183494);
        if ((self->ext.GH_Props.unkB0[0] == 0) &&
            (self->ext.GH_Props.unkB4[0] == 0)) {
            var_v0 = func_801D0B78(self);
            if (var_v0 != 0) {
                func_801CE1E8(var_v0);
            } else {
                func_801CE1E8(5);
            }
        }
        break;
    case 24:
        switch (self->step_s) {
        case 0:
            for (var_s2 = &D_80183494; *var_s2 != 0; var_s2++) {
                otherEnt = self + *var_s2;
                otherEnt->hitboxState = 0;
            }
            self->hitboxState = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (self->ext.GH_Props.unk84 == 1) {
                var_s2 = D_801834B8;
            } else {
                var_s2 = D_801834D8;
            }
            func_801CDF1C(var_s2, &D_80183A24, 0);
            func_801CDE10(var_s2);
            func_801D0A00(var_s2);
            func_801CE258(&D_80183494);
            if ((self->ext.GH_Props.unkB0[0] == 3) &&
                (self->ext.GH_Props.unkB4[0] == 0)) {
                PlaySfxPositional(SFX_STOMP_HARD_A);
            }
            if (self->ext.GH_Props.unkB0[0] == 0 &&
                self->ext.GH_Props.unkB4[0] == 0) {
                self->step_s++;
            }
            break;
        case 2:
            var_s2 = D_80183580;
            func_801CDF1C(var_s2, &D_80183A4C, 0);
            func_801CDE88(var_s2);
            func_801CE258(&D_80183494);
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB4[0] == 0)) {
                PlaySfxPositional(SFX_ARROW_SHOT_A);
                (self + 15)->ext.GH_Props.unk8C = 1;
                (self + 15)->ext.GH_Props.rotZ = 0x400;
                (self + 15)->rotZ = 0x400;
                self->ext.GH_Props.unk80 = 0x20;
                self->step_s++;
            }
            break;
        case 3:
            if (--self->ext.GH_Props.unk80 == 0) {
                self->step_s++;
            }
            break;
        case 4:
            for (var_s2 = &D_80183494; *var_s2 != 0; var_s2++) {
                otherEnt = self + *var_s2;
                otherEnt->step = 0x18;
                otherEnt->step_s = 0;
            }
            self->ext.GH_Props.unk80 = 0x40;
            self->step_s++;
            /* fallthrough */
        case 5:
            if (!(g_Timer & 7)) {
                if (Random() & 1) {
                    PlaySfxPositional(SFX_FM_EXPLODE_B);
                } else {
                    PlaySfxPositional(SFX_EXPLODE_D);
                }
            }
            if (--self->ext.GH_Props.unk80 == 0) {
                DestroyEntity(self);
            }
            return;
        }
        break;
    }
    for (var_s2 = &D_80183494; *var_s2 != 0; var_s2++) {
        otherEnt = self + *var_s2;
        otherEnt->facingLeft = self->facingLeft;
        otherEnt->ext.GH_Props.unkA8 = 0;
    }
    D_8006C384.y = self->ext.GH_Props.unkB0[0];
    D_8006C38C.y = self->ext.GH_Props.unkB4[0];
}

void EntityBladeSword(Entity* self) {
    Primitive *prim, *prim2;
    s32 x0, x1, y0, y1;
    s16 primIndex;
    s16 angle;
    s32 i;

    if (self->ext.et_801D1BB8.unk8C != 0) {
        self->step = 8;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGurkhaBlade);
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->drawFlags |= FLAG_DRAW_ROTZ;
        primIndex = g_api.AllocPrimitives(PRIM_G4, 6);
        if (primIndex == -1) {
            self->ext.et_801D1BB8.prim = NULL;
            break;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.et_801D1BB8.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;

        for (i = 0; prim != NULL; prim = prim->next) {
            prim->r0 = i;
            prim->g0 = i;
            prim->b0 = i;
            i += 10;
            prim->r2 = i;
            prim->g2 = i;
            prim->b2 = i;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r2);
            prim->x0 = self->posX.i.hi;
            prim->y0 = self->posY.i.hi;
            LOW(prim->x1) = LOW(prim->x0);
            LOW(prim->x2) = LOW(prim->x0);
            LOW(prim->x3) = LOW(prim->x0);
            prim->priority = self->zPriority;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        }

    case 1:
        self->rotZ = self->ext.et_801D1BB8.unk9C;
        break;

    case 24:
        self->hitboxState = 0;
        self->flags |= FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        break;

    case 8:
        if (self->facingLeft == 0) {
            self->velocityX = FIX(-8.0);
        } else {
            self->velocityX = FIX(8.0);
        }
        MoveEntity();
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
    }

    angle = self->rotZ;
    self->hitboxOffX = -1 * (rsin(angle) * 13) >> 12;
    self->hitboxOffY = +1 * (rcos(angle) * 13) >> 12;

    prim = self->ext.et_801D1BB8.prim;
    if (prim != NULL) {
        for (i = 0; i < 5; i++) {
            prim2 = prim->next;
            LOW(prim->x0) = LOW(prim2->x0);
            LOW(prim->x1) = LOW(prim2->x1);
            LOW(prim->x2) = LOW(prim2->x2);
            LOW(prim->x3) = LOW(prim2->x3);
            if (self->ext.et_801D1BB8.unk8D) {
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            } else {
                prim->drawMode = DRAW_HIDE | DRAW_UNK02;
            }
            prim = prim2;
        }
    }

    angle = self->rotZ;
    if (self->facingLeft != 0) {
        angle = -angle;
    }

    x0 = (-1 * (rsin(angle) * 20) >> 12) + self->posX.i.hi;
    y0 = (+1 * (rcos(angle) * 20) >> 12) + self->posY.i.hi;
    x1 = (+1 * (rsin(angle) * 4) >> 12) + self->posX.i.hi;
    y1 = (-1 * (rcos(angle) * 4) >> 12) + self->posY.i.hi;

    LOW(prim->x2) = LOW(prim->x0);
    LOW(prim->x3) = LOW(prim->x1);

    prim->x0 = x0;
    prim->y0 = y0;
    prim->y1 = y1;
    prim->x1 = x1;

    if (self->ext.et_801D1BB8.unk8D) {
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
    } else {
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
    }
}
