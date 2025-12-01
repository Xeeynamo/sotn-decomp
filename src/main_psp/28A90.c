// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include <game_psp.h>
#include <psxsdk/libgte.h>
#include <psxsdk/libgpu.h>

extern SVECTOR D_psp_08C63B28;
extern SVECTOR D_psp_08C63B30;
extern SVECTOR D_psp_08C63B38;
extern s16 D_psp_08C63B44;
extern s32 D_psp_08C63B4C;
extern s32 D_psp_08C63B50;
extern s32 D_psp_08C63B54;
extern s16 D_psp_08C63B58;
extern s16 D_psp_08C63B5A;
extern s16 D_psp_08C63B5C;
extern s16 D_psp_08C63B5E;
extern s16 D_psp_08C63B60;
extern s16 D_psp_08C63B62;
extern s32 D_psp_08C63B78;
extern s32 D_psp_08C63B88;
extern MATRIX D_psp_08C63BA8;
extern MATRIX D_psp_08C63BC8;
extern MATRIX D_psp_08C63BE8;
extern s32 D_psp_08C63C08;
extern s32 D_psp_08C63C0C;
extern s16 D_psp_08C63C10;
extern s16 D_psp_08C63C1C;
extern s16 D_psp_08C63C20;

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", ApplyRotMatrix);

MATRIX* ScaleMatrix(MATRIX* m, VECTOR* v) {
    m->m[0][0] = m->m[0][0] * v->vx / 0x1000;
    m->m[1][0] = m->m[1][0] * v->vx / 0x1000;
    m->m[2][0] = m->m[2][0] * v->vx / 0x1000;
    m->m[0][1] = m->m[0][1] * v->vy / 0x1000;
    m->m[1][1] = m->m[1][1] * v->vy / 0x1000;
    m->m[2][1] = m->m[2][1] * v->vy / 0x1000;
    m->m[0][2] = m->m[0][2] * v->vz / 0x1000;
    m->m[1][2] = m->m[1][2] * v->vz / 0x1000;
    m->m[2][2] = m->m[2][2] * v->vz / 0x1000;
    return m;
}

MATRIX* CompMatrix(MATRIX* m0, MATRIX* m1, MATRIX* m2) {
    m2->m = m0->m;
    m2->t = m0->t;
    MulMatrix(m2, m1);
    SetRotMatrix(m0);
    m2->t[0] = m0->t[0] + (D_psp_08C63BA8.m[0][0] / 4096.0f * m1->t[0]) +
               (D_psp_08C63BA8.m[0][1] / 4096.0f * m1->t[1]) +
               (D_psp_08C63BA8.m[0][2] / 4096.0f * m1->t[2]);
    m2->t[1] = m0->t[1] + (D_psp_08C63BA8.m[1][0] / 4096.0f * m1->t[0]) +
               (D_psp_08C63BA8.m[1][1] / 4096.0f * m1->t[1]) +
               (D_psp_08C63BA8.m[1][2] / 4096.0f * m1->t[2]);
    m2->t[2] = m0->t[2] + (D_psp_08C63BA8.m[2][0] / 4096.0f * m1->t[0]) +
               (D_psp_08C63BA8.m[2][1] / 4096.0f * m1->t[1]) +
               (D_psp_08C63BA8.m[2][2] / 4096.0f * m1->t[2]);
    return NULL;
}

void DpqColor(CVECTOR* v0, long p, CVECTOR* v1) {
    v1->r = v0->r;
    v1->g = v0->g;
    v1->b = v0->b;
    v1->cd = v0->cd;
}

