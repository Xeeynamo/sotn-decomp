#ifndef RELIC_H
#define RELIC_H

#include <types.h>

#define RELIC_FLAG_DISABLE 0
#define RELIC_FLAG_FOUND 1
#define RELIC_FLAG_ACTIVE 2
#if defined(VERSION_US)
#define NUM_AVAIL_RELICS (NUM_RELICS - 2)
#elif defined(VERSION_HD)
#define NUM_AVAIL_RELICS (NUM_RELICS)
#endif
typedef enum {
    RELIC_SOUL_OF_BAT,
    RELIC_FIRE_OF_BAT,
    RELIC_ECHO_OF_BAT,
    RELIC_FORCE_OF_ECHO,
    RELIC_SOUL_OF_WOLF,
    RELIC_POWER_OF_WOLF,
    RELIC_SKILL_OF_WOLF,
    RELIC_FORM_OF_MIST,
    RELIC_POWER_OF_MIST,
    RELIC_GAS_CLOUD,
    RELIC_CUBE_OF_ZOE,
    RELIC_SPIRIT_ORB,
    RELIC_GRAVITY_BOOTS,
    RELIC_LEAP_STONE,
    RELIC_HOLY_SYMBOL,
    RELIC_FAERIE_SCROLL,
    RELIC_JEWEL_OF_OPEN,
    RELIC_MERMAN_STATUE,
    RELIC_BAT_CARD,
    RELIC_GHOST_CARD,
    RELIC_FAERIE_CARD,
    RELIC_DEMON_CARD,    // 0x097979
    RELIC_SWORD_CARD,    // 0x09797A
    RELIC_JP_0,          // 0x09797B (nose demon or half fairy)
    RELIC_JP_1,          // 0x09797C
    RELIC_HEART_OF_VLAD, // 0x09797D
    RELIC_TOOTH_OF_VLAD,
    RELIC_RIB_OF_VLAD,
    RELIC_RING_OF_VLAD,
    RELIC_EYE_OF_VLAD,
    NUM_RELICS,
} RelicIds;

typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ const char* desc;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ s32 unk0C;
} RelicDesc; /* size=0x10 */

typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ const char* desc;
    /* 0x08 */ u16 icon;
    /* 0x0A */ u16 iconPalette;
#ifndef VERSION_BETA
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
#endif
} RelicOrb; /* size=0x10 */

#endif // RELIC_H
