// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

extern s32 D_8B42044;
extern u32 g_DebugCurPal;
extern s32 g_DebugEnabled2;

// BSS
u8 D_psp_091CB700[0x2000];

void func_psp_090DFBD0(void) {
    if ((s8)g_SaveAreaNames[g_StageId][0] != 0) {
        StoreSaveData((SaveData*)D_psp_091CB700, 0, rand() & 0xF);
        if (D_8B42044 != 0) {
            D_8B42044 = 0;
            D_psp_091CB700[0x1FFF] = 0;
        } else {
            D_psp_091CB700[0x1FFF] = 0xFF;
        }
        D_psp_091CB700[0x1FFE] = D_8006C374;
    }
}

void func_psp_090DFC68() {
    memcpy(D_psp_091CB700, &g_Pix, sizeof(D_psp_091CB700));
}

void func_psp_090DFC80() {
    func_89195C0(D_psp_091CB700, sizeof(D_psp_091CB700), D_8006C378);
}

void func_800EA538(s32 arg0) {
    s32 i;
    Unkstruct_8006C3C4* ptr;

    u16 mask = 0x8000;
    mask = mask >> (arg0 - 1);

    if (arg0) {
        for (i = 0, ptr = D_8006C3C4; i < LEN(D_8006C3C4); i++) {
            if (ptr->unk8 & mask) {
                ptr->unk8 = 0;
            }
            ptr++;
        }
    } else {
        D_8003C0EC[3] = 0;
        for (i = 0, ptr = D_8006C3C4; i < LEN(D_8006C3C4); i++) {
            ptr->unk8 = 0;
            ptr++;
        }
    }
}

void func_800EA5AC(u16 a, u8 r, u8 g, u8 b) {
    D_8003C0EC[3] = a;
    D_8003C0EC[0] = r;
    D_8003C0EC[1] = g;
    D_8003C0EC[2] = b;
}

s32 func_800EA5E4(u32 arg0) {
    u16 temp_v0;
    s32 i, j;
    u32 start;
    u32 count;
    u_long* clut;
    Unkstruct_8006C3C4* ptr;

    temp_v0 = arg0 & ~0xFF; // & 0xFF00 would be more descriptive.
    arg0 = arg0 & 0xFF;

    if (temp_v0 & 0x8000) {
        clut = g_api.o.cluts[arg0];
    } else {
        clut = D_800A3BB8[arg0];
    }

    if (clut[0] == 0) {
        return 1;
    }
    if (clut[0] == -1) {
        return 1;
    }

    for (i = 0, ptr = D_8006C3C4; i < LEN(D_8006C3C4); i++, ptr++) {
        if (!ptr->unk8) {
            ptr->desc = clut;
            ptr->data = clut + 3;
            ptr->unk8 = GET_PAL_OP_KIND(clut[0]) | temp_v0;
            ptr->index = 0;
            ptr->unkC = 0;

            // Set unkStruct's array to all zeros, except within this range
            start = clut[1];
            count = clut[2] + start - 1;
            start >>= 8;
            count >>= 8;
            for (j = 0; j < LEN(ptr->unkArray); j++) {
                ptr->unkArray[j] = 0;
            }
            for (j = start; j <= count; j++) {
                ptr->unkArray[j] = 1;
            }

            switch (ptr->unk8 & 0xFF) {
            case PAL_UNK_OP2:
            case 16:
                ptr->unkE = 0x1F;
            }
            return 0;
        }
    }
    return -1;
}

// Takes a color "col" in RGB5551 and increments/decrements each component
// to bring it closer to the target by 1.
static u16 func_800EA720(u16 target, u16 col) {
    if ((target & RED_MASK) > (col & RED_MASK)) {
        col = (col & UNRED_MASK) | ((col & RED_MASK) + 1);
    }
    if ((target & RED_MASK) < (col & RED_MASK)) {
        col = (col & UNRED_MASK) | ((col & RED_MASK) - 1);
    }

    if ((target & GREEN_MASK) > (col & GREEN_MASK)) {
        col = (col & UNGREEN_MASK) | ((col & GREEN_MASK) + (1 << 5));
    }
    if ((target & GREEN_MASK) < (col & GREEN_MASK)) {
        col = (col & UNGREEN_MASK) | ((col & GREEN_MASK) - (1 << 5));
    }

    if ((target & BLUE_MASK) > (col & BLUE_MASK)) {
        col = (col & UNBLUE_MASK) | ((col & BLUE_MASK) + (1 << 10));
    }
    if ((target & BLUE_MASK) < (col & BLUE_MASK)) {
        col = (col & UNBLUE_MASK) | ((col & BLUE_MASK) - (1 << 10));
    }

    return col;
}

