#include <game.h>

typedef enum {
    CSOP_END_CUTSCENE,
    CSOP_LINE_BREAK,
    CSOP_SET_SPEED,
    CSOP_SET_WAIT,
    CSOP_SCRIPT_UNKNOWN_4,
    CSOP_SET_PORTRAIT,
    CSOP_NEXT_DIALOG,
    CSOP_SET_POS,
    CSOP_CLOSE_DIALOG,
    CSOP_PLAY_SOUND,
    CSOP_WAIT_FOR_SOUND,
    CSOP_UNK_11,
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
    CSOP_SCRIPT_UNKNOWN_24,
} CutsceneOpcode;

#define script_half(x) (((x) & 0xFF0) >> 4), ((x) & 0xFF)
#define script_word(x) (x & 0xFF000) >> 12, (x & 0xFF00) >> 8, script_half(x)

#define END_CUTSCENE() CSOP_END_CUTSCENE
#define LINE_BREAK() CSOP_LINE_BREAK
#define SET_SPEED(x) CSOP_SET_SPEED, x
#define SET_WAIT(x) CSOP_SET_WAIT, x
#define SET_PORTRAIT(clut, side) CSOP_SET_PORTRAIT, clut, side
#define NEXT_DIALOG() CSOP_NEXT_DIALOG
#define SET_POS(x, y) CSOP_SET_POS, x, y
#define CLOSE_DIALOG() CSOP_CLOSE_DIALOG
#define PLAY_SOUND(id) CSOP_PLAY_SOUND, script_half(id)
#define WAIT_FOR_SOUND() CSOP_WAIT_FOR_SOUND
#define SCRIPT_UNKNOWN_11() CSOP_UNK_11
#define SET_END(x) CSOP_SET_END, script_word(x)
#define SCRIPT_UNKNOWN_14(x, y, z)                                             \
    CSOP_SCRIPT_UNKNOWN_14, script_word(x), script_word(y), script_word(z)
#define SCRIPT_UNKNOWN_15(x) CSOP_SCRIPT_UNKNOWN_15, script_word(x)
#define WAIT_FOR_FLAG(x) CSOP_WAIT_FOR_FLAG, x
#define SET_FLAG(x) CSOP_SET_FLAG, x
#define LOAD_PORTRAIT(addr, id) CSOP_LOAD_PORTRAIT, script_word(addr), id
#define SCRIPT_UNKNOWN_20(x) CSOP_SCRIPT_UNKNOWN_20, script_half(x)
