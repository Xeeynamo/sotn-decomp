// SPDX-License-Identifier: AGPL-3.0-or-later
#include "richter.h"

void func_060BACA4(void) {
    memset(&g_RichterCastleMapState, 0, 4);
    memcpy(CASTLE_MAP_BITMAP, g_RichterCastleMapBitmap, CASTLE_MAP_BITMAP_SIZE);

    func_060BB330();
}

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BACEC, func_060BACEC);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BAED0, func_060BAED0);
void func_060BB09C(u8 walls, u8* dst) {
    u8* p;
    s32 i;

    if (walls & 0x40) {
        p = dst;
        for (i = 0; i < 5; i++) {
            *p++ |= 0x88;
            *p++ |= 0x88;
            *p |= 0x88;
            p += CASTLE_MAP_BITMAP_PITCH - 2;
        }
    }
    if (walls & 0x10) {
        p = dst + 2;
        for (i = 0; i < 5; i++) {
            *p++ |= 0x08;
            *p++ |= 0x88;
            *p++ |= 0x88;
            *p |= 0x80;
            p += CASTLE_MAP_BITMAP_PITCH - 3;
        }
    }
    if (walls & 4) {
        p = dst + 5;
        for (i = 0; i < 5; i++) {
            *p++ |= 0x88;
            *p++ |= 0x88;
            *p |= 0x88;
            p += CASTLE_MAP_BITMAP_PITCH - 2;
        }
    }
    if (walls & 1) {
        p = dst + 7;
        for (i = 0; i < 5; i++) {
            *p++ |= 0x08;
            *p++ |= 0x88;
            *p++ |= 0x88;
            *p |= 0x80;
            p += CASTLE_MAP_BITMAP_PITCH - 3;
        }
    }
}

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB184, func_060BB184);

void func_060BB330(void) {
    u8* dst;
    u8* revealDst;
    s32 mapOffset;
    s32 mapIndex;
    s32 row;
    s32 col;
    s32 revealRow;
    u32 revealCol;

    dst = CASTLE_MAP_BITMAP;
    mapOffset = 0;

    if (g_CurrentRoom.stageID & 0x20) {
        mapOffset = 0x0400;
        revealDst = dst + 0x6970;

        for (revealRow = 0; revealRow <= 3; revealRow++) {
            for (revealCol = 0; revealCol <= 10; revealCol++) {
                revealDst[revealCol] = g_RichterMapRevealPattern[revealCol];
            }
            revealDst += CASTLE_MAP_BITMAP_PITCH;
        }
    }

    row = 0;
    mapIndex = mapOffset;
    for (; row <= 0x3F; row++) {
        for (col = 0; col <= 0x0F; col++) {
            func_060BACEC(g_CastleMap[mapIndex++], dst);
            dst += CASTLE_MAP_CELL_WIDTH;
        }
        dst += CASTLE_MAP_BITMAP_PITCH * 3;
    }

    func_060BB184();

    dst = CASTLE_MAP_BITMAP;
    row = 0;
    mapIndex = mapOffset;
    for (; row <= 0x3F; row++) {
        for (col = 0; col <= 0x0F; col++) {
            func_060BB09C(g_CastleMap[mapIndex++], dst);
            dst += CASTLE_MAP_CELL_WIDTH;
        }
        dst += CASTLE_MAP_BITMAP_PITCH * 3;
    }

    dst = CASTLE_MAP_BITMAP;
    row = 0;
    mapIndex = mapOffset;
    for (; row <= 0x3F; row++) {
        for (col = 0; col <= 0x0F; col++) {
            func_060BAED0(g_CastleMap[mapIndex++], dst);
            dst += CASTLE_MAP_CELL_WIDTH;
        }
        dst += CASTLE_MAP_BITMAP_PITCH * 3;
    }
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB454, func_060BB454);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB58C, func_060BB58C);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BB718, func_060BB718);
s32* func_060784A8(void);

