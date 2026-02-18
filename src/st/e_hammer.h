// SPDX-License-Identifier: AGPL-3.0-or-later
typedef enum {
    HAMMER_STEP_0,
    HAMMER_STEP_1,
    HAMMER_STEP_2,
    HAMMER_STEP_3,
    HAMMER_STEP_5 = 5,
    HAMMER_STEP_6,
    HAMMER_STEP_7,
    HAMMER_STEP_8,
    HAMMER_STEP_10 = 10,
    HAMMER_STEP_12 = 12,
    HAMMER_DYING = 24
} HammerSteps;

// clang-format off
static u16 sensors1[] = {0, 9, 0, 4, 4, -4, -8, 0};

// Hammer is a complex construction made of 16 entities.
// EntityHammer is the pelvis, and itself +1, +2, etc up to +14
// are the body parts. +15 is the hammer (the weapon).
// these are useful names for those body parts.
// The arms and legs are in 2 pairs. There is a bright blue foreground arm,
// and a dim grey background arm. Foreground is unprefixed, background is BACK_
typedef enum {
    PELVIS,
    HEAD,
    TORSO,
    SHOULDER,
    ARM_UPPER,
    ARM_LOWER,
    BACK_SHOULDER,
    BACK_ARM_UPPER,
    BACK_ARM_LOWER,
    LEG_UPPER,
    LEG_LOWER,
    FOOT,
    BACK_LEG_UPPER,
    BACK_LEG_LOWER,
    BACK_FOOT,
    HAMMER_WEAPON
} partEntOffsets;
// Struct reminder: Entity slot offset, parent entity's slot offset, length, params, zOffset
// To view the body parts, make sure Hammer is loaded, then invoke:
// python3 tools/display_animset_frames.py LIVE no2 0x8006 0x23E 48 48 --unk5A 0x4C
static giantBroBodyPartsInit D_us_801821AC[] = {
    {LEG_UPPER, PELVIS, 16, 7, 1},
    {LEG_LOWER, LEG_UPPER, 14, 8, 2},
    {FOOT, LEG_LOWER, 0, 9, 3},
    {BACK_LEG_UPPER, PELVIS, 16, 13, -1},
    {BACK_LEG_LOWER, BACK_LEG_UPPER, 14, 14, -2},
    {BACK_FOOT, BACK_LEG_LOWER, 0, 15, -3},
    {TORSO, PELVIS, -18, 2, 1},
    {HEAD, TORSO, -4, 16, 0},
    {SHOULDER, TORSO, 0, 4, 2},
    {ARM_UPPER, SHOULDER, 10, 5, 5},
    {ARM_LOWER, ARM_UPPER, 13, 6, 4},
    {BACK_SHOULDER, TORSO, 0, 10, -2},
    {BACK_ARM_UPPER, BACK_SHOULDER, 10, 11, -4},
    {BACK_ARM_LOWER, BACK_ARM_UPPER, 13, 12, -3},
    {0, 0, 0, 0, 0}};

static s16 partsList1[] = {TORSO, HEAD,
                           SHOULDER, ARM_UPPER, ARM_LOWER,
                           BACK_SHOULDER, BACK_ARM_UPPER, BACK_ARM_LOWER,
                           LEG_UPPER, LEG_LOWER, FOOT,
                           BACK_LEG_UPPER, BACK_LEG_LOWER, BACK_FOOT,
                           HAMMER_WEAPON,
                           0};
static s16 partsList2[] = {LEG_UPPER, LEG_LOWER,
                           BACK_LEG_UPPER, BACK_LEG_LOWER,
                           FOOT, BACK_FOOT,
                           TORSO, HEAD,
                           ARM_UPPER, ARM_LOWER,
                           BACK_ARM_UPPER, BACK_ARM_LOWER,
                           HAMMER_WEAPON,
                           0};
static s16 partsList3[] = {BACK_LEG_UPPER, BACK_LEG_LOWER,
                           LEG_UPPER, LEG_LOWER,
                           BACK_FOOT, FOOT,
                           TORSO, HEAD,
                           ARM_UPPER, ARM_LOWER,
                           BACK_ARM_UPPER, BACK_ARM_LOWER,
                           HAMMER_WEAPON,
                           0};
static s16 partsList4[] = {LEG_UPPER, LEG_LOWER,
                           BACK_LEG_UPPER, BACK_LEG_LOWER,
                           0}; // unused
static s16 partsList5[] = {BACK_LEG_UPPER, BACK_LEG_LOWER,
                           LEG_UPPER, LEG_LOWER,
                           0}; // unused
static s16 partsList6[] = {LEG_UPPER, LEG_LOWER,
                           BACK_LEG_UPPER, BACK_LEG_LOWER,
                           TORSO,
                           255, 255,
                           BACK_ARM_UPPER, BACK_ARM_LOWER,
                           0}; // unused
