#ifndef FAMILIAR_H
#define FAMILIAR_H

typedef enum { STAT_STR, STAT_CON, STAT_INT, STAT_LCK } Stats;
typedef struct {
    s32 level;
    s32 exp;
    s32 unk8;
} FamiliarStats;

// Need two familiar enums. One has a zero entry, one does not.
// This one is used in places that need to access the familiar
// stats array...
typedef enum {
    FAM_STATS_BAT,
    FAM_STATS_GHOST,
    FAM_STATS_FAERIE,
    FAM_STATS_DEMON,
    FAM_STATS_SWORD,
    FAM_STATS_YOUSEI,     // JP only
    FAM_STATS_NOSE_DEMON, // JP only
    NUM_FAMILIARS
} FamiliarStatsIds;

// ...and this one is used to designate the active familiar, where
// 0 means no familiar is active, and the rest are off-by-one from
// the previous enum set. Hacky, but works.
typedef enum {
    FAM_ACTIVE_NONE,
    FAM_ACTIVE_BAT = FAM_STATS_BAT + 1,
    FAM_ACTIVE_GHOST = FAM_STATS_GHOST + 1,
    FAM_ACTIVE_FAERIE = FAM_STATS_FAERIE + 1,
    FAM_ACTIVE_DEMON = FAM_STATS_DEMON + 1,
    FAM_ACTIVE_SWORD = FAM_STATS_SWORD + 1,
    FAM_ACTIVE_YOUSEI = FAM_STATS_YOUSEI + 1,
    FAM_ACTIVE_NOSE_DEMON = FAM_STATS_NOSE_DEMON + 1,
} FamiliarActiveIds;

#endif // FAMILILAR_H
