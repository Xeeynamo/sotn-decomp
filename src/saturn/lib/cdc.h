#ifndef CDC_H
#define CDC_H

#include "xpt.h"

#define CDC_HIRQ_CMOK   0x0001
#define CDC_HIRQ_DRDY   0x0002
#define CDC_HIRQ_CSCT   0x0004
#define CDC_HIRQ_BFUL   0x0008
#define CDC_HIRQ_PEND   0x0010
#define CDC_HIRQ_DCHG   0x0020
#define CDC_HIRQ_ESEL   0x0040
#define CDC_HIRQ_EHST   0x0080
#define CDC_HIRQ_ECPY   0x0100
#define CDC_HIRQ_EFLS   0x0200
#define CDC_HIRQ_SCDQ   0x0400
#define CDC_HIRQ_MPED   0x0800
#define CDC_HIRQ_MPCM   0x1000
#define CDC_HIRQ_MPST   0x2000

#define CDC_SNUM_END    -1

#define CDC_NUL_SEL     0xff
#define CDC_NUL_FID     -1

#define CDC_PM_DFL          0x00
#define CDC_PM_REP_NOCHG    0x7f
#define CDC_PM_PIC_NOCHG    0x80
#define CDC_PM_NOCHG        -1

#define CDC_ATR_DIRFG   0x02
#define CDC_ATR_FORM1   0x08
#define CDC_ATR_FORM2   0x10
#define CDC_ATR_INTLV   0x20
#define CDC_ATR_CDDA    0x40
#define CDC_ATR_DIRXA   0x80

#define CDC_STC_MSK     0x0f

enum CdcErrCode {
    CDC_ERR_OK = OK,

    CDC_ERR_CMDBUSY=-1,
    CDC_ERR_CMDNG  =-2,
    CDC_ERR_TMOUT  =-3,
    CDC_ERR_PUT    =-4,
    CDC_ERR_REJECT =-5,
    CDC_ERR_WAIT   =-6,
    CDC_ERR_TRNS   =-7,
    CDC_ERR_PERI   =-8
};

enum CdcStatus {
    CDC_ST_BUSY     = 0x00,
    CDC_ST_PAUSE    = 0x01,
    CDC_ST_STANDBY  = 0x02,
    CDC_ST_PLAY     = 0x03,
    CDC_ST_SEEK     = 0x04,
    CDC_ST_SCAN     = 0x05,
    CDC_ST_OPEN     = 0x06,
    CDC_ST_NODISC   = 0x07,
    CDC_ST_RETRY    = 0x08,
    CDC_ST_ERROR    = 0x09,
    CDC_ST_FATAL    = 0x0a,

    CDC_ST_PERI     = 0x20,
    CDC_ST_TRNS     = 0x40,
    CDC_ST_WAIT     = 0x80,
    CDC_ST_REJECT   = 0xff
};

enum CdcPosType {
    CDC_PTYPE_DFL,
    CDC_PTYPE_FAD,
    CDC_PTYPE_TNO,
    CDC_PTYPE_NOCHG,

    CDC_PTYPE_END
};

enum CdcDrdyType {
    CDC_DRDY_GET,
    CDC_DRDY_PUT,

    CDC_DRDY_END
};

enum CdcSctLen {
    CDC_SLEN_2048  = 0,
    CDC_SLEN_2336  = 1,
    CDC_SLEN_2340  = 2,
    CDC_SLEN_2352  = 3,
    CDC_SLEN_NOCHG = -1
};

#define CDC_STAT_STATUS(stat)       ((stat)->status)
#define CDC_STAT_FLGREP(stat)       ((stat)->report.flgrep)
#define CDC_STAT_CTLADR(stat)       ((stat)->report.ctladr)
#define CDC_STAT_TNO(stat)          ((stat)->report.tno)
#define CDC_STAT_IDX(stat)          ((stat)->report.idx)
#define CDC_STAT_FAD(stat)          ((stat)->report.fad)

#define CDC_POS_PTYPE(pos)          ((pos)->ptype)
#define CDC_POS_FAD(pos)            ((pos)->pbody.fad)
#define CDC_POS_TNO(pos)            ((pos)->pbody.trkidx.tno)
#define CDC_POS_IDX(pos)            ((pos)->pbody.trkidx.idx)

