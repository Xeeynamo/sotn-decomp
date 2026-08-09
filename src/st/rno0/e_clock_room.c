// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"

void func_us_801CCAAC(Entity* self) {
    Entity* tempEntity;
    s16 angle;

    if ((self->ext.clockRoom.unk88 & 0x1F) == 0) {
        g_api.PlaySfxVolPan(SFX_STONE_MOVE_A, 0x40, 0);
    }
    self->ext.clockRoom.unk88++;

    // Minute hand
    tempEntity = self + 5;
    angle =
        tempEntity->ext.clockRoom.unk80 +
        (LOW(tempEntity->ext.clockRoom.bellTimer) * self->ext.clockRoom.unk88) /
            512;
    angle %= (60 * 60);
    tempEntity->ext.clockRoom.hand = angle;

    // Hour hand
    tempEntity++;
    angle =
        tempEntity->ext.clockRoom.unk80 -
        (LOW(tempEntity->ext.clockRoom.bellTimer) * self->ext.clockRoom.unk88) /
            512;
    angle %= (60 * 60);
    tempEntity->ext.clockRoom.hand = angle;
}

INCLUDE_ASM("st/rno0/nonmatchings/e_clock_room", UpdateBirdcages);

INCLUDE_ASM("st/rno0/nonmatchings/e_clock_room", UpdateClockHands);

INCLUDE_ASM("st/rno0/nonmatchings/e_clock_room", EntityClockRoomController);

INCLUDE_ASM("st/rno0/nonmatchings/e_clock_room", EntityClockHands);

INCLUDE_ASM("st/rno0/nonmatchings/e_clock_room", EntityBirdcageDoor);

INCLUDE_ASM("st/rno0/nonmatchings/e_clock_room", UpdateStatueTiles);

INCLUDE_ASM("st/rno0/nonmatchings/e_clock_room", EntityStatue);

INCLUDE_ASM("st/rno0/nonmatchings/e_clock_room", EntityStatueGear);

INCLUDE_ASM("st/rno0/nonmatchings/e_clock_room", UpdateStoneDoorTiles);

INCLUDE_ASM("st/rno0/nonmatchings/e_clock_room", EntityStoneDoor);

void RNO0_Unused801C2338(void) {}
