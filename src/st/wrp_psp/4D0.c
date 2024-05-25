#include "common.h"
#include "game.h"

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", func_8018A0CC);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", func_8018A118);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", func_8018A170);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", func_8018A26C);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", func_8018A380);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", func_8018A3CC);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", func_8018A424);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", func_8018A520);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", InitRoomEntities);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", func_8018A7AC);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", CreateEntityFromCurrentEntity);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", CreateEntityFromEntity);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", EntityStageNamePopup);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", EntityIsNearPlayer);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", EntityRedDoor);

// INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", Random);

u8 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}
