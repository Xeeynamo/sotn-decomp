#include "../../sattypes.h"
#include "../../inc_asm.h"

#include "gfs.h"
#include "gfs_def.h"
#include "gfs_mmc.h"
#include "gfs_dir.h"
#include "gfs_cdc.h"

#include "gfs_scsi.h"

#define SECT_BUF_SIZ 2048

#define MF_OVW 0x01

#define GFDR_CURRENT_DIR_ID 0
#define GFDR_PARENT_DIR_ID 1

#define GFDR_BASE_MAX 8
#define GFDR_EXT_MAX 3

#define GFDR_FILE_UNREAD -1

#define LSN2FAD(lsn) ((lsn) + 150)
#define FAD2LSN(fad) ((fad) - 150)

#define RECORDING_DATE_LEN 7

#define GFS_DIR_DIRREC(rec) ((rec)->dirrec)

#define NEEDS_PADDING(n) ((n + 1) & 1)

typedef struct {
    Uint32 pos;
    Uint32 len;
    Uint8 rsize;
    Uint8 atr;
    Uint8 unitsize;
    Uint8 gapsize;
    Sint8 fname[GFS_FNAME_LEN + 1];
    Uint8 fn;
} XaDirEnt;

#define XA_DIR_RSIZE(dir) ((dir)->rsize)
#define XA_DIR_POS(dir) ((dir)->pos)
#define XA_DIR_LEN(dir) ((dir)->len)
#define XA_DIR_ATR(dir) ((dir)->atr)
#define XA_DIR_USIZE(dir) ((dir)->unitsize)
#define XA_DIR_GSIZE(dir) ((dir)->gapsize)
#define XA_DIR_FNAME(dir) ((dir)->fname)
#define XA_DIR_FN(dir) ((dir)->fn)

#define XA_ATR_DIR 0x80
#define XA_ATR_INTLV 0x20
#define XA_ATR_FORM2 0x10
#define XA_ATR_FORM1 0x08
#define XA_ATR_ERR 0x0080

typedef struct {
    GfsHn gfs;
    Uint8* buf;
    Sint32 rp;
    Sint32 ap;
    Sint32 nsct;
} GfdrFile;

#define GFDR_FILE_GFS(fp) ((fp)->gfs)
#define GFDR_FILE_BUF(fp) ((fp)->buf)
#define GFDR_FILE_RP(fp) ((fp)->rp)
#define GFDR_FILE_AP(fp) ((fp)->ap)
#define GFDR_FILE_NSCT(fp) ((fp)->nsct)

GFS_LOCAL Sint32 gfdr_setupDirIdTbl(GfsHn gfs, GfsDirId* rectbl, Sint32 nrec);
GFS_LOCAL Sint32 gfdr_setupDirNameTbl(
    GfsHn gfs, GfsDirName* rectbl, Sint32 nrec);
GFS_LOCAL void gfdr_open(GfdrFile* fp, GfsHn gfs);
GFS_LOCAL Sint32 gfdr_read(GfdrFile* fp, void* buf, Uint32 size);
GFS_LOCAL Uint8 gfdr_readByte(GfdrFile* fp, Sint32* ec);
GFS_LOCAL Uint16 gfdr_readWord(GfdrFile* fp, Sint32* ec);
GFS_LOCAL Uint16 gfdr_readWordNB(GfdrFile* fp, Sint32* ec);
GFS_LOCAL Uint32 gfdr_readLongNB(GfdrFile* fp, Sint32* ec);
GFS_LOCAL Uint32 gfdr_readLongNM(GfdrFile* fp, Sint32* ec);
GFS_LOCAL Sint32 gfdr_setNextRec(GfdrFile* fp, Sint32* ec);
GFS_LOCAL Sint32 gfdr_readDirEnt(GfdrFile* fp, XaDirEnt* dir);
GFS_LOCAL void gfdr_setDirrecCd(CdcFile* rec, XaDirEnt* dir);
GFS_LOCAL void gfdr_setDirrecMem(CdcFile* rec, Sint32 fid, Sint32 len);
GFS_LOCAL void gfdr_setDirrecScsi(CdcFile* rec, Sint32 fid, Sint32 len);
GFS_LOCAL Bool gfdr_getScsiFinfo(Sint8* fname, Sint32* fid, Sint32* len);
GFS_LOCAL Bool gfdr_findScsiFile(GfsDirId* rec, GfsDirId* recend, Sint32 fid);
GFS_LOCAL GfsDirName* gfdr_findFile(
    GfsDirName* rectbl, Sint32 n_dirent, Sint8* fname);
