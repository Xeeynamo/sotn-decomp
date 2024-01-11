/*
 * File: 8DF0.c
 * Overlay: RWRP
 * Description: All reverse warp rooms.
 */

#include "game.h"
#include "rwrp.h"

INCLUDE_ASM("st/rwrp/nonmatchings/8DF0", func_80188DF0);

INCLUDE_ASM("st/rwrp/nonmatchings/8DF0", func_80188ED0);

extern u8* D_801805B8[];
extern Entity D_8007D858;
extern char D_801805E0;
extern u16 D_80180440[];
extern u8 D_801805F8[];
extern u8 D_801805D8[];
extern u16 D_801805E8[];
void EntityBreakable(Entity* entity) {
    Entity* temp_v0;
    u16 temp_s0 = entity->params >> 0xC;

    if (entity->step != 0) {
        func_8018D6B0(D_801805B8[temp_s0], entity);
        if (entity->unk44 != 0) {
            g_api.PlaySfx(NA_SE_BREAK_CANDLE);
            temp_v0 = AllocEntity(&D_8007D858, &D_8007D858 + 32);
            if (temp_v0 != NULL) {
                CreateEntityFromCurrentEntity(2, temp_v0);
                temp_v0->params = (&D_801805E0)[temp_s0];
            }
            ReplaceBreakableWithItemDrop(entity);
        }
    } else {
        InitializeEntity(D_80180440);
        entity->zPriority = g_unkGraphicsStruct.g_zEntityCenter.S16.unk0 - 20;
        entity->blendMode = D_801805F8[temp_s0];
        entity->hitboxHeight = D_801805D8[temp_s0];
        entity->animSet = D_801805E8[temp_s0];
    }
}

INCLUDE_ASM("st/rwrp/nonmatchings/8DF0", func_801891C0);

INCLUDE_ASM("st/rwrp/nonmatchings/8DF0", func_80189E9C);
