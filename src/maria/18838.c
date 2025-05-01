// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

void func_pspeu_092BEA38(Entity* entity, s32 setUnk6C) {
    if (setUnk6C >= 0x80) {
        entity->drawMode = entity->drawFlags = FLAG_DRAW_DEFAULT;
        entity->unk6C = 0x80;
    } else {
        entity->drawMode = DRAW_TPAGE | DRAW_TPAGE2;
        entity->drawFlags = FLAG_DRAW_UNK8;
        entity->unk6C = setUnk6C;
    }
}

s32 func_pspeu_092BEAB0(s16 setUnk80) {
    Entity* entity = (Entity*)MarGetFreeEntity(0x38, 0x40);
    if (entity == NULL) {
        return -1;
    }
    DestroyEntity(entity);
    entity->entityId = E_UNK_16;
    entity->posX.val = g_Entities->posX.val;
    entity->posY.val = g_Entities->posY.val;
    entity->ext.maria092BEB40.unk80 = setUnk80;
    entity->ext.maria092BEB40.unk82 = 1;
    return 0;
}

INCLUDE_ASM("maria_psp/nonmatchings/18838", func_pspeu_092BEB40);

INCLUDE_ASM("maria_psp/nonmatchings/18838", func_pspeu_092BF8B8);

INCLUDE_ASM("maria_psp/nonmatchings/18838", func_pspeu_092BF950);

INCLUDE_ASM("maria_psp/nonmatchings/18838", func_pspeu_092BFD30);

INCLUDE_ASM("maria_psp/nonmatchings/18838", func_pspeu_092BFEB0);

void func_pspeu_092BFF78(Entity* self) {
    if (g_Player.unk28) {
        g_Player.unk28(self);
    }
}
