#ifndef GAME_H
#define GAME_H
#include "common.h"
#include "log.h"
#include <psxsdk/kernel.h>

// lseek etc. conflicts
#ifndef VERSION_PC
#include <psxsdk/libapi.h>
#include <psxsdk/libc.h>
#endif

#include <psxsdk/libcd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/libgpu.h>
#include <psxsdk/libgs.h>
#include <psxsdk/libgte.h>
#include <psxsdk/libspu.h>
#include <psxsdk/libsnd.h>
#include <psxsdk/romio.h>

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
    PRIM_TILE_ALT = PRIM_TILE | 0x10,
    PRIM_G4_ALT = PRIM_G4 | 0x10
} PrimitiveType;

typedef struct Vertex {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 p;
    /* 0x4 */ s16 x;
    /* 0x6 */ s16 y;
    /* 0x8 */ u8 u;
    /* 0x9 */ u8 v;
    /* 0xA */ u16 param;
} Vertex; // size = 0xC

typedef struct {
    /* 0x00 */ SVECTOR* v0;
    /* 0x04 */ SVECTOR* v1;
    /* 0x08 */ SVECTOR* v2;
    /* 0x0C */ SVECTOR* v3;
} SVEC4; // size = 0x10

// This structure is identical to Vertex but it is used for a FAKE! match.
// The fields are shifted compared to Vertex but they are not supposed to.
typedef struct {
    s16 x;
    s16 y;
    u8 u;
    u8 v;
    u16 param;
    u8 r;
    u8 g;
    u8 b;
    u8 p;
} VertexFake; // size = 0xC

typedef struct Prim {
    struct Prim* next;
    struct Vertex v[4];
} Prim;

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

#define BLEND_VISIBLE 8 // if unset, the primitive will not be rendered

#include "entity.h"

#define COLORS_PER_PAL (16)
#define COLOR_BPP (16)
#define COLOR_LEN ((COLOR_BPP) / 8)
#define PALETTE_LEN ((COLORS_PER_PAL) * ((COLOR_BPP) / 8))
#define OTSIZE 0x200
#define MAXSPRT16 0x280
#define MAX_DRAW_MODES 0x400

// Width in pixel of how wide is the horizontal camera during normal game play
#define STAGE_WIDTH 256

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

#define WEAPON_0_START 0xE0
#define WEAPON_0_END (WEAPON_1_START - 1)
#define WEAPON_1_START 0xF0

#define RIC_PRG_PTR 0x8013C000
#define FAMILIAR_PTR 0x80170000
#define WEAPON0_PTR 0x8017A000
#define WEAPON1_PTR 0x8017D000
#define STAGE_PRG_PTR 0x80180000
#define CASTLE_MAP_PTR 0x801E0000
#ifndef DEMO_KEY_PTR
#define DEMO_KEY_PTR 0x801E8000
#endif
#define SIM_CHR0 0x80280000
#define SIM_CHR1 0x80284000
#define SIM_PTR 0x80280000

// Flags for entity->drawFlags
#define FLAG_DRAW_ROTX 0x01
#define FLAG_DRAW_ROTY 0x02
#define FLAG_DRAW_ROTZ 0x04
#define FLAG_DRAW_UNK8 0x08
#define FLAG_DRAW_UNK10 0x10
#define FLAG_DRAW_UNK20 0x20
#define FLAG_DRAW_UNK80 0x80

// Flags for entity->flags
#define FLAG_UNK_2000 0x2000
#define FLAG_UNK_10000 0x10000
#define FLAG_UNK_20000 0x20000 // func_8011A9D8 will destroy if not set
#define FLAG_UNK_40000 0x40000
#define FLAG_UNK_80000 0x80000
#define FLAG_UNK_100000 0x100000
#define FLAG_UNK_00200000 0x00200000

// When an entity used AllocPrimitives and their primIndex set.
// At their destruction they need to free the prims with FreePrimitives.
#define FLAG_HAS_PRIMS 0x00800000

#define FLAG_UNK_01000000 0x01000000
#define FLAG_UNK_02000000 0x02000000
#define FLAG_UNK_04000000 0x04000000
#define FLAG_UNK_08000000 0x08000000
#define FLAG_UNK_10000000 0x10000000
#define FLAG_UNK_20000000 0x20000000
#define FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA 0x40000000
#define FLAG_DESTROY_IF_OUT_OF_CAMERA 0x80000000

#define PLAYER_STATUS_BAT_FORM 0x00000001
#define PLAYER_STATUS_MIST_FORM 0x00000002
#define PLAYER_STATUS_WOLF_FORM 0x00000004
#define PLAYER_STATUS_TRANSFORM                                                \
    (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_WOLF_FORM)
#define PLAYER_STATUS_STONE 0x00000080
#define PLAYER_STATUS_POISON 0x00004000
#define PLAYER_STATUS_CURSE 0x00008000

#define ANIMSET_OVL_FLAG 0x8000
#define ANIMSET_DRA(x) (x)
#define ANIMSET_OVL(x) ((x) | ANIMSET_OVL_FLAG)

#ifndef SOTN_STR
// Decorator to re-encode strings with tools/sotn-str.py when building the game.
// Certain strings in SOTN do not follow the ASCII encoding and each character
// is offseted by 0x20. This is only for strings that use the 8x8 font.
// e.g. _S("I am a Symphony of the Night encoded string")
#define _S(x) (x)
#endif

#define DEMO_KEY_LEN 3
#define DEMO_MAX_LEN 0x2000

#define FONT_W 8               // small font size used for dialogues and menu
#define FONT_H 8               // small font size used for dialogues and menu
#define FONT_GAP FONT_W        // gap between the beginning of two letters
#define FONT_SPACE 4           // gap for the space character
#define MENUCHAR(x) ((x)-0x20) // 8x8 characters are ASCII offset by 0x20
#define DIAG_EOL 0xFF          // end of line
#define DIAG_EOS 0x00          // end of string

#define SAVE_FLAG_CLEAR (1)
#define SAVE_FLAG_REPLAY (2)

#if defined(VERSION_US)
#define MEMCARD_ID "BASLUS-00067DRAX00"
#elif defined(VERSION_HD)
#define MEMCARD_ID "BISLPM-86023DRAX00"
#endif

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

