// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef GAME_H
#define GAME_H
#include "common.h"
#include "log.h"
#include "castle_flags.h"
#include "player_steps.h"
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

// PSP does & 7FFF for many calls to rand(), PS1 does not.
// This works around that.
#ifdef VERSION_PSP
#define PSP_RANDMASK 0x7FFF
#else
#define PSP_RANDMASK 0xFFFFFFFF
#endif

#define SPAD(x) ((s32*)SP(x * sizeof(s32)))

typedef long Event;

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

#include "primitive.h"

typedef enum {
    DRAW_DEFAULT = 0x00,
    DRAW_TRANSP = 0x01, // make it semi transparent
    DRAW_UNK02 = 0x02,  // unknown
    DRAW_COLORS = 0x04, // use color blending
    DRAW_HIDE = 0x08,   // do not render the primitive
    DRAW_TPAGE = 0x10,  // use custom tpage
    DRAW_TPAGE2 = 0x20, // use custom tpage
    DRAW_UNK_40 = 0x40,
    DRAW_MENU = 0x80,       // render only if D_800973EC is set
    DRAW_UNK_100 = 0x100,   // unknown
    DRAW_UNK_200 = 0x200,   // unknown
    DRAW_UNK_400 = 0x400,   // unknown
    DRAW_UNK_800 = 0x800,   // unknown
    DRAW_UNK_1000 = 0x1000, // unknown
    DRAW_ABSPOS = 0x2000,   // use absolute coordinates with DRAW_MENU
} DrawMode;

#include "entity.h"

#define COLORS_PER_PAL (16)
#define COLOR_BPP (16)
#define COLOR_LEN ((COLOR_BPP) / 8)
#define PALETTE_LEN ((COLORS_PER_PAL) * ((COLOR_BPP) / 8))
#define COLOR16(r, g, b, a) (r) + ((g) << 5) + ((b) << 10) + ((a) << 15)
// PS1 and PSP use different values for most of these.
#ifndef VERSION_PSP
#define OTSIZE 0x200
#define MAXSPRT16 0x280
#define MAX_DRAW_MODES 0x400
#define MAX_POLY_GT4_COUNT 0x300
#endif
#ifdef VERSION_PSP
#define OTSIZE 0x600
#define MAXSPRT16 0x320
// Very low confidence on these. These make GpuBuffer the right size.
// More decomp will give proper sizes for individual members.
#define MAX_DRAW_MODES 0x1F0
#define MAX_POLY_GT4_COUNT 0x2F0
#endif
#define MAX_TILE_COUNT 0x100
#define MAX_LINE_G2_COUNT 0x100
#define MAX_POLY_GT3_COUNT 0x30
#define MAX_POLY_G4_COUNT 0x100
#define MAX_SPRT_COUNT 0x200
#define MAX_ENV_COUNT 0x10

#define DISP_ALL_H 240
#define DISP_STAGE_W 256
#define DISP_STAGE_H DISP_ALL_H
#define DISP_MENU_W 384
#define DISP_MENU_H DISP_ALL_H
#define DISP_TITLE_W 512
#define DISP_TITLE_H DISP_ALL_H
// Width in pixel of how wide is the horizontal camera during normal game play
#define STAGE_WIDTH 256

#ifdef VERSION_PSP // PSP does not need a double buffer
#define DISP_STAGE_NEXT_X 0
#else
#define DISP_STAGE_NEXT_X DISP_STAGE_W
#endif

#define BUTTON_COUNT 8
#define PAD_COUNT 2

#if !defined(VERSION_PSP)
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

#else
#define PAD_L1 0x0100
#define PAD_R1 0x0200
#define PAD_TRIANGLE 0x1000
#define PAD_CIRCLE 0x2000
#define PAD_CROSS 0x4000
#define PAD_SQUARE 0x8000
#define PAD_SELECT 0x0001
#define PAD_START 0x0008
#define PAD_UP 0x0010
#define PAD_RIGHT 0x0020
#define PAD_DOWN 0x0040
#define PAD_LEFT 0x0080
#endif

// Game Buttons unofficially refers to buttons used in playing the game.
// Direction, action and shoulder buttons. Any button except start or select.
#define GAMEBUTTONS (~(PAD_START | PAD_SELECT))

#define MAX_PRIM_COUNT 0x500
#define MAX_PRIM_ALLOC_COUNT 0x400
#define MAX_BG_LAYER_COUNT 16

#define RENDERFLAGS_NOSHADOW 2
#define PLAYER_ALUCARD 0
#define PLAYER_RICHTER 1
#define PLAYER_MARIA 2
#define MAX_GOLD 999999
#define HEART_VESSEL_INCREASE 5
#define HEART_VESSEL_RICHTER 30
#define LIFE_VESSEL_INCREASE 5
#define FALL_GRAVITY 0x4000
#define FALL_TERMINAL_VELOCITY 0x60000

#define WEAPON_0_START 0xE0
#define WEAPON_0_END (WEAPON_1_START - 1)
#define WEAPON_1_START 0xF0

#ifndef VERSION_PC
#define DRA_PRG_PTR 0x800A0000
#define RIC_PRG_PTR 0x8013C000
#define SPRITESHEET_PTR 0x8013C020 // g_PlOvlSpritesheet
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

#else
#define DRA_PRG_PTR 0x800A0000
#define RIC_PRG_PTR 0x8013C000
#define SPRITESHEET_PTR g_PlOvlSpritesheet
#define FAMILIAR_PTR 0x80170000
#define WEAPON0_PTR 0x8017A000
#define WEAPON1_PTR 0x8017D000
#define STAGE_PRG_PTR 0x80180000
#define CASTLE_MAP_PTR g_BmpCastleMap
#ifndef DEMO_KEY_PTR
#define DEMO_KEY_PTR 0x801E8000
#endif
#define SIM_CHR0 0x80280000
#define SIM_CHR1 0x80284000
#define SIM_PTR 0x80280000

extern u8 g_BmpCastleMap[0x20000];

#endif

// used with various equipment, enemy resistances, etc
#define ELEMENT_HIT 0x20
#define ELEMENT_CUT 0x40
#define ELEMENT_POISON 0x80
#define ELEMENT_CURSE 0x100
#define ELEMENT_STONE 0x200
#define ELEMENT_WATER 0x400
#define ELEMENT_DARK 0x800
#define ELEMENT_HOLY 0x1000
#define ELEMENT_ICE 0x2000
#define ELEMENT_THUNDER 0x4000
#define ELEMENT_FIRE 0x8000
#define ELEMENT_UNK_10000 0x10000

