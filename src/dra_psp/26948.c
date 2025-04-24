// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", HideAllBackgroundLayers);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", RenderTilemap);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", SetRoomForegroundLayer);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", SetRoomBackgroundLayer);

INCLUDE_ASM("dra_psp/psp/dra_psp/26948", LoadRoomLayer);
