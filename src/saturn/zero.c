#include "inc_asm.h"
#include "sattypes.h"
INCLUDE_ASM("asm/saturn/zero/data", d6004080, d_06004080);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600EE88, func_0600EE88);
INCLUDE_ASM("asm/saturn/zero/data", d600EFBC, d_0600EFBC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600F914, func_0600F914);
INCLUDE_ASM("asm/saturn/zero/data", d600F96C, d_0600F96C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f600FFB8, func_0600FFB8);
INCLUDE_ASM("asm/saturn/zero/data", d6010008, d_06010008);

// SEGADGFS.A (debug version of lib)
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B2B4, func_0601B2B4); // GFS_Init
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B3A0, func_0601B3A0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B448, func_0601B448); // GFS_SetDir
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B4AC,
            func_0601B4AC); // GFS_NameToId
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B518,
            func_0601B518); // _GFS_IdToName
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B58C,
            func_0601B58C); // _GFS_GetDirInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B600, func_0601B600); // _GFS_Reset
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B674, func_0601B674); // _GFS_Open
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B724, func_0601B724);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B75C, func_0601B75C); // _GFS_Seek
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B810, func_0601B810); // _GFS_Tell
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B860, func_0601B860); // _GFS_IsEof
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B8B4,
            func_0601B8B4); // _GFS_ByteToSct
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601B932, func_0601B932);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B998, func_0601B998);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601B9E4, func_0601B9E4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BA0C, func_0601BA0C); // _GFS_Load
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BAD4, func_0601BAD4); // _GFS_Fread
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601BB86, func_0601BB86);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BC74, func_0601BC74);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BD20,
            func_0601BD20); // _GFS_NwCdRead
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BD94,
            func_0601BD94); // _GFS_NwIsComplete
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BDD0, func_0601BDD0); // _GFS_NwStop
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601BE6A, func_0601BE6A);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BEB8,
            func_0601BEB8); // _gfs_recovRdErr
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BEE8, func_0601BEE8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601BFA8,
            func_0601BFA8); // _GFS_NwExecServer
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601C03A, func_0601C03A);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601C09E, func_0601C09E);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601C10A, func_0601C10A);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601C16E, func_0601C16E);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C1BC,
            func_0601C1BC); // _GFS_SetTrFunc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C220,
            func_0601C220); // _GFS_StartTrans
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C26C,
            func_0601C26C); // _GFS_CdMovePickup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C2D8,
            func_0601C2D8); // _GFS_SetErrFunc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C308, func_0601C308);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C32C, func_0601C32C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C354,
            func_0601C354); // _gfs_chgRoot
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C420, func_0601C420);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C42C,
            func_0601C42C); // _gfs_mngSetupFuncTbl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C4A8,
            func_0601C4A8); // _gfs_mngInitWork
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C54C,
            func_0601C54C); // _gfs_mngGetNumFile
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C5B0,
            func_0601C5B0); // _GFS_mngAllocGrp
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C5F8, func_0601C5F8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C604,
            func_0601C604); // _gfs_mngTermAccess
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C680,
            func_0601C680); // _gfs_mngSetErrCode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C6C8,
            func_0601C6C8); // _gfs_svrSearchHndl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C708,
            func_0601C708); // _gfs_svrAddHndl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C744,
            func_0601C744); // _gfs_svrRemoveHndl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C7A0,
            func_0601C7A0); // _GFS_OpenSub
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C840,
            func_0601C840); // _gfs_loadVol
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C908,
            func_0601C908); // _gfs_getRootDir
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601C9FC,
            func_0601C9FC); // _gfs_loadRootDir
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CA88, func_0601CA88); // _gfs_flowIn
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601CB46, func_0601CB46);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CBD4, func_0601CBD4); // _GFS_GetFad
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CC2C, func_0601CC2C); // _gfs_SetSct
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CC80, func_0601CC80);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CCA0,
            func_0601CCA0); // _gfs_closeSub
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CCF0, func_0601CCF0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CD08, func_0601CD08);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CD50,
            func_0601CD50); // _gfs_convFinStat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CDC0, func_0601CDC0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CE60, func_0601CE60); // _GFCF_Setup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CFA0,
            func_0601CFA0); // _GFCF_SetSct
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601CFEC,
            func_0601CFEC); // _GFCF_GetFileInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D060, func_0601D060);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D1B0,
            func_0601D1B0); // _GFCF_StopInBuf
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D250,
            func_0601D250); // _GFCF_Recover
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D29C, func_0601D29C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D2B4, func_0601D2B4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D2CC,
            func_0601D2CC); // _GFCF_MovePickup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D36C,
            func_0601D36C); // _GFCF_cnvIntlvOfs
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D3BC,
            func_0601D3BC); // _GFCF_GetStat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D440,
            func_0601D440); // _gfcf_getSctSize
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D478,
            func_0601D478); // _gfcf_isCdOk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D534,
            func_0601D534); // _gfcf_getPlayRange
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D674, func_0601D674);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D69C, func_0601D69C); // _GFMF_Setup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D758,
            func_0601D758); // _GFSF_FlowInBuf
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D7B0, func_0601D7B0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D7C0, func_0601D7C0); // _GFSF_Seek
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D814, func_0601D814);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D824, func_0601D824);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D86C, func_0601D86C); // _GFSF_Setup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D94C,
            func_0601D94C); // _GFSF_FlowInBuf
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D9A4, func_0601D9A4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601D9B4, func_0601D9B4); // _GFSF_Seek
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DA08, func_0601DA08);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DA18, func_0601DA18);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DA34, func_0601DA34);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DA64, func_0601DA64);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DAC4, func_0601DAC4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DAD8, func_0601DAD8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DAEC, func_0601DAEC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DB08, func_0601DB08);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DB1C, func_0601DB1C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DB34,
            func_0601DB34); // _GFDR_ChgDir
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DBC4, func_0601DBC4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601DE38, func_0601DE38);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E084, func_0601E084);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E0AC, func_0601E0AC); // _gfdr_read
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E16C,
            func_0601E16C); // _gfdr_readByte
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E198, func_0601E198);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E1C4,
            func_0601E1C4); // _gfdr_readWordNB
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E218,
            func_0601E218); // _gfdr_readLongNB
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E264, func_0601E264);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E28C,
            func_0601E28C); // _gfdr_setNextRec
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E318, func_0601E318);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E688,
            func_0601E688); // _gfdr_setDirrecCd
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E6C4,
            func_0601E6C4); // _gfdr_setDirrecMem
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E700,
            func_0601E700); // _gfdr_setDirrecScsi
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E728,
            func_0601E728); // _gfdr_getScsiFinfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E7B8,
            func_0601E7B8); // _gfdr_findScsiFile
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E7E4,
            func_0601E7E4); // _gfdr_findFile
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E834,
            func_0601E834); // _gfdr_clearMemRsv
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E89C, func_0601E89C); // _GFTR_Setup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E8E4, func_0601E8E4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E8F8, func_0601E8F8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E904,
            func_0601E904); // _GFTR_SetTransPara
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E938, func_0601E938);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E944, func_0601E944);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E950, func_0601E950);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E95C, func_0601E95C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E968, func_0601E968);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601E974, func_0601E974); // _GFTR_Stop
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EA28, func_0601EA28); // _GFTR_Exec
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EAAC, func_0601EAAC); // _GFTR_Idle
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EB2C,
            func_0601EB2C); // _GFTR_ExecSvr
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EC30,
            func_0601EC30); // _gftr_getSrcPack
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601ECB8,
            func_0601ECB8); // _gftr_getDstPack
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601ED14, func_0601ED14);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601ED20,
            func_0601ED20); // _gftr_execScu
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EDBC,
            func_0601EDBC); // _gftr_remScu
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EDEC, func_0601EDEC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EDF8, func_0601EDF8); // _gfdma_exec
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EEF4,
            func_0601EEF4); // _gfdma_getBytecnt
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EF28, func_0601EF28);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EF48, func_0601EF48);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EF64, func_0601EF64);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EF7C, func_0601EF7C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EF9C, func_0601EF9C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EFB8, func_0601EFB8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EFD0, func_0601EFD0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601EFDC,
            func_0601EFDC); // _gftr_execCpu
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F01C, func_0601F01C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F028,
            func_0601F028); // _gftr_reqTrn
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F128, func_0601F128);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F160,
            func_0601F160); // _gftr_remTrn
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F1C8,
            func_0601F1C8); // _gftr_copyFrac
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F1F0, func_0601F1F0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F1FC, func_0601F1FC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F210,
            func_0601F210); // _GFTR_GetDstPack
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F248, func_0601F248);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F264, func_0601F264);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F278, func_0601F278);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F28C, func_0601F28C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F2D0, func_0601F2D0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F2F4,
            func_0601F2F4); // _GFBF_GetNumData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F320, func_0601F320);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F348, func_0601F348);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F370, func_0601F370);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F398, func_0601F398);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601F44A, func_0601F44A);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F4B0, func_0601F4B0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F528, func_0601F528);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F57C, func_0601F57C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F5CC, func_0601F5CC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F5EC, func_0601F5EC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F614, func_0601F614);
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f601F63A, func_0601F63A);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F670, func_0601F670); // _GFCB_Seek
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F7C8, func_0601F7C8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F840,
            func_0601F840); // _GFCB_GetSctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F878, func_0601F878);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F884, func_0601F884); // _GFCB_RtnPk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F8CC, func_0601F8CC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F8E8,
            func_0601F8E8); // _GFCB_SetCon
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F91C, func_0601F91C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F944, func_0601F944);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F95C, func_0601F95C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F974, func_0601F974);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601F9A0, func_0601F9A0); // _GFCD_Init
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FB98,
            func_0601FB98); // _GFCD_AllocFilt
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FBD0,
            func_0601FBD0); // _GFCD_FreeFilt
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FC00,
            func_0601FC00); // _GFCD_AllocBuf
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FC34, func_0601FC34);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FCD4,
            func_0601FCD4); // _GFCD_GetBaseFad
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FD08,
            func_0601FD08); // _GFCD_GetPickup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FD3C,
            func_0601FD3C); // _GFCD_UngetPickup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FD68, func_0601FD68);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FD8C,
            func_0601FD8C); // _GFCD_SetFilt
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FE4C,
            func_0601FE4C); // _GFCD_GetFilt
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FE94,
            func_0601FE94); // _GFCD_SetCon
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FEEC, func_0601FEEC); // _GFCD_Play
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FF4C,
            func_0601FF4C); // _GFCD_GetLenData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601FFB0,
            func_0601FFB0); // _GFCD_ReqData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602000C,
            func_0602000C); // _GFCD_EndData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020054, func_06020054);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60200A8, func_060200A8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60200D4,
            func_060200D4); // _GFCD_GetStat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020188,
            func_06020188); // _GFCD_MovePickup
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60201D4,
            func_060201D4); // _GFCD_MoveSctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020240, func_06020240);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020264,
            func_06020264); // _GFCD_GetSctInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60202AC,
            func_060202AC); // _GFCD_ChgDir
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020328,
            func_06020328); // _GFCD_SetFiltCon
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020420,
            func_06020420); // _GFCD_GetFileInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60204F8,
            func_060204F8); // _GFCD_GetBufSiz
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020530,
            func_06020530); // _GFCD_ExecServer
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602060C,
            func_0602060C); // _gfcd_isIdleTask
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020698,
            func_06020698); // _gfcd_doTask
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020744, func_06020744);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020758,
            func_06020758); // _GFCD_WaitServer
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020794,
            func_06020794); // _gfcd_doSetFiltTsk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602093C,
            func_0602093C); // _gfcd_doSetConTsk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60209C8,
            func_060209C8); // _gfcd_doGetLenDataTsk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020B18,
            func_06020B18); // _gfcd_doReqDataTsk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020BB8,
            func_06020BB8); // _gfcd_doDelSctDataTsk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020CE8,
            func_06020CE8); // _gfcd_doMoveSctTsk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6020E4C, func_06020E4C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021048, func_06021048);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021180, func_06021180);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60211A4,
            func_060211A4); // _gfcd_initCdbMng
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021224, func_06021224);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021250, func_06021250);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602126C, func_0602126C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021290, func_06021290);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60212AC,
            func_060212AC); // _GFCD_WaitScdqFlag
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60212F0,
            func_060212F0); // _GFCD_WaitPause
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602133C, func_0602133C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021358, func_06021358);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60213A0, func_060213A0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021434,
            func_06021434); // _GFMB_GetSrcPack
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60214B4, func_060214B4); // _GFMB_RtnPk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021500, func_06021500);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021510,
            func_06021510); // _GFMC_GetFileInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021564,
            func_06021564); // _GFMC_GetNumFile
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021594, func_06021594);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60215B4, func_060215B4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60215D8, func_060215D8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60215FC, func_060215FC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021638, func_06021638);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021654, func_06021654);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021670,
            func_06021670); // _GFSB_GetLenData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60216F4,
            func_060216F4); // _GFSB_GetSrcPack
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021770, func_06021770); // _GFSB_RtnPk
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60217C0,
            func_060217C0); // _gfsb_getActSiz
INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f602185A, func_0602185A);

// SEGA_SPR.A
// doesn't match as closely as SEGA_BUP, different version of lib?
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60218E8,
            func_060218E8); // SPR_SetTvMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021A58,
            func_06021A58); // SPR_GetStatus
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021AE8, func_06021AE8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022060, func_06022060);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022088,
            func_06022088); // SPR_SetEosMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60220B4, func_060220B4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60220EC, func_060220EC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022138, func_06022138);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022148, func_06022148);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022164, func_06022164);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022194, func_06022194);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022514,
            func_06022514); // SPR_2SetTvMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022588,
            func_06022588); // SPR_2FrameChgIntr
// func_060225C4 is SPR_2FrameEraseData, splitter bug
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60225F4, func_060225F4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602262C,
            func_0602262C); // SPR_2SetGourTbl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022678,
            func_06022678); // SPR_2SetLookupTbl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60226D0,
            func_060226D0); // SPR_2ClrAllChar
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022768,
            func_06022768); // SPR_2GourTblNoToVram
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60227AC,
            func_060227AC); // SPR_2LookupTblNoToVram
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60227E4,
            func_060227E4); // SPR_2CharNoToVram
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602281C,
            func_0602281C); // SPR_2GetAreaSizeInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602292C,
            func_0602292C); // SPR_2OpenCommand
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022A48, func_06022A48);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022C7C, func_06022C7C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022C9C,
            func_06022C9C); // SPR_2LocalCoord
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022D28,
            func_06022D28); // SPR_2SysClip
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022D98,
            func_06022D98); // SPR_2UserClip
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022E2C, func_06022E2C); // SPR_2Cmd
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022E8C,
            func_06022E8C); // SPR_2FlushDrawPrtyBlock
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60230B8,
            func_060230B8); // SlaveFlushDrawPrtyBlock
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023108, func_06023108);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023114,
            func_06023114); // SPR_RunSlaveSH
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023144, func_06023144);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60231C0,
            func_060231C0); // flushDrawPrtyBlock