void NormalColorDpq(SVECTOR* v0, CVECTOR* v1, long p, CVECTOR* v2) {
    v2->r = v1->r;
    v2->g = v1->g;
    v2->b = v1->b;
    v2->cd = v1->cd;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", NormalClip);

void RotTrans(SVECTOR* v0, VECTOR* v1, long* flag) {
    gte_ldv0(v0);
    func_psp_08928980();
    v1->vx = D_psp_08C63B58;
    v1->vy = D_psp_08C63B5A;
    v1->vz = 0;
    *flag = 0;
}

long RotTransPers(SVECTOR* v0, long* sxy, long* p, long* flag) {
    gte_ldv0(v0);
    gte_rtps();
    gte_stsxy(sxy);
    *p = 0;
    *flag = 0;
    return D_psp_08C63B44 / 4;
}

long RotTransPers3(SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, long* sxy0,
                   long* sxy1, long* sxy2, long* p, long* flag) {
    gte_ldv0(v0);
    gte_ldv1(v1);
    gte_ldv2(v2);
    gte_rtpt();
    *sxy0 = LOW(D_psp_08C63B58);
    *sxy1 = LOW(D_psp_08C63B5C);
    *sxy2 = LOW(D_psp_08C63B60);
    *p = 0;
    *flag = 0;
    return D_psp_08C63B44 / 4;
}

long RotTransPers4(
    SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, SVECTOR* v3, long* sxy0, long* sxy1,
    long* sxy2, long* sxy3, long* p, long* flag) {
    RotTransPers(v0, sxy0, p, flag);
    return RotTransPers3(v1, v2, v3, sxy1, sxy2, sxy3, p, flag);
}

long RotAverage3(SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, long* sxy0, long* sxy1,
                 long* sxy2, long* p, long* flag) {
    return RotTransPers3(v0, v1, v2, sxy0, sxy1, sxy2, p, flag);
}

long RotAverage4(SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, SVECTOR* v3, long* sxy0,
                 long* sxy1, long* sxy2, long* sxy3, long* p, long* flag) {
    return RotTransPers4(v0, v1, v2, v3, sxy0, sxy1, sxy2, sxy3, p, flag);
}

long RotAverageNclip3(SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, long* sxy0,
                      long* sxy1, long* sxy2, long* p, long* otz, long* flag) {
    *otz = RotTransPers3(v0, v1, v2, sxy0, sxy1, sxy2, p, flag);
    gte_nclip();
    return D_psp_08C63B88;
}

long RotAverageNclip4(
    SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, SVECTOR* v3, long* sxy0, long* sxy1,
    long* sxy2, long* sxy3, long* p, long* otz, long* flag) {
    s32 temp_s0;

    RotTransPers3(v0, v1, v2, sxy0, sxy1, sxy2, p, flag);
    gte_nclip();
    temp_s0 = D_psp_08C63B88;
    RotTransPers(v3, sxy3, p, flag);
    return temp_s0;
}

long func_psp_08927C5C(long a) {
    s32 temp_v0;
    s32 var_a1;

    if (a == 0 || a < 0) {
        return 0;
    }
    var_a1 = (a > 1) ? a : 1;
    do {
        temp_v0 = var_a1;
        var_a1 = (var_a1 + (a / var_a1)) / 2;
    } while (var_a1 < temp_v0);
    return temp_v0;
}

long SquareRoot0(long a) { return func_psp_08927C5C(a); }

long SquareRoot12(long a) { return func_psp_08927C5C(a / 0x1000) * 0x1000; }

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", ratan2);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", VectorNormalS);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", rcos);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", rsin);

void gte_stub(void) {}

void InitGeom(void) {
    SetGeomScreen(0);
    SetGeomOffset(0, 0);
    D_psp_08C63C1C = 0x555;
    D_psp_08C63C20 = 0x400;
}

void SetGeomScreen(long h) { D_psp_08C63C10 = h; }

void SetGeomOffset(long ofx, long ofy) {
    D_psp_08C63C08 = ofx & 0xFFFF;
    D_psp_08C63C0C = ofy & 0xFFFF;
}

void SetFarColor(long rfc, long gfc, long bfc) {}

void SetFogNear(long a, long h) {}