GFS_LOCAL void gfdr_clearMemRsv(Sint32 n_memfile);

// 0x0601DA34
Sint32 GFDR_SetupDirTbl(GfsHn gfs, GfsDirTbl* dirtbl, Sint32 nsct) {
    Sint32 ndir;

    if (GFS_DIRTBL_TYPE(dirtbl) == GFS_DIR_ID) {
        ndir = gfdr_setupDirIdTbl(
            gfs, GFS_DIRTBL_DIRID(dirtbl), GFS_DIRTBL_NDIR(dirtbl));
    } else {
        ndir = gfdr_setupDirNameTbl(
            gfs, GFS_DIRTBL_DIRNAME(dirtbl), GFS_DIRTBL_NDIR(dirtbl));
    }
    return ndir;
}

// 0x0601DA64
Sint32 GFDR_NameToId(GfsDirName* rectbl, Sint8* fname, Sint32 max) {
    Sint32 i;

    for (i = 0; i < max; ++i, ++rectbl) {
        if (XSTRNCMP(fname, GFS_DIR_FNAME(rectbl), GFS_FNAME_LEN) == 0) {
            return i;
        }
        if (GFS_DIR_ATR(rectbl) & GFS_ATR_END_TBL) {
            break;
        }
    }
    return -1;
}

// 0x0601DAC4
GfsDirId* GFDR_GetInfoDirId(Sint32 fid, GfsDirId* rectbl) {
    return &rectbl[fid];
}

// 0x0601DAD8
GfsDirName* GFDR_GetInfoDirName(Sint32 fid, GfsDirName* rectbl) {
    return &rectbl[fid];
}

// 0x0601DAEC
Sint32 GFDR_GetAtrDirId(Sint32 fid, GfsDirId* rectbl) {
    return GFS_DIR_ATR(&rectbl[fid]);
}

// 0x0601DB04
Sint32 GFDR_GetAtrDirName(Sint32 fid, GfsDirName* rectbl) {
    return GFS_DIR_ATR(&rectbl[fid]);
}

// 0x0601DB1C
Sint32 GFDR_ChgRoot(void) { return GFDR_ChgDir(CDC_NUL_FID); }

// 0x0601DB34
Sint32 GFDR_ChgDir(Sint32 fid) {
    Sint32 err, ndir;

    GFCD_SetTimer(GFCD_TMOUT_COUNT);
    do {
        err = GFCD_ChgDir(fid, GFCD_SYS_SEL, &ndir);
        if (err == GFCD_ERR_INUSE) {
            return GFS_ERR_CDBFS;
        }
    } while (err != GFCD_ERR_OK);

    err = GFCD_WaitServer();
    if (err == GFCD_SVR_TMOUT) {
        return GFS_ERR_TMOUT;
    } else if (err == GFCD_SVR_ERROR) {
        switch (gfcd_fatal_err) {
        case GFCD_ERR_OPEN:
            return GFS_ERR_CDOPEN;
        case GFCD_ERR_NODISC:
            return GFS_ERR_CDNODISC;
        case GFCD_ERR_FATAL:
        default:
            return GFS_ERR_FATAL;
        }
    } else if (err != GFCD_SVR_COMPLETED) {
        return GFS_ERR_CDRD;
    }
    return ndir;
}

