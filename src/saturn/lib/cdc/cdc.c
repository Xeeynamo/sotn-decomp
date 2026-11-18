#include "../../sattypes.h"
#include "../../inc_asm.h"
#include "../machine.h"

#include "cdc.h"

typedef struct {
    union {
        Uint32 val32;
        Uint16 val16[2];
        Uint8 val8[4];
    } start;
    union {
        Uint32 val32;
        Uint16 val16[2];
        Uint8 val8[4];
    } end;
} CdcCmd;

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E4B4, CDC_SetSctLen);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E520, CDC_GetSctData);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E5A4, CDC_DelSctData);

// _CDC_GetdelSctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E628, func_0602E628);

// _CDC_PutSctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E6AC, func_0602E6AC);

// _CDC_CopySctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E71C, func_0602E71C);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E7B0, CDC_MoveSctData);

// _CDC_GetCopyErr
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E844, func_0602E844);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E8A8, CDC_SetFiltRange);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E914, func_0602E914);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E998, CDC_SetFiltSubh);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EA50, CDC_GetFiltSubh);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EB14, CDC_SetFiltMode);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EB80, CDC_GetFiltMode);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EBF4, CDC_SetFiltCon);

// _CDC_GetFiltCon
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EC84, func_0602EC84);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602ED08, CDC_ResetSelector);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602ED74, CDC_GetBufSiz);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EDF8, CDC_GetSctNum);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EE6C, CDC_CalActSiz);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EEEC, CDC_GetActSiz);

// _chkEselUpdStatus
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EF50, func_0602EF50);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EFA4, CDC_GetSctInfo);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F06C, func_0602F06C);

// _CDC_GetFadSearch
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F0E0, func_0602F0E0);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F164, CDC_CdSetCon);

// _CDC_CdGetCon
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F1C0, func_0602F1C0);

// _CDC_CdGetLastBuf
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F224, func_0602F224);

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
        stat->status = pCmdRsp->start.val8[0];
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
    stat->status = pCmdRsp->start.val8[0];
    stat->report.flgrep = pCmdRsp->start.val8[1];
    stat->report.ctladr = pCmdRsp->start.val8[2];
    stat->report.tno = pCmdRsp->start.val8[3];
    stat->report.idx = pCmdRsp->end.val8[0];
    stat->report.fad = pCmdRsp->end.val32 & 0xFFFFFF;
    return;
}

// _CDSUB_SoftTimer
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F46C, func_0602F46C);
