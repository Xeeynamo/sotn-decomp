#include "common.h"
#include <game.h>

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", GsInitVcount);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetRCnt);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", GetRCnt);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", StartRCnt);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", StopRCnt);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", ResetRCnt);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", GsGetVcount);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", GsClearVcount);

s32 rsin(s32 arg0) {
    if (arg0 < 0) {
        return -sin_1(-arg0 & 0xFFF);
    }
    return sin_1(arg0 & 0xFFF);
}

extern s16 D_8002C3CC[];
extern s16 rsin_tbl[];
s32 sin_1(s32 arg0) {
    if (arg0 < 0x801) {
        if (arg0 < 0x401) {
            return rsin_tbl[arg0];
        } else {
            return rsin_tbl[0x800 - arg0];
        }
    } else {
        if (arg0 < 0xC01) {
            return -1 * D_8002C3CC[arg0];
        } else {
            return -1 * rsin_tbl[0x1000 - arg0];
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", rcos);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetFogNear);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", InitGeom);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SquareRoot0);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", func_80016F7C);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", func_80017008);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", func_80017078);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", func_80017134);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SquareRoot12);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", CompMatrix);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", func_8001741C);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", func_80017528);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", func_8001760C);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetMulMatrix);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", func_80017804);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", func_80017964);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", func_80017994);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", PushMatrix);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", PopMatrix);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", func_80017BF8);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", func_80017C40);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", ReadColorMatrix);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", TransMatrix);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", ScaleMatrix);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetRotMatrix);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetLightMatrix);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetColorMatrix);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetTransMatrix);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetVertex0);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetVertex1);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetVertex2);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetVertexTri);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetRGBfifo);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetIR123);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetIR0);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetSZfifo3);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetSZfifo4);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetSXSYfifo);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetRii);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetMAC123);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetData32);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetDQA);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetDQB);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetBackColor);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetFarColor);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetGeomOffset);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", SetGeomScreen);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", LocalLight);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", DpqColor);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", NormalColor);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", NormalColor3);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", NormalColorDpq);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", NormalColorDpq3);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", NormalColorCol);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", NormalColorCol3);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", ColorDpq);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", ColorCol);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", AverageSZ3);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", AverageSZ4);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", RotTransPers);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", RotTransPers3);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", RotTrans);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", NormalClip);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", RotTransPers4);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", RotAverage3);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", RotAverage4);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", RotAverageNclip3);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", RotAverageNclip4);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", RotAverageNclipColorCol3);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", RotMatrix);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", RotMatrixYXZ);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", RotMatrixX);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", RotMatrixY);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", RotMatrixZ);

long ratan2(long dx, long dy) {
    long ret;
    bool flag0;
    bool flag1;
    s32 lookup;

    flag0 = false;
    flag1 = false;
    if (dy < 0) {
        flag0 = true;
        dy = -dy;
    }
    if (dx < 0) {
        flag1 = true;
        dx = -dx;
    }
    if ((dy == 0) && (dx == 0)) {
        return 0;
    }
    if (dx < dy) {
        if (dx & 0x7FE00000) {
            lookup = (dx / (dy >> 10));
        } else {
            lookup = ((dx << 10) / dy);
        }
        ret = g_AtanTable[lookup];
    } else {
        if (dy & 0x7FE00000) {
            lookup = (dy / (dx >> 10));
        } else {
            lookup = ((dy << 10) / dx);
        }
        ret = 0x400 - g_AtanTable[lookup];
    }
    if (flag0)
        ret = 0x800 - ret;
    if (flag1)
        ret = -ret;
    return ret;
}

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", patch_gte);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", func_8001929C);

INCLUDE_ASM("asm/us/main/nonmatchings/72A4", FlushCache);

void func_800192DC(s32 arg0, s32 arg1) {
    D_800987C8 = arg0;
    D_80098894 = arg1;
    StClearRing();
}

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/main/nonmatchings/72A4", CdInit);
#else
int CdInit() {
    int i;

    for (i = 4; i != -1; i--) {
        if (CdReset(1)) {
            CdSyncCallback(def_cbsync);
            CdReadyCallback(def_cbready);
            CdReadCallback(def_cbread);
            return true;
        }
    }

    printf("CdInit: Init failed\n");
    return false;
}
#endif

void def_cbsync(u_char intr, u_char* result) {
    DeliverEvent(HwCdRom, EvSpCOMP);
}

void def_cbready(u_char intr, u_char* result) { DeliverEvent(HwCdRom, EvSpDR); }

void def_cbread(u_char intr, u_char* result) { DeliverEvent(HwCdRom, EvSpDR); }
