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

Sint32 CDC_SetFiltRange(Sint32 filtno, Sint32 fad, Sint32 fasnum) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val32 = fad;
    pCmd->start.val8[0] = 0x40;
    pCmd->end.val32 = fasnum;
    pCmd->end.val8[0] = filtno;

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
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmdRsp = &cmdRsp;
    pCmd->start.val8[0] = 0x41;
    pCmd->end.val8[0] = filtno;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);

    *fad = pCmdRsp->start.val32 & 0xFFFFFF;
    *fasnum = pCmdRsp->end.val32 & 0xFFFFFF;
    return ret;
}

Sint32 CDC_SetFiltSubh(Sint32 filtno, CdcSubh* subh) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val8[0] = 0x42;
    pCmd->start.val8[1] = subh->cn;
    pCmd->start.val8[2] = subh->smmsk;
    pCmd->start.val8[3] = subh->cimsk;
    pCmd->end.val8[0] = filtno;
    pCmd->end.val8[1] = subh->fn;
    pCmd->end.val8[2] = subh->smval;
    pCmd->end.val8[3] = subh->cival;

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
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmdRsp = &cmdRsp;
    pCmd->start.val8[0] = 0x43;
    pCmd->end.val8[0] = filtno;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);

    subh->cn = pCmdRsp->start.val8[1];
    subh->smmsk = pCmdRsp->start.val8[2];
    subh->cimsk = pCmdRsp->start.val8[3];
    subh->fn = pCmdRsp->end.val8[1];
    subh->smval = pCmdRsp->end.val8[2];
    subh->cival = pCmdRsp->end.val8[3];
    return ret;
}

Sint32 CDC_SetFiltMode(Sint32 filtno, Sint32 fmode) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val8[0] = 0x44;
    pCmd->start.val8[1] = fmode;
    pCmd->end.val8[0] = filtno;

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
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmdRsp = &cmdRsp;
    pCmd->start.val8[0] = 0x45;
    pCmd->end.val8[0] = filtno;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);

    *fmode = pCmdRsp->start.val8[1];
    return ret;
}

Sint32 CDC_SetFiltCon(
    Sint32 filtno, Sint32 cflag, Sint32 bufno, Sint32 flnout) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val8[0] = 0x46;
    pCmd->start.val8[1] = cflag;
    pCmd->start.val8[2] = bufno;
    pCmd->start.val8[3] = flnout;
    pCmd->end.val8[0] = filtno;

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
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmdRsp = &cmdRsp;
    pCmd->start.val8[0] = 0x47;
    pCmd->end.val8[0] = filtno;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);

    *bufno = pCmdRsp->start.val8[2];
    *flnout = pCmdRsp->start.val8[3];
    return ret;
}

Sint32 CDC_ResetSelector(Sint32 rflag, Sint32 bufno) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val8[0] = 0x48;
    pCmd->start.val8[1] = rflag;
    pCmd->end.val8[0] = bufno;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_ESEL, pCmd);
    return ret;
}