static s16 partsList7[] = {BACK_LEG_UPPER, BACK_LEG_LOWER,
                           LEG_UPPER, LEG_LOWER,
                           TORSO,
                           BACK_ARM_UPPER, BACK_ARM_LOWER,
                           255, 255,
                           0}; // unused
static s16 partsList8[] = {LEG_UPPER, LEG_LOWER,
                           BACK_LEG_UPPER, BACK_LEG_LOWER,
                           FOOT, BACK_FOOT,
                           TORSO,
                           255, 255,
                           BACK_ARM_UPPER, BACK_ARM_LOWER,
                           0};
static s16 partsList9[] = {BACK_LEG_UPPER, BACK_LEG_LOWER,
                           LEG_UPPER, LEG_LOWER,
                           BACK_FOOT, FOOT,
                           TORSO,
                           BACK_ARM_UPPER, BACK_ARM_LOWER,
                           255, 255,
                           0};
static s16 partsList10[] = {LEG_UPPER, LEG_LOWER,
                            BACK_LEG_UPPER, BACK_LEG_LOWER,
                            FOOT, BACK_FOOT,
                            TORSO,
                            ARM_UPPER, ARM_LOWER,
                            HAMMER_WEAPON,
                            0};
static s16 partsList11[] = {BACK_LEG_UPPER, BACK_LEG_LOWER,
                            LEG_UPPER, LEG_LOWER,
                            BACK_FOOT, FOOT,
                            TORSO,
                            ARM_UPPER, ARM_LOWER,
                            HAMMER_WEAPON,
                            0};
static s16 partsList12[] = {LEG_UPPER, LEG_LOWER,
                            BACK_LEG_UPPER, BACK_LEG_LOWER,
                            FOOT, BACK_FOOT,
                            0}; //unused
