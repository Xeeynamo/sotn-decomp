#include "cdc.h"

typedef union {
    Uint32 val32[2];
    Uint16 val16[4];
    Uint8 val8[8];
} CdcCmd;

Sint32 CDC_CdSetCon(Sint32 filtno) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x30;
    pCmd->val8[4] = filtno;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_ESEL, pCmd);
    return ret;
}

Sint32 CDC_CdGetCon(Sint32* filtno) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmdRsp = &cmdRsp;
    pCmd->val8[0] = 0x31;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);
    *filtno = pCmdRsp->val8[4];

    return ret;
}

Sint32 CDC_CdGetLastBuf(Sint32* bufno) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmdRsp = &cmdRsp;
    pCmd->val8[0] = 0x32;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);
    *bufno = pCmdRsp->val8[4];

    return ret;
}
