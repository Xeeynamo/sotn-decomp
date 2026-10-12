#include "../../sattypes.h"
#include "../../inc_asm.h"

#include "gfs.h"
#include "gfs_def.h"
#include "gfs_mmf.h"
#include "gfs_cdf.h"
#include "gfs_cdb.h"
#include "gfs_dir.h"
#include "gfs_trn.h"
#include "gfs_cdc.h"
#include "gfs_buf.h"

#include "../int.h"
#include "gfs_sf.h"

// SEGADGFS.A (debug version of lib)

const char gfs_version[] = "GFS_SBL Version 2.14 1997-04-11";

#define PVD_FAD 166
#define PVD_BYTSIZ GFS_MD1_SCTSIZ
#define PVD_SCTSIZ 1

#define ROOT_FAD_LOW_LIM (150 + 16)

#define ROOT_RECPOS 156

#define FREAD_TMOUT_COUNT 300000L

#define SVR_NOHNDL (-1)

#define LSN_TO_FAD(lsn) ((lsn) += 150)

#define DIRREC_EXT(rec) ((rec) + 6)
#define DIRREC_LEN(rec) ((rec) + 14)

GFS_LOCAL Sint32 gfs_chgRoot(GfsDirTbl* dirtbl);
GFS_LOCAL Sint32 gfs_aborttrans(GfsHn gfs, Sint32 nsct);
GFS_LOCAL void gfs_mngSetupFuncTbl(void);
GFS_LOCAL void gfs_mngInitWork(Sint32 open_max);
GFS_LOCAL Sint32 gfs_mngGetNumFile(GfsDirTbl* dirtbl);
GFS_LOCAL void gfs_mngFreeGrp(GfsFile* gfs);
GFS_LOCAL void gfs_mngTermAccess(GfsHn gfs, Bool wait_pause);
GFS_LOCAL Sint32 gfs_mngSetErrCode(Sint32 code);
GFS_LOCAL Sint32 gfs_svrSearchHndl(GfsHn gfs);
GFS_LOCAL void gfs_svrAddHndl(GfsHn gfs);
GFS_LOCAL void gfs_svrRemoveHndl(GfsHn gfs);
GFS_LOCAL Sint32 gfs_loadVol(Uint8* buf);
GFS_LOCAL Sint32 gfs_getRootDir(GfsDirId* dir);
GFS_LOCAL Sint32 gfs_loadRootDir(GfsDirTbl* dirtbl);
GFS_LOCAL Sint32 gfs_flowIn(GfsHn gfs);
GFS_LOCAL Sint32 gfs_transData(GfsHn gfs);
GFS_LOCAL void gfs_SetSct(GfsFlow* flow, Sint32 sct);
GFS_LOCAL void gfs_GetFinfo(
    GfsFlow* flow, Sint32* fid, Sint32* fad, Sint32* sctsiz, Sint32* nsct,
    Sint32* lastsiz, Sint32* fno, Sint32* atr);
GFS_LOCAL void gfs_closeSub(GfsHn gfs);
GFS_LOCAL Sint32 gfs_getGmode(GfsHn gfs);
GFS_LOCAL Bool gfs_isTaskDone(GfsHn gfs);
GFS_LOCAL Sint32 gfs_convFinStat(GfsHn gfs, Sint32 fstat);
GFS_LOCAL Sint32 gfs_waitRead(GfsHn gfs);

// 0x0601B2B4
Sint32 GFS_Init(Sint32 open_max, void* work, GfsDirTbl* dirtbl) {
    Sint32 ndir, ret;

    gfs_use_scudma = FALSE;
    if ((open_max < 1) || (GFS_OPEN_MAX < open_max)) {
        return GFS_ERR_OPENMAX;
    }
    if (((Uint32)work) & 3) {
        return GFS_ERR_ALIGN;
    }
    if (dirtbl != NULL) {
        if (((GFS_DIRTBL_TYPE(dirtbl) != GFS_DIR_ID) &&
             (GFS_DIRTBL_TYPE(dirtbl) != GFS_DIR_NAME)) ||
            (GFS_DIRTBL_NDIR(dirtbl) < 2) ||
            (GFS_DIRTBL_DIRID(dirtbl) == NULL)) {
            return GFS_ERR_DIRTBL;
        }
    }
    INT_ChgMsk(INT_MSK_DMA0, INT_MSK_NULL);

    gfs_mng_ptr = work;
    gfs_mngInitWork(open_max);
    ret = GFCF_Init((dirtbl == NULL) ? TRUE : FALSE);
    if (dirtbl == NULL) {
        return gfs_mngSetErrCode(GFS_ERR_CDBFS);
    }
    GFMF_Init();
    GFSF_Init();
    ndir = gfs_chgRoot(dirtbl);
    if (ndir < 0) {
        return gfs_mngSetErrCode(ndir);
    }
    ret = gfs_mngSetErrCode(GFS_ERR_OK);
    if (ret < 0) {
        return ret;
    }
    return ndir;
}

// 0x0601B3A0
Sint32 GFS_LoadDir(Sint32 fid, GfsDirTbl* dirtbl) {
    GfsHn gfs;
    Sint32 nsct;
    Sint32 readdir;

    if (dirtbl == NULL) {
        if (DIRMNG_DIRID(&MNG_CURDIR(gfs_mng_ptr)) != NULL) {
            return gfs_mngSetErrCode(GFS_ERR_CDBFS);
        }
        readdir = GFDR_ChgDir(fid);
        if (readdir < 0) {
            return gfs_mngSetErrCode(readdir);
        }
        return readdir;
    }
    gfs = GFS_Open(fid);
    if (gfs == NULL) {
        return GFS_ERR_CODE(&MNG_ERROR(gfs_mng_ptr));
    }
    GFS_GetFileSize(gfs, NULL, &nsct, NULL);
    readdir = GFDR_SetupDirTbl(gfs, dirtbl, nsct);
    GFS_Close(gfs);
    return readdir;
}

// 0x0601B448
Sint32 GFS_SetDir(GfsDirTbl* dirtbl) {
    GfsDirMng* mng;

    mng = &MNG_CURDIR(gfs_mng_ptr);
    if (dirtbl == NULL) {
        if (DIRMNG_DIRID(mng) != NULL) {
            return gfs_mngSetErrCode(GFS_ERR_CDBFS);
        }
        DIRMNG_DIRID(mng) = NULL;
        DIRMNG_NDIR(mng) = DIRMNG_NFILE(mng) = 0;
    } else {
        DIRMNG_DIRTBL(mng) = *dirtbl;
        DIRMNG_NFILE(mng) = gfs_mngGetNumFile(dirtbl);
    }
    return gfs_mngSetErrCode(GFS_ERR_OK);
}

// 0x0601B4AC
Sint32 GFS_NameToId(Sint8* fname) {
    Sint32 fid;
    GfsDirMng* cdir = &MNG_CURDIR(gfs_mng_ptr);
    Sint32 ret;

    if ((DIRMNG_DIRID(cdir) == NULL) || (DIRMNG_TYPE(cdir) != GFS_DIR_NAME)) {
        return gfs_mngSetErrCode(GFS_ERR_NONAME);
    }
    fid = GFDR_NameToId(DIRMNG_DIRNAME(cdir), fname, DIRMNG_NDIR(cdir));
    if (fid < 0) {
        return gfs_mngSetErrCode(GFS_ERR_NEXIST);
    }
    ret = gfs_mngSetErrCode(GFS_ERR_OK);
    if (ret < 0) {
        return ret;
    }
    return fid;
}