static s16 partsList13[] = {BACK_LEG_UPPER, BACK_LEG_LOWER,
                            LEG_UPPER, LEG_LOWER,
                            BACK_FOOT, FOOT,
                            0}; //unused

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
        func_801CE1E8(HAMMER_STEP_10);
        return;
    }

    if (g_CurrentEntity->ext.GH_Props.unk84 == 1) {
        otherEnt = g_CurrentEntity + LEG_LOWER;
    } else {
        otherEnt = g_CurrentEntity + BACK_LEG_LOWER;
    }

    step = func_801CE120(otherEnt, g_CurrentEntity->facingLeft);
    if (step != 0) {
        func_801CE1E8(HAMMER_STEP_7);
        return;
    }
    step = func_801CE120(otherEnt, g_CurrentEntity->facingLeft ^ 1);
    if (step != 0) {
        func_801CE1E8(HAMMER_STEP_5);
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
        func_801CE1E8(HAMMER_STEP_12);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < HAMMER_DYING)) {
        PlaySfxPositional(SFX_HAMMER_DEATH);
        func_801CE1E8(HAMMER_DYING);
    }
    switch (self->step) {
    case HAMMER_STEP_0:
        InitializeEntity(g_EInitHammer);
        self->animCurFrame = 3;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        /* fallthrough */
    case HAMMER_STEP_1:
        if (UnkCollisionFunc3(sensors1) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step++;
        }
        break;

    case HAMMER_STEP_2:
        // Loop through all parts until the eArrayOffset is zero
        // (null-terminated)
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
        otherEnt = self + HAMMER_WEAPON;
        CreateEntityFromCurrentEntity(E_HAMMER_WEAPON, otherEnt);
        otherEnt->ext.GH_Props.length = 12;
        otherEnt->ext.GH_Props.parent = self + ARM_LOWER;
        otherEnt->zPriority = self->zPriority + 3;
        otherEnt->params = 0x12;
        self->step++;
        /* fallthrough */
    case HAMMER_STEP_3:
        func_801CE228();
        otherEnt = self + ARM_UPPER;
        otherEnt->ext.GH_Props.rotate = 0x100;
        otherEnt = self + ARM_LOWER;
        otherEnt->ext.GH_Props.rotate = 0x680;
        otherEnt = self + HAMMER_WEAPON;
        otherEnt->ext.GH_Props.rotate = 0x2C0;
        func_801CE1E8(HAMMER_STEP_5);
        /* fallthrough */
    case HAMMER_STEP_5:
        if (self->ext.GH_Props.unk84 == 1) {
            ptr = partsList8;
        } else {
            ptr = partsList9;
        }
        func_801CDF1C(ptr, D_us_801823D8, 0);
        func_801CDE10(ptr);
        func_801CE2CC(ptr);
        polarPlacePartsList(partsList1);
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

    case HAMMER_STEP_7:
        if (self->ext.GH_Props.unk84 == 1) {
            ptr = partsList8;
        } else {
            ptr = partsList9;
        }
        func_801CDF1C(ptr, D_us_80182410, 0);
        func_801CDE10(ptr);
        func_801CE2CC(ptr);
        polarPlacePartsList(partsList1);
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

    case HAMMER_STEP_8:
        if (self->ext.GH_Props.unk84 == 1) {
            ptr = partsList8;
        } else {
            ptr = partsList9;
        }
        switch (self->step_s) {
        case 0:
            if (self->ext.GH_Props.unk84 == 1) {
                ptr = partsList2;
            } else {
                ptr = partsList3;
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
        polarPlacePartsList(partsList1);
        break;

    case HAMMER_STEP_6:
        switch (self->step_s) {
        case 0:
            self->step_s++;
            /* fallthrough */
        case 1:
            if (self->ext.GH_Props.unk84 == 1) {
                ptr = partsList10;
            } else {
                ptr = partsList11;
            }
            func_801CDF1C(ptr, D_us_8018265C, 0);
            func_801CDE10(ptr);
            func_801CE2CC(ptr);
            otherEnt = self + HAMMER_WEAPON;
            var_s3 = self + BACK_ARM_LOWER;
            var_s3->posX.val = otherEnt->posX.val;
            var_s3->posY.val = otherEnt->posY.val;
            otherEnt = self + BACK_ARM_UPPER;
            func_801CDAC8(otherEnt, var_s3);
            func_801CDFD8(otherEnt, 0x10);
            func_801CDFD8(var_s3, 0x10);
            polarPlacePartsList(partsList1);
            if (!self->ext.GH_Props.unkB0[0] && !self->ext.GH_Props.unkB4[0]) {
                PlaySfxPositional(SFX_HAMMER_ATTACK);
                self->step_s++;
            }
            break;

        case 2:
            if (self->ext.GH_Props.unk84 == 1) {
                ptr = partsList10;
            } else {
                ptr = partsList11;
            }
            func_801CDF1C(ptr, D_us_8018266C, 0);
            func_801CDE10(ptr);
            func_801CE2CC(ptr);
            otherEnt = self + HAMMER_WEAPON;
            var_s3 = self + BACK_ARM_LOWER;
            var_s3->posX.val = otherEnt->posX.val;
            var_s3->posY.val = otherEnt->posY.val;
            otherEnt = self + BACK_ARM_UPPER;
            func_801CDAC8(otherEnt, var_s3);
            func_801CDFD8(otherEnt, 2);
            func_801CDFD8(var_s3, 2);
            polarPlacePartsList(partsList1);
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
                ptr = partsList10;
            } else {
                ptr = partsList11;
            }
            func_801CDF1C(ptr, D_us_8018265C, 0);
            func_801CDE10(ptr);
            func_801CE2CC(ptr);
            polarPlacePartsList(partsList1);
            if (!self->ext.GH_Props.unkB0[0] && !self->ext.GH_Props.unkB4[0]) {
                self->step_s++;
            }
            break;

        case 4:
            func_801CE4CC(self);
            break;
        }
        break;

    case HAMMER_STEP_10:
        if (self->ext.GH_Props.unk84 == 1) {
            ptr = partsList8;
        } else {
            ptr = partsList9;
        }
        func_801CDF1C(ptr, D_us_80182520, 0);
        func_801CDE10(ptr);
        func_801CE2CC(ptr);
        polarPlacePartsList(partsList1);
        if (!self->ext.GH_Props.unkB4[0]) {
            self->facingLeft ^= 1;
            func_801CE4CC(self);
        }
        break;

    case HAMMER_STEP_12:
        if (!self->step_s) {
            PlaySfxPositional(SFX_HAMMER_PAIN);
            self->step_s++;
        }
        if (self->ext.GH_Props.unk84 == 1) {
            ptr = partsList2;
        } else {
            ptr = partsList3;
        }
        func_801CDF1C(ptr, D_us_80182700, 0);
        func_801CDE10(ptr);
        func_801CE2CC(ptr);
        polarPlacePartsList(partsList1);
        if (!self->ext.GH_Props.unkB0[0] && !self->ext.GH_Props.unkB4[0]) {
            func_801CE4CC(self);
        }
        break;

    case HAMMER_DYING:
        switch (self->step_s) {
        case 0:
            for (ptr = partsList1; *ptr; ptr++) {
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
    for (ptr = partsList1; *ptr; ptr++) {
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
            self->ext.GH_Props.timer = (Random() & 0x1F) + 0x20;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->hitboxState = 0;
            self->step_s++;
            break;

        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            self->rotate += self->ext.GH_Props.rotVel;
            if (!--self->ext.GH_Props.timer) {
                self->step = 0;
                self->pfnUpdate = EntityExplosion;
                self->params = 0;
                self->drawFlags = ENTITY_DEFAULT;
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
        self->drawFlags |= ENTITY_ROTATE;
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
