typedef enum {
    PLAYER_CHARACTER,
    UNK_ENTITY_1,
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

#define PLAYER g_Entities[PLAYER_CHARACTER]
