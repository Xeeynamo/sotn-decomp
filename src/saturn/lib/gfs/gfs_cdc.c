#include "../../sattypes.h"
#include "../../inc_asm.h"

#include "gfs.h"
#include "gfs_cdc.h"
#include "gfs_def.h"

#define SCDQ_COUNT_SEC 60
#define TMOUT_DRV_COUNT (10 * SCDQ_COUNT_SEC)

#define NOBODY -1

#define CDBLK_SWRST 0x00
#define SUBCODE_DECODE 0x00
#define USE_MODE2 0x00
#define FORM2_RDRETRY 0x00
#define HIGH_SPEED 0x00
#define NCHG_INIT_FLAG 0x00

#define INIT_FLAG                                                              \
    (CDBLK_SWRST | SUBCODE_DECODE | USE_MODE2 | FORM2_RDRETRY | HIGH_SPEED |   \
     NCHG_INIT_FLAG)

#define DEF_STBYTIM 0x0000
#define DEF_ECC 0x04
#define DEF_RETRY 0x0f

#define RESET_FLG 0xfc

#define MAX_CMD_PER_EXEC 30

#define FLTCON_BUF_SET 1
#define FLTCON_FLN_SET 2

#define TRREG_UNUSED (-1)

#define SCDQ_TMOUT_COUNT (12186 * 2)

#define PAUSE_TMOUT_COUNT 433333

enum CdbResStat { UNUSED, INUSE };

enum TaskStatus {
    GFCD_TSK_READY,
    GFCD_TSK_STAT1,
    GFCD_TSK_STAT2,
    GFCD_TSK_STAT3,
    GFCD_TSK_STAT4,
    GFCD_TSK_STAT5
};

enum TskId {
    TSK_ID_SETFLT = 0,
    TSK_ID_SETCON,
    TSK_ID_GETLEN,
    TSK_ID_REQDAT,
    TSK_ID_DELSCT,
    TSK_ID_MOVSCT,
    TSK_ID_FLTCON,
    TSK_ID_CHGDIR,
    TSK_ID_END
};

#define GFS_WORD_BYTE(word) ((word) * 2)

#define IS_ROM(toc) ((toc) & 0x40000000)

#define CDBMNG_USEBUF(mng, i) ((mng)->use_buf[i])
#define CDBMNG_USEFILT(mng, i) ((mng)->use_filt[i])
#define CDBMNG_USEPU(mng) ((mng)->use_pu)
#define CDBMNG_TRBUFNO(mng) ((mng)->tr_bufno)
#define CDBMNG_PUID(mng) ((mng)->puid)
#define CDBMNG_STAT(mng) ((mng)->stat)
#define CDBMNG_TIMER(mng) ((mng)->timer)
#define CDBMNG_FUNC(mng) ((mng)->func)
#define CDBMNG_OBJ(mng) ((mng)->obj)

#define TSK_SETFLT_LEN(mng) ((mng)->tsk_setflt.len)
#define TSK_SETFLT_STAT(mng) ((mng)->tsk_setflt.stat)
#define TSK_SETFLT_QELT(mng, i) ((mng)->tsk_setflt.selq[i])
#define TSK_SETFLT_FLT(mng, i) (TSK_SETFLT_QELT(mng, i).flt)
#define TSK_SETFLT_FMODE(mng, i) (TSK_SETFLT_QELT(mng, i).fmode)
#define TSK_SETFLT_SUBH(mng, i) (TSK_SETFLT_QELT(mng, i).subh)
#define TSK_SETFLT_FAD(mng, i) (TSK_SETFLT_QELT(mng, i).fad)
#define TSK_SETFLT_SNUM(mng, i) (TSK_SETFLT_QELT(mng, i).snum)

#define TSK_SETCON_STAT(mng) ((mng)->tsk_setcon.stat)
#define TSK_SETCON_FLT(mng) ((mng)->tsk_setcon.flt)

#define TSK_GETLEN_STAT(mng) ((mng)->tsk_getlen.stat)
#define TSK_GETLEN_BUFNO(mng) ((mng)->tsk_getlen.bufno)
#define TSK_GETLEN_SPOS(mng) ((mng)->tsk_getlen.spos)
#define TSK_GETLEN_USCT(mng) ((mng)->tsk_getlen.usct)
#define TSK_GETLEN_CNT(mng) ((mng)->tsk_getlen.cnt)
#define TSK_GETLEN_NSCT(mng) ((mng)->tsk_getlen.nsct)
#define TSK_GETLEN_NBYTE(mng) ((mng)->tsk_getlen.nbyte)

#define TSK_REQDAT_STAT(mng) ((mng)->tsk_reqdat.stat)
#define TSK_REQDAT_BUFNO(mng) ((mng)->tsk_reqdat.bufno)
#define TSK_REQDAT_SCTPOS(mng) ((mng)->tsk_reqdat.sctpos)
#define TSK_REQDAT_NSCT(mng) ((mng)->tsk_reqdat.nsct)

#define TSK_DELSCT_STAT(mng) ((mng)->tsk_delsct.stat)
#define TSK_DELSCT_BUFNO(mng) ((mng)->tsk_delsct.bufno)
#define TSK_DELSCT_SCTPOS(mng) ((mng)->tsk_delsct.sctpos)
#define TSK_DELSCT_NSCT(mng) ((mng)->tsk_delsct.nsct)

#define TSK_MOVSCT_STAT(mng) ((mng)->tsk_movsct.stat)
#define TSK_MOVSCT_DST(mng) ((mng)->tsk_movsct.dst)
#define TSK_MOVSCT_SRC(mng) ((mng)->tsk_movsct.src)
#define TSK_MOVSCT_SPOS(mng) ((mng)->tsk_movsct.spos)
#define TSK_MOVSCT_SNUM(mng) ((mng)->tsk_movsct.snum)
#define TSK_MOVSCT_FMODE(mng) ((mng)->tsk_movsct.fmode)

#define TSK_CHGDIR_STAT(mng) ((mng)->tsk_chgdir.stat)
#define TSK_CHGDIR_FID(mng) ((mng)->tsk_chgdir.fid)
#define TSK_CHGDIR_WORK(mng) ((mng)->tsk_chgdir.work)
#define TSK_CHGDIR_NDIR(mng) ((mng)->tsk_chgdir.ndir)

#define TSK_FLTCON_LEN(mng) ((mng)->tsk_fltcon.len)
#define TSK_FLTCON_STAT(mng) ((mng)->tsk_fltcon.stat)
#define TSK_FLTCON_QELT(mng, i) ((mng)->tsk_fltcon.fconq[i])
#define TSK_FLTCON_FLT(mng, i) (TSK_FLTCON_QELT(mng, i).flt)
#define TSK_FLTCON_BUF(mng, i) (TSK_FLTCON_QELT(mng, i).buf)
#define TSK_FLTCON_FLNOUT(mng, i) (TSK_FLTCON_QELT(mng, i).flnout)

typedef union {
    Uint8 nses[4];
    Uint32 xfad;
} GfcdSes;

#define GFCD_SES_NSES(ses) ((ses)->nses[0])
#define GFCD_SES_SFAD(ses) ((ses)->xfad & 0x00ffffff)