// 0x0601B518
Sint8* GFS_IdToName(Sint32 fid) {
    GfsDirName* pdir;
    GfsDirMng* cdir = &MNG_CURDIR(gfs_mng_ptr);
    Sint32 ret;

    if ((DIRMNG_DIRID(cdir) == NULL) || (DIRMNG_TYPE(cdir) != GFS_DIR_NAME)) {
        gfs_mngSetErrCode(GFS_ERR_NONAME);
        return NULL;
    }
    if ((fid < 0) || (DIRMNG_NFILE(cdir) <= fid)) {
        gfs_mngSetErrCode(GFS_ERR_NEXIST);
        return NULL;
    }
    pdir = GFDR_GetInfoDirName(fid, DIRMNG_DIRNAME(cdir));
    ret = gfs_mngSetErrCode(GFS_ERR_OK);
    if (ret < 0) {
        return NULL;
    }
    return GFS_DIR_FNAME(pdir);
}

// 0x0601B58C
Sint32 GFS_GetDirInfo(Sint32 fid, GfsDirId* dirrec) {
    GfsDirName* pdirn;
    GfsDirId* pdir;
    GfsDirMng* cdir = &MNG_CURDIR(gfs_mng_ptr);

    if ((DIRMNG_DIRID(cdir) == NULL) || (fid < 0) ||
        (fid >= DIRMNG_NFILE(cdir))) {
        return gfs_mngSetErrCode(GFS_ERR_FID);
    }
    if (DIRMNG_TYPE(cdir) == GFS_DIR_NAME) {
        pdirn = GFDR_GetInfoDirName(fid, DIRMNG_DIRNAME(cdir));
        memcpy(dirrec, pdirn, sizeof(GfsDirId));
    } else {
        pdir = GFDR_GetInfoDirId(fid, DIRMNG_DIRID(cdir));
        memcpy(dirrec, pdir, sizeof(GfsDirId));
    }
    return gfs_mngSetErrCode(GFS_ERR_OK);
}

// 0x0601B600
void GFS_Reset(void) {
    GfsHn gfs;
    GftrHn gftr;
    Sint32 i;

    gfs = MNG_FILE(gfs_mng_ptr);
    for (i = 0; i < MNG_OPENMAX(gfs_mng_ptr); i++, gfs++) {
        if (GFS_FILE_USED(gfs) == TRUE) {
            gftr = &GFS_FILE_TRANS(gfs);
            if (GFS_TRN_MODE(gftr) == GFS_TMODE_STM) {
                GFTR_SetTransFunc(gfs, (GfsTransFunc)gfs_aborttrans, gfs);
            }
            GFS_Close(gfs);
        }
    }
}

// 0x0601B674
GfsHn GFS_Open(Sint32 fid) {
    GfsDirId* dirrec;
    GfsHn gfs;
    GfsDirMng* cdir = &MNG_CURDIR(gfs_mng_ptr);
    Sint32 ret;

    if ((DIRMNG_DIRID(cdir) != NULL) &&
        ((fid < 0) || (fid >= DIRMNG_NFILE(cdir)))) {
        gfs_mngSetErrCode(GFS_ERR_FID);
        return NULL;
    }
    gfs = GFS_mngAllocGrp();
    if (gfs == NULL) {
        gfs_mngSetErrCode(GFS_ERR_NOHNDL);
        return NULL;
    }
    if (DIRMNG_DIRID(cdir) == NULL) {
        dirrec = NULL;
    } else if (DIRMNG_TYPE(cdir) == GFS_DIR_ID) {
        dirrec = GFDR_GetInfoDirId(fid, DIRMNG_DIRID(cdir));
    } else {
        dirrec = (GfsDirId*)GFDR_GetInfoDirName(fid, DIRMNG_DIRNAME(cdir));
    }
    gfs = GFS_OpenSub(gfs, dirrec, fid);
    if (gfs == NULL) {
        gfs_mngSetErrCode(GFS_ERR_FID);
    } else {
        ret = gfs_mngSetErrCode(GFS_ERR_OK);
        if (ret < 0) {
            return NULL;
        }
    }
    return gfs;
}

// 0x0601B724
void GFS_Close(GfsHn gfs) {
    if (gfs != NULL) {
        gfs_mngTermAccess(gfs, TRUE);
        gfs_closeSub(gfs);
    }
    gfs_mngSetErrCode(GFS_ERR_OK);
}

// 0x0601B75C
Sint32 GFS_Seek(GfsHn gfs, Sint32 ofs, Sint32 org) {
    GfsFileFunc* func;
    Sint32 nsct;
    GfsFlow* flow;
    GfsDtsrc* dts;
    Sint32 ret;

    if (gfs == NULL) {
        return gfs_mngSetErrCode(GFS_ERR_HNDL);
    }
    flow = &GFS_FILE_FLOW(gfs);
    dts = &GFS_FLW_DTSRC(flow);
    func = &MNG_FUNCTBL(gfs_mng_ptr, GFS_DTS_FTYPE(dts));
    GFS_GetFileSize(gfs, NULL, &nsct, NULL);
    if (org == GFS_SEEK_CUR) {
        ofs += (FUNC_TELL(func))(flow);
    } else if (org == GFS_SEEK_END) {
        ofs = nsct + ofs;
    } else if (org != GFS_SEEK_SET) {
        return gfs_mngSetErrCode(GFS_ERR_ORG);
    }
    if (ofs < 0) {
        return gfs_mngSetErrCode(GFS_ERR_SEEK);
    }
    if (ofs > nsct) {
        return gfs_mngSetErrCode(GFS_ERR_SEEK);
    }
    ofs = (FUNC_SEEK(func))(flow, ofs);
    ret = gfs_mngSetErrCode(GFS_ERR_OK);
    if (ret < 0) {
        return ret;
    }
    return ofs;
}

// 0x0601B810
Sint32 GFS_Tell(GfsHn gfs) {
    GfsFileFunc* func;
    Sint32 ofs;
    GfsFlow* flow;
    GfsDtsrc* dts;
    Sint32 ret;

    if (gfs == NULL) {
        return gfs_mngSetErrCode(GFS_ERR_HNDL);
    }
    flow = &GFS_FILE_FLOW(gfs);
    dts = &GFS_FLW_DTSRC(flow);
    func = &MNG_FUNCTBL(gfs_mng_ptr, GFS_DTS_FTYPE(dts));
    ofs = (FUNC_TELL(func))(flow);
    ret = gfs_mngSetErrCode(GFS_ERR_OK);
    if (ret < 0) {
        return ret;
    }
    return ofs;
}

// 0x0601B860
Bool GFS_IsEof(GfsHn gfs) {
    Sint32 pos, nsct;

    if (gfs == NULL) {
        return gfs_mngSetErrCode(GFS_ERR_HNDL);
    }
    pos = GFS_Tell(gfs);
    GFS_GetFileSize(gfs, NULL, &nsct, NULL);
    gfs_mngSetErrCode(GFS_ERR_OK);
    return (pos >= nsct) ? TRUE : FALSE;
}