// Indices of g_StatBuffTimers
typedef enum {
    SBT_DEF,
    SBT_ATK,
    SBT_LCK,
    SBT_INT,
    SBT_STR,
    SBT_RESISTFIRE,
    SBT_RESISTICE,
    SBT_RESISTTHUNDER,
    SBT_RESISTCURSE,
    SBT_RESISTHOLY,
    SBT_RESISTSTONE,
    SBT_RESISTDARK,
} StatBuffTimers;

// Flags for entity->drawFlags
typedef enum {
    FLAG_DRAW_DEFAULT = 0x00,
    FLAG_DRAW_ROTX = 0x01,
    FLAG_DRAW_ROTY = 0x02,
    FLAG_DRAW_ROTZ = 0x04,
    FLAG_DRAW_UNK8 = 0x08, // Salem Witch uses this for shadows
                           // Looks like semi-transparency?
    FLAG_DRAW_UNK10 = 0x10,
    FLAG_DRAW_UNK20 = 0x20,
    FLAG_DRAW_UNK40 = 0x40,
    // renderEntities uses this to disable rendering on even/odd g_Timer
    FLAG_BLINK = 0x80,
    FLAG_DRAW_UNK100 = 0x100,
    FLAG_DRAW_UNK400 = 0x400
} DrawFlag;

// Flags for entity->flags
typedef enum {
    FLAG_UNK_10 = 0x10,
    FLAG_UNK_20 = 0x20,
    FLAG_UNK_40 = 0x40,
    FLAG_UNK_80 = 0x80,
    // Signals that the entity should run its death routine
    FLAG_DEAD = 0x100,
    FLAG_UNK_200 = 0x200,
    FLAG_UNK_400 = 0x400,
    FLAG_UNK_800 = 0x800,
    FLAG_UNK_1000 = 0x1000,
    FLAG_UNK_2000 = 0x2000,
    FLAG_UNK_4000 = 0x4000,
    FLAG_UNK_8000 = 0x8000,
    FLAG_UNK_10000 = 0x10000,
    FLAG_UNK_20000 = 0x20000, // func_8011A9D8 will destroy if not set
    FLAG_POS_PLAYER_LOCKED = 0x40000,
    FLAG_UNK_80000 = 0x80000,
    FLAG_UNK_100000 = 0x100000,
    FLAG_UNK_00200000 = 0x00200000,
    FLAG_UNK_400000 = 0x400000,
    // When an entity used AllocPrimitives and their primIndex set.
    // At their destruction they need to free the prims with FreePrimitives.
    FLAG_HAS_PRIMS = 0x800000,
    FLAG_NOT_AN_ENEMY = 0x01000000,
    FLAG_UNK_02000000 = 0x02000000,
    FLAG_KEEP_ALIVE_OFFCAMERA = 0x04000000,
    FLAG_POS_CAMERA_LOCKED = 0x08000000,
    FLAG_UNK_10000000 = 0x10000000, // CHI func_801A169C: "Is Airborne"?
    FLAG_UNK_20000000 = 0x20000000,
    FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA = 0x40000000,
    FLAG_DESTROY_IF_OUT_OF_CAMERA = 0x80000000,
} EntityFlag;

// document g_Player.status
typedef enum {
    PLAYER_STATUS_BAT_FORM = 0x1,
    PLAYER_STATUS_MIST_FORM = 0x2,
    PLAYER_STATUS_WOLF_FORM = 0x4,
    PLAYER_STATUS_TRANSFORM =
        (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM |
         PLAYER_STATUS_WOLF_FORM),
    PLAYER_STATUS_UNK8 = 0x8,
    PLAYER_STATUS_UNK10 = 0x10,
    PLAYER_STATUS_CROUCH = 0x20,
    PLAYER_STATUS_UNK40 = 0x40,
    PLAYER_STATUS_STONE = 0x80,
    PLAYER_STATUS_UNK100 = 0x100,
    PLAYER_STATUS_UNK200 = 0x200,
    PLAYER_STATUS_UNK400 = 0x400,
    PLAYER_STATUS_UNK800 = 0x800,
    PLAYER_STATUS_UNK1000 = 0x1000,
    PLAYER_STATUS_UNK2000 = 0x2000,
    PLAYER_STATUS_POISON = 0x4000,
    PLAYER_STATUS_CURSE = 0x8000,
    PLAYER_STATUS_UNK10000 = 0x10000, // possibly freezing?
    PLAYER_STATUS_UNK20000 = 0x20000,
    PLAYER_STATUS_DEAD = 0x40000, // possibly just "dead"
    PLAYER_STATUS_UNK80000 = 0x80000,
    PLAYER_STATUS_UNK100000 = 0x100000,
    PLAYER_STATUS_UNK200000 = 0x200000,
    PLAYER_STATUS_UNK400000 = 0x400000,
    PLAYER_STATUS_UNK800000 = 0x800000,
    PLAYER_STATUS_AXEARMOR = 0x1000000,
    PLAYER_STATUS_ABSORB_BLOOD = 0x2000000,
    PLAYER_STATUS_UNK4000000 = 0x4000000,
    NO_AFTERIMAGE = 0x8000000,
    PLAYER_STATUS_UNK10000000 = 0x10000000,
    PLAYER_STATUS_UNK40000000 = 0x40000000,
    PLAYER_STATUS_UNK80000000 = 0x80000000,
} PlayerStateStatus;

#define ANIMSET_OVL_FLAG 0x8000
#define ANIMSET_DRA(x) (x)
#define ANIMSET_OVL(x) ((x) | ANIMSET_OVL_FLAG)

#define PAL_OVL_FLAG 0x8000
#define PAL_DRA(x) (x)
#define PAL_OVL(x) ((x) | ANIMSET_OVL_FLAG)

#ifndef SOTN_STR
// Decorator to re-encode strings with tools/sotn_str/sotn_str.py when building
// the game. Certain strings in SOTN do not follow the ASCII encoding and each
// character is offseted by 0x20. This is only for strings that use the 8x8
// font. e.g. _S("I am a Symphony of the Night encoded string")
#define _S(x) (x)
#endif
// same as above, but it processes a single character from CPP
#define CH(x) ((x) - 0x20)

#define DEMO_KEY_LEN 3
#define DEMO_MAX_LEN 0x2000

#define FONT_W 8                 // small font size used for dialogues and menu
#define FONT_H 8                 // small font size used for dialogues and menu
#define FONT_GAP FONT_W          // gap between the beginning of two letters
#define FONT_SPACE 4             // gap for the space character
#define MENUCHAR(x) ((x) - 0x20) // 8x8 characters are ASCII offset by 0x20
#define DIAG_EOL 0xFF            // end of line
#define DIAG_EOS 0x00            // end of string