#define CDC_PLY_START(ply)          ((ply)->start)
#define CDC_PLY_END(ply)            ((ply)->end)
#define CDC_PLY_PMODE(ply)          ((ply)->pmode)

#define CDC_PLY_STYPE(ply)          CDC_POS_PTYPE(&CDC_PLY_START(ply))
#define CDC_PLY_SFAD(ply)           CDC_POS_FAD(&CDC_PLY_START(ply))
#define CDC_PLY_STNO(ply)           CDC_POS_TNO(&CDC_PLY_START(ply))
#define CDC_PLY_SIDX(ply)           CDC_POS_IDX(&CDC_PLY_START(ply))

#define CDC_PLY_ETYPE(ply)          CDC_POS_PTYPE(&CDC_PLY_END(ply))
#define CDC_PLY_EFAS(ply)           CDC_POS_FAD(&CDC_PLY_END(ply))
#define CDC_PLY_ETNO(ply)           CDC_POS_TNO(&CDC_PLY_END(ply))
#define CDC_PLY_EIDX(ply)           CDC_POS_IDX(&CDC_PLY_END(ply))

#define CDC_SUBH_FN(subh)           ((subh)->fn)
#define CDC_SUBH_CN(subh)           ((subh)->cn)
#define CDC_SUBH_SMMSK(subh)        ((subh)->smmsk)
#define CDC_SUBH_SMVAL(subh)        ((subh)->smval)
#define CDC_SUBH_CIMSK(subh)        ((subh)->cimsk)
#define CDC_SUBH_CIVAL(subh)        ((subh)->cival)

#define CDC_FILE_FAD(file)          ((file)->fad)
#define CDC_FILE_SIZE(file)         ((file)->size)
#define CDC_FILE_UNIT(file)         ((file)->unit)
#define CDC_FILE_GAP(file)          ((file)->gap)
#define CDC_FILE_FN(file)           ((file)->fn)
#define CDC_FILE_ATR(file)          ((file)->atr)

#define CDC_GET_STC(stat)       (CDC_STAT_STATUS(stat) & CDC_STC_MSK)

typedef struct {
    Uint8   status;
    struct {
        Uint8   flgrep;
        Uint8   ctladr;
        Uint8   tno;
        Uint8   idx;
        Sint32  fad;
    } report;
} CdcStat;

typedef struct {
    Uint8   hflag;
    Uint8   ver;
    Uint8   mpver;
    Uint8   drv;
    Uint8   rev;
} CdcHw;

typedef struct {
    Sint32 ptype;
    union {
        Sint32 fad;
        struct {
            Uint8 tno;
            Uint8 idx;
        } trkidx;
    } pbody;
} CdcPos;

typedef struct {
    CdcPos  start;
    CdcPos  end;
    Uint8   pmode;
} CdcPly;

typedef struct {
    Uint8   fn;
    Uint8   cn;
    Uint8   smmsk;
    Uint8   smval;
    Uint8   cimsk;
    Uint8   cival;
} CdcSubh;

typedef struct {
    Sint32  fad;
    Uint8   fn;
    Uint8   cn;
    Uint8   sm;
    Uint8   ci;
} CdcSct;

typedef struct {
    Sint32  fad;
    Sint32  size;
    Uint8   unit;
    Uint8   gap;
    Uint8   fn;
    Uint8   atr;
} CdcFile;

/* cdc_cmn.c */
Sint32 CDC_GetCurStat(CdcStat *stat);
Sint32 CDC_GetLastStat(CdcStat *stat);
Sint32 CDC_GetHwInfo(CdcHw *hw);
Sint32 CDC_TgetToc(Uint32 *toc);
Sint32 CDC_GetSes(Sint32 sesno, Uint32 *ses);
Sint32 CDC_CdInit(Sint32 iflag, Sint32 stnby, Sint32 ecc, Sint32 retry);
Sint32 CDC_CdOpen(void);
Sint32 CDC_DataReady(Sint32 dtype);
Sint32 CDC_DataEnd(Sint32 *cdwnum);
Sint32 CDC_GetPeriStat(CdcStat *stat);

