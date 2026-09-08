// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", RNO4_Unused801C8768);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", RNO4_Unused801C8770);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", EntityBoatElevatorChains);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", RNO4_Unused801C8BD4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", RNO4_Unused801C8BDC);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", LoadFerrymanGateTiles);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C8C54);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C12B0_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C15F8_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C5364);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", EntityBgColumnsParallax_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C1EE4_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C5C78);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C5EE4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C2850_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C2B78_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C2E60_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C3160_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C34EC_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C37C8_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C3A04_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C3CC4_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C3FB0_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C4228_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", EntityWaterBox);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C81C8);

void EntityFloatingIcePlatform(Entity* self) {
    extern u16 g_FloatingIcePlatformHitbox[];
    u16* hitboxPtr;
    u16 collision;
    Entity* player;
    s16 prevPosY;
    s16 dx, dy;
    u16 hitboxIndex;

    player = &PLAYER;
    hitboxIndex = self->params;

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = hitboxIndex + 25;
        self->drawFlags = ENTITY_ROTATE;
        self->ext.floatingIcePlatform.baseY =
            self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    }

    hitboxPtr = &g_FloatingIcePlatformHitbox[hitboxIndex * 2];

    prevPosY = self->posY.i.hi;
    self->posY.i.hi =
        self->ext.floatingIcePlatform.baseY - g_Tilemap.scrollY.i.hi +
        self->ext.floatingIcePlatform.bobOffset;
#ifdef VERSION_PSP
    collision = GetPlayerCollisionWith(self, hitboxPtr[0], hitboxPtr[1], 4);
#else
    collision = GetPlayerCollisionWith(self, *hitboxPtr++, *hitboxPtr, 4);
#endif
    self->posY.i.hi = prevPosY;
    self->ext.floatingIcePlatform.previousBobOffset =
        self->ext.floatingIcePlatform.bobOffset;

    dx = self->posX.i.hi - player->posX.i.hi;

    if (collision) {
        if (self->ext.floatingIcePlatform.bobOffset < 4) {
            self->ext.floatingIcePlatform.bobOffset++;
        }
    } else {
        if (self->ext.floatingIcePlatform.bobOffset) {
            self->ext.floatingIcePlatform.bobOffset--;
        }
    }

    dy = self->ext.floatingIcePlatform.bobOffset;
    if (dx < 0) {
        prevPosY = (dx * dy * -0x100) / 56;
    } else {
        prevPosY = (dx * dy * 0x100) / 56;
    }

    self->posY.i.hi = self->ext.floatingIcePlatform.baseY -
                      g_Tilemap.scrollY.i.hi + (dy - prevPosY / 256);

    if (collision) {
        dy = dy - self->ext.floatingIcePlatform.previousBobOffset;
        player->posY.i.hi += dy;
        g_unkGraphicsStruct.shoveX.i.hi += dy;
    }

    prevPosY = -prevPosY;
    if (collision || dy) {
        if (dx < 0) {
            self->rotate = ratan2(prevPosY, -0x3800);
            self->rotate = (self->rotate - 0x800) & 0xFFF;
            return;
        }
        self->rotate = ratan2(prevPosY, 0x3800);
    } else {
        self->rotate = 0;
    }
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C4BD8_from_no4);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C8668);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", RNO4_Unused801C8704);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_1CF10", func_us_801C870C);
