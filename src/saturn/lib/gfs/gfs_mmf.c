#include "../../sattypes.h"
#include "../../inc_asm.h"

#include "gfs.h"
#include "gfs_def.h"
#include "gfs_mmf.h"
#include "gfs_mmb.h"
#include "gfs_mmc.h"

// 0x0601D674
Bool GFMF_Init(void) {
    GFMB_Init();
    return (GFMC_GetBase() == NULL) ? FALSE : TRUE;
}

// 0x0601D69C
void GFMF_Setup(GfsFlow* flow, GfsDirId* dirrec, Sint32 fid) {
    Sint32 fsize;
    GfsFinfo* finfo = &GFS_FLW_FINFO(flow);

    fsize = GFS_DIR_SIZE(dirrec);
    GFS_FI_FID(finfo) = fid;
    GFS_FI_FAD(finfo) = 0;
    GFS_FI_SIZE(finfo) = fsize;
    GFS_FI_UNIT(finfo) = GFS_DIR_UNIT(dirrec);
    GFS_FI_GAP(finfo) = GFS_DIR_GAP(dirrec);
    GFS_FI_FN(finfo) = 0;
    GFS_FI_ATR(finfo) = GFS_DIR_ATR(dirrec);
    GFS_FI_SCTSZ(finfo) = MMF_SCTSIZE;
    GFS_FI_NSCT(finfo) = GFS_BYTE_SCT(fsize, MMF_SCTSIZE);
    GFS_FI_LSTRM(finfo) = GFS_LAST_ROOM(fsize, MMF_SCTSIZE);
    GFMB_Setup(flow, GFS_DIR_FAD(dirrec));
    GFS_FLW_GMODE(flow) = GFS_GMODE_ERASE;
    GFS_FLW_SCT(flow) = GFS_FLW_SCTCNT(flow) = 0;
    GFS_FLW_SCTMAX(flow) = GFS_RPARA_DFL;
}

// 0x0601D758
Sint32 GFMF_FlowInBuf(GfsFlow* flow) {
    Sint32 remain;
    Sint32 nsct;
    GfsDtsrc* dts = &GFS_FLW_DTSRC(flow);

    remain = GFS_FLW_SCT(flow) - GFS_FLW_SCTCNT(flow);
    if (remain <= 0) {
        return GFS_FIN_END;
    }
    nsct = MIN(remain, GFS_FLW_SCTMAX(flow));
    GFS_FLW_SCTCNT(flow) += nsct;
    nsct -= GFS_MEMR_SCTNUM(dts) - GFS_MEMR_SCTPOS(dts);
    if (nsct > 0) {
        GFS_MEMR_SCTNUM(dts) += nsct;
    }
    if (GFS_FLW_SCTCNT(flow) >= GFS_FLW_SCT(flow)) {
        return GFS_FIN_END;
    } else {
        return GFS_FIN_START;
    }
}

// 0x0601D7B0
void GFMF_StopInBuf(GfsFlow* flow, Bool stop_flag) {
    GfsDtsrc* dts = &GFS_FLW_DTSRC(flow);

    GFS_MEMR_SCTPOS(dts) = GFS_MEMR_SCTNUM(dts) = 0;
}

// 0x0601D7C0
Sint32 GFMF_Seek(GfsFlow* flow, Sint32 pos) {
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
    if ((GFS_MEMR_FILEPOS(dts) <= pos) &&
        (pos <= (GFS_MEMR_FILEPOS(dts) + GFS_MEMR_SCTNUM(dts)))) {
        ofs = pos - GFS_MEMR_FILEPOS(dts);
        if (GFS_FLW_GMODE(flow) == GFS_GMODE_RESIDENT) {
            GFS_MEMR_SCTPOS(dts) = ofs;
        } else {
            GFS_MEMR_FILEPOS(dts) = pos;
            GFS_MEMR_SCTNUM(dts) -= ofs;
        }
    } else {
        GFS_MEMR_FILEPOS(dts) = pos;
        GFS_MEMR_SCTPOS(dts) = 0;
        GFS_MEMR_SCTNUM(dts) = 0;
    }
    return pos;
}

// 0x0601D814
Sint32 GFMF_Tell(GfsFlow* flow) {
    GfsDtsrc* dts = &GFS_FLW_DTSRC(flow);

    return GFS_MEMR_FILEPOS(dts) + GFS_MEMR_SCTPOS(dts);
}
