// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

static AnimationFrame D_us_80182028[] = {
    POSE(0x4, 0x7A, 1), POSE(0x50, 0x7B, 1), POSE_END,
    POSE(0x8, 0x7B, 1), POSE(0x18, 0x7C, 9), POSE_LOOP(1),
};

static AnimationFrame D_us_80182040[] = {
    POSE(0x50, 0x79, 1),
    POSE_END,
};

static AnimationFrame D_us_80182048[] = {
    POSE(0xFF, 1, 1), POSE(0xFF, 1, 1), POSE(0xFF, 1, 1),
    POSE(0xFF, 1, 1), POSE_JUMP(6),
};

static AnimationFrame D_us_8018205C[] = {
    POSE(0xFF, 0x4F, 1),
    POSE_LOOP(0),
};

static AnimationFrame D_us_80182064[] = {
    POSE_UNKNOWN(0x10), POSE_UNKNOWN(0x11), POSE(6, 0x13, 1),
    POSE(6, 0x14, 1),   POSE(6, 0x15, 1),   POSE(6, 0x16, 1),
    POSE(6, 0x17, 1),   POSE(6, 0x18, 1),   POSE_JUMP(2),
};

static AnimationFrame D_us_80182088[] = {
    POSE(4, 0x13, 1), POSE(4, 0x14, 1), POSE(4, 0x15, 1), POSE(4, 0x16, 1),
    POSE(4, 0x17, 1), POSE(4, 0x18, 1), POSE_END,
};

static AnimationFrame D_us_801820A4[] = {
    POSE(5, 0x13, 1), POSE(5, 0x14, 1), POSE(5, 0x15, 1), POSE(5, 0x16, 1),
    POSE(5, 0x17, 1), POSE(5, 0x18, 1), POSE_END,
};

static AnimationFrame D_us_801820C0[] = {
    POSE(6, 0x56, 2), POSE(6, 0x57, 1), POSE(6, 0x58, 1), POSE(6, 0x59, 1),
    POSE(6, 0x5A, 1), POSE(5, 0x5B, 1), POSE(3, 0x5C, 1), POSE(3, 0x5B, 1),
    POSE(2, 0x5C, 1), POSE(2, 0x5D, 1), POSE(2, 0x5C, 1), POSE(0x80, 0x5D, 1),
    POSE_JUMP(6),
};

static AnimationFrame D_us_801820F4[] = {
    POSE(0xC0, 0x5D, 1), POSE(7, 0x5C, 1),   POSE(3, 0x5B, 1),
    POSE(4, 0x5C, 1),    POSE(0xB, 0x5D, 1), POSE(8, 0x5E, 1),
    POSE(0xA0, 0x4F, 1), POSE_JUMP(3),
};

static AnimationFrame D_us_80182114[] = {
    POSE(3, 0x19, 1), POSE(3, 0x1A, 1), POSE(3, 0x1B, 1), POSE(3, 0x1C, 1),
    POSE(3, 0x1D, 4), POSE(3, 0x1E, 4), POSE(3, 0x1F, 5), POSE(3, 0x20, 5),
    POSE(3, 0x21, 5), POSE(3, 0x22, 5), POSE(3, 0x23, 5), POSE(3, 0x24, 5),
    POSE(3, 0x25, 4), POSE(3, 0x26, 4), POSE(3, 0x27, 4), POSE(3, 0x28, 4),
    POSE_JUMP(8),
};

static AnimationFrame D_us_80182158[] = {
    POSE(3, 0x2C, 1), POSE(3, 0x2D, 1), POSE(3, 0x2E, 1), POSE(3, 0x2F, 1),
    POSE(3, 0x30, 1), POSE(3, 0x31, 1), {-3, 1},          POSE_JUMP(0xD),
};

static AnimationFrame D_us_80182178[] = {
    POSE(2, 0x39, 1), POSE(3, 0x3A, 1), POSE(3, 0x3B, 1), POSE(4, 0x3C, 1),
    POSE(4, 0x3D, 1), POSE(5, 0x3E, 4), POSE(7, 0x3F, 4), POSE(5, 0x40, 5),
    POSE(3, 0x41, 5), POSE(3, 0x42, 4), POSE_JUMP(0xC),
};

static AnimationFrame D_us_801821A4[] = {
    POSE_UNKNOWN(0),
    POSE_JUMP(4),
};

static AnimationFrame D_us_801821AC[] = {
    POSE_UNKNOWN(0),
    POSE_JUMP(5),
};

static AnimationFrame D_us_801821B4[] = {
    POSE(2, 0x39, 1), POSE(2, 0x3A, 1), POSE(2, 0x3B, 1), POSE(3, 0x3C, 1),
    POSE(3, 0x3D, 1), POSE(3, 0x3E, 4), POSE(3, 0x3F, 4), POSE(3, 0x40, 5),
    POSE(2, 0x41, 5), POSE(2, 0x42, 4), POSE_END,
};

static AnimationFrame D_us_801821E0[] = {
    POSE(3, 0x32, 1), POSE(3, 0x33, 1), POSE(3, 0x34, 1), POSE(3, 0x35, 1),
    POSE(3, 0x36, 1), POSE(3, 0x37, 1), POSE(3, 0x38, 1), POSE_END,
};

static AnimationFrame D_us_80182200[] = {
    POSE_UNKNOWN(1),
    POSE_JUMP(0xD),
};

static AnimationFrame D_us_80182208[] = {
    POSE(3, 0x29, 1), POSE(2, 0x2A, 1), POSE(3, 0x2B, 1), POSE(2, 0x2C, 1),
    POSE(3, 0x2D, 1), POSE(2, 0x2E, 1), POSE(3, 0x2F, 1), POSE(2, 0x30, 1),
    POSE(3, 0x31, 1), POSE(2, 0x32, 1), POSE(3, 0x33, 1), POSE(2, 0x34, 1),
    POSE(3, 0x35, 1), POSE(2, 0x36, 1), POSE(3, 0x37, 1), POSE(2, 0x38, 1),
    POSE_LOOP(0),
};

static AnimationFrame D_us_8018224C[] = {
    POSE_UNKNOWN(2),  POSE(4, 0x50, 1), POSE(4, 0x51, 1), POSE(4, 0x52, 1),
    POSE(4, 0x53, 1), POSE(4, 0x54, 1), POSE(4, 0x55, 1), POSE(4, 0x54, 1),
    POSE(4, 0x55, 1), POSE_JUMP(4),
};

static AnimationFrame D_us_80182274[] = {
    POSE(4, 0x43, 6), POSE(4, 0x44, 6), POSE(4, 0x45, 6), POSE(4, 0x46, 6),
    POSE(4, 0x47, 6), POSE(4, 0x48, 6), POSE(4, 0x49, 6), POSE_END,
};

static AnimationFrame D_us_80182294[] = {
    POSE_UNKNOWN(2),  POSE(4, 0x4A, 1), POSE(4, 0x4B, 1), POSE(4, 0x4C, 1),
    POSE(4, 0x4D, 1), POSE(4, 0x4E, 1), POSE(4, 0x4F, 1), POSE(4, 0x4E, 1),
    POSE(4, 0x4F, 1), POSE_JUMP(3),
};

static AnimationFrame D_us_801822BC[] = {
    POSE(2, 0x42, 4), POSE(2, 0x41, 5), POSE(3, 0x40, 5), POSE(3, 0x3F, 4),
    POSE(3, 0x3E, 4), POSE_UNKNOWN(2),  POSE_END,
};

static AnimationFrame D_us_801822D8[] = {
    POSE(2, 2, 2), POSE(4, 3, 3), POSE(4, 4, 3),   POSE(4, 5, 3),
    POSE(4, 6, 3), POSE(4, 7, 3), POSE_UNKNOWN(3), POSE_END,
};

static AnimationFrame D_us_801822F8[] = {
    POSE(4, 0x8, 3), POSE(4, 0x9, 3), POSE(4, 0xA, 3), POSE(4, 0xB, 3),
    POSE(4, 0xC, 3), POSE(4, 0xD, 3), POSE(4, 0xE, 3), POSE_END,
};

static AnimationFrame D_us_80182318[] = {
    POSE(0xFF, 0xF, 3),
    POSE_LOOP(0),
};

static AnimationFrame D_us_80182320[] = {
    POSE(0x10, 0xF, 3),
    POSE_END,
};

static AnimationFrame D_us_80182328[] = {
    POSE(3, 0x10, 3),
    POSE(3, 0x11, 2),
    POSE(3, 0x12, 1),
    POSE_END,
};

