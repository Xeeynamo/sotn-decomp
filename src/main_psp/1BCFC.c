// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>
#include <scratchpad.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspctrl.h>
#include <pspgu.h>
#include <psxsdk/libgpu.h>

#define isSemiTrans(ptr) (((ptr)->code & 0x40) >> 6)
#define isFlatShaded(ptr) (((ptr)->code & 0x80) ? 0 : 1)

#define white GU_RGBA(0xFF, 0xFF, 0xFF, 0x80)
#define black GU_RGBA(0, 0, 0, 0x80)
#define red GU_RGBA(0xFF, 0, 0, 0x80)
#define green GU_RGBA(0, 0xFF, 0, 0x80)
#define blue GU_RGBA(0, 0, 0xFF, 0x80)
#define magenta GU_RGBA(0xFF, 0, 0xFF, 0x80)

#undef MIN
#define MIN(a, b) (a) < (b) ? (a) : (b)

#define g_GameClearFlag (*((s32*)0x091FC418))

#define getTPF(tpage) (((tpage) >> 7) & 3) // Get Texture Pattern Format
#define getABR(tpage)                                                          \
    (((tpage) >> 5) & 3) // Semi Transparency (0=B/2+F/2, 1=B+F, 2=B-F, 3=B+F/4)

typedef enum {
    // stretches the game resolution to fill the PSP screen vertically
    SCREEN_MODE_FULL,

    // pixel perfect, but with borders around the game screen
    SCREEN_MODE_PERFECT,
} ScreenMode;

typedef enum {
    SUB_BUF_OFF = 0,
    SUB_BUF_TEMP = 1,
    SUB_BUF_PS = 2,
    SUB_BUF_WOLF = 3,
    SUB_BUF_ALL = 4,
} SubBufType;

#define SB_TEMP_ADDR (s32) sceGeEdramGetAddr() + GU_VRAM_BUFSIZE * 3
#define SB_TEMP_WIDTH 0x100

#define SB_PS_ADDR SB_TEMP_ADDR + (0x200 * SB_TEMP_WIDTH)
#define SB_PS_WIDTH 0x200

#define SB_WOLF_ADDR SB_PS_ADDR + (0x201 * SB_PS_WIDTH)
#define SB_WOLF_WIDTH 0x40

typedef struct {
    s32 x;
    s32 y;
} Unk08C4218C;

typedef struct {
    u32 c;
    float x, y, z;
} Vertex;

typedef struct {
    float u, v;
    u32 c;
    float x, y, z;
} TVertex;

typedef void (*Callback)();

// BSS
static char debugBuf[0x40]; // local
static s32 skipFrames;      // local
s32 D_psp_08C630DC;
s32 D_psp_08C630D8;
s32 D_psp_08C630D4;
bool g_UnlockAllTactics;
static u32 at3Index; // local
bool g_InfiniteHearts;
bool g_InvincibleFlag;
static char D_psp_08C62EC4[0x200];
static s32 packetsDrawn;
static bool drawDebugMenuBG;
static u16 D_psp_08C62CBC[0x100]; // local
static u16 tempClutBuf[0x100];    // local
static u8* D_psp_08C62AB8;        // local
static u16 D_psp_08C62AB4;        // local
static Unk08C4218C D_psp_08C62AAC;
static bool D_psp_08C62AA8;
bool D_psp_08C62AA4;
static bool D_psp_08C62AA0;
static s32 D_psp_08C62A9C;
static s8 D_psp_08C62A98;         // local
static char D_psp_08C62A78[0x20]; // local
static OT_TYPE* D_psp_08C62A74;
bool D_psp_08C62A70;
s32 D_psp_08C62A6C;
s32 D_psp_08C62A68;
static s32 frameTime;
static s32 gpuTime;
static s32 cpuTime;
static bool cpuGpuTime;
static s32 polysDrawn;
static s32 D_psp_08C62A50; // spritesDrawn
static s32 frameCount;
static u32 resetGraphLevel;
static bool gpuEmuInfo;
static SubBufType D_psp_08C62A40; // currend sub buffer
s32 D_psp_08C62A3C;
static Point32 screenOffset;
s32 D_psp_08C62A30; // screen_mode
static DRAWENV D_psp_08C629EC;
static DISPENV D_psp_08C629D8;
static RECT D_psp_08C629D0;
static s32 D_psp_08C629CC; // ofsy
static s32 D_psp_08C629C8; // ofsx
static u32 D_psp_08C629C4; // tpage
static s32 clut8bppCount;
static u8 D_psp_08C429C0[0x100][0x200];
static u8 D_psp_08C4298C[0x34] UNUSED;
static Point32 clut8bppIndexMap[0x100];
static u32 D_psp_08C42188;
static Callback currVSyncCallback;
static u32 VCount;
static u8* D_psp_08C42100[0x20];
static s32 D_psp_08C42080[0x20];
static u8 D_psp_08B42080[0x20][0x8000];
static u8 D_psp_08B42070[0x10] UNUSED;
static SubBufType dispSubBuffer;
static bool drawPolyline;

// DATA
static s32 lastVCount = -1; // VCount at last vSync(n)
static s32 D_psp_089464D4 = -1;
static s32 screenW = 320;
static s32 screenH = 240;
static ScePspFVector2 screenScale = {1, 1};
s32 D_psp_089464E8 = 2;
static bool D_psp_089464EC = true;
static s32 D_psp_089464F0 = 1;

extern s32 g_currFrameBuf;

void func_psp_089113A8(s32 abr, u8 arg1);
void ClearClut8bpp(void);
void func_psp_0891CD28(u_long* p, s32 x, s32 y);
void func_psp_0891CEB8(s32 x, s32 y);

void func_psp_0891A608(void) {
    float x = D_psp_08C629C8;
    float y = D_psp_08C629CC;

    __asm__(".set		push\n"      // save assembler option
            ".set		noreorder\n" // suppress reordering
            "lv.s		s410, 0(%0)\n"
            "lv.s		s411, 0(%1)\n"
            ".set		pop\n" // suppress reordering
            :
            : "m"(x), "m"(y));
}

void func_psp_0891A650(void) {
    float x = 16.0f;
    float y = 256.0f;

    __asm__(".set		push\n"      // save assembler option
            ".set		noreorder\n" // suppress reordering
            "lv.s		s403, 0(%1)\n"
            "lv.s		s420, 0(%0)\n"
            "vmov.s     s421, s420\n"
            "vone.s     s402\n"
            "vone.s     s422\n"
            "vone.s     s302\n"
            "vone.s     s312\n"
            "vone.s     s322\n"
            "vone.s     s332\n"
            "vzero.s    S400\n"
            ".set		pop\n" // suppress reordering
            :
            : "m"(x), "m"(y));
}

void SetScreenMode(s32 screenMode) {
    D_psp_08C62A30 = screenMode;
    switch (D_psp_08C62A30) {
    case SCREEN_MODE_FULL:
        screenW = 362;
        screenH = 272;
        break;
    case SCREEN_MODE_PERFECT:
        screenW = 320;
        screenH = 240;
        break;
    }
    screenOffset.x = (GU_SCR_WIDTH - screenW) / 2;
    screenOffset.y = (GU_SCR_HEIGHT - screenH) / 2;
    D_psp_089464E8 = 2;
}

void func_psp_0891A790(void) {
    s32 i;

    for (i = 0; i < LEN(D_psp_08C42080); i++) {
        D_psp_08C42080[i] = -1;
        D_psp_08C42100[i] = D_psp_08B42080[i];
    }
}

void func_psp_0891A800(void) {
    s32 i;

    for (i = 0; i < LEN(D_psp_08C42080); i++) {
        if (D_psp_08C42080[i] >= 0) {
            D_psp_08C42080[i] = 1;
        }
    }
}

static void func_psp_0891A868(s32 arg0, bool arg1) {
    s32 i;
    u8* addr;

    arg0 &= 0x1F;
    if (arg1) {
        D_psp_08C42080[arg0] = 1;
        D_psp_08C42100[arg0] = NULL;
    } else {
        D_psp_08C42080[arg0] = -1;
        D_psp_08C42100[arg0] = D_psp_08B42080[arg0];
    }
    addr = (u8*)((long)sceGeEdramGetAddr() + 0x12E200);
    for (i = 0; i < LEN(D_psp_08C42080); i++) {
        if (D_psp_08C42080[i] >= 0) {
            D_psp_08C42100[i] = addr;
            addr += 0x8000;
        }
    }
}

static void func_psp_0891A99C(s32 arg0) {
    arg0 &= 0x1F;
    if (D_psp_08C42080[arg0] >= 0) {
        D_psp_08C42080[arg0 & 0x1F]++;
    }
}

static char* func_psp_0891AA00(void) {
    s32 i;

    D_psp_08C62A98 = 0;
    for (i = 0; i < LEN(D_psp_08C42080); i++) {
        if (D_psp_08C42080[i] < 0) {
            D_psp_08C62A78[i] = 'X';
        } else if (D_psp_08C42080[i] == 0) {
            D_psp_08C62A78[i] = '-';
        } else {
            D_psp_08C62A78[i] = 'O';
        }
    }
    return D_psp_08C62A78;
}

static u8* func_psp_0891AAC8(s32 tpage) { return D_psp_08C42100[tpage & 0x1F]; }

static void func_psp_0891AAF8() {
    s32 i;

    if (gpuEmuInfo) {
        sceGuDebugPrint(0, 0x100, 0xFFFFFFFF, func_psp_0891AA00());
    }
    for (i = 0; i < LEN(D_psp_08C42080); i++) {
        if (D_psp_08C42080[i] > 0) {
            func_psp_089117F4(1, 0, 0, 0x40, 0x100, 0x40, D_psp_08B42080[i], 0,
                              0, 0x40, func_psp_0891AAC8(i));
            D_psp_08C42080[i] = 0;
        }
    }
}

static void func_psp_0891ABE4(void) { D_psp_08C62A9C = D_psp_08C62A9C ? 0 : 1; }

static u8* func_psp_0891AC24(void) {
    return (u8*)(SB_PS_ADDR + D_psp_08C62A9C * SB_PS_WIDTH);
}

static u8* func_psp_0891AC60(void) {
    return (u8*)(SB_PS_ADDR + (D_psp_08C62A9C ? 0 : 1) * SB_PS_WIDTH);
}

void func_psp_0891ACBC(void) {
    ClearClut8bpp();
    clut8bppCount = 0;
    D_psp_08C629C4 = 0;
    D_psp_08C629C8 = 0;
    D_psp_08C629CC = 0;
    func_psp_0891A608();
    D_psp_08C62A40 = SUB_BUF_OFF;
    lastVCount = -1;
    D_psp_089464D4 = -1;
    VCount = 0;
    currVSyncCallback = NULL;
    D_psp_08C42188 = 0;
    func_psp_0891A790();
    func_psp_0891A800();
    SetScreenMode(SCREEN_MODE_FULL);
    func_psp_0891A868(24, true);
    func_psp_0891A868(8, true);
    func_psp_0891A868(9, true);
    func_psp_0891A868(10, true);
    func_psp_0891A868(11, true);
    func_psp_0891A868(12, true);
    func_psp_0891A868(13, true);
    func_psp_0891A868(14, true);
    func_psp_0891A868(15, true);
    func_psp_08911C3C(0, 0, 0);
    func_psp_0891A650();
}

void func_psp_0891AE04(void) {
    func_psp_0891A868(1, true);
    func_psp_0891A868(2, true);
    func_psp_0891A868(3, true);
    func_psp_0891A868(4, true);
    D_psp_08C62AA0 = true;
}

void func_psp_0891AE68(void) {
    func_psp_0891A868(1, false);
    func_psp_0891A868(2, false);
    func_psp_0891A868(3, false);
    func_psp_0891A868(4, false);
    D_psp_08C62AA0 = false;
}

void EndFrame(void) {
    g_currFrameBuf = g_currFrameBuf ? 0 : 1;
    sceGuSwapBuffers();
    if (cpuGpuTime) {
        frameTime = GetTimeSinceStartOfFrame();
        ClearFrameTimer();
        StartFrameTimer();
    }
}

static void SetSubBufType(SubBufType bufType) {
    void* base_addr;

    switch (bufType) {
    case SUB_BUF_TEMP:
        D_psp_08C62A40 = SUB_BUF_TEMP;
        PutDrawBuffer((u8*)SB_TEMP_ADDR, SB_TEMP_WIDTH);
        PutTexFilter(GU_NEAREST, GU_NEAREST);
        break;
    case SUB_BUF_WOLF:
        D_psp_08C62A40 = SUB_BUF_WOLF;
        PutDrawBuffer((u8*)SB_WOLF_ADDR, SB_WOLF_WIDTH);
        PutTexFilter(GU_NEAREST, GU_NEAREST);
        break;
    case SUB_BUF_PS:
        D_psp_08C62A40 = SUB_BUF_PS;
        PutDrawBuffer(func_psp_0891AC24(), SB_PS_WIDTH);
        PutTexFilter(GU_NEAREST, GU_NEAREST);
        break;
    default:
    case SUB_BUF_OFF:
        D_psp_08C62A40 = SUB_BUF_OFF;
        if (g_currFrameBuf != 0) {
            base_addr = GU_VRAM_BP_1;
        } else {
            base_addr = GU_VRAM_BP_0;
        }
        PutDrawBuffer((u8*)sceGeEdramGetAddr() + (s32)base_addr, GU_VRAM_WIDTH);
        PutTexFilter(GU_LINEAR, GU_LINEAR);
        break;
    }
}

