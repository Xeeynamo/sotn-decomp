#include "np3.h"

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CB018);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CBF18);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CC2E0);

void func_801CD540(Entity* self) {
    s8* hitbox;
    s32 diff;

    if (self->step == 0) {
        InitializeEntity(D_80180B20);
    }

    self->facing = self[-1].facing;
    self->posX.i.hi = self[-1].posX.i.hi;
    self->posY.i.hi = self[-1].posY.i.hi;
    hitbox = D_80182914;
    diff = D_80182935[self[-1].animCurFrame];

    diff -= 4;
    if (diff < 0) {
        diff = 0;
    }

    hitbox += diff * 4;
    self->hitboxOffX = *hitbox++;
    self->hitboxOffY = *hitbox++;
    self->hitboxWidth = hitbox[0];
    self->hitboxHeight = hitbox[1];
    if (self[-1].entityId != 0x44) {
        DestroyEntity(self);
    }
}

void func_801CD620(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(D_80180A6C);
    }
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CD658);

void func_801CD734() {
    while (PadRead(0))
        func_801CD658();
    while (!PadRead(0))
        func_801CD658();
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CD78C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CD83C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CD91C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDA14);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDA6C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDAC8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDC80);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDD00);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDD80);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDE10);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDE88);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDF1C);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CDFD8);

void func_801CE04C(Entity* entity, Collider* collider) {
    s16 var_s0 = 0;

    g_api.CheckCollision(
        entity->posX.i.hi, (s16)(entity->posY.i.hi + collider->unk18), collider,
        0);
    if (collider->effects & 1) {
        var_s0 = 1;
        if (collider->effects & 0x8000) {
            if (collider->effects & 0x4000) {
                if (g_CurrentEntity->facing != 0) {
                    var_s0 = 4;
                } else {
                    var_s0 = 2;
                }
            } else {
                if (g_CurrentEntity->facing != 0) {
                    var_s0 = 2;
                } else {
                    var_s0 = 4;
                }
            }
        }
    }
    entity->ext.generic.unk88.S16.unk0 = var_s0;
}

s32 func_801CE120(Entity* self, s32 arg1) {
    Collider collider;
    s32 x = self->posX.i.hi;
    s32 y = self->posY.i.hi + 9;
    s32 ret = 0;

    if (arg1 != 0) {
        x += 64;
    } else {
        x -= 64;
    }

    g_api.CheckCollision(x, y - 6, &collider, 0);
    if (collider.effects & 1) {
        ret |= 2;
    }

    g_api.CheckCollision(x, y + 6, &collider, 0);
    if (!(collider.effects & 1)) {
        ret |= 4;
    }

    return ret;
}

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CE1E8);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CE228);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CE258);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CE2CC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CE3FC);

INCLUDE_ASM("asm/us/st/np3/nonmatchings/4B018", func_801CE4CC);
