// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz1.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s16 unkC;
    s16 unkE;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 unk2C;
    u8 step;
    u8 substep;
    s16 unk30;
    s16 unk32;
} batWingStruct;

static void WipeBatwing(batWingStruct* arg0) {
    s32* ptr = (s32*)arg0;
    s32 bound = sizeof(batWingStruct) / sizeof(s32);
    s32 i;

    for (i = 0; i < bound; i++) {
        *ptr++ = 0;
    }
}

static void UnusedCopyBatwing(s32* arg0, s32* arg1) {
    s32 bound = sizeof(batWingStruct) / sizeof(s32);
    s32 i;

    for (i = 0; i < bound; i++) {
        *arg1++ = *arg0++;
    }
}

static void func_us_801AB198(batWingStruct* arg0) {
    s32 var_s2;
    s32 var_s1;
    s32 var_s0;

    var_s2 = arg0->unk8 * 0x50 / 0x100;
    var_s1 = arg0->unk0;
    arg0->unk4 =
        (var_s2 * rcos(arg0->unkE) / 0x1000) +
        (((arg0->unk18 * rcos(arg0->unk28 / 0x100)) / 0x1000) * 0x3E) / 0x100;
    var_s0 = var_s1 - arg0->unk4;
    arg0->unk8 += var_s0;
    arg0->unk10 += arg0->unk8;
    var_s2 = (arg0->unk1C + arg0->unk8) * 0x90 / 0x100;
    var_s1 = arg0->unk14;
    arg0->unk18 = var_s2 * rcos(arg0->unk24) / 0x1000;
    var_s0 = var_s1 - arg0->unk18;
    arg0->unk1C += var_s0;
    arg0->unk28 += arg0->unk1C;
    if (arg0->unk10 > FIX(3.5)) {
        arg0->unk10 = FIX(3.5);
        arg0->unk8 = 0;
    }
    if (arg0->unk10 < FIX(-2.5)) {
        arg0->unk10 = FIX(-2.5);
        arg0->unk8 = 0;
    }
    if ((arg0->unk28 - arg0->unk10) > FIX(5)) {
        arg0->unk28 = (arg0->unk10 + FIX(5));
        arg0->unk1C = 0;
    }
    if ((arg0->unk28 - arg0->unk10) < FIX(-2.5)) {
        arg0->unk28 = (arg0->unk10 + FIX(-2.5));
        arg0->unk1C = 0;
    }
}

static Primitive* func_us_801AB380(
    batWingStruct* arg0, Primitive* prim, SVECTOR** arg2) {
    s16 transX;
    s16 transY;
    long spA8;
    long spA4;
    long spA0;
    long sp9C;
    long sp98;
    SVECTOR rotVec;
    VECTOR transVec;
    MATRIX sp60;
    MATRIX m;
    Primitive* prevPrim;
    s16 xOffset;
    s16 yOffset;
    s16 transZ;
    s16 rotX;
    s16 rotY;
    s16 rotZ;
    s32 i;
    s32 zOffset;
    s32 stackpad1[8];
    SVECTOR sp38 = {0};
    s32 stackpad2[2];
    Entity* mainBat;

    rotVec.vx = g_CurrentEntity->ext.batwing.rotX;
    rotVec.vy = g_CurrentEntity->ext.batwing.rotY;
    rotVec.vz = g_CurrentEntity->ext.batwing.rotZ;
    RotMatrix(&sp38, &m);
    RotMatrixY(rotVec.vy, &m);
    RotMatrixX(rotVec.vx, &m);
    RotMatrixZ(rotVec.vz, &m);
    mainBat = g_CurrentEntity - 1;
    if (mainBat->facingLeft) {
        RotMatrixY(0x800, &m);
    }
    xOffset = arg0->unk30;
    yOffset = arg0->unk32;
    transX = 0;
    transY = 0;
    transZ = g_CurrentEntity->ext.batwing.transZ;
    rotX = arg0->unkC;
    rotY = arg0->unkE;
    rotZ = arg0->unk10 / 0x100;
    SetGeomScreen(0x180);
    for (i = 0; i < 2; i += 1) {
        rotVec.vx = rotX;
        rotVec.vy = rotY;
        if (arg0->unk2C) {
            rotVec.vy = -rotVec.vy;
        }
        rotVec.vz = rotZ;
        if (arg0->unk2C) {
            rotVec.vz = -rotVec.vz;
        }
        RotMatrix(&sp38, &sp60);
        RotMatrixY(rotVec.vy, &sp60);
        RotMatrixZ(rotVec.vz, &sp60);
        RotMatrixX(rotVec.vx, &sp60);
        SetMulMatrix(&m, &sp60);
        transVec.vx = transX;
        transVec.vy = transY;
        transVec.vz = transZ;
        TransMatrix(&sp60, &transVec);
        SetTransMatrix(&sp60);
        SetGeomOffset(xOffset, yOffset);
        zOffset = RotTransPers(*arg2, &spA8, &sp9C, &sp98);
        arg2++;
        zOffset = zOffset + RotTransPers(*arg2, &spA4, &sp9C, &sp98);
        arg2++;
        zOffset /= 2;

        rotVec.vx = rotX;
        rotVec.vy = 0;
        rotVec.vz = rotZ;
        if (arg0->unk2C) {
            rotVec.vz = -rotVec.vz;
        }
        RotMatrix(&sp38, &sp60);
        RotMatrixY(rotVec.vy, &sp60);
        RotMatrixZ(rotVec.vz, &sp60);
        RotMatrixX(rotVec.vx, &sp60);
        SetMulMatrix(&m, &sp60);
        RotTransPers(*arg2, &spA0, &sp9C, &sp98);
        arg2++;
        if (i == 0) {
            xOffset = prim->x1 = (u16)spA8;
            yOffset = prim->y1 = spA8 >> 0x10;
            LOW(prim->x0) = spA4;
            LOW(prim->x2) = spA0;
            transZ = zOffset * 4;
            rotX = arg0->unk20;
            rotY = arg0->unk24;
            rotZ = arg0->unk28 / 0x100;
        } else {
            LOW(prim->x1) = spA8;
            prim->x0 = prevPrim->x1;
            prim->y0 = prevPrim->y1;
            LOW(prim->x3) = spA4;
            LOW(prevPrim->x3) = LOW(prim->x2) = spA0;
        }
        prim->priority = ((g_CurrentEntity->zPriority +
                           g_CurrentEntity->ext.batwing.transZ / 4) -
                          zOffset);
        prevPrim = prim;
        prim = prim->next;
    }
    return prim;
}