GFS_LOCAL Bool gfcd_isIdleTask(Sint32 tsk);
GFS_LOCAL Sint32 gfcd_doTask(Sint32 tsk, Sint32* ncmd);
GFS_LOCAL Sint32 gfcd_doSetFiltTsk(Sint32* ncmd);
GFS_LOCAL Sint32 gfcd_doSetConTsk(Sint32* ncmd);
GFS_LOCAL Sint32 gfcd_doGetLenDataTsk(Sint32* ncmd);
GFS_LOCAL Sint32 gfcd_doReqDataTsk(Sint32* ncmd);
GFS_LOCAL Sint32 gfcd_doDelSctDataTsk(Sint32* ncmd);
GFS_LOCAL Sint32 gfcd_doMoveSctTsk(Sint32* ncmd);
GFS_LOCAL Sint32 gfcd_doChgDirTsk(Sint32* ncmd);
GFS_LOCAL Sint32 gfcd_doSetFiltConTsk(Sint32* ncmd);
GFS_LOCAL Bool gfcd_checkEflag(Sint32 mask);
GFS_LOCAL void gfcd_initCdbMng(void);
GFS_LOCAL void gfcd_setStat(void);

extern GfsCdbMng* gfcd_work;
extern Sint32 gfcd_playflag;

// 0x0601F974
void GFCD_SetCdbfs(Bool use_cdbfs) {
    if (use_cdbfs) {
        CDBMNG_USEBUF(gfcd_work, GFCD_SYS_SEL) = INUSE;
        CDBMNG_USEFILT(gfcd_work, GFCD_SYS_SEL) = INUSE;
    } else {
        CDBMNG_USEBUF(gfcd_work, GFCD_SYS_SEL) = UNUSED;
        CDBMNG_USEFILT(gfcd_work, GFCD_SYS_SEL) = UNUSED;
    }
}

// 0x0601F9A0
Sint32 GFCD_Init(GfsCdbMng* work, Bool use_cdbfs) {
    Sint32 tm_count;
    Bool ok_flag;
    Uint32* toc_tbl;
    Sint32 ret;
    CdcStat stat;
    GfcdSes ses;

    gfcd_work = work;
    gfcd_playflag = FALSE;
    gfcd_fatal_err = GFCD_ERR_OK;
    gfcd_initCdbMng();
    GFCD_SetCdbfs(use_cdbfs);
    GFCD_GetStat(&stat);
    if (gfcd_fatal_err != GFCD_ERR_OK) {
        return gfcd_fatal_err;
    }
    if (CDC_GET_STC(&stat) == CDC_ST_ERROR) {
        return GFCD_ERR_CDC;
    }

    CDC_AbortFile();

    ret = CDC_CdInit(INIT_FLAG, DEF_STBYTIM, DEF_ECC, DEF_RETRY);
    if (ret != CDC_ERR_OK) {
        return GFCD_ERR_NOCDBLK;
    }

    for (tm_count = 0;; tm_count++) {
        ret = CDC_SetSctLen(CDC_SLEN_2048, CDC_SLEN_NOCHG);
        if (ret == CDC_ERR_OK) {
            break;
        }
        if ((ret != CDC_ERR_CMDBUSY) || (tm_count > GFCD_TMOUT_COUNT)) {
            return GFCD_ERR_NOCDBLK;
        }
    }
    CDBMNG_TIMER(gfcd_work) = GFCD_TMOUT_COUNT;
    while (gfcd_checkEflag(CDC_HIRQ_ESEL) == FALSE) {
        if (--CDBMNG_TIMER(gfcd_work) == 0) {
            return GFCD_ERR_NOCDBLK;
        }
    }
    CDBMNG_TIMER(gfcd_work) = GFCD_NO_TMOUT;

    CDC_ClrHirqReq(~(CDC_HIRQ_PEND | CDC_HIRQ_BFUL));

    tm_count = 0;
    ok_flag = FALSE;
    while (ok_flag == FALSE) {
        if (gfcd_checkEflag(CDC_HIRQ_SCDQ) == FALSE) {
            continue;
        }
        CDC_ClrHirqReq(~CDC_HIRQ_SCDQ);
        ++tm_count;
        if (tm_count > TMOUT_DRV_COUNT) {
            return GFCD_ERR_NOCDBLK;
        }
        GFCD_GetStat(&stat);
        if (gfcd_fatal_err != GFCD_ERR_OK) {
            return gfcd_fatal_err;
        }
        switch (CDC_GET_STC(&stat)) {
        case CDC_ST_ERROR:
            return GFCD_ERR_CDC;
        case CDC_ST_PAUSE:
        case CDC_ST_STANDBY:
            ok_flag = TRUE;
            break;
        }
    }
    CDC_DataEnd(&ret);

    toc_tbl = (Uint32*)MNG_SECTBUF(gfs_mng_ptr);
    ret = CDC_TgetToc(toc_tbl);
    if (ret != CDC_ERR_OK) {
        return GFCD_ERR_NOCDBLK;
    }
    CDC_GetSes(0, (Uint32*)&ses);
    CDC_GetSes(GFCD_SES_NSES(&ses), (Uint32*)&ses);
    if (IS_ROM(toc_tbl[GFCD_SES_NSES(&ses) - 1]) == FALSE) {
        return GFCD_ERR_CDROM;
    }
    ret = CDC_ResetSelector(RESET_FLG, CDC_NUL_SEL);
    CDBMNG_TIMER(gfcd_work) = GFCD_TMOUT_COUNT;
    while (gfcd_checkEflag(CDC_HIRQ_ESEL) == FALSE) {
        if (--CDBMNG_TIMER(gfcd_work) == 0) {
            return GFCD_ERR_NOCDBLK;
        }
    }
    CDBMNG_TIMER(gfcd_work) = GFCD_NO_TMOUT;
    GFCD_GetStat(&CDBMNG_STAT(gfcd_work));
    return gfcd_fatal_err;
}

// 0x0601FB98
Sint32 GFCD_AllocFilt(Sint32* flt_no) {
    Sint32 i;

    for (i = 0; i < GFS_CDBBUF_NR; ++i) {
        if (CDBMNG_USEFILT(gfcd_work, i) == UNUSED) {
            CDBMNG_USEFILT(gfcd_work, i) = INUSE;
            *flt_no = i;
            return GFCD_ERR_OK;
        }
    }
    *flt_no = -1;
    return GFCD_ERR_NOFILT;
}

// 0x0601FBD0
Sint32 GFCD_FreeFilt(Sint32 flt_no) {
    if ((flt_no < 0) || (GFS_CDBBUF_NR <= flt_no)) {
        return GFCD_ERR_RANGE;
    }
    if (CDBMNG_USEFILT(gfcd_work, flt_no) != INUSE) {
        return GFCD_ERR_UNUSE;
    }
    CDBMNG_USEFILT(gfcd_work, flt_no) = UNUSED;
    return GFCD_ERR_OK;
}

// 0x0601FC00
Sint32 GFCD_AllocBuf(Sint32* buf_no) {
    Sint32 i;

    for (i = 0; i < GFS_CDBBUF_NR; ++i) {
        if (CDBMNG_USEBUF(gfcd_work, i) == UNUSED) {
            CDBMNG_USEBUF(gfcd_work, i) = INUSE;
            *buf_no = i;
            return GFCD_ERR_OK;
        }
    }
    *buf_no = -1;
    return GFCD_ERR_NOBUF;
}

