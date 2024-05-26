#include "../wrp/wrp.h"

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_red_door", EntityIsNearPlayer);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_red_door", EntityRedDoor);

// TODO move this function to the next file
// but only when the func Update is matching
s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return (g_randomNext >> 0x18) & 0xFF;
}
