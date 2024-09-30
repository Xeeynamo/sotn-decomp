/** Unkstruct section:
 * These are to be merged later on
 */

typedef struct {
    /* 0x0 */ s32 x;
    /* 0x4 */ s32 y;
} Point32; // size = 0x8

typedef struct {
    /* 0x00 */ u8 vabid;
    /* 0x01 */ u8 prog;
    /* 0x02 */ u8 note;
    /* 0x03 */ s8 volume;
    /* 0x04 */ u8 mode;
    /* 0x05 */ u8 tone;
    /* 0x06 */ u8 unk6;
} Unkstruct_800BF554; // size = 0x7

#define MAKE_PAL_OP(kind, freq) ((kind) | ((freq) << 0x10))
#define GET_PAL_OP_KIND(x) (LOH(x))
#define GET_PAL_OP_FREQ(x) (HIH(x))

#define PAL_COPY 1
#define PAL_COPY_INFO() MAKE_PAL_OP(PAL_COPY, 0)
#define PAL_COPY_DATA(dst, data) (dst), (u_long*)LEN(data), (u_long*)(data)
#define PAL_COPY_DATA_(dst, data, len) (dst), (u_long*)(len), (u_long*)(data)

#define PAL_UNK_OP2 2
#define PAL_UNK_OP2_INFO(dst, n) (u_long*)(dst), (u_long*)(n)
#define PAL_UNK_OP2_DATA(data) (u_long*)(data)

#define PAL_UNK_OP3 3
#define PAL_UNK_OP3_INFO(dst, n) (u_long*)(dst), (u_long*)(n)
#define PAL_UNK_OP3_DATA(data) (u_long*)(data)

#define PAL_GLOW_ANIM 4
#define PAL_GLOW_INFO(dst, n) (u_long*)(dst), (u_long*)(n)
#define PAL_GLOW_DATA(data) (u_long*)(data)

#define PAL_BULK_COPY 5
#define PAL_BULK_COPY_INFO(dst, n) (u_long*)(dst), (u_long*)(n)
#define PAL_BULK(dst, data) (u_long*)(dst), (u_long*)LEN(data), (u_long*)(data)

#define PAL_TERMINATE() ((u_long*)-1)

typedef struct {
    /* 0x00 */ u_long* desc;
    /* 0x04 */ u_long* data;
    /* 0x08 */ u16 unk8; // anim mode?
    /* 0x0A */ u16 index;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u16 unkE;
    /* 0x10 */ u8 unkArray[0x30]; // color buffer
} Unkstruct_8006C3C4;             // size = 0x40

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
    /* 0x02 */ u16 sndVol;
    /* 0x04 */ s16 sndPan;
} SfxRingBufferItem;

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
    s32 unkC;
} Unkstruct_800FDB18;

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
    /* 0x0 */ s16 animSet;
    /* 0x2 */ s16 unk2; // Entity::unk5A
    /* 0x4 */ u16 palette;
    /* 0x6 */ s8 drawMode;
    /* 0x7 */ char pad_7;
    /* 0x8 */ s32 unk8;
} Unkstruct_80180FE0;

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
    u8 unk0[8];
    u8 unk8[8];
    u8 unk16[1];
    u8 pad3[5];
    u32 unk18;
} Unkstruct_800ADEF0;

typedef struct {
    u16 palette;
    u8 unk2;
} Unkstruct_800AE180;

typedef struct {
    /* 0x800973F8 */ s32 D_800973F8;
    /* 0x800973FC */ s32 D_800973FC;
    /* 0x80097400 */ bool pauseEnemies; // True for Stopwatch and cutscenes
    /* 0x80097404 */ s32 unk4;
    /* 0x80097408 */ s32 g_zEntityCenter;
    /* 0x8009740C */ s32 unkC;
    /* 0x80097410 */ s32 BottomCornerTextTimer;
    /* 0x80097414 */ s32 BottomCornerTextPrims;
    /* 0x80097418 */ s32 unk18;
    /* 0x8009741C */ s32 unk1C;
    /* 0x80097420 */ s32 unk20;
    /* 0x80097424 */ s32 unk24;

    // size must be 8 for the loop in RunMainEngine, while
    // PreventEntityFromRespawning suggests it has a size of 32
    /* 0x80097428 */ s32 D_80097428[8];
} unkGraphicsStruct;

typedef struct {
    /* 0x00 */ u8 count;
    /* 0x01 */ u8 r;
    /* 0x02 */ u8 g;
    /* 0x03 */ u8 b;
    /* 0x04 */ u8 w;
    /* 0x05 */ u8 h;
    /* 0x06 */ u16 priority;
    /* 0x08 */ u16 drawMode;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u32 flags;
} unkStr_8011E4BC; // size = 0x10

typedef struct {
    s32 : 32;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
} Unkstruct_8012BEF8; // size = 0x1C

typedef struct {
    u8 childId;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
} FactoryBlueprint;

typedef struct {
    s32 unk0;
    s16 unk4;
} unkstr_800cfe48; // for EntityAlucard

typedef struct {
    s16 flipX;
    s16 flipY;
    s16 clut;
    s16 unk3;
    s16 unk4;
    u8 r;
    u8 g;
    u8 b;
    u8 unused;
} Unkstruct_8017AAD8; // for w_046
