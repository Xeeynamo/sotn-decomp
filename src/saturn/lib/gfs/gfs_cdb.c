#include "../../sattypes.h"
#include "../../inc_asm.h"

#include "gfs.h"
#include "gfs_def.h"
#include "gfs_cdf.h"
#include "gfs_cdb.h"
#include "gfs_cdc.h"
#include "gfs_trn.h"

#define BUF_TOP 0

#define FMODE_SELECT_FN 0x01
#define FMODE_SELECT_CN 0x02
#define FMODE_SELECT_SM 0x04
#define FMODE_SELECT_CI 0x08
#define FMODE_REV_SUBH 0x10
#define FMODE_SELECT_FRNG 0x40
#define FMODE_INIT_FMODE 0x80

#define CDB_ADDR_DLT 0

#define GFCB_NOSEL 0

// 0x0601F3A4
Bool GFCB_Setup(GfsFlow* flow) {
    GfsFinfo* finfo = &GFS_FLW_FINFO(flow);
    GfsDtsrc* dts = &GFS_FLW_DTSRC(flow);
    Sint32 bufno, fltno;
    CdcSubh subh;

    GFS_DTS_FTYPE(dts) = CD_FILE;
    GFS_CDR_FMODE(dts) = FMODE_SELECT_FN;
    CDC_SUBH_FN(&subh) = GFS_FI_FN(finfo);
    CDC_SUBH_CN(&subh) = GFCB_NOSEL;
    CDC_SUBH_SMMSK(&subh) = GFCB_NOSEL;
    CDC_SUBH_SMVAL(&subh) = GFCB_NOSEL;
    CDC_SUBH_CIMSK(&subh) = 0;
    CDC_SUBH_CIVAL(&subh) = 0;
    GFS_CDR_SUBH(dts) = subh;
    GFS_CDR_PUID(dts) = GFCD_UID_NONE;
    GFS_CDR_SCTPOS(dts) = 0;
    GFS_CDR_FILEPOS(dts) = 0;
    GFS_CDR_SFAD(dts) = GFS_CDR_EFAD(dts) = 0;
    if (GFCD_AllocBuf(&bufno) != GFCD_ERR_OK) {
        return FALSE;
    }
    GFS_CDR_BUFNO(dts) = bufno;
    if (GFCD_AllocFilt(&fltno) != GFCD_ERR_OK) {
        GFCD_FreeBuf(bufno);
        return FALSE;
    }
    GFS_CDR_FLT(dts) = fltno;
    if (GFCD_SetFilt(fltno, GFS_CDR_FMODE(dts), &subh, 0, 0) != GFCD_ERR_OK) {
        return FALSE;
    }
    if (GFCD_SetFiltCon(fltno, bufno, CDC_NUL_SEL) != GFCD_ERR_OK) {
        return FALSE;
    }
    if (GFCD_WaitServer() != GFCD_ERR_OK) {
        return FALSE;
    }
    if (GFCB_DeleteAllData(dts) != GFCD_ERR_OK) {
        return FALSE;
    }
    return TRUE;
}

// 0x0601F4B0
void GFCB_Close(GfsDtsrc* dts) {
    GFCD_FreeBuf(GFS_CDR_BUFNO(dts));
    GFCD_FreeFilt(GFS_CDR_FLT(dts));
}

// 0x0601F4D8
Sint32 GFCB_GetLenData(GfsFlow* flow, Sint32 usct, Sint32* asiz) {
    Sint32 ret, nsct;
    Sint32 sctsiz, fsct, lastsiz;
    GfsDtsrc* dts = &GFS_FLW_DTSRC(flow);

    ret = GFCD_GetLenData(
        GFS_CDR_BUFNO(dts), GFS_CDR_SCTPOS(dts), usct, &nsct, asiz);
    if (ret != GFCD_ERR_OK) {
        return 0;
    }
    if (GFCD_WaitServer() != GFCD_ERR_OK) {
        return 0;
    }
    if (asiz != NULL) {
        GFCF_GetFileInfo(
            flow, NULL, NULL, &sctsiz, &fsct, &lastsiz, NULL, NULL);
        if ((GFCB_Tell(dts) + nsct >= fsct) && (lastsiz != 0) && (nsct > 0)) {
            *asiz -= sctsiz - lastsiz;
        }
    }
    return nsct;
}