static void func_us_801AB768(batWingStruct* arg0) {
    switch (arg0->step) {
    case 0:
        if (arg0->unkE < 0x200) {
            arg0->unkE += 0x10;
        }
        if (arg0->unk24 > -0x100) {
            arg0->unk24 -= 0x18;
        }
        switch (arg0->substep) {
        case 0:
            if (arg0->unk8 > -0x3000) {
                arg0->unk0 = arg0->unk0 - 0x80;
            }
            if (arg0->unk10 < 0) {
                arg0->unk0 = arg0->unk0 + 0x60;
                if (arg0->unk1C > -0x4000) {
                    arg0->unk14 -= 0x200;
                }
            }
            if (arg0->unk10 < FIX(-1.5)) {
                arg0->unk0 = 0;
                arg0->substep++;
            }
            break;
        case 1:
            if (arg0->unk1C > -0x4000) {
                arg0->unk14 -= 0x180;
            }
            if ((arg0->unk28 - arg0->unk10) <= FIX(-1)) {
                arg0->unk14 = 0;
                arg0->substep = 0;
                arg0->step = 1;
                break;
            }
            break;
        }
        break;
    case 1:
        if (arg0->unkE > -0x20) {
            arg0->unkE -= 0x10;
        }
        if (arg0->unk24 < 0x20) {
            arg0->unk24 += 0x28;
        }
        switch (arg0->substep) {
        case 0:
            if (arg0->unk8 < 0x4000) {
                arg0->unk0 += 0x60;
            }
            if ((arg0->unk28 - arg0->unk10) < FIX(-0.5)) {
                arg0->unk14 += 0x180;
                break;
            }
            PlaySfxPositional(SFX_UNK_RNZ1_EXPLODE_822);
            arg0->substep++;
            break;
        case 1:
            if (arg0->unk8 < 0x4000) {
                arg0->unk0 += 0x60;
            }
            if (arg0->unk10 > FIX(1.5)) {
                arg0->unk0 = 0;
                arg0->substep++;
                break;
            }
            break;
        case 2:
            if (arg0->unk1C < 0x4000) {
                arg0->unk14 += 0xE0;
            }
            if ((arg0->unk28 - arg0->unk10) >= FIX(1.75)) {
                arg0->unk14 = 0;
                arg0->substep = 0;
                arg0->step = 0;
            }
            break;
        }
        break;
    }
}