void func_800EA7CC(void) {
    // stores which palettes have been invalidated and need to be re-uploaded
    // to the VRAM
    u8 palettes[0x30];
    u_long* desc;
    u16* data;
    u16* clut;
    s32 i, j;
    s32 clutOffset;
    s32 count;
    s32 offset;
    u16 prevClut;
    u16 newClut;
    u32 clutX;
    bool isAnimNotDone;
    Unkstruct_8006C3C4* ptr;

    if (g_DebugEnabled2 && g_DebugMode == 10) {
        return;
    }

    for (i = 0; i < LEN(palettes); i++) {
        palettes[i] = 0;
    }

    // cycles through a list of palette operations stored in D_8006C3C4
    for (i = 0, ptr = D_8006C3C4; i < 0x20; i++, ptr++) {
        if (!ptr->unk8) {
            continue;
        }
        if (ptr->index) {
            ptr->index--;
            continue;
        }
        desc = ptr->desc;
        data = (u16*)*ptr->data;
        count = desc[2];
        clutOffset = desc[1];
        clut = g_Clut[0];
        clut += clutOffset;

        switch (ptr->unk8 & 0xFF) {
        case PAL_COPY: // simple palette copy
            for (j = 0; j < count; j++) {
                *clut++ = *data++;
            }
            for (j = 0; j < LEN(palettes); j++) {
                palettes[j] |= ptr->unkArray[j];
            }
            ptr->unk8 = 0;
            break;
        case PAL_UNK_OP3: // palette rotation
            for (j = 0; j < count; j++) {
                *clut++ = *data++;
            }
            for (j = 0; j < LEN(palettes); j++) {
                palettes[j] |= ptr->unkArray[j];
            }
            ptr->index = (desc[0] >> 0x10) - 1;
            ptr->data++;
            if (*ptr->data == -1) {
                ptr->data = desc + 3;
            }
            break;
        case 16:
            break;
        case PAL_UNK_OP2: // blend to destination color?
            for (j = 0; j < count; j++) {
                *clut++ = func_800EA720(*data++, *clut);
            }
            for (j = 0; j < LEN(palettes); j++) {
                palettes[j] |= ptr->unkArray[j];
            }
            if (ptr->unkE != 0) {
                ptr->unkE--;
                desc = ptr->desc;
                ptr->index = (desc[0] >> 0x10) - 1;
            } else {
                ptr->unkE = 0x1F;
                ptr->data++;
                if (*ptr->data == -1) {
                    ptr->unk8 = 0;
                }
            }
            break;
        case PAL_GLOW_ANIM: // blend to destination, causes item to glow
            isAnimNotDone = false;
            for (j = 0; j < count; j++) {
                prevClut = *clut;
                newClut = func_800EA720(*data++, prevClut);
                if (prevClut != newClut) {
                    isAnimNotDone = true;
                }
                *clut++ = newClut;
            }
            for (j = 0; j < LEN(palettes); j++) {
                palettes[j] |= ptr->unkArray[j];
            }
            desc = ptr->desc;
            ptr->index = (desc[0] >> 0x10) - 1;
            if (!isAnimNotDone) {
                ptr->data++;
                if (*ptr->data == -1) {
                    ptr->data = desc + 3;
                }
            }
            break;
        case PAL_BULK_COPY: // some kind of bulk palette copy?
            while (true) {
                desc = (u_long*)(ptr->data - 2);
                data = (u16*)*ptr->data;
                clut = g_Clut[0];
                clutOffset = desc[0];
                count = desc[1];
                clut += clutOffset;
                for (j = 0; j < count; j++) {
                    *clut++ = *data++;
                }
                if (desc[3] == -1) {
                    break;
                }
                ptr->data += 3;
            }
            for (j = 0; j < LEN(palettes); j++) {
                palettes[j] = 1;
            }
            ptr->unk8 = 0;
            break;
        }
    }

    if (g_DebugEnabled2 && g_DebugMode == DEBUG_PALETTE_VIEWER) {
        palettes[g_DebugCurPal >> 4] = 1;
    }

    // re-upload updated stage tileset palette
    clut = g_Clut[0];
    offset = 0;
    clutX = 0x200;
    for (i = 0xF0; i < 0x100; i++) {
        if (palettes[offset]) {
            LoadClut((u_long*)clut, clutX, i);
        }
        clut += 0x100;
        offset++;
    }

    // re-upload updated shared entity palette
    clutX = 0;
    for (i = 0xF0; i < 0x100; i++) {
        if (palettes[offset]) {
            LoadClut((u_long*)clut, clutX, i);
        }
        clut += 0x100;
        offset++;
    }

    // re-upload updated stage-specific entities palette
    clutX = 0x100;
    for (i = 0xF0; i < 0x100; i++) {
        if (palettes[offset]) {
            LoadClut((u_long*)clut, clutX, i);
        }
        clut += 0x100;
        offset++;
    }
}

s32 func_800EAD0C(void) { // the return type is needed for matching
    func_800EA5E4(4);
    func_800EA5E4(5);
    func_800EA5E4(6);
    func_800EA5E4(7);
    func_800EA5E4(8);

    if (g_PlayableCharacter == PLAYER_ALUCARD && g_StageId != STAGE_ST0) {
        func_800EA5E4(0x17);
    }
}

void func_800EAD7C(void) {
    s32 index = 0;
    s32 i;
    s32 j;

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x200; j < 0x300; j += 0x10) {
            g_ClutIds[index++] = getClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0; j < 0x100; j += 0x10) {
            g_ClutIds[index++] = getClut(j, i);
        }
    }

    for (i = 0xF0; i < 0x100; i++) {
        for (j = 0x100; j < 0x200; j += 0x10) {
            g_ClutIds[index++] = getClut(j, i);
        }
    }
}