// entityId: what entity to spawn based on the Entity Set
// amount: How many entities to spawn in total
// nPerCycle: how many entities to spawn at once without waiting for tCycle
// isNonCritical: 'true' for particles, 'false' for gameplay related entities
//   false: keep searching for a free entity slot every frame to make the entity
//   true: when there are no entities available then just forgets about it
// incParamsKind: the technique used to set the self->params to the new entity
//   false: it is set from 0 to 'nPerCycle'
//   true: it is set from 0 to 'amount'
// tCycle: wait 'tCycle' frames per cycle until 'amount' of entities are made
// kind: refer to `BlueprintKind` for a list of options
// f: ???
// tDelay: how many frames to wait before starting to make the first entity
#define B_MAKE(entityId, amount, nPerCycle, isNonCritical, incParamsKind,      \
               tCycle, kind, f, tDelay)                                        \
    {entityId,                                                                 \
     (amount),                                                                 \
     ((nPerCycle) & 0x3F) | ((!!(incParamsKind)) << 6) |                       \
         ((!!(isNonCritical)) << 7),                                           \
     (tCycle),                                                                 \
     ((kind) & 15) | ((f) << 4),                                               \
     tDelay}
enum BlueprintKind {
    B_DECOR,      // cannot collide with any other entity, used for decoration
    B_WPN,        // can collide to stage items, like candles or enemies
    B_WPN_UNIQUE, // same as above, but new entity replaces the prev. one
    B_KIND_3,
    B_KIND_4,
    B_KIND_5,
    B_KIND_6,
    B_KIND_7,
    B_KIND_8,
    B_KIND_9,
    B_KIND_10,
    B_KIND_11,
    B_KIND_12,
    B_KIND_13,
    B_KIND_14,
    B_KIND_15,
};

#define SAVE_FLAG_NORMAL (0)
#define SAVE_FLAG_CLEAR (1)
#define SAVE_FLAG_REPLAY (2)

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

#if defined(VERSION_US)
#define MEMCARD_ID "BASLUS-00067DRAX00"
#elif defined(VERSION_HD)
#define MEMCARD_ID "BISLPM-86023DRAX00"
#endif

#define ICON_SLOT_NUM 32
#define SPU_VOICE_NUM 24

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
    Game_Boot,
    Game_99 = 99,
} GameState;

typedef enum {
    Engine_Init,
    Engine_Normal,
    Engine_Menu,
    Engine_3,
    Engine_5 = 5,
    Engine_10 = 10,
    Engine_Map = 20,
    Engine_0x70 = 0x70
} GameEngineStep;

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
    // Used by the ST0 prologue scroll and now loading screen
    Play_16 = 16,

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

#include "unkstruct.h"

typedef struct {
    f32 x;
    f32 y;
} Pos;

typedef struct {
    f32 posX;
    f32 posY;
} Camera;

