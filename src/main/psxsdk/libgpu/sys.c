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

s32 VSync(s32);

extern gpu* D_8002C260;
extern void (*GPU_printf)(const char* fmt, ...); // 8002c264
extern int D_8002C268;                           // log level
extern int D_8002C26C;                           // graph type
extern int D_8002C270;                           // reverse
extern int D_8002C274;                           // graph queue mode
extern void (*D_8002C278)();
extern volatile s32* GPU_DATA;   // 0x1F801810
extern volatile s32* GPU_STATUS; // 0x1F801814
extern volatile s32* DMA2_MADR;  // 0x1F8010A0
extern volatile s32* DMA2_BCR;   // 0x1F8010A4
extern volatile s32* DMA2_CHCR;  // 0x1F8010A8
extern s32* DMA6_MADR;           // 0x1F8010E0
extern s32* DMA6_BCR;            // 0x1F8010E4
extern volatile s32* DMA6_CHCR;  // 0x1F8010E8
extern s32* DPCR;                // 0x1F8010F0
extern s32 D_80037E20[12];
extern DRAWENV D_80037E60;
extern DISPENV D_80037EBC;
extern s32 D_80039254;
extern s32 D_80039258;

s32 get_alarm();
void set_alarm(void);

u_long get_ce(short, short);
u_long get_cs(short, short);
u_long get_tw(RECT* tw);
u_long get_ofs(short, short);

#define CLAMP(value, low, high)                                                \
    value < low ? low : (value > high ? high : value)

// gpu commands
#define CMD_CLEAR_CACHE 0x01000000
#define CMD_FILL_RECTANGLE_IN_VRAM(color) ((color & 0xFFFFFF) | 0x02000000)
#define CMD_MONOCHROME_RECTANGLE(color) ((color & 0xFFFFFF) | 0x60000000)
#define CMD_COPY_VRAM_TO_CPU 0xC0000000
#define CMD_COPY_CPU_TO_VRAM 0xA0000000

// status reg bits
#define STATUS_READY_TO_RECEIVE_CMD (1 << 26)
#define STATUS_READY_TO_SEND_VRAM_TO_CPU (1 << 27)

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

