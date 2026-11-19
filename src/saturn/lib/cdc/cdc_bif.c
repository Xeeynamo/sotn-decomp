#include "cdc.h"

typedef union {
    Uint32 val32[2];
    Uint16 val16[4];
    Uint8 val8[8];
} CdcCmd;

Sint32 CDC_GetBufSiz(Sint32* totalsiz, Sint32* bufnum, Sint32* freesiz) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmdRsp = &cmdRsp;
    pCmd->val8[0] = 0x50;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);

    *freesiz = pCmdRsp->val16[1];
    *bufnum = pCmdRsp->val8[4];
    *totalsiz = pCmdRsp->val16[3];

    return ret;
}

Sint32 CDC_GetSctNum(Sint32 bufno, Sint32* snum) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmdRsp = &cmdRsp;
    pCmd->val8[0] = 0x51;
    pCmd->val8[4] = bufno;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);
    *snum = pCmdRsp->val16[3];

    return ret;
}

Sint32 CDC_CalActSiz(Sint32 bufno, Sint32 spos, Sint32 snum) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x52;
    pCmd->val16[1] = spos;
    pCmd->val8[4] = bufno;
    pCmd->val16[3] = snum;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_ESEL, pCmd);
    return ret;
}

Sint32 CDC_GetActSiz(Sint32* actwnum) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmdRsp = &cmdRsp;
    pCmd->val8[0] = 0x53;

    ret = chkEselUpdStatus(pCmd, pCmdRsp);
    *actwnum = pCmdRsp->val32[0] & 0xFFFFFF;

    return ret;
}

Sint32 chkEselUpdStatus(CdcCmd* pCmd, CdcCmd* pCmdRsp) {
    Sint32 ret;
    Sint32 hirq;

    hirq = CDC_GetHirqReq();
    if (!(hirq & CDC_HIRQ_ESEL)) {
        return CDC_ERR_CMDBUSY;
    }
    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);
    return ret;
}

Sint32 CDC_GetSctInfo(Sint32 bufno, Sint32 spos, CdcSct* sct) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmdRsp = &cmdRsp;
    pCmd->val8[0] = 0x54;
    pCmd->val16[1] = spos;
    pCmd->val8[4] = bufno;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);

    sct->fad = pCmdRsp->val32[0] & 0xFFFFFF;
    sct->fn = pCmdRsp->val8[4];
    sct->cn = pCmdRsp->val8[5];
    sct->sm = pCmdRsp->val8[6];
    sct->ci = pCmdRsp->val8[7];

    return ret;
}

Sint32 CDC_ExeFadSearch(Sint32 bufno, Sint32 spos, Sint32 fad) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x55;
    pCmd->val16[1] = spos;
    pCmd->val32[1] = fad;
    pCmd->val8[4] = bufno;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_ESEL, pCmd);
    return ret;
}

Sint32 CDC_GetFadSearch(Sint32* bufno, Sint32* spos, Sint32* fad) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmdRsp = &cmdRsp;
    pCmd->val8[0] = 0x56;

    ret = chkEselUpdStatus(pCmd, pCmdRsp);

    *spos = pCmdRsp->val16[1];
    *bufno = pCmdRsp->val8[4];
    *fad = pCmdRsp->val32[1] & 0xFFFFFF;

    return ret;
}