typedef struct {
    unsigned char width;
    unsigned char height;
    unsigned short unk2;
#ifdef _MSC_VER
    unsigned char* data;
#else
    unsigned char data[0];
#endif
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
    /* 0x6 */ u16 unk6; // Current Stage ID to reload Tile GFX if you move
                        // through CD Room but change your mind and go back out.
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

#define FRAME(x, y) ((x) | ((y) << 8))
#define A_LOOP_AT(frame) {0, frame}
#define A_END {-1, 0}
#define A_JUMP_AT(anim) {-2, anim}
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

#define ANIM_FRAME_LOAD 0x8000

typedef struct Entity {
    /* 0x00 */ f32 posX;
    /* 0x04 */ f32 posY;
    /* 0x08 */ s32 velocityX;
    /* 0x0C */ s32 velocityY;
#if defined(STAGE) || defined(WEAPON) || defined(SERVANT)
    /* 0x10 */ s16 hitboxOffX;
#else // hack to match in DRA and RIC
    /* 0x10 */ u16 hitboxOffX;
#endif
    /* 0x12 */ s16 hitboxOffY;
    /* 0x14 */ u16 facingLeft;
    /* 0x16 */ u16 palette;
    /* 0x18 */ u8 drawMode;
    /* 0x19 */ u8 drawFlags;
    /* 0x1A */ s16 rotX;
    /* 0x1C */ s16 rotY;
    /* 0x1E */ s16 rotZ;
    /* 0x20 */ s16 rotPivotX;
    /* 0x22 */ s16 rotPivotY;
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
    /* 0x42 */ u16 attackElement;
    /* 0x44 */ u16 hitParams;
    /* 0x46 */ u8 hitboxWidth;
    /* 0x47 */ u8 hitboxHeight;
    /* 0x48 */ u8 hitFlags; // 1 = took hit
    /* 0x49 */ u8 nFramesInvincibility;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ AnimationFrame* anim;
    /* 0x50 */ u16 animFrameIdx;
    /* 0x52 */ s16 animFrameDuration;
    /* 0x54 */ s16 animSet;
    /* 0x56 */ s16 animCurFrame;
    /* 0x58 */ s16 stunFrames;
    /* 0x5A */ u16 unk5A;
    /* 0x5C */ struct Entity* unk5C;
    /* 0x60 */ struct Entity* unk60;
    /* 0x64 */ s32 primIndex;
    /* 0x68 */ u16 unk68; // Appears to be set for entities with parallax
    /* 0x6A */ u16 hitEffect;
    /* 0x6C */ u8 unk6C; // Salem Witch: timer to destroy its shadows.
                         // Thornweed: timer before spawning death explosion
    /* 0x6D */ u8 unk6D[11];
    /* 0x78 */ s32 unk78;
    /* 0x7C */ Ext ext;
    /* 0xB8 */ struct Entity* unkB8;
} Entity; // size = 0xBC

typedef struct {
    /* 0x00 */ u16 animSet;
    /* 0x02 */ u16 zPriority;
    /* 0x04 */ u16 unk5A; // not 5A in this struct, but goes to 5A in entity
    /* 0x06 */ u16 palette;
    /* 0x08 */ u16 drawFlags;
    /* 0x0A */ u16 drawMode;
    /* 0x0C */ u32 flags;
    /* 0x10 */ u8* animFrames;
} ObjInit; // size = 0x14

typedef struct { // only difference from above is this one uses a facingLeft
    /* 0x00 */ u16 animSet;
    /* 0x02 */ u16 zPriority;
    /* 0x04 */ u8 facingLeft;
    /* 0x05 */ u8 unk5A;
    /* 0x06 */ u16 palette;
    /* 0x08 */ u16 drawFlags;
    /* 0x0A */ u16 drawMode;
    /* 0x0C */ u32 flags;
    /* 0x10 */ u8* animFrames;
} ObjInit2; // size = 0x14

typedef struct GpuBuffer { // also called 'DB' in the PSY-Q samples
    /* 0x00000 */ struct GpuBuffer* next;    // next chained buffer
    /* 0x00004 */ DRAWENV draw;              // drawing environment
    /* 0x0005C */ DISPENV disp;              // display environment
    /* 0x00074 */ DR_ENV env[MAX_ENV_COUNT]; // packed drawing environment
    /* 0x00474 */ OT_TYPE ot[OTSIZE];        // ordering table
    /* 0x00474 */ DR_MODE drawModes[MAX_DRAW_MODES];    // draw modes
    /* 0x03C74 */ POLY_GT4 polyGT4[MAX_POLY_GT4_COUNT]; // textured quads
    /* 0x0D874 */ POLY_G4 polyG4[MAX_POLY_G4_COUNT];    // untextured quads
    /* 0x0FC74 */ POLY_GT3 polyGT3[MAX_POLY_GT3_COUNT]; // textured triangles
    /* 0x103F4 */ LINE_G2 lineG2[MAX_LINE_G2_COUNT];    // lines
    /* 0x117F4 */ SPRT_16 sprite16[MAXSPRT16];          // tile map sprites
    /* 0x13FF4 */ TILE tiles[MAX_TILE_COUNT];           // squared sprites
    /* 0x14FF4 */ SPRT sprite[MAX_SPRT_COUNT];          // dynamic-size sprites
} GpuBuffer;                                            // size=0x177F4

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

typedef enum {
    GFX_BANK_NONE,
    GFX_BANK_4BPP,
    GFX_BANK_8BPP,
    GFX_BANK_16BPP,
    GFX_BANK_COMPRESSED,
} GfxBankKind;
#define GFX_TERMINATE() ((u_long*)-1) // can't be in GfxBankKind
#define GFX_ENTRY(x, y, w, h, data)                                            \
    (u_long*)((x) | ((y) << 16)), (u_long*)((w) | ((h) << 16)), (u_long*)data
typedef struct {
    /* 0x00 */ u_long* xy;
    /* 0x04 */ u_long* wh;
    /* 0x08 */ u_long* data;
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

typedef enum EquipKind {
    EQUIP_HAND,
    EQUIP_HEAD,
    EQUIP_ARMOR,
    EQUIP_CAPE,
    EQUIP_ACCESSORY,
    NUM_EQUIP_KINDS,
} EquipKind;

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

typedef enum {
    SUBWPN_NONE,
    SUBWPN_DAGGER,
    SUBWPN_AXE,
    SUBWPN_HOLYWATER,
    SUBWPN_CROSS,
    SUBWPN_BIBLE,
    SUBWPN_STOPWATCH,
    SUBWPN_REBNDSTONE,
    SUBWPN_VIBHUTI,
    SUBWPN_AGUNEA
} SubWpnID;

typedef enum { STAT_STR, STAT_CON, STAT_INT, STAT_LCK } Stats;
typedef struct {
    s32 level;
    s32 exp;
    s32 unk8; // Possibly the number of times loaded
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

// This enum has the ids for familiar abilities which use the g_SpellDef
// table to fetch stats and modifiers for said abilities.
typedef enum {
    FAM_ABILITY_BAT_ATTACK = 15,
    FAM_ABILITY_GHOST_ATTACK = 17,
    FAM_ABILITY_GHOST_ATTACK_SOULSTEAL,
    FAM_ABILITY_SWORD_UNK19,
    FAM_ABILITY_SWORD_UNK20,
    FAM_ABILITY_DEMON_UNK21,
    FAM_ABILITY_DEMON_UNK22,
    FAM_ABILITY_DEMON_UNK24 = 24,
    FAM_ABILITY_DEMON_UNK25,
    FAM_ABILITY_DEMON_UNK26,
} FamiliarAbilityIds;

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
    /* 80097BF0 */ s32 gold;
    /* 80097BF4 */ s32 killCount;
    /* 80097BF8 */ u32 D_80097BF8;
    /* 80097BFC */ u32 subWeapon;
    /* 80097C00 */ u32 equipment[7];
    /* 80097C1C */ u32 attackHands[2]; // right hand, left hand
    /* 80097C24 */ s32 defenseEquip;
    /* 80097C28 */ u16 elementsWeakTo;
    /* 80097C2A */ u16 elementsResist;
    /* 80097C2C */ u16 elementsImmune;
    /* 80097C2E */ u16 elementsAbsorb;
    /* 80097C30 */ s32 timerHours;
    /* 80097C34 */ s32 timerMinutes;
    /* 80097C38 */ s32 timerSeconds;
    /* 80097C3C */ s32 timerFrames;
    /* 80097C40 */ u32 D_80097C40; // reused for Maria subweapon
    /* 80097C44 */ FamiliarStats statsFamiliars[NUM_FAMILIARS];
} PlayerStatus; /* size=0x334 */

typedef struct {
    /* 0x00, 8003C9A8 */ s32 cursorMain;
    /* 0x04, 8003C9AC */ s32 cursorRelic;
    /* 0x08, 8003C9B0 */ s32 cursorEquip;
    /* 0x0C, 8003C9B4 */ s32 cursorEquipType[NUM_EQUIP_KINDS];
    /* 0x20, 8003C9C8 */ s32 scrollEquipType[NUM_EQUIP_KINDS];
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
    /* 0x00 */ u8* gfxPage;
    /* 0x04 */ u8* gfxIndex;
    /* 0x08 */ u8* clut;
    /* 0x0C */ u8* collision;
} TileDefinition; // size = 0x10

#define LAYOUT_RECT_PARAMS_HIDEONMAP 0x10
#define LAYOUT_RECT_PARAMS_UNKNOWN_20 0x20
#define LAYOUT_RECT_PARAMS_UNKNOWN_40 0x40

typedef struct {
    /* 0x00 */ u32 left : 6;
    /* 0x04 */ u32 top : 6;
    /* 0x08 */ u32 right : 6;
    /* 0x0C */ u32 bottom : 6;
    /* 0x10 */ u8 params : 8;
} LayoutRect; // size = 0x4

typedef struct {
    /* 0x00 */ u16* layout;
    /* 0x04 */ TileDefinition* tileDef;
    /* 0x08 */ LayoutRect rect;
    /* 0x0C */ u16 zPriority;
    /* 0x0E */ u16 flags;
} LayerDef; // size = 0x10

typedef struct {
    LayerDef* fg;
    LayerDef* bg;
} RoomDef;

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 width;
    /* 0x06 */ s16 height;
    /* 0x08 */ s16 clut;
    /* 0x0A */ s16 tpage;
    /* 0x0C */ s16 texLeft;
    /* 0x0E */ s16 texTop;
    /* 0x10 */ s16 texRight;
    /* 0x12 */ s16 texBottom;
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

/*
 * In the PSX version of the game, stage objects begin with this
 * header (or `AbbreviatedOverlay`) at 0x0. This describes the
 * primary interface for the game engine to interact with stages.
 */
typedef struct {
    /* 8003C774 */ void (*Update)(void);
    /* 8003C778 */ void (*HitDetection)(void);
    /* 8003C77C */ void (*UpdateRoomPosition)(void);
    /* 8003C780 */ void (*InitRoomEntities)(s32 layoutId);
    /* 8003C784 */ RoomHeader* rooms;
    /* 8003C788 */ SpriteParts** spriteBanks;
    /* 8003C78C */ u_long** cluts;
    /* 8003C790 */ void* objLayoutHorizontal;
    /* 8003C794 */ RoomDef* tileLayers;
    /* 8003C798 */ GfxBank** gfxBanks;
    /* 8003C79C */ void (*UpdateStageEntities)(void);
    /* 8003C7A0 */ u8** unk2c; // sprite bank 1
    /* 8003C7A4 */ u8** unk30; // sprite bank 2
    /* 8003C7A8 */ s32* unk34;
    /* 8003C7AC */ s32* unk38;
    /* 8003C7B0 */ void (*StageEndCutScene)(void);
} Overlay;

/*
 * Several stages start their sprite bank array immeidately
 * after `UpdateStageEntities` instead of including the
 * trailing 5 pointers found in `Overlay`. `DRA` seems to
 * know which stages have valid data in those fields and
 * which don't.
 */
typedef struct {
    /* 8003C774 */ void (*Update)(void);
    /* 8003C778 */ void (*HitDetection)(void);
    /* 8003C77C */ void (*UpdateRoomPosition)(void);
    /* 8003C780 */ void (*InitRoomEntities)(s32 layoutId);
    /* 8003C784 */ RoomHeader* rooms;
    /* 8003C788 */ SpriteParts** spriteBanks;
    /* 8003C78C */ u_long** cluts;
    /* 8003C790 */ void* objLayoutHorizontal;
    /* 8003C794 */ RoomDef* tileLayers;
    /* 8003C798 */ GfxBank** gfxBanks;
    /* 8003C79C */ void (*UpdateStageEntities)(void);
} AbbreviatedOverlay;

typedef enum {
    EFFECT_NONE = 0,
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
    EFFECT_NOTHROUGH_PLUS = EFFECT_SOLID | EFFECT_UNK_0002 | EFFECT_QUICKSAND,
    // Should be renamed once we know what 8000 and 4000 are
    EFFECT_UNK_C000 = EFFECT_UNK_8000 | EFFECT_UNK_4000
} ColliderEffectFlags;

typedef struct Collider {
    /* 0x00 */ u32 effects;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14; // Left edge of queried tile collision
    /* 0x18 */ s32 unk18; // Top edge of queried tile collision
    /* 0x1C */ s32 unk1C; // Right edge of queried tile collision
    /* 0x20 */ s32 unk20; // Bottom edge of queried tile collision
} Collider;               /* size=0x24 */

typedef struct XaMusicConfig {
    u32 cd_addr;
    s32 unk228;
    u8 filter_file;
    u8 filter_channel_id;
    u8 volume;
    u8 unk22f;
    u8 unk230;
    u8 pad[3];
} XaMusicConfig;

typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ s16 hitPoints;
    /* 0x06 */ s16 attack;
    /* 0x08 */ u16 attackElement;
    /* 0x0A */ s16 defense;
    /* 0x0C */ u16 hitboxState;
    /* 0x0E */ u16 weaknesses;
    /* 0x10 */ u16 strengths;
    /* 0x12 */ u16 immunes;
    /* 0x14 */ u16 absorbs;
    /* 0x16 */ u16 level;
    /* 0x18 */ u16 exp;
    /* 0x1A */ u16 rareItemId;
    /* 0x1C */ u16 uncommonItemId;
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
    /* 0x06 */ u8 chainLimit; // how many instances of subwpn can coexist
    /* 0x07 */ u8 nFramesInvincibility;
    /* 0x08 */ u16 stunFrames;
    /* 0x0A */ u8 anim;
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
    /* 10 */ u16 weakToElements;
    /* 12 */ u16 resistElements;
    /* 14 */ u16 immuneElements;
    /* 16 */ u16 absorbElements;
    /* 18 */ u16 icon;
    /* 1A */ u16 iconPalette;
    /* 1C */ u16 equipType;
    /* 1E */ u16 unk1E;
} Accessory; /* size=0x20 */

typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ const char* combo;
    /* 0x08 */ const char* description;
    /* 0x0C */ u8 mpUsage;
    /* 0x0D */ s8 nFramesInvincibility;
    /* 0x0E */ s16 stunFrames;
    /* 0x10 */ s16 hitboxState;
    /* 0x12 */ s16 hitEffect;
    /* 0x14 */ s16 entityRoomIndex;
    /* 0x16 */ u16 attackElement;
    /* 0x18 */ s16 attack;
    /* 0x1A */ s16 unk1A;
} SpellDef;

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
    /* 0x00 */ u8* scriptCur;         // ptr to dialogue next character
    /* 0x04 */ s16 startX;            // starting x coord
    /* 0x06 */ s16 nextLineY;         // next line y coord
    /* 0x08 */ s16 startY;            // starting y coord
    /* 0x0A */ s16 nextCharX;         // next char x coord
    /* 0x0C */ s16 nextLineX;         // next line x coord
    /* 0x0E */ s16 nextCharY;         // next char y coord
    /* 0x10 */ s16 portraitAnimTimer; // portrait animation timer
    /* 0x12 */ u16 unk12;             // unknown
    /* 0x14 */ u16 clutIndex;         // CLUT index
    /* 0x16 */ u8 nextCharTimer;      // timer to next character
    /* 0x17 */ u8 unk17;              // unknown
