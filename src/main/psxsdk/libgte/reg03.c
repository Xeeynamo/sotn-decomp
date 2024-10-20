#include "common.h"
#include "psxsdk/libgte.h"

void SetVertex0(SVECTOR* vector) { gte_ldv0(vector); }

void SetVertex1(SVECTOR* vector) { gte_ldv1(vector); }

void SetVertex2(SVECTOR* vector) { gte_ldv2(vector); }

void SetVertexTri(SVECTOR* vector1, SVECTOR* vector2, SVECTOR* vector3) {
    gte_ldv3(vector1, vector2, vector3);
}

void SetRGBfifo(u_char r, u_char g, u_char b) { gte_SetRGBfifo(r, g, b); }

void SetIR123(u32 arg0, u32 arg1, u32 arg3) { gte_SetIR123(arg0, arg1, arg3); }

void SetIR0(u32 arg0) { gte_lddp(arg0); }

void SetSZfifo3(u32 arg0, u32 arg1, u32 arg3) { gte_ldsz3(arg0, arg1, arg3); }

void SetSZfifo4(u32 arg0, u32 arg1, u32 arg3, u32 arg4) {
    gte_ldsz4(arg0, arg1, arg3, arg4);
}

void SetSXSYfifo(u32 arg0, u32 arg1, u32 arg3) { gte_ldsxy3(arg0, arg1, arg3); }

void SetRii(u32 arg0, u32 arg1, u32 arg3) { gte_SetRii(arg0, arg1, arg3); }

void SetMAC123(u32 arg0, u32 arg1, u32 arg3) {
    gte_SetMAC123(arg0, arg1, arg3);
}

void SetData32(void) { __asm__("mtc2 $a0, $30"); }

void SetDQA(void) { __asm__("ctc2 $a0, $27"); }

void SetDQB(void) { __asm__("ctc2 $a0, $28"); }