#define STAGE_INVERTEDCASTLE_MASK 0x1F
#define STAGE_INVERTEDCASTLE_FLAG 0x20
typedef enum {
    STAGE_NO0 = 0x00,
    STAGE_NO1 = 0x01,
    STAGE_LIB = 0x02,
    STAGE_CAT = 0x03,
    STAGE_NO2 = 0x04,
    STAGE_CHI = 0x05,
    STAGE_DAI = 0x06,
    STAGE_NP3 = 0x07,
    STAGE_CEN = 0x08,
    STAGE_NO4 = 0x09,
    STAGE_ARE = 0x0A,
    STAGE_TOP = 0x0B,
    STAGE_NZ0 = 0x0C,
    STAGE_NZ1 = 0x0D,
    STAGE_WRP = 0x0E,
    STAGE_NO1_ALT = 0x0F,
    STAGE_NO0_ALT = 0x10,
    STAGE_DRE = 0x12,
    STAGE_NZ0_DEMO = 0x13,
    STAGE_NZ1_DEMO = 0x14,
    STAGE_LIB_DEMO = 0x15,
    STAGE_BO7 = 0x16,
    STAGE_MAR = 0x17,
    STAGE_BO6 = 0x18,
    STAGE_BO5 = 0x19,
    STAGE_BO4 = 0x1A,
    STAGE_BO3 = 0x1B,
    STAGE_BO2 = 0x1C,
    STAGE_BO1 = 0x1D,
    STAGE_BO0 = 0x1E,
    STAGE_ST0 = 0x1F,
    STAGE_RNO0 = STAGE_NO0 | STAGE_INVERTEDCASTLE_FLAG,
    STAGE_RNO1 = STAGE_NO1 | STAGE_INVERTEDCASTLE_FLAG,
    STAGE_RLIB = STAGE_LIB | STAGE_INVERTEDCASTLE_FLAG,
    STAGE_RCAT = STAGE_CAT | STAGE_INVERTEDCASTLE_FLAG,
    STAGE_RNO2 = STAGE_NO2 | STAGE_INVERTEDCASTLE_FLAG,
    STAGE_RCHI = STAGE_CHI | STAGE_INVERTEDCASTLE_FLAG,
    STAGE_RDAI = STAGE_DAI | STAGE_INVERTEDCASTLE_FLAG,
    STAGE_RNO3 = STAGE_NP3 | STAGE_INVERTEDCASTLE_FLAG,
    STAGE_RCEN = STAGE_CEN | STAGE_INVERTEDCASTLE_FLAG,
    STAGE_RNO4 = STAGE_NO4 | STAGE_INVERTEDCASTLE_FLAG,
    STAGE_RARE = STAGE_ARE | STAGE_INVERTEDCASTLE_FLAG,
    STAGE_RTOP = STAGE_TOP | STAGE_INVERTEDCASTLE_FLAG,
    STAGE_RNZ0 = STAGE_NZ0 | STAGE_INVERTEDCASTLE_FLAG,
    STAGE_RNZ1 = STAGE_NZ1 | STAGE_INVERTEDCASTLE_FLAG,
    STAGE_RWRP = STAGE_WRP | STAGE_INVERTEDCASTLE_FLAG,
    STAGE_RNZ1_DEMO = 0x35,
    STAGE_RBO8 = 0x36,
    STAGE_RBO7 = 0x37,
    STAGE_RBO6 = 0x38,
    STAGE_RBO5 = 0x39,
    STAGE_RBO4 = 0x3A,
    STAGE_RBO3 = 0x3B,
    STAGE_RBO2 = 0x3C,
    STAGE_RBO1 = 0x3D,
    STAGE_RBO0 = 0x3E,
    STAGE_MAD = 0x40,
    STAGE_NO3 = 0x41,
    STAGE_IWA_LOAD = 0x42,
    STAGE_IGA_LOAD = 0x43,
    STAGE_HAGI_LOAD = 0x44,
    STAGE_SEL = 0x45,
    STAGE_TE1 = 0x46,
    STAGE_TE2 = 0x47,
    STAGE_TE3 = 0x48,
    STAGE_TE4 = 0x49,
    STAGE_TE5 = 0x4A,
    STAGE_TOP_ALT = 0x4B,
    STAGE_EU_WARNING = 0x70, // EU piracy legal message screen,
    STAGE_ENDING = 0xFE,
    STAGE_MEMORYCARD = 0xFF,
} Stages;

typedef enum {
    GFX_BANK_NONE,
    GFX_BANK_4BPP,
    GFX_BANK_8BPP,
    GFX_BANK_16BPP,
    GFX_BANK_COMPRESSED,
} GfxBankKind;

typedef enum {
    // Clean-up and reset all the gameplay related memory
    Play_Reset = 0,
    // Re-initialize stage-specific resources
    Play_Init,
    // Set random seed if playing a demo
    Play_PrepareDemo,
    // Normal gameplay
    Play_Default,
    // Releases all the resources from the unloading stage
    Play_PrepareNextStage,
    // Load graphics for those stages without a CD room transition
    Play_LoadStageChr,
    // Wait until the previous operation is complete
    Play_WaitStageChr,
    // Load the sound effects specific for the selected stage
    Play_LoadStageSfx,
    // Wait until the previous operation is complete
    Play_WaitStageSfx,
    // Load the overlay program from the disk
    Play_LoadStagePrg,
    // Wait until the previous operation is complete
    Play_WaitStagePrg,

    // Deallocate stage resources
    Gameover_Init = 0,
    // Make screenshot and allocate 3D model for the melting foreground
    Gameover_AllocResources,
    // Wait for something...?
    Gameover_2,
    // Start loading game over graphics from the disk
    Gameover_3,
    // When the file is loaded, move it into the VRAM
    Gameover_4,
    // foreground melting
    Gameover_5,
    // Game over text starts brightening
    Gameover_6,
    // Start using Game Over textures that looks brighter
    Gameover_7,
    // Revert back to the slightly less bright Game Over text
    Gameover_8,
    // Game over screen fade out
    Gameover_9,
    // unknown
    Gameover_10,
    // Return to the title screen (if you are not in ST0)
    Gameover_11,

    Gameover_Alt = 99,
    Gameover_Init_Alt,
    Gameover_AllocResources_Alt,
    Gameover_2_Alt,
    Gameover_3_Alt,
    Gameover_11_Alt = 111,

    NowLoading_2 = 2,
} GameSteps;

typedef enum {
    Demo_None,
    Demo_PlaybackInit,
    Demo_Recording,
    Demo_End,
    Demo_Playback,
} DemoMode;

typedef enum {
    TIMEATTACK_INVALID = -1,
    TIMEATTACK_GET_RECORD,
    TIMEATTACK_SET_RECORD,
    TIMEATTACK_SET_VISITED,
} TimeAttackActions;

