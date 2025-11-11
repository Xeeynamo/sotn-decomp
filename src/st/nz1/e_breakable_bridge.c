// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

// pspeu deadstrips this function
INCLUDE_ASM("st/nz1/nonmatchings/e_breakable_bridge", DropBridgePiece);

INCLUDE_ASM("st/nz1/nonmatchings/e_breakable_bridge", BreakBridge);

INCLUDE_ASM("st/nz1/nonmatchings/e_breakable_bridge", EntityBridgeBreakTrigger);

INCLUDE_ASM("st/nz1/nonmatchings/e_breakable_bridge", EntityBridgeBackgroundPiece);
