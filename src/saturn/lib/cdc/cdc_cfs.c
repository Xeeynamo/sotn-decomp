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

Sint32 CDC_ChgDir(Sint32 filtno, Sint32 fid) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val8[0] = 0x70;
    pCmd->end.val32 = fid;
    pCmd->end.val8[0] = filtno;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_EFLS, pCmd);
    return ret;
}

Sint32 CDC_ReadDir(Sint32 filtno, Sint32 fid) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val8[0] = 0x71;
    pCmd->end.val32 = fid;
    pCmd->end.val8[0] = filtno;

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
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmdRsp = &cmdRsp;
    pCmd->start.val8[0] = 0x72;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);

    *infnum = pCmdRsp->start.val16[1];
    *drend = pCmdRsp->end.val8[0];
    *fid = pCmdRsp->end.val32 & 0xFFFFFF;

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
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmdRsp = &cmdRsp;
    pCmd->start.val8[0] = 0x73;
    pCmd->end.val32 = fid;
    pCmd->end.val8[0] = 0;

    ret = CDSUB_UpdStatus(0, pCmd, pCmdRsp);
    if (ret != CDC_ERR_OK) {
        return ret;
    }

    tsize = pCmdRsp->start.val32 & 0xFFFFFF;
    ret = CDREG_TgetData(tsize, file);

    return ret;
}

Sint32 CDC_ReadFile(Sint32 filtno, Sint32 fid, Sint32 offset) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val32 = offset;
    pCmd->start.val8[0] = 0x74;
    pCmd->end.val32 = fid;
    pCmd->end.val8[0] = filtno;

    ret = CDSUB_UpdCdstat(CDC_HIRQ_EFLS, pCmd);
    return ret;
}

Sint32 CDC_AbortFile(void) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->start.val32 = 0;
    pCmd->end.val32 = 0;

    pCmd->start.val8[0] = 0x75;

    CDREG_SetHirqFlag(CDC_HIRQ_EFLS);

    ret = CDSUB_UpdCdstat(CDC_HIRQ_EFLS, pCmd);
    return ret;
}
