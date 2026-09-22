#ifndef GFS_H
#define GFS_H

#include "../cdc.h"

#define GFS_FNAME_LEN 12

#define GFS_ATR_DIR 0x80
#define GFS_ATR_CDDA 0x40
#define GFS_ATR_INTLV 0x20
#define GFS_ATR_FORM2 0x10
#define GFS_ATR_FORM1 0x08
#define GFS_ATR_END_TBL 0x01

#define GFS_BUFSIZ_INF -1
#define GFS_RPARA_DFL 0x7fffffff

#define GFS_DDS_ADDR 0x6000ccc
#define GFS_DDS_EXEC 0x01
#define GFS_DDS_ID() (*(Uint8*)(GFS_DDS_ADDR + 0))
#define GFS_DDS_TNO() (*(Uint8*)(GFS_DDS_ADDR + 1))
#define GFS_DDS_FID() (*(Uint16*)(GFS_DDS_ADDR + 2))
#define GFS_IS_DDS() (GFS_DDS_ID() == GFS_DDS_EXEC)

#define GFS_ERR_OK 0
#define GFS_ERR_CDRD (-1)
#define GFS_ERR_CDNODISC (-2)
#define GFS_ERR_CDROM (-3)
#define GFS_ERR_DIRTBL (-4)
#define GFS_ERR_OPENMAX (-5)
#define GFS_ERR_DIR (-6)
#define GFS_ERR_CDBFS (-7)
#define GFS_ERR_NONAME (-8)
#define GFS_ERR_NEXIST (-9)
#define GFS_ERR_FID (-10)
#define GFS_ERR_HNDL (-11)
#define GFS_ERR_SEEK (-12)
#define GFS_ERR_ORG (-13)
#define GFS_ERR_NUM (-14)
#define GFS_ERR_OFS (-15)
#define GFS_ERR_FBUSY (-16)
#define GFS_ERR_PARA (-17)
#define GFS_ERR_BUSY (-18)
#define GFS_ERR_NOHNDL (-19)
#define GFS_ERR_PUINUSE (-20)
#define GFS_ERR_ALIGN (-21)
#define GFS_ERR_TMOUT (-22)
#define GFS_ERR_CDOPEN (-23)
#define GFS_ERR_BFUL (-24)
#define GFS_ERR_FATAL (-25)

enum GfsAccessMode {
    GFS_NWSTAT_NOACT = 0,
    GFS_NWSTAT_FREAD,
    GFS_NWSTAT_CDREAD
};

enum GfsSeekMode { GFS_SEEK_SET = 0, GFS_SEEK_CUR, GFS_SEEK_END };

enum GfsGetMode { GFS_GMODE_ERASE = 0, GFS_GMODE_RESIDENT };

enum GfsTransMode {
    GFS_TMODE_SCU = 0,
    GFS_TMODE_SDMA0,
    GFS_TMODE_SDMA1,
    GFS_TMODE_CPU,
    GFS_TMODE_STM,
    GFS_TMODE_END
};

enum GfsServerStatus {
    GFS_SVR_COMPLETED = 0,
    GFS_SVR_BUSY,
    GFS_SVR_CDPAUSE,
    GFS_SVR_ERROR
};

enum GfsDirType { GFS_DIR_ID = 0, GFS_DIR_NAME };

#define GFS_DIR_REC(rec) ((rec)->dirrec)
#define GFS_DIR_FAD(rec) CDC_FILE_FAD(&GFS_DIR_REC(rec))
#define GFS_DIR_SIZE(rec) CDC_FILE_SIZE(&GFS_DIR_REC(rec))
#define GFS_DIR_UNIT(rec) CDC_FILE_UNIT(&GFS_DIR_REC(rec))
#define GFS_DIR_GAP(rec) CDC_FILE_GAP(&GFS_DIR_REC(rec))
#define GFS_DIR_FN(rec) CDC_FILE_FN(&GFS_DIR_REC(rec))
#define GFS_DIR_ATR(rec) CDC_FILE_ATR(&GFS_DIR_REC(rec))
#define GFS_DIR_FNAME(rec) ((rec)->fname)

#define GFS_DIRTBL_TYPE(dirtbl) ((dirtbl)->type)
#define GFS_DIRTBL_NDIR(dirtbl) ((dirtbl)->ndir)
#define GFS_DIRTBL_DIRID(dirtbl) ((dirtbl)->dir.dir_i)
#define GFS_DIRTBL_DIRNAME(dirtbl) ((dirtbl)->dir.dir_n)

#define GFS_ERR_FUNC(err) ((err)->func)
#define GFS_ERR_OBJ(err) ((err)->obj)
#define GFS_ERR_CODE(err) ((err)->code)