static AnimationFrame D_us_80182338[] = {
    POSE_UNKNOWN(3),
    POSE_JUMP(0x11),
};

static AnimationFrame D_us_80182340[] = {
    POSE(1, 2, 2),  POSE(1, 4, 3),  POSE(1, 6, 3),  POSE(1, 8, 3),
    POSE(1, 10, 3), POSE(1, 12, 3), POSE(1, 14, 3), POSE_END,
};

static AnimationFrame D_us_80182360[] = {
    POSE(5, 0x5F, 1),
    POSE(5, 0x60, 1),
    POSE_JUMP(0x17),
};

static AnimationFrame D_us_8018236C[] = {
    POSE(5, 0x61, 1), POSE(5, 0x62, 1),    POSE(5, 0x67, 1),
    POSE(5, 0x68, 1), POSE(0x40, 0x69, 1), POSE_END,
};

static AnimationFrame D_us_80182384[] = {
    POSE(5, 0x63, 7),
    POSE(5, 0x64, 8),
    POSE_JUMP(0x1A),
};

static AnimationFrame D_us_80182390[] = {
    POSE(5, 0x64, 8),
    POSE(5, 0x63, 7),
    POSE_JUMP(0x17),
};

static AnimationFrame D_us_8018239C[] = {
    POSE(3, 0x65, 8),
    POSE(3, 0x66, 8),
    POSE_LOOP(0),
};

static AnimationFrame D_us_801823A8[] = {
    POSE(3, 0x6A, 7), POSE(4, 0x6B, 7), POSE(4, 0x6C, 7),
    POSE(4, 0x6D, 7), POSE_JUMP(0x1C),
};

static AnimationFrame D_us_801823BC[] = {
    POSE(8, 0x6E, 7), POSE(5, 0x6F, 7),    POSE(5, 0x70, 7),
    POSE(5, 0x71, 7), POSE(0x41, 0x72, 7), POSE_END,
};

static AnimationFrame D_us_801823D4[] = {
    POSE_UNKNOWN(4),  POSE(4, 0x51, 1), POSE(4, 0x52, 1),
    POSE(4, 0x53, 1), POSE(4, 0x54, 1), POSE(4, 0x55, 1),
    POSE(4, 0x54, 1), POSE(4, 0x55, 1), POSE_JUMP(4),
};

static AnimationFrame D_us_801823F8[] = {
    POSE(5, 0x74, 4), POSE(5, 0x75, 4), POSE(5, 0x76, 2),
    POSE(5, 0x77, 1), POSE(5, 0x78, 1), POSE_END,
};

static AnimationFrame D_us_80182410[] = {
    POSE_UNKNOWN(4),  POSE(4, 0x4C, 1), POSE(4, 0x4D, 1), POSE(4, 0x4E, 1),
    POSE(4, 0x4F, 1), POSE(4, 0x4E, 1), POSE(4, 0x4F, 1), POSE_JUMP(3),
};

static AnimationFrame D_us_80182430[] = {
    POSE(3, 0x71, 7),
    POSE(0x42, 0x72, 7),
    POSE_END,
};

static AnimationFrame D_us_8018243C[] = {
    POSE(0x2, 0x1099, 8), POSE(0x2, 0x1098, 8),
    POSE(0x4, 0x1099, 8), POSE(0x3, 0x109A, 8),
    POSE(0x3, 0x109B, 8), POSE(0x3, 0x1065, 8),
    POSE(0x3, 0x1066, 8), POSE(0x3, 0x1065, 8),
    POSE(0x3, 0x1066, 8), POSE_END,
};

static AnimationFrame D_us_80182464[] = {
    POSE(5, 0x5F, 1),
    POSE(5, 0x60, 1),
    POSE_JUMP(0x17),
};

static AnimationFrame D_us_80182470[] = {
    POSE(0xFF, 0x73, 7),
    POSE_LOOP(0),
};

static AnimationFrame D_us_80182478[] = {
    POSE(3, 0x74, 7),    POSE(3, 0x3, 7), POSE(3, 0x4, 3), POSE(3, 0x5, 3),
    POSE(3, 0x6, 3),     POSE(3, 0x7, 3), POSE(3, 0x8, 3), POSE(3, 0x9, 3),
    POSE(3, 0xA, 3),     POSE(3, 0xB, 3), POSE(4, 0xC, 3), POSE(4, 0xD, 3),
    POSE(5, 0xE, 3),     POSE(7, 0xC, 3), POSE(5, 0xB, 3), POSE(4, 0xA, 3),
    POSE(4, 0x9, 3),     POSE(4, 0x8, 3), POSE(4, 0x7, 3), POSE(4, 0x6, 3),
    POSE(4, 0x5, 3),     POSE(4, 0x4, 3), POSE(4, 0x3, 3), POSE(0xFF, 0x74, 3),
    POSE(0xFF, 0x74, 3), POSE_END,
};

static AnimationFrame D_us_801824E0[] = {
    POSE(5, 0x9C, 3),
    POSE(6, 0x9D, 1),
    POSE(6, 0x9E, 5),
    POSE_END,
};

static AnimationFrame D_us_801824F0[] = {
    POSE(0x2, 0x127C, 9), POSE(0x2, 0x127D, 9),
    POSE(0x2, 0x127E, 9), POSE(0x2, 0x127F, 9),
    POSE(0x3, 0x127E, 9), POSE(0x2, 0x127C, 9),
    POSE(0x3, 0x127D, 9), POSE(0x4, 0x127C, 9),
    POSE(0x6, 0x1280, 9), POSE_END,
};

static AnimationFrame D_us_80182518[] = {
    POSE(2, 0x81, 3), POSE(2, 0x82, 3), POSE(2, 0x83, 3),
    POSE(2, 0x84, 3), POSE(3, 0x83, 3), POSE(2, 0x81, 3),
    POSE(3, 0x82, 3), POSE(4, 0x81, 3), POSE_END,
};

static AnimationFrame D_us_8018253C[] = {
    POSE(0x2, 0x1085, 8), POSE(0x2, 0x1086, 8), POSE(0x2, 0x1087, 8),
    POSE(0x3, 0x1086, 8), POSE(0x3, 0x1085, 8), POSE_END,
};

static AnimationFrame D_us_80182554[] = {
    POSE(2, 0x88, 7), POSE(2, 0x89, 7), POSE(2, 0x8A, 7),
    POSE(3, 0x89, 7), POSE(3, 0x88, 7), POSE_END,
};

static AnimationFrame D_us_8018256C[] = {
    POSE(3, 0x6E, 7),    POSE(11, 0x8B, 10), POSE(5, 0x8C, 7), POSE(5, 0x8D, 7),
    POSE(7, 0x6E, 7),    POSE(3, 0x6F, 7),   POSE(3, 0x70, 7), POSE(3, 0x71, 7),
    POSE(0xFF, 0x72, 7), POSE_END,
};

static AnimationFrame D_us_80182594[] = {
    POSE(0x30, 0x9F, 7),
    POSE_END,
};

static AnimationFrame D_us_8018259C[] = {
    POSE(0x10, 0x9F, 7),
    POSE(7, 0xA1, 1),
    POSE(0x1C, 0xA2, 1),
    POSE_END,
};

static AnimationFrame D_us_801825AC[] = {
    POSE(0x30, 0xA3, 1),
    POSE_END,
};

static AnimationFrame D_us_801825B4[] = {
    POSE(9, 0xA5, 6), POSE(2, 0xA6, 6), POSE(2, 0xA5, 6),  POSE(3, 0xA6, 6),
    POSE(3, 0xA5, 6), POSE(3, 0xA6, 6), POSE(17, 0xA5, 6), POSE(3, 0x9F, 6),
    POSE(4, 0x11, 6), POSE(4, 0x12, 6), POSE_END,
};

static AnimationFrame D_us_801825E0[] = {
    POSE(9, 0xA7, 4), POSE(2, 0xA8, 4), POSE(2, 0xA7, 4),  POSE(3, 0xA8, 4),
    POSE(3, 0xA7, 4), POSE(3, 0xA8, 4), POSE(17, 0xA7, 4), POSE(3, 0x9F, 6),
    POSE(4, 0x11, 6), POSE(4, 0x12, 6), POSE_END,
};

static AnimationFrame D_us_8018260C[] = {
    POSE(9, 0xA9, 4), POSE(2, 0xAA, 4), POSE(2, 0xA9, 4),  POSE(3, 0xAA, 4),
    POSE(3, 0xA9, 4), POSE(3, 0xAA, 4), POSE(17, 0xA9, 4), POSE(3, 0x11, 6),
    POSE(3, 0x12, 6), POSE_END,
};

