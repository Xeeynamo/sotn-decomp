// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"

// For EntityGurkha
static u16 D_80182EF4[] = {0x0, 0x9, 0x0, 0x4, 0x4, -0x4, -0x8, 0x0,};
extern bladeBodyPartsInit D_80182F04[];
extern s16 D_80182F9C;
extern s16 D_80182FBC[];
extern s16 D_80182FD8[];
extern s16 D_80182FF4[];
extern s16 D_80183010[];
extern s16 D_8018302C[];
extern s16 D_80183044[];
extern s16 D_80183098[];
extern s16 D_801830F8[];
extern s16 D_80183130[];
extern s16 D_801831F8[];
extern s16 D_80183218[];
extern s16 D_80183258[];
extern s16 D_80183284[];
extern s16 D_80183360[];
extern s16 D_80183378[];
extern s16 D_801833A0[];
extern s16 D_801833CC[];

void func_801CF778(void) {
    Entity* currEnt15;
    Entity* ent15Parent;
    currEnt15 = &g_CurrentEntity[15];
    ent15Parent = currEnt15->ext.GH_Props.parent;
    currEnt15->ext.GH_Props.rotate = ent15Parent->ext.GH_Props.rotate + 0x300;
}

int func_801CF7A0(Entity* ent) {
    Entity* otherEnt;
    s32 xDistance;
    s32 step;

    if (g_CurrentEntity->ext.GH_Props.unk8E) {
        --g_CurrentEntity->ext.GH_Props.unk8E;
    }
    otherEnt = &PLAYER;
    xDistance = ent->posX.i.hi - otherEnt->posX.i.hi;

    if (g_CurrentEntity->facingLeft) {
        xDistance = -xDistance;
    }

    if (xDistance < -16) {
        func_801CE1E8(10);
        return;
    }

    if (g_CurrentEntity->ext.GH_Props.unk84 == 1) {
        otherEnt = g_CurrentEntity + 10;
    } else {
        otherEnt = g_CurrentEntity + 13;
    }

    step = func_801CE120(otherEnt, g_CurrentEntity->facingLeft);
    if (step) {
        func_801CE1E8(7);
        return;
    }

    step = 5;

    if (xDistance < 48) {
        step = 7;
    }

    if (xDistance < 80) {
        step = 5;
    }

    if (xDistance > 128) {
        step = 8;
    }

    if (!g_CurrentEntity->ext.GH_Props.unk8E) {
        if (xDistance < 160) {
            g_CurrentEntity->ext.GH_Props.unk8E = 3;
            step = 6;
            g_CurrentEntity->ext.GH_Props.unk8C = 1;
        }
        if (xDistance < 64) {
            g_CurrentEntity->ext.GH_Props.unk8C = 0;
        }
    }

    if (step != g_CurrentEntity->step) {
        do {
            func_801CE1E8(step);
        } while (0); // no idea why, found by permuter
    }

    if ((g_CurrentEntity->step == 7) && (step == 5)) {
        g_CurrentEntity->ext.GH_Props.unkB0[0] = 1;
    }
}