// 0x0601F57C
Sint32 GFCB_GetLenRoom(GfsDtsrc* dts) { return 0; }

// 0x0601F588
void GFCB_SetFilt(GfsDtsrc* dts, Sint32 fmode, CdcSubh* subh) {
    Sint32 ret;

    GFS_CDR_FMODE(dts) = fmode;
    GFS_CDR_SUBH(dts) = *subh;
    ret = GFCD_SetFilt(GFS_CDR_FLT(dts), fmode, subh, 0, 0);
    if (ret != GFCD_ERR_OK) {
        return;
    }
    GFCD_WaitServer();
}

// 0x0601F5EC
Sint32 GFCB_DeleteAllData(GfsDtsrc* dts) {
    GFCD_DelSctData(GFS_CDR_BUFNO(dts), BUF_TOP, CDC_SNUM_END);
    return GFCD_WaitServer();
}

// 0x0601F614
Sint32 GFCB_Tell(GfsDtsrc* dts) {
    return GFS_CDR_FILEPOS(dts) + GFS_CDR_SCTPOS(dts);
}

// 0x0601F624
Sint32 gfcb_getSctNum(GfsDtsrc* dts) {
    Sint32 nsct;
    Sint32 ret;

    ret =
        GFCD_GetLenData(GFS_CDR_BUFNO(dts), BUF_TOP, GFTB_BUF_END, &nsct, NULL);
    if (ret != GFCD_ERR_OK) {
        return -1;
    }
    if (GFCD_WaitServer() != GFCD_ERR_OK) {
        return -1;
    }
    if (nsct < 0) {
        nsct = 0;
    }
    return nsct;
}

// 0x0601F670
Sint32 GFCB_Seek(GfsFlow* flow, Sint32 off, Sint32 org) {
    Sint32 nsct;
    GfsDtsrc* dts = &GFS_FLW_DTSRC(flow);

    if (off < 0) {
        off = 0;
    }
    if (org == GFS_SEEK_CUR) {
        nsct = off;
        off = GFCB_Tell(dts) + nsct;
    } else {
        if (GFCB_Tell(dts) == off) {
            return off;
        }
        nsct = gfcb_getSctNum(dts);
        if (nsct < 0) {
            return -1;
        }
    }
    if (GFS_FLW_GMODE(flow) == GFS_GMODE_ERASE) {
        if ((GFS_CDR_FILEPOS(dts) <= off) && (off < GFCB_Tell(dts))) {
            nsct = off - GFS_CDR_FILEPOS(dts);
        }
        if (nsct > 0) {
            GFCD_DelSctData(GFS_CDR_BUFNO(dts), BUF_TOP, nsct);
            if (GFCD_WaitServer() != GFCD_ERR_OK) {
                return -1;
            }
        }
        GFS_CDR_FILEPOS(dts) = off;
        GFS_CDR_SCTPOS(dts) = 0;
    } else if (GFS_FLW_GMODE(flow) == GFS_GMODE_RESIDENT) {
        if (org == GFS_SEEK_CUR) {
            nsct = gfcb_getSctNum(dts);
            if (nsct < 0) {
                return -1;
            }
        }
        if ((off < GFS_CDR_FILEPOS(dts)) ||
            (off > (GFS_CDR_FILEPOS(dts) + nsct))) {
            if (GFCB_DeleteAllData(dts) != GFCD_ERR_OK) {
                return -1;
            }
            GFS_CDR_FILEPOS(dts) = off;
        }
        GFS_CDR_SCTPOS(dts) = off - GFS_CDR_FILEPOS(dts);
    }
    return GFCB_Tell(dts);
}

