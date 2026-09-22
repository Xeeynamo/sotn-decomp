#include "../../sattypes.h"
#include "../../inc_asm.h"

#include "gfs.h"
#include "gfs_def.h"
#include "gfs_mmc.h"
#include "gfs_mmb.h"
#include "gfs_mmf.h"
#include "gfs_trn.h"

extern GfsDataPack gfmb_dtpk;

// 0x0602133C
void GFMB_Init(void) {
    GfdpHn      dtk = &gfmb_dtpk;
    
    GFDP_DATA(dtk) = NULL;
    GFDP_ADLT(dtk) = 0;
    GFDP_LEN(dtk) = 0;
    GFDP_NSCT(dtk) = 0;
    GFDP_USE(dtk) = FALSE;
}

// 0x06021358
void GFMB_Setup(GfsFlow *flow, Sint32 fid) {
    void        *area;
    GfsDtsrc    *dts = &GFS_FLW_DTSRC(flow);
    
    if (fid >= 0) {
        GFMC_GetFileInfo(fid, &area, NULL, NULL);
    } else {
        area = NULL;
    }
    GFS_DTS_FTYPE(dts) = MEM_FILE;
    GFS_MEMR_DATA(dts) = area;
    GFS_MEMR_FILEPOS(dts) = GFS_MEMR_SCTPOS(dts) = GFS_MEMR_SCTNUM(dts) = 0;
}

// 0x060213A0
Sint32 GFMB_GetLenData(GfsFlow *flow, Sint32 usct, Sint32 *len) {
    Sint32      ap;
    Sint32      nsct;
    Sint32      lastsize;
    GfsFinfo    *finfo = &GFS_FLW_FINFO(flow);
    GfsDtsrc    *dts = &GFS_FLW_DTSRC(flow);

    if (usct == GFTB_BUF_END) {
        usct = GFS_LONG_MAX;
    }
    nsct = GFS_MEMR_SCTNUM(dts) - GFS_MEMR_SCTPOS(dts);
    nsct = MIN(nsct, usct);
    if (len != NULL) {
        *len = nsct * MMF_SCTSIZE;
        ap = GFS_MEMR_FILEPOS(dts) + GFS_MEMR_SCTPOS(dts);
        lastsize = GFS_FI_SIZE(finfo) % MMF_SCTSIZE;
        if ((ap > GFS_FI_NSCT(finfo))&&(lastsize != 0)&&
            (GFS_MEMR_SCTPOS(dts) > 0)&&(*len != 0)) {
            *len -= MMF_SCTSIZE - lastsize;
        }
    }
    return nsct;
}

// 0x06021434
GfdpHn GFMB_GetSrcPack(GfsFlow *flow, Sint32 nsct) {
    GfsDtsrc    *dts = &GFS_FLW_DTSRC(flow);
    GfsFinfo    *finfo = &GFS_FLW_FINFO(flow);
    GfdpHn      dtk = &gfmb_dtpk;
    Sint32      len;
    
    if (GFDP_USE(dtk)) {
        return NULL;
    }
    len = nsct * MMF_SCTSIZE;

    if (((GFMF_Tell(flow) + nsct) >= GFS_FI_NSCT(finfo))&&
        (GFS_FI_LSTRM(finfo) != 0)&&(nsct > 0)) {
        len -= GFS_FI_LSTRM(finfo);
    }

    GFDP_DATA(dtk) = (Uint8 *)GFS_MEMR_DATA(dts) +
        (GFS_MEMR_FILEPOS(dts) +GFS_MEMR_SCTPOS(dts)) * MMF_SCTSIZE;
    GFDP_ADLT(dtk) = sizeof(Uint8);
    GFDP_LEN(dtk) = len;
    GFDP_NSCT(dtk) = nsct;
    GFDP_USE(dtk) = TRUE;
    return dtk;
}

// 0x060214B4
void GFMB_RtnPk(GfsFlow *flow, GfdpHn dpk, Sint32 nsct) {
    GfdpHn      dtk = &gfmb_dtpk;

    if (nsct == GFTR_ALLSCT) {
        nsct = GFDP_NSCT(dpk);
    }
    GFMF_Seek(flow, GFMF_Tell(flow) + nsct);
    GFDP_USE(dtk) = FALSE;
}