// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz1.h"

void func_801B2CF8(s32* arg0) {
    s32* ptr = arg0;
    s32 bound = 13;
    s32 i;

    for(i = 0; i < bound; i++) {
        *ptr++ = 0;
    }
}

void func_us_801AB16C(s32* arg0, s32* arg1) {
    s32 bound = 13;
    s32 i;

    for(i = 0; i < bound; i++) {
        *arg1++ = *arg0++;
    }
}

typedef struct{
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

void func_us_801AB198(batWingStruct* arg0) {
    s32 var_s2;
    s32 var_s1;
    s32 var_s0;

    var_s2 = arg0->unk8 * 0x50 / 0x100;
    var_s1 = arg0->unk0;
    arg0->unk4 = (var_s2 * rcos(arg0->unkE) / 0x1000) + (((arg0->unk18 * rcos(arg0->unk28 / 0x100)) / 0x1000) * 0x3E) / 0x100;
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

Primitive* func_us_801AB380(batWingStruct* arg0, Primitive* prim, SVECTOR** arg2) {
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
    Entity* other;

    rotVec.vx = g_CurrentEntity->ext.ILLEGAL.s16[4];
    rotVec.vy = g_CurrentEntity->ext.ILLEGAL.s16[5];
    rotVec.vz = g_CurrentEntity->ext.ILLEGAL.s16[6];
    RotMatrix(&sp38, &m);
    RotMatrixY(rotVec.vy, &m);
    RotMatrixX(rotVec.vx, &m);
    RotMatrixZ(rotVec.vz, &m);
    other = g_CurrentEntity - 1;
    if (other->facingLeft) {
        RotMatrixY(0x800, &m);
    }
    xOffset = arg0->unk30;
    yOffset = arg0->unk32;
    transX = 0;
    transY = 0;
    transZ = g_CurrentEntity->ext.ILLEGAL.s16[7];
    rotX = arg0->unkC;
    rotY = arg0->unkE;
    rotZ = arg0->unk10 / 0x100;
    SetGeomScreen(0x180);
    for(i = 0; i < 2; i += 1) {
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
        prim->priority = ((g_CurrentEntity->zPriority + g_CurrentEntity->ext.ILLEGAL.s16[7] / 4) - zOffset);
        prevPrim = prim;
        prim = prim->next;
    }
    return prim;
}

void func_us_801AB768(batWingStruct* arg0) {
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
            PlaySfxPositional(0x822);
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

void func_us_801ABA38(batWingStruct* arg0) {
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
        arg0->unk24 += var_s0/ 16;
        var_s2 = (FIX(-1) - arg0->unk28);
        arg0->unk14 = var_s2 / 32;
        if (abs(var_s1 + var_s0) < 0x20) {
            arg0->step += 1;
            arg0->step &= 3;
        }
    }
}

INCLUDE_ASM("st/rnz1/nonmatchings/unk_2B148", func_us_801ABB58);

void RNZ1_Unused801ABDC0(void) {}

INCLUDE_ASM("st/rnz1/nonmatchings/unk_2B148", func_us_801ABDC8);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_2B148", func_us_801ABDE4);
