// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

static AnimationFrame D_us_801820B4[] = {
    POSE(0x4, 0x7A, 1), POSE(0x50, 0x7B, 1), POSE_END,
    POSE(0x8, 0x7B, 1), POSE(0x18, 0x7C, 9), POSE_LOOP(1),
};

static AnimationFrame D_us_801820CC[] = {
    POSE(0x50, 0x79, 1),
    POSE_END,
};

static AnimationFrame D_us_801820D4[] = {
    POSE(0xFF, 1, 1), POSE(0xFF, 1, 1), POSE(0xFF, 1, 1),
    POSE(0xFF, 1, 1), POSE_JUMP(6),
};

static AnimationFrame D_us_801820E8[] = {
    POSE(0xFF, 0x4F, 1),
    POSE_LOOP(0),
};

static AnimationFrame D_us_801820F0[] = {
    POSE_UNKNOWN(0x10), POSE_UNKNOWN(0x11), POSE(6, 0x13, 1),
    POSE(6, 0x14, 1),   POSE(6, 0x15, 1),   POSE(6, 0x16, 1),
    POSE(6, 0x17, 1),   POSE(6, 0x18, 1),   POSE_JUMP(2),
};

static AnimationFrame D_us_80182114[] = {
    POSE(4, 0x13, 1), POSE(4, 0x14, 1), POSE(4, 0x15, 1), POSE(4, 0x16, 1),
    POSE(4, 0x17, 1), POSE(4, 0x18, 1), POSE_END,
};

static AnimationFrame D_us_80182130[] = {
    POSE(5, 0x13, 1), POSE(5, 0x14, 1), POSE(5, 0x15, 1), POSE(5, 0x16, 1),
    POSE(5, 0x17, 1), POSE(5, 0x18, 1), POSE_END,
};

static AnimationFrame D_us_8018214C[] = {
    POSE(6, 0x56, 2), POSE(6, 0x57, 1), POSE(6, 0x58, 1), POSE(6, 0x59, 1),
    POSE(6, 0x5A, 1), POSE(5, 0x5B, 1), POSE(3, 0x5C, 1), POSE(3, 0x5B, 1),
    POSE(2, 0x5C, 1), POSE(2, 0x5D, 1), POSE(2, 0x5C, 1), POSE(0x80, 0x5D, 1),
    POSE_JUMP(6),
};

static AnimationFrame D_us_80182180[] = {
    POSE(0xC0, 0x5D, 1), POSE(7, 0x5C, 1),   POSE(3, 0x5B, 1),
    POSE(4, 0x5C, 1),    POSE(0xB, 0x5D, 1), POSE(8, 0x5E, 1),
    POSE(0xA0, 0x4F, 1), POSE_JUMP(3),
};

static AnimationFrame D_us_801821A0[] = {
    POSE(3, 0x19, 1), POSE(3, 0x1A, 1), POSE(3, 0x1B, 1), POSE(3, 0x1C, 1),
    POSE(3, 0x1D, 4), POSE(3, 0x1E, 4), POSE(3, 0x1F, 5), POSE(3, 0x20, 5),
    POSE(3, 0x21, 5), POSE(3, 0x22, 5), POSE(3, 0x23, 5), POSE(3, 0x24, 5),
    POSE(3, 0x25, 4), POSE(3, 0x26, 4), POSE(3, 0x27, 4), POSE(3, 0x28, 4),
    POSE_JUMP(8),
};

static AnimationFrame D_us_801821E4[] = {
    POSE(3, 0x2C, 1), POSE(3, 0x2D, 1), POSE(3, 0x2E, 1), POSE(3, 0x2F, 1),
    POSE(3, 0x30, 1), POSE(3, 0x31, 1), {-3, 1},          POSE_JUMP(0xD),
};

static AnimationFrame D_us_80182204[] = {
    POSE(2, 0x39, 1), POSE(3, 0x3A, 1), POSE(3, 0x3B, 1), POSE(4, 0x3C, 1),
    POSE(4, 0x3D, 1), POSE(5, 0x3E, 4), POSE(7, 0x3F, 4), POSE(5, 0x40, 5),
    POSE(3, 0x41, 5), POSE(3, 0x42, 4), POSE_JUMP(0xC),
};

static AnimationFrame D_us_80182230[] = {
    POSE_UNKNOWN(0),
    POSE_JUMP(4),
};

static AnimationFrame D_us_80182238[] = {
    POSE_UNKNOWN(0),
    POSE_JUMP(5),
};

static AnimationFrame D_us_80182240[] = {
    POSE(2, 0x39, 1), POSE(2, 0x3A, 1), POSE(2, 0x3B, 1), POSE(3, 0x3C, 1),
    POSE(3, 0x3D, 1), POSE(3, 0x3E, 4), POSE(3, 0x3F, 4), POSE(3, 0x40, 5),
    POSE(2, 0x41, 5), POSE(2, 0x42, 4), POSE_END,
};

static AnimationFrame D_us_8018226C[] = {
    POSE(3, 0x32, 1), POSE(3, 0x33, 1), POSE(3, 0x34, 1), POSE(3, 0x35, 1),
    POSE(3, 0x36, 1), POSE(3, 0x37, 1), POSE(3, 0x38, 1), POSE_END,
};

static AnimationFrame D_us_8018228C[] = {
    POSE_UNKNOWN(1),
    POSE_JUMP(0xD),
};

static AnimationFrame D_us_80182294[] = {
    POSE(3, 0x29, 1), POSE(2, 0x2A, 1), POSE(3, 0x2B, 1), POSE(2, 0x2C, 1),
    POSE(3, 0x2D, 1), POSE(2, 0x2E, 1), POSE(3, 0x2F, 1), POSE(2, 0x30, 1),
    POSE(3, 0x31, 1), POSE(2, 0x32, 1), POSE(3, 0x33, 1), POSE(2, 0x34, 1),
    POSE(3, 0x35, 1), POSE(2, 0x36, 1), POSE(3, 0x37, 1), POSE(2, 0x38, 1),
    POSE_LOOP(0),
};

static AnimationFrame D_us_801822D8[] = {
    POSE_UNKNOWN(2),  POSE(4, 0x50, 1), POSE(4, 0x51, 1), POSE(4, 0x52, 1),
    POSE(4, 0x53, 1), POSE(4, 0x54, 1), POSE(4, 0x55, 1), POSE(4, 0x54, 1),
    POSE(4, 0x55, 1), POSE_JUMP(4),
};

static AnimationFrame D_us_80182300[] = {
    POSE(4, 0x43, 6), POSE(4, 0x44, 6), POSE(4, 0x45, 6), POSE(4, 0x46, 6),
    POSE(4, 0x47, 6), POSE(4, 0x48, 6), POSE(4, 0x49, 6), POSE_END,
};

static AnimationFrame D_us_80182320[] = {
    POSE_UNKNOWN(2),  POSE(4, 0x4A, 1), POSE(4, 0x4B, 1), POSE(4, 0x4C, 1),
    POSE(4, 0x4D, 1), POSE(4, 0x4E, 1), POSE(4, 0x4F, 1), POSE(4, 0x4E, 1),
    POSE(4, 0x4F, 1), POSE_JUMP(3),
};

static AnimationFrame D_us_80182348[] = {
    POSE(2, 0x42, 4), POSE(2, 0x41, 5), POSE(3, 0x40, 5), POSE(3, 0x3F, 4),
    POSE(3, 0x3E, 4), POSE_UNKNOWN(2),  POSE_END,
};

static AnimationFrame D_us_80182364[] = {
    POSE(2, 2, 2), POSE(4, 3, 3), POSE(4, 4, 3),   POSE(4, 5, 3),
    POSE(4, 6, 3), POSE(4, 7, 3), POSE_UNKNOWN(3), POSE_END,
};

static AnimationFrame D_us_80182384[] = {
    POSE(4, 0x8, 3), POSE(4, 0x9, 3), POSE(4, 0xA, 3), POSE(4, 0xB, 3),
    POSE(4, 0xC, 3), POSE(4, 0xD, 3), POSE(4, 0xE, 3), POSE_END,
};

static AnimationFrame D_us_801823A4[] = {
    POSE(0xFF, 0xF, 3),
    POSE_LOOP(0),
};

static AnimationFrame D_us_801823AC[] = {
    POSE(0x10, 0xF, 3),
    POSE_END,
};

