// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

bool func_80131F68(void) {
    bool ret;
    if (D_8013B61C) {
        ret = 1;
    } else {
        ret = (D_8013901C != 0);
    }
    return ret;
}

// Never called in PSX; probably removed by deadstripping.
// s16 GetCdVolume(void) { return g_CdVolume; }

void SetReverbDepth(short depth) { SsUtSetReverbDepth(depth, depth); }

void func_80131FCC(void) {
    switch(D_8013B680){
        case 0:
        D_80138F7C = 0;
        break;
        case 1:
        case 2:
        D_80138F7C++;
        break;
    }
    D_8013B680 = 0;
}

u8 DoCdCommand(u_char com, u_char* param, u_char* result) {
    g_CdCommandStatus = CdSync(1, g_CdCommandResult);

    if (com == CdlGetlocL) {
        if (g_CdCommandStatus != CdlComplete) {
            CdControl(CdlNop, 0, 0);
            D_8013B680 = 2;
            return D_8013B680;
        }
    } else if (*g_CdCommandResult & CdlStatShellOpen){
        CdControl(CdlNop, 0, 0);
        D_8013B680 = 2;
        return D_8013B680;
    } else if(*g_CdCommandResult & CdlStatSeekError) {
        CdControl(CdlNop, 0, 0);
        D_8013B680 = 2;
        return D_8013B680;
    }

    if (g_CdCommandStatus == CdlComplete) {
        if (CdControl(com, param, result)) {
            D_8013B680 = 0;
            return D_8013B680;
        }
    }

    D_8013B680 = 1;
    return D_8013B680;
}