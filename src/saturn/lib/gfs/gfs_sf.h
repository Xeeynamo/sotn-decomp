#ifndef GFS_SF_H
#define GFS_SF_H

void GFSF_Init(void);
Bool GFSF_Setup(GfsFlow *flow, GfsDirId *dirrec, Sint32 fid);
Sint32 GFSF_FlowInBuf(GfsFlow *flow);
void GFSF_StopInBuf(GfsFlow *flow, Bool stop_flag);
Sint32 GFSF_Seek(GfsFlow *flow, Sint32 off);
Sint32 GFSF_Tell(GfsFlow *flow);
void GFSF_Close(GfsDtsrc *dtsrc);

void GFSB_Init(void);
void GFSB_Setup(GfsFlow *flow, Sint32 fid);
Sint32 GFSB_GetLenData(GfsFlow *flow, Sint32 usct, Sint32 *len);
GfdpHn GFSB_GetSrcPack(GfsFlow *flow, Sint32 nsct);
void GFSB_RtnPk(GfsFlow *flow, GfdpHn dtpk, Sint32 nsct);

#endif