void func_060BB90C(void) {
    s32* ptr;
    u16* colors0;
    u16* colors1;

    ptr = func_060784A8();
    func_060BBDE0(ptr);
    g_RichterSavedMapVramBase = DAT_060476a0;
    g_RichterSavedMapPlaneConfig = DAT_060476a4;
    if (g_PlayableCharacter == 0) {
        DAT_060476a0 = DAT_00252000;
        DAT_060476a4 = 1;
    }
    colors0 = SpGourTbl->colors0;
    colors0[0] = colors0[1] = 0xB18C;
    colors0[2] = colors0[3] = 0xD294;
    colors1 = SpGourTbl->colors1;
    colors1[0] = colors1[1] = colors1[2] = colors1[3] = 0x9084;
    DAT_0605C6E4 = 1;
}

void func_060BB9BC(s32* src) {
    s32* dst;
    Unk0605DB60* entry;
    s32 i;

    dst = (s32*)((DAT_0605AEC0[0][0] * 8) + 0x25C00000);
    DMA_CpuMemCopy2(dst, src, 0x8400);
    while (DMA_CpuResult() == 2) {
    }

    entry = d_0605DB60;
    for (i = 0; i <= 0x1F; i++) {
        entry->unkC = entry->unk8;
        entry->unkE = entry->unkA;
        entry++;
    }

    dst = (s32*)((SPR_2LookupTblNoToVram(0x10) * 8) + 0x25C00000);
    DMA_CpuMemCopy2(dst, src + 0x4200, 0x400);
    while (DMA_CpuResult() == 2) {
    }

    dst = (s32*)0x25F00800;
    DMA_CpuMemCopy2(dst, src + 0x4400, 0x200);
    while (DMA_CpuResult() == 2) {
    }
}

s32 DAT_06086390;
u8* DAT_060476a0;
s32 DAT_060476a4;

void func_060BBA88(void) {
    s32* iVar2;
    iVar2 = func_060784A8();
    func_060BB9BC(iVar2);
    DAT_060476a0 = g_RichterSavedMapVramBase;
    DAT_060476a4 = g_RichterSavedMapPlaneConfig;
}

void func_060BBAC8(void) {
    s32* iVar2;
    DAT_06086390 = 0;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

void func_060BBAF4(void) {
    s32* work;
    u8* area;
    u8* dst;
    s32 i;
    u32 clear_size;
    u8* dma_base;
    s32 dma_offset;
    u16 dma_value;
    s32* dma_dest;

    DAT_06086390 = 1;
    work = func_060784A8();
    work[0x4500] = -1;

    clear_size = 0xA000U;
    area = (u8*)(work + 0x4501);
    memset(area, 0, clear_size);
    dst = area;

    for (i = 0; i < 11; i++) {
        func_06078700(dst, DAT_06085DE8[i], 4);
        dst += 0x180;
    }

    for (i = 0; i < 8; i++) {
        func_06078700(dst, DAT_06085E14[i], 4);
        dst += 0x180;
    }

    for (i = 0; i < 2; i++) {
        func_06078700(dst, (s8*)g_StatusMenuLabelPointers[i], 4);
        dst += 0x180;
    }

    dma_base = (u8*)DAT_0605AEC0;
    dma_offset = 8;
    dma_value = *(u16*)(dma_base + dma_offset);
    dma_dest = (s32*)(0x25C00000 + dma_value * 8);
    DMA_CpuMemCopy2(dma_dest, work + 0x4501, 0xFC0U);
    while (DMA_CpuResult() == 2) {
    }
}
void func_060BBC00(void) {
    s32* base;
    s32* dst;
    u8* text;
    s32 slot;
    s32 i;

    DAT_06086390 = 2;
    base = func_060784A8();
    base[0x4500] = -1;
    memset(base + 0x4501, 0, 0xA000);

    text = (u8*)(base + 0x4501);
    for (i = 0; i < 8; i++) {
        func_06078700(text, GetMenuItemName(i), 12);
        text += 0x480;
    }
    func_06078700(text, (s8*)g_StatusMenuLabelPointers[2], 6);

    slot = 2;
    dst = (s32*)((DAT_0605AEC0[slot][0] * 8) + 0x25C00000);
    DMA_CpuMemCopy2(dst, base + 0x4501, 0x1320);
    while (DMA_CpuResult() == 2) {
    }
}

void func_060BBCCC(void) {
    s32* base;
    s32* dst;
    u8* text;
    s32 slot;
    s32 i;

    DAT_06086390 = 3;
    base = func_060784A8();
    base[0x4500] = -1;
    memset(base + 0x4501, 0, 0xA000);

    text = (u8*)(base + 0x4501);
    for (i = 0; i < 0x20; i++) {
        func_06078700(text, GetMenuItemName(i), 12);
        text += 0x480;
    }

    slot = 2;
    dst = (s32*)((DAT_0605AEC0[slot][0] * 8) + 0x25C00000);
    DMA_CpuMemCopy2(dst, base + 0x4501, 0x4800);
    while (DMA_CpuResult() == 2) {
    }
}

void func_060BBD88(void) {
    int* iVar2;
    DAT_06086390 = 4;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

void func_060BBDB4(void) {
    int* iVar2;
    DAT_06086390 = 5;
    iVar2 = func_060784A8();
    iVar2[0x4500] = 0xffffffff;
}

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BBDE0, func_060BBDE0);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BBF08, func_060BBF08);

