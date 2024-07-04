#include "common.h"
#include <psxsdk/libgpu.h>

typedef struct {
    /* 0x00 */ u32 unk00;                       // aIdSysCV1831995
    /* 0x04 */ void (*addque)();                // _addque
    /* 0x08 */ int (*addque2)();                // _addque2
    /* 0x0C */ u32 clr;                         // _clr
    /* 0x10 */ void (*ctl)(int);                // _ctl
    /* 0x14 */ s32 (*cwb)(s32* arg0, s32 arg1); // _cwb
    /* 0x18 */ u32 cwc;                         // _cwc
    /* 0x1C */ u32 drs;                         // _drs
    /* 0x20 */ u32 dws;                         // _dws
    /* 0x24 */ u32 unk24;                       // _exeque
    /* 0x28 */ int (*getctl)(int);              // _getctl
    /* 0x2C */ void (*otc)(u32* ot, s32 n);     // _otc
    /* 0x30 */ u32 unk30;                       // _param
    /* 0x34 */ void (*reset)(int);              // _reset
    /* 0x38 */ u_long (*status)(void);          // _status
    /* 0x3C */ void (*sync)(int);               // _sync
} gpu;                                          // size = 0x40

const char aIdSysCV1831995[] =
    "$Id: sys.c,v 1.83 1995/05/25 13:43:27 suzu Exp $";

extern const char D_800101FC[]; // "ResetGraph(%d)...\n"
extern const char D_80010360[]; // "PutDispEnv(%08x)...\n"
extern const char D_80010378[]; // "GPU_exeque: null func.\n"
extern const char
    D_80010390[]; // "GPU timeout:que=%d,stat=%08x,chcr=%08x,madr=%08x\n"

extern gpu* D_8002C260;
extern int D_8002C268; // log level
extern int D_8002C26C; // graph type
extern int D_8002C270; // reverse
extern int D_8002C274; // graph queue mode
extern void (*D_8002C278)();
extern void (*GPU_printf)(const char* fmt, ...);
extern DRAWENV D_80037E60;
extern DISPENV D_80037EBC;

u_long get_ce(short, short);
u_long get_cs(short, short);
u_long get_tw(RECT* tw);
u_long get_ofs(short, short);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", ResetGraph);

int SetGraphReverse(int mode) {
    unsigned int var_a0;
    s32 temp_a0;
    s32 var_v0;
    int old = D_8002C270;

    if (D_8002C268 >= 2) {
        GPU_printf("SetGraphReverse(%d)...\n", mode);
    }

    D_8002C270 = mode;
    D_8002C260->ctl(
        D_8002C260->getctl(8) | (D_8002C270 ? 0x08000080 : 0x08000000));
    if (D_8002C26C == 2) {
        D_8002C260->ctl(D_8002C270 ? 0x20000501 : 0x20000504);
    }
    return old;
}

int SetGraphDebug(int level) {
    int old = D_8002C268;

    D_8002C268 = level;
    if (level) {
        GPU_printf("SetGraphDebug:level:%d,type:%d reverse:%d\n", level,
                   D_8002C26C, D_8002C270);
    }

    return old;
}

int SetGraphQueue(int mode) {
    int old = D_8002C274;

    if (D_8002C268 >= 2) {
        GPU_printf("SetGraphQueue(%d)...\n", mode);
    }
    if (mode != D_8002C274) {
        D_8002C260->reset(1);
        D_8002C274 = mode;
    }

    return old;
}

int GetGraphType(void) { return D_8002C26C; }

int GetGraphDebug(void) { return D_8002C268; }

u_long DrawSyncCallback(void (*func)()) {
    void (*old)();

    if (D_8002C268 >= 2) {
        GPU_printf("DrawSyncCallback(%08x)...\n", func);
    }
    old = D_8002C278;
    D_8002C278 = func;
    return old;
}

void SetDispMask(int mask) {
    if (D_8002C268 >= 2) {
        GPU_printf("SetDispMask(%d)...\n", mask);
    }
    D_8002C260->ctl(mask ? 0x03000000 : 0x03000001);
}

s32 DrawSync(s32 mode) {
    if (D_8002C268 >= 2) {
        GPU_printf("DrawSync(%d)...\n", mode);
    }
    D_8002C260->sync(mode);
}

void checkRECT(const char* log, RECT* r) {
    switch (D_8002C268) {
    case 1:
        if (r->w > 0x400 || r->w + r->x > 0x400 || r->y > 0x400 ||
            r->y + r->h > 0x400 || r->w <= 0 || r->x < 0 || r->y < 0 ||
            r->h <= 0) {
            GPU_printf("%s:bad RECT", log);
            GPU_printf("(%d,%d)-(%d,%d)\n", r->x, r->y, r->w, r->h);
        }
        break;
    case 2:
        GPU_printf("%s:", log);
        GPU_printf("(%d,%d)-(%d,%d)\n", r->x, r->y, r->w, r->h);
        break;
    }
}

int ClearImage(RECT* rect, u8 r, u8 g, u8 b) {
    checkRECT("ClearImage", rect);
    return D_8002C260->addque2(
        D_8002C260->clr, rect, sizeof(RECT), (b << 0x10) | (g << 8) | r);
}

int LoadImage(RECT* rect, u_long* p) {
    checkRECT("LoadImage", rect);
    return D_8002C260->addque2(D_8002C260->dws, rect, sizeof(RECT), p);
}