typedef enum {
    TIMEATTACK_EVENT_DRACULA_DEFEAT,
    TIMEATTACK_EVENT_ORLOX_DEFEAT,
    TIMEATTACK_EVENT_DOPPLEGANGER_10_DEFEAT,
    TIMEATTACK_EVENT_GRANFALOON_DEFEAT,
    TIMEATTACK_EVENT_MINOTAUR_WEREWOLF_DEFEAT,
    TIMEATTACK_EVENT_SCYLLA_DEFEAT,
    TIMEATTACK_EVENT_SLOGRA_GAIBON_DEFEAT,
    TIMEATTACK_EVENT_HYPPOGRYPH_DEFEAT,
    TIMEATTACK_EVENT_BEELZEBUB_DEFEAT,
    TIMEATTACK_EVENT_SUCCUBUS_DEFEAT,
    TIMEATTACK_EVENT_KARASUMAN_DEFEAT,
    TIMEATTACK_EVENT_RALPH_GRANT_SYPHA_DEFEAT,
    TIMEATTACK_EVENT_DEATH_DEFEAT,
    TIMEATTACK_EVENT_CERBERUS_DEFEAT,
    TIMEATTACK_EVENT_SAVE_RICHTER,
    TIMEATTACK_EVENT_MEDUSA_DEFEAT,
    TIMEATTACK_EVENT_THE_CREATURE_DEFEAT,
    TIMEATTACK_EVENT_LESSER_DEMON_DEFEAT,
    TIMEATTACK_EVENT_DOPPLEGANGER_40_DEFEAT,
    TIMEATTACK_EVENT_AKMODAN_II_DEFEAT,
    TIMEATTACK_EVENT_DARKWING_BAT_DEFEAT,
    TIMEATTACK_EVENT_GALAMOTH_DEFEAT,
    TIMEATTACK_EVENT_FINAL_SAVEPOINT,
    TIMEATTACK_EVENT_MEET_DEATH,
    TIMEATTACK_EVENT_GET_HOLYGLASSES,
    TIMEATTACK_EVENT_MEET_MASTER_LIBRARIAN,
    TIMEATTACK_EVENT_FIRST_MARIA_MEET,
    NUM_TIMEATTACK_EVENTS,
    TIMEATTACK_EVENT_UNUSED_28,
    TIMEATTACK_EVENT_UNUSED_29,
    TIMEATTACK_EVENT_UNUSED_30,
    TIMEATTACK_EVENT_UNUSED_31,
    TIMEATTACK_EVENT_END,
    TIMEATTACK_EVENT_INVALID = 0xFF,
} TimeAttackEvents;

struct Entity;

typedef void (*PfnEntityUpdate)(struct Entity*);

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
    /* 0x18 */ s16 otIdx;
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

// fake struct for D_801375BC
typedef struct {
    RoomLoadDef* def;
} RoomLoadDefHolder;

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
    /* 0x08 */ Stages stageId;
    /* 0x0C */ TimeAttackEvents eventId;
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
    /* 0x08 */ s32 velocityX;
    /* 0x0C */ s32 velocityY;
#ifdef STAGE
    /* 0x10 */ s16 hitboxOffX;
#else // hack to match in DRA and RIC
    /* 0x10 */ u16 hitboxOffX;
#endif
    /* 0x12 */ s16 hitboxOffY;
    /* 0x14 */ u16 facingLeft;
    /* 0x16 */ u16 palette;
    /* 0x18 */ s8 blendMode;
    /* 0x19 */ u8 drawFlags;
    /* 0x1A */ s16 rotX;
    /* 0x1C */ s16 rotY;
    /* 0x1E */ s16 rotZ;
    /* 0x20 */ u16 rotPivotX;
    /* 0x22 */ u16 rotPivotY;
    /* 0x24 */ u16 zPriority;
    /* 0x26 */ u16 entityId;
    /* 0x28 */ PfnEntityUpdate pfnUpdate;
    /* 0x2C */ u16 step;
    /* 0x2E */ u16 step_s;
    /* 0x30 */ u16 params;
    /* 0x32 */ u16 entityRoomIndex;
    /* 0x34 */ s32 flags;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ u16 enemyId;
    /* 0x3C */ u16 hitboxState; // hitbox state
    /* 0x3E */ s16 hitPoints;
    /* 0x40 */ s16 attack;
    /* 0x42 */ s16 attackElement;
    /* 0x44 */ u16 unk44;
    /* 0x46 */ u8 hitboxWidth;
    /* 0x47 */ u8 hitboxHeight;
    /* 0x48 */ u8 hitFlags; // 1 = took hit
    /* 0x49 */ u8 nFramesInvincibility;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ AnimationFrame* unk4C;
    /* 0x50 */ u16 animFrameIdx;
    /* 0x52 */ s16 animFrameDuration;
    /* 0x54 */ s16 animSet;
    /* 0x56 */ s16 animCurFrame;
    /* 0x58 */ s16 stunFrames;
    /* 0x5A */ u16 unk5A;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 primIndex;
    /* 0x68 */ u16 unk68;
    /* 0x6A */ u16 hitEffect;
    /* 0x6C */ u8 unk6C;
    /* 0x6D */ u8 unk6D[11];
    /* 0x78 */ s32 unk78;
    /* 0x7C */ Ext ext;
} Entity; // size = 0xBC

typedef struct {
    /* 0x00 */ s16 animSet;
    /* 0x02 */ u16 zPriority;
    /* 0x04 */ Multi16 unk4;
    /* 0x06 */ u16 palette;
    /* 0x08 */ u8 drawFlags;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 blendMode;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u32 unkC;
    /* 0x10 */ const u8* unk10;
} ObjInit2; // size = 0x14

#define GPU_MAX_TILE_COUNT 0x100

