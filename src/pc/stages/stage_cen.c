// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stage_loader.h"
#include "cen.h"

u16 D_8018658C[0x80];
u16 D_8018678C[0x80];
u16 D_8018698C[0x10];
u16 D_801869AC[0x20];
u8 D_80183A40[4400];
u8 D_80184B70[3264];
u8 D_80181658[836];
u8 D_8018199C[8356];
u8 D_80185830[3420];

extern Overlay OVL_EXPORT(Overlay);
extern PfnEntityUpdate* PfnEntityUpdates;
extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];
void InitStageCEN(Overlay* o) {
    LoadReset();
    LOAD_ASSET("assets/st/cen/D_8018658C.bin", D_8018658C);
    LOAD_ASSET("assets/st/cen/D_8018678C.bin", D_8018678C);
    LOAD_ASSET("assets/st/cen/D_8018698C.bin", D_8018698C);
    LOAD_ASSET("assets/st/cen/D_801869AC.bin", D_801869AC);
    LOAD_ASSET("assets/st/cen/D_80183A40.bin", D_80183A40);
    LOAD_ASSET("assets/st/cen/D_80184B70.bin", D_80184B70);
    LOAD_ASSET("assets/st/cen/D_80181658.bin", D_80181658);
    LOAD_ASSET("assets/st/cen/D_8018199C.bin", D_8018199C);
    LOAD_ASSET("assets/st/cen/D_80185830.bin", D_80185830);
    memcpy(o, &OVL_EXPORT(Overlay), sizeof(Overlay));
    // PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
}