// 0x0601DBC4
GFS_LOCAL Sint32 gfdr_setupDirIdTbl(GfsHn gfs, GfsDirId* rectbl, Sint32 nrec) {
    GfsDirId* r = rectbl;
    Sint32 n_dirent, ec;
    GfdrFile fp;
    XaDirEnt dir_ent;
    Sint32 n_memfile = GFMC_GetNumFile();
    Sint32 i, n_scsifile;
    Uint8* dummy1;
    Sint32 dummy2, len;
    GfsdInfo info;

    for (i = 0; i < n_memfile; ++i) {
        GFMC_SetRsv(i, 0);
    }
    gfdr_open(&fp, gfs);
    for (n_dirent = 0; nrec > 0; ++r, ++n_dirent, --nrec) {
        ec = gfdr_readDirEnt(&fp, &dir_ent);
        if (ec != GFS_ERR_OK) {
            return ec;
        }
        if (XA_DIR_RSIZE(&dir_ent) == 0) {
            break;
        }
        for (i = 0; i < n_memfile; ++i) {
            if (XSTRNCPY(XA_DIR_FNAME(&dir_ent), GFMC_GetFname(i),
                         GFS_FNAME_LEN) == 0) {
                GFMC_GetFileInfo(i, (void**)&dummy1, &len, &dummy2);
                gfdr_setDirrecMem(&GFS_DIR_DIRREC(r), i, len);
                break;
            }
        }
        if (i == n_memfile) {
            if (gfdr_getScsiFinfo(XA_DIR_FNAME(&dir_ent), &i, &len) == TRUE) {
                gfdr_setDirrecScsi(&GFS_DIR_DIRREC(r), i, len);
            } else {
                gfdr_setDirrecCd(&GFS_DIR_DIRREC(r), &dir_ent);
            }
        }
    }
    for (i = 0; (i < n_memfile) && (nrec > 0); ++i) {
        if (GFMC_GetRsv(i) != MF_OVW) {
            --nrec;
            GFMC_GetFileInfo(i, (void**)&dummy1, &len, &dummy2);
            gfdr_setDirrecMem(&GFS_DIR_DIRREC(r), i, len);
            ++r;
            ++n_dirent;
        }
    }
    gfdr_clearMemRsv(n_memfile);
    if (MNG_SCSICON(gfs_mng_ptr)) {
        GFSD_GetFileNum(&n_scsifile);
        for (i = 0; (i < n_scsifile) && (nrec > 0); ++i) {
            if (gfdr_findScsiFile(rectbl, r, i) != TRUE) {
                GFSD_GetFileInfo(i, &info);
                gfdr_setDirrecScsi(
                    &GFS_DIR_DIRREC(r), i, GFSD_INFO_LENGTH(&info));
            }
            ++r;
            ++n_dirent;
        }
    }
    --r;
    GFS_DIR_ATR(r) |= GFS_ATR_END_TBL;
    return n_dirent;
}

