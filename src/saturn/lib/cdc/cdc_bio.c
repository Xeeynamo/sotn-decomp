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

Sint32 CDC_SetSctLen(Sint32 getslen, Sint32 putslen) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val8[0] = 0x60;
    pCmd->start.val8[1] = getslen;
    pCmd->start.val8[2] = putslen;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_ESEL, pCmd);
    return ret;
}

Sint32 CDC_GetSctData(Sint32 bufno, Sint32 spos, Sint32 snum) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val8[0] = 0x61;
    pCmd->start.val16[1] = spos;
    pCmd->end.val8[0] = bufno;
    pCmd->end.val16[1] = snum;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_EHST, pCmd);
    return ret;
}

Sint32 CDC_DelSctData(Sint32 bufno, Sint32 spos, Sint32 snum) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val8[0] = 0x62;
    pCmd->start.val16[1] = spos;
    pCmd->end.val8[0] = bufno;
    pCmd->end.val16[1] = snum;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_EHST, pCmd);
    return ret;
}

Sint32 CDC_GetdelSctData(Sint32 bufno, Sint32 spos, Sint32 snum) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val8[0] = 0x63;
    pCmd->start.val16[1] = spos;
    pCmd->end.val8[0] = bufno;
    pCmd->end.val16[1] = snum;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_EHST, pCmd);
    return ret;
}

Sint32 CDC_PutSctData(Sint32 filtno, Sint32 snum) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val8[0] = 0x64;
    pCmd->end.val8[0] = filtno;
    pCmd->end.val16[1] = snum;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_EHST, pCmd);
    return ret;
}

Sint32 CDC_CopySctData(Sint32 srcbn, Sint32 spos, Sint32 snum, Sint32 dstfln) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val8[0] = 0x65;
    pCmd->start.val8[1] = dstfln;
    pCmd->start.val16[1] = spos;
    pCmd->end.val8[0] = srcbn;
    pCmd->end.val16[1] = snum;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_ECPY, pCmd);
    return ret;
}

Sint32 CDC_MoveSctData(Sint32 srcbn, Sint32 spos, Sint32 snum, Sint32 dstfln) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val8[0] = 0x66;
    pCmd->start.val8[1] = dstfln;
    pCmd->start.val16[1] = spos;
    pCmd->end.val8[0] = srcbn;
    pCmd->end.val16[1] = snum;

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
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmdRsp = &cmdRsp;
    pCmd->start.val8[0] = 0x67;
    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);
    *cpyerr = pCmdRsp->start.val8[1];

    return ret;
}
