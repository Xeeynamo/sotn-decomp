#ifndef GFS_DIR_H
#define GFS_DIR_H

#define GFS_ATR_FTYPE_MASK 0x06
#define GFS_ATR_CD_FILE 0x00
#define GFS_ATR_MEM_FILE 0x04
#define GFS_ATR_SCSI_FILE 0x02

#define IS_CDFILE(atr)                                                         \
    ((((atr) & GFS_ATR_FTYPE_MASK) == GFS_ATR_CD_FILE) ? TRUE : FALSE)

#define IS_MEMFILE(atr)                                                        \
    ((((atr) & GFS_ATR_FTYPE_MASK) == GFS_ATR_MEM_FILE) ? TRUE : FALSE)

#define IS_SCSIFILE(atr)                                                       \
    ((((atr) & GFS_ATR_FTYPE_MASK) == GFS_ATR_SCSI_FILE) ? TRUE : FALSE)

Sint32 GFDR_SetupDirTbl(GfsHn gfs, GfsDirTbl* dirtbl, Sint32 nsct);
Sint32 GFDR_NameToId(GfsDirName* rectbl, Sint8* fname, Sint32 max);
GfsDirId* GFDR_GetInfoDirId(Sint32 fid, GfsDirId* rectbl);
GfsDirName* GFDR_GetInfoDirName(Sint32 fid, GfsDirName* rectbl);
Sint32 GFDR_GetAtrDirId(Sint32 fid, GfsDirId* rectbl);
Sint32 GFDR_GetAtrDirName(Sint32 fid, GfsDirName* rectbl);
Sint32 GFDR_ChgRoot(void);
Sint32 GFDR_ChgDir(Sint32 fid);

#endif