typedef struct GpuBuffer { // also called 'DB' in the PSY-Q samples
    /* 0x00000 */ struct GpuBuffer* next; // next chained buffer
    /* 0x00004 */ DRAWENV draw;           // drawing environment
    /* 0x0005C */ DISPENV disp;           // display environment
    /* 0x00074 */ DR_ENV env[0x10];       // packed drawing environment
    /* 0x00474 */ u_long ot[OTSIZE];      // ordering table
    /* 0x00474 */ DR_MODE drawModes[MAX_DRAW_MODES]; // draw modes
    /* 0x03C74 */ POLY_GT4 polyGT4[0x300];           // textured quads
    /* 0x0D874 */ POLY_G4 polyG4[0x100];             // untextured quads
    /* 0x0FC74 */ POLY_GT3 polyGT3[0x30];            // textured triangles
    /* 0x103F4 */ LINE_G2 lineG2[0x100];             // lines
    /* 0x117F4 */ SPRT_16 sprite16[MAXSPRT16];       // tile map sprites
    /* 0x13FF4 */ TILE tiles[GPU_MAX_TILE_COUNT];    // squared sprites
    /* 0x14FF4 */ SPRT sprite[0x200];                // dynamic-size sprites
} GpuBuffer;                                         // size=0x177F4

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
    /* 0x00 */ u32 xy;
    /* 0x04 */ u32 wh;
    /* 0x08 */ void* data;
} GfxEntry; // size=0xC

typedef struct {
    GfxBankKind kind;
    GfxEntry entries[0];
} GfxBank;

typedef struct {
    /* 0x0 */ GfxEntry* next;
    /* 0x4 */ u16 kind;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 unk8;
    /* 0xA */ s16 unkA;
} GfxLoad; // size=0xC

typedef enum ItemTypes {
    HAND_TYPE,
    HEAD_TYPE,
    ARMOR_TYPE,
    CAPE_TYPE,
    ACCESSORY_TYPE,
    NUM_ITEM_TYPES,
} ItemTypes;

typedef enum {
    ITEM_S_SWORD,
    ITEM_SWORD,
    ITEM_THROW_1,
    ITEM_FIST,
    ITEM_CLUB,
    ITEM_TWOHAND,
    ITEM_FOOD,
    ITEM_BOMB,
    ITEM_THROW_2,
    ITEM_SHIELD,
    ITEM_MEDICINE,
    ITEM_END,
} ItemCategory;

typedef enum { STAT_STR, STAT_CON, STAT_INT, STAT_LCK } Stats;
typedef struct {
    s32 level;
    s32 exp;
    s32 unk8;
} FamiliarStats;

#define RELIC_FLAG_DISABLE 0
#define RELIC_FLAG_FOUND 1
#define RELIC_FLAG_ACTIVE 2
#if defined(VERSION_US)
#define NUM_AVAIL_RELICS (NUM_RELICS - 2)
#elif defined(VERSION_HD)
#define NUM_AVAIL_RELICS (NUM_RELICS)
#endif
typedef enum {
    RELIC_SOUL_OF_BAT,
    RELIC_FIRE_OF_BAT,
    RELIC_ECHO_OF_BAT,
    RELIC_FORCE_OF_ECHO,
    RELIC_SOUL_OF_WOLF,
    RELIC_POWER_OF_WOLF,
    RELIC_SKILL_OF_WOLF,
    RELIC_FORM_OF_MIST,
    RELIC_POWER_OF_MIST,
    RELIC_GAS_CLOUD,
    RELIC_CUBE_OF_ZOE,
    RELIC_SPIRIT_ORB,
    RELIC_GRAVITY_BOOTS,
    RELIC_LEAP_STONE,
    RELIC_HOLY_SYMBOL,
    RELIC_FAERIE_SCROLL,
    RELIC_JEWEL_OF_OPEN,
    RELIC_MERMAN_STATUE,
    RELIC_BAT_CARD,
    RELIC_GHOST_CARD,
    RELIC_FAERIE_CARD,
    RELIC_DEMON_CARD,    // 0x097979
    RELIC_SWORD_CARD,    // 0x09797A
    RELIC_JP_0,          // 0x09797B (nose demon or half fairy)
    RELIC_JP_1,          // 0x09797C
    RELIC_HEART_OF_VLAD, // 0x09797D
    RELIC_TOOTH_OF_VLAD,
    RELIC_RIB_OF_VLAD,
    RELIC_RING_OF_VLAD,
    RELIC_EYE_OF_VLAD,
    NUM_RELICS,
} RelicIds;

#define SPELL_FLAG_KNOWN 0x80
typedef enum {
    SPELL_DARK_METAMORPHOSIS,
    SPELL_SUMMON_SPIRIT,
    SPELL_HELLFIRE,
    SPELL_TETRA_SPIRIT,
    SPELL_WOLF_CHARGE,
    SPELL_SOUL_STEAL,
    SPELL_WING_SMASH,
    SPELL_SWORD_BROTHERS,
    NUM_SPELLS,
} SpellIds;

// Need two familiar enums. One has a zero entry, one does not.
// This one is used in places that need to access the familiar
// stats array...
typedef enum {
    FAM_STATS_BAT,
    FAM_STATS_GHOST,
    FAM_STATS_FAERIE,
    FAM_STATS_DEMON,
    FAM_STATS_SWORD,
    FAM_STATS_YOUSEI,     // JP only
    FAM_STATS_NOSE_DEMON, // JP only
    NUM_FAMILIARS
} FamiliarStatsIds;

// ...and this one is used to designate the active familiar, where
// 0 means no familiar is active, and the rest are off-by-one from
// the previous enum set. Hacky, but works.
typedef enum {
    FAM_ACTIVE_NONE,
    FAM_ACTIVE_BAT = FAM_STATS_BAT + 1,
    FAM_ACTIVE_GHOST = FAM_STATS_GHOST + 1,
    FAM_ACTIVE_FAERIE = FAM_STATS_FAERIE + 1,
    FAM_ACTIVE_DEMON = FAM_STATS_DEMON + 1,
    FAM_ACTIVE_SWORD = FAM_STATS_SWORD + 1,
    FAM_ACTIVE_YOUSEI = FAM_STATS_YOUSEI + 1,
    FAM_ACTIVE_NOSE_DEMON = FAM_STATS_NOSE_DEMON + 1,
} FamiliarActiveIds;

typedef struct {
    /* 80097964 */ u8 relics[30];
    /* 80097982 */ u8 spells[NUM_SPELLS];
    /* 8009798A */ u8 equipHandCount[169];
    /* 80097A33 */ u8 equipBodyCount[90];
    /* 80097A8D */ u8 equipHandOrder[169];
    /* 80097B36 */ u8 equipBodyOrder[90];
    /* 80097B90 */ u8 saveName[12];
    /* 80097B9C */ u32 spellsLearnt;
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
    /* 80097C24 */ s32 defenseEquip;
    /* 80097C28 */ u16 defenseElement;
    /* 80097C2A */ u16 D_80097C2A;
    /* 80097C2C */ u16 D_80097C2C;
    /* 80097C2E */ u16 D_80097C2E;
    /* 80097C30 */ s32 timerHours;
    /* 80097C34 */ s32 timerMinutes;
    /* 80097C38 */ s32 timerSeconds;
    /* 80097C3C */ s32 timerFrames;
    /* 80097C40 */ u32 D_80097C40;
    /* 80097C44 */ FamiliarStats statsFamiliars[NUM_FAMILIARS];
} PlayerStatus; /* size=0x334 */

