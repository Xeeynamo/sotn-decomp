#ifndef GAME_H
#define GAME_H
#include "common.h"
#include <psxsdk/kernel.h>
#include <psxsdk/libapi.h>
#include <psxsdk/libc.h>
#include <psxsdk/libcd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/libgpu.h>
#include <psxsdk/libgs.h>
#include <psxsdk/libgte.h>
#include <psxsdk/libsnd.h>

typedef long Event;

typedef enum {
    PRIM_NONE,
    PRIM_TILE,
    PRIM_LINE_G2,
    PRIM_G4,
    PRIM_GT4,
    PRIM_GT3,
    PRIM_SPRT,
    PRIM_ENV,
} PrimitiveType;

typedef struct Primitive {
    /* 0x00 */ struct Primitive* next;
    /* 0x04 */ u8 r0;
    /* 0x05 */ u8 g0;
    /* 0x06 */ u8 b0;
    /* 0x07 */ u8 type; // PrimitiveType
    /* 0x08 */ s16 x0;
    /* 0x0A */ s16 y0;
    /* 0x0C */ u8 u0;    // w for PrimitiveType::TILE
    /* 0x0D */ u8 v0;    // h for PrimitiveType::TILE
    /* 0x0E */ u16 clut; // TODO not verified
    /* 0x10 */ u8 r1;
    /* 0x11 */ u8 g1;
    /* 0x12 */ u8 b1;
    /* 0x13 */ u8 p1; // TODO not verified
    /* 0x14 */ s16 x1;
    /* 0x16 */ s16 y1;
    /* 0x18 */ u8 u1;     // TODO not verified
    /* 0x19 */ u8 v1;     // TODO not verified
    /* 0x1A */ u16 tpage; // TODO not verified
    /* 0x1C */ u8 r2;
    /* 0x1D */ u8 g2;
    /* 0x1E */ u8 b2;
    /* 0x1F */ u8 p2; // TODO not verified
    /* 0x20 */ s16 x2;
    /* 0x22 */ s16 y2;
    /* 0x24 */ u8 u2; // TODO not verified
    /* 0x25 */ u8 v2; // TODO not verified
    /* 0x26 */ u16 priority;
    /* 0x28 */ u8 r3;
    /* 0x29 */ u8 g3;
    /* 0x2A */ u8 b3;
    /* 0x2B */ u8 p3; // TODO not verified
    /* 0x2C */ s16 x3;
    /* 0x2E */ s16 y3;
    /* 0x30 */ u8 u3; // TODO not verified
    /* 0x31 */ u8 v3; // TODO not verified
    /* 0x32 */ u16 blendMode;
} Primitive; /* size=0x34 */

#include "entity.h"

#define COLORS_PER_PAL 16
#define OTSIZE 0x200
#define MAXSPRT16 0x280

#define BUTTON_COUNT 8
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

#define MAX_PRIM_COUNT 0x500
#define MAX_PRIM_ALLOC_COUNT 0x400
#define MAX_BG_LAYER_COUNT 16

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
#define STAGE_ENTITY_START 64
#define MaxEntityCount 32
#define EQUIP_TYPE_COUNT 11

#define RIC_PRG_PTR 0x8013C000
#define FAMILIAR_PTR 0x80170000
#define WEAPON0_PTR 0x8017A000
#define WEAPON1_PTR 0x8017D000
#define STAGE_PRG_PTR 0x80180000
#define CASTLE_MAP_PTR 0x801E0000
#define DEMO_KEY_PTR 0x801E8000
#define DEBUG_PTR 0x80280000

#define STAGE_NO0 0x00
#define STAGE_NO1 0x01
#define STAGE_LIB 0x02
#define STAGE_CAT 0x03
#define STAGE_NO2 0x04
#define STAGE_CHI 0x05
#define STAGE_DAI 0x06
#define STAGE_NP3 0x07
#define STAGE_CEN 0x08
#define STAGE_NO4 0x09
#define STAGE_ARE 0x0A
#define STAGE_TOP 0x0B
#define STAGE_NZ0 0x0C
#define STAGE_NZ1 0x0D
#define STAGE_WRP 0x0E
#define STAGE_NO1_ALT 0x0F
#define STAGE_NO0_ALT 0x10
#define STAGE_DRE 0x12
#define STAGE_UNK_13 0x13
#define STAGE_UNK_14 0x14
#define STAGE_UNK_15 0x15
#define STAGE_BO7 0x16
#define STAGE_MAR 0x17
#define STAGE_BO6 0x18
#define STAGE_BO5 0x19
#define STAGE_BO4 0x1A
#define STAGE_BO3 0x1B
#define STAGE_BO2 0x1C
#define STAGE_BO1 0x1D
#define STAGE_BO0 0x1E
#define STAGE_ST0 0x1F
#define STAGE_RCEN (STAGE_CEN | STAGE_INVERTEDCASTLE_FLAG)
#define STAGE_RNZ1 0x35
#define STAGE_RBO8 0x36
#define STAGE_RBO7 0x37
#define STAGE_RBO6 0x38
#define STAGE_RBO5 0x39
#define STAGE_RBO4 0x3A
#define STAGE_RBO3 0x3B
#define STAGE_RBO2 0x3C
#define STAGE_RBO1 0x3D
#define STAGE_RBO0 0x3E
#define STAGE_MAD 0x40
#define STAGE_NO3 0x41
#define STAGE_IWA_LOAD 0x42
#define STAGE_IGA_LOAD 0x43
#define STAGE_HAGI_LOAD 0x44
#define STAGE_SEL 0x45
#define STAGE_TE1 0x46
#define STAGE_TE2 0x47
#define STAGE_TE3 0x48
#define STAGE_TE4 0x49
#define STAGE_TE5 0x4A
#define STAGE_TOP_ALT 0x4B
#define STAGE_INVERTEDCASTLE_MASK 0x1F
#define STAGE_INVERTEDCASTLE_FLAG 0x20
#define STAGE_EU_WARNING 0x70 // EU piracy legal message thing
#define STAGE_ENDING 0xFE
#define STAGE_MEMORYCARD 0xFF

