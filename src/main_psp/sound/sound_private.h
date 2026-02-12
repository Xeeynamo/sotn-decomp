// SPDX-License-Identifier: AGPL-3.0-or-later
#include <common.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspthreadman.h>
#include <pspiofilemgr.h>
#include <pspatrac3.h>
#include <pspkerror.h>
#include <pspumd.h>

typedef struct {
    s32 fd;
    char assignName[10];
} StrFile;

typedef struct {
    s32 atracID;     // ATRAC playback ID
    StrFile strFile; // File structure
    s32 playFlag; // Event flag indicating status Used for cueing, playing, and
                  // ending
    s32 outputChannel; // Channel when outputting to libwave
    s32 iEndSample;
    s32 iVol;
    s32 fileSize;
    s32 unk28;
} SceAtracArg;

typedef struct {
    char* filename;     // "ATRAC3plus" file
    u8* pucFirstBuf;    // FirstBuffer starting address
    s32 iFirstBufSize;  // FirstBuffer size
    u8* pucSecondBuf;   // SecondBuffer starting address
    s32 iSecondBufSize; // SecondBuffer size
    s32 iOutputChannel; // Output channel
    SceUID playFlag;    // Event flag for setting playback mode
    s32 loop;
    s32 fileSize;
} SceBGMArg;

// clang-format off
// Values for setting playback mode and EVENTFLAG
#define BGM_INIT_END              (0x00000001U) // Status when playback initialization ended
#define BGM_PLAY_START            (0x00000002U) // Status when playback start instruction was received
#define BGM_RESET_POSITION        (0x00000004U) // Status when playback position changes
#define BGM_PLAY_FINISH           (0x00000008U) // Status when playback termination is specified
#define BGM_INIT_START            (0x00000010U) // Status when playback initialization starts
#define BGM_UNK_20                (0x00000020U)
#define BGM_UNK_40                (0x00000040U)
#define BGM_UNK_80                (0x00000080U)
#define BGM_UNK_100               (0x00000100U)
// clang-format on
