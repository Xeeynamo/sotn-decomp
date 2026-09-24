#include "../../sattypes.h"
#include "../../inc_asm.h"

#include "gfs.h"
#include "gfs_def.h"
#include "gfs_scsi.h"
#include "gfs_sf.h"

#define BOOT_WORK_DIPSW (*(Sint32*)0x6000248)

#define DIP_USE_SCSI 0x10

// 0x0601D824
void GFSF_Init(void) {
    MNG_FLAGS(gfs_mng_ptr) &= ~MNG_SCSICON_MSK;
    if (BOOT_WORK_DIPSW & DIP_USE_SCSI) {
        MNG_FLAGS(gfs_mng_ptr) |= MNG_SCSICON_MSK;
    }
    GFSB_Init();
}

// 0x0601D86C
Bool GFSF_Setup(GfsFlow* flow, GfsDirId* dirrec, Sint32 fid) {
    Sint32 fsize;
    GfsFinfo* finfo = &GFS_FLW_FINFO(flow);

    if (GFSD_Open(GFS_DIR_FAD(dirrec)) != GFSD_ERR_OK) {
        return FALSE;
    }
    fsize = GFS_DIR_SIZE(dirrec);
    GFS_FI_FID(finfo) = fid;
    GFS_FI_FAD(finfo) = 0;
    GFS_FI_SIZE(finfo) = fsize;
    GFS_FI_UNIT(finfo) = GFS_DIR_UNIT(dirrec);
    GFS_FI_GAP(finfo) = GFS_DIR_GAP(dirrec);
    GFS_FI_FN(finfo) = 0;
    GFS_FI_ATR(finfo) = GFS_DIR_ATR(dirrec);
    GFS_FI_SCTSZ(finfo) = SFM_SCTSIZE;
    GFS_FI_NSCT(finfo) = GFS_BYTE_SCT(fsize, SFM_SCTSIZE);
    GFS_FI_LSTRM(finfo) = GFS_LAST_ROOM(fsize, SFM_SCTSIZE);
    GFSB_Setup(flow, GFS_DIR_FAD(dirrec));
    GFS_FLW_GMODE(flow) = GFS_GMODE_ERASE;
    GFS_FLW_SCT(flow) = GFS_FLW_SCTCNT(flow) = 0;
    GFS_FLW_SCTMAX(flow) = GFS_RPARA_DFL;
    return TRUE;
}

// 0x0601D94C
Sint32 GFSF_FlowInBuf(GfsFlow* flow) {
    Sint32 remain;
    Sint32 nsct;
    GfsDtsrc* dts = &GFS_FLW_DTSRC(flow);

    remain = GFS_FLW_SCT(flow) - GFS_FLW_SCTCNT(flow);
    if (remain <= 0) {
        return GFS_FIN_END;
    }
    nsct = MIN(remain, GFS_FLW_SCTMAX(flow));
    GFS_FLW_SCTCNT(flow) += nsct;
    nsct -= GFS_SCR_SCTNUM(dts) - GFS_SCR_SCTPOS(dts);
    if (nsct > 0) {
        GFS_SCR_SCTNUM(dts) += nsct;
    }
    if (GFS_FLW_SCTCNT(flow) >= GFS_FLW_SCT(flow)) {
        return GFS_FIN_END;
    } else {
        return GFS_FIN_START;
    }
}

// 0x0601D9A4
void GFSF_StopInBuf(GfsFlow* flow, Bool stop_flag) {
    GfsDtsrc* dts = &GFS_FLW_DTSRC(flow);

    GFS_SCR_SCTPOS(dts) = GFS_SCR_SCTNUM(dts) = 0;
}

// 0x0601D9B4
Sint32 GFSF_Seek(GfsFlow* flow, Sint32 pos) {
    Sint32 nsct, ofs;
    GfsFinfo* finfo = &GFS_FLW_FINFO(flow);
    GfsDtsrc* dts = &GFS_FLW_DTSRC(flow);

    nsct = GFS_FI_NSCT(finfo);
    if (pos > nsct) {
        pos = nsct;
    }
    if (pos < 0) {
        pos = 0;
    }
    if ((GFS_SCR_FILEPOS(dts) <= pos) &&
        (pos <= (GFS_SCR_FILEPOS(dts) + GFS_SCR_SCTNUM(dts)))) {
        ofs = pos - GFS_SCR_FILEPOS(dts);
        if (GFS_FLW_GMODE(flow) == GFS_GMODE_RESIDENT) {
            GFS_SCR_SCTPOS(dts) = ofs;
        } else {
            GFS_SCR_FILEPOS(dts) = pos;
            GFS_SCR_SCTNUM(dts) -= ofs;
        }
    } else {
        GFS_SCR_FILEPOS(dts) = pos;
        GFS_SCR_SCTPOS(dts) = 0;
        GFS_SCR_SCTNUM(dts) = 0;
    }
    return pos;
}

// 0x0601DA08
Sint32 GFSF_Tell(GfsFlow* flow) {
    GfsDtsrc* dts = &GFS_FLW_DTSRC(flow);

    return GFS_SCR_FILEPOS(dts) + GFS_SCR_SCTPOS(dts);
}

// 0x0601DA18
void GFSF_Close(GfsDtsrc* dts) { GFSD_Close(GFS_SCR_FID(dts)); }
