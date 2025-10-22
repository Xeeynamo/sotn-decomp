// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

// clang-format off
static u16 D_us_8018219C[] = {0, 9, 0, 4, 4, -4, -8, 0};
static giantBroBodyPartsInit D_us_801821AC[] = {
    {9, 0, 16, 7, 1},    {10, 9, 14, 8, 2},    {11, 10, 0, 9, 3},
    {12, 0, 16, 13, -1}, {13, 12, 14, 14, -2}, {14, 13, 0, 15, -3},
    {2, 0, -18, 2, 1},   {1, 2, -4, 16, 0},    {3, 2, 0, 4, 2},
    {4, 3, 10, 5, 5},    {5, 4, 13, 6, 4},     {6, 2, 0, 10, -2},
    {7, 6, 10, 11, -4},  {8, 7, 13, 12, -3},   {0, 0, 0, 0, 0}};
static s16 D_us_80182244[] = {2, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
static s16 D_us_80182264[] = {9, 10, 12, 13, 11, 14, 2, 1, 4, 5, 7, 8, 15, 0};
static s16 D_us_80182280[] = {12, 13, 9, 10, 14, 11, 2, 1, 4, 5, 7, 8, 15, 0};
static s16 D_us_8018229C[] = {9, 10, 12, 13, 0}; // unused
static s16 D_us_801822A8[] = {12, 13, 9, 10, 0}; // unused
static s16 D_us_801822B4[] = {9, 10, 12, 13, 2, 255, 255, 7, 8, 0}; // unused
static s16 D_us_801822C8[] = {12, 13, 9, 10, 2, 7, 8, 255, 255, 0}; // unused
static s16 D_us_801822DC[] = {9, 10, 12, 13, 11, 14, 2, 255, 255, 7, 8, 0};
static s16 D_us_801822F4[] = {12, 13, 9, 10, 14, 11, 2, 7, 8, 255, 255, 0};
static s16 D_us_8018230C[] = {9, 10, 12, 13, 11, 14, 2, 4, 5, 15, 0};
static s16 D_us_80182324[] = {12, 13, 9, 10, 14, 11, 2, 4, 5, 15, 0};
static s16 D_us_8018233C[] = {9, 10, 12, 13, 11, 14, 0}; //unused
static s16 D_us_8018234C[] = {12, 13, 9, 10, 14, 11, 0}; //unused

static s16 D_us_8018235C[] = {0x000, 0x000, 0x080, -0x100, 0x000, 0x000, 0x000,
                              0x000, 0x100, 0x680, 0x000,  0x200, 0x2C0, 0x000};
static unkStr_801CDD80 D_us_80182378[] = {
    {32, D_us_8018235C},
    {0, 0}
};

static s16 D_us_80182388[] = {0x100, 0x0C0, -0x100, -0x180}; //unused
static s16 D_us_80182390[] = {0x040, -0x020, 0x020,  -0x220, 0x000, -0x100,
                              0x000, -0x0C0, -0x0C0, 0x020,  0x100, 0x000};
static s16 D_us_801823A8[] = {-0x090, -0x090, 0x158, 0x000,  0x000,  -0x020,
                              0x000,  0x080,  0x100, -0x0C0, -0x0C0, 0x000};
static s16 D_us_801823C0[] = {-0x100, -0x180, 0x100, 0x0C0,  0x000,  0x040,
                              0x000,  0x100,  0x280, -0x140, -0x140, 0x000};
static unkStr_801CDD80 D_us_801823D8[] = {
    {14, D_us_80182390},
    {14, D_us_801823A8},
    {14, D_us_801823C0},
    {0, 0}
};

static s16 D_us_801823F8[] = {0x200, 0x0C0, -0x100, -0x180, 0x000,  -0x040,
                              0x000, 0x100, 0x280,  -0x140, -0x140, 0x000};
static unkStr_801CDD80 D_us_80182410[] = {
    {16, D_us_801823A8},
    {16, D_us_80182390},
    {16, D_us_801823F8},
    {0, 0}
};

static s16 D_us_80182430[] = {0x100,  0x040,  0x080, -0x400, 0x000, -0x380,
                              -0x080, -0x0C0, 0x080, 0x000,  0x300, 0x000};
static s16 D_us_80182448[] = {0x0C0,  -0x080, 0x100, -0x480, 0x000, -0x400,
                              -0x0C0, -0x040, 0x100, -0x080, 0x240, 0x000};
static s16 D_us_80182460[] = {0x080,  -0x100, 0x200, -0x400, 0x000, -0x400,
                              -0x100, -0x100, 0x380, -0x100, 0x040, 0x000};
static s16 D_us_80182478[] = {-0x080, -0x120, 0x280, -0x200, 0x000, -0x200,
                              -0x0C0, 0x000,  0x440, -0x140, 0x000, 0x000};
static s16 D_us_80182490[] = {-0x0C0, -0x180, 0x240, -0x100, -0x180, 0x000,
                              -0x080, 0x000,  0x440, -0x180, -0x040, 0x000};
static s16 D_us_801824A8[] = {0x020,  -0x240, 0x1C0, 0x000,  -0x240, 0x100,
                              -0x080, 0x000,  0x400, -0x140, 0x000,  0x000};
static unkStr_801CDD80 D_us_801824C0[] = {
    {3, D_us_80182430},
    {3, D_us_80182448},
    {3, D_us_80182460},
    {3, D_us_80182478},
    {0, 0}
};
static unkStr_801CDD80 D_us_801824E8[] = {
    {3, D_us_80182490},
    {3, D_us_801824A8},
    {112, D_us_801824A8},
    {0, 0}
};

static s16 D_us_80182508[] = {0x000, 0x000, 0x080, -0x080, 0x000, 0x000,
                              0x000, 0x000, 0x000, 0x000,  0x000, 0x000};
static unkStr_801CDD80 D_us_80182520[] = {
    {32, D_us_80182508},
    {0, 0}
};

static s16 D_us_80182530[] = {0x000, -0x100, 0x080, -0x080, 0x000,
                              0x000, 0x000,  0x100, 0x680,  0x2C0};
static s16 D_us_80182544[] = {0x000, -0x040, 0x200, -0x100, 0x000,
                              0x000, 0x040,  0x580, 0xB00,  0x580};
static s16 D_us_80182558[] = {0x080, -0x040, 0x200, 0x0C0, 0x000,
                              0x000, 0x100,  0x680, 0xC00, 0x600};
static s16 D_us_8018256C[] = {0x000, -0x180, 0x200, -0x080, 0x000,
                              0x000, 0x000,  0x600, 0xA00,  0x400};
static s16 D_us_80182580[] = {-0x100, -0x200, 0x200, -0x080, 0x000,
                              0x000,  -0x040, 0x600, 0x680,  0x200};
static s16 D_us_80182594[] = {0x100, 0x000,  -0x200, -0x180, 0x000,
                              0x000, -0x180, 0x200,  0x600,  -0x100};
static s16 D_us_801825A8[] = {0x000,  -0x100, -0x280, -0x300, 0x000,
                              -0x240, -0x300, 0x200,  0x200,  -0x580};
static s16 D_us_801825BC[] = {0x000,  -0x100, -0x200, -0x340, 0x000,
                              -0x280, -0x300, 0x200,  0x300,  -0x400};
static s16 D_us_801825D0[] = {0x000,  -0x100, -0x180, -0x280, 0x000,
                              -0x180, -0x380, 0x200,  0x380,  -0x380};
static s16 D_us_801825E4[] = {0x000,  -0x100, -0x100, -0x200, 0x000,
                              -0x180, -0x200, 0x180,  0x280,  -0x500};
static s16 D_us_801825F8[] = {0x100,  -0x100, 0x100, -0x100, 0x000,
                              -0x100, -0x100, 0x200, 0x200,  -0x580};
static s16 D_us_8018260C[] = {0x080, -0x080, 0x200, 0x000, 0x000,
                              0x000, -0x080, 0x180, 0x300, -0x4C0};
static s16 D_us_80182620[] = {0x080, 0x080, 0x200, 0x100, 0x000,
                              0x000, 0x080, 0x200, 0x480, -0x400};
static s16 D_us_80182634[] = {0x100, 0x080, -0x100, -0x100, 0x000,
                              0x000, 0x0C0, 0x300,  0x600,  -0x200};
static s16 D_us_80182648[] = {0x280, 0x0C0, -0x1C0, -0x200, 0x000,
                              0x000, 0x040, 0x580,  0xB00,  0x580};
static unkStr_801CDD80 D_us_8018265C[] = {
    {32, D_us_80182530},
    {0, 0}
};
static unkStr_801CDD80 D_us_8018266C[] = {
    {16, D_us_80182544},
    {32, D_us_80182558},
    {9, D_us_8018256C},
    {4, D_us_80182580},
    {5, D_us_80182594},
    {3, D_us_801825A8},
    {4, D_us_801825BC},
    {8, D_us_801825D0},
    {6, D_us_801825E4},
    {6, D_us_801825F8},
    {6, D_us_8018260C},
    {6, D_us_80182620},
    {6, D_us_80182634},
    {16, D_us_80182648},
    {0, 0}
};

static s16 D_us_801826E4[] = {0x0C0, -0x080, 0x180, -0x200, 0x000, -0x200, 0x100,
                              0x180, 0x700,  0xC00, 0x300,  0x500, 0x600,  0x000};
static unkStr_801CDD80 D_us_80182700[] = {
    {16, D_us_801826E4},
    {32, D_us_8018235C},
    {0, 0}
};
// clang-format on

static s32 func_801CE4CC(Entity* self) {
    Entity* otherEnt;
    s32 step;
    s32 dx;

    if (g_CurrentEntity->ext.GH_Props.unk8E) {
        g_CurrentEntity->ext.GH_Props.unk8E--;
    }

    otherEnt = &PLAYER;
    dx = self->posX.i.hi - otherEnt->posX.i.hi;
    if (g_CurrentEntity->facingLeft) {
        dx = -dx;
    }

    if (dx < -16) {
        func_801CE1E8(10);
        return;
    }

    if (g_CurrentEntity->ext.GH_Props.unk84 == 1) {
        otherEnt = g_CurrentEntity + 10;
    } else {
        otherEnt = g_CurrentEntity + 13;
    }

    step = func_801CE120(otherEnt, g_CurrentEntity->facingLeft);
    if (step != 0) {
        func_801CE1E8(7);
        return;
    }
    step = func_801CE120(otherEnt, g_CurrentEntity->facingLeft ^ 1);
    if (step != 0) {
        func_801CE1E8(5);
        return;
    }

    switch (g_CurrentEntity->step) {
    case 8:
        step = 8;
        if (dx < 80) {
            step = 5;
        }
        break;

    default:
        step = 5;
        if (dx < 80) {
            step = 7;
        }
        if (dx > 160) {
            step = 8;
        }
        break;
    }

    if (!g_CurrentEntity->ext.GH_Props.unk8E) {
        if (dx < 96) {
            g_CurrentEntity->ext.GH_Props.unk8E = 3;
            step = 6;
        }
    }

    if (step != g_CurrentEntity->step) {
        func_801CE1E8(step);
    }

    if (g_CurrentEntity->step == 7 && step == 5) {
        g_CurrentEntity->ext.GH_Props.unkB0[0] = 1;
    }
}

void EntityHammer(Entity* self) {
    Collider collider;
    Entity* otherEnt;
    Entity* var_s3;
    s16* ptr;
    giantBroBodyPartsInit* parts;
    s32 step;

    if ((self->step & 1) && (self->hitFlags & 3)) {
        func_801CE1E8(12);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < 24)) {
        PlaySfxPositional(SFX_HAMMER_DEATH);
        func_801CE1E8(24);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitHammer);
        self->animCurFrame = 3;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        /* fallthrough */
    case 1:
        if (UnkCollisionFunc3(D_us_8018219C) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step++;
        }
        break;

    case 2:
        for (parts = D_us_801821AC, var_s3 = self; parts->eArrayOffset;
             parts++) {
            otherEnt = self + parts->eArrayOffset;
            CreateEntityFromCurrentEntity(E_GURKHA_BODY_PARTS, otherEnt);
            otherEnt->ext.GH_Props.length = parts->length;
            otherEnt->ext.GH_Props.parent = self + parts->eArrayParentOffset;
            otherEnt->params = parts->params;
            otherEnt->zPriority = self->zPriority + parts->zOffset;
            otherEnt->unk5C = self;
            otherEnt->unk60 = var_s3;
            var_s3 = otherEnt;
        }
        self->unk60 = var_s3;
        self->unk5C = NULL;
        otherEnt = self + 15;
        CreateEntityFromCurrentEntity(E_HAMMER_WEAPON, otherEnt);
        otherEnt->ext.GH_Props.length = 12;
        otherEnt->ext.GH_Props.parent = self + 5;
        otherEnt->zPriority = self->zPriority + 3;
        otherEnt->params = 0x12;
        self->step++;
        /* fallthrough */
    case 3:
        func_801CE228();
        otherEnt = self + 4;
        otherEnt->ext.GH_Props.rotate = 0x100;
        otherEnt = self + 5;
        otherEnt->ext.GH_Props.rotate = 0x680;
        otherEnt = self + 15;
        otherEnt->ext.GH_Props.rotate = 0x2C0;
        func_801CE1E8(5);
        /* fallthrough */
    case 5:
        if (self->ext.GH_Props.unk84 == 1) {
            ptr = D_us_801822DC;
        } else {
            ptr = D_us_801822F4;
        }
        func_801CDF1C(ptr, D_us_801823D8, 0);
        func_801CDE10(ptr);
        func_801CE2CC(ptr);
        polarPlacePartsList(D_us_80182244);
        if (self->ext.GH_Props.unkB0[0] > 1) {
            collider.unk18 = 9;
            otherEnt = self + ptr[3];
            func_801CE04C(otherEnt, &collider);
            if (otherEnt->ext.GH_Props.unk88) {
                otherEnt->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                func_801CE4CC(otherEnt);
            } else if (self->ext.GH_Props.unkB0[0] == 2 &&
                       self->ext.GH_Props.unkB4[0] == 1) {
                func_801CE1E8(8);
            }
        }
        break;

    case 7:
        if (self->ext.GH_Props.unk84 == 1) {
            ptr = D_us_801822DC;
        } else {
            ptr = D_us_801822F4;
        }
        func_801CDF1C(ptr, D_us_80182410, 0);
        func_801CDE10(ptr);
        func_801CE2CC(ptr);
        polarPlacePartsList(D_us_80182244);
        if (self->ext.GH_Props.unkB0[0] > 1) {
            collider.unk18 = 9;
            otherEnt = self + ptr[3];
            func_801CE04C(otherEnt, &collider);
            if (otherEnt->ext.GH_Props.unk88) {
                otherEnt->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                step = func_801CE120(otherEnt, self->facingLeft ^ 1);
                if (step != 0) {
                    func_801CE1E8(5);
                } else {
                    func_801CE4CC(self);
                }
            }
        }
        break;

    case 8:
        if (self->ext.GH_Props.unk84 == 1) {
            ptr = D_us_801822DC;
        } else {
            ptr = D_us_801822F4;
        }
        switch (self->step_s) {
        case 0:
            if (self->ext.GH_Props.unk84 == 1) {
                ptr = D_us_80182264;
            } else {
                ptr = D_us_80182280;
            }
            func_801CDF1C(ptr, D_us_80182378, 0);
            func_801CDE10(ptr);
            func_801CE2CC(ptr);
            if (!self->ext.GH_Props.unkB0[0] && !self->ext.GH_Props.unkB4[0]) {
                self->step_s++;
            }
            break;

        case 1:
            func_801CDF1C(ptr, D_us_801824C0, 0);
            func_801CDE10(ptr);
            func_801CE2CC(ptr);
            if (!self->ext.GH_Props.unkB4[0] && !self->ext.GH_Props.unkB0[0]) {
                self->step_s++;
            }
            break;

        case 2:
            if (self->facingLeft) {
                self->velocityX = FIX(2);
            } else {
                self->velocityX = FIX(-2);
            }
            self->velocityY = FIX(-7.0 / 64); // immediately overwritten
            self->velocityY = FIX(-0.75);
            func_801CE228();
            self->step_s++;
            /* fallthrough */
        case 3:
            MoveEntity();
            self->velocityY += FIX(0.375);
            func_801CDF1C(ptr, D_us_801824E8, 0);
            func_801CDE10(ptr);
            func_801CE3FC(ptr);
            otherEnt = self + ptr[3];
            collider.unk18 = 10;
            func_801CE04C(otherEnt, &collider);
            if (otherEnt->ext.GH_Props.unk88) {
                PlaySfxPositional(SFX_STOMP_HARD_C);
                otherEnt->posY.i.hi += collider.unk18 + 1;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                self->step_s = 1;
                func_801CE4CC(otherEnt);
            }
            break;
        }
        polarPlacePartsList(D_us_80182244);
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            self->step_s++;
            /* fallthrough */
        case 1:
            if (self->ext.GH_Props.unk84 == 1) {
                ptr = D_us_8018230C;
            } else {
                ptr = D_us_80182324;
            }
            func_801CDF1C(ptr, D_us_8018265C, 0);
            func_801CDE10(ptr);
            func_801CE2CC(ptr);
            otherEnt = self + 15;
            var_s3 = self + 8;
            var_s3->posX.val = otherEnt->posX.val;
            var_s3->posY.val = otherEnt->posY.val;
            otherEnt = self + 7;
            func_801CDAC8(otherEnt, var_s3);
            func_801CDFD8(otherEnt, 0x10);
            func_801CDFD8(var_s3, 0x10);
            polarPlacePartsList(D_us_80182244);
            if (!self->ext.GH_Props.unkB0[0] && !self->ext.GH_Props.unkB4[0]) {
                PlaySfxPositional(SFX_HAMMER_ATTACK);
                self->step_s++;
            }
            break;

        case 2:
            if (self->ext.GH_Props.unk84 == 1) {
                ptr = D_us_8018230C;
            } else {
                ptr = D_us_80182324;
            }
            func_801CDF1C(ptr, D_us_8018266C, 0);
            func_801CDE10(ptr);
            func_801CE2CC(ptr);
            otherEnt = self + 15;
            var_s3 = self + 8;
            var_s3->posX.val = otherEnt->posX.val;
            var_s3->posY.val = otherEnt->posY.val;
            otherEnt = self + 7;
            func_801CDAC8(otherEnt, var_s3);
            func_801CDFD8(otherEnt, 2);
            func_801CDFD8(var_s3, 2);
            polarPlacePartsList(D_us_80182244);
            if (self->ext.GH_Props.unkB0[0] == 4 &&
                !self->ext.GH_Props.unkB4[0]) {
                self->ext.GH_Props.unk84 ^= 1;
            }
            if (self->ext.GH_Props.unkB0[0] == 6 &&
                !self->ext.GH_Props.unkB4[0]) {
                PlaySfxPositional(SFX_FM_EXPLODE_D);
                g_api.func_80102CD8(1);
            }
            if (!self->ext.GH_Props.unkB0[0] && !self->ext.GH_Props.unkB4[0]) {
                self->ext.GH_Props.unk84 ^= 1;
                self->step_s++;
            }
            break;

        case 3:
            if (self->ext.GH_Props.unk84 == 1) {
                ptr = D_us_8018230C;
            } else {
                ptr = D_us_80182324;
            }
            func_801CDF1C(ptr, D_us_8018265C, 0);
            func_801CDE10(ptr);
            func_801CE2CC(ptr);
            polarPlacePartsList(D_us_80182244);
            if (!self->ext.GH_Props.unkB0[0] && !self->ext.GH_Props.unkB4[0]) {
                self->step_s++;
            }
            break;

        case 4:
            func_801CE4CC(self);
            break;
        }
        break;

    case 10:
        if (self->ext.GH_Props.unk84 == 1) {
            ptr = D_us_801822DC;
        } else {
            ptr = D_us_801822F4;
        }
        func_801CDF1C(ptr, D_us_80182520, 0);
        func_801CDE10(ptr);
        func_801CE2CC(ptr);
        polarPlacePartsList(D_us_80182244);
        if (!self->ext.GH_Props.unkB4[0]) {
            self->facingLeft ^= 1;
            func_801CE4CC(self);
        }
        break;

    case 12:
        if (!self->step_s) {
            PlaySfxPositional(SFX_HAMMER_PAIN);
            self->step_s++;
        }
        if (self->ext.GH_Props.unk84 == 1) {
            ptr = D_us_80182264;
        } else {
            ptr = D_us_80182280;
        }
        func_801CDF1C(ptr, D_us_80182700, 0);
        func_801CDE10(ptr);
        func_801CE2CC(ptr);
        polarPlacePartsList(D_us_80182244);
        if (!self->ext.GH_Props.unkB0[0] && !self->ext.GH_Props.unkB4[0]) {
            func_801CE4CC(self);
        }
        break;

    case 24:
        switch (self->step_s) {
        case 0:
            for (ptr = D_us_80182244; *ptr; ptr++) {
                otherEnt = self + *ptr;
                otherEnt->hitboxState = 0;
                otherEnt->step = 24;
                otherEnt->step_s = 0;
            }
            self->velocityY = FIX(-2);
            self->hitboxState = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.1875);
            if ((g_Timer & 7) == 0) {
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
    for (ptr = D_us_80182244; *ptr; ptr++) {
        otherEnt = self + *ptr;
        otherEnt->facingLeft = self->facingLeft;
        otherEnt->ext.GH_Props.unkA8 = 0;
    }
    D_8006C384.y = self->ext.GH_Props.unkB0[0];
    D_8006C38C.y = self->ext.GH_Props.unkB4[0];
}