// 0x0601B8B4
Sint32 GFS_ByteToSct(GfsHn gfs, Sint32 nbyte) {
    Sint32 sctsz;
    Sint32 ret;

    if (gfs == NULL) {
        return gfs_mngSetErrCode(GFS_ERR_HNDL);
    }
    GFS_GetFileSize(gfs, &sctsz, NULL, NULL);
    if (sctsz == 0) {
        return 0;
    }
    ret = gfs_mngSetErrCode(GFS_ERR_OK);
    if (ret < 0) {
        return ret;
    }
    return GFS_BYTE_SCT(nbyte, sctsz);
}

// 0x0601B910
void GFS_GetFileSize(GfsHn gfs, Sint32* sctsz, Sint32* nsct, Sint32* lstlen) {
    Sint32 atr;
    GfsFlow* flow;

    if (gfs == NULL) {
        gfs_mngSetErrCode(GFS_ERR_HNDL);
    } else {
        flow = &GFS_FILE_FLOW(gfs);
        gfs_GetFinfo(flow, NULL, NULL, sctsz, nsct, lstlen, NULL, &atr);
        if ((sctsz != NULL) && IS_FORM1(atr) && IS_FORM2(atr)) {
            *sctsz = 0;
        }
    }
    gfs_mngSetErrCode(GFS_ERR_OK);
}

// 0x0601B970
void GFS_GetFileInfo(
    GfsHn gfs, Sint32* fid, Sint32* fn, Sint32* fsize, Sint32* atr) {
    Sint32 nsct;
    Sint32 lstlen;
    GfsFlow* flow;

    if (gfs == NULL) {
        gfs_mngSetErrCode(GFS_ERR_HNDL);
    } else {
        flow = &GFS_FILE_FLOW(gfs);
        gfs_GetFinfo(flow, fid, NULL, NULL, &nsct, &lstlen, fn, atr);
        if (atr != NULL) {
            *atr &= ~GFS_ATR_FTYPE_MASK;
        }
        if (fsize != NULL) {
            *fsize = (nsct - 1) * GFS_MD1_SCTSIZ + lstlen;
        }
    }
    gfs_mngSetErrCode(GFS_ERR_OK);
}

// 0x0601B9E4
Sint32 GFS_GetNumCdbuf(GfsHn gfs) {
    if (gfs == NULL) {
        return gfs_mngSetErrCode(GFS_ERR_HNDL);
    }
    return GFBF_GetNumData(gfs);
}

// 0x0601BA0C
Sint32 GFS_Load(Sint32 fid, Sint32 ofs, void* buf, Sint32 bsize) {
    GfsHn gfs;
    Sint32 nsct;
    Sint32 bsct;
    Sint32 sctsiz1, sctsiz2;
    Sint32 readlen;
    Sint32 ap;
    GfsFinfo* finfo;

    gfs = GFS_Open(fid);
    if (gfs == NULL) {
        return GFS_ERR_CODE(&MNG_ERROR(gfs_mng_ptr));
    }
    ap = GFS_Seek(gfs, ofs, GFS_SEEK_SET);
    if (ap < 0) {
        return gfs_mngSetErrCode(GFS_ERR_OFS);
    }
    finfo = &GFS_FLW_FINFO(&GFS_FILE_FLOW(gfs));
    sctsiz1 = sctsiz2 = GFS_FI_SCTSZ(finfo);
    if (sctsiz1 == 0) {
        sctsiz1 = GFS_FM2_SCTSIZ;
        sctsiz2 = GFS_FM1_SCTSIZ;
    }
    nsct = GFS_FI_NSCT(finfo) - ofs;
    if (bsize == GFS_BUFSIZ_INF) {
        bsize = nsct * sctsiz1;
    }
    bsct = (bsize + sctsiz1 - 1) / sctsiz2;
    nsct = MIN(nsct, bsct);
    readlen = GFS_Fread(gfs, nsct, buf, bsize);
    GFS_Close(gfs);
    if (readlen >= 0) {
        gfs_mngSetErrCode(GFS_ERR_OK);
    }
    return readlen;
}

// 0x0601BAD4
Sint32 GFS_Fread(GfsHn gfs, Sint32 nsct, void* buf, Sint32 bsize) {
    Sint32 err, rpara_old, amode, ndata;

    if (gfs == NULL) {
        return gfs_mngSetErrCode(GFS_ERR_HNDL);
    }
    err = GFS_NwFread(gfs, nsct, buf, bsize);
    if (err != GFS_ERR_OK) {
        return err;
    }
    rpara_old = GFS_SetReadPara(gfs, GFS_RPARA_DFL);
    err = gfs_waitRead(gfs);
    if (err < 0) {
        ndata = gfs_mngSetErrCode(err);
    } else {
        GFS_NwGetStat(gfs, &amode, &ndata);
        err = gfs_mngSetErrCode(GFS_ERR_OK);
        if (err < 0) {
            return err;
        }
    }
    if (rpara_old >= 0) {
        GFS_SetReadPara(gfs, rpara_old);
    }

    return ndata;
}

// 0x0601BB6C
GFS_LOCAL Sint32 gfs_waitRead(GfsHn gfs) {
    Sint32 err, atr, timer;
    GfsDtsrc* dts;
    GfsTrans* trn;

    dts = &GFS_FLW_DTSRC(&GFS_FILE_FLOW(gfs));
    trn = &GFS_FILE_TRANS(gfs);
    GFS_GetFileInfo(gfs, NULL, NULL, NULL, &atr);
    if (atr & GFS_ATR_CDDA) {
        timer = -1;
    } else {
        timer = 0;
    }
    while (1) {
        err = GFS_NwExecOne(gfs);
        if ((err == GFS_SVR_COMPLETED) || (err < 0)) {
            break;
        }
        if ((GFS_TRN_STAT(trn) == GFTR_ST_END) &&
            ((GFS_DTS_FTYPE(dts) != CD_FILE) ||
             (gfcf_fad < GFS_CDR_EFAD(dts)) || (gfcf_stat != GFS_STAT_SEEK))) {
            break;
        }
        if ((GFS_TRN_WP(trn) == 0) && (timer >= 0)) {
            timer++;
            if (timer > FREAD_TMOUT_COUNT) {
                return GFS_ERR_TMOUT;
            }
        }
    }
    return err;
}