typedef struct {
    /* 0x00, 8003C9A8 */ s32 cursorMain;
    /* 0x04, 8003C9AC */ s32 cursorRelic;
    /* 0x08, 8003C9B0 */ s32 cursorEquip;
    /* 0x0C, 8003C9B4 */ s32 cursorEquipType[NUM_ITEM_TYPES];
    /* 0x20, 8003C9C8 */ s32 scrollEquipType[NUM_ITEM_TYPES];
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
    /* 0x030, 0x8003CA28 */ s32 timeAttackRecords[TIMEATTACK_EVENT_END];
    /* 0x0B0, 0x8003CAA8 */ s32 cloakColors[6];
    /* 0x0C8, 0x8003CAC0 */ s32 windowColors[3];
    /* 0x0D4, 0x8003CACC */ s32 equipOrderTypes[ITEM_END];
    /* 0x100, 0x8003CAF8 */ s32 isCloakLiningReversed;
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
    /* 0x10 */ u8 params : 8;
} LayoutRect; // size = 0x14

typedef struct {
    /* 0x00 */ const u16* layout;
    /* 0x04 */ const TileDefinition* tileDef;
    /* 0x08 */ const LayoutRect rect;
    /* 0x0C */ const u16 zPriority;
    /* 0x0E */ const u16 flags;
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
    /* 8003C78C */ UnkStructClut** cluts;
    /* 8003C790 */ void* unk1C; // related to entity layout
    /* 8003C794 */ RoomDef* tileLayers;
    /* 8003C798 */ GfxBank** gfxBanks;
    /* 8003C79C */ void (*unk28)(void);
    /* 8003C7A0 */ void (*unk2c)(void); // similar to Update
    /* 8003C7A4 */ void* unk30;
    /* 8003C7A8 */ s32* unk34;
    /* 8003C7AC */ s32* unk38;
    /* 8003C7B0 */ void (*unk3C)(void);
} Overlay;

typedef enum {
    EFFECT_SOLID = 1 << 0,
    EFFECT_UNK_0002 = 1 << 1,
    EFFECT_QUICKSAND = 1 << 2,
    EFFECT_WATER = 1 << 3,
    EFFECT_MIST_ONLY = 1 << 4,
    EFFECT_UNK_0020 = 1 << 5,
    // Used when you jump from below to a platform. You can drop below.
    EFFECT_SOLID_FROM_ABOVE = 1 << 6,
    // Doesn't collide when falling on it but you cannot go back up.
    EFFECT_SOLID_FROM_BELOW = 1 << 7,
    EFFECT_UNK_0100 = 1 << 8,
    EFFECT_UNK_0200 = 1 << 9,
    EFFECT_UNK_0400 = 1 << 10,
    EFFECT_UNK_0800 = 1 << 11,
    EFFECT_UNK_1000 = 1 << 12,
    EFFECT_UNK_2000 = 1 << 13,
    EFFECT_UNK_4000 = 1 << 14,
    EFFECT_UNK_8000 = 1 << 15,

    // Aggregate helpers below:
    EFFECT_NOTHROUGH = EFFECT_SOLID | EFFECT_QUICKSAND,
    EFFECT_NOTHROUGH_PLUS = EFFECT_SOLID | EFFECT_UNK_0002 | EFFECT_QUICKSAND
} ColliderEffectFlags;

typedef struct Collider {
    /* 0x00 */ s32 effects;
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
    /* 0x0C */ u16 hitboxState;
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
    /* 0x24 */ s32 flags;
} EnemyDef; /* size=0x28 */

typedef struct {
    /* 0x00 */ s16 attack;
    /* 0x02 */ s16 heartCost;
    /* 0x04 */ u16 attackElement;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 nFramesInvincibility;
    /* 0x08 */ u16 stunFrames;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 blueprintNum; // Blueprint for entity factory spawning subwpn
    /* 0x0C */ u16 hitboxState;
    /* 0x0E */ u16 hitEffect;
    /* 0x10 */ u8 crashId; // the ID for the crash version of this subweapon
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u16 entityRoomIndex;
} SubweaponDef; /* size=0x14 */

// Defines the equipment that can be set on left and right hand
// This includes weapons, throw weapons, consumable and restoration items.
// g_EquipDefs it is assumed the equip data starts from here
// https://github.com/3snowp7im/SotN-Randomizer/blob/master/src/stats.js
typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ const char* description;
    /* 0x08 */ s16 attack;
    /* 0x0A */ s16 defense;
    /* 0x0C */ u16 element;
    /* 0x0E */ u8 itemCategory;
    /* 0x0F */ u8 weaponId;
    /* 0x10 */ u8 palette;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 playerAnim;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 lockDuration;
    /* 0x16 */ u8 chainLimit;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 specialMove;
    /* 0x19 */ u8 isConsumable;
    /* 0x1A */ u8 enemyInvincibilityFrames;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u32 comboSub;
    /* 0x20 */ u32 comboMain;
    /* 0x24 */ u16 mpUsage;
    /* 0x26 */ u16 stunFrames;
    /* 0x28 */ u16 hitType;
    /* 0x2A */ u16 hitEffect;
    /* 0x2C */ u16 icon;
    /* 0x2E */ u16 iconPalette;
    /* 0x30 */ u16 criticalRate;
    /* 0x32 */ u16 unk32;
} Equipment; /* size=0x34 */

// Defines armor, cloak and rings
typedef struct {
    /* 00 */ const char* name;
    /* 04 */ const char* description;
    /* 08 */ s16 attBonus;
    /* 0A */ s16 defBonus;
    /* 0C */ u8 statsBonus[4];
    /* 10 */ u16 unk10;
    /* 10 */ u16 unk12;
    /* 14 */ u16 unk14;
    /* 10 */ u16 unk16;
    /* 18 */ u16 icon;
    /* 1A */ u16 iconPalette;
    /* 1C */ u16 equipType;
    /* 1E */ u16 unk1E;
} Accessory; /* size=0x20 */

typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ const char* desc;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ s32 unk0C;
} RelicDesc; /* size=0x10 */

typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ const char* desc;
    /* 0x08 */ u16 icon;
    /* 0x0A */ u16 iconPalette;
