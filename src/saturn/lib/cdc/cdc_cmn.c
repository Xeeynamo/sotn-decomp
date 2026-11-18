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

Sint32 CDC_GetCurStat(CdcStat* stat) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmdRsp = &cmdRsp;
    pCmd->start.val8[0] = 0;

    ret = CDSUB_CdCmd(0, pCmd, pCmdRsp, 1);

    CDSUB_RspToCdstat(pCmdRsp, stat);

    return ret;
}

Sint32 CDC_GetLastStat(CdcStat* stat) { return CDSUB_GetCdstat(stat); }

Sint32 CDC_GetPeriStat(CdcStat* stat) {
    Sint32 ret;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmdRsp = &cmdRsp;
    ret = getPeriRsp(pCmdRsp);
    if (ret != CDC_ERR_OK) {
        return ret;
    }
    CDSUB_RspToCdstat(pCmdRsp, stat);
    if (CDC_STAT_STATUS(stat) == CDC_ST_REJECT ||
        !(CDC_STAT_STATUS(stat) & CDC_ST_PERI)) {
        ret = CDC_ERR_PERI;
    }
    return ret;
}

Sint32 getPeriRsp(CdcCmd* pCmdRsp) {
    Sint32 ret;
    Uint32 msk;
    Sint32 i;
    CdcCmd cmdRsp2;
    CdcCmd* pCmdRsp2;

    pCmdRsp2 = &cmdRsp2;
    ret = CDC_ERR_TMOUT;

    for (i = 0; i < 100; i++) {
        msk = get_imask();
        set_imask(15);

        CDREG_ReadRsp(pCmdRsp);
        CDREG_ReadRsp(pCmdRsp2);

        set_imask(msk);

        if (pCmdRsp->start.val32 == pCmdRsp2->start.val32 &&
            pCmdRsp->end.val32 == pCmdRsp2->end.val32) {
            ret = CDC_ERR_OK;
            break;
        }
    }
    return ret;
}

Sint32 CDC_GetHwInfo(CdcHw* hw) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmdRsp = &cmdRsp;
    pCmd->start.val8[0] = 1;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);

    hw->hflag = pCmdRsp->start.val8[2];
    hw->ver = pCmdRsp->start.val8[3];
    hw->mpver = pCmdRsp->end.val8[1];
    hw->drv = pCmdRsp->end.val8[2];
    hw->rev = pCmdRsp->end.val8[3];

    return ret;
}

Sint32 CDC_TgetToc(Uint32* toc) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;
    Sint32 tsize;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmdRsp = &cmdRsp;
    pCmd->start.val8[0] = 2;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);
    if (ret != CDC_ERR_OK) {
        return ret;
    }
    tsize = pCmdRsp->start.val32 & 0xFFFFFF;
    ret = CDREG_TgetData(tsize, toc);
    return ret;
}

Sint32 CDC_GetSes(Sint32 sesno, Uint32* ses) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmdRsp = &cmdRsp;
    pCmd->start.val8[0] = 3;
    pCmd->start.val8[1] = sesno;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);
    *ses = pCmdRsp->end.val32;
    return ret;
}

Sint32 CDC_CdInit(Sint32 iflag, Sint32 stnby, Sint32 ecc, Sint32 retry) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val8[0] = 4;
    pCmd->start.val8[1] = iflag;
    pCmd->start.val16[1] = stnby;
    pCmd->end.val8[2] = ecc;
    pCmd->end.val8[3] = retry;

    if ((iflag & 0x81) == 1) {
        func_0602F46C(10500);
        CDREG_SetHirqFlag(CDC_HIRQ_ESEL | CDC_HIRQ_CMOK);
        ret = CDSUB_UpdCdstat(CDC_HIRQ_ESEL, pCmd);
        if (ret == CDC_ERR_OK) {
            CDREG_InitHirqReq();
        }
    } else {
        ret = CDSUB_UpdCdstat(0, pCmd);
    }
    return ret;
}

Sint32 CDC_CdOpen(void) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val8[0] = 5;

    ret = CDSUB_UpdCdstat(0, pCmd);
    return ret;
}

Sint32 CDC_DataReady(Sint32 dtype) {
    Sint32 ret;
    Sint32 cdwnum;
    Sint32 bitpat;
    Sint32 hirq;

    bitpat = CDC_HIRQ_DRDY;
    if (dtype == CDC_DRDY_PUT) {
        bitpat |= CDC_HIRQ_EHST;
    }
    ret = CDREG_WaitHirq(bitpat, &hirq);
    if ((dtype == CDC_DRDY_PUT) && (ret == CDC_ERR_OK) &&
        (hirq & CDC_HIRQ_EHST)) {
        ret = CDC_ERR_PUT;
    }
    if (ret != CDC_ERR_OK) {
        CDC_DataEnd(&cdwnum);
    }
    CDREG_ClrHirqReq(~CDC_HIRQ_DRDY);
    return ret;
}

Sint32 CDC_DataEnd(Sint32* cdwnum) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmdRsp = &cmdRsp;
    pCmd->start.val8[0] = 6;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);
    *cdwnum = pCmdRsp->start.val32 & 0xFFFFFF;
    CDREG_ClrHirqReq(~CDC_HIRQ_DRDY);
    return ret;
}