void EntityGurkha(Entity* self) {
    Collider collider;
    Entity* ent_s0;
    Entity* ent_s3;
    s16* var_s1;
    bladeBodyPartsInit* parts;
    s32 res;

    if ((self->step & 1) && (self->hitFlags & 3)) {
        func_801CE1E8(0xC);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < 24)) {
        PlaySfxPositional(0x742);
        func_801CE1E8(0x18);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGurkhaType1);
        self->animCurFrame = 3;
        self->facingLeft = self->params;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        /* fallthrough */
    case 1:
        if (UnkCollisionFunc3(D_80182EF4) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step++;
        }
        break;
    case 2:
        for (parts = D_80182F04, ent_s3 = self; parts->eArrayOffset; parts++) {
            ent_s0 = self + parts->eArrayOffset;
            CreateEntityFromCurrentEntity(E_GURKHA_BODY_PARTS, ent_s0);
            ent_s0->ext.GH_Props.length = parts->length;
            ent_s0->ext.GH_Props.parent = self + parts->eArrayParentOffset;
            ent_s0->params = parts->params + 0x100;
            ent_s0->zPriority = self->zPriority + parts->zOffset;
            ent_s0->unk5C = self;
            ent_s0->unk60 = ent_s3;
            ent_s3 = ent_s0;
        }
        self->unk60 = ent_s3;
        self->unk5C = NULL;
        ent_s0 = self + 15;
        CreateEntityFromCurrentEntity(E_GURKHA_SWORD, ent_s0);
        ent_s0->ext.GH_Props.length = 0;
        ent_s0->ext.GH_Props.parent = self + 5;
        ent_s0->zPriority = self->zPriority + 3;
        ent_s0->params = 0x14;
        self->step++;
        /* fallthrough */
    case 3:
        self->ext.GH_Props.unk8E = 3;
        func_801CE228();
        func_801CE1E8(0xB);
        break;
    case 5:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s1 = D_8018302C;
        } else {
            var_s1 = D_80183044;
        }
        func_801CDF1C(var_s1, &D_801830F8, 0);
        func_801CDE10(var_s1);
        func_801CE2CC(var_s1);
        func_801CF778();
        polarPlacePartsList(&D_80182F9C);
        if (self->ext.GH_Props.unkB0[0] > 1) {
            collider.unk18 = 9;
            ent_s0 = &self[var_s1[3]];
            func_801CE04C(ent_s0, &collider);
            if (ent_s0->ext.GH_Props.unk88) {
                ent_s0->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                func_801CF7A0(ent_s0);
            }
        }
        break;
    case 7:
        if (!self->step_s) {
            self->ext.GH_Props.unkB0[0] = 1;
            self->step_s++;
        }
        if (self->ext.GH_Props.unk84 == 1) {
            var_s1 = D_8018302C;
        } else {
            var_s1 = D_80183044;
        }
        func_801CDF1C(var_s1, &D_80183130, 0);
        func_801CDE10(var_s1);
        func_801CE2CC(var_s1);
        polarPlacePartsList(&D_80182F9C);
        func_801CF778();
        if (self->ext.GH_Props.unkB0[0] > 1) {
            collider.unk18 = 9;
            ent_s0 = &self[var_s1[3]];
            func_801CE04C(ent_s0, &collider);
            if (ent_s0->ext.GH_Props.unk88) {
                ent_s0->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                res = func_801CE120(ent_s0, self->facingLeft ^ 1);
                if (res) {
                    func_801CE1E8(5);
                } else {
                    func_801CF7A0(self);
                }
            }
        }
        break;
    case 8:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s1 = D_8018302C;
        } else {
            var_s1 = D_80183044;
        }
        switch (self->step_s) {
        case 0:
            if (self->ext.GH_Props.unk84 == 1) {
                var_s1 = D_80182FBC;
            } else {
                var_s1 = D_80182FD8;
            }
            func_801CDF1C(var_s1, &D_80183098, 0);
            func_801CDE10(var_s1);
            func_801CE2CC(var_s1);
            if (!self->ext.GH_Props.unkB0[0] &&
                !self->ext.GH_Props.unkB4[0]) {
                self->step_s++;
            }
            break;
        case 1:
            func_801CDF1C(var_s1, &D_801831F8, 0);
            func_801CDE10(var_s1);
            func_801CE2CC(var_s1);
            func_801CF778();
            if (!self->ext.GH_Props.unkB4[0] &&
                !self->ext.GH_Props.unkB0[0]) {
                self->step_s++;
            }
            break;
        case 2:
            if (self->facingLeft) {
                self->velocityX = FIX(2.5);
            } else {
                self->velocityX = FIX(-2.5);
            }
            self->velocityY = FIX(-1);
            func_801CE228();
            self->step_s++;
            /* fallthrough */
        case 3:
            MoveEntity();
            self->velocityY += FIX(11.0 / 128);
            func_801CDF1C(var_s1, &D_80183218, 0);
            func_801CDE10(var_s1);
            func_801CE3FC(var_s1);
            func_801CF778();
            ent_s0 = &self[var_s1[3]];
            collider.unk18 = 9;
            func_801CE04C(ent_s0, &collider);
            if (ent_s0->ext.GH_Props.unk88) {
                PlaySfxPositional(SFX_STOMP_HARD_C);
                ent_s0->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                self->step_s = 1;
                func_801CF7A0(ent_s0);
            }
            break;
        }
        polarPlacePartsList(&D_80182F9C);
        break;
    case 11:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s1 = D_80182FBC;
        } else {
            var_s1 = D_80182FD8;
        }
        switch (self->step_s) {
        case 0:
            func_801CDF1C(var_s1, &D_80183284, 0);
            func_801CDE10(var_s1);
            func_801CE2CC(var_s1);
            polarPlacePartsList(&D_80182F9C);
            if (!self->ext.GH_Props.unkB0[0] &&
                !self->ext.GH_Props.unkB4[0]) {
                self->ext.GH_Props.unk80 = 0;
                self->step_s++;
            }
            break;
        case 1:
            self->ext.GH_Props.unk80 += 0x80;
            self->posY.val += rcos(self->ext.GH_Props.unk80) * 2;
            ent_s0 = self + 9;
            ent_s3 = self + 10;
            func_801CDAC8(ent_s0, ent_s3);
            ent_s0->ext.GH_Props.rotate = ent_s0->ext.GH_Props.unkA4;
            ent_s3->ext.GH_Props.rotate = ent_s3->ext.GH_Props.unkA4;
            ent_s3->ext.GH_Props.unkA8 = 1;
            ent_s0 = self + 12;
            ent_s3 = self + 13;
            func_801CDAC8(ent_s0, ent_s3);
            ent_s0->ext.GH_Props.rotate = ent_s0->ext.GH_Props.unkA4;
            ent_s3->ext.GH_Props.rotate = ent_s3->ext.GH_Props.unkA4;
            ent_s3->ext.GH_Props.unkA8 = 1;
            polarPlacePartsList(&D_80182F9C);
            if ((self->ext.GH_Props.unk80 & 0x7FF) == 0) {
                func_801CF7A0(self);
            }
            break;
        }
        break;
    case 6:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s1 = D_80182FBC;
        } else {
            var_s1 = D_80182FD8;
        }
        switch (self->step_s) {
        case 0:
            func_801CDF1C(var_s1, &D_80183360, 0);
            func_801CDE10(var_s1);
            func_801CE2CC(var_s1);
            polarPlacePartsList(&D_80182F9C);
            if (!self->ext.GH_Props.unkB0[0] &&
                !self->ext.GH_Props.unkB4[0]) {
                PlaySfxPositional(0x740);
                // we appear to write 0x10 twice here, weird
                self->ext.GH_Props.unk80 = 0x10;
                ent_s0 = self + 15;
                ent_s0->ext.GH_Props.unkA6 = 0;
                self->ext.GH_Props.unk80 = 0x10;
                if (self->ext.GH_Props.unk8C) {
                    self->step_s = 1;
                } else {
                    self->step_s = 2;
                }
            }
            break;
        case 1:
            ent_s0 = self + 15;
            if (ent_s0->ext.GH_Props.rotate > -0x800) {
                ent_s0->ext.GH_Props.unkA6 -= 0x10;
            } else {
                ent_s0->ext.GH_Props.unkA6 += 0x10;
            }
            if (ent_s0->ext.GH_Props.unkA6 > -0x20) {
                ent_s0->ext.GH_Props.unkA6 = -0x20;
            }
            ent_s0->ext.GH_Props.rotate += ent_s0->ext.GH_Props.unkA6;
            polarPlacePartsList(&D_80182F9C);
            if (ent_s0->ext.GH_Props.rotate < -0x1100) {
                ent_s0->ext.GH_Props.rotate = -0x100;
                self->step_s++;
            }
            break;
        case 2:
            if (!--self->ext.GH_Props.unk80) {
                self->step_s++;
            }
            break;
        case 3:
            func_801CDF1C(var_s1, &D_80183378, 0);
            func_801CDE10(var_s1);
            func_801CE2CC(var_s1);
            polarPlacePartsList(&D_80182F9C);
            if (!self->ext.GH_Props.unkB0[0] &&
                !self->ext.GH_Props.unkB4[0]) {
                if (self->facingLeft) {
                    self->velocityX = FIX(4);
                } else {
                    self->velocityX = FIX(-4);
                }
                self->step_s++;
            }
            break;
        case 4:
            ent_s0 = self + 15;
            ent_s0->ext.GH_Props.unk8C = self->ext.GH_Props.unk8C;
            self->step_s++;
            /* fallthrough */
        case 5:
            if (self->ext.GH_Props.unk8C) {
                if (self->ext.GH_Props.unk84 == 1) {
                    var_s1 = D_80182FF4;
                } else {
                    var_s1 = D_80183010;
                }
                ent_s0 = self + 15;
                ent_s0->ext.GH_Props.unkA8 = 1;
            }
            ent_s0 = self + var_s1[1];
            ent_s0->posX.val += self->velocityX;
            self->velocityX -= self->velocityX / 8;
            func_801CDF1C(var_s1, &D_801833A0, 0);
            func_801CDE10(var_s1);
            func_801CE2CC(var_s1);
            polarPlacePartsList(&D_80182F9C);
            if (!self->ext.GH_Props.unkB0[0] &&
                !self->ext.GH_Props.unkB4[0]) {
                self->step_s++;
            }
            break;
        case 6:
            ent_s0 = self + 15;
            if (!ent_s0->ext.GH_Props.unk8C) {
                self->step_s++;
            }
            break;
        case 7:
            if (self->ext.GH_Props.unk8C) {
                if (self->ext.GH_Props.unk84 == 1) {
                    var_s1 = D_80182FF4;
                } else {
                    var_s1 = D_80183010;
                }
            }
            func_801CDF1C(var_s1, &D_80183098, 0);
            func_801CDE10(var_s1);
            func_801CE2CC(var_s1);
            ent_s0 = self + 15;
            ent_s0->ext.GH_Props.rotate += ent_s0->ext.GH_Props.unkA6;
            ent_s0->ext.GH_Props.unkA6 -=
                ent_s0->ext.GH_Props.unkA6 / 16;
            polarPlacePartsList(&D_80182F9C);
            if (!self->ext.GH_Props.unkB0[0] &&
                !self->ext.GH_Props.unkB4[0]) {
                SetStep(5);
            }
            break;
        }
        break;
    case 10:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s1 = D_8018302C;
        } else {
            var_s1 = D_80183044;
        }
        func_801CDF1C(var_s1, &D_80183258, 0);
        func_801CDE10(var_s1);
        func_801CE2CC(var_s1);
        polarPlacePartsList(&D_80182F9C);
        if (!self->ext.GH_Props.unkB4[0]) {
            self->facingLeft ^= 1;
            func_801CF7A0(self);
        }
        break;
    case 12:
        if (!self->step_s) {
            PlaySfxPositional(0x741);
            self->step_s++;
        }
        if (self->ext.GH_Props.unk84 == 1) {
            var_s1 = D_80182FBC;
        } else {
            var_s1 = D_80182FD8;
        }
        func_801CDF1C(var_s1, &D_801833CC, 0);
        func_801CDE10(var_s1);
        func_801CE2CC(var_s1);
        polarPlacePartsList(&D_80182F9C);
        if (!self->ext.GH_Props.unkB0[0] &&
            !self->ext.GH_Props.unkB4[0]) {
            func_801CF7A0(self);
        }
        break;
    case 24:
        switch (self->step_s) {
        case 0:
            for (var_s1 = &D_80182F9C; *var_s1; var_s1++) {
                ent_s0 = self + *var_s1;
                ent_s0->step = 0x18;
                ent_s0->step_s = 0;
                ent_s0->hitboxState = 0;
            }
            self->velocityY = FIX(-2);
            self->hitboxState = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityY += FIX(24.0 / 128);
            if (!(g_Timer & 7)) {
                if (Random() & 1) {
                    PlaySfxPositional(SFX_FM_EXPLODE_B);
                } else {
                    PlaySfxPositional(SFX_EXPLODE_D);
                }
            }
            return;
        }
        break;
    }
    for (var_s1 = &D_80182F9C; *var_s1; var_s1++) {
        ent_s0 = self + *var_s1;
        ent_s0->facingLeft = self->facingLeft;
        ent_s0->ext.GH_Props.unkA8 = 0;
    }
    D_8006C384.y = self->ext.GH_Props.unkB0[0];
    D_8006C38C.y = self->ext.GH_Props.unkB4[0];
}

