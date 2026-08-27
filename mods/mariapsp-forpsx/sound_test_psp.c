// SPDX-License-Identifier: AGPL-3.0-or-later

// enable like
//
// #if !defined(VERSION_PSP) || !defined(MARIA_SFX_DEBUG)
//
// // MarMain left out
//
// #else
//
// void MarSoundTest(void) {
//     MarPspSoundTest();
//     MARIA_PSP_NOP_8192
//     MARIA_PSP_NOP_512
//     MARIA_PSP_NOP_256
//     MARIA_PSP_NOP_128
//     MARIA_PSP_NOP_64
//     MARIA_PSP_NOP_8
//     MARIA_PSP_NOP_4
//     MARIA_PSP_NOP_2
//     MARIA_PSP_NOP_1
// }
// #endif

#if defined(VERSION_PSP) && defined(MARIA_SFX_DEBUG)

    #define MARIA_PSP_SFX_FIRST 0x601
    #define MARIA_PSP_SFX_LAST 0x90B
    #define MARIA_PSP_SFX_DATA ((Unkstruct_800BF554*)0x0918E070)
    #define MARIA_PSP_MENU_PRIMS 128
    #define MARIA_PSP_NOP_1 asm("nop");
    #define MARIA_PSP_NOP_2 MARIA_PSP_NOP_1 MARIA_PSP_NOP_1
    #define MARIA_PSP_NOP_4 MARIA_PSP_NOP_2 MARIA_PSP_NOP_2
    #define MARIA_PSP_NOP_8 MARIA_PSP_NOP_4 MARIA_PSP_NOP_4
    #define MARIA_PSP_NOP_16 MARIA_PSP_NOP_8 MARIA_PSP_NOP_8
    #define MARIA_PSP_NOP_32 MARIA_PSP_NOP_16 MARIA_PSP_NOP_16
    #define MARIA_PSP_NOP_64 MARIA_PSP_NOP_32 MARIA_PSP_NOP_32
    #define MARIA_PSP_NOP_128 MARIA_PSP_NOP_64 MARIA_PSP_NOP_64
    #define MARIA_PSP_NOP_256 MARIA_PSP_NOP_128 MARIA_PSP_NOP_128
    #define MARIA_PSP_NOP_512 MARIA_PSP_NOP_256 MARIA_PSP_NOP_256
    #define MARIA_PSP_NOP_1024 MARIA_PSP_NOP_512 MARIA_PSP_NOP_512
    #define MARIA_PSP_NOP_2048 MARIA_PSP_NOP_1024 MARIA_PSP_NOP_1024
    #define MARIA_PSP_NOP_4096 MARIA_PSP_NOP_2048 MARIA_PSP_NOP_2048
    #define MARIA_PSP_NOP_8192 MARIA_PSP_NOP_4096 MARIA_PSP_NOP_4096

static s16 s_MariaPspSfxPrimIndex = -1;
static s32 s_MariaPspSfxId = SFX_VO_MAR_8E6;
static char* MarPspAppendDec(char* out, s32 value) {
    if (value < 0) {
        *out++ = '-';
        value = -value;
    }
    if (value >= 100) {
        *out++ = '0' + value / 100;
        value %= 100;
        *out++ = '0' + value / 10;
    } else if (value >= 10) {
        *out++ = '0' + value / 10;
    }
    *out++ = '0' + value % 10;
    return out;
}

static char* MarPspAppendHex3(char* out, s32 value) {
    s32 shift;
    s32 digit;

    for (shift = 8; shift >= 0; shift -= 4) {
        digit = (value >> shift) & 0xF;
        *out++ = digit < 10 ? digit + '0' : digit + 'A' - 10;
    }
    return out;
}

static Primitive* MarPspDrawChar(Primitive* prim, s32* x, s32 y, char ch) {
    u8 glyph;

    if (ch == ' ') {
        *x += FONT_W;
        return prim;
    }
    if (prim == NULL) {
        return NULL;
    }
    glyph = ch - 0x20;
    prim->type = PRIM_SPRT;
    prim->tpage = 0x1E;
    prim->clut = PAL_UNK_196;
    prim->u0 = (glyph & 0xF) * FONT_W;
    prim->v0 = (glyph & 0xF0) >> 1;
    prim->u1 = FONT_W;
    prim->v1 = FONT_H;
    prim->x0 = *x;
    prim->y0 = y;
    prim->priority = 0x1F1;
    prim->drawMode = DRAW_DEFAULT;
    *x += FONT_W;
    return prim->next;
}