// 0x0601FC34
Sint32 GFCD_FreeBuf(Sint32 buf_no) {
    Sint32 err;

    if (gfcd_fatal_err == GFCD_ERR_FATAL) {
        gfcd_fatal_err = GFCD_ERR_OK;
    }
    if ((buf_no < 0) || (GFS_CDBBUF_NR <= buf_no)) {
        return GFCD_ERR_RANGE;
    }
    if (CDBMNG_USEBUF(gfcd_work, buf_no) != INUSE) {
        return GFCD_ERR_UNUSE;
    }
    GFCD_DelSctData(buf_no, 0, CDC_SNUM_END);
    GFCD_SetTimer(GFCD_TMOUT_COUNT);
    for (;;) {
        err = GFCD_ExecServer();
        if (err == GFCD_SVR_TMOUT) {
            return GFCD_ERR_TMOUT;
        } else if (err == GFCD_SVR_ERROR) {
            return GFCD_ERR_FATAL;
        }
        if (GFCD_CheckDelSctData(buf_no) == TRUE) {
            break;
        }
    }
    GFCD_SetTimer(GFCD_NO_TMOUT);
    CDBMNG_USEBUF(gfcd_work, buf_no) = UNUSED;
    return GFCD_ERR_OK;
}

// 0x0601FCD4
Sint32 GFCD_GetBaseFad(void) {
    GfcdSes ses;

    CDC_GetSes(0, (Uint32*)&ses);
    CDC_GetSes(GFCD_SES_NSES(&ses), (Uint32*)&ses);
    return GFCD_SES_SFAD(&ses);
}

// 0x0601FD08
Sint32 GFCD_GetPickup(void) {
    if (CDBMNG_USEPU(gfcd_work) == INUSE) {
        return GFCD_ERR_INUSE;
    }
    CDBMNG_USEPU(gfcd_work) = INUSE;
    ++CDBMNG_PUID(gfcd_work);
    if (CDBMNG_PUID(gfcd_work) < 0) {
        CDBMNG_PUID(gfcd_work) = 0;
    }
    return CDBMNG_PUID(gfcd_work);
}

// 0x0601FD3C
Sint32 GFCD_UngetPickup(Sint32 puid) {
    if (CDBMNG_USEPU(gfcd_work) == UNUSED) {
        return GFCD_ERR_UNUSE;
    }
    if (CDBMNG_PUID(gfcd_work) != puid) {
        return GFCD_ERR_NOTOWNER;
    }
    CDBMNG_USEPU(gfcd_work) = UNUSED;
    return GFCD_ERR_OK;
}

// 0x0601FD68
Sint32 GFCD_IsPuOwner(Sint32 puid) {
    if (CDBMNG_USEPU(gfcd_work) == UNUSED) {
        return FALSE;
    }
    return (CDBMNG_PUID(gfcd_work) == puid) ? TRUE : FALSE;
}

// 0x0601FD8C
Sint32 GFCD_SetFilt(
    Sint32 flt, Sint32 fmode, CdcSubh* subh, Sint32 fad, Sint32 snum) {
    Sint32 ncmd;
    Sint32 len = TSK_SETFLT_LEN(gfcd_work);

    if (CDBMNG_USEFILT(gfcd_work, flt) != INUSE) {
        return GFCD_ERR_UNUSE;
    }
    if (len >= GFS_SELQ_MAX) {
        return GFCD_ERR_QFULL;
    }
    if (TSK_SETFLT_STAT(gfcd_work) == GFCD_TSK_READY) {
        TSK_SETFLT_STAT(gfcd_work) = GFCD_TSK_STAT1;
    }
    TSK_SETFLT_FLT(gfcd_work, len) = flt;
    TSK_SETFLT_FMODE(gfcd_work, len) = fmode;
    TSK_SETFLT_SUBH(gfcd_work, len) = *subh;
    TSK_SETFLT_FAD(gfcd_work, len) = fad;
    TSK_SETFLT_SNUM(gfcd_work, len) = snum;
    ++TSK_SETFLT_LEN(gfcd_work);
    gfcd_doSetFiltTsk(&ncmd);
    return GFCD_ERR_OK;
}

// 0x0601FE4C
Sint32 GFCD_GetFilt(Sint32 flt, Sint32* fmode, CdcSubh* subh) {
    Sint32 ret;

    ret = CDC_GetFiltMode(flt, fmode);
    if (ret != CDC_ERR_OK) {
        return GFCD_ERR_CDC;
    }
    ret = CDC_GetFiltSubh(flt, subh);
    if (ret != CDC_ERR_OK) {
        return GFCD_ERR_CDC;
    }
    gfcd_setStat();
    return GFCD_ERR_OK;
}

// 0x0601FE94
Sint32 GFCD_SetCon(Sint32 flt, Sint32 puid) {
    Sint32 ncmd;

    if ((flt != CDC_NUL_SEL) && (CDBMNG_USEFILT(gfcd_work, flt) != INUSE)) {
        return GFCD_ERR_UNUSE;
    }
    if (CDBMNG_PUID(gfcd_work) != puid) {
        return GFCD_ERR_NOTOWNER;
    }
    TSK_SETCON_STAT(gfcd_work) = GFCD_TSK_STAT1;
    TSK_SETCON_FLT(gfcd_work) = flt;
    gfcd_doSetConTsk(&ncmd);
    return GFCD_ERR_OK;
}

// 0x0601FEEC
Sint32 GFCD_Play(CdcPly* pinfo, Sint32 puid) {
    CdcStat stat;

    if (CDBMNG_PUID(gfcd_work) != puid) {
        return GFCD_ERR_NOTOWNER;
    }
    GFCD_GetStat(&stat);
    if (gfcd_fatal_err != GFCD_ERR_OK) {
        return gfcd_fatal_err;
    }

    CDC_ClrHirqReq(~(CDC_HIRQ_PEND | CDC_HIRQ_CSCT));
    CDC_CdPlay(pinfo);
    gfcd_playflag = TRUE;
    return GFCD_ERR_OK;
}

// 0x0601FF4C
Sint32 GFCD_GetLenData(
    Sint32 bufno, Sint32 spos, Sint32 usct, Sint32* nsct, Sint32* nbyte) {
    Sint32 ncmd;

    if (TSK_GETLEN_STAT(gfcd_work) != GFCD_TSK_READY) {
        return GFCD_ERR_WAIT;
    }
    TSK_GETLEN_STAT(gfcd_work) = GFCD_TSK_STAT1;
    TSK_GETLEN_BUFNO(gfcd_work) = bufno;
    TSK_GETLEN_SPOS(gfcd_work) = spos;
    TSK_GETLEN_USCT(gfcd_work) = usct;
    TSK_GETLEN_CNT(gfcd_work) = 0;
    TSK_GETLEN_NSCT(gfcd_work) = nsct;
    TSK_GETLEN_NBYTE(gfcd_work) = nbyte;
    gfcd_doGetLenDataTsk(&ncmd);
    return GFCD_ERR_OK;
}

// 0x0601FFB0
Sint32 GFCD_ReqData(Sint32 bufno, Sint32 sctpos, Sint32 nsct) {
    Sint32 ncmd;

    if (TSK_REQDAT_STAT(gfcd_work) != GFCD_TSK_READY) {
        return GFCD_ERR_WAIT;
    }
    if (CDBMNG_TRBUFNO(gfcd_work) != TRREG_UNUSED) {
        return GFCD_ERR_INUSE;
    }
    CDBMNG_TRBUFNO(gfcd_work) = bufno;
    TSK_REQDAT_STAT(gfcd_work) = GFCD_TSK_STAT1;
    TSK_REQDAT_BUFNO(gfcd_work) = bufno;
    TSK_REQDAT_SCTPOS(gfcd_work) = sctpos;
    TSK_REQDAT_NSCT(gfcd_work) = nsct;
    gfcd_doReqDataTsk(&ncmd);
    return GFCD_ERR_OK;
}

