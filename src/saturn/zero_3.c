// SPDX-License-Identifier: AGPL-3.0-or-later
#include "zero.h"
#include "zero/overlay.h"
#include "inc_asm.h"
#include "sattypes.h"

// original name: SET_STAGE_OVERLAYADDR
void SetStageOverlayAddress(void) {
    PfnEntityUpdates[0] = g_StageOverlayData.entityEntries;
    *DAT_060645EC = *DAT_060DC004;
    *DAT_060645E4 = *DAT_060DC008;
    *DAT_060645F8 = *DAT_060DC00C;
}

// _SET_SCL_OVERLAYADDR
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601AC48, func_0601AC48);

// original name: SET_PLAYER_OVERLAYADDR
void func_0601AD14(void) {
    DAT_06064610 = DAT_060A5000;
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

void func_0601AE2C(s32 arg0) {
    if (arg0) {
        DAT_06064670 = DAT_060D9040;
    } else {
        DAT_060645D4 = DAT_060D6040;
    }
}

s32 func_0601AE5C(s32 arg0, s32 arg1) {
    OverlayHandler* handler;
    s32 i;

    handler = arg0 != 0 ? PLAYER_SERVANT_HANDLERS : MARIA_SERVANT_HANDLERS;

    for (i = 0; i < 0x10; i++) {
        if (i == 6) {
            *handler = func_0601AEA8;
        } else {
            *handler = func_0601AE9C;
        }
        handler++;
    }

    return i;
}

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
    func_06064688 = DAT_060A5000;
    func_0606468c = DAT_060A5004;
    func_06064614 = DAT_060A5008;
}

void func_0601AF2C(void) { func_06064674 = DAT_060A5000; }

void func_0601AF44(void) { func_06064580 = DAT_060A5000; }

void func_0601AF5C(void) {
    if (g_PlayableCharacter != 0) {
        func_060645B4 = DAT_060D4000;
        func_06064594 = DAT_060D4004;
        func_06064628 = DAT_060D4008;
        DAT_06064584 = DAT_060D400C;
        DAT_0606460C = DAT_060D4010;
        func_06064638 = DAT_060D4014;
        func_060645FC = DAT_060D4018;
        func_060645BC = DAT_060D401C;
        func_06064620 = DAT_060D4020;
        func_06064600 = DAT_060D4024;
        func_0606464C = DAT_060D4028;
        func_060645A0 = DAT_060D402C;
        func_06064630 = DAT_060D4030;
        func_06064590 = DAT_060D4034;
        DAT_0606467C = DAT_060D4038;
        func_06064618 = DAT_060D403C;
        DAT_06064678 = DAT_060D4040;
        func_060645C0 = DAT_060D4044;
        func_060645B0 = DAT_060D4048;
    } else {
        func_060645B4 = DAT_060D6000;
        func_06064594 = DAT_060D6004;
        func_06064628 = DAT_060D6008;
        DAT_06064584 = DAT_060D600C;
        DAT_0606460C = DAT_060D6010;
        func_06064638 = DAT_060D6014;
        func_060645FC = DAT_060D6018;
        func_060645BC = DAT_060D601C;
        func_06064620 = DAT_060D6020;
        func_06064600 = DAT_060D6024;
        func_0606464C = DAT_060D6028;
        func_060645A0 = DAT_060D602C;
        func_06064630 = DAT_060D6030;
        func_06064590 = DAT_060D6034;
        DAT_0606467C = DAT_060D6038;
        func_06064618 = DAT_060D603C;
        DAT_06064678 = DAT_060D6040;
        func_060645C0 = DAT_060D6044;
        func_060645B0 = DAT_060D6048;
    }
}

void func_0601B184(void) { func_060645E0 = DAT_060A5000; }

void func_0601B19C(void) {
    func_06064644 = (void (*)())g_StageOverlayData.entityEntries;
}

void func_0601B1B4(void) { func_06064690 = DAT_06066000; }

// original name: SET_GAME_OVERLAYADDR
void func_0601B1CC(void) {
    DAT_060645AC = DAT_06066000;
    func_0606463C = DAT_06066004;
    func_0606465C = DAT_06066008;
    DAT_06064680 = DAT_0606600C;
    DAT_0606462C = DAT_06066010;
    DAT_060645DC = DAT_06066014;
    DAT_06064598 = DAT_06066018;
    DAT_060645CC = DAT_0606601C;
    func_060645C4 = DAT_06066020;
    DAT_0606461C = DAT_06066024;
    DAT_06064624 = DAT_06066028;
    func_06064640 = DAT_0606602C;
}
