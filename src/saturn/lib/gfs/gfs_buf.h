#ifndef GFS_BUF_H
#define GFS_BUF_H

Sint32 GFBF_GetTranData(GfsHn gfs, Sint32 rsct, Sint32* len);
Sint32 GFBF_GetNumData(GfsHn gfs);
GfdpHn GFBF_GetSrcPk(GfsHn gfs, Sint32 nsct);
Bool GFBF_GetSctData(GfdpHn dpk, GfsFlow* flow);
void GFBF_RtnPk(GfsHn gfs, GfdpHn gpdp, Sint32 nsct);

#endif
