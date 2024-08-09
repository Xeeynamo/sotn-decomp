#include "game.h"
#include "stage.h"

void EntityUnkId01(Entity*);
void EntityExplosion(Entity*);
void EntityPrizeDrop(Entity*);
void EntityDamageDisplay(Entity*);
void EntityRedDoor(Entity*);
void EntityIntenseExplosion(Entity*);
void EntitySoulStealOrb(Entity*);
void EntityUnkId08(Entity*);
void EntityStageNamePopup(Entity*);
void EntityEquipItemDrop(Entity*);
void EntityRelicOrb(Entity*);
void EntityHeartDrop(Entity*);
void EntityEnemyBlood(Entity*);
void EntityMessageBox(Entity*);
void EntityDummy(Entity*);
void EntityBackgroundBlock(Entity*);
void EntityUnkId12(Entity*);
void EntityUnkId13(Entity*);
void EntityUnkId14(Entity*);
void EntityUnkId15(Entity*);
void EntityHolyGlassesCutscene(Entity*);
void EntityPlatform(Entity*);
void EntityMaria(Entity*);
void EntityRoomDarkness(Entity*);
void EntityElevatorStationary(Entity*);
void EntityUnkId1B(Entity*);
void EntityMovingElevator(Entity*);

PfnEntityUpdate PfnEntityUpdates[] = {
    EntityUnkId01,         EntityExplosion,
    EntityPrizeDrop,       EntityDamageDisplay,
    EntityRedDoor,         EntityIntenseExplosion,
    EntitySoulStealOrb,    EntityUnkId08,
    EntityStageNamePopup,  EntityEquipItemDrop,
    EntityRelicOrb,        EntityHeartDrop,
    EntityEnemyBlood,      EntityMessageBox,
    EntityDummy,           EntityDummy,
    EntityBackgroundBlock, EntityUnkId12,
    EntityUnkId13,         EntityUnkId14,
    EntityUnkId15,         EntityHolyGlassesCutscene,
    EntityPlatform,        EntityMaria,
    EntityRoomDarkness,    EntityElevatorStationary,
    EntityUnkId1B,         EntityMovingElevator,
};

EntityInit D_80180404 = {
    .animSet = ANIMSET_OVL(1),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 0,
};

EntityInit g_InitializeData0 = {
    .animSet = ANIMSET_DRA(3),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 1,
};

EntityInit g_InitializeEntityData0 = {
    .animSet = ANIMSET_DRA(3),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 2,
};

EntityInit D_80180428 = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 4,
};

EntityInit g_EInitGeneric = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 5,
};

EntityInit g_InitDataEnt13 = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 2,
};

EntityInit D_8018044C = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 1,
};

EntityInit g_eInitGeneric2 = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 3,
};

EntityInit g_eDamageDisplayInit = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 3,
};

EntityInit D_80180470 = {
    .animSet = ANIMSET_OVL(1),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 3,
};

EntityInit D_8018047C = {
    .animSet = ANIMSET_OVL(11),
    .animCurFrame = 1,
    .unk5A = 72,
    .palette = PAL_DRA(547),
    .enemyId = 5,
};

static u32 JUNK_80180488 = 0x00FF0140;
static u32 D_8018048C = 0x00FF0740;

ObjInit2 D_80180490 = {
    .animSet = ANIMSET_OVL(2),
    .zPriority = 129,
    .unk4 = {.s = 0},
    .palette = PAL_DRA(0),
    .drawFlags = DRAW_DEFAULT,
    .unkC = NULL,
    .unk10 = &D_8018048C,
};

u16 g_eRedDoorTiles[3][8] = {
    {
        0x039C,
        0x039B,
        0x039C,
        0x039B,
        0x010D,
        0x010B,
        0x010D,
        0x010B,
    },
    {
        0x03A3,
        0x03A4,
        0x03A5,
        0x03A6,
        0x02F4,
        0x0309,
        0x0305,
        0x0307,
    },
    {
        0x03A3,
        0x03A7,
        0x03A8,
        0x03A3,
        0x02F4,
        0x030F,
        0x0310,
        0x02F4,
    },
};

u8 D_801804D4[] = {32, 32, 32, 32, 32, 32, 80, 32};
u8 D_801804DC[] = {0, 0, 0, 0, 0, 0, 0, 0};

u16 D_801804E4[] = {
    0x0000, 0x0000, 0x0600, 0x0100, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x01FC, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x00FC, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x0200, 0x0600, 0x0300,
    0x0000, 0x01FC, 0x0500, 0x02FC, 0x0000, 0x0000, 0x0500, 0x0400,
    0x0000, 0x0000, 0x0500, 0x0400, 0x0000, 0x01FC, 0x0500, 0x02FC,
    0x00F0, 0x01FC, 0x0310, 0x02FC, 0x00F0, 0x01FC, 0x0310, 0x02FC,
};

static u16 D_80180554[] = {
    0x0E03, 0x0F04, 0x1004, 0x1104, 0x1204, 0x1304, 0x1403, 0x0000,
};

static u16 D_80180564[] = {
    0x1503, 0x1604, 0x1704, 0x1804, 0x1904, 0x1A04, 0x1B03, 0x0000,
};

u16* D_80180574[] = {
    D_80180554, D_80180564, NULL, NULL, NULL, NULL, NULL, NULL,
};