// 0x0601BC14
Sint32 GFS_NwFread(GfsHn gfs, Sint32 nsct, void* buf, Sint32 bsize) {
    Sint32 remain, atr;
    Bool add_flag = FALSE;
    GfsFlow* flow;
    GfsFinfo* finfo;
    GfsTrans* trn;

    if (gfs == NULL) {
        return gfs_mngSetErrCode(GFS_ERR_HNDL);
    }
    flow = &GFS_FILE_FLOW(gfs);
    finfo = &GFS_FLW_FINFO(flow);
    trn = &GFS_FILE_TRANS(gfs);
    remain = GFS_FI_NSCT(finfo) - GFS_Tell(gfs);
    remain = MIN(remain, nsct);
    if (remain < 0) {
        return gfs_mngSetErrCode(GFS_ERR_PARA);
    }
    if (GFS_FILE_AMODE(gfs) == GFS_NWSTAT_NOACT) {
        gfs_SetSct(flow, remain);
        add_flag = TRUE;
    }
    GFS_FILE_AMODE(gfs) = GFS_NWSTAT_FREAD;
    GFS_GetFileInfo(gfs, NULL, NULL, NULL, &atr);
    if (atr & GFS_ATR_CDDA) {
        GFTR_SetTransPara(trn, 0);
        GFTR_SetData(trn, NULL, 0, 1);
    } else if ((GFS_TRN_STAT(trn) == GFTR_ST_NOACT) ||
               (GFS_TRN_STAT(trn) == GFTR_ST_END)) {
        GFTR_SetTransPara(trn, remain);
        GFTR_SetData(trn, buf, bsize, 1);
        GFTR_Start(trn);
        add_flag = TRUE;
    }
    if (add_flag == FALSE) {
        return gfs_mngSetErrCode(GFS_ERR_FBUSY);
    }
    gfs_svrAddHndl(gfs);
    GFS_FILE_ASTAT(gfs) = GFS_SVR_BUSY;
    return gfs_mngSetErrCode(GFS_ERR_OK);
}

// 0x0601BD20
Sint32 GFS_NwCdRead(GfsHn gfs, Sint32 nsct) {
    Sint32 remain;
    GfsFlow* flow;
    GfsFinfo* finfo;

    if (gfs == NULL) {
        return gfs_mngSetErrCode(GFS_ERR_HNDL);
    }
    flow = &GFS_FILE_FLOW(gfs);
    finfo = &GFS_FLW_FINFO(flow);
    if (GFS_FILE_AMODE(gfs) != GFS_NWSTAT_NOACT) {
        return gfs_mngSetErrCode(GFS_ERR_FBUSY);
    }
    remain = GFS_FI_NSCT(finfo) - GFS_Tell(gfs);
    remain = MIN(remain, nsct);
    gfs_SetSct(flow, remain);
    GFS_FILE_AMODE(gfs) = GFS_NWSTAT_CDREAD;
    GFS_FILE_ASTAT(gfs) = GFS_SVR_BUSY;
    gfs_svrAddHndl(gfs);
    return gfs_mngSetErrCode(GFS_ERR_OK);
}

// 0x0601BD94
Bool GFS_NwIsComplete(GfsHn gfs) {
    Sint32 ret;

    if (gfs == NULL) {
        gfs_mngSetErrCode(GFS_ERR_HNDL);
        return TRUE;
    }

    ret = gfs_mngSetErrCode(GFS_ERR_OK);
    if (ret < 0) {
        return TRUE;
    }
    return (GFS_FILE_ASTAT(gfs) == GFS_SVR_COMPLETED) ? TRUE : FALSE;
}

// 0x0601BDD0
Sint32 GFS_NwStop(GfsHn gfs) {
    Sint32 ap, ec;
    Bool wait_pause;

    if (gfs == NULL) {
        return gfs_mngSetErrCode(GFS_ERR_HNDL);
    }
    GFS_FILE_AMODE(gfs) = GFS_NWSTAT_NOACT;
    GFS_FILE_ASTAT(gfs) = GFS_SVR_COMPLETED;
    gfs_svrRemoveHndl(gfs);
    if (gfs_getGmode(gfs) == GFS_GMODE_ERASE) {
        wait_pause = FALSE;
    } else {
        wait_pause = TRUE;
    }
    gfs_mngTermAccess(gfs, wait_pause);
    ap = GFS_Tell(gfs);
    ec = gfs_mngSetErrCode(GFS_ERR_OK);
    if (ec < 0) {
        return ec;
    }
    return ap;
}

// 0x0601BE3C
void GFS_NwGetStat(GfsHn gfs, Sint32* amode, Sint32* ndata) {
    GfsTrans* trn;
    Sint32 atr;

    if (gfs == NULL) {
        gfs_mngSetErrCode(GFS_ERR_HNDL);
    } else {
        trn = &GFS_FILE_TRANS(gfs);
        *amode = GFS_FILE_AMODE(gfs);
        GFS_GetFileInfo(gfs, NULL, NULL, NULL, &atr);
        if (atr & GFS_ATR_CDDA) {
            *ndata = 0;
        } else if (GFS_FILE_AMODE(gfs) == GFS_NWSTAT_CDREAD) {
            *ndata = GFBF_GetNumData(gfs);
        } else {
            *ndata = GFS_TRN_WP(trn);
        }
    }
    gfs_mngSetErrCode(GFS_ERR_OK);
}

// 0x0601BEB8
GFS_LOCAL Sint32 gfs_recovRdErr(GfsHn gfs) {
    Sint32 fstat;
    GfsDtsrc* dtsrc;
    GfsFlow* flow;

    flow = &GFS_FILE_FLOW(gfs);
    dtsrc = &GFS_FLW_DTSRC(flow);
    if (GFS_DTS_FTYPE(dtsrc) == CD_FILE) {
        fstat = GFCF_Recover(flow);
        if (fstat == GFS_FIN_PLAY) {
            GFS_FILE_ASTAT(gfs) = GFS_SVR_BUSY;
        }
    }
    return GFS_FILE_ASTAT(gfs);
}

// 0x0601BEE8
Sint32 GFS_NwExecOne(GfsHn gfs) {
    Sint32 tstat, ec;
    Bool flag;

    if (gfs == NULL) {
        return gfs_mngSetErrCode(GFS_ERR_HNDL);
    }
    if (GFS_FILE_ASTAT(gfs) != GFS_SVR_COMPLETED) {
        if (gfs_use_scudma == TRUE) {
            GFTR_ExecSvr(gfs, &flag);
            if (gfs_use_scudma == TRUE) {
                return GFS_FILE_ASTAT(gfs);
            }
        }
        if (GFS_FILE_ASTAT(gfs) == GFS_ERR_CDRD) {
            ec = gfs_recovRdErr(gfs);
            return ec;
        }
        ec = gfs_flowIn(gfs);
        if (ec < 0) {
            return ec;
        }
        if (GFS_FLW_STAT(&GFS_FILE_FLOW(gfs)) != GFS_FIN_NOACT) {
            tstat = gfs_transData(gfs);
            if (tstat == GFTR_ST_END) {
                ec = gfs_flowIn(gfs);
                if (ec < 0) {
                    return ec;
                }
                if (gfs_isTaskDone(gfs)) {
                    GFS_FILE_AMODE(gfs) = GFS_NWSTAT_NOACT;
                    GFS_FILE_ASTAT(gfs) = GFS_SVR_COMPLETED;
                    gfs_svrRemoveHndl(gfs);
                }
            }
        }
    }
    ec = gfs_mngSetErrCode(GFS_ERR_OK);
    if (ec < 0) {
        return ec;
    }
    return GFS_FILE_ASTAT(gfs);
}