void EntityGurkhaBodyParts(Entity* self) {
    Entity* parent;
    Collider collider;
    s16 angle;
    s32 speed;
    s32 unk88;

    switch (self->step) {
    case 0:
        switch (self->params >> 8) {
        case 0:
            InitializeEntity(g_EInitHammer);
            break;

        case 1:
            InitializeEntity(g_EInitGurkha);
            break;

        case 2:
            InitializeEntity(g_EInitBlade);
            break;
        }
        self->params &= 0xFF;
        self->animCurFrame = self->params;
        self->drawFlags |= DRAW_COLORS;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        break;

    case 1:
        self->rotate = self->ext.GH_Props.rotate;
        break;

    case 24:
        switch (self->step_s) {
        case 0:
            speed = (Random() & 0x1F) + 0x10;
            angle = (Random() * 6) + 0x900;
            self->velocityX = speed * rcos(angle) / 2;
            self->velocityY = speed * rsin(angle);
            self->ext.GH_Props.unk80 = (Random() & 0x1F) + 0x20;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->hitboxState = 0;
            self->step_s++;
            break;

        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            self->rotate += self->ext.GH_Props.unkA6;
            if (!--self->ext.GH_Props.unk80) {
                self->step = 0;
                self->pfnUpdate = EntityExplosion;
                self->params = 0;
                self->drawFlags = FLAG_DRAW_DEFAULT;
            }
            return;
        }
        break;
    }
    // Careful following control flow here, this is completely after
    // the previous switch.
    switch (self->params) {
    case 8:
    case 14:
        collider.unk18 = 9;
        func_801CE04C(self, &collider);
        break;

    case 9:
    case 15:
        parent = self->ext.GH_Props.parent;
        unk88 = parent->ext.GH_Props.unk88;
        if (unk88 == 2) {
            self->ext.GH_Props.rotate = 0x200;
        } else if (unk88 == 4) {
            self->ext.GH_Props.rotate = -0x200;
        } else if (unk88 == 1) {
            self->ext.GH_Props.rotate = 0;
        }
        if (self->ext.GH_Props.unk8D) {
            angle = self->rotate;
            self->hitboxOffX = (rsin(angle) * -8) >> 0xC;
            self->hitboxOffY = (rcos(angle) * 8) >> 0xC;
            self->attack = g_api.enemyDefs[192].attack;
            self->attackElement = g_api.enemyDefs[192].attackElement;
        } else {
            self->hitboxOffX = 0;
            self->hitboxOffY = 0;
            self->attack = g_api.enemyDefs[190].attack;
            self->attackElement = g_api.enemyDefs[190].attackElement;
        }
        break;

    case 5:
    case 11:
        parent = self->ext.GH_Props.parent;
        parent->ext.GH_Props.rotate = self->ext.GH_Props.rotate;
        break;
    }
}

void EntityHammerWeapon(Entity* self) {
    s16 angle;
    s32 speed;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitHammerWeapon);
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->hitboxWidth = 10;
        self->hitboxHeight = 10;
        /* fallthrough */
    case 1:
        self->rotate = self->ext.GH_Props.rotate;
        angle = self->rotate;
        self->hitboxOffX = (rsin(angle) * 0x34) >> 0xC;
        self->hitboxOffY = (rcos(angle) * -0x34) >> 0xC;
        break;

    case 24:
        switch (self->step_s) {
        case 0:
            speed = (Random() & 0x1F) + 0x10;
            angle = (Random() * 6) + 0x900;
            self->velocityX = speed * rcos(angle) / 2;
            self->velocityY = speed * rsin(angle);
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->hitboxState = 0;
            self->step_s++;
            break;

        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            func_801CDC80(&self->rotate, 0x800, 0x20);
            break;
        }
    }
}
