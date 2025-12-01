// SPDX-License-Identifier: MIT
//! PSYQ=3.3
#include "common.h"
#include <psxsdk/libgpu.h>

typedef struct {
    /* 0x00 */ const char* rcsid; // aIdSysCV1831995
    /* 0x04 */ void (*addque)(void (*)(int*, int), int*, int);      // _addque
    /* 0x08 */ int (*addque2)(void (*)(int*, int), int*, int, int); // _addque2
    /* 0x0C */ int (*clr)(RECT*, int);                              // _clr
    /* 0x10 */ void (*ctl)(u_long);                                 // _ctl
    /* 0x14 */ int (*cwb)(int*, int);                               // _cwb
    /* 0x18 */ void (*cwc)(int);                                    // _cwc
    /* 0x1C */ int (*drs)(RECT*, int*);                             // _drs
    /* 0x20 */ int (*dws)(RECT*, int*);                             // _dws
    /* 0x24 */ int (*exeque)(void);                                 // _exeque
    /* 0x28 */ int (*getctl)(int);                                  // _getctl
    /* 0x2C */ int (*otc)(int, int);                                // _otc
    /* 0x30 */ int (*param)(int);                                   // _param
    /* 0x34 */ int (*reset)(int);                                   // _reset
    /* 0x38 */ u_long (*status)(void);                              // _status
    /* 0x3C */ int (*sync)(int);                                    // _sync
} gpu; // size = 0x40

struct QueueItem {
    void (*unk0)(int*, int);
    int* unk4;
    int unk8;
    int unk[0x10];
};

void _addque(void (*)(int*, int), int*, int);
int _addque2(void (*)(int*, int), int*, int, int);
int _clr(RECT*, int);
void _ctl(u_long);
int _cwb(int*, int);
void _cwc(int);
int _drs(RECT*, int*);
int _dws(RECT*, int*);
int _exeque(void);
int _getctl(int);
int _otc(int, int);
int _param(int);
int _reset(int);
u_long _status(void);
int _sync(int);

int printf(char*, ...);
u_long get_ce(short, short);
u_long get_cs(short, short);
u_long get_tw(RECT* tw);
u_long get_ofs(short, short);

static int D_80037E20[0x10];
static DRAWENV D_80037E60;
static DISPENV D_80037EBC;
static int ctlbuf[0x21];
static volatile struct QueueItem D_80037F54[0x40];
static int D_80039254;
static int D_80039258;

static gpu D_8002C220 = {
    .rcsid = "$Id: sys.c,v 1.83 1995/05/25 13:43:27 suzu Exp $",
    .addque = _addque,
    .addque2 = _addque2,
    .clr = _clr,
    .ctl = _ctl,
    .cwb = _cwb,
    .cwc = _cwc,
    .drs = _drs,
    .dws = _dws,
    .exeque = _exeque,
    .getctl = _getctl,
    .otc = _otc,
    .param = _param,
    .reset = _reset,
    .status = _status,
    .sync = _sync,
};
static gpu* D_8002C260 = &D_8002C220;
void (*GPU_printf)(const char* fmt, ...) = printf;
static int D_8002C268 = 0; // log level
static int D_8002C26C = 0; // graph type
static int D_8002C270 = 0; // reverse
static int D_8002C274 = 1; // graph queue mode
static void (*D_8002C278)() = NULL;
static volatile int* GPU_DATA = (int*)0x1F801810;
static volatile u_long* GPU_STATUS = (u_long*)0x1F801814;
static volatile int* DMA2_MADR = (int*)0x1F8010A0;
static volatile int* DMA2_BCR = (int*)0x1F8010A4;
static volatile int* DMA2_CHCR = (int*)0x1F8010A8;
static volatile int* DMA6_MADR = (int*)0x1F8010E0;
static volatile int* DMA6_BCR = (int*)0x1F8010E4;
static volatile int* DMA6_CHCR = (int*)0x1F8010E8;
static volatile int* DPCR = (int*)0x1F8010F0;
static volatile int _qin = 0;
static volatile int _qout = 0;

#ifndef CLAMP
#define CLAMP(value, low, high)                                                \
    value < low ? low : (value > high ? high : value)
#endif