/* cdc_drv.c */
Sint32 CDC_CdPlay(CdcPly *ply);
Sint32 CDC_CdSeek(CdcPos *pos);
Sint32 CDC_CdScan(Sint32 scandir);

/* cdc_scd.c */
Sint32 CDC_TgetScdQch(Uint16 *qcode);
Sint32 CDC_TgetScdRwch(Uint16 *rwcode, Sint32 *scdflag);

/* cdc_dev.c */
Sint32 CDC_CdSetCon(Sint32 filtno);
Sint32 CDC_CdGetCon(Sint32 *filtno);
Sint32 CDC_CdGetLastBuf(Sint32 *bufno);

/* cdc_sel.c */
Sint32 CDC_SetFiltRange(Sint32 filtno, Sint32 fad, Sint32 fasnum);
Sint32 CDC_GetFiltRange(Sint32 filtno, Sint32 *fad, Sint32 *fasnum);
Sint32 CDC_SetFiltSubh(Sint32 filtno, CdcSubh *subh);
Sint32 CDC_GetFiltSubh(Sint32 filtno, CdcSubh *subh);
Sint32 CDC_SetFiltMode(Sint32 filtno, Sint32 fmode);
Sint32 CDC_GetFiltMode(Sint32 filtno, Sint32 *fmode);
Sint32 CDC_SetFiltCon(Sint32 filtno, Sint32 cflag, Sint32 bufno, Sint32 flnout);
Sint32 CDC_GetFiltCon(Sint32 filtno, Sint32 *bufno, Sint32 *flnout);
Sint32 CDC_ResetSelector(Sint32 rflag, Sint32 bufno);

/* cdc_bif.c */
Sint32 CDC_GetBufSiz(Sint32 *totalsiz, Sint32 *bufnum, Sint32 *freesiz);
Sint32 CDC_GetSctNum(Sint32 bufno, Sint32 *snum);
Sint32 CDC_CalActSiz(Sint32 bufno, Sint32 spos, Sint32 snum);
Sint32 CDC_GetActSiz(Sint32 *actwnum);
Sint32 CDC_GetSctInfo(Sint32 bufno, Sint32 spos, CdcSct *sct);
Sint32 CDC_ExeFadSearch(Sint32 bufno, Sint32 spos, Sint32 fad);
Sint32 CDC_GetFadSearch(Sint32 *bufno, Sint32 *spos, Sint32 *fad);

/* cdc_bio.c */
Sint32 CDC_SetSctLen(Sint32 getslen, Sint32 putslen);
Sint32 CDC_GetSctData(Sint32 bufno, Sint32 spos, Sint32 snum);
Sint32 CDC_DelSctData(Sint32 bufno, Sint32 spos, Sint32 snum);
Sint32 CDC_GetdelSctData(Sint32 bufno, Sint32 spos, Sint32 snum);
Sint32 CDC_PutSctData(Sint32 filtno, Sint32 snum);
Sint32 CDC_CopySctData(Sint32 srcbn, Sint32 spos, Sint32 snum, Sint32 dstfln);
Sint32 CDC_MoveSctData(Sint32 srcbn, Sint32 spos, Sint32 snum, Sint32 dstfln);
Sint32 CDC_GetCopyErr(Sint32 *cpyerr);

/* cdc_cfs.c */
Sint32 CDC_ChgDir(Sint32 filtno, Sint32 fid);
Sint32 CDC_ReadDir(Sint32 filtno, Sint32 fid);
Sint32 CDC_GetFileScope(Sint32 *fid, Sint32 *infnum, Bool *drend);
Sint32 CDC_TgetFileInfo(Sint32 fid, CdcFile *file);
Sint32 CDC_ReadFile(Sint32 filtno, Sint32 fid, Sint32 offset);
Sint32 CDC_AbortFile(void);

/* cdc_reg.c */
Uint32 *CDC_GetDataPtr(void);
Sint32 CDC_GetHirqReq(void);
void CDC_ClrHirqReq(Sint32 bitpat);
Sint32 CDC_GetHirqMsk(void);
void CDC_SetHirqMsk(Sint32 bitpat);
Uint32 *CDC_GetMpegPtr(void);

#endif