typedef Sint32 (*GfsTransFunc)(void* obj, Sint32 nsct);

typedef struct {
    Sint32 fid;
    CdcFile finfo;
    Sint32 sctsz;
    Sint32 nsct;
    Sint32 lstrm;
} GfsFinfo;

typedef struct {
    Sint32 bufno;
    Sint32 sctsz;
    Sint32 flt;
    CdcSubh subh;
    Sint32 fmode;
    Sint32 puid;
    Sint32 filepos;
    Sint32 sctpos;
    Sint32 sfad;
    Sint32 efad;
} GfsCdRsrc;

typedef struct {
    Sint32 fid;
    Sint32 filepos;
    Sint32 sctpos;
    Sint32 sctnum;
} GfsScsiRsrc;

typedef struct {
    void* data;
    Sint32 filepos;
    Sint32 sctpos;
    Sint32 sctnum;
} GfsMemRsrc;

typedef struct {
    Sint32 ftype;
    union {
        GfsCdRsrc cd;
        GfsScsiRsrc scsi;
        GfsMemRsrc mem;
    } rsrc;
} GfsDtsrc;

typedef struct {
    GfsFinfo finfo;
    GfsDtsrc dtsrc;
    Sint32 gmode;
    Sint32 stat;
    Sint32 sct;
    Sint32 sctcnt;
    Sint32 sctmax;
} GfsFlow;

typedef struct {
    void* data;
    Sint32 adlt;
    Sint32 len;
    Sint32 nsct;
    Bool use;
} GfsDataPack;

typedef GfsDataPack* GfdpHn;

typedef struct {
    void* buf;
    Sint32 size;
    Sint32 wp;
    GfdpHn dps;
    GfdpHn dpd;
    Sint32 tsctmax;
    Sint32 tsct;
    Sint32 tsctcnt;
    Sint32 tbytcnt;
    void* obj;
    GfsTransFunc tfunc;
    Sint32 unit;
    Bool active;
    Sint32 stat;
    Sint32 mode;
} GfsTrans;

typedef GfsTrans* GftrHn;

typedef struct {
    Bool used;
    Sint32 amode;
    Sint32 astat;
    GfsFlow flow;
    GfsTrans trans;
} GfsFile;

typedef GfsFile* GfsHn;

typedef Sint32 (*GfsTrFunc)(GfsHn gfs, Sint32 nsct);

typedef struct {
    CdcFile dirrec;
} GfsDirId;

typedef struct {
    CdcFile dirrec;
    Sint8 fname[GFS_FNAME_LEN];
} GfsDirName;

typedef struct {
    Sint32 type;
    Sint32 ndir;
    union {
        GfsDirId* dir_i;
        GfsDirName* dir_n;
    } dir;
} GfsDirTbl;

typedef void (*GfsErrFunc)(void* obj, Sint32 ec);

typedef struct {
    GfsErrFunc func;
    void* obj;
    Sint32 code;
} GfsErrStat;

Sint32 GFS_Init(Sint32 open_max, void* work, GfsDirTbl* dirtbl);
Sint32 GFS_LoadDir(Sint32 fid, GfsDirTbl* dirtbl);
Sint32 GFS_SetDir(GfsDirTbl* dirtbl);
Sint32 GFS_NameToId(Sint8* fname);
Sint8* GFS_IdToName(Sint32 fid);
Sint32 GFS_GetDirInfo(Sint32 fid, GfsDirId* dirrec);
void GFS_Reset(void);
GfsHn GFS_Open(Sint32 fid);
void GFS_Close(GfsHn gfs);
Sint32 GFS_Seek(GfsHn gfs, Sint32 ofs, Sint32 org);
Sint32 GFS_Tell(GfsHn gfs);
Bool GFS_IsEof(GfsHn gfs);
Sint32 GFS_ByteToSct(GfsHn gfs, Sint32 nbyte);
void GFS_GetFileSize(GfsHn gfs, Sint32* sctsz, Sint32* nsct, Sint32* lstsz);
void GFS_GetFileInfo(
    GfsHn gfs, Sint32* fid, Sint32* fn, Sint32* fsize, Sint32* atr);