// Flags for entity->flags
#define FLAG_UNK_10000 0x10000
#define FLAG_FREE_POLYGONS 0x00800000
#define FLAG_UNK_04000000 0x04000000
#define FLAG_UNK_08000000 0x08000000
#define FLAG_DESTROY_IF_OUT_OF_CAMERA 0x80000000
#define FLAG_UNK_20000000 0x20000000
#define FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA 0x40000000

typedef enum {
    Game_Init,
    Game_Title,
    Game_Play,
    Game_GameOver,
    Game_NowLoading,
    Game_VideoPlayback,
    Game_Unk6,
    Game_PrologueEnd,
    Game_MainMenu,
    Game_Ending,
    Game_99 = 99,
} GameState;

typedef enum {
    Demo_None,
    Demo_PlaybackInit,
    Demo_Recording,
    Demo_End,
    Demo_Playback,
} DemoMode;

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
    f32 posX;
    f32 posY;
} Camera;

typedef struct {
    unsigned char width;
    unsigned char height;
    unsigned short unk2;
    unsigned char data[0];
} ImgSrc;

typedef struct {
    /* 00 */ u32 gfxOff;
    /* 04 */ u32 ovlOff;
    /* 08 */ u32 ovlLen;
    /* 0C */ u32 vhOff;
    /* 10 */ u32 vhLen;
    /* 14 */ u32 vbLen;
    /* 18 */ u32 unk18;
    /* 1C */ const char* gfxName;
    /* 20 */ const char* ovlName;
    /* 24 */ const char* name;
    /* 28 */ u8 unk28;
    /* 29 */ s8 seqIdx; // index of D_800ACCF8
    /* 2A */ u16 unk2A;
} Lba; /* size=0x2C */

typedef struct {
    /* 0x00 */ s16 cursorX;
    /* 0x02 */ s16 cursorY;
    /* 0x04 */ s16 cursorW;
    /* 0x06 */ s16 cursorH;
    /* 0x08 */ RECT unk1;
    /* 0x10 */ s16 w;
    /* 0x12 */ s16 h;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
} MenuContext; // size = 0x1E
#define SIZEOF_MENUCONTEXT (0x1E)

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
    /* 0x0 */ u16 x;
    /* 0x2 */ u16 y;
    /* 0x4 */ u16 roomId;
    /* 0x6 */ u16 unk6;
    /* 0x8 */ u16 stageId;
} RoomTeleport; // size = 0xA

typedef struct {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 stageId;
    /* 0x0C */ s32 bossId;
    /* 0x10 */ s32 unk10;
} RoomBossTeleport; /* size=0x14 */

typedef struct {
    /* 0x0 */ u16 pressed;
    /* 0x2 */ s16 previous;
    /* 0x4 */ u16 tapped;
    /* 0x6 */ u16 repeat;
} Pad; // size = 0x8

typedef struct {
    u16 duration;
    u16 unk2;
} AnimationFrame;

typedef struct {
    s8 unk0; // Entity::unk10
    s8 unk2; // Entity::unk12
    s8 hitboxWidth;
    s8 hitboxHeight;
} FrameProperty;

typedef struct Entity {
    /* 0x00 */ f32 posX;
    /* 0x04 */ f32 posY;
    /* 0x08 */ s32 accelerationX;
    /* 0x0C */ s32 accelerationY;
    /* 0x10 */ u16 unk10; // Hitbox X Offset
    /* 0x12 */ s16 unk12; // Hitbox Y Offset
    /* 0x14 */ u16 facing;
    /* 0x16 */ u16 palette;
    /* 0x18 */ s8 blendMode;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E; // poly rotation angle
    /* 0x20 */ s16 unk20; // poly / rotation origin x
    /* 0x22 */ s16 unk22; // poly / rotation origin y
    /* 0x24 */ u16 zPriority;
    /* 0x26 */ u16 objectId;
    /* 0x28 */ PfnEntityUpdate pfnUpdate;
    /* 0x2C */ u16 step;
    /* 0x2E */ u16 step_s;
    /* 0x30 */ u16 subId;
    /* 0x32 */ u16 objectRoomIndex;
    /* 0x34 */ s32 flags;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ u16 enemyId;
    /* 0x3C */ u16 unk3C; // hitbox state
    /* 0x3E */ s16 hitPoints;
    /* 0x40 */ s16 attack;
    /* 0x42 */ s16 attackElement;
    /* 0x44 */ u16 unk44;
    /* 0x46 */ u8 hitboxWidth;
    /* 0x47 */ u8 hitboxHeight;
    /* 0x48 */ u8 unk48; // 1 = took hit
    /* 0x49 */ u8 unk49; // invincibility frames
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ AnimationFrame* unk4C;
    /* 0x50 */ u16 animFrameIdx;
    /* 0x52 */ s16 animFrameDuration;
    /* 0x54 */ s16 animSet;
    /* 0x56 */ s16 animCurFrame;
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
    /* 0x7C */ Ext ext;
} Entity; // size = 0xBC