#ifndef VERSION_BETA
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
#endif
} RelicOrb; /* size=0x10 */

typedef struct {
    /* 0x00 */ const char* nextCharDialogue; // ptr to dialogue next character
    /* 0x04 */ u16 startX;                   // starting x coord
    /* 0x06 */ u16 nextLineY;                // next line y coord
    /* 0x08 */ u16 startY;                   // starting y coord
    /* 0x0A */ u16 nextCharX;                // next char x coord
    /* 0x0C */ u16 nextLineX;                // next line x coord
    /* 0x0E */ s16 nextCharY;                // next char y coord
    /* 0x10 */ u16 portraitAnimTimer;        // portrait animation timer
    /* 0x12 */ u16 unk12;                    // unknown
    /* 0x14 */ u16 clutIndex;                // CLUT index
    /* 0x16 */ u8 nextCharTimer;             // timer to next character
    /* 0x17 */ u8 unk17;                     // unknown
    /* 0x18 */ Primitive* prim[6];           // for dialogue graphics rendering
    /* 0x30 */ s32 primIndex[3];             // primIndices: unk, actorName, unk
    /* 0x3C */ u16 unk3C;                    // unknown
    /* 0x3E */ u16 timer;                    // global timer
    /* 0x40 */ const char* unk40;            // dialogue settings, maybe?
} Dialogue;                                  // size = 0x44

typedef struct {
    /* 8003C774 */ Overlay o;
    /* 8003C7B4 */ void (*FreePrimitives)(s32);
    /* 8003C7B8 */ s16 (*AllocPrimitives)(PrimitiveType type, s32 count);
    /* 8003C7BC */ void (*CheckCollision)(s32 x, s32 y, Collider* res, s32 unk);
    /* 8003C7C0 */ void (*func_80102CD8)(s32 arg0);
    /* 8003C7C4 */ void (*UpdateAnim)(FrameProperty* frameProps, s32* arg1);
    /* 8003C7C8 */ void (*SetSpeedX)(s32 value);
    /* 8003C7CC */ Entity* (*GetFreeEntity)(s16 start, s16 end);
    /* 8003C7D0 */ void (*GetEquipProperties)(
        s32 handId, Equipment* res, s32 equipId);
    /* 8003C7D4 */ s32 (*func_800EA5E4)(u32);
    /* 8003C7D8 */ void (*LoadGfxAsync)(s32 gfxId);
    /* 8003C7DC */ void (*PlaySfx)(s32 sfxId);
    /* 8003C7E0 */ s16 (*func_800EDB58)(s32, s32);
    /* 8003C7E4 */ void (*func_800EA538)(s32 arg0);
    /* 8003C7E8 */ void (*g_pfn_800EA5AC)(u16 arg0, u8 arg1, u8 arg2, u8 arg3);
    /* 8003C7EC */ void (*func_801027C4)(u32 arg0);
    /* 8003C7F0 */ void (*func_800EB758)(
        s16 pivotX, s16 pivotY, Entity* e, u16 flags, POLY_GT4* p, u8 flipX);
    /* 8003C7F4 */ Entity* (*CreateEntFactoryFromEntity)(
        Entity* self, u32 flags, s32 arg2);
    /* 8003C7F8 */ bool (*func_80131F68)(void);
    /* 8003C7FC */ DR_ENV* (*func_800EDB08)(POLY_GT4* poly);
    /* 8003C800 */ u16* (*func_80106A28)(u32 arg0, u16 kind);
    /* 8003C804 */ void (*func_80118894)(Entity*);
    /* 8003C808 */ EnemyDef* enemyDefs;
    /* 8003C80C */ Entity* (*func_80118970)(void);
    /* 8003C810 */ s32 (*func_80118B18)(Entity* ent1, Entity* ent2, s32 arg2);
    ;
    /* 8003C814 */ s32 (*UpdateUnarmedAnim)(s8* frameProps, u16** frames);
    /* 8003C818 */ void (*func_8010DBFC)(s32*, s32*);
    /* 8003C81C */ void (*func_80118C28)(s32 arg0);
    /* 8003C820 */ void (*func_8010E168)(s32 arg0, s16 arg1);
    /* 8003C824 */ void (*func_8010DFF0)(s32 arg0, s32 arg1);
    /* 8003C828 */ u16 (*DealDamage)(
        Entity* enemyEntity, Entity* attackerEntity);
    /* 8003C82C */ void (*LoadEquipIcon)(s32 equipIcon, s32 palette, s32 index);
    /* 8003C830 */ Equipment* equipDefs;
    /* 8003C834 */ Accessory* accessoryDefs;
    /* 8003C838 */ void (*AddHearts)(s32 value);
    /* 8003C83C */ bool (*LoadMonsterLibrarianPreview)(s32 monsterId);
    /* 8003C840 */ s32 (*TimeAttackController)(
        TimeAttackEvents eventId, TimeAttackActions action);
    /* 8003C844 */ void* (*func_8010E0A8)(void);
    /* 8003C848 */ void (*func_800FE044)(s32, s32);
    /* 8003C84C */ void (*AddToInventory)(u16 itemId, s32 itemCategory);
    /* 8003C850 */ RelicOrb* relicDefs;
    /* 8003C854 */ void (*InitStatsAndGear)(bool debugMode);
    /* 8003C858 */ s32 (*func_80134714)(s32 arg0, s32 arg1, s32 arg2);
    /* 8003C85C */ s32 (*func_80134678)(s16 arg0, u16 arg1);
    /* 8003C860 */ void (*func_800F53A4)(void);
    /* 8003C864 */ u32 (*CheckEquipmentItemCount)(u32 itemId, u32 equipType);
    /* 8003C868 */ void (*func_8010BF64)(Unkstruct_8010BF64* arg0);
    /* 8003C86C */ void (*func_800F1FC4)(s32 arg0);
    /* 8003C870 */ void* func_800F2288;
    /* 8003C874 */ void (*func_8011A3AC)(
        Entity* entity, s32 arg1, s32 arg2, Unkstruct_8011A3AC* arg3);
    /* 8003C878 */ s32 (*func_800FF460)(s32 arg0);
    /* 8003C87C */ s32 (*func_800FF494)(EnemyDef* arg0);
    /* 8003C880 */ bool (*CdSoundCommandQueueEmpty)(void);
    /* 8003C884 */ bool (*func_80133950)(void);
    /* 8003C888 */ bool (*func_800F27F4)(s32 arg0);
    /* 8003C88C */ s32 (*func_800FF110)(s32 arg0);
    /* 8003C890 */ s32 (*func_800FD664)(s32 arg0);
    /* 8003C894 */ s32 (*func_800FD5BC)(Unkstruct_800FD5BC* arg0);
    /* 8003C898 */ void (*LearnSpell)(s32 spellId);
    /* 8003C89C */ void (*DebugInputWait)(const char* str);
    /* 8003C8A0 */ void* unused12C;
    /* 8003C8A4 */ void* unused130;
    /* 8003C8A8 */ void* unused134;
    /* 8003C8AC */ void* unused138;
    /* 8003C8B4 */ void* unused13C;
} GameApi; /* size=0x140 */