INCLUDE_ASM("asm/saturn/zero/data", d6023394, d_06023394);

// SEGA_BUP.A
const char* bup_version = "BUP Version 1.25 1997-06-20";
const u32 pad_06030400 = 0x00000000;
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030404, func_06030404); // BUP_Init
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030478, func_06030478); // preProc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60304CC, func_060304CC); // postProc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030518,
            func_06030518); // change_dfunc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030554,
            func_06030554); // return_dfunc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030580, func_06030580); // dummy_func
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603058C, func_0603058C); // isConSeri
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60305CC, func_060305CC); // BUP_SelPart
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030640, func_06030640); // BUP_Format
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030690, func_06030690); // BUP_Stat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60306EC, func_060306EC); // BUP_Write
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030768, func_06030768); // BUP_Read
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60307C4, func_060307C4); // BUP_Delete
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603081C, func_0603081C); // BUP_Dir
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030898, func_06030898); // BUP_Verify
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60308F4, func_060308F4); // BUP_GetDate
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030968, func_06030968); // BUP_SetDate
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603099C, func_0603099C); // get_imask
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60309D4, func_060309D4); // set_imask
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030A20, func_06030A20); // set_sr
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030A30, func_06030A30); // get_sr

INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/data", d6030A4A, d_06030A4A);
