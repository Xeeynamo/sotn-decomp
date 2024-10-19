// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stage_loader.h"
#include "../st/nz0/nz0.h"

u16 D_80195C3C[0x40];
u16 D_80195CDC[0x10];
u16 D_80195D3C[0x40];
u16 D_80195DBC[0x30];
u16 D_80195E1C[0x10];
u16 D_80195E3C[0x30];
u16 D_80195E9C[0x40];
u16 D_80195F1C[0x40];
u16 D_80195F9C[0x40];
u16 D_8019601C[0x100];
u16 D_801962DC[0xA0];
u16 D_8019641C[0x30];
u16 D_8019647C[0x80];
u16 D_8019657C[0x50];
u16 D_8019663C[0x10];
u16 D_8019665C[0x80];
u16 D_8019685C[0x80];

u8 D_80184154[2960];
u8 D_80184CE4[3036];
u8 D_801858C0[3824];
u8 D_801867B0[3056];
u8 D_801873A0[3256];
u8 D_80188058[2912];
u8 D_80188BB8[3160];
u8 D_80189810[3320];
u8 D_8018A508[1480];
u8 D_8018AAD0[1508];
u8 D_8018B0B4[3076];
u8 D_8018BCB8[3964];
u8 D_8018CC34[2900];
u8 D_8018D788[2804];
u8 D_8018E27C[2536];
u8 D_8018EC64[2244];
u8 D_8018F528[3440];
u8 D_80190298[1984];
u8 D_80190A58[4288];
u8 D_80191B18[4884];
u8 D_80192E2C[3448];
u8 D_801956A4[1432];

extern AbbreviatedOverlay OVL_EXPORT(Overlay);
extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutHorizontal)[];
extern LayoutEntity* OVL_EXPORT(pStObjLayoutVertical)[];
extern PfnEntityUpdate* PfnEntityUpdates;
extern LayoutEntity** g_pStObjLayoutHorizontal;
extern LayoutEntity** g_pStObjLayoutVertical;
void InitStageNZ0(Overlay* o) {
    LoadReset();
    LOAD_ASSET("assets/st/nz0/D_80195C3C.bin", D_80195C3C);
    LOAD_ASSET("assets/st/nz0/D_80195CDC.bin", D_80195CDC);
    LOAD_ASSET("assets/st/nz0/D_80195D3C.bin", D_80195D3C);
    LOAD_ASSET("assets/st/nz0/D_80195DBC.bin", D_80195DBC);
    LOAD_ASSET("assets/st/nz0/D_80195E1C.bin", D_80195E1C);
    LOAD_ASSET("assets/st/nz0/D_80195E3C.bin", D_80195E3C);
    LOAD_ASSET("assets/st/nz0/D_80195E9C.bin", D_80195E9C);
    LOAD_ASSET("assets/st/nz0/D_80195F1C.bin", D_80195F1C);
    LOAD_ASSET("assets/st/nz0/D_80195F9C.bin", D_80195F9C);
    LOAD_ASSET("assets/st/nz0/D_8019601C.bin", D_8019601C);
    LOAD_ASSET("assets/st/nz0/D_801962DC.bin", D_801962DC);
    LOAD_ASSET("assets/st/nz0/D_8019641C.bin", D_8019641C);
    LOAD_ASSET("assets/st/nz0/D_8019647C.bin", D_8019647C);
    LOAD_ASSET("assets/st/nz0/D_8019657C.bin", D_8019657C);
    LOAD_ASSET("assets/st/nz0/D_8019663C.bin", D_8019663C);
    LOAD_ASSET("assets/st/nz0/D_8019665C.bin", D_8019665C);
    LOAD_ASSET("assets/st/nz0/D_8019685C.bin", D_8019685C);
    LOAD_ASSET("assets/st/nz0/D_80184154.bin", D_80184154);
    LOAD_ASSET("assets/st/nz0/D_80184CE4.bin", D_80184CE4);
    LOAD_ASSET("assets/st/nz0/D_801858C0.bin", D_801858C0);
    LOAD_ASSET("assets/st/nz0/D_801867B0.bin", D_801867B0);
    LOAD_ASSET("assets/st/nz0/D_801873A0.bin", D_801873A0);
    LOAD_ASSET("assets/st/nz0/D_80188058.bin", D_80188058);
    LOAD_ASSET("assets/st/nz0/D_80188BB8.bin", D_80188BB8);
    LOAD_ASSET("assets/st/nz0/D_80189810.bin", D_80189810);
    LOAD_ASSET("assets/st/nz0/D_8018A508.bin", D_8018A508);
    LOAD_ASSET("assets/st/nz0/D_8018AAD0.bin", D_8018AAD0);
    LOAD_ASSET("assets/st/nz0/D_8018B0B4.bin", D_8018B0B4);
    LOAD_ASSET("assets/st/nz0/D_8018BCB8.bin", D_8018BCB8);
    LOAD_ASSET("assets/st/nz0/D_8018CC34.bin", D_8018CC34);
    LOAD_ASSET("assets/st/nz0/D_8018D788.bin", D_8018D788);
    LOAD_ASSET("assets/st/nz0/D_8018E27C.bin", D_8018E27C);
    LOAD_ASSET("assets/st/nz0/D_8018EC64.bin", D_8018EC64);
    LOAD_ASSET("assets/st/nz0/D_8018F528.bin", D_8018F528);
    LOAD_ASSET("assets/st/nz0/D_80190298.bin", D_80190298);
    LOAD_ASSET("assets/st/nz0/D_80190A58.bin", D_80190A58);
    LOAD_ASSET("assets/st/nz0/D_80191B18.bin", D_80191B18);
    LOAD_ASSET("assets/st/nz0/D_80192E2C.bin", D_80192E2C);
    LOAD_ASSET("assets/st/nz0/D_801956A4.bin", D_801956A4);
    memcpy(o, &OVL_EXPORT(Overlay), sizeof(AbbreviatedOverlay));
    // PfnEntityUpdates = OVL_EXPORT(EntityUpdates);
    g_pStObjLayoutHorizontal = OVL_EXPORT(pStObjLayoutHorizontal);
    g_pStObjLayoutVertical = OVL_EXPORT(pStObjLayoutVertical);
}
