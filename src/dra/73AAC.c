#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

void func_80113AAC(void) {
    s32 var_s1;
    s32 temp;
    var_s1 = 0;
    D_80072F6A[0]++;
    if (func_8010FDF8(2) == 0) {
        switch (PLAYER.unk2E) {
        case 0:
            if (D_80072F20 & 2) {
                func_801139CC(3);
                if ((D_80072F6A[0]) >= 5) {
                    PLAYER.unk2E = 2;
                    PLAYER.unk1E = 0x800;
                    PLAYER.unk22 = 2;
                    PLAYER.unk20 = 0;
                    PLAYER.unk19 |= 4;
                    PLAYER.facing = (PLAYER.facing + 1) & 1;
                    func_8010DA48(0x2B);
                } else {
                    PLAYER.unk2E = 3;
                }
            } else if (D_80072F6A[0] > 28) {
                PLAYER.unk2E = 1;
                PLAYER.accelerationY = -0x60000;
                func_8010DA48(0x1B);
            }
            break;

        case 1:
            if (D_80072F20 & 2) {
                PLAYER.unk2E = 2;
                func_801139CC(3);
            } else {
                PLAYER.accelerationY += 0x6000;
                if (PLAYER.accelerationY > 0x8000) {
                    var_s1 = 1;
                }
            }
            break;

        case 2:
            D_800733F8 = 0;    // TODO: !FAKE: symbol should be PLAYER.unk20
            D_800733FA = 2;    // TODO: !FAKE: symbol should be PLAYER.unk22
            PLAYER.unk19 |= 4; // But it doesn't match with them for some reason
            if (D_80072F6A[0] >= 0x39) {
                func_8010DA48(0x2D);
                PLAYER.unk1E = 0;
                PLAYER.unk2E = 4;
                PLAYER.unk19 &= 0xFB;
                PLAYER.facing = (PLAYER.facing + 1) & 1;
            }
            break;

        case 3:
            if (D_80072F6A[0] > 20) {
                var_s1 = 1;
            }
            break;

        case 4:
            PLAYER.accelerationY += 0x1000;
            if (D_8007342A < 0) {
                var_s1 = 2;
            }
            break;
        }

        if (var_s1 != 0) {
            temp = 0; // TODO: !FAKE
            if ((var_s1 - 1) != temp) {
                func_8010DA48(0x1C);
            }
            PLAYER.palette = 0x8100;
            PLAYER.unk2E = 1;
            PLAYER.step = 4;
        }
    }
}