#ifndef GAME_H
#define GAME_H
#include <psxsdk/kernel.h>
#include <psxsdk/libapi.h>
#include <psxsdk/libc.h>
#include <psxsdk/libcd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/libgpu.h>
#include <psxsdk/libgs.h>
#include <psxsdk/libgte.h>
#include <psxsdk/libsnd.h>

#define PAD_COUNT 2
#define PAD_L2 0x0001
#define PAD_R2 0x0002
#define PAD_L1 0x0004
#define PAD_R1 0x0008
#define PAD_TRIANGLE 0x0010
#define PAD_CIRCLE 0x0020
#define PAD_CROSS 0x0040
#define PAD_SQUARE 0x0080
#define PAD_SELECT 0x0100
#define PAD_L3 0x0200
#define PAD_R3 0x0400
#define PAD_START 0x0800
#define PAD_UP 0x1000
#define PAD_RIGHT 0x2000
#define PAD_DOWN 0x4000
#define PAD_LEFT 0x8000

#define RENDERFLAGS_NOSHADOW 2
#define PLAYER_ALUCARD 0
#define PLAYER_RICHTER 1
#define MAX_GOLD 999999
#define HEART_VESSEL_INCREASE 5
#define HEART_VESSEL_RICHTER 30
#define LIFE_VESSEL_INCREASE 5
#define FALL_GRAVITY 0x4000
#define FALL_TERMINAL_VELOCITY 0x60000

#define TOTAL_ENTITY_COUNT 256
#define MaxEntityCount 32

#define PROGRAM_NO0 0x00
#define PROGRAM_NO1 0x01
#define PROGRAM_LIB 0x02
#define PROGRAM_CAT 0x03
#define PROGRAM_NO2 0x04
#define PROGRAM_CHI 0x05
#define PROGRAM_DAI 0x06
#define PROGRAM_NP3 0x07
#define PROGRAM_CEN 0x08
#define PROGRAM_NO4 0x09
#define PROGRAM_ARE 0x0A
#define PROGRAM_TOP 0x0B
#define PROGRAM_NZ0 0x0C
#define PROGRAM_NZ1 0x0D
#define PROGRAM_WRP 0x0E
#define PROGRAM_NO1_ALT 0x0F
#define PROGRAM_NO0_ALT 0x10
#define PROGRAM_DRE 0x12
#define PROGRAM_BO7 0x16
#define PROGRAM_MAR 0x17
#define PROGRAM_BO6 0x18
#define PROGRAM_BO5 0x19
#define PROGRAM_BO4 0x1A
#define PROGRAM_BO3 0x1B
#define PROGRAM_BO2 0x1C
#define PROGRAM_BO1 0x1D
#define PROGRAM_BO0 0x1E
#define PROGRAM_ST0 0x1F
#define PROGRAM_MAD 0x40
#define PROGRAM_NO3 0x41
#define PROGRAM_IWA_LOAD 0x42
#define PROGRAM_IGA_LOAD 0x43
#define PROGRAM_HAGI_LOAD 0x44
#define PROGRAM_UNKNOWN 0x45
#define PROGRAM_TE1 0x46
#define PROGRAM_TE2 0x47
#define PROGRAM_TE3 0x48
#define PROGRAM_TE4 0x49
#define PROGRAM_TE5 0x4A
#define PROGRAM_TOP_ALT 0x4B
#define PROGRAM_INVERTEDCASTLE_FLAG 0x20
#define PROGRAM_ENDING 0xFE
#define PROGRAM_MEMORYCARD 0xFF

#define LBA_BIN_F_GAME 0x61CE
#define LBA_BIN_F_GAME2 0x6252
#define LBA_STAGE_MAD_ART 0x7D6F
#define LBA_STAGE_MAD_VH 0x7DEF
#define LBA_STAGE_MAD_BIN 0x7E28
#define LBA_STAGE_NO0_ART 0x7E5D
#define LBA_STAGE_NO0_VH 0x7EDD
#define LBA_STAGE_NO0_BIN 0x7F16
#define LBA_STAGE_NO3_ART 0x8297
#define LBA_STAGE_NO3_VH 0x8317
#define LBA_STAGE_NO3_BIN 0x834F
#define LBA_STAGE_ST0_ART 0x9044
#define LBA_STAGE_ST0_VH 0x90C4
#define LBA_STAGE_ST0_BIN 0x90F9
#define LBA_STAGE_NP3_ART 0x917F
#define LBA_STAGE_NP3_VH 0x91FF
#define LBA_STAGE_NP3_BIN 0x9235

struct Entity;

typedef void (*PfnEntityUpdate)(struct Entity*);

typedef union {
    s32 val;
    struct {
        s16 lo;
        s16 hi;
    } i;
} f32;

#include "unkstruct.h"