static AnimationFrame D_us_801823B4[] = {
    POSE(3, 0x10, 3),
    POSE(3, 0x11, 2),
    POSE(3, 0x12, 1),
    POSE_END,
};

static AnimationFrame D_us_801823C4[] = {
    POSE_UNKNOWN(3),
    POSE_JUMP(0x11),
};

static AnimationFrame D_us_801823CC[] = {
    POSE(1, 2, 2),  POSE(1, 4, 3),  POSE(1, 6, 3),  POSE(1, 8, 3),
    POSE(1, 10, 3), POSE(1, 12, 3), POSE(1, 14, 3), POSE_END,
};

static AnimationFrame D_us_801823EC[] = {
    POSE(5, 0x5F, 1),
    POSE(5, 0x60, 1),
    POSE_JUMP(0x17),
};

static AnimationFrame D_us_801823F8[] = {
    POSE(5, 0x61, 1), POSE(5, 0x62, 1),    POSE(5, 0x67, 1),
    POSE(5, 0x68, 1), POSE(0x40, 0x69, 1), POSE_END,
};

static AnimationFrame D_us_80182410[] = {
    POSE(5, 0x63, 7),
    POSE(5, 0x64, 8),
    POSE_JUMP(0x1A),
};

static AnimationFrame D_us_8018241C[] = {
    POSE(5, 0x64, 8),
    POSE(5, 0x63, 7),
    POSE_JUMP(0x17),
};

static AnimationFrame D_us_80182428[] = {
    POSE(3, 0x65, 8),
    POSE(3, 0x66, 8),
    POSE_LOOP(0),
};

static AnimationFrame D_us_80182434[] = {
    POSE(3, 0x6A, 7), POSE(4, 0x6B, 7), POSE(4, 0x6C, 7),
    POSE(4, 0x6D, 7), POSE_JUMP(0x1C),
};

static AnimationFrame D_us_80182448[] = {
    POSE(8, 0x6E, 7), POSE(5, 0x6F, 7),    POSE(5, 0x70, 7),
    POSE(5, 0x71, 7), POSE(0x41, 0x72, 7), POSE_END,
};

static AnimationFrame D_us_80182460[] = {
    POSE_UNKNOWN(4),  POSE(4, 0x51, 1), POSE(4, 0x52, 1),
    POSE(4, 0x53, 1), POSE(4, 0x54, 1), POSE(4, 0x55, 1),
    POSE(4, 0x54, 1), POSE(4, 0x55, 1), POSE_JUMP(4),
};

static AnimationFrame D_us_80182484[] = {
    POSE(5, 0x74, 4), POSE(5, 0x75, 4), POSE(5, 0x76, 2),
    POSE(5, 0x77, 1), POSE(5, 0x78, 1), POSE_END,
};

static AnimationFrame D_us_8018249C[] = {
    POSE_UNKNOWN(4),  POSE(4, 0x4C, 1), POSE(4, 0x4D, 1), POSE(4, 0x4E, 1),
    POSE(4, 0x4F, 1), POSE(4, 0x4E, 1), POSE(4, 0x4F, 1), POSE_JUMP(3),
};

static AnimationFrame D_us_801824BC[] = {
    POSE(3, 0x71, 7),
    POSE(0x42, 0x72, 7),
    POSE_END,
};

static AnimationFrame D_us_801824C8[] = {
    POSE(0x2, 0x1099, 8), POSE(0x2, 0x1098, 8),
    POSE(0x4, 0x1099, 8), POSE(0x3, 0x109A, 8),
    POSE(0x3, 0x109B, 8), POSE(0x3, 0x1065, 8),
    POSE(0x3, 0x1066, 8), POSE(0x3, 0x1065, 8),
    POSE(0x3, 0x1066, 8), POSE_END,
};

static AnimationFrame D_us_801824F0[] = {
    POSE(5, 0x5F, 1),
    POSE(5, 0x60, 1),
    POSE_JUMP(0x17),
};

static AnimationFrame D_us_801824FC[] = {
    POSE(0xFF, 0x73, 7),
    POSE_LOOP(0),
};

static AnimationFrame D_us_80182504[] = {
    POSE(3, 0x74, 7),    POSE(3, 0x3, 7), POSE(3, 0x4, 3), POSE(3, 0x5, 3),
    POSE(3, 0x6, 3),     POSE(3, 0x7, 3), POSE(3, 0x8, 3), POSE(3, 0x9, 3),
    POSE(3, 0xA, 3),     POSE(3, 0xB, 3), POSE(4, 0xC, 3), POSE(4, 0xD, 3),
    POSE(5, 0xE, 3),     POSE(7, 0xC, 3), POSE(5, 0xB, 3), POSE(4, 0xA, 3),
    POSE(4, 0x9, 3),     POSE(4, 0x8, 3), POSE(4, 0x7, 3), POSE(4, 0x6, 3),
    POSE(4, 0x5, 3),     POSE(4, 0x4, 3), POSE(4, 0x3, 3), POSE(0xFF, 0x74, 3),
    POSE(0xFF, 0x74, 3), POSE_END,
};

static AnimationFrame D_us_8018256C[] = {
    POSE(5, 0x9C, 3),
    POSE(6, 0x9D, 1),
    POSE(6, 0x9E, 5),
    POSE_END,
};

static AnimationFrame D_us_8018257C[] = {
    POSE(0x2, 0x127C, 9), POSE(0x2, 0x127D, 9),
    POSE(0x2, 0x127E, 9), POSE(0x2, 0x127F, 9),
    POSE(0x3, 0x127E, 9), POSE(0x2, 0x127C, 9),
    POSE(0x3, 0x127D, 9), POSE(0x4, 0x127C, 9),
    POSE(0x6, 0x1280, 9), POSE_END,
};

static AnimationFrame D_us_801825A4[] = {
    POSE(2, 0x81, 3), POSE(2, 0x82, 3), POSE(2, 0x83, 3),
    POSE(2, 0x84, 3), POSE(3, 0x83, 3), POSE(2, 0x81, 3),
    POSE(3, 0x82, 3), POSE(4, 0x81, 3), POSE_END,
};

static AnimationFrame D_us_801825C8[] = {
    POSE(0x2, 0x1085, 8), POSE(0x2, 0x1086, 8), POSE(0x2, 0x1087, 8),
    POSE(0x3, 0x1086, 8), POSE(0x3, 0x1085, 8), POSE_END,
};

static AnimationFrame D_us_801825E0[] = {
    POSE(2, 0x88, 7), POSE(2, 0x89, 7), POSE(2, 0x8A, 7),
    POSE(3, 0x89, 7), POSE(3, 0x88, 7), POSE_END,
};

static AnimationFrame D_us_801825F8[] = {
    POSE(3, 0x6E, 7),    POSE(11, 0x8B, 10), POSE(5, 0x8C, 7), POSE(5, 0x8D, 7),
    POSE(7, 0x6E, 7),    POSE(3, 0x6F, 7),   POSE(3, 0x70, 7), POSE(3, 0x71, 7),
    POSE(0xFF, 0x72, 7), POSE_END,
};

static AnimationFrame D_us_80182620[] = {
    POSE(0x30, 0x9F, 7),
    POSE_END,
};

static AnimationFrame D_us_80182628[] = {
    POSE(0x10, 0x9F, 7),
    POSE(7, 0xA1, 1),
    POSE(0x1C, 0xA2, 1),
    POSE_END,
};

static AnimationFrame D_us_80182638[] = {
    POSE(0x30, 0xA3, 1),
    POSE_END,
};

static AnimationFrame D_us_80182640[] = {
    POSE(9, 0xA5, 6), POSE(2, 0xA6, 6), POSE(2, 0xA5, 6),  POSE(3, 0xA6, 6),
    POSE(3, 0xA5, 6), POSE(3, 0xA6, 6), POSE(17, 0xA5, 6), POSE(3, 0x9F, 6),
    POSE(4, 0x11, 6), POSE(4, 0x12, 6), POSE_END,
};

static AnimationFrame D_us_8018266C[] = {
    POSE(9, 0xA7, 4), POSE(2, 0xA8, 4), POSE(2, 0xA7, 4),  POSE(3, 0xA8, 4),
    POSE(3, 0xA7, 4), POSE(3, 0xA8, 4), POSE(17, 0xA7, 4), POSE(3, 0x9F, 6),
    POSE(4, 0x11, 6), POSE(4, 0x12, 6), POSE_END,
};

