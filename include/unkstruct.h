/** Unkstruct section:
 * These are to be merged later on
 */

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
} Point16; // size = 0x4

typedef struct {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
} Point32; // size = 0x8

typedef struct {
    /* 0x00 */ u8 vabid;
    /* 0x01 */ u8 prog;
    /* 0x02 */ u8 note;
    /* 0x03 */ s8 volume;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 tone;
    /* 0x06 */ u8 unk6;
} Unkstruct_800BF554; // size = 0x7

typedef struct {
    /* 0x00 */ f32 posX;
    /* 0x04 */ f32 posY;
    /* 0x08 */ char pad8[0xC];
} Unkstruct_80138094; // size = 0x14

typedef struct {
    /* 0x00 */ s32 unk0;
} Unkstruct_80137990;

typedef struct {
    struct UnkStructClut* struct1;
    struct UnkStructClut* struct2;
    u16 unk8;
    u16 unkA;
    u16 unkC;
    u16 unkE;
    u8 unkArray[0x30];
} Unkstruct_8006C3C4; // size = 0x40

typedef struct {
    s16 unk0;
    s16 unk2;
} s16_pair;

typedef struct {
    /* 0x00 */ s16_pair pairs[4];
    /* 0x08 */ char pad12[0x8];
    /* 0x10 */ s16 unk1A; /* D_800ACEE0 */
    /* 0x12 */ s16 unk1C; /* D_800ACEE2 */
} Unkstruct_800ACED0;

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
    /* 0x00 */ s16 sndId;
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

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
} Unkstruct_800EA5E4;

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
    u16 start;
    s16 current;
    s16* coords;
    s16 unk8;
} Unkstruct_80102CD8;

typedef struct {
    s16 unk0;
    u8 unk2;
    u8 unk3;
} unkstruct_800ACF7C;

typedef struct {
    /* 0x0 */ s16 animSet;
    /* 0x2 */ s16 unk2; // Entity::unk5A
    /* 0x4 */ u16 palette;
    /* 0x6 */ s8 blendMode;
    /* 0x7 */ char pad_7;
    /* 0x8 */ s32 unk8;
} Unkstruct_80180FE0;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} UnkStructClut;

typedef struct Unkstruct_801C7954 {
    /* 0x00 */ u16 x1;
    /* 0x02 */ u16 x0;
    /* 0x04 */ u16 y2;
    /* 0x06 */ u16 y0;
    /* 0x08 */ u16 y3;
    /* 0x0A */ u16 y1;
    /* 0x0C */ u16 x3;
    /* 0x0E */ u16 x2;
} Unkstruct_801C7954; // size = 0x10

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} unk_800B08CC; // size = 0xC

typedef struct {
    Multi g_zEntityCenter;
    byte pad[0x1A];
    s32 D_8009742C[8];
} unkGraphicsStruct;

typedef struct {
    u8 count;
    u8 r;
    u8 g;
    u8 b;
    u8 w;
    u8 h;
    u16 priority;
    u16 blendMode;
    s16 unkA;
    u32 flags;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
} unkStr_8011E4BC;

typedef struct FakePrim {
    struct FakePrim* next;
    /* 0x04 */ u8 r0;
    /* 0x05 */ u8 g0;
    /* 0x06 */ u8 b0;
    /* 0x07 */ u8 type; // PrimitiveType
    /* 0x08 */ s16 x0;
    /* 0x0A */ s16 y0;
    /* 0x0C */ u8 w;
    /* 0x0D */ u8 h;
    /* 0x0E */ u16 clut;
    /* 0x10 */ f32 posX;
    /* 0x14 */ f32 posY;
    /* 0x18 */ f32 velocityX;
    /* 0x1C */ f32 velocityY;
    /* 0x20 */ s16 x2;
    /* 0x22 */ s16 y2;
    /* 0x24 */ s16 delay;
    /* 0x26 */ u16 priority;
    /* 0x28 */ f32 accelerationX;
    /* 0x2C */ f32 accelerationY;
    s16 timer;
    /* 0x32 */ u16 blendMode;
} FakePrim;

typedef struct {
    u8 childId;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
} FactoryBlueprint;