typedef struct {
    unsigned char width;
    unsigned char height;
    unsigned short unk2;
    unsigned char data[0];
} ImgSrc;

typedef struct {
    /* 0x00 */ s16 cursorX;
    /* 0x02 */ s16 cursorY;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ RECT unk1;
    /* 0x10 */ s16 w;
    /* 0x10 */ s16 h;
    /* 0x14 */ int unk14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
} MenuContext; // size = 0x1E

typedef struct {
    /* 0x0 */ u8 tileLayoutId;
    /* 0x1 */ u8 tilesetId;
    /* 0x2 */ u8 objGfxId;
    /* 0x3 */ u8 objLayoutId;
} RoomLoadDef; // size = 0x4

typedef struct {
    /* 0x0 */ u8 left;
    /* 0x1 */ u8 top;
    /* 0x2 */ u8 right;
    /* 0x3 */ u8 bottom;
    /* 0x4 */ RoomLoadDef load;
} RoomHeader; // size = 0x8

typedef struct {
    /* 0x0 */ s16 pressed;
    /* 0x2 */ s16 previous;
    /* 0x4 */ s16 tapped;
    /* 0x6 */ s16 repeat;
} Pad; // size = 0x8

typedef struct Entity {
    /* 0x00 */ f32 posX;
    /* 0x04 */ f32 posY;
    /* 0x08 */ s32 accelerationX;
    /* 0x0C */ s32 accelerationY;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u16 facing;
    /* 0x16 */ u16 palette;
    /* 0x18 */ s8 blendMode;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ u16 zPriority;
    /* 0x26 */ u16 objectId;
    /* 0x28 */ PfnEntityUpdate pfnUpdate;
    /* 0x2C */ u16 step;
    /* 0x2E */ u16 unk2E;
    /* 0x30 */ u16 subId;
    /* 0x32 */ u16 objectRoomIndex;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ u16 unk3C;
    /* 0x3E */ s16 hitPoints;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ s16 unk42;
    /* 0x44 */ u16 unk44;
    /* 0x46 */ u8 hitboxWidth;
    /* 0x47 */ u8 hitboxHeight;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ s32* unk4C;
    /* 0x50 */ u16 animationFrameIndex;
    /* 0x52 */ s16 animationFrameDuration;
    /* 0x54 */ s16 animationSet;
    /* 0x56 */ s16 animationFrame;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 firstPolygonIndex;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 unk6C;
    /* 0x6D */ s8 unk6D;
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ Multi16 unk7C; // posX
    union {
        /* 0x7E */ u16 modeU16;
        struct {
            /* 0x7E */ u8 unk0;
            /* 0x7F */ u8 unk1;
        } modeU8;
    } unk7E; // posY
    union {
        /* 0x80 */ struct Entity* entityPtr;
        /* 0x80 */ s32 modeS32;
        struct {
            /* 0x80 */ s16 unk0;
            /* 0x82 */ s16 unk2;
        } modeS16;
        struct {
            /* 0x80 */ u8 unk0;
            /* 0x81 */ u8 unk1;
        } modeS8;
    } unk80; // size = 0x4
    /* 0x84 */ Multi unk84;
    /* 0x88 */ Multi unk88; // this is a Multi: refer to EntityWarpSmallRocks
    union {
        /* 0x8C */ struct Entity* entityPtr;
        /* 0x8C */ s32 modeS32;
        struct {
            /* 0x8C */ u16 unk0;
            /* 0x8E */ u16 unk2;
        } modeU16;
    } unk8C; // size = 0x4
    /* 0x90 */ s32 unk90;
    /* 0x94 */ u8 unk94;
    /* 0x95 */ u8 unk95;
    /* 0x96 */ s16 unk96;
    /* 0x98 */ s32 unk98;
    /* 0x9C */ s32 unk9C;
    /* 0xA0 */ s16 unkA0;
    /* 0xA2 */ s16 unkA2;
    /* 0xA4 */ s32 unkA4;
    /* 0xA8 */ s32 unkA8;
    /* 0xAC */ u8 unkAC;
    /* 0xAD */ s8 unkAD;
    /* 0xAE */ s8 unkAE;
    /* 0xAF */ s8 unkAF;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ s16 unkB6;
    union {
        /* 0xB8 */ void (*unkFuncB8)(struct Entity*, u32, struct Entity*);
        /* 0xB8 */ struct Entity* entityPtr;
        struct {
            /* 0xB8 */ u8 unk0;
            /* 0xB9 */ u8 unk1;
            /* 0xBA */ u8 unk2;
            /* 0xBB */ u8 unk3;
        } modeU8;
    } unkB8;
} Entity; // size = 0xBC

