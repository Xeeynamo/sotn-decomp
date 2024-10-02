// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"
#include "sfx.h"

void EntityHammerWeapon(Entity* self) {
    s16 temp_s0;
    s32 velY;
    s32 temp_s1;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B98);
        self->hitboxWidth = 10;
        self->hitboxHeight = 10;
        self->drawFlags |= FLAG_DRAW_ROTZ;

    case 1:
        angle = *(u16*)&self->ext.stub[0x20];
        self->rotZ = angle;
        self->hitboxOffX = ((u32)(rsin(angle) * 0xD) >> 0xA);
        self->hitboxOffY = (-(rcos(angle) * 0x34) >> 0xC);
        break;

    case 24:
        switch (self->step_s) {
        case 0:
            temp_s1 = (Random() & 0x1F) + 0x10;
            temp_s0 = (Random() * 6) + 0x900;
            self->velocityX = (temp_s1 * rcos(temp_s0)) / 2;
            velY = temp_s1 * rsin(temp_s0);
            self->hitboxState = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;
            self->velocityY = velY;
            break;

        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            func_801CDC80(&self->rotZ, 0x800, 0x20);
            break;
        }
    }
}

void func_801CF778(void) {
    ET_801CF254* et = &g_CurrentEntity[15].ext.et_801CF254;
    et->unk9C = et->next->ext.et_801CF254.unk9C + 0x300;
}