// 0x0602000C
Sint32 GFCD_EndData(Sint32* nsct) {
    Sint32 ret;

    if (CDBMNG_TRBUFNO(gfcd_work) == TRREG_UNUSED) {
        return GFCD_ERR_UNUSE;
    }
    ret = CDC_DataEnd(nsct);
    CDBMNG_TRBUFNO(gfcd_work) = TRREG_UNUSED;
    if (ret != CDC_ERR_OK) {
        return GFCD_ERR_CDC;
    }
    gfcd_setStat();
    return GFCD_ERR_OK;
}

// 0x06020054
Sint32 GFCD_DelSctData(Sint32 bufno, Sint32 sctpos, Sint32 nsct) {
    Sint32 ncmd;

    if (TSK_DELSCT_STAT(gfcd_work) != GFCD_TSK_READY) {
        return GFCD_ERR_WAIT;
    }
    if (CDBMNG_TRBUFNO(gfcd_work) == bufno) {
        return GFCD_ERR_INUSE;
    }
    TSK_DELSCT_STAT(gfcd_work) = GFCD_TSK_STAT1;
    TSK_DELSCT_BUFNO(gfcd_work) = bufno;
    TSK_DELSCT_SCTPOS(gfcd_work) = sctpos;
    TSK_DELSCT_NSCT(gfcd_work) = nsct;
    gfcd_doDelSctDataTsk(&ncmd);
    return GFCD_ERR_OK;
}

// 0x060200A8
Bool GFCD_CheckDelSctData(Sint32 bufno) {
    if ((TSK_DELSCT_STAT(gfcd_work) != GFCD_TSK_READY) &&
        (TSK_DELSCT_BUFNO(gfcd_work) == bufno)) {
        return FALSE;
    }
    return TRUE;
}

// 0x060200D4
Sint32 GFCD_GetStat(CdcStat* stat) {
    Sint32 ret;
    Sint32 hirq;
    CdcPos pos;

    if (gfcd_playflag == TRUE) {
        ret = CDC_ERR_PERI;
        gfcd_playflag = FALSE;
    } else {
        ret = CDC_GetPeriStat(stat);
    }
    if (ret != CDC_ERR_OK) {
        CDC_GetCurStat(stat);
    }

    hirq = CDC_GetHirqReq();
    if (hirq & CDC_HIRQ_DCHG) {
        gfcd_fatal_err = GFCD_ERR_OPEN;
    } else {
        switch (CDC_GET_STC(stat)) {
        case CDC_ST_OPEN:
            gfcd_fatal_err = GFCD_ERR_OPEN;
            break;
        case CDC_ST_NODISC:
            gfcd_fatal_err = GFCD_ERR_NODISC;
            break;
        case CDC_ST_FATAL:
            gfcd_fatal_err = GFCD_ERR_FATAL;
            CDC_POS_PTYPE(&pos) = CDC_PTYPE_DFL;
            CDC_CdSeek(&pos);
            GFCD_WaitScdqFlag();
            GFCD_WaitScdqFlag();
            break;
        default:
            break;
        }
    }
    return hirq;
}

// 0x06020188
Sint32 GFCD_MovePickup(CdcPos* pos, Sint32 puid) {
    CdcStat stat;

    if (CDBMNG_PUID(gfcd_work) != puid) {
        return GFCD_ERR_NOTOWNER;
    }
    GFCD_GetStat(&stat);
    if (gfcd_fatal_err != GFCD_ERR_OK) {
        return gfcd_fatal_err;
    }
    CDC_CdSeek(pos);
    return GFCD_ERR_OK;
}

// 0x060201D4
Sint32 GFCD_MoveSctData(Sint32 dst, Sint32 src, Sint32 spos, Sint32 snum) {
    Sint32 ncmd;

    if ((CDBMNG_USEFILT(gfcd_work, dst) == UNUSED) ||
        (CDBMNG_USEFILT(gfcd_work, src) == UNUSED)) {
        return GFCD_ERR_UNUSE;
    }
    if (TSK_MOVSCT_STAT(gfcd_work) != GFCD_TSK_READY) {
        return GFCD_ERR_WAIT;
    }
    TSK_MOVSCT_STAT(gfcd_work) = GFCD_TSK_STAT1;
    TSK_MOVSCT_DST(gfcd_work) = dst;
    TSK_MOVSCT_SRC(gfcd_work) = src;
    TSK_MOVSCT_SPOS(gfcd_work) = spos;
    TSK_MOVSCT_SNUM(gfcd_work) = snum;
    gfcd_doMoveSctTsk(&ncmd);
    return GFCD_ERR_OK;
}

// 0x06020240
Bool GFCD_CheckMove(void) {
    if (TSK_MOVSCT_STAT(gfcd_work) != GFCD_TSK_READY) {
        return FALSE;
    }
    return TRUE;
}

// 0x06020264
Sint32 GFCD_GetSctInfo(Sint32 bufno, Sint32 sn, CdcSct* info) {
    Sint32 ret;

    if ((bufno < 0) || (GFS_CDBBUF_NR <= bufno)) {
        return GFCD_ERR_RANGE;
    }
    if (CDBMNG_USEBUF(gfcd_work, bufno) == UNUSED) {
        return GFCD_ERR_UNUSE;
    }
    ret = CDC_GetSctInfo(bufno, sn, info);
    if (ret != CDC_ERR_OK) {
        return GFCD_ERR_CDC;
    }
    gfcd_setStat();
    return GFCD_ERR_OK;
}

// 0x060202AC
Sint32 GFCD_ChgDir(Sint32 fid, Sint32 work, Sint32* ndir) {
    Sint32 ncmd;

    if ((CDBMNG_USEFILT(gfcd_work, work) != INUSE) ||
        (CDBMNG_USEBUF(gfcd_work, work) != INUSE)) {
        return GFCD_ERR_INUSE;
    }
    if (TSK_CHGDIR_STAT(gfcd_work) != GFCD_TSK_READY) {
        return GFCD_ERR_WAIT;
    }
    if (fid == CDC_NUL_FID) {
        TSK_CHGDIR_STAT(gfcd_work) = GFCD_TSK_STAT3;
    } else {
        TSK_CHGDIR_STAT(gfcd_work) = GFCD_TSK_STAT1;
    }
    TSK_CHGDIR_FID(gfcd_work) = fid;
    TSK_CHGDIR_WORK(gfcd_work) = work;
    TSK_CHGDIR_NDIR(gfcd_work) = ndir;
    gfcd_doChgDirTsk(&ncmd);
    return GFCD_ERR_OK;
}

