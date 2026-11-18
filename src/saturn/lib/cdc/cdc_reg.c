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

const char DAT_0602DCC4[] = "CDC Version 1.22 1997-02-27";

const Uint16 DAT_0602DCE0[] = {0x00, 0x00};

Uint32* CDC_GetDataPtr(void) { return (Uint32*)0x25818000; }

Sint32 CDC_GetHirqReq(void) { return *((volatile Uint16*)0x25890008); }

extern Uint16 DAT_06057EF4;

void CDC_ClrHirqReq(Sint32 bitpat) {
    DAT_06057EF4 |= *(volatile Uint16*)0x25890008;
    bitpat |= 1;
    CDREG_ClrHirqReq(bitpat);
    return;
}

void CDREG_ClrHirqReq(Sint32 bitpat) {
    *(volatile Uint16*)0x25890008 = bitpat;
    return;
}

void CDREG_InitHirqReq(void) {
    CDREG_ClrHirqReq(
        CDC_HIRQ_MPED | CDC_HIRQ_EFLS | CDC_HIRQ_ECPY | CDC_HIRQ_EHST |
        CDC_HIRQ_ESEL | CDC_HIRQ_DCHG | CDC_HIRQ_CMOK);
    DAT_06057EF4 =
        CDC_HIRQ_MPED | CDC_HIRQ_EFLS | CDC_HIRQ_ECPY | CDC_HIRQ_EHST |
        CDC_HIRQ_ESEL | CDC_HIRQ_DCHG | CDC_HIRQ_CMOK;
    return;
}

void CDREG_SetHirqFlag(Sint32 bitpat) {
    DAT_06057EF4 |= bitpat;
    return;
}

Sint32 CDC_GetHirqMsk(void) { return *((volatile Uint16*)0x2589000C); }

void CDC_SetHirqMsk(Sint32 bitpat) {
    *((volatile Uint16*)0x2589000C) = bitpat;
    return;
}

Uint32* CDC_GetMpegPtr(void) { return (Uint32*)0x25810028; }

Sint32 CDREG_TgetData(Sint32 tsize, Uint16* toc) {
    Sint32 ret;
    Sint32 i;
    Sint32 cdwnum;
    Uint16* ptr;

    ret = CDC_DataReady(CDC_DRDY_GET);
    if (ret != CDC_ERR_OK) {
        return ret;
    }
    ptr = toc;
    for (i = 0; i < tsize; i++) {
        *ptr = *((volatile Uint16*)0x25898000);
        ptr++;
    }
    ret = CDC_DataEnd(&cdwnum);
    if ((ret == CDC_ERR_OK) && (tsize != cdwnum)) {
        ret = CDC_ERR_TRNS;
    }
    return ret;
}

Sint32 CDREG_CmdRsp(Sint32 bitpat, CdcCmd* pCmd, CdcCmd* pCmdRsp) {
    Sint32 ret;
    Uint32 msk;

    msk = get_imask();
    set_imask(15);
    ret = doCmdRsp(bitpat, pCmd, pCmdRsp);
    set_imask(msk);
    return ret;
}

Sint32 doCmdRsp(Sint32 bitpat, CdcCmd* pCmd, CdcCmd* pCmdRsp) {
    Sint32 ret;
    Sint32 hirq;
    Sint32 status;

    DAT_06057EF4 |= *((volatile Uint16*)0x25890008);
    if ((DAT_06057EF4 & bitpat) != bitpat) {
        return CDC_ERR_CMDBUSY;
    }
    if ((DAT_06057EF4 & CDC_HIRQ_CMOK) == 0) {
        return CDC_ERR_CMDNG;
    }
    CDREG_ClrHirqReq(~(bitpat | CDC_HIRQ_CMOK));
    DAT_06057EF4 &= ~CDC_HIRQ_CMOK;
    writeCmd(pCmd);
    ret = CDREG_WaitHirq(CDC_HIRQ_CMOK, &hirq);
    if (ret != CDC_ERR_OK) {
        return ret;
    }
    CDREG_ReadRsp(pCmdRsp);
    status = pCmdRsp->start.val8[0];
    if (status == CDC_ST_REJECT) {
        ret = CDC_ERR_REJECT;
    } else if (status & CDC_ST_WAIT) {
        ret = CDC_ERR_WAIT;
    }
    if (ret == CDC_ERR_OK) {
        DAT_06057EF4 &= ~bitpat;
    }
    return ret;
}

Sint32 CDREG_WaitHirq(Sint32 bitpat, Sint32* hirq) {
    Sint32 i;
    Sint32 ret;
    Sint32 temp;

    ret = CDC_ERR_TMOUT;
    for (i = 0; i < 0x240000; i++) {
        temp = *((volatile Uint16*)0x25890008);
        if (temp & bitpat) {
            ret = CDC_ERR_OK;
            *hirq = temp;
            break;
        }
    }
    return ret;
}

void writeCmd(CdcCmd* cmd) {
    *((volatile Uint16*)0x25890018) = cmd->start.val16[0];
    *((volatile Uint16*)0x2589001C) = cmd->start.val16[1];
    *((volatile Uint16*)0x25890020) = cmd->end.val16[0];
    *((volatile Uint16*)0x25890024) = cmd->end.val16[1];
    return;
}

void CDREG_ReadRsp(CdcCmd* cmd) {
    cmd->start.val16[0] = *((volatile Uint16*)0x25890018);
    cmd->start.val16[1] = *((volatile Uint16*)0x2589001C);
    cmd->end.val16[0] = *((volatile Uint16*)0x25890020);
    cmd->end.val16[1] = *((volatile Uint16*)0x25890024);
    return;
}