typedef struct {
    /* 0x00 */ u16 animationSet;
    /* 0x02 */ u16 zPriority;
    /* 0x04 */ Multi16 unk4;
    /* 0x06 */ u16 palette;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 blendMode;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u32 unkC;
    /* 0x10 */ const u8* unk10;
} ObjInit2; // size = 0x14

typedef enum { MONO, STEREO } SoundMode;

typedef struct {
    /* 0x00 */ DRAWENV draw; // drawing environment
    /* 0x58 */ DISPENV disp; // display environment
} DisplayBuffer;

typedef struct {
    /* 0x00000 */ void* unk0;
    /* 0x00004 */ DisplayBuffer buf;
    /* 0x00074 */ char pad74[0x400];
    /* 0x00474 */ u32 _unk_0474[0x200];
    /* 0x00474 */ DR_MODE drawModes[0x400];
    /* 0x03C74 */ POLY_GT4 polyGT4[0x300];
    /* 0x0D874 */ POLY_G4 polyG4[0x100];
    /* 0x0FC74 */ POLY_GT3 polyGT3[0x30];
    /* 0x103F4 */ LINE_G2 lineG2[0x100];
    /* 0x117F4 */ SPRT_16 sprite16[0x280];
    /* 0x13FF4 */ TILE tiles[0x100];
    /* 0x14FF4 */ SPRT sprite[0x200];
} GpuBuffer; /* size = 0x177F4 */

typedef struct {
    /* 0x00 */ u32 drawModes;
    /* 0x04 */ u32 gt4;
    /* 0x08 */ u32 g4;
    /* 0x0C */ u32 gt3;
    /* 0x10 */ u32 line;
    /* 0x14 */ u32 sp16;
    /* 0x18 */ u32 tile;
    /* 0x1C */ u32 sp;
    /* 0x20 */ u32 env;
} GpuUsage;

typedef struct {
    u32 unk0;
    s32 hp;
    s32 hpMax;
    s32 hearts;
    s32 heartsMax;
    s32 mp;
    s32 mpMax;
    s32 statStr;
    s32 statCon;
    s32 statInt;
    s32 statLck;
} PlayerStats;

typedef struct {
    s32 hours;
    s32 minutes;
    s32 seconds;
    s32 frames;
} GameTimer;

typedef struct {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u32 unk4;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u32 unkC;
} SaveData_Unk238;

typedef struct {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u32 unk4;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u32 unkC;
} SaveData_Unk56C;

typedef struct {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u32 unk4;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u32 unkC;
} SaveData_Unk5B8;

