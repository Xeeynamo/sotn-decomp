// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"

#include "warp.h"

INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DC040, func_060DC040);

// inlined in case 0 of EntityWarpRoom on PSX
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DC4D4, func_060DC4D4);

// inlined in the final chunk of code from EntityWarpRoom on PSX
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DC7D8, func_060DC7D8);

INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DCAFC, func_060DCAFC);

void func_060DCE50(u16 arg0) {
    Collider collider;
    Entity* self;
    Entity* entity;
    s32 sway;

    self = g_CurrentEntity;
    if (self->velocityY < 0) {
        CheckCollision(self->posX.val, self->posY.val - 0x70000, &collider, 0);
        if (collider.effects & 5) {
            self->velocityY = 0;
        }
    }

    CheckCollision(self->posX.val, self->posY.val + 0x80000, &collider, 0);
    if (arg0) {
        if (!(collider.effects & 5)) {
            MoveEntity(self);
            func_06079BE4(self);
            return;
        }

        self->velocityX = 0;
        self->velocityY = 0;
        if (collider.effects & 4) {
            self->posY.val += FIX(0.125);
        } else {
            self->posY.val += collider.unk18;
        }
        self->posY.i.hi++;
        self->posY.i.lo = 0;
    } else if (!(collider.effects & 5)) {
        MoveEntity(self);
        entity = g_CurrentEntity;
        if (entity->velocityY >= 0) {
            sway = entity->ext.et_060DCE50.swayVelocity +
                   entity->ext.et_060DCE50.swayStep;
            entity->ext.et_060DCE50.swayVelocity = sway;
            entity->velocityX = sway;
            if ((sway == 0x10000) || (sway == 0xFFFF0000)) {
                entity->ext.et_060DCE50.swayStep =
                    -entity->ext.et_060DCE50.swayStep;
            }
        }
        if (entity->velocityY <= 0x3FFF) {
            entity->velocityY += FIX(0.125);
        }
    }
}

void func_060DCF5C(u16 arg0) {
    Entity* entity;
    Entity* player;
    SpriteObject* sprite;
    s16 subweapon;
    u16 params;

    entity = g_CurrentEntity;
    PlaySfx(0x67C);
    player = g_Entities;
    params = g_Status.subWeapon;
    subweapon = DAT_060E2218[arg0];
    g_Status.subWeapon = subweapon;
    if (params == subweapon) {
        params = 1;
        entity->unk6D[0] = 0x10;
    } else {
        params = DAT_060E1FFC[params];
        entity->unk6D[0] = 0x60;
    }
    if (params != 0) {
        entity->params = params;
        entity->posY.i.hi = player->posY.i.hi + 0xC;
        SetStep(7);
        sprite = entity->unk0;
        sprite->flags |= 8;
        entity->ext.et_060DCF5C.timer = 5;
        entity->velocityY = FIX(-2.5);
        if (player->facingLeft != 1) {
            entity->velocityX = FIX(-2.5);
            return;
        }
        entity->velocityX = FIX(2.5);
    } else {
        DestroyEntity(entity);
    }
}

INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DD038, func_060DD038);

INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DD894, func_060DD894);
