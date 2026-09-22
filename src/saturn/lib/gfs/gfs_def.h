#ifndef GFS_DEF_H
#define GFS_DEF_H

#define GFS_LOCAL

#define GFTB_BUF_END    0xffff

#define MNG_CDCON_MSK   0x0001
#define MNG_SCSICON_MSK 0x0002

#define GFS_MD1_SCTSIZ  2048
#define GFS_FM1_SCTSIZ  2048
#define GFS_FM2_SCTSIZ  2324
#define GFS_CDDA_SCTSIZ 2352

#define SFM_SCTSIZE     GFS_MD1_SCTSIZ

#define MMF_SCTSIZE     GFS_MD1_SCTSIZ

#define GFS_LONG_MAX    0x7fffffff

enum GfsFlowinStat {
    GFS_FIN_NOACT,
    GFS_FIN_START,
    GFS_FIN_PLAY,
    GFS_FIN_PAUSE,
    GFS_FIN_END,
    GFS_FIN_OPEN,
    GFS_FIN_NODISC,
    GFS_FIN_PUINUSE,
    GFS_FIN_ERROR,
    GFS_FIN_FATAL
};

enum GfsCdBlockStatus {
    GFS_STAT_NOACT,
    GFS_STAT_READ,
    GFS_STAT_SEEK,
    GFS_STAT_OPEN,
    GFS_STAT_NODISC,
    GFS_STAT_ERROR,
    GFS_STAT_FATAL
};

enum GfsFileType {
    CD_FILE = 0,
    MEM_FILE,
    SCSI_FILE,
    FILE_TYPE
};

#define IS_FORM1(atr)   (((atr) & GFS_ATR_FORM1)? TRUE: FALSE)
#define IS_FORM2(atr)   (((atr) & GFS_ATR_FORM2)? TRUE: FALSE)
#define IS_CDDA(atr)    (((atr) & GFS_ATR_CDDA)? TRUE: FALSE)

#define IS_ENDTBL(atr)  (((atr) & GFS_ATR_END_TBL)? TRUE: FALSE)

#define XSTRNCPY(s1, s2, n)     strncpy((Sint8 *)s1, (Sint8 *)s2, n)
#define XSTRCPY(s1, s2)         strcpy((Sint8 *)s1, (Sint8 *)s2)
#define XSTRNCMP(s1, s2, n)     strncmp((Sint8 *)s1, (Sint8 *)s2, n)
#define XSTRCMP(s1, s2)         strcmp((Sint8 *)s1, (Sint8 *)s2)

#define GFS_BYTE_SCT(byte, sctsiz)  \
    ((Sint32)(((Uint32)(byte)) + ((Uint32)(sctsiz)) - 1) / ((Uint32)(sctsiz)))
#define GFS_LAST_ROOM(byte, sctsiz) (((sctsiz)-((byte)%(sctsiz)))%(sctsiz))

#define GFS_FI_FID(finfo)       ((finfo)->fid)
#define GFS_FI_FINFO(finfo)     ((finfo)->finfo)
#define GFS_FI_FAD(finfo)       ((finfo)->finfo.fad)
#define GFS_FI_SIZE(finfo)      ((finfo)->finfo.size)
#define GFS_FI_UNIT(finfo)      ((finfo)->finfo.unit)
#define GFS_FI_GAP(finfo)       ((finfo)->finfo.gap)
#define GFS_FI_FN(finfo)        ((finfo)->finfo.fn)
#define GFS_FI_ATR(finfo)       ((finfo)->finfo.atr)
#define GFS_FI_SCTSZ(finfo)     ((finfo)->sctsz)
#define GFS_FI_NSCT(finfo)      ((finfo)->nsct)
#define GFS_FI_LSTRM(finfo)     ((finfo)->lstrm)

#define GFS_CDR_BUFNO(dts)      ((dts)->rsrc.cd.bufno)
#define GFS_CDR_SCTSZ(dts)      ((dts)->rsrc.cd.sctsz)
#define GFS_CDR_FLT(dts)        ((dts)->rsrc.cd.flt)
#define GFS_CDR_SUBH(dts)       ((dts)->rsrc.cd.subh)
#define GFS_CDR_FMODE(dts)      ((dts)->rsrc.cd.fmode)
#define GFS_CDR_PUID(dts)       ((dts)->rsrc.cd.puid)
#define GFS_CDR_SCTPOS(dts)     ((dts)->rsrc.cd.sctpos)
#define GFS_CDR_FILEPOS(dts)    ((dts)->rsrc.cd.filepos)
#define GFS_CDR_SFAD(dts)       ((dts)->rsrc.cd.sfad)
#define GFS_CDR_EFAD(dts)       ((dts)->rsrc.cd.efad)

#define GFS_SCR_FID(dts)        ((dts)->rsrc.scsi.fid)
#define GFS_SCR_FILEPOS(dts)    ((dts)->rsrc.scsi.filepos)
#define GFS_SCR_SCTPOS(dts)     ((dts)->rsrc.scsi.sctpos)
#define GFS_SCR_SCTNUM(dts)     ((dts)->rsrc.scsi.sctnum)

#define GFS_MEMR_DATA(dts)      ((dts)->rsrc.mem.data)
#define GFS_MEMR_FILEPOS(dts)   ((dts)->rsrc.mem.filepos)
#define GFS_MEMR_SCTPOS(dts)    ((dts)->rsrc.mem.sctpos)
#define GFS_MEMR_SCTNUM(dts)    ((dts)->rsrc.mem.sctnum)

