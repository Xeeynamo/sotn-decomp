#include "../../sattypes.h"
#include "../../inc_asm.h"

#include "gfs.h"
#include "gfs_def.h"
#include "gfs_mmc.h"

#define GFMC_FNAME_LEN  12

typedef struct {
    Uint32      fblksiz;
    Sint8       fname[GFMC_FNAME_LEN];
    Sint16      version;
    Sint16      ftype;
    Sint32      filesiz;
    Uint32      datetime;
    Sint16      sctsiz;
    Sint16      rsv;
} MmcHeader;

#define MMCH_FBLKSIZ(mmch)      DWORD(&((mmch)->fblksiz))
#define MMCH_FNAME(mmch)        ((mmch)->fname)
#define MMCH_VERSION(mmch)      ((mmch)->version)
#define MMCH_FTYPE(mmch)        ((mmch)->ftype)
#define MMCH_FILESIZ(mmch)      ((mmch)->filesiz)
#define MMCH_DATETIME(mmch)     ((mmch)->datetime)
#define MMCH_SCTSIZ(mmch)       ((mmch)->sctsiz)
#define MMCH_RSV(mmch)          ((mmch)->rsv)

#define DWORD(x)    (*((Uint32 *)(x)))
#define WORD(x)     (*((Uint16 *)(x)))

GFS_LOCAL MmcHeader *gfmc_getHeaderAddr(Sint32 fid);

// 0x06021500
void *GFMC_GetBase(void) {
    return (void *)GFMC_base;
}

// 0x06021510
void GFMC_GetFileInfo(Sint32 fid, void **area, Sint32 *size, Sint32 *sct_siz) {
    MmcHeader   *hp;
    void        *a;
    Sint32      fsize;
    Sint32      ssize;

    hp = gfmc_getHeaderAddr(fid);
    if (hp == NULL) {
        a = NULL;
        fsize = ssize = 0;
    } else {
        a = (Sint8 *)(hp + 1);
        fsize = DWORD(&(MMCH_FILESIZ(hp)));
        ssize = WORD(&(MMCH_SCTSIZ(hp)));
    }
    if (area != NULL) {
        *area = a;
    }
    if (size != NULL) {
        *size = fsize;
    }
    if (sct_siz != NULL) {
        *sct_siz = ssize;
    }
}

// 0x06021564
Sint32 GFMC_GetNumFile(void) {
    Sint8   *bp;
    Uint32  blksiz;
    Uint32  i;

    bp = GFMC_GetBase();
    if (bp == NULL) {
        return 0;
    }
    i = 0;
    while (TRUE) {
        blksiz = MMCH_FBLKSIZ((MmcHeader *)bp);
        if (blksiz == 0) {
            break;
        }
        bp += blksiz;
        i++;
    }
    return i;
}

// 0x06021594
Sint8 *GFMC_GetFname(Sint32 fid) {
    MmcHeader   *hp;

    hp = gfmc_getHeaderAddr(fid);
    if (hp == NULL) {
        return NULL;
    } else {
        return MMCH_FNAME(hp);
    }
}

// 0x060215B4
void GFMC_SetRsv(Sint32 fid, Sint16 rsv) {
    MmcHeader   *hp;
    
    hp = gfmc_getHeaderAddr(fid);
    if (hp != NULL) {
        MMCH_RSV(hp) = rsv;
    }
}

// 0x060215D8
Sint16 GFMC_GetRsv(Sint32 fid) {
    MmcHeader   *hp;
    
    hp = gfmc_getHeaderAddr(fid);
    if (hp != NULL) {
        return MMCH_RSV(hp);
    } else {
        return MMC_ERROR;
    }
}

// 0x060215FC
GFS_LOCAL MmcHeader *gfmc_getHeaderAddr(Sint32 fid) {
    Sint8       *bp;
    Uint32      blksiz;
    Sint32      i;
    MmcHeader   *hp;

    bp = (Sint8 *)GFMC_GetBase();
    if (bp == NULL) {
        return NULL;
    }
    for (i = 0; i < fid; i++) {
        hp = (MmcHeader *)bp;
        blksiz = MMCH_FBLKSIZ(hp);
        if (blksiz == 0L) {
            return NULL;
        }
        bp += blksiz;
    }
    return (MmcHeader *)bp;
}
