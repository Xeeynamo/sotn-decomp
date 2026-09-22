#ifndef GFS_SCSI_H
#define GFS_SCSI_H

enum GfsdErrCode {
    GFSD_ERR_OK = 0,
    GFSD_ERR_OPEN,
    GFSD_ERR_SEEK,
    GFSD_ERR_READ,
    GFSD_ERR_FID,
    GFSD_WARN_OPEN,
    GFSD_WARN_CLOSE,
    GFSD_ERR_TRANS,
    GFSD_ERR_END
};

#define GFSD_INFO_LENGTH(sinfo) ((sinfo)->length)
#define GFSD_INFO_FNAME(sinfo)  ((sinfo)->fname)

typedef struct {
    Sint32      length;
    Sint8       fname[12];
} GfsdInfo;

#define GFSD_Init        ((Sint32(*)())*((long*)0x60003c0))
#define GFSD_GetFileNum  ((Sint32(*)())*((long*)0x60003c4))
#define GFSD_GetFileInfo ((Sint32(*)())*((long*)0x60003c8))
#define GFSD_Read        ((Sint32(*)())*((long*)0x60003cc))
#define GFSD_Term        ((Sint32(*)())*((long*)0x60003d0))
#define GFSD_Open        ((Sint32(*)())*((long*)0x60003d4))
#define GFSD_Close       ((Sint32(*)())*((long*)0x60003d8))
#define GFSD_GetBuf      ((Uint8*(*)())*((long*)0x60003dc))

#endif