// 0x0601F768
GfdpHn GFCB_GetSrcPack(GfsFlow* flow, Sint32 usct) {
    Sint32 len, nsct;
    Sint32 sctsiz, fsct, lastsiz;
    GfsDtsrc* dts = &GFS_FLW_DTSRC(flow);
    GfdpHn dpk = &MNG_SRCPK(gfs_mng_ptr);

    if (GFDP_USE(dpk)) {
        return NULL;
    }

    if (GFCD_GetLenData(GFS_CDR_BUFNO(dts), GFS_CDR_SCTPOS(dts), usct, &nsct,
                        &len) != GFCD_ERR_OK) {
        return NULL;
    }
    if (GFCD_WaitServer() != GFCD_ERR_OK) {
        return NULL;
    }
    if (len <= 0) {
        return NULL;
    }
    GFCF_GetFileInfo(flow, NULL, NULL, &sctsiz, &fsct, &lastsiz, NULL, NULL);
    if ((GFCB_Tell(dts) + nsct >= fsct) && (lastsiz != 0) && (nsct > 0)) {
        len -= sctsiz - lastsiz;
    }
    GFDP_DATA(dpk) = CDC_GetDataPtr();
    GFDP_ADLT(dpk) = CDB_ADDR_DLT;
    GFDP_LEN(dpk) = len;
    GFDP_NSCT(dpk) = nsct;
    GFDP_USE(dpk) = TRUE;
    return dpk;
}

// 0x0601F840
Bool GFCB_GetSctData(GfdpHn dpk, GfsDtsrc* dts) {
    Sint32 ret;

    ret = GFCD_ReqData(GFS_CDR_BUFNO(dts), GFS_CDR_SCTPOS(dts), GFDP_NSCT(dpk));
    if (ret != GFCD_ERR_OK) {
        return FALSE;
    }
    if (GFCD_WaitServer() != GFCD_ERR_OK) {
        return FALSE;
    }
    return TRUE;
}

// 0x0601F878
GfdpHn GFCB_GetDstPack(GfsDtsrc* dts, Sint32 len) { return NULL; }

// 0x0601F884
void GFCB_RtnPk(GfsFlow* flow, GfdpHn dpk, Sint32 nsct) {
    Sint32 txw;

    GFCD_EndData(&txw);
    if (nsct == GFTR_ALLSCT) {
        nsct = GFDP_NSCT(dpk);
    }
    GFCB_Seek(flow, nsct, GFS_SEEK_CUR);
    GFDP_USE(dpk) = FALSE;
}

// 0x0601F8CC
Sint32 GFCB_MovePickup(GfsDtsrc* dts, CdcPos* pos) {
    return GFCD_MovePickup(pos, GFS_CDR_PUID(dts));
}

// 0x0601F8E8
Bool GFCB_SetCon(GfsDtsrc* dts) {
    Sint32 ec;

    ec = GFCD_SetCon(GFS_CDR_FLT(dts), GFS_CDR_PUID(dts));
    if (ec != GFCD_ERR_OK) {
        return FALSE;
    }
    ec = GFCD_WaitServer();
    if (ec != GFCD_ERR_OK) {
        return FALSE;
    }
    return TRUE;
}

// 0x0601F91C
Bool GFCB_GetPickup(GfsDtsrc* dts) {
    Sint32 puid = GFCD_GetPickup();

    if (puid < GFCD_ERR_OK) {
        return FALSE;
    }
    GFS_CDR_PUID(dts) = puid;
    return TRUE;
}

// 0x0601F944
Bool GFCB_IsPuOwner(GfsDtsrc* dts) { return GFCD_IsPuOwner(GFS_CDR_PUID(dts)); }

// 0x0601F95C
void GFCB_UngetPickup(GfsDtsrc* dts) { GFCD_UngetPickup(GFS_CDR_PUID(dts)); }
