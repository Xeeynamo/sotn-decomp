#include "../../sattypes.h"
#include "../../inc_asm.h"

#include "gfs.h"
#include "gfs_def.h"
#include "gfs_sf.h"
#include "gfs_scsi.h"
#include "gfs_trn.h"

#define GFSB_TPARA_DFL  1

GFS_LOCAL Sint32 gfsb_getActSiz(GfsFlow *flow, Sint32 usct, Sint32 *len);

extern GfsDataPack gfsb_dtpk;

// 0x06021638
void GFSB_Init(void) {
    GfdpHn      dpk = &gfsb_dtpk;
    
    GFDP_DATA(dpk) = NULL;
    GFDP_ADLT(dpk) = 0;
    GFDP_LEN(dpk) = 0;
    GFDP_NSCT(dpk) = 0;
    GFDP_USE(dpk) = FALSE;
}

// 0x06021654
void GFSB_Setup(GfsFlow *flow, Sint32 fid) {
    GfsDtsrc    *dts = &GFS_FLW_DTSRC(flow);

    GFS_DTS_FTYPE(dts) = SCSI_FILE;
    GFS_SCR_FID(dts) = fid;
    GFS_SCR_FILEPOS(dts) = GFS_SCR_SCTPOS(dts) = GFS_SCR_SCTNUM(dts) = 0;
}

// 0x06021670
Sint32 GFSB_GetLenData(GfsFlow *flow, Sint32 usct, Sint32 *len) {
    Sint32      nsct, lastsize, ap;
    GfsFinfo    *finfo = &GFS_FLW_FINFO(flow);
    GfsDtsrc    *dts = &GFS_FLW_DTSRC(flow);

    if (usct == GFTB_BUF_END) {
        usct = GFS_LONG_MAX;
    }
    nsct = GFS_SCR_SCTNUM(dts) - GFS_SCR_SCTPOS(dts);
    nsct = MIN(nsct, usct);
    if (len != NULL) {
        *len = nsct * SFM_SCTSIZE;
        ap = GFS_SCR_FILEPOS(dts) + GFS_SCR_SCTPOS(dts); 
        if (ap > GFS_FI_NSCT(finfo)) {
            lastsize = GFS_FI_SIZE(finfo) % SFM_SCTSIZE;
            if ((*len != 0)&&(lastsize != 0)) {
                *len -= SFM_SCTSIZE - lastsize;
            }
        }
    }
    return nsct;
}

// 0x060216F4
GfdpHn GFSB_GetSrcPack(GfsFlow *flow, Sint32 usct) {
    Sint32      len, nsct;
    GfsDtsrc    *dts = &GFS_FLW_DTSRC(flow);
    GfdpHn      dpk = &gfsb_dtpk;
    
    if (GFDP_USE(dpk)) {
        return NULL;
    }
    GFDP_DATA(dpk) = GFSD_GetBuf();
    GFDP_ADLT(dpk) = sizeof(Uint8);
    nsct = gfsb_getActSiz(flow, usct, &len);
    GFSD_Read(GFS_SCR_FID(dts), GFS_SCR_FILEPOS(dts) + GFS_SCR_SCTPOS(dts));
    GFDP_LEN(dpk) = len;
    GFDP_NSCT(dpk) = nsct;
    GFDP_USE(dpk) = TRUE;
    return dpk;
}

// 0x06021770
void GFSB_RtnPk(GfsFlow *flow, GfdpHn dtpk, Sint32 nsct) {
    GfdpHn      dpk = &gfsb_dtpk;

    if (GFDP_USE(dpk)) {
        if (nsct == GFTR_ALLSCT) {
            nsct = GFDP_NSCT(dpk);
        }
        GFSF_Seek(flow, GFSF_Tell(flow) + nsct);
        GFDP_USE(dpk) = FALSE;
    }
}

// 0x060217C0
GFS_LOCAL Sint32 gfsb_getActSiz(GfsFlow *flow, Sint32 usct, Sint32 *len) {
    Sint32      nsct;
    GfsDtsrc    *dts = &GFS_FLW_DTSRC(flow);

    nsct = GFS_SCR_SCTNUM(dts) - GFS_SCR_SCTPOS(dts);
    nsct = MIN(nsct, usct);
    nsct = MIN(nsct, GFSB_TPARA_DFL);
    *len = nsct * SFM_SCTSIZE;
    return nsct;
}
