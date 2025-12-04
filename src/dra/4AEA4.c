// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include "dra.h"
#include "dra_bss.h"

extern u8 g_GfxEquipIcon[];
extern u16 g_PalEquipIcon[];
extern GfxBank* D_psp_0918BBD0[];
extern GfxBank* D_psp_0918BBE8[];
extern GfxBank* D_psp_0918BC00[];
extern GfxBank* D_psp_0918BC18[];
extern GfxBank* D_psp_0918BC30[];
extern u16 D_psp_091654C0[];

// BSS
static u16 D_80137478[ICON_SLOT_NUM];
static u16 D_801374B8[ICON_SLOT_NUM];
static u16 D_801374F8[ICON_SLOT_NUM];
static u16 D_80137538[ICON_SLOT_NUM];
static u8* g_DecSrcPtr;
static u8* g_DecDstPtr;
static bool g_DecReadNibbleFlag;
static bool g_DecWriteNibbleFlag;
STATIC_PAD_BSS(8);

#include "../get_lang.h"

void func_800EAEA4(void) {
    s32 i;
    u16* ptr;

    for (i = 0, ptr = D_801374F8; i < ICON_SLOT_NUM; i++) {
        *ptr++ = -1;
    }

    for (i = 0, ptr = D_80137538; i < ICON_SLOT_NUM; i++) {
        *ptr++ = -1;
    }
}

void ResetPendingGfxLoad(void) {
    s32 i;
    GfxLoad* ptr;

    for (i = 0, ptr = g_GfxLoad; i < LEN(g_GfxLoad); i++, ptr++) {
        ptr->kind = GFX_BANK_NONE;
    }

    func_800EAEA4();
}

void LoadGfxAsync(s32 gfxId) {
    // Schedule the load of new graphics into the video RAM in the very next
    // frame by LoadPendingGfx. A maximum amount of 16 transfers can be chained.

    s32 i;
    GfxBank* gfxBank;
    GfxLoad* gfxLoad;

    if (gfxId & ANIMSET_OVL_FLAG) {
        gfxBank = g_api.o.gfxBanks[gfxId & 0x7FFF];
    } else {
#ifdef VERSION_PSP
        GfxBank** g_GfxSharedBank =
            GetLang(D_psp_0918BBD0, D_psp_0918BC30, D_psp_0918BBE8,
                    D_psp_0918BC18, D_psp_0918BC00);
#endif
        gfxBank = g_GfxSharedBank[gfxId];
    }
    if (gfxBank->kind == GFX_BANK_NONE) {
        return;
    }
    if (gfxBank->kind == -1) {
        return;
    }
    for (i = 0; i < LEN(g_GfxLoad); i++) {
        gfxLoad = &g_GfxLoad[i];
        if (gfxLoad->kind == GFX_BANK_NONE) {
            gfxLoad->kind = gfxBank->kind;
            gfxLoad->unk6 = 0;
            gfxLoad->unk8 = 0;
            gfxLoad->next = gfxBank->entries;
            return;
        }
    }
}

#ifdef VERSION_PSP
s32 func_psp_091040A0(GfxBank* gfxBank) {
    GfxLoad* ptr;
    s32 i;

    if (gfxBank->kind == GFX_BANK_NONE) {
        return -1;
    }
    if (gfxBank->kind == -1) {
        return -1;
    }
    for (i = 0; i < LEN(g_GfxLoad); i++) {
        ptr = &g_GfxLoad[i];
        if (ptr->kind == GFX_BANK_NONE) {
            ptr->kind = gfxBank->kind;
            ptr->unk6 = 0;
            ptr->unk8 = 0;
            ptr->next = gfxBank->entries;
            return i;
        }
        ptr++;
    }
    return -1;
}
#endif

static void DecompressWriteNibble(u8 ch) {
    if (!g_DecWriteNibbleFlag) {
        g_DecWriteNibbleFlag = true;
        *g_DecDstPtr = ch;
    } else {
        g_DecWriteNibbleFlag = false;
        *g_DecDstPtr += ch << 4;
        g_DecDstPtr++;
    }
}

static u8 DecompressReadNibble(void) {
    u8 ret;

    if (!g_DecReadNibbleFlag) {
        g_DecReadNibbleFlag = true;
        ret = *g_DecSrcPtr >> 4;
    } else {
        g_DecReadNibbleFlag = false;
        ret = *g_DecSrcPtr & 0xF;
        g_DecSrcPtr++;
    }
    return ret;
}

static s32 DecompressData(u8* dst, u8* src) {
    u32 buf[8];
    s32 ch, ch2;
    s32 count;
    s32 i, j;
    u32* ptr;
    u32 op;

    ptr = buf;
    for (j = 0; j < LEN(buf); j++) {
        *ptr++ = *src++;
    }

    g_DecReadNibbleFlag = false;
    g_DecWriteNibbleFlag = false;
    g_DecSrcPtr = src;
    g_DecDstPtr = dst;

    while (true) {
        op = DecompressReadNibble();
        switch (op) {
        case 0:
            ch = DecompressReadNibble();
            ch2 = DecompressReadNibble();
            count = (ch * 16) + ch2 + 0x13;
            for (i = 0; i < count; i++) {
                DecompressWriteNibble(0);
            }
            break;

        case 1:
            ch = DecompressReadNibble();
            DecompressWriteNibble(ch);
            break;

        case 2:
            ch = DecompressReadNibble();
            DecompressWriteNibble(ch);
            DecompressWriteNibble(ch);
            break;

        case 3:
            ch = DecompressReadNibble();
            DecompressWriteNibble(ch);
            ch = DecompressReadNibble();
            DecompressWriteNibble(ch);
            break;

        case 4:
            ch = DecompressReadNibble();
            DecompressWriteNibble(ch);
            ch = DecompressReadNibble();
            DecompressWriteNibble(ch);
            ch = DecompressReadNibble();
            DecompressWriteNibble(ch);
            break;

        case 5:
            ch = DecompressReadNibble();
            ch2 = DecompressReadNibble();
            count = ch2 + 3;
            for (i = 0; i < count; i++) {
                DecompressWriteNibble(ch);
            }
            break;

        case 6:
            ch = DecompressReadNibble();
            count = ch + 3;
            for (i = 0; i < count; i++) {
                DecompressWriteNibble(0);
            }
            break;

        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            ch = buf[op - 7];
            switch (ch & 0xF0) {
            case 0x20:
                DecompressWriteNibble(ch & 0xF);
            case 0x10:
                DecompressWriteNibble(ch & 0xF);
                break;

            case 0x60:
                count = (ch & 0xF) + 3;
                for (i = 0; i < count; i++) {
                    DecompressWriteNibble(0);
                }
                break;
            }
            break;

        case 15:
            if (dst + 0x2000 < g_DecDstPtr) {
                return g_DecDstPtr - dst + 0x2000;
            }
            return 0;
        }
    }
}