void func_psp_0891B0BC(s32 arg0) { D_psp_089464F0 = arg0; }

void func_psp_0891B0DC(s32 x, s32 y) {
    D_psp_08C62AA8 = true;
    D_psp_08C62AAC.x = x;
    D_psp_08C62AAC.y = y;
}

static s32 DrawSolidLine(s32 x0, s32 y0, s32 x1, s32 y1, s32 color) {
    Vertex v[2];

    v[0].x = x0;
    v[0].y = y0;
    v[1].x = x1;
    v[1].y = y1;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    v[0].z = v[1].z = 1.0f;
    v[0].c = v[1].c = color;
    func_psp_08912008();
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

s32 func_psp_0891B1F8(s32 x0, s32 y0, s32 x1, s32 y1, s32 color) {
    if (drawPolyline == true) {
        DrawSolidLine(x0, y0, x1 - 1, y0, color);
        DrawSolidLine(x1 - 1, y0, x1 - 1, y1 - 1, color);
        DrawSolidLine(x1 - 1, y1 - 1, x0, y1 - 1, color);
        DrawSolidLine(x0, y1 - 1, x0, y0, color);
    }
    return 0;
}

static s32 DrawSolidRect(s32 x, s32 y, s32 w, s32 h, s32 color) {
    Vertex v[4];

    v[0].x = x;
    v[0].y = y;
    v[1].x = x + w;
    v[1].y = y;
    v[2].x = x;
    v[2].y = y + h;
    v[3].x = x + w;
    v[3].y = y + h;
    v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
    v[1].c = v[0].c = v[3].c = v[2].c = color;
    func_psp_08912008();
    func_psp_089113A8(-1, 0x80);
    func_psp_08910A80(v, 4, sizeof(Vertex), GU_TRIANGLE_STRIP,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

s32 func_psp_0891B400(void) {
    if (~D_psp_089464D4 > 0U) {
    }
    VCount = 0;
    D_psp_089464D4 = sceDisplayGetVcount();
    return D_psp_089464D4;
}

s32 DrawSync(s32 arg0) {
    if (gpuEmuInfo) {
        if (sceGuSync(GU_SYNC_FINISH, GU_SYNC_NOWAIT) == 1) {
            sceGuDebugPrint(472, 0, 0xFFFFFFFF, "G");
        } else {
            sceGuDebugPrint(472, 0, 0xFFFFFFFF, "C");
        }
    }
    if (arg0 == 0) {
        if (cpuGpuTime) {
            cpuTime = GetTimeSinceStartOfFrame();
        }
        sceGuSync(GU_SYNC_FINISH, GU_SYNC_WAIT);
        return 0;
    }
    return sceGuSync(GU_SYNC_FINISH, GU_SYNC_NOWAIT);
}

s32 GetVCount() { return VCount; }

void FinishedRenderingCB(s32 arg0) {
    if (cpuGpuTime) {
        gpuTime = GetTimeSinceStartOfFrame();
    }
}

void VBlankhandler(int idx, void* cookie) {
    VCount++;
    if (currVSyncCallback != NULL) {
        currVSyncCallback();
    }
}

s32 VSync(s32 mode) {
    s32 thisVCount;
    if (mode == 0) {
        sceDisplayWaitVblankStartCB();
        lastVCount = sceDisplayGetVcount();
    } else if (mode == 1) {
        thisVCount = sceDisplayGetVcount();
        return lastVCount - thisVCount;
    } else if (mode > 1) {
        while (mode) {
            sceDisplayWaitVblankStartCB();
            lastVCount = sceDisplayGetVcount();
            mode--;
        }
    } else {
        thisVCount = sceDisplayGetVcount();
        return thisVCount - D_psp_089464D4;
    }
    return 0;
}

s32 ResetGraph(s32 level) {
    if (level == 0) {
        resetGraphLevel = 0;
    } else {
        resetGraphLevel += level;
    }
    return 0;
}

void ClearClut8bpp() { clut8bppCount = 0; }

static s32 FindClut8bppIndex(s32 x, s32 y) {
    s32 i;

    for (i = 0; i < clut8bppCount; i++) {
        if (x == clut8bppIndexMap[i].x && y == clut8bppIndexMap[i].y) {
            return i;
        }
    }
    return -1;
}

static s32 LoadClut8bpp(s32 x, s32 y, s32 w, void* p) {
    s32 clutIndex;
    Point32* ptr;

    if ((clutIndex = FindClut8bppIndex(x, y)) < 0) {
        if (clut8bppCount < 0x100) {
            clutIndex = clut8bppCount;
            clut8bppCount = clutIndex + 1;
        } else {
            return 0;
            ptr = ptr; // FAKE!
        }
    }
    ptr = &clut8bppIndexMap[clutIndex];
    ptr->x = x;
    ptr->y = y;
    memcpy(D_psp_08C429C0[clutIndex], p, w * 2);
    return 1;
}

static u16 GetClut(s32 x, s32 y) {
    s32 clutIndex = FindClut8bppIndex(x, y);
    if (clutIndex >= 0) {
        return (u16)clutIndex | 0x8000;
    } else {
        return getClut(x, y);
    }
}

u8* func_psp_0891B8F0(u16 clut, s32 tpf, s32 arg2) {
    Unk08C4218C v;
    u16 var_s0;

    if (D_psp_08C62AB4 == clut) {
        return D_psp_08C62AB8;
    }
    if (!(clut & 0x8000)) {
        v.y = (clut & 0x3F) * 0x10;
        v.x = clut >> 6;
        if (tpf == 1 && arg2) {
            var_s0 = GetClut(v.y, v.x);
            if (var_s0 & 0x8000) {
                D_psp_08C62AB8 = D_psp_08C429C0[var_s0 & 0x7FFF];
            } else {
                func_psp_0891CEB8(v.y, v.x);
                D_psp_08C62AB8 = D_psp_08C429C0[GetClut(v.y, v.x) & 0x7FFF];
            }
        } else {
            D_psp_08C62AB8 =
                &D_psp_08B42080[(v.y / 0x40) + (v.x / 0x100) * 0x10]
                               [(v.y % 0x40) * 2 + (v.x % 0x100) * 0x80];
        }
    } else {
        D_psp_08C62AB8 = D_psp_08C429C0[clut & 0x7FFF];
    }
    D_psp_08C62AB4 = clut;
    return D_psp_08C62AB8;
}

static void func_psp_0891BB18(RECT* rect, u_long* p, s32 width) {
    u16* dst = (u16*)p;
    s32 x1 = rect->x + rect->w;
    s32 x0 = rect->x;

    while (x0 < x1) {
        s32 dx = 0x40 - (x0 % 0x40);
        if (x1 < (x0 + dx)) {
            dx = x1 - x0;
        }

        memcpy(&D_psp_08B42080[x0 / 0x40 + (rect->y / 0x100) * 0x10]
                              [(x0 % 0x40) * 2 + (rect->y % 0x100) * 0x80],
               &dst[x0 - rect->x], dx * 2);
        x0 += dx;
    }
}

static s32 func_psp_0891BCA0(RECT* rect, u_long* p, s32 width, bool arg3) {
    s32 sp3C;
    s32 x0, y0;
    s32 x1, y1;
    u8* ptr;
    s32 i;
    u8* dst;
    u8* src;

    ptr = (u8*)p;
    if (rect->h == 1) {
        func_psp_0891BB18(rect, p, width);
        return 0;
    }
    x1 = rect->x + rect->w;
    y1 = rect->y + rect->h;
    sp3C = arg3 ? 0x100 : 0x100;
    y0 = rect->y;
    while (y0 < y1) {
        s32 dy = sp3C - (y0 % sp3C);
        if (y0 + dy > y1) {
            dy = y1 - y0;
        }
        x0 = rect->x;
        while (x0 < x1) {
            s32 dx = 0x40 - (x0 % 0x40);
            if (x1 < x0 + dx) {
                dx = x1 - x0;
            }
            dx = dx * 2;
            func_psp_0891A99C(x0 / 0x40 + (y0 / 0x100) * 0x10);
            dst = &D_psp_08B42080[x0 / 0x40 + (y0 / 0x100) * 0x10]
                                 [(x0 % 0x40) * 2 + (y0 % 0x100) * 0x80];
            src = &ptr[width * (y0 - rect->y) + (x0 - rect->x) * 2];
            for (i = 0; i < dy; i++) {
                memcpy(dst, src, dx);
                src += width;
                dst += 0x80;
            }
            x0 += dx / 2;
        }
        y0 += dy;
        if (y0 >= 0x200) {
            break;
        }
    }
    return 0;
}

static inline u16* RemapClut(u16* clut, s32 w, s32 h) {
    s32 i;

    for (i = 0; i < w * h; i++) {
        if (clut[i] == 0x8000) {
            tempClutBuf[i] = 0x8001;
        } else {
            tempClutBuf[i] = clut[i];
        }
    }
    return tempClutBuf;
}

s32 LoadImage(RECT* rect, u_long* p) {
    bool var_a4 = false;

    if (rect->h == 1 &&
        (rect->w == 0x10 || rect->w == 0x100 || rect->w == 0x80)) {
        p = (u_long*)RemapClut((u16*)p, rect->w, rect->h);
    }
    if (rect->h == 1 && rect->w == 0x100) {
        LoadClut8bpp(rect->x, rect->y, rect->w, p);
    }
    return func_psp_0891BCA0(rect, p, rect->w * 2, var_a4);
}

void func_psp_0891C1C0(RECT* rect, u_long* p) {
    func_psp_0891BCA0(rect, p, rect->w * 2, false);
}

static int func_psp_0891C204(RECT* rect, u_long* p, s32 width, s32 arg3) {
    u8* ptr;
    s32 toRead;
    s32 x, y;
    s32 dx, dy;
    s32 i;
    u8* src;
    u8* dst;

    ptr = (u8*)p;
    dy = arg3 ? 0x100 : 0x100;
    for (y = rect->y; y < rect->y + rect->h; y += dy) {
        for (x = rect->x; x < rect->x + rect->w; x += dx / 2) {
            dx = MIN(rect->x + rect->w - x, 0x40);
            if ((x % 0x40) != 0) {
                dx = MIN(dx, 0x40 - (x % 0x40));
            }
            dx = dx * 2;
            toRead = MIN(rect->y + rect->h - y, dy);
            src = &D_psp_08B42080[x / 0x40 + y / 0x100 * 0x10]
                                 [(x % 0x40) * 2 + (y % 0x100) * 0x80];
            dst = &ptr[width * (y - rect->y) + (x - rect->x) * 2];
            for (i = 0; i < toRead; i++) {
                memcpy(dst, src, dx);
                dst += width;
                src += 0x80;
            }
        }
    }
    return 0;
}

s32 StoreImage(RECT* rect, u_long* p) {
    if (rect->y + rect->h > 0x200) {
    }
    if (rect->w == 0x100 && rect->h == 1) {
        func_psp_0891CD28(p, rect->x, rect->y);
        return 0;
    }
    return func_psp_0891C204(rect, p, rect->w * 2, 0);
}

static int func_psp_0891C668(RECT* rect, u8 r, u8 g, u8 b, s32 arg4) {
    s32 toWrite;
    s32 x, y;
    s32 dx, dy;
    s32 i;
    u8* data;
    u16 color;
    u16* var_s1;
    u16* var_s0;

    color = b >> 3 << 11 | g >> 2 << 5 | r >> 2;
    if (color) {
        color |= 0x8000;
    }
    dy = arg4 ? 0x100 : 0x100;
    for (y = rect->y; y < rect->y + rect->h; y += dy) {
        for (x = rect->x; x < rect->x + rect->w; x += dx / 2) {
            dx = MIN(rect->x + rect->w - x, 0x40);
            if ((x % 0x40) != 0) {
                dx = MIN(dx, 0x40 - (x % 0x40));
            }
            dx = dx * 2;
            toWrite = MIN(rect->y + rect->h - y, dy);
            func_psp_0891A99C(x / 0x40 + y / 0x100 * 0x10);
            data = &D_psp_08B42080[x / 0x40 + y / 0x100 * 0x10]
                                  [(x % 0x40) * 2 + (y % 0x100) * 0x80];
            for (i = 0; i < toWrite; i++) {
                var_s0 = (u16*)data;
                var_s1 = (u16*)(data + dx);
                while (var_s0 != var_s1) {
                    *var_s0 = color;
                    var_s0++;
                }
                data += 0x80;
            }
        }
    }
    return 0;
}

int ClearImage(RECT* rect, u_char r, u_char g, u_char b) {
    s32 var_s0 = 0;
    func_psp_0891C668(rect, r, g, b, var_s0);
}

s32 MoveImage(RECT* rect, s32 x, s32 y) {
    RECT load;
    u_long* ptr;
    s32 size;
    s32 w, h;

    size = rect->w * rect->h * 2;
    ptr = (u_long*)malloc(size);
    if (ptr) {
        StoreImage(rect, ptr);
        load.x = x;
        load.y = y;
        load.w = rect->w;
        load.h = rect->h;
        LoadImage(&load, ptr);
        free(ptr);
    }
    return 0;
}

static s32 func_psp_0891CB80(
    s32 x, s32 y, s32 w, s32 h, s32 dstx, s32 dsty, s32 unused) {
    RECT rect;
    s32 i;

    for (i = 0; i < w; i += 0x100) {
        rect.x = x + i;
        rect.y = y;
        rect.w = (i + 0x100 < w) ? 0x100 : w - i;
        rect.h = h;
        MoveImage(&rect, dstx, dsty);
    }
    return 0;
}

u_short LoadClut(u_long* clut, s32 x, s32 y) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = 0x100;
    rect.h = 1;
    LoadImage(&rect, clut);
    return GetClut(x, y);
}

void func_psp_0891CCBC(u_long* clut, s32 x, s32 y) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = 0x10;
    rect.h = 1;
    LoadImage(&rect, clut);
    GetClut(x, y);
}

static void func_psp_0891CD28(u_long* p, s32 x, s32 y) {
    RECT rect;
    s32 clutIndex;

    if ((clutIndex = FindClut8bppIndex(x, y)) < 0) {
        rect.x = x;
        rect.y = y;
        rect.w = 0x100;
        rect.h = 1;
        func_psp_0891C204(&rect, p, rect.w * 2, 0);
        return;
    }
    memcpy(p, &D_psp_08C429C0[clutIndex], sizeof(*D_psp_08C429C0));
}

static void func_psp_0891CDE0(u16* clut, s32 x, s32 y) {
    clut = RemapClut(clut, 0x100, 1);
    LoadClut8bpp(x, y, 0x100, clut);
}

static void func_psp_0891CEB8(s32 x, s32 y) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = 0x100;
    rect.h = 1;
    func_psp_0891C204(&rect, (u_long*)D_psp_08C62CBC, rect.w * 2, 0);
    func_psp_0891CDE0(D_psp_08C62CBC, x, y);
}

