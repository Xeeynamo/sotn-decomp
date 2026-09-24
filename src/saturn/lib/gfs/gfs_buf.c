#include "../../sattypes.h"
#include "../../inc_asm.h"

#include "gfs.h"
#include "gfs_def.h"
#include "gfs_buf.h"
#include "gfs_cdb.h"

#include "gfs_sf.h"
#include "gfs_mmb.h"

typedef struct {
    Sint32 (*getltran)(GfsFlow* flow, Sint32 usct, Sint32* nsct);
    GfdpHn (*getsrcpk)(GfsFlow* flow, Sint32 nsct);
    Bool (*getsctdt)(GfdpHn dpk, GfsDtsrc* dts);
    void (*rtnpk)(GfsFlow* flow, GfdpHn dtpk, Sint32 nsct);
} GfsBufIf;

GFS_LOCAL Bool gfbf_getSctDt(GfdpHn dpk, GfsDtsrc* dts);

static const GfsBufIf bufif_func[FILE_TYPE] = {
    {GFCB_GetLenData, GFCB_GetSrcPack, GFCB_GetSctData, GFCB_RtnPk},
    {GFMB_GetLenData, GFMB_GetSrcPack, gfbf_getSctDt, GFMB_RtnPk},
    {GFSB_GetLenData, GFSB_GetSrcPack, gfbf_getSctDt, GFSB_RtnPk},
};

// 0x0601F2D0
Sint32 GFBF_GetTranData(GfsHn gfs, Sint32 rsct, Sint32* len) {
    GfsFlow* flow = &GFS_FILE_FLOW(gfs);
    Sint32 ftype = GFS_DTS_FTYPE(&GFS_FLW_DTSRC(flow));

    return bufif_func[ftype].getltran(flow, rsct, len);
}

// 0x0601F2F4
Sint32 GFBF_GetNumData(GfsHn gfs) {
    GfsFlow* flow = &GFS_FILE_FLOW(gfs);
    Sint32 ftype = GFS_DTS_FTYPE(&GFS_FLW_DTSRC(flow));

    return bufif_func[ftype].getltran(flow, GFTB_BUF_END, NULL);
}

// 0x0601F320
GfdpHn GFBF_GetSrcPk(GfsHn gfs, Sint32 nsct) {
    GfsFlow* flow = &GFS_FILE_FLOW(gfs);
    Sint32 ftype = GFS_DTS_FTYPE(&GFS_FLW_DTSRC(flow));

    return bufif_func[ftype].getsrcpk(flow, nsct);
}

// 0x0601F348
Bool GFBF_GetSctData(GfdpHn dpk, GfsFlow* flow) {
    Sint32 ftype = GFS_DTS_FTYPE(&GFS_FLW_DTSRC(flow));

    return bufif_func[ftype].getsctdt(dpk, &GFS_FLW_DTSRC(flow));
}

// 0x0601F370
void GFBF_RtnPk(GfsHn gfs, GfdpHn gpdp, Sint32 nsct) {
    GfsFlow* flow = &GFS_FILE_FLOW(gfs);
    Sint32 ftype = GFS_DTS_FTYPE(&GFS_FLW_DTSRC(flow));

    bufif_func[ftype].rtnpk(flow, gpdp, nsct);
}

// 0x0601F398
GFS_LOCAL Bool gfbf_getSctDt(GfdpHn dpk, GfsDtsrc* dts) { return TRUE; }