// 0x06020328
Sint32 GFCD_SetFiltCon(Sint32 flt, Sint32 buf, Sint32 flnout) {
    Sint32 ncmd;
    Sint32 len = TSK_FLTCON_LEN(gfcd_work);

    if (((flt != CDC_NUL_SEL) && (flt != GFCD_ANY_FLT) &&
         ((flt < 0) || (GFS_CDBBUF_NR <= flt))) ||
        ((buf < 0) || (GFS_CDBBUF_NR <= buf)) ||
        ((flnout != CDC_NUL_SEL) && (flnout != GFCD_ANY_FLT) &&
         ((flnout < 0) || (GFS_CDBBUF_NR <= flnout)))) {
        return GFCD_ERR_RANGE;
    }
    if (((flt != CDC_NUL_SEL) && (flt != GFCD_ANY_FLT) &&
         (CDBMNG_USEFILT(gfcd_work, flt) != INUSE)) ||
        ((flnout != CDC_NUL_SEL) && (flnout != GFCD_ANY_FLT) &&
         (CDBMNG_USEFILT(gfcd_work, flnout) != INUSE)) ||
        (CDBMNG_USEBUF(gfcd_work, buf) != INUSE)) {
        return GFCD_ERR_UNUSE;
    }
    if (len >= GFS_FCONQ_MAX) {
        return GFCD_ERR_QFULL;
    }
    if (TSK_FLTCON_STAT(gfcd_work) == GFCD_TSK_READY) {
        TSK_FLTCON_STAT(gfcd_work) = GFCD_TSK_STAT1;
    }
    TSK_FLTCON_FLT(gfcd_work, len) = flt;
    TSK_FLTCON_BUF(gfcd_work, len) = buf;
    TSK_FLTCON_FLNOUT(gfcd_work, len) = flnout;
    ++TSK_FLTCON_LEN(gfcd_work);
    gfcd_doSetFiltConTsk(&ncmd);
    return GFCD_ERR_OK;
}

// 0x06020420
Sint32 GFCD_GetFileInfo(Sint32 fid, CdcFile* finfo) {
    Sint32 ret;
    Sint32 base_fid, infnum;
    Bool drend;

    ret = CDC_GetFileScope(&base_fid, &infnum, &drend);
    if (ret != CDC_ERR_OK) {
        return GFCD_ERR_CDBFS;
    }
    if ((fid < base_fid) || ((base_fid + infnum) <= fid)) {
        ret = CDC_ReadDir(GFCD_SYS_SEL, fid);
        if (ret != CDC_ERR_OK) {
            return GFCD_ERR_CDBFS;
        }
        while (gfcd_checkEflag(CDC_HIRQ_EFLS) == FALSE) {
        }
        ret = CDC_GetFileScope(&base_fid, &infnum, &drend);
        if ((ret != CDC_ERR_OK) ||
            ((fid < base_fid) && (base_fid + infnum <= fid))) {
            return GFCD_ERR_CDBFS;
        }
    }
    ret = CDC_TgetFileInfo(fid, finfo);
    if (ret != CDC_ERR_OK) {
        return GFCD_ERR_CDBFS;
    }
    if ((CDC_FILE_ATR(finfo) & CDC_ATR_DIRFG) != 0) {
        CDC_FILE_ATR(finfo) |= CDC_ATR_DIRXA;
    }
    if ((drend) && ((base_fid + infnum - 1) == fid)) {
        CDC_FILE_ATR(finfo) |= GFS_ATR_END_TBL;
    }
    gfcd_setStat();
    return GFCD_ERR_OK;
}

// 0x060204F8
Sint32 GFCD_GetBufSiz(void) {
    Sint32 ret;
    Sint32 bufsiz, partsiz, freesiz;

    ret = CDC_GetBufSiz(&bufsiz, &partsiz, &freesiz);
    if (ret != CDC_ERR_OK) {
        return GFCD_ERR_CDC;
    }
    gfcd_setStat();
    return freesiz;
}

// 0x06020530
Sint32 GFCD_ExecServer(void) {
    Sint32 ncmd = 0;
    Sint32 ntsk = 0;
    Sint32 tsk;
    Sint32 ret;

    if (CDBMNG_TIMER(gfcd_work) != GFCD_NO_TMOUT) {
        if (--CDBMNG_TIMER(gfcd_work) <= 0) {
            gfcd_initCdbMng();
            return GFCD_SVR_TMOUT;
        }
    }
    GFCD_GetStat(&CDBMNG_STAT(gfcd_work));
    if (gfcd_fatal_err != GFCD_ERR_OK) {
        return GFCD_SVR_ERROR;
    }
    if (gfcd_checkEflag(CDC_HIRQ_SCDQ) == TRUE) {
        CDC_ClrHirqReq(~CDC_HIRQ_SCDQ);
        if (CDBMNG_FUNC(gfcd_work) != NULL) {
            CDBMNG_FUNC(gfcd_work)(CDBMNG_OBJ(gfcd_work));
        }
    }
    for (tsk = 0; tsk < TSK_ID_END; ++tsk) {
        if (gfcd_isIdleTask(tsk)) {
            continue;
        }
        ret = gfcd_doTask(tsk, &ncmd);
        if (ret < 0) {
            return ret;
        }
        ntsk += ret;
        if (ncmd > MAX_CMD_PER_EXEC) {
            return GFCD_SVR_BUSY;
        }
    }
    return (ntsk > 0) ? GFCD_SVR_BUSY : GFCD_SVR_COMPLETED;
}

// 0x0602060C
GFS_LOCAL Bool gfcd_isIdleTask(Sint32 tsk) {
    Sint32 stat = GFCD_TSK_READY;

    switch (tsk) {
    case TSK_ID_SETFLT:
        stat = TSK_SETFLT_STAT(gfcd_work);
        break;
    case TSK_ID_SETCON:
        stat = TSK_SETCON_STAT(gfcd_work);
        break;
    case TSK_ID_GETLEN:
        stat = TSK_GETLEN_STAT(gfcd_work);
        break;
    case TSK_ID_REQDAT:
        stat = TSK_REQDAT_STAT(gfcd_work);
        break;
    case TSK_ID_DELSCT:
        stat = TSK_DELSCT_STAT(gfcd_work);
        break;
    case TSK_ID_MOVSCT:
        stat = TSK_MOVSCT_STAT(gfcd_work);
        break;
    case TSK_ID_FLTCON:
        stat = TSK_FLTCON_STAT(gfcd_work);
        break;
    case TSK_ID_CHGDIR:
        stat = TSK_CHGDIR_STAT(gfcd_work);
        break;
    }
    return (stat == GFCD_TSK_READY) ? TRUE : FALSE;
}

// 0x06020698
GFS_LOCAL Sint32 gfcd_doTask(Sint32 tsk, Sint32* ncmd) {
    switch (tsk) {
    case TSK_ID_SETFLT:
        return gfcd_doSetFiltTsk(ncmd);
    case TSK_ID_SETCON:
        return gfcd_doSetConTsk(ncmd);
    case TSK_ID_GETLEN:
        return gfcd_doGetLenDataTsk(ncmd);
    case TSK_ID_REQDAT:
        return gfcd_doReqDataTsk(ncmd);
    case TSK_ID_DELSCT:
        return gfcd_doDelSctDataTsk(ncmd);
    case TSK_ID_MOVSCT:
        return gfcd_doMoveSctTsk(ncmd);
    case TSK_ID_FLTCON:
        return gfcd_doSetFiltConTsk(ncmd);
    case TSK_ID_CHGDIR:
        return gfcd_doChgDirTsk(ncmd);
    }
    return GFCD_TSK_READY;
}

// 0x06020744
GFS_LOCAL void GFCD_SetTimer(Sint32 tm_count) {
    CDBMNG_TIMER(gfcd_work) = tm_count;
}

// 0x06020758
Sint32 GFCD_WaitServer(void) {
    Sint32 err;

    GFCD_SetTimer(GFCD_TMOUT_COUNT);
    for (;;) {
        err = GFCD_ExecServer();
        if (err != GFCD_SVR_BUSY) {
            break;
        }
    }
    GFCD_SetTimer(GFCD_NO_TMOUT);
    return err;
}

