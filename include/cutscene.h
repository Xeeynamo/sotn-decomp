#ifndef CUTSCENE_H
#define CUTSCENE_H

typedef enum {
    CSOP_END_CUTSCENE,
    CSOP_LINE_BREAK,
    CSOP_SET_SPEED,
    CSOP_SET_WAIT,
    CSOP_HIDE_DIALOG,
    CSOP_SET_PORTRAIT,
    CSOP_NEXT_DIALOG,
    CSOP_SET_POS,
    CSOP_CLOSE_DIALOG,
    CSOP_PLAY_SOUND,
    CSOP_WAIT_FOR_SOUND,
    CSOP_SCRIPT_UNKNOWN_11,
    CSOP_SET_END,
    CSOP_SCRIPT_UNKNOWN_13,
    CSOP_SCRIPT_UNKNOWN_14,
    CSOP_SCRIPT_UNKNOWN_15,
    CSOP_WAIT_FOR_FLAG,
    CSOP_SET_FLAG,
    CSOP_SCRIPT_UNKNOWN_18,
    CSOP_LOAD_PORTRAIT,
    CSOP_SCRIPT_UNKNOWN_20,
    CSOP_SCRIPT_UNKNOWN_21,
    CSOP_SCRIPT_UNKNOWN_22,
    CSOP_SCRIPT_UNKNOWN_23,
    CSOP_WAIT_FOR_FLAG_RESET,
} CutsceneOpcode;

#define CUTSCENE_FLAG_NONE 0

#define script_half(x) (((x) & 0xFF0) >> 4), ((x) & 0xFF)
#define script_word(x) (x & 0xFF000) >> 12, (x & 0xFF00) >> 8, script_half(x)

#define END_CUTSCENE() CSOP_END_CUTSCENE
#define LINE_BREAK() CSOP_LINE_BREAK
#define SET_SPEED(x) CSOP_SET_SPEED, x
#define SET_WAIT(x) CSOP_SET_WAIT, x
#define HIDE_DIALOG() CSOP_HIDE_DIALOG
#define SET_PORTRAIT(clut, side) CSOP_SET_PORTRAIT, clut, side
#define NEXT_DIALOG() CSOP_NEXT_DIALOG
#define SET_POS(x, y) CSOP_SET_POS, x, y
#define CLOSE_DIALOG() CSOP_CLOSE_DIALOG
#define PLAY_SOUND(id) CSOP_PLAY_SOUND, script_half(id)
#define WAIT_FOR_SOUND() CSOP_WAIT_FOR_SOUND
#define SCRIPT_UNKNOWN_11() CSOP_SCRIPT_UNKNOWN_11
#define SET_END(x) CSOP_SET_END, script_word(x)
#define SCRIPT_UNKNOWN_14(x, y, z)                                             \
    CSOP_SCRIPT_UNKNOWN_14, script_word(x), script_word(y), script_word(z)
#define SCRIPT_UNKNOWN_15(x) CSOP_SCRIPT_UNKNOWN_15, script_word(x)
#define WAIT_FOR_FLAG(x) CSOP_WAIT_FOR_FLAG, x
#define SET_FLAG(x) CSOP_SET_FLAG, x
#define SCRIPT_UNKNOWN_18() CSOP_SCRIPT_UNKNOWN_18
#define LOAD_PORTRAIT(addr, id) CSOP_LOAD_PORTRAIT, script_word(addr), id
#define SCRIPT_UNKNOWN_20(x) CSOP_SCRIPT_UNKNOWN_20, script_half(x)
#define SCRIPT_UNKNOWN_21() CSOP_SCRIPT_UNKNOWN_21
#define SCRIPT_UNKNOWN_23() CSOP_SCRIPT_UNKNOWN_23
#define WAIT_FOR_FLAG_RESET(x) CSOP_WAIT_FOR_FLAG_RESET, x
#if defined(VERSION_PSP) || defined(VERSION_HD)
#define CS_LINE_SPACING 16
#define CS_LINE_MAX 3
#else
#define CS_LINE_SPACING 12
#define CS_LINE_MAX 4
#endif
#define ASCII_SPACE 32

