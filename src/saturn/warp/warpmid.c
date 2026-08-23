// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"

#include "warp.h"

INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DDD80, func_060DDD80);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DE574, func_060DE574);
void func_060DE8B4(Entity* self) {
    PfnEntityUpdate update;
    s16 savedParams;
    u16 param;

    if (self->step == 0) {
        self->ext.et_060DE8B4.savedParams = savedParams = self->params;
        param = savedParams;
        if ((DAT_0605CB50[param >> 3] >> (param & 7)) & 1) {
            update = DestroyEntity;
        } else {
            param = ((u16*)g_WarpHLayout49)[param];
            if (param <= 0x7F) {
                self->unkB4 = (Entity*)func_060DD038;
            } else {
                self->unkB4 = (Entity*)func_060DD894;
                param -= 0x80;
            }
            self->params = param - 0x8000;
            update = (PfnEntityUpdate)self->unkB4;
        }
    } else {
        savedParams = self->ext.et_060DE8B4.savedParams;
        param = savedParams;
        if (self->step <= 4 && self->hitFlags != 0) {
            DAT_0605CB50[param >> 3] |= 1 << (param & 7);
            self->step = 5;
        }
        update = (PfnEntityUpdate)self->unkB4;
    }
    update(self);
}
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DE9A4, func_060DE9A4);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DEEB8, func_060DEEB8);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DF528, func_060DF528);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DF580, func_060DF580);
void func_060DF938(Entity* self) {
    Tilemap* map;
    u8* dest;
    s16 scrollY;
    s32 index;
    s32 i;
    s32 offset;
    s32 x;
    s32 y;

    map = &g_Tilemap;
    i = 0;
    dest = DAT_0608FFF8;
    offset = -0x18;
    do {
        x = self->posX.i.hi;
        y = self->posY.i.hi;
        index = ((x + map->scrollX.i.hi) << 2) / 5;
        scrollY = map->scrollY.i.hi;
        index =
            (index >> 4) + (((y + offset + scrollY) >> 4) * map->hSize * 0x10);
        dest[index] = self->animCurFrame != 0 ? 3 : 0;
        i += 1;
        offset += 0x10;
    } while (i <= 3);
}

const u16 pad_060DF9BC[] = {0xCCCC, 0xCCCD};
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DF9C0, func_060DF9C0);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60E0094, func_060E0094);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60E01FC, func_060E01FC);
void func_060E0364(Entity* self) {
    Entity* entity;

    switch (self->step) {
    case 0:
        TekiInit(self, 2);
        self->step++;
        self->ext.et_060E0364.targetEntityId =
            self->ext.et_060E0364.target->entityId;
    case 1:
        if (self->ext.et_060E0364.timer++ > 4U) {
            entity = AllocEntity(&g_Entities[0xE0], &g_Entities[0x100]);
            if (entity != NULL) {
                CreateEntityFromEntity(2, self, entity);
                entity->entityId = 2;
                entity->pfnUpdate = EntityWarpExplosion;
                entity->params = self->params;
            }
            self->ext.et_060E0364.timer = 0;
        }

        self->posX.i.hi = self->ext.et_060E0364.target->posX.i.hi;
        self->posY.i.hi = self->ext.et_060E0364.target->posY.i.hi;
        if (self->ext.et_060E0364.target->entityId !=
            self->ext.et_060E0364.targetEntityId) {
            DestroyEntity(self);
        }
        break;
    }
}
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60E0450, func_060E0450);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60E05BC, func_060E05BC);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60E06F0, func_060E06F0);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60E080C, func_060E080C);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60E08EC, func_060E08EC);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60E0BD8, func_060E0BD8);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60E10B0, func_060E10B0);
void func_060E11BC(Entity* self) { DestroyEntity(self); }

const u8 pad_060E11D4[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