static void func_us_801ABA38(batWingStruct* arg0) {
    s32 var_s2;
    s16 var_s1;
    s16 var_s0;

    var_s1 = 0;
    var_s0 = 0;
    var_s2 = 0;
    switch (arg0->step) {
    case 3:
        var_s1 += 0x80;
        var_s0 += 0xC0;
        /* fallthrough */
    case 1:
        var_s0 -= 0xC0;
        /* fallthrough */
    case 2:
    case 0:
        var_s1 += (-0x80 - arg0->unkE);
        arg0->unkE += var_s1 / 16;
        var_s2 = (FIX(-0.5) - arg0->unk10);
        arg0->unk0 = var_s2 / 16;
        var_s0 += (0x40 - arg0->unk24);
        arg0->unk24 += var_s0 / 16;
        var_s2 = (FIX(-1) - arg0->unk28);
        arg0->unk14 = var_s2 / 32;
        if (abs(var_s1 + var_s0) < 0x20) {
            arg0->step += 1;
            arg0->step &= 3;
        }
    }
}

static void func_us_801ABB58(batWingStruct* arg0) {
    s16 temp;

    switch (arg0->step) {
    case 0:
        temp = 0x140 - arg0->unkE;
        arg0->unkE += temp / 8;
        temp = 0x100 - arg0->unk24;
        arg0->unk24 += temp / 8;
        switch (arg0->substep) {
        case 0:
            if (arg0->unk8 > FIX(-0.5)) {
                arg0->unk0 = arg0->unk0 - 0x180;
            }
            if (arg0->unk10 < FIX(-2)) {
                arg0->unk0 = 0;
                arg0->substep += 1;
                arg0->unk14 = -0x2000;
                break;
            }
            break;
        case 1:
            if (arg0->unk1C > FIX(-0.5)) {
                arg0->unk14 -= 0x100;
            }
            if (arg0->unk28 < 0) {
                arg0->unk14 = 0;
                arg0->substep = 0;
                arg0->step = 1;
                break;
            }
            break;
        }
        break;
    case 1:
        temp = 0x100 - arg0->unkE;
        arg0->unkE += temp / 8;
        temp = 0x180 - arg0->unk24;
        arg0->unk24 += temp / 8;
        switch (arg0->substep) {
        case 0:
            if (arg0->unk8 < FIX(0.5)) {
                arg0->unk0 += 0xC0;
            }
            if (arg0->unk1C < FIX(0.5)) {
                arg0->unk14 += 0xC0;
            }
            if (arg0->unk10 > FIX(1.5)) {
                arg0->unk0 = 0;
                arg0->substep += 1;
                break;
            }
            break;
        case 1:
            if (arg0->unk1C < FIX(0.5)) {
                arg0->unk14 += 0xC0;
            }
            if ((arg0->unk28 - arg0->unk10) >= FIX(2)) {
                arg0->unk14 = 0;
                arg0->substep = 0;
                arg0->step = 0;
            }
            break;
        }
        break;
    }
}

static void emptyFunction(void) {}

static void func_us_801ABDC8(batWingStruct* arg0) {
    arg0->unk0 -= 0x400;
    arg0->unk14 -= 0x400;
}

extern EInit g_EInitDarkwingBat2;
static SVECTOR vec1 = {56, 0, 0};
static SVECTOR vec2 = {4, 0, 0};
static SVECTOR vec3 = {56, 0, 128};
static SVECTOR vec4 = {4, 0, 128};
static SVECTOR vec5 = {88, 0, 0};
static SVECTOR vec6 = {0, 0, 0};
static SVECTOR vec7 = {88, 0, 128};
static SVECTOR vec8 = {0, 0, 128};

static SVECTOR* positive_vecs[] = {&vec1, &vec2, &vec4, &vec5, &vec7, &vec8};
// All the same vectors but with the X coordinate negated
static SVECTOR vecn1 = {-56, 0, 0};
static SVECTOR vecn2 = {-4, 0, 0};
static SVECTOR vecn3 = {-56, 0, 128};
static SVECTOR vecn4 = {-4, 0, 128};
static SVECTOR vecn5 = {-88, 0, 0};
static SVECTOR vecn6 = {-0, 0, 0};
static SVECTOR vecn7 = {-88, 0, 128};
static SVECTOR vecn8 = {-0, 0, 128};
static SVECTOR* negative_vecs[] = {
    &vecn1, &vecn2, &vecn4, &vecn5, &vecn7, &vecn8};

// Probably not actually s32, but with it being unused, hard to know.
// Doesn't really match any common data we run into.
static s32 unused[] = {
    0x10000000, 0, 0x4000800, 0, 0x0800, 0x10000000, 0, 0, 0, 0};

static AnimateEntityFrame anim[] = {
    {6, 41}, {6, 42}, {5, 43}, {6, 42}, POSE_LOOP(0)};