typedef struct {
    /* 0x00 */ u8* scriptCur;         // ptr to dialogue next character
    /* 0x04 */ s16 startX;            // starting x coord
    /* 0x06 */ s16 nextLineY;         // next line y coord
    /* 0x08 */ s16 startY;            // starting y coord
    /* 0x0A */ s16 nextCharX;         // next char x coord
    /* 0x0C */ s16 nextLineX;         // next line x coord
    /* 0x0E */ s16 nextCharY;         // next char y coord
    /* 0x10 */ s16 portraitAnimTimer; // portrait animation timer
    /* 0x12 */ u16 unk12;             // unknown
    /* 0x14 */ u16 clutIndex;         // CLUT index
    /* 0x16 */ u8 nextCharTimer;      // timer to next character
    /* 0x17 */ u8 unk17;              // unknown
// Of course, offsets beyond here won't be right in ST0_WEIRD_DIALOGUE.
#if defined(VERSION_PSP) || defined(VERSION_HD)
    /* 0x18 */ Primitive* prim[5]; // for dialogue graphics rendering
#else
    /* 0x18 */ Primitive* prim[6]; // for dialogue graphics rendering
#endif
    /* 0x30 */ s32 primIndex[3]; // primIndices: unk, actorName, unk
    /* 0x3C */ u16 unk3C;        // maybe it is a begin flag?
    /* 0x3E */ u16 timer;        // global timer
    /* 0x40 */ u8* scriptEnd;    // pointer to the end of the script
} Dialogue;                      // size = 0x44

// no4/cutscene
typedef struct {
    /* 0x00 */ u8* scriptCur;         // ptr to dialogue next character
    /* 0x04 */ s16 nextCharX;         // starting x coord
    /* 0x06 */ s16 nextCharY;         // next char y coord
    /* 0x08 */ s16 portraitAnimTimer; // portrait animation timer
    /* 0x0A */ u8 nextCharTimer;
    /* 0x0B */ u8 unk17;
    // Of course, offsets beyond here won't be right on PSP
#if defined(VERSION_PSP)
    /* 0x0C */ Primitive* prim[5]; // for dialogue graphics rendering
    /* 0x20 */ s32 nextLineX;
#else
    /* 0x0C */ Primitive* prim[4]; // for dialogue graphics rendering
#endif
    /* 0x1C */ s32 primIndex[3]; // primIndices: unk, actorName, unk
    /* 0x30 */ s16 startX;
    /* 0x32 */ s16 nextLineY;
    /* 0x34 */ s16 startY;
    /* 0x36 */ u16 clutIndex;
    /* 0x38 */ u16 unk12;
    /* 0x3A */ s16 : 16;
    /* 0x3C */ u16 unk3C;
} Dialogue3; // size = 0x28

// sel_psp/cutscene.c
typedef struct {
    /* 0x00 */ u8* scriptCur;         // ptr to dialogue next character
    /* 0x04 */ s16 startX;            // starting x coord
    /* 0x06 */ s16 nextLineY;         // next line y coord
    /* 0x08 */ s16 startY;            // starting y coord
    /* 0x0A */ s16 nextCharX;         // next char x coord
    /* 0x0C */ s16 nextLineX;         // next line x coord
    /* 0x0E */ u16 nextCharY;         // next char y coord
    /* 0x10 */ u16 portraitAnimTimer; // portrait animation timer
    /* 0x12 */ u16 unk12;             // unknown
    /* 0x14 */ u16 clutIndex;         // CLUT index
    /* 0x16 */ u16 nextCharTimer;     // timer to next character
    /* 0x18 */ Primitive* prim;       // for dialogue graphics rendering
    /* 0x1C */ s32 primIndex;         // primIndex: unk
} Dialogue4;                          // size = 0x20

#endif // CUTSCENE_H