typedef struct {
    /* 0x00 */ u16 animSet;
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

#define GPU_MAX_TILE_COUNT 0x100

typedef struct GpuBuffer { // also called 'DB' in the PSY-Q samples
    /* 0x00000 */ struct GpuBuffer* next;         // next chained buffer
    /* 0x00004 */ DRAWENV draw;                   // drawing environment
    /* 0x0005C */ DISPENV disp;                   // display environment
    /* 0x00074 */ DR_ENV env[0x10];               // packed drawing environment
    /* 0x00474 */ u_long ot[OTSIZE];              // ordering table
    /* 0x00474 */ DR_MODE drawModes[0x400];       // draw modes
    /* 0x03C74 */ POLY_GT4 polyGT4[0x300];        // textured quads
    /* 0x0D874 */ POLY_G4 polyG4[0x100];          // untextured quads
    /* 0x0FC74 */ POLY_GT3 polyGT3[0x30];         // textured triangles
    /* 0x103F4 */ LINE_G2 lineG2[0x100];          // lines
    /* 0x117F4 */ SPRT_16 sprite16[MAXSPRT16];    // 16x16 fixed-size sprites
    /* 0x13FF4 */ TILE tiles[GPU_MAX_TILE_COUNT]; // squared sprites
    /* 0x14FF4 */ SPRT sprite[0x200];             // dynamic-size sprites
} GpuBuffer;                                      /* size = 0x177F4 */

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
    s32 statStr;
    s32 statCon;
    s32 statInt;
    s32 statLck;
} Stats;

typedef struct {
    /* 80097964 */ u8 relics[30];
    /* 80097982 */ u8 spells[8];
    /* 8009798A */ u8 equipHandCount[169];
    /* 80097A33 */ u8 equipBodyCount[26];
    /* 80097A4D */ u8 equipHeadCount[22];
    /* 80097A63 */ u8 equipCloakCount[9];
    /* 80097A6C */ u8 equipOtherCount[33];
    /* 80097A8D */ u8 equipHandOrder[169];
    /* 80097B36 */ u8 equipBodyOrder[26];
    /* 80097B50 */ u8 equipHeadOrder[22];
    /* 80097B66 */ u8 equipCloakOrder[9];
    /* 80097B6F */ u8 equipOtherOrder[33];
    /* 80097B90 */ u8 saveName[12];
    /* 80097B90 */ u32 D_80097B9C;
    /* 80097BA0 */ s32 hp;
    /* 80097BA4 */ s32 hpMax;
    /* 80097BA8 */ s32 hearts;
    /* 80097BAC */ s32 heartsMax;
    /* 80097BB0 */ s32 mp;
    /* 80097BB4 */ s32 mpMax;
    /* 80097BB8 */ s32 statsBase[4];
    /* 80097BC8 */ s32 statsEquip[4];
    /* 80097BD8 */ s32 statsTotal[4];
    /* 80097BE8 */ u32 level;
    /* 80097BEC */ u32 exp;
    /* 80097BF0 */ u32 gold;
    /* 80097BF4 */ u32 killCount;
    /* 80097BF8 */ u32 D_80097BF8;
    /* 80097BFC */ u32 subWeapon;
    /* 80097C00 */ u32 equipment[7];
    /* 80097C1C */ u32 attackHands[2]; // right hand, left hand
    /* 80097C24 */ u32 defenseEquip;
    /* 80097C28 */ u16 defenseElement;
    /* 80097C2A */ u16 D_80097C2A;
    /* 80097C2C */ u16 D_80097C2C;
    /* 80097C2E */ u16 D_80097C2E;
    /* 80097C30 */ s32 timerHours;
    /* 80097C34 */ s32 timerMinutes;
    /* 80097C38 */ s32 timerSeconds;
    /* 80097C3C */ s32 timerFrames;
    /* 80097C40 */ u32 D_80097C40;
    /* 80097C44 */ u32 D_80097C44;
    /* 80097C48 */ u32 D_80097C48;
    /* 80097C4C */ u32 D_80097C4C;
    /* 80097C50 */ u32 D_80097C50;
    /* 80097C54 */ u32 D_80097C54;
    /* 80097C58 */ u32 D_80097C58;
    /* 80097C5C */ u32 D_80097C5C;
    /* 80097C60 */ u32 D_80097C60;
    /* 80097C64 */ u32 D_80097C64;
    /* 80097C68 */ u32 D_80097C68;
    /* 80097C6C */ u32 D_80097C6C;
    /* 80097C70 */ u32 D_80097C70;
    /* 80097C74 */ u32 D_80097C74;
    /* 80097C78 */ u32 D_80097C78;
    /* 80097C7C */ u32 D_80097C7C;
    /* 80097C80 */ u32 D_80097C80;
    /* 80097C84 */ u32 D_80097C84;
    /* 80097C88 */ u32 D_80097C88;
    /* 80097C8C */ u32 D_80097C8C;
    /* 80097C90 */ u32 D_80097C90;
    /* 80097C94 */ u32 D_80097C94;
} PlayerStatus; /* size=0x334 */