MATRIX* MulMatrix(MATRIX* m0, MATRIX* m1) {
    MATRIX temp;
    s32 i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            temp.m[i][j] = m0->m[i][0] * m1->m[0][j] / 0x1000 +
                           m0->m[i][1] * m1->m[1][j] / 0x1000 +
                           m0->m[i][2] * m1->m[2][j] / 0x1000;
        }
    }
    m0->m = temp.m;
    m0->t = temp.t;
    return m0;
}

MATRIX* MulMatrix2(MATRIX* m0, MATRIX* m1) {
    MATRIX temp;
    s32 i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            temp.m[i][j] = m0->m[i][0] * m1->m[0][j] / 0x1000 +
                           m0->m[i][1] * m1->m[1][j] / 0x1000 +
                           m0->m[i][2] * m1->m[2][j] / 0x1000;
        }
    }
    m1->m = temp.m;
    m1->t = temp.t;
    return m1;
}

MATRIX* func_psp_08928428(MATRIX* m0, MATRIX* m1) {
    MATRIX temp;

    temp.m = m0->m;
    temp.t = m0->t;
    MulMatrix(&temp, m1);
    SetRotMatrix(&temp);
    return m0;
}

MATRIX* func_psp_08928498(long r, MATRIX* m) {
    m->m[0][0] = 0x1000;
    m->m[0][1] = 0;
    m->m[0][2] = 0;
    m->m[1][0] = 0;
    m->m[1][1] = rcos(r);
    m->m[1][2] = -rsin(r);
    m->m[2][0] = 0;
    m->m[2][1] = rsin(r);
    m->m[2][2] = rcos(r);
    m->t[2] = 0;
    m->t[1] = 0;
    m->t[0] = 0;
    return m;
}

MATRIX* func_psp_0892851C(long r, MATRIX* m) {
    m->m[0][0] = rcos(r);
    m->m[0][1] = 0;
    m->m[0][2] = rsin(r);
    m->m[1][0] = 0;
    m->m[1][1] = 0x1000;
    m->m[1][2] = 0;
    m->m[2][0] = -rsin(r);
    m->m[2][1] = 0;
    m->m[2][2] = rcos(r);
    m->t[2] = 0;
    m->t[1] = 0;
    m->t[0] = 0;
    return m;
}

MATRIX* func_psp_089285A0(long r, MATRIX* m) {
    m->m[0][0] = rcos(r);
    m->m[0][1] = -rsin(r);
    m->m[0][2] = 0;
    m->m[1][0] = rsin(r);
    m->m[1][1] = rcos(r);
    m->m[1][2] = 0;
    m->m[2][0] = 0;
    m->m[2][1] = 0;
    m->m[2][2] = 0x1000;
    m->t[2] = 0;
    m->t[1] = 0;
    m->t[0] = 0;
    return m;
}

MATRIX* RotMatrixX(long r, MATRIX* m) {
    MATRIX rot;

    func_psp_08928498(r, &rot);
    MulMatrix2(&rot, m);
    return m;
}

MATRIX* RotMatrixY(long r, MATRIX* m) {
    MATRIX rot;

    func_psp_0892851C(r, &rot);
    MulMatrix2(&rot, m);
    return m;
}

MATRIX* RotMatrixZ(long r, MATRIX* m) {
    MATRIX rot;

    func_psp_089285A0(r, &rot);
    MulMatrix2(&rot, m);
    return m;
}

MATRIX* RotMatrix(SVECTOR* r, MATRIX* m) {
    MATRIX rotY;
    MATRIX rotZ;

    func_psp_08928498(r->vx, m);
    func_psp_0892851C(r->vy, &rotY);
    func_psp_089285A0(r->vz, &rotZ);
    MulMatrix(m, &rotY);
    MulMatrix(m, &rotZ);
    return m;
}

