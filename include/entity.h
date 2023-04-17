/**
 * Custom Entity Subtypes
*/

#include "common.h"

typedef struct ET_LeftSecretRoomWall {
    /* 0x00 */ u16 timer;
    /* 0x02 */ s16 unk7E;
    /* 0x04 */ u8 unk80;
    /* 0x05 */ s8 unk81;
    /* 0x06 */ s16 unk82;
    /* 0x08 */ s16 unk84;
    /* 0x0A */ s16 unk86;
    /* 0x0C */ s16 unk88;
    /* 0x0E */ s16 unk8A;
    /* 0x10 */ s16 unk8C;
    /* 0x12 */ s16 unk8E;
    /* 0x14 */ s16 unk90;
    /* 0x16 */ s16 unk92;
    /* 0x18 */ s16 unk94;
} ET_EquipItemDrop;

typedef union {
        /* 0x7C */ ET_EquipItemDrop equipItemDrop;
        /* 0x7C */ // ET_whatever2 whatever2; ...
        /* 0x7C */ // ET_whatever3 whatever3; ...
        /* 0x7C */ char stub[0x40];
} Ext;