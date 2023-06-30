/*
 * Overlay: ST0
 * Description: Cutscene of Richter talking to Dracula
 */

#include "st0.h"

INCLUDE_ASM("asm/us/st/st0/nonmatchings/28BF8", func_801A8BF8);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/28BF8", func_801A8CB0);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/28BF8", func_801A8E34);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/28BF8", func_801A8E60);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/28BF8", func_801A910C);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/28BF8", EntityDialogue);

void func_801AA218(s16 arg0) {
    s16 temp_a1;
    s16 temp_v1;
    s16 var_v0;

    temp_a1 = ((0xE0 - arg0) / 2) + 0x80;
    temp_v1 = temp_a1 - *D_8009740C;
    if (temp_v1 >= 3) {
        *D_8009740C = *D_8009740C + 2;
    } else if (temp_v1 < -2) {
        *D_8009740C = *D_8009740C - 2;
    } else {
        *D_8009740C = temp_a1;
    }
}

INCLUDE_ASM("asm/us/st/st0/nonmatchings/28BF8", EntityCutscene);