#include "dra.h"
#include "objects.h"
#include "sfx.h"

s32 DecompressData(u8* dst, u8* src);

INCLUDE_ASM("dra/nonmatchings/47BB8", func_800E7BB8);

void func_800E7D08(void) {
    s32 i;

    for (i = 0; i < 1024; i++) {
        D_80136460[i] = 0;
        D_80136C60[i] = 0;
    }

    D_800A04EC = 1;
}

void LoadStageTileset(u8* pTilesetData, s32 y) {
    RECT rect;
    u8* pTilesetDataSrc;
    s32 i;

    rect.w = 0x20;
    rect.h = 0x80;
    for (i = 0; i < 0x20; i++) {
        pTilesetDataSrc = pTilesetData + 0x2000 * i;
        rect.x = D_800AC958[i];
        if (i & 2) {
            rect.y = y + 0x80;
        } else {
            rect.y = y;
        }

        LoadImage(&rect, pTilesetDataSrc);
        while (DrawSync(1)) {
        }
    }
}

// Not matching due to case 2/11
#ifndef NON_EQUIVALENT
s32 func_800E7E08(u32);
INCLUDE_ASM("dra/nonmatchings/47BB8", func_800E7E08);
#else
extern u32 D_8006EBCC;
extern u32 D_80070BCC;
extern u32 D_800A04CC;
extern s32 g_VabAddrs[];
extern const char aPqes_1[]; // pQES
extern RECT rect;
extern s32* g_StageOverlay;

s32 func_800E7E08(u32 arg0) {
    s32 i;
    void (**pSrc)();
    void (**pDst)();

    switch (arg0) {
    case 0:
        pSrc = g_StageOverlay;
        i = 0;
        pDst = &g_api.o;
        do {
            i++;
            *pDst++ = *pSrc++;
        } while (i < 0x10);
        break;
    case 19:
        LoadTPage((u8*)0x80280000, 0, 0, 0x2C0, 0x100, 0x100, 0x80);
        LoadTPage((u8*)0x80284000, 0, 0, 0x2C0, 0x180, 0x80, 0x80);
        break;
    case 9:
        LoadTPage(g_Pix[0], 0, 0, 0x240, 0x100, 0x100, 0x80);
        break;
    case 10:
        LoadTPage(g_Pix[2], 0, 0, 0x240, 0x180, 0x100, 0x80);
        break;
    case 20:
        LoadTPage(0x80280000, 2, 0, 0x20, 0x100, 0x60, 0x70);
        break;
    case 1:
        LoadStageTileset(0x80180000, 0x100);
        DrawSync(0);
        LoadImage(&rect, &D_800A04CC);
        LoadImage(&rect + 2, (u32*)0x801C0000);
        while (DrawSync(1))
            ;
        StoreImage(&g_Vram.D_800ACDA8, &D_8006EBCC);
        break;
    default:
        break;
    case 2:
    case 11: // .rodata+0x8,0x2c
        LoadStageTileset(0x80280000, 0);
        DrawSync(0);
        StoreImage(&g_Vram.D_800ACDB8, g_Clut);
        if (arg0 == 0xB) {
            StoreImage(&g_Vram.D_800ACDB8, g_Clut + 0x4000);
            DrawSync(0);
            LoadImage(&g_Vram.D_800ACDB0, g_Clut + 0x4000);
            break;
        }
        break;
    case 12:
    case 13: // .rodata+0x30,0x34
        LoadStageTileset(0x80280000, 0x100);
        if (arg0 == 0xD) {
            LoadImage(&rect, &D_800A04CC);
        }
        DrawSync(0);
        break;
    case 4:
        while (SsVabTransCompleted(SS_IMEDIATE) != 1)
            ;
        if (SsVabOpenHeadSticky(
                D_8013644C->addr, D_800A0248, g_VabAddrs[D_800A0248]) < 0) {
            return -1;
        }
        break;
    case 5:
        if (SsVabTransBodyPartly(
                (s32*)0x80280000, D_8013644C->size, D_800A0248) == -1) {
            return -1;
        }
        while (SsVabTransCompleted(SS_IMEDIATE) != 1)
            ;
        break;
    case 7:
        if (g_StageId == STAGE_LIB) {
            func_80131EBC(&aPqes_1, 0x202);
        }
        if (g_StageId == STAGE_DAI) {
            func_80131EBC(&aPqes_1, 0x204);
        }
        break;
    case 6:
        LoadImage(&g_Vram.D_800ACDC0, (u32*)0x80180000);
        break;
    case 14:
        LoadImage(&g_Vram.D_800ACDD0, (u32*)0x80280000);
        break;
    case 21:
        LoadImage(&g_Vram.D_800ACDE0, (u32*)0x80280000);
        break;
    case 15:
        LoadImage(&g_Vram.D_800ACDD8, (u32*)0x80280000);
        break;
    case 16:
        LoadImage(&g_Vram.D_800ACDB8, (u32*)0x80280000);
        StoreImage(&g_Vram.D_800ACDB8, &D_80070BCC);
        break;
    case 17:
        LoadImage(&g_Vram.D_800ACDA8, (u32*)0x80280000);
        StoreImage(&g_Vram.D_800ACDA8, &g_Clut);
        break;
    }

    return 0;
}
#endif

