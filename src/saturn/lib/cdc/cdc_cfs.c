#include "cdc.h"

typedef union {
    Uint32 val32[2];
    Uint16 val16[4];
    Uint8 val8[8];
} CdcCmd;

Sint32 CDC_ChgDir(Sint32 filtno, Sint32 fid) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x70;
    pCmd->val32[1] = fid;
    pCmd->val8[4] = filtno;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_EFLS, pCmd);
    return ret;
}

Sint32 CDC_ReadDir(Sint32 filtno, Sint32 fid) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x71;
    pCmd->val32[1] = fid;
    pCmd->val8[4] = filtno;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_EFLS, pCmd);
    return ret;
}

Sint32 CDC_GetFileScope(Sint32* fid, Sint32* infnum, Bool* drend) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmdRsp = &cmdRsp;
    pCmd->val8[0] = 0x72;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);

    *infnum = pCmdRsp->val16[1];
    *drend = pCmdRsp->val8[4];
    *fid = pCmdRsp->val32[1] & 0xFFFFFF;

    return ret;
}

Sint32 CDC_TgetFileInfo(Sint32 fid, CdcFile* file) {
    Sint32 ret;
    Sint32 tsize;
    CdcCmd cmd;
    CdcCmd* pCmd;
    CdcCmd cmdRsp;
    CdcCmd* pCmdRsp;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmdRsp = &cmdRsp;
    pCmd->val8[0] = 0x73;
    pCmd->val32[1] = fid;
    pCmd->val8[4] = 0;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);
    if (ret != CDC_ERR_OK) {
        return ret;
    }

    tsize = pCmdRsp->val32[0] & 0xFFFFFF;
    ret = CDREG_TgetData(tsize, file);

    return ret;
}

Sint32 CDC_ReadFile(Sint32 filtno, Sint32 fid, Sint32 offset) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val32[0] = offset;
    pCmd->val8[0] = 0x74;
    pCmd->val32[1] = fid;
    pCmd->val8[4] = filtno;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_EFLS, pCmd);
    return ret;
}

Sint32 CDC_AbortFile(void) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x75;

    CDREG_SetHirqFlag(CDC_HIRQ_EFLS);

    ret = CDSUB_UpdCdstat(CDC_HIRQ_EFLS, pCmd);
    return ret;
}