static AnimationFrame D_us_80182698[] = {
    POSE(9, 0xA9, 4), POSE(2, 0xAA, 4), POSE(2, 0xA9, 4),  POSE(3, 0xAA, 4),
    POSE(3, 0xA9, 4), POSE(3, 0xAA, 4), POSE(17, 0xA9, 4), POSE(3, 0x11, 6),
    POSE(3, 0x12, 6), POSE_END,
};

static AnimationFrame D_us_801826C0[] = {
    POSE(9, 0xAB, 4), POSE(2, 0xAC, 4), POSE(2, 0xAB, 4),  POSE(3, 0xAC, 4),
    POSE(3, 0xAB, 4), POSE(3, 0xAC, 4), POSE(17, 0xAB, 4), POSE(3, 0x11, 6),
    POSE(3, 0x12, 6), POSE_END,
};

static AnimationFrame D_us_801826E8[] = {
    POSE(2, 0x9F, 7),
    POSE(2, 0xA0, 7),
    POSE_LOOP(0),
};

static AnimationFrame D_us_801826F4[] = {
    POSE(2, 0xA3, 1),
    POSE(2, 0xA4, 1),
    POSE_LOOP(0),
};

static AnimationFrame D_us_80182700[] = {
    POSE(5, 0x9F, 7), POSE(5, 0xA2, 1), POSE(5, 0xA3, 1),
    POSE(5, 0xA5, 6), POSE(5, 0xA9, 4), POSE_LOOP(0),
};

static AnimationFrame D_us_80182718[] = {
    POSE(0xF, 0xAD, 7),
    POSE_END,
};

static AnimationFrame D_us_80182720[] = {
    POSE(0xF, 0xAE, 7),
    POSE_END,
};

static AnimationFrame D_us_80182728[] = {
    POSE(0xF, 0xAF, 7),
    POSE_END,
};

static AnimationFrame D_us_80182730[] = {
    POSE(5, 0xA5, 6), POSE(2, 0xA6, 6), POSE(2, 0xA5, 6),  POSE(3, 0xA6, 6),
    POSE(3, 0xA5, 6), POSE(3, 0xA6, 6), POSE(17, 0xA5, 6), POSE(3, 0x11, 6),
    POSE(3, 0x12, 6), POSE_END,
};

static AnimationFrame D_us_80182758[] = {
    POSE(9, 0x9F, 7), POSE(4, 0xA1, 1),  POSE(4, 0xA2, 1), POSE(4, 0xA9, 4),
    POSE(4, 0xAA, 4), POSE(17, 0xB1, 7), POSE(8, 0xB2, 7), POSE(8, 0xB3, 7),
    POSE(5, 0x71, 7), POSE(66, 0x72, 7), POSE_END,
};

static AnimationFrame D_us_80182784[] = {
    POSE(3, 0xB5, 7), POSE(3, 0xB6, 7), POSE(3, 0xB7, 7), POSE(3, 0xB8, 7),
    POSE(3, 0xB4, 7), POSE(4, 0xB5, 7), POSE(4, 0xB6, 7), POSE(4, 0xB7, 7),
    POSE(4, 0xB8, 7), POSE(4, 0xB4, 7), POSE(5, 0xB5, 7), POSE(5, 0xB6, 7),
    POSE(5, 0xB7, 7), POSE(5, 0xB8, 7), POSE(5, 0xB4, 7), POSE(6, 0xB5, 7),
    POSE(6, 0xB6, 7), POSE(6, 0xB7, 7), POSE(6, 0xB8, 7), POSE(6, 0xB4, 7),
    POSE_END,
};

static AnimationFrame D_us_801827D8[] = {
    POSE(2, 0xB5, 7),    POSE(2, 0xB6, 7), POSE(2, 0xB7, 7),
    POSE(2, 0xB8, 7),    POSE(2, 0xB4, 7), POSE_UNKNOWN(0x1B),
    POSE(7, 0xB5, 7),    POSE(7, 0xB6, 7), POSE(7, 0xB7, 7),
    POSE(8, 0xB8, 7),    POSE(9, 0xB4, 7), POSE(0xA, 0xB5, 7),
    POSE(0x40, 0x9F, 7), POSE_END,
};

static AnimationFrame D_us_80182810[] = {
    POSE(2, 0xC7, 3),    POSE(2, 0xC8, 3), POSE(2, 0xC9, 3), POSE(2, 0xCA, 3),
    POSE(0x10, 0xCB, 3), POSE(2, 0xCC, 3), POSE(2, 0xCD, 3), POSE(1, 0xCE, 3),
    POSE(1, 0xCF, 3),    POSE_END,
};

static AnimationFrame D_us_80182838[] = {
    POSE_UNKNOWN(0x1B), POSE(7, 0xB5, 7), POSE(7, 0xB6, 7), POSE(7, 0xB7, 7),
    POSE(8, 0xA1, 7),   POSE(1, 0xA2, 7), POSE_END,
};

static AnimationFrame D_us_80182854[] = {
    POSE_UNKNOWN(0x1B), POSE(7, 0xB5, 7), POSE(7, 0xB6, 7),
    POSE(7, 0xB7, 7),   POSE_END,
};

static AnimationFrame D_us_80182868[] = {
    POSE(0x18, 0x8E, 1), POSE(4, 0x8F, 1),    POSE(4, 0x90, 1),
    POSE(4, 0x91, 1),    POSE(6, 0x92, 1),    POSE(7, 0x93, 1),
    POSE(4, 0x94, 1),    POSE(0x19, 0x95, 1), POSE(4, 0x96, 1),
    POSE(4, 0x97, 1),    POSE(4, 0xB0, 1),    POSE(2, 0x97, 1),
    POSE(2, 0x96, 1),    POSE(0x41, 0x95, 1), POSE(9, 0x93, 1),
    POSE(4, 0x92, 1),    POSE(3, 0x91, 1),    POSE(4, 0x90, 1),
    POSE(4, 0x8F, 1),    POSE(4, 0x8E, 1),    POSE_END,
};

static AnimationFrame D_us_801828BC[] = {
    POSE(4, 0x8E, 1),
    POSE_END,
};

