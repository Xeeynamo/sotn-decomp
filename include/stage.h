#ifndef STAGE_H
#define STAGE_H
#define STAGE 0xCC

#include "common.h"
#include "types.h"
#include "items.h"
#include "layer.h"
#include "objects.h"
#include "sfx.h"
#include "ui.h"

typedef struct {
    /* 0x0 */ u16 posX;
    /* 0x2 */ u16 posY;
    /* 0x4 */ u16 entityId;
    /* 0x6 */ u16 entityRoomIndex;
    /* 0x8 */ u16 params;
} LayoutEntity; // size = 0xA

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

typedef struct {
    u16* layout;
    TileDefinition* tileDef;
    u32 params;
    u16 zPriority;
    u8 unkE;
    u8 unkF;
} MyLayer;

typedef struct {
    MyLayer* fg;
    MyLayer* bg;
} MyRoomDef;

#if defined(VERSION_PSP)
// A horizontally ordered array with head and tail sigils in the 1st field
extern LayoutEntity** g_pStObjLayoutHorizontal;
// A vertically ordered array with head and tail sigils in the 1st field
extern LayoutEntity** g_pStObjLayoutVertical;

#else
// A horizontally ordered array with head and tail sigils in the 1st field
extern LayoutEntity* g_pStObjLayoutHorizontal[];
// A vertically ordered array with head and tail sigils in the 1st field
extern LayoutEntity* g_pStObjLayoutVertical[];

#endif

#if defined(VERSION_PSP)
extern PfnEntityUpdate* PfnEntityUpdates;
#else
extern PfnEntityUpdate PfnEntityUpdates[];
#endif

extern u16 g_ItemIconSlots[0x20];

/*
 * Sets up layout arrays and initializes stage state to
 * initial values.
 *
 * - Parameters:
 *   - objLayoutId - the room to initialize
 */
void InitRoomEntities(s32 objLayoutId);

/*
 * An callback for notifying the stage that the
 * viewport has changed.
 */
void UpdateRoomPosition();

void Update(void);

void HitDetection(void);

s32 Random();
void CreateEntityFromEntity(u16 entityId, Entity* source, Entity* entity);
void CreateEntityFromLayout(Entity* entity, LayoutEntity* initDesc);
void DestroyEntity(Entity*);
void DestroyEntitiesFromIndex(s16 index);
void MoveEntity();
void FallEntity(void);
Entity* AllocEntity(Entity* start, Entity* end);

/*
 * `EntityInit` is used to define initialization options
 * for entities. This is treated as a `u16[]` by
 * `InitializeEntity` but is defined as a struct for
 * convenience and readability as well as providing the
 * correct layout and size for these entries.
 */
typedef struct EntityInit {
    u16 animSet;
    u16 animCurFrame;
    u16 unk5A;
    u16 palette;
    u16 enemyId;
    u16 : 16;
} EntityInit;

/*
 * InitializeEntity takes a EntityInit but treats it as
 * a `u16[]`.
 */
void InitializeEntity(u16 arg0[]);

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

extern Stages g_StageId;

// Width in pixel of how wide is the horizontal camera during normal game play
#define STAGE_WIDTH 256

#endif
