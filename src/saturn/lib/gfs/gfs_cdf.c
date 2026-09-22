#include "../../sattypes.h"
#include "../../inc_asm.h"

#include "gfs.h"
#include "gfs_def.h"
#include "gfs_cdf.h"
#include "gfs_cdb.h"
#include "gfs_cdc.h"

GFS_LOCAL Sint32 gfcf_getSctSize(Sint32 atr);
GFS_LOCAL Bool gfcf_isCdOk(GfsFlow *flow, Sint32 stat, Sint32 *err);
GFS_LOCAL Bool gfcf_getPlayRange(GfsFlow *flow, Sint32 *nsct, Sint32 *fstat);

// 0x0601CDC0
Sint32 GFCF_Init(Bool use_cdbfs) {
    Sint32 ret;

    MNG_FLAGS(gfs_mng_ptr) &= ~MNG_CDCON_MSK;
    ret = GFCD_Init(&MNG_CDBMNG(gfs_mng_ptr), use_cdbfs);
    if (ret == GFCD_ERR_OK) {
        MNG_FLAGS(gfs_mng_ptr) |= MNG_CDCON_MSK;
    }
    switch (ret) {
    case GFCD_ERR_OK:
        return GFS_ERR_OK;
    case GFCD_ERR_OPEN:
        return GFS_ERR_CDOPEN;
    case GFCD_ERR_NODISC:
        return GFS_ERR_CDNODISC;
    case GFCD_ERR_CDROM:
        return GFS_ERR_CDROM;
    case GFCD_ERR_FATAL:
        return GFS_ERR_FATAL;
    default:
        return GFS_ERR_CDRD;
    }
}

// 0x0601CE60
Bool GFCF_Setup(GfsFlow *flow, GfsDirId *dirrec, Sint32 fid) {
    Sint32      fsize;
    GfsFinfo    *finfo = &GFS_FLW_FINFO(flow);

    if (dirrec == NULL) {
        GFS_FI_FID(finfo) = fid;
        if (GFCD_GetFileInfo(fid, &GFS_FI_FINFO(finfo)) != GFCD_ERR_OK) {
            return FALSE;
        }
        fsize = GFS_FI_SIZE(finfo);
    } else {
        fsize = GFS_DIR_SIZE(dirrec);
        if ((GFS_DIR_ATR(dirrec) & GFS_ATR_DIR) != 0) {
            fsize = (fsize + GFS_MD1_SCTSIZ - 1) / 
                                         GFS_MD1_SCTSIZ * GFS_MD1_SCTSIZ;
        }
        GFS_FI_FID(finfo) = fid;
        GFS_FI_FAD(finfo) = GFS_DIR_FAD(dirrec);
        GFS_FI_SIZE(finfo) = fsize;
        GFS_FI_UNIT(finfo) = GFS_DIR_UNIT(dirrec);
        GFS_FI_GAP(finfo) = GFS_DIR_GAP(dirrec);
        GFS_FI_FN(finfo) = GFS_DIR_FN(dirrec);
        GFS_FI_ATR(finfo) = GFS_DIR_ATR(dirrec);
    }
    GFS_FI_SCTSZ(finfo) = gfcf_getSctSize(GFS_DIR_ATR(dirrec));
    GFS_FI_NSCT(finfo) = GFS_BYTE_SCT(fsize, GFS_MD1_SCTSIZ);
    if (GFS_FI_SCTSZ(finfo) == 0) {
        GFS_FI_LSTRM(finfo) = 0;
    } else {
        GFS_FI_LSTRM(finfo) = GFS_LAST_ROOM(fsize, GFS_MD1_SCTSIZ);
    }
    if (GFCB_Setup(flow) == FALSE) {
        return FALSE;
    }
    GFS_FLW_GMODE(flow) = GFS_GMODE_ERASE;
    GFS_FLW_STAT(flow) = GFS_FIN_NOACT;
    GFS_FLW_SCT(flow) = GFS_FLW_SCTCNT(flow) = 0;
    GFS_FLW_SCTMAX(flow) = GFS_RPARA_DFL;
    return TRUE;
}

// 0x0601CFA0
void GFCF_SetSct(GfsFlow *flow, Sint32 sct) {
    Sint32      nsct;

    GFS_FLW_SCT(flow) = sct;
    nsct = GFCB_GetLenData(flow, GFS_RPARA_DFL, NULL);
    if (nsct < 0) {
        nsct = 0;
    }
    if (nsct >= sct) {
	    GFS_FLW_SCTCNT(flow) = sct;
	    GFS_FLW_STAT(flow) = GFS_FIN_END;
    } else {
	    GFS_FLW_SCTCNT(flow) = nsct;
	}
}