int StoreImage(RECT* rect, u_long* p) {
    checkRECT("StoreImage", rect);
    return D_8002C260->addque2(D_8002C260->drs, rect, sizeof(RECT), p);
}

int MoveImage(RECT* rect, int x, int y) {
    u32 param[5];

    checkRECT("MoveImage", rect);
    param[0] = 0x04FFFFFF;
    param[1] = 0x80000000;
    param[2] = LOW(rect->x);
    param[3] = (u16)y << 0x10 | (u16)x;
    param[4] = LOW(rect->w);
    return D_8002C260->addque2(D_8002C260->cwc, param, sizeof(param), 0);
}

OT_TYPE* ClearOTag(OT_TYPE* ot, int n) {
    if (D_8002C268 >= 2) {
        GPU_printf("ClearOTag(%08x,%d)...\n", ot, n);
    }

    n--;
    while (n) {
        setlen(ot, 0);
        setaddr(ot, ot + 1);
        n--;
        ot++;
    }

    *ot = 0xFFFFFF;
    return ot;
}

OT_TYPE* ClearOTagR(OT_TYPE* ot, int n) {
    if (D_8002C268 >= 2) {
        GPU_printf("ClearOTagR(%08x,%d)...\n", ot, n);
    }

    D_8002C260->otc(ot, n);
    return ot;
}

struct Temp {
    s16 unk0;
    u8 unk2;
    u8 unk3;
};

void func_80012DBC(struct Temp* arg0) {
    u8 temp_s1;

    temp_s1 = arg0->unk3;
    D_8002C260->sync(0);
    D_8002C260->cwb((u8*)(arg0) + 4, temp_s1);
}

void DrawOTag(OT_TYPE* p) {
    if (D_8002C268 >= 2) {
        GPU_printf("DrawOTag(%08x)...\n", p);
    }
    D_8002C260->addque(D_8002C260->cwc, p, 0);
}

DRAWENV* PutDrawEnv(DRAWENV* env) {
    if (D_8002C268 >= 2) {
        GPU_printf("PutDrawEnv(%08x)...\n", env);
    }

    SetDrawEnv(&env->dr_env, env);
    env->dr_env.tag |= 0xFFFFFF;
    D_8002C260->addque2(D_8002C260->cwc, &env->dr_env, sizeof(DR_ENV), 0);
    D_80037E60 = *env;

    return env;
}

DRAWENV* GetDrawEnv(DRAWENV* env) {
    *env = D_80037E60;
    return env;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", PutDispEnv);

DISPENV* GetDispEnv(DISPENV* env) {
    *env = D_80037EBC;
    return env;
}

u_long GetODE(void) { return D_8002C260->status() >> 0x1F; }

void SetTexWindow(DR_TWIN* p, RECT* tw) {
    setlen(p, 2);
    p->code[0] = get_tw(tw);
    p->code[1] = 0;
}

void SetDrawArea(DR_AREA* p, RECT* r) {
    setlen(p, 2);
    p->code[0] = get_cs(r->x, r->y);
    p->code[1] = get_ce(r->x + r->w - 1, r->y + r->h - 1);
}

void SetDrawOffset(DR_OFFSET* p, u_short* ofs) {
    setlen(p, 2);
    p->code[0] = get_ofs(ofs[0], ofs[1]);
    p->code[1] = 0;
}

void SetPriority(DR_PRIO* p, s32 pbc, s32 pbw) {
    s32 var_v1;

    *(((u8*)&p->tag) + 3) = 2;
    var_v1 = 0xE6000000;
    if (pbc != 0) {
        var_v1 = 0xE6000002;
    }
    p->code[0] = var_v1 | (pbw != 0);
    p->code[1] = 0;
}

extern void SetDrawMode(DR_MODE* p, int dfe, int dtd, int tpage, RECT* tw) {
    setlen(p, 2);
    p->code[0] = get_mode(dfe, dtd, (u_short)tpage);
    p->code[1] = get_tw(tw);
}

extern void SetDrawEnv(DR_ENV* dr_env, DRAWENV* env);
INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", SetDrawEnv);

int get_mode(int dfe, int dtd, int tpage) {
    if (D_8002C26C) {
        return (dtd ? 0xE1000800 : 0xE1000000) | (dfe ? 0x1000 : 0) |
               (tpage & 0x27FF);
    } else {
        return (dtd ? 0xE1000200 : 0xE1000000) | (dfe ? 0x400 : 0) |
               (tpage & 0x1FF);
    }
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", get_cs);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", get_ce);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", get_ofs);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", get_tw);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", get_dx);

extern s32* D_8002C280;

s32 _status(void) { return *D_8002C280; }

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _otc);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _clr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _dws);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _drs);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _ctl);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _getctl);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _cwb);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _cwc);

extern s32* D_8002C27C;

s32 _param(s32 arg0) {
    *D_8002C280 = arg0 | 0x10000000;
    return *D_8002C27C & 0xFFFFFF;
}

void _addque2(s32, s32, s32, s32);

void _addque(s32 arg0, s32 arg1, s32 arg2) { _addque2(arg0, arg1, 0, arg2); }

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _addque2);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _exeque);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _reset);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _sync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", set_alarm);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", get_alarm);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", GPU_memset);