// Of course, offsets beyond here won't be right in ST0_WEIRD_DIALOGUE.
#if defined(VERSION_PSP)
    /* 0x18 */ Primitive* prim[5]; // for dialogue graphics rendering
#else
    /* 0x18 */ Primitive* prim[6]; // for dialogue graphics rendering
#endif
    /* 0x30 */ s32 primIndex[3]; // primIndices: unk, actorName, unk
    /* 0x3C */ u16 unk3C;        // maybe it is a begin flag?
    /* 0x3E */ u16 timer;        // global timer
    /* 0x40 */ u8* scriptEnd;    // pointer to the end of the script
} Dialogue;                      // size = 0x44

// Used for the damageKind of DamageParam
typedef enum {
    DAMAGEKIND_0,
    DAMAGEKIND_1,
    DAMAGEKIND_2,
    DAMAGEKIND_3,
    DAMAGEKIND_4,
    DAMAGEKIND_5,
    DAMAGEKIND_6,
    DAMAGEKIND_7,
    DAMAGEKIND_8,
    DAMAGEKIND_9,
    DAMAGEKIND_10,
    DAMAGEKIND_11,
    DAMAGEKIND_12,
    DAMAGEKIND_13,
    DAMAGEKIND_14,
    DAMAGEKIND_15,
    DAMAGEKIND_16,
    DAMAGEKIND_17,
    DAMAGEKIND_18,
} DamageKind;