void EntityGurkhaSword(Entity* self) {
    s16 angle;
    s32 rnd;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGurkhaSword);
        self->hitboxWidth = 8;
        self->hitboxHeight = 8;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        break;

    case 1:
        angle = self->ext.GH_Props.rotate;
        self->rotate = angle;
        self->hitboxOffX = (u32)rsin(angle) >> 8;
        self->hitboxOffY = -(rcos(angle) * 16) >> 0xC;
        if (self->ext.GH_Props.unk8C) {
            self->step++;
        }
        break;

    case 2:
        if (self->facingLeft == 0) {
            self->velocityX = FIX(-8);
        } else {
            self->velocityX = FIX(8);
        }
        self->step++;

    case 3:
        MoveEntity();
        self->rotate -= 0x100;
        self->ext.GH_Props.rotate = self->rotate;
        self->ext.GH_Props.unkA6 = -0xC0;
        angle = self->rotate;
        self->hitboxOffX = (u32)rsin(self->rotate) >> 8;
        self->hitboxOffY = -(rcos(angle) * 16) >> 0xC;

        if (self->facingLeft != 0) {
            self->velocityX -= FIX(0.25);
        } else {
            self->velocityX += FIX(0.25);
        }

        if ((g_Timer % 16) == 0) {
            PlaySfxPositional(SFX_ARROW_SHOT_A);
        }

        if (abs(self->velocityX) == 0x80000) {
            self->ext.GH_Props.unk8C = 0;
            self->step = 1;
        }
        break;

    case 24:
        switch (self->step_s) {
        case 0:
            rnd = (Random() & 0x1F) + 0x10;
            angle = (Random() * 6) + 0x900;
            self->velocityX = (rnd * rcos(angle)) / 2;
            self->velocityY = rnd * rsin(angle);
            self->ext.GH_Props.unk80 = (Random() & 0x1F) + 0x20;
            self->hitboxState = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;
            break;

        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            self->rotate += self->ext.GH_Props.unkA6;
            if (--self->ext.GH_Props.unk80 == 0) {
                self->step = 0;
                self->pfnUpdate = EntityExplosion;
                self->params = 0;
                self->drawFlags = FLAG_DRAW_DEFAULT;
            }
        }
        break;
    }
}