u_short LoadTPage(u_long* pix, s32 tpf, s32 abr, s32 x, s32 y, s32 w, s32 h) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = (tpf == 0) ? w / 4 : (tpf == 1) ? w / 2 : w;
    rect.h = h;
    LoadImage(&rect, pix);
    return ((tpf & 3) << 7) | ((abr & 3) << 5) | ((y & 0x100) >> 4) |
           ((x & 0x3FF) >> 6) | ((y & 0x200) << 2);
}

void AddPrim(void* ot, void* p) { addPrim(ot, p); }

Callback VSyncCallback(Callback f) {
    Callback prev;

    prev = currVSyncCallback;
    currVSyncCallback = f;
    return prev;
}

OT_TYPE* ClearOTag(OT_TYPE* ot, int n) {
    P_TAG* pTag;
    s32 i;

    pTag = (P_TAG*)ot;

    for (i = 0; i < (n - 1); i++) {
        pTag->addr = (u32)(pTag + 1);
        pTag->len = 0;
        pTag->code = 0;
        pTag++;
    }
    pTag->len = 0;
    pTag->code = 0;
    pTag->addr = -1;
    return ot;
}

void SetSemiTrans(void* p, int abe) {
    P_TAG* pTag = p;
    if (abe) {
        pTag->code |= 0x40;
    } else {
        pTag->code &= ~0x40;
    }
}

void SetShadeTex(void* p, int tge) {
    P_TAG* pTag = p;
    if (tge) {
        pTag->code |= 0x80;
    } else {
        pTag->code &= ~0x80;
    }
}

void SetDrawMode(DR_MODE* p, s32 dfe, s32 dtd, s32 tpage, RECT* tw) {
    p->len = 2;
    p->code[0] =
        0x0C000000 | (dtd ? 0x200 : 0) | (dfe ? 0x400 : 0) | (tpage & 0x9FF);
    p->code[1] = (tw != NULL) ? (0xE2000000 | (((tw->y & 0xFF) >> 3) << 0xF) |
                                 (((tw->x & 0xFF) >> 3) << 0xA) |
                                 (((~(tw->h - 1) & 0xFF) >> 3) << 5) |
                                 ((~(tw->w - 1) & 0xFF) >> 3))
                              : 0;
}

void SetDrawEnv(DR_ENV* dr_env, DRAWENV* env) {
    dr_env->len = 8;
    dr_env->code = 0x10;
    if (env != NULL) {
        dr_env->clip.x = env->clip.x;
        dr_env->clip.y = env->clip.y;
        dr_env->clip.w = env->clip.w;
        dr_env->clip.h = env->clip.h;
        dr_env->ofs[0] = env->ofs[0];
        dr_env->ofs[1] = env->ofs[1];
        dr_env->tw.x = env->tw.x;
        dr_env->tw.y = env->tw.y;
        dr_env->tw.w = env->tw.w;
        dr_env->tw.h = env->tw.h;
        dr_env->tpage = env->tpage;
        dr_env->dtd = env->dtd;
        dr_env->dfe = env->dfe;
        dr_env->isbg = env->isbg;
        dr_env->r0 = env->r0;
        dr_env->g0 = env->g0;
        dr_env->b0 = env->b0;
    }
}

DRAWENV* PutDrawEnv(DRAWENV* env) {
    D_psp_08C629EC.clip = env->clip;
    D_psp_08C629EC.ofs = env->ofs;
    D_psp_08C629EC.tw = env->tw;
    D_psp_08C629EC.tpage = env->tpage;
    D_psp_08C629EC.dtd = env->dtd;
    D_psp_08C629EC.dfe = env->dfe;
    D_psp_08C629EC.isbg = env->isbg;
    D_psp_08C629EC.r0 = env->r0;
    D_psp_08C629EC.g0 = env->g0;
    D_psp_08C629EC.b0 = env->b0;
    D_psp_08C629EC.dr_env = env->dr_env;
    SetDrawEnv(&D_psp_08C629EC.dr_env, &D_psp_08C629EC);
    D_psp_08C629D0.x = env->clip.x;
    D_psp_08C629D0.y = env->clip.y;
    D_psp_08C629D0.w = env->clip.w;
    D_psp_08C629D0.h = env->clip.h;
    D_psp_08C629C4 = env->tpage;
    D_psp_08C629C8 = D_psp_08C629EC.ofs[0];
    D_psp_08C629CC = D_psp_08C629EC.ofs[1];
    func_psp_0891A608();
    return env;
}

DISPENV* PutDispEnv(DISPENV* env) {
    D_psp_08C629D8.disp = env->disp;
    D_psp_08C629D8.screen = env->screen;
    D_psp_08C629D8.isinter = env->isinter;
    D_psp_08C629D8.isrgb24 = env->isrgb24;
    D_psp_08C629D8.pad0 = env->pad0;
    D_psp_08C629D8.pad1 = env->pad1;
    switch (D_psp_08C62A30) {
    case SCREEN_MODE_FULL:
        screenW = 362;
        screenH = 272;
        break;
    case SCREEN_MODE_PERFECT:
        screenW = 320;
        screenH = 240;
        break;
    }
    screenOffset.x = (GU_SCR_WIDTH - screenW) / 2;
    screenOffset.y = (GU_SCR_HEIGHT - screenH) / 2;
    if (D_psp_08C629D8.disp.w == 256 && D_psp_08C629D8.disp.h == 240) {
        if (D_psp_08C62A30 == SCREEN_MODE_PERFECT) {
            screenOffset.x += D_psp_08C629EC.clip.x;
            screenOffset.y += D_psp_08C629EC.clip.y;
            screenH = D_psp_08C629EC.clip.h;
            screenW = (D_psp_08C62A30 == SCREEN_MODE_FULL) ? 418 : 320;
        } else {
            screenW = (D_psp_08C62A30 == SCREEN_MODE_FULL) ? 418 : 320;
            screenOffset.x = (GU_SCR_WIDTH - screenW) / 2;
            screenScale.x = screenScale.y = 1.0f;
        }
    } else if (D_psp_08C629D8.disp.w <= 480 && D_psp_08C629D8.disp.h <= 256) {
        screenScale.x = screenScale.y = 1.0f;
    } else {
        screenScale.x = (float)screenW / (float)D_psp_08C629D8.disp.w;
        screenScale.y = (float)screenH / (float)D_psp_08C629D8.disp.h;
    }
    return env;
}

void func_psp_0891D9F4(TVertex* ptr, s32 len) {
    s32 i;

    if (len == 2) {
        ptr->x = screenOffset.x + ptr->x * screenScale.x;
        ptr->y = screenOffset.y + ptr->y * screenScale.y;
        ptr++;
        ptr->x = screenOffset.x + (ptr->x + 1) * screenScale.x;
        ptr->y = screenOffset.y + (ptr->y + 1) * screenScale.y;
    } else {
        for (i = 0; i < len; i++) {
            ptr->x = screenOffset.x + ptr->x * screenScale.x;
            ptr->y = screenOffset.y + ptr->y * screenScale.y;
            ptr++;
        }
    }
}

void ApplyScreenAdjustmentsPoly(Vertex* ptr, s32 len) {
    s32 i;

    for (i = 0; i < len; i++) {
        ptr->x = screenOffset.x + ptr->x * screenScale.x;
        ptr->y = screenOffset.y + ptr->y * screenScale.y;
        ptr++;
    }
}

void ApplyScreenAdjustmentsLine(Vertex* ptr, s32 len) {
    s32 i;

    for (i = 0; i < len; i++) {
        ptr->x = screenOffset.x + ptr->x * screenScale.x;
        ptr->y = screenOffset.y + ptr->y * screenScale.y;
        ptr++;
    }
}

DRAWENV* SetDefDrawEnv(DRAWENV* env, s32 x, s32 y, s32 w, s32 h) {
    env->clip.x = x;
    env->clip.y = y;
    env->clip.w = w;
    env->clip.h = h;
    env->ofs[0] = x;
    env->ofs[1] = y;
    env->tw.x = 0;
    env->tw.y = 0;
    env->tw.w = 0;
    env->tw.h = 0;
    env->tpage = 0;
    env->dtd = 1;
    env->dfe = 1;
    env->isbg = 0;
    env->r0 = 0;
    env->g0 = 0;
    env->b0 = 0;
    return env;
}

DISPENV* SetDefDispEnv(DISPENV* env, s32 x, s32 y, s32 w, s32 h) {
    env->disp.x = x;
    env->disp.y = y;
    env->disp.w = w;
    env->disp.h = h;
    env->screen.x = 0;
    env->screen.y = 0;
    env->screen.w = 0;
    env->screen.h = 0;
    env->isinter = 0;
    env->isrgb24 = 0;
    return env;
}

float D_psp_089464FC = 382.0f;
float D_psp_08946500 = 240.0f;
s32 D_psp_08946504 = GU_RGBA(0xA0, 0xA0, 0xA0, 0x80);

s32 DrawNone(void*);
s32 func_psp_08920498(void*);
s32 DrawSprt16(void*);
s32 DrawPolyFT4(void*);
s32 DrawPolyGT3(void*);
s32 DrawPolyGT4(void*);
s32 DrawPolyG4(void*);
s32 DrawLineF2(void*);
s32 DrawLineF4(void*);
s32 DrawLineG2(void*);
s32 DrawLineG4(void*);
s32 DrawTile(void*);
s32 func_psp_0891FCC0(void*);
s32 func_psp_0891FCF0(void*);
s32 SetDROffset(void*);
s32 SetDRArea(void*);
s32 SetDREnv(void*);

// clang-format off
static s32 (*packetFuncs[])(void*) = {
    DrawNone,
    func_psp_08920498, // SPRT
    DrawSprt16,
    DrawPolyFT4,
    DrawPolyGT3,
    DrawPolyGT4,
    DrawPolyG4,
    DrawLineF2,
    DrawLineF4,
    DrawLineG2,
    DrawLineG4,
    DrawTile,
    func_psp_0891FCC0, // DR_MODE OR DR_TWIN ?
    func_psp_0891FCF0, // DR_MODE OR DR_TWIN ?
    SetDROffset,
    SetDRArea,
    SetDREnv,
};
// clang-format on

