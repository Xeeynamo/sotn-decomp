#include <common.h>
#include <psxsdk/libgpu.h>
#include <stdarg.h>
#include <stdio.h>
#include <log.h>

int FntOpen(int x, int y, int w, int h, int isbg, int n) {
    DEBUGF("not implemented");
}

void FntLoad(int tx, int ty) { DEBUGF("not implemented"); }

int FntPrint(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buf[256];
    vsnprintf(buf, sizeof(buf), fmt, args);
    INFOF(buf);

    va_end(args);
}

u_long* FntFlush(int) { fflush(stderr); }

void SetDumpFnt(int id) { DEBUGF("not implemented"); }

void SetDispMask(int mask) { DEBUGF("not implemented"); }

DISPENV* SetDefDispEnv(DISPENV* env, int x, int y, int w, int h) {
    DEBUGF("not implemented");
}
DRAWENV* SetDefDrawEnv(DRAWENV* env, int x, int y, int w, int h) {
    DEBUGF("not implemented");
}

int ClearImage(RECT* rect, u_char r, u_char g, u_char b) {
    DEBUGF("not implemented");
}
int LoadImage(RECT* rect, u_long* p) { DEBUGF("not implemented"); }
int StoreImage(RECT* rect, u_long* p) { DEBUGF("not implemented"); }

int DrawSync(int mode) { DEBUGF("not implemented"); }

DRAWENV* PutDrawEnv(DRAWENV* env) { DEBUGF("not implemented"); }

DISPENV* PutDispEnv(DISPENV* env) { DEBUGF("not implemented"); }

void DrawOTag(u_long* p) { DEBUGF("not implemented"); }

void AddPrim(void* ot, void* p) { DEBUGF("not implemented"); }

void SetShadeTex(void* p, int tge) { DEBUGF("not implemented"); }

void SetSemiTrans(void* p, int abe) { DEBUGF("not implemented"); }

void SetDrawMode(DR_MODE* p, int dfe, int dtd, int tpage, RECT* tw) {
    DEBUGF("not implemented");
}

int ResetGraph(int mode) { DEBUGF("not implemented"); }

int SetGraphDebug(int level) { DEBUGF("not implemented"); }

u_long* ClearOTag(u_long* ot, int n) { DEBUGF("not implemented"); }