void LoadPendingGfx(void) {
    // Called every frame, it continuously checks if there is any new graphics
    // to transfer from RAM to Video RAM. Compressed graphics are loaded as
    // 128x128 images into a 256x256 tpage (hence the `j < 4`). Each pending
    // GFX load contains a descriptor to instruct this function in which area
    // of the Video RAM the texture will be transferred to.

    char buf[0x100];
    GfxEntry* gfxEntry;
    GfxLoad* gfxLoad;
    s32 over;
    s32 i, j;
    u32 xy;
    u32 wh;
    u8* src;
    u8* dst;
    u8* cmp;

    for (j = 0, i = 0, gfxLoad = g_GfxLoad; i < LEN(g_GfxLoad); i++) {
        switch (gfxLoad->kind) {
        case GFX_BANK_NONE:
            break;

        case GFX_BANK_4BPP:
        case GFX_BANK_8BPP:
        case GFX_BANK_16BPP:
            gfxEntry = gfxLoad->next;
            while ((u32)gfxEntry->xy != -1) {
                xy = (u32)gfxEntry->xy;
                wh = (u32)gfxEntry->wh;
                src = (u8*)gfxEntry->data;
                LoadTPage((u_long*)src, gfxLoad->kind - 1, 0, xy >> 0x10,
                          (u16)xy, wh >> 0x10, (u16)wh);
                gfxEntry++;
            }
            gfxLoad->kind = GFX_BANK_NONE;
            break;

        case GFX_BANK_COMPRESSED:
            gfxEntry = gfxLoad->next;
            for (; j < 4; j++) {
                dst = g_Pix[j];
                xy = (u32)gfxEntry->xy;
                wh = (u32)gfxEntry->wh;
                cmp = (u8*)gfxEntry->data;
                over = DecompressData(dst, cmp);
                if (over) {
                    sprintf(buf, "over:%08x(%04x)", cmp, over);
                    DebugInputWait(buf);
                }
                LoadTPage((u_long*)dst, 0, 0, xy >> 0x10, (u16)xy, wh >> 0x10,
                          (u16)wh);
                gfxLoad->next = ++gfxEntry;
                if ((u32)gfxEntry->xy == -1) {
                    gfxLoad->kind = GFX_BANK_NONE;
                    break;
                }
            }
            break;
        }
        gfxLoad++;
    }
}

void func_800EB4F8(PixPattern* pix, s32 bitDepth, s32 x, s32 y) {
    LoadTPage(
        (u_long*)((s32*)pix + 1), bitDepth, 0, x, y, (int)pix->w, (int)pix->h);
}

void LoadEquipIcon(s32 equipIcon, s32 palette, s32 index) {
    s32 i;
    u16* ptr;
    s32 x, y;

    if (D_801374F8[index] != equipIcon) {
        LoadTPage((u_long*)&g_GfxEquipIcon[equipIcon * (16 * 16 / 2)], 0, 0,
                  ((index & 7) * 4) + 0x280, (index / 8) * 0x10 + 0x180, 16,
                  16);
    }

    if (D_80137538[index] != palette) {
        for (i = 0; i < 16; i++) {
            g_Clut[1][index * COLORS_PER_PAL + i + 0xD00] =
                g_PalEquipIcon[palette * 0x10 + i];
        }
#ifdef VERSION_PSP
        x = index & 0xF;
        y = index / 16;
        if (palette < 0x100) {
            ptr = &g_PalEquipIcon[palette * 0x10];
        } else {
            ptr = &D_psp_091654C0[(palette - 0x100) * 0x10];
        }
        func_psp_0891CCBC(ptr, x * 0x10, y + 0xFD);
#else
        LoadClut(&g_Clut[1][0xD00], 0, 0xFD);
        LoadClut(&g_Clut[1][0xE00], 0, 0xFE);
#endif
    }
    if (D_800973EC == 0) {
        D_80137478[index] = equipIcon;
        D_801374B8[index] = palette;
    }
    D_801374F8[index] = equipIcon;
    D_80137538[index] = palette;
}

void func_800EB6B4(void) {
    s32 i;

    for (i = 0; i < ICON_SLOT_NUM; i++) {
        LoadEquipIcon(D_80137478[i], D_801374B8[i], i);
    }
}

bool func_800EB720(void) {
    GfxLoad* ptr;
    s32 i;

    for (i = 0, ptr = g_GfxLoad; i < LEN(g_GfxLoad); i++) {
        if (ptr[i].kind) {
            return true;
        }
    }

    return false;
}
