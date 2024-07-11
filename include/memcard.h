#ifndef MEMCARD_H
#define MEMCARD_H

// save manager
// port: 0 or 1, it is the physical port where you plug the memory card.
// port_s: 0-3, valid only in the context of multi tap, unused in this game.
// channel: the numerical combination of port and port_s
// block: 0-14, a memory card can store up to 15 blocks

// TODO: include types instead of common
#include "common.h"
#include "gamesettings.h"
#include "menunavigation.h"
#include "player.h"
#include <psxsdk/kernel.h>
#include <psxsdk/libapi.h>

#define PORT_COUNT (2)
#define BLOCK_PER_CARD (15)
#define CARD_BLOCK_SIZE (8192)

typedef struct {
    /* 0x000 */ struct DIRENTRY entries[BLOCK_PER_CARD];
    /* 0x258 */ u32 unk258;
    /* 0x25C */ u32 unk25C;
    /* 0x260 */ u32 nBlockUsed;
    /* 0x264 */ s32 nFreeBlock;
    /* 0x268 */ u8 blocks[BLOCK_PER_CARD];
} MemcardInfo; /* size=0x278 */

extern MemcardInfo g_MemcardInfo[2];
extern s32 g_MemcardBlockRead;
extern s32 g_MemcardPortMask[];
extern u16 g_saveIconPal0[0x10][0x10];
extern u8* g_saveIconTexture[0x10];

typedef struct {
    /* 0x00 */ u8 Magic[2];
    /* 0x02 */ u8 Type;
    /* 0x03 */ u8 BlockEntry;
    /* 0x04 */ u8 Title[64];
    /* 0x44 */ u8 reserve[28];
    /* 0x60 */ u8 Clut[32];
    /* 0x80 */ u8 Icon[3][128];
} MemcardHeader; /* size=0x200 */

typedef struct {
    /* 0x00 */ char name[12];
    /* 0x0C */ s32 level;
    /* 0x10 */ s32 gold;
    /* 0x14 */ s32 playHours;
    /* 0x18 */ s32 playMinutes;
    /* 0x1C */ s32 playSeconds;
    /* 0x20 */ s32 cardIcon;
    /* 0x24 */ s32 endGameFlags;
    /* 0x28 */ s16 stage;
    /* 0x2A */ u16 nRoomsExplored;
    /* 0x2C */ u16 roomX;
    /* 0x2E */ u16 roomY;
    /* 0x30 */ s32 character;
    /* 0x34 */ s32 saveSize;
} SaveInfo; /* 0x38 */

typedef struct {
    /* 0x000 */ MemcardHeader header;
    /* 0x200 */ SaveInfo info;
    /* 0x238 */ PlayerStatus status;
    /* 0x56C */ MenuNavigation menuNavigation;
    /* 0x5B8 */ GameSettings settings;
    /* 0x6C8 */ u8 castleFlags[0x300];
    /* 0x6C8 */ u8 castleMap[0x800];
    /* 0x11C8 */ s32 rng;
} SaveData; /* size = 0x11CC */

extern const char g_MemcardSavePath[];
extern const char g_strMemcardRootPath[];
extern u8 g_SaveName[12] ALIGNED4;

typedef long Event;

extern Event g_EvSwCardEnd; // 80073068
extern Event g_EvSwCardErr; // 8007306C
extern Event g_EvSwCardTmo; // 80073070
extern Event g_EvSwCardNew; // 80073078
extern Event g_EvHwCardEnd;
extern Event g_EvHwCardErr;
extern Event g_EvHwCardTmo;
extern Event g_EvHwCardNew;

#if defined(VERSION_US)
#define MEMCARD_ID "BASLUS-00067DRAX00"
#elif defined(VERSION_HD)
#define MEMCARD_ID "BISLPM-86023DRAX00"
#endif

#endif
