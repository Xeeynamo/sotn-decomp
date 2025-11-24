// SPDX-License-Identifier: MIT
//! PSYQ=3.3
#include "common.h"
#include <libgpu.h>
#include <stdarg.h>

typedef struct {
    /* 0x00 */ TILE tile;
    /* 0x10 */ DR_MODE draw_mode;
    /* 0x1C */ s32 capacity;
    /* 0x20 */ SPRT_8* sprites;
    /* 0x24 */ char* buffer;
    /* 0x28 */ s32 written;
} FntStream;

extern int (*GPU_printf)(const char*, ...);

static char D_80033A18[0x400];
static SPRT_8 D_80033E18[0x400];
static u16 tpage;
STATIC_PAD_BSS(2);
static u16 clut;
STATIC_PAD_BSS(2);

static FntStream Font[4] = {0};
static s32 D_8002B810 = 0;
static s32 D_8002B814 = 0;
static u16 D_8002B818[] = {
#include "../../gen/D_8002B818.h"
};
static u8 D_8002BA18[] = {
#include "../../gen/D_8002BA18.h"
};
static s32 D_8002C218 = 0;
static char* D_8002C21C = "0123456789ABCDEF";

void SetDumpFnt(int id) {
    if (id >= 0 && D_8002B810 >= id) {
        D_8002B814 = id;
        GPU_printf = FntPrint;
    }
}

void FntLoad(s32 tx, s32 ty) {
    clut = LoadClut(D_8002B818, tx, ty + 0x80);
    tpage = LoadTPage(D_8002B818 + 0x100, 0, 0, tx, ty, 0x80, 0x20);
    D_8002B810 = 0;
    memset(Font, 0, sizeof(Font));
}

s32 FntOpen(s32 x, s32 y, s32 w, s32 h, s32 isbg, s32 n) {
    s32 i;
    SPRT_8* sprites;

    if (D_8002B810 >= 4) {
        return -1;
    }
    if (D_8002B810 == 0) {
        D_8002C218 = 0;
    }
    if ((n + D_8002C218) > 0x400) {
        n = 0x400 - D_8002C218;
    }
    SetDrawMode(&Font[D_8002B810].draw_mode, 0, 0, tpage, NULL);
    if (isbg) {
        SetTile(&Font[D_8002B810].tile);
        (*&Font[D_8002B810].tile).r0 = 0;
        (*&Font[D_8002B810].tile).g0 = 0;
        (*&Font[D_8002B810].tile).b0 = 0;
    }
    (*&Font[D_8002B810].tile).x0 = x;
    (*&Font[D_8002B810].tile).y0 = y;
    (*&Font[D_8002B810].tile).w = w;
    (*&Font[D_8002B810].tile).h = h;
    Font[D_8002B810].capacity = n;
    Font[D_8002B810].written = 0;
    Font[D_8002B810].buffer = &D_80033A18[D_8002C218];
    Font[D_8002B810].sprites = &D_80033E18[D_8002C218];
    *Font[D_8002B810].buffer = 0;
    sprites = Font[D_8002B810].sprites;
    for (i = 0; i < n; i++) {
        SetSprt8(sprites);
        SetShadeTex(sprites, true);
        sprites->clut = clut;
        sprites++;
    }
    D_8002C218 += n;
    return D_8002B810++;
}