// CheckIfAllButtonsAreAssigned
bool func_060BC048(void) {
    s32 buf[9];
    s32 i;
    s32 bitMask_Assigned;
    s32* buttonConfig;

    for (i = 0; i < 9; i++) {
        buf[i] = 0;
    }

    buttonConfig = g_Settings.buttonConfig;
    for (i = 0; i < 8; i++) {
        buf[*buttonConfig++] = 1;
    }

    for (i = 0; i < 9; i++) {
        if (buf[i] == 0) {
            g_Settings.buttonConfig[8] = i;
            break;
        }
    }

    for (i = 0; i < 9; i++) {
        g_Settings.buttonMask[i] = g_ButtonMask[g_Settings.buttonConfig[i]];
    }

    bitMask_Assigned = 0;
    buttonConfig = g_Settings.buttonConfig;
    for (i = 0; i < 9; i++) {
        bitMask_Assigned |= 1 << *buttonConfig++;
    }
    if (bitMask_Assigned == 0xFF) {
        return true;
    } else {
        return false;
    }
}
void func_060BC108(void) {
    Point16* pos;
    s32 i;
    s32 value;
    s32 buttonConfig;

    pos = g_RichterMapUiPositionsA;
    for (i = 0; i < 4; i++) {
        func_06078684(0x1C0, g_Status.statsBase[i], pos++);
        if (g_Status.statsEquip[i] != 0) {
            if (g_Status.statsEquip[i] > 0) {
                func_06078550(0x1C0, 0x0B, pos++);
                value = g_Status.statsEquip[i];
            } else {
                func_06078550(0x1C0, 0x0D, pos++);
                value = -g_Status.statsEquip[i];
            }
            func_06078684(0x1C0, value, pos++);
        } else {
            pos += 2;
        }
    }

    pos = g_RichterMapUiPositionsB;
    buttonConfig = g_Settings.buttonConfig[0];
    func_06078550(0x1C0, g_RichterMapIconIndices[buttonConfig], pos++);
    func_06078684(0x1C0, g_Status.attackHands[0], pos++);
    buttonConfig = g_Settings.buttonConfig[2];
    func_06078550(0x1C0, g_RichterMapIconIndices[buttonConfig], pos++);
    func_06078684(0x1C0, g_Status.attackHands[1], pos++);
    func_06078684(0x1C0, g_Status.defenseEquip, pos);
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BC228, func_060BC228);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BC4E4, func_060BC4E4);

