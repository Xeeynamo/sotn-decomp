#ifndef GAME_H
#define GAME_H

#include "common.h"

#include "animset.h"
#include "castle.h"
#include "clut.h"
#include "collider.h"
#include "disk.h"
#include "drawmode.h"
#include "entity.h"
#include "gamepad.h"
#include "gamesettings.h"
#include "graphics.h"
#include "familiar.h"
#include "item.h"
#include "layer.h"
#include "log.h"
#include "memcard.h"
#include "menunavigation.h"
#include "palette.h"
#include "player.h"
#include "primitive.h"
#include "relic.h"
#include "servant.h"
#include "spell.h"
#include "sprite.h"
#include "timeattack.h"
#include "ui.h"
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

#define SPAD(x) ((s32*)SP(x * sizeof(s32)))

typedef struct {
    /* 0x00 */ SVECTOR* v0;
    /* 0x04 */ SVECTOR* v1;
    /* 0x08 */ SVECTOR* v2;
    /* 0x0C */ SVECTOR* v3;
} SVEC4; // size = 0x10

#define DISP_ALL_H 240
#define DISP_STAGE_W 256
#define DISP_STAGE_H DISP_ALL_H
#define DISP_MENU_W 384
#define DISP_MENU_H DISP_ALL_H
#define DISP_TITLE_W 512
#define DISP_TITLE_H DISP_ALL_H
// Width in pixel of how wide is the horizontal camera during normal game play
#define STAGE_WIDTH 256

#define MAX_BG_LAYER_COUNT 16

#define RENDERFLAGS_NOSHADOW 2
#define MAX_GOLD 999999
#define HEART_VESSEL_INCREASE 5
#define HEART_VESSEL_RICHTER 30
#define LIFE_VESSEL_INCREASE 5
#define FALL_GRAVITY 0x4000
#define FALL_TERMINAL_VELOCITY 0x60000

#define STAGE_ENTITY_START 64

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
#define SPRITESHEET_PTR 0x8013C020 // g_PlOvlSpritesheet
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

#ifndef SOTN_STR
// Decorator to re-encode strings with tools/sotn_str/sotn_str.py when building
// the game. Certain strings in SOTN do not follow the ASCII encoding and each
// character is offseted by 0x20. This is only for strings that use the 8x8
// font. e.g. _S("I am a Symphony of the Night encoded string")
#define _S(x) (x)
#endif

#define DEMO_KEY_LEN 3
#define DEMO_MAX_LEN 0x2000

#define FONT_W 8                 // small font size used for dialogues and menu
#define FONT_H 8                 // small font size used for dialogues and menu
#define FONT_GAP FONT_W          // gap between the beginning of two letters
#define FONT_SPACE 4             // gap for the space character
#define MENUCHAR(x) ((x) - 0x20) // 8x8 characters are ASCII offset by 0x20
#define DIAG_EOL 0xFF            // end of line
#define DIAG_EOS 0x00            // end of string

#define SAVE_FLAG_NORMAL (0)
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
    Game_Boot,
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
    s8 unk0; // Entity::unk10
    s8 unk2; // Entity::unk12
    s8 hitboxWidth;
    s8 hitboxHeight;
} FrameProperty;

typedef struct {
    /* 0x00 */ u16 animSet;
    /* 0x02 */ u16 zPriority;
    /* 0x04 */ Multi16 unk4;
    /* 0x06 */ u16 palette;
    /* 0x08 */ u16 drawFlags;
    /* 0x0A */ u16 drawMode;
    /* 0x0C */ u32 unkC;
    /* 0x10 */ u8* unk10;
} ObjInit2; // size = 0x14

typedef struct {
    /* 0x00 */ u32 left : 6;
    /* 0x04 */ u32 top : 6;
    /* 0x08 */ u32 right : 6;
    /* 0x0C */ u32 bottom : 6;
    /* 0x10 */ u8 params : 8;
} LayoutRect; // size = 0x14

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
 /* size=0x24 */

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
    /* 0x06 */ u8 unk6;
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
    u32 effects; // Curse, poison, etc; needs an enum.
    u32 damageKind;
    s32 damageTaken;
    s32 unkC;
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
    /* 8003C84C */ void (*AddToInventory)(u16 id, EquipKind kind);
    /* 8003C850 */ RelicOrb* relicDefs;
    /* 8003C854 */ void (*InitStatsAndGear)(bool debugMode);
    /* 8003C858 */ s32 (*func_80134714)(s32 arg0, s32 arg1, s32 arg2);
    /* 8003C85C */ s32 (*func_80134678)(s16 arg0, u16 arg1);
    /* 8003C860 */ void (*func_800F53A4)(void);
    /* 8003C864 */ u32 (*CheckEquipmentItemCount)(u32 itemId, u32 equipType);
    /* 8003C868 */ void (*func_8010BF64)(Unkstruct_8010BF64* arg0);
    /* 8003C86C */ void (*func_800F1FC4)(s32 arg0);
    /* 8003C870 */ void (*func_800F2288)(s32 arg0);
    /* 8003C874 */ void (*func_8011A3AC)(
        Entity* entity, s32 spellId, s32 arg2, FamiliarStats* out);
    /* 8003C878 */ s32 (*func_800FF460)(s32 arg0);
    /* 8003C87C */ s32 (*func_800FF494)(EnemyDef* arg0);
    /* 8003C880 */ bool (*CdSoundCommandQueueEmpty)(void);
    /* 8003C884 */ bool (*func_80133950)(void);
    /* 8003C888 */ bool (*func_800F27F4)(s32 arg0);
    /* 8003C88C */ s32 (*func_800FF110)(s32 arg0);
    /* 8003C890 */ s32 (*func_800FD664)(s32 arg0);
    /* 8003C894 */ s32 (*func_800FD5BC)(DamageParam* arg0);
    /* 8003C898 */ void (*LearnSpell)(s32 spellId);
    /* 8003C89C */ void (*DebugInputWait)(const char* str);
    /* 8003C8A0 */ void* unused12C;
    /* 8003C8A4 */ void* unused130;
    // this matches on both versions but doing this to show the difference