typedef struct {
    /* 0x00, 8003C9A8 */ s32 cursorMain;
    /* 0x04, 8003C9AC */ s32 cursorRelic;
    /* 0x08, 8003C9B0 */ s32 cursorEquip;
    /* 0x0C, 8003C9B4 */ s32 cursorEquipHand;
    /* 0x10, 8003C9B8 */ s32 cursorEquipHead;
    /* 0x14, 8003C9BC */ s32 cursorEquipBody;
    /* 0x18, 8003C9C0 */ s32 cursorEquipCloak;
    /* 0x1C, 8003C9C4 */ s32 cursorEquipOther;
    /* 0x20, 8003C9C8 */ s32 scrollEquipHand;
    /* 0x24, 8003C9D0 */ s32 scrollEquipAccessories[4];
    /* 0x34, 8003C9DC */ s32 cursorSpells;
    /* 0x38, 8003C9E0 */ s32 cursorSettings;
    /* 0x3C, 8003C9E4 */ s32 cursorCloak;
    /* 0x40, 8003C9E8 */ s32 cursorButtons;
    /* 0x44, 8003C9EC */ s32 cursorWindowColors;
    /* 0x48, 8003C9F0 */ s32 cursorTimeAttack;
} MenuNavigation; /* size=0x4C */

typedef struct {
    /* 0x000, 0x8003C9F8 */ u32 buttonConfig[BUTTON_COUNT];
    /* 0x020, 0x8003CA18 */ u16 buttonMask[BUTTON_COUNT];
    /* 0x030, 0x8003CA28 */ s32 timeAttackRecords[32];
    /* 0x0B0, 0x8003CAA8 */ s32 cloakExteriorColors[3];
    /* 0x0BC, 0x8003CAB4 */ s32 cloakLiningColors[3];
    /* 0x0C8, 0x8003CAC0 */ s32 windowColors[3];
    /* 0x0D4, 0x8003CACC */ s32 equipOrderTypes[EQUIP_TYPE_COUNT];
    /* 0x100, 0x8003CAF8 */ s32 isCloakLingingReversed;
    /* 0x104, 0x8003CAFC */ s32 isSoundMono;
    /* 0x108, 0x8003CB00 */ s32 D_8003CB00;
    /* 0x10C, 0x8003CB04 */ s32 D_8003CB04;
} GameSettings; /* size=0x110 */

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
    /* 0x000 */ MemcardHeader header;
    /* 0x200 */ u8 saveName[12];
    /* 0x20C */ u32 level;
    /* 0x210 */ u32 goldAmount;
    /* 0x214 */ u32 playTimeHours;
    /* 0x218 */ u32 playTimeMinutes;
    /* 0x21C */ u32 playTimeSeconds;
    /* 0x220 */ u32 memcardIcon;
    /* 0x224 */ u32 isTimeAttackUnlocked;
    /* 0x228 */ s16 stageID;
    /* 0x22A */ u16 exploredRoomCount;
    /* 0x22C */ u16 roomX;
    /* 0x22E */ u16 roomY;
    /* 0x230 */ u32 playableCharacter;
    /* 0x234 */ u32 saveSize;
    /* 0x238 */ PlayerStatus status;
    /* 0x56C */ MenuNavigation menuNavigation;
    /* 0x5B8 */ GameSettings settings;
    /* 0x6C8 */ u8 castleFlags[0x300];
    /* 0x6C8 */ u8 castleMap[0x800];
    /* 0x11C8 */ s32 rng;
} SaveData; /* size = 0x11CC */

typedef struct {
    /* 0x00 */ const u8* gfxPage;
    /* 0x04 */ const u8* gfxIndex;
    /* 0x08 */ const u8* clut;
    /* 0x0C */ const u8* collision;
} TileDefinition; // size = 0x10

typedef struct {
    /* 0x00 */ u32 left : 6;
    /* 0x04 */ u32 top : 6;
    /* 0x08 */ u32 right : 6;
    /* 0x0C */ u32 bottom : 6;
    /* 0x10 */ u8 flags : 8;
} LayoutRect; // size = 0x14

typedef struct {
    /* 0x00 */ const u16* layout;
    /* 0x04 */ const TileDefinition* tileDef;
    /* 0x08 */ const LayoutRect rect;
    /* 0x0C */ const u16 zPriority;
    /* 0x0E */ const u16 unkE;
} LayerDef2; // size = 0x10

typedef struct {
    /* 0x00 */ const u16* layout;
    /* 0x04 */ const TileDefinition* tileDef;
    /* 0x08 */ const u32 rect;
    /* 0x0C */ const u16 zPriority;
    /* 0x0E */ const u8 unkE;
    /* 0x0F */ const u8 unkF;
} LayerDef; // size = 0x10

typedef struct {
    LayerDef* fg;
    LayerDef* bg;
} RoomDef;

typedef struct {
    /* 8003C774 */ void (*Update)(void);
    /* 8003C778 */ void (*TestCollisions)(void);
    /* 8003C77C */ void (*unk08)(void);
    /* 8003C780 */ void (*InitRoomEntities)(s32 layoutId);
    /* 8003C784 */ RoomHeader* rooms;
    /* 8003C788 */ s16** spriteBanks;
    /* 8003C78C */ s32** cluts;
    /* 8003C790 */ void* unk1C; // related to object layout
    /* 8003C794 */ RoomDef* tileLayers;
    /* 8003C798 */ void** entityGfxs;
    /* 8003C79C */ void (*unk28)(void);
    /* 8003C7A0 */ void (*unk2c)(void); // similar to Update
    /* 8003C7A4 */ void* unk30;
    /* 8003C7A8 */ s32* unk34;
    /* 8003C7AC */ s32* unk38;
    /* 8003C7B0 */ void (*unk3C)(void);
} Overlay;