// 0x0601DE38
GFS_LOCAL Sint32 gfdr_setupDirNameTbl(
    GfsHn gfs, GfsDirName* rectbl, Sint32 nrec) {
    GfsDirName* r = rectbl;
    Sint32 n_dirent, ec;
    GfdrFile fp;
    XaDirEnt dir_ent;
    Sint32 n_memfile;
    Uint8* dummy1;
    Sint32 dummy2, len, i, n_scsifile, n_new_scsi, n_new_memf;
    GfsdInfo info;

    gfdr_open(&fp, gfs);
    for (n_dirent = 0; nrec > 0; ++r, ++n_dirent, --nrec) {
        ec = gfdr_readDirEnt(&fp, &dir_ent);
        if (ec != GFS_ERR_OK) {
            return ec;
        }
        if (XA_DIR_RSIZE(&dir_ent) == 0) {
            break;
        }
        if ((n_dirent > 2) &&
            (XSTRNCMP(GFS_DIR_FNAME(&r[-1]), XA_DIR_FNAME(&dir_ent),
                      GFS_FNAME_LEN) == 0)) {
            continue;
        }
        gfdr_setDirrecCd(&GFS_DIR_DIRREC(r), &dir_ent);
        XSTRNCPY(GFS_DIR_FNAME(r), XA_DIR_FNAME(&dir_ent), GFS_FNAME_LEN);
    }
    if (MNG_SCSICON(gfs_mng_ptr)) {
        GFSD_GetFileNum(&n_scsifile);
        n_new_scsi = 0;
        for (i = 0; (i < n_scsifile) && (n_new_scsi < nrec); ++i) {
            GFSD_GetFileInfo(i, &info);
            r = gfdr_findFile(rectbl, n_dirent, GFSD_INFO_FNAME(&info));
            if (r == NULL) {
                r = &rectbl[n_dirent + n_new_scsi];
                gfdr_setDirrecScsi(
                    &GFS_DIR_DIRREC(r), i, GFSD_INFO_LENGTH(&info));
                XSTRNCPY(
                    GFS_DIR_FNAME(r), GFSD_INFO_FNAME(&info), GFS_FNAME_LEN);
                ++n_new_scsi;
            } else {
                gfdr_setDirrecScsi(
                    &GFS_DIR_DIRREC(r), i, GFSD_INFO_LENGTH(&info));
            }
        }
        n_dirent += n_new_scsi;
    }
    n_memfile = GFMC_GetNumFile();
    n_new_memf = 0;
    for (i = 0; (i < n_memfile) && (n_new_memf < nrec); ++i) {
        r = gfdr_findFile(rectbl, n_dirent, GFMC_GetFname(i));
        GFMC_GetFileInfo(i, (void**)&dummy1, &len, &dummy2);
        if (r == NULL) {
            r = &rectbl[n_dirent + n_new_memf];
            gfdr_setDirrecMem(&GFS_DIR_DIRREC(r), i, len);
            XSTRNCPY(GFS_DIR_FNAME(r), GFMC_GetFname(i), GFS_FNAME_LEN);
            ++n_new_memf;
        } else {
            gfdr_setDirrecMem(&GFS_DIR_DIRREC(r), i, len);
        }
    }
    gfdr_clearMemRsv(n_memfile);
    n_dirent += n_new_memf;
    r = &rectbl[n_dirent];
    --r;
    GFS_DIR_ATR(r) |= GFS_ATR_END_TBL;
    return n_dirent;
}

// 0x0601E084
GFS_LOCAL void gfdr_open(GfdrFile* fp, GfsHn gfs) {
    GfsFinfo* finfo = &GFS_FLW_FINFO(&GFS_FILE_FLOW(gfs));

    GFDR_FILE_GFS(fp) = gfs;
    GFDR_FILE_BUF(fp) = MNG_SECTBUF(gfs_mng_ptr);
    GFDR_FILE_RP(fp) = GFDR_FILE_UNREAD;
    GFDR_FILE_NSCT(fp) = GFS_FI_NSCT(finfo);
    GFDR_FILE_AP(fp) = 0;
}

// 0x0601E0AC
GFS_LOCAL Sint32 gfdr_read(GfdrFile* fp, void* buf, Uint32 size) {
    Sint32 i, ret;

    if (GFDR_FILE_GFS(fp) == NULL) {
        memset(buf, 0, size);
        return GFS_ERR_OK;
    }
    if ((GFDR_FILE_RP(fp) == GFDR_FILE_UNREAD) ||
        (GFDR_FILE_RP(fp) >= SECT_BUF_SIZ)) {
        ret = GFS_Fread(GFDR_FILE_GFS(fp), 1, GFDR_FILE_BUF(fp), SECT_BUF_SIZ);
        if (ret != SECT_BUF_SIZ) {
            if (ret < GFS_ERR_OK) {
                return ret;
            }
            return GFS_ERR_CDRD;
        }
        GFDR_FILE_RP(fp) = 0;
    }
    i = SECT_BUF_SIZ - GFDR_FILE_RP(fp);
    i = MIN(i, (Sint32)size);
    memcpy(buf, GFDR_FILE_BUF(fp) + GFDR_FILE_RP(fp), i);
    GFDR_FILE_RP(fp) += i;
    if (i < (Sint32)size) {
        size -= i;
        ret = GFS_Fread(GFDR_FILE_GFS(fp), 1, GFDR_FILE_BUF(fp), SECT_BUF_SIZ);
        if (ret != SECT_BUF_SIZ) {
            if (ret < GFS_ERR_OK) {
                return ret;
            }
            return GFS_ERR_CDRD;
        }
        memcpy((Uint8*)buf + i, GFDR_FILE_BUF(fp), size);
        GFDR_FILE_RP(fp) = size;
    }
    return GFS_ERR_OK;
}