// 0x0601CFEC
void GFCF_GetFileInfo(GfsFlow *flow, Sint32 *fid, Sint32 *fad, Sint32 *sctsiz,
                      Sint32 *nsct, Sint32 *lastsiz, Sint32 *fno, Sint32 *atr) {
    GfsFinfo    *finfo = &GFS_FLW_FINFO(flow);

    if (fid != NULL) {
        *fid = GFS_FI_FID(finfo);
    }
    if (fad != NULL) {
        *fad = GFS_FI_FAD(finfo);
    }
    if (fno != NULL) {
        *fno = GFS_FI_FN(finfo);
    }
    if (sctsiz != NULL) {
        *sctsiz = GFS_FI_SCTSZ(finfo);
    }
    if (nsct != NULL){
        *nsct = GFS_FI_NSCT(finfo);
    }
    if (atr != NULL) {
        *atr = GFS_FI_ATR(finfo);
    }
    if (lastsiz != NULL) {
        if (IS_FORM1(GFS_FI_ATR(finfo)) && IS_FORM2(GFS_FI_ATR(finfo))) {
            *lastsiz = 0;
        } else {
            *lastsiz = GFS_FI_SCTSZ(finfo) - GFS_FI_LSTRM(finfo);
        }
    }
}

// 0x0601D060
Sint32 GFCF_FlowInBuf(GfsFlow *flow) {
    Sint32      stat, fad, err, nsct;
    CdcPly      pinfo;
    GfsDtsrc    *dts = &GFS_FLW_DTSRC(flow);
    Sint32      hirq;

    stat = GFCF_GetStat(&fad, &hirq);
    gfcf_stat = stat;
    gfcf_fad = fad;
    if (gfcf_isCdOk(flow, stat, &err) == FALSE) {
        return err;
    }
    if (GFCB_IsPuOwner(dts) == FALSE) {
        if (gfcf_getPlayRange(flow, &nsct, &err) == FALSE) {
            return err;
        }
        if (GFCB_GetPickup(dts) == FALSE) {
            return GFS_FIN_ERROR;
        }
        if (GFCB_SetCon(dts) == FALSE) {
            return GFS_FIN_ERROR;
        }
        /* CdPlay�𔭍s���� */
        CDC_PLY_STYPE(&pinfo) = CDC_PTYPE_FAD;
        CDC_PLY_SFAD(&pinfo) = GFS_CDR_SFAD(dts);
        CDC_PLY_ETYPE(&pinfo) = CDC_PTYPE_FAD;
        CDC_PLY_EFAS(&pinfo) = GFS_CDR_EFAD(dts) - CDC_PLY_SFAD(&pinfo);
        CDC_PLY_PMODE(&pinfo) = CDC_PM_DFL;
        err = GFCD_Play(&pinfo, GFS_CDR_PUID(dts));
        if (err != GFCD_ERR_OK) {
            return GFS_FIN_ERROR;
        }
        GFS_FLW_SCTCNT(flow) += nsct;
        MNG_SFAD(gfs_mng_ptr) = CDC_PLY_SFAD(&pinfo);
        MNG_EFAD(gfs_mng_ptr) = GFS_CDR_EFAD(dts);
        return GFS_FIN_START;
    }
    if ((fad >= GFS_CDR_EFAD(dts))&&
        (((hirq & CDC_HIRQ_CSCT) != 0)||(stat == GFS_STAT_NOACT))) {
        GFCB_UngetPickup(dts);
        if ((GFS_FLW_SCT(flow) == GFS_FLW_SCTCNT(flow))&&
            (MNG_EFAD(gfs_mng_ptr) <= fad)&&(stat != GFS_STAT_SEEK)) {
            MNG_SFAD(gfs_mng_ptr) = MNG_EFAD(gfs_mng_ptr);
            return GFS_FIN_END;
        }
        return GFS_FIN_PLAY;
    }
    return GFS_FIN_PLAY;
}

// 0x0601D1B0
void GFCF_StopInBuf(GfsFlow *flow, Bool wait_pause) {
    CdcPos      pos;
    Sint32      fad;
    GfsDtsrc    *dts = &GFS_FLW_DTSRC(flow);

    MNG_SFAD(gfs_mng_ptr) = MNG_EFAD(gfs_mng_ptr) = 0;
    CDC_POS_PTYPE(&pos) = CDC_PTYPE_NOCHG;
    GFCB_MovePickup(dts, &pos);
    if (wait_pause) {
        GFCD_WaitPause();
    }
    GFCB_DeleteAllData(dts);

    if (GFCB_IsPuOwner(dts)) {
        GFCB_UngetPickup(dts);
        GFCF_GetStat(&fad, NULL);
        if (MNG_EFAD(gfs_mng_ptr) <= fad) {
            MNG_SFAD(gfs_mng_ptr) = MNG_EFAD(gfs_mng_ptr);
        }
    }
}

