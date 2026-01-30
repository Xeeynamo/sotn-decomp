// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include <game_psp.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspgu.h>
#include <pspgecmd.h>

typedef struct {
    s32* listStart;
    s32* listEnd;
    s32 unk8;
    s32 count;
    s32 capacity;
    s32 unk14;
    s32 unk18;
} DispListContext;

// BSS
static s32 D_psp_08B1F1D0[19][0x20];
static u8 D_psp_08B1F1C4[0xC] UNUSED;

static u8* currClutPtr;
static s32 currTPF;
static u8* currTexPtr;

static s32 D_psp_08B1F1B4; // unk
static s32 D_psp_08B1F1B0; // unk
static s32 pktCount;
static s32 pktCapacity;
static s32* pktStart;
static s32 D_psp_08B1F1A0; // unk
static s32* pktList;
static s32 currDispListIdx;

static s32* globalParamPktList;

static DispListContext contexts[3];
static s32 genericDispList[2][0x20000];
s32 D_psp_089B7140[2][0xD000]; // unknown display list
static s32 globalParamDispList[2][0x100];
static s32 immDispList[0x100];

extern s32 g_frameBufIdx;

void func_psp_08910088(void);
u32 FinishDispList(s32, bool);
void ClearContexts(void);
void ClearContext(DispListContext*);
void RestoreDispList(s32);
void SaveCurrDispList(void);
void PutAmbient(char, char, char, char);

void ClearDispLists(void) {
    func_psp_08910088();
    contexts[0].listStart = NULL;
    contexts[0].listEnd = NULL;
    contexts[1].listStart = NULL;
    contexts[1].listEnd = NULL;
    contexts[2].listStart = NULL;
    contexts[2].listEnd = NULL;
    currDispListIdx = -1;
    genericDispList[g_frameBufIdx][0] = GE_SET_RET();
    globalParamPktList = globalParamDispList[g_frameBufIdx];
    PutAmbient(0xFF, 0x40, 0x40, 0x40);
}