static void DebugDisplaySubBuffer(void) {
    s32 var_s2 = 0;
    TVertex* v = (TVertex*)SP(0);

    SubBufType prevType = D_psp_08C62A40;
    SetSubBufType(SUB_BUF_OFF);
    PutAlphaBlendingEnable(GU_FALSE);
    v[0].c = v[1].c = v[2].c = v[3].c = white;
    func_psp_08911F24(0, D_psp_089464F0);
    func_psp_08911B7C();
    switch (dispSubBuffer) {
    case SUB_BUF_OFF:
        break;

    case SUB_BUF_TEMP:
        v[0].x = v[0].y = v[1].y = v[2].x = 0.0f;
        v[1].x = v[2].y = v[3].x = v[3].y = 255.0f;
        v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
        v[0].u = v[0].v = v[1].v = v[2].u = 0.0f;
        v[1].u = v[2].v = v[3].u = v[3].v = 255.0f;
        PutScissorRect(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
        func_psp_08911990(SB_TEMP_ADDR, SB_TEMP_WIDTH);
        func_psp_08910A80(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
        break;

    case SUB_BUF_PS:
        PutAlphaBlendingEnable(GU_TRUE);
        PutBlendFunc(GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFF808080);
        v[0].c = v[1].c = v[2].c = v[3].c = 0xFFFFFFFF;
        v[0].x = v[2].x = screenOffset.x;
        v[0].y = v[1].y = screenOffset.y;
        v[1].x = v[3].x = screenOffset.x + screenW;
        v[2].y = v[3].y = screenOffset.y + screenH;
        v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
        v[0].u = v[0].v = v[1].v = v[2].u = 0.0f;
        v[1].u = D_psp_089464FC;
        v[2].v = D_psp_08946500;
        v[3].u = D_psp_089464FC;
        v[3].v = D_psp_08946500;
        PutScissorRect(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
        func_psp_08911990(func_psp_0891AC24(), SB_PS_WIDTH);
        func_psp_08910A80(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
        break;

    case SUB_BUF_WOLF:
        v[0].x = v[0].y = v[1].y = v[2].x = 0.0f;
        v[1].x = v[3].x = 63.0f;
        v[2].y = v[3].y = 63.0f;
        v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
        v[0].u = v[0].v = v[1].v = v[2].u = 0.0f;
        v[1].u = v[3].u = 63.0f;
        v[2].v = v[3].v = 63.0f;
        PutScissorRect(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
        func_psp_08911990(SB_WOLF_ADDR, SB_WOLF_WIDTH);
        func_psp_08910A80(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
        break;

    case SUB_BUF_ALL:
        v[0].x = 0.0f;
        v[0].y = 0.0f;
        v[1].x = 128.0f;
        v[1].y = 0.0f;
        v[2].x = 0.0f;
        v[2].y = 136.0f;
        v[3].x = 128.0f;
        v[3].y = 136.0f;
        v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
        v[0].u = 0.0f;
        v[0].v = 0.0f;
        v[1].u = 256.0f;
        v[1].v = 0.0f;
        v[2].u = 0.0f;
        v[2].v = 272.0f;
        v[3].u = 256.0f;
        v[3].v = 272.0f;
        PutScissorRect(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
        func_psp_08911990(SB_TEMP_ADDR, SB_TEMP_WIDTH);
        func_psp_08910A80(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
        v[0].y += 136.0f;
        v[1].y += 136.0f;
        v[2].y += 136.0f;
        v[3].y += 136.0f;
        v[1].u = 512.0f;
        v[3].u = 512.0f;
        func_psp_08911990(func_psp_0891AC24(), SB_PS_WIDTH);
        func_psp_08910A80(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
        break;
    }
    SetSubBufType(prevType);
}

void func_psp_0891E420(void) {
    s32 var_s1 = 0;
    TVertex* v = (TVertex*)SP(0);

    func_psp_08911990(func_psp_0891AC24(), SB_PS_WIDTH);
    PutAlphaBlendingEnable(GU_FALSE);
    v[0].c = v[1].c = v[2].c = v[3].c = D_psp_08946504;
    v[0].x = v[2].x = screenOffset.x;
    v[0].y = v[1].y = screenOffset.y;
    v[1].x = v[3].x = screenOffset.x + screenW;
    v[2].y = v[3].y = screenOffset.y + screenH;
    v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
    v[0].u = v[2].u = D_psp_08C629EC.clip.x;
    v[0].v = v[1].v = D_psp_08C629EC.clip.y;
    v[1].u = v[3].u = D_psp_08C629EC.clip.x + (float)D_psp_08C629EC.clip.w;
    v[2].v = v[3].v = D_psp_08C629EC.clip.y + (float)D_psp_08C629EC.clip.h;
    SetSubBufType(SUB_BUF_OFF);
    func_psp_08911F24(0, D_psp_089464F0);
    func_psp_08911B7C();
    PutTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA, GU_TRUE);
    PutScissorRect(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    func_psp_08910A80(
        v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
        GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 | GU_TEXTURE_32BITF);
    PutTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA, GU_FALSE);
    SetSubBufType(SUB_BUF_PS);
}

void func_psp_0891E638(void) {
    s32 temp_s2 = 0;
    TVertex* v = (TVertex*)SP(0);
    SubBufType prevType;

    PutAlphaBlendingEnable(GU_FALSE);
    v[0].c = v[1].c = v[2].c = v[3].c = white;
    v[0].x = 0.0f;
    v[0].y = 0.0f;
    v[1].x = GU_SCR_WIDTH;
    v[1].y = 0.0f;
    v[2].x = 0.0f;
    v[2].y = GU_SCR_HEIGHT;
    v[3].x = GU_SCR_WIDTH;
    v[3].y = GU_SCR_HEIGHT;
    v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
    v[0].u = 0.0f;
    v[0].v = 0.0f;
    v[1].u = GU_SCR_WIDTH;
    v[1].v = 0.0f;
    v[2].u = 0.0f;
    v[2].v = GU_SCR_HEIGHT;
    v[3].u = GU_SCR_WIDTH;
    v[3].v = GU_SCR_HEIGHT;
    prevType = D_psp_08C62A40;
    SetSubBufType(SUB_BUF_OFF);
    func_psp_08911F24(0, D_psp_089464F0);
    func_psp_08911B7C();
    PutScissorRect(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    if (func_psp_08919E44()) {
        func_psp_08910FD8((s32)sceGeEdramGetAddr() + 0x1BC000,
                          (s32)sceGeEdramGetAddr() + 0x1BC000 +
                              (GU_VRAM_WIDTH * GU_SCR_HEIGHT),
                          5, GU_VRAM_WIDTH, 9, 9);
    } else {
        DrawSolidRect(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT, black);
    }
    func_psp_08910A80(
        v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
        GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 | GU_TEXTURE_32BITF);
    SetSubBufType(prevType);
}

void func_psp_0891E840(void) {
    func_psp_08910D28();
    func_psp_0890FC2C();
    func_psp_0890FF84();
    func_psp_08910298(1);
    PutLightingEnable(GU_FALSE);
    PutFoggingEnable(GU_FALSE);
    PutTextureMappingEnable(GU_TRUE);
    PutAlphaBlendingEnable(GU_TRUE);
    PutAlphaTestEnable(GU_TRUE);
    PutDepthMask(0);
    PutDepthFunc(GU_NEVER);
    PutPrimitiveCullingEnable(GU_FALSE);
    PutClippingEnable(GU_FALSE);
    PutDitheringEnable(GU_TRUE);
    PutAntiAliasEnable(GU_FALSE);
    PutColorTestEnable(GU_FALSE);
    PutShadeModel(GU_SMOOTH);
    PutStencilTestEnable(GU_FALSE);
    PutTexWrap(GU_CLAMP, GU_CLAMP);
    PutOffset(0, 0);
}

void func_psp_0891E944(void) {
    func_psp_0890FF2C();
    sceKernelDcacheWritebackAll();
    func_psp_0890FE98();
    D_psp_08C62A6C = 0;
    D_psp_08C62A68 = 0;
    D_psp_08C42188 = VCount;
}

static inline OT_TYPE* DrawPackets(OT_TYPE* p) {
    OT_TYPE* ret = NULL;

    while (p != NULL) {
        s32 code = getcode(p) & 0x3F;
        if (code >= 0 && code < LEN(packetFuncs)) {
            if (code != 0) {
                packetFuncs[code](p);
                if (code != 0) {
                    packetsDrawn++;
                }
            }
        }
        if (getaddr(p) == -1 || getaddr(p) == NULL) {
            break;
        }
        ret = p;
        p = (OT_TYPE*)getaddr(p);
    }
    return ret;
}

static void DrawOTag_PSP(OT_TYPE* p) {
    s32 x, y;
    s32 w, h;
    SubBufType prevType;
    u8* temp_s5;
    s32 temp_v0;
    s32 i;
    s32 var_s4;
    s32 var_s3;

    if (p != (OT_TYPE*)-1) {
        D_psp_08C62A74 = p;
        func_psp_0891E840();
        if (D_psp_08C62AA8) {
            D_psp_08C62AA8 = false;
            temp_s5 = func_psp_0891AC24();
            if (D_psp_08C62AAC.x == 0 && D_psp_08C62AAC.y == 0x100) {
                func_psp_089117F4(1, 0, 0, 0x100, 0x100, SB_PS_WIDTH, temp_s5,
                                  0, 0, SB_TEMP_WIDTH, (u8*)SB_TEMP_ADDR);
                for (i = 0; i < 0x20; i++) {
                    func_psp_0891A99C(i);
                }
            } else {
                for (var_s4 = 0; var_s4 < 0x100; var_s4 += 0x40) {
                    func_psp_089117F4(
                        1, var_s4, 0, 0x40, 0xF0, SB_PS_WIDTH, temp_s5, 0, 0,
                        0x40,
                        &D_psp_08B42080[(D_psp_08C62AAC.x + var_s4) / 0x40 +
                                        (D_psp_08C62AAC.y / 0x100) * 0x10]
                                       [((D_psp_08C62AAC.x + var_s4) % 0x40) *
                                            2 +
                                        (D_psp_08C62AAC.y % 0x100) * 0x80]);
                }
                for (i = 0; i < 0x20; i++) {
                    func_psp_0891A99C(i);
                }
            }
        }
        if (D_psp_08C62AA4) {
            D_psp_08C62AA4 = false;
            for (var_s3 = 0; var_s3 < 0x40; var_s3 += 0x40) {
                func_psp_089117F4(1, var_s3, 0, 0x40, 0x100, SB_TEMP_WIDTH,
                                  (u8*)SB_TEMP_ADDR, 0, 0, 0x40,
                                  &D_psp_08B42080[(var_s3 / 0x40) + 0x10]
                                                 [(var_s3 % 0x40) * 2]);
            }
            for (i = 0; i < 0x20; i++) {
                func_psp_0891A99C(i);
            }
        }
        func_psp_0891AAF8();
        func_psp_0891ABE4();
        if (D_psp_08C62A3C > 0) {
            PutScissorRect(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
            DrawSolidRect(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT, black);
            if (D_psp_08C62A3C > 0) {
                D_psp_08C62A3C--;
            }
        }
        if (D_psp_08C629D8.disp.w > 0x100 || D_psp_089464E8 > 0) {
            func_psp_0891E638();
            if (D_psp_089464E8 > 0) {
                D_psp_089464E8--;
            }
        } else {
            prevType = D_psp_08C62A40;
            switch (D_psp_08C62A30) {
            case SCREEN_MODE_FULL:
                w = 418;
                h = 272;
                break;
            case SCREEN_MODE_PERFECT:
                w = 369;
                h = 240;
                break;
            }
            x = (GU_SCR_WIDTH - w) / 2;
            y = (GU_SCR_HEIGHT - h) / 2;
            SetSubBufType(SUB_BUF_OFF);
            PutScissorRect(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
            DrawSolidRect(x, y, w - 1, h - 1, black);
            SetSubBufType(prevType);
        }
        SetDREnv(&D_psp_08C629EC.dr_env);
        packetsDrawn = 0;
        D_psp_08C62A50 = 0;
        polysDrawn = 0;
        DrawPackets(p);
        if (D_psp_08C62A40 == SUB_BUF_PS) {
            func_psp_0891E420();
        }
        if (dispSubBuffer != SUB_BUF_OFF) {
            DebugDisplaySubBuffer();
        }
        if (drawDebugMenuBG) {
            SetSubBufType(SUB_BUF_OFF);
            PutScissorRect(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
            DrawSolidRect(0x130, 0, 0xB0, 0x70, black);
        }
        if (cpuGpuTime && frameTime != 0) {
            u32 var_s7 = (VCount != D_psp_08C42188)
                             ? (VCount - D_psp_08C42188) * 0xF0
                             : 0xF0;
            SetSubBufType(SUB_BUF_OFF);
            PutScissorRect(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
            DrawSolidLine(0, 0, (frameTime * var_s7) / frameTime, 0, white);
            DrawSolidLine(0, 1, (cpuTime * var_s7) / frameTime, 1, red);
            DrawSolidLine(0, 2, (gpuTime * var_s7) / frameTime, 2, green);
        }
        SetSubBufType(SUB_BUF_OFF);
        PutScissorRect(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
        func_psp_08932228();
        func_psp_0891E944();
        if (gpuEmuInfo) {
            s32 fps =
                (VCount != D_psp_08C42188) ? 60 / (VCount - D_psp_08C42188) : 0;
            sprintf(D_psp_08C62EC4, "Frame=%d/ResetGraph=%2d/W:%d,H:%d/%2dfps",
                    frameCount, resetGraphLevel, screenW, screenH, fps);
            sceGuDebugPrint(0, 264, 0xFFFFFFFF, D_psp_08C62EC4);
        }
        frameCount++;
        ResetGraph(0);
    }
}

void DrawOTag(OT_TYPE* p) {
    static char* off_on[] = {"OFF", "ON"};
    static char* subBufType[] = {"OFF", "TEMP", "PS", "WOLF", "ALL"};

    s32 x, y;

    D_psp_08C62A74 = p;
    if (PadReadPSP() & PSP_CTRL_R3) {
        s32 prevPad = PadReadPSP();
        s32 cursor = 0;
        s32 sp48 = -1;
        drawDebugMenuBG = true;
        while (cursor >= 0) {
            s32 thisPad = PadReadPSP();
            if (prevPad == 0 && thisPad != 0) {
                if (thisPad & PSP_CTRL_CROSS) {
                    while (PadReadPSP() != 0) {
                        VSync(0);
                    }
                    drawDebugMenuBG = false;
                    DrawOTag_PSP(p);
                    break;
                }
                if (thisPad & PSP_CTRL_UP) {
                    cursor = (cursor + 11) % 12;
                }
                if (thisPad & PSP_CTRL_DOWN) {
                    cursor = (cursor + 1) % 12;
                }
                if (cursor == 11) {
                    if (thisPad & PSP_CTRL_RIGHT) {
                        at3Index += 1;
                    }
                    if (thisPad & PSP_CTRL_LEFT) {
                        at3Index += 0x230;
                    }
                    if (thisPad & PSP_CTRL_RTRIGGER) {
                        at3Index += 0x14;
                    }
                    if (thisPad & PSP_CTRL_LTRIGGER) {
                        at3Index += 0x21D;
                    }
                    at3Index = at3Index % 0x231;
                }
                if (thisPad & PSP_CTRL_CIRCLE) {
                    switch (cursor) {
                    case 0:
                        g_GameClearFlag = g_GameClearFlag ? false : true;
                        break;
                    case 1:
                        g_InvincibleFlag = g_InvincibleFlag ? false : true;
                        break;
                    case 2:
                        g_InfiniteHearts = g_InfiniteHearts ? false : true;
                        break;
                    case 3:
                        D_psp_08C62A30 = (D_psp_08C62A30 + 1) % 2;
                        SetScreenMode(D_psp_08C62A30);
                        break;
                    case 4:
                        skipFrames++;
                        if (skipFrames > 6) {
                            skipFrames = 0;
                        }
                        break;
                    case 5:
                        D_psp_08C62A70 = D_psp_08C62A70 ? false : true;
                        break;
                    case 6:
                        drawPolyline = drawPolyline ? false : true;
                        break;
                    case 7:
                        dispSubBuffer =
                            (dispSubBuffer < 4) ? dispSubBuffer + 1 : 0;
                        break;
                    case 8:
                        gpuEmuInfo = gpuEmuInfo ? false : true;
                        break;
                    case 9:
                        cpuGpuTime = cpuGpuTime ? false : true;
                        break;
                    case 11:
                        func_psp_09141878(at3Index);
                        break;
                    case 10:
                        g_UnlockAllTactics = g_UnlockAllTactics ? false : true;
                        break;
                    }
                }
            }
            x = 304;
            y = 0;
            sprintf(debugBuf, "=== DEGUG MENU ===");
            sceGuDebugPrint(x, y, 0xFFFFFFFF, debugBuf);
            sprintf(
                debugBuf, "GameClearFlag:%s", off_on[g_GameClearFlag ? 1 : 0]);
            sceGuDebugPrint(x + 0x10, y + 0x8, 0xFFFFFFFF, debugBuf);
            sprintf(debugBuf, "MutekiFlag:%s", off_on[g_InvincibleFlag]);
            sceGuDebugPrint(x + 0x10, y + 0x10, 0xFFFFFFFF, debugBuf);
            sprintf(debugBuf, "Heart99:%s", off_on[g_InfiniteHearts]);
            sceGuDebugPrint(x + 0x10, y + 0x18, 0xFFFFFFFF, debugBuf);
            sprintf(debugBuf, "ScreenMode:%d", D_psp_08C62A30);
            sceGuDebugPrint(x + 0x10, y + 0x20, 0xFFFFFFFF, debugBuf);
            sprintf(debugBuf, "PlayWait:%d", skipFrames);
            sceGuDebugPrint(x + 0x10, y + 0x28, 0xFFFFFFFF, debugBuf);
            sprintf(debugBuf, "FntPrint:%s", off_on[D_psp_08C62A70]);
            sceGuDebugPrint(x + 0x10, y + 0x30, 0xFFFFFFFF, debugBuf);
            sprintf(debugBuf, "DrawPolyline:%s", off_on[drawPolyline]);
            sceGuDebugPrint(x + 0x10, y + 0x38, 0xFFFFFFFF, debugBuf);
            sprintf(debugBuf, "DispSubBuffer:%s", subBufType[dispSubBuffer]);
            sceGuDebugPrint(x + 0x10, y + 0x40, 0xFFFFFFFF, debugBuf);
            sprintf(debugBuf, "GpuEmuInfo:%s", off_on[gpuEmuInfo]);
            sceGuDebugPrint(x + 0x10, y + 0x48, 0xFFFFFFFF, debugBuf);
            sprintf(debugBuf, "CpuGpuTime:%s", off_on[cpuGpuTime]);
            sceGuDebugPrint(x + 0x10, y + 0x50, 0xFFFFFFFF, debugBuf);
            sprintf(debugBuf, "OYAJI:%03d", g_UnlockAllTactics);
            sceGuDebugPrint(x + 0x10, y + 0x58, 0xFFFFFFFF, debugBuf);
            sprintf(debugBuf, "AT3:%03d", at3Index);
            sceGuDebugPrint(x + 0x10, y + 0x60, 0xFFFFFFFF, debugBuf);
            sprintf(debugBuf, "[%s]", GetAT3FileName(at3Index));
            sceGuDebugPrint(x + 0x10, y + 0x68, 0xFFFFFFFF, debugBuf);
            func_psp_0892A8FC();
            if (GetVCount() & 0x20) {
                sceGuDebugPrint(x, y + (cursor + 1) * 8, 0xFFFFFFFF, "=>");
            }
            DrawOTag_PSP(p);
            GsClearVcount();
            DrawSync(0);
            VSync(0);
            EndFrame();
            prevPad = thisPad;
        }
        drawDebugMenuBG = false;
        D_psp_089464E8 = 2;
    } else {
        s32 i;
        for (i = 0; i < skipFrames; i++) {
            GsClearVcount();
            VSync(0);
        }
        DrawOTag_PSP(p);
    }
}

void func_psp_0891FC64(void) {
    if (D_psp_08C62A74 != NULL) {
        DrawOTag(D_psp_08C62A74);
    } else {
        DrawOTag(NULL);
    }
}

void SetDispMask(int mask) {}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1BCFC", func_psp_0891FCC0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1BCFC", func_psp_0891FCF0);

s32 SetDROffset(void* p) {
    DR_OFFSET* ptr = p;

    D_psp_08C629C8 = ptr->ofs[0];
    D_psp_08C629CC = ptr->ofs[1];
    func_psp_0891A608();
    return 0;
}

s32 SetDRArea(void* p) {
    DR_AREA* ptr = p;

    D_psp_08C629D0.x = ptr->clip.x;
    D_psp_08C629D0.y = ptr->clip.y;
    D_psp_08C629D0.w = ptr->clip.w;
    D_psp_08C629D0.h = ptr->clip.h;
    return 0;
}

s32 SetDREnv(void* p) {
    DR_ENV* ptr = p;
    RECT rect;
    s32 x, y;

    D_psp_08C629EC.dr_env.tag = ptr->tag;
    D_psp_08C629EC.dr_env.len = ptr->len;
    D_psp_08C629EC.dr_env.r0 = ptr->r0;
    D_psp_08C629EC.dr_env.g0 = ptr->g0;
    D_psp_08C629EC.dr_env.b0 = ptr->b0;
    D_psp_08C629EC.dr_env.code = ptr->code;
    D_psp_08C629EC.dr_env.clip = ptr->clip;
    D_psp_08C629EC.dr_env.ofs = ptr->ofs;
    D_psp_08C629EC.dr_env.tw = ptr->tw;
    D_psp_08C629EC.dr_env.tpage = ptr->tpage;
    D_psp_08C629EC.dr_env.dtd = ptr->dtd;
    D_psp_08C629EC.dr_env.dfe = ptr->dfe;
    D_psp_08C629EC.dr_env.isbg = ptr->isbg;
    if (ptr->ofs[0] == 0x40 && ptr->clip.x == 0x40) {
        D_psp_08C629C8 = 0x40;
    } else {
        D_psp_08C629C8 = 0;
    }
    D_psp_08C629CC = 0;
    func_psp_0891A608();
    x = 0;
    y = 0;
    rect = ptr->clip;
    if (D_psp_089464EC && ptr->ofs[1] == 0x100) {
        SetSubBufType(SUB_BUF_TEMP);
        rect.y -= ptr->ofs[1];
    } else if (ptr->ofs[0] == 0x200 && ptr->ofs[1] == 0x1C0) {
        SetSubBufType(SUB_BUF_WOLF);
        rect.x = 0;
        rect.y = 0;
    } else if (D_psp_08C629D8.disp.w <= 480 && D_psp_08C629D8.disp.h <= 256) {
        SetSubBufType(SUB_BUF_PS);
    } else {
        SetSubBufType(SUB_BUF_OFF);
        x = screenOffset.x;
        y = screenOffset.y;
        rect.x *= screenScale.x;
        rect.y *= screenScale.y;
        rect.w *= screenScale.x;
        rect.h *= screenScale.y;
    }
    PutScissorRect(
        x + rect.x, y + rect.y, x + rect.x + rect.w, y + rect.y + rect.h);
    if (ptr->isbg == true) {
        DrawSolidRect(x + rect.x, y + rect.y, rect.w, rect.h,
                      GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80));
    }
    PutDitheringEnable(D_psp_08C629EC.dtd ? GU_TRUE : GU_FALSE);
    return 0;
}

void func_psp_089201E8(SPRT* ptr, TVertex* v, float arg2, float arg3,
                       float arg4, float arg5, u8 tpf) {
    float u0, v0;
    float u1, v1;
    u16 temp_s2;
    u16 temp_s1;
    u32 var_s0;

    if (tpf == 0) {
        var_s0 = 0x100;
    } else if (tpf == 1) {
        var_s0 = 0x80;
    } else if (tpf == 2) {
        var_s0 = 0x40;
    }
    temp_s2 = (u16)ptr->u0 + arg2;
    temp_s2 %= var_s0;
    temp_s1 = (u16)ptr->v0 + arg4;
    temp_s1 %= 0x100;
    u0 = temp_s2;
    v0 = temp_s1;
    u1 = u0 + (arg3 - 0.4f);
    v1 = v0 + (arg5 - 0.4f);
    v[0].u = u0;
    v[1].u = u1;
    v[0].v = v0;
    v[1].v = v1;
}

s32 DrawNone(void* p) {}

static inline u8* GetTextureAddr(s32 tpage) {
    if (D_psp_089464EC) {
        if ((tpage & 0x1F) == 0x10 && getTPF(tpage) == 2) {
            return (u8*)SB_TEMP_ADDR;
        }
        if ((tpage & 0xF000) == 0x8000) {
            return (u8*)SB_TEMP_ADDR;
        }
        if ((tpage & 0xF000) == 0x4000) {
            return (u8*)SB_WOLF_ADDR;
        }
    }
    if ((tpage & 0x1F) == 0 && getTPF(tpage) == 2) {
        return func_psp_0891AC60();
    }
    if (!D_psp_08C62AA0) {
        if ((tpage & 0x1F) == 4 && getTPF(tpage) == 2) {
            return func_psp_0891AC24();
        }
    }
    return func_psp_0891AAC8(tpage);
}

static inline void unkInlineFunc2(u8* texPtr, u8* clutPtr, s32 tpf) {
    if (texPtr == (u8*)(SB_TEMP_ADDR)) {
        if (tpf == 2) {
            func_psp_08911990(texPtr, SB_TEMP_WIDTH);
        } else {
            func_psp_0891149C(texPtr, 0x400, 0x100, clutPtr, tpf);
        }
    } else if (texPtr == func_psp_0891AC24()) {
        func_psp_08911990(texPtr, SB_PS_WIDTH);
    } else if (texPtr == func_psp_0891AC60()) {
        func_psp_08911990(texPtr, SB_PS_WIDTH);
    } else if (texPtr == (u8*)(SB_WOLF_ADDR)) {
        func_psp_0891149C(texPtr, 0x40, 0x40, NULL, 2);
    } else {
        func_psp_08910D44(texPtr, clutPtr, tpf);
    }
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1BCFC", func_psp_08920498);

s32 DrawSprt16(void* p) {
    SPRT_16* ptr = p;
    TVertex* v;

    v = (TVertex*)func_psp_089104B4(0xC);
    if (getTPF(D_psp_08C629C4) == 2) {
    }
    func_psp_08910D44(
        D_psp_08B42080[D_psp_08C629C4 & 0x1F],
        &D_psp_08B42080[((ptr->clut & 0x3F) << 4) / 0x40 +
                        ((ptr->clut >> 6) / 0x100) * 0x10]
                       [(((ptr->clut & 0x3F) << 4) % 0x40) * 2 +
                        ((ptr->clut >> 6) % 0x100) * 0x80],
        getTPF(D_psp_08C629C4));
    if (isSemiTrans(ptr)) {
        switch (getABR(D_psp_08C629C4)) {
        case 0:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
            break;
        case 1:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
            break;
        case 2:
            func_psp_08911B84(
                1, GU_REVERSE_SUBTRACT, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
            break;
        case 3:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFF404040, 0xFFFFFFFF);
            break;
        default:
            func_psp_08911B84(
                0, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
            break;
        }
    } else {
        func_psp_08911B84(0, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
    }
    if (isFlatShaded(ptr)) {
        v[0].c = v[1].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    } else {
        v[0].c = v[1].c = white;
    }
    __asm__(
        ".set		push\n"      // save assembler option
        ".set		noreorder\n" // suppress reordering
        "lv.s		s700, 0xC(%1)\n"
        "vs2i.p		c710, c700\n"
        "vi2f.p		c300, c710, 16\n"
        "vadd.p		c300, c300, c410\n"
        "sv.s		s300, 0xC(%0)\n"
        "sv.s		s301, 0x10(%0)\n"
        "sv.s		s302, 0x14(%0)\n"
        "vadd.p		c310, c300, c420\n"
        "sv.s		s310, 0x24(%0)\n"
        "sv.s		s311, 0x28(%0)\n"
        "sv.s		s312, 0x2C(%0)\n"
        "lbu		$4, 0x10(%1)\n"
        "lbu		$5, 0x11(%1)\n"
        "mtv		$4, s610\n"
        "mtv		$5, s611\n"
        "vi2f.p		c620, c610, 0\n"
        "sv.s		s620, 0(%0)\n"
        "sv.s		s621, 4(%0)\n"
        "vadd.p		c630, c620, c420\n"
        "sv.s		s630, 0x18(%0)\n"
        "sv.s		s631, 0x1C(%0)\n"
        ".set		pop\n" // suppress reordering
        : "+r"(v)
        : "r"(ptr));
    if (ptr->code & 0x40) {
        func_psp_08912070(D_psp_089464F0, 0, 0, 0);
        func_psp_08910C74(v, 2, sizeof(TVertex), GU_SPRITES,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
        func_psp_089120E4();
        func_psp_08910C74(v, 2, sizeof(TVertex), GU_SPRITES,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
    } else {
        func_psp_0891214C(D_psp_089464F0, 0, 0, 0);
        func_psp_08910C74(v, 2, sizeof(TVertex), GU_SPRITES,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
    }
    func_psp_0891B1F8(v[0].x, v[0].y, v[1].x, v[1].y, red);
    D_psp_08C62A50++;
    return 0;
}

s32 DrawPolyG4(void* p) {
    POLY_G4* ptr = p;
    Vertex v[4];
    u8 var_s1;

    if (isSemiTrans(ptr)) {
        var_s1 = 0x80;
        func_psp_089113A8(getABR(D_psp_08C629C4), var_s1);
    } else {
        func_psp_089113A8(-1, 0x80);
    }
    v[0].x = D_psp_08C629C8 + ptr->x0;
    v[0].y = D_psp_08C629CC + ptr->y0;
    v[0].z = 1.0f;
    v[1].x = D_psp_08C629C8 + ptr->x1;
    v[1].y = D_psp_08C629CC + ptr->y1;
    v[1].z = 1.0f;
    v[2].x = D_psp_08C629C8 + ptr->x2;
    v[2].y = D_psp_08C629CC + ptr->y2;
    v[2].z = 1.0f;
    v[3].x = D_psp_08C629C8 + ptr->x3;
    v[3].y = D_psp_08C629CC + ptr->y3;
    v[3].z = 1.0f;
    v[0].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    v[1].c = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
    v[2].c = GU_RGBA(ptr->r2, ptr->g2, ptr->b2, 0x80);
    v[3].c = GU_RGBA(ptr->r3, ptr->g3, ptr->b3, 0x80);
    if (D_psp_08C62A40 == SUB_BUF_OFF) {
        ApplyScreenAdjustmentsPoly(v, 4);
    }
    func_psp_08912008();
    func_psp_08910A80(v, 4, sizeof(Vertex), GU_TRIANGLE_STRIP,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    func_psp_0891B1F8(v[0].x, v[0].y, v[3].x, v[3].y, blue);
    return 0;
}

s32 DrawPolyFT4(void* p) {
    POLY_FT4* ptr = p;
    s32 isSemiTrans;
    u8 tpf;
    u8* clutPtr;
    u8* texPtr;
    TVertex* v;

    clutPtr = NULL;
    isSemiTrans = isSemiTrans(ptr);
    D_psp_08C629C4 = ptr->tpage;
    v = (TVertex*)SP(0);
    tpf = getTPF(ptr->tpage);
    texPtr = GetTextureAddr(ptr->tpage);
    if (tpf != 2) {
        clutPtr = func_psp_0891B8F0(ptr->clut, tpf, 1);
    }
    unkInlineFunc2(texPtr, clutPtr, tpf);
    if (isSemiTrans(ptr)) {
        func_psp_089113A8(getABR(ptr->tpage), 0x80);
    } else {
        PutAlphaBlendingEnable(GU_FALSE);
    }
    if (isFlatShaded(ptr)) {
        v[0].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
        v[1].c = v[2].c = v[3].c = v[0].c;
    } else {
        v[0].c = v[1].c = v[2].c = v[3].c = white;
    }
    v[0].x = D_psp_08C629C8 + ptr->x0;
    v[0].y = D_psp_08C629CC + ptr->y0;
    v[0].z = 1.0f;
    v[1].x = D_psp_08C629C8 + ptr->x1;
    v[1].y = D_psp_08C629CC + ptr->y1;
    v[1].z = 1.0f;
    v[2].x = D_psp_08C629C8 + ptr->x2;
    v[2].y = D_psp_08C629CC + ptr->y2;
    v[2].z = 1.0f;
    v[3].x = D_psp_08C629C8 + ptr->x3;
    v[3].y = D_psp_08C629CC + ptr->y3;
    v[3].z = 1.0f;

    v[0].u = ptr->u0;
    v[0].v = ptr->v0;
    v[1].u = ptr->u1;
    v[1].v = ptr->v1;
    v[2].u = ptr->u2;
    v[2].v = ptr->v2;
    v[3].u = ptr->u3;
    v[3].v = ptr->v3;

    if (D_psp_08C62A40 == SUB_BUF_OFF) {
        func_psp_0891D9F4(v, 4);
    }
    func_psp_08911F24(isSemiTrans, D_psp_089464F0);
    func_psp_08910A80(
        v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
        GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 | GU_TEXTURE_32BITF);
    if (isSemiTrans) {
        func_psp_08911FA0();
        func_psp_08910A80(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
    }
    if (drawPolyline == true) {
        s32 color = red;
        DrawSolidLine(v[0].x, v[0].y, v[1].x, v[1].y, color);
        DrawSolidLine(v[1].x, v[1].y, v[3].x, v[3].y, color);
        DrawSolidLine(v[3].x, v[3].y, v[2].x, v[2].y, color);
        DrawSolidLine(v[2].x, v[2].y, v[0].x, v[0].y, color);
    }
    polysDrawn++;
    return 0;
}

s32 DrawPolyGT3(void* p) {
    POLY_GT3* ptr = p;
    TVertex* v;
    u8 tpf;
    u8* texPtr;
    u8* clutPtr;
    s32 isSemiTrans;

    clutPtr = NULL;
    isSemiTrans = isSemiTrans(ptr);
    D_psp_08C629C4 = ptr->tpage;
    v = (TVertex*)func_psp_089104B4(0x12);
    tpf = getTPF(ptr->tpage);
    texPtr = GetTextureAddr(ptr->tpage);
    if (tpf != 2) {
        clutPtr = func_psp_0891B8F0(ptr->clut, tpf, 1);
    }
    unkInlineFunc2(texPtr, clutPtr, tpf);
    if (isSemiTrans(ptr)) {
        func_psp_089113A8(getABR(ptr->tpage), 0x80);
    } else {
        PutAlphaBlendingEnable(GU_FALSE);
    }
    if (isFlatShaded(ptr)) {
        v[0].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
        v[1].c = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
        v[2].c = GU_RGBA(ptr->r2, ptr->g2, ptr->b2, 0x80);
    } else {
        v[0].c = v[1].c = v[2].c = white;
    }
    __asm__(
        ".set		push\n"      // save assembler option
        ".set		noreorder\n" // suppress reordering
        "lv.s		s700, 0xC(%1)\n"
        "vs2i.p		c710, c700\n"
        "vi2f.p		c300, c710, 16\n"
        "vadd.p		c300, c300, c410\n"
        "sv.s		s300, 0xC(%0)\n"
        "sv.s		s301, 0x10(%0)\n"
        "sv.s		s302, 0x14(%0)\n"
        "lv.s		s700, 0x18(%1)\n"
        "vs2i.p		c710, c700\n"
        "vi2f.p		c300, c710, 16\n"
        "vadd.p		c300, c300, c410\n"
        "sv.s		s300, 0x24(%0)\n"
        "sv.s		s301, 0x28(%0)\n"
        "sv.s		s302, 0x2C(%0)\n"
        "lv.s		s700, 0x24(%1)\n"
        "vs2i.p		c710, c700\n"
        "vi2f.p		c300, c710, 16\n"
        "vadd.p		c300, c300, c410\n"
        "sv.s		s300, 0x3C(%0)\n"
        "sv.s		s301, 0x40(%0)\n"
        "sv.s		s302, 0x44(%0)\n"
        "lbu		$4, 0x10(%1)\n"
        "lbu		$5, 0x11(%1)\n"
        "mtv		$4, s610\n"
        "mtv		$5, s611\n"
        "vi2f.p		c620, c610, 0\n"
        "sv.s		s620, 0(%0)\n"
        "sv.s		s621, 4(%0)\n"
        "lbu		$4, 0x1C(%1)\n"
        "lbu		$5, 0x1D(%1)\n"
        "mtv		$4, s610\n"
        "mtv		$5, s611\n"
        "vi2f.p		c620, c610, 0\n"
        "sv.s		s620, 0x18(%0)\n"
        "sv.s		s621, 0x1C(%0)\n"
        "lbu		$4, 0x28(%1)\n"
        "lbu		$5, 0x29(%1)\n"
        "mtv		$4, s610\n"
        "mtv		$5, s611\n"
        "vi2f.p		c620, c610, 0\n"
        "sv.s		s620, 0x30(%0)\n"
        "sv.s		s621, 0x34(%0)\n"
        ".set		pop\n" // suppress reordering
        : "+r"(v)
        : "r"(ptr));

    if (D_psp_08C62A40 == SUB_BUF_OFF) {
        func_psp_0891D9F4(v, 3);
    }
    func_psp_08911F24(isSemiTrans, D_psp_089464F0);
    func_psp_08910C74(
        v, 3, sizeof(TVertex), GU_TRIANGLE_STRIP,
        GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 | GU_TEXTURE_32BITF);
    if (isSemiTrans) {
        func_psp_08911FA0();
        func_psp_08910C74(v, 3, sizeof(TVertex), GU_TRIANGLE_STRIP,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
    }
    if (drawPolyline == true) {
        s32 color = green;
        DrawSolidLine(v[0].x, v[0].y, v[1].x, v[1].y, color);
        DrawSolidLine(v[1].x, v[1].y, v[2].x, v[2].y, color);
        DrawSolidLine(v[2].x, v[2].y, v[0].x, v[0].y, color);
    }
    polysDrawn++;
    return 0;
}

s32 func_psp_08922C14(void* p) {
    POLY_GT4* ptr = p;
    s32 r, g, b;
    s32 fix;
    TVertex* v;

    D_psp_08C629C4 = ptr->tpage;
    v = (TVertex*)SP(0);

    func_psp_0891149C(SB_WOLF_ADDR, 0x40, 0x40, 0, 2);
    r = (ptr->r0 >= 0x80) ? 0xFF : ptr->r0 * 2;
    g = (ptr->g0 >= 0x80) ? 0xFF : ptr->g0 * 2;
    b = (ptr->b0 >= 0x80) ? 0xFF : ptr->b0 * 2;
    r = g = b;
    fix = GU_RGBA(r, g, b, 0);
    PutAlphaBlendingEnable(GU_TRUE);
    PutBlendFunc(GU_ADD, GU_FIX, GU_FIX, fix, 0x00FFFFFF - fix);
    v[0].c = v[1].c = v[2].c = v[3].c = white;
    v[0].x = D_psp_08C629C8 + ptr->x0;
    v[0].y = D_psp_08C629CC + ptr->y0;
    v[1].x = D_psp_08C629C8 + ptr->x1;
    v[1].y = D_psp_08C629CC + ptr->y1;
    v[2].x = D_psp_08C629C8 + ptr->x2;
    v[2].y = D_psp_08C629CC + ptr->y2;
    v[3].x = D_psp_08C629C8 + ptr->x3;
    v[3].y = D_psp_08C629CC + ptr->y3;
    v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
    v[0].u = ptr->u0;
    v[0].v = ptr->v0;
    v[1].u = ptr->u1;
    v[1].v = ptr->v1;
    v[2].u = ptr->u2;
    v[2].v = ptr->v2;
    v[3].u = ptr->u3;
    v[3].v = ptr->v3;
    PutAlphaTestEnable(GU_FALSE);
    PutTextureMappingEnable(GU_TRUE);
    func_psp_08911AB8(0, 0, 0);
    func_psp_08910A80(
        v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
        GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 | GU_TEXTURE_32BITF);
    if (drawPolyline == true) {
        s32 color = magenta;
        DrawSolidLine(v[0].x, v[0].y, v[1].x, v[1].y, color);
        DrawSolidLine(v[1].x, v[1].y, v[3].x, v[3].y, color);
        DrawSolidLine(v[3].x, v[3].y, v[2].x, v[2].y, color);
        DrawSolidLine(v[2].x, v[2].y, v[0].x, v[0].y, color);
    }
    polysDrawn++;
    return 0;
}

s32 func_psp_089231F8(void* p) {
    POLY_GT4* ptr = p;
    u8 tpf;
    u8* clutPtr;
    s32 isSemiTrans;
    u8* texPtr;
    TVertex* v;

    clutPtr = NULL;
    isSemiTrans = isSemiTrans(ptr);
    D_psp_08C629C4 = ptr->tpage;
    tpf = getTPF(ptr->tpage);
    texPtr = GetTextureAddr(ptr->tpage);
    if (tpf != 2) {
        clutPtr = func_psp_0891B8F0(ptr->clut, tpf, 1);
    }
    unkInlineFunc2(texPtr, clutPtr, tpf);
    if (isSemiTrans(ptr)) {
        switch (getABR(ptr->tpage)) {
        case 0:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
            break;
        case 1:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
            break;
        case 2:
            func_psp_08911B84(
                1, GU_REVERSE_SUBTRACT, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
            break;
        case 3:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFF404040, 0xFFFFFFFF);
            break;
        default:
            func_psp_08911B84(
                0, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
            break;
        }
    } else {
        func_psp_08911B84(0, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
    }
    v = (TVertex*)func_psp_089104B4(0x18);
    if (isFlatShaded(ptr)) {
        v[0].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
        v[1].c = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
        v[2].c = GU_RGBA(ptr->r2, ptr->g2, ptr->b2, 0x80);
        v[3].c = GU_RGBA(ptr->r3, ptr->g3, ptr->b3, 0x80);
    } else {
        v[0].c = v[1].c = v[2].c = v[3].c = 0xFFFFFFFF;
    }
    v[0].x = D_psp_08C629C8 + ptr->x0;
    v[0].y = D_psp_08C629CC + ptr->y0;
    v[1].x = D_psp_08C629C8 + ptr->x1;
    v[1].y = D_psp_08C629CC + ptr->y1;
    v[2].x = D_psp_08C629C8 + ptr->x2;
    v[2].y = D_psp_08C629CC + ptr->y2;
    v[3].x = D_psp_08C629C8 + ptr->x3;
    v[3].y = D_psp_08C629CC + ptr->y3;
    v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
    v[0].u = ptr->u0;
    v[0].v = ptr->v0;
    v[1].u = ptr->u1;
    v[1].v = ptr->v1;
    v[2].u = ptr->u2;
    v[2].v = ptr->v2;
    v[3].u = ptr->u3;
    v[3].v = ptr->v3;
    if (D_psp_08C62A40 == SUB_BUF_OFF) {
        func_psp_0891D9F4(v, 4);
    }
    if (D_psp_08C62A40 == SUB_BUF_TEMP) {
        PutDitheringEnable(GU_FALSE);
        if (isSemiTrans) {
            PutAlphaTestEnable(GU_TRUE);
            PutAlphaFunc(GU_ALWAYS, 0, 0);
            PutTextureMappingEnable(GU_TRUE);
            func_psp_08911AB8(0, 0, 0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        } else {
            func_psp_0891214C(D_psp_089464F0, 0, 0, 0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        }
    } else if (tpf == 2 && !isSemiTrans) {
        if ((ptr->x1 - ptr->x0) != 1) {
            func_psp_08911F24(0, D_psp_089464F0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        } else {
            func_psp_08911F24(0, D_psp_089464F0);
            func_psp_08911B7C();
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        }
    } else {
        if (ptr->u0 > ptr->u1) {
            v[0].u++;
            v[1].u++;
            v[2].u++;
            v[3].u++;
        }
        if (ptr->v0 > ptr->v2) {
            v[0].v++;
            v[1].v++;
            v[2].v++;
            v[3].v++;
        }
        if (isSemiTrans) {
            PutAlphaTestEnable(GU_TRUE);
            PutAlphaFunc(GU_ALWAYS, 0, 0);
            PutTextureMappingEnable(GU_TRUE);
            func_psp_08911AB8(0, 0, 0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        } else {
            func_psp_0891214C(D_psp_089464F0, 0, 0, 0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        }
    }
    if (drawPolyline == true) {
        s32 color = green;
        DrawSolidLine(v[0].x, v[0].y, v[1].x, v[1].y, color);
        DrawSolidLine(v[1].x, v[1].y, v[3].x, v[3].y, color);
        DrawSolidLine(v[3].x, v[3].y, v[2].x, v[2].y, color);
        DrawSolidLine(v[2].x, v[2].y, v[0].x, v[0].y, color);
    }
    polysDrawn++;
    return 0;
}

s32 DrawPolyGT4(void* p) {
    POLY_GT4* ptr = p;
    u8 tpf;
    s32 u0;
    s32 dx0, dy0;
    s32 dx1, dy1;
    s32 i;
    s32 x0;
    s32 dx;
    u8* texPtr;
    u8* clutPtr;
    TVertex* v;
    s32 isSemiTrans;

    clutPtr = NULL;
    isSemiTrans = isSemiTrans(ptr);
    if (LOW(((POLY_GT4*)p)->x0) == 0 && LOW(((POLY_GT4*)p)->x1) == 0 &&
        LOW(((POLY_GT4*)p)->x2) == 0 && LOW(((POLY_GT4*)p)->x3) == 0) {
        return 0;
    }
    D_psp_08C629C4 = ptr->tpage;
    if (getTPF(ptr->tpage) == 2 && (ptr->tpage & 0x1F) != 0x10) {
        if (ptr->u1 == 0xFF && ptr->u0 == 0) {
            POLY_GT4 poly;
            poly.tag = ptr->tag;
            poly.len = ptr->len;
            poly.r0 = ptr->r0;
            poly.g0 = ptr->g0;
            poly.b0 = ptr->b0;
            poly.code = ptr->code;
            poly.x0 = ptr->x0;
            poly.y0 = ptr->y0;
            poly.u0 = ptr->u0;
            poly.v0 = ptr->v0;
            poly.clut = ptr->clut;
            poly.r1 = ptr->r1;
            poly.g1 = ptr->g1;
            poly.b1 = ptr->b1;
            poly.p1 = ptr->p1;
            poly.x1 = ptr->x1;
            poly.y1 = ptr->y1;
            poly.u1 = ptr->u1;
            poly.v1 = ptr->v1;
            poly.tpage = ptr->tpage;
            poly.r2 = ptr->r2;
            poly.g2 = ptr->g2;
            poly.b2 = ptr->b2;
            poly.p2 = ptr->p2;
            poly.x2 = ptr->x2;
            poly.y2 = ptr->y2;
            poly.u2 = ptr->u2;
            poly.v2 = ptr->v2;
            poly.pad2 = ptr->pad2;
            poly.r3 = ptr->r3;
            poly.g3 = ptr->g3;
            poly.b3 = ptr->b3;
            poly.p3 = ptr->p3;
            poly.x3 = ptr->x3;
            poly.y3 = ptr->y3;
            poly.u3 = ptr->u3;
            poly.v3 = ptr->v3;
            poly.pad3 = ptr->pad3;

            dx0 = ((ptr->x1 - ptr->x0) + 1) / 4;
            dy0 = ((ptr->y1 - ptr->y0) + 1) / 4;
            dx1 = ((ptr->x3 - ptr->x2) + 1) / 4;
            dy1 = ((ptr->y3 - ptr->y2) + 1) / 4;
            for (i = 0; i < 4; i++) {
                poly.x0 = ptr->x0 + dx0 * i;
                poly.y0 = ptr->y0 + dy0 * i;
                poly.x1 = poly.x0 + dx0;
                poly.y1 = poly.y0 + dy0;
                poly.x2 = ptr->x2 + dx1 * i;
                poly.y2 = ptr->y2 + dy1 * i;
                poly.x3 = poly.x2 + dx1;
                poly.y3 = poly.y2 + dy1;
                poly.u0 = poly.u2 = 0;
                poly.u1 = poly.u3 = 0x3F;
                DrawPolyGT4(&poly);
                poly.tpage++;
            }
            return 0;
        }
        if (ptr->u1 == 0xF9 && ptr->u0 == 6) {
            POLY_GT4 poly;
            poly.tag = ptr->tag;
            poly.len = ptr->len;
            poly.r0 = ptr->r0;
            poly.g0 = ptr->g0;
            poly.b0 = ptr->b0;
            poly.code = ptr->code;
            poly.x0 = ptr->x0;
            poly.y0 = ptr->y0;
            poly.u0 = ptr->u0;
            poly.v0 = ptr->v0;
            poly.clut = ptr->clut;
            poly.r1 = ptr->r1;
            poly.g1 = ptr->g1;
            poly.b1 = ptr->b1;
            poly.p1 = ptr->p1;
            poly.x1 = ptr->x1;
            poly.y1 = ptr->y1;
            poly.u1 = ptr->u1;
            poly.v1 = ptr->v1;
            poly.tpage = ptr->tpage;
            poly.r2 = ptr->r2;
            poly.g2 = ptr->g2;
            poly.b2 = ptr->b2;
            poly.p2 = ptr->p2;
            poly.x2 = ptr->x2;
            poly.y2 = ptr->y2;
            poly.u2 = ptr->u2;
            poly.v2 = ptr->v2;
            poly.pad2 = ptr->pad2;
            poly.r3 = ptr->r3;
            poly.g3 = ptr->g3;
            poly.b3 = ptr->b3;
            poly.p3 = ptr->p3;
            poly.x3 = ptr->x3;
            poly.y3 = ptr->y3;
            poly.u3 = ptr->u3;
            poly.v3 = ptr->v3;
            poly.pad3 = ptr->pad3;

            x0 = ptr->x0;
            while (x0 < ptr->x1) {
                u0 = x0 % 0x40;
                dx = 0x40 - u0;
                if ((x0 + dx) > ptr->x1) {
                    dx = ptr->x1 - x0;
                }
                poly.x0 = poly.x2 = x0;
                poly.x1 = poly.x3 = x0 + dx;
                poly.u0 = poly.u2 = u0;
                poly.u1 = poly.u3 = (u0 + dx) - 1;
                DrawPolyGT4(&poly);
                poly.tpage++;
                x0 += dx;
            }
            return 0;
        }
    }
    if (ptr->tpage & 0xF000) {
        if ((ptr->tpage & 0xF000) == 0x4000) {
            return func_psp_08922C14(p);
        }
        if ((ptr->tpage & 0xF000) == 0x2000) {
            SPRT sprt;
            DrawSolidRect(ptr->x0, ptr->y0, ptr->x3 - ptr->x0,
                          ptr->y3 - ptr->y0, GU_RGBA(0, 0, 8, 0x80));
            sprt.u0 = ptr->u0;
            sprt.v0 = ptr->v0;
            sprt.w = ptr->x3 - ptr->x0;
            sprt.h = ptr->y3 - ptr->y0;
            sprt.x0 = ptr->x0;
            sprt.y0 = ptr->y0;
            sprt.r0 = sprt.g0 = sprt.b0 = 0x80;
            sprt.clut = ptr->clut;
            sprt.code = ptr->code;
            D_psp_08C629C4 &= 0x9FF;
            return func_psp_08920498(&sprt);
        }
        if ((ptr->tpage & 0xF000) == 0x1000) {
            return func_psp_089231F8(p);
        }
    }
    tpf = getTPF(ptr->tpage);
    texPtr = GetTextureAddr(ptr->tpage);
    if (tpf != 2) {
        clutPtr = func_psp_0891B8F0(ptr->clut, tpf, 1);
    }
    unkInlineFunc2(texPtr, clutPtr, tpf);
    if (isSemiTrans(ptr)) {
        switch (getABR(ptr->tpage)) {
        case 0:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
            break;
        case 1:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
            break;
        case 2:
            func_psp_08911B84(
                1, GU_REVERSE_SUBTRACT, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
            break;
        case 3:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFF404040, 0xFFFFFFFF);
            break;
        default:
            func_psp_08911B84(
                0, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
            break;
        }
    } else {
        func_psp_08911B84(0, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
    }
    v = (TVertex*)func_psp_089104B4(0x18);
    if (isFlatShaded(ptr)) {
        v[0].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
        v[1].c = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
        v[2].c = GU_RGBA(ptr->r2, ptr->g2, ptr->b2, 0x80);
        v[3].c = GU_RGBA(ptr->r3, ptr->g3, ptr->b3, 0x80);
    } else {
        v[0].c = v[1].c = v[2].c = v[3].c = 0xFFFFFFFF;
    }
    __asm__(
        ".set		push\n"      // save assembler option
        ".set		noreorder\n" // suppress reordering
        "lv.s		s700, 0xC(%1)\n"
        "vs2i.p		c710, c700\n"
        "vi2f.p		c300, c710, 16\n"
        "vadd.p		c300, c300, c410\n"
        "sv.s		s300, 0xC(%0)\n"
        "sv.s		s301, 0x10(%0)\n"
        "sv.s		s302, 0x14(%0)\n"
        "lv.s		s700, 0x18(%1)\n"
        "vs2i.p		c710, c700\n"
        "vi2f.p		c300, c710, 16\n"
        "vadd.p		c300, c300, c410\n"
        "sv.s		s300, 0x24(%0)\n"
        "sv.s		s301, 0x28(%0)\n"
        "sv.s		s302, 0x2C(%0)\n"
        "lv.s		s700, 0x24(%1)\n"
        "vs2i.p		c710, c700\n"
        "vi2f.p		c300, c710, 16\n"
        "vadd.p		c300, c300, c410\n"
        "sv.s		s300, 0x3C(%0)\n"
        "sv.s		s301, 0x40(%0)\n"
        "sv.s		s302, 0x44(%0)\n"
        "lv.s		s700, 0x30(%1)\n"
        "vs2i.p		c710, c700\n"
        "vi2f.p		c300, c710, 16\n"
        "vadd.p		c300, c300, c410\n"
        "sv.s		s300, 0x54(%0)\n"
        "sv.s		s301, 0x59(%0)\n"
        "sv.s		s302, 0x5E(%0)\n"
        "lbu		$4, 0x10(%1)\n"
        "lbu		$5, 0x11(%1)\n"
        "mtv		$4, s610\n"
        "mtv		$5, s611\n"
        "vi2f.p		c620, c610, 0\n"
        "sv.s		s620, 0(%0)\n"
        "sv.s		s621, 4(%0)\n"
        "lbu		$4, 0x1C(%1)\n"
        "lbu		$5, 0x1D(%1)\n"
        "mtv		$4, s610\n"
        "mtv		$5, s611\n"
        "vi2f.p		c620, c610, 0\n"
        "sv.s		s620, 0x18(%0)\n"
        "sv.s		s621, 0x1C(%0)\n"
        "lbu		$4, 0x28(%1)\n"
        "lbu		$5, 0x29(%1)\n"
        "mtv		$4, s610\n"
        "mtv		$5, s611\n"
        "vi2f.p		c620, c610, 0\n"
        "sv.s		s620, 0x30(%0)\n"
        "sv.s		s621, 0x34(%0)\n"
        "lbu		$4, 0x34(%1)\n"
        "lbu		$5, 0x35(%1)\n"
        "mtv		$4, s610\n"
        "mtv		$5, s611\n"
        "vi2f.p		c620, c610, 0\n"
        "sv.s		s620, 0x48(%0)\n"
        "sv.s		s621, 0x4D(%0)\n"
        ".set		pop\n" // suppress reordering
        : "+r"(v)
        : "r"(ptr));

    if (D_psp_08C62A40 == SUB_BUF_OFF) {
        func_psp_0891D9F4(v, 4);
    }
    if (D_psp_08C62A40 == SUB_BUF_TEMP) {
        PutDitheringEnable(GU_FALSE);
        if (isSemiTrans) {
            func_psp_08912070(D_psp_089464F0, 0, 0, 0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
            func_psp_089120E4();
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        } else {
            func_psp_0891214C(D_psp_089464F0, 0, 0, 0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        }
    } else if (tpf == 2 && !isSemiTrans) {
        if ((ptr->x1 - ptr->x0) != 1) {
            func_psp_08911F24(0, D_psp_089464F0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        } else {
            func_psp_08911F24(0, D_psp_089464F0);
            func_psp_08911B7C();
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        }
    } else {
        if (ptr->u0 > ptr->u1) {
            v[0].u++;
            v[1].u++;
            v[2].u++;
            v[3].u++;
        }
        if (ptr->v0 > ptr->v2) {
            v[0].v++;
            v[1].v++;
            v[2].v++;
            v[3].v++;
        }
        if (isSemiTrans) {
            func_psp_08912070(D_psp_089464F0, 0, 0, 0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
            func_psp_089120E4();
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        } else {
            func_psp_0891214C(D_psp_089464F0, 0, 0, 0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        }
    }
    if (drawPolyline == true) {
        s32 color = green;
        DrawSolidLine(v[0].x, v[0].y, v[1].x, v[1].y, color);
        DrawSolidLine(v[1].x, v[1].y, v[3].x, v[3].y, color);
        DrawSolidLine(v[3].x, v[3].y, v[2].x, v[2].y, color);
        DrawSolidLine(v[2].x, v[2].y, v[0].x, v[0].y, color);
    }
    polysDrawn++;
    return 0;
}

s32 DrawTile(void* p) {
    TILE* ptr = p;
    Vertex v[4];
    u8 var_s1;

    if (ptr->w == 0 || ptr->h == 0) {
        return 0;
    }
    if (D_psp_08C62A40 == SUB_BUF_TEMP) {
        return 0;
    }
    if (isSemiTrans(ptr)) {
        var_s1 = 0x80;
        if (getABR(D_psp_08C629C4) == 2) {
            var_s1 = (ptr->b0 + ptr->g0 + ptr->r0) / 3;
        }
        func_psp_089113A8(getABR(D_psp_08C629C4), var_s1);
    } else {
        func_psp_089113A8(-1, 0x80);
    }
    v[0].x = D_psp_08C629C8 + ptr->x0;
    v[0].y = D_psp_08C629CC + ptr->y0;
    v[1].x = D_psp_08C629C8 + ptr->x0 + ptr->w;
    v[1].y = D_psp_08C629CC + ptr->y0;
    v[2].x = D_psp_08C629C8 + ptr->x0;
    v[2].y = D_psp_08C629CC + ptr->y0 + ptr->h;
    v[3].x = D_psp_08C629C8 + ptr->x0 + ptr->w;
    v[3].y = D_psp_08C629CC + ptr->y0 + ptr->h;
    v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
    v[0].c = v[1].c = v[2].c = v[3].c =
        GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    if (D_psp_08C62A40 == SUB_BUF_OFF) {
        ApplyScreenAdjustmentsPoly(v, 4);
    }
    func_psp_08912008();
    func_psp_08910A80(v, 4, sizeof(Vertex), GU_TRIANGLE_STRIP,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    func_psp_0891B1F8(v[0].x, v[0].y, v[1].x, v[1].y, magenta);
    return 0;
}

s32 DrawLineF2(void* p) {
    LINE_F2* ptr = p;
    Vertex v[2];

    v[0].x = ptr->x0;
    v[0].y = ptr->y0;
    v[1].x = ptr->x1;
    v[1].y = ptr->y1;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    v[0].z = v[1].z = 1.0f;
    v[0].c = v[1].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    if (D_psp_08C62A40 == SUB_BUF_OFF) {
        ApplyScreenAdjustmentsLine(v, 2);
    }
    func_psp_08912008();
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

s32 DrawLineF4(void* p) {
    LINE_F4* ptr = p;
    Vertex v[2];

    v[0].z = v[1].z = 1.0f;
    v[0].c = v[1].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    func_psp_08912008();
    v[0].x = ptr->x0;
    v[0].y = ptr->y0;
    v[1].x = ptr->x1;
    v[1].y = ptr->y1;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    if (D_psp_08C62A40 == SUB_BUF_OFF) {
        ApplyScreenAdjustmentsLine(v, 2);
    }
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    v[0].x = v[1].x;
    v[0].y = v[1].y;
    v[1].x = ptr->x2;
    v[1].y = ptr->y2;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    if (D_psp_08C62A40 == SUB_BUF_OFF) {
        ApplyScreenAdjustmentsLine(v, 2);
    }
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    v[0].x = v[1].x;
    v[0].y = v[1].y;
    v[1].x = ptr->x3;
    v[1].y = ptr->y3;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    if (D_psp_08C62A40 == SUB_BUF_OFF) {
        ApplyScreenAdjustmentsLine(v, 2);
    }
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

s32 DrawLineG2(void* p) {
    LINE_G2* ptr = p;
    Vertex v[2];

    v[0].x = ptr->x0;
    v[0].y = ptr->y0;
    v[1].x = ptr->x1;
    v[1].y = ptr->y1;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    v[0].z = v[1].z = 1.0f;
    v[0].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    v[1].c = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
    if (D_psp_08C62A40 == SUB_BUF_OFF) {
        ApplyScreenAdjustmentsLine(v, 2);
    }
    if (isSemiTrans(ptr)) {
        func_psp_089113A8(getABR(D_psp_08C629C4), 0x80);
    } else {
        func_psp_089113A8(-1, 0x80);
    }
    func_psp_08912008();
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

s32 DrawLineG4(void* p) {
    LINE_G4* ptr = p;
    Vertex v[2];

    v[0].z = v[1].z = 1.0f;
    func_psp_08912008();
    v[0].x = ptr->x0;
    v[0].y = ptr->y0;
    v[1].x = ptr->x1;
    v[1].y = ptr->y1;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    v[0].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    v[1].c = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
    if (D_psp_08C62A40 == SUB_BUF_OFF) {
        ApplyScreenAdjustmentsLine(v, 2);
    }
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    v[0].x = v[1].x;
    v[0].y = v[1].y;
    v[1].x = ptr->x2;
    v[1].y = ptr->y2;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    v[0].c = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
    v[1].c = GU_RGBA(ptr->r2, ptr->g2, ptr->b2, 0x80);
    if (D_psp_08C62A40 == SUB_BUF_OFF) {
        ApplyScreenAdjustmentsLine(v, 2);
    }
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    v[0].x = v[1].x;
    v[0].y = v[1].y;
    v[1].x = ptr->x3;
    v[1].y = ptr->y3;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    v[0].c = GU_RGBA(ptr->r2, ptr->g2, ptr->b2, 0x80);
    v[1].c = GU_RGBA(ptr->r3, ptr->g3, ptr->b3, 0x80);
    if (D_psp_08C62A40 == SUB_BUF_OFF) {
        ApplyScreenAdjustmentsLine(v, 2);
    }
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

void SetLineG2(LINE_G2* p) { setLineG2(p); }

void SetPolyG4(POLY_G4* p) { setPolyG4(p); }

void SetPolyGT3(POLY_GT3* p) { setPolyGT3(p); }

void SetPolyGT4(POLY_GT4* p) { setPolyGT4(p); }

void SetSprt(SPRT* p) { setSprt(p); }

void SetSprt16(SPRT_16* p) { setSprt16(p); }

void SetTile(TILE* p) { setTile(p); }
