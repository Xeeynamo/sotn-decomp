// SPDX-License-Identifier: AGPL-3.0-or-later
#include "zero.h"
#include "zero/overlay.h"
#include "inc_asm.h"
#include "sattypes.h"

// original name: SET_STAGE_OVERLAYADDR
void SetStageOverlayAddress(void) {
    PfnEntityUpdates[0] = g_StageOverlayData.entityEntries; // 0x60dc000
    *DAT_060645EC = *DAT_0601ac30;                          // 0x60dc004
    *DAT_060645e4 = *DAT_0601ac38;                          // 0x60dc008
    *DAT_060645f8 = *DAT_0601ac40;                          // 0x60dc00c
}

// _SET_SCL_OVERLAYADDR
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AC48, func_0601AC48);

// _SET_PLAYER_OVERLAYADDR
void func_0601AD14(void) {
    DAT_06064610 = DAT_060a5000;
    func_06064604 = DAT_060A5004;
    func_06064664 = DAT_060A5008;
    func_060645E8 = DAT_060A500C;
    func_06064684 = DAT_060A5010;
    GetPlayerSensor = DAT_060A5014;
    DAT_06064588 = DAT_060A5018;
    func_8010E168 = DAT_060A501C;
    func_0606458C = DAT_060A5020;
    func_06064658 = DAT_060A5024;
    g_api.CreateEntFactoryFromEntity = DAT_060A5028;
    func_06064608 = DAT_060A502C;
    DAT_060645F0 = DAT_060A5030;
    func_060645A4 = DAT_060A5034;
    func_06064660 = DAT_060A5038;
    DAT_06064650 = DAT_060A503C;
    DAT_06064668 = DAT_060A5040;
}
void func_0601AE2C(s32 param_1) {
    if (param_1) {
        DAT_06064670 = DAT_060D9040;
    } else {
        DAT_060645D4 = DAT_060D6040;
    }
}
s32 func_0601AE5C(s32 param_1, s32 param_2) {
    OverlayHandler* handler;
    s32 i;

    handler = param_1 != 0 ? PLAYER_SERVANT_HANDLERS : MARIA_SERVANT_HANDLERS;

    i = 0;
    do {
        if (i == 6) {
            *handler = func_0601AEA8;
        } else {
            *handler = func_0601AE9C;
        }
        i++;
        handler++;
    } while (i <= 15);

    return i;
}

static const volatile u16 DAT_0601AE8A = 9;

s32 func_0601AE9C(void) { return 0xFF; }

s32 func_0601AEA8(void) { return 0xFF; }

// func_0601AEB4
void SetServantResourceList(void) {
    DAT_060645D0 = (s32)g_BatResourceDescriptorList;
}

// call familiar update function
// func_0601AECC
void InitServant() {
    if (g_Servant != 0) {
        g_BatServantDesc.Init();
    }
}

void func_0601AEF4(void) {
    func_06064688 = (void (*)())DAT_060a5000;
    func_0606468c = DAT_060A5004;
    func_06064614 = DAT_060A5008;
}

void func_0601AF2C(void) { func_06064674 = (void (*)())DAT_060a5000; }

void func_0601AF44(void) { func_06064580 = (void (*)())DAT_060a5000; }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AF5C, func_0601AF5C);

void func_0601B184(void) { func_060645E0 = (void (*)())DAT_060a5000; }

void func_0601B19C(void) {
    func_06064644 = (void (*)())g_StageOverlayData.entityEntries;
}

void func_0601B1B4(void) { func_06064690 = (s32(*)())DAT_06066000; }

// _SET_GAME_OVERLAYADDR
void func_0601B1CC(void) {
    DAT_060645AC = DAT_06066000;
    func_0606463c = DAT_06066004;
    DAT_0606465C = DAT_06066008;
    DAT_06064680 = DAT_0606600C;
    DAT_0606462C = DAT_06066010;
    DAT_060645DC = DAT_06066014;
    DAT_06064598 = DAT_06066018;
    DAT_060645CC = DAT_0606601C;
    DAT_060645C4 = DAT_06066020;
    DAT_0606461C = DAT_06066024;
    DAT_06064624 = DAT_06066028;
    DAT_06064640 = DAT_0606602C;
}