// 0x06020794
GFS_LOCAL Sint32 gfcd_doSetFiltTsk(Sint32* ncmd) {
    Sint32 i, j;
    Sint32 ret;

    for (i = 0; i < TSK_SETFLT_LEN(gfcd_work); ++i) {
        if (TSK_SETFLT_STAT(gfcd_work) == GFCD_TSK_STAT1) {
            ret = CDC_SetFiltMode(
                TSK_SETFLT_FLT(gfcd_work, i), TSK_SETFLT_FMODE(gfcd_work, i));
            if (ret != CDC_ERR_OK) {
                break;
            }
            gfcd_setStat();
            ++*ncmd;
            TSK_SETFLT_STAT(gfcd_work) = GFCD_TSK_STAT2;
        }
        if (TSK_SETFLT_STAT(gfcd_work) == GFCD_TSK_STAT2) {
            ret = CDC_SetFiltSubh(
                TSK_SETFLT_FLT(gfcd_work, i), &TSK_SETFLT_SUBH(gfcd_work, i));
            if (ret != CDC_ERR_OK) {
                break;
            }
            gfcd_setStat();
            ++*ncmd;
            if (TSK_SETFLT_SNUM(gfcd_work, i) != 0) {
                TSK_SETFLT_STAT(gfcd_work) = GFCD_TSK_STAT3;
            } else {
                TSK_SETFLT_STAT(gfcd_work) = GFCD_TSK_STAT1;
            }
        }
        if (TSK_SETFLT_STAT(gfcd_work) == GFCD_TSK_STAT3) {
            ret = CDC_SetFiltRange(
                TSK_SETFLT_FLT(gfcd_work, i), TSK_SETFLT_FAD(gfcd_work, i),
                TSK_SETFLT_SNUM(gfcd_work, i));
            if (ret != CDC_ERR_OK) {
                break;
            }
            gfcd_setStat();
            ++*ncmd;
            TSK_SETFLT_STAT(gfcd_work) = GFCD_TSK_STAT1;
        }
    }
    if (i >= TSK_SETFLT_LEN(gfcd_work)) {
        TSK_SETFLT_LEN(gfcd_work) = 0;
    } else {
        for (j = 0; i < TSK_SETFLT_LEN(gfcd_work); ++i, ++j) {
            TSK_SETFLT_QELT(gfcd_work, j) = TSK_SETFLT_QELT(gfcd_work, i);
        }
        TSK_SETFLT_LEN(gfcd_work) = j;
    }
    if (gfcd_checkEflag(CDC_HIRQ_ESEL)) {
        if (TSK_SETFLT_LEN(gfcd_work) == 0) {
            TSK_SETFLT_STAT(gfcd_work) = GFCD_TSK_READY;
        }
    }
    return TSK_SETFLT_LEN(gfcd_work);
}

// 0x0602093C
GFS_LOCAL Sint32 gfcd_doSetConTsk(Sint32* ncmd) {
    Sint32 ret;

    if (TSK_SETCON_STAT(gfcd_work) == GFCD_TSK_STAT1) {
        ret = CDC_CdSetCon(TSK_SETCON_FLT(gfcd_work));
        ++*ncmd;
        if (ret == CDC_ERR_OK) {
            TSK_SETCON_STAT(gfcd_work) = GFCD_TSK_STAT2;
        }
        gfcd_setStat();
    }
    if (TSK_SETCON_STAT(gfcd_work) == GFCD_TSK_STAT2) {
        if (gfcd_checkEflag(CDC_HIRQ_ESEL)) {
            TSK_SETCON_STAT(gfcd_work) = GFCD_TSK_READY;
        }
    }
    return TSK_SETCON_STAT(gfcd_work);
}

// 0x060209C8
GFS_LOCAL Sint32 gfcd_doGetLenDataTsk(Sint32* ncmd) {
    Sint32 ret;
    Sint32 actwsiz, nsct;

    if (TSK_GETLEN_STAT(gfcd_work) == GFCD_TSK_STAT1) {
        ret = CDC_GetSctNum(TSK_GETLEN_BUFNO(gfcd_work), &nsct);
        gfcd_setStat();
        ++*ncmd;
        nsct -= TSK_GETLEN_SPOS(gfcd_work);
        nsct = MIN(nsct, TSK_GETLEN_USCT(gfcd_work));
        *TSK_GETLEN_NSCT(gfcd_work) = nsct;
        if (TSK_GETLEN_NBYTE(gfcd_work) == NULL) {
            TSK_GETLEN_STAT(gfcd_work) = GFCD_TSK_READY;
            return GFCD_TSK_READY;
        }
        if (nsct <= 0) {
            TSK_GETLEN_STAT(gfcd_work) = GFCD_TSK_READY;
            *TSK_GETLEN_NBYTE(gfcd_work) = 0;
            return GFCD_TSK_READY;
        }
        TSK_GETLEN_STAT(gfcd_work) = GFCD_TSK_STAT2;
    }
    if (TSK_GETLEN_STAT(gfcd_work) == GFCD_TSK_STAT2) {
        if (CDBMNG_TRBUFNO(gfcd_work) != TRREG_UNUSED) {
            return GFCD_TSK_STAT2;
        }
        CDBMNG_TRBUFNO(gfcd_work) = TSK_GETLEN_BUFNO(gfcd_work);
        ret = CDC_CalActSiz(
            TSK_GETLEN_BUFNO(gfcd_work), TSK_GETLEN_SPOS(gfcd_work),
            *TSK_GETLEN_NSCT(gfcd_work));
        if (ret != CDC_ERR_OK) {
            return GFCD_TSK_STAT2;
        }
        gfcd_setStat();
        ++*ncmd;
        TSK_GETLEN_STAT(gfcd_work) = GFCD_TSK_STAT3;
    }
    if (TSK_GETLEN_STAT(gfcd_work) == GFCD_TSK_STAT3) {
        ret = CDC_GetActSiz(&actwsiz);
        if (ret != CDC_ERR_OK) {
            return GFCD_TSK_STAT1;
        }
        gfcd_setStat();
        ++*ncmd;
        TSK_GETLEN_STAT(gfcd_work) = GFCD_TSK_READY;
        *TSK_GETLEN_NBYTE(gfcd_work) = GFS_WORD_BYTE(actwsiz);
        CDBMNG_TRBUFNO(gfcd_work) = TRREG_UNUSED;
        return GFCD_TSK_READY;
    }
    return GFCD_TSK_STAT1;
}

// 0x06020B18
GFS_LOCAL Sint32 gfcd_doReqDataTsk(Sint32* ncmd) {
    Sint32 ret;

    if (TSK_REQDAT_STAT(gfcd_work) == GFCD_TSK_STAT1) {
        ret = CDC_GetSctData(
            TSK_REQDAT_BUFNO(gfcd_work), TSK_REQDAT_SCTPOS(gfcd_work),
            TSK_REQDAT_NSCT(gfcd_work));
        if (ret != CDC_ERR_OK) {
            return GFCD_TSK_STAT1;
        }
        gfcd_setStat();
        ++*ncmd;
        TSK_REQDAT_STAT(gfcd_work) = GFCD_TSK_STAT2;
    }
    if (TSK_REQDAT_STAT(gfcd_work) == GFCD_TSK_STAT2) {
        ret = CDC_DataReady(CDC_DRDY_GET);
        if (ret == CDC_ERR_OK) {
            TSK_REQDAT_STAT(gfcd_work) = GFCD_TSK_READY;
            return GFCD_TSK_READY;
        }
    }
    return GFCD_TSK_STAT1;
}