// 0x0601BFA8
Sint32 GFS_NwExecServer(GfsHn* now_gfs) {
    GfsSvr* svr;
    Sint32 i, stat = GFS_SVR_COMPLETED;

    svr = &MNG_SVR(gfs_mng_ptr);
    if (SVR_NFILE(svr) == 0) {
        *now_gfs = NULL;
    } else {
        for (i = 0; i < SVR_NFILE(svr); ++i) {
            stat = GFS_NwExecOne(SVR_ACFILE(svr, i));
            if (stat < 0) {
                break;
            }
            if (stat == GFS_SVR_COMPLETED) {
                --i;
            }
        }
        *now_gfs = SVR_ACFILE(svr, 0);
        if ((stat == GFS_ERR_PUINUSE) && (i > 0)) {
            stat = GFS_SVR_BUSY;
        }
    }
    return stat;
}

// 0x0601C01C
Sint32 GFS_SetGmode(GfsHn gfs, Sint32 gmode) {
    Sint32 old_mode, atr;
    GfsFlow* flow;
    GfsDtsrc* dtsrc;
    Sint32 ret;

    if (gfs == NULL) {
        return gfs_mngSetErrCode(GFS_ERR_HNDL);
    }
    GFS_GetFileInfo(gfs, NULL, NULL, NULL, &atr);
    if (atr & GFS_ATR_CDDA) {
        return GFS_ERR_PARA;
    }
    flow = &GFS_FILE_FLOW(gfs);
    dtsrc = &GFS_FLW_DTSRC(flow);
    old_mode = GFS_FLW_GMODE(flow);
    GFS_FLW_GMODE(flow) = gmode;
    ret = gfs_mngSetErrCode(GFS_ERR_OK);
    if (ret < 0) {
        return ret;
    }
    return old_mode;
}

// 0x0601C080
Sint32 GFS_SetTmode(GfsHn gfs, Sint32 tmode) {
    GfsFlow* flow;
    GfsDtsrc* dtsrc;
    GfsTrans* trans;
    Sint32 old_mode, atr;
    Sint32 ret;

    if (gfs == NULL) {
        return gfs_mngSetErrCode(GFS_ERR_HNDL);
    }
    GFS_GetFileInfo(gfs, NULL, NULL, NULL, &atr);
    if (atr & GFS_ATR_CDDA) {
        return GFS_ERR_PARA;
    }
    flow = &GFS_FILE_FLOW(gfs);
    dtsrc = &GFS_FLW_DTSRC(flow);
    trans = &GFS_FILE_TRANS(gfs);
    old_mode = GFTR_SetMode(trans, tmode);
    ret = gfs_mngSetErrCode(GFS_ERR_OK);
    if (ret < 0) {
        return ret;
    }
    return old_mode;
}

// 0x0601C0EC
Sint32 GFS_SetReadPara(GfsHn gfs, Sint32 nsct) {
    GfsFlow* flow;
    Sint32 old_para, atr;
    Sint32 ret;

    if (gfs == NULL) {
        return gfs_mngSetErrCode(GFS_ERR_HNDL);
    }
    GFS_GetFileInfo(gfs, NULL, NULL, NULL, &atr);
    if (atr & GFS_ATR_CDDA) {
        return GFS_ERR_PARA;
    }
    flow = &GFS_FILE_FLOW(gfs);
    old_para = GFS_FLW_SCTMAX(flow);
    GFS_FLW_SCTMAX(flow) = nsct;
    ret = gfs_mngSetErrCode(GFS_ERR_OK);
    if (ret < 0) {
        return ret;
    }
    return old_para;
}

// 0x0601C150
Sint32 GFS_SetTransPara(GfsHn gfs, Sint32 tsize) {
    Sint32 old_para, atr;
    Sint32 ret;

    if (gfs == NULL) {
        return gfs_mngSetErrCode(GFS_ERR_HNDL);
    }
    GFS_GetFileInfo(gfs, NULL, NULL, NULL, &atr);
    if (atr & GFS_ATR_CDDA) {
        return GFS_ERR_PARA;
    }
    old_para = GFTR_SetTransMax(&GFS_FILE_TRANS(gfs), tsize);
    ret = gfs_mngSetErrCode(GFS_ERR_OK);
    if (ret < 0) {
        return ret;
    }
    return old_para;
}

// 0x0601C1BC
void GFS_SetTrFunc(GfsHn gfs, GfsTrFunc func) {
    if (gfs == NULL) {
        gfs_mngSetErrCode(GFS_ERR_HNDL);
        return;
    }
    GFTR_SetData(&(GFS_FILE_TRANS(gfs)), NULL, GFS_LONG_MAX / GFS_MD1_SCTSIZ,
                 GFS_MD1_SCTSIZ);
    GFTR_SetMode(&(GFS_FILE_TRANS(gfs)), GFS_TMODE_STM);
    GFTR_SetTransFunc(gfs, (GfsTransFunc)func, gfs);
}

// 0x0601C220
Uint32* GFS_StartTrans(GfsHn gfs, Sint32* dadr) {
    GfsFlow* flow;
    GfsDtsrc* dtsrc;
    GfdpHn dpk;

    if (gfs == NULL) {
        gfs_mngSetErrCode(GFS_ERR_HNDL);
        return NULL;
    }
    flow = &GFS_FILE_FLOW(gfs);
    dtsrc = &GFS_FLW_DTSRC(flow);
    dpk = GFS_TRN_DPS(&(GFS_FILE_TRANS(gfs)));
    if (GFS_DTS_FTYPE(dtsrc) == CD_FILE) {
        GFCB_GetSctData(dpk, dtsrc);
    }
    *dadr = GFDP_ADLT(dpk);
    return GFDP_DATA(dpk);
}

// 0x0601C26C
Sint32 GFS_CdMovePickup(GfsHn gfs) {
    Sint32 ap, err;
    GfsFlow* flow;
    GfsDtsrc* dtsrc;

    if (gfs == NULL) {
        return gfs_mngSetErrCode(GFS_ERR_HNDL);
    }
    flow = &GFS_FILE_FLOW(gfs);
    dtsrc = &GFS_FLW_DTSRC(flow);
    if (GFS_DTS_FTYPE(dtsrc) == CD_FILE) {
        ap = GFS_Tell(gfs);
        err = GFCF_MovePickup(flow, ap);
        if (err != GFS_ERR_OK) {
            return gfs_mngSetErrCode(err);
        }
        MNG_PICKUP(gfs_mng_ptr) = gfs;
    }
    return gfs_mngSetErrCode(GFS_ERR_OK);
}

// 0x0601C2D8
void GFS_SetErrFunc(GfsErrFunc func, void* obj) {
    GFS_ERR_FUNC(&MNG_ERROR(gfs_mng_ptr)) = func;
    GFS_ERR_OBJ(&MNG_ERROR(gfs_mng_ptr)) = obj;
    gfs_mngSetErrCode(GFS_ERR_OK);
}

// 0x0601C308
void GFS_GetErrStat(GfsErrStat* stat) { *stat = MNG_ERROR(gfs_mng_ptr); }

// 0x0601C32C
Sint32 GFS_ConvTno(Sint32 logtno) {
    if (GFS_IS_DDS() == TRUE) {
        logtno += GFS_DDS_TNO();
    }
    return logtno;
}