typedef struct Collider {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
} Collider; /* size=0x24 */

typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ s16 hitPoints;
    /* 0x06 */ u16 attack;
    /* 0x08 */ u16 attackElement;
    /* 0x0A */ s16 defense;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 weaknesses;
    /* 0x10 */ u16 strengths;
    /* 0x12 */ u16 immunes;
    /* 0x14 */ u16 absorbs;
    /* 0x16 */ s16 level;
    /* 0x18 */ s16 exp;
    /* 0x1A */ s16 rareItemId;
    /* 0x1C */ s16 uncommonItemId;
    /* 0x1E */ u16 rareItemDropRate;
    /* 0x20 */ u16 uncommonItemDropRate;
    /* 0x22 */ u8 hitboxWidth;
    /* 0x23 */ u8 hitboxHeight;
    /* 0x24 */ s32 unk24;
} EnemyDef; /* size=0x28 */

typedef struct {
    /* 0x00 */ s16 attack;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u16 attackElement;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 sp17;
    /* 0x08 */ u16 sp18;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u16 sp1C;
    /* 0x0E */ u16 sp1E;
    /* 0x10 */ u8 sp20;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u16 sp22; // entity->objectRoomIndex
} SubweaponDef;          /* size=0x14 */

// Defines the equipment that can be set on left and right hand
// This includes weapons, throw weapons, consumable and restoration items.
// D_800A4B04 it is assumed the equip data starts from here
// https://github.com/3snowp7im/SotN-Randomizer/blob/master/src/stats.js
typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ const char* description;
    /* 0x08 */ s16 attack;
    /* 0x0A */ s16 defense;
    /* 0x0C */ u16 element;
    /* 0x0E */ u8 damageScale;
    /* 0x0F */ u8 weaponId;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u8 playerAnim;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 lockDuration;
    /* 0x16 */ u16 chainable;
    /* 0x18 */ u8 specialMove;
    /* 0x19 */ u8 isConsumable;
    /* 0x1A */ u8 enemyInvincibilityFrames;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ u16 unk20;
    /* 0x22 */ u16 unk22;
    /* 0x24 */ u16 mpUsage;
    /* 0x26 */ u16 stunFrames;
    /* 0x28 */ u16 hitType;
    /* 0x2A */ u16 hitEffect;
    /* 0x2C */ u16 icon;
    /* 0x2E */ u16 palette;
    /* 0x30 */ u16 criticalRate;
    /* 0x32 */ u16 unk32;
} Equipment; /* size=0x34 */

// Defines armor, cloak and rings
typedef struct {
    /* 00 */ const char* name;
    /* 04 */ const char* description;
    /* 08 */ u32 unk08;
    /* 0C */ u32 unk0C;
    /* 10 */ u32 unk10;
    /* 14 */ u32 unk14;
    /* 18 */ u16 icon;
    /* 1A */ u16 palette;
    /* 1C */ u32 unk1C;
} Accessory; /* size=0x20 */

