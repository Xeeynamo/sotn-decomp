/** Unkstruct section:
 * These are to be merged later on
 */

typedef struct {
    /* 0x0 */ char pad0[0xA];
    /* 0xA */ s16 unkA;
    /* 0xC */ s16 unkC;
    /* 0xE */ s16 unkE;
} Unkstruct4; // size = 0x10

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
} Point16; // size = 0x4

typedef struct {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
} Point32; // size = 0x8

typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 unk2;
} Unsktruct_800EAF28; // size = 0x4

typedef struct {
    /* 0x0 */ Unsktruct_800EAF28* unk0;
    /* 0x4 */ u16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 unk8;
    /* 0xA */ s16 unkA;
} unkstruct_80072FA0; // size = 0xC

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ char unk4[0xC];
} unkStruct_800A872C; // size = 0x10

typedef struct {
    /* 0x00 */ u16* fg;
    /* 0x04 */ u16* bg;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ char pad_10[0x30];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
} Unkstruct8; // size = unknown

typedef struct {
    /* 0x00 */ u8 unk0[0x278];
} Unkstruct_8013B160; // size = 0x278

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[0x1E - 0x02];
} Unkstruct_80137638; // size = 0x1E

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ char pad2[0x32];
} Unkstruct_80086FFA; // size = 0x34

typedef struct {
    /* 0x00 */ u8 vabid;
    /* 0x01 */ u8 prog;
    /* 0x02 */ u8 note;
    /* 0x03 */ s8 volume;
    /* 0x04 */ u8 pad0;
    /* 0x05 */ u8 tone;
    /* 0x06 */ u8 pad1;
} Unkstruct_800BF554; // size = 0x7

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ char pad8[0xC];
} Unkstruct_80138094; // size = 0x14

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ char pad8[0x2E];
    /* 0x36 */ s16 unk36;
} Unkstruct_80138FB4; // size = unknown

typedef struct {
    /* 0x00 */ s32 unk0;
} Unkstruct_80137990;

typedef struct {
    /* 0x000 */ s32 unk000;
    /* 0x004 */ char pad004[0x274];
} Unkstruct_8013B15C; // size = 0x278

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u16 unk16;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u16 unk1C;
    /* 0x2E */ u16 unk1E;
    /* 0x20 */ u16 unk20;
    /* 0x22 */ u16 unk22;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ u16 unk26;
    /* 0x28 */ u16 unk28;
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ char padA[0x10];
} Unkstruct_8006C3CC; // size = 0x40

typedef struct {
    /* 0x00 */ s16 unk0; /* D_800ACEC6 */
    /* 0x02 */ char pad2[0xE];
    /* 0x10 */ s16 unk10; /* D_800ACED6 */
    /* 0x12 */ char pad12[0x8];
    /* 0x1A */ s16 unk1A; /* D_800ACEE0 */
    /* 0x1C */ s16 unk1C; /* D_800ACEE2 */
} Unkstruct_800ACEC6;

// Used in:
// func_8015E7B4
// func_8010BF64
typedef struct {
    /* 0x00 */ char pad0[0x14];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
} Unkstruct_8010BF64;

// related to SFX
typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ s16 unk04;
} SfxRingBufferItem;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} Unkstruct_800FD5BC;

typedef struct {
    /* 0x00 */ u8 unk00[3];
    /* 0x03 */ char unk03[9];
} Unkstruct_80128BBC_Sub;

typedef struct Unkstruct_80128BBC {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ Unkstruct_80128BBC_Sub unk04[4];
} Unkstruct_80128BBC;

typedef struct Unkstruct_aSimCBinDemoKey {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s8 unk4;
    /* 0x05 */ char pad5[0x3];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
} Unkstruct_aSimCBinDemoKey;

typedef struct Unkstruct_800A2D98 {
    /* 0x0 */ s32 equipTypeFilter;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} Unkstruct_800A2D98;

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
} Unkstruct_800EA5E4;

typedef struct Unkstruct_800A7734 {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ char unk02[0x1E];
} Unkstruct_800A7734; // size = 0x20

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Unkstruct_8011A3AC;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Unkstruct_800FDB18;

typedef struct Unkstruct_801C3F9C {
    /* 0x00 */ char pad0[0xA];
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ char pad16[0x8];
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ char pad20[0x4];
    /* 0x24 */ u8 unk24;
    /* 0x25 */ char pad25[0x7];
    /* 0x2C */ s16 unk2C;
} Unkstruct_801C3F9C;

typedef struct {
    u16 D_800A37D8;
    u16 D_800A37DA;
} Unkstruct_801092E8;

typedef struct {
    s32 D_8003C908;
    s32 D_8003C90C;
    s32 D_8003C910;
} Unkstruct_8003C908;

typedef struct Unkstruct_801C6C6C {
    union {
        struct {
            u16 w;
            u16 x;
        } c;
        s32 p;
    } x;
    union {
        struct {
            u16 h;
            u16 y;
        } c;
        s32 p;
    } y;
} Unkstruct_801C6C6C;

typedef struct {
    s16 x, y;
} Unkstruct_80138FC0;

// Somehow related to how Player sprites are stored in the VRAM
typedef struct {
    s16 unk00, unk02;
    u16 unk04, unk06;
    u16 unk08, unk0A;
    u16 unk0c, unk0E;
    u16 unk10, unk12;
    u16 unk14, unk16;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
    u8 unk20;
    u8 unk21;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 unk25;
    u8 unk26;
    u8 unk27;
} Unkstruct_800ECBF8_1; /* size = 0x28 */

typedef struct {
    u16 start;
    s16 current;
    s16* coords;
    s16 unk8;
} Unkstruct_80102CD8;

typedef struct {
    /* 0x0 */ s16 animSet;
    /* 0x2 */ s16 unk2; // Entity::unk5A
    /* 0x4 */ u16 palette;
    /* 0x6 */ s8 blendMode;
    /* 0x7 */ char pad_7;
    /* 0x8 */ s32 unk8;
} Unkstruct_80180FE0;
