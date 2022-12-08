#include "main.h"

/* Unkstruct section:
 * These are to be merged later on
 */

typedef struct unkstruct_80072FA0 {
    /* 0x00 */ char unk0[0x4];
    /* 0x04 */ u16 unk4;
    /* 0x08 */ char unk8[0x6];
} unkstruct_80072FA0; // size = 0xC

typedef struct unkStruct_800A872C {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ char unk4[0xC];
} unkStruct_800A872C; // size = 0x10

typedef struct Unkstruct_800ECE2C {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad8[0x30 - 0x8];
} Unkstruct_800ECE2C;

typedef struct Unkstruct_80137638 {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[0x1E - 0x02];
} Unkstruct_80137638; // size = 0x1E

typedef struct Unkstruct_800A4B12 {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ char unk1[0x34 - 0x1];
} Unkstruct_800A4B12;

typedef struct Unkstruct_80086FFA {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ char unk2[0x32];
} Unkstruct_80086FFA; // size = 0x34

typedef struct Unkstruct_80138094 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    char pad[12];
} Unkstruct_80138094;

typedef struct Unkstruct_80138FB4 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ char pad8[0x2E];
    /* 0x36 */ s16 unk36;
} Unkstruct_80138FB4; // size = unknown

typedef struct Unkstruct_80137990 {
    /* 0x00 */ s32 unk0;
} Unkstruct_80137990;