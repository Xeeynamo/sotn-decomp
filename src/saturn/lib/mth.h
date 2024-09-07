#ifndef MTH_H
#define MTH_H

#include "xpt.h"
#include "def.h"

typedef Sint32 Fixed32;

typedef struct MthXy {
    Fixed32 x;
    Fixed32 y;
} MthXy;

typedef struct MthXyz {
    Fixed32 x;
    Fixed32 y;
    Fixed32 z;
} MthXyz;

typedef struct MthMatrix {
    Fixed32 val[3][4];
} MthMatrix;

typedef struct MthMatrixTbl {
    Uint16 stackSize;
    MthMatrix* current;
    MthMatrix* stack;
} MthMatrixTbl;

typedef struct MthViewLight {
    MthMatrix viewMatrix;
    MthXyz lightVector;
    MthMatrix worldMatrix;
} MthViewLight;

typedef struct MthPolyTransParm {
    MthViewLight* viewLight;
    Uint32 surfCount;
    MthXyz* surfPoint;
    MthXyz* surfNormal;
    Sint32* surfBright;
    Uint32 transViewVertCount;
    MthXyz* transViewVertSrc;
    MthXyz* transViewVertAns;
    Uint32 gourVertCount;
    MthXyz* vertNormal;
    Sint32* vertBright;
    Uint32 transWorldVertCount;
    MthXyz* transWorldVertSrc;
    MthXyz* transWorldVertAns;
} MthPolyTransParm;

Fixed32 MTH_Sin(Fixed32 degree);
Fixed32 MTH_Cos(Fixed32 degree);
Fixed32 MTH_Atan(Fixed32 y, Fixed32 x);

Fixed32 fsin(Fixed32 a);
Fixed32 fcos(Fixed32 a);

void MTH_InitialMatrix(
    MthMatrixTbl* matrixTbl, Uint16 stackSize, MthMatrix* matrix);
void MTH_ClearMatrix(MthMatrixTbl* matrixTbl);
void MTH_PushMatrix(MthMatrixTbl* matrixTbl);
void MTH_PopMatrix(MthMatrixTbl* matrixTbl);
void MTH_MoveMatrix(MthMatrixTbl* matrixTbl, Fixed32 x, Fixed32 y, Fixed32 z);
void MTH_RotateMatrixX(MthMatrixTbl* matrixTbl, Fixed32 xDegree);
void MTH_RotateMatrixY(MthMatrixTbl* matrixTbl, Fixed32 yDegree);
void MTH_RotateMatrixZ(MthMatrixTbl* matrixTbl, Fixed32 zDegree);
void MTH_ReverseZ(MthMatrixTbl* matrixTbl);
void MTH_MulMatrix(MthMatrix* a, MthMatrix* b, MthMatrix* c);
void MTH_CoordTrans(MthMatrix* matrix, MthXyz* src, MthXyz* ans);
void MTH_NormalTrans(MthMatrix* matrix, MthXyz* src, MthXyz* ans);

void MTH_PolyDataTransInit(void);
void MTH_PolyDataTransExec(MthPolyTransParm* polyTransParm);
void MTH_PolyDataTransCheck(void);

void MTH_Pers2D(MthXyz* p3d, MthXy* unitPixel, XyInt* p2d);
Sint32 MTH_ComputeBright(MthXyz* lightVector, MthXyz* normalVector);
void MTH_ComputeNormVect(
    Fixed32 surfNormK, MthXyz* p0, MthXyz* p1, MthXyz* p2, MthXyz* normal);

void MTH_InitialRand(Uint32 initVal);
Uint32 MTH_GetRand(void);

typedef struct {
    Uint32 num;
    Fixed32* MTH_crvh;
    Fixed32* MTH_crvd;
    Fixed32* MTH_crvx;
    Fixed32* MTH_crvy;
    Fixed32* MTH_crvz;
    Fixed32* MTH_crvp;
    Fixed32* MTH_crva;
    Fixed32* MTH_crvb;
    Fixed32* MTH_crvc;
} MthCurveWork;

#define MTH_INIT_CURVE(wk, n)                                                  \
    static Fixed32 MTH_crvh[n];                                                \
    static Fixed32 MTH_crvd[n];                                                \
    static Fixed32 MTH_crvx[n];                                                \
    static Fixed32 MTH_crvy[n];                                                \
    static Fixed32 MTH_crvz[n];                                                \
    static Fixed32 MTH_crvp[n];                                                \
    static Fixed32 MTH_crva[n];                                                \
    static Fixed32 MTH_crvb[n];                                                \
    static Fixed32 MTH_crvc[n];                                                \
    static MthCurveWork wk = {                                                 \
        n,        MTH_crvh, MTH_crvd, MTH_crvx, MTH_crvy,                      \
        MTH_crvz, MTH_crvp, MTH_crva, MTH_crvb, MTH_crvc}

Uint32 MTH_Curve2(MthCurveWork* work, MthXy* in_aray, Uint32 in_n, Uint32 step,
                  MthXy* out_aray);
Uint32 MTH_Curve2t(MthCurveWork* work, MthXy* in_aray, Uint32 in_n, Uint32 step,
                   MthXy* out_aray, MthXy* tan_aray);
Uint32 MTH_Curve3(MthCurveWork* work, MthXyz* in_aray, Uint32 in_n, Uint32 step,
                  MthXyz* out_aray);
Uint32 MTH_Curve3t(MthCurveWork* work, MthXyz* in_aray, Uint32 in_n,
                   Uint32 step, MthXyz* out_aray, MthXyz* tan_aray);
Fixed32 MTH_Sqrt(Fixed32 x);
Fixed32 MTH_Hypot(Fixed32 x, Fixed32 y);

#define MTH_FLOAT(x) ((Float32)((long)(x) / 65536.0))
#define MTH_FIXED(x) ((Fixed32)((x) * 65536.0))
Fixed32 MTH_IntToFixed(Sint32 x);
Sint32 MTH_FixedToInt(Fixed32 x);
Fixed32 MTH_Mul(Fixed32 a, Fixed32 b);
Fixed32 MTH_Div(Fixed32 a, Fixed32 b);
Fixed32 MTH_Product(Fixed32* a, Fixed32* b);

#endif
