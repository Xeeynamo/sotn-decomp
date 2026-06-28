// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno3/rno3.h"

extern s16 D_pspeu_0925A550[];

void func_pspeu_0924EB18(void) {
    // return value not used, but function has side effects
    s32 unused = UnkCollisionFunc2(&D_pspeu_0925A550);
    // if cooldown has expired...
    if (!g_CurrentEntity->ext.ILLEGAL.u8[5]) {
        if (GetDistanceToPlayerX() >= 0x80){
            return;
        }
        if((g_CurrentEntity->facingLeft) ^ (GetSideToPlayer() & 1)) {
            SetStep(6);
        }
    } else {
        g_CurrentEntity->ext.ILLEGAL.u8[5]--;
    }
}

extern SVECTOR D_pspeu_0925A680;
extern SVECTOR D_pspeu_0925A688;
extern SVECTOR D_pspeu_0925A690;
extern SVECTOR D_pspeu_0925A698;

void func_pspeu_0924EBC8(void) {
    s32 p;
    s32 flag;
    SVECTOR sp60;
    VECTOR sp50;
    MATRIX sp30;
    SVECTOR sp28 = {0};
    s32 yVar;
    s32 xVar;
    Primitive* prim;

    switch (g_CurrentEntity->ext.ILLEGAL.u8[0xC]) {
    case 0:
        g_CurrentEntity->ext.ILLEGAL.s16[8] = 0;
        prim = g_CurrentEntity->ext.prim;        
        prim->r0 = prim->g0 = prim->b0 = 0xC0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->drawMode = 0x37;
        g_CurrentEntity->ext.ILLEGAL.u8[0xC] = 1;
        break;
    case 1:
        g_CurrentEntity->ext.ILLEGAL.s16[9] += 0x100;
        g_CurrentEntity->ext.ILLEGAL.s16[8] += 0x200;
        break;
    }
    SetGeomScreen(0x200);
    xVar = g_CurrentEntity->posX.i.hi;
    yVar = g_CurrentEntity->posY.i.hi;
    if (g_CurrentEntity->facingLeft) {
        xVar += 10;
    } else {
        xVar -= 10;
    }
    yVar -= 2;
    SetGeomOffset(xVar, yVar);
    sp60.vx = 0;
    if (g_CurrentEntity->facingLeft) {
        sp60.vy = -0x2E0;
    } else {
        sp60.vy = 0x2E0;
    }
    sp60.vz = g_CurrentEntity->ext.ILLEGAL.s16[9];
    RotMatrix(&sp28, &sp30);
    RotMatrixZ(sp60.vz, &sp30);
    RotMatrixY(sp60.vy, &sp30);
    sp50.vx = 0;
    sp50.vy = 0;
    sp50.vz = 0x200;
    TransMatrix(&sp30, &sp50);
    sp50.vx = g_CurrentEntity->ext.ILLEGAL.s16[8];
    sp50.vy = g_CurrentEntity->ext.ILLEGAL.s16[8];
    sp50.vz = 0x1000;
    ScaleMatrix(&sp30, &sp50);
    SetRotMatrix(&sp30);
    SetTransMatrix(&sp30);
    prim = g_CurrentEntity->ext.prim;
    RotTransPers4(&D_pspeu_0925A680, &D_pspeu_0925A688, &D_pspeu_0925A690, &D_pspeu_0925A698, (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2,
                      (long*)&prim->x3, (long*)&p, (long*)&flag);
}

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/e_nova_skeleton", EntityNovaSkeleton);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/e_nova_skeleton", EntityBladeSoldierDeathParts);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/e_nova_skeleton", func_us_801C2FF0);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/e_nova_skeleton", func_us_801C34A0);