void func_060BC7A8(u32 arg0) {
    s32 first;
    s32 current;
    s32 offset;
    s32 i;
    u8* ptr;

    if (arg0 == 6) {
        offset = 0x28;
    } else if (arg0 & 1) {
        offset = 0x28;
    } else {
        offset = 0;
    }

    first = g_RichterMapRevealRowIndices[arg0];
    for (current = first; current < first + 4; current++) {
        s32 tile = current << 6;

        ptr = (u8*)tile;
        ptr += 0x25E58000 + offset;
        for (i = 0; i < 0x20; i++) {
            *ptr++ = 0;
        }

        if (offset == 0x28) {
            ptr = (u8*)(0x25E58800 + tile);
            for (i = 0; i < 0x10; i++) {
                *ptr++ = 0;
            }
        }
    }
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BC834, func_060BC834);

extern u32 D_06085534;
s32 func_060732E4(u16 arg0);

void func_060BCA10(void) {
    if (DAT_0605cd70.unk8 != 0) {
        if (DAT_0605cd70.unk8 == 1) {
            goto after;
        }
        return;
    } else {
        func_060732E4(DAT_0605cd70.unk0);
        DAT_0605cd70.unk8++;
    }
after:
    if ((DAT_06057f68 == 0) && (g_pads[0].tapped & PAD_CROSS)) {
        D_06085534 = 6;
        DAT_06057f68 = 4;
    }
    func_060BC834();
}

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BCA84, func_060BCA84);

void func_060BCDB8(void) {
    switch (DAT_0605cd70.unk8) {
    case 0:
        func_060732E4(DAT_0605cd70.unk0);
        DAT_0605cd70.unk8++;
        /* fall through */
    case 1:
        if (DAT_06057f68 == 0 && (g_pads[0].tapped & PAD_CROSS)) {
            D_06085534 = 6;
            DAT_06057f68 = 4;
        }
        if (DAT_06057f68 == 3) {
            DAT_06057f68 = 0;
        }
        if (DAT_06057f68 == 6) {
            DAT_0605cd70.unk0 = 6;
            DAT_0605cd70.unk8 = 0;
            Scl_s_reg.dispenbl &= ~0x003F;
            SclProcess = 1;
        }
        func_060BCA84();
    }
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BCE64, func_060BCE64);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BD11C, func_060BD11C);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BD2AC, func_060BD2AC);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BD3D8, func_060BD3D8);

// SortTimeAttackEntries
void func_060BD4EC(void) {
    s32 i;
    s32 isLooping;
    s32 swapTime;
    s32 swapName;

    for (i = 0; i < 28; i++) {
        D_060CEE6C[i] = TimeAttackController(i, 0);
        if (D_060CEE6C[i] == 0) {
            D_060CEE6C[i] = 1000000;
        }
        D_060CEEDC[i] = i;
    }

    do {
        isLooping = false;
        for (i = 0; i < 27; i++) {
            if (D_060CEE6C[i] > D_060CEE6C[i + 1]) {
                swapTime = D_060CEE6C[i];
                D_060CEE6C[i] = D_060CEE6C[i + 1];
                D_060CEE6C[i + 1] = swapTime;
                swapName = D_060CEEDC[i];
                D_060CEEDC[i] = D_060CEEDC[i + 1];
                D_060CEEDC[i + 1] = swapName;
                isLooping++;
            }
        }
    } while (isLooping);
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BD580, func_060BD580);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BD768, func_060BD768);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BDADC, func_060BDADC);
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BDFD4, func_060BDFD4);

void func_060BE110(void) {
    if (d_06086234 == 0) {
        memset((void*)0x25E58288, 0, 0xC);
        memset((void*)0x25E582C8, 0, 0xC);
    }

    if (d_06086250 == 0) {
        memset((void*)0x25E58348, 0, 0xC);
        memset((void*)0x25E58388, 0, 0xC);
    }

    if (g_GameClearFlag == 0) {
        memset((void*)0x25E584C8, 0, 0x10);
        memset((void*)0x25E58508, 0, 0x10);
    }
}
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BE198, func_060BE198);
