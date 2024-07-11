#include <stage.h>
#include <game.h> // TODO: placeholder

#define OVL_EXPORT(x) WRP_##x

#define CASTLE_FLAG_BANK 0x00

// WRP Sound IDs
#define SE_WARP_ENTER 0x636
#define SE_WARP_DEBRIS 0x644

typedef enum {
    E_NONE,
    E_BREAKABLE,
    E_EXPLOSION,
    E_PRIZE_DROP,
    E_NUMERIC_DAMAGE,
    E_RED_DOOR,
    E_INTENSE_EXPLOSION,
    E_SOUL_STEAL_ORB,
    E_ROOM_FOREGROUND,
    E_STAGE_NAME_POPUP,
    E_EQUIP_ITEM_DROP,
    E_RELIC_ORB,
    E_HEART_DROP,
    E_ENEMY_BLOOD,
    E_SAVE_GAME_POPUP,
    E_DUMMY_0F,
    E_DUMMY_10,
    E_UNK_11,
    E_UNK_12,
    E_UNK_13,
    E_ID_14,
    E_ID_15,
    E_WARP,
    E_SMALL_ROCKS,
} EntityIDs;

typedef struct {
    s16 x, y;
} WarpCoord;

extern s32 D_8003C8B8;

extern u16 g_InitializeData0[];
extern u16 g_InitializeEntityData0[];
extern u16 g_EInitGeneric[];
extern u16 g_eInitGeneric2[];
extern u16 D_801804C4[];
extern u16 g_eRedDoorTiles[2][8];
extern u8 g_eRedDoorUV[3][8];
extern u16 g_eUnk14SpawnRots[];
extern u16 g_ESoulStealOrbAngles[];
extern s16 g_ESoulStealOrbSprt[];
extern u8 g_ESoulStealOrbAnim[];

extern u16 g_ItemIconSlots[32];

void func_8018F838(Entity*);
void EntityUnkId14(Entity* entity);
void EntityUnkId15(Entity* entity);
