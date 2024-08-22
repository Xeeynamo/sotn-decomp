// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mad.h"
#include "sfx.h"

void func_8018D8C8(u16* tilemap);
INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8018D8C8);

void func_8018DC28(u16* tilemap);
INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8018DC28);

void func_8018DF0C(u16* tilemap, s32 arg1) {
    const int RoomWidth = 32;
    s32 y, x;
    s16 tile;

    for (y = 0; y < 16; y++) {
        for (x = 0; x < 32; x++) {
            if (y < 2 || y > 13) {
                tile = 3;
            } else {
                tile = 0;
            }
            if (x < 2 || x > 29) {
                tile = 3;
            }
            *(tilemap + x + y * RoomWidth) = tile;
        }
    }
    if (arg1 & 4) {
        for (y = 6; y < 10; y++) {
            for (x = 0; x < 2; x++) {
                *(tilemap + x + y * RoomWidth) = 0;
            }
        }
    }
    if (arg1 & 8) {
        for (y = 6; y < 10; y++) {
            for (x = 30; x < 32; x++) {
                *(tilemap + x + y * RoomWidth) = 0;
            }
        }
    }
    if (arg1 & 1) {
        for (y = 0; y < 2; y++) {
            for (x = 6; x < 10; x++) {
                u8 variant = !(arg1 & 8) * RoomWidth;
                *((u16*)((u8*)&tilemap[x] + variant) + y * RoomWidth) = 0;
            }
        }
    }
    if (arg1 & 2) {
        for (y = 14; y < 16; y++) {
            for (x = 6; x < 10; x++) {
                u8 variant = !(arg1 & 8) * RoomWidth;
                *((u16*)((u8*)&tilemap[x] + variant) + y * RoomWidth) = 0;
            }
        }
    }
}

void func_8018E090(u16* tilemap) {
    const int RoomWidth = 32;
    s32 x, y;
    s32 varY;
    s32 varX;

randomize_pos:
    varX = (rand() & 0xF) + 8;
    varY = (rand() & 7) + 4;
    for (y = -2; y < 3; y++) {
        for (x = -1; x < 2; x++) {
            if (*(&tilemap[varX + x] + (varY + y) * RoomWidth)) {
                goto randomize_pos;
            }
        }
    }
    *(tilemap + varX + varY * RoomWidth) = 3;
}

void func_8018E13C(u16* tilemap) {
    const int RoomWidth = 16;
    s32 x, y;

    for (y = 10; y < 16; y++) {
        for (x = 0; x < RoomWidth; x++) {
            if (rand() & 1) {
                *(tilemap + x + y * RoomWidth) = 3;
            }
        }
    }
}

void func_8018E1D4(void);
INCLUDE_ASM("asm/us/st/mad/nonmatchings/D8C8", func_8018E1D4);

void func_8018E5AC(Entity* self) {
    s32 temp_v0;
    ObjInit* objInit = &D_8018056C[self->params];

    if (self->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        self->animSet = objInit->animSet;
        self->zPriority = objInit->zPriority;
        self->unk5A = objInit->unk5A;
        self->palette = objInit->palette;
        self->drawFlags = objInit->drawFlags;
        self->drawMode = objInit->drawMode;
        temp_v0 = objInit->unkC;
        if (temp_v0 != 0) {
            self->flags = temp_v0;
        }
    }
    AnimateEntity(objInit->unk10, self);
}

void func_8018E674(Entity* self) {
    u16 var_s0;
    u16 params;
    u16* tilemapProps;

    self->unk6D[0] = 0;
    params = self->params;
    if (self->step) {
        switch (params) {
        case 4:
        case 5:
            if (g_Tilemap.x) {
                return;
            }
            break;
        case 6:
            if (g_pads->pressed & PAD_TRIANGLE) {
                g_Tilemap.x = 0;
                g_Tilemap.width = 1280;
                self->step++;
                return;
            }
            break;
        }
        if (self->unk44) {
            var_s0 = GetSideToPlayer();
            if (self->ext.generic.unk7C.u) {
                var_s0 &= 2;
                var_s0 *= 2;
            } else {
                var_s0 &= 1;
                var_s0 *= 4;
            }
            params = (params << 3) + var_s0;
            tilemapProps = &D_801805C4[params];
            g_Tilemap.x = *tilemapProps++;
            g_Tilemap.y = *tilemapProps++;
            g_Tilemap.width = *tilemapProps++;
            g_Tilemap.height = *tilemapProps;
        }
    } else {
        InitializeEntity(D_80180538);
        var_s0 = self->ext.timer.t = D_801805BC[params];
        if (var_s0) {
            self->hitboxWidth = D_801805B4[params];
            self->hitboxHeight = 16;
            return;
        }
        self->hitboxWidth = 16;
        self->hitboxHeight = D_801805B4[params];
    }
}

void EntityBreakable(Entity* entity) {
    u16 breakableType = entity->params >> 0xC;
    if (entity->step) {
        AnimateEntity(g_eBreakableAnimations[breakableType], entity);
        if (entity->unk44) { // If the candle is destroyed
            Entity* entityDropItem;
            g_api.PlaySfx(SFX_CANDLE_HIT);
            entityDropItem = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entityDropItem != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entityDropItem);
                entityDropItem->params =
                    g_eBreakableExplosionTypes[breakableType];
            }
            ReplaceBreakableWithItemDrop(entity);
        }
    } else {
        InitializeEntity(g_eBreakableInit);
        entity->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        entity->drawMode = g_eBreakableDrawModes[breakableType];
        entity->hitboxHeight = g_eBreakableHitboxes[breakableType];
        entity->animSet = g_eBreakableanimSets[breakableType];
    }
}