typedef struct {
    /* 8003C774 */ Overlay o;
    /* 8003C7B4 */ void (*FreePrimitives)(s32);
    /* 8003C7B8 */ s16 (*AllocPrimitives)(PrimitiveType type, s32 count);
    /* 8003C7BC */ void (*CheckCollision)(s32 x, s32 y, Collider* res, s32 unk);
    /* 8003C7C0 */ void (*func_80102CD8)(s32 arg0);
    /* 8003C7C4 */ void (*UpdateAnim)(FrameProperty* frameProps, s32* arg1);
    /* 8003C7C8 */ void (*AccelerateX)(s32 value);
    /* 8003C7CC */ Entity* (*GetFreeDraEntity)(s16 start, s16 end);
    /* 8003C7D0 */ void (*GetEquipProperties)(s32 handId, Equipment* res,
                                              s32 equipId);
    /* 8003C7D4 */ void (*func_800EA5E4)(s32);
    /* 8003C7D8 */ void (*func_800EAF28)(s32);
    /* 8003C7DC */ void (*PlaySfx)(s32 sfxId);
    /* 8003C7E0 */ s16 (*func_800EDB58)(s32, s32);
    /* 8003C7E4 */ void (*func_800EA538)(s32 arg0);
    /* 8003C7E8 */ void (*g_pfn_800EA5AC)(u16 arg0, u8 arg1, u8 arg2, u8 arg3);
    /* 8003C7EC */ void* func_801027C4;
    /* 8003C7F0 */ void* func_800EB758;
    /* 8003C7F4 */ Entity* (*func_8011AAFC)(Entity* self, u32 flags, s32 arg2);
    /* 8003C7F8 */ bool (*func_80131F68)(void);
    /* 8003C7FC */ DR_ENV* (*func_800EDB08)(POLY_GT4* poly);
    /* 8003C800 */ void* func_80106A28;
    /* 8003C804 */ void (*func_80118894)(Entity*);
    /* 8003C808 */ EnemyDef* enemyDefs;
    /* 8003C80C */ void* func_80118970;
    /* 8003C810 */ void* func_80118B18;
    /* 8003C814 */ void* func_8010DB38;
    /* 8003C818 */ void (*func_8010DBFC)(s32*, s32*);
    /* 8003C81C */ void* func_80118C28;
    /* 8003C820 */ void (*func_8010E168)(s32 arg0, s16 arg1);
    /* 8003C824 */ void (*func_8010DFF0)(s32 arg0, s32 arg1);
    /* 8003C828 */ u16 (*func_800FF128)(Entity* enemyEntity,
                                        Entity* weaponEntity);
    /* 8003C82C */ void (*func_800EB534)(s32 equipIcon, s32 palette, s32 index);
    /* 8003C830 */ Equipment* D_800A4B04;
    /* 8003C834 */ Accessory* D_800A7718;
    /* 8003C838 */ void (*AddHearts)(s32 value);
    /* 8003C83C */ void* func_8010715C;
    /* 8003C840 */ s32 (*func_800FD4C0)(s32 bossId, s32 action);
    /* 8003C844 */ void* (*func_8010E0A8)(void);
    /* 8003C848 */ void (*func_800FE044)(s32, s32);
    /* 8003C84C */ void (*AddToInventory)(u16 itemId, s32 itemCategory);
    /* 8003C850 */ void* D_800A8720;
    /* 8003C854 */ void* func_800FF7B8;
    /* 8003C858 */ s32 (*func_80134714)(s32 arg0, s32 arg1, s32 arg2);
    /* 8003C85C */ s32 (*func_80134678)(s16 arg0, u16 arg1);
    /* 8003C860 */ void (*func_800F53A4)(void);
    /* 8003C864 */ u32 (*CheckEquipmentItemCount)(u32 itemId, u32 equipType);
    /* 8003C868 */ void (*func_8010BF64)(Unkstruct_8010BF64* arg0);
    /* 8003C86C */ void (*func_800F1FC4)(s32 arg0);
    /* 8003C870 */ void* func_800F2288;
    /* 8003C874 */ void (*func_8011A3AC)(Entity* entity, s32 arg1, s32 arg2,
                                         Unkstruct_8011A3AC* arg3);
    /* 8003C878 */ s32 (*func_800FF460)(s32 arg0);
    /* 8003C87C */ s32 (*func_800FF494)(EnemyDef* arg0);
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

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 width;
    /* 0x06 */ s16 height;
    /* 0x08 */ s16 clut;
    /* 0x0A */ s16 tpage;
    /* 0x0C */ u8 texLeft, dummyLeft;
    /* 0x0E */ u8 texTop, dummyTop;
    /* 0x10 */ u8 texRight, dummyRight;
    /* 0x12 */ u8 texBottom, dummyBottom;
} Sprite; /* size=0x14 */

typedef struct {
    /* 00 */ s16 flags;
    /* 02 */ s16 offsetx;
    /* 04 */ s16 offsety;
    /* 06 */ s16 width;
    /* 08 */ s16 height;
    /* 0A */ s16 clut;
    /* 0C */ s16 tileset;
    /* 0E */ s16 left;
    /* 10 */ s16 top;
    /* 12 */ s16 right;
    /* 14 */ s16 bottom;
} SpritePart; /* size=0x16 */

typedef struct {
    /* 00 */ u16 count;
    /* 02 */ SpritePart parts[0];
} SpriteParts; // size = 4 + count*sizeof(SpritePart)

typedef struct {
    /* 800730D8 0x00 */ u16* layout;
    /* 800730DC 0x04 */ u32 tileDef;
    /* 800730E0 0x08 */ f32 scrollX;
    /* 800730E4 0x0C */ f32 scrollY;
    /* 800730E8 0x10 */ u32 D_800730E8;
    /* 800730EC 0x14 */ u32 D_800730EC;
    /* 800730F0 0x18 */ u32 zPriority;
    /* 800730F4 0x1C */ u32 D_800730F4;
    /* 800730F8 0x20 */ u32 w;
    /* 800730FC 0x24 */ u32 h;
    /* 80073100 0x28 */ u32 D_80073100;
    /* 80073104 0x2C */ u32 flags;
} BgLayer; /* size=0x30 */

typedef struct {
    /* 800730A0 0x00 */ s32 unk00;
    /* 800730A4 0x04 */ s32 hSize;
    /* 800730A8 0x08 */ u16 vSize;
    /* 800730AA 0x0A */ u16 _padding06;
    /* 800730AC 0x0C */ s32 unk8;
    /* 800730B0 0x10 */ s32 left;
    /* 800730B4 0x14 */ s32 top;
    /* 800730B8 0x18 */ s32 right;
    /* 800730BC 0x1C */ s32 bottom;
    /* 800730C0 0x20 */ s32 x;
    /* 800730C4 0x24 */ s32 y;
    /* 800730C8 0x28 */ s32 width;
    /* 800730CC 0x2C */ s32 height;
    /* 800730D0 0x30 */ s32 _padding30;
    /* 800730D4 0x34 */ s32 D_800730D4;
    /* 800730D8 0x38 */ BgLayer bg[MAX_BG_LAYER_COUNT];
} RoomDimensions;

typedef struct {
    /* D_8003C708 */ u16 flags;
    /* D_8003C70A */ u16 unk2;
    /* D_8003C70C */ u16 unk4;
    /* D_8003C70E */ s16 zPriority;
} FgLayer; /* size=0x8 */

