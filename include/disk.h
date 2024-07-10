#ifndef DISK_H
#define DISK_H

#include "types.h"

typedef enum {
    CdStep_None,
    CdStep_LoadInit,
    CdStep_SetSpeed,
    CdStep_SetPos,
    CdStep_Seek,
    CdStep_5,
    CdStep_6,
    CdStep_Complete = 10,
    CdStep_DmaErr = 0xC0,
    CdStep_SdHeaderErr = 0xC1,
    CdStep_DiskErr = 0xC2,
    CdStep_Retry = 0xD0,
    CdStep_RetryXa = 0xD1,
    CdStep_CdShellOpenErr = 0xF0,
    CdStep_F1 = 0xF1,
    CdStep_F2 = 0xF2,
    CdStep_F3 = 0xF3,
} CdStep;

typedef enum {
    CdFile_None,
    CdFile_Sel,
    CdFile_GameChr,
    CdFile_StageChr,
    CdFile_4,
    CdFile_RichterPrg,
    CdFile_Prologue,
    CdFile_Seq = 12,
    CdFile_StageSfx,
    CdFile_14,
    CdFile_15,
    CdFile_16,
    CdFile_Weapon0,
    CdFile_Weapon1,
    CdFile_AlucardPrg,
    CdFile_24 = 24,
    CdFile_25,
    CdFile_26,
    CdFile_ServantChr,
    CdFile_Monster,
    CdFile_ServantPrg,
    CdFile_30,
    CdFile_31,
    CdFile_DemoKey,
    CdFile_NoNext = 0xFF,
    CdFile_StagePrg = 0x100,
} CdFileType;

typedef enum {
    CdCallback_0,        // func_801080DC
    CdCallback_1,        // func_801080DC
    CdCallback_StageChr, // func_801080DC
    CdCallback_3,        // func_801080DC
    CdCallback_4,        // CopyStageOvlCallback
    CdCallback_5,        // func_801080DC
    CdCallback_6,        // func_801080DC
    CdCallback_7,        // func_801080DC
    CdCallback_StagePrg, // CopyStageOvlCallback
    CdCallback_9,        // CopyStageOvlCallback
    CdCallback_Ric,      // CopyRicOvlCallback
    CdCallback_11,       // func_801080DC
    CdCallback_12,       // func_801078C4
    CdCallback_13,       // func_801078C4
    CdCallback_Monster,  // CopyMonsterPreviewCallback
    CdCallback_Familiar, // func_801078C4
    CdCallback_16,       // func_80107DB4
    CdCallback_17,       // func_80107C6C
    CdCallback_Seq,      // func_80107DB4
    CdCallback_Vh,       // func_80107EF0
} CdCallbacks;

extern s32 g_UseDisk;
extern u32 g_CdStep; // CdStep
extern s32 g_IsUsingCd;

#endif // DISK_H