// 0x06020BB8
GFS_LOCAL Sint32 gfcd_doDelSctDataTsk(Sint32* ncmd) {
    Sint32 ret;
    Sint32 nsct;
    Bool tsk_stat;

    tsk_stat = TRUE;
    if (TSK_DELSCT_STAT(gfcd_work) == GFCD_TSK_STAT1) {
        if ((TSK_DELSCT_SCTPOS(gfcd_work) == 0) &&
            (TSK_DELSCT_NSCT(gfcd_work) == CDC_SNUM_END)) {
            ret = CDC_ResetSelector(0, TSK_DELSCT_BUFNO(gfcd_work));
            if (ret != CDC_ERR_OK) {
                return GFCD_TSK_STAT1;
            }
            gfcd_setStat();
            ++*ncmd;
            TSK_DELSCT_STAT(gfcd_work) = GFCD_TSK_STAT4;
        } else {
            nsct = TSK_DELSCT_NSCT(gfcd_work);
            if (nsct == 0) {
                tsk_stat = FALSE;
            } else {
                TSK_DELSCT_STAT(gfcd_work) = GFCD_TSK_STAT2;
            }
        }
    }
    if (TSK_DELSCT_STAT(gfcd_work) == GFCD_TSK_STAT2) {
        ret = CDC_DelSctData(
            TSK_DELSCT_BUFNO(gfcd_work), TSK_DELSCT_SCTPOS(gfcd_work),
            TSK_DELSCT_NSCT(gfcd_work));
        ++*ncmd;
        if (ret == CDC_ERR_OK) {
            TSK_DELSCT_STAT(gfcd_work) = GFCD_TSK_STAT3;
            gfcd_setStat();
        }
    }
    if (TSK_DELSCT_STAT(gfcd_work) == GFCD_TSK_STAT3) {
        if (gfcd_checkEflag(CDC_HIRQ_EHST)) {
            tsk_stat = FALSE;
        }
    }
    if (TSK_DELSCT_STAT(gfcd_work) == GFCD_TSK_STAT4) {
        if (gfcd_checkEflag(CDC_HIRQ_ESEL)) {
            tsk_stat = FALSE;
        }
    }
    if (tsk_stat == TRUE) {
        return GFCD_TSK_STAT1;
    }
    CDC_ClrHirqReq(~CDC_HIRQ_BFUL);
    TSK_DELSCT_STAT(gfcd_work) = GFCD_TSK_READY;
    return GFCD_TSK_READY;
}

// 0x06020CE8
GFS_LOCAL Sint32 gfcd_doMoveSctTsk(Sint32* ncmd) {
    Sint32 ret;

    if (TSK_MOVSCT_STAT(gfcd_work) == GFCD_TSK_STAT1) {
        ret = CDC_GetFiltMode(
            TSK_MOVSCT_DST(gfcd_work), &TSK_MOVSCT_FMODE(gfcd_work));
        ++*ncmd;
        gfcd_setStat();
        ret = CDC_SetFiltMode(TSK_MOVSCT_DST(gfcd_work), 0);
        if (ret != CDC_ERR_OK) {
            return GFCD_TSK_STAT1;
        }
        gfcd_setStat();
        ++*ncmd;
        TSK_MOVSCT_STAT(gfcd_work) = GFCD_TSK_STAT2;
    }
    if (TSK_MOVSCT_STAT(gfcd_work) == GFCD_TSK_STAT2) {
        ret = CDC_MoveSctData(
            TSK_MOVSCT_SRC(gfcd_work), TSK_MOVSCT_SPOS(gfcd_work),
            TSK_MOVSCT_SNUM(gfcd_work), TSK_MOVSCT_DST(gfcd_work));
        if (ret != CDC_ERR_OK) {
            return GFCD_TSK_STAT1;
        }
        gfcd_setStat();
        ++*ncmd;
        TSK_MOVSCT_STAT(gfcd_work) = GFCD_TSK_STAT3;
    }
    if (TSK_MOVSCT_STAT(gfcd_work) == GFCD_TSK_STAT3) {
        if (gfcd_checkEflag(CDC_HIRQ_ECPY)) {
            TSK_MOVSCT_STAT(gfcd_work) = GFCD_TSK_STAT4;
        }
    }
    if (TSK_MOVSCT_STAT(gfcd_work) == GFCD_TSK_STAT4) {
        ret = CDC_SetFiltMode(
            TSK_MOVSCT_DST(gfcd_work), TSK_MOVSCT_FMODE(gfcd_work));
        if (ret != CDC_ERR_OK) {
            return GFCD_TSK_STAT1;
        }
        ++*ncmd;
        TSK_MOVSCT_STAT(gfcd_work) = GFCD_TSK_STAT5;
    }
    if (TSK_MOVSCT_STAT(gfcd_work) == GFCD_TSK_STAT5) {
        if (gfcd_checkEflag(CDC_HIRQ_ESEL) == TRUE) {
            TSK_MOVSCT_STAT(gfcd_work) = GFCD_TSK_READY;
        }
    }
    return TSK_MOVSCT_STAT(gfcd_work);
}

// 0x06020E4C
GFS_LOCAL Sint32 gfcd_doChgDirTsk(Sint32* ncmd) {
    Sint32 base_fid, infnum, ret;
    Bool drend;
    CdcStat stat;

    if (TSK_CHGDIR_STAT(gfcd_work) == GFCD_TSK_STAT1) {
        ret = CDC_GetFileScope(&base_fid, &infnum, &drend);
        if (ret != CDC_ERR_OK) {
            TSK_CHGDIR_STAT(gfcd_work) = GFCD_TSK_READY;
            *TSK_CHGDIR_NDIR(gfcd_work) = GFS_ERR_CDRD;
            return GFCD_ERR_CDBFS;
        }
        ++*ncmd;
        if ((TSK_CHGDIR_FID(gfcd_work) == 0) ||
            (TSK_CHGDIR_FID(gfcd_work) == 1) ||
            ((base_fid <= TSK_CHGDIR_FID(gfcd_work)) &&
             (TSK_CHGDIR_FID(gfcd_work) < base_fid + infnum))) {
            TSK_CHGDIR_STAT(gfcd_work) = GFCD_TSK_STAT3;
        } else {
            ret = CDC_ReadDir(GFCD_SYS_SEL, TSK_CHGDIR_FID(gfcd_work));
            if (ret != CDC_ERR_OK) {
                TSK_CHGDIR_STAT(gfcd_work) = GFCD_TSK_READY;
                *TSK_CHGDIR_NDIR(gfcd_work) = GFS_ERR_CDRD;
                return GFCD_ERR_CDBFS;
            }
            ++*ncmd;
            TSK_CHGDIR_STAT(gfcd_work) = GFCD_TSK_STAT2;
        }
    }
    if (TSK_CHGDIR_STAT(gfcd_work) == GFCD_TSK_STAT2) {
        if (gfcd_checkEflag(CDC_HIRQ_EFLS)) {
            ret = CDC_GetFileScope(&base_fid, &infnum, &drend);
            if ((ret != CDC_ERR_OK) ||
                ((TSK_CHGDIR_FID(gfcd_work) < base_fid) &&
                 (base_fid + infnum <= TSK_CHGDIR_FID(gfcd_work)))) {
                TSK_CHGDIR_STAT(gfcd_work) = GFCD_TSK_READY;
                *TSK_CHGDIR_NDIR(gfcd_work) = GFS_ERR_CDRD;
                return GFCD_ERR_CDBFS;
            }
            TSK_CHGDIR_STAT(gfcd_work) = GFCD_TSK_STAT3;
        }
    }
    if (TSK_CHGDIR_STAT(gfcd_work) == GFCD_TSK_STAT3) {
        GFCD_GetStat(&stat);
        if (gfcd_fatal_err != GFCD_ERR_OK) {
            return gfcd_fatal_err;
        }
        ret = CDC_ChgDir(TSK_CHGDIR_WORK(gfcd_work), TSK_CHGDIR_FID(gfcd_work));
        if (ret != CDC_ERR_OK) {
            return GFCD_TSK_STAT1;
        }
        gfcd_setStat();
        ++*ncmd;
        TSK_CHGDIR_STAT(gfcd_work) = GFCD_TSK_STAT4;
    }
    if (TSK_CHGDIR_STAT(gfcd_work) == GFCD_TSK_STAT4) {
        if (gfcd_checkEflag(CDC_HIRQ_EFLS)) {
            TSK_CHGDIR_STAT(gfcd_work) = GFCD_TSK_READY;
            ret = CDC_GetFileScope(&base_fid, &infnum, &drend);
            if (ret != CDC_ERR_OK) {
                TSK_CHGDIR_STAT(gfcd_work) = GFCD_TSK_READY;
                *TSK_CHGDIR_NDIR(gfcd_work) = GFS_ERR_CDRD;
                return GFCD_ERR_CDBFS;
            }
            *TSK_CHGDIR_NDIR(gfcd_work) = infnum;
        }
    }
    return TSK_CHGDIR_STAT(gfcd_work);
}

