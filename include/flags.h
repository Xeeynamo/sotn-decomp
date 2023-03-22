typedef enum {
    PATH_BLOCK_WEIGHT = 49,
    MERMAN_ROCK = 51,
} flags;

/**
 * Rocks in the room full of Mermans
 * used by:
 * EntityMermanRockLeftSide
 * EntityMermanRockRightSide
 */
#define LEFT_HALF_BROKEN (1 << 0)
#define RIGHT_HALF_BROKEN (1 << 1)
#define LEFT_BROKEN (1 << 2)
#define RIGHT_BROKEN (1 << 3)

/**
 * Weight blocking the path to Marble Gallery
 * used by:
 * EntityPathBlockTallWeight
 */
#define PATH_SHORTCUT_OPEN (D_8003BDEC[49] != 0)

/**
 * Underground Garden hatch
 */
#define UNDERGROUND_GARDEN_HATCH_CLOSED 0
#define UNDERGROUND_GARDEN_HATCH_OPEN 1
