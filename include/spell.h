#ifndef SPELL_H
#define SPELL_H

#include "types.h"

#define SPELL_FLAG_KNOWN 0x80
typedef enum {
    SPELL_DARK_METAMORPHOSIS,
    SPELL_SUMMON_SPIRIT,
    SPELL_HELLFIRE,
    SPELL_TETRA_SPIRIT,
    SPELL_WOLF_CHARGE,
    SPELL_SOUL_STEAL,
    SPELL_WING_SMASH,
    SPELL_SWORD_BROTHERS,
    NUM_SPELLS,
} SpellIds;

typedef struct {
    /* 0x00 */ const char* name;
    /* 0x04 */ const char* combo;
    /* 0x08 */ const char* description;
    /* 0x0C */ u8 mpUsage;
    /* 0x0D */ s8 nFramesInvincibility;
    /* 0x0E */ s16 stunFrames;
    /* 0x10 */ s16 hitboxState;
    /* 0x12 */ s16 hitEffect;
    /* 0x14 */ s16 entityRoomIndex;
    /* 0x16 */ u16 attackElement;
    /* 0x18 */ s16 attack;
    /* 0x1A */ s16 unk1A;
} SpellDef;

#endif // SPELL_H