static AnimationFrame D_us_80182634[] = {
    POSE(9, 0xAB, 4), POSE(2, 0xAC, 4), POSE(2, 0xAB, 4),  POSE(3, 0xAC, 4),
    POSE(3, 0xAB, 4), POSE(3, 0xAC, 4), POSE(17, 0xAB, 4), POSE(3, 0x11, 6),
    POSE(3, 0x12, 6), POSE_END,
};

static AnimationFrame D_us_8018265C[] = {
    POSE(2, 0x9F, 7),
    POSE(2, 0xA0, 7),
    POSE_LOOP(0),
};

static AnimationFrame D_us_80182668[] = {
    POSE(2, 0xA3, 1),
    POSE(2, 0xA4, 1),
    POSE_LOOP(0),
};

static AnimationFrame D_us_80182674[] = {
    POSE(5, 0x9F, 7), POSE(5, 0xA2, 1), POSE(5, 0xA3, 1),
    POSE(5, 0xA5, 6), POSE(5, 0xA9, 4), POSE_LOOP(0),
};

static AnimationFrame D_us_8018268C[] = {
    POSE(0xF, 0xAD, 7),
    POSE_END,
};

static AnimationFrame D_us_80182694[] = {
    POSE(0xF, 0xAE, 7),
    POSE_END,
};

static AnimationFrame D_us_8018269C[] = {
    POSE(0xF, 0xAF, 7),
    POSE_END,
};

static AnimationFrame D_us_801826A4[] = {
    POSE(5, 0xA5, 6), POSE(2, 0xA6, 6), POSE(2, 0xA5, 6),  POSE(3, 0xA6, 6),
    POSE(3, 0xA5, 6), POSE(3, 0xA6, 6), POSE(17, 0xA5, 6), POSE(3, 0x11, 6),
    POSE(3, 0x12, 6), POSE_END,
};

static AnimationFrame D_us_801826CC[] = {
    POSE(9, 0x9F, 7), POSE(4, 0xA1, 1),  POSE(4, 0xA2, 1), POSE(4, 0xA9, 4),
    POSE(4, 0xAA, 4), POSE(17, 0xB1, 7), POSE(8, 0xB2, 7), POSE(8, 0xB3, 7),
    POSE(5, 0x71, 7), POSE(66, 0x72, 7), POSE_END,
};

static AnimationFrame D_us_801826F8[] = {
    POSE(3, 0xB5, 7), POSE(3, 0xB6, 7), POSE(3, 0xB7, 7), POSE(3, 0xB8, 7),
    POSE(3, 0xB4, 7), POSE(4, 0xB5, 7), POSE(4, 0xB6, 7), POSE(4, 0xB7, 7),
    POSE(4, 0xB8, 7), POSE(4, 0xB4, 7), POSE(5, 0xB5, 7), POSE(5, 0xB6, 7),
    POSE(5, 0xB7, 7), POSE(5, 0xB8, 7), POSE(5, 0xB4, 7), POSE(6, 0xB5, 7),
    POSE(6, 0xB6, 7), POSE(6, 0xB7, 7), POSE(6, 0xB8, 7), POSE(6, 0xB4, 7),
    POSE_END,
};

static AnimationFrame D_us_8018274C[] = {
    POSE(2, 0xB5, 7),    POSE(2, 0xB6, 7), POSE(2, 0xB7, 7),
    POSE(2, 0xB8, 7),    POSE(2, 0xB4, 7), POSE_UNKNOWN(0x1B),
    POSE(7, 0xB5, 7),    POSE(7, 0xB6, 7), POSE(7, 0xB7, 7),
    POSE(8, 0xB8, 7),    POSE(9, 0xB4, 7), POSE(0xA, 0xB5, 7),
    POSE(0x40, 0x9F, 7), POSE_END,
};

static AnimationFrame D_us_80182784[] = {
    POSE(2, 0xC7, 3),    POSE(2, 0xC8, 3), POSE(2, 0xC9, 3), POSE(2, 0xCA, 3),
    POSE(0x10, 0xCB, 3), POSE(2, 0xCC, 3), POSE(2, 0xCD, 3), POSE(1, 0xCE, 3),
    POSE(1, 0xCF, 3),    POSE_END,
};

static AnimationFrame D_us_801827AC[] = {
    POSE_UNKNOWN(0x1B), POSE(7, 0xB5, 7), POSE(7, 0xB6, 7), POSE(7, 0xB7, 7),
    POSE(8, 0xA1, 7),   POSE(1, 0xA2, 7), POSE_END,
};

static AnimationFrame D_us_801827C8[] = {
    POSE_UNKNOWN(0x1B), POSE(7, 0xB5, 7), POSE(7, 0xB6, 7),
    POSE(7, 0xB7, 7),   POSE_END,
};

static AnimationFrame D_us_801827DC[] = {
    POSE(0x18, 0x8E, 1), POSE(4, 0x8F, 1),    POSE(4, 0x90, 1),
    POSE(4, 0x91, 1),    POSE(6, 0x92, 1),    POSE(7, 0x93, 1),
    POSE(4, 0x94, 1),    POSE(0x19, 0x95, 1), POSE(4, 0x96, 1),
    POSE(4, 0x97, 1),    POSE(4, 0xB0, 1),    POSE(2, 0x97, 1),
    POSE(2, 0x96, 1),    POSE(0x41, 0x95, 1), POSE(9, 0x93, 1),
    POSE(4, 0x92, 1),    POSE(3, 0x91, 1),    POSE(4, 0x90, 1),
    POSE(4, 0x8F, 1),    POSE(4, 0x8E, 1),    POSE_END,
};

static AnimationFrame D_us_80182830[] = {
    POSE(4, 0x8E, 1),
    POSE_END,
};

