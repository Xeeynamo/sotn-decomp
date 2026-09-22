#ifndef GFS_MMC_H
#define GFS_MMC_H

#define MMC_ERROR       (-1)

void *GFMC_GetBase(void);
void GFMC_GetFileInfo(Sint32 fid, void **area, Sint32 *size, Sint32 *sctsiz);
Sint32 GFMC_GetNumFile(void);
Sint8 *GFMC_GetFname(Sint32 fid);
void GFMC_SetRsv(Sint32 fid, Sint16 rsv);
Sint16 GFMC_GetRsv(Sint32 fid);

#endif