typedef struct {
    u32 effects;    // Curse, poison, fire, ice, etc.
    u32 damageKind; // informed by "dam_kind:%04x\n"
    s32 damageTaken;
    u32 unkC;
} DamageParam;

typedef struct {
    /* 8003C774 */ Overlay o;
    /* 8003C7B4 */ void (*FreePrimitives)(s32);
    /* 8003C7B8 */ s16 (*AllocPrimitives)(PrimitiveType type, s32 count);
    /* 8003C7BC */ void (*CheckCollision)(s32 x, s32 y, Collider* res, s32 unk);
    /* 8003C7C0 */ void (*func_80102CD8)(s32 arg0);
    /* 8003C7C4 */ void (*UpdateAnim)(
        FrameProperty* frameProps, AnimationFrame** anims);
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
    // Note type of facingLeft is different from in the C for this function.
    // Needs s16 to match the code for this, but callers treat it as s32.
    /* 8003C810 */ s16 (*func_80118B18)(
        Entity* ent1, Entity* ent2, s32 facingLeft);
    /* 8003C814 */ s32 (*UpdateUnarmedAnim)(s8* frameProps, u16** frames);
    /* 8003C818 */ void (*PlayAnimation)(s8*, AnimationFrame** frames);
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
    /* 8003C84C */ void (*AddToInventory)(u32 id, EquipKind kind);
    /* 8003C850 */ RelicOrb* relicDefs;
    /* 8003C854 */ void (*InitStatsAndGear)(bool debugMode);
    /* 8003C858 */ s32 (*PlaySfxVolPan)(s32 sfxId, s32 sfxVol, s32 sfxPan);
    /* 8003C85C */ s32 (*SetVolumeCommand22_23)(s16 vol, s16 distance);
    /* 8003C860 */ void (*func_800F53A4)(void);
    /* 8003C864 */ u32 (*CheckEquipmentItemCount)(u32 itemId, u32 equipType);
    /* 8003C868 */ void (*GetPlayerSensor)(Collider* col);
    /* 8003C86C */ void (*func_800F1FC4)(s32 arg0);
    /* 8003C870 */ void (*func_800F2288)(s32 arg0);
    /* 8003C874 */ void (*GetServantStats)(
        Entity* entity, s32 spellId, s32 arg2, FamiliarStats* out);
    /* 8003C878 */ s32 (*func_800FF460)(s32 arg0);
    /* 8003C87C */ s32 (*func_800FF494)(EnemyDef* arg0);
    /* 8003C880 */ bool (*CdSoundCommandQueueEmpty)(void);
    /* 8003C884 */ bool (*func_80133950)(void);
    /* 8003C888 */ bool (*func_800F27F4)(s32 arg0);
    /* 8003C88C */ s32 (*GetStatBuffTimer)(s32 arg0);
    /* 8003C890 */ s32 (*func_800FD664)(s32 arg0);
    /* 8003C894 */ s32 (*CalcPlayerDamage)(DamageParam* damageParam);
    /* 8003C898 */ void (*LearnSpell)(s32 spellId);
    /* 8003C89C */ void (*DebugInputWait)(const char* str);
    /* 8003C8A0 */ void* unused12C;
    // this matches on both versions but doing this to show the difference
#if defined(VERSION_PSP)
    /* 8003C8A4 */ s32 (*CalcPlayerDamageAgain)(DamageParam* damageParam);
    /* 8003C8A8 */ u16* (*func_ptr_91CF86C)(u32 arg0, u16 kind);
    /* 8003C8AC */ u16 (*func_ptr_91CF870)(char*, u8* ch);
#else
    /* 8003C8A4 */ void* unused130;
    /* 8003C8A8 */ void* unused134;
    /* 8003C8AC */ void* unused138;
#endif
    /* 8003C8B4 */ void* unused13C;
} GameApi; /* size=0x140 */

typedef struct {
    void (*D_8013C000)(void);
    void (*D_8013C004)(u16 params);
    void (*D_8013C008)(void);
    void (*GetPlayerSensor)(Collider* col);
} PlayerOvl;
extern PlayerOvl g_PlOvl;
extern u8** g_PlOvlAluBatSpritesheet[1];
extern u8* g_PlOvlSpritesheet[];

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
extern void (*g_api_PlayAnimation)(s8*, AnimationFrame** frames);
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
extern void (*g_api_AddToInventory)(u16 id, EquipKind kind);
extern RelicOrb* g_api_relicDefs;
extern s32 (*g_api_PlaySfxVolPan)(s32 sfxId, s32 sfxVol, s32 sfxPan);
extern s32 (*g_api_SetVolumeCommand22_23)(s16 vol, s16 distance);
extern void (*g_api_func_800F53A4)(void);
extern u32 (*g_api_CheckEquipmentItemCount)(u32 itemId, u32 equipType);
extern void (*g_api_GetPlayerSensor)(Collider* col);
extern void (*g_api_func_800F1FC4)(s32 arg0);
extern void (*g_api_func_800F2288)(s32 arg0);
extern void (*g_api_GetServantStats)(
    Entity* entity, s32 spellId, s32 arg2, FamiliarStats* out);
