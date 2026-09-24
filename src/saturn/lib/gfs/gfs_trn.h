#ifndef GFS_TRN_H
#define GFS_TRN_H

#define GFTR_ALLSCT -1

#define GFTR_NULLFUNC ((GfsTransFunc)0)

enum {
    GFTR_ST_NOACT = 0,
    GFTR_ST_STAT1,
    GFTR_ST_STAT2,
    GFTR_ST_STAT3,
    GFTR_ST_STAT4,
    GFTR_ST_STAT5,
    GFTR_ST_END,
    GFTR_ST_ERROR
};

Sint32 GFTR_ExecSvr(GfsHn gfs, Bool* flag);
GftrHn GFTR_Setup(GfsTrans* gftr);
Sint32 GFTR_SetMode(GftrHn gftr, Sint32 tmode);
void GFTR_SetUnit(GftrHn gftr, Sint32 unit);
void GFTR_SetTransPara(GftrHn gftr, Sint32 tsct);
Sint32 GFTR_GetTransPara(GftrHn gftr);
Sint32 GFTR_GetNumTrans(GftrHn gftr);
Sint32 GFTR_SetTransMax(GftrHn gftr, Sint32 tmax);
void GFTR_Start(GftrHn gftr);
void GFTR_Pause(GftrHn gftr);
void GFTR_Stop(GfsHn gfs, Sint32 nsct);
Sint32 GFTR_Exec(GfsHn gfs, Bool* flag);
Sint32 GFTR_Idle(GfsHn gfs);
Sint32 GFTR_GetLenData(GfsTrans* trn);
Sint32 GFTR_GetLenRoom(GfsTrans* trn);
GfdpHn GFTR_GetDstPack(GfsTrans* trn, Sint32 len);
void GFTR_RtnDstPk(GfsTrans* trn, GfdpHn dpk);
void GFTR_GetData(GfsTrans* trn, Uint8** data, Sint32* bsize, Sint32* unit);
void GFTR_SetData(GfsTrans* trn, Uint8* data, Sint32 bsize, Sint32 unit);
void GFTR_SetTransFunc(GfsHn gfs, GfsTransFunc func, void* obj);

#endif
