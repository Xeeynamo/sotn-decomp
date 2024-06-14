#include <common.h>
#include <psxsdk/libgte.h>
#include <log.h>
#include <math.h>

void InitGeom() { NOT_IMPLEMENTED; }

void SetGeomOffset(long ofx, long ofy) { NOT_IMPLEMENTED; }

void SetGeomScreen(long h) { NOT_IMPLEMENTED; }

int rsin(int a) {
    float x = (s16)a / 4096.f * M_PI * 2;
    return sin(x) * 4096.f;
}

int rcos(int a) {
    float x = (s16)a / 4096.f * M_PI * 2;
    return cos(x) * 4096.f;
}

long ratan2(long y, long x) { return (long)(atan2(y, x) * 2048.0 / M_PI); }

long SquareRoot0(long a) { return (long)sqrt((double)a); }

long SquareRoot12(long a) { return (long)sqrt((double)a * 4096.0); }

MATRIX* RotMatrix(SVECTOR* r, MATRIX* m) {
    NOT_IMPLEMENTED;
    return 0;
}

MATRIX* TransMatrix(MATRIX* m, VECTOR* v) {
    NOT_IMPLEMENTED;
    return 0;
}

void SetRotMatrix(MATRIX* m) { NOT_IMPLEMENTED; }

MATRIX* RotMatrixX(long r, MATRIX* m) {
    NOT_IMPLEMENTED;
    return m;
}

MATRIX* RotMatrixY(long r, MATRIX* m) {
    NOT_IMPLEMENTED;
    return m;
}

MATRIX* RotMatrixZ(long r, MATRIX* m) {
    NOT_IMPLEMENTED;
    return m;
}

void SetLightMatrix(MATRIX* m) { NOT_IMPLEMENTED; }

void SetColorMatrix(MATRIX* m) { NOT_IMPLEMENTED; }

MATRIX* ScaleMatrix(MATRIX* m, VECTOR* v) {
    NOT_IMPLEMENTED;
    return m;
}

void SetTransMatrix(MATRIX* m) { NOT_IMPLEMENTED; }

void SetBackColor(long rbk, long gbk, long bbk) { NOT_IMPLEMENTED; }

void func_80017008(VECTOR* v, long* l) { NOT_IMPLEMENTED; }

long RotAverageNclip3(SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, long* sxy0,
                      long* sxy1, long* sxy2, long* p, long* otz, long* flag) {
    NOT_IMPLEMENTED;
    return 0;
}

long RotAverage3(SVECTOR* v0, SVECTOR* v1, SVECTOR* v2, long* sxy0, long* sxy1,
                 long* sxy2, long* p, long* flag) {
    NOT_IMPLEMENTED;
    return 0;
}

long RotTransPers4(
    SVECTOR* v0, SVECTOR* v1, SVECTOR* v2,
    SVECTOR* v3, // Pointers to vectors (input)
    long* v10, long* v11, long* v12,
    long* v13, // Pointers to screen coordinates
    long* p,   // Pointer to interpolated value for depth cueing
    long* flag // Pointer to flag)
) {
    NOT_IMPLEMENTED;
    return 0;
}
