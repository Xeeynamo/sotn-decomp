// Holds flags that maintain the persistant "state" of the castle.
// These cover a wide range of uses, but what they have in common is a need to
// track something across rooms or stages.
extern u8 g_CastleFlags[0x300]; // starts at 0x8003BDEC

// All offsets and values included for organizational convenience.
typedef enum {
    /* 0x0 */ CEN_OPEN = 0, // Wear the gold and silver rings in the clock room
    /* 0x1 */ NO4_OPEN = 1, // Floor switch behind the blue door in NO0
    /* 0x2 */ NO0_BANNER = 2,
    /* 0x10 */ NO1_ELEVATOR_ACTIVATED = 16, // Set by switch in outer wall
    /* 0x11 */ CASTLE_FLAG_17 = 17,         // Unknown trigger
    /* 0x12 */ NO1_SECRET_WALL_BROKEN = 18, // Wall chicken wall fully broken

    // Used for the weather in NO1. An option is randomly selected
    // from g_NO1WeatherOptions when changing overlays.
    // A value of 0x80 is rain
    // A value of 0x81 is clear
    // A value of 0x82 is fog
    /* 0x13 */ NO1_WEATHER = 19,

    // Used for the bird lifecycle under the bottom room of NO1.
    // It is incremented each time the bird leaves it's nest, to a max of 8.
    /* 0x14 */ NO1_BIRD_CYCLE = 20,
    /* 0x15 */ NO1_BANNER = 21,

    // For some reason, offset 0x20 is the only wall/floor break flag that
    // changes when you enter the room: 0x1 is wall broken, 0x3 is room entered
    /* 0x20 */ NO2_SECRET_WALL_BROKEN = 32,
    /* 0x21 */ NO2_SECRET_CEILING_BROKEN = 33,
    /* 0x22 */ NO2_BANNER = 34,
    /* 0x30 */ NO4_TO_NP3_SHORTCUT = 48,
    /* 0x31 */ NO0_TO_NP3_SHORTCUT = 49,
    /* 0x32 */ WRP_TO_NP3_SHORTCUT = 50,

    // Used for tracking the steps to unlock the jewel sword room
    // Bit 1 is set when the left side rocks are destroyed
    // Bit 2 is set when the right side rocks are destroyed
    // Bit 3 is set when you pass through as wolf
    // Bit 4 is set when you pass through as bat
    /* 0x33 */ JEWEL_SWORD_ROOM_STEPS = 51,
    /* 0x34 */ PROLOGUE_COMPLETE = 52,
    /* 0x35 */ IVE_BEEN_ROBBED = 53,        // Set when Death takes your stuff
    /* 0x36 */ CASTLE_FLAG_54 = 54,         // Unused?
    /* 0x37 */ CASTLE_TURNED_ON = 55,       // Sets in first NO3 Hallway
    /* 0x38 */ DEATH_STAIRWAY_BROKEN = 56,  // Break the ledge just before Death
    /* 0x39 */ SLO_GAI_RETREATED = 57,      // Slogra/Gaibon retreated in NP3
    /* 0x3A */ JEWEL_SWORD_ROOM_OPEN = 58,  // Set after flag offset 0x33 == 15
    /* 0x40 */ CAT_SIGN_WALL_BROKEN = 64,   // The wall with an arrow sign
    /* 0x41 */ CAT_SECRET_WALL_BROKEN = 65, // The other breakable wall
    /* 0x42 */ CAT_SPIKE_ROOM_LIT = 66,     // The switch after the spike room
    /* 0x43 */ CAT_BANNER = 67,
    /* 0x44 */ SPIKE_BREAKER_SECRET = 68, // The wall behind spike breaker armor
    /* 0x50 */ DEMON_SWITCH = 80, // When the demon hits the switch in CHI
    /* 0x51 */ CHI_SECRET_WALL_BROKEN = 81,
    /* 0x52 */ CHI_LARGE_STEPS_FALLEN = 82,
    /* 0x53 */ CHI_TINY_STEPS_FALLEN = 83,
    /* 0x54 */ CHI_BANNER = 84,
    /* 0x60 */ NO2_TO_DAI_SHORTCUT = 96,
    /* 0x61 */ DAI_BANNER = 97,
    /* 0x62 */ MET_MARIA_AFTER_HIPPOGRYPH = 98,
    /* 0x63 */ MET_MARIA_IN_DAI = 99,
    /* 0x70 */ LIB_BOOKSHELF_SECRET = 112, // The spinning bookshelf in LIB
    /* 0x71 */ LIB_BANNER = 113,
    /* 0x72 */ MET_LIBRARIAN = 114,
    /* 0x73 */ BOUGHT_CASTLE_MAP = 115, // Buy the castle map from the librarian
    /* 0x74 */ LIBRARIAN_DROPS = 116,   // Gravity jump into the librarian
    /* 10000000 */ // LIBRARIAN_LIFE_VESSEL // Always on the first hit
    /* 01000000 */ // LIBRARIAN_RING_OF_ARCANA
    /* 00100000 */ // LIBRARIAN_AXE_LORD_ARMOR
    /* 00010000 */ // LIBRARIAN_DRACULAS_CAPE // Unconfirmed

    /* 0x80 */ NZ0_BANNER = 128,
    /* 0x81 */ NZ0_SECRET_WALL_BROKEN = 129,
    /* 0x82 */ NZ0_SECRET_FLOOR_BROKEN = 130,
    /* 0x83 */ NZ0_CANNON_WALL_SHORTCUT = 131,
    /* 0x84 */ SLO_GAI_DEFEATED = 132, // Defeated Slogra & Gaibon in NZ0
    /* 0x85 */ MET_MARIA_IN_NZ0 = 133,
    /* 0x90 */ TOP_BANNER = 144,
    /* 0x92 */ TOP_SECRET_WALL_BROKEN = 146,
    /* 0x93 */ TOP_LION_LIGHTS = 147,    // Different bits for each lion pair
    /* 0x94 */ TOP_SECRET_STAIRS = 148,  // The drop down stairs before Richter
    /* 0x95 */ SHAFT_ORB_DEFEATED = 149, // Set by defeating Shaft's orb
    /* 0x96 */ INVERTED_CASTLE_UNLOCKED = 150,

    // Since 0x9B and 0xB9 are set at the same time, this goes by code order for
    // what they likely are
    /* 0x9B */ ST0_BANNER = 155,
    /* 0xA0 */ NZ1_BANNER = 160,
    /* 0xA1 */ NZ1_SECRET_WALL_BROKEN = 161, // Lower left wall of the long room
    /* 0xA2 */ NZ1_UPPER_WALL_BROKEN = 162,  // Top of the left gear room
    /* 0xA3 */ NZ1_STATUE_ROOM_BREAKABLE_WALLS = 163,
    /* 10000000 */ //
    /* 01000000 */ // LEFT_WALL_BROKEN
    /* 00100000 */ // BOTTOM_WALL_BROKEN
    /* 00010000 */ // RIGHT_WALL_BROKEN

    /* 0xB0 */ ARE_BANNER = 176,
    /* 0xB1 */ ARE_TO_DAI_SHORTCUT = 177,
    /* 0xB2 */ ARE_ELEVATOR_ACTIVATED = 178,

    // The cutscene with Richter after the Minotaur and Werewolf fight
    /* 0xB4 */ RICHTER_CS_AFTER_M_AND_W = 180,

    // Since 0x9B and 0xB9 are set at the same time, this goes by code order for
    // what they likely are
    /* 0xB9 */ INTRO_VIDEO = 185,
    /* 0xC0 */ NO4_BANNER = 192,

    // Offset 0xC1 is set by blocking the water with the crate in NO4
    // Ends at value of 3, incrementing by 1 as the water fills
    /* 0xC1 */ NO4_WATER_BLOCKED = 193,
    /* 0xC2 */ BOATMAN_GATE_OPENED = 194, // At the end of the second boat trip
    /* 0xC3 */ SCYLLA_DEFEATED = 195,     // Controls the water before Scylla
    /* 0xC4 */ NO4_FLOOR_SECRET = 196,
    /* 0xC5 */ SCYLLA_WYRM_DEFEATED = 197, // Miniboss before Scylla
    /* 0xC6 */ NO4_SECRET_WALL_BROKEN = 198,

    // Set by pushing the wall switch in the upper room left of the waterfall
    // Value of 1 spawns the ape, 2 is when theh bridge is half broken, and 3 is
    // when the bridge is gone Pressing triangle on the P2 controller increments
    // this flag by 1
    /* 0xC7 */ NO4_SKELETON_APE_AND_BRIDGE = 199,
    /* 0xC8 */ MET_FERRYMAN_AGAIN = 200, // Meet the ferryman on the right side
    /* 0xC9 */ MET_FERRYMAN = 201,       // Meet the ferryman on the left side
    /* 0xD0 */ WRP_UNLOCKS = 208,
    /* 10000000 */ // NP3_WARP
    /* 01000000 */ // CHI_WARP
    /* 00100000 */ // NO1_WARP
    /* 00010000 */ // TOP_WARP
    /* 00001000 */ // NO2_WARP

    /* 0xD1 */ RWRP_UNLOCKS = 209,
    /* 10000000 */ // RNO3_WARP
    /* 01000000 */ // RCHI_WARP
    /* 00100000 */ // RNO1_WARP
    /* 00010000 */ // RTOP_WARP
    /* 00001000 */ // RNO2_WARP

    /* 0xD4 */ SUCCUBUS_CS = 212, // After Succubus (as Lisa) cutscene
    /* 0xD5 */ DRE_BANNER = 213,
    /* 0xD8 */ MET_MARIA_IN_CEN = 216, // Holy Glasses cutscene in CEN
    /* 0xDC */ CASTLE_FLAG_220 = 220,  // Unknown trigger
    /* 0x100 */ CASTLE_COLLECTIBLES_100 = 256,
    /* 10000000 */ // NO0_CLOCK_LIFE_VESSEL
    /* 01000000 */ // NO0_ALUCART_SHIELD
    /* 00100000 */ // NO0_CLOCK_HEART_VESSEL
    /* 00010000 */ // NO0_CLOCK_LIFE_APPLE
    /* 00001000 */ // NO0_CLOCK_HAMMER
    /* 00000100 */ // NO0_CLOCK_POTION
    /* 00000010 */ // NO0_ALUCART_MAIL
    /* 00000001 */ // NO0_ALUCART_SWORD

    /* 0x101 */ CASTLE_COLLECTIBLES_101 = 257,
    /* 10000000 */ // NO0_CLOCK_SECRET_LIFE_VESSEL // Below the clock room
    /* 01000000 */ // NO0_CLOCK_SECRET_HEART_VESSEL // Below the clock room
    /* 00100000 */ // NO0_LIB_CARD
    /* 00010000 */ // NO0_ATTACK_POTION
    /* 00001000 */ // NO0_HAMMER
    /* 00000100 */ // NO0_STR_POTION
    /* 00000010 */ //
    /* 00000001 */ //

    /* 0x102 */ CASTLE_COLLECTIBLES_102 = 258,
    /* 10000000 */ // NO1_JEWEL_KNUCKLES
    /* 01000000 */ // NO1_MIRROR_CUIRASS
    /* 00100000 */ // NO1_ELEVATOR_HEART_VESSEL
    /* 00010000 */ // NO1_GARNET
    /* 00001000 */ // NO1_GLADIUS
    /* 00000100 */ // NO1_LIFE_VESSEL
    /* 00000010 */ // NO1_ZIRCON
    /* 00000001 */ //

    /* 0x104 */ CASTLE_COLLECTIBLES_104 = 260,
    /* 10000000 */ //
    /* 01000000 */ // NO2_HEART_VESSEL
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00001000 */ // NO2_SECRET_BROADSWORD
    /* 00000100 */ // NO2_SECRET_ONYX
    /* 00000010 */ // NO2_SECRET_CHEESE
    /* 00000001 */ // NO2_MANNA_PRISM

    /* 0x105 */ CASTLE_COLLECTIBLES_105 = 261,
    /* 10000000 */ // NO2_RESIST_FIRE
    /* 01000000 */ // NO2_LUCK_POTION
    /* 00100000 */ // NO2_ESTOC
    /* 00010000 */ // NO2_IRON_BALL
    /* 00001000 */ // NO2_GARNET
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //

    // NP3_MERMAN_LIFE_APPLE is technically collectable in NO3, but you
    // can't unlock the room
    /* 0x106 */ CASTLE_COLLECTIBLES_106 = 262,
    /* 10000000 */ // NP3_DEATH_HEART_VESSEL // Left side room above Death
    /* 01000000 */ // NP3_LIFE_VESSEL
    /* 00100000 */ // NP3_MERMAN_LIFE_APPLE
    /* 00000001 */ //
    /* 00001000 */ // NP3_SHIELD_POTION
    /* 00000100 */ // NP3_HOLY_MAIL
    /* 00000010 */ // NP3_MERMAN_LIFE_VESSEL
    /* 00000001 */ // NP3_WARP_HEART_VESSEL

    /* 0x107 */ CASTLE_COLLECTIBLES_107 = 263,
    /* 10000000 */ //
    /* 01000000 */ // NP3_JEWEL_SWORD // Doesn't exist in NO3
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //

    /* 0x108 */ CASTLE_COLLECTIBLES_108 = 264,
    /* 10000000 */ // NO4_HEART_VESSEL
    /* 01000000 */ // NO4_LIFE_VESSEL
    /* 00100000 */ // NO4_CRYSTAL_CLOAK
    /* 00000001 */ //
    /* 00001000 */ // NO4_ANTIVENOM
    /* 00000100 */ // NO4_UNDERWATER_LIFE_VESSEL
    /* 00000010 */ // NO4_WATERFALL_LIFE_VESSEL
    /* 00000001 */ // NO4_HERALD_SHIELD

    /* 0x109 */ CASTLE_COLLECTIBLES_109 = 265,
    /* 10000000 */ //
    /* 01000000 */ // NO4_ZIRCON
    /* 00100000 */ // NO4_GOLD_RING // Appears after Succubus fight
    /* 00010000 */ // NO4_BANDANNA
    /* 00001000 */ // NO4_SHIITAKE_1
    /* 00000100 */ // NO4_CLAYMORE
    /* 00000010 */ // NO4_MEAL_TICKET_1 // Top urn on the right side
    /* 00000001 */ // NO4_MEAL_TICKET_2 // Middle urn on the right side

    /* 0x10A */ CASTLE_COLLECTIBLES_10A = 266,
    /* 10000000 */ // NO4_MEAL_TICKET_3 // Top urn on the left side
    /* 01000000 */ // NO4_MEAL_TICKET_4 // Bottom urn on the left side
    /* 00100000 */ // NO4_MOONSTONE // Bottom urn on the right side
    /* 00010000 */ // NO4_SCIMITAR
    /* 00001000 */ // NO4_RESIST_ICE
    /* 00000100 */ // NO4_POT_ROAST
    /* 00000010 */ // NO4_ONYX
    /* 00000001 */ // NO4_KNUCKLE_DUSTER

    /* 0x10B */ CASTLE_COLLECTIBLES_10B = 267,
    /* 10000000 */ // NO4_BOATMAN_LIFE_VESSEL // Second boatman area
    /* 01000000 */ // NO4_ELIXER
    /* 00100000 */ // NO4_SHIITAKE_2
    /* 00010000 */ // NO4_TOADSTOOL
    /* 00001000 */ // NO4_BRIDGE_LIFE_VESSEL
    /* 00000100 */ // NO4_BRIDGE_HEART_VESSEL
    /* 00000010 */ // NO4_PENTAGRAM
    /* 00000001 */ // NO4_SECRET_BOOTS

    /* 0x10C */ CASTLE_COLLECTIBLES_10C = 268,
    /* 10000000 */ // NO4_SHIITAKE_3 // Found with NO4_SHIITAKE_4
    /* 01000000 */ // NO4_SHIITAKE_4 // Found with NO4_SHIITAKE_3
    /* 00000001 */ //
    /* 00010000 */ // NO4_SHORTCUT_SIDE_SHIITAKE
    /* 00001000 */ // NO4_NUNCHAKU
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //

    /* 0x10E */ CASTLE_COLLECTIBLES_10E = 270,
    /* 10000000 */ //
    /* 01000000 */ // LIB_STONE_MASK
    /* 00100000 */ // LIB_HOLY_ROD
    /* 00000001 */ //
    /* 00001000 */ // LIB_BRONZE_CUIRASS
    /* 00000100 */ // LIB_TAKEMITSU
    /* 00000010 */ // LIB_ONYX
    /* 00000001 */ // LIB_FRANKFURTER

    /* 0x10F */ CASTLE_COLLECTIBLES_10F = 271,
    /* 10000000 */ // LIB_POTION
    /* 01000000 */ // LIB_ANTIVENOM
    /* 00100000 */ // LIB_TOPAZ_CIRCLET
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //

    /* 0x110 */ CASTLE_COLLECTIBLES_110 = 272,
    /* 10000000 */ // CAT_CATEYE_CIRCLET
    /* 01000000 */ // CAT_ICEBRAND
    /* 00100000 */ // CAT_WALK_ARMOR
    /* 00010000 */ // CAT_MORMEGIL
    /* 00001000 */ // CAT_LIBRARY_CARD // Found by destroying the wall behind
                   // the Spike Breaker armor
    /* 00000001 */ //
    /* 00000010 */ // CAT_HEART_VESSEL_2 // Top urn on left side of CAT
    /* 00000001 */ // CAT_BALLROOM_MASK // Bottom urn on left side of CAT

    /* 0x111 */ CASTLE_COLLECTIBLES_111 = 273,
    /* 10000000 */ // CAT_BLOODSTONE
    /* 01000000 */ // CAT_LIFE_VESSEL
    /* 00100000 */ // CAT_HEART_VESSEL_1
    /* 00010000 */ // CAT_CROSS_SHURIKEN_2 // Right urn,top ledge,right side
    /* 00001000 */ // CAT_CROSS_SHURIKEN_1 // Left urn,top ledge,right side
    /* 00000100 */ // CAT_KARMA_COIN_2 //  Right urn,bottom ledge,right side
    /* 00000010 */ // CAT_KARMA_COIN_1 // Left urn,bottom ledge,right side
    /* 00000001 */ // CAT_PORK_BUN // Lower rightmost space in CAT

    /* 0x112 */ CASTLE_COLLECTIBLES_112 = 274,
    /* 10000000 */ // CAT_SPIKE_BREAKER_ARMOR
    /* 01000000 */ // CAT_MONSTER_VIAL_3_4 // Third sarcophogus from left
    /* 00100000 */ // CAT_MONSTER_VIAL_3_3 // Fifth sarcophogus from left
    /* 00010000 */ // CAT_MONSTER_VIAL_3_2 // Sixth sarcophogus from left
    /* 00001000 */ // CAT_MONSTER_VIAL_3_1 // Eighth sarcophogus from left
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //

    /* 0x113 */ CASTLE_COLLECTIBLES_113 = 275,
    /* 10000000 */ // DAI_ANKH_OF_LIFE
    /* 01000000 */ // DAI_MORNINGSTAR
    /* 00100000 */ // DAI_SILVER_RING
    /* 00010000 */ // DAI_AQUAMARINE
    /* 00001000 */ // DAI_MYSTIC_PENDANT
    /* 00000100 */ // DAI_MAGIC_MISSILE
    /* 00000010 */ // DAI_SHURIKEN
    /* 00000001 */ // DAI_TNT

    /* 0x114 */ CASTLE_COLLECTIBLES_114 = 276,
    /* 10000000 */ // DAI_BOOMERANG
    /* 01000000 */ // DAI_GOGGLES
    /* 00100000 */ // DAI_SILVER_PLATE
    /* 00010000 */ // DAI_STR_POTION
    /* 00001000 */ // DAI_LIFE_VESSEL
    /* 00000100 */ // DAI_ZIRCON
    /* 00000010 */ // DAI_CUTLASS
    /* 00000001 */ // DAI_POTION

    /* 0x115 */ CASTLE_COLLECTIBLES_115 = 277,
    /* 10000000 */ //
    /* 01000000 */ //
    /* 00100000 */ //
    /* 00010000 */ //
    /* 00001000 */ //
    /* 00000100 */ //
    /* 00000010 */ //
    /* 00000001 */ //

    /* 0x116 */ CASTLE_COLLECTIBLES_116 = 278,
    /* 10000000 */ // CHI_SECRET_POWER_OF_SIRE
    /* 01000000 */ // CHI_KARMA_COIN       // Left side room at the bottom
    /* 00000001 */ //
    /* 00010000 */ // CHI_WALL_TURKEY
    /* 00001000 */ // CHI_RING_OF_ARES
    /* 00000100 */ // CHI_COMBAT_KNIFE
    /* 00000010 */ // CHI_SHIITAKE_2       // Right side of shaft to CAT
    /* 00000001 */ // CHI_SHIITAKE_1       // Left side of shaft to CAT

    /* 0x117 */ CASTLE_COLLECTIBLES_117 = 279,
    /* 10000000 */ // CHI_SECRET_BARLEY_TEA
    /* 01000000 */ // CHI_SECRET_PEANUTS_1 // Counting the 4 peanuts from left
    /* 00100000 */ // CHI_SECRET_PEANUTS_2 // to right of the secret room
    /* 00010000 */ // CHI_SECRET_PEANUTS_3
    /* 00001000 */ // CHI_SECRET_PEANUTS_4
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //

    /* 0x11A */ CASTLE_COLLECTIBLES_11A = 282,
    /* 10000000 */ // ARE_HEART_VESSEL
    /* 01000000 */ // ARE_SHIELD_ROD
    /* 00000001 */ //
    /* 00010000 */ // ARE_BLOOD_CLOAK
    /* 00001000 */ // ARE_KNIGHT_SHIELD
    /* 00000100 */ // ARE_LIBRARY_CARD
    /* 00000010 */ // ARE_GREEN_TEA         // "guarded" by Grave Keeper
    /* 00000001 */ //

    /* 0x11B */ CASTLE_COLLECTIBLES_11B = 283,
    /* 10000000 */ //
    /* 01000000 */ //
    /* 00100000 */ //
    /* 00010000 */ //
    /* 00001000 */ //
    /* 00000100 */ //
    /* 00000010 */ //
    /* 00000001 */ //

    /* 0x11C */ CASTLE_COLLECTIBLES_11C = 284,
    /* 10000000 */ // TOP_TURQOISE
    /* 01000000 */ // TOP_WALL_TURKEY
    /* 00000001 */ //
    /* 00010000 */ // TOP_TYRFING
    /* 00001000 */ // TOP_SIRLOIN
    /* 00000100 */ // TOP_STATUE_TURKEY
    /* 00000010 */ // TOP_POT_ROAST
    /* 00000001 */ // TOP_FRANKFURTER

    /* 0x11D */ CASTLE_COLLECTIBLES_11D = 285,
    /* 10000000 */ // TOP_RESIST_STONE
    /* 01000000 */ // TOP_RESIST_DARK
    /* 00100000 */ // TOP_RESIST_HOLY
    /* 00010000 */ // TOP_PLATINUM_MAIL
    /* 00001000 */ // TOP_FALCHION
    /* 00000100 */ // TOP_LIFE_VESSEL_1 // Counting from top to bottom of the
    /* 00000010 */ // TOP_LIFE_VESSEL_2 // ledge room in the upper right
    /* 00000001 */ // TOP_HEART_VESSEL_1 // of the outdoor area

    /* 0x11E */ CASTLE_COLLECTIBLES_11E = 286,
    /* 10000000 */ // TOP_HEART_VESSEL_2
    /* 00000001 */ //
    /* 00100000 */ // TOP_TABLE_HEART_VESSEL // Just before Richter
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //

    /* 0x11F */ CASTLE_COLLECTIBLES_11F = 287,
    /* 10000000 */ // NZ0_HIDE_CUIRASS
    /* 01000000 */ // NZ0_HEART_UP
    /* 00100000 */ // NZ0_CLOTH_CAPE
    /* 00010000 */ // NZ0_LIFE_UP
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000010 */ // NZ0_SUNGLASSES
    /* 00000001 */ // NZ0_RESIST_THUNDER

    // Likely mirrors ENEMY_LIST in function
    /* 0x120 */ MAD_COLLISION_FLAGS_START = 288,
    /* 0x120 */ CASTLE_COLLECTIBLES_120 = 288,
    /* 10000000 */ // NZ0_LEATHER_SHIELD
    /* 01000000 */ // NZ0_BASILARD
    /* 00100000 */ // NZ0_POTION
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //

    /* 0x121 */ CASTLE_COLLECTIBLES_121 = 289,
    /* 10000000 */ // NZ1_MAGIC_MISSILE
    /* 01000000 */ // NZ1_PENTAGRAM
    /* 00000001 */ //
    /* 00010000 */ // NZ1_STAR_FLAIL
    /* 00001000 */ // NZ1_GOLD_PLATE
    /* 00000100 */ // NZ1_STEEL_HELM
    /* 00000010 */ // NZ1_HEALING_MAIL
    /* 00000001 */ //

    /* 0x122 */ CASTLE_COLLECTIBLES_122 = 290,
    /* 10000000 */ //
    /* 01000000 */ //
    /* 00100000 */ // NZ1_SECRET_GEAR_ROOM_LIFE_VESSEL
    /* 00010000 */ // NZ1_SECRET_GEAR_ROOM_HEART_VESSEL
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000001 */ //

    // Likely mirrors ENEMY_LIST_RAREDROP in function
    /* 0x140 */ MAD_RAREDROP_FLAGS_START = 320,
    /* 0x180 */ ENEMY_TACTICS_180 = 384,
    /* 10000000 */ // DRACULA_TACTICS
    /* 01000000 */ // OLROX_TACTICS
    /* 00100000 */ // DOPPLEGANGER10_TACTICS
    /* 00010000 */ // GRANFALOON_TACTICS
    /* 00001000 */ // MINOTAUR_WEREWOLF_TACTICS
    /* 00000100 */ // SCYLLA_TACTICS
    /* 00000010 */ // SLO_GAI_TACTICS
    /* 00000001 */ // HIPPOGRYPH_TACTICS

    /* 0x181 */ ENEMY_TACTICS_181 = 385,
    /* 10000000 */ //
    /* 01000000 */ // SUCCUBUS_TACTICS
    /* 00100000 */ // KARASUMAN_TACTICS
    /* 00000001 */ //
    /* 00000001 */ //
    /* 00000100 */ // CERBERUS_TACTICS // It is spelled Cerberos for the enemy
    /* 00000010 */ // RICHTER_TACTICS
    /* 00000001 */ //

    // Each bit is an entry in the Librarian's enemy list, sequential
    /* 0x190 */ ENEMY_LIST_190 = 400,
    /* 10000000 */ // DRACULA_PROLOGUE
    /* 01000000 */ // BLOOD_SKELETON
    /* 00100000 */ // BAT
    /* 00010000 */ // STONE_SKULL
    /* 00001000 */ // ZOMBIE
    /* 00000100 */ // MERMAN_ORANGE
    /* 00000010 */ // SKELETON
    /* 00000001 */ // WARG

    /* 0x191 */ ENEMY_LIST_191 = 401,
    /* 10000000 */ // BONE_SCIMITAR
    /* 01000000 */ // MERMAN_RED
    /* 00100000 */ // SPITTLE_BONE
    /* 00010000 */ // AXE_KNIGHT_GREEN
    /* 00001000 */ // BLOODY_ZOMBIE
    /* 00000100 */ // SLINGER
    /* 00000010 */ // OUIJA_TABLE
    /* 00000001 */ // SKELERANG

    /* 0x192 */ ENEMY_LIST_192 = 402,
    /* 10000000 */ // THORNWEED
    /* 01000000 */ // GAIBON
    /* 00100000 */ // GHOST
    /* 00010000 */ // MARIONETTE
    /* 00001000 */ // SLOGRA
    /* 00000100 */ // DIPLOCEPHALUS
    /* 00000010 */ // FLEA_MAN
    /* 00000001 */ // MEDUSA_HEAD_BLUE

    /* 0x193 */ ENEMY_LIST_193 = 403,
    /* 10000000 */ // BLADE_SOLDIER
    /* 01000000 */ // BONE_MUSKET
    /* 00100000 */ // MEDUSA_HEAD_GOLD
    /* 00010000 */ // PLATE_LORD
    /* 00001000 */ // STONE_ROSE
    /* 00000100 */ // AXE_KNIGHT_BLUE
    /* 00000010 */ // CTULHU
    /* 00000001 */ // BONE_ARCHER

    /* 0x194 */ ENEMY_LIST_194 = 404,
    /* 10000000 */ // BONE_PILLAR
    /* 01000000 */ // DOPPLEGANGER10
    /* 00100000 */ // OWL
    /* 00010000 */ // PHANTOM_SKULL
    /* 00001000 */ // SCYLLA_WYRM
    /* 00000100 */ // SKELETON_APE
    /* 00000010 */ // SPEAR_GUARD
    /* 00000001 */ // SPELLBOOK

    /* 0x195 */ ENEMY_LIST_195 = 405,
    /* 10000000 */ // WINGED_GUARD
    /* 01000000 */ // ECTOPLASM_BLUE
    /* 00100000 */ // SWORD_LORD
    /* 00010000 */ // TOAD
    /* 00001000 */ // ARMOR_LORD
    /* 00000100 */ // CORNER_GUARD
    /* 00000010 */ // DHURON
    /* 00000001 */ // FROG

    /* 0x191 */ ENEMY_LIST_196 = 406,
    /* 10000000 */ // FROZEN_SHADE
    /* 01000000 */ // MAGIC_TOME
    /* 00100000 */ // SKULL_LORD
    /* 00010000 */ // BLACK_CROW
    /* 00001000 */ // BLUE_RAVEN
    /* 00000100 */ // CORPSEWEED
    /* 00000010 */ // FLAIL_GUARD
    /* 00000001 */ // FLEA_RIDER

    /* 0x197 */ ENEMY_LIST_197 = 407,
    /* 10000000 */ // SPECTRAL_SWORD_1 // Has multiple different weapons
    /* 01000000 */ // BONE_HALBERD
    /* 00100000 */ // SCYLLA
    /* 00010000 */ // HUNTING_GIRL
    /* 00001000 */ // MUDMAN
    /* 00000100 */ // OWL_KNIGHT
    /* 00000010 */ // SPECTRAL_SWORD_2 // Has all swords
    /* 00000001 */ // VANDAL_SWORD

    /* 0x198 */ ENEMY_LIST_198 = 408,
    /* 10000000 */ // FLEA_ARMOR
    /* 01000000 */ // HIPPOGRYPH
    /* 00100000 */ // PARANTHROPUS
    /* 00010000 */ // SLIME
    /* 00001000 */ // BLADE_MASTER
    /* 00000100 */ // WERESKELETON
    /* 00000010 */ // GRAVE_KEEPER
    /* 00000001 */ // GREMLIN

    /* 0x199 */ ENEMY_LIST_199 = 409,
    /* 10000000 */ // HARPY
    /* 01000000 */ // MINOTAURUS
    /* 00100000 */ // WEREWOLF
    /* 00010000 */ // BONE_ARK
    /* 00001000 */ // VALHALLA_KNIGHT
    /* 00000100 */ // CLOAKED_KNIGHT
    /* 00000010 */ // FISHHEAD
    /* 00000001 */ // LESSER_DEMON

    /* 0x19A */ ENEMY_LIST_19A = 410,
    /* 10000000 */ // LOSSOTH
    /* 01000000 */ // SALEM_WITCH
    /* 00100000 */ // BLADE
    /* 00010000 */ // GURKHA
    /* 00001000 */ // HAMMER
    /* 00000100 */ // DISCUS_LORD
    /* 00000010 */ // KARASUMAN
    /* 00000001 */ // LARGE_SLIME

    /* 0x19B */ ENEMY_LIST_19B = 411,
    /* 10000000 */ // HELLFIRE_BEAST
    /* 01000000 */ // CERBEROS // It is spelled Cerberus for tactics
    /* 00100000 */ // KILLER_FISH
    /* 00010000 */ // OLROX
    /* 00001000 */ // SUCCUBUS
    /* 00000100 */ // TOMBSTONE
    /* 00000010 */ // VENUS_WEED
    /* 00000001 */ // LION

    /* 0x19C */ ENEMY_LIST_19C = 412,
    /* 10000000 */ // SCARECROW
    /* 01000000 */ // GRANFALOON
    /* 00100000 */ // SCHMOO
    /* 00010000 */ // TIN_MAN
    /* 00001000 */ // BALLOON_POD
    /* 00000100 */ // YORICK
    /* 00000010 */ // BOMB_KNIGHT
    /* 00000001 */ // FLYING_ZOMBIE

    /* 0x19D */ ENEMY_LIST_19D = 413,
    /* 10000000 */ // BITTERFLY
    /* 01000000 */ // JACK_O_BONES
    /* 00100000 */ // ARCHER
    /* 00010000 */ // WEREWOLF
    /* 00001000 */ // BLACK_PANTHER
    /* 00000100 */ // DARKWING_BAT
    /* 00000010 */ // DRAGON_RIDER
    /* 00000001 */ // MINOTAUR

    /* 0x19E */ ENEMY_LIST_19E = 414,
    /* 10000000 */ // NOVA_SKELETON
    /* 01000000 */ // OROBOUROUS
    /* 00100000 */ // WHITE_DRAGON
    /* 00010000 */ // FIRE_WARG
    /* 00001000 */ // ROCK_KNIGHT
    /* 00000100 */ // SNIPER_OF_GOTH
    /* 00000010 */ // SPECTRAL_SWORD_3 // Has shields and spears
    /* 00000001 */ // GHOST_DANCER

    /* 0x19F */ ENEMY_LIST_19F = 415,
    /* 10000000 */ // WARG_RIDER
    /* 01000000 */ // CAVE_TROLL
    /* 00100000 */ // DARK_OCTOPUS
    /* 00010000 */ // FIRE_DEMON
    /* 00001000 */ // GORGON
    /* 00000100 */ // MALACHI
    /* 00000010 */ // AKMODAN_ii
    /* 00000001 */ // BLUE_VENUS_WEED

    /* 0x1A0 */ ENEMY_LIST_1A0 = 416,
    /* 10000000 */ // DOPPLEGANGER40
    /* 01000000 */ // MEDUSA
    /* 00100000 */ // THE_CREATURE
    /* 00010000 */ // FAKE_GRANT
    /* 00001000 */ // FAKE_TREVOR
    /* 00000100 */ // IMP
    /* 00000010 */ // FAKE_SYPHA
    /* 00000001 */ // BEEZELBUB

    /* 0x1A1 */ ENEMY_LIST_1A1 = 417,
    /* 10000000 */ // AZAGHAL
    /* 01000000 */ // FROZEN_HALF
    /* 00100000 */ // SALOME
    /* 00010000 */ // RICHTER_BELMONT
    /* 00001000 */ // DODO_BIRD
    /* 00000100 */ // GALAMOTH
    /* 00000010 */ // GUARDIAN
    /* 00000001 */ // DEATH

    /* 0x1A2 */ ENEMY_LIST_1A2 = 418,
    /* 10000000 */ // SHAFT
    /* 01000000 */ // DRACULA_FINALE

    // Each bit corresponds to the rare drop of each enemy in the enemy list,
    // sequentially Each enemy has an entry, even if the item is "NONE", only
    // the first two bits
    /* 0x1B0 */ ENEMY_LIST_RAREDROP_1B0 = 432,
    /* 10000000 */ // DRACULA_PROLOGUE_NONE
    /* 01000000 */ // BLOOD_SKELETON_NONE
    /* 00100000 */ // BAT_MONSTER_VIAL_2
    /* 00010000 */ // STONE_SKULL_NONE
    /* 00001000 */ // ZOMBIE_CLOTH_TUNIC
    /* 00000100 */ // MERMAN_ORANGE_MONSTER_VIAL_1
    /* 00000010 */ // SKELETON_MONSTER_VIAL_3
    /* 00000001 */ // WARG_NONE

    /* 0x1B1 */ ENEMY_LIST_RAREDROP_1B1 = 433,
    /* 10000000 */ // BONE_SCIMITAR_RED_RUST
    /* 01000000 */ // MERMAN_RED_MONSTER_VIAL_1
    /* 00100000 */ // SPITTLE_BONE_NONE
    /* 00010000 */ // AXE_KNIGHT_GREEN_BRONZE_CUIRASS
    /* 00001000 */ // BLOODY_ZOMBIE_BASILARD
    /* 00000100 */ // SLINGER_KNIGHT_SHIELD
    /* 00000010 */ // OUIJA_TABLE_MORNING_SET
    /* 00000001 */ // SKELERANG_FIRE_BOOMERANG

    /* 0x1B2 */ ENEMY_LIST_RAREDROP_1B2 = 434,
    /* 10000000 */ // THORNWEED_STRAWBERRY
    /* 01000000 */ // GAIBON_NONE
    /* 00100000 */ // GHOST_ANTIVENOM
    /* 00010000 */ // MARIONETTE_CIRCLET
    /* 00001000 */ // SLOGRA_NONE
    /* 00000100 */ // DIPLOCEPHALUS_TART
    /* 00000010 */ // FLEA_MAN_CHEESE
    /* 00000001 */ // MEDUSA_HEAD_BLUE_MEDUSA_SHIEL;D

    /* 0x1B3 */ ENEMY_LIST_RAREDROP_1B3 = 435,
    /* 10000000 */ // BLADE_SOLDIER_NAMAKURA
    /* 01000000 */ // BONE_MUSKET_TALISMAN
    /* 00100000 */ // MEDUSA_HEAD_GOLD_MEDUSA_SHIEL;D
    /* 00010000 */ // PLATE_LORD_NEUTRON_BOMB
    /* 00001000 */ // STONE_ROSE_MEAL_TICKET
    /* 00000100 */ // AXE_KNIGHT_BLUE_AXELORD_SHIELD
    /* 00000010 */ // CTULHU_BAT_PENTAGRAM
    /* 00000001 */ // BONE_ARCHER_MAGIC_MISSILE

    /* 0x1B4 */ ENEMY_LIST_RAREDROP_1B4 = 436,
    /* 10000000 */ // BONE_PILLAR_BALLROOM_MASK
    /* 01000000 */ // DOPPLEGANGER10_NONE
    /* 00100000 */ // OWL_NONE
    /* 00010000 */ // PHANTOM_SKULL_RESIST_DARK
    /* 00001000 */ // SCYLLA_WYRM_NONE
    /* 00000100 */ // SKELETON_APE_TNT
    /* 00000010 */ // SPEAR_GUARD_IRON_CUIRASS
    /* 00000001 */ // SPELLBOOK_PENTAGRAM

    /* 0x1B5 */ ENEMY_LIST_RAREDROP_1B5 = 437,
    /* 10000000 */ // WINGED_GUARD_JAVELIN
    /* 01000000 */ // ECTOPLASM_BLUE_MANNA_PRISM
    /* 00100000 */ // SWORD_LORD_BEKATOWA
    /* 00010000 */ // TOAD_PIZZA
    /* 00001000 */ // ARMOR_LORD_SABER
    /* 00000100 */ // CORNER_GUARD_DAMASCUS_SWORD
    /* 00000010 */ // DHURON_RAPIER
    /* 00000001 */ // FROG_PIZZA

    /* 0x1B1 */ ENEMY_LIST_RAREDROP_1B6 = 438,
    /* 10000000 */ // FROZEN_SHADE_ICE_CREAM
    /* 01000000 */ // MAGIC_TOME_SABER
    /* 00100000 */ // SKULL_LORD_SKULL_SHIELD
    /* 00010000 */ // BLACK_CROW_RED_BEAN_BUN
    /* 00001000 */ // BLUE_RAVEN_PORK_BUN
    /* 00000100 */ // CORPSEWEED_POTION
    /* 00000010 */ // FLAIL_GUARD_POT_ROAST
    /* 00000001 */ // FLEA_RIDER_HAM_AND_EGGS

    /* 0x1B7 */ ENEMY_LIST_RAREDROP_1B7 = 439,
    /* 10000000 */ // SPECTRAL_SWORD_1_BASTARD_SWORD
    /* 01000000 */ // BONE_HALBERD_HAM_AND_EGGS
    /* 00100000 */ // SCYLLA_NONE
    /* 00010000 */ // HUNTING_GIRL_CHEESECAKE
    /* 00001000 */ // MUDMAN_NONE
    /* 00000100 */ // OWL_KNIGHT_MEDAL
    /* 00000010 */ // SPECTRAL_SWORD_2_BASTARD_SWORD
    /* 00000001 */ // VANDAL_SWORD_MURAMASA

    /* 0x1B8 */ ENEMY_LIST_RAREDROP_1B8 = 440,
    /* 10000000 */ // FLEA_ARMOR_IRON_CUIRASS
    /* 01000000 */ // HIPPOGRYPH_NONE
    /* 00100000 */ // PARANTHROPUS_RING_OF_VARDA
    /* 00010000 */ // SLIME_NONE
    /* 00001000 */ // BLADE_MASTER_CROSS_SHURIKEN
    /* 00000100 */ // WERESKELETON_GARNET
    /* 00000010 */ // GRAVE_KEEPER_NATOU
    /* 00000001 */ // GREMLIN_FIRE_MAIL

    /* 0x1B9 */ ENEMY_LIST_RAREDROP_1B9 = 441,
    /* 10000000 */ // HARPY_LIFE_APPLE
    /* 01000000 */ // MINOTAURUS_NONE
    /* 00100000 */ // WEREWOLF_NONE
    /* 00010000 */ // BONE_ARK_SKULL_SHIELD
    /* 00001000 */ // VALHALLA_KNIGHT_CLAYMORE
    /* 00000100 */ // CLOAKED_KNIGHT_HEAVEN_SWORD
    /* 00000010 */ // FISHHEAD_ICEBRAND
    /* 00000001 */ // LESSER_DEMON_HOLBEIN_DAGGER

    /* 0x1BA */ ENEMY_LIST_RAREDROP_1BA = 442,
    /* 10000000 */ // LOSSOTH_FIREBRAND
    /* 01000000 */ // SALEM_WITCH_SHORTCAKE
    /* 00100000 */ // BLADE_GOLD_PLATE
    /* 00010000 */ // GURKHA_GOLD_PLATE
    /* 00001000 */ // HAMMER_GOLD_PLATE
    /* 00000100 */ // DISCUS_LORD_JEWEL_SWORD
    /* 00000010 */ // KARASUMAN_RING_OF_FEANOR
    /* 00000001 */ // LARGE_SLIME_NONE

    /* 0x1BB */ ENEMY_LIST_RAREDROP_1BB = 443,
    /* 10000000 */ // HELLFIRE_BEAST_FIRE_MAIL
    /* 01000000 */ // CERBEROS_NONE
    /* 00100000 */ // KILLER_FISH_SUSHI
    /* 00010000 */ // OLROX_NONE
    /* 00001000 */ // SUCCUBUS_NONE
    /* 00000100 */ // TOMBSTONE_GREEN_TEA
    /* 00000010 */ // VENUS_WEED_HEART_REFRESH
    /* 00000001 */ // LION_FIST_OF_TULKAS

    /* 0x1BC */ ENEMY_LIST_RAREDROP_1BC = 444,
    /* 10000000 */ // SCARECROW_MURAMASA
    /* 01000000 */ // GRANFALOON_NONE
    /* 00100000 */ // SCHMOO_CRISSAEGRIM
    /* 00010000 */ // TIN_MAN_MOJO_MAIL
    /* 00001000 */ // BALLOON_POD_NONE
    /* 00000100 */ // YORICK_SKULL_SHIELD
    /* 00000010 */ // BOMB_KNIGHT_DYNAMITE
    /* 00000001 */ // FLYING_ZOMBIE_FRANKFURTER

    /* 0x1BD */ ENEMY_LIST_RAREDROP_1BD = 445,
    /* 10000000 */ // BITTERFLY_MYSTIC_PENDANT
    /* 01000000 */ // JACK_O_BONES_FLAME_STAR
    /* 00100000 */ // ARCHER_VORPAL_BLADE
    /* 00010000 */ // WEREWOLF_YASUTSUNA
    /* 00001000 */ // BLACK_PANTHER_MASAMUNE
    /* 00000100 */ // DARKWING_BAT_NONE
    /* 00000010 */ // DRAGON_RIDER_NONE
    /* 00000001 */ // MINOTAUR_FURY_PLATE

    /* 0x1BE */ ENEMY_LIST_RAREDROP_1BE = 446,
    /* 10000000 */ // NOVA_SKELETON_TERMINUS_EST
    /* 01000000 */ // OROBOUROUS_LAPIS_LAZULI
    /* 00100000 */ // WHITE_DRAGON_NONE
    /* 00010000 */ // FIRE_WARG_KARMA_COIN
    /* 00001000 */ // ROCK_KNIGHT_PLATINUM_MAIL
    /* 00000100 */ // SNIPER_OF_GOTH_BRILLIANT_MAIL
    /* 00000010 */ // SPECTRAL_SWORD_3_MABLUNG_SWORD
    /* 00000001 */ // GHOST_DANCER_STONE_MASK

    /* 0x1BF */ ENEMY_LIST_RAREDROP_1BF = 447,
    /* 10000000 */ // WARG_RIDER_NONE
    /* 01000000 */ // CAVE_TROLL_NAUGLAMIR
    /* 00100000 */ // DARK_OCTOPUS_GREEN_TEA
    /* 00010000 */ // FIRE_DEMON_MARSIL
    /* 00001000 */ // GORGON_STONE_SWORD
    /* 00000100 */ // MALACHI_DARK_ARMOR
    /* 00000010 */ // AKMODAN_ii_NONE
    /* 00000001 */ // BLUE_VENUS_WEED_HEART_REFRESH

    /* 0x1C0 */ ENEMY_LIST_RAREDROP_1C0 = 448,
    /* 10000000 */ // DOPPLEGANGER40_NONE
    /* 01000000 */ // MEDUSA_NONE
    /* 00100000 */ // THE_CREATURE_NONE
    /* 00010000 */ // FAKE_GRANT_NONE
    /* 00001000 */ // FAKE_TREVOR_NONE
    /* 00000100 */ // IMP_KING'S_STONE
    /* 00000010 */ // FAKE_SYPHA_NONE
    /* 00000001 */ // BEEZELBUB_NONE

    /* 0x1C1 */ ENEMY_LIST_RAREDROP_1C1 = 449,
    /* 10000000 */ // AZAGHAL_MOURNEBLADE
    /* 01000000 */ // FROZEN_HALF_OPAL_CIRCLET
    /* 00100000 */ // SALOME_MANNA_PRISM
    /* 00010000 */ // RICHTER_BELMONT_NONE
    /* 00001000 */ // DODO_BIRD_RUNESWORD
    /* 00000100 */ // GALAMOTH_NONE
    /* 00000010 */ // GUARDIAN_GOD'S_GARB
    /* 00000001 */ // DEATH_NONE

    /* 0x1C2 */ ENEMY_LIST_RAREDROP_1C2 = 450,
    /* 10000000 */ // SHAFT_NONE
    /* 01000000 */ // DRACULA_FINALE_NONE

    // TT_004 - Controls aspects of the sword familiar
    /* 0x1D0 */ SWORD_FAMILIAR = 464,
} CastleFlagOffsets;
