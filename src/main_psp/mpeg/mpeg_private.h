// SPDX-License-Identifier: AGPL-3.0-or-later
#include <common.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h

#include <pspmpeg.h>
#include <pspiofilemgr.h>

#define DISPLAY_MODE_NORMAL (0x01)
#define DISPLAY_MODE_SKIP (0x02)
#define DISPLAY_MODE_WAIT (0x03)
#define DISPLAY_MODE_UNK (0x04)
#define DISPLAY_MODE_END (0xFF)

typedef struct t_displayBuffer {
    s32 startSema;
    s32 lockSema;
    s32 displayWaitSema;
    u8** buf;
    u32* pts;
    s32* write;
    s32* read;
    s32* count;
    s32* size;
    s32 pixelFormat;
    s32* displayMode;
} t_displayBuffer;

typedef struct t_soundBuffer {
    s32 lockSema;
    s32* unk4;
    u8** buf;
    u32* pts;
    s32* write;
    s32* read;
    s32* count;
    s32* size;
    s32 startSema;
} t_soundBuffer;

typedef struct t_avSync_Video {
    u32* pts;
    s32 write;
    s32 read;
    s32 count;
    s32 size;
} t_avSync_Video;

typedef struct t_avSyncControl {
    t_displayBuffer* pDisp;
    t_soundBuffer* pSound;
    t_avSync_Video video;
} t_avSyncControl;

typedef struct unkStruct2 {
    u32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u32 unk10;
    u32 unk14;
    s32 unk18;
    u8* unk1C;
    s32 unk20;
    u8 unk24;
    u8 unk25;
    s16 unk26;
    u32 unk28;
    u32 unk2C;
    s32 unk30;
} unkStruct2;

typedef struct StrFile {
    s32 fd;
    s32 unk4;
    unkStruct2* unk8;
    s32 unkC;
    s32 unk10;
    s16 unk14;
    u8 unk16[0x200];
} StrFile;

typedef struct t_mpegStreamData {
    SceMpegStream* pAvcStream;
    SceMpegAu* pAvcAu;
    SceMpegStream* pAtracStream;
    SceMpegAu* pAtracAu;
} t_mpegStreamData;

typedef struct t_ringBuffer {
    s32 dataLen;
    s32 decodeSleepSema;
    SceMpegRingbuffer* pRingbuf;
    s32* statusFlag;
    s32 unk10;
    u8* unk14;
    StrFile* pStrFile;
    unkStruct2 unk1C;
} t_ringBuffer;

SceOff func_psp_089168E8(StrFile*, SceOff, s32);