typedef struct {
    /* 0x000 */ u32 unk00;
    /* 0x004 */ u32 unk04;
    /* 0x008 */ u32 unk08;
    /* 0x00C */ u32 unk0C;
    /* 0x010 */ u32 unk10;
    /* 0x014 */ u32 unk14;
    /* 0x018 */ u32 unk18;
    /* 0x01C */ u32 unk1C;
    /* 0x020 */ u32 unk20;
    /* 0x024 */ u32 unk24;
    /* 0x028 */ u32 unk28;
    /* 0x02C */ u32 unk2C;
    /* 0x030 */ u32 unk30;
    /* 0x034 */ u32 unk34;
    /* 0x038 */ u32 unk38;
    /* 0x03C */ u32 unk3C;
    /* 0x040 */ u32 unk40;
    /* 0x044 */ u32 unk44;
    /* 0x048 */ u32 unk48;
    /* 0x04C */ u32 unk4C;
    /* 0x050 */ u32 unk50;
    /* 0x054 */ u32 unk54;
    /* 0x058 */ u32 unk58;
    /* 0x05C */ u32 unk5C;
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u32 unk64;
    /* 0x068 */ u32 unk68;
    /* 0x06C */ u32 unk6C;
    /* 0x070 */ u32 unk70;
    /* 0x074 */ u32 unk74;
    /* 0x078 */ u32 unk78;
    /* 0x07C */ u32 unk7C;
    /* 0x080 */ u32 unk80;
    /* 0x084 */ u32 unk84;
    /* 0x088 */ u32 unk88;
    /* 0x08C */ u32 unk8C;
    /* 0x090 */ u32 unk90;
    /* 0x094 */ u32 unk94;
    /* 0x098 */ u32 unk98;
    /* 0x09C */ u32 unk9C;
    /* 0x0A0 */ u32 unkA0;
    /* 0x0A4 */ u32 unkA4;
    /* 0x0A8 */ u32 unkA8;
    /* 0x0AC */ u32 unkAC;
    /* 0x0B0 */ u32 unkB0;
    /* 0x0B4 */ u32 unkB4;
    /* 0x0B8 */ u32 unkB8;
    /* 0x0BC */ u32 unkBC;
    /* 0x0C0 */ u32 unkC0;
    /* 0x0C4 */ u32 unkC4;
    /* 0x0C8 */ u32 unkC8;
    /* 0x0CC */ u32 unkCC;
    /* 0x0D0 */ u32 unkD0;
    /* 0x0D4 */ u32 unkD4;
    /* 0x0D8 */ u32 unkD8;
    /* 0x0DC */ u32 unkDC;
    /* 0x0E0 */ u32 unkE0;
    /* 0x0E4 */ u32 unkE4;
    /* 0x0E8 */ u32 unkE8;
    /* 0x0EC */ u32 unkEC;
    /* 0x0F0 */ u32 unkF0;
    /* 0x0F4 */ u32 unkF4;
    /* 0x0F8 */ u32 unkF8;
    /* 0x0FC */ u32 unkFC;
    /* 0x100 */ u32 unk100;
    /* 0x104 */ u32 unk104;
    /* 0x108 */ u32 unk108;
    /* 0x10C */ u32 unk10C;
    /* 0x110 */ u32 unk110;
    /* 0x114 */ u32 unk114;
    /* 0x118 */ u32 unk118;
    /* 0x11C */ u32 unk11C;
    /* 0x120 */ u32 unk120;
    /* 0x124 */ u32 unk124;
    /* 0x128 */ u32 unk128;
    /* 0x12C */ u32 unk12C;
    /* 0x130 */ u32 unk130;
    /* 0x134 */ u32 unk134;
    /* 0x138 */ u32 unk138;
    /* 0x13C */ u32 unk13C;
    /* 0x140 */ u32 unk140;
    /* 0x144 */ u32 unk144;
    /* 0x148 */ u32 unk148;
    /* 0x14C */ u32 unk14C;
    /* 0x150 */ u32 unk150;
    /* 0x154 */ u32 unk154;
    /* 0x158 */ u32 unk158;
    /* 0x15C */ u32 unk15C;
    /* 0x160 */ u32 unk160;
    /* 0x164 */ u32 unk164;
    /* 0x168 */ u32 unk168;
    /* 0x16C */ u32 unk16C;
    /* 0x170 */ u32 unk170;
    /* 0x174 */ u32 unk174;
    /* 0x178 */ u32 unk178;
    /* 0x17C */ u32 unk17C;
    /* 0x180 */ u32 unk180;
    /* 0x184 */ u32 unk184;
    /* 0x188 */ u32 unk188;
    /* 0x18C */ u32 unk18C;
    /* 0x190 */ u32 unk190;
    /* 0x194 */ u32 unk194;
    /* 0x198 */ u32 unk198;
    /* 0x19C */ u32 unk19C;
    /* 0x1A0 */ u32 unk1A0;
    /* 0x1A4 */ u32 unk1A4;
    /* 0x1A8 */ u32 unk1A8;
    /* 0x1AC */ u32 unk1AC;
    /* 0x1B0 */ u32 unk1B0;
    /* 0x1B4 */ u32 unk1B4;
    /* 0x1B8 */ u32 unk1B8;
    /* 0x1BC */ u32 unk1BC;
    /* 0x1C0 */ u32 unk1C0;
    /* 0x1C4 */ u32 unk1C4;
    /* 0x1C8 */ u32 unk1C8;
    /* 0x1CC */ u32 unk1CC;
    /* 0x1D0 */ u32 unk1D0;
    /* 0x1D4 */ u32 unk1D4;
    /* 0x1D8 */ u32 unk1D8;
    /* 0x1DC */ u32 unk1DC;
    /* 0x1E0 */ u32 unk1E0;
    /* 0x1E4 */ u32 unk1E4;
    /* 0x1E8 */ u32 unk1E8;
    /* 0x1EC */ u32 unk1EC;
    /* 0x1F0 */ u32 unk1F0;
    /* 0x1F4 */ u32 unk1F4;
    /* 0x1F8 */ u32 unk1F8;
    /* 0x1FC */ u32 unk1FC;
    /* 0x200 */ u32 unk200;
    /* 0x204 */ u32 unk204;
    /* 0x208 */ u32 unk208;
    /* 0x20C */ u32 level;
    /* 0x210 */ u32 goldAmount;
    /* 0x214 */ u32 playTimeHours;
    /* 0x218 */ u32 playTimeMinutes;
    /* 0x21C */ u32 playTimeSeconds;
    /* 0x220 */ u32 unk220;
    /* 0x224 */ u32 isTimeAttackUnlocked; // g_IsTimeAttackUnlocked
    /* 0x228 */ s16 stageID;
    /* 0x22A */ u16 exploredRoomCount;
    /* 0x22C */ u16 roomX;
    /* 0x22E */ u16 roomY;
    /* 0x230 */ u32 playableCharacter;
    /* 0x234 */ u32 saveSize;
    /* 0x238 */ SaveData_Unk238 unk238[51]; // relics and equip?
    /* 0x568 */ u32 unk568;
    /* 0x56C */ SaveData_Unk56C unk56C[16];
    /* 0x5AC */ u32 unk5AC;
    /* 0x5B0 */ u32 unk5B0;
    /* 0x5B4 */ u32 unk5B4;
    /* 0x5B8 */ SaveData_Unk5B8 unk5B8[17];
    /* 0x6C4 */ u32 unk6C4;
    /* 0x6C8 */ u8 unk[0x11CC - 0x6C8];
} SaveData; /* size = 0x11CC */