// 0x06021048
GFS_LOCAL Sint32 gfcd_doSetFiltConTsk(Sint32* ncmd) {
    Sint32 ret;
    Sint32 i, j;
    Sint32 flag, flout, flnout;

    for (i = 0; i < TSK_FLTCON_LEN(gfcd_work); ++i) {
        if (TSK_FLTCON_BUF(gfcd_work, i) == GFCD_ANY_FLT) {
            flag = 0;
            flout = CDC_NUL_SEL;
        } else {
            flag = FLTCON_BUF_SET;
            flout = TSK_FLTCON_BUF(gfcd_work, i);
        }
        if (TSK_FLTCON_FLNOUT(gfcd_work, i) == GFCD_ANY_FLT) {
            flnout = CDC_NUL_SEL;
        } else {
            flag |= FLTCON_FLN_SET;
            flnout = TSK_FLTCON_FLNOUT(gfcd_work, i);
        }
        ret = CDC_SetFiltCon(TSK_FLTCON_FLT(gfcd_work, i), flag, flout, flnout);
        if (ret != CDC_ERR_OK) {
            break;
        }
        gfcd_setStat();
        ++*ncmd;
    }
    if (i >= TSK_FLTCON_LEN(gfcd_work)) {
        TSK_FLTCON_LEN(gfcd_work) = 0;
    } else {
        for (j = 0; i < TSK_FLTCON_LEN(gfcd_work); ++i, ++j) {
            TSK_FLTCON_FLT(gfcd_work, j) = TSK_FLTCON_FLT(gfcd_work, i);
            TSK_FLTCON_BUF(gfcd_work, j) = TSK_FLTCON_BUF(gfcd_work, i);
            TSK_FLTCON_FLNOUT(gfcd_work, j) = TSK_FLTCON_FLNOUT(gfcd_work, i);
        }
        TSK_FLTCON_LEN(gfcd_work) = j;
    }
    if (gfcd_checkEflag(CDC_HIRQ_ESEL)) {
        if (TSK_FLTCON_LEN(gfcd_work) == 0) {
            TSK_FLTCON_STAT(gfcd_work) = GFCD_TSK_READY;
        }
    }
    return TSK_FLTCON_LEN(gfcd_work);
}

// 0x06021180
GFS_LOCAL Bool gfcd_checkEflag(Sint32 mask) {
    Sint32 hirq;

    hirq = CDC_GetHirqReq();
    return (mask & hirq) ? TRUE : FALSE;
}

// 0x060211A4
GFS_LOCAL void gfcd_initCdbMng(void) {
    Sint32 i;

    for (i = 0; i < GFS_OPEN_MAX - 1; ++i) {
        CDBMNG_USEBUF(gfcd_work, i) = UNUSED;
        CDBMNG_USEFILT(gfcd_work, i) = UNUSED;
    }
    CDBMNG_USEPU(gfcd_work) = UNUSED;
    CDBMNG_TRBUFNO(gfcd_work) = TRREG_UNUSED;
    CDBMNG_PUID(gfcd_work) = NOBODY;
    CDBMNG_TIMER(gfcd_work) = GFCD_NO_TMOUT;
    CDBMNG_FUNC(gfcd_work) = GFCD_NULLFUNC;
    CDBMNG_OBJ(gfcd_work) = NULL;
    TSK_SETFLT_LEN(gfcd_work) = 0;
    TSK_SETFLT_STAT(gfcd_work) = GFCD_TSK_READY;
    TSK_SETCON_STAT(gfcd_work) = GFCD_TSK_READY;
    TSK_GETLEN_STAT(gfcd_work) = GFCD_TSK_READY;
    TSK_REQDAT_STAT(gfcd_work) = GFCD_TSK_READY;
    TSK_DELSCT_STAT(gfcd_work) = GFCD_TSK_READY;
    TSK_MOVSCT_STAT(gfcd_work) = GFCD_TSK_READY;
    TSK_CHGDIR_STAT(gfcd_work) = GFCD_TSK_READY;
    TSK_FLTCON_LEN(gfcd_work) = 0;
    TSK_FLTCON_STAT(gfcd_work) = GFCD_TSK_READY;
}

// 0x06021224
GFS_LOCAL void gfcd_setStat(void) {
    CdcStat stat;

    CDC_GetLastStat(&stat);
    CDC_STAT_STATUS(&CDBMNG_STAT(gfcd_work)) = CDC_STAT_STATUS(&stat);
}

// 0x06021250
void GFCD_SetCsctFunc(void (*func)(void*), void* obj) {
    CDBMNG_FUNC(gfcd_work) = func;
    CDBMNG_OBJ(gfcd_work) = obj;
}

// 0x0602126C
Bool GFCD_ChkScdqFlag(void) {
    if (CDC_GetHirqReq() & CDC_HIRQ_SCDQ) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// 0x06021290
void GFCD_ClrScdqFlag(void) { CDC_ClrHirqReq(~CDC_HIRQ_SCDQ); }

// 0x060212AC
Bool GFCD_WaitScdqFlag(void) {
    Sint32 timer;

    for (timer = 0; timer < SCDQ_TMOUT_COUNT; ++timer) {
        if (GFCD_ChkScdqFlag() == TRUE) {
            GFCD_ClrScdqFlag();
            return FALSE;
        }
    }
    return TRUE;
}

// 0x060212F0
void GFCD_WaitPause(void) {
    Sint32 i;
    CdcStat st;

    for (i = 0; i < PAUSE_TMOUT_COUNT; i++) {
        GFCD_GetStat(&st);
        if ((CDC_GET_STC(&st) == CDC_ST_PAUSE) ||
            (CDC_GET_STC(&st) == CDC_ST_STANDBY) ||
            (gfcd_fatal_err != GFCD_ERR_OK)) {
            break;
        }
    }
}