#if defined(VERSION_PSP)
    /* 8003C8A8 */ u16* (*func_ptr_91CF86C)(u32 arg0, u16 kind);
    /* 8003C8AC */ u16 (*func_ptr_91CF870)(char*, u8* ch);
#else
    /* 8003C8A8 */ void* unused134;
    /* 8003C8AC */ void* unused138;
#endif
    /* 8003C8B4 */ void* unused13C;
} GameApi; /* size=0x140 */

typedef struct {
    void (*D_8013C000)(void);
    void (*D_8013C004)(void);
    void (*D_8013C008)(void);
    void (*D_8013C00C)(void);
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
extern s32 (*g_api_func_80134714)(s32 arg0, s32 arg1, s32 arg2);
extern s32 (*g_api_func_80134678)(s16 arg0, u16 arg1);
extern void (*g_api_func_800F53A4)(void);
extern u32 (*g_api_CheckEquipmentItemCount)(u32 itemId, u32 equipType);
extern void (*g_api_func_8010BF64)(Unkstruct_8010BF64* arg0);
extern void (*g_api_func_800F1FC4)(s32 arg0);
extern void (*g_api_func_800F2288)(s32 arg0);
extern void (*g_api_func_8011A3AC)(
    Entity* entity, s32 spellId, s32 arg2, FamiliarStats* out);
extern s32 (*g_api_func_800FF460)(s32 arg0);
extern s32 (*g_api_func_800FF494)(EnemyDef* arg0);
extern bool (*g_api_CdSoundCommandQueueEmpty)(void);
extern bool (*g_api_func_80133950)(void);
extern bool (*g_api_func_800F27F4)(s32 arg0);
extern s32 (*g_api_func_800FF110)(s32 arg0);
extern s32 (*g_api_func_800FD664)(s32 arg0);
extern s32 (*g_api_func_800FD5BC)(DamageParam* arg0);
extern void (*g_api_LearnSpell)(s32 spellId);
extern void (*g_api_func_800E2438)(const char* str);
/***************************/

extern s32 D_8003925C;

extern s32 D_8003C0EC[4];
extern s32 D_8003C0F8;
extern s32 D_8003C100;
extern s32 D_8003C704;
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
extern s32 g_MapCursorTimer;
extern const char aBaslus00067dra[19];
extern s32 g_LoadFile;
extern s32 D_8006BB00;
extern u8 g_CastleMap[0x800];
extern s32 D_8006C374;
extern s32 D_8006C378;
extern Point32 D_8006C384;
extern Point32 D_8006C38C;
extern s32 D_8006C3AC;
extern s32 g_backbufferX;
extern s32 g_backbufferY;
extern Unkstruct_8006C3C4 D_8006C3C4[32];

extern u32 g_GameStep;
extern Event g_EvSwCardEnd; // 80073068
extern Event g_EvSwCardErr; // 8007306C
extern Event g_EvSwCardTmo; // 80073070
extern s32 g_PrevScrollX;
extern Event g_EvSwCardNew; // 80073078
extern s32 g_PrevScrollY;
extern s32 D_80073080;
extern Event g_EvHwCardEnd;
extern Event g_EvHwCardErr;
extern Event g_EvHwCardTmo;
extern Event g_EvHwCardNew;
extern u8 g_Pix[4][128 * 128 / 2];
extern u32 g_randomNext;
extern s32 D_80096ED8[];
extern s8 D_80097B98;
extern s8 D_80097B99;
extern unkGraphicsStruct g_unkGraphicsStruct;
extern s32 D_80097448[]; // underwater physics. 7448 and 744C. Could be struct.
extern s32 D_80097450;
extern Pos D_80097488;
extern Stages g_StageId;
extern s32 D_800974A4; // map open
extern DR_ENV D_800974AC[16];
extern s32 D_800978B4;
extern s32 D_800978C4;
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
extern s32 D_80097C98;
extern u32 D_80097C40[];
extern s32 D_800987B4;
extern s32 D_800987C8;
extern s32 D_80098894;

#endif
