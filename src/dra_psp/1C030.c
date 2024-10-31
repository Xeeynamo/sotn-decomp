// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/1C030", func_psp_090F89B0);

INCLUDE_ASM("dra_psp/psp/dra_psp/1C030", HandleNowLoading);

INCLUDE_ASM("dra_psp/psp/dra_psp/1C030", HandleVideoPlayback);

void nullsub_9(void) {}

INCLUDE_ASM("dra_psp/psp/dra_psp/1C030", HandlePrologueEnd);

INCLUDE_ASM("dra_psp/psp/dra_psp/1C030", MainMenuHandler);

INCLUDE_ASM("dra_psp/psp/dra_psp/1C030", HandleEnding);
