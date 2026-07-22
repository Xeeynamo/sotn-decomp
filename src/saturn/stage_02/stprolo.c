// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

// Unreferenced linker residue between the stage exports and the first function.
// STAGE_11.PRG contains the same six words at the same offset.
u32 g_Stage02LinkerResidue[6] = {
    0x584C4100,
    0x484C4100,
    0x384C4100,
    0x284C4100,
    0x184C4100,
    0x084C4100,
};