int func_801CF7A0(Entity* ent) {
    Entity* otherEnt;
    s32 step;
    s32 xDistance;

    if (g_CurrentEntity->ext.et_801CE4CC.unk8E != 0) {
        --g_CurrentEntity->ext.et_801CE4CC.unk8E;
    }

    xDistance = ent->posX.i.hi - PLAYER.posX.i.hi;

    if (g_CurrentEntity->facingLeft) {
        xDistance = -xDistance;
    }

    if (xDistance < -16) {
        func_801CE1E8(10);
        return;
    }

    if ((u8)g_CurrentEntity->ext.generic.unk84.S8.unk0 == 1) {
        otherEnt = g_CurrentEntity + 10;
    } else {
        otherEnt = g_CurrentEntity + 13;
    }

    if (func_801CE120(otherEnt, g_CurrentEntity->facingLeft)) {
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

    if (xDistance >= 129) {
        step = 8;
    }

    if (g_CurrentEntity->ext.et_801CE4CC.unk8E == 0) {
        if (xDistance < 160) {
            step = 6;
            g_CurrentEntity->ext.et_801CE4CC.unk8E = 3;
            g_CurrentEntity->ext.gurkhaSword.unk8C = 1;
        }
        if (xDistance < 64) {
            g_CurrentEntity->ext.gurkhaSword.unk8C = 0;
        }
    }

    if (step != g_CurrentEntity->step) {
        do {
            func_801CE1E8(step);
        } while (0); // no idea why, found by permuter
    }

    if ((g_CurrentEntity->step == 7) && (step == 5)) {
        g_CurrentEntity->ext.factory.unkB0 = 1;
    }
}

void EntityGurkha(Entity* self) {
    Collider collider;
    Entity* otherEnt;
    Entity* var_s3;
    s16* var_s2;
    s16* var_s4;
    u16 zPriority;

    if ((self->step & 1) && (self->hitFlags & 3)) {
        func_801CE1E8(0xC);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < 24)) {
        PlaySfxPositional(0x742);
        func_801CE1E8(0x18);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BA4);
        self->animCurFrame = 3;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->facingLeft = self->params;
        /* fallthrough */
    case 1:
        if (UnkCollisionFunc3(D_80182EF4) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step++;
        }
        break;
    case 2:
        var_s3 = self;
        for (var_s4 = &D_80182F04; *var_s4 != 0; var_s4 += 5) {
            otherEnt = self + var_s4[0];
            CreateEntityFromCurrentEntity(E_GURKHA_BODY_PARTS, otherEnt);
            otherEnt->ext.GH_Props.unk9E = var_s4[2];
            otherEnt->ext.GH_Props.parent = self + var_s4[1];
            otherEnt->params = var_s4[3] + 0x100;
            zPriority = self->zPriority + var_s4[4];
            otherEnt->unk60 = var_s3;
            var_s3 = otherEnt;
            var_s3->unk5C = self;
            var_s3->zPriority = zPriority;
        }
        self->unk60 = var_s3;
        self->unk5C = NULL;
        CreateEntityFromCurrentEntity(E_GURKHA_SWORD, self + 15);
        (self + 15)->ext.GH_Props.parent = self + 5;
        (self + 15)->params = 0x14;
        (self + 15)->ext.GH_Props.unk9E = 0;
        (self + 15)->zPriority = self->zPriority + 3;
        self->step++;
        /* fallthrough */
    case 3:
        self->ext.GH_Props.unk8E = 3;
        func_801CE228();
        func_801CE1E8(0xB);
        break;
    case 5:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_8018302C;
        } else {
            var_s2 = D_80183044;
        }
        func_801CDF1C(var_s2, &D_801830F8, 0);
        func_801CDE10(var_s2);
        func_801CE2CC(var_s2);
        func_801CF778();
        func_801CE258(&D_80182F9C);
        if (self->ext.GH_Props.unkB0[0] > 1) {
            collider.unk18 = 9;
            otherEnt = &self[var_s2[3]];
            func_801CE04C(otherEnt, &collider);
            if (otherEnt->ext.GH_Props.unk88 != 0) {
                otherEnt->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                func_801CF7A0(otherEnt);
            }
        }
        break;
    case 7:
        if (self->step_s == 0) {
            self->ext.GH_Props.unkB0[0] = 1;
            self->step_s++;
        }
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_8018302C;
        } else {
            var_s2 = D_80183044;
        }
        func_801CDF1C(var_s2, &D_80183130, 0);
        func_801CDE10(var_s2);
        func_801CE2CC(var_s2);
        func_801CE258(&D_80182F9C);
        func_801CF778();
        if (self->ext.GH_Props.unkB0[0] > 1) {
            collider.unk18 = 9;
            otherEnt = &self[var_s2[3]];
            func_801CE04C(otherEnt, &collider);
            if (otherEnt->ext.GH_Props.unk88 != 0) {
                otherEnt->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                if (func_801CE120(otherEnt, self->facingLeft ^ 1) != 0) {
                    func_801CE1E8(5);
                } else {
                    func_801CF7A0(self);
                }
            }
        }
        break;
    case 8:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_8018302C;
        } else {
            var_s2 = D_80183044;
        }
        switch (self->step_s) {
        case 0:
            if (self->ext.GH_Props.unk84 == 1) {
                var_s2 = D_80182FBC;
            } else {
                var_s2 = D_80182FD8;
            }
            func_801CDF1C(var_s2, &D_80183098, 0);
            func_801CDE10(var_s2);
            func_801CE2CC(var_s2);
            if (self->ext.GH_Props.unkB0[0] == 0 &&
                self->ext.GH_Props.unkB4[0] == 0) {
                self->step_s++;
            }
            break;
        case 1:
            func_801CDF1C(var_s2, &D_801831F8, 0);
            func_801CDE10(var_s2);
            func_801CE2CC(var_s2);
            func_801CF778();
            if (self->ext.GH_Props.unkB4[0] == 0 &&
                self->ext.GH_Props.unkB0[0] == 0) {
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
            func_801CDF1C(var_s2, &D_80183218, 0);
            func_801CDE10(var_s2);
            func_801CE3FC(var_s2);
            func_801CF778();
            otherEnt = &self[var_s2[3]];
            collider.unk18 = 9;
            func_801CE04C(otherEnt, &collider);
            if (otherEnt->ext.GH_Props.unk88 != 0) {
                PlaySfxPositional(SFX_STOMP_HARD_C);
                otherEnt->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                self->step_s = 1;
                func_801CF7A0(otherEnt);
            }
            break;
        }
        func_801CE258(&D_80182F9C);
        break;
    case 11:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_80182FBC;
        } else {
            var_s2 = D_80182FD8;
        }
        switch (self->step_s) {
        case 0:
            func_801CDF1C(var_s2, &D_80183284, 0);
            func_801CDE10(var_s2);
            func_801CE2CC(var_s2);
            func_801CE258(&D_80182F9C);
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB4[0] == 0)) {
                self->ext.GH_Props.unk80 = 0;
                self->step_s++;
            }
            break;
        case 1:
            self->ext.GH_Props.unk80 += 0x80;
            self->posY.val += rcos(self->ext.GH_Props.unk80) * 2;
            func_801CDAC8(self + 9, self + 10);
            (self + 10)->ext.GH_Props.unkA8 = 1;
            (self + 9)->ext.GH_Props.rotZ = (self + 9)->ext.GH_Props.unkA4;
            (self + 10)->ext.GH_Props.rotZ = (self + 10)->ext.GH_Props.unkA4;
            func_801CDAC8(self + 12, self + 13);
            (self + 13)->ext.GH_Props.unkA8 = 1;
            (self + 12)->ext.GH_Props.rotZ = (self + 12)->ext.GH_Props.unkA4;
            (self + 13)->ext.GH_Props.rotZ = (self + 13)->ext.GH_Props.unkA4;
            func_801CE258(&D_80182F9C);
            if ((self->ext.GH_Props.unk80 & 0x7FF) == 0) {
                func_801CF7A0(self);
            }
            break;
        }
        break;
    case 6:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_80182FBC;
        } else {
            var_s2 = D_80182FD8;
        }
        switch (self->step_s) {
        case 0:
            func_801CDF1C(var_s2, &D_80183360, 0);
            func_801CDE10(var_s2);
            func_801CE2CC(var_s2);
            func_801CE258(&D_80182F9C);
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB4[0] == 0)) {
                PlaySfxPositional(0x740);
                // we appear to write 0x10 twice here, weird
                self->ext.GH_Props.unk80 = 0x10;
                (self + 15)->ext.GH_Props.unkA6 = 0;
                self->ext.GH_Props.unk80 = 0x10;
                if (self->ext.GH_Props.unk8C != 0) {
                    self->step_s = 1;
                } else {
                    self->step_s = 2;
                }
            }
            break;
        case 1:
            otherEnt = self + 15;
            if ((self + 15)->ext.GH_Props.rotZ > -0x800) {
                (self + 15)->ext.GH_Props.unkA6 -= 0x10;
            } else {
                (self + 15)->ext.GH_Props.unkA6 += 0x10;
            }
            if (otherEnt->ext.GH_Props.unkA6 > -0x20) {
                otherEnt->ext.GH_Props.unkA6 = -0x20;
            }
            otherEnt->ext.GH_Props.rotZ += otherEnt->ext.GH_Props.unkA6;
            func_801CE258(&D_80182F9C);
            if (otherEnt->ext.GH_Props.rotZ < -0x1100) {
                otherEnt->ext.GH_Props.rotZ = -0x100;
                self->step_s++;
            }
            break;
        case 2:
            if (--self->ext.GH_Props.unk80 == 0) {
                self->step_s++;
            }
            break;
        case 3:
            func_801CDF1C(var_s2, &D_80183378, 0);
            func_801CDE10(var_s2);
            func_801CE2CC(var_s2);
            func_801CE258(&D_80182F9C);
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB4[0] == 0)) {
                if (self->facingLeft == 0) {
                    self->velocityX = FIX(-4);
                } else {
                    self->velocityX = FIX(4);
                }
                self->step_s++;
            }
            break;
        case 4:
            (self + 15)->ext.GH_Props.unk8C = self->ext.GH_Props.unk8C;
            self->step_s++;
            /* fallthrough */
        case 5:
            if (self->ext.GH_Props.unk8C != 0) {
                if (self->ext.GH_Props.unk84 == 1) {
                    var_s2 = D_80182FF4;
                } else {
                    var_s2 = D_80183010;
                }
                (self + 15)->ext.GH_Props.unkA8 = 1;
            }
            otherEnt = self + var_s2[1];
            otherEnt->posX.val += self->velocityX;
            self->velocityX -= self->velocityX / 8;
            func_801CDF1C(var_s2, &D_801833A0, 0);
            func_801CDE10(var_s2);
            func_801CE2CC(var_s2);
            func_801CE258(&D_80182F9C);
            if (self->ext.GH_Props.unkB0[0] == 0 &&
                self->ext.GH_Props.unkB4[0] == 0) {
                self->step_s++;
            }
            break;
        case 6:
            if ((self + 15)->ext.GH_Props.unk8C == 0) {
                self->step_s++;
            }
            break;
        case 7:
            if (self->ext.GH_Props.unk8C != 0) {
                if (self->ext.GH_Props.unk84 == 1) {
                    var_s2 = D_80182FF4;
                } else {
                    var_s2 = D_80183010;
                }
            }
            func_801CDF1C(var_s2, &D_80183098, 0);
            func_801CDE10(var_s2);
            func_801CE2CC(var_s2);
            (self + 15)->ext.GH_Props.rotZ += (self + 15)->ext.GH_Props.unkA6;
            (self + 15)->ext.GH_Props.unkA6 -=
                (self + 15)->ext.GH_Props.unkA6 / 16;
            func_801CE258(&D_80182F9C);
            if ((self->ext.GH_Props.unkB0[0] == 0) &&
                (self->ext.GH_Props.unkB4[0] == 0)) {
                SetStep(5);
            }
            break;
        }
        break;
    case 10:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_8018302C;
        } else {
            var_s2 = D_80183044;
        }
        func_801CDF1C(var_s2, &D_80183258, 0);
        func_801CDE10(var_s2);
        func_801CE2CC(var_s2);
        func_801CE258(&D_80182F9C);
        if (self->ext.GH_Props.unkB4[0] == 0) {
            self->facingLeft ^= 1;
            func_801CF7A0(self);
        }
        break;
    case 12:
        if (self->step_s == 0) {
            PlaySfxPositional(0x741);
            self->step_s++;
        }
        if (self->ext.GH_Props.unk84 == 1) {
            var_s2 = D_80182FBC;
        } else {
            var_s2 = D_80182FD8;
        }
        func_801CDF1C(var_s2, &D_801833CC, 0);
        func_801CDE10(var_s2);
        func_801CE2CC(var_s2);
        func_801CE258(&D_80182F9C);
        if (self->ext.GH_Props.unkB0[0] == 0 &&
            self->ext.GH_Props.unkB4[0] == 0) {
            func_801CF7A0(self);
        }
        break;
    case 24:
        switch (self->step_s) {
        case 0:
            for (var_s2 = &D_80182F9C; *var_s2 != 0; var_s2++) {
                otherEnt = self + *var_s2;
                otherEnt->step = 0x18;
                otherEnt->step_s = 0;
                otherEnt->hitboxState = 0;
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
    for (var_s2 = &D_80182F9C; *var_s2 != 0; var_s2++) {
        otherEnt = self + *var_s2;
        otherEnt->facingLeft = self->facingLeft;
        otherEnt->ext.GH_Props.unkA8 = 0;
    }
    D_8006C384.y = self->ext.GH_Props.unkB0[0];
    D_8006C38C.y = self->ext.GH_Props.unkB4[0];
    return;
}

void EntityGurkhaSword(Entity* self) {
    s16 angle;
    s32 rnd;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BB0);
        self->hitboxWidth = 8;
        self->hitboxHeight = 8;
        self->drawFlags |= FLAG_DRAW_ROTZ;
        break;

    case 1:
        angle = self->ext.gurkhaSword.unk9C;
        self->rotZ = angle;
        self->hitboxOffX = (u32)rsin(angle) >> 8;
        self->hitboxOffY = -(rcos(angle) * 16) >> 0xC;
        if (self->ext.gurkhaSword.unk8C) {
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
        self->rotZ -= 0x100;
        self->ext.gurkhaSword.unk9C = self->rotZ;
        self->ext.gurkhaSword.unkA6 = -0xC0;
        angle = self->rotZ;
        self->hitboxOffX = (u32)rsin(self->rotZ) >> 8;
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
            self->ext.gurkhaSword.unk8C = 0;
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
            self->ext.gurkhaSword.unk80 = (Random() & 0x1F) + 0x20;
            self->hitboxState = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;
            break;

        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            self->rotZ += self->ext.gurkhaSword.unkA6;
            if (--self->ext.gurkhaSword.unk80 == 0) {
                self->step = 0;
                self->pfnUpdate = EntityExplosion;
                self->params = 0;
                self->drawFlags = FLAG_DRAW_DEFAULT;
            }
        }
        break;
    }
}
