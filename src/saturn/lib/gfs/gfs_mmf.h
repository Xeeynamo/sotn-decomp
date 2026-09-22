#ifndef GFS_MMF_H
#define GFS_MMF_H

Bool GFMF_Init(void);
void GFMF_Setup(GfsFlow *flow, GfsDirId *dirrec, Sint32 fid);
Sint32 GFMF_FlowInBuf(GfsFlow *flow);
void GFMF_StopInBuf(GfsFlow *flow, Bool stop_flag);
Sint32 GFMF_Seek(GfsFlow *flow, Sint32 off);
Sint32 GFMF_Tell(GfsFlow *flow);

#endif