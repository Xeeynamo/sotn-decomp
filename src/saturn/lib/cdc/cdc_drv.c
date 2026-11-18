#include "cdc.h"

typedef union {
    Uint32 val32[2];
    Uint16 val16[4];
    Uint8 val8[8];
} CdcCmd;

Sint32 CDC_CdPlay(CdcPly* ply) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x10;
    func_0602D528(&ply->start, &pCmd->val8[1]);

    pCmd->val8[4] = ply->pmode;
    func_0602D528(&ply->end, &pCmd->val8[5]);

    ret = CDSUB_UpdCdstat(0, pCmd);
    return ret;
}

void func_0602D528(CdcPos* pos, Uint8* arg1) {
    switch (CDC_POS_PTYPE(pos)) {
    case CDC_PTYPE_TNO:
        arg1[0] = 0;
        arg1[1] = CDC_POS_TNO(pos);
        arg1[2] = CDC_POS_IDX(pos);
        break;

    case CDC_PTYPE_FAD:
        arg1[0] = ((Uint8*)&CDC_POS_FAD(pos))[1] | 0x80;
        arg1[1] = ((Uint8*)&CDC_POS_FAD(pos))[2];
        arg1[2] = ((Uint8*)&CDC_POS_FAD(pos))[3];
        break;

    case CDC_PTYPE_NOCHG:
        arg1[0] = CDC_PM_NOCHG;
        arg1[1] = CDC_PM_NOCHG;
        arg1[2] = CDC_PM_NOCHG;
        break;

    case CDC_PTYPE_DFL:
    default:
        arg1[0] = CDC_PM_DFL;
        arg1[1] = CDC_PM_DFL;
        arg1[2] = CDC_PM_DFL;
        break;
    }
    return;
}

Sint32 CDC_CdSeek(CdcPos* pos) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x11;
    func_0602D528(pos, &pCmd->val8[1]);

    ret = CDSUB_UpdCdstat(0, pCmd);
    return ret;
}

Sint32 CDC_CdScan(Sint32 scandir) {
    Sint32 ret;
    CdcCmd cmd;
    CdcCmd* pCmd;

    pCmd = &cmd;
    pCmd->val32[0] = 0;
    pCmd->val32[1] = 0;

    pCmd->val8[0] = 0x12;
    pCmd->val8[1] = scandir;

    ret = CDSUB_UpdCdstat(0, pCmd);
    return ret;
}