s32 LoadFileSim(s32 fileId, SimFileType type) {
    char buf[33];
    s32 fid;

    func_800E7D08();
    D_800A04EC = 1;
    D_8013644C = &D_800A024C[fileId];
    if (type == SimFileType_StagePrg) {
        STRCPY(buf, "sim:c:\\bin\\");
        D_8013644C = &D_80136450;
        strcat(buf, g_StagesLba[g_StageId].ovlName);
        strcat(buf, ".bin");
        D_8013644C->addr = (u8*)0x80180000;
        D_8013644C->path = buf;
        D_8013644C->size = 0x60000;
        D_8013644C->type = 0;
    }
    if (type == SimFileType_Vh) {
        if (fileId & 0x8000) {
            D_8013644C = &D_800A036C[fileId & 0x7FFF];
        } else {
            STRCPY(buf, "sim:c:\\sound\\data\\sd_");
            D_8013644C = &D_80136450;
            strcat(buf, g_StagesLba[g_StageId].name);
            strcat(buf, ".vh");
            D_8013644C->addr = (u8*)aPbav_2;
            D_8013644C->path = buf;
            D_8013644C->size = g_StagesLba[g_StageId].vhLen;
            D_8013644C->type = 4;
        }
        if (D_8013644C->addr == aPbav) {
            D_800A0248 = 0;
        }
        if (D_8013644C->addr == aPbav_0) {
            D_800A0248 = 1;
        }
        if (D_8013644C->addr == aPbav_2) {
            D_800A0248 = 3;
        }
        if (D_8013644C->addr == aPbav_1) {
            D_800A0248 = 2;
        }
        SsVabClose(D_800A0248);
    }
    if (type == SimFileType_Vb) {
        if (fileId & 0x8000) {
            D_8013644C = &D_800A036C[fileId & 0x7FFF];
        } else {
            D_8013644C = &D_80136450;
            STRCPY(buf, "sim:c:\\sound\\data\\sd_");
            strcat(buf, g_StagesLba[g_StageId].name);
            strcat(buf, ".vb");
            D_8013644C->addr = (u8*)0x80280000;
            D_8013644C->path = buf;
            D_8013644C->size = g_StagesLba[g_StageId].vbLen;
            D_8013644C->type = 5;
        }
    }
    if (type == SimFileType_Seq) {
        D_8013644C = &D_800A04AC[fileId];
    }
    if (type == SimFileType_StageChr) {
        D_8013644C = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\");
        strcat(buf, g_StagesLba[g_StageId].gfxName);
        strcat(buf, ".bin");
        D_8013644C->addr = DEBUG_PTR;
        D_8013644C->size = 0x40000;
        D_8013644C->path = buf;
        D_8013644C->type = 2;
    }
    if (type == SimFileType_Weapon0Prg) {
        D_8013644C = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\w0_000.bin");
        buf[15] = ((fileId / 10) % 10) + '0';
        buf[16] = (fileId % 10) + '0';
        D_8013644C->path = buf;
        D_8013644C->size = 0x3000;
        D_8013644C->addr = WEAPON0_PTR;
        D_8013644C->type = 8;
    }
    if (type == SimFileType_Weapon1Prg) {
        D_8013644C = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\w1_000.bin");
        buf[15] = ((fileId / 10) % 10) + '0';
        buf[16] = (fileId % 10) + '0';
        D_8013644C->path = buf;
        D_8013644C->addr = WEAPON1_PTR;
        D_8013644C->size = 0x3000;
        D_8013644C->type = 8;
    }
    if (type == SimFileType_Weapon0Chr) {
        D_8013644C = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\f0_000.bin");
        buf[15] = ((fileId / 10) % 10) + '0';
        buf[16] = (fileId % 10) + '0';
        D_8013644C->path = buf;
        D_8013644C->addr = g_Pix[0];
        D_8013644C->size = 0x4000;
        D_8013644C->type = 9;
    }
    if (type == SimFileType_Weapon1Chr) {
        D_8013644C = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\f1_000.bin");
        buf[15] = ((fileId / 10) % 10) + '0';
        buf[16] = (fileId % 10) + '0';
        D_8013644C->path = buf;
        D_8013644C->addr = g_Pix[2];
        D_8013644C->size = 0x4000;
        D_8013644C->type = 10;
    }
    if (type == SimFileType_FamiliarPrg) {
        D_8013644C = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\tt_000.bin");
        buf[16] = (fileId % 10) + '0';
        D_8013644C->path = buf;
        D_8013644C->addr = FAMILIAR_PTR;
        D_8013644C->size = 0xA000;
        D_8013644C->type = 18;
    }
    if (type == SimFileType_FamiliarChr) {
        D_8013644C = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\ft_000.bin");
        buf[16] = (fileId % 10) + '0';
        D_8013644C->path = buf;
        D_8013644C->addr = DEBUG_PTR;
        D_8013644C->size = 0x6000;
        D_8013644C->type = 19;
    }
    if (type == SimFileType_Monster) {
        D_8013644C = &D_80136450;
        STRCPY(buf, "sim:c:\\bin\\mo_000.bin");
        buf[14] = fileId / 100 + '0';
        buf[15] = fileId / 10 - fileId / 100 * 10 + '0';
        buf[16] = fileId % 10 + '0';
        D_8013644C->path = buf;
        D_8013644C->addr = DEBUG_PTR;
        D_8013644C->size = 0x5800;
        D_8013644C->type = 20;
    }

    fid = open(D_8013644C->path, O_RDONLY);
    if (fid < 0) {
        FntPrint("o err:%s\n", D_8013644C->path);
        D_800A04EC = 0;
        return -1;
    }
    if (read(fid, D_8013644C->addr, D_8013644C->size) < 0) {
        FntPrint("r err\n");
        D_800A04EC = 0;
        return -1;
    }
    if (close(fid) < 0) {
        FntPrint("cl err\n");
        D_800A04EC = 0;
        return -1;
    }
    if (func_800E7E08(D_8013644C->type) < 0) {
        FntPrint("tr err\n");
        D_800A04EC = 0;
        return -1;
    }
    D_800A04EC = 0;
    return 0;
}