/**** Helper signatures ****/
extern void (*g_api_FreePrimitives)(s32);
extern s16 (*g_api_AllocPrimitives)(PrimitiveType type, s32 count);
extern void (*g_api_CheckCollision)(s32 x, s32 y, Collider* res, s32 unk);
extern void (*g_api_func_80102CD8)(s32 arg0);
extern void (*g_api_UpdateAnim)(FrameProperty* frameProps, s32* arg1);
extern void (*g_api_SetSpeedX)(s32 value);
extern Entity* (*g_api_GetFreeEntity)(s16 start, s16 end);
extern void (*g_api_GetEquipProperties)(
    s32 handId, Equipment* res, s32 equipId);
extern s32 (*g_api_func_800EA5E4)(u32);
extern void (*g_api_LoadGfxAsync)(s32);
extern void (*g_api_PlaySfx)(s32 sfxId);
extern s16 (*g_api_func_800EDB58)(s32, s32);
extern void (*g_api_func_800EA538)(s32 arg0);
extern void (*g_api_g_pfn_800EA5AC)(u16 arg0, u8 arg1, u8 arg2, u8 arg3);
extern Entity* (*g_api_CreateEntFactoryFromEntity)(
    Entity* self, u32 flags, s32 arg2);
extern bool (*g_api_func_80131F68)(void);
extern DR_ENV* (*g_api_func_800EDB08)(POLY_GT4* poly);
extern u16* (*g_api_func_80106A28)(u16 arg0, u16 kind);
extern void (*g_api_func_80118894)(Entity*);
extern EnemyDef* g_api_enemyDefs;
extern u32 (*g_api_UpdateUnarmedAnim)(s8* frameProps, u16** frames);
extern void (*g_api_func_8010DBFC)(s32*, s32*);
extern void (*g_api_func_8010E168)(s32 arg0, s16 arg1);
extern void (*g_api_func_8010DFF0)(s32 arg0, s32 arg1);
extern u16 (*g_api_DealDamage)(Entity* enemyEntity, Entity* attackerEntity);
extern void (*g_api_LoadEquipIcon)(s32 equipIcon, s32 palette, s32 index);
extern Equipment* g_api_equipDefs;
extern Accessory* g_api_g_AccessoryDefs;
extern void (*g_api_AddHearts)(s32 value);
extern s32 (*g_api_TimeAttackController)(
    TimeAttackEvents eventId, TimeAttackActions action);
extern void* (*g_api_func_8010E0A8)(void);
extern void (*g_api_func_800FE044)(s32, s32);
extern void (*g_api_AddToInventory)(u16 itemId, s32 itemCategory);
extern RelicOrb* g_api_relicDefs;
extern s32 (*g_api_func_80134714)(s32 arg0, s32 arg1, s32 arg2);
extern s32 (*g_api_func_80134678)(s16 arg0, u16 arg1);
extern void (*g_api_func_800F53A4)(void);
extern u32 (*g_api_CheckEquipmentItemCount)(u32 itemId, u32 equipType);
extern void (*g_api_func_8010BF64)(Unkstruct_8010BF64* arg0);
extern void (*g_api_func_800F1FC4)(s32 arg0);
extern void (*g_api_func_8011A3AC)(
    Entity* entity, s32 arg1, s32 arg2, Unkstruct_8011A3AC* arg3);
extern s32 (*g_api_func_800FF460)(s32 arg0);
extern s32 (*g_api_func_800FF494)(EnemyDef* arg0);
extern bool (*g_api_CdSoundCommandQueueEmpty)(void);
extern bool (*g_api_func_80133950)(void);
extern bool (*g_api_func_800F27F4)(s32 arg0);
extern s32 (*g_api_func_800FF110)(s32 arg0);
extern s32 (*g_api_func_800FD664)(s32 arg0);
extern s32 (*g_api_func_800FD5BC)(Unkstruct_800FD5BC* arg0);
extern void (*g_api_LearnSpell)(s32 spellId);
extern void (*g_api_func_800E2438)(const char* str);
/***************************/

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
    /* 0x00 */ u16** frames;
    /* 0x04 */ s8* frameProps;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u16 soundId;
    /* 0x0C */ u8 ACshift;
    /* 0x0D */ u8 soundFrame;
} AnimSoundEvent;

#define TILE_SIZE 16
#define TILE_MASK 0x0F
#define N_HORIZ_TILES 17
#define N_VERTI_TILES 16

typedef struct {
    /* 800730D8 0x00 */ u16* layout;
    /* 800730DC 0x04 */ TileDefinition* tileDef;
    /* 800730E0 0x08 */ f32 scrollX;
    /* 800730E4 0x0C */ f32 scrollY;
    /* 800730E8 0x10 */ u32 D_800730E8;
    /* 800730EC 0x14 */ u32 D_800730EC;
    /* 800730F0 0x18 */ u32 zPriority;
    /* 800730F4 0x1C */ u32 flags;
    /* 800730F8 0x20 */ u32 w;
    /* 800730FC 0x24 */ u32 h;
    /* 80073100 0x28 */ u32 D_80073100;
    /* 80073104 0x2C */ u32 scrollKind;
} BgLayer; /* size=0x30 */

typedef struct {
    /* 80073084 */ u16* fg;
    /* 80073088 */ TileDefinition* D_80073088;
    /* 8007308C */ f32 cameraX;
    /* 80073090 */ f32 cameraY;
    /* 80073094 */ s32 D_80073094;
    /* 80073098 */ s32 D_80073098;
    /* 8007309C */ s32 zPriority;
    /* 800730A0 */ s32 flags;
    /* 800730A4 */ s32 hSize;
    /* 800730A8 */ s32 vSize;
    /* 800730AC */ u32 unk8;
    /* 800730B0 */ s32 left;
    /* 800730B4 */ s32 top;
    /* 800730B8 */ s32 right;
    /* 800730BC */ s32 bottom;
    /* 800730C0 */ s32 x;
    /* 800730C4 */ s32 y;
    /* 800730C8 */ s32 width;
    /* 800730CC */ s32 height;
    /* 800730D0 */ s32 unk30;
    /* 800730D4 */ s32 D_800730D4;
    /* 800730D8 */ BgLayer bg[MAX_BG_LAYER_COUNT];
} Tilemap;