u_long* FntFlush(s32 id) {
    DR_MODE* dr;
    s32 x, y;
    s32 max_x, max_y;
    s32 len;
    bool line_break;
    s32 ch;
    char* buf;
    FntStream* font;
    SPRT_8* sprt;
    u8 u, v;

    if (id < 0 || id >= D_8002B810) {
        id = D_8002B814;
        if (Font[id].buffer == NULL) {
            return NULL;
        }
    }
    font = &Font[id];
    dr = &font->draw_mode;
    buf = font->buffer;
    sprt = font->sprites;
    len = font->capacity;
    x = font->tile.x0;
    y = font->tile.y0;
    max_x = x + font->tile.w;
    max_y = y + font->tile.h;
    TermPrim(dr);
    while (*buf != 0) {
        if (len == 0) {
            break;
        }
        line_break = false;
        switch (*buf) {
        case '\n':
            line_break = true;
            break;

        case '\t':
            x += 0x20;
            if (x >= max_x) {
                line_break = true;
            }
            break;

        case ' ':
            x += 8;
            if (x >= max_x) {
                line_break = true;
            }
            break;

        default:
            if (*buf >= 'a' && *buf <= 'z') {
                ch = *buf - 0x40;
            } else {
                ch = *buf - 0x20;
            }
            u = (ch % 16) * 8;
            v = (ch / 16) * 8;
            sprt->u0 = u;
            sprt->v0 = v;
            sprt->x0 = x;
            sprt->y0 = y;
            AddPrim(dr, &sprt->tag);
            x += 8;
            if (x >= max_x) {
                line_break = true;
            }
            break;
        }
        if (line_break) {
            x = font->tile.x0;
            y += 8;
            if (y >= max_y) {
                break;
            }
        }
        sprt++;
        buf++;
        len--;
    }
    if (font->tile.code != 0) {
        AddPrim(dr, &font->tile.tag);
    }
    DrawOTag((u_long*)dr);
    font->written = 0;
    *font->buffer = 0;
    return (u_long*)dr;
}

#define WriteChar(c)                                                           \
    font->buffer[font->written++] = (c);                                       \
    if (font->written > font->capacity) {                                      \
        return -1;                                                             \
    }

int FntPrint(const char* id, ...) {
    char buf[0x200];
    va_list args;
    FntStream* font;
    u8 padZeros;
    s32 num;
    s32 len;
    s32 width;
    char* f;
    char* bufPtr;
    char sign;
    u32 ch;

    va_start(args, id);
    if (LOW(id) < 0 || LOW(id) >= D_8002B810) {
        f = (char*)id;
        id = D_8002B814;
        if (Font[LOW(id)].buffer == NULL) {
            return -1;
        }
    } else {
        f = va_arg(args, char*);
    }

    font = &Font[LOW(id)];
    if (font->written > font->capacity) {
        return -1;
    }
    for (; ch = *f, ch; ++f) {
        if (ch != '%') {
            WriteChar(ch);
            continue;
        }

        ch = *++f;
        if (ch == '%') {
            WriteChar('%');
            continue;
        }

        width = 0;
        padZeros = ch == '0';
        while (ch >= '0' && ch <= '9') {
            width = (width * 10) + (ch - '0');
            ch = *++f;
        }
        bufPtr = &args;
        if (width <= 0) {
            width = 1;
        }

        switch (ch) {
        case 'd':
            num = va_arg(args, s32);
            sign = 0;
            if (num < 0) {
                num = -num;
                sign = '-';
            }
            len = 0;
            do {
                do {
                    *--bufPtr = (num % 10U) + '0';
                    num /= 10U;
                    len++;
                } while (len == 0);
            } while (num != 0);
            if (sign != 0) {
                *--bufPtr = sign;
                len++;
            }
            break;

        case 'X':
        case 'x':
            len = 0;
            num = va_arg(args, s32);
            do {
                do {
                    *--bufPtr = D_8002C21C[num % 16U];
                    num /= 16U;
                    len++;
                } while (len == 0);
            } while (num != 0);
            if (padZeros) {
                while (len < width) {
                    *--bufPtr = '0';
                    len++;
                }
            }
            break;

        case 'c':
            *--bufPtr = va_arg(args, char);
            len = 1;
            break;

        case 's':
            bufPtr = va_arg(args, char*);
            len = strlen(bufPtr);
            break;
        }

        while (len < width) {
            WriteChar(' ');
            width--;
        }
        len--;
        while (len != -1) {
            WriteChar(*bufPtr++);
            len--;
        }
    }
    font->buffer[font->written] = 0;
    return font->written;
}