typedef struct {
    /* 80072BD0 */ s32 D_80072BD0[8][9];
    /* 80072CF0 */ s32 D_80072CF0[14][9];
    /* 80072EE8 */ s32 padPressed;
    /* 80072EEC */ s32 padTapped;
    /* 80072EF0 */ s32 padHeld;
    /* 80072EF4 */ s32 D_80072EF4;
    /* 80072EF8 */ s32 D_80072EF8;
    /* 80072EFC */ s32 D_80072EFC; // stun timer
    /* 80072F00 */ s16 D_80072F00; // poison timer
    /* 80072F02 */ s16 D_80072F02; // curse timer
    /* 80072F04 */ s16 D_80072F04; // visual effect timer stoned/hit
    /* 80072F06 */ s16 D_80072F06;
    /* 80072F08 */ s16 D_80072F08;
    /* 80072F0A */ s16 D_80072F0A;
    /* 80072F0C */ s16 D_80072F0C;
    /* 80072F0E */ s16 D_80072F0E;
    /* 80072F10 */ s16 D_80072F10;
    /* 80072F12 */ s16 D_80072F12;
    /* 80072F14 */ s16 D_80072F14;
    /* 80072F16 */ s16 D_80072F16;
    /* 80072F18 */ s16 D_80072F18;
    /* 80072F1A */ s16 D_80072F1A; // invincibility timer
    /* 80072F1C */ s16 D_80072F1C; // invincibility timer from consumables
    /* 80072F1E */ s16 D_80072F1E;
    /* 80072F20 */ s32 pl_vram_flag;
    /* 80072F24 */ s32 unk04;
    /* 80072F28 */ s32 unk08;
    /* 80072F2C */ u32 unk0C;
    /* 80072F30 */ s32 unk10;
    /* 80072F34 */ s32 unk14;
    /* 80072F38 */ s32 unk18;
    /* 80072F3C */ s32 unk1C;
    /* 80072F40 */ s32 unk20[8];
    /* 80072F60 */ u16 unk40;
    /* 80072F62 */ u16 pl_high_jump_timer;
    /* 80072F64 */ u16 unk44;
    /* 80072F66 */ u16 unk46;
    /* 80072F68 */ u16 unk48;
    /* 80072F6A */ s16 unk4A;
    /* 80072F6C */ u16 unk4C;
    /* 80072F6E */ u16 unk4E;
    /* 80072F70 */ u16 unk50;
    /* 80072F72 */ u16 unk52;
    /* 80072F74 */ u16 unk54;
    /* 80072F76 */ u16 unk56;
    /* 80072F78 */ u16 unk58;
    /* 80072F7A */ u16 unk5A;
    /* 80072F7C */ u16 unk5C;
    /* 80072F7E */ u16 unk5E;
    /* 80072F80 */ u16 unk60;
    /* 80072F82 */ u16 unk62;
    /* 80072F84 */ u16 unk64;
    /* 80072F86 */ u16 unk66;
    /* 80072F88 */ u16 unk68;
    /* 80072F8A */ u16 unk6A;
    /* 80072F8C */ u16 unk6C;
    /* 80072F8E */ u16 unk6E;
    /* 80072F90 */ u16 unk70;
    /* 80072F92 */ u16 unk72;
    /* 80072F94 */ u32 unk74;
    /* 80072F98 */ u16 unk78;
    /* 80072F9A */ u16 unk7A;
    /* 80072F9C */ u16 unk7C;
    /* 80072F9E */ u16 unk7E;
} PlayerState;

extern const s16 g_AtanTable[0x400];

extern s32 D_8003925C;
extern s32 g_IsTimeAttackUnlocked;

// Holds flags that checks if certain switches are enabled to allow to have
// shortcuts around the castle. One typical example is the wood column that
// prevents the player to enter in the warp room. When D_8003BDEC[0x32] the
// column will disappear.
extern u8 D_8003BDEC[];
extern u8 D_8003BE23;
extern u8 D_8003BEEC[];
extern u8 D_8003BF9C[];
extern s32 D_8003C0EC[4];
extern s32 D_8003C0F8;
extern s32 D_8003C100;
extern u16 D_8003C104[];
extern u16 D_8003C3C2[]; // confirmed array
extern s32 D_8003C704;
extern FgLayer D_8003C708;
extern s16 D_8003C710;
extern s16 D_8003C712;
extern s32 D_8003C728;
extern s32 D_8003C730;
extern GameState g_GameState;
extern s32 D_8003C73C;
extern u32 D_8003C744;
extern s32 g_roomCount;
extern Unsktruct_800EAF28** D_8003C798;
extern GameApi g_api;
extern s32 D_8003C8B8;
extern u32 D_8003C8C4;
extern Unkstruct_8003C908 D_8003C908;
extern s32 D_8003C90C[2];
extern u32 g_blinkTimer;
/* 0x8003C99C */ extern s32 D_8003C99C;
/* 0x8003C9A0 */ extern s32 g_CurrentPlayableCharacter;
/* 0x8003C9A4 */ extern s32 D_8003C9A4; // when player change stages?
/* 0x8003C9A8 */ extern MenuNavigation g_MenuNavigation;
/* 0x8003C9F8 */ extern GameSettings g_Settings;
extern GpuBuffer g_GpuBuffers[2];
extern s16 g_GpuBuffers_1_buf_draw_clip_y; // member of D_800542FC, TODO
                                           // overlap, hard to remove