// 0x0601E16C
GFS_LOCAL Uint8 gfdr_readByte(GfdrFile* fp, Sint32* ec) {
    Uint8 tmp;

    *ec = gfdr_read(fp, &tmp, sizeof(tmp));
    return tmp;
}

// 0x0601E198
GFS_LOCAL Uint16 gfdr_readWord(GfdrFile* fp, Sint32* ec) {
    Uint16 tmp;

    *ec = gfdr_read(fp, &tmp, sizeof(tmp));
    return tmp;
}

// 0x0601E1C4
GFS_LOCAL Uint16 gfdr_readWordNB(GfdrFile* fp, Sint32* ec) {
    Uint16 tmp, dummy;

    *ec = gfdr_read(fp, &dummy, sizeof(dummy));
    if (*ec != GFS_ERR_OK) {
        return 0;
    }
    *ec = gfdr_read(fp, &tmp, sizeof(tmp));
    if (*ec != GFS_ERR_OK) {
        return 0;
    }
    return tmp;
}

// 0x0601E218
GFS_LOCAL Uint32 gfdr_readLongNB(GfdrFile* fp, Sint32* ec) {
    Uint32 tmp, dummy;

    *ec = gfdr_read(fp, &dummy, sizeof(dummy));
    if (*ec != GFS_ERR_OK) {
        return 0;
    }
    *ec = gfdr_read(fp, &tmp, sizeof(tmp));
    if (*ec != GFS_ERR_OK) {
        return 0;
    }
    return tmp;
}

// 0x0601E264
GFS_LOCAL Uint32 gfdr_readLongNM(GfdrFile* fp, Sint32* ec) {
    Uint32 tmp;

    *ec = gfdr_read(fp, &tmp, sizeof(tmp));
    return tmp;
}

// 0x0601E28C
GFS_LOCAL Sint32 gfdr_setNextRec(GfdrFile* fp, Sint32* ec) {
    Sint32 rsize, ret;

    rsize = gfdr_readByte(fp, ec);
    if (*ec != GFS_ERR_OK) {
        return 0;
    }
    if (rsize != 0) {
        return rsize;
    }

    ++GFDR_FILE_AP(fp);
    if (GFDR_FILE_AP(fp) >= GFDR_FILE_NSCT(fp)) {
        return rsize;
    }
    ret = GFS_Fread(GFDR_FILE_GFS(fp), 1, GFDR_FILE_BUF(fp), SECT_BUF_SIZ);
    if (ret != SECT_BUF_SIZ) {
        if (ret > 0) {
            *ec = GFS_ERR_CDRD;
        } else {
            *ec = ret;
        }
        return 0;
    }
    GFDR_FILE_RP(fp) = 0;
    rsize = gfdr_readByte(fp, ec);
    if (*ec != GFS_ERR_OK) {
        return 0;
    }
    return rsize;
}