typedef struct {
    /* D_8003C708 */ u16 flags;
    /* D_8003C70A */ u16 unk2;
    /* D_8003C70C */ u16 unk4;
    /* D_8003C70E */ s16 zPriority;
} FgLayer; /* size=0x8 */

typedef struct {
    /* 80072BD0 */ Collider colliders[8];
    /* 80072CF0 */ Collider colliders2[14];
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
    /* 80072F34 */ u32 unk14;
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
    /* 80072F7E */ u16 unk5E; // status ailment timer
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

// Primitive used ad-hoc for the Player entity and the after-image effect
typedef struct {
    /* 0x00 */ RECT rect0;
    /* 0x08 */ RECT rect1;
    /* 0x10 */ RECT rect2;
    /* 0x18 */ u8 r0;
    /* 0x19 */ u8 g0;
    /* 0x1A */ u8 b0;
    /* 0x1B */ u8 enableColorBlend;
    /* 0x1C */ u8 r1;
    /* 0x1D */ u8 g1;
    /* 0x1E */ u8 b1;
    /* 0x1F */ u8 tpage;
    /* 0x20 */ u8 r2;
    /* 0x21 */ u8 g2;
    /* 0x22 */ u8 b2;
    /* 0x23 */ u8 flipX;
    /* 0x24 */ u8 r3;
    /* 0x25 */ u8 g3;
    /* 0x26 */ u8 b3;
    /* 0x27 */ u8 unk27;
} PlayerDraw; /* size = 0x28 */

extern s32 D_8003925C;
extern s32 g_IsTimeAttackUnlocked;

// Holds flags that checks if certain switches are enabled to allow to have
// shortcuts around the castle. One typical example is the wood column that
// prevents the player to enter in the warp room. When g_CastleFlags[0x32] the
// column will disappear.
extern u8 g_CastleFlags[0x300];
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
extern s32 D_8003C738;
extern s32 D_8003C73C;
extern u32 D_8003C744;
extern u32 g_RoomCount;
extern GameApi g_api;
extern s32 D_8003C8B8;
extern u32 g_GameTimer; // Increases when unpaused
extern Unkstruct_8003C908 D_8003C908;
extern s32 D_8003C90C[2];
extern u32 g_Timer; // Increases continuously
/* 0x8003C99C */ extern s32 D_8003C99C;
/* 0x8003C9A0 */ extern s32 g_PlayableCharacter;
/* 0x8003C9A4 */ extern u32 D_8003C9A4; // when player change stages?
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
extern u8 g_CastleMap[0x800];
extern s32 D_8006C374;
extern s32 D_8006C378;
extern GpuBuffer* g_CurrentBuffer; // g_CurrentBuffer;
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
extern Unkstruct_8006C3C4 D_8006C3C4[32];
extern s32 g_Servant; // Currently selected familiar in the menu
extern u16 g_Clut[];
extern u32 D_8006EBCC;
extern u16 D_8006EBE0;
extern u16 D_8006F3CC[];
extern u16 D_8006F42C[];
extern s16 D_800705CC[];
extern u32 D_80070BCC;

extern PlayerState g_Player;
extern u16 g_Player_D_80072EF6; // TODO merge with g_Player

extern GfxLoad g_GfxLoad[0x10];
extern u32 g_GameStep;
extern s32 g_ServantLoaded; // Currently loaded servant in-memory
extern Event g_EvSwCardEnd; // 80073068
extern Event g_EvSwCardErr; // 8007306C
extern Event g_EvSwCardTmo; // 80073070
extern s32 D_80073074;      // Probably also an Event?
extern Event g_EvSwCardNew; // 80073078
extern s32 D_8007307C;      // Maybe also an Event?
extern s32 D_80073080;

extern Tilemap g_Tilemap;

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

extern Entity D_8007A958[]; // &g_Entities[160]
extern Entity D_8007C0D8[]; // &g_Entities[192]
extern Entity D_8007DE38[];
extern unkGraphicsStruct g_unkGraphicsStruct;
extern s32 g_entityDestroyed[];
extern Entity D_8007EF1C;
extern Event g_EvHwCardEnd;
extern Event g_EvHwCardErr;
extern Event g_EvHwCardTmo;
extern Event g_EvHwCardNew;
extern u8 g_Pix[4][128 * 128 / 2];
extern Primitive g_PrimBuf[MAX_PRIM_COUNT];
extern s32 playerX;
extern s32 playerY;
extern u32 g_randomNext;
extern s32 D_80096ED8[];
extern s8 D_80097B98;
extern s8 D_80097B99;
extern s32 D_800973EC; // flag to check if the menu is shown
extern s32 D_800973F8;
extern s32 D_800973FC;
extern s32 D_80097400[];
extern s32 D_8009740C[];
extern s32 g_BottomCornerTextTimer;
extern s32 g_BottomCornerTextPrims;
extern s32 D_80097418;
extern s32 D_8009741C;
extern s32 D_80097420[];
extern s32 D_80097424;
extern s32 D_80097448[]; // underwater physics. 7448 and 744C. Could be struct.
extern s32 D_80097450;
extern s32 D_80097488;
// Overlapping data, worth further investigation
extern u16 D_8009748A[];
extern s32 D_8009748C;

/*
 * Elevator moving, "underflowed" to 0xFF
 * when going up, 0x1 when going up
 */
extern u16 D_8009748E[];
extern Pad g_pads[PAD_COUNT];
extern Stages g_StageId;
extern s32 D_800974A4; // map open
extern DR_ENV D_800974AC;
extern s32 g_UseDisk;
extern s32 D_800978B4;
extern s32 D_800978C4;
extern u32 g_MenuStep;
extern char D_80097902[];
extern s32 D_80097904;
extern s32 D_80097908;
extern s32 D_8009790C;
extern s32 D_80097910;
extern DemoMode g_DemoMode;
extern s32 g_LoadOvlIdx; // 0x80097918
extern s32 D_8009791C;
extern s32 D_80097920;
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
extern PlayerDraw g_PlayerDraw[0x10];
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
extern s32 g_DebugPlayer;
extern s32 D_80098894;

#endif