extern const char g_MemcardSavePath[];
extern const char aBaslus00067dra[19];
extern const char g_strMemcardRootPath[];
extern s32 g_LoadFile;
extern s32 D_8006BB00;
extern u8 D_8006BB74[0x800];
extern s32 D_8006C374;
extern s32 D_8006C378;
extern GpuBuffer* g_CurrentBuffer; // g_CurrentBuffer;
extern s32 D_8006C384;
extern s32 D_8006C388;
extern s32 D_8006C38C;
extern s32 D_8006C390;
extern s32 D_8006C384;
extern s32 D_8006C388;
extern s32 D_8006C38C;
extern s32 D_8006C390;
extern u32 g_CdStep; // CdStep
extern s32 D_8006C3AC;
extern s32 g_backbufferX;
extern s32 g_backbufferY;
extern s32 g_IsUsingCd;
extern Entity* g_CurrentEntity;
extern Unkstruct_8006C3CC D_8006C3C4[32];
extern s32 D_8006CBC4;
extern u16 g_Clut[];
extern u32 D_8006EBCC;
extern u16 D_8006EBE0;
extern u16 D_8006F3CC[];
extern u16 D_8006F42C[];
extern s16 D_800705CC[];
extern u32 D_80070BCC;
extern Unkstruct4 D_80072B34;

extern PlayerState g_Player;
extern u16 g_Player_D_80072EF6; // TODO merge with g_Player
extern u32 g_Player_unk0C;      // TODO merge with g_Player

extern unkstruct_80072FA0 D_80072FA0[];
extern u32 g_GameStep; // set to 4 to reload stage from disk
extern s32 D_80073064;
extern Event g_EvSwCardEnd;
extern Event g_EvSwCardErr;
extern Event g_EvSwCardTmo;
extern Event g_EvSwCardNew;
extern s32 D_80073080;
extern TileDefinition* D_80073088;
extern Camera g_Camera;
extern RoomDimensions g_CurrentRoom;
extern s32 g_CurrentRoom_vSize; // g_CurrentRoom.vSize

// Beginning of Player Character offset = 0x800733D8
extern Entity g_Entities[TOTAL_ENTITY_COUNT];

// D_800736C8 g_Entities[4]
// D_80073784 g_Entities[5]
// D_800739B8 g_Entities[8]
// D_80073F98 g_Entities[16]
// D_800741CC g_Entities[19]
// D_80074C08 g_Entities[20]

// *** ENTITY DIRECT ACCESS PROPERTIES START ***
extern Entity D_80074C08[];
// *** ENTITY DIRECT ACCESS PROPERTIES END ***

extern Unkstruct8 g_CurrentRoomTileLayout;
extern Entity D_8007A958[]; // &g_Entities[0xA0]
extern Entity D_8007C0D8[];
extern Entity D_8007D858[];
extern Entity D_8007DE38[];
extern Multi g_zEntityCenter;
extern s32 g_entityDestroyed[];
extern Entity D_8007EF1C;
extern Event g_EvHwCardEnd;
extern Event g_EvHwCardErr;
extern Event g_EvHwCardTmo;
extern s32 D_80084FE4[];
extern Event g_EvHwCardNew;
extern PixPattern D_8007EFE4;
extern s32 D_80080FE4; // maybe PixPattern[]?
extern s8 D_80082FE4;
extern u16 D_8008701E[];
extern Primitive g_PrimBuf[MAX_PRIM_COUNT]; // entity polygons
extern s32 playerX;
extern s32 playerY;
extern u32 g_randomNext;
extern s32 D_80096ED8[];
extern u32 D_80097364;
extern s32 D_800973B4;
extern POLY_GT4 D_800973B8[];
extern s8 D_80097B98;
extern s8 D_80097B99;
extern s32 D_800973EC; // flag to check if the menu is shown
extern s32 D_800973F8;
extern s32 D_800973FC;
extern s32 D_80097400[];
extern s32 D_8009740C[];
extern s32 D_80097410;
extern s32 D_80097414;
extern s32 D_80097418;
extern s32 D_8009741C;
extern s32 D_80097420[];
extern s32 D_80097424;
extern s32 D_80097448; // underwater physics
extern s32 D_8009744C;
extern s32 D_80097450;
extern u16 D_8009748A[];
extern Pad g_pads[];
extern u32 g_StageId;
extern s32 D_800974A4; // map open
extern DR_ENV D_800974AC;
extern s32 g_UseDisk;
extern s32 D_800978B4;
extern s32 D_800978C4;
extern u32 D_800978F8;
extern s32 D_80097904;
extern s32 D_80097908;
extern s32 D_8009790C;
extern s32 D_80097910;
extern DemoMode g_DemoMode;
extern s32 g_mapTilesetId; // 0x80097918
extern s32 D_80097924;
extern s32 D_80097928;
extern GpuUsage g_GpuUsage;
extern PlayerStatus g_Status;
extern u8 D_80097B9C[];
extern s32 subWeapon; // g_SubweaponId
extern u8 g_SaveName[12] ALIGNED4;
extern Unkstruct_8011A3AC D_80097C38[];
extern u32 D_80097C40[];
extern s32 D_80097C98;
extern Unkstruct_800ECBF8_1 D_80097D1C[0x10];
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
s32 SquareRoot12(s32, s32);
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
s16 func_80021350(const char* str, s32, s32);
s32 func_80021880(s32*, s32, s32);
s16 func_800219E0(s32);
void func_80021F6C(s16, s16);
void func_8002A024(s32, s32);

#endif