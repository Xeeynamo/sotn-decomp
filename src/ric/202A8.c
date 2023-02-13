
#include "ric.h"

extern AnimationFrame* D_80155534;

void func_8015C2A8(void) {
    bool loadAnim = 0;
    s32 temp;

    FntPrint("pl_vram_flag:%04x\n", D_80072F20.pl_vram_flag);
    FntPrint("pl_high_jump_timer:%04x\n", D_80072F20.pl_high_jump_timer);
    FntPrint("pl_step_s:%02x\n", PLAYER.unk2E);
    D_80072F20.pl_high_jump_timer++;

    switch (PLAYER.unk2E) {
    case 0:
        if (D_80072EE8 & 0xA000) {

            if (PLAYER.facing == 0) {
                temp = D_80072EE8 & 0x2000;
            } else {
                temp = D_80072EE8 & 0x8000;
            }
            if (temp == 0) {
                func_8015C93C(0x1000);
            }
        } else {
            func_8015C93C(0x1000);
        }
        if (D_80072F20.pl_vram_flag & 2) {
            func_80158B04(3);
            D_80072F62 = 0;
            PLAYER.unk2E = 2;
        } else if (D_80072F62 >= 0x1D) {
            PLAYER.unk2E = 1;
            PLAYER.accelerationY = -0x60000;
        }
        break;
    case 1:
        if (D_80072F20.pl_vram_flag & 2) {
            PLAYER.unk2E = 2;
            func_80158B04(3);
            D_80072F20.pl_high_jump_timer = 0;
        } else {
            PLAYER.accelerationY += 0x6000;
            if (PLAYER.accelerationY > 0x8000) {
                loadAnim = true;
            }
        }
        break;

    case 2:
        if (D_80072F20.pl_high_jump_timer >= 5) {
            loadAnim = 1;
        }
        break;
    }
    if (loadAnim) {
        func_8015C920(&D_80155534);
        func_8015C908(4);
    }
}

INCLUDE_ASM("asm/ric/nonmatchings/1FCD0", func_8015C4AC);

INCLUDE_ASM("asm/ric/nonmatchings/1FCD0", func_8015C6D4);

void func_8015C908(s32 step) {
    PLAYER.step = step;
    PLAYER.unk2E = 0;
}