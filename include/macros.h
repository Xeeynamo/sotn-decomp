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
    UNK_ENTITY_10 = 0x10,
    UNK_ENTITY_13 = 0x13
} EntityTypes;

#define PLAYER g_EntityArray[PLAYER_CHARACTER]

#define SQ(x) ((x) * (x))
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define ABS_ALT(x) ((x) >= 0 ? (x) : -(x))
#define DECR(x) ((x) == 0 ? 0 : --(x))

#define CLAMP(x, min, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x))
#define CLAMP_MAX(x, max) ((x) > (max) ? (max) : (x))
#define CLAMP_MIN(x, min) ((x) < (min) ? (min) : (x))

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

#define FLAG_CHECK(entity, flag) (g_CastleFlags[entity] & flag)
#define FLAG_SET(entity, flag) (g_CastleFlags[entity] |= flag)