// 0x0601D250
Sint32 GFCF_Recover(GfsFlow *flow) {
    GfsDtsrc    *dts = &GFS_FLW_DTSRC(flow);
    CdcPly      pinfo;
    Sint32      err;

    if (GFCB_IsPuOwner(dts)) {
        /* CdPlay�𔭍s���� */
        CDC_PLY_STYPE(&pinfo) = CDC_PTYPE_NOCHG;
        CDC_PLY_ETYPE(&pinfo) = CDC_PTYPE_NOCHG;
        CDC_PLY_PMODE(&pinfo) = CDC_PM_NOCHG;
        err = GFCD_Play(&pinfo, GFS_CDR_PUID(dts));
        if (err != GFCD_ERR_OK) {
            return GFS_FIN_ERROR;
        }
    } else {
        return GFS_FIN_ERROR;
    }
    return GFS_FIN_PLAY;
}

// 0x0601D29C
Sint32 GFCF_Tell(GfsFlow *flow) {
    return GFCB_Tell(&GFS_FLW_DTSRC(flow));
}

// 0x0601D2B4
Sint32 GFCF_Seek(GfsFlow *flow, Sint32 off) {
    return GFCB_Seek(flow, off, GFS_SEEK_SET);
}

// 0x0601D2CC
Sint32 GFCF_MovePickup(GfsFlow *flow, Sint32 off) {
    Sint32      err;
    CdcPos      pos;
    GfsFinfo    *finfo = &GFS_FLW_FINFO(flow);

    if (GFCF_GetStat(NULL, NULL) != GFS_STAT_NOACT) {
        return GFS_ERR_PUINUSE;
    }
    if (GFCB_GetPickup(&GFS_FLW_DTSRC(flow)) == FALSE) {
        return GFS_ERR_PUINUSE;
    }
    CDC_POS_PTYPE(&pos) = CDC_PTYPE_FAD;
    CDC_POS_FAD(&pos) = GFCF_cnvIntlvOfs(finfo, off) + GFS_FI_FAD(finfo);
    switch (GFCB_MovePickup(&GFS_FLW_DTSRC(flow), &pos)) {
    case GFCD_ERR_OK:
        err = GFS_ERR_OK;
        break;
    case GFCD_ERR_NOTOWNER:
        err = GFS_ERR_PUINUSE;
        break;
    case GFCD_ERR_OPEN:
        err = GFS_ERR_CDOPEN;
        break;
    default:
        err = GFS_ERR_CDRD;
        break;
    }
    GFCB_UngetPickup(&GFS_FLW_DTSRC(flow));
    return err;
}

// 0x0601D36C
Sint32 GFCF_cnvIntlvOfs(GfsFinfo *finfo, Sint32 ofs) {
    if (GFS_FI_UNIT(finfo) == 0) {
        return ofs;
    }
    return (ofs / GFS_FI_UNIT(finfo) *
            (GFS_FI_UNIT(finfo) + GFS_FI_GAP(finfo))) +
                ofs % GFS_FI_UNIT(finfo);
}

// 0x0601D3BC
Sint32 GFCF_GetStat(Sint32 *fad, Sint32 *hirq) {
    CdcStat     stat;
    Sint32      tmp;

    tmp = GFCD_GetStat(&stat);
    if (hirq != NULL) {
        *hirq = tmp;
    }
    if (fad != NULL) {
        *fad = CDC_STAT_FAD(&stat);
    }
    if (gfcd_fatal_err == GFCD_ERR_OK) {
        switch (CDC_GET_STC(&stat)) {
        case CDC_ST_BUSY:
            return GFS_STAT_SEEK;
        case CDC_ST_PAUSE:
        case CDC_ST_STANDBY:
            return GFS_STAT_NOACT;
        case CDC_ST_PLAY:
        case CDC_ST_RETRY:
            return GFS_STAT_READ;
        case CDC_ST_SEEK:
            return GFS_STAT_SEEK;
        case CDC_ST_SCAN:
            return GFS_STAT_READ;
        case CDC_ST_ERROR:
        default:
            break;
        }
    } else if (gfcd_fatal_err == GFCD_ERR_FATAL) {
        return GFS_STAT_FATAL;
    }
    return GFS_STAT_ERROR;
}

