#include "sel.h"

void func_801B60D4(void) {
    Entity* ent;
    Entity* ent4;
    s32 i;
    s32 var_v1;

    switch (D_8003C9A4) {
    case 0:
        if (D_8006C3B0 == 0) {
            D_8003C728 = 1;
            if (D_800978B4 == 0) {
                D_8003C100 = 2;
            } else {
                D_8003C100 = 3;
            }
            D_8003C9A4++;
        }
        break;

    case 1:
        func_801B9C80();
        if (D_8003C728 == 0) {
            D_8003C100 = 0;
            func_801B18F4();
        }
        if (D_800978B4 != 0) {
            D_80073060++;
        } else {
            D_80073060 = 0x100;
        }
        D_8003C9A4++;
        break;

    case 2:
        ent = g_EntityArray;
        for (i = 0; i < 9; i++) {
            func_801B4B30(ent);
            ent++;
        }

        D_801D6B24 = 0;
        D_801BD030 = 0;
        g_EntityArray[8].subId = *(u16*)&D_800978B4 - 1;
        g_api.func_800EA5E4(0x16);
        g_api.func_800EA5E4(0);
        g_api.func_800EA5E4(0x8005);
        g_api.func_800EAF28(0x8000);
        D_8003C9A4++;
        break;

    case 3:
        ent4 = &g_EntityArray[4];
        func_801B5A7C();
        func_801B69F8(ent4);
        func_801B4C68();
        func_801B519C();
        func_801B4D78();
        func_801B4DE0();
        ent = ent4 - 1;
        for (i = 3; i < 8; i++) {
            var_v1 = D_801D6B24;
            if (var_v1 < 0) {
                var_v1 += 0xFFFF;
            }
            ent->posX.i.hi = (s16)(var_v1 >> 0x10) + ent->unk80.modeS16.unk2;
            ent++;
        }

        if (D_801BD030 != 0) {
            ent = g_EntityArray;
            for (i = 0; i < 9; i++) {
                func_801B4B30(ent);
                ent++;
            }

            for (i = 0; i < 9; i++) {
                func_801B4B30(ent);
                ent++;
            }

            D_8003C9A4++;
        }
        break;

    case 4:
        ClearImage(&D_8018258C, 0, 0, 0);
        D_8003C9A4++;
        break;

    case 5:
        func_801B1B88();
        D_8003C9A4++;
        break;

    case 6:
        g_api.func_800EA5E4(0);
        D_8003C9A4++;
        break;

    case 7:
        ent4 = &g_EntityArray[4];
        if (func_801B79D4(ent4) != 0) {
            g_EntityArray[1].step = 0;
            D_801BC3E4 = 1;
            D_8003C9A4++;
        }
        break;

    case 8:
        func_801B4FFC();
        if (D_801BC3E4 == 0) {
            D_80073060 += 1;
        }
        break;
    }
}
