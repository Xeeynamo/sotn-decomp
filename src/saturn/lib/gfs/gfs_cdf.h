#ifndef GFS_CDF_H
#define GFS_CDF_H

extern Sint32 gfcf_stat;
extern Sint32 gfcf_fad;

Sint32 GFCF_Init(Bool use_cdbfs);
Bool GFCF_Setup(GfsFlow* flow, GfsDirId* dirrec, Sint32 fid);
void GFCF_SetSct(GfsFlow* flow, Sint32 sct);
void GFCF_GetFileInfo(GfsFlow* flow, Sint32* fid, Sint32* fad, Sint32* sctsiz,
                      Sint32* nsct, Sint32* lastsiz, Sint32* fno, Sint32* atr);
Sint32 GFCF_FlowInBuf(GfsFlow* flow);
void GFCF_StopInBuf(GfsFlow* flow, Bool stop_flag);
Sint32 GFCF_Recover(GfsFlow* flow);
Sint32 GFCF_Tell(GfsFlow* flow);
Sint32 GFCF_Seek(GfsFlow* flow, Sint32 off);
Sint32 GFCF_MovePickup(GfsFlow* flow, Sint32 off);
Sint32 GFCF_cnvIntlvOfs(GfsFinfo* finfo, Sint32 ofs);
Sint32 GFCF_GetStat(Sint32* fad, Sint32* hirq);

#endif
