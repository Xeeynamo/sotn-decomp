#ifndef GFS_CDC_H
#define GFS_CDC_H

#define GFCD_UID_NONE   -1

#define GFCD_ANY_FLT    -2

#define GFCD_TMOUT_COUNT        0x30000
#define GFCD_NO_TMOUT           0

#define GFCD_ERR_OK             0
#define GFCD_ERR_WAIT           -1
#define GFCD_ERR_NOCDBLK        -2
#define GFCD_ERR_NOFILT         -3
#define GFCD_ERR_NOBUF          -4
#define GFCD_ERR_INUSE          -5
#define GFCD_ERR_RANGE          -6
#define GFCD_ERR_UNUSE          -7
#define GFCD_ERR_QFULL          -8
#define GFCD_ERR_NOTOWNER       -9
#define GFCD_ERR_CDC            -10
#define GFCD_ERR_CDBFS          -11
#define GFCD_ERR_TMOUT          -12
#define GFCD_ERR_OPEN           -13
#define GFCD_ERR_NODISC         -14
#define GFCD_ERR_CDROM          -15
#define GFCD_ERR_FATAL          -16

#define GFCD_SYS_SEL    (GFS_OPEN_MAX - 1)

#define GFCD_NULLFUNC   ((void (*)(void *))0)

enum GfcdExecServerStat {
    GFCD_SVR_COMPLETED,
    GFCD_SVR_BUSY,
    GFCD_SVR_ERROR,
    GFCD_SVR_TMOUT
};

extern Sint32 gfcd_fatal_err;

void GFCD_SetCdbfs(Bool use_cdbfs);
Sint32 GFCD_Init(GfsCdbMng *work, Bool use_cdbfs);
Sint32 GFCD_AllocBuf(Sint32 *buf_no);
Sint32 GFCD_FreeBuf(Sint32 buf_no);
Sint32 GFCD_AllocFilt(Sint32 *flt_no);
Sint32 GFCD_FreeFilt(Sint32 flt_no);
Sint32 GFCD_GetBaseFad(void);
Sint32 GFCD_GetPickup(void);
Sint32 GFCD_UngetPickup(Sint32 puid);
Sint32 GFCD_IsPuOwner(Sint32 puid);
Sint32 GFCD_SetFilt(Sint32 flt, Sint32 fmode, CdcSubh *subh, Sint32 fad, Sint32 snum);
Sint32 GFCD_GetFilt(Sint32 flt, Sint32 *fmode, CdcSubh *subh);
Sint32 GFCD_SetCon(Sint32 flt, Sint32 puid);
Sint32 GFCD_Play(CdcPly *pinfo, Sint32 puid);
Sint32 GFCD_GetLenData(Sint32 bufno, Sint32 spos, Sint32 usct, Sint32 *nsct, Sint32 *nbyte);
Sint32 GFCD_ReqData(Sint32 bufno, Sint32 sctpos, Sint32 nsct);
Sint32 GFCD_EndData(Sint32 *nsct);
Sint32 GFCD_DelSctData(Sint32 bufno, Sint32 sctpos, Sint32 nsct);
Bool GFCD_CheckDelSctData(Sint32 bufno);
Sint32 GFCD_GetStat(CdcStat *stat);
Sint32 GFCD_MovePickup(CdcPos *pos, Sint32 puid);
Sint32 GFCD_MoveSctData(Sint32 dst, Sint32 src, Sint32 spos, Sint32 snum);
Bool GFCD_CheckMove(void);
Sint32 GFCD_GetSctInfo(Sint32 bufno, Sint32 sn, CdcSct *info);
Sint32 GFCD_GetFileInfo(Sint32 fid, CdcFile *finfo);
Sint32 GFCD_GetBufSiz(void);
Sint32 GFCD_ExecServer(void);
void GFCD_SetTimer(Sint32 tm_count);
Sint32 GFCD_WaitServer(void);
Sint32 GFCD_ChgDir(Sint32 fid, Sint32 work, Sint32 *ndir);
Sint32 GFCD_ReadFile(Sint32 fltno, Sint32 fid, Sint32 ofs, Sint32 puid);
Sint32 GFCD_SetFiltCon(Sint32 flt, Sint32 buf, Sint32 flnout);
void GFCD_SetCsctFunc(void (*func)(void *), void *obj);
Bool GFCD_ChkScdqFlag(void);
void GFCD_ClrScdqFlag(void);
Bool GFCD_WaitScdqFlag(void);
void GFCD_WaitPause(void);

#endif