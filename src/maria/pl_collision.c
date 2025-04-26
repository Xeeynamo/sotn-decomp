// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", func_pspeu_092B3848);

void MarGetPlayerSensor(Collider* col) {
    col->unk14 = g_MarSensorsWall[0].x;
    col->unk1C = g_MarSensorsWall[0].y;
    col->unk18 = g_MarSensorsFloor[1].y - 1;
    col->unk20 = g_MarSensorsCeiling[1].y + 1;
}

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", MarCheckFloor);

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", MarCheckCeiling);

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", MarCheckWallRight);

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", MarCheckWallLeft);
