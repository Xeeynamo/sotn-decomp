#include "common.h"
#include "psxsdk/libgte.h"

void SetVertex0(SVECTOR* vector) { gte_ldv0(vector); }

void SetVertex1(SVECTOR* vector) { gte_ldv1(vector); }

void SetVertex2(SVECTOR* vector) { gte_ldv2(vector); }

void SetVertexTri(SVECTOR* vector1, SVECTOR* vector2, SVECTOR* vector3) {
    gte_ldv0(vector1);
    gte_ldv1(vector2);
    gte_ldv2(vector3);
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgte/reg03", SetRGBfifo);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgte/reg03", SetIR123);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgte/reg03", SetIR0);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgte/reg03", SetSZfifo3);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgte/reg03", SetSZfifo4);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgte/reg03", SetSXSYfifo);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgte/reg03", SetRii);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgte/reg03", SetMAC123);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgte/reg03", SetData32);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgte/reg03", SetDQA);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgte/reg03", SetDQB);