// 0x0601D440
GFS_LOCAL Sint32 gfcf_getSctSize(Sint32 atr) {
    Sint32      sctsz;

    if (IS_CDDA(atr)) {
        sctsz = GFS_CDDA_SCTSIZ;
    } else if (IS_FORM2(atr)) {
        if (IS_FORM1(atr)) {
            sctsz = 0;
        } else {
            sctsz = GFS_FM2_SCTSIZ;
        }
    } else if (IS_FORM1(atr)) {
        sctsz = GFS_FM1_SCTSIZ;
    } else {
        sctsz = GFS_MD1_SCTSIZ;
    }
    return sctsz;
}

// 0x0601D478
GFS_LOCAL Bool gfcf_isCdOk(GfsFlow *flow, Sint32 stat,  Sint32 *err) {
    GfsDtsrc    *dts = &GFS_FLW_DTSRC(flow);

    switch (stat) {
    case GFS_STAT_SEEK:
        *err = GFS_FLW_STAT(flow);
        return FALSE;
    case GFS_STAT_READ:
        break;
    case GFS_STAT_NOACT:
        if (GFCD_GetBufSiz() == 0) {
            *err = GFS_FIN_PAUSE;
            return FALSE;
        }
        break;
    case GFS_STAT_OPEN:
        *err = GFS_FIN_OPEN;
        return FALSE;
    case GFS_STAT_NODISC:
        *err = GFS_FIN_NODISC;
        return FALSE;
    case GFS_STAT_FATAL:
        *err = GFS_FIN_FATAL;
        return FALSE;
    default:
        *err = GFS_FIN_ERROR;
        return FALSE;
    }
    if ((GFS_FLW_GMODE(flow) != GFS_GMODE_RESIDENT)&&
        (GFS_FLW_STAT(flow) == GFS_FIN_NOACT)) {
        GFCB_DeleteAllData(dts);
        GFS_FLW_SCTCNT(flow) = 0;
        MNG_SFAD(gfs_mng_ptr) = MNG_EFAD(gfs_mng_ptr) = 0;
    }
    *err = GFS_FIN_START;
    return TRUE;
}

// 0x0601D534
GFS_LOCAL Bool gfcf_getPlayRange(GfsFlow *flow, Sint32 *nsct, Sint32 *fstat) {
    Sint32      ap_fad, bsct;
    GfsFinfo    *finfo = &GFS_FLW_FINFO(flow);
    GfsDtsrc    *dts = &GFS_FLW_DTSRC(flow);

    *nsct = GFS_FLW_SCT(flow) - GFS_FLW_SCTCNT(flow);
    *nsct = MIN(*nsct, GFS_FLW_SCTMAX(flow));
    ap_fad = GFS_FI_FAD(finfo) + GFCF_cnvIntlvOfs(finfo, GFCB_Tell(dts));
    if (GFS_FLW_GMODE(flow) == GFS_GMODE_RESIDENT) {
        bsct = GFCB_GetLenData(flow, GFS_LONG_MAX, NULL);
        if (bsct < 0) {
            bsct = 0;
        }
        if ((bsct > 0)&&(ap_fad < MNG_SFAD(gfs_mng_ptr))) {
            bsct -= MNG_SFAD(gfs_mng_ptr) - ap_fad;
        }
    } else {
        bsct = 0;
    }
    if (bsct >= *nsct) {
        GFS_FLW_SCTCNT(flow) += *nsct;
        if (GFS_FLW_SCT(flow) == GFS_FLW_SCTCNT(flow)) {
            *fstat = GFS_FIN_END;
            MNG_SFAD(gfs_mng_ptr) = MNG_EFAD(gfs_mng_ptr);
        } else {
            *fstat = GFS_FIN_PLAY;
            MNG_SFAD(gfs_mng_ptr) = ap_fad;
        }
        return FALSE;
    }
    *nsct -= bsct;
    GFS_CDR_SFAD(dts) = ap_fad;
    GFS_CDR_EFAD(dts) = GFS_FI_FAD(finfo) +
        GFCF_cnvIntlvOfs(finfo, *nsct + GFCB_Tell(dts) - 1) + 1;
    if ((MNG_SFAD(gfs_mng_ptr) <= GFS_CDR_SFAD(dts))&&
        (GFS_CDR_SFAD(dts) < MNG_EFAD(gfs_mng_ptr))&&
        (MNG_SFAD(gfs_mng_ptr) < GFS_CDR_EFAD(dts))&&
        (GFS_CDR_EFAD(dts) <= MNG_EFAD(gfs_mng_ptr))) {
        MNG_SFAD(gfs_mng_ptr) = GFS_CDR_SFAD(dts);
        *fstat = GFS_FIN_START;
        return FALSE;
    }
    return TRUE;
}