// 0x0601E318
GFS_LOCAL Sint32 gfdr_readDirEnt(GfdrFile* fp, XaDirEnt* dir) {
    Sint32 ec, i, rdsz, fn_err = FALSE;
    Uint8 fn_len, file_flg;
    Sint8 ch = '\0', *fn_buf, *ext_pos;

    if (GFDR_FILE_GFS(fp) == NULL) {
        XA_DIR_RSIZE(dir) = 0;
        return GFS_ERR_OK;
    }
    XA_DIR_RSIZE(dir) = gfdr_setNextRec(fp, &ec);
    if (ec != GFS_ERR_OK) {
        return ec;
    }
    if (XA_DIR_RSIZE(dir) == 0) {
        return GFS_ERR_OK;
    }
    gfdr_readByte(fp, &ec);
    if (ec != GFS_ERR_OK) {
        return ec;
    }
    XA_DIR_POS(dir) = LSN2FAD(gfdr_readLongNB(fp, &ec));
    if (ec != GFS_ERR_OK) {
        return ec;
    }
    XA_DIR_LEN(dir) = gfdr_readLongNB(fp, &ec);
    if (ec != GFS_ERR_OK) {
        return ec;
    }
    for (i = 0; i < RECORDING_DATE_LEN; ++i) {
        gfdr_readByte(fp, &ec);
        if (ec != GFS_ERR_OK) {
            return ec;
        }
    }
    file_flg = gfdr_readByte(fp, &ec);
    if (ec != GFS_ERR_OK) {
        return ec;
    }
    XA_DIR_USIZE(dir) = gfdr_readByte(fp, &ec);
    if (ec != GFS_ERR_OK) {
        return ec;
    }
    XA_DIR_GSIZE(dir) = gfdr_readByte(fp, &ec);
    if (ec != GFS_ERR_OK) {
        return ec;
    }
    gfdr_readWordNB(fp, &ec);
    if (ec != GFS_ERR_OK) {
        return ec;
    }
    fn_len = gfdr_readByte(fp, &ec);
    if (ec != GFS_ERR_OK) {
        return ec;
    }
    rdsz = 33 + fn_len;
    fn_buf = ext_pos = XA_DIR_FNAME(dir);
    i = 0;
    while (i < MIN(GFDR_BASE_MAX, fn_len)) {
        ch = gfdr_readByte(fp, &ec), ++i;
        if (ec != GFS_ERR_OK) {
            return ec;
        }
        if (ch == ';') {
            break;
        }
        *fn_buf++ = ch;
        if (ch == '.') {
            ext_pos = fn_buf;
            break;
        }
    }
    if (ch == ';') {
        while (i < fn_len) {
            gfdr_readByte(fp, &ec), ++i;
            if (ec != GFS_ERR_OK) {
                return ec;
            }
        }
    } else if (ch != '.') {
        while (i < fn_len) {
            ch = gfdr_readByte(fp, &ec), ++i;
            if (ec != GFS_ERR_OK) {
                return ec;
            }
            if (ch == '.') {
                *fn_buf++ = ch;
                ext_pos = fn_buf;
                break;
            }
            fn_err = TRUE;
        }
    }
    while (i < fn_len) {
        ch = gfdr_readByte(fp, &ec), ++i;
        if (ec != GFS_ERR_OK) {
            return ec;
        }
        if (ch == ';') {
            while (i < fn_len) {
                gfdr_readByte(fp, &ec), ++i;
                if (ec != GFS_ERR_OK) {
                    return ec;
                }
            }
            break;
        }
        if (fn_buf - ext_pos > GFDR_EXT_MAX) {
            fn_err = TRUE;
            continue;
        }
        if (fn_buf - XA_DIR_FNAME(dir) < GFS_FNAME_LEN) {
            *fn_buf++ = ch;
        }
    }
    if (fn_buf - XA_DIR_FNAME(dir) < GFS_FNAME_LEN) {
        *fn_buf = '\0';
    }
    if (NEEDS_PADDING(fn_len)) {
        gfdr_readByte(fp, &ec);
        if (ec != GFS_ERR_OK) {
            return ec;
        }
        ++rdsz;
    }
    if (XA_DIR_FNAME(dir)[0] == GFDR_CURRENT_DIR_ID) {
        XSTRCPY(XA_DIR_FNAME(dir), ".");
    } else if (XA_DIR_FNAME(dir)[0] == GFDR_PARENT_DIR_ID) {
        XSTRCPY(XA_DIR_FNAME(dir), "..");
    }
    if (rdsz < XA_DIR_RSIZE(dir)) {
        gfdr_readLongNM(fp, &ec);
        if (ec != GFS_ERR_OK) {
            return ec;
        }
        XA_DIR_ATR(dir) = gfdr_readByte(fp, &ec) &
                          (GFS_ATR_DIR | GFS_ATR_CDDA | GFS_ATR_INTLV |
                           GFS_ATR_FORM2 | GFS_ATR_FORM1);
        if (ec != GFS_ERR_OK) {
            return ec;
        }
        gfdr_readByte(fp, &ec);
        if (ec != GFS_ERR_OK) {
            return ec;
        }
        gfdr_readWord(fp, &ec);
        if (ec != GFS_ERR_OK) {
            return ec;
        }
        XA_DIR_FN(dir) = gfdr_readByte(fp, &ec);
        if (ec != GFS_ERR_OK) {
            return ec;
        }
        for (i = rdsz + 9; i < XA_DIR_RSIZE(dir); ++i) {
            gfdr_readByte(fp, &ec);
            if (ec != GFS_ERR_OK) {
                return ec;
            }
        }
    } else {
        XA_DIR_ATR(dir) = (file_flg & 2) ? XA_ATR_DIR : 0;
        XA_DIR_FN(dir) = 0;
    }
    return GFS_ERR_OK;
}