// height
u8 D_80180594[] = {
    12, 20, 0, 0, 0, 0, 0, 0,
};

// params
u8 D_8018059C[] = {
    0x3, 0x3, 0, 0, 0, 0, 0, 0,
};

// animset
u16 D_801805A4[] = {
    ANIMSET_OVL(1), ANIMSET_OVL(1), 0, 0, 0, 0, 0, 0,
};

// draw mode
u8 D_801805B4[] = {
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
};

s16 D_801805BC[] = {
    -4, -4, 3, -6, 2, 9, -4, 12, 0, 2, 0, 15, 0, 31,
};

u8 D_801805D8[] = {0, 64, 0, 0};
u8 D_801805DC[] = {0, 0, 0, 0};

// clut
u16 D_801805E0[] = {
    LAYER_CLUT_ALT | 0,
    LAYER_CLUT_ALT | 8,
    LAYER_CLUT_ALT | 16,
    LAYER_CLUT_ALT | 24,
};
u16 D_801805E8[] = {0, 32};

u16 D_801805EC[] = {
    0x01A1,
    0x01A1,
    0x01A1,
    0x01A1,
};

// x-coords
u16 D_801805F4[] = {
    0x08, 0x13, 0x11, 0x31, 0x4F, 0x26, 0x36, 0x1D, 0x1B, 0x33, 0x2C, 0x21,
    0x19, 0x0A, 0x33, 0x1F, 0x48, 0x2F, 0x13, 0x19, 0x4D, 0x4B, 0x17, 0x1D,
    0x12, 0x02, 0x1B, 0x2A, 0x50, 0x45, 0x32, 0x0D, 0x2A, 0x4D, 0x06, 0x27,
    0x07, 0x48, 0x2F, 0x1B, 0x36, 0x22, 0x39, 0x14, 0x39, 0x1D, 0x0A, 0x35,
    0x10, 0x1B, 0x3D, 0x17, 0x2E, 0x0B, 0x49, 0x42, 0x3D, 0x2A, 0x01, 0x0C,
    0x1B, 0x34, 0x41, 0x35, 0x08, 0x0E, 0x4D, 0x11, 0x34, 0x41, 0x29, 0x48,
};

char* D_80180684[] = {
    _S("Alucard"),
    _S("Maria"),
};

static const char _pad[4] = "";

// tile layout
u16 D_8018068C[] = {
    0x014A, 0x014B, 0x014E, 0x014F, 0x014C, 0x014D, 0x0150, 0x0151, 0x00F5,
    0x00F6, 0x012B, 0x012C, 0x00FC, 0x00FD, 0x012F, 0x0130, 0x0101, 0x00FF,
    0x0201, 0x00FF, 0x0201, 0x0307, 0x0407, 0x0507, 0x0607, 0x0707, 0x0807,
    0x0907, 0x0A10, 0x00FF, 0x0A01, 0x0B06, 0x0C06, 0x0D06, 0x0E10, 0x0F0A,
    0x0E0A, 0x0F0A, 0x0E20, 0x00FF, 0x0E01, 0x1004, 0x1104, 0x120B, 0x00FF,
    0x0000, 0x1301, 0x00FF, 0x1201, 0x00FF, 0x1220, 0x1103, 0x1003, 0x1403,
    0x1503, 0x1640, 0x1506, 0x0D05, 0x0C05, 0x0B05, 0x0A20, 0x00FF, 0x0A10,
    0x1710, 0x0A08, 0x00FF, 0x0A01, 0x0B02, 0x0C02, 0x1806, 0x1906, 0x1850,
    0x0C03, 0x0B03, 0x0A08, 0x00FF, 0x0A01, 0x0B03, 0x0C03, 0x0D03, 0x0E03,
    0x1B06, 0x1A10, 0x1B20, 0x0E03, 0x0D03, 0x0C03, 0x00FF, 0x1C04, 0x1D04,
    0x1E04, 0x1F04, 0x00FF, 0x0000, 0x2002, 0x2104, 0x2204, 0x2304, 0x2404,
    0x2504, 0x2604, 0x2704, 0x2002, 0x0000, 0x2808, 0x2908, 0x2A60, 0x00FF,
    0x0C01, 0x00FF,
};

u32 D_80180768[] = {
    0x04040308, 0x06040504, 0x08040704, 0x0A020904, 0x0A100B01, 0x000000FF,
};

u32 D_80180780[] = {
    0x09040A04, 0x07040804, 0x05040604, 0x03040404, 0x03040C02,
    0x000000FF, 0x00000000, 0x00000000, 0x00000001, 0x00000001,
    0x00010001, 0x00010001, 0x00010001, 0x01010001,
};

// palette
u16 UNK_Invincibility0[] = {
    PAL_OVL(0x163), PAL_OVL(0x164), PAL_OVL(0x166), PAL_OVL(0x164),
    PAL_OVL(0x160), PAL_OVL(0x166), PAL_OVL(0x162), PAL_OVL(0x164),
    PAL_OVL(0x167), PAL_OVL(0x164), PAL_OVL(0x167), PAL_OVL(0x168),
    PAL_OVL(0x168), PAL_OVL(0x164), PAL_OVL(0x161), PAL_OVL(0x164),
    PAL_OVL(0x165), PAL_OVL(0x165), PAL_OVL(0x163), PAL_OVL(0x163),
    PAL_OVL(0x165), PAL_OVL(0x165),
};