MATRIX* RotMatrixYXZ(SVECTOR* r, MATRIX* m) {
    MATRIX rotX;
    MATRIX rotZ;

    func_psp_0892851C(r->vy, m);
    func_psp_08928498(r->vx, &rotX);
    func_psp_089285A0(r->vz, &rotZ);
    MulMatrix(m, &rotX);
    MulMatrix(m, &rotZ);
    return m;
}

void SetRotMatrix(MATRIX* m) {
    D_psp_08C63BA8.m[0][0] = m->m[0][0];
    D_psp_08C63BA8.m[0][1] = m->m[0][1];
    D_psp_08C63BA8.m[0][2] = m->m[0][2];
    D_psp_08C63BA8.m[1][0] = m->m[1][0];
    D_psp_08C63BA8.m[1][1] = m->m[1][1];
    D_psp_08C63BA8.m[1][2] = m->m[1][2];
    D_psp_08C63BA8.m[2][0] = m->m[2][0];
    D_psp_08C63BA8.m[2][1] = m->m[2][1];
    D_psp_08C63BA8.m[2][2] = m->m[2][2];
}

MATRIX* TransMatrix(MATRIX* m, VECTOR* v) {
    m->t[0] = v->vx;
    m->t[1] = v->vy;
    m->t[2] = v->vz;
    return m;
}

void SetTransMatrix(MATRIX* m) {
    D_psp_08C63BA8.t[0] = m->t[0];
    D_psp_08C63BA8.t[1] = m->t[1];
    D_psp_08C63BA8.t[2] = m->t[2];
}

void gte_SetTransVector(VECTOR* v) {
    D_psp_08C63BA8.t[0] = v->vx;
    D_psp_08C63BA8.t[1] = v->vy;
    D_psp_08C63BA8.t[2] = v->vz;
}

void gte_ldv0(SVECTOR* v) {
    D_psp_08C63B28.vx = v->vx;
    D_psp_08C63B28.vy = v->vy;
    D_psp_08C63B28.vz = v->vz;
}

void gte_ldv1(SVECTOR* v) {
    D_psp_08C63B30.vx = v->vx;
    D_psp_08C63B30.vy = v->vy;
    D_psp_08C63B30.vz = v->vz;
}

void gte_ldv2(SVECTOR* v) {
    D_psp_08C63B38.vx = v->vx;
    D_psp_08C63B38.vy = v->vy;
    D_psp_08C63B38.vz = v->vz;
}

void gte_ldv3c(SVECTOR* v) {
    gte_ldv0(&v[0]);
    gte_ldv1(&v[1]);
    gte_ldv2(&v[2]);
}

void gte_ldtx(s16 x) { D_psp_08C63BA8.t[0] = x; }

void gte_ldty(s16 y) { D_psp_08C63BA8.t[1] = y; }

void gte_ldtz(s16 z) { D_psp_08C63BA8.t[2] = z; }

void gte_ldtr(s16 x, s16 y, s16 z) {
    D_psp_08C63BA8.t[0] = x;
    D_psp_08C63BA8.t[1] = y;
    D_psp_08C63BA8.t[2] = z;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_08928980);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", gte_rtps);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", gte_rtpt);

void gte_stsxy(long* sxy) { *sxy = LOW(D_psp_08C63B58); }

void gte_stsxy3_gt3(POLY_GT3* poly) {
    poly->x0 = D_psp_08C63B58;
    poly->y0 = D_psp_08C63B5A;
    poly->x1 = D_psp_08C63B5C;
    poly->y1 = D_psp_08C63B5E;
    poly->x2 = D_psp_08C63B60;
    poly->y2 = D_psp_08C63B62;
}

void gte_stsxy3(long* sxy0, long* sxy1, long* sxy2) {
    *sxy0 = LOW(D_psp_08C63B58);
    *sxy1 = LOW(D_psp_08C63B5C);
    *sxy2 = LOW(D_psp_08C63B60);
}

void gte_stszotz(long* otz) { *otz = D_psp_08C63B44 / 4; }

