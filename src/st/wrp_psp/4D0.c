#include "common.h"
#include "game.h"

// redeclaring for the moment due to header conflict with Random() definition
typedef struct {
    /* 0x0 */ u16 posX;
    /* 0x2 */ u16 posY;
    /* 0x4 */ u16 entityId;
    /* 0x6 */ u16 entityRoomIndex;
    /* 0x8 */ u16 params;
} LayoutEntity; // size = 0xA

extern LayoutEntity* g_LayoutObjHorizontal;
extern LayoutEntity* g_LayoutObjVertical;

void FindFirstEntityToTheRight(s16 arg0) {
    while (1) {
        LayoutEntity* layoutEntity = g_LayoutObjHorizontal;
        if ((layoutEntity->posX != 0xFFFE) &&
            ((s32)layoutEntity->posX >= arg0)) {
            break;
        }

        g_LayoutObjHorizontal++;
    }
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", func_8018A118);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", func_8018A170);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", func_8018A26C);

void FindFirstEntityAbove(s16 arg0) {
    while (true) {
        u16* ptr = &g_LayoutObjVertical->posY;
        if ((*ptr != (u16)~1) && !(*ptr < arg0)) {
            break;
        }
        g_LayoutObjVertical++;
    }
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", func_8018A3CC);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", func_8018A424);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", func_8018A520);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", InitRoomEntities);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", func_8018A7AC);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", CreateEntityFromCurrentEntity);

extern PfnEntityUpdate* PfnEntityUpdates;
void CreateEntityFromEntity(u16 entityId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->entityId = entityId;
    entity->pfnUpdate = PfnEntityUpdates[entityId - 1];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", EntityStageNamePopup);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", EntityIsNearPlayer);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4D0", EntityRedDoor);

u8 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}
