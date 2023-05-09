#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

void func_800E6FD4(void) {
    Primitive* prim;
    u8 temp;
    s32 temp2;

    if (!(g_pads[0].tapped & PAD_START) || !g_IsTimeAttackUnlocked) {
        switch (D_80073060) {
        case 0:
            if (D_8006C3B0 == 0) {
                func_800EA538(0);
                func_800EA5E4(0x1A);
                g_CdStep = CdStep_LoadInit;
                D_8006BAFC = CdFileType_24;
                func_800E3618(0x140);
                D_8013640C = AllocPrimitives(PRIM_GT4, 2);
                prim = &g_PrimBuf[D_8013640C];
                func_80107360(prim, 44, 96, 232, 32, 0, 0);
                func_801072BC(prim);
                prim->tpage = 0x1C;
                prim->blendMode = 4;
                prim->p1 = 0x40;
                prim = prim->next;
                func_80107360(prim, 60, 208, 192, 16, 0, 32);
                func_801072DC(prim);
                prim->tpage = 0x1C;
                prim->blendMode = 8;
                D_80073060++;
                return;
            }
            break;

        case 1:
            prim = &g_PrimBuf[D_8013640C];
            prim->p1--;
            if (prim->p1 == 0) {
                D_80073060++;
            }
            break;

        case 2:
            temp2 = D_8013640C;
            prim = &g_PrimBuf[temp2];
            temp = prim->r0 + 1;
            func_80107250(prim, temp);
            if (temp == 96) {
                temp2 = prim->next;
#if defined(VERSION_US)
                ((Primitive*)temp2)->blendMode = 8;
#elif defined(VERSION_HD)
                ((Primitive*)temp2)->blendMode = 0;
#endif
            }
            if (temp == 128) {
                prim->p1 = 128;
                D_80073060++;
            }
            break;

        case 3:
            prim = &g_PrimBuf[D_8013640C];
            prim->p1--;
            if (prim->p1 == 0) {
                D_80073060++;
            }
            break;

        case 4:
            prim = &g_PrimBuf[D_8013640C];
            temp = prim->r0 - 1;
            func_80107250(prim, temp);
            if (temp == 64) {
                ((Primitive*)prim->next)->blendMode = 8;
            }
            if (temp == 0) {
                FreePrimitives(D_8013640C);
                D_80073060++;
            }
            break;

        case 5:
            if (D_8006C3B0 == 0) {
                D_8003C728 = 1;
                D_8003C100 = 1;
                D_80073060++;
            }
            break;

        case 6:
            g_api.o.unk08();
            if (D_8003C728 == 0) {
                func_800E4970();
            }
            break;
        }

    } else {
        func_800E4970();
    }
}

void nullsub_9(void) {}

void func_800E738C(void) {
    if (D_80073060 == 1) {
        if ((g_UseDisk && D_8006C3B0 == 0) ||
            (!g_UseDisk && func_800E81FC(6, SimFileType_System) >= 0 &&
             func_800E81FC(7, SimFileType_System) >= 0)) {
            if (func_80131F68() != 0) {
                PlaySfx(0x80);
            }
            func_800E346C();
            D_80073060++;
            return;
        }
    }
    g_api.o.unk3C();
}

void func_800E7458(void) {
    s32 pad[0x40];

    switch (D_80073060) {
    case 0:
        g_StageId = STAGE_SEL;
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            D_8006BAFC = CdFileType_StageChr;
            g_mapTilesetId = STAGE_SEL;
        }
        D_80073060++;
        break;
    case 1:
        if (g_UseDisk && D_8006C3B0 != 0)
            break;

        if (g_UseDisk || func_800E81FC(12, SimFileType_System) >= 0) {
            D_80073060++;
        }
        break;
    case 2:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            D_8006BAFC = CdFileType_StageSfx;
        }
        D_80073060++;
        break;
    case 3:
        if (g_UseDisk && D_8006C3B0 != 0)
            break;

        if (g_UseDisk || func_800E81FC(0, SimFileType_Vh) >= 0 &&
                             func_800E81FC(0, SimFileType_Vb) >= 0) {
            D_80073060++;
        }
        break;
    case 4:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            D_8006BAFC = CdFileType_StagePrg;
        }
        D_80073060++;
        break;
    case 5:
        if (g_UseDisk && D_8006C3B0 != 0)
            break;

        if (g_UseDisk || func_800E81FC(0, SimFileType_StagePrg) >= 0) {
            D_8003C9A4 = 0;
            D_80073060++;
        }
        break;
    case 6:
        g_api.o.Update();
        break;
    case 7:
        func_800E4970();
        break;
    }
}

#if defined(VERSION_US)
INCLUDE_ASM("asm/us/dra/nonmatchings/46FD4", func_800E768C);
#elif defined(VERSION_HD)
INCLUDE_ASM("asm/hd/dra/nonmatchings/46FD4", func_800E768C);
#endif

void func_800E7AEC(void) {
    switch (D_8003C734) {
    case 0:
    case 1:
#if defined(VERSION_US)
    case 99:
#endif
        func_800E451C();
        break;
    case 2:
        func_800E4A14();
        break;
    case 3:
        func_800E5584();
        break;
    case 4:
        func_800E6358();
        break;
    case 5:
        func_800E6FD4();
        break;
    case 6:
        nullsub_9();
        break;
    case 7:
        func_800E738C();
        break;
    case 8:
        func_800E7458();
        break;
    case 9:
        func_800E768C();
        break;
    }
}
