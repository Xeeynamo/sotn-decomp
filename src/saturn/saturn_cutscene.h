// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_CUTSCENE_H
#define SATURN_CUTSCENE_H

typedef enum {
    SATURN_CSOP_END_CUTSCENE,
    SATURN_CSOP_LINE_BREAK,
    SATURN_CSOP_SET_SPEED,
    SATURN_CSOP_SET_WAIT,
    SATURN_CSOP_HIDE_DIALOG,
    SATURN_CSOP_SET_PORTRAIT,
    SATURN_CSOP_NEXT_DIALOG,
    SATURN_CSOP_SET_POS,
    SATURN_CSOP_CLOSE_DIALOG,
    SATURN_CSOP_PLAY_SOUND,
    SATURN_CSOP_WAIT_FOR_SOUND,
    SATURN_CSOP_SCRIPT_UNKNOWN_11,
    SATURN_CSOP_SET_END,
    SATURN_CSOP_SCRIPT_UNKNOWN_13,
    SATURN_CSOP_SCRIPT_SWITCH,
    SATURN_CSOP_SCRIPT_UNKNOWN_15,
    SATURN_CSOP_WAIT_FOR_FLAG,
    SATURN_CSOP_SET_FLAG,
    SATURN_CSOP_SCRIPT_UNKNOWN_18,
    SATURN_CSOP_LOAD_PORTRAIT,
    SATURN_CSOP_SCRIPT_UNKNOWN_20,
    SATURN_CSOP_SCRIPT_UNKNOWN_21,
    SATURN_CSOP_RESET_FLAG,
    SATURN_CSOP_SCRIPT_UNKNOWN_23,
    SATURN_CSOP_WAIT_FOR_FLAG_RESET,
} SaturnCutsceneOpcode;

#define SATURN_CS_CMD(op, payload)                                             \
    (((u32)(op) << 24) | ((u32)(payload) & 0xFFFFFF))
#define SATURN_CS_CMD_U32(op, payload, value)                                  \
    SATURN_CS_CMD(op, payload), (u32)(value)
#define SATURN_CS_CMD_U32_3(op, payload, value0, value1, value2)               \
    SATURN_CS_CMD(op, payload), (u32)(value0), (u32)(value1), (u32)(value2)

/* Fixed-arity macros keep padded Shift-JIS records visible as text records. */
#define SATURN_CS_TEXT_1(a) a
#define SATURN_CS_TEXT_2(a, b) a, b
#define SATURN_CS_TEXT_3(a, b, c) a, b, c
#define SATURN_CS_TEXT_4(a, b, c, d) a, b, c, d
#define SATURN_CS_TEXT_5(a, b, c, d, e) a, b, c, d, e
#define SATURN_CS_TEXT_6(a, b, c, d, e, f) a, b, c, d, e, f
#define SATURN_CS_TEXT_7(a, b, c, d, e, f, g) a, b, c, d, e, f, g
#define SATURN_CS_TEXT_8(a, b, c, d, e, f, g, h) a, b, c, d, e, f, g, h

#endif
