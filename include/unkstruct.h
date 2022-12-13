#include "main.h"

/* Unkstruct section:
 * These are to be merged later on
 */

typedef struct unkstruct_80072FA0 {
    /* 0x00 */ char pad0[0x4];
    /* 0x04 */ u16 unk4;
    /* 0x08 */ char pad8[0x6];
} unkstruct_80072FA0; // size = 0xC

typedef struct unkStruct_800A872C {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ char unk4[0xC];
} unkStruct_800A872C; // size = 0x10

typedef struct Unkstruct_800ECE2C {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ char pad8[0x28];
} Unkstruct_800ECE2C; // size = 0x30

typedef struct Unkstruct_80137638 {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[0x1E - 0x02];
} Unkstruct_80137638; // size = 0x1E

typedef struct Unkstruct_800A4B12 {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ char pad1[0x33];
} Unkstruct_800A4B12; // size = 0x34

typedef struct Unkstruct_80086FFA {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ char pad2[0x32];
} Unkstruct_80086FFA; // size = 0x34

typedef struct Unkstruct_80138094 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ char pad8[0xC];
} Unkstruct_80138094; // size = 0x14

typedef struct Unkstruct_80138FB4 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ char pad8[0x2E];
    /* 0x36 */ s16 unk36;
} Unkstruct_80138FB4; // size = unknown

typedef struct Unkstruct_80137990 {
    /* 0x00 */ s32 unk0;
} Unkstruct_80137990;

typedef struct Unkstruct_8013B15C {
    /* 0x000 */ s32 unk000;
    /* 0x004 */ char pad004[0x274];
} Unkstruct_8013B15C; // size = 0x278

typedef struct Unkstruct_8006C3CC {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ char pad2[0x6];
    /* 0x8 */ u16 unk8;
    /* 0xA */ char padA[0x36];
} Unkstruct_8006C3CC; // size = 0x40

typedef struct Unkstruct_8011A290 {
    /* 0x00 */ u16 sp10;
    /* 0x02 */ char pad2[0x2];
    /* 0x04 */ u16 sp14;
    /* 0x06 */ char pad6[0x1];
    /* 0x07 */ u8 sp17;
    /* 0x08 */ u16 sp18;
    /* 0x0A */ char padA[0x2];
    /* 0x0C */ u16 sp1C;
    /* 0x0E */ u16 sp1E;
    /* 0x10 */ u8 sp20;
    /* 0x11 */ char pad11[0x1];
    /* 0x12 */ u16 sp22;
} Unkstruct_8011A290;

typedef struct {
    /* 0x00 */ s32 sp10;
    /* 0x04 */ s32 sp14;
    /* 0x08 */ s32 sp18;
    /* 0x0C */ s32 sp1C;
    /* 0x10 */ s32 sp20;
    /* 0x14 */ s16 sp24;
    /* 0x18 */ s16 sp26;
    /* 0x1C */ s16 sp28;
    /* 0x20 */ s16 sp2A;
    /* 0x24 */ s32 sp2C;
    /* 0x28 */ s32 sp30;
} Unkstruct7; // size = 0x2C

typedef struct Unkstruct_8011A328 {
    /* 0x00 */ char pad0[0xD];
    /* 0x0D */ s8 sp1D;
    /* 0x0E */ s16 sp1E;
    /* 0x10 */ s16 sp20;
    /* 0x12 */ s16 sp22;
    /* 0x14 */ s16 sp24;
    /* 0x16 */ s16 sp26;
    /* 0x18 */ s16 sp28;
} Unkstruct_8011A328;