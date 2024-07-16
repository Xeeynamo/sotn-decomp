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

int MyMoveImage(RECT* rect, int x, int y);
int MoveImage(RECT* rect, int x, int y) { return MyMoveImage(rect, x, y); }

int MyDrawSync(int mode);
int DrawSync(int mode) { return MyDrawSync(mode); }

DRAWENV* MyPutDrawEnv(DRAWENV* env);
DRAWENV* PutDrawEnv(DRAWENV* env) { return MyPutDrawEnv(env); }

DISPENV* MyPutDispEnv(DISPENV* env);
DISPENV* PutDispEnv(DISPENV* env) { MyPutDispEnv(env); }

void MyDrawOTag(OT_TYPE* p);
void DrawOTag(OT_TYPE* p) { MyDrawOTag(p); }

u32 get_tw_(RECT* arg0) {
    u32 pad[4];

    if (arg0 != 0) {
        pad[0] = (u8)arg0->x >> 3;
        pad[2] = (s32)(-arg0->w & 0xFF) >> 3;
        pad[1] = (u8)arg0->y >> 3;
        pad[3] = (s32)(-arg0->h & 0xFF) >> 3;
        return (pad[1] << 0xF) | 0xE2000000 | (pad[0] << 0xA) | (pad[3] << 5) |
               pad[2];
    }
    return 0;
}

void SetDrawMode(DR_MODE* p, int dfe, int dtd, int tpage, RECT* tw) {
    setlen(p, 2);
    p->code[0] =
        (dtd ? 0xE1000200 : 0xE1000000) | (dfe ? 0x400 : 0) | (tpage & 0x1FF);
    p->code[1] = get_tw_(tw);
}

int MyResetGraph(int mode);
int ResetGraph(int mode) { return MyResetGraph(mode); }

int SetGraphDebug(int level) { NOT_IMPLEMENTED; }

OT_TYPE* ClearOTag(OT_TYPE* ot, int n) {
    n--;
    while (n) {
        setlen(ot, 0);
        setaddr(ot, ot + 1);
        n--;
        ot++;
    }

    ot->tag = 0xffffff;
    return ot;
}

void MySetDrawEnv(DR_ENV* dr_env, DRAWENV* env);

void SetDrawEnv(DR_ENV* dr_env, DRAWENV* env) { MySetDrawEnv(dr_env, env); }

int GetGraphType(void) {
    // always 0 in SOTN
    return 0;
}