// gpu commands
#define CMD_CLEAR_CACHE 0x01000000
#define CMD_FILL_RECTANGLE_IN_VRAM(color) ((color & 0xFFFFFF) | 0x02000000)
#define CMD_MONOCHROME_RECTANGLE(color) ((color & 0xFFFFFF) | 0x60000000)
#define CMD_COPY_VRAM_TO_CPU 0xC0000000
#define CMD_COPY_CPU_TO_VRAM 0xA0000000

// status reg bits
#define STATUS_READY_TO_RECEIVE_CMD (1 << 26)
#define STATUS_READY_TO_SEND_VRAM_TO_CPU (1 << 27)

int ResetGraph(int mode) {
    if (D_8002C268 >= 2) {
        GPU_printf("ResetGraph(%d)...\n", mode);
    }
    switch (mode & 3) {
    case 0:
        ResetCallback();
        D_8002C26C = D_8002C260->reset(0);
        GPU_cw((int)D_8002C260 & 0xFFFFFF);
        break;
    case 1:
    case 2:
    case 3:
        D_8002C26C = D_8002C260->reset(1);
        break;
    default:
        return -1;
    }

    memset2(&D_80037E60, -1, sizeof(DRAWENV));
    memset2(&D_80037EBC, -1, sizeof(DISPENV));
    if (D_8002C26C != 0) {
        D_8002C260->ctl(
            D_8002C260->getctl(8) | (D_8002C270 ? 0x08000080 : 0x08000000));
        if (mode & 8) {
            D_8002C26C = 2;
            D_8002C260->ctl(D_8002C270 ? 0x20000501 : 0x20000504);
        }
    }
}

