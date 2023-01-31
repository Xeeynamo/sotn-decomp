#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

extern u16 D_80072F6A[];
extern s16 D_800733F8;
extern u16 D_800733FA;

void func_80113AAC(void) {
    s32 temp_v1;
    s32 var_s1;
    int new_var;
    var_s1 = 0;
    D_80072F6A[0]++;
    if (func_8010FDF8(2) == 0) {
        switch (D_80073406) {
        case 0:
            if (D_80072F20 & 2) {
                func_801139CC(3);
                if (((s16)D_80072F6A[0]) >= 5) {
                    D_80073406 = 2;
                    D_800733F6 = 0x800;
                    D_800733FA = 2;
                    D_800733F8 = 0;
                    D_800733F1 |= 4;
                    D_800733EC = (D_800733EC + 1) & 1;
                    func_8010DA48(0x2B);
                } else {
                    D_80073406 = 3;
                }
            } else if (((s16)D_80072F6A[0]) >= 0x1D) {
                D_80073406 = 1;
                D_800733E4 = -0x60000;
                func_8010DA48(0x1B);
            }
            break;

        case 1:
            if (D_80072F20 & 2) {
                D_80073406 = 2;
                func_801139CC(3);
            } else {
                g_EntityArray[PLAYER_CHARACTER].accelerationY += 0x6000;
                if (g_EntityArray[PLAYER_CHARACTER].accelerationY > 0x8000) {
                    var_s1 = 1;
                }
            }
            break;

        case 2:
            D_800733F8 = 0;
            D_800733FA = 2;
            g_EntityArray[PLAYER_CHARACTER].unk19 |= 4;
            if (((s16)D_80072F6A[0]) >= 0x39) {
                func_8010DA48(0x2D);
                D_800733F6 = 0;
                D_80073406 = 4;
                g_EntityArray[PLAYER_CHARACTER].unk19 &= 0xFB;
                D_800733EC = (D_800733EC + 1) & 1;
            }
            break;

        case 3:
            if (((s16)D_80072F6A[0]) >= 0x15) {
                var_s1 = 1;
            }
            break;

        case 4:
            g_EntityArray[PLAYER_CHARACTER].accelerationY += 0x1000;
            if (D_8007342A < 0) {
                var_s1 = 2;
            }
            break;
        }

        if (var_s1 != 0) {
            new_var = 0;
            if ((var_s1 - 1) != new_var) {
                func_8010DA48(0x1C);
            }
            D_800733EE = 0x8100;
            D_80073406 = 1;
            D_80073404 = 4;
        }
    }
}