// 0x0601C354
GFS_LOCAL Sint32 gfs_chgRoot(GfsDirTbl* dirtbl) {
    Sint32 ndir;
    Sint32 fid;
    GfsDirMng* mng;

    if (GFS_IS_DDS() == TRUE) {
        if (dirtbl != NULL) {
            GFCD_SetCdbfs(TRUE);
        }
        ndir = GFDR_ChgRoot();
        if (ndir < 0) {
            return gfs_mngSetErrCode(GFS_ERR_CDBFS);
        }
        mng = &MNG_CURDIR(gfs_mng_ptr);
        DIRMNG_DIRID(mng) = NULL;
        DIRMNG_NDIR(mng) = DIRMNG_NFILE(mng) = 0;
        GFS_SetDir(NULL);
        if (dirtbl != NULL) {
            GFCD_SetCdbfs(FALSE);
        }
        fid = (Sint32)GFS_DDS_FID();
        ndir = GFS_LoadDir(fid, dirtbl);
    } else {
        if (dirtbl == NULL) {
            ndir = GFDR_ChgRoot();
            if (ndir < 0) {
                return gfs_mngSetErrCode(GFS_ERR_CDBFS);
            }
        } else {
            ndir = gfs_loadRootDir(dirtbl);
            if (ndir <= 0) {
                return gfs_mngSetErrCode(ndir);
            }
        }
    }
    GFS_SetDir(dirtbl);
    gfs_mngSetErrCode(GFS_ERR_OK);
    return ndir;
}

// 0x0601C420
GFS_LOCAL Sint32 gfs_aborttrans(GfsHn gfs, Sint32 nsct) { return 0; }

// 0x0601C42C
GFS_LOCAL void gfs_mngSetupFuncTbl(void) {
    GfsFileFunc* func;

    func = &MNG_FUNCTBL(gfs_mng_ptr, CD_FILE);
    FUNC_FLOWIN(func) = GFCF_FlowInBuf;
    FUNC_STOPIN(func) = GFCF_StopInBuf;
    FUNC_SEEK(func) = GFCF_Seek;
    FUNC_TELL(func) = GFCF_Tell;
    func = &MNG_FUNCTBL(gfs_mng_ptr, MEM_FILE);
    FUNC_FLOWIN(func) = GFMF_FlowInBuf;
    FUNC_STOPIN(func) = GFMF_StopInBuf;
    FUNC_SEEK(func) = GFMF_Seek;
    FUNC_TELL(func) = GFMF_Tell;
    func = &MNG_FUNCTBL(gfs_mng_ptr, SCSI_FILE);
    FUNC_FLOWIN(func) = GFSF_FlowInBuf;
    FUNC_STOPIN(func) = GFSF_StopInBuf;
    FUNC_SEEK(func) = GFSF_Seek;
    FUNC_TELL(func) = GFSF_Tell;
}

// 0x0601C4A8
GFS_LOCAL void gfs_mngInitWork(Sint32 open_max) {
    Sint32 i;
    GfsFile* fp;
    GfdpHn dpk;

    MNG_OPENMAX(gfs_mng_ptr) = open_max;
    gfs_mngSetupFuncTbl();
    SVR_NFILE(&MNG_SVR(gfs_mng_ptr)) = 0;
    MNG_PICKUP(gfs_mng_ptr) = MNG_TRANS(gfs_mng_ptr) = NULL;
    MNG_SFAD(gfs_mng_ptr) = MNG_EFAD(gfs_mng_ptr) = 0;
    GFS_ERR_FUNC(&MNG_ERROR(gfs_mng_ptr)) = NULL;
    MNG_FLAGS(gfs_mng_ptr) = 0;
    fp = MNG_FILE(gfs_mng_ptr);
    for (i = 0; i < open_max; i++) {
        GFS_FILE_USED(fp) = FALSE;
        ++fp;
    }
    dpk = &MNG_SRCPK(gfs_mng_ptr);
    GFDP_DATA(dpk) = NULL;
    GFDP_ADLT(dpk) = GFDP_LEN(dpk) = GFDP_NSCT(dpk) = 0;
    GFDP_USE(dpk) = FALSE;
    dpk = &MNG_DSTPK(gfs_mng_ptr);
    GFDP_DATA(dpk) = NULL;
    GFDP_ADLT(dpk) = GFDP_LEN(dpk) = GFDP_NSCT(dpk) = 0;
    GFDP_USE(dpk) = FALSE;
}

// 0x0601C54C
GFS_LOCAL Sint32 gfs_mngGetNumFile(GfsDirTbl* dirtbl) {
    Sint32 i;
    Sint32 atr;

    for (i = 0; i < GFS_DIRTBL_NDIR(dirtbl); i++) {
        if (GFS_DIRTBL_TYPE(dirtbl) == GFS_DIR_ID) {
            atr = GFDR_GetAtrDirId(i, GFS_DIRTBL_DIRID(dirtbl));
        } else {
            atr = GFDR_GetAtrDirName(i, GFS_DIRTBL_DIRNAME(dirtbl));
        }
        if (IS_ENDTBL(atr)) {
            break;
        }
    }
    if (i > GFS_DIRTBL_NDIR(dirtbl)) {
        return 0;
    }
    return i + 1;
}

// 0x0601C5B0
GfsFile* GFS_mngAllocGrp(void) {
    Sint32 i;
    GfsFile* gfs;

    gfs = MNG_FILE(gfs_mng_ptr);
    for (i = 0; i < MNG_OPENMAX(gfs_mng_ptr); i++) {
        if (GFS_FILE_USED(gfs) == FALSE) {
            break;
        }
        ++gfs;
    }

    if (i == MNG_OPENMAX(gfs_mng_ptr)) {
        gfs = NULL;
    } else {
        GFS_FILE_USED(gfs) = TRUE;
    }
    return gfs;
}

// 0x0601C5F8
GFS_LOCAL void gfs_mngFreeGrp(GfsFile* gfs) { GFS_FILE_USED(gfs) = FALSE; }

// 0x0601C604
GFS_LOCAL void gfs_mngTermAccess(GfsHn gfs, Bool wait_pause) {
    GfsFileFunc* func;
    GfsFlow* flow = &GFS_FILE_FLOW(gfs);
    Sint32 ftype;

    if (MNG_TRANS(gfs_mng_ptr) == gfs) {
        MNG_TRANS(gfs_mng_ptr) = NULL;
        GFTR_Stop(gfs, GFTR_ALLSCT);
    }
    ftype = GFS_DTS_FTYPE(&GFS_FLW_DTSRC(flow));
    if ((MNG_PICKUP(gfs_mng_ptr) == gfs) ||
        ((ftype != CD_FILE) && (MNG_PICKUP(gfs_mng_ptr) == NULL))) {
        MNG_PICKUP(gfs_mng_ptr) = NULL;
        func = &MNG_FUNCTBL(gfs_mng_ptr, ftype);
        (FUNC_STOPIN(func))(flow, wait_pause);
        GFS_FLW_STAT(flow) = GFS_FIN_NOACT;
        GFS_FLW_SCTCNT(flow) = 0;
    }
}