typedef struct {
    /* 8003C774 */ void (*Update)(void);
    /* 8003C778 */ void (*TestCollisions)(void);
    /* 8003C77C */ void (*unk08)(void);
    /* 8003C780 */ void (*InitRoomEntities)(s32 layoutId);
    /* 8003C784 */ RoomHeader* rooms;
    /* 8003C788 */ s16** spriteBanks;
    /* 8003C78C */ s32** cluts;
    /* 8003C790 */ void* unk1C;       // related to object layout
    /* 8003C794 */ void** tileLayers; // related to tiles layout
    /* 8003C798 */ void** entityGfxs;
    /* 8003C79C */ void (*unk28)(void);
    /* 8003C7A0 */ void (*unk2c)(void); // similar to Update
    /* 8003C7A4 */ void* unk30;
    /* 8003C7A8 */ s32* unk34;
    /* 8003C7AC */ s32* unk38;
    /* 8003C7B0 */ void (*unk3C)();
} Overlay;

typedef struct RoomDimensions {
    /* 0x00 */ s32 hSize;
    /* 0x04 */ s32 vSize;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 left;
    /* 0x10 */ s32 top;
    /* 0x14 */ s32 right;
    /* 0x18 */ s32 bottom;
    /* 0x1C */ s32 x;
    /* 0x20 */ s32 y;
    /* 0x24 */ s32 width;
    /* 0x28 */ s32 height;
} RoomDimensions;

typedef struct CollisionResult {
    /* 0x00 */ s32 unk0; // if not 0 it collides
    /* 0x04 */ u32 unk4;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u32 unkC;
    /* 0x10 */ u32 unk10;
    /* 0x14 */ s16 unk14; // rightRepel
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18; // bottomRepel
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ u8 pad2[2];
} CollisionResult; /* size=0x24 */

typedef struct {
    /* 8003C774 */ Overlay o;
    /* 8003C7B4 */ void (*FreePolygons)(s32);
    /* 8003C7B8 */ s16 (*AllocPolygons)(s32 primitives, s32 count);
    /* 8003C7BC */ void (*CheckCollision)(s32 x, s32 y, CollisionResult* res,
                                          s32 unk);
    /* 8003C7C0 */ void (*func_80102CD8)(s32 arg0);
    /* 8003C7C4 */ void* func_8010DDA0;
    /* 8003C7C8 */ void (*AccelerateX)(s32 value);
    /* 8003C7CC */ Entity* (*GetFreeDraEntity)(s16 start, s16 end);
    /* 8003C7D0 */ void* func_800FE728;
    /* 8003C7D4 */ void (*func_800EA5E4)(s32);
    /* 8003C7D8 */ void (*func_800EAF28)(s32);
    /* 8003C7DC */ void (*PlaySfx)(s32 sfxId);
    /* 8003C7E0 */ void* func_800EDB58;
    /* 8003C7E4 */ void (*func_800EA538)(s32 arg0);
    /* 8003C7E8 */ void (*g_pfn_800EA5AC)(u16 arg0, u8 arg1, u8 arg2, u8 arg3);
    /* 8003C7EC */ void* func_801027C4;
    /* 8003C7F0 */ void* func_800EB758;
    /* 8003C7F4 */ void* func_8011AAFC;
    /* 8003C7F8 */ bool (*func_80131F68)(void);
    /* 8003C7FC */ DR_ENV* (*func_800EDB08)(POLY_GT4* poly);
    /* 8003C800 */ void* func_80106A28;
    /* 8003C804 */ void* func_80118894;
    /* 8003C808 */ Unkstruct5* D_800A8900;
    /* 8003C80C */ void* func_80118970;
    /* 8003C810 */ void* func_80118B18;
    /* 8003C814 */ void* func_8010DB38;
    /* 8003C818 */ void* func_8010DBFC;
    /* 8003C81C */ void* func_80118C28;
    /* 8003C820 */ void (*func_8010E168)(s32 arg0, s16 arg1);
    /* 8003C824 */ void (*func_8010DFF0)(s32 arg0, s32 arg1);
    /* 8003C828 */ void* func_800FF128;
    /* 8003C82C */ void (*func_800EB534)(s32 equipIcon, s32 palette, s32 index);
    /* 8003C830 */ s32 D_800A4B04;
    /* 8003C834 */ s32 D_800A7718;
    /* 8003C838 */ void (*AddHearts)(s32 value);
    /* 8003C83C */ void* func_8010715C;
    /* 8003C840 */ void* func_800FD4C0;
    /* 8003C844 */ void* func_8010E0A8;
    /* 8003C848 */ void (*func_800FE044)(s32, s32);
    /* 8003C84C */ void (*func_800FD874)(u16 context, s32 arg1);
    /* 8003C850 */ void* D_800A8720;
    /* 8003C854 */ void* func_800FF7B8;
    /* 8003C858 */ s32 (*func_80134714)(s32 arg0, s32 arg1, s32 arg2);
    /* 8003C85C */ s32 (*func_80134678)(s16 arg0, u16 arg1);
    /* 8003C860 */ void (*func_800F53A4)(void);
    /* 8003C864 */ u32 (*CheckEquipmentItemCount)(u32 itemId, u32 equipType);
    /* 8003C868 */ void (*func_8010BF64)(Unkstruct_8010BF64* arg0);
    /* 8003C86C */ void (*func_800F1FC4)(s32 arg0);
    /* 8003C870 */ void* func_800F2288;
    /* 8003C874 */ void* func_8011A3AC;
    /* 8003C878 */ s32 (*func_800FF460)(s32 arg0);
    /* 8003C87C */ void* func_800FF494;
    /* 8003C880 */ bool (*func_80133940)(void);
    /* 8003C884 */ bool (*func_80133950)(void);
    /* 8003C888 */ bool (*func_800F27F4)(s32 arg0);
    /* 8003C88C */ s32 (*func_800FF110)(s32 arg0);
    /* 8003C890 */ s32 (*func_800FD664)(s32 arg0);
    /* 8003C894 */ s32 (*func_800FD5BC)(Unkstruct_800FD5BC* arg0);
    /* 8003C898 */ void* func_800FDCE0;
    /* 8003C89C */ void (*func_800E2438)(const char* str);
    /* 8003C8A0 */ void* unused12C;
    /* 8003C8A4 */ void* unused130;
    /* 8003C8A8 */ void* unused134;
    /* 8003C8AC */ void* unused138;
    /* 8003C8B4 */ void* unused13C;
} GameApi; /* size=0x140 */

