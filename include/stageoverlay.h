#ifndef STAGEOVERLAY_H
#define STAGEOVERLAY_H

#include "overlay.h"
#include "palette.h"
#include "stage.h"
#include "sprite.h"
#include "types.h"
#include "graphics.h"

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


#endif // STAGE_OVERLAY_H