// BSS vars, not sure why order is reversed.
// Likely something we could remove ifdef on, just don't know how
#ifdef VERSION_US
static batWingStruct wing1;
static batWingStruct wing2;
static batWingStruct* wingPtrs[2];
static batWingStruct* currWing;
#else
static batWingStruct* currWing;
static batWingStruct* wingPtrs[2];
static batWingStruct wing2;
static batWingStruct wing1;
#endif

void EntityDarkwingBatWings(Entity* self) {
    Entity* mainBat;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s32 clip;
    bool should_destroy;
    Primitive* prim2;

    wingPtrs[0] = &wing1;
    wingPtrs[1] = &wing2;
    FntPrint("wing step %x\n", self->step);
    FntPrint("wing step_s %x\n", self->step_s);
    mainBat = self - 1;
    if ((mainBat->flags & FLAG_DEAD) && (self->step != 5)) {
        for (i = 0; i < 2; i++) {
            currWing = wingPtrs[i];
            currWing->step = 0;
            currWing->substep = 0;
        }
        SetStep(5);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDarkwingBat2);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 10);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.batwing.prim = prim;
            for (i = 0; i < 4; i++) {
                prim->tpage = 0x13;
                prim->clut = 0x200;
                if (i % 2) {
                    prim->u0 = 0x80;
                    prim->u1 = 0x80;
                    prim->u2 = 0xF0;
                    prim->u3 = 0xF0;
                    prim->v1 = 0x48;
                    prim->v3 = 0x48;
                    prim->v0 = 0x20;
                    prim->v2 = 0x10;
                } else {
                    prim->u0 = 0x80;
                    prim->u1 = 0x80;
                    prim->u2 = 0xF0;
                    prim->u3 = 0xF0;
                    prim->v1 = 0x20;
                    prim->v3 = 0x10;
                    prim->v0 = 4;
                    prim->v2 = 4;
                }
                prim->r0 = prim->g0 = prim->b0 = 0x80;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->priority = self->zPriority;
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
            }
            self->ext.batwing.prim2 = prim;
            for (i = 0; i < 4; i++) {
                prim->tpage = 0x12;
                prim->clut = 0x200;
                if (i % 2) {
                    prim->u0 = 0x80;
                    prim->u1 = 0x80;
                    prim->u2 = 0xF0;
                    prim->u3 = 0xF0;
                    prim->v1 = 0;
                    prim->v3 = 0;
                    prim->v0 = 0x24;
                    prim->v2 = 0x34;
                } else {
                    prim->u0 = 0x80;
                    prim->u1 = 0x80;
                    prim->u2 = 0xF0;
                    prim->u3 = 0xF0;
                    prim->v1 = 0x24;
                    prim->v3 = 0x34;
                    prim->v0 = 0x44;
                    prim->v2 = 0x44;
                }
                prim->r0 = prim->g0 = prim->b0 = 0x40;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->priority = self->zPriority;
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        self->pose = 0;
        self->poseTimer = 0;
    case 1:
        self->ext.batwing.rotX = -0x100;
        self->ext.batwing.rotY = 0x400;
        self->ext.batwing.rotZ = 0;
        self->ext.batwing.transZ = 0x260;
        for (i = 0; i < 2; i++) {
            currWing = wingPtrs[i];
            WipeBatwing(currWing);
            currWing->unk24 = -0x80;
            currWing->unk2C = i;
        }
        self->ext.batwing.unused = 0x200;
        self->step_s = 0;
        self->step = 2;
        self->step = 3;
        break;
    case 2:
        for (i = 0; i < 2; i++) {
            currWing = wingPtrs[i];
            func_us_801AB768(currWing);
        }
        mainBat = self - 1;
        if (mainBat->ext.darkwing.unk85) {
            for (i = 0; i < 2; i++) {
                currWing = wingPtrs[i];
                currWing->step = 0;
                currWing->substep = 0;
            }
            SetStep(3);
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            self->ext.batwing.timer = 0x38;
            mainBat = self - 1;
            if (!mainBat->ext.darkwing.unk85) {
                self->step_s++;
            }
            /* fallthrough */
        case 1:
            for (i = 0; i < 2; i++) {
                currWing = wingPtrs[i];
                func_us_801ABA38(currWing);
            }
            if (!--self->ext.batwing.timer) {
                for (i = 0; i < 2; i++) {
                    currWing = wingPtrs[i];
                    currWing->step = 0;
                    currWing->substep = 0;
                }
                SetStep(2);
            }
            mainBat = self - 1;
            if (mainBat->ext.darkwing.unk86) {
                for (i = 0; i < 2; i++) {
                    currWing = wingPtrs[i];
                    currWing->step = 0;
                    currWing->substep = 0;
                }
                SetStep(4);
            }
            break;
        }
        break;
    case 4:
        for (i = 0; i < 2; i++) {
            currWing = wingPtrs[i];
            func_us_801ABB58(currWing);
        }
        mainBat = self - 1;
        if (!mainBat->ext.darkwing.unk86) {
            for (i = 0; i < 2; i++) {
                currWing = wingPtrs[i];
                currWing->step = 0;
                currWing->substep = 0;
            }
            SetStep(3);
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            self->ext.batwing.rotX = 0;
            wing1.unk0 = 0;
            wing1.unk14 = 0;
            wing2.unk0 = 0;
            wing2.unk14 = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            for (i = 0; i < 2; i++) {
                currWing = wingPtrs[i];
                func_us_801ABDC8(currWing);
            }
            mainBat = self - 1;
            if (mainBat->posY.i.hi > 0xB0) {
                wing1.unk0 = 0;
                wing1.unk14 = 0;
                wing2.unk0 = 0;
                wing2.unk14 = 0;
                self->step_s++;
                PlaySfxPositional(SFX_UNK_RNZ1_DEBRIS_820);
            }
            break;
        case 2:
            should_destroy = true;
            for (i = 0; i < 2; i++) {
                currWing = wingPtrs[i];
                // Well now we're treating BF80 as if its next pointer is an
                // integer That is extremely unusual.
                currWing->unk0 += 0x40;
                currWing->unk14 += 0x40;
                if (currWing->unk10 > 0) {
                    currWing->unk10 = 0;
                    currWing->unk0 = 0;
                } else {
                    should_destroy = false;
                }
                if (currWing->unk28 > 0) {
                    currWing->unk28 = 0;
                    currWing->unk14 = 0;
                } else {
                    should_destroy = false;
                }
            }
            if (should_destroy) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
    }
    mainBat = self - 1;
    self->facingLeft = mainBat->facingLeft;
    self->posX.i.hi = mainBat->posX.i.hi;
    self->posY.i.hi = mainBat->posY.i.hi;
    if (mainBat->ext.darkwing.unk87) {
        AnimateEntity(anim, self);
    } else {
        self->animCurFrame = 0;
    }
    if (!mainBat->ext.darkwing.unk84) {
        for (prim = &g_PrimBuf[self->primIndex]; prim != NULL;
             prim = prim->next) {
            prim->drawMode = DRAW_HIDE;
        }
        return;
    }
    self->ext.batwing.rotZ = mainBat->rotate;
    if (mainBat->rotate) {
        if (mainBat->facingLeft) {
            self->posX.i.hi += ((rcos(mainBat->rotate) * 0x18) >> 0xC);
        } else {
            self->posX.i.hi += -((rcos(mainBat->rotate) * 0x18) >> 0xC);
        }
        self->posY.i.hi += -((rsin(mainBat->rotate) * 0x18) >> 0xC);
    } else if (mainBat->facingLeft) {
        self->posX.i.hi += 0x18;
    } else {
        self->posX.i.hi -= 0x18;
    }
    for (i = 0; i < 2; i++) {
        currWing = wingPtrs[i];
        currWing->unk30 = self->posX.i.hi;
        currWing->unk32 = self->posY.i.hi;
        func_us_801AB198(currWing);
    }
    prim = self->ext.batwing.prim;
    currWing = wingPtrs[0];
    prim = func_us_801AB380(currWing, prim, positive_vecs);
    currWing = wingPtrs[1];
    prim = func_us_801AB380(currWing, prim, negative_vecs);
    prim = self->ext.batwing.prim;
    prim2 = self->ext.batwing.prim2;
    for (i = 0; i < 4; i++) {
#define LONG(x) (*(long*)&(x))

        if (!(i % 2)) {
            clip = NormalClip(LONG(prim->x0), LONG(prim->x1), LONG(prim->x2));
        } else {
            clip = NormalClip(LONG(prim->x0), LONG(prim->x1), LONG(prim->x3));
        }
        if (i > 1) {
            clip = -clip;
        }
        if (clip > 0) {
            prim->drawMode = DRAW_HIDE;
            prim2->drawMode = DRAW_UNK02;
            LOW(prim2->x0) = LOW(prim->x0);
            LOW(prim2->x1) = LOW(prim->x1);
            LOW(prim2->x2) = LOW(prim->x2);
            LOW(prim2->x3) = LOW(prim->x3);
            prim2->priority = prim->priority;
        } else {
            prim->drawMode = DRAW_UNK02;
            prim2->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
        prim2 = prim2->next;
    }
}