extern s32 D_8003925C;
extern bool g_IsTimeAttackUnlocked;
extern s32 D_8003C0EC[4];
extern s32 D_8003C0F8;
extern s32 D_8003C100;
extern u16 D_8003C104[];
extern u16 D_8003C3C2[]; // confirmed array
extern Unkstruct5* D_8003C704;
extern u16 D_8003C708;
extern s32 D_8003C728;
extern s32 D_8003C730;
extern s32 D_8003C734;
extern s32 D_8003C73C;
extern void (*D_8003C744)(s32, s32);
extern GameApi g_api;
#ifndef STAGE_MAD
extern void (*g_pfnInitRoomEntities)(void);
#endif
extern u32 D_8003C8C4;
extern s32 g_roomCount;
extern s32 D_8003C99C;
extern u16 D_8003C9C8;
extern s32 D_8003C9CC[];
extern s32 g_CurrentPlayableCharacter;
extern s32 D_8003C9A4; // related to when player change stages?
extern s32 g_blinkTimer;
extern s32 g_menuMainCursorIndex;
extern s32 g_menuRelicsCursorIndex[];
extern s32 g_SettingsCloakMode;
extern s32 g_SettingsSoundMode;
extern s32 D_8003CACC;
extern s32 D_8003CB00[];
extern s32 D_8003CB04;
extern GpuBuffer D_8003CB08;
extern GpuBuffer D_800542FC;
extern s16 D_80054302;     // TODO overlap, hard to remove
extern DISPENV D_8005435C; // TODO overlap, hard to remove
extern const char g_strMemcardSavePath[];
extern const char g_strMemcardRootPath[];
extern s32 D_8006BAFC;
extern s32 D_8006BB00;
extern s32 D_8006C374;
extern s32 D_8006C378;
extern GpuBuffer* D_8006C37C;
extern s32 D_8006C384;
extern s32 D_8006C388;
extern s32 D_8006C38C;
extern s32 D_8006C390;
extern s32 D_8006C384;
extern s32 D_8006C388;
extern s32 D_8006C38C;
extern s32 D_8006C390;
extern s32 D_8006C398;
extern s32 D_8006C3AC;
extern s32 g_backbufferX;
extern s32 g_backbufferY;
extern s32 D_8006C3B0;
extern Entity* g_CurrentEntity;
extern Unkstruct_8006C3CC D_8006C3C4[32];
extern s32 D_8006CBC4;
extern u16 g_Clut[];
extern Unkstruct4 D_80072B34;
extern s32 D_80072EE8;
extern s32 D_80072EEC;
extern s32 D_80072EF4;
extern u16 D_80072EF6;
extern s32 D_80072EFC;
extern s16 D_80072F00[];
extern s16 D_80072F02[];
extern s16 D_80072F04;
extern s16 D_80072F0A;
extern s16 D_80072F0C;
extern s16 D_80072F10;
extern s16 D_80072F14[]; // could be an array or a struct
extern s16 D_80072F16[];
extern s16 D_80072F18;
extern s16 D_80072F1A[];
extern s16 D_80072F1C[];
extern s16 D_80072F1E;
extern s32 D_80072F20;
extern s32 D_80072F24;
extern u32 D_80072F2C;
extern s32 D_80072F30;
extern s32 D_80072F3C;
extern u16 D_80072F9A;
// Probably part of the same array / struct
extern u16 D_80072F60[];
extern u16 D_80072F64;
extern u16 D_80072F66;
extern u16 D_80072F68;
extern s16 D_80072F6A[];
extern u16 D_80072F6C;
extern u16 D_80072F6E;
extern u16 D_80072F70;
extern u16 D_80072F7C;
extern u16 D_80072F86;
extern u16 D_80072F88;
extern u16 D_80072F92;
extern unkstruct_80072FA0 D_80072FA0[];
extern u32 D_80073060; // set to 4 to reload stage from disk
extern s32 D_80073080;
extern u16 D_8007308E;
extern u32 D_80073068; // ev0
extern u32 D_8007306C; // ev1
extern u32 D_80073070; // ev2
extern u32 D_80073078; // ev3
extern s16 D_80073092;
extern RoomDimensions g_CurrentRoom;
extern s32 g_CurrentRoomVSize;  // g_CurrentRoom.vSize
extern s32 D_800730AC;          // g_CurrentRoom.unk8
extern s32 g_CurrentRoomLeft;   // g_CurrentRoom.left
extern s32 g_CurrentRoomTop;    // g_CurrentRoom.top
extern s32 g_CurrentRoomRight;  // g_CurrentRoom.right
extern s32 g_CurrentRoomBottom; // g_CurrentRoom.bottom
extern s32 g_CurrentRoomX;      // g_CurrentRoom.x
extern s32 g_CurrentRoomY;      // g_CurrentRoom.y
extern s32 g_CurrentRoomWidth;  // g_CurrentRoom.width
extern s32 g_CurrentRoomHeight; // g_CurrentRoom.height