int SetGraphReverse(int mode) {
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

int DrawSync(int mode) {
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
    u_long param[5];

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

    while (--n) {
        setlen(ot, 0);
        setaddr(ot, ot + 1);
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

void DrawPrim(void* p) {
    int len = getlen(p);
    D_8002C260->sync(0);
    D_8002C260->cwb((u_long*)&((P_TAG*)p)->r0, len);
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

DISPENV* PutDispEnv(DISPENV* env) {
    int h_start;
    int v_start;
    int mode;
    int v_end;
    int h_end;

    mode = 0x08000000;
    if (D_8002C268 >= 2) {
        GPU_printf("PutDispEnv(%08x)...\n", env);
    }
    D_8002C260->ctl((D_8002C26C != 0) ? ((env->disp.y & 0xFFF) << 0xC) |
                                            (get_dx(env) & 0xFFF) | 0x05000000
                                      : ((env->disp.y & 0x1FF) << 0xA) |
                                            (env->disp.x & 0x3FF) | 0x05000000);
    if (!(LOW(D_80037EBC.screen.x) == LOW(env->screen.x) &&
          LOW(D_80037EBC.screen.w) == LOW(env->screen.w))) {
        env->pad0 = GetVideoMode();
        h_start = env->screen.x * 0xA + 0x260;
        v_start = env->screen.y + 0x10;
        h_end = h_start + (env->screen.w ? env->screen.w * 0xA : 0xA00);
        v_end = v_start + (env->screen.h ? env->screen.h : 0xF0);
        h_start = CLAMP(h_start, 0x1F4, 0xCDA);
        h_end = CLAMP(h_end, h_start + 0x50, 0xCDA);
        v_start = CLAMP(v_start, 0, (env->pad0 ? 0x136 : 0xFE));
        v_end = CLAMP(v_end, v_start + 1, (env->pad0 ? 0x138 : 0x100));
        D_8002C260->ctl(
            ((h_end & 0xFFF) << 0xC) | 0x06000000 | (h_start & 0xFFF));
        D_8002C260->ctl(
            ((v_end & 0x3FF) << 0xA) | 0x07000000 | (v_start & 0x3FF));
    }
    if (LOW(D_80037EBC.isinter) != LOW(env->isinter) ||
        !(LOW(D_80037EBC.disp.x) == LOW(env->disp.x) &&
          LOW(D_80037EBC.disp.w) == LOW(env->disp.w))) {
        env->pad0 = GetVideoMode();
        if (env->pad0 == 1) {
            mode |= 0x8;
        }
        if (env->isrgb24) {
            mode |= 0x10;
        }
        if (env->isinter) {
            mode |= 0x20;
        }
        if (D_8002C270 != 0) {
            mode |= 0x80;
        }
        if (env->disp.w > 0x118) {
            if (env->disp.w <= 0x160) {
                mode |= 1;
            } else if (env->disp.w <= 0x190) {
                mode |= 0x40;
            } else if (env->disp.w <= 0x230) {
                mode |= 2;
            } else {
                mode |= 3;
            }
        }
        if (env->disp.h <= (env->pad0 ? 0x120 : 0x100)) {
        } else {
            mode |= 0x24;
        }
        D_8002C260->ctl(mode);
    }
    memcpy((u8*)&D_80037EBC, (u8*)env, sizeof(DISPENV));
    return env;
}

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

void SetPriority(DR_PRIO* p, int pbc, int pbw) {
    setlen(p, 2);
    p->code[0] = (pbc ? 0xE6000002 : 0xE6000000) | (pbw ? 1 : 0);
    p->code[1] = 0;
}

void SetDrawMode(DR_MODE* p, int dfe, int dtd, int tpage, RECT* tw) {
    setlen(p, 2);
    p->code[0] = get_mode(dfe, dtd, (u_short)tpage);
    p->code[1] = get_tw(tw);
}

void SetDrawEnv(DR_ENV* dr_env_in, DRAWENV* env) {
    RECT clip_rect;
    int offset;
    DR_ENV* dr_env;

    dr_env = dr_env_in;

    dr_env->code[0] = get_cs(env->clip.x, env->clip.y);
    dr_env->code[1] =
        get_ce(env->clip.w + env->clip.x - 1, env->clip.y + env->clip.h - 1);
    dr_env->code[2] = get_ofs(env->ofs[0], env->ofs[1]);
    dr_env->code[3] = get_mode(env->dfe, env->dtd, env->tpage);
    dr_env->code[4] = get_tw(&env->tw);
    dr_env->code[5] = 0xE6000000;

    offset = 7;
    if (env->isbg != 0) {
        clip_rect.x = env->clip.x;
        clip_rect.y = env->clip.y;
        clip_rect.w = env->clip.w;
        clip_rect.h = env->clip.h;
        clip_rect.w = CLAMP(clip_rect.w, 0, 1023);
        clip_rect.h = CLAMP(clip_rect.h, 0, (D_8002C26C ? 1024 : 512) - 1);

        if ((clip_rect.x & 0x3F) || (clip_rect.w & 0x3F)) {
            clip_rect.x -= env->ofs[0];
            clip_rect.y -= env->ofs[1];
            *((int*)dr_env + offset++) =
                0x60000000 | env->b0 << 0x10 | env->g0 << 8 | env->r0;
            *((int*)dr_env + offset++) = LOW(clip_rect.x);
            *((int*)dr_env + offset++) = LOW(clip_rect.w);
            clip_rect.x += env->ofs[0];
            clip_rect.y += env->ofs[1];
        } else {
            *((int*)dr_env + offset++) =
                0x02000000 | env->b0 << 0x10 | env->g0 << 8 | env->r0;
            *((int*)dr_env + offset++) = LOW(clip_rect.x);
            *((int*)dr_env + offset++) = LOW(clip_rect.w);
        }
    }

    setlen(dr_env, offset - 1);
}

int get_mode(int dfe, int dtd, int tpage) {
    if (D_8002C26C) {
        return (dtd ? 0xE1000800 : 0xE1000000) | (dfe ? 0x1000 : 0) |
               (tpage & 0x27FF);
    } else {
        return (dtd ? 0xE1000200 : 0xE1000000) | (dfe ? 0x400 : 0) |
               (tpage & 0x1FF);
    }
}

u_long get_cs(short x, short y) {
    x = CLAMP(x, 0, 0x400 - 1);
    y = CLAMP(y, 0, (D_8002C26C ? 0x400 : 0x200) - 1);
    if (D_8002C26C) {
        return 0xE3000000 | ((y & 0xFFF) << 12) | (x & 0xFFF);
    } else {
        return 0xE3000000 | ((y & 0x3FF) << 10) | (x & 0x3FF);
    }
}

u_long get_ce(short x, short y) {
    x = CLAMP(x, 0, 0x400 - 1);
    y = CLAMP(y, 0, (D_8002C26C ? 0x400 : 0x200) - 1);
    if (D_8002C26C) {
        return 0xE4000000 | ((y & 0xFFF) << 12) | (x & 0xFFF);
    } else {
        return 0xE4000000 | ((y & 0x1FF) << 10) | (x & 0x3FF);
    }
}

u_long get_ofs(short x, short y) {
    if (D_8002C26C) {
        return 0xE5000000 | ((y & 0xFFF) << 12) | (x & 0xFFF);
    } else {
        return 0xE5000000 | ((y & 0x7FF) << 11) | (x & 0x7FF);
    }
}

u_long get_tw(RECT* arg0) {
    u_long pad[4];

    if (arg0 != 0) {
        pad[0] = (u8)arg0->x >> 3;
        pad[2] = (int)(-arg0->w & 0xFF) >> 3;
        pad[1] = (u8)arg0->y >> 3;
        pad[3] = (int)(-arg0->h & 0xFF) >> 3;
        return (pad[1] << 0xF) | 0xE2000000 | (pad[0] << 0xA) | (pad[3] << 5) |
               pad[2];
    }
    return 0;
}

u_long get_dx(DISPENV* env) {
    switch (D_8002C26C) {
    case 0:
        return env->disp.x;
    case 1:
        return D_8002C270 ? 0x400 - env->disp.x - env->disp.w : env->disp.x;
    case 2:
        return D_8002C270 ? 0x400 - env->disp.x - (env->disp.w / 2)
                          : env->disp.x / 2;
    }
}

u_long _status(void) { return *GPU_STATUS; }

int _otc(int arg0, int arg1) {
    *DPCR |= 0x08000000;
    *DMA6_CHCR = 0;
    *DMA6_MADR = arg0 - 4 + arg1 * 4;
    *DMA6_BCR = arg1;
    *DMA6_CHCR = 0x11000002;
    set_alarm();
    while (*DMA6_CHCR & 0x01000000) {
        if (get_alarm()) {
            return -1;
        }
    }
    return arg1;
}

// Clears Frame Buffer
int _clr(RECT* arg0, int color) {
    RECT temp;
    int* ptr;

    temp.x = arg0->x;
    temp.y = arg0->y;
    temp.w = arg0->w;
    temp.h = arg0->h;

    temp.w = CLAMP(temp.w, 0, 1023);
    temp.h = CLAMP(temp.h, 0, (D_8002C26C ? 1024 : 512) - 1);

    if ((temp.x & 0x3F) || (temp.w & 0x3F)) {
        ptr = &D_80037E20[8];
        D_80037E20[0] = ((int)ptr & 0xFFFFFF) | 0x07000000; // set up otag
        D_80037E20[1] = 0xE3000000; // set drawing area top left
        D_80037E20[2] = 0xE4FFFFFF; // set drawing area bottom right
        D_80037E20[3] = 0xE5000000; // set drawing offset
        D_80037E20[4] = 0xE6000000;

        D_80037E20[5] = CMD_MONOCHROME_RECTANGLE(color);
        D_80037E20[6] = LOW(temp.x);
        D_80037E20[7] = LOW(temp.w);
        D_80037E20[8] = 0x03FFFFFF;
        D_80037E20[9] = _param(3) | 0xE3000000; // set drawing area top left
        D_80037E20[10] =
            _param(4) | 0xE4000000; // set drawing area bottom right
        D_80037E20[11] = _param(5) | 0xE5000000; // set drawing offset
    } else {
        D_80037E20[0] = 0x04FFFFFF;
        D_80037E20[1] = 0xE6000000; // mask bit setting

        D_80037E20[2] = CMD_FILL_RECTANGLE_IN_VRAM(color);
        D_80037E20[3] = LOW(temp.x);
        D_80037E20[4] = LOW(temp.w);
    }
    _cwc(&D_80037E20[0]);
    return 0;
}

// LoadImage
int _dws(RECT* arg0, int* arg1) {
    RECT temp;
    int temp_a0;
    int size;
    int var_s0;
    int var_s4;

    set_alarm();
    temp.x = arg0->x;
    temp.y = arg0->y;
    temp.w = arg0->w;
    temp.h = arg0->h;
    var_s4 = 0;

    temp.w = CLAMP(temp.w, 0, 1023);
    temp.h = CLAMP(temp.h, 0, (D_8002C26C ? 1024 : 512) - 1);

    temp_a0 = ((temp.w * temp.h) + 1) / 2;
    if (temp_a0 <= 0) {
        return -1;
    }
    var_s0 = temp_a0 % 16;
    size = temp_a0 / 16;
    while (!(*GPU_STATUS & STATUS_READY_TO_RECEIVE_CMD)) {
        if (get_alarm()) {
            return -1;
        }
    }

    *GPU_STATUS = STATUS_READY_TO_RECEIVE_CMD;

    *GPU_DATA = CMD_CLEAR_CACHE;
    *GPU_DATA = var_s4 ? 0xB0000000 : CMD_COPY_CPU_TO_VRAM;
    *GPU_DATA = LOW(temp.x);
    *GPU_DATA = LOW(temp.w);

    while (var_s0--) {
        *GPU_DATA = *arg1++;
    }

    if (size != 0) {
        *GPU_STATUS = 0x04000002;
        *DMA2_MADR = arg1;
        *DMA2_BCR = (size << 0x10) | 0x10;
        *DMA2_CHCR = 0x01000201;
    }

    return 0;
}

// StoreImage
// Transfers image data from the frame buffer to main memory.
int _drs(RECT* arg0, int* arg1) {
    RECT temp;
    int temp_a0;
    int size;
    int var_s0;

    set_alarm();
    temp.x = arg0->x;
    temp.y = arg0->y;
    temp.w = arg0->w;
    temp.h = arg0->h;

    temp.w = CLAMP(temp.w, 0, 1023);
    temp.h = CLAMP(temp.h, 0, (D_8002C26C ? 1024 : 512) - 1);

    temp_a0 = ((temp.w * temp.h) + 1) / 2;
    if (temp_a0 <= 0) {
        return -1;
    }
    var_s0 = temp_a0 % 16;
    size = temp_a0 / 16;
    while (!(*GPU_STATUS & STATUS_READY_TO_RECEIVE_CMD)) {
        if (get_alarm()) {
            return -1;
        }
    }

    *GPU_STATUS = STATUS_READY_TO_RECEIVE_CMD;

    *GPU_DATA = CMD_CLEAR_CACHE;
    *GPU_DATA = CMD_COPY_VRAM_TO_CPU;
    *GPU_DATA = LOW(temp.x);
    *GPU_DATA = LOW(temp.w);

    while (!(*GPU_STATUS & STATUS_READY_TO_SEND_VRAM_TO_CPU)) {
        if (get_alarm()) {
            return -1;
        }
    }

    while (var_s0--) {
        *arg1++ = *GPU_DATA;
    }

    if (size != 0) {
        *GPU_STATUS = 0x04000003;
        *DMA2_MADR = arg1;
        *DMA2_BCR = (size << 0x10) | 0x10;
        *DMA2_CHCR = 0x01000200;
    }

    return 0;
}

void _ctl(u_long arg0) {
    *GPU_STATUS = arg0;
    ctlbuf[(arg0 >> 0x18)] = arg0 & 0xFFFFFF;
}

int _getctl(int arg0) { return (arg0 << 0x18) | ctlbuf[arg0]; }

int _cwb(int* arg0, int arg1) {
    *GPU_STATUS = 0x04000000;
    while (arg1--) {
        *GPU_DATA = *arg0++;
    }
    return 0;
}

void _cwc(int arg0) {
    *GPU_STATUS = 0x04000002;
    *DMA2_MADR = arg0;
    *DMA2_BCR = 0;
    *DMA2_CHCR = 0x01000401;
}

int _param(int arg0) {
    *GPU_STATUS = arg0 | 0x10000000;
    return *GPU_DATA & 0xFFFFFF;
}

void _addque(void (*arg0)(int*, int), int* arg1, int arg2) {
    _addque2(arg0, arg1, 0, arg2);
}

int _addque2(void (*arg0)(int*, int), int* arg1, int arg2, int arg3) {
    int temp_s0;
    int intrMask;
    int i;
    struct QueueItem* queueItem;

    intrMask = SetIntrMask(0);
    if (D_8002C274 == 0) {
        _sync(0);
        arg0(arg1, arg3);
        SetIntrMask(intrMask);
        return 0;
    }
    if ((_qin == _qout) && !(*DMA2_CHCR & 0x01000000)) {
        if (D_8002C278 != NULL) {
            DMACallback(2, _exeque);
        }
        while (!(*GPU_STATUS & 0x10000000)) {
        }
        arg0(arg1, arg3);
        SetIntrMask(intrMask);
        return 0;
    }
    temp_s0 = (_qin + 1) & 0x3F;
    if (temp_s0 == _qout) {
        set_alarm();
        while (temp_s0 == _qout) {
            if (get_alarm()) {
                SetIntrMask(intrMask);
                return -1;
            }
            _exeque();
        }
    }
    queueItem = &D_80037F54[_qin];
    _qin = temp_s0;
    queueItem->unk0 = NULL;
    if (arg2 != 0) {
        for (i = 0; i < (arg2 / 4); i++) {
            queueItem->unk[i] = arg1[i];
        }
        queueItem->unk4 = queueItem->unk;
    } else {
        queueItem->unk4 = arg1;
    }
    queueItem->unk8 = arg3;
    queueItem->unk0 = arg0;
    _exeque();
    SetIntrMask(intrMask);
    return (_qin - _qout) & 0x3F;
}

int _exeque(void) {
    int intrMask;
    int ret;

    intrMask = SetIntrMask(0);

loop_1:

    if (_qin == _qout) {
        if (D_8002C278 == NULL) {
            DMACallback(2, NULL);
        }
        ret = 0;
        goto temp0;
    }

    if (*DMA2_CHCR & 0x01000000) {
        goto temp1;
    }

    if (D_80037F54[_qout].unk0 != NULL) {
        while (!(*GPU_STATUS & 0x10000000)) {
        }
        D_80037F54[_qout].unk0(D_80037F54[_qout].unk4, D_80037F54[_qout].unk8);
        D_80037F54[_qout].unk0 = NULL;
        _qout = (_qout + 1) & 0x3F;
        goto loop_1;
    }
    _reset(1);
    printf("GPU_exeque: null func.\n");
    ret = -1;
    goto temp0;

temp0:

    if ((D_8002C278 != NULL) && CheckCallback() && (ret == 0) &&
        !(*DMA2_CHCR & 0x01000000)) {
        set_alarm();
        while (!(*GPU_STATUS & 0x04000000)) {
            if (get_alarm()) {
                break;
            }
        }
        SetIntrMask(intrMask);
        D_8002C278();
        return ret;
    } else {
        goto temp2;
    }

temp1:

    DMACallback(2, _exeque);
    ret = 1;
    goto temp0;

temp2:

    SetIntrMask(intrMask);
    return ret;
}

inline int _reset(int arg0) {
    int intrMask;
    int i;

    intrMask = SetIntrMask(0);
    DMACallback(2, NULL);
    _qout = 0;
    _qin = _qout;

    for (i = 0; i < 64; i++) {
        D_80037F54[i].unk0 = 0;
    }

    switch (arg0) {
    case 0:
        *DMA2_CHCR = 0x401;
        *DPCR |= 0x800;
        *GPU_STATUS = 0;
        break;
    case 1:
        *DMA2_CHCR = 0x401;
        *DPCR |= 0x800;
        *GPU_STATUS = 0x02000000;
        *GPU_STATUS = 0x01000000;
        break;
    default:
        break;
    }
    *GPU_DATA = (*GPU_STATUS & 0x3FFF) | 0xE1001000;
    SetIntrMask(intrMask);
    return ((u_long)*GPU_STATUS >> 0xC) & 1;
}

int _sync(int arg0) {
    if (arg0 == 0) {
        if (D_8002C278 == NULL) {
            DMACallback(2, NULL);
        }
        set_alarm();
        while (_qin != _qout) {
            if (!(*DMA2_CHCR & 0x01000000)) {
                _exeque();
            }
            if (get_alarm()) {
                return -1;
            }
        }
        while (*DMA2_CHCR & 0x01000000) {
            if (get_alarm()) {
                return -1;
            }
        }
        while (!(*GPU_STATUS & 0x04000000)) {
            if (get_alarm()) {
                return -1;
            }
        }
        return 0;
    }
    if ((_qin != _qout) && !(*DMA2_CHCR & 0x01000000)) {
        _exeque();
    }

    if (*DMA2_CHCR & 0x01000000) {
        return 1;
    } else if (!(*GPU_STATUS & 0x04000000)) {
        return 1;
    } else {
        return 0;
    }
}

void set_alarm(void) {
    // schedule timeout for 240 vblanks from now
    D_80039254 = VSync(-1) + 240;
    D_80039258 = 0;
}

int get_alarm(void) {
    if (D_80039254 < VSync(-1) || D_80039258++ > 0x780000) {
        *GPU_STATUS;
        printf("GPU timeout:que=%d,stat=%08x,chcr=%08x,madr=%08x\n",
               (_qin - _qout) & 0x3F, *GPU_STATUS, *DMA2_CHCR, *DMA2_MADR);
        _reset(1);
        return -1;
    }
    return 0;
}

void memset2(s8* ptr, int value, int num) {
    while (num--) {
        *ptr++ = value;
    }
}