void SetDrawEnv(DR_ENV* dr_env_in, DRAWENV* env) {
    RECT clip_rect;
    s32 offset;
    u16 calc_clip_height;
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

        if (clip_rect.h >= 0) {
            if ((D_8002C26C != 0 && clip_rect.h >= 1024) ||
                (D_8002C26C == 0 && clip_rect.h >= 512)) {
                if (D_8002C26C != 0) {
                    calc_clip_height = 1023;
                } else {
                    calc_clip_height = 511;
                }
            } else {
                calc_clip_height = clip_rect.h;
            }
        } else {
            calc_clip_height = 0;
        }

        clip_rect.h = calc_clip_height;
        if ((clip_rect.x & 0x3F) || (clip_rect.w & 0x3F)) {
            clip_rect.x -= env->ofs[0];
            clip_rect.y -= env->ofs[1];
            *((s32*)dr_env + offset++) =
                0x60000000 | env->b0 << 0x10 | env->g0 << 8 | env->r0;
            *((s32*)dr_env + offset++) = *(s32*)&clip_rect.x;
            *((s32*)dr_env + offset++) = *(s32*)&clip_rect.w;
            clip_rect.x += env->ofs[0];
            clip_rect.y += env->ofs[1];
        } else {
            *((s32*)dr_env + offset++) =
                0x02000000 | env->b0 << 0x10 | env->g0 << 8 | env->r0;
            *((s32*)dr_env + offset++) = *(s32*)&clip_rect.x;
            *((s32*)dr_env + offset++) = *(s32*)&clip_rect.w;
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

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", get_dx);

s32 _status(void) { return *GPU_STATUS; }

s32 _otc(s32 arg0, s32 arg1) {
    s32 temp_a0;

    *DPCR |= 0x08000000;
    *DMA6_CHCR = 0;
    temp_a0 = arg0 - 4 + arg1 * 4;
    *DMA6_MADR = temp_a0;
    *DMA6_BCR = arg1;
    *DMA6_CHCR = 0x11000002;
    set_alarm();
    if (*DMA6_CHCR & 0x01000000) {
        while (1) {
            if (get_alarm()) {
                return -1;
            } else if (!(*DMA6_CHCR & (1 << 24))) {
                break;
            }
        }
    }
    return arg1;
}

// Clears Frame Buffer
s32 _clr(RECT* arg0, s32 color) {
    s16 var_v0;
    s32 temp_a1;
    u16 temp_v0;
    u16 var_v1;
    RECT temp;
    u16 temp_h;
    s32* ptr;

    temp.x = arg0->x;
    temp.y = arg0->y;
    temp.w = arg0->w;
    temp.h = arg0->h;

    temp.w = CLAMP(temp.w, 0, 1023);

    if (temp.h >= 0) {
        if ((D_8002C26C != 0 && temp.h >= 1024) ||
            (D_8002C26C == 0 && temp.h >= 512)) {
            if (D_8002C26C != 0) {
                temp_h = 1023;
            } else {
                temp_h = 511;
            }
        } else {
            temp_h = temp.h;
        }
    } else {
        temp_h = 0;
    }

    temp.h = temp_h;
    if ((temp.x & 0x3F) || (temp.w & 0x3F)) {
        ptr = &D_80037E20[8];
        D_80037E20[0] = ((s32)ptr & 0xFFFFFF) | 0x07000000; // set up otag
        D_80037E20[1] = 0xE3000000; // set drawing area top left
        D_80037E20[2] = 0xE4FFFFFF; // set drawing area bottom right
        D_80037E20[3] = 0xE5000000; // set drawing offset
        D_80037E20[4] = 0xE6000000;

        D_80037E20[5] = CMD_MONOCHROME_RECTANGLE(color);
        D_80037E20[6] = (s32) * (u32*)&temp.x;
        D_80037E20[7] = (s32) * (u32*)&temp.w;
        *ptr = 0x03FFFFFF;
        D_80037E20[9] = _param(3) | 0xE3000000; // set drawing area top left
        D_80037E20[10] =
            _param(4) | 0xE4000000; // set drawing area bottom right
        D_80037E20[11] = _param(5) | 0xE5000000; // set drawing offset
    } else {
        D_80037E20[0] = 0x04FFFFFF;
        D_80037E20[1] = 0xE6000000; // mask bit setting

        D_80037E20[2] = CMD_FILL_RECTANGLE_IN_VRAM(color);
        D_80037E20[3] = (s32) * (u32*)&temp.x;
        D_80037E20[4] = (s32) * (u32*)&temp.w;
    }
    _cwc(&D_80037E20[0]);
    return 0;
}

// LoadImage
s32 _dws(RECT* arg0, s32* arg1) {
    RECT temp;
    s32 temp_a0;
    s32 size;
    s32 var_s0;
    s32* img_ptr;
    s16 temp_h;
    s32 var_s4;

    img_ptr = arg1;
    set_alarm();
    temp.x = arg0->x;
    temp.y = arg0->y;
    temp.w = arg0->w;
    temp.h = arg0->h;
    var_s4 = 0;

    temp.w = CLAMP(temp.w, 0, 1023);

    if (temp.h >= 0) {
        if ((D_8002C26C != 0 && temp.h >= 1024) ||
            (D_8002C26C == 0 && temp.h >= 512)) {
            if (D_8002C26C != 0) {
                temp_h = 1023;
            } else {
                temp_h = 511;
            }
        } else {
            temp_h = temp.h;
        }
    } else {
        temp_h = 0;
    }
    temp.h = temp_h;
    temp_a0 = ((temp.w * temp.h) + 1) / 2;
    if (temp_a0 <= 0) {
        return -1;
    }
    var_s0 = temp_a0 % 16;
    size = temp_a0 / 16;
    if (!(*GPU_STATUS & STATUS_READY_TO_RECEIVE_CMD)) {
        while (1) {
            if (get_alarm()) {
                return -1;
            } else if (*GPU_STATUS & STATUS_READY_TO_RECEIVE_CMD) {
                break;
            }
        }
    }

    *GPU_STATUS = STATUS_READY_TO_RECEIVE_CMD;

    *GPU_DATA = CMD_CLEAR_CACHE;

    *GPU_DATA = var_s4 ? 0xB0000000 : CMD_COPY_CPU_TO_VRAM;
    *GPU_DATA = *(s32*)&temp.x;
    *GPU_DATA = *(s32*)&temp.w;

    for (var_s0 = var_s0 - 1; var_s0 != -1; var_s0--) {
        *GPU_DATA = *img_ptr++;
    }

    if (size != 0) {
        *GPU_STATUS = 0x04000002;
        *DMA2_MADR = img_ptr;
        *DMA2_BCR = (size << 0x10) | 0x10;
        *DMA2_CHCR = 0x01000201;
    }

    return 0;
}

// StoreImage
// Transfers image data from the frame buffer to main memory.
s32 _drs(RECT* arg0, s32* arg1) {
    RECT temp;
    s32 temp_a0;
    s32 size;
    s32 var_s0;
    s32* img_ptr;
    s16 var_a0;
    s32 var_s4;

    img_ptr = arg1;
    set_alarm();
    temp.x = arg0->x;
    temp.y = arg0->y;
    temp.w = arg0->w;
    temp.h = arg0->h;
    var_s4 = 0;

    temp.w = CLAMP(temp.w, 0, 1023);

    if (temp.h >= 0) {
        if ((D_8002C26C != 0 && temp.h >= 1024) ||
            (D_8002C26C == 0 && temp.h >= 512)) {
            if (D_8002C26C != 0) {
                var_a0 = 1023;
            } else {
                var_a0 = 511;
            }
        } else {
            var_a0 = temp.h;
        }
    } else {
        var_a0 = 0;
    }
    temp.h = var_a0;
    temp_a0 = ((temp.w * temp.h) + 1) / 2;
    if (temp_a0 <= 0) {
        return -1;
    }
    var_s0 = temp_a0 % 16;
    size = temp_a0 / 16;
    if (!(*GPU_STATUS & STATUS_READY_TO_RECEIVE_CMD)) {
        while (1) {
            if (get_alarm()) {
                return -1;
            } else {
                if (*GPU_STATUS & STATUS_READY_TO_RECEIVE_CMD) {
                    break;
                }
            }
        }
    }

    *GPU_STATUS = STATUS_READY_TO_RECEIVE_CMD;

    *GPU_DATA = CMD_CLEAR_CACHE;

    *GPU_DATA = CMD_COPY_VRAM_TO_CPU;
    *GPU_DATA = *(s32*)&temp.x;
    *GPU_DATA = *(s32*)&temp.w;

    if (!(*GPU_STATUS & STATUS_READY_TO_SEND_VRAM_TO_CPU)) {
        while (1) {
            if (get_alarm()) {
                return -1;
            } else if (*GPU_STATUS & STATUS_READY_TO_SEND_VRAM_TO_CPU) {
                break;
            }
        }
    }

    for (var_s0 = var_s0 - 1; var_s0 != -1; var_s0--) {
        *img_ptr++ = *GPU_DATA;
    }

    if (size != 0) {
        *GPU_STATUS = 0x04000003;
        *DMA2_MADR = img_ptr;
        *DMA2_BCR = (size << 0x10) | 0x10;
        *DMA2_CHCR = 0x01000200;
    }

    return 0;
}

extern s32 ctlbuf[];

void _ctl(u32 arg0) {
    *GPU_STATUS = arg0;
    ctlbuf[(arg0 >> 0x18)] = arg0 & 0xFFFFFF;
}

s32 _getctl(s32 arg0) { return (arg0 << 0x18) | ctlbuf[arg0]; }

s32 _cwb(s32* arg0, s32 arg1) {
    s32* var_a0;
    s32 i;

    *GPU_STATUS = 0x04000000;
    var_a0 = arg0;
    for (i = arg1 - 1; i != -1; i--) {
        *GPU_DATA = *var_a0++;
    }
    return 0;
}

void _cwc(s32 arg0) {
    *GPU_STATUS = 0x04000002;
    *DMA2_MADR = arg0;
    *DMA2_BCR = 0;
    *DMA2_CHCR = 0x01000401;
}

s32 _param(s32 arg0) {
    *GPU_STATUS = arg0 | 0x10000000;
    return *GPU_DATA & 0xFFFFFF;
}

void _addque2(s32, s32, s32, s32);

void _addque(s32 arg0, s32 arg1, s32 arg2) { _addque2(arg0, arg1, 0, arg2); }

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _addque2);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _exeque);

