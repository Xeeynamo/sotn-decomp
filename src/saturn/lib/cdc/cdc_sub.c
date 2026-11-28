#include "../../sattypes.h"
#include "../../inc_asm.h"
#include "../machine.h"

#include "cdc.h"

typedef union {
    Uint32 val32[2];
    Uint16 val16[4];
    Uint8 val8[8];
} CdcCmd;

extern CdcStat DAT_06057EF8;

// func_0602F288
Sint32 CDSUB_UpdStatus(Sint32 bitpat, CdcCmd* pCmd, CdcCmd* pCmdRsp) {
    return CDSUB_CdCmd(bitpat, pCmd, pCmdRsp, 0);
}

// func_0602F2C4
Sint32 CDSUB_UpdCdstat(Sint32 bitpat, CdcCmd* pCmd) {
    CdcCmd cmdRsp;

    return CDSUB_CdCmd(bitpat, pCmd, &cmdRsp, 1);
}

// func_0602F300
Sint32 CDSUB_CdCmd(
    Sint32 bitpat, CdcCmd* pCmd, CdcCmd* pCmdRsp, Sint32 getRsp) {
    Sint32 ret;
    Uint32 msk;
    CdcStat* stat;

    ret = CDREG_CmdRsp(bitpat, pCmd, pCmdRsp);
    if (ret != CDC_ERR_OK) {
        return ret;
    }
    msk = get_imask();
    set_imask(15);

    stat = &DAT_06057EF8;
    if (getRsp) {
        CDSUB_RspToCdstat(pCmdRsp, stat);
    } else {
        stat->status = pCmdRsp->val8[0];
    }

    set_imask(msk);

    return ret;
}

// func_0602F398
Sint32 CDSUB_GetCdstat(CdcStat* stat) {
    Uint32 msk;

    msk = get_imask();
    set_imask(15);

    *stat = DAT_06057EF8;

    set_imask(msk);

    return CDC_ERR_OK;
}

// func_0602F3FC
void CDSUB_RspToCdstat(CdcCmd* pCmdRsp, CdcStat* stat) {
    stat->status = pCmdRsp->val8[0];
    stat->report.flgrep = pCmdRsp->val8[1];
    stat->report.ctladr = pCmdRsp->val8[2];
    stat->report.tno = pCmdRsp->val8[3];
    stat->report.idx = pCmdRsp->val8[4];
    stat->report.fad = pCmdRsp->val32[1] & 0xFFFFFF;
    return;
}

// _CDSUB_SoftTimer
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F46C, func_0602F46C);