extern s32 (*g_api_func_800FF460)(s32 arg0);
extern s32 (*g_api_func_800FF494)(EnemyDef* arg0);
extern bool (*g_api_CdSoundCommandQueueEmpty)(void);
extern bool (*g_api_func_80133950)(void);
extern bool (*g_api_func_800F27F4)(s32 arg0);
extern s32 (*g_api_GetStatBuffTimer)(s32 arg0);
extern s32 (*g_api_func_800FD664)(s32 arg0);
extern s32 (*g_api_CalcPlayerDamage)(DamageParam* arg0);
extern void (*g_api_LearnSpell)(s32 spellId);
extern void (*g_api_func_800E2438)(const char* str);
/***************************/

typedef struct {
    /* 0x00 */ u16** frames;   // all the animation frames
    /* 0x04 */ s8* frameProps; // hitboxes
    /* 0x08 */ u16 palette;    // palette modifier
    /* 0x0A */ u16 soundId;    // which sound effect to trigger
    /* 0x0C */ u8 frameStart;  // when the animation starts
    /* 0x0D */ u8 soundFrame;  // when the sound effect is triggered
    /* 0x0E */ s16 unused;     // reserved, always 0
} WeaponAnimation;             // size = 0x10

#define TILE_SIZE 16
#define TILE_MASK 0x0F
#define N_HORIZ_TILES 17
#define N_VERTI_TILES 16

#define LAYER_SHOW 1
#define LAYER_TPAGE_ID (0x20 | 0x40)
#define LAYER_SEMI_TRANS 0x80
#define LAYER_TPAGE_ALT 0x100
#define LAYER_CLUT_ALT 0x200
#define LAYER_WRAP_BG 0x1000

typedef struct {
    /* 800730D8 0x00 */ u16* layout;
    /* 800730DC 0x04 */ TileDefinition* tileDef;
    /* 800730E0 0x08 */ f32 scrollX;
    /* 800730E4 0x0C */ f32 scrollY;
    /* 800730E8 0x10 */ u32 unused10;
    /* 800730EC 0x14 */ u32 unused14;
    /* 800730F0 0x18 */ u32 order;
    /* 800730F4 0x1C */ u32 flags;
    /* 800730F8 0x20 */ u32 w;
    /* 800730FC 0x24 */ u32 h;
    /* 80073100 0x28 */ u32 hideTimer;
    /* 80073104 0x2C */ u32 scrollKind;
} BgLayer; /* size=0x30 */

typedef struct {
    /* 80073084 */ u16* fg;
    /* 80073088 */ TileDefinition* tileDef;
    /* 8007308C */ f32 scrollX;
    /* 80073090 */ f32 scrollY;
    /* 80073094 */ s32 unused10;
    /* 80073098 */ s32 unused14;
    /* 8007309C */ s32 order;
    /* 800730A0 */ u32 flags;
    /* 800730A4 */ s32 hSize;
    /* 800730A8 */ s32 vSize;
    /* 800730AC */ u32 hideTimer;
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
} Tilemap;

typedef struct {
    /* D_8003C708 */ u16 flags;
    /* D_8003C70A */ u16 unk2;
    /* D_8003C70C */ u16 unk4;
    /* D_8003C70E */ s16 zPriority;
} FgLayer; /* size=0x8 */

typedef struct {
    /* D_8003C708 */ u32 flags;
    /* D_8003C70C */ u32 zPriority;
} FgLayer32;

enum AluTimers {
    ALU_T_POISON,
    ALU_T_CURSE,
    ALU_T_HITEFFECT,
    ALU_T_3,
    ALU_T_4,
    ALU_T_5,
    ALU_T_6,
    ALU_T_7,
    ALU_T_8,
    ALU_T_9,
    ALU_T_10,
    ALU_T_DARKMETAMORPH,
    ALU_T_12,
    ALU_T_INVINCIBLE,
    ALU_T_INVINCIBLE_CONSUMABLES,
    ALU_T_15,
};

// A tall player needs to have multiple sensors to detect collision at the
// center of the body.
#define NUM_HORIZONTAL_SENSORS 4
#define NUM_VERTICAL_SENSORS 7

