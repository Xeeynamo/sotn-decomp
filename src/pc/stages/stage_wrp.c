// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stage_loader.h"
#include "../../st/wrp/wrp.h"

u32 D_80181764[1444];
u32 D_80181420[836];
u16 D_80181D08[48];

extern Overlay OVL_EXPORT(Overlay);
extern PfnEntityUpdate* PfnEntityUpdates;
extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];
void InitStageWRP(Overlay* o) {
    LoadReset();
    LOAD_ASSET("assets/st/wrp/D_80181D08.bin", D_80181D08);
    LOAD_ASSET("assets/st/wrp/D_80181420.bin", D_80181420);
    LOAD_ASSET("assets/st/wrp/D_80181764.bin", D_80181764);
    memcpy(o, &OVL_EXPORT(Overlay), sizeof(Overlay));
    PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
}