Sint32 GFS_GetNumCdbuf(GfsHn gfs);
Sint32 GFS_Load(Sint32 fid, Sint32 ofs, void* buf, Sint32 bsize);
Sint32 GFS_Fread(GfsHn gfs, Sint32 nsct, void* buf, Sint32 bsize);
Sint32 GFS_NwFread(GfsHn gfs, Sint32 nsct, void* buf, Sint32 bsize);
Sint32 GFS_NwCdRead(GfsHn gfs, Sint32 nsct);
Bool GFS_NwIsComplete(GfsHn gfs);
Sint32 GFS_NwStop(GfsHn gfs);
void GFS_NwGetStat(GfsHn gfs, Sint32* amode, Sint32* ndata);
Sint32 GFS_NwExecOne(GfsHn gfs);
Sint32 GFS_NwExecServer(GfsHn* now_gfs);
Sint32 GFS_SetGmode(GfsHn gfs, Sint32 gmode);
Sint32 GFS_SetTmode(GfsHn gfs, Sint32 tmode);
Sint32 GFS_SetReadPara(GfsHn gfs, Sint32 nsct);
Sint32 GFS_SetTransPara(GfsHn gfs, Sint32 tsize);
void GFS_SetTrFunc(GfsHn gfs, GfsTrFunc func);
Uint32* GFS_StartTrans(GfsHn gfs, Sint32* dadr);
Sint32 GFS_CdMovePickup(GfsHn gfs);
void GFS_SetErrFunc(GfsErrFunc func, void* obj);
void GFS_GetErrStat(GfsErrStat* stat);
Sint32 GFS_ConvTno(Sint32 logtno);
Sint32 GFS_GetFad(Sint32 fid, Sint32 ofs);

#define GFS_OPEN_MAX 24
#define GFS_TBUF_NR 2
#define GFS_FTYPE_NR 3
#define GFS_SCTBUF_SIZ 2048
#define GFS_CDBBUF_NR 24
#define GFS_SELQ_MAX 24
#define GFS_FCONQ_MAX 24

typedef struct {
    Sint32 (*flowin)(GfsFlow*);
    void (*stopin)(GfsFlow*, Bool);
    Sint32 (*seek)(GfsFlow*, Sint32);
    Sint32 (*tell)(GfsFlow*);
} GfsFileFunc;

typedef struct {
    GfsHn access_file[GFS_OPEN_MAX];
    Sint32 nfile;
} GfsSvr;

typedef struct {
    GfsDirTbl dirtbl;
    Sint32 nfile;
} GfsDirMng;

typedef struct {
    Uint8 flt;
    Uint8 fmode;
    CdcSubh subh;
    Sint32 fad;
    Sint32 snum;
} GfcdSelQu;

typedef struct {
    Sint32 flt;
    Sint32 buf;
    Sint32 flnout;
} GfcdFconQu;

typedef struct {
    Sint8 use_buf[GFS_CDBBUF_NR];
    Sint8 use_filt[GFS_CDBBUF_NR];
    Bool use_pu;
    Sint32 tr_bufno;
    Sint32 puid;
    Sint32 timer;
    CdcStat stat;
    void (*func)(void*);
    void* obj;
    struct {
        Sint32 len;
        Sint32 stat;
        GfcdSelQu selq[GFS_SELQ_MAX];
    } tsk_setflt;
    struct {
        Sint32 len;
        Sint32 stat;
        GfcdFconQu fconq[GFS_FCONQ_MAX];
    } tsk_fltcon;
    struct {
        Sint32 stat;
        Sint32 flt;
    } tsk_setcon;
    struct {
        Sint32 stat;
        Sint32 bufno;
        Sint32 spos;
        Sint32 usct;
        Sint32 cnt;
        Sint32* nsct;
        Sint32* nbyte;
    } tsk_getlen;
    struct {
        Sint32 stat;
        Sint32 bufno;
        Sint32 sctpos;
        Sint32 nsct;
    } tsk_reqdat;
    struct {
        Sint32 stat;
        Sint32 bufno;
        Sint32 sctpos;
        Sint32 nsct;
    } tsk_delsct;
    struct {
        Sint32 stat;
        Sint32 dst;
        Sint32 src;
        Sint32 spos;
        Sint32 snum;
        Sint32 fmode;
    } tsk_movsct;
    struct {
        Sint32 stat;
        Sint16 fid;
        Sint16 work;
        Sint32* ndir;
    } tsk_chgdir;
} GfsCdbMng;

typedef struct {
    Sint32 openmax;
    GfsFileFunc functbl[GFS_FTYPE_NR];
    GfsSvr svr;
    GfsDirMng curdir;
    GfsHn pickup;
    Sint32 sfad;
    Sint32 efad;
    GfsHn trans;
    GfsErrStat error;
    Uint32 flags;
    Sint32 timer;
    GfsCdbMng cdb;
    GfsDataPack srcpk;
    GfsDataPack dstpk;
    Uint8 sect_buf[GFS_SCTBUF_SIZ];
    GfsFile file[1];
} GfsMng;

#endif
