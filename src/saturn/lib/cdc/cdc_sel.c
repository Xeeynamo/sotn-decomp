#include "cdc.h"

typedef union {
    Uint32 val32[2];
    Uint16 val16[4];
    Uint8 val8[8];
} CdcCmd;

Sint32 CDC_SetFiltRange(Sint32 filtno, Sint32 fad, Sint32 fasnum) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val32[0] = fad;
    pCmd->val8[0] = 0x40;
    pCmd->val32[1] = fasnum;
    pCmd->val8[4] = filtno;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_ESEL, pCmd);
    return ret;
}

Sint32 CDC_GetFiltRange(Sint32 filtno, Sint32* fad, Sint32* fasnum) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmdRsp = &cmdRsp;
    pCmd->val8[0] = 0x41;
    pCmd->val8[4] = filtno;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);

    *fad = pCmdRsp->val32[0] & 0xFFFFFF;
    *fasnum = pCmdRsp->val32[1] & 0xFFFFFF;
    return ret;
}

Sint32 CDC_SetFiltSubh(Sint32 filtno, CdcSubh* subh) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x42;
    pCmd->val8[1] = subh->cn;
    pCmd->val8[2] = subh->smmsk;
    pCmd->val8[3] = subh->cimsk;
    pCmd->val8[4] = filtno;
    pCmd->val8[5] = subh->fn;
    pCmd->val8[6] = subh->smval;
    pCmd->val8[7] = subh->cival;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_ESEL, pCmd);
    return ret;
}

Sint32 CDC_GetFiltSubh(Sint32 filtno, CdcSubh* subh) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmdRsp = &cmdRsp;
    pCmd->val8[0] = 0x43;
    pCmd->val8[4] = filtno;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);

    subh->cn = pCmdRsp->val8[1];
    subh->smmsk = pCmdRsp->val8[2];
    subh->cimsk = pCmdRsp->val8[3];
    subh->fn = pCmdRsp->val8[5];
    subh->smval = pCmdRsp->val8[6];
    subh->cival = pCmdRsp->val8[7];
    return ret;
}

Sint32 CDC_SetFiltMode(Sint32 filtno, Sint32 fmode) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x44;
    pCmd->val8[1] = fmode;
    pCmd->val8[4] = filtno;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_ESEL, pCmd);
    return ret;
}

Sint32 CDC_GetFiltMode(Sint32 filtno, Sint32* fmode) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmdRsp = &cmdRsp;
    pCmd->val8[0] = 0x45;
    pCmd->val8[4] = filtno;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);

    *fmode = pCmdRsp->val8[1];
    return ret;
}

Sint32 CDC_SetFiltCon(
    Sint32 filtno, Sint32 cflag, Sint32 bufno, Sint32 flnout) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x46;
    pCmd->val8[1] = cflag;
    pCmd->val8[2] = bufno;
    pCmd->val8[3] = flnout;
    pCmd->val8[4] = filtno;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_ESEL, pCmd);
    return ret;
}

Sint32 CDC_GetFiltCon(Sint32 filtno, Sint32* bufno, Sint32* flnout) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmdRsp = &cmdRsp;
    pCmd->val8[0] = 0x47;
    pCmd->val8[4] = filtno;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);

    *bufno = pCmdRsp->val8[2];
    *flnout = pCmdRsp->val8[3];
    return ret;
}

Sint32 CDC_ResetSelector(Sint32 rflag, Sint32 bufno) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x48;
    pCmd->val8[1] = rflag;
    pCmd->val8[4] = bufno;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_ESEL, pCmd);
    return ret;
}