s32 DMACallback(s32, s32);
s32 SetIntrMask(s32);

struct QueueItem {
    s32 unk0;
    s32 unk[0x4a / 4];
};

extern volatile struct QueueItem D_80037F54[];
extern volatile s32 _qin;
extern volatile s32 _qout;

s32 _reset(s32 arg0) {
    s32 temp_s1;
    s32 var_a0;

    temp_s1 = SetIntrMask(0);
    DMACallback(2, 0);
    _qout = 0;
    _qin = _qout;

    for (var_a0 = 0; var_a0 < 0x40; var_a0++) {
        D_80037F54[var_a0].unk0 = 0;
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
    SetIntrMask(temp_s1);
    return ((u32)*GPU_STATUS >> 0xC) & 1;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _sync);

void set_alarm(void) {
    // schedule timeout for 240 vblanks from now
    D_80039254 = VSync(-1) + 240;
    D_80039258 = 0;
}

s32 get_alarm(void) {
    s32 temp_s0;
    s32 var_v1;
    if ((D_80039254 < VSync(-1)) || D_80039258++ > 0x780000) {
        *GPU_STATUS;
        printf("GPU timeout:que=%d,stat=%08x,chcr=%08x,madr=%08x\n",
               (_qin - _qout) & 0x3F, *GPU_STATUS, *DMA2_CHCR, *DMA2_MADR);
        temp_s0 = SetIntrMask(0);
        DMACallback(2, 0);
        _qout = 0;
        _qin = _qout;
        for (var_v1 = 0; var_v1 < 64; var_v1++) {
            D_80037F54[var_v1].unk0 = 0;
        }
        *DMA2_CHCR = 0x401;
        *DPCR |= 0x800;
        *GPU_STATUS = 0x02000000;
        *GPU_STATUS = 0x01000000;
        *GPU_DATA = (*GPU_STATUS & 0x3FFF) | 0xE1001000;
        SetIntrMask(temp_s0);
        *GPU_STATUS;
        return -1;
    }
    return 0;
}

void GPU_memset(s8* ptr, int value, s32 num) {
    s32 i;

    for (i = num - 1; i != -1; i--) {
        *ptr++ = value;
    }
}