#define GFS_DTS_FTYPE(dts)      ((dts)->ftype)
#define GFS_DTS_CD(dts)         ((dts)->rsrc.cd)
#define GFS_DTS_SCSI(dts)       ((dts)->rsrc.scsi)
#define GFS_DTS_MEM(dts)        ((dts)->rsrc.mem)

#define GFS_FLW_FINFO(flow)     ((flow)->finfo)
#define GFS_FLW_DTSRC(flow)     ((flow)->dtsrc)
#define GFS_FLW_GMODE(dts)      ((flow)->gmode)
#define GFS_FLW_STAT(flow)      ((flow)->stat)
#define GFS_FLW_SCT(flow)       ((flow)->sct)
#define GFS_FLW_SCTCNT(flow)    ((flow)->sctcnt)
#define GFS_FLW_SCTMAX(flow)    ((flow)->sctmax)

#define GFDP_DATA(dpk)          ((dpk)->data)
#define GFDP_ADLT(dpk)          ((dpk)->adlt)
#define GFDP_LEN(dpk)           ((dpk)->len)
#define GFDP_NSCT(dpk)          ((dpk)->nsct)
#define GFDP_USE(dpk)           ((dpk)->use)

#define GFS_TRN_BUF(tran)       ((tran)->buf)
#define GFS_TRN_SIZE(tran)      ((tran)->size)
#define GFS_TRN_WP(tran)        ((tran)->wp)
#define GFS_TRN_DPS(tran)       ((tran)->dps)
#define GFS_TRN_DPD(tran)       ((tran)->dpd)
#define GFS_TRN_TSCTMAX(tran)   ((tran)->tsctmax)
#define GFS_TRN_TSCT(tran)      ((tran)->tsct)
#define GFS_TRN_TSCTCNT(tran)   ((tran)->tsctcnt)
#define GFS_TRN_TBYTCNT(tran)   ((tran)->tbytcnt)
#define GFS_TRN_OBJ(tran)       ((tran)->obj)
#define GFS_TRN_TFUNC(tran)     ((tran)->tfunc)
#define GFS_TRN_UNIT(tran)      ((tran)->unit)
#define GFS_TRN_ACTIVE(tran)    ((tran)->active)
#define GFS_TRN_STAT(tran)      ((tran)->stat)
#define GFS_TRN_MODE(tran)      ((tran)->mode)

#define GFS_FILE_USED(file)     ((file)->used)
#define GFS_FILE_AMODE(file)    ((file)->amode)
#define GFS_FILE_ASTAT(file)    ((file)->astat)
#define GFS_FILE_FLOW(file)     ((file)->flow)
#define GFS_FILE_TRANS(file)    ((file)->trans)

#define SVR_ACFILE(svr, i)      ((svr)->access_file[i])
#define SVR_NFILE(svr)          ((svr)->nfile)

#define FUNC_FLOWIN(func)       ((func)->flowin)
#define FUNC_STOPIN(func)       ((func)->stopin)
#define FUNC_RECOVER(func)      ((func)->recover)
#define FUNC_SEEK(func)         ((func)->seek)
#define FUNC_TELL(func)         ((func)->tell)

#define DIRMNG_DIRTBL(mng)      ((mng)->dirtbl)
#define DIRMNG_DIRID(mng)       GFS_DIRTBL_DIRID(&(mng)->dirtbl)
#define DIRMNG_DIRNAME(mng)     GFS_DIRTBL_DIRNAME(&(mng)->dirtbl)
#define DIRMNG_TYPE(mng)        GFS_DIRTBL_TYPE(&(mng)->dirtbl)
#define DIRMNG_NDIR(mng)        GFS_DIRTBL_NDIR(&(mng)->dirtbl)
#define DIRMNG_NFILE(mng)       ((mng)->nfile)

#define MNG_OPENMAX(mng)        ((mng)->openmax)
#define MNG_FUNCTBL(mng, type)  ((mng)->functbl[type])
#define MNG_SVR(mng)            ((mng)->svr)
#define MNG_CURDIR(mng)         ((mng)->curdir)
#define MNG_PICKUP(mng)         ((mng)->pickup)
#define MNG_SFAD(mng)           ((mng)->sfad)
#define MNG_EFAD(mng)           ((mng)->efad)
#define MNG_TRANS(mng)          ((mng)->trans)
#define MNG_ERROR(mng)          ((mng)->error)
#define MNG_FLAGS(mng)          ((mng)->flags)
#define MNG_CDCON(mng)          (MNG_FLAGS(mng) & MNG_CDCON_MSK)
#define MNG_SCSICON(mng)        (MNG_FLAGS(mng) & MNG_SCSICON_MSK)
#define MNG_CDBMNG(mng)         ((mng)->cdb)
#define MNG_SRCPK(mng)          ((mng)->srcpk)
#define MNG_DSTPK(mng)          ((mng)->dstpk)
#define MNG_SECTBUF(mng)        ((mng)->sect_buf)
#define MNG_FILE(mng)           ((mng)->file)
#define MNG_TIMER(mng)          ((mng)->timer)

extern GfsMng *gfs_mng_ptr;

extern Sint8    *GFMC_base;

extern Bool gfs_use_scudma;

GfsHn GFS_OpenSub(GfsFile *gfs, GfsDirId *dirrec, Sint32 fid);
GfsFile *GFS_mngAllocGrp(void);
Sint32 GFS_GetFad(Sint32 fid, Sint32 off);

#endif