// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"

// BSS
extern u16 D_80137478[ICON_SLOT_NUM];
extern u16 D_801374B8[ICON_SLOT_NUM];
extern u16 D_801374F8[ICON_SLOT_NUM];
extern u16 D_80137538[ICON_SLOT_NUM];
extern u8* g_DecSrcPtr;
extern u8* g_DecDstPtr;
extern bool g_DecReadNibbleFlag;
extern bool g_DecWriteNibbleFlag;

void func_800EAEA4(void) {
    u16* ptr;
    s32 i;

    for (i = 0, ptr = D_801374F8; i < ICON_SLOT_NUM; i++) {
        *ptr++ = -1;
    }

    for (i = 0, ptr = D_80137538; i < ICON_SLOT_NUM; i++) {
        *ptr++ = -1;
    }
}

void ResetPendingGfxLoad(void) {
    GfxLoad* ptr;
    s32 i;

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

void DecompressWriteNibble(u8 ch) {
    if (!g_DecWriteNibbleFlag) {
        g_DecWriteNibbleFlag = true;
        *g_DecDstPtr = ch;
    } else {
        g_DecWriteNibbleFlag = false;
        *g_DecDstPtr += ch << 4;
        g_DecDstPtr++;
    }
}

u8 DecompressReadNibble(void) {
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

s32 DecompressData(u8* dst, u8* src) {
    u32 buf[8];
    s32 ch;
    s32 count;
    s32 i;
    s32 var_v1;
    u32* var_a0;
    u32 op;

    var_a0 = buf;
    for (var_v1 = 0; var_v1 < LEN(buf); var_v1++) {
        *var_a0++ = *src++;
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
            op = DecompressReadNibble();
            count = (ch << 4) + op + 0x13;
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
            var_v1 = DecompressReadNibble();
            count = var_v1 + 3;
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
    s32 i;
    s32 j;
    u32 xy;
    u32 wh;
    u8* cmp;
    u8* src;
    u8* dst;
    s32 over;
    GfxLoad* gfxLoad;
    GfxEntry* gfxEntry;

    j = 0;
    gfxLoad = g_GfxLoad;
    for (i = 0; i < LEN(g_GfxLoad); i++, gfxLoad++) {
        switch (gfxLoad->kind) {
        case GFX_BANK_NONE:
            break;
        case GFX_BANK_4BPP:
        case GFX_BANK_8BPP:
        case GFX_BANK_16BPP:
            for (gfxEntry = gfxLoad->next; gfxEntry->xy != -1; gfxEntry++) {
                xy = (u32)gfxEntry->xy;
                wh = (u32)gfxEntry->wh;
                src = (u8*)gfxEntry->data;
                LoadTPage(src, gfxLoad->kind - 1, 0, xy >> 0x10, (u16)xy,
                          wh >> 0x10, (u16)wh);
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
                LoadTPage(dst, 0, 0, xy >> 0x10, (u16)xy, wh >> 0x10, (u16)wh);
                gfxLoad->next = ++gfxEntry;
                if (gfxEntry->xy == -1) {
                    gfxLoad->kind = GFX_BANK_NONE;
                    break;
                }
            }
            break;
        }
    }
}

void func_800EB4F8(PixPattern* pix, s32 bitDepth, s32 x, s32 y) {
    LoadTPage((u_long*)pix + 1, bitDepth, 0, x, y, (int)pix->w, (int)pix->h);
}

void LoadEquipIcon(s32 equipIcon, s32 palette, s32 index) {
    s32 i;

    if (D_801374F8[index] != equipIcon) {
        LoadTPage((u_long*)g_GfxEquipIcon[equipIcon], 0, 0,
                  ((index & 7) * 4) + 0x280, (index / 8) * 0x10 + 0x180, 16,
                  16);
    }

    if (D_80137538[index] != palette) {
        for (i = 0; i < 16; i++) {
            g_Clut[index * 0x10 + i + 0x1D00] =
                g_PalEquipIcon[palette * 0x10 + i];
        }

        LoadClut(&g_Clut[0x1D00], 0, 0xFD);
        LoadClut(&g_Clut[0x1E00], 0, 0xFE);
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