static AnimationFrame D_us_80182838[] = {
    POSE_UNKNOWN(5),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_80182844[] = {
    POSE(0x4, 0x12BF, 9), POSE(6, 0xC0, 1), POSE(5, 0xC1, 1), POSE(5, 0xC2, 1),
    POSE(4, 0xC3, 1),     POSE(3, 0x54, 1), POSE(3, 0x55, 1), POSE_END,
};

static AnimationFrame D_us_80182864[] = {
    POSE(0x2, 0x12B9, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x1, 0x12BB, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x2, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x4, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_8018289C[] = {
    POSE_UNKNOWN(5),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_801828A8[] = {
    POSE(0x4, 0x12BF, 9), POSE(5, 0x57, 1),    POSE(4, 0x58, 1),
    POSE(3, 0x59, 1),     POSE(3, 0x5A, 1),    POSE(3, 0x5B, 1),
    POSE(3, 0x5C, 1),     POSE(0x40, 0x5D, 1), POSE_END,
};

static AnimationFrame D_us_801828CC[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC5, 3), POSE(1, 0xC5, 3),  POSE(1, 0xC5, 3),
    POSE(1, 0xC5, 3), POSE_UNKNOWN(6),  POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_801828EC[] = {
    POSE(4, 0xCB, 3), POSE(6, 0xCC, 3), POSE(5, 0xCD, 3),
    POSE(5, 0xCE, 3), POSE(5, 0xCF, 3), POSE(0x40, 0xF, 3),
};

static AnimationFrame D_us_80182904[] = {
    POSE(1, 0xC7, 3), POSE(1, 0xC7, 3), POSE(1, 0xC7, 3),
    POSE(2, 0xC7, 3), POSE(4, 0xC8, 3), POSE(4, 0xC9, 3),
    POSE(4, 0xCA, 3), POSE(4, 0xCB, 3), POSE_END,
};

static AnimationFrame D_us_80182928[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC6, 3), POSE(1, 0xC6, 3),  POSE(1, 0xC6, 3),
    POSE(1, 0xC6, 3), POSE_UNKNOWN(6),  POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182948[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7),  POSE(1, 0xD1, 7),
    POSE(2, 0xD1, 7), POSE_UNKNOWN(0xA), POSE_END,
};

static AnimationFrame D_us_80182960[] = {
    POSE(1, 0xD2, 7), POSE(1, 0xD2, 7), POSE(1, 0xD2, 7),
    POSE(2, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_80182978[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(2, 0xD5, 7), POSE_UNKNOWN(7),  POSE_END,
};

static AnimationFrame D_us_80182990[] = {
    POSE(1, 0xD7, 7), POSE(1, 0xD7, 7), POSE(1, 0xD7, 7),
    POSE(2, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_801829A8[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(2, 0xD6, 7), POSE_UNKNOWN(7),  POSE_END,
};

static AnimationFrame D_us_801829C0[] = {
    POSE_UNKNOWN(8),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_801829CC[] = {
    POSE(0x1, 0x12B9, 9), POSE(0x1, 0x12B9, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x2, 0x12BA, 9),
    POSE(0x8, 0x12BA, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x1, 0x12BB, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x1, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x4, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80182A04[] = {
    POSE_UNKNOWN(8),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_80182A10[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(2, 0xC5, 3),
    POSE(8, 0xC5, 3), POSE_UNKNOWN(9),  POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182A30[] = {
    POSE(1, 0xC7, 3), POSE(1, 0xC7, 3), POSE(1, 0xC7, 3),
    POSE(2, 0xC7, 3), POSE(4, 0xC8, 3), POSE(4, 0xC9, 3),
    POSE(4, 0xCA, 3), POSE(8, 0xCB, 3), POSE_END,
};

static AnimationFrame D_us_80182A54[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(2, 0xC6, 3),
    POSE(8, 0xC6, 3), POSE_UNKNOWN(9),  POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182A74[] = {
    POSE(1, 0xD0, 7), POSE(1, 0xD0, 7),  POSE(1, 0xD1, 7), POSE(2, 0xD1, 7),
    POSE(8, 0xD1, 7), POSE_UNKNOWN(0xA), POSE_END,
};

static AnimationFrame D_us_80182A90[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD5, 7), POSE(2, 0xD5, 7),
    POSE(8, 0xD5, 7), POSE_UNKNOWN(7),  POSE_END,
};

static AnimationFrame D_us_80182AAC[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD6, 7), POSE(2, 0xD6, 7),
    POSE(8, 0xD6, 7), POSE_UNKNOWN(7),  POSE_END,
};

static AnimationFrame D_us_80182AC8[] = {
    POSE_UNKNOWN(0xB),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_80182AD4[] = {
    POSE(0x1, 0x12B9, 9), POSE(0x1, 0x12B9, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x2, 0x12BA, 9), POSE(0x2, 0x12BA, 9), POSE(0x2, 0x12BA, 9),
    POSE(0x2, 0x12BA, 9), POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BB, 9), POSE(0x1, 0x12BB, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x1, 0x12BB, 9), POSE(0x4, 0x12BC, 9), POSE(0x4, 0x12BD, 9),
    POSE(0x4, 0x12BE, 9), POSE(0x4, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80182B1C[] = {
    POSE_UNKNOWN(0xB),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_80182B28[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(2, 0xC5, 3),
    POSE(2, 0xC5, 3), POSE(2, 0xC5, 3), POSE(2, 0xC5, 3),  POSE(1, 0xC5, 3),
    POSE(1, 0xC5, 3), POSE_UNKNOWN(6),  POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182B58[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(2, 0xC6, 3),
    POSE(2, 0xC6, 3), POSE(2, 0xC6, 3), POSE(2, 0xC6, 3),  POSE(1, 0xC6, 3),
    POSE(1, 0xC6, 3), POSE_UNKNOWN(6),  POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182B88[] = {
    POSE(1, 0xD0, 7), POSE(1, 0xD0, 7),  POSE(1, 0xD1, 7), POSE(2, 0xD1, 7),
    POSE(2, 0xD1, 7), POSE(2, 0xD1, 7),  POSE(2, 0xD1, 7), POSE(1, 0xD1, 7),
    POSE(1, 0xD1, 7), POSE_UNKNOWN(0xA), POSE_END,
};

static AnimationFrame D_us_80182BB4[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD5, 7), POSE(2, 0xD5, 7),
    POSE(2, 0xD5, 7), POSE(2, 0xD5, 7), POSE(2, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(1, 0xD5, 7), POSE_UNKNOWN(7),  POSE_END,
};

static AnimationFrame D_us_80182BE0[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD6, 7), POSE(2, 0xD6, 7),
    POSE(2, 0xD6, 7), POSE(2, 0xD6, 7), POSE(2, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(1, 0xD6, 7), POSE_UNKNOWN(7),  POSE_END,
};

static AnimationFrame D_us_80182C0C[] = {
    POSE_UNKNOWN(0xC),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_80182C18[] = {
    POSE(0x2, 0x12B9, 9), POSE(0x1, 0x12B9, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x2, 0x12BA, 9), POSE(0x2, 0x12BA, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BA, 9), POSE(0x3, 0x12BA, 9),
    POSE(0x1, 0x12BB, 9), POSE(0x1, 0x12BB, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x1, 0x12BB, 9), POSE(0x4, 0x12BC, 9), POSE(0x4, 0x12BD, 9),
    POSE(0x4, 0x12BE, 9), POSE(0x8, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80182C60[] = {
    POSE_UNKNOWN(0xC),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_80182C6C[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(2, 0xC5, 3),
    POSE(2, 0xC5, 3), POSE(1, 0xC5, 3), POSE(1, 0xC5, 3),  POSE(1, 0xC5, 3),
    POSE(3, 0xC5, 3), POSE_UNKNOWN(9),  POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182C9C[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(2, 0xC6, 3),
    POSE(2, 0xC6, 3), POSE(1, 0xC6, 3), POSE(1, 0xC6, 3),  POSE(1, 0xC6, 3),
    POSE(3, 0xC6, 3), POSE_UNKNOWN(9),  POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182CCC[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD0, 7),  POSE(1, 0xD1, 7), POSE(2, 0xD1, 7),
    POSE(2, 0xD1, 7), POSE(1, 0xD1, 7),  POSE(1, 0xD1, 7), POSE(1, 0xD1, 7),
    POSE(3, 0xD1, 7), POSE_UNKNOWN(0xA), POSE_END,
};

static AnimationFrame D_us_80182CF8[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD5, 7), POSE(2, 0xD5, 7),
    POSE(2, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(3, 0xD5, 7), POSE_UNKNOWN(7),  POSE_END,
};

static AnimationFrame D_us_80182D24[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD6, 7), POSE(2, 0xD6, 7),
    POSE(2, 0xD6, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(3, 0xD6, 7), POSE_UNKNOWN(7),  POSE_END,
};

static AnimationFrame D_us_80182D50[] = {
    POSE(2, 0x7A, 1),     POSE(2, 0x7B, 1),     POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BB, 9), POSE(0x1, 0x12BC, 9), POSE(0x1, 0x12BD, 9),
    POSE(0x1, 0x12BE, 9), POSE(0x3, 0x12BF, 9), POSE(3, 0xC0, 1),
    POSE(3, 0xC1, 1),     POSE(3, 0xC2, 1),     POSE(3, 0xC3, 1),
    POSE(2, 0x54, 1),     POSE(2, 0x55, 1),     POSE_UNKNOWN(0x10),
    POSE_JUMP(2),
};

static AnimationFrame D_us_80182D90[] = {
    POSE(5, 0x57, 1), POSE(4, 0x58, 1),    POSE(3, 0x59, 1),
    POSE(3, 0x5A, 1), POSE(3, 0x5B, 1),    POSE(3, 0x5C, 1),
    POSE(3, 0x5D, 1), POSE(0x10, 0x79, 1), POSE_JUMP(3),
};

static AnimationFrame D_us_80182DB4[] = {
    POSE(4, 0x7A, 1),   POSE(4, 0x7B, 1),   POSE(4, 0x1, 1),
    POSE_UNKNOWN(0x10), POSE_UNKNOWN(0x11), POSE_JUMP(2),
};

static AnimationFrame D_us_80182DCC[] = {
    POSE(6, 0x56, 2), POSE(6, 0x57, 1), POSE(6, 0x58, 1), POSE(6, 0x59, 1),
    POSE(6, 0x5A, 1), POSE(5, 0x5B, 1), POSE(3, 0x5C, 1), POSE(3, 0x5B, 1),
    POSE(2, 0x5C, 1), POSE(2, 0x5D, 1), POSE(2, 0x5C, 1), POSE(0x80, 0x5D, 1),
    POSE_JUMP(6),
};

static AnimationFrame D_us_80182E00[] = {
    POSE(1, 0xC5, 3), POSE(1, 0xC7, 3), POSE(1, 0xC8, 3), POSE(1, 0xC9, 3),
    POSE(1, 0xCA, 3), POSE(1, 0xCB, 3), POSE(4, 0xCC, 3), POSE(3, 0xCD, 3),
    POSE(3, 0xCE, 3), POSE(3, 0xCF, 3), POSE(1, 0xF, 3),  POSE_END,
};

static AnimationFrame D_us_80182E30[] = {
    POSE(2, 0x7A, 1),    POSE(2, 0x7A, 1), POSE(2, 0x7A, 1),
    POSE(0x40, 0x7B, 1), POSE_END,
};

static AnimationFrame D_us_80182E44[] = {
    POSE(2, 0x81, 3),    POSE(2, 0x81, 3), POSE(2, 0x81, 3),
    POSE(0x40, 0x82, 3), POSE_END,
};

static AnimationFrame D_us_80182E58[] = {
    POSE_UNKNOWN(2),  POSE(4, 0x50, 1), POSE(4, 0x51, 1), POSE(4, 0x52, 1),
    POSE(4, 0x53, 1), POSE(4, 0x54, 1), POSE(4, 0x55, 1), POSE(4, 0x54, 1),
    POSE(4, 0x55, 1), POSE_END,
};

static AnimationFrame D_us_80182E80[] = {
    POSE_UNKNOWN(2),  POSE(4, 0x4A, 1), POSE(4, 0x4B, 1), POSE(4, 0x4C, 1),
    POSE(4, 0x4D, 1), POSE(4, 0x4E, 1), POSE(4, 0x4F, 1), POSE(4, 0x4E, 1),
    POSE(4, 0x4F, 1), POSE_END,
};

static AnimationFrame D_us_80182EA8[] = {
    POSE_UNKNOWN(0x12),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_80182EB4[] = {
    POSE(0x1, 0x12B9, 9), POSE(0x1, 0x12B9, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x2, 0x12BB, 9), POSE(0x2, 0x12BB, 9),
    POSE(0x2, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x8, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80182EEC[] = {
    POSE_UNKNOWN(0x12),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_80182EF8[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3),  POSE(1, 0xC5, 3), POSE(1, 0xC5, 3),
    POSE(1, 0xC5, 3), POSE(1, 0xC5, 3),  POSE(2, 0xC7, 3), POSE(2, 0xC7, 3),
    POSE(2, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182F34[] = {
    POSE(1, 0xC4, 3),  POSE(1, 0xC4, 3), POSE(1, 0xC6, 3), POSE(2, 0xC6, 3),
    POSE(1, 0xC6, 3),  POSE(2, 0xC7, 3), POSE(2, 0xC7, 3), POSE(2, 0xC7, 3),
    POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3), POSE(8, 0xCB, 3),
    POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182F6C[] = {
    POSE(1, 0xD0, 7), POSE(1, 0xD0, 7), POSE(1, 0xD1, 7), POSE(1, 0xD1, 7),
    POSE(1, 0xD1, 7), POSE(1, 0xD1, 7), POSE(1, 0xD2, 7), POSE(1, 0xD2, 7),
    POSE(2, 0xD2, 7), POSE(2, 0xD3, 7), POSE(2, 0xD3, 7), POSE(2, 0xD3, 7),
    POSE(2, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_80182FA4[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD7, 7), POSE(1, 0xD7, 7),
    POSE(2, 0xD7, 7), POSE(2, 0xD8, 7), POSE(2, 0xD8, 7), POSE(2, 0xD8, 7),
    POSE(2, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_80182FDC[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(1, 0xD6, 7), POSE(1, 0xD7, 7), POSE(1, 0xD7, 7), POSE(1, 0xD7, 7),
    POSE(2, 0xD8, 7), POSE(2, 0xD8, 7), POSE(2, 0xD8, 7), POSE(2, 0xD8, 7),
    POSE_END,
};

static AnimationFrame D_us_80183010[] = {
    POSE(1, 0xD0, 1),     POSE(1, 0xD0, 2),     POSE(0x1, 0x26D1, 0x13),
    POSE(1, 0xD1, 4),     POSE(0x10, 0xD1, 4),  POSE(1, 0xBA, 4),
    POSE(1, 0xBA, 4),     POSE(1, 0xBB, 5),     POSE(1, 0xBB, 6),
    POSE(1, 0xBB, 7),     POSE(0x2, 0x10BC, 8), POSE(0x2, 0x10BD, 8),
    POSE(0x2, 0x10BE, 8), POSE(0x2, 0x10BF, 8), POSE_END,
};

static AnimationFrame D_us_8018304C[] = {
    POSE_UNKNOWN(0x1C), POSE_UNKNOWN(0xD), POSE_END,
    POSE_UNKNOWN(0x1C), POSE_UNKNOWN(0xE), POSE_END,
};

static AnimationFrame D_us_80183064[] = {
    POSE(0x2, 0x127C, 9), POSE(0x2, 0x127D, 9), POSE(0x1, 0x127E, 9),
    POSE(0x1, 0x127F, 9), POSE(0x2, 0x127E, 9), POSE(0x2, 0x127D, 9),
    POSE(0x4, 0x127C, 9), POSE(0x5, 0x1280, 9), POSE_END,
};

static AnimationFrame D_us_80183088[] = {
    POSE(2, 0x81, 3), POSE(2, 0x82, 3), POSE(1, 0x83, 3), POSE(1, 0x84, 3),
    POSE(2, 0x83, 3), POSE(2, 0x82, 3), POSE(4, 0x81, 3), POSE_END,
};

static AnimationFrame D_us_801830A8[] = {
    POSE(0x1, 0x1085, 8), POSE(0x1, 0x1086, 8), POSE(0x1, 0x1087, 8),
    POSE(0x2, 0x1086, 8), POSE(0x2, 0x1085, 8), POSE_END,
};

static AnimationFrame D_us_801830C0[] = {
    POSE(1, 0x88, 7),
    POSE(4, 0x89, 7),
    POSE(2, 0x88, 7),
    POSE_END,
};

static AnimationFrame D_us_801830D0[] = {
    POSE_UNKNOWN(0x13),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_801830DC[] = {
    POSE(0x2, 0x12B9, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x3, 0x12BA, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x3, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x8, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80183104[] = {
    POSE_UNKNOWN(0x13),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_80183110[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(3, 0xC5, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_8018313C[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(3, 0xC6, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80183168[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7), POSE(3, 0xD1, 7), POSE(1, 0xD2, 7),
    POSE(3, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_80183184[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(3, 0xD5, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_801831A0[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD6, 7), POSE(3, 0xD6, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_801831BC[] = {
    POSE(0x1, 0x127C, 9), POSE(0x1, 0x127D, 9), POSE(0x1, 0x127E, 9),
    POSE(0x1, 0x127F, 9), POSE(0x2, 0x127E, 9), POSE(0x2, 0x127D, 9),
    POSE(0x4, 0x127C, 9), POSE(0x5, 0x1280, 9), POSE_END,
};

static AnimationFrame D_us_801831E0[] = {
    POSE(1, 0x81, 3), POSE(1, 0x82, 3), POSE(1, 0x83, 3), POSE(1, 0x84, 3),
    POSE(2, 0x83, 3), POSE(2, 0x82, 3), POSE(4, 0x81, 3), POSE_END,
};

static AnimationFrame D_us_80183200[] = {
    POSE_UNKNOWN(0x14),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_8018320C[] = {
    POSE(0x2, 0x12B9, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x2, 0x12BA, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x3, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x8, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80183234[] = {
    POSE_UNKNOWN(0x14),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_80183240[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(2, 0xC5, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_8018326C[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(2, 0xC6, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80183298[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7), POSE(2, 0xD1, 7), POSE(1, 0xD2, 7),
    POSE(3, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_801832B4[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(2, 0xD5, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_801832D0[] = {
    POSE_UNKNOWN(0x15),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_801832DC[] = {
    POSE(0x2, 0x127C, 9),
    POSE(0x2, 0x127D, 9),
    POSE(0x1, 0x127E, 9),
    POSE(0x1, 0x127F, 9),
    POSE(0x2, 0x127E, 9),
    POSE(0x2, 0x127E, 9),
    POSE(0x2, 0x127D, 9),
    POSE(0x2, 0x127C, 9),
    POSE(0x1, 0x12B9, 9),
    POSE(0x1, 0x12B9, 9),
    POSE(0x1, 0x12BA, 9),
    POSE(0x3, 0x12BA, 9),
    POSE(0x1, 0x12BB, 9),
    POSE(0x3, 0x12BB, 9),
    POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9),
    POSE(0x4, 0x12BE, 9),
    POSE(0x4, 0x12BF, 9),
    POSE_END,
};

static AnimationFrame D_us_80183328[] = {
    POSE_UNKNOWN(0x15),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_80183334[] = {
    POSE(2, 0x81, 3), POSE(2, 0x82, 3), POSE(1, 0x83, 3),  POSE(1, 0x84, 3),
    POSE(2, 0x83, 3), POSE(2, 0x83, 3), POSE(2, 0x82, 3),  POSE(2, 0x81, 3),
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(3, 0xC6, 3),
    POSE(1, 0xC7, 3), POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3),
    POSE(4, 0xCA, 3), POSE(4, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80183384[] = {
    POSE(1, 0xD0, 7), POSE(1, 0xD0, 7), POSE(1, 0xD1, 7), POSE(3, 0xD1, 7),
    POSE(1, 0xD2, 7), POSE(3, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_801833A4[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD5, 7), POSE(3, 0xD5, 7),
    POSE(1, 0xD7, 7), POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_801833C4[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD6, 7), POSE(3, 0xD6, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_801833E0[] = {
    POSE_UNKNOWN(0x16),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_801833EC[] = {
    POSE(0x2, 0x12B9, 9),
    POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BB, 9),
    POSE(0x3, 0x12BB, 9),
    POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9),
    POSE(0x4, 0x12BE, 9),
    POSE(0x8, 0x12BF, 9),
    POSE_END,
};

static AnimationFrame D_us_80183420[] = {
    POSE_UNKNOWN(0x16),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_8018342C[] = {
    POSE(2, 0xC4, 3),  POSE(1, 0xC5, 3), POSE(1, 0xC5, 3), POSE(1, 0xC5, 3),
    POSE(1, 0xC5, 3),  POSE(1, 0xC5, 3), POSE(1, 0xC7, 3), POSE(3, 0xC7, 3),
    POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3), POSE(8, 0xCB, 3),
    POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80183464[] = {
    POSE(2, 0xC4, 3),  POSE(1, 0xC6, 3), POSE(1, 0xC6, 3), POSE(1, 0xC6, 3),
    POSE(1, 0xC6, 3),  POSE(1, 0xC6, 3), POSE(1, 0xC7, 3), POSE(3, 0xC7, 3),
    POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3), POSE(8, 0xCB, 3),
    POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_8018349C[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7), POSE(1, 0xD1, 7), POSE(1, 0xD1, 7),
    POSE(1, 0xD1, 7), POSE(1, 0xD1, 7), POSE(1, 0xD2, 7), POSE(3, 0xD2, 7),
    POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_801834C4[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD7, 7), POSE(3, 0xD7, 7),
    POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_801834EC[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(1, 0xD6, 7), POSE(1, 0xD6, 7), POSE(1, 0xD7, 7), POSE(3, 0xD7, 7),
    POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_80183514[] = {
    POSE_UNKNOWN(0x17),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_80183520[] = {
    POSE(0x2, 0x12B9, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x3, 0x12BA, 9), POSE(0x2, 0x12BB, 9),
    POSE(0x2, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x8, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80183548[] = {
    POSE_UNKNOWN(0x17),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_80183554[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(3, 0xC5, 3), POSE(2, 0xC7, 3),
    POSE(2, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80183580[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7), POSE(3, 0xD1, 7), POSE(2, 0xD2, 7),
    POSE(2, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_8018359C[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(3, 0xD5, 7), POSE(2, 0xD7, 7),
    POSE(2, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_801835B8[] = {
    POSE_UNKNOWN(0x18),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_801835C4[] = {
    POSE(0x3, 0x12B9, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x4, 0x12BA, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x3, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x8, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_801835EC[] = {
    POSE_UNKNOWN(0x18),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_801835F8[] = {
    POSE(3, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(4, 0xC5, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80183624[] = {
    POSE(3, 0xD0, 7), POSE(1, 0xD1, 7), POSE(4, 0xD1, 7), POSE(1, 0xD2, 7),
    POSE(3, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_80183640[] = {
    POSE(3, 0xD4, 7), POSE(1, 0xD5, 7), POSE(4, 0xD5, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_8018365C[] = {
    POSE_UNKNOWN(0x19),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_80183668[] = {
    POSE(0x4, 0x12B9, 9), POSE(0x2, 0x12BA, 9),
    POSE(0x3, 0x12BA, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x3, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x8, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80183690[] = {
    POSE_UNKNOWN(0x19),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_8018369C[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(3, 0xC5, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_801836C8[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(3, 0xC6, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_801836F4[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7), POSE(3, 0xD1, 7), POSE(1, 0xD2, 7),
    POSE(3, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_80183710[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(3, 0xD5, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_8018372C[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD6, 7), POSE(3, 0xD6, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_80183748[] = {
    POSE_UNKNOWN(0x1A),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_80183754[] = {
    POSE(0x1, 0x12B9, 9), POSE(0x1, 0x12B9, 9),
    POSE(0x1, 0x12B9, 9), POSE(0x1, 0x12B9, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x3, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x8, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80183794[] = {
    POSE_UNKNOWN(0x1A),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_801837A0[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC4, 3),
    POSE(1, 0xC5, 3), POSE(1, 0xC5, 3), POSE(1, 0xC5, 3), POSE(1, 0xC5, 3),
    POSE(1, 0xC5, 3), POSE(1, 0xC7, 3), POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),
    POSE(4, 0xC9, 3), POSE(4, 0xCA, 3), POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF),
    POSE_END,
};

static AnimationFrame D_us_801837E4[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC4, 3),
    POSE(1, 0xC6, 3), POSE(1, 0xC6, 3), POSE(1, 0xC6, 3), POSE(1, 0xC6, 3),
    POSE(1, 0xC6, 3), POSE(1, 0xC7, 3), POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),
    POSE(4, 0xC9, 3), POSE(4, 0xCA, 3), POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF),
    POSE_END,
};

static AnimationFrame D_us_80183828[] = {
    POSE(1, 0xD0, 7), POSE(1, 0xD0, 7), POSE(1, 0xD0, 7), POSE(1, 0xD0, 7),
    POSE(1, 0xD1, 7), POSE(1, 0xD1, 7), POSE(1, 0xD1, 7), POSE(1, 0xD1, 7),
    POSE(1, 0xD1, 7), POSE(1, 0xD2, 7), POSE(3, 0xD2, 7), POSE(8, 0xD3, 7),
    POSE_END,
};

static AnimationFrame D_us_8018385C[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD4, 7),
    POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(1, 0xD5, 7), POSE(1, 0xD7, 7), POSE(3, 0xD7, 7), POSE(8, 0xD8, 7),
    POSE_END,
};

static AnimationFrame D_us_80183890[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD4, 7),
    POSE(1, 0xD6, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(1, 0xD6, 7), POSE(1, 0xD7, 7), POSE(3, 0xD7, 7), POSE(8, 0xD8, 7),
    POSE_END,
};

static AnimationFrame D_us_801838C4[] = {
    POSE(2, 0xC3, 1), POSE(2, 0xC2, 1),    POSE(2, 0xC1, 1), POSE(2, 0xC0, 1),
    POSE(2, 0xBF, 1), POSE(2, 0xC0, 1),    POSE(2, 0xBF, 1), POSE(2, 0xC0, 1),
    POSE(2, 0xBF, 1), POSE(0x24, 0xC0, 1), POSE_END,
};

static AnimationFrame D_us_801838F0[] = {
    POSE(2, 0xC7, 3), POSE(2, 0xC8, 3),    POSE(2, 0xC9, 3), POSE(2, 0xCA, 3),
    POSE(2, 0xC9, 3), POSE(2, 0xCA, 3),    POSE(2, 0xC9, 3), POSE(2, 0xCA, 3),
    POSE(2, 0xC9, 3), POSE(0x18, 0xCA, 3), POSE_END,
};

static AnimationFrame D_us_8018391C[] = {
    POSE(2, 0xD2, 7), POSE(2, 0xD3, 7),    POSE(2, 0xD2, 7),
    POSE(2, 0xD3, 7), POSE(2, 0xD2, 7),    POSE(0x24, 0xD3, 7),
    POSE_END,         POSE(0x30, 0x7B, 1), POSE_END,
};

static AnimationFrame D_us_80183940[] = {
    POSE(0x30, 0x79, 1),
    POSE_END,
};

static AnimationFrame D_us_80183948[] = {
    POSE(3, 0x67, 1), POSE(3, 0x68, 1),    POSE(3, 0x69, 1),
    POSE(3, 0x68, 1), POSE(3, 0x69, 1),    POSE(3, 0x68, 1),
    POSE(3, 0x69, 1), POSE(3, 0x68, 1),    POSE(0x18, 0x69, 1),
    POSE(4, 0x78, 1), POSE(0x20, 0x79, 1), POSE_END,
};

static AnimationFrame D_us_80183978[] = {
    POSE(6, 0x79, 1),
    POSE(6, 0x7A, 1),
    POSE(0x10, 0x7B, 1),
    POSE_END,
};

static AnimationFrame D_us_80183988[] = {
    POSE(6, 0x79, 1),
    POSE(6, 0x7A, 1),
    POSE(0x10, 0x79, 1),
    POSE_END,
};

static AnimationFrame D_us_80183998[] = {
    POSE(4, 0x8E, 1),    POSE(4, 0x8F, 1), POSE(4, 0x90, 1),
    POSE(0x14, 0x91, 1), POSE(4, 0x90, 1), POSE(4, 0x8F, 1),
    POSE(0x10, 0x8E, 1), POSE_JUMP(4),
};

static AnimationFrame D_us_801839B8[] = {
    POSE(0x28, 0, 0),
    POSE_END,
};

static AnimationFrame D_us_801839C0[] = {
    POSE(0x2, 0x1E01, 0xF), POSE(0x3, 0x1E02, 0xF), POSE(0x4, 0x1E03, 0xF),
    POSE(0x4, 0x1E04, 0xF), POSE(0x3, 0x1E05, 0xF), POSE(0x2, 0x1E06, 0xF),
    POSE(0x2, 0x1E07, 0xF), POSE(0x2, 0x1E08, 0xF), POSE(0x2, 0x1E09, 0xF),
    POSE(0x2, 0x1E0A, 0xF), POSE_LOOP(0),
};

static AnimationFrame D_us_801839EC[] = {
    POSE(0x1, 0x1E0C, 0xF), POSE(0x1, 0x1E0D, 0xF), POSE(0x1, 0x1E0F, 0xF),
    POSE(0x1, 0x1E10, 0xF), POSE(0x1, 0x1E0E, 0xF), POSE(0x1, 0x1E0D, 0xF),
    POSE(0x1, 0x1E0C, 0xF), POSE(0x1, 0x1E0D, 0xF), POSE(0x1, 0x1E0F, 0xF),
    POSE(0x2, 0x1E10, 0xF), POSE(0x2, 0x1E0E, 0xF), POSE(0x2, 0x1E0D, 0xF),
    POSE(0x2, 0x1E0C, 0xF), POSE(0x2, 0x1E0D, 0xF), POSE(0x2, 0x1E0F, 0xF),
    POSE(0x3, 0x1E10, 0xF), POSE(0x3, 0x1E0E, 0xF), POSE(0x3, 0x1E0D, 0xF),
    POSE_JUMP(0xC4),
};

static AnimationFrame D_us_80183A38[] = {
    POSE(0x3, 0x1E01, 0xF), POSE(0x4, 0x1E02, 0xF), POSE(0x6, 0x1E03, 0xF),
    POSE(0x6, 0x1E04, 0xF), POSE(0x5, 0x1E05, 0xF), POSE(0x4, 0x1E06, 0xF),
    POSE(0x4, 0x1E07, 0xF), POSE(0x3, 0x1E08, 0xF), POSE(0x3, 0x1E09, 0xF),
    POSE(0x3, 0x1E0A, 0xF), POSE_LOOP(0),
};

static AnimationFrame D_us_80183A64[] = {
    POSE(0x4, 0x1E02, 0xF), POSE(0x6, 0x1E03, 0xF), POSE(0x6, 0x1E04, 0xF),
    POSE(0x5, 0x1E05, 0xF), POSE(0x4, 0x1E06, 0xF), POSE(0x4, 0x1E07, 0xF),
    POSE(0x3, 0x1E08, 0xF), POSE(0x3, 0x1E09, 0xF), POSE(0x3, 0x1E0A, 0xF),
    POSE(0x3, 0x1E01, 0xF), POSE_LOOP(9),
};

static AnimationFrame D_us_80183A90[] = {
    POSE(0x6, 0x1E03, 0xF),
    POSE_END,
};

static AnimationFrame D_us_80183A98[] = {
    POSE(0x4, 0x1EC7, 0xF), POSE(0x4, 0x1EC8, 0xF),
    POSE(0x4, 0x1EC9, 0xF), POSE(0x4, 0x1ECA, 0xF),
    POSE(0x4, 0x1ECB, 0xF), POSE(0x6, 0x1ECC, 0xF),
    POSE(0x5, 0x1ECD, 0xF), POSE(0x5, 0x1ECE, 0xF),
    POSE(0x5, 0x1ECF, 0xF), POSE_END,
};

static AnimationFrame D_us_80183AC0[] = {
    POSE(0x4, 0x1ECE, 0xF),
    POSE(0x4, 0x1ECD, 0xF),
    POSE(0x6, 0x1ECC, 0xF),
    POSE(0x5, 0x1ECD, 0xF),
    POSE(0x5, 0x1ECE, 0xF),
    POSE(0x5, 0x1ECF, 0xF),
    POSE_END,
};

static AnimationFrame D_us_80183ADC[] = {
    POSE(0x1, 0x1E0C, 0xF), POSE(0x1, 0x1E0D, 0xF), POSE(0x1, 0x1E0F, 0xF),
    POSE(0x1, 0x1E10, 0xF), POSE(0x1, 0x1E0E, 0xF), POSE(0x1, 0x1E0D, 0xF),
    POSE(0x1, 0x1E0C, 0xF), POSE(0x1, 0x1E0D, 0xF), POSE(0x1, 0x1E0F, 0xF),
    POSE(0x1, 0x1E10, 0xF), POSE(0x4, 0x1E0E, 0xF), POSE_END,
};

// n.b.! not `static`
AnimationFrame D_us_80183B0C[] = {
    POSE(0x80, 0, 0),
    POSE_END,
};

static AnimationFrame D_us_80183B14[] = {
    POSE(0x84, 0x5F, 0),
    POSE_END,
};

static AnimationFrame D_us_80183B1C[] = {
    POSE(0x84, 0xC7, 0),
    POSE_END,
};

static AnimationFrame D_us_80183B24[] = {
    POSE(3, 0x1, 1), POSE(2, 0x2, 1), POSE(2, 0x3, 1), POSE(3, 0x4, 1),
    POSE(2, 0x3, 1), POSE(2, 0x2, 1), POSE_LOOP(0),
};

static AnimationFrame D_us_80183B40[] = {
    POSE(1, 0x5, 1),
    POSE(0x10, 0x6, 1),
    POSE_END,
};

static AnimationFrame D_us_80183B4C[] = {
    POSE(0x80, 0x3, 1), POSE(1, 0x2, 1), POSE(0x10, 0x2, 1),
    POSE(0x10, 0x3, 1), POSE(1, 0x2, 1), POSE(0x10, 0x2, 1),
    POSE(0x10, 0x3, 1), POSE(1, 0x2, 1), POSE(0x10, 0x2, 1),
    POSE(0x10, 0x3, 1), POSE(1, 0x2, 1), POSE(0x80, 0x2, 1),
    POSE_LOOP(0),
};

static AnimationFrame D_us_80183B80[] = {
    POSE(0x80, 0x2, 1),
    POSE_END,
};

static AnimationFrame D_us_80183B88[] = {
    POSE(0x80, 0x8, 1),
    POSE_END,
};

static AnimationFrame D_us_80183B90[] = {
    POSE(1, 0xC, 3),     POSE(1, 0xB, 3), POSE(1, 0xA, 3),
    POSE(0x18, 0x82, 3), POSE(1, 0xF, 3), POSE_END,
};

static AnimationFrame D_us_80183BA8[] = {
    POSE(1, 0x10, 1),    POSE(1, 0x11, 1), POSE(1, 0x12, 1),
    POSE(0x14, 0x7D, 1), POSE(4, 0x7A, 1), POSE_JUMP(4),
};

static AnimationFrame D_us_80183BC0[] = {
    POSE(2, 0x1A, 0),    POSE(2, 0x1B, 0), POSE(2, 0x1C, 0),
    POSE(2, 0x1D, 0),    POSE(2, 0x1E, 0), POSE(2, 0x1F, 0),
    POSE(2, 0xD0, 0),    POSE(4, 0xD1, 0), POSE(5, 0xD2, 0),
    POSE(0x10, 0xD3, 0), POSE(2, 0x6A, 0), POSE(2, 0x6B, 0),
    POSE(2, 0x6C, 0),    POSE(2, 0x6D, 0), POSE(3, 0x6E, 0),
    POSE(1, 0x6E, 0),    POSE(0x80, 1, 0), POSE_END,
};

static AnimationFrame D_us_80183C08[] = {
    POSE(2, 0x1A, 0), POSE(2, 0x1B, 0), POSE(2, 0x1C, 0), POSE(2, 0x1D, 0),
    POSE(2, 0x1E, 0), POSE(2, 0x1F, 0), POSE(2, 0xD0, 0), POSE(4, 0xD1, 0),
    POSE(5, 0xD2, 0), POSE(4, 0xD3, 0), POSE(2, 0xD0, 0), POSE(4, 0xD1, 0),
    POSE(5, 0xD2, 0), POSE(4, 0xD3, 0), POSE(2, 0x6A, 0), POSE(2, 0x6B, 0),
    POSE(2, 0x6C, 0), POSE(2, 0x6D, 0), POSE(3, 0x6E, 0), POSE(1, 0x6E, 0),
    POSE(0x80, 1, 0), POSE_END,
};

static AnimationFrame D_us_80183C60[] = {
    POSE_UNKNOWN(2),
    POSE(4, 0x78, 1),
    POSE(0x40, 0x79, 1),
    POSE_END,
};

u8 D_us_80183C70[][4] = {
    {
        0,
        0,
        0,
        0,
    },
    {
        0,
        0x1,
        0x4,
        0x14,
    },
    {
        0,
        0x7,
        0x4,
        0x10,
    },
    {
        0,
        0xD,
        0x4,
        0x9,
    },
    {
        0x2,
        0x3,
        0x5,
        0xD,
    },
    {
        0x5,
        0xFF,
        0x8,
        0x9,
    },
    {
        0xFE,
        0x4,
        0x6,
        0x10,
    },
    {
        0,
        0xFD,
        0x4,
        0x10,
    },
    {
        0x5,
        0xFB,
        0x6,
        0xC,
    },
    {
        0x5,
        0x1,
        0x4,
        0x14,
    },
    {
        0x1,
        0xF9,
        0xB,
        0x9,
    },
    {
        0xFE,
        0xFB,
        0x19,
        0x1A,
    },
    {
        0xE0,
        0xE1,
        0,
        0,
    },
    {
        0x1,
        0xFD,
        0x7,
        0x7,
    },
    {
        0x1,
        0xFD,
        0x7,
        0x7,
    },
    {
        0,
        0x1,
        0x4,
        0x7,
    },
    {
        0x1,
        0xFD,
        0x7,
        0x7,
    },
};

AnimationFrame* D_us_80183CB4[] = {
    &D_us_80182028, &D_us_80182040, &D_us_80182048, &D_us_8018205C,
    &D_us_80182064, &D_us_801820C0, &D_us_801820F4, &D_us_80182114,
    &D_us_80182158, &D_us_80182178, &D_us_801821A4, &D_us_801821AC,
    &D_us_80182200, &D_us_80182208, &D_us_8018224C, &D_us_80182294,
    &D_us_801822D8, &D_us_80182318, &D_us_80182320, &D_us_80182328,
    &D_us_80182338, &D_us_80182340, &D_us_80182360, &D_us_8018236C,
    &D_us_80182384, &D_us_80182390, &D_us_8018239C, &D_us_801823A8,
    &D_us_801823BC, &D_us_801823D4, &D_us_80182410, &D_us_80182430,
    &D_us_8018243C, &D_us_80182464, &D_us_80182470, &D_us_80182784,
    &D_us_801824F0, &D_us_801824F0, &D_us_80182518, &D_us_80182518,
    &D_us_8018253C, &D_us_80182554, &D_us_8018256C, &D_us_80182478,
    &D_us_80182478, &D_us_801824E0, &D_us_80182594, &D_us_8018259C,
    &D_us_801825AC, &D_us_801825B4, &D_us_801825E0, &D_us_8018260C,
    &D_us_80182634, &D_us_8018265C, &D_us_80182668, &D_us_80182674,
    &D_us_8018268C, &D_us_80182694, &D_us_8018269C, &D_us_801826A4,
    &D_us_801827DC, &D_us_80182830, &D_us_801839B8, &D_us_801826CC,
    &D_us_8018274C, &D_us_80182838, &D_us_8018289C, &D_us_801828CC,
    &D_us_80182928, &D_us_80182948, &D_us_80182978, &D_us_801829A8,
    &D_us_801829C0, &D_us_80182A04, &D_us_80182A10, &D_us_80182A54,
    &D_us_80182A74, &D_us_80182A90, &D_us_80182AAC, &D_us_80182AC8,
    &D_us_80182B1C, &D_us_80182B28, &D_us_80182B58, &D_us_80182B88,
    &D_us_80182BB4, &D_us_80182BE0, &D_us_80182C0C, &D_us_80182C60,
    &D_us_80182C6C, &D_us_80182C9C, &D_us_80182CCC, &D_us_80182CF8,
    &D_us_80182D24, &D_us_80182D50, &D_us_80182D90, &D_us_80182E00,
    &D_us_80182DB4, &D_us_80182DCC, &D_us_80182E00, &D_us_80182E30,
    &D_us_80182E30, &D_us_80182E44, &D_us_80182E58, &D_us_80182E80,
    &D_us_80182EA8, &D_us_80182EEC, &D_us_80182EF8, &D_us_80182F34,
    &D_us_80182F6C, &D_us_80182FA4, &D_us_80182FDC, &D_us_80183064,
    &D_us_80183064, &D_us_80183088, &D_us_80183088, &D_us_801830A8,
    &D_us_801830C0, &D_us_801830C0, &D_us_801830D0, &D_us_80183104,
    &D_us_80183110, &D_us_8018313C, &D_us_80183168, &D_us_80183184,
    &D_us_801831A0, &D_us_801831BC, &D_us_801831BC, &D_us_801831E0,
    &D_us_801831E0, &D_us_801830A8, &D_us_801830C0, &D_us_801830C0,
    &D_us_80183200, &D_us_80183234, &D_us_80183240, &D_us_8018326C,
    &D_us_80183298, &D_us_801832B4, &D_us_801832B4, &D_us_801832D0,
    &D_us_80183328, &D_us_80183334, &D_us_80183334, &D_us_80183384,
    &D_us_801833A4, &D_us_801833C4, &D_us_801833E0, &D_us_80183420,
    &D_us_8018342C, &D_us_80183464, &D_us_8018349C, &D_us_801834C4,
    &D_us_801834EC, &D_us_80183514, &D_us_80183548, &D_us_80183554,
    &D_us_80183554, &D_us_80183580, &D_us_8018359C, &D_us_8018359C,
    &D_us_801835B8, &D_us_801835EC, &D_us_801835F8, &D_us_801835F8,
    &D_us_80183624, &D_us_80183640, &D_us_80183640, &D_us_8018365C,
    &D_us_80183690, &D_us_8018369C, &D_us_801836C8, &D_us_801836F4,
    &D_us_80183710, &D_us_8018372C, &D_us_80183748, &D_us_80183794,
    &D_us_801837A0, &D_us_801837E4, &D_us_80183828, &D_us_8018385C,
    &D_us_80183890, &D_us_801838C4, &D_us_801838F0, &D_us_8018391C,
    &D_us_80183940, &D_us_80183940, &D_us_80183948, &D_us_80183948,
    &D_us_80183978, &D_us_80183988, &D_us_80183998, &D_us_80183998,
    &D_us_801827AC, &D_us_801827C8, &D_us_801839C0, &D_us_801839EC,
    &D_us_80183A38, &D_us_80183A64, &D_us_80183A90, &D_us_80183A98,
    &D_us_80183AC0, &D_us_80183ADC, &D_us_80183B0C, &D_us_80183B14,
    &D_us_80183B1C, &D_us_80183B24, &D_us_80183B40, &D_us_80183B4C,
    &D_us_80183B80, &D_us_80183B88, &D_us_80183BA8, &D_us_80183BA8,
    &D_us_80183B90, &D_us_80183B90, &D_us_8018304C, &D_us_8018304C,
    &D_us_80183BC0, &D_us_80183C08, &D_us_80183C60, &D_us_801822BC,
};

AnimationFrame* g_DopAnimationFrames[] = {
    &D_us_801821B4, &D_us_801821E0, &D_us_80182274, &D_us_801822F8,
    &D_us_801823F8, &D_us_80182864, &D_us_80182904, &D_us_80182990,
    &D_us_801829CC, &D_us_80182A30, &D_us_80182960, &D_us_80182AD4,
    &D_us_80182C18, &D_us_80182844, &D_us_801828A8, &D_us_801828EC,
    &D_us_80182088, &D_us_801820A4, &D_us_80182EB4, &D_us_801830DC,
    &D_us_8018320C, &D_us_801832DC, &D_us_801833EC, &D_us_80183520,
    &D_us_801835C4, &D_us_80183668, &D_us_80183754, &D_us_801826F8,
    &D_us_80183010,
};