// Beginning of Player Character offset = 0x800733D8
extern Entity g_EntityArray[TOTAL_ENTITY_COUNT];
// dictionary of direct accesses
// g_EntityArray PLAYER
extern s16 D_800733DA;  // PLAYER.posX.i.hi
extern s16 D_800733DE;  // PLAYER.posY.i.hi
extern s32 D_800733E0;  // PLAYER.accelerationX
extern s32 D_800733E4;  // PLAYER.accelerationY
extern s32 D_800733E8;  // PLAYER.unk10
extern u16 D_800733EC;  // PLAYER.facing
extern u16 D_800733EE;  // PLAYER.palette
extern s8 D_800733F0;   // PLAYER.blendMode
extern u8 D_800733F1;   // PLAYER.unk19
extern s16 D_800733F6;  // PLAYER.unk1E
extern s16 D_800733F8;  // PLAYER.unk20
extern u16 D_800733FA;  // PLAYER.unk22
extern u16 D_800733FC;  // PLAYER.zPriority
extern s16 D_800733FE;  // PLAYER.objectId
extern u16 D_80073404;  // PLAYER.step
extern u16 D_80073406;  // PLAYER.unk2E
extern u16 D_8007340A;  // PLAYER.objectRoomIndex
extern u16 D_8007341C;  // PLAYER.unk44
extern s32* D_80073424; // PLAYER.unk4C
extern s32 D_80073428;  // PLAYER.animationFrameIndex
extern s16 D_8007342A;  // PLAYER.animationFrameDuration
extern s16 D_8007342C;  // PLAYER.animationSet
extern u16 D_8007342E;  // PLAYER.animationFrame
extern u8 D_80073484;   // PLAYER.unkAC
// End of Player Character offset = 0x80073494

// D_80073494 g_EntityArray[1]
// D_80073550 g_EntityArray[2]
// D_8007360C g_EntityArray[3]
// D_800736C8 g_EntityArray[4]
// D_80073784 g_EntityArray[5]
// D_800739B8 g_EntityArray[8]
// D_80073F98 g_EntityArray[16]
// D_800741CC g_EntityArray[19]
// D_80074C08 g_EntityArray[20]

// *** ENTITY DIRECT ACCESS PROPERTIES START ***
extern Entity D_80074C08[];
// *** ENTITY DIRECT ACCESS PROPERTIES END ***

