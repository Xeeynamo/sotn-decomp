// SPDX-License-Identifier: AGPL-3.0-only
#include "sattypes.h"
#include "inc_asm.h"

// SEGA_CDC.A

// _CDC_CdScan
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D660, func_0602D660);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D6BC, func_0602D6BC);

// _CDC_MpGetLastStat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D724, func_0602D724);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D754, func_0602D754);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D7CC, func_0602D7CC);

// _CDC_GetHwInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D86C, func_0602D86C);

// _CDC_TgetToc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D90C, func_0602D90C);

// _CDC_GetSes
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D98C, func_0602D98C);

// _CDC_CdInit
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D9FC, func_0602D9FC);

// _CDC_CdOpen
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DAD4, func_0602DAD4);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DB1C, func_0602DB1C);

// _CDC_DataEnd
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DBA4, func_0602DBA4);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DC14, func_0602DC14);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DC4C, func_0602DC4C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DC98, func_0602DC98);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DCA8, func_0602DCA8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DCE4, func_0602DCE4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DCFC, func_0602DCFC);

// _CDC_ClrHirqReq
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DD18, func_0602DD18);

// _CDREG_ClrHirqReq
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DD60, func_0602DD60);

// _CDREG_InitHirqReq
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DD88, func_0602DD88);

// _CDREG_SetHirqFlag
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DDBC, func_0602DDBC);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DDE8, func_0602DDE8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DE04, func_0602DE04);

// _CDC_GetMpegPtr
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DE2C, func_0602DE2C);

// _CDREG_TgetData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DE44, func_0602DE44);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DEDC, func_0602DEDC);

// _doCmdRsp
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602DF38, func_0602DF38);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E044, func_0602E044);

// _writeCmd
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E0A8, func_0602E0A8);

// _CDREG_ReadRsp
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E0FC, func_0602E0FC);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E150, func_0602E150);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E188, func_0602E188);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E1D4, func_0602E1D4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E1E4, func_0602E1E4);

// _CDC_ChgDir
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E200, func_0602E200);

// _CDC_ReadDir
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E268, func_0602E268);

// _CDC_GetFileScope
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E2D0, func_0602E2D0);

// _CDC_TgetFileInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E354, func_0602E354);

// _CDC_ReadFile
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E3E8, func_0602E3E8);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E458, func_0602E458);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E4B4, func_0602E4B4);

// _CDC_GetSctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E520, func_0602E520);

// _CDC_DelSctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E5A4, func_0602E5A4);

// _CDC_GetdelSctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E628, func_0602E628);

// _CDC_PutSctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E6AC, func_0602E6AC);

// _CDC_CopySctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E71C, func_0602E71C);

// _CDC_MoveSctData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E7B0, func_0602E7B0);

// _CDC_GetCopyErr
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E844, func_0602E844);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E8A8, func_0602E8A8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E914, func_0602E914);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602E998, func_0602E998);

// _CDC_GetFiltSubh
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EA50, func_0602EA50);

// _CDC_SetFiltMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EB14, func_0602EB14);

// _CDC_GetFiltMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EB80, func_0602EB80);

// _CDC_SetFiltCon
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EBF4, func_0602EBF4);

// _CDC_GetFiltCon
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EC84, func_0602EC84);

// _CDC_ResetSelector
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602ED08, func_0602ED08);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602ED74, func_0602ED74);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EDF8, func_0602EDF8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EE6C, func_0602EE6C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EEEC, func_0602EEEC);

// _chkEselUpdStatus
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EF50, func_0602EF50);

// _CDC_GetSctInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602EFA4, func_0602EFA4);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F06C, func_0602F06C);

// _CDC_GetFadSearch
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F0E0, func_0602F0E0);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F164, func_0602F164);

// _CDC_CdGetCon
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F1C0, func_0602F1C0);

// _CDC_CdGetLastBuf
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F224, func_0602F224);

// _CDC_MpSetImgPos
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F288, func_0602F288);

// _CDMSB_UpdMpstat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F2C4, func_0602F2C4);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F300, func_0602F300);

// _CDSUB_GetCdstat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F398, func_0602F398);

// _CDSUB_RspToCdstat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F3FC, func_0602F3FC);

// _CDSUB_SoftTimer
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602F46C, func_0602F46C);

INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/data", d602F49E, d_0602F49E);