// 0x0601C680
GFS_LOCAL Sint32 gfs_mngSetErrCode(Sint32 code) {
    GfsErrStat* err;

    switch (gfcd_fatal_err) {
    case GFCD_ERR_OK:
        break;
    case GFCD_ERR_FATAL:
        code = GFS_ERR_FATAL;
        break;
    default:
        break;
    }

    err = &MNG_ERROR(gfs_mng_ptr);
    GFS_ERR_CODE(err) = code;
    if ((code != GFS_ERR_OK) && (GFS_ERR_FUNC(err) != NULL)) {
        GFS_ERR_FUNC(err)(GFS_ERR_OBJ(err), code);
    }
    return code;
}

// 0x0601C6C8
GFS_LOCAL Sint32 gfs_svrSearchHndl(GfsHn gfs) {
    Sint32 i;
    GfsSvr* svr;

    svr = &MNG_SVR(gfs_mng_ptr);
    for (i = 0; i < SVR_NFILE(svr); i++) {
        if (gfs == SVR_ACFILE(svr, i)) {
            break;
        }
    }
    if (i == SVR_NFILE(svr)) {
        i = SVR_NOHNDL;
    }
    return i;
}

// 0x0601C708
GFS_LOCAL void gfs_svrAddHndl(GfsHn gfs) {
    GfsSvr* svr;
    Sint32 i;

    i = gfs_svrSearchHndl(gfs);
    if (i == SVR_NOHNDL) {
        svr = &MNG_SVR(gfs_mng_ptr);
        SVR_ACFILE(svr, SVR_NFILE(svr)) = gfs;
        ++SVR_NFILE(svr);
    }
}

// 0x0601C744
GFS_LOCAL void gfs_svrRemoveHndl(GfsHn gfs) {
    GfsSvr* svr;
    Sint32 i, nfile;

    if (gfs == NULL) {
        return;
    }
    i = gfs_svrSearchHndl(gfs);
    if (i != SVR_NOHNDL) {
        svr = &MNG_SVR(gfs_mng_ptr);
        --SVR_NFILE(svr);
        nfile = SVR_NFILE(svr);
        for (; i < nfile; i++) {
            SVR_ACFILE(svr, i) = SVR_ACFILE(svr, i + 1);
        }
        SVR_ACFILE(svr, i) = NULL;
    }
}

// 0x0601C7A0
GfsHn GFS_OpenSub(GfsFile* gfs, GfsDirId* dirrec, Sint32 fid) {
    GftrHn gftr;
    Bool ret;

    if (gfs == NULL) {
        return NULL;
    }
    gftr = GFTR_Setup(&GFS_FILE_TRANS(gfs));
    if (dirrec != NULL) {
        if (IS_MEMFILE(GFS_DIR_ATR(dirrec))) {
            GFMF_Setup(&GFS_FILE_FLOW(gfs), dirrec, fid);
            ret = TRUE;
        } else if (IS_SCSIFILE(GFS_DIR_ATR(dirrec))) {
            ret = GFSF_Setup(&GFS_FILE_FLOW(gfs), dirrec, fid);
        } else {
            ret = GFCF_Setup(&GFS_FILE_FLOW(gfs), dirrec, fid);
        }
    } else {
        ret = GFCF_Setup(&GFS_FILE_FLOW(gfs), dirrec, fid);
    }
    if (ret == FALSE) {
        return NULL;
    }
    GFS_FILE_AMODE(gfs) = GFS_NWSTAT_NOACT;
    GFS_FILE_ASTAT(gfs) = GFS_SVR_COMPLETED;
    return gfs;
}

// 0x0601C840
GFS_LOCAL Sint32 gfs_loadVol(Uint8* buf) {
    GfsDirId dirrec;
    GfsHn gfs;
    Sint32 ret;
    GfsErrStat stat;
    static const Sint8 pvd_id[] = {1, 'C', 'D', '0', '0', '1'};

    GFS_DIR_FAD(&dirrec) = PVD_FAD + GFCD_GetBaseFad();
    GFS_DIR_SIZE(&dirrec) = PVD_BYTSIZ;
    GFS_DIR_FN(&dirrec) = 0;
    GFS_DIR_ATR(&dirrec) = 0;
    GFS_DIR_UNIT(&dirrec) = 0;
    GFS_DIR_GAP(&dirrec) = 0;
    gfs = GFS_mngAllocGrp();
    gfs = GFS_OpenSub(gfs, &dirrec, 0);
    if (gfs == NULL) {
        return GFS_ERR_CDRD;
    }
    ret = GFS_Fread(gfs, PVD_SCTSIZ, buf, PVD_BYTSIZ);
    if (ret != PVD_BYTSIZ) {
        return GFS_ERR_CDRD;
    }
    GFS_GetErrStat(&stat);
    ret = GFS_ERR_CODE(&stat);
    if (ret == GFS_ERR_OK) {
        if (memcmp(buf, pvd_id, sizeof(pvd_id))) {
            ret = GFS_ERR_CDROM;
        }
    }
    GFS_Close(gfs);
    return ret;
}

// 0x0601C908
GFS_LOCAL Sint32 gfs_getRootDir(GfsDirId* dir) {
    Sint32 ret;
    Uint8* rec;
    Sint32 size;

    if (!MNG_CDCON(gfs_mng_ptr)) {
        return GFS_ERR_CDNODISC;
    }
    ret = gfs_loadVol(MNG_SECTBUF(gfs_mng_ptr));
    if (ret != GFS_ERR_OK) {
        return ret;
    }
    rec = MNG_SECTBUF(gfs_mng_ptr) + ROOT_RECPOS;
    memcpy(&GFS_DIR_FAD(dir), DIRREC_EXT(rec), sizeof(Sint32));
    LSN_TO_FAD(GFS_DIR_FAD(dir));
    if (GFS_DIR_FAD(dir) < ROOT_FAD_LOW_LIM) {
        return GFS_ERR_CDROM;
    }
    memcpy(&size, DIRREC_LEN(rec), sizeof(Sint32));
    if (size <= 0) {
        return GFS_ERR_CDROM;
    }
    GFS_DIR_SIZE(dir) =
        (size + GFS_MD1_SCTSIZ - 1) / GFS_MD1_SCTSIZ * GFS_MD1_SCTSIZ;
    GFS_DIR_FN(dir) = 0;
    GFS_DIR_ATR(dir) = GFS_ATR_DIR;
    GFS_DIR_UNIT(dir) = 0;
    GFS_DIR_GAP(dir) = 0;
    return GFS_ERR_OK;
}

// 0x0601C9FC
GFS_LOCAL Sint32 gfs_loadRootDir(GfsDirTbl* dirtbl) {
    GfsHn gfs;
    Sint32 ndir, ret;
    GfsDirId dir;

    ret = gfs_getRootDir(&dir);
    if (ret != GFS_ERR_OK) {
        gfs = NULL;
    } else {
        gfs = GFS_mngAllocGrp();
        gfs = GFS_OpenSub(gfs, &dir, 0);
    }
    if (MNG_CDCON(gfs_mng_ptr) && (gfs == NULL)) {
        return ret;
    }
    ndir = GFDR_SetupDirTbl(gfs, dirtbl, GFS_DIR_SIZE(&dir));
    if (gfs != NULL) {
        GFS_Close(gfs);
    }
    return ndir;
}

