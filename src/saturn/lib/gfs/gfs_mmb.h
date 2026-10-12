#ifndef GFS_MMB_H
#define GFS_MMB_H

void GFMB_Init(void);
void GFMB_Setup(GfsFlow* flow, Sint32 fid);
Sint32 GFMB_GetLenData(GfsFlow* flow, Sint32 usct, Sint32* len);
Sint32 GFMB_GetLenRoom(GfsFile* fp);
GfdpHn GFMB_GetSrcPack(GfsFlow* flow, Sint32 nsct);
GfdpHn GFMB_GetDstPack(GfsTrans* trn, Sint32 len);
void GFMB_RtnPk(GfsFlow* flow, GfdpHn dpk, Sint32 nsct);

#endif
