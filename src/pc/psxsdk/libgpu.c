#include <common.h>
#include <psxsdk/libgpu.h>
#include <stdarg.h>
#include <stdio.h>
#include <log.h>

int (*GPU_printf)(const char*, ...) = FntPrint;

int FntOpen(int x, int y, int w, int h, int isbg, int n) { NOT_IMPLEMENTED; }

void FntLoad(int tx, int ty) { NOT_IMPLEMENTED; }

int MyFntPrint(const char* fmt, va_list arg);
int FntPrint(const char* fmt, ...) {
    int n;
    va_list args;
    va_start(args, fmt);
    n = MyFntPrint(fmt, args);
    va_end(args);
    return n;
}

u_long* MyFntFlush(int id);
u_long* FntFlush(int id) { return MyFntFlush(id); }

void SetDumpFnt(int id) { NOT_IMPLEMENTED; }

void SetDispMask(int mask) { NOT_IMPLEMENTED; }

int MyClearImage(RECT* rect, u_char r, u_char g, u_char b);
int ClearImage(RECT* rect, u_char r, u_char g, u_char b) {
    return MyClearImage(rect, r, g, b);
}

int MyLoadImage(RECT* rect, u_long* p);
int LoadImage(RECT* rect, u_long* p) { return MyLoadImage(rect, p); }

int MyStoreImage(RECT* rect, u_long* p);
int StoreImage(RECT* rect, u_long* p) { return MyStoreImage(rect, p); }

int MoveImage(RECT* rect, int x, int y) { NOT_IMPLEMENTED; }

int MyDrawSync(int mode);
int DrawSync(int mode) { return MyDrawSync(mode); }

DRAWENV* PutDrawEnv(DRAWENV* env) { NOT_IMPLEMENTED; }

DISPENV* MyPutDispEnv(DISPENV* env);
DISPENV* PutDispEnv(DISPENV* env) { MyPutDispEnv(env); }

void DrawOTag(u_long* p) { NOT_IMPLEMENTED; }

void MySetDrawMode(DR_MODE* p, int dfe, int dtd, int tpage, RECT* tw);
void SetDrawMode(DR_MODE* p, int dfe, int dtd, int tpage, RECT* tw) {
    MySetDrawMode(p, dfe, dtd, tpage, tw);
}

int MyResetGraph(int mode);
int ResetGraph(int mode) { return MyResetGraph(mode); }

int SetGraphDebug(int level) { NOT_IMPLEMENTED; }

u_long* ClearOTag(u_long* ot, int n) { NOT_IMPLEMENTED; }

void SetDrawEnv(DR_ENV* dr_env, DRAWENV* env) { NOT_IMPLEMENTED; }

int GetGraphType(void) {
    // always 0 in SOTN
    return 0;
}