void ResetPadsRepeat(void) {
    s8* ptr;
    s32 i;

    g_pads[0].repeat = 0;
    ptr = g_PadsRepeatTimer;

    for (i = 0; i < LEN(g_PadsRepeatTimer); i++) {
        *ptr++ = 0x10;
    }
}

void UpdatePadsRepeat(void) {
    u16 button = 1;
    u16 repeat = 0;
    u16 unk = g_pads[0].tapped;
    u16 pressed = g_pads[0].pressed;
    u8* timers = g_PadsRepeatTimer;
    s32 i = 0;

    while (i < 0x10) {
        if (pressed & button) {
            if (unk & button) {
                repeat |= button;
                timers[0] = 0x10;
            } else {
                if (--timers[0] == 0xFF) {
                    repeat |= button;
                    timers[0] = 5;
                }
            }
        }
        i++;
        timers++;
        button <<= 1;
    }
    g_pads[0].repeat = repeat;
}

void InitializePads(void) {
    Pad* pad;
    s32 i;

    PadInit(0);
    for (pad = g_pads, i = 0; i < PAD_COUNT; i++, pad++) {
        pad->tapped = 0;
        pad->previous = 0;
        pad->pressed = 0;
    }
    ResetPadsRepeat();
}

void ReadPads(void) {
    Pad* pad;
    s32 i;
    u_long padd;

    for (pad = g_pads, i = 0; i < PAD_COUNT; i++, pad++) {
        pad->previous = pad->pressed;
        padd = PadRead(i >> 1);
        if (!(i & 1))
            pad->pressed = padd;
        else
            pad->pressed = padd >> 0x10;
        pad->tapped = (pad->pressed ^ pad->previous) & pad->pressed;
    }
    UpdatePadsRepeat();
}