static AnimationFrame D_us_801828C4[] = {
    POSE_UNKNOWN(5),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_801828D0[] = {
    POSE(0x4, 0x12BF, 9), POSE(6, 0xC0, 1), POSE(5, 0xC1, 1), POSE(5, 0xC2, 1),
    POSE(4, 0xC3, 1),     POSE(3, 0x54, 1), POSE(3, 0x55, 1), POSE_END,
};

static AnimationFrame D_us_801828F0[] = {
    POSE(0x2, 0x12B9, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x1, 0x12BB, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x2, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x4, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80182928[] = {
    POSE_UNKNOWN(5),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_80182934[] = {
    POSE(0x4, 0x12BF, 9), POSE(5, 0x57, 1),    POSE(4, 0x58, 1),
    POSE(3, 0x59, 1),     POSE(3, 0x5A, 1),    POSE(3, 0x5B, 1),
    POSE(3, 0x5C, 1),     POSE(0x40, 0x5D, 1), POSE_END,
};

static AnimationFrame D_us_80182958[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC5, 3), POSE(1, 0xC5, 3),  POSE(1, 0xC5, 3),
    POSE(1, 0xC5, 3), POSE_UNKNOWN(6),  POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182978[] = {
    POSE(4, 0xCB, 3), POSE(6, 0xCC, 3), POSE(5, 0xCD, 3),
    POSE(5, 0xCE, 3), POSE(5, 0xCF, 3), POSE(0x40, 0xF, 3),
};

static AnimationFrame D_us_80182990[] = {
    POSE(1, 0xC7, 3), POSE(1, 0xC7, 3), POSE(1, 0xC7, 3),
    POSE(2, 0xC7, 3), POSE(4, 0xC8, 3), POSE(4, 0xC9, 3),
    POSE(4, 0xCA, 3), POSE(4, 0xCB, 3), POSE_END,
};

static AnimationFrame D_us_801829B4[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC6, 3), POSE(1, 0xC6, 3),  POSE(1, 0xC6, 3),
    POSE(1, 0xC6, 3), POSE_UNKNOWN(6),  POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_801829D4[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7),  POSE(1, 0xD1, 7),
    POSE(2, 0xD1, 7), POSE_UNKNOWN(0xA), POSE_END,
};

static AnimationFrame D_us_801829EC[] = {
    POSE(1, 0xD2, 7), POSE(1, 0xD2, 7), POSE(1, 0xD2, 7),
    POSE(2, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_80182A04[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(2, 0xD5, 7), POSE_UNKNOWN(7),  POSE_END,
};

static AnimationFrame D_us_80182A1C[] = {
    POSE(1, 0xD7, 7), POSE(1, 0xD7, 7), POSE(1, 0xD7, 7),
    POSE(2, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_80182A34[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(2, 0xD6, 7), POSE_UNKNOWN(7),  POSE_END,
};

static AnimationFrame D_us_80182A4C[] = {
    POSE_UNKNOWN(8),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_80182A58[] = {
    POSE(0x1, 0x12B9, 9), POSE(0x1, 0x12B9, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x2, 0x12BA, 9),
    POSE(0x8, 0x12BA, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x1, 0x12BB, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x1, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x4, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80182A90[] = {
    POSE_UNKNOWN(8),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_80182A9C[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(2, 0xC5, 3),
    POSE(8, 0xC5, 3), POSE_UNKNOWN(9),  POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182ABC[] = {
    POSE(1, 0xC7, 3), POSE(1, 0xC7, 3), POSE(1, 0xC7, 3),
    POSE(2, 0xC7, 3), POSE(4, 0xC8, 3), POSE(4, 0xC9, 3),
    POSE(4, 0xCA, 3), POSE(8, 0xCB, 3), POSE_END,
};

static AnimationFrame D_us_80182AE0[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(2, 0xC6, 3),
    POSE(8, 0xC6, 3), POSE_UNKNOWN(9),  POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182B00[] = {
    POSE(1, 0xD0, 7), POSE(1, 0xD0, 7),  POSE(1, 0xD1, 7), POSE(2, 0xD1, 7),
    POSE(8, 0xD1, 7), POSE_UNKNOWN(0xA), POSE_END,
};

static AnimationFrame D_us_80182B1C[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD5, 7), POSE(2, 0xD5, 7),
    POSE(8, 0xD5, 7), POSE_UNKNOWN(7),  POSE_END,
};

static AnimationFrame D_us_80182B38[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD6, 7), POSE(2, 0xD6, 7),
    POSE(8, 0xD6, 7), POSE_UNKNOWN(7),  POSE_END,
};

static AnimationFrame D_us_80182B54[] = {
    POSE_UNKNOWN(0xB),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_80182B60[] = {
    POSE(0x1, 0x12B9, 9), POSE(0x1, 0x12B9, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x2, 0x12BA, 9), POSE(0x2, 0x12BA, 9), POSE(0x2, 0x12BA, 9),
    POSE(0x2, 0x12BA, 9), POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BB, 9), POSE(0x1, 0x12BB, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x1, 0x12BB, 9), POSE(0x4, 0x12BC, 9), POSE(0x4, 0x12BD, 9),
    POSE(0x4, 0x12BE, 9), POSE(0x4, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80182BA8[] = {
    POSE_UNKNOWN(0xB),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_80182BB4[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(2, 0xC5, 3),
    POSE(2, 0xC5, 3), POSE(2, 0xC5, 3), POSE(2, 0xC5, 3),  POSE(1, 0xC5, 3),
    POSE(1, 0xC5, 3), POSE_UNKNOWN(6),  POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182BE4[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(2, 0xC6, 3),
    POSE(2, 0xC6, 3), POSE(2, 0xC6, 3), POSE(2, 0xC6, 3),  POSE(1, 0xC6, 3),
    POSE(1, 0xC6, 3), POSE_UNKNOWN(6),  POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182C14[] = {
    POSE(1, 0xD0, 7), POSE(1, 0xD0, 7),  POSE(1, 0xD1, 7), POSE(2, 0xD1, 7),
    POSE(2, 0xD1, 7), POSE(2, 0xD1, 7),  POSE(2, 0xD1, 7), POSE(1, 0xD1, 7),
    POSE(1, 0xD1, 7), POSE_UNKNOWN(0xA), POSE_END,
};

static AnimationFrame D_us_80182C40[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD5, 7), POSE(2, 0xD5, 7),
    POSE(2, 0xD5, 7), POSE(2, 0xD5, 7), POSE(2, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(1, 0xD5, 7), POSE_UNKNOWN(7),  POSE_END,
};

static AnimationFrame D_us_80182C6C[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD6, 7), POSE(2, 0xD6, 7),
    POSE(2, 0xD6, 7), POSE(2, 0xD6, 7), POSE(2, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(1, 0xD6, 7), POSE_UNKNOWN(7),  POSE_END,
};

static AnimationFrame D_us_80182C98[] = {
    POSE_UNKNOWN(0xC),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_80182CA4[] = {
    POSE(0x2, 0x12B9, 9), POSE(0x1, 0x12B9, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x2, 0x12BA, 9), POSE(0x2, 0x12BA, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BA, 9), POSE(0x3, 0x12BA, 9),
    POSE(0x1, 0x12BB, 9), POSE(0x1, 0x12BB, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x1, 0x12BB, 9), POSE(0x4, 0x12BC, 9), POSE(0x4, 0x12BD, 9),
    POSE(0x4, 0x12BE, 9), POSE(0x8, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80182CEC[] = {
    POSE_UNKNOWN(0xC),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_80182CF8[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(2, 0xC5, 3),
    POSE(2, 0xC5, 3), POSE(1, 0xC5, 3), POSE(1, 0xC5, 3),  POSE(1, 0xC5, 3),
    POSE(3, 0xC5, 3), POSE_UNKNOWN(9),  POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182D28[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(2, 0xC6, 3),
    POSE(2, 0xC6, 3), POSE(1, 0xC6, 3), POSE(1, 0xC6, 3),  POSE(1, 0xC6, 3),
    POSE(3, 0xC6, 3), POSE_UNKNOWN(9),  POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182D58[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD0, 7),  POSE(1, 0xD1, 7), POSE(2, 0xD1, 7),
    POSE(2, 0xD1, 7), POSE(1, 0xD1, 7),  POSE(1, 0xD1, 7), POSE(1, 0xD1, 7),
    POSE(3, 0xD1, 7), POSE_UNKNOWN(0xA), POSE_END,
};

static AnimationFrame D_us_80182D84[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD5, 7), POSE(2, 0xD5, 7),
    POSE(2, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(3, 0xD5, 7), POSE_UNKNOWN(7),  POSE_END,
};

static AnimationFrame D_us_80182DB0[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD6, 7), POSE(2, 0xD6, 7),
    POSE(2, 0xD6, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(3, 0xD6, 7), POSE_UNKNOWN(7),  POSE_END,
};

static AnimationFrame D_us_80182DDC[] = {
    POSE(2, 0x7A, 1),     POSE(2, 0x7B, 1),     POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BB, 9), POSE(0x1, 0x12BC, 9), POSE(0x1, 0x12BD, 9),
    POSE(0x1, 0x12BE, 9), POSE(0x3, 0x12BF, 9), POSE(3, 0xC0, 1),
    POSE(3, 0xC1, 1),     POSE(3, 0xC2, 1),     POSE(3, 0xC3, 1),
    POSE(2, 0x54, 1),     POSE(2, 0x55, 1),     POSE_UNKNOWN(0x10),
    POSE_JUMP(2),
};

static AnimationFrame D_us_80182E1C[] = {
    POSE(5, 0x57, 1), POSE(4, 0x58, 1),    POSE(3, 0x59, 1),
    POSE(3, 0x5A, 1), POSE(3, 0x5B, 1),    POSE(3, 0x5C, 1),
    POSE(3, 0x5D, 1), POSE(0x10, 0x79, 1), POSE_JUMP(3),
};

static AnimationFrame D_us_80182E40[] = {
    POSE(4, 0x7A, 1),   POSE(4, 0x7B, 1),   POSE(4, 0x1, 1),
    POSE_UNKNOWN(0x10), POSE_UNKNOWN(0x11), POSE_JUMP(2),
};

static AnimationFrame D_us_80182E58[] = {
    POSE(6, 0x56, 2), POSE(6, 0x57, 1), POSE(6, 0x58, 1), POSE(6, 0x59, 1),
    POSE(6, 0x5A, 1), POSE(5, 0x5B, 1), POSE(3, 0x5C, 1), POSE(3, 0x5B, 1),
    POSE(2, 0x5C, 1), POSE(2, 0x5D, 1), POSE(2, 0x5C, 1), POSE(0x80, 0x5D, 1),
    POSE_JUMP(6),
};

static AnimationFrame D_us_80182E8C[] = {
    POSE(1, 0xC5, 3), POSE(1, 0xC7, 3), POSE(1, 0xC8, 3), POSE(1, 0xC9, 3),
    POSE(1, 0xCA, 3), POSE(1, 0xCB, 3), POSE(4, 0xCC, 3), POSE(3, 0xCD, 3),
    POSE(3, 0xCE, 3), POSE(3, 0xCF, 3), POSE(1, 0xF, 3),  POSE_END,
};

static AnimationFrame D_us_80182EBC[] = {
    POSE(2, 0x7A, 1),    POSE(2, 0x7A, 1), POSE(2, 0x7A, 1),
    POSE(0x40, 0x7B, 1), POSE_END,
};

static AnimationFrame D_us_80182ED0[] = {
    POSE(2, 0x81, 3),    POSE(2, 0x81, 3), POSE(2, 0x81, 3),
    POSE(0x40, 0x82, 3), POSE_END,
};

static AnimationFrame D_us_80182EE4[] = {
    POSE_UNKNOWN(2),  POSE(4, 0x50, 1), POSE(4, 0x51, 1), POSE(4, 0x52, 1),
    POSE(4, 0x53, 1), POSE(4, 0x54, 1), POSE(4, 0x55, 1), POSE(4, 0x54, 1),
    POSE(4, 0x55, 1), POSE_END,
};

static AnimationFrame D_us_80182F0C[] = {
    POSE_UNKNOWN(2),  POSE(4, 0x4A, 1), POSE(4, 0x4B, 1), POSE(4, 0x4C, 1),
    POSE(4, 0x4D, 1), POSE(4, 0x4E, 1), POSE(4, 0x4F, 1), POSE(4, 0x4E, 1),
    POSE(4, 0x4F, 1), POSE_END,
};

static AnimationFrame D_us_80182F34[] = {
    POSE_UNKNOWN(0x12),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_80182F40[] = {
    POSE(0x1, 0x12B9, 9), POSE(0x1, 0x12B9, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x2, 0x12BB, 9), POSE(0x2, 0x12BB, 9),
    POSE(0x2, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x8, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80182F78[] = {
    POSE_UNKNOWN(0x12),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_80182F84[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3),  POSE(1, 0xC5, 3), POSE(1, 0xC5, 3),
    POSE(1, 0xC5, 3), POSE(1, 0xC5, 3),  POSE(2, 0xC7, 3), POSE(2, 0xC7, 3),
    POSE(2, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182FC0[] = {
    POSE(1, 0xC4, 3),  POSE(1, 0xC4, 3), POSE(1, 0xC6, 3), POSE(2, 0xC6, 3),
    POSE(1, 0xC6, 3),  POSE(2, 0xC7, 3), POSE(2, 0xC7, 3), POSE(2, 0xC7, 3),
    POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3), POSE(8, 0xCB, 3),
    POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80182FF8[] = {
    POSE(1, 0xD0, 7), POSE(1, 0xD0, 7), POSE(1, 0xD1, 7), POSE(1, 0xD1, 7),
    POSE(1, 0xD1, 7), POSE(1, 0xD1, 7), POSE(1, 0xD2, 7), POSE(1, 0xD2, 7),
    POSE(2, 0xD2, 7), POSE(2, 0xD3, 7), POSE(2, 0xD3, 7), POSE(2, 0xD3, 7),
    POSE(2, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_80183030[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD7, 7), POSE(1, 0xD7, 7),
    POSE(2, 0xD7, 7), POSE(2, 0xD8, 7), POSE(2, 0xD8, 7), POSE(2, 0xD8, 7),
    POSE(2, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_80183068[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(1, 0xD6, 7), POSE(1, 0xD7, 7), POSE(1, 0xD7, 7), POSE(1, 0xD7, 7),
    POSE(2, 0xD8, 7), POSE(2, 0xD8, 7), POSE(2, 0xD8, 7), POSE(2, 0xD8, 7),
    POSE_END,
};

static AnimationFrame D_us_8018309C[] = {
    POSE(1, 0xD0, 1),     POSE(1, 0xD0, 2),     POSE(0x1, 0x26D1, 0x13),
    POSE(1, 0xD1, 4),     POSE(0x10, 0xD1, 4),  POSE(1, 0xBA, 4),
    POSE(1, 0xBA, 4),     POSE(1, 0xBB, 5),     POSE(1, 0xBB, 6),
    POSE(1, 0xBB, 7),     POSE(0x2, 0x10BC, 8), POSE(0x2, 0x10BD, 8),
    POSE(0x2, 0x10BE, 8), POSE(0x2, 0x10BF, 8), POSE_END,
};

static AnimationFrame D_us_801830D8[] = {
    POSE_UNKNOWN(0x1C),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_801830E4[] UNUSED = {
    POSE_UNKNOWN(0x1C),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_801830F0[] = {
    POSE(0x2, 0x127C, 9), POSE(0x2, 0x127D, 9), POSE(0x1, 0x127E, 9),
    POSE(0x1, 0x127F, 9), POSE(0x2, 0x127E, 9), POSE(0x2, 0x127D, 9),
    POSE(0x4, 0x127C, 9), POSE(0x5, 0x1280, 9), POSE_END,
};

static AnimationFrame D_us_80183114[] = {
    POSE(2, 0x81, 3), POSE(2, 0x82, 3), POSE(1, 0x83, 3), POSE(1, 0x84, 3),
    POSE(2, 0x83, 3), POSE(2, 0x82, 3), POSE(4, 0x81, 3), POSE_END,
};

static AnimationFrame D_us_80183134[] = {
    POSE(0x1, 0x1085, 8), POSE(0x1, 0x1086, 8), POSE(0x1, 0x1087, 8),
    POSE(0x2, 0x1086, 8), POSE(0x2, 0x1085, 8), POSE_END,
};

static AnimationFrame D_us_8018314C[] = {
    POSE(1, 0x88, 7),
    POSE(4, 0x89, 7),
    POSE(2, 0x88, 7),
    POSE_END,
};

static AnimationFrame D_us_8018315C[] = {
    POSE_UNKNOWN(0x13),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_80183168[] = {
    POSE(0x2, 0x12B9, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x3, 0x12BA, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x3, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x8, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80183190[] = {
    POSE_UNKNOWN(0x13),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_8018319C[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(3, 0xC5, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_801831C8[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(3, 0xC6, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_801831F4[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7), POSE(3, 0xD1, 7), POSE(1, 0xD2, 7),
    POSE(3, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_80183210[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(3, 0xD5, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_8018322C[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD6, 7), POSE(3, 0xD6, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_80183248[] = {
    POSE(0x1, 0x127C, 9), POSE(0x1, 0x127D, 9), POSE(0x1, 0x127E, 9),
    POSE(0x1, 0x127F, 9), POSE(0x2, 0x127E, 9), POSE(0x2, 0x127D, 9),
    POSE(0x4, 0x127C, 9), POSE(0x5, 0x1280, 9), POSE_END,
};

static AnimationFrame D_us_8018326C[] = {
    POSE(1, 0x81, 3), POSE(1, 0x82, 3), POSE(1, 0x83, 3), POSE(1, 0x84, 3),
    POSE(2, 0x83, 3), POSE(2, 0x82, 3), POSE(4, 0x81, 3), POSE_END,
};

static AnimationFrame D_us_8018328C[] = {
    POSE_UNKNOWN(0x14),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_80183298[] = {
    POSE(0x2, 0x12B9, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x2, 0x12BA, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x3, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x8, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_801832C0[] = {
    POSE_UNKNOWN(0x14),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_801832CC[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(2, 0xC5, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_801832F8[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(2, 0xC6, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80183324[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7), POSE(2, 0xD1, 7), POSE(1, 0xD2, 7),
    POSE(3, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_80183340[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(2, 0xD5, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_8018335C[] = {
    POSE_UNKNOWN(0x15),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_80183368[] = {
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

static AnimationFrame D_us_801833B4[] = {
    POSE_UNKNOWN(0x15),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_801833C0[] = {
    POSE(2, 0x81, 3), POSE(2, 0x82, 3), POSE(1, 0x83, 3),  POSE(1, 0x84, 3),
    POSE(2, 0x83, 3), POSE(2, 0x83, 3), POSE(2, 0x82, 3),  POSE(2, 0x81, 3),
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(3, 0xC6, 3),
    POSE(1, 0xC7, 3), POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3),
    POSE(4, 0xCA, 3), POSE(4, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80183410[] = {
    POSE(1, 0xD0, 7), POSE(1, 0xD0, 7), POSE(1, 0xD1, 7), POSE(3, 0xD1, 7),
    POSE(1, 0xD2, 7), POSE(3, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_80183430[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD5, 7), POSE(3, 0xD5, 7),
    POSE(1, 0xD7, 7), POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_80183450[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD6, 7), POSE(3, 0xD6, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_8018346C[] = {
    POSE_UNKNOWN(0x16),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_80183478[] = {
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

static AnimationFrame D_us_801834AC[] = {
    POSE_UNKNOWN(0x16),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_801834B8[] = {
    POSE(2, 0xC4, 3),  POSE(1, 0xC5, 3), POSE(1, 0xC5, 3), POSE(1, 0xC5, 3),
    POSE(1, 0xC5, 3),  POSE(1, 0xC5, 3), POSE(1, 0xC7, 3), POSE(3, 0xC7, 3),
    POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3), POSE(8, 0xCB, 3),
    POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_801834F0[] = {
    POSE(2, 0xC4, 3),  POSE(1, 0xC6, 3), POSE(1, 0xC6, 3), POSE(1, 0xC6, 3),
    POSE(1, 0xC6, 3),  POSE(1, 0xC6, 3), POSE(1, 0xC7, 3), POSE(3, 0xC7, 3),
    POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3), POSE(8, 0xCB, 3),
    POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80183528[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7), POSE(1, 0xD1, 7), POSE(1, 0xD1, 7),
    POSE(1, 0xD1, 7), POSE(1, 0xD1, 7), POSE(1, 0xD2, 7), POSE(3, 0xD2, 7),
    POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_80183550[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD7, 7), POSE(3, 0xD7, 7),
    POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_80183578[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(1, 0xD6, 7), POSE(1, 0xD6, 7), POSE(1, 0xD7, 7), POSE(3, 0xD7, 7),
    POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_801835A0[] = {
    POSE_UNKNOWN(0x17),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_801835AC[] = {
    POSE(0x2, 0x12B9, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x3, 0x12BA, 9), POSE(0x2, 0x12BB, 9),
    POSE(0x2, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x8, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_801835D4[] = {
    POSE_UNKNOWN(0x17),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_801835E0[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(3, 0xC5, 3), POSE(2, 0xC7, 3),
    POSE(2, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_8018360C[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7), POSE(3, 0xD1, 7), POSE(2, 0xD2, 7),
    POSE(2, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_80183628[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(3, 0xD5, 7), POSE(2, 0xD7, 7),
    POSE(2, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_80183644[] = {
    POSE_UNKNOWN(0x18),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_80183650[] = {
    POSE(0x3, 0x12B9, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x4, 0x12BA, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x3, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x8, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80183678[] = {
    POSE_UNKNOWN(0x18),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_80183684[] = {
    POSE(3, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(4, 0xC5, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_801836B0[] = {
    POSE(3, 0xD0, 7), POSE(1, 0xD1, 7), POSE(4, 0xD1, 7), POSE(1, 0xD2, 7),
    POSE(3, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_801836CC[] = {
    POSE(3, 0xD4, 7), POSE(1, 0xD5, 7), POSE(4, 0xD5, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_801836E8[] = {
    POSE_UNKNOWN(0x19),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_801836F4[] = {
    POSE(0x4, 0x12B9, 9), POSE(0x2, 0x12BA, 9),
    POSE(0x3, 0x12BA, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x3, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x8, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_8018371C[] = {
    POSE_UNKNOWN(0x19),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_80183728[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(3, 0xC5, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80183754[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(3, 0xC6, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF), POSE_END,
};

static AnimationFrame D_us_80183780[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7), POSE(3, 0xD1, 7), POSE(1, 0xD2, 7),
    POSE(3, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_8018379C[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(3, 0xD5, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_801837B8[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD6, 7), POSE(3, 0xD6, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_us_801837D4[] = {
    POSE_UNKNOWN(0x1A),
    POSE_UNKNOWN(0xD),
    POSE_END,
};

static AnimationFrame D_us_801837E0[] = {
    POSE(0x1, 0x12B9, 9), POSE(0x1, 0x12B9, 9),
    POSE(0x1, 0x12B9, 9), POSE(0x1, 0x12B9, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BA, 9),
    POSE(0x1, 0x12BA, 9), POSE(0x1, 0x12BB, 9),
    POSE(0x3, 0x12BB, 9), POSE(0x4, 0x12BC, 9),
    POSE(0x4, 0x12BD, 9), POSE(0x4, 0x12BE, 9),
    POSE(0x8, 0x12BF, 9), POSE_END,
};

static AnimationFrame D_us_80183820[] = {
    POSE_UNKNOWN(0x1A),
    POSE_UNKNOWN(0xE),
    POSE_END,
};

static AnimationFrame D_us_8018382C[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC4, 3),
    POSE(1, 0xC5, 3), POSE(1, 0xC5, 3), POSE(1, 0xC5, 3), POSE(1, 0xC5, 3),
    POSE(1, 0xC5, 3), POSE(1, 0xC7, 3), POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),
    POSE(4, 0xC9, 3), POSE(4, 0xCA, 3), POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF),
    POSE_END,
};

static AnimationFrame D_us_80183870[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC4, 3),
    POSE(1, 0xC6, 3), POSE(1, 0xC6, 3), POSE(1, 0xC6, 3), POSE(1, 0xC6, 3),
    POSE(1, 0xC6, 3), POSE(1, 0xC7, 3), POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),
    POSE(4, 0xC9, 3), POSE(4, 0xCA, 3), POSE(8, 0xCB, 3), POSE_UNKNOWN(0xF),
    POSE_END,
};

static AnimationFrame D_us_801838B4[] = {
    POSE(1, 0xD0, 7), POSE(1, 0xD0, 7), POSE(1, 0xD0, 7), POSE(1, 0xD0, 7),
    POSE(1, 0xD1, 7), POSE(1, 0xD1, 7), POSE(1, 0xD1, 7), POSE(1, 0xD1, 7),
    POSE(1, 0xD1, 7), POSE(1, 0xD2, 7), POSE(3, 0xD2, 7), POSE(8, 0xD3, 7),
    POSE_END,
};

static AnimationFrame D_us_801838E8[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD4, 7),
    POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(1, 0xD5, 7), POSE(1, 0xD7, 7), POSE(3, 0xD7, 7), POSE(8, 0xD8, 7),
    POSE_END,
};

static AnimationFrame D_us_8018391C[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD4, 7),
    POSE(1, 0xD6, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(1, 0xD6, 7), POSE(1, 0xD7, 7), POSE(3, 0xD7, 7), POSE(8, 0xD8, 7),
    POSE_END,
};

static AnimationFrame D_us_80183950[] = {
    POSE(2, 0xC3, 1), POSE(2, 0xC2, 1),    POSE(2, 0xC1, 1), POSE(2, 0xC0, 1),
    POSE(2, 0xBF, 1), POSE(2, 0xC0, 1),    POSE(2, 0xBF, 1), POSE(2, 0xC0, 1),
    POSE(2, 0xBF, 1), POSE(0x24, 0xC0, 1), POSE_END,
};

static AnimationFrame D_us_8018397C[] = {
    POSE(2, 0xC7, 3), POSE(2, 0xC8, 3),    POSE(2, 0xC9, 3), POSE(2, 0xCA, 3),
    POSE(2, 0xC9, 3), POSE(2, 0xCA, 3),    POSE(2, 0xC9, 3), POSE(2, 0xCA, 3),
    POSE(2, 0xC9, 3), POSE(0x18, 0xCA, 3), POSE_END,
};

static AnimationFrame D_us_801839A8[] = {
    POSE(2, 0xD2, 7), POSE(2, 0xD3, 7),    POSE(2, 0xD2, 7), POSE(2, 0xD3, 7),
    POSE(2, 0xD2, 7), POSE(0x24, 0xD3, 7), POSE_END,
};

static AnimationFrame D_us_801839C4[] UNUSED = {
    POSE(0x30, 0x7B, 1),
    POSE_END,
};

static AnimationFrame D_us_801839CC[] = {
    POSE(0x30, 0x79, 1),
    POSE_END,
};

static AnimationFrame D_us_801839D4[] = {
    POSE(3, 0x67, 1), POSE(3, 0x68, 1),    POSE(3, 0x69, 1),
    POSE(3, 0x68, 1), POSE(3, 0x69, 1),    POSE(3, 0x68, 1),
    POSE(3, 0x69, 1), POSE(3, 0x68, 1),    POSE(0x18, 0x69, 1),
    POSE(4, 0x78, 1), POSE(0x20, 0x79, 1), POSE_END,
};

static AnimationFrame D_us_80183A04[] = {
    POSE(6, 0x79, 1),
    POSE(6, 0x7A, 1),
    POSE(0x10, 0x7B, 1),
    POSE_END,
};

static AnimationFrame D_us_80183A14[] = {
    POSE(6, 0x79, 1),
    POSE(6, 0x7A, 1),
    POSE(0x10, 0x79, 1),
    POSE_END,
};

static AnimationFrame D_us_80183A24[] = {
    POSE(4, 0x8E, 1),    POSE(4, 0x8F, 1), POSE(4, 0x90, 1),
    POSE(0x14, 0x91, 1), POSE(4, 0x90, 1), POSE(4, 0x8F, 1),
    POSE(0x10, 0x8E, 1), POSE_JUMP(4),
};

static AnimationFrame D_us_80183A44[] = {
    POSE(0x28, 0, 0),
    POSE_END,
};

static AnimationFrame D_us_80183A4C[] = {
    POSE(0x2, 0x1E01, 0xF), POSE(0x3, 0x1E02, 0xF), POSE(0x4, 0x1E03, 0xF),
    POSE(0x4, 0x1E04, 0xF), POSE(0x3, 0x1E05, 0xF), POSE(0x2, 0x1E06, 0xF),
    POSE(0x2, 0x1E07, 0xF), POSE(0x2, 0x1E08, 0xF), POSE(0x2, 0x1E09, 0xF),
    POSE(0x2, 0x1E0A, 0xF), POSE_LOOP(0),
};

static AnimationFrame D_us_80183A78[] = {
    POSE(0x1, 0x1E0C, 0xF), POSE(0x1, 0x1E0D, 0xF), POSE(0x1, 0x1E0F, 0xF),
    POSE(0x1, 0x1E10, 0xF), POSE(0x1, 0x1E0E, 0xF), POSE(0x1, 0x1E0D, 0xF),
    POSE(0x1, 0x1E0C, 0xF), POSE(0x1, 0x1E0D, 0xF), POSE(0x1, 0x1E0F, 0xF),
    POSE(0x2, 0x1E10, 0xF), POSE(0x2, 0x1E0E, 0xF), POSE(0x2, 0x1E0D, 0xF),
    POSE(0x2, 0x1E0C, 0xF), POSE(0x2, 0x1E0D, 0xF), POSE(0x2, 0x1E0F, 0xF),
    POSE(0x3, 0x1E10, 0xF), POSE(0x3, 0x1E0E, 0xF), POSE(0x3, 0x1E0D, 0xF),
    POSE_JUMP(0xC4),
};

static AnimationFrame D_us_80183AC4[] = {
    POSE(0x3, 0x1E01, 0xF), POSE(0x4, 0x1E02, 0xF), POSE(0x6, 0x1E03, 0xF),
    POSE(0x6, 0x1E04, 0xF), POSE(0x5, 0x1E05, 0xF), POSE(0x4, 0x1E06, 0xF),
    POSE(0x4, 0x1E07, 0xF), POSE(0x3, 0x1E08, 0xF), POSE(0x3, 0x1E09, 0xF),
    POSE(0x3, 0x1E0A, 0xF), POSE_LOOP(0),
};

static AnimationFrame D_us_80183AF0[] = {
    POSE(0x4, 0x1E02, 0xF), POSE(0x6, 0x1E03, 0xF), POSE(0x6, 0x1E04, 0xF),
    POSE(0x5, 0x1E05, 0xF), POSE(0x4, 0x1E06, 0xF), POSE(0x4, 0x1E07, 0xF),
    POSE(0x3, 0x1E08, 0xF), POSE(0x3, 0x1E09, 0xF), POSE(0x3, 0x1E0A, 0xF),
    POSE(0x3, 0x1E01, 0xF), POSE_LOOP(9),
};

static AnimationFrame D_us_80183B1C[] = {
    POSE(0x6, 0x1E03, 0xF),
    POSE_END,
};

static AnimationFrame D_us_80183B24[] = {
    POSE(0x4, 0x1EC7, 0xF), POSE(0x4, 0x1EC8, 0xF),
    POSE(0x4, 0x1EC9, 0xF), POSE(0x4, 0x1ECA, 0xF),
    POSE(0x4, 0x1ECB, 0xF), POSE(0x6, 0x1ECC, 0xF),
    POSE(0x5, 0x1ECD, 0xF), POSE(0x5, 0x1ECE, 0xF),
    POSE(0x5, 0x1ECF, 0xF), POSE_END,
};

static AnimationFrame D_us_80183B4C[] = {
    POSE(0x4, 0x1ECE, 0xF),
    POSE(0x4, 0x1ECD, 0xF),
    POSE(0x6, 0x1ECC, 0xF),
    POSE(0x5, 0x1ECD, 0xF),
    POSE(0x5, 0x1ECE, 0xF),
    POSE(0x5, 0x1ECF, 0xF),
    POSE_END,
};

static AnimationFrame D_us_80183B68[] = {
    POSE(0x1, 0x1E0C, 0xF), POSE(0x1, 0x1E0D, 0xF), POSE(0x1, 0x1E0F, 0xF),
    POSE(0x1, 0x1E10, 0xF), POSE(0x1, 0x1E0E, 0xF), POSE(0x1, 0x1E0D, 0xF),
    POSE(0x1, 0x1E0C, 0xF), POSE(0x1, 0x1E0D, 0xF), POSE(0x1, 0x1E0F, 0xF),
    POSE(0x1, 0x1E10, 0xF), POSE(0x4, 0x1E0E, 0xF), POSE_END,
};

// n.b.! not `static`
AnimationFrame D_us_80183B98[] = {
    POSE(0x80, 0, 0),
    POSE_END,
};

static AnimationFrame D_us_80183BA0[] = {
    POSE(0x84, 0x5F, 0),
    POSE_END,
};

static AnimationFrame D_us_80183BA8[] = {
    POSE(0x84, 0xC7, 0),
    POSE_END,
};

static AnimationFrame D_us_80183BB0[] = {
    POSE(3, 0x1, 1), POSE(2, 0x2, 1), POSE(2, 0x3, 1), POSE(3, 0x4, 1),
    POSE(2, 0x3, 1), POSE(2, 0x2, 1), POSE_LOOP(0),
};

static AnimationFrame D_us_80183BCC[] = {
    POSE(1, 0x5, 1),
    POSE(0x10, 0x6, 1),
    POSE_END,
};

static AnimationFrame D_us_80183BD8[] = {
    POSE(0x80, 0x3, 1), POSE(1, 0x2, 1), POSE(0x10, 0x2, 1),
    POSE(0x10, 0x3, 1), POSE(1, 0x2, 1), POSE(0x10, 0x2, 1),
    POSE(0x10, 0x3, 1), POSE(1, 0x2, 1), POSE(0x10, 0x2, 1),
    POSE(0x10, 0x3, 1), POSE(1, 0x2, 1), POSE(0x80, 0x2, 1),
    POSE_LOOP(0),
};

static AnimationFrame D_us_80183C0C[] = {
    POSE(0x80, 0x2, 1),
    POSE_END,
};

static AnimationFrame D_us_80183C14[] = {
    POSE(0x80, 0x8, 1),
    POSE_END,
};

static AnimationFrame D_us_80183C1C[] = {
    POSE(1, 0xC, 3),     POSE(1, 0xB, 3), POSE(1, 0xA, 3),
    POSE(0x18, 0x82, 3), POSE(1, 0xF, 3), POSE_END,
};

static AnimationFrame D_us_80183C34[] = {
    POSE(1, 0x10, 1),    POSE(1, 0x11, 1), POSE(1, 0x12, 1),
    POSE(0x14, 0x7D, 1), POSE(4, 0x7A, 1), POSE_JUMP(4),
};

static AnimationFrame D_us_80183C4C[] = {
    POSE(2, 0x1A, 0),    POSE(2, 0x1B, 0), POSE(2, 0x1C, 0),
    POSE(2, 0x1D, 0),    POSE(2, 0x1E, 0), POSE(2, 0x1F, 0),
    POSE(2, 0xD0, 0),    POSE(4, 0xD1, 0), POSE(5, 0xD2, 0),
    POSE(0x10, 0xD3, 0), POSE(2, 0x6A, 0), POSE(2, 0x6B, 0),
    POSE(2, 0x6C, 0),    POSE(2, 0x6D, 0), POSE(3, 0x6E, 0),
    POSE(1, 0x6E, 0),    POSE(0x80, 1, 0), POSE_END,
};

static AnimationFrame D_us_80183C94[] = {
    POSE(2, 0x1A, 0), POSE(2, 0x1B, 0), POSE(2, 0x1C, 0), POSE(2, 0x1D, 0),
    POSE(2, 0x1E, 0), POSE(2, 0x1F, 0), POSE(2, 0xD0, 0), POSE(4, 0xD1, 0),
    POSE(5, 0xD2, 0), POSE(4, 0xD3, 0), POSE(2, 0xD0, 0), POSE(4, 0xD1, 0),
    POSE(5, 0xD2, 0), POSE(4, 0xD3, 0), POSE(2, 0x6A, 0), POSE(2, 0x6B, 0),
    POSE(2, 0x6C, 0), POSE(2, 0x6D, 0), POSE(3, 0x6E, 0), POSE(1, 0x6E, 0),
    POSE(0x80, 1, 0), POSE_END,
};

static AnimationFrame D_us_80183CEC[] = {
    POSE_UNKNOWN(2),
    POSE(4, 0x78, 1),
    POSE(0x40, 0x79, 1),
    POSE_END,
};

u8 D_us_80183CFC[][4] = {
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

AnimationFrame* D_us_80183D40[] = {
    D_us_801820B4, D_us_801820CC, D_us_801820D4, D_us_801820E8, D_us_801820F0,
    D_us_8018214C, D_us_80182180, D_us_801821A0, D_us_801821E4, D_us_80182204,
    D_us_80182230, D_us_80182238, D_us_8018228C, D_us_80182294, D_us_801822D8,
    D_us_80182320, D_us_80182364, D_us_801823A4, D_us_801823AC, D_us_801823B4,
    D_us_801823C4, D_us_801823CC, D_us_801823EC, D_us_801823F8, D_us_80182410,
    D_us_8018241C, D_us_80182428, D_us_80182434, D_us_80182448, D_us_80182460,
    D_us_8018249C, D_us_801824BC, D_us_801824C8, D_us_801824F0, D_us_801824FC,
    D_us_80182810, D_us_8018257C, D_us_8018257C, D_us_801825A4, D_us_801825A4,
    D_us_801825C8, D_us_801825E0, D_us_801825F8, D_us_80182504, D_us_80182504,
    D_us_8018256C, D_us_80182620, D_us_80182628, D_us_80182638, D_us_80182640,
    D_us_8018266C, D_us_80182698, D_us_801826C0, D_us_801826E8, D_us_801826F4,
    D_us_80182700, D_us_80182718, D_us_80182720, D_us_80182728, D_us_80182730,
    D_us_80182868, D_us_801828BC, D_us_80183A44, D_us_80182758, D_us_801827D8,
    D_us_801828C4, D_us_80182928, D_us_80182958, D_us_801829B4, D_us_801829D4,
    D_us_80182A04, D_us_80182A34, D_us_80182A4C, D_us_80182A90, D_us_80182A9C,
    D_us_80182AE0, D_us_80182B00, D_us_80182B1C, D_us_80182B38, D_us_80182B54,
    D_us_80182BA8, D_us_80182BB4, D_us_80182BE4, D_us_80182C14, D_us_80182C40,
    D_us_80182C6C, D_us_80182C98, D_us_80182CEC, D_us_80182CF8, D_us_80182D28,
    D_us_80182D58, D_us_80182D84, D_us_80182DB0, D_us_80182DDC, D_us_80182E1C,
    D_us_80182E8C, D_us_80182E40, D_us_80182E58, D_us_80182E8C, D_us_80182EBC,
    D_us_80182EBC, D_us_80182ED0, D_us_80182EE4, D_us_80182F0C, D_us_80182F34,
    D_us_80182F78, D_us_80182F84, D_us_80182FC0, D_us_80182FF8, D_us_80183030,
    D_us_80183068, D_us_801830F0, D_us_801830F0, D_us_80183114, D_us_80183114,
    D_us_80183134, D_us_8018314C, D_us_8018314C, D_us_8018315C, D_us_80183190,
    D_us_8018319C, D_us_801831C8, D_us_801831F4, D_us_80183210, D_us_8018322C,
    D_us_80183248, D_us_80183248, D_us_8018326C, D_us_8018326C, D_us_80183134,
    D_us_8018314C, D_us_8018314C, D_us_8018328C, D_us_801832C0, D_us_801832CC,
    D_us_801832F8, D_us_80183324, D_us_80183340, D_us_80183340, D_us_8018335C,
    D_us_801833B4, D_us_801833C0, D_us_801833C0, D_us_80183410, D_us_80183430,
    D_us_80183450, D_us_8018346C, D_us_801834AC, D_us_801834B8, D_us_801834F0,
    D_us_80183528, D_us_80183550, D_us_80183578, D_us_801835A0, D_us_801835D4,
    D_us_801835E0, D_us_801835E0, D_us_8018360C, D_us_80183628, D_us_80183628,
    D_us_80183644, D_us_80183678, D_us_80183684, D_us_80183684, D_us_801836B0,
    D_us_801836CC, D_us_801836CC, D_us_801836E8, D_us_8018371C, D_us_80183728,
    D_us_80183754, D_us_80183780, D_us_8018379C, D_us_801837B8, D_us_801837D4,
    D_us_80183820, D_us_8018382C, D_us_80183870, D_us_801838B4, D_us_801838E8,
    D_us_8018391C, D_us_80183950, D_us_8018397C, D_us_801839A8, D_us_801839CC,
    D_us_801839CC, D_us_801839D4, D_us_801839D4, D_us_80183A04, D_us_80183A14,
    D_us_80183A24, D_us_80183A24, D_us_80182838, D_us_80182854, D_us_80183A4C,
    D_us_80183A78, D_us_80183AC4, D_us_80183AF0, D_us_80183B1C, D_us_80183B24,
    D_us_80183B4C, D_us_80183B68, D_us_80183B98, D_us_80183BA0, D_us_80183BA8,
    D_us_80183BB0, D_us_80183BCC, D_us_80183BD8, D_us_80183C0C, D_us_80183C14,
    D_us_80183C34, D_us_80183C34, D_us_80183C1C, D_us_80183C1C, D_us_801830D8,
    D_us_801830D8, D_us_80183C4C, D_us_80183C94, D_us_80183CEC, D_us_80182348,
};

AnimationFrame* g_DopAnimationFrames[] = {
    D_us_80182240, D_us_8018226C, D_us_80182300, D_us_80182384, D_us_80182484,
    D_us_801828F0, D_us_80182990, D_us_80182A1C, D_us_80182A58, D_us_80182ABC,
    D_us_801829EC, D_us_80182B60, D_us_80182CA4, D_us_801828D0, D_us_80182934,
    D_us_80182978, D_us_80182114, D_us_80182130, D_us_80182F40, D_us_80183168,
    D_us_80183298, D_us_80183368, D_us_80183478, D_us_801835AC, D_us_80183650,
    D_us_801836F4, D_us_801837E0, D_us_80182784, D_us_8018309C,
};
