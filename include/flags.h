/**
 * Holds flags that checks if certain switches are enabled to allow to have
 * shortcuts around the castle. One typical example is the wood column that
 * prevents the player to enter the warp room.
 */
#define CASTLE_FLAGS g_CastleFlags

/**
 * Rocks in the room full of Mermans
 * used by:
 * EntityMermanSecretPassage
 * EntityMermanRockLeftSide
 * EntityMermanRockRightSide
 */
#define MERMAN_ROCK (CASTLE_FLAGS[51])
#define LEFT_BROKEN (1 << 0)
#define RIGHT_BROKEN (1 << 1)
#define WOLF_FLAG (1 << 2)
#define BAT_FLAG (1 << 3)
#define MERMAN_WOLF_BAT (WOLF_FLAG + BAT_FLAG)

/**
 * Weight blocking the path to Marble Gallery
 * used by:
 * EntityPathBlockTallWeight
 * EntityPathBlockSmallWeight
 * EntityClickSwitch
 */
#define MARBLE_GALLERY_SHORTCUT_OPEN (CASTLE_FLAGS[49])

/**
 * Underground Garden hatch
 * used by:
 * EntityTrapDoor
 */
#define UNDERGROUND_GARDEN_HATCH_CLOSED (false)
#define UNDERGROUND_GARDEN_HATCH_OPEN (true)

/**
 * Castle Entrance Warp room shortcut
 * used by:
 * EntitySwitch
 * EntityHeartRoomGoldDoor
 */
#define ENTRANCE_WARP_ROOM_SHORTCUT_OPEN (CASTLE_FLAGS[50])

/**
 * Underground Caverns path door
 * used by:
 * EntityCavernDoorLever
 * EntityCavernDoor
 */
#define UNDERGROUND_CAVERNS_DOOR_OPEN (CASTLE_FLAGS[48])

/**
 * Merman Room Secret Passage
 * used by:
 * EntityMermanSecretPassage
 */
#define MERMAN_ROOM_SECRET_PASSAGE_OPEN (CASTLE_FLAGS[58])