// 0x0601E688
GFS_LOCAL void gfdr_setDirrecCd(CdcFile* rec, XaDirEnt* dir) {
    CDC_FILE_FAD(rec) = XA_DIR_POS(dir);
    CDC_FILE_SIZE(rec) = XA_DIR_LEN(dir);
    CDC_FILE_FN(rec) = XA_DIR_FN(dir);
    CDC_FILE_ATR(rec) = XA_DIR_ATR(dir);
    CDC_FILE_UNIT(rec) = XA_DIR_USIZE(dir);
    CDC_FILE_GAP(rec) = XA_DIR_GSIZE(dir);
}

// 0x0601E6C4
GFS_LOCAL void gfdr_setDirrecMem(CdcFile* rec, Sint32 fid, Sint32 len) {
    CDC_FILE_FAD(rec) = fid;
    CDC_FILE_SIZE(rec) = len;
    CDC_FILE_FN(rec) = 0;
    CDC_FILE_ATR(rec) = GFS_ATR_MEM_FILE;
    CDC_FILE_UNIT(rec) = 0;
    CDC_FILE_GAP(rec) = 0;
    GFMC_SetRsv(fid, MF_OVW);
}

// 0x0601E700
GFS_LOCAL void gfdr_setDirrecScsi(CdcFile* rec, Sint32 fid, Sint32 len) {
    CDC_FILE_FAD(rec) = fid;
    CDC_FILE_SIZE(rec) = len;
    CDC_FILE_FN(rec) = 0;
    CDC_FILE_ATR(rec) = GFS_ATR_SCSI_FILE;
    CDC_FILE_UNIT(rec) = 0;
    CDC_FILE_GAP(rec) = 0;
}

// 0x0601E728
GFS_LOCAL Bool gfdr_getScsiFinfo(Sint8* fname, Sint32* fid, Sint32* len) {
    Sint32 i, n_scsi_file;
    GfsdInfo info;

    if (MNG_SCSICON(gfs_mng_ptr)) {
        GFSD_GetFileNum(&n_scsi_file);
        for (i = 0; i < n_scsi_file; ++i) {
            GFSD_GetFileInfo(i, &info);
            if (XSTRNCMP(fname, GFSD_INFO_FNAME(&info), GFS_FNAME_LEN) == 0) {
                *fid = i;
                *len = GFSD_INFO_LENGTH(&info);
                return TRUE;
            }
        }
    }
    return FALSE;
}

// 0x0601E7B8
GFS_LOCAL Bool gfdr_findScsiFile(GfsDirId* rec, GfsDirId* recend, Sint32 fid) {
    while (rec < recend) {
        if ((GFS_DIR_ATR(rec) == GFS_ATR_SCSI_FILE) &&
            (GFS_DIR_FAD(rec) == fid)) {
            return TRUE;
        }
        ++rec;
    }
    return FALSE;
}

// 0x0601E7E4
GFS_LOCAL GfsDirName* gfdr_findFile(
    GfsDirName* rectbl, Sint32 n_dirent, Sint8* fname) {
    Sint32 i;

    for (i = 0; i < n_dirent; ++i) {
        if (XSTRNCMP(GFS_DIR_FNAME(rectbl), fname, GFS_FNAME_LEN) == 0) {
            return rectbl;
        }
        ++rectbl;
    }
    return NULL;
}

// 0x0601E834
GFS_LOCAL void gfdr_clearMemRsv(Sint32 n_memfile) {
    Sint32 i;

    for (i = 0; i < n_memfile; ++i) {
        GFMC_SetRsv(i, 0);
    }
}
