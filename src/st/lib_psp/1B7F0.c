// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../lib/lib.h"

INCLUDE_ASM("st/lib_psp/psp/lib_psp/1B7F0", func_psp_09252E70);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/1B7F0", func_psp_092531A8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/1B7F0", func_psp_09253498);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/1B7F0", func_psp_092537F8);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/1B7F0", func_psp_09253D58);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/1B7F0", func_psp_09253E20);

INCLUDE_ASM("st/lib_psp/psp/lib_psp/1B7F0", func_psp_09254120);

// Using an include to consolidate the code because I can't get
// the psp split in a way that allows merging at this time.
// func_us_801BB53C
#include "../lib/unk_3B53C.h"