static void MarPspDrawMenu(char* text) {
    Primitive* prim;
    s32 x = 8;
    s32 y = 8;

    if (s_MariaPspSfxPrimIndex < 0) {
        return;
    }
    prim = &g_PrimBuf[s_MariaPspSfxPrimIndex];
    prim->type = PRIM_TILE;
    prim->r0 = prim->g0 = prim->b0 = 0x10;
    prim->x0 = 4;
    prim->y0 = 4;
    prim->u0 = 248;
    prim->v0 = 64;
    prim->priority = 0x1F0;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;

    while (*text != 0) {
        if (*text == '\n') {
            x = 8;
            y += 10;
        } else {
            prim = MarPspDrawChar(prim, &x, y, *text);
        }
        text++;
    }
    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

static void MarPspSoundTest(void) {
    char* out = (char*)mar_80175958;
    Unkstruct_800BF554* metadata;
    u16 repeat = g_pads[0].repeat;
    u16 tapped = g_pads[0].tapped;

    if (s_MariaPspSfxPrimIndex < 0) {
        s_MariaPspSfxPrimIndex =
            g_api.AllocPrimitives(PRIM_SPRT, MARIA_PSP_MENU_PRIMS);
        if (s_MariaPspSfxPrimIndex < 0) {
            return;
        }
    }

    if (repeat & PAD_UP) {
        s_MariaPspSfxId++;
    }
    if (repeat & PAD_DOWN) {
        s_MariaPspSfxId--;
    }
    if (tapped & PAD_RIGHT) {
        s_MariaPspSfxId += 0x10;
    }
    if (tapped & PAD_LEFT) {
        s_MariaPspSfxId -= 0x10;
    }
    if (s_MariaPspSfxId > MARIA_PSP_SFX_LAST) {
        s_MariaPspSfxId = MARIA_PSP_SFX_FIRST;
    }
    if (s_MariaPspSfxId < MARIA_PSP_SFX_FIRST) {
        s_MariaPspSfxId = MARIA_PSP_SFX_LAST;
    }
    if (tapped & PAD_CROSS) {
        g_api.PlaySfx(s_MariaPspSfxId);
    }

    metadata = &MARIA_PSP_SFX_DATA[s_MariaPspSfxId - 0x600];
    #define PUT(c) *out++ = (c)
    PUT('P');
    PUT('S');
    PUT('P');
    PUT(' ');
    PUT('M');
    PUT('A');
    PUT('R');
    PUT('I');
    PUT('A');
    PUT(' ');
    PUT('S');
    PUT('F');
    PUT('X');
    PUT(' ');
    PUT('T');
    PUT('E');
    PUT('S');
    PUT('T');
    PUT('\n');
    PUT('U');
    PUT('P');
    PUT('/');
    PUT('D');
    PUT('N');
    PUT(' ');
    PUT('1');
    PUT(' ');
    PUT('L');
    PUT('T');
    PUT('/');
    PUT('R');
    PUT('T');
    PUT(' ');
    PUT('1');
    PUT('0');
    PUT(' ');
    PUT('X');
    PUT(' ');
    PUT('P');
    PUT('L');
    PUT('A');
    PUT('Y');
    PUT('\n');
    PUT('S');
    PUT('f');
    PUT('x');
    PUT('{');
    PUT('I');
    PUT('D');
    PUT(':');
    PUT('0');
    PUT('x');
    out = MarPspAppendHex3(out, s_MariaPspSfxId);
    PUT('}');
    PUT('\n');
    PUT('V');
    PUT(':');
    out = MarPspAppendDec(out, metadata->vabid);
    PUT(' ');
    PUT('P');
    PUT(':');
    out = MarPspAppendDec(out, metadata->prog);
    PUT(' ');
    PUT('N');
    PUT(':');
    out = MarPspAppendDec(out, metadata->note);
    PUT(' ');
    PUT('L');
    PUT(':');
    out = MarPspAppendDec(out, metadata->volume);
    PUT('\n');
    PUT('M');
    PUT(':');
    out = MarPspAppendDec(out, metadata->mode);
    PUT(' ');
    PUT('T');
    PUT(':');
    out = MarPspAppendDec(out, metadata->tone);
    PUT(' ');
    PUT('U');
    PUT(':');
    out = MarPspAppendDec(out, metadata->unk6);
    PUT('\n');
    *out = 0;
    #undef PUT
    MarPspDrawMenu((char*)mar_80175958);
}

#endif
