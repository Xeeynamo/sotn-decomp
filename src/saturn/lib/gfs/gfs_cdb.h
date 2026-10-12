#ifndef GFS_CDB_H
#define GFS_CDB_H

Bool GFCB_Setup(GfsFlow* flow);
void GFCB_Close(GfsDtsrc* dts);
Sint32 GFCB_SetGmode(GfsDtsrc* dts, Sint32 gmode);
Sint32 GFCB_GetLenData(GfsFlow* flow, Sint32 usct, Sint32* asiz);
void GFCB_SetFilt(GfsDtsrc* dts, Sint32 fmode, CdcSubh* subh);
Sint32 GFCB_DeleteAllData(GfsDtsrc* dts);
Sint32 GFCB_Tell(GfsDtsrc* dts);
Sint32 GFCB_Seek(GfsFlow* flow, Sint32 off, Sint32 org);
GfdpHn GFCB_GetSrcPack(GfsFlow* flow, Sint32 nsct);
GfdpHn GFCB_ReadySrcPack(GfsFlow* flow, Sint32 nsct);
Bool GFCB_GetSctData(GfdpHn dpk, GfsDtsrc* dts);
GfdpHn GFCB_GetDstPack(GfsDtsrc* dts, Sint32 len);
void GFCB_RtnPk(GfsFlow* flow, GfdpHn dpk, Sint32 nsct);
Sint32 GFCB_MovePickup(GfsDtsrc* dts, CdcPos* pos);
Bool GFCB_SetCon(GfsDtsrc* dts);
Bool GFCB_GetPickup(GfsDtsrc* dts);
Bool GFCB_IsPuOwner(GfsDtsrc* dts);
void GFCB_UngetPickup(GfsDtsrc* dts);

#endif
