// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"

// The enemy called "Blade", his helper functions, and his swords

static void func_801D0A00(s16* arg0) {
    Entity* ent;

    ent = &g_CurrentEntity[arg0[1]];
    func_801CD91C(ent);
    ent = &g_CurrentEntity[arg0[0]];
    func_801CD91C(ent);
    ent = &g_CurrentEntity[18];
    func_801CD91C(ent);
    ent = &g_CurrentEntity[arg0[2]];
    polarPlacePart(ent);
    ent = &g_CurrentEntity[arg0[3]];
    polarPlacePart(ent);

    for (arg0 += 4; *arg0; arg0++) {
        if (*arg0 != 0xFF) {
            ent = &g_CurrentEntity[*arg0];
            polarPlacePart(ent);
        }
    }
}

static void func_801D0B40(void) {
    Entity* ent;
    s16* unk88;

    ent = &g_CurrentEntity[15];
    unk88 = ent->ext.et_801D0B40.unk88;
    ent->ext.et_801D0B40.unk84 = unk88[0x4E] - 0x600;

    ent = &g_CurrentEntity[16];
    unk88 = ent->ext.et_801D0B40.unk88;
    ent->ext.et_801D0B40.unk84 = unk88[0x4E] - 0x600;
}

static s32 func_801D0B78(Entity* ent) {
    Entity* player = &PLAYER;
    s32 xDist_unused;
    s32 ret;

    // This is the logic of GetDistanceToPlayerX.
    // We just call the function over and over instead.
    xDist_unused = player->posX.i.hi - ent->posX.i.hi;
    if (xDist_unused < 0) {
        xDist_unused = -xDist_unused;
    }

    ret = 0;

    switch (g_CurrentEntity->step) {
    case 8:
        if (GetDistanceToPlayerX() < 64) {
            ret = 10;
        }
        if (GetDistanceToPlayerX() > 80) {
            ret = 6;
        }
        if (g_CurrentEntity->ext.et_801D0B78.unk88) {
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
        if (g_CurrentEntity->ext.et_801D0B78.unk88) {
            ret = 7;
        }
        break;

    case 12:
        if (GetDistanceToPlayerX() < 64) {
            ret = 10;
        }
        break;

    case 6:
        if (g_CurrentEntity->ext.et_801D0B78.unk88) {
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
        if (g_CurrentEntity->ext.et_801D0B78.unk88) {
            ret = 7;
        }
        break;
    }

    if (g_CurrentEntity->facingLeft != ((GetSideToPlayer() & 1) ^ 1)) {
        ret = 12;
    }
    return ret;
}

// note on member types: length and zOffset definitely look signed
// in the data, but psp uses lhu instead of lh.
typedef struct {
    s16 eArrayOffset;
    s16 eArrayParentOffset;
    u16 length;
    u16 params;
    u16 zOffset;
} bladeBodyPartsInit;

// For EntityBlade

// TODO: Lots of these are referencing the body parts numerically.
// We should make enums for each of them (12 might be BLADE_LEFT_THIGH)
// to make these giant data sets more meaningful.

static s16 D_801833E4[] = {0, 9, 0, 4, 4, -4, -8, 0};
static bladeBodyPartsInit D_801833F4[] = {
    {9, 18, 16, 7, 1},    {10, 9, 14, 8, 2},    {11, 10, 0, 9, 3},
    {12, 18, 16, 13, -1}, {13, 12, 14, 14, -2}, {14, 13, 0, 15, -3},
    {18, 0, 8, 3, 0},     {2, 0, -12, 2, 1},    {1, 2, -4, 1, 0},
    {3, 2, 0, 4, 2},      {4, 3, 10, 5, 5},     {5, 4, 13, 6, 4},
    {6, 2, 0, 10, -2},    {7, 6, 10, 11, -6},   {8, 7, 13, 12, -5},
    {0, 0, 0, 0, 0}};
static s16 D_80183494[] = {
    18, 2, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 0};
static s16 D_801834B8[] = {9, 10, 12, 13, 11, 14, 2, 1, 4, 5, 7, 8, 15, 16, 0};
static s16 D_801834D8[] = {12, 13, 9, 10, 14, 11, 2, 1, 4, 5, 7, 8, 15, 16, 0};
static s16 D_801834F8[] = {9, 10, 12, 13, 11, 14, 2, 1, 4, 5, 7, 8, 0};
static s16 D_80183514[] = {12, 13, 9, 10, 14, 11, 2, 1, 4, 5, 7, 8, 0};
static s16 D_80183530[] = {9, 10, 12, 13, 11, 14, 2, 4, 5, 7, 8, 0};
static s16 D_80183548[] = {12, 13, 9, 10, 14, 11, 2, 7, 8, 4, 5, 0};
static s16 D_80183560[] = {9, 10, 12, 13, 11, 14, 0};
static s16 D_80183570[] = {12, 13, 9, 10, 14, 11, 0};
static s16 D_80183580[] = {2, 4, 5, 15, 0};
static s16 D_8018358C[] = {0,      0,     0x80,  -0x100, 0,     0,      0,
                           -0x100, -0x40, 0x100, 0,      0x200, -0x500, -0x400};
static unkStr_801CDD80 D_801835A8[] = {{16, D_8018358C}, {0, 0}};
static s16 D_801835B8[] = {
    0x40, -0x20, 0x20, -0x220, 0, -0x100, 0, -0xc0, -0xc0, 0x20, 0x100, 0};
static s16 D_801835D0[] = {
    -0x90, -0x90, 0x158, 0, 0, -0x20, 0, 0x80, 0x100, -0xc0, -0xc0, 0};
static s16 D_801835E8[] = {
    -0x100, -0x180, 0x100, 0xc0, 0, 0x40, 0, 0x100, 0x280, -0x140, -0x140, 0};
static unkStr_801CDD80 D_80183600[] = {
    {14, D_801835B8}, {14, D_801835D0}, {14, D_801835E8}, {0, 0}};
static s16 D_80183620[] = {
    0x200, 0xc0, -0x100, -0x180, 0, -0x40, 0, -0x140, -0x140, 0x100, 0x280, 0};
static unkStr_801CDD80 D_80183638[] = {
    {14, D_801835D0}, {14, D_801835B8}, {14, D_80183620}, {0, 0}};
static s16 D_80183658[] = {
    0x100, 0x40, 0x80, -0x400, 0, -0x380, -0xc0, -0xc0, 0x80, 0, 0x300, 0};
static s16 D_80183670[] = {0xc0,  -0x100, 0x100, -0x480, 0,     -0x400,
                           -0xe0, -0x40,  0x100, -0x80,  0x240, 0};
static s16 D_80183688[] = {-0x140, -0x180, 0x240, -0x400, 0,    -0x400,
                           -0x100, -0x100, 0x2c0, -0x100, 0x40, 0};
static s16 D_801836A0[] = {
    -0x1c0, -0x200, 0x2c0, -0x200, 0, -0x200, -0xe0, 0, 0x440, -0x140, 0};
static s16 D_801836B8[] = {
    -0xc0, -0x300, 0x240, -0x100, -0x180, 0, -0xc0, 0, 0x440, -0x180, -0x40, 0};
static s16 D_801836D0[] = {
    0x20, -0x380, 0x1c0, 0, -0x240, 0x100, -0xc0, 0, 0x400, -0x140, 0};
static s16 D_801836E8[] = {
    0x80, -0x400, 0x100, 0x40, -0x380, 0x100, -0xc0, 0, 0x300, -0xc0, 0x80, 0};
static unkStr_801CDD80 D_80183700[] = {
    {5, D_80183670}, {5, D_80183688}, {4, D_801836A0}, {0, 0}};
static unkStr_801CDD80 D_80183720[] = {
    {4, D_801836B8},
    {4, D_801836D0},
    {4, D_801836E8},
    {0x60, D_801836E8},
    {0, 0}};
static s16 D_80183748[] = {0, 0, 0x80, -0x80, 0, 0, 0, 0, 0, 0, 0, 0};
static unkStr_801CDD80 D_80183760[] = {{32, D_80183748}, {0, 0}};
static s16 D_80183770[] = {
    0x100,  -0x240, 0x200, -0x100, 0,     0,      -0x1c0,
    -0x100, -0x300, 0x100, 0,      0x180, -0x500, -0x480};
static s16 D_8018378C[] = {
    0x180,  -0x240, 0x280, -0x100, 0,     0,      -0x1c0,
    -0x100, -0x300, 0x100, 0,      0x180, -0x500, -0x480};
static s16 D_801837A8[] = {0x40,  -0x180, 0x1c0, -0x180, 0,     0,      -0x20,
                           -0x40, -0x300, 0x100, 0x300,  0x500, -0x500, 0};
static s16 D_801837C4[] = {0, -0x100, 0x100, -0x100, 0,     0,      0x80,
                           0, -0x300, 0x100, 0x700,  0xa00, -0x300, 0x500};
static s16 D_801837E0[] = {
    0, -0x140, 0x100, -0xc0, 0, 0, 0, 0, -0x300, 0x100, 0x740, 0xa80, 0, 0x600};
static s16 D_801837FC[] = {0x40, -0x1c0, 0x1c0, 0,     0,     0,     0,
                           0,    -0x300, 0x100, 0x400, 0x900, 0x380, 0x300};
static s16 D_80183818[] = {-0x100, -0x240, 0x200, 0, 0,     0,     -0x80,
                           -0x40,  0x200,  0x300, 0, 0x300, 0x300, -0x300};
static s16 D_80183834[] = {-0x240, -0x240, 0x300, -0x100, 0, 0,     -0x200,
                           -0x100, 0x400,  0x400, -0x200, 0, 0x400, -0x600};
static s16 D_80183850[] = {-0x280, -0x280, 0x380, -0x140, 0,     0,     -0x180,
                           -0x80,  0x340,  0x4c0, -0x200, 0x200, 0x500, -0x300};
static unkStr_801CDD80 D_8018386C[] = {
    {16, D_80183770}, {24, D_8018378C}, {4, D_801837A8},
    {8, D_801837C4},  {18, D_801837E0}, {0, 0}};
static unkStr_801CDD80 D_8018389C[] = {
    {4, D_801837FC},
    {6, D_80183818},
    {4, D_80183834},
    {32, D_80183850},
    {0, 0}};
static unkStr_801CDD80 D_801838C4[] = {{16, D_80183770}, {0, 0}};
static s16 D_801838D4[] = {0x80,  -0x40, 0x300,  -0x200, 0,     -0x200,
                           0x100, -0x80, -0x100, 0x300,  0x100, 0x180};
static s16 D_801838EC[] = {
    0xa0, -0x40, 0x400, 0x300, 0, 0x300, 0x180, -0x80, 0, 0x400, -0x1c0, 0};
static s16 D_80183904[] = {
    0x80, -0x40, 0x500, 0x380, 0, 0x400, 0x180, -0x80, 0x100, 0x500, -0x200, 0};
static s16 D_8018391C[] = {0x80,  -0x40, 0x480, 0x300, 0,      0x300,
                           0x180, -0x80, 0x80,  0x300, -0x100, 0x80};
static unkStr_801CDD80 D_80183934[] = {
    {12, D_8018358C}, {12, D_80183770}, {4, D_801838D4},  {4, D_801838EC},
    {6, D_80183904},  {24, D_8018391C}, {16, D_80183770}, {0, 0}};
static s16 D_80183974[] = {0xc0,  -0x80, 0x180, -0x200, 0,     -0x200, 0x100,
                           0x180, 0x400, 0x600, 0x300,  0x500, 0,      -0x100};
static unkStr_801CDD80 D_80183990[] = {
    {16, D_80183974}, {32, D_8018358C}, {0, 0}};
static s16 D_801839A8[] = {
    0,      -0x200, 0x80,  -0x200, -0x200, -0x200, 0,
    -0x100, -0x40,  0x100, 0,      0x200,  -0x500, -0x400};
static s16 D_801839C4[] = {
    -0x100, -0x400, -0x140, -0x400, -0x400, -0x400, -0x200,
    -0x100, -0x100, 0x200,  0x200,  0x300,  -0x300, -0x100};
static s16 D_801839E0[] = {
    0,      -0x400, 0x80,  -0x400, -0x400, -0x400, -0x100,
    -0x100, 0x200,  0x400, 0x200,  0x280,  -0x300, -0x100};
static s16 D_801839FC[] = {0, 0x400, 0x600, 0x300};
static s16 D_80183A04[] = {0x40, 0x700, 0xb00, 0x800};
static s16 D_80183A0C[] = {0x0, 0x780, 0xb80, 0xc00};
static s16 D_80183A14[] = {-0x180, 0x600, 0x600, 0xa00};
static s16 D_80183A1C[] = {-0x340, 0x400, 0x4c0, 0x400};
static unkStr_801CDD80 D_80183A24[] = {
    {16, D_8018358C},
    {16, D_801839A8},
    {6, D_801839C4},
    {56, D_801839E0},
    {0, 0}};
static unkStr_801CDD80 D_80183A4C[] = {
    {6, D_801839FC}, {8, D_80183A04}, {32, D_80183A0C},
    {4, D_80183A14}, {3, D_80183A1C}, {0, 0}};

void EntityBlade(Entity* self) {
    Collider collider;
    Entity* ent_s4;
    s32 var_s3;
    bladeBodyPartsInit* parts;
    s16* var_s1;
    Entity* ent_s0;

    if ((self->step & 1) && (self->hitFlags & 3)) {
        func_801CE1E8(0xE);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < 0x18)) {
        ent_s0 = self + 13;
        ent_s4 = self + 10;

        if (ent_s0->ext.GH_Props.unk88 || ent_s4->ext.GH_Props.unk88) {
            PlaySfxPositional(0x750);
            func_801CE1E8(0x18);
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGurkhaType2);
        // we start on frame 3
        self->animCurFrame = 3;
        // eh nah i change my mind, we start on frame 0
        self->animCurFrame = 0;
        self->facingLeft = self->params;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        /* fallthrough */
    case 1:
        if (UnkCollisionFunc3(D_801833E4) & 1) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step++;
        }
        break;
    case 2:
        for (parts = D_801833F4, ent_s4 = self; parts->eArrayOffset; parts++) {
            ent_s0 = self + parts->eArrayOffset;
            CreateEntityFromCurrentEntity(E_GURKHA_BODY_PARTS, ent_s0);
            ent_s0->ext.GH_Props.length = parts->length;
            ent_s0->ext.GH_Props.parent = self + parts->eArrayParentOffset;
            ent_s0->params = parts->params + 0x200;
            ent_s0->zPriority = self->zPriority + parts->zOffset;
            ent_s0->unk5C = self;
            ent_s0->unk60 = ent_s4;
            ent_s4 = ent_s0;
        }
        self->unk60 = ent_s4;
        self->unk5C = NULL;

        ent_s0 = self + 15;
        CreateEntityFromCurrentEntity(E_BLADE_SWORD, ent_s0);
        ent_s0->ext.GH_Props.length = 12;
        ent_s0->ext.GH_Props.parent = self + 5;
        ent_s0->zPriority = self->zPriority + 3;
        ent_s0->params = 19;

        ent_s0 = self + 16;
        CreateEntityFromCurrentEntity(E_BLADE_SWORD, ent_s0);
        ent_s0->ext.GH_Props.length = 12;
        ent_s0->ext.GH_Props.parent = self + 8;
        ent_s0->zPriority = self->zPriority - 4;
        ent_s0->params = 19;
        self->step++;
        /* fallthrough */
    case 3:
        func_801CE228();
        func_801CE1E8(5);
        /* fallthrough */
    case 5:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s1 = D_80183530;
        } else {
            var_s1 = D_80183548;
        }
        func_801CDF1C(var_s1, &D_80183600, 0);
        func_801CDE10(var_s1);
        func_801D0A00(var_s1);
        func_801D0B40();
        polarPlacePartsList(&D_80183494);
        if (self->ext.GH_Props.unkB0[0] > 1) {
            collider.unk18 = 9;
            ent_s0 = &self[var_s1[3]];
            func_801CE04C(ent_s0, &collider);
            if (ent_s0->ext.GH_Props.unk88) {
                ent_s0->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                var_s3 = func_801CE120(ent_s0, self->facingLeft);
                self->ext.GH_Props.unk88 = var_s3;

                var_s3 = func_801D0B78(ent_s0);
                if (var_s3) {
                    func_801CE1E8(var_s3);
                }
            }
        }
        break;
    case 7:
        if (!self->step_s) {
            self->ext.GH_Props.unkB0[0] = 1;
            self->step_s++;
        }
        if (self->ext.GH_Props.unk84 == 1) {
            var_s1 = D_80183560;
        } else {
            var_s1 = D_80183570;
        }
        func_801CDF1C(var_s1, &D_80183638, 0);
        func_801CDE10(var_s1);
        func_801D0A00(var_s1);
        func_801D0B40();
        polarPlacePartsList(&D_80183494);
        if (self->ext.GH_Props.unkB0[0] > 1) {
            collider.unk18 = 9;
            ent_s0 = &self[var_s1[3]];
            func_801CE04C(ent_s0, &collider);
            if (ent_s0->ext.GH_Props.unk88) {
                ent_s0->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                var_s3 = func_801CE120(ent_s0, self->facingLeft ^ 1);
                if (var_s3) {
                    func_801CE1E8(6);
                }

                var_s3 = func_801CE120(ent_s0, self->facingLeft);
                self->ext.GH_Props.unk88 = var_s3;

                var_s3 = func_801D0B78(self);
                if (var_s3) {
                    func_801CE1E8(var_s3);
                }
            }
        }
        break;
    case 6:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s1 = D_80183530;
        } else {
            var_s1 = D_80183548;
        }
        switch (self->step_s) {
        case 0:
            if (self->ext.GH_Props.unk84 == 1) {
                var_s1 = D_801834B8;
            } else {
                var_s1 = D_801834D8;
            }
            func_801CDF1C(var_s1, &D_801838C4, 0);
            func_801CDE10(var_s1);
            func_801D0A00(var_s1);
            func_801D0B40();
            if ((!self->ext.GH_Props.unkB0[0]) &&
                (!self->ext.GH_Props.unkB4[0])) {
                self->step_s++;
            }
            self->step_s++;
            break;
        case 1:
            func_801CDF1C(var_s1, &D_80183700, 0);
            func_801CDE10(var_s1);
            func_801D0A00(var_s1);
            func_801D0B40();
            if ((!self->ext.GH_Props.unkB4[0]) &&
                (!self->ext.GH_Props.unkB0[0])) {
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
            func_801CDF1C(var_s1, &D_80183720, 0);
            func_801CDE10(var_s1);
            func_801CE3FC(var_s1);
            func_801D0B40();
            ent_s0 = &self[var_s1[3]];
            collider.unk18 = 9;
            func_801CE04C(ent_s0, &collider);
            if (ent_s0->ext.GH_Props.unk88) {
                PlaySfxPositional(SFX_STOMP_HARD_C);
                ent_s0->posY.i.hi += collider.unk18;
                self->ext.GH_Props.unk84 ^= 1;
                func_801CE228();
                var_s3 = func_801CE120(ent_s0, self->facingLeft);
                self->ext.GH_Props.unk88 = var_s3;

                var_s3 = func_801D0B78(ent_s0);
                if (var_s3) {
                    func_801CE1E8(var_s3);
                } else {
                    self->step_s = 1;
                }
            }
            break;
        }
        polarPlacePartsList(&D_80183494);
        break;
    case 8:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s1 = D_801834B8;
        } else {
            var_s1 = D_801834D8;
        }
        switch (self->step_s) {
        case 0:
            ent_s0 = self + 15;
            ent_s0->ext.GH_Props.unk8D = 1;
            ent_s0 = self + 16;
            ent_s0->ext.GH_Props.unk8D = 1;
            self->ext.GH_Props.unk8D = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            func_801CDF1C(var_s1, &D_8018386C, 0);
            func_801CDE10(var_s1);
            func_801D0A00(var_s1);
            polarPlacePartsList(&D_80183494);
            ent_s0 = self + 16;
            if (ent_s0->hitFlags) {
                self->ext.GH_Props.unk8D = 1;
            }
            if ((!self->ext.GH_Props.unkB0[0]) &&
                (!self->ext.GH_Props.unkB4[0])) {
                if (self->ext.GH_Props.unk8D) {
                    self->step_s = 3;
                } else {
                    self->step_s = 2;
                }
            }
            break;
        case 2:
            func_801CDF1C(var_s1, &D_8018389C, 0);
            func_801CDE10(var_s1);
            func_801D0A00(var_s1);
            if ((self->ext.GH_Props.unkB0[0] == 1) &&
                (!self->ext.GH_Props.unkB4[0])) {
                PlaySfxPositional(SFX_BONE_SWORD_SWISH_C);
            }
            polarPlacePartsList(&D_80183494);
            if ((!self->ext.GH_Props.unkB0[0]) &&
                (!self->ext.GH_Props.unkB4[0])) {
                ent_s0 = self + 15;
                ent_s0->ext.GH_Props.unk8D = 0;
                ent_s0 = self + 16;
                ent_s0->ext.GH_Props.unk8D = 0;
                self->step_s++;
            }
            break;
        case 3:
            func_801CDF1C(var_s1, &D_801835A8, 0);
            func_801CDE10(var_s1);
            func_801D0A00(var_s1);
            polarPlacePartsList(&D_80183494);
            if ((!self->ext.GH_Props.unkB0[0]) &&
                (!self->ext.GH_Props.unkB4[0])) {
                var_s3 = func_801D0B78(self);
                if (var_s3) {
                    func_801CE1E8(var_s3);
                } else {
                    func_801CE1E8(5);
                }
            }
            break;
        }
        break;
    case 10:
        if (!self->step_s) {
            PlaySfxPositional(0x74E);
            self->step_s++;
        }
        if (self->ext.GH_Props.unk84 == 1) {
            var_s1 = D_801834F8;
        } else {
            var_s1 = D_80183514;
        }
        func_801CDF1C(var_s1, &D_80183934, 0);
        func_801CDE10(var_s1);
        func_801D0A00(var_s1);
        func_801D0B40();
        polarPlacePartsList(&D_80183494);
        ent_s0 = self + var_s1[5];
        ent_s0->ext.GH_Props.unk8D = 1;
        if ((!self->ext.GH_Props.unkB0[0]) && (!self->ext.GH_Props.unkB4[0])) {
            // repeated line, surprised it gets compiled
            ent_s0 = self + var_s1[5];
            ent_s0->ext.GH_Props.unk8D = 0;
            var_s3 = func_801D0B78(self);
            if (var_s3) {
                func_801CE1E8(var_s3);
            } else {
                func_801CE1E8(5);
            }
        }
        break;
    case 12:
        if (self->ext.GH_Props.unk84 == 1) {
            var_s1 = D_80183530;
        } else {
            var_s1 = D_80183548;
        }
        func_801CDF1C(var_s1, &D_80183760, 0);
        func_801CDE10(var_s1);
        func_801D0A00(var_s1);
        func_801D0B40();
        polarPlacePartsList(&D_80183494);
        if (!self->ext.GH_Props.unkB4[0]) {
            self->facingLeft ^= 1;
            self->ext.GH_Props.unk88 = 0;
            var_s3 = func_801D0B78(self);
            if (var_s3) {
                func_801CE1E8(var_s3);
            } else {
                func_801CE1E8(5);
            }
        }
        break;
    case 14:
        if (!self->step_s) {
            PlaySfxPositional(0x74F);
            self->step_s++;
        }
        if (self->ext.GH_Props.unk84 == 1) {
            var_s1 = D_801834B8;
        } else {
            var_s1 = D_801834D8;
        }
        func_801CDF1C(var_s1, &D_80183990, 0);
        func_801CDE10(var_s1);
        func_801D0A00(var_s1);
        polarPlacePartsList(&D_80183494);
        if ((!self->ext.GH_Props.unkB0[0]) && (!self->ext.GH_Props.unkB4[0])) {
            var_s3 = func_801D0B78(self);
            if (var_s3) {
                func_801CE1E8(var_s3);
            } else {
                func_801CE1E8(5);
            }
        }
        break;
    case 24:
        switch (self->step_s) {
        case 0:
            for (var_s1 = D_80183494; *var_s1; var_s1++) {
                ent_s0 = self + *var_s1;
                ent_s0->hitboxState = 0;
            }
            self->hitboxState = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (self->ext.GH_Props.unk84 == 1) {
                var_s1 = D_801834B8;
            } else {
                var_s1 = D_801834D8;
            }
            func_801CDF1C(var_s1, &D_80183A24, 0);
            func_801CDE10(var_s1);
            func_801D0A00(var_s1);
            polarPlacePartsList(&D_80183494);
            if ((self->ext.GH_Props.unkB0[0] == 3) &&
                (!self->ext.GH_Props.unkB4[0])) {
                PlaySfxPositional(SFX_STOMP_HARD_A);
            }
            if (!self->ext.GH_Props.unkB0[0] && !self->ext.GH_Props.unkB4[0]) {
                self->step_s++;
            }
            break;
        case 2:
            var_s1 = D_80183580;
            func_801CDF1C(var_s1, &D_80183A4C, 0);
            polarPlacePartsWithAngvel(var_s1);
            polarPlacePartsList(&D_80183494);
            if ((!self->ext.GH_Props.unkB0[0]) &&
                (!self->ext.GH_Props.unkB4[0])) {
                PlaySfxPositional(SFX_ARROW_SHOT_A);
                ent_s0 = self + 15;
                ent_s0->ext.GH_Props.unk8C = 1;
                ent_s0->ext.GH_Props.rotate = 0x400;
                ent_s0->rotate = 0x400;
                self->ext.GH_Props.unk80 = 0x20;
                self->step_s++;
            }
            break;
        case 3:
            if (!--self->ext.GH_Props.unk80) {
                self->step_s++;
            }
            break;
        case 4:
            for (var_s1 = D_80183494; *var_s1; var_s1++) {
                ent_s0 = self + *var_s1;
                ent_s0->step = 0x18;
                ent_s0->step_s = 0;
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
            if (!--self->ext.GH_Props.unk80) {
                DestroyEntity(self);
            }
            return;
        }
        break;
    }
    for (var_s1 = D_80183494; *var_s1; var_s1++) {
        ent_s0 = self + *var_s1;
        ent_s0->facingLeft = self->facingLeft;
        ent_s0->ext.GH_Props.unkA8 = 0;
    }
    D_8006C384.y = self->ext.GH_Props.unkB0[0];
    D_8006C38C.y = self->ext.GH_Props.unkB4[0];
}

