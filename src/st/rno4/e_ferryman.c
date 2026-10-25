// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

void RNO4_Unused801C8768(void) {}

void RNO4_Unused801C8770(void) {}

INCLUDE_ASM("st/rno4/nonmatchings/e_ferryman", EntityBoatElevatorChains);

void RNO4_Unused801C8BD4(void) {}

void RNO4_Unused801C8BDC(void) {}

INCLUDE_ASM("st/rno4/nonmatchings/e_ferryman", LoadFerrymanGateTiles);

void func_us_801C8C54(Entity* self) {
    LoadFerrymanGateTiles();
    DestroyEntity(self);
}
