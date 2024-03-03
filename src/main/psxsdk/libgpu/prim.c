#include "common.h"
#include <psxsdk/libgpu.h>

extern void (*GPU_printf)(const char* fmt, ...);

u_short GetTPage(int tp, int abr, int x, int y) {
    return GetGraphType() ? (tp & 3) << 9 | (abr & 3) << 7 | (y & 0x300) >> 3 |
                                (x & 0x3FF) >> 6
                          : (tp & 3) << 7 | (abr & 3) << 5 | (y & 0x100) >> 4 |
                                (x & 0x3FF) >> 6;
}

u16 GetClut(s32 x, s32 y) { return getClut(x, y); }

void DumpTPage(u_short tpage) {
    if (GetGraphType()) {
        GPU_printf("tpage: (%d,%d,%d,%d)\n", (tpage >> 9) & 3, (tpage >> 7) & 3,
                   (tpage << 6) & 0x7C0, (tpage * 8) & 0x300);
    } else {
        GPU_printf("tpage: (%d,%d,%d,%d)\n", (tpage >> 7) & 3, (tpage >> 5) & 3,
                   (tpage << 6) & 0x7C0, (tpage * 0x10) & 0x100);
    }
}

void DumpClut(u_short clut) {
    GPU_printf("clut: (%d,%d)\n", (clut & 0x3F) * 0x10, clut >> 6);
}

void* NextPrim(void* p) { return nextPrim(p); }

int IsEndPrim(void* p) { return isendprim(p); }

void AddPrim(void* ot, void* p) { addPrim(ot, p); }

void AddPrims(void* ot, void* p0, void* p1) { addPrims(ot, p0, p1); }

void CatPrim(void* p0, void* p1) { catPrim(p0, p1); }

void TermPrim(void* p) { return termPrim(p); }

void SetSemiTrans(void* p, int abe) { return setSemiTrans(p, abe); }

void SetShadeTex(void* p, int tge) { return setShadeTex(p, tge); }

void SetPolyF3(POLY_F3* p) { setPolyF3(p); }
void SetPolyFT3(POLY_FT3* p) { setPolyFT3(p); }
void SetPolyG3(POLY_G3* p) { setPolyG3(p); }
void SetPolyGT3(POLY_GT3* p) { setPolyGT3(p); }
void SetPolyF4(POLY_F4* p) { setPolyF4(p); }
void SetPolyFT4(POLY_FT4* p) { setPolyFT4(p); }
void SetPolyG4(POLY_G4* p) { setPolyG4(p); }
void SetPolyGT4(POLY_GT4* p) { setPolyGT4(p); }
void SetSprt8(SPRT_8* p) { setSprt8(p); }
void SetSprt16(SPRT_16* p) { setSprt16(p); }
void SetSprt(SPRT* p) { setSprt(p); }
void SetTile1(TILE_1* p) { setTile1(p); }
void SetTile8(TILE_8* p) { setTile8(p); }
void SetTile16(TILE_16* p) { setTile16(p); }
void SetTile(TILE* p) { setTile(p); }
void SetBlockFill(BLK_FILL* p) { setBlockFill(p); }
void SetLineF2(LINE_F2* p) { setLineF2(p); }
void SetLineG2(LINE_G2* p) { setLineG2(p); }
void SetLineF3(LINE_F3* p) { setLineF3(p); }
void SetLineG3(LINE_G3* p) { setLineG3(p); }
void SetLineF4(LINE_F4* p) { setLineF4(p); }
void SetLineG4(LINE_G4* p) { setLineG4(p); }

int MargePrim(void* p1, void* p2) {
    int length = getlen(p1) + getlen(p2) + 1;
    if (length >= 0x21) {
        return -1;
    }
    setlen(p1, length);
    // Bug: this should also do *(u_long*)p2 = 0; so the link pointer of
    // prim2 isn't treated as a GPU command. Fixed in newer PSY-Q.
    return 0;
}

void DumpDrawEnv(DRAWENV* env) {
    GPU_printf("clip (%3d,%3d)-(%d,%d)\n", env->clip.x, env->clip.y,
               env->clip.w, env->clip.h);
    GPU_printf("ofs  (%3d,%3d)\n", env->ofs[0], env->ofs[1]);
    GPU_printf(
        "tw   (%d,%d)-(%d,%d)\n", env->tw.x, env->tw.y, env->tw.w, env->tw.h);
    GPU_printf("dtd   %d\n", env->dtd);
    GPU_printf("dfe   %d\n", env->dfe);
    if (GetGraphType()) {
        GPU_printf("tpage: (%d,%d,%d,%d)\n", (env->tpage >> 9) & 3,
                   (env->tpage >> 7) & 3, (env->tpage << 6) & 0x7C0,
                   (env->tpage * 8) & 0x300);
    } else {
        GPU_printf("tpage: (%d,%d,%d,%d)\n", (env->tpage >> 7) & 3,
                   (env->tpage >> 5) & 3, (env->tpage << 6) & 0x7C0,
                   (env->tpage * 0x10) & 0x100);
    }
}

void DumpDispEnv(DISPENV* env) {
    GPU_printf("disp   (%3d,%3d)-(%d,%d)\n", env->disp.x, env->disp.y,
               env->disp.w, (s32)env->disp.h);
    GPU_printf("screen (%3d,%3d)-(%d,%d)\n", env->screen.x, env->screen.y,
               env->screen.w, (s32)env->screen.h);
    GPU_printf("isinter %d\n", env->isinter);
    GPU_printf("isrgb24 %d\n", env->isrgb24);
}