extern Entity D_800762D8[]; // g_EntityArray[64]
extern Unkstruct8 g_CurrentRoomTileLayout;
extern Entity D_8007A958[];
extern Entity D_8007C0D8[];
extern Entity D_8007D858[];
extern Multi g_zEntityCenter;
extern s32 g_entityDestroyed[];
extern Entity D_8007EF1C;
extern unsigned long D_8007EFD8; // ev10 IOE
extern s32 D_8007EFDC;           // ev11 ERROR
extern s32 D_8007EFE0;           // ev12 TIMEOUT
extern s32 D_80084FE4[];
extern s32 D_80086FE4;  // ev13 NEW CARD
extern s32* D_8007EFE4; // 'struct SaveData'?
extern s32 D_80080FE4;  // maybe PixPattern[]?
extern s8 D_80082FE4;
extern POLY_GT4 D_80086FEC[]; // entity polygons
extern s32 playerX;
extern s32 playerY;
extern u32 g_randomNext;
extern s32 D_80096ED8[];
extern u32 D_80097364;
extern s32 D_800973B4;
extern POLY_GT4 D_800973B8[];
extern s32 D_800973EC; // flag to check if the menu is shown
extern s32 D_800973F8;
extern s32 D_800973FC;
extern s32 D_80097400[];
extern s32 D_8009740C[];
extern s32 D_80097410;
extern s32 D_80097414;
extern s32 D_80097418;
extern s32 D_8009741C;
extern s32 D_80097420;
extern s32 D_80097424;
extern s32 D_80097448;
extern s32 D_8009744C;
extern s32 D_80097450;
extern Pad g_pads[];
extern u16 D_80097494; // related to g_menuRelicsCursorIndex
extern u16 D_80097496;
extern u16 D_80097498;
extern u16 D_8009749C[];
extern s32 g_mapProgramId;
extern s32 D_800974A4;
extern DR_ENV D_800974AC;
extern s32 D_800978AC;
extern s32 D_800978B4;
extern s32 D_800978C4;
extern u32 D_800978F8;
extern s32 D_80097904;
extern s32 D_80097908;
extern s32 D_8009790C;
extern s32 D_80097910;
extern s32 D_80097914;
extern s32 D_80097924;
extern s32 D_80097928;
extern GpuUsage g_GpuUsage;
extern s32 D_80097930[]; // confirmed array
extern s32 D_80097934;
extern u32 D_80097944;
extern u8 D_80097964[];
extern u8 D_8009796E;
extern s8 D_8009798A[];
extern u8 D_80097A8D;
extern s32 D_80097BE4[];
extern s32 g_playerLevel;
extern s32 g_playerExp;
extern s32 g_playerGold;
extern s32 g_killCount;
extern u8 g_SaveName[12];
extern PlayerStats D_80097B9C;
extern s32 g_playerHp;       // D_80097B9C.hp
extern s32 g_playerHpMax;    // D_80097B9C.hpMax
extern s32 g_playerHeart;    // D_80097B9C.hearts
extern s32 g_playerHeartMax; // D_80097B9C.heartsMax
extern s32 g_playerMP;       // D_80097B9C.mp
extern s32 g_playerMpMax;    // D_80097B9C.mpMax
extern s32 D_80097C1C[];
extern s32 D_80097C20;
extern s32 D_80097C24;
extern u32 D_80097C40[];
extern GameTimer g_GameTimer;
extern s32 D_80097C98;
extern s8 D_80097D37;
extern u8 D_80097F3C;
extern u8 D_80097F3D;
extern u8 D_80097F3E;
extern s8 D_80097F3F;
extern u8 D_80097F40;
extern u8 D_80097F41;
extern u8 D_80097F42;
extern u8 D_80097F44;
extern u8 D_80097F45;
extern u8 D_80097F46;
extern u8 D_80097F48;
extern u8 D_80097F49;
extern u8 D_80097F4A;
extern s32 D_800987B4;
extern s32 D_800987C8;
extern s32 D_80098850;
extern s32 D_80098894;

void PadInit(s32 arg0);
int VSync(s32);
s32 rcos(s32);
s32 rsin(s32);
s32 SquareRoot0(s32);
long ratan2(long x, long y);
void* DMACallback(int dma, void (*func)());
void func_800192DC(s32 arg0, s32 arg1);
void func_8001C550(s32);
s32 func_8001D290(s32, s32);
s32 func_8001D374(s8, s16, s16);
void func_8001D2E0(s32, s32, s32);
void func_800202E0(s16);
void func_80020F44(s16);
void func_80021174(void);
void func_80021188(void);
s32 func_80021350(const char* str, s32, s32);
s32 func_80021880(s32*, s32, s32);
s32 func_800219E0(s32);
void func_80021F6C(s16, s16);
void func_8002A024(s32, s32);

#endif