static void func_psp_0890FCD0(void) {
    sceGuStart(GU_IMMEDIATE, immDispList, sizeof(immDispList));
    sceGuDrawBuffer(GU_PSM_5551, GU_VRAM_BP_0, GU_VRAM_WIDTH);
    sceGuDispBuffer(GU_SCR_WIDTH, GU_SCR_HEIGHT, GU_VRAM_BP_1, GU_VRAM_WIDTH);
    sceGuDepthBuffer(GU_VRAM_BP_2, GU_VRAM_WIDTH);
    sceGuOffset(GU_SCR_OFFSETX, GU_SCR_OFFSETY);
    sceGuViewport(0x800, 0x800, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    sceGuScissor(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuDepthRange(1, 0xFFFF);
    sceGuColorFunc(GU_ALWAYS, 0, 0xFFFFFF);
    sceGuAlphaFunc(GU_GREATER, 1, 0xFF);
    sceGuStencilOp(GU_KEEP, GU_KEEP, GU_REPLACE);
    sceGuStencilFunc(GU_ALWAYS, 0x80, 0x80);
    sceGuDepthFunc(GU_LEQUAL);
    sceGuDepthMask(GU_TRUE);
    sceGuDisable(GU_BLEND);
    sceGuBlendFunc(GU_ADD, GU_FIX, GU_FIX, 0x00000000, 0xFFFFFFFF);
    sceGuBlendFunc(
        GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0x00000000, 0x00000000);
    sceGuBlendFunc(
        GU_REVERSE_SUBTRACT, GU_SRC_ALPHA, GU_FIX, 0x00000000, 0xFFFFFFFF);
    sceGuBlendFunc(GU_ADD, GU_SRC_COLOR, GU_FIX, 0x00000000, 0x00000000);
    sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_FIX, 0x00000000, 0xFFFFFFFF);
    sceGuEnable(GU_BLEND);
    sceGuDisable(GU_COLOR_LOGIC_OP);
    sceGuShadeModel(GU_FLAT);
    sceGuClearColor(0x00000000);
    sceGuClearStencil(0);
    sceGuClearDepth(0xFFFF);
    sceGuClear(GU_CLEAR_ALL);
    sceGuTexOffset(0.0f, 0.0f);
    sceGuFinish();
}

void func_psp_0890FE98(void) {
    sceGuStart(GU_IMMEDIATE, immDispList, sizeof(immDispList));
    sceGuCallList(globalParamDispList[g_frameBufIdx]);
    sceGuCallList(genericDispList[g_frameBufIdx]);
    sceGuCallList(D_psp_089B7140[g_frameBufIdx]);
    sceGuFinish();
}

s32 func_psp_0890FF2C(void) {
    s32 ret;

    ret = sceGuFinish();
    *globalParamPktList++ = GE_SET_RET();
    FinishDispList(1, true);
    return ret;
}

void func_psp_0890FF84(void) {
    sceGuStart(
        GU_CALL, D_psp_089B7140[g_frameBufIdx], sizeof(D_psp_089B7140[0]));
    sceGuClearColor(0xFFFFFFFF);
    sceGuDisable(GU_COLOR_TEST);
    sceGuDisable(GU_ALPHA_TEST);
    sceGuDisable(GU_STENCIL_TEST);
    sceGuDisable(GU_COLOR_LOGIC_OP);
    sceGuTexWrap(GU_CLAMP, GU_CLAMP);
    sceGuTexFilter(GU_NEAREST, GU_NEAREST);
    sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
    sceGuShadeModel(GU_FLAT);
    sceGuDisable(GU_LIGHTING);
    sceGuDisable(GU_FOG);
    sceGuDisable(GU_CULL_FACE);
    sceGuDisable(GU_CLIP_PLANES);
}

void func_psp_08910044(void) {
    func_psp_0890FCD0();
    g_frameBufIdx = 0;
    D_psp_08B1F1A0 = 0;
    pktList = NULL;
    currDispListIdx = -1;
    ClearContexts();
}

static void func_psp_08910088(void) { D_psp_08B1F1B0 = -1; }

static u32 FinishDispList(s32 idx, bool endList) {
    DispListContext* ctx;
    s32 prevIdx = -1;
    u32 count;

    if (currDispListIdx != idx) {
        ctx = &contexts[idx];
        if (ctx->listStart != NULL) {
            if (currDispListIdx != -1) {
                prevIdx = currDispListIdx;
                SaveCurrDispList();
            }
            RestoreDispList(idx);
            if (endList) {
                *pktList++ = GE_SET_RET();
                *pktList++ = GE_SET_NOP();
            }
            count = ((u32)pktList - (u32)pktStart) / 4;
            pktCount = count;
            ClearContext(ctx);
            if (prevIdx != -1) {
                RestoreDispList(prevIdx);
            }
        }
    } else {
        currDispListIdx = -1;
        if (endList) {
            *pktList++ = GE_SET_RET();
            *pktList++ = GE_SET_NOP();
        }
        count = ((u32)pktList - (u32)pktStart) / 4;
        pktCount = count;
    }
    return count;
}

static void InitDispList(s32* ptr, s32 capacity, s32 idx) {
    if (idx != currDispListIdx && currDispListIdx != -1) {
        SaveCurrDispList();
    }
    pktStart = ptr;
    pktCapacity = capacity;
    pktList = ptr;
    currDispListIdx = idx;
}

void SetCurrDispList(s32 idx) {
    s32 capacity;
    s32* ptr;

    switch (idx) {
    case 0:
        capacity = 0x100;
        ptr = globalParamDispList[g_frameBufIdx];
        break;
    case 1:
        capacity = 0x20000;
        ptr = genericDispList[g_frameBufIdx];
        break;
    }
    if (idx != currDispListIdx) {
        if (contexts[idx].listStart != NULL) {
            RestoreDispList(idx);
        } else {
            InitDispList(ptr, capacity, idx);
        }
    }
}

static void ClearContexts(void) {
    memset(contexts, 0, sizeof(DispListContext) * 3);
}

static void ClearContext(DispListContext* ctx) {
    memset(ctx, 0, sizeof(DispListContext));
}

static void RestoreDispList(s32 idx) {
    DispListContext* ctx;

    if (idx != -1) {
        ctx = &contexts[idx];
        pktStart = ctx->listStart;
        pktCapacity = ctx->capacity;
        pktCount = ctx->count;
        D_psp_08B1F1A0 = ctx->unk8;
        pktList = ctx->listEnd;
        D_psp_08B1F1B0 = ctx->unk14;
        D_psp_08B1F1B4 = ctx->unk18;
        ClearContext(ctx);
        currDispListIdx = idx;
    }
}

static void SaveCurrDispList(void) {
    DispListContext* ctx;

    if (currDispListIdx != -1) {
        ctx = &contexts[currDispListIdx];
        ctx->listStart = pktStart;
        ctx->capacity = pktCapacity;
        ctx->count = pktCount;
        ctx->unk8 = D_psp_08B1F1A0;
        ctx->listEnd = pktList;
        ctx->unk14 = D_psp_08B1F1B0;
        ctx->unk18 = D_psp_08B1F1B4;
    }
}

s32* GetMemory(int size) {
    s32* prev = pktList;
    pktList += size;
    return prev;
}

s32* func_psp_089104B4(int size) {
    s32* temp_a2;
    s32* temp_v0;

    temp_v0 = GetMemory(2);
    temp_a2 = pktList;
    pktList += size;
    *temp_v0++ = GE_SET_BASE_BASE8(pktList);
    *temp_v0++ = GE_SET_JUMP_ADDR24(pktList);
    return temp_a2;
}

void PutShadeModel(int model) { *pktList++ = GE_SET_SHADE(model); }

void PutLightingEnable(int lte) { *pktList++ = GE_SET_LTE(lte); }

void PutClippingEnable(int cle) { *pktList++ = GE_SET_CLE(cle); }

void PutPrimitiveCullingEnable(int bce) { *pktList++ = GE_SET_BCE(bce); }

void PutTextureMappingEnable(int tme) { *pktList++ = GE_SET_TME(tme); }

void PutFoggingEnable(int fge) { *pktList++ = GE_SET_FGE(fge); }

void PutDitheringEnable(int dte) { *pktList++ = GE_SET_DTE(dte); }

void PutAlphaBlendingEnable(int abe) { *pktList++ = GE_SET_ABE(abe); }

void PutAlphaTestEnable(int ate) { *pktList++ = GE_SET_ATE(ate); }

void PutAlphaFunc(int atf, int aref, int amask) {
    *pktList++ = GE_SET_ATEST(atf, aref, amask);
}

void PutDepthFunc(int zte) { *pktList++ = GE_SET_ZTE(zte); }

void PutStencilTestEnable(int ste) { *pktList++ = GE_SET_STE(ste); }

void PutAntiAliasEnable(int aae) { *pktList++ = GE_SET_AAE(aae); }

void PutColorTestEnable(int cte) { *pktList++ = GE_SET_CTE(cte); }

void PutDepthMask(int zmask) { *pktList++ = GE_SET_ZMSK((1 - zmask) & 1); }

void PutTexWrap(int uwrap, int vwrap) {
    *pktList++ = GE_SET_TWRAP(uwrap, vwrap);
}

void PutBlendFunc(int equ, int asel, int bsel, int afix, int bfix) {
    *pktList++ = GE_SET_BLEND(asel, bsel, equ);
    *pktList++ = GE_SET_FIXA_RGB24(afix);
    *pktList++ = GE_SET_FIXB_RGB24(bfix);
}

void PutScissorRect(int x1, int y1, int x2, int y2) {
    *pktList++ = GE_SET_SCISSOR1(x1, y1);
    *pktList++ = GE_SET_SCISSOR2(x2, y2);
}

void PutOffset(int x, int y) {
    *pktList++ = GE_SET_OFFSETX(x);
    *pktList++ = GE_SET_OFFSETY(y);
}

void PutTexFilter(int min, int mag) { *pktList++ = GE_SET_TFILTER(min, mag); }

void PutAmbient(char a, char r, char b, char g) {
    *globalParamPktList++ = GE_SET_AC(r, g, b);
    *globalParamPktList++ = GE_SET_AA(a);
}

void PutTexFunc(int func, int component, int colordoulbe) {
    *pktList++ = GE_SET_TFUNC(func, component, colordoulbe);
}

void PutDrawBuffer(int fbp, int fbw) {
    *pktList++ = GE_SET_FBP_ADDR24(fbp);
    *pktList++ = GE_SET_FBW_BASE8(fbw, fbp);
}

s32 func_psp_08910A80(
    s32* vertices, u32 nVerts, u32 vertexSize, s32 primType, s32 vType) {
    s32* temp_s1;
    s32* temp_s2;
    s32* temp_v0;
    s32* temp_a1;
    s32 i;

    *pktList++ = GE_SET_VTYPE(vType);
    temp_s2 = GetMemory(2);
    *pktList++ = GE_SET_PRIM(nVerts, primType);

    temp_s1 = GetMemory(2);
    temp_v0 = GetMemory((vertexSize * nVerts) / 4);

    *temp_s1++ = GE_SET_BASE_BASE8(pktList);
    *temp_s1++ = GE_SET_JUMP_ADDR24(pktList);

    temp_a1 = temp_v0;
    for (i = (vertexSize * nVerts) / 4; i > 0; i--) {
        *temp_a1++ = *vertices++;
    }

    *temp_s2++ = GE_SET_BASE_BASE8(temp_v0);
    *temp_s2++ = GE_SET_VADR_ADDR24(temp_v0);
    return 2;
}

s32 func_psp_08910C74(
    s32* vertices, u32 nVerts, u32 vertexSize, s32 primType, s32 vType) {
    *pktList++ = GE_SET_VTYPE(vType);
    *pktList++ = GE_SET_BASE_BASE8(vertices);
    *pktList++ = GE_SET_VADR_ADDR24(vertices);
    *pktList++ = GE_SET_PRIM(nVerts, primType);
    return 2;
}

void func_psp_08910D28(void) {
    currTexPtr = NULL;
    currTPF = 0;
    currClutPtr = NULL;
}

s32 func_psp_08910D44(u8* texPtr, u8* clutPtr, s32 tpf) {
    int formats[] = {GU_PSM_T4, GU_PSM_T8, GU_PSM_5551};
    int tbw[] = {0x100, 0x80, 0x40};

    if (currTexPtr == texPtr && currTPF == tpf) {
        texPtr = NULL;
    }
    if (currClutPtr == clutPtr) {
        clutPtr = NULL;
    }
    if (clutPtr != NULL) {
        *pktList++ = GE_SET_CLUT(GU_PSM_5551, 0, 0xFF, 0);
        *pktList++ = GE_SET_CBP_ADDR24(clutPtr);
        *pktList++ = GE_SET_CBW_BASE8(clutPtr);
        if (tpf == 1) {
            *pktList = GE_SET_CLOAD(16);
        } else {
            *pktList = GE_SET_CLOAD(1);
        }
        pktList++;
        currClutPtr = clutPtr;
    }
    if (texPtr != NULL) {
        *pktList++ = GE_SET_TMODE(GU_TEXBUF_NORMAL, GU_SINGLE_CLUT, 0);
        *pktList++ = GE_SET_TPF(formats[tpf], 0);
        *pktList++ = GE_SET_TBP0_ADDR24(texPtr);
        *pktList++ = GE_SET_TBW0_BASE8(tbw[tpf], texPtr);
        *pktList++ = GE_SET_TSIZE0(8 - tpf, 9);
        currTexPtr = texPtr;
        currTPF = tpf;
    }
    if (texPtr != NULL) {
        *pktList++ = GE_SET_TFLUSH();
        ResetGraph(1);
    }
    return (u32)clutPtr | (u32)texPtr;
}

s32 func_psp_08910FD8(
    u8* texPtr, u8* clutPtr, s32 tpf, s32 tbw, s32 tw, s32 th) {
    if (clutPtr != NULL) {
        *pktList++ = GE_SET_CLUT(GU_PSM_5551, 0, 0xFF, 0);
        *pktList++ = GE_SET_CBP_ADDR24(clutPtr);
        *pktList++ = GE_SET_CBW_BASE8(clutPtr);
        *pktList++ = GE_SET_CLOAD(16);
        currClutPtr = clutPtr;
    }
    if (texPtr != NULL) {
        *pktList++ = GE_SET_TMODE(GU_TEXBUF_NORMAL, GU_SINGLE_CLUT, 0);
        *pktList++ = GE_SET_TPF(tpf, 0);
        *pktList++ = GE_SET_TBP0_ADDR24(texPtr);
        *pktList++ = GE_SET_TBW0_BASE8(tbw, texPtr);
        *pktList++ = GE_SET_TSIZE0(tw, th);
        currTexPtr = texPtr;
        currTPF = tpf;
    }
    if (texPtr != NULL) {
        *pktList++ = GE_SET_TFLUSH();
        ResetGraph(1);
    }
    return (u32)clutPtr | (u32)texPtr;
}

s32 func_psp_089111C0(
    u8* texPtr, u8* clutPtr, s32 tpf, s32 tbw, s32 tw, s32 th) {
    if (clutPtr != NULL) {
        *pktList++ = GE_SET_CLUT(GU_PSM_8888, 0, 0xFF, 0);
        *pktList++ = GE_SET_CBP_ADDR24(clutPtr);
        *pktList++ = GE_SET_CBW_BASE8(clutPtr);
        *pktList++ = GE_SET_CLOAD(16);
        currClutPtr = clutPtr;
    }
    if (texPtr != NULL) {
        *pktList++ = GE_SET_TMODE(GU_TEXBUF_NORMAL, GU_SINGLE_CLUT, 0);
        *pktList++ = GE_SET_TPF(tpf, 0);
        *pktList++ = GE_SET_TBP0_ADDR24(texPtr);
        *pktList++ = GE_SET_TBW0_BASE8(tbw, texPtr);
        *pktList++ = GE_SET_TSIZE0(tw, th);
        currTexPtr = texPtr;
        currTPF = tpf;
    }
    if (texPtr != NULL) {
        *pktList++ = GE_SET_TFLUSH();
        ResetGraph(1);
    }
    return (u32)clutPtr | (u32)texPtr;
}

void func_psp_089113A8(s32 abr, u8 a) {
    switch (abr) {
    case 0:
        PutAlphaBlendingEnable(GU_TRUE);
        PutBlendFunc(GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
        break;
    case 1:
        PutAlphaBlendingEnable(GU_TRUE);
        PutBlendFunc(GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
        break;
    case 2:
        PutAlphaBlendingEnable(GU_TRUE);
        PutBlendFunc(
            GU_REVERSE_SUBTRACT, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
        break;
    case 3:
        PutAlphaBlendingEnable(GU_TRUE);
        PutBlendFunc(GU_ADD, GU_FIX, GU_FIX, 0xFF404040, 0xFFFFFFFF);
        break;
    default:
        PutAlphaBlendingEnable(GU_FALSE);
        break;
    }
}

static inline s32 Log2(u32 value) {
    if (value > 0x100) {
        return 9;
    } else if (value > 0x80) {
        return 8;
    } else if (value > 0x40) {
        return 7;
    } else if (value > 0x20) {
        return 6;
    } else if (value > 0x10) {
        return 5;
    } else if (value > 8) {
        return 4;
    } else {
        return 3;
    }
}

s32 func_psp_0891149C(u8* texPtr, s32 width, s32 height, u8* clutPtr, s32 tpf) {
    s32 formats[] = {GU_PSM_T4, GU_PSM_T8, GU_PSM_5551};
    bool var_v0;
    s32 tbw;
    s32 tw, th;

    var_v0 = false;
    if (clutPtr != NULL && currClutPtr != clutPtr) {
        *pktList++ = GE_SET_CLUT(GU_PSM_5551, 0, 0xFF, 0);
        *pktList++ = GE_SET_CBP_ADDR24(clutPtr);
        *pktList++ = GE_SET_CBW_BASE8(clutPtr);
        if (tpf == 1) {
            *pktList = GE_SET_CLOAD(16);
        } else {
            *pktList = GE_SET_CLOAD(1);
        }
        pktList++;
        currClutPtr = clutPtr;
    }
    if (texPtr != NULL && currTexPtr != texPtr) {
        tbw = 0;
        switch (tpf) {
        case 0:
            width = (width + 0x1F) & ~0x1F;
            tbw = width;
            break;
        case 1:
            width = (width + 0xF) & ~0xF;
            tbw = width;
            break;
        case 2:
            width = (width + 7) & ~7;
            tbw = width;
            break;
        }

        tw = Log2(width);
        th = Log2(height);

        *pktList++ = GE_SET_TMODE(GU_TEXBUF_NORMAL, GU_SINGLE_CLUT, 0);
        *pktList++ = GE_SET_TPF(formats[tpf], 0);
        *pktList++ = GE_SET_TBP0_ADDR24(texPtr);
        *pktList++ = GE_SET_TBW0_BASE8(tbw, texPtr);
        *pktList++ = GE_SET_TSIZE0(tw, th);
        currTexPtr = texPtr;
        currTPF = tpf;
        var_v0 = true;
    }
    if (var_v0) {
        *pktList++ = GE_SET_TFLUSH();
        ResetGraph(1);
    }
    return 0;
}

void func_psp_089117F4(s32 mode, s32 sx, s32 sy, s32 height, s32 width, s32 sbw,
                       u8* sbp, s32 dx, s32 dy, s32 dbw, u8* dbp) {
    *pktList++ = GE_SET_TSYNC();
    *pktList++ = GE_SET_XBP1_ADDR24(sbp);
    *pktList++ = GE_SET_XBW1_BASE8(sbw, sbp);
    *pktList++ = GE_SET_XPOS1(sx, sy);
    *pktList++ = GE_SET_XBP2_ADDR24(dbp);
    *pktList++ = GE_SET_XBW2_BASE8(dbw, dbp);
    *pktList++ = GE_SET_XPOS2(dx, dy);
    *pktList++ = GE_SET_XSIZE(height - 1, width - 1);
    *pktList++ = GE_SET_XSTART(mode == 3);
    *pktList++ = GE_SET_TSYNC();
}

s32 func_psp_08911990(s32 texPtr, s32 tbw) {

    s32 tw = (tbw == 0x100) ? 8 : 9;

    *pktList++ = GE_SET_TMODE(GU_TEXBUF_NORMAL, GU_SINGLE_CLUT, 0);
    *pktList++ = GE_SET_TPF(GU_PSM_5551, 0);
    *pktList++ = GE_SET_TBP0_ADDR24(texPtr);
    *pktList++ = GE_SET_TBW0_BASE8(tbw, texPtr);
    *pktList++ = GE_SET_TSIZE0(tw, 9);
    *pktList++ = GE_SET_TFLUSH();
    ResetGraph(1);
    currTexPtr = NULL;
    currTPF = 0;
    currClutPtr = NULL;
    return 0;
}

void func_psp_08911AB8(u8 r, u8 g, u8 b) {
    PutColorTestEnable(GU_TRUE);
    *pktList++ = GE_SET_CREF(r, g, b);
    *pktList++ = GE_SET_CMSK(0xFF, 0xFF, 0xFF);
    *pktList++ = GE_SET_CTEST(GU_NOTEQUAL);
}

void func_psp_08911B7C(void) { PutColorTestEnable(GU_FALSE); }

void func_psp_08911B84(
    int abe, int equ, int asel, int bsel, int afix, int bfix) {
    *pktList++ = GE_SET_ABE(abe);
    if (abe == GU_TRUE) {
        *pktList++ = GE_SET_BLEND(asel, bsel, equ);
        *pktList++ = GE_SET_FIXA_RGB24(afix);
        *pktList++ = GE_SET_FIXB_RGB24(bfix);
    }
}

void func_psp_08911C3C(u8 r, u8 g, u8 b) {
    s32* ptr;

    ptr = D_psp_08B1F1D0[0];
    *ptr++ = GE_SET_ATE(GU_FALSE);
    *ptr++ = GE_SET_TME(GU_TRUE);
    *ptr++ = GE_SET_CTE(GU_FALSE);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[1];
    *ptr++ = GE_SET_ATE(GU_FALSE);
    *ptr++ = GE_SET_TME(GU_TRUE);
    *ptr++ = GE_SET_CTE(GU_TRUE);
    *ptr++ = GE_SET_CREF(r, g, b);
    *ptr++ = GE_SET_CMSK(0xFF, 0xFF, 0xFF);
    *ptr++ = GE_SET_CTEST(GU_NOTEQUAL);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[2];
    *ptr++ = GE_SET_ATE(GU_TRUE);
    *ptr++ = GE_SET_ATEST(GU_GEQUAL, 1, 0xFF);
    *ptr++ = GE_SET_TME(GU_TRUE);
    *ptr++ = GE_SET_CTE(GU_FALSE);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[3];
    *ptr++ = GE_SET_ATE(GU_TRUE);
    *ptr++ = GE_SET_ATEST(GU_GEQUAL, 1, 0xFF);
    *ptr++ = GE_SET_TME(GU_TRUE);
    *ptr++ = GE_SET_CTE(GU_TRUE);
    *ptr++ = GE_SET_CREF(r, g, b);
    *ptr++ = GE_SET_CMSK(0xFF, 0xFF, 0xFF);
    *ptr++ = GE_SET_CTEST(GU_NOTEQUAL);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[4];
    *ptr++ = GE_SET_ATE(GU_TRUE);
    *ptr++ = GE_SET_ATEST(GU_EQUAL, 0, 0xFF);
    *ptr++ = GE_SET_ABE(GU_TRUE);
    *ptr++ = GE_SET_BLEND(GU_ONE_MINUS_SRC_ALPHA, GU_FIX, GU_ADD);
    *ptr++ = GE_SET_FIXA_RGB24(0x00000000);
    *ptr++ = GE_SET_FIXB_RGB24(0x00000000);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[5];
    *ptr++ = GE_SET_ATE(GU_FALSE);
    *ptr++ = GE_SET_TME(GU_TRUE);
    *ptr++ = GE_SET_CTE(GU_FALSE);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[6];
    *ptr++ = GE_SET_ATE(GU_FALSE);
    *ptr++ = GE_SET_TME(GU_TRUE);
    *ptr++ = GE_SET_CTE(GU_TRUE);
    *ptr++ = GE_SET_CREF(r, g, b);
    *ptr++ = GE_SET_CMSK(0xFF, 0xFF, 0xFF);
    *ptr++ = GE_SET_CTEST(GU_NOTEQUAL);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[7];
    *ptr++ = GE_SET_ATE(GU_TRUE);
    *ptr++ = GE_SET_ATEST(GU_GEQUAL, 1, 0xFF);
    *ptr++ = GE_SET_TME(GU_TRUE);
    *ptr++ = GE_SET_CTE(GU_FALSE);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[8];
    *ptr++ = GE_SET_ATE(GU_TRUE);
    *ptr++ = GE_SET_ATEST(GU_GEQUAL, 1, 0xFF);
    *ptr++ = GE_SET_TME(GU_TRUE);
    *ptr++ = GE_SET_CTE(GU_TRUE);
    *ptr++ = GE_SET_CREF(r, g, b);
    *ptr++ = GE_SET_CMSK(0xFF, 0xFF, 0xFF);
    *ptr++ = GE_SET_CTEST(GU_NOTEQUAL);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[9];
    *ptr++ = GE_SET_ATE(GU_TRUE);
    *ptr++ = GE_SET_ATEST(GU_EQUAL, 0, 0xFF);
    *ptr++ = GE_SET_ABE(GU_TRUE);
    *ptr++ = GE_SET_BLEND(GU_ONE_MINUS_SRC_ALPHA, GU_FIX, GU_ADD);
    *ptr++ = GE_SET_FIXA_RGB24(0x00000000);
    *ptr++ = GE_SET_FIXB_RGB24(0x00000000);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[10];
    *ptr++ = GE_SET_ATE(GU_FALSE);
    *ptr++ = GE_SET_CTE(GU_FALSE);
    *ptr++ = GE_SET_TME(GU_FALSE);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[15];
    *ptr++ = GE_SET_ABE(GU_TRUE);
    *ptr++ = GE_SET_BLEND(GU_FIX, GU_FIX, GU_ADD);
    *ptr++ = GE_SET_FIXA_RGB24(0xFF808080);
    *ptr++ = GE_SET_FIXB_RGB24(0xFF808080);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[16];
    *ptr++ = GE_SET_ABE(GU_TRUE);
    *ptr++ = GE_SET_BLEND(GU_FIX, GU_FIX, GU_ADD);
    *ptr++ = GE_SET_FIXA_RGB24(0xFFFFFFFF);
    *ptr++ = GE_SET_FIXB_RGB24(0xFFFFFFFF);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[17];
    *ptr++ = GE_SET_ABE(GU_TRUE);
    *ptr++ = GE_SET_BLEND(GU_FIX, GU_FIX, GU_REVERSE_SUBTRACT);
    *ptr++ = GE_SET_FIXA_RGB24(0xFFFFFFFF);
    *ptr++ = GE_SET_FIXB_RGB24(0xFFFFFFFF);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[18];
    *ptr++ = GE_SET_ABE(GU_TRUE);
    *ptr++ = GE_SET_BLEND(GU_FIX, GU_FIX, GU_ADD);
    *ptr++ = GE_SET_FIXA_RGB24(0xFF404040);
    *ptr++ = GE_SET_FIXB_RGB24(0xFFFFFFFF);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[11];
    *ptr++ = GE_SET_ABE(GU_FALSE);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[12];
    *ptr++ = GE_SET_ABE(GU_FALSE);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[13];
    *ptr++ = GE_SET_ABE(GU_FALSE);
    *ptr++ = GE_SET_RET();

    ptr = D_psp_08B1F1D0[14];
    *ptr++ = GE_SET_ABE(GU_FALSE);
    *ptr++ = GE_SET_RET();
}

void func_psp_08911F24(s32 arg0, s32 arg1) {
    *pktList++ = GE_SET_BASE_BASE8(D_psp_08B1F1D0[(arg0 * 2) + 5 + arg1]);
    *pktList++ = GE_SET_CALL_ADDR24(D_psp_08B1F1D0[(arg0 * 2) + 5 + arg1]);
}

void func_psp_08911FA0(void) {
    *pktList++ = GE_SET_BASE_BASE8(D_psp_08B1F1D0[9]);
    *pktList++ = GE_SET_CALL_ADDR24(D_psp_08B1F1D0[9]);
}

void func_psp_08912008(void) {
    *pktList++ = GE_SET_BASE_BASE8(D_psp_08B1F1D0[10]);
    *pktList++ = GE_SET_CALL_ADDR24(D_psp_08B1F1D0[10]);
}

void func_psp_08912070(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    *pktList++ = GE_SET_BASE_BASE8(D_psp_08B1F1D0[arg0 + 2]);
    *pktList++ = GE_SET_CALL_ADDR24(D_psp_08B1F1D0[arg0 + 2]);
}

void func_psp_089120E4(void) {
    *pktList++ = GE_SET_BASE_BASE8(D_psp_08B1F1D0[4]);
    *pktList++ = GE_SET_CALL_ADDR24(D_psp_08B1F1D0[4]);
}

void func_psp_0891214C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    *pktList++ = GE_SET_BASE_BASE8(D_psp_08B1F1D0[arg0]);
    *pktList++ = GE_SET_CALL_ADDR24(D_psp_08B1F1D0[arg0]);
}