void gte_stotz(long* otz) { *otz = D_psp_08C63B44 / 4; }

void gte_stopz(long* opz) { *opz = D_psp_08C63B88; }

void gte_dpcs(void) {}

void gte_strgb(long* rgb) { *rgb = D_psp_08C63B78; }

void gte_ldrgb(long* rgb) { D_psp_08C63B78 = *rgb; }

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", gte_nclip);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", gte_avsz3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_089295E4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", gte_avsz4);

void gte_ldv01c(SVECTOR* v) {
    gte_ldv0(&v[0]);
    gte_ldv1(&v[1]);
}

void gte_stsxy01c(SVECTOR* v) {
    v->vx = D_psp_08C63B58;
    v->vy = D_psp_08C63B5A;
    v->vz = D_psp_08C63B5C;
    v->pad = D_psp_08C63B5E;
}

void SetColorMatrix(MATRIX* m) {
    D_psp_08C63BE8.m[0][0] = m->m[0][0];
    D_psp_08C63BE8.m[0][1] = m->m[0][1];
    D_psp_08C63BE8.m[0][2] = m->m[0][2];
    D_psp_08C63BE8.m[1][0] = m->m[1][0];
    D_psp_08C63BE8.m[1][1] = m->m[1][1];
    D_psp_08C63BE8.m[1][2] = m->m[1][2];
    D_psp_08C63BE8.m[2][0] = m->m[2][0];
    D_psp_08C63BE8.m[2][1] = m->m[2][1];
    D_psp_08C63BE8.m[2][2] = m->m[2][2];
}

void SetLightMatrix(MATRIX* m) {
    D_psp_08C63BC8.m[0][0] = m->m[0][0];
    D_psp_08C63BC8.m[0][1] = m->m[0][1];
    D_psp_08C63BC8.m[0][2] = m->m[0][2];
    D_psp_08C63BC8.m[1][0] = m->m[1][0];
    D_psp_08C63BC8.m[1][1] = m->m[1][1];
    D_psp_08C63BC8.m[1][2] = m->m[1][2];
    D_psp_08C63BC8.m[2][0] = m->m[2][0];
    D_psp_08C63BC8.m[2][1] = m->m[2][1];
    D_psp_08C63BC8.m[2][2] = m->m[2][2];
}

void SetBackColor(long rbk, long gbk, long bbk) {
    D_psp_08C63BC8.t[0] = rbk * 0x1000 / 0x80;
    D_psp_08C63BC8.t[1] = gbk * 0x1000 / 0x80;
    D_psp_08C63BC8.t[2] = bbk * 0x1000 / 0x80;
}

void func_psp_08929838(SVECTOR* v) {
    D_psp_08C63B4C = v->vx;
    D_psp_08C63B50 = v->vy;
    D_psp_08C63B54 = v->vz;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_08929860);

void NormalColorCol(SVECTOR* v0, CVECTOR* v1, CVECTOR* v2) {
    func_psp_08929838(v0);
    gte_ldrgb((long*)v1);
    func_psp_08929860();
    gte_strgb((long*)v2);
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_08929FA8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A018);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A0C4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A0F0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A1EC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A21C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A28C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A2D8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A3D4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A414);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A620);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A70C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A76C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A7E0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A8C0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A8FC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A97C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A998);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", SsSetSerialVol);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", func_psp_0892A9E0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", strFileOpen);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", strFileClose);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", strFileRead);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", strFileLseek);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", play_bgm);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", init_atrac3plus);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", play_atrac3plus);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", createPlayModeFlag);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", setPlayMode);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", checkPlayMode);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", waitPlayMode);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", clearPlayMode);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", release_arg);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", at3plus_addData);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", reset_position);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", fadeoutOperation);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", DvdUmdIoInit);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", DvdUmdIoTerm);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", DvdUmdRetryOpenCB);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/28A90", DvdUmdRetryRead);