void EntityBladeSword(Entity* self) {
    Primitive *prim, *prim2;
    s32 x0, y0, x1, y1;
    s32 primIndex;
    s16 angle;
    s32 i;

    if (self->ext.et_801D1BB8.unk8C) {
        self->step = 8;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGurkhaBlade);
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        primIndex = g_api.AllocPrimitives(PRIM_G4, 6);
        if (primIndex == -1) {
#ifdef VERSION_PSP
            DestroyEntity(self);
#else
            self->ext.et_801D1BB8.prim = NULL;
#endif
            break;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801D1BB8.prim = prim;

        for (i = 0; prim != NULL; prim = prim->next) {
            prim->r0 = i;
            prim->g0 = i;
            prim->b0 = i;
            LOW(prim->r1) = LOW(prim->r0);
            i += 10;
            prim->r2 = i;
            prim->g2 = i;
            prim->b2 = i;
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
        self->rotate = self->ext.et_801D1BB8.unk9C;
        break;

    case 24:
        self->flags |= FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        self->hitboxState = 0;
        break;

    case 8:
        if (self->facingLeft) {
            self->velocityX = FIX(8.0);
        } else {
            self->velocityX = FIX(-8.0);
        }
        MoveEntity();
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
    }

    angle = self->rotate;
    self->hitboxOffX = (rsin(angle) * -13) >> 12;
    self->hitboxOffY = (rcos(angle) * 13) >> 12;

    prim = self->ext.et_801D1BB8.prim;
    #if !defined(VERSION_PSP)
    if(prim != NULL){
    #else
    if(1){
    #endif
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
    

    angle = self->rotate;
    if (self->facingLeft) {
        angle = -angle;
    }

    x0 = ((rsin(angle) * -20) >> 12) + self->posX.i.hi;
    y0 = ((rcos(angle) * 20) >> 12) + self->posY.i.hi;
    x1 = ((rsin(angle) * 4) >> 12) + self->posX.i.hi;
    y1 = ((rcos(angle) * -4) >> 12) + self->posY.i.hi;

    LOW(prim->x2) = LOW(prim->x0);
    LOW(prim->x3) = LOW(prim->x1);

    prim->x0 = x0;
    prim->y0 = y0;
    prim->x1 = x1;
    prim->y1 = y1;

    if (self->ext.et_801D1BB8.unk8D) {
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
    } else {
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
    }
}
