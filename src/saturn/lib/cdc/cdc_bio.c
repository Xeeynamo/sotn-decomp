#include "cdc.h"

typedef union {
    Uint32 val32[2];
    Uint16 val16[4];
    Uint8 val8[8];
} CdcCmd;

Sint32 CDC_SetSctLen(Sint32 getslen, Sint32 putslen) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x60;
    pCmd->val8[1] = getslen;
    pCmd->val8[2] = putslen;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_ESEL, pCmd);
    return ret;
}

Sint32 CDC_GetSctData(Sint32 bufno, Sint32 spos, Sint32 snum) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x61;
    pCmd->val16[1] = spos;
    pCmd->val8[4] = bufno;
    pCmd->val16[3] = snum;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_EHST, pCmd);
    return ret;
}

Sint32 CDC_DelSctData(Sint32 bufno, Sint32 spos, Sint32 snum) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x62;
    pCmd->val16[1] = spos;
    pCmd->val8[4] = bufno;
    pCmd->val16[3] = snum;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_EHST, pCmd);
    return ret;
}

Sint32 CDC_GetdelSctData(Sint32 bufno, Sint32 spos, Sint32 snum) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x63;
    pCmd->val16[1] = spos;
    pCmd->val8[4] = bufno;
    pCmd->val16[3] = snum;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_EHST, pCmd);
    return ret;
}

Sint32 CDC_PutSctData(Sint32 filtno, Sint32 snum) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x64;
    pCmd->val8[4] = filtno;
    pCmd->val16[3] = snum;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_EHST, pCmd);
    return ret;
}

Sint32 CDC_CopySctData(Sint32 srcbn, Sint32 spos, Sint32 snum, Sint32 dstfln) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x65;
    pCmd->val8[1] = dstfln;
    pCmd->val16[1] = spos;
    pCmd->val8[4] = srcbn;
    pCmd->val16[3] = snum;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_ECPY, pCmd);
    return ret;
}

Sint32 CDC_MoveSctData(Sint32 srcbn, Sint32 spos, Sint32 snum, Sint32 dstfln) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x66;
    pCmd->val8[1] = dstfln;
    pCmd->val16[1] = spos;
    pCmd->val8[4] = srcbn;
    pCmd->val16[3] = snum;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_ECPY, pCmd);
    return ret;
}

Sint32 CDC_GetCopyErr(Sint32* cpyerr) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmdRsp = &cmdRsp;
    pCmd->val8[0] = 0x67;
    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);
    *cpyerr = pCmdRsp->val8[1];

    return ret;
}
