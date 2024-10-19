#include "common.h"
#include "no0.h"

INCLUDE_ASM("st/no0/nonmatchings/clock_room", func_us_801CCC74);

INCLUDE_ASM("st/no0/nonmatchings/clock_room", func_us_801CD750);

INCLUDE_ASM("st/no0/nonmatchings/clock_room", func_us_801CD864);

void UpdateStatueTiles(s32 tilePos, s32 tile) {
    u32 i;

    for (i = 0; i < 6; i++) {
        g_Tilemap.fg[tilePos] = tile;
        tilePos++;
        g_Tilemap.fg[tilePos] = tile;
        tilePos += 15;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/clock_room", func_us_801CDB20);

INCLUDE_ASM("st/no0/nonmatchings/clock_room", func_us_801CDE48);

INCLUDE_ASM("st/no0/nonmatchings/clock_room", func_us_801CE058);

INCLUDE_ASM("st/no0/nonmatchings/clock_room", func_us_801CE0F8);

void func_us_801CE2D8(void) {}