// 0x0601CA88
GFS_LOCAL Sint32 gfs_flowIn(GfsHn gfs) {
    Sint32 fstat;
    GfsFileFunc* func;
    GfsFlow* flow;

    flow = &GFS_FILE_FLOW(gfs);
    if (GFS_FLW_STAT(flow) == GFS_FIN_END) {
        return GFS_FLW_STAT(flow);
    }

    if ((MNG_PICKUP(gfs_mng_ptr) != NULL) && (MNG_PICKUP(gfs_mng_ptr) != gfs)) {
        return GFS_FIN_PUINUSE;
    }
    func = &MNG_FUNCTBL(gfs_mng_ptr, GFS_DTS_FTYPE(&GFS_FLW_DTSRC(flow)));
    fstat = (FUNC_FLOWIN(func))(flow);
    if (fstat == GFS_FIN_START) {
        MNG_PICKUP(gfs_mng_ptr) = gfs;
    } else if (fstat == GFS_FIN_END) {
        if (MNG_PICKUP(gfs_mng_ptr) == gfs) {
            MNG_PICKUP(gfs_mng_ptr) = NULL;
            MNG_SFAD(gfs_mng_ptr) = MNG_EFAD(gfs_mng_ptr) = 0;
        }
    }
    GFS_FLW_STAT(flow) = fstat;
    return gfs_convFinStat(gfs, fstat);
}

// 0x0601CB28
GFS_LOCAL Sint32 gfs_transData(GfsHn gfs) {
    Sint32 stat, atr, room;
    Bool flag;

    if ((MNG_TRANS(gfs_mng_ptr) != gfs) && (MNG_TRANS(gfs_mng_ptr) != NULL)) {
        return GFS_SVR_BUSY;
    }
    GFS_GetFileInfo(gfs, NULL, NULL, NULL, &atr);
    if (atr & GFS_ATR_CDDA) {
        return GFTR_ST_END;
    }
    room = GFTR_GetLenRoom(&GFS_FILE_TRANS(gfs));
    if (room == 0) {
        stat = GFTR_Idle(gfs);
    } else {
        stat = GFTR_Exec(gfs, &flag);
    }
    if (stat == GFTR_ST_END) {
        if (MNG_TRANS(gfs_mng_ptr) == gfs) {
            MNG_TRANS(gfs_mng_ptr) = NULL;
        }
    } else if (MNG_TRANS(gfs_mng_ptr) == NULL) {
        MNG_TRANS(gfs_mng_ptr) = gfs;
    }
    return stat;
}

// 0x0601CBD4
Sint32 GFS_GetFad(Sint32 fid, Sint32 ofs) {
    GfsDirId dir;
    Sint32 unit;
    Sint32 ret;

    ret = GFS_GetDirInfo(fid, &dir);
    if (ret < 0) {
        return ret;
    }
    unit = GFS_DIR_UNIT(&dir);
    if (unit == 0) {
        return GFS_DIR_FAD(&dir) + ofs;
    } else {
        return GFS_DIR_FAD(&dir) + (ofs / unit * (unit + GFS_DIR_GAP(&dir)));
    }
}

// 0x0601CC2C
GFS_LOCAL void gfs_SetSct(GfsFlow* flow, Sint32 sct) {
    GfsDtsrc* dtsrc = &GFS_FLW_DTSRC(flow);

    GFS_FLW_STAT(flow) = GFS_FIN_NOACT;
    if (GFS_DTS_FTYPE(dtsrc) == CD_FILE) {
        GFCF_SetSct(flow, sct);
    } else {
        GFS_FLW_SCT(flow) = sct;
        GFS_FLW_SCTCNT(flow) = 0;
    }
}

// 0x0601CC60
void gfs_GetFinfo(GfsFlow* flow, Sint32* fid, Sint32* fad, Sint32* sctsiz,
                  Sint32* nsct, Sint32* lastsiz, Sint32* fno, Sint32* atr) {
    GfsFinfo* finfo;

    GFCF_GetFileInfo(flow, fid, fad, sctsiz, nsct, NULL, fno, atr);
    if (lastsiz != NULL) {
        finfo = &GFS_FLW_FINFO(flow);
        *lastsiz = GFS_FI_SCTSZ(finfo) - GFS_FI_LSTRM(finfo);
    }
}

// 0x0601CCA0
GFS_LOCAL void gfs_closeSub(GfsHn gfs) {
    GfsFlow* flow;
    GfsDtsrc* dts;

    if (gfs == NULL) {
        return;
    }
    flow = &GFS_FILE_FLOW(gfs);
    dts = &GFS_FLW_DTSRC(flow);
    gfs_svrRemoveHndl(gfs);
    gfs_mngFreeGrp(gfs);
    if (GFS_DTS_FTYPE(dts) == CD_FILE) {
        GFCB_Close(dts);
    } else if (GFS_DTS_FTYPE(dts) == SCSI_FILE) {
        GFSF_Close(dts);
    }
}

// 0x0601CCF0
GFS_LOCAL Sint32 gfs_getGmode(GfsHn gfs) {
    GfsFlow* flow = &GFS_FILE_FLOW(gfs);

    return GFS_FLW_GMODE(flow);
}

// 0x0601CCFC
GFS_LOCAL Bool gfs_isTaskDone(GfsHn gfs) {
    Sint32 atr;
    GfsFlow* flow = &GFS_FILE_FLOW(gfs);

    GFS_GetFileInfo(gfs, NULL, NULL, NULL, &atr);
    if ((GFS_FLW_STAT(flow) == GFS_FIN_END) &&
        ((GFBF_GetNumData(gfs) == 0) || (atr & GFS_ATR_CDDA))) {
        return TRUE;
    }
    return FALSE;
}

// 0x0601CD50
GFS_LOCAL Sint32 gfs_convFinStat(GfsHn gfs, Sint32 fstat) {
    switch (fstat) {
    case GFS_FIN_FATAL:
        GFS_FILE_ASTAT(gfs) = GFS_ERR_FATAL;
        return gfs_mngSetErrCode(GFS_ERR_FATAL);
    case GFS_FIN_ERROR:
        GFS_FILE_ASTAT(gfs) = GFS_ERR_CDRD;
        return gfs_mngSetErrCode(GFS_ERR_CDRD);
    case GFS_FIN_OPEN:
        GFS_FILE_ASTAT(gfs) = GFS_ERR_CDOPEN;
        return gfs_mngSetErrCode(GFS_ERR_CDOPEN);
    case GFS_FIN_NODISC:
        GFS_FILE_ASTAT(gfs) = GFS_ERR_CDNODISC;
        return gfs_mngSetErrCode(GFS_ERR_CDNODISC);
    case GFS_FIN_PUINUSE:
        GFS_FILE_ASTAT(gfs) = GFS_ERR_PUINUSE;
        return gfs_mngSetErrCode(GFS_ERR_PUINUSE);
    case GFS_FIN_PAUSE:
        if (gfs_getGmode(gfs) == GFS_GMODE_RESIDENT) {
            GFS_FILE_ASTAT(gfs) = GFS_ERR_BFUL;
            return gfs_mngSetErrCode(GFS_ERR_BFUL);
        }
        break;
    default:
        GFS_FILE_ASTAT(gfs) = GFS_SVR_BUSY;
        break;
    }
    return GFS_ERR_OK;
}