typedef struct {
    /* 80072BD0 */ Collider colFloor[NUM_HORIZONTAL_SENSORS];
    /* 80072C60 */ Collider colCeiling[NUM_HORIZONTAL_SENSORS];
    /* 80072CF0 */ Collider colWall[NUM_VERTICAL_SENSORS * 2];
    /* 80072EE8 */ s32 padPressed;
    /* 80072EEC */ s32 padTapped;
    /* 80072EF0 */ s32 padHeld;
    /* 80072EF4 */ u32 padSim; // simulate input to force player actions
    /* 80072EF8 */ s32 D_80072EF8;
    /* 80072EFC */ s32 D_80072EFC; // stun timer
    /* 80072F00 */ s16 timers[16]; /// Indexed with AluTimers

    // 0x01: touching the ground
    // 0x02: touching the ceiling
    // 0x04: touching the right wall
    // 0x08: touching the left wall
    // 0x20: in-air or near the edge
    // 0x0800: touching the ceiling slope
    // 0x1000: standing on a slightly ascending or descending slope
    // 0x4000: standing on a raising slope
    // 0x8000: standing on any slope
    /* 80072F20 */ s32 pl_vram_flag;

    /* 80072F24 */ s32 unk04; // copy of the previous field
    /* 80072F28 */ s32 unk08;
    /* 80072F2C */ PlayerStateStatus status;
    /* 80072F30 */ s32 unk10;
    /* 80072F34 */ u32 unk14;
    // unk18 & 0xFA00 give elemental status of damage received
    /* 80072F38 */ s32 unk18;
    /* 80072F3C */ s32 unk1C;
    /* 80072F40 */ s32 unk20;
    /* 80072F44 */ s32 unk24;
    /* 80072F48 */ s32 unk28;
    /* 80072F4C */ s32 unk2C;
    /* 80072F50 */ s32 unk30;
    /* 80072F54 */ s32 unk34;
    /* 80072F58 */ s32 unk38;
    /* 80072F5C */ s32 unk3C;
    /* 80072F60 */ u16 unk40;
    /* 80072F62 */ u16 pl_high_jump_timer;
    /* 80072F64 */ u16 unk44;
    /* 80072F66 */ u16 unk46;
    /* 80072F68 */ u16 unk48;
    /* 80072F6A */ s16 unk4A;
    /* 80072F6C */ u16 unk4C;
    /* 80072F6E */ u16 unk4E;
    /* 80072F70 */ u16 prev_step;
    /* 80072F72 */ u16 prev_step_s;
    /* 80072F74 */ u16 unk54;
    /* 80072F76 */ u16 unk56;
    /* 80072F78 */ u16 unk58;
    /* 80072F7A */ u16 damageTaken;
    /* 80072F7C */ u16 unk5C; // ALU: hellfire spell state, RIC: isPrologue
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

// Used to track the state of moves the player does with a sequence of buttons.
// This includes spells, some of Richter's moves, etc.
typedef struct {
    s16 buttonsCorrect;
    s16 timer;
} ButtonComboState;

extern s32 D_8003925C;
extern s32 g_IsTimeAttackUnlocked;

extern s32 D_8003C0EC[4];
extern s32 D_8003C0F8;
extern s32 D_8003C100;
extern u16 g_ClutIds[]; // array of palette VRAM offsets
extern s32 g_CutsceneHasControl;
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
extern bool g_PauseAllowed;
extern u32 g_GameTimer; // Increases when unpaused
extern bool D_8003C908;
extern s32 g_EquippedWeaponIds[2];
extern u32 g_Timer; // Increases continuously
extern s32 g_MapCursorTimer;
/* 0x8003C9A0 */ extern s32 g_PlayableCharacter;
/* 0x8003C9A4 */ extern u32 g_GameEngineStep;
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
extern Point32 D_8006C384;
extern Point32 D_8006C38C;
extern u32 g_CdStep; // CdStep
extern s32 D_8006C3AC;
extern s32 g_backbufferX;
extern s32 g_backbufferY;
extern s32 g_IsUsingCd;
extern Entity* g_CurrentEntity;
extern Unkstruct_8006C3C4 D_8006C3C4[32];
extern s32 g_Servant; // Currently selected familiar in the menu

#define CLUT_INDEX_SERVANT 0x1400
#define CLUT_INDEX_SERVANT_OVERWRITE 0x1430
extern u16 g_Clut[0x3000];
extern u16 D_8006EBCC[0x1000]; // part of g_Clut
extern u16 D_8006EBE0;         // part of g_Clut
extern s16 D_800705CC[];       // part of g_Clut
extern u32 D_80070BCC;         // part of g_Clut

extern PlayerState g_Player;
// the following are most likely part of g_Player
extern Entity* D_psp_091CF3A0;
extern s32 D_psp_091CF3A4; // maybe not s32 but a pointer?
extern void (*D_psp_091CF3A8)(Entity*);
extern s32 D_psp_091CF3AC; // maybe not s32 but a pointer?
extern u16 D_psp_091CF3DC;

extern GfxLoad g_GfxLoad[0x10];
extern u32 g_GameStep;
extern s32 g_ServantLoaded; // Currently loaded servant in-memory
extern Event g_EvSwCardEnd; // 80073068
extern Event g_EvSwCardErr; // 8007306C
extern Event g_EvSwCardTmo; // 80073070
extern s32 g_PrevScrollX;
extern Event g_EvSwCardNew; // 80073078
extern s32 g_PrevScrollY;
extern s32 D_80073080;
extern Tilemap g_Tilemap;
// this was previously g_Tilemap.bg, but func_801BD8F0 showed that it is a
// separate symbol.
extern BgLayer g_BgLayers[MAX_BG_LAYER_COUNT]; /* 800730D8 */

#define PLAYER_CHARACTER 0
#define TOTAL_ENTITY_COUNT 256
#define STAGE_ENTITY_START 64
#define MaxEntityCount 32
#define PLAYER g_Entities[PLAYER_CHARACTER]
typedef enum {
    UNK_ENTITY_1 = 1,
    UNK_ENTITY_2,
    UNK_ENTITY_3,
    UNK_ENTITY_4,
    UNK_ENTITY_5,
    UNK_ENTITY_6,
    UNK_ENTITY_7,
    UNK_ENTITY_8,
    E_WEAPON = 0x10,
    UNK_ENTITY_11 = 0x11, // related to wolf
    UNK_ENTITY_12 = 0x12, // related to wolf?
    UNK_ENTITY_13 = 0x13,
    UNK_ENTITY_20 = 0x20,
    UNK_ENTITY_51 = 0x51, // SubWeapons container falling liquid
    UNK_ENTITY_100 = 0x100
} EntityTypes;
extern Entity g_Entities[TOTAL_ENTITY_COUNT];

extern s32 g_entityDestroyed[18];
extern Event g_EvHwCardEnd;
extern Event g_EvHwCardErr;
extern Event g_EvHwCardTmo;
extern Event g_EvHwCardNew;
extern u8 g_Pix[4][128 * 128 / 2];
extern Primitive g_PrimBuf[MAX_PRIM_COUNT];
extern s32 g_PlayerX;
extern s32 g_PlayerY;
extern u32 g_randomNext;
extern s32 D_80096ED8[];
extern s8 D_80097B98;
extern s8 D_80097B99;
extern s32 D_800973EC; // flag to check if the menu is shown
extern unkGraphicsStruct g_unkGraphicsStruct;
extern s32 D_80097448[]; // underwater physics. 7448 and 744C. Could be struct.
extern s32 D_80097450;
extern Pos D_80097488;
extern Pad g_pads[PAD_COUNT];
extern Stages g_StageId;
extern s32 D_800974A4; // map open
extern DR_ENV D_800974AC[16];
extern s32 g_UseDisk;
extern s32 D_800978B4;
extern s32 D_800978C4;
extern u32 g_MenuStep;
extern char D_80097902[];
extern s32 D_80097904;
extern s32 g_ScrollDeltaX;
extern s32 g_ScrollDeltaY;
extern s32 D_80097910;
extern DemoMode g_DemoMode;
extern s32 g_LoadOvlIdx; // 0x80097918
extern s32 D_8009791C;
extern s32 D_80097920;
extern s32 D_80097924;
extern s32 D_80097928;
extern GpuUsage g_GpuUsage;
extern PlayerStatus g_Status;
extern s32 D_80097C98;
extern s32 subWeapon; // g_SubweaponId
extern u8 g_SaveName[12] ALIGNED4;
extern u32 D_80097C40[];
extern PlayerDraw g_PlayerDraw[0x10];
extern s32 D_800987B4;
extern s32 D_800987C8;
extern s32 g_DebugPlayer;
extern s32 D_80098894;

// exclusive PSP content
typedef enum {
    LANG_JP,
    LANG_EN,
    LANG_FR,
    LANG_SP,
    LANG_GE,
    LANG_IT,
} Language;
u8* GetLangAt(s32 idx, u8* en, u8* fr, u8* sp, u8* ge, u8* it);
u8* GetLang(u8* en, u8* fr, u8* sp, u8* ge, u8* it);

#endif
