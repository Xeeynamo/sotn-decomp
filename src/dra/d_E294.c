// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"

static AnimationFrame D_800AE2A8[] = {
    POSE(4, 0x7A, 1), POSE(80, 0x7B, 1), POSE_END,
    POSE(8, 0x7B, 1), POSE(24, 0x7C, 9), POSE_LOOP(1),
};

static AnimationFrame D_800AE2C0[] = {
    POSE(80, 0x79, 1),
    POSE_END,
};

static AnimationFrame D_800AE2C8[] = {
    POSE(255, 0x01, 1), POSE(255, 0x01, 1), POSE(255, 0x01, 1),
    POSE(255, 0x01, 1), POSE_JUMP(6),
};

static AnimationFrame D_800AE2DC[] = {
    POSE(255, 0x4F, 1),
    POSE_LOOP(0),
};

static AnimationFrame D_800AE2E4[] = {
    POSE(-3, 0x10, 0), POSE(-3, 0x11, 0), POSE(6, 0x13, 1),
    POSE(6, 0x14, 1),  POSE(6, 0x15, 1),  POSE(6, 0x16, 1),
    POSE(6, 0x17, 1),  POSE(6, 0x18, 1),  POSE_JUMP(2),
};

static AnimationFrame D_800AE308[] = {
    POSE(4, 0x13, 1), POSE(4, 0x14, 1), POSE(4, 0x15, 1), POSE(4, 0x16, 1),
    POSE(4, 0x17, 1), POSE(4, 0x18, 1), POSE_END,
};

static AnimationFrame D_800AE324[] = {
    POSE(5, 0x13, 1), POSE(5, 0x14, 1), POSE(5, 0x15, 1), POSE(5, 0x16, 1),
    POSE(5, 0x17, 1), POSE(5, 0x18, 1), POSE_END,
};

static AnimationFrame D_800AE340[] = {
    POSE(6, 0x56, 2), POSE(6, 0x57, 1), POSE(6, 0x58, 1), POSE(6, 0x59, 1),
    POSE(6, 0x5A, 1), POSE(5, 0x5B, 1), POSE(3, 0x5C, 1), POSE(3, 0x5B, 1),
    POSE(2, 0x5C, 1), POSE(2, 0x5D, 1), POSE(2, 0x5C, 1), POSE(128, 0x5D, 1),
    POSE_JUMP(6),
};

static AnimationFrame D_800AE374[] = {
    POSE(192, 0x5D, 1), POSE(7, 0x5C, 1), POSE(3, 0x5B, 1),   POSE(4, 0x5C, 1),
    POSE(11, 0x5D, 1),  POSE(8, 0x5E, 1), POSE(160, 0x4F, 1), POSE_JUMP(3),
};

static AnimationFrame D_800AE394[] = {
    POSE(3, 0x19, 1), POSE(3, 0x1A, 1), POSE(3, 0x1B, 1), POSE(3, 0x1C, 1),
    POSE(3, 0x1D, 4), POSE(3, 0x1E, 4), POSE(3, 0x1F, 5), POSE(3, 0x20, 5),
    POSE(3, 0x21, 5), POSE(3, 0x22, 5), POSE(3, 0x23, 5), POSE(3, 0x24, 5),
    POSE(3, 0x25, 4), POSE(3, 0x26, 4), POSE(3, 0x27, 4), POSE(3, 0x28, 4),
    POSE_JUMP(8),
};

static AnimationFrame D_800AE3D8[] = {
    POSE(3, 0x2C, 1), POSE(3, 0x2D, 1), POSE(3, 0x2E, 1),  POSE(3, 0x2F, 1),
    POSE(3, 0x30, 1), POSE(3, 0x31, 1), POSE(-3, 0x01, 0), POSE_JUMP(13),
};

static AnimationFrame D_800AE3F8[] = {
    POSE(2, 0x39, 1), POSE(3, 0x3A, 1), POSE(3, 0x3B, 1), POSE(4, 0x3C, 1),
    POSE(4, 0x3D, 1), POSE(5, 0x3E, 4), POSE(7, 0x3F, 4), POSE(5, 0x40, 5),
    POSE(3, 0x41, 5), POSE(3, 0x42, 4), POSE_JUMP(12),
};

static AnimationFrame D_800AE424[] = {
    POSE(-3, 0x00, 0),
    POSE_JUMP(4),
};

static AnimationFrame D_800AE42C[] = {
    POSE(-3, 0x00, 0),
    POSE_JUMP(5),
};

static AnimationFrame D_800AE434[] = {
    POSE(2, 0x39, 1), POSE(2, 0x3A, 1), POSE(2, 0x3B, 1), POSE(3, 0x3C, 1),
    POSE(3, 0x3D, 1), POSE(3, 0x3E, 4), POSE(3, 0x3F, 4), POSE(3, 0x40, 5),
    POSE(2, 0x41, 5), POSE(2, 0x42, 4), POSE_END,
};

static AnimationFrame D_800AE460[] = {
    POSE(3, 0x32, 1), POSE(3, 0x33, 1), POSE(3, 0x34, 1), POSE(3, 0x35, 1),
    POSE(3, 0x36, 1), POSE(3, 0x37, 1), POSE(3, 0x38, 1), POSE_END,
};

static AnimationFrame D_800AE480[] = {
    POSE(-3, 0x01, 0),
    POSE_JUMP(13),
};

static AnimationFrame D_800AE488[] = {
    POSE(3, 0x29, 1), POSE(2, 0x2A, 1), POSE(3, 0x2B, 1), POSE(2, 0x2C, 1),
    POSE(3, 0x2D, 1), POSE(2, 0x2E, 1), POSE(3, 0x2F, 1), POSE(2, 0x30, 1),
    POSE(3, 0x31, 1), POSE(2, 0x32, 1), POSE(3, 0x33, 1), POSE(2, 0x34, 1),
    POSE(3, 0x35, 1), POSE(2, 0x36, 1), POSE(3, 0x37, 1), POSE(2, 0x38, 1),
    POSE_LOOP(0),
};

static AnimationFrame D_800AE4CC[] = {
    POSE(-3, 0x02, 0), POSE(4, 0x50, 1), POSE(4, 0x51, 1), POSE(4, 0x52, 1),
    POSE(4, 0x53, 1),  POSE(4, 0x54, 1), POSE(4, 0x55, 1), POSE(4, 0x54, 1),
    POSE(4, 0x55, 1),  POSE_JUMP(4),
};

static AnimationFrame D_800AE4F4[] = {
    POSE(4, 0x43, 6), POSE(4, 0x44, 6), POSE(4, 0x45, 6), POSE(4, 0x46, 6),
    POSE(4, 0x47, 6), POSE(4, 0x48, 6), POSE(4, 0x49, 6), POSE_END,
};

static AnimationFrame D_800AE514[] = {
    POSE(-3, 0x02, 0), POSE(4, 0x4A, 1), POSE(4, 0x4B, 1), POSE(4, 0x4C, 1),
    POSE(4, 0x4D, 1),  POSE(4, 0x4E, 1), POSE(4, 0x4F, 1), POSE(4, 0x4E, 1),
    POSE(4, 0x4F, 1),  POSE_JUMP(3),
};

static AnimationFrame D_800AE53C[] = {
    POSE(2, 0x42, 4), POSE(2, 0x41, 5), POSE(3, 0x40, 5),
    POSE(3, 0x3F, 4), POSE(3, 0x3E, 4), POSE_JUMP(14),
};

static AnimationFrame D_800AE554[] = {
    POSE(2, 0x02, 2), POSE(4, 0x03, 3), POSE(4, 0x04, 3),  POSE(4, 0x05, 3),
    POSE(4, 0x06, 3), POSE(4, 0x07, 3), POSE(-3, 0x03, 0), POSE_END,
};

static AnimationFrame D_800AE574[] = {
    POSE(4, 0x08, 3), POSE(4, 0x09, 3), POSE(4, 0x0A, 3), POSE(4, 0x0B, 3),
    POSE(4, 0x0C, 3), POSE(4, 0x0D, 3), POSE(4, 0x0E, 3), POSE_END,
};

static AnimationFrame D_800AE594[] = {
    POSE(255, 0x0F, 3),
    POSE_END,
};

static AnimationFrame D_800AE59C[] = {
    POSE(16, 0x0F, 3),
    POSE_END,
};

static AnimationFrame D_800AE5A4[] = {
    POSE(1, 0x0F, 3), POSE(3, 0x10, 3), POSE(3, 0x11, 2),
    POSE(3, 0x12, 1), POSE_END,
};

static AnimationFrame D_800AE5B8[] = {
    POSE(-3, 0x03, 0),
    POSE_JUMP(17),
};

static AnimationFrame D_800AE5C0[] = {
    POSE(1, 0x02, 2), POSE(1, 0x04, 3), POSE(1, 0x06, 3), POSE(1, 0x08, 3),
    POSE(1, 0x0A, 3), POSE(1, 0x0C, 3), POSE(1, 0x0E, 3), POSE_END,
};

static AnimationFrame D_800AE5E0[] = {
    POSE(6, 0x0F, 3),  POSE(6, 0x0F, 3),  POSE(12, 0x10, 2),
    POSE(12, 0x11, 1), POSE(12, 0x12, 1), POSE_END,
};

static AnimationFrame D_800AE5F8[] = {
    POSE(5, 0x5F, 1),
    POSE(5, 0x60, 1),
    POSE_JUMP(23),
};

static AnimationFrame D_800AE604[] = {
    POSE(5, 0x61, 1), POSE(5, 0x62, 1),  POSE(5, 0x67, 1),
    POSE(5, 0x68, 1), POSE(64, 0x69, 1), POSE_END,
};

static AnimationFrame D_800AE61C[] = {
    POSE(5, 0x63, 7),
    POSE(5, 0x64, 8),
    POSE_JUMP(26),
};

static AnimationFrame D_800AE628[] = {
    POSE(5, 0x64, 8),
    POSE(5, 0x63, 7),
    POSE_JUMP(23),
};

static AnimationFrame D_800AE634[] = {
    POSE(3, 0x65, 8),
    POSE(3, 0x66, 8),
    POSE_LOOP(0),
};

static AnimationFrame D_800AE640[] = {
    POSE(3, 0x6A, 7), POSE(4, 0x6B, 7), POSE(4, 0x6C, 7),
    POSE(4, 0x6D, 7), POSE_JUMP(28),
};

static AnimationFrame D_800AE654[] = {
    POSE(8, 0x6E, 7), POSE(5, 0x6F, 7),  POSE(5, 0x70, 7),
    POSE(5, 0x71, 7), POSE(65, 0x72, 7), POSE_END,
};

static AnimationFrame D_800AE66C[] = {
    POSE(-3, 0x04, 0), POSE(4, 0x51, 1), POSE(4, 0x52, 1),
    POSE(4, 0x53, 1),  POSE(4, 0x54, 1), POSE(4, 0x55, 1),
    POSE(4, 0x54, 1),  POSE(4, 0x55, 1), POSE_JUMP(4),
};

static AnimationFrame D_800AE690[] = {
    POSE(5, 0x74, 4), POSE(5, 0x75, 4), POSE(5, 0x76, 2),
    POSE(5, 0x77, 1), POSE(5, 0x78, 1), POSE_END,
};

static AnimationFrame D_800AE6A8[] = {
    POSE(-3, 0x04, 0), POSE(4, 0x4C, 1), POSE(4, 0x4D, 1), POSE(4, 0x4E, 1),
    POSE(4, 0x4F, 1),  POSE(4, 0x4E, 1), POSE(4, 0x4F, 1), POSE_JUMP(3),
};

static AnimationFrame D_800AE6C8[] = {
    POSE(3, 0x71, 7),
    POSE(66, 0x72, 7),
    POSE_END,
};

static AnimationFrame D_800AE6D4[] = {
    POSE(2, 0x99, 8), POSE(2, 0x98, 8), POSE(4, 0x99, 8), POSE(3, 0x9A, 8),
    POSE(3, 0x9B, 8), POSE(3, 0x65, 8), POSE(3, 0x66, 8), POSE(3, 0x65, 8),
    POSE(3, 0x66, 8), POSE_END,
};

static AnimationFrame D_800AE6FC[] = {
    POSE(5, 0x5F, 1),
    POSE(5, 0x60, 1),
    POSE_JUMP(23),
};

static AnimationFrame D_800AE708[] = {
    POSE(255, 0x73, 7),
    POSE_LOOP(0),
};

static AnimationFrame D_800AE710[] = {
    POSE(3, 0x74, 7),   POSE(3, 0x03, 7), POSE(3, 0x04, 3), POSE(3, 0x05, 3),
    POSE(3, 0x06, 3),   POSE(3, 0x07, 3), POSE(3, 0x08, 3), POSE(3, 0x09, 3),
    POSE(3, 0x0A, 3),   POSE(3, 0x0B, 3), POSE(4, 0x0C, 3), POSE(4, 0x0D, 3),
    POSE(5, 0x0E, 3),   POSE(7, 0x0C, 3), POSE(5, 0x0B, 3), POSE(4, 0x0A, 3),
    POSE(4, 0x09, 3),   POSE(4, 0x08, 3), POSE(4, 0x07, 3), POSE(4, 0x06, 3),
    POSE(4, 0x05, 3),   POSE(4, 0x04, 3), POSE(4, 0x03, 3), POSE(255, 0x74, 3),
    POSE(255, 0x74, 3), POSE_END,
};

static AnimationFrame D_800AE778[] = {
    POSE(5, 0x9C, 3),
    POSE(6, 0x9D, 1),
    POSE(6, 0x9E, 5),
    POSE_END,
};

static AnimationFrame D_800AE788[] = {
    POSE(2, 0x7C, 9), POSE(2, 0x7D, 9), POSE(2, 0x7E, 9), POSE(2, 0x7F, 9),
    POSE(3, 0x7E, 9), POSE(2, 0x7C, 9), POSE(3, 0x7D, 9), POSE(4, 0x7C, 9),
    POSE(6, 0x80, 9), POSE_END,
};

static AnimationFrame D_800AE7B0[] = {
    POSE(2, 0x81, 3), POSE(2, 0x82, 3), POSE(2, 0x83, 3),
    POSE(2, 0x84, 3), POSE(3, 0x83, 3), POSE(2, 0x81, 3),
    POSE(3, 0x82, 3), POSE(4, 0x81, 3), POSE_END,
};

static AnimationFrame D_800AE7D4[] = {
    POSE(2, 0x85, 8), POSE(2, 0x86, 8), POSE(2, 0x87, 8),
    POSE(3, 0x86, 8), POSE(3, 0x85, 8), POSE_END,
};

static AnimationFrame D_800AE7EC[] = {
    POSE(2, 0x88, 7), POSE(2, 0x89, 7), POSE(2, 0x8A, 7),
    POSE(3, 0x89, 7), POSE(3, 0x88, 7), POSE_END,
};

static AnimationFrame D_800AE804[] = {
    POSE(3, 0x6E, 7),   POSE(11, 0x8B, 10), POSE(5, 0x8C, 7), POSE(5, 0x8D, 7),
    POSE(7, 0x6E, 7),   POSE(3, 0x6F, 7),   POSE(3, 0x70, 7), POSE(3, 0x71, 7),
    POSE(255, 0x72, 7), POSE_END,
};

static AnimationFrame D_800AE82C[] = {
    POSE(48, 0x9F, 7),
    POSE_END,
};

static AnimationFrame D_800AE834[] = {
    POSE(16, 0x9F, 7),
    POSE(7, 0xA1, 1),
    POSE(28, 0xA2, 1),
    POSE_END,
};

static AnimationFrame D_800AE844[] = {
    POSE(48, 0xA3, 1),
    POSE_END,
};

static AnimationFrame D_800AE84C[] = {
    POSE(9, 0xA5, 6), POSE(2, 0xA6, 6), POSE(2, 0xA5, 6),  POSE(3, 0xA6, 6),
    POSE(3, 0xA5, 6), POSE(3, 0xA6, 6), POSE(17, 0xA5, 6), POSE(3, 0x9F, 6),
    POSE(4, 0x11, 6), POSE(4, 0x12, 6), POSE_END,
};

static AnimationFrame D_800AE878[] = {
    POSE(9, 0xA7, 4), POSE(2, 0xA8, 4), POSE(2, 0xA7, 4),  POSE(3, 0xA8, 4),
    POSE(3, 0xA7, 4), POSE(3, 0xA8, 4), POSE(17, 0xA7, 4), POSE(3, 0x9F, 6),
    POSE(4, 0x11, 6), POSE(4, 0x12, 6), POSE_END,
};

static AnimationFrame D_800AE8A4[] = {
    POSE(9, 0xA9, 4), POSE(2, 0xAA, 4), POSE(2, 0xA9, 4),  POSE(3, 0xAA, 4),
    POSE(3, 0xA9, 4), POSE(3, 0xAA, 4), POSE(17, 0xA9, 4), POSE(3, 0x11, 6),
    POSE(3, 0x12, 6), POSE_END,
};

static AnimationFrame D_800AE8CC[] = {
    POSE(9, 0xAB, 4), POSE(2, 0xAC, 4), POSE(2, 0xAB, 4),  POSE(3, 0xAC, 4),
    POSE(3, 0xAB, 4), POSE(3, 0xAC, 4), POSE(17, 0xAB, 4), POSE(3, 0x11, 6),
    POSE(3, 0x12, 6), POSE_END,
};

static AnimationFrame D_800AE8F4[] = {
    POSE(2, 0x9F, 7),
    POSE(2, 0xA0, 7),
    POSE_LOOP(0),
};

static AnimationFrame D_800AE900[] = {
    POSE(2, 0xA3, 1),
    POSE(2, 0xA4, 1),
    POSE_LOOP(0),
};

static AnimationFrame D_800AE90C[] = {
    POSE(5, 0x9F, 7), POSE(5, 0xA2, 1), POSE(5, 0xA3, 1),
    POSE(5, 0xA5, 6), POSE(5, 0xA9, 4), POSE_LOOP(0),
};

static AnimationFrame D_800AE924[] = {
    POSE(15, 0xAD, 7),
    POSE_END,
};

static AnimationFrame D_800AE92C[] = {
    POSE(15, 0xAE, 7),
    POSE_END,
};

static AnimationFrame D_800AE934[] = {
    POSE(15, 0xAF, 7),
    POSE_END,
};

static AnimationFrame D_800AE93C[] = {
    POSE(5, 0xA5, 6), POSE(2, 0xA6, 6), POSE(2, 0xA5, 6),  POSE(3, 0xA6, 6),
    POSE(3, 0xA5, 6), POSE(3, 0xA6, 6), POSE(17, 0xA5, 6), POSE(3, 0x11, 6),
    POSE(3, 0x12, 6), POSE_END,
};

static AnimationFrame D_800AE964[] = {
    POSE(9, 0x9F, 7), POSE(4, 0xA1, 1),  POSE(4, 0xA2, 1), POSE(4, 0xA9, 4),
    POSE(4, 0xAA, 4), POSE(17, 0xB1, 7), POSE(8, 0xB2, 7), POSE(8, 0xB3, 7),
    POSE(5, 0x71, 7), POSE(66, 0x72, 7), POSE_END,
};

static AnimationFrame D_800AE990[] = {
    POSE(3, 0xB5, 7), POSE(3, 0xB6, 7), POSE(3, 0xB7, 7), POSE(3, 0xB8, 7),
    POSE(3, 0xB4, 7), POSE(4, 0xB5, 7), POSE(4, 0xB6, 7), POSE(4, 0xB7, 7),
    POSE(4, 0xB8, 7), POSE(4, 0xB4, 7), POSE(5, 0xB5, 7), POSE(5, 0xB6, 7),
    POSE(5, 0xB7, 7), POSE(5, 0xB8, 7), POSE(5, 0xB4, 7), POSE(6, 0xB5, 7),
    POSE(6, 0xB6, 7), POSE(6, 0xB7, 7), POSE(6, 0xB8, 7), POSE(6, 0xB4, 7),
    POSE_END,
};

static AnimationFrame D_800AE9E4[] = {
    POSE(2, 0xB5, 7),  POSE(2, 0xB6, 7),  POSE(2, 0xB7, 7), POSE(2, 0xB8, 7),
    POSE(2, 0xB4, 7),  POSE(-3, 0x1B, 0), POSE(7, 0xB5, 7), POSE(7, 0xB6, 7),
    POSE(7, 0xB7, 7),  POSE(8, 0xB8, 7),  POSE(9, 0xB4, 7), POSE(10, 0xB5, 7),
    POSE(64, 0x9F, 7), POSE_END,
};

static AnimationFrame D_800AEA1C[] = {
    POSE(2, 0xC7, 3),  POSE(2, 0xC8, 3), POSE(2, 0xC9, 3), POSE(2, 0xCA, 3),
    POSE(16, 0xCB, 3), POSE(2, 0xCC, 3), POSE(2, 0xCD, 3), POSE(1, 0xCE, 3),
    POSE(1, 0xCF, 3),  POSE_END,
};

static AnimationFrame D_800AEA44[] = {
    POSE(-3, 0x1B, 0), POSE(7, 0xB5, 7), POSE(7, 0xB6, 7), POSE(7, 0xB7, 7),
    POSE(8, 0xA1, 7),  POSE(1, 0xA2, 7), POSE_END,
};

static AnimationFrame D_800AEA60[] = {
    POSE(-3, 0x1B, 0), POSE(7, 0xB5, 7), POSE(7, 0xB6, 7),
    POSE(7, 0xB7, 7),  POSE_END,
};

static AnimationFrame D_800AEA74[] = {
    POSE(24, 0x8E, 1), POSE(4, 0x8F, 1),  POSE(4, 0x90, 1), POSE(4, 0x91, 1),
    POSE(6, 0x92, 1),  POSE(7, 0x93, 1),  POSE(4, 0x94, 1), POSE(25, 0x95, 1),
    POSE(4, 0x96, 1),  POSE(4, 0x97, 1),  POSE(4, 0xB0, 1), POSE(2, 0x97, 1),
    POSE(2, 0x96, 1),  POSE(65, 0x95, 1), POSE(9, 0x93, 1), POSE(4, 0x92, 1),
    POSE(3, 0x91, 1),  POSE(4, 0x90, 1),  POSE(4, 0x8F, 1), POSE(4, 0x8E, 1),
    POSE_END,
};

static AnimationFrame D_800AEAC8[] = {
    POSE(4, 0x8E, 1),
    POSE_END,
};

static AnimationFrame D_800AEAD0[] = {
    POSE(-3, 0x05, 0),
    POSE(-3, 0x0D, 0),
    POSE_END,
};

static AnimationFrame D_800AEADC[] = {
    POSE(4, 0xBF, 9), POSE(6, 0xC0, 1), POSE(5, 0xC1, 1), POSE(5, 0xC2, 1),
    POSE(4, 0xC3, 1), POSE(3, 0x54, 1), POSE(3, 0x55, 1), POSE_END,
};

static AnimationFrame D_800AEAFC[] = {
    POSE(2, 0xB9, 9), POSE(1, 0xBA, 9), POSE(1, 0xBA, 9), POSE(1, 0xBA, 9),
    POSE(1, 0xBA, 9), POSE(1, 0xBB, 9), POSE(1, 0xBB, 9), POSE(1, 0xBB, 9),
    POSE(2, 0xBB, 9), POSE(4, 0xBC, 9), POSE(4, 0xBD, 9), POSE(4, 0xBE, 9),
    POSE(4, 0xBF, 9), POSE_END,
};

static AnimationFrame D_800AEB34[] = {
    POSE(-3, 0x05, 0),
    POSE(-3, 0x0E, 0),
    POSE_END,
};

static AnimationFrame D_800AEB40[] = {
    POSE(4, 0xBF, 9), POSE(5, 0x57, 1),  POSE(4, 0x58, 1),
    POSE(3, 0x59, 1), POSE(3, 0x5A, 1),  POSE(3, 0x5B, 1),
    POSE(3, 0x5C, 1), POSE(64, 0x5D, 1), POSE_END,
};

static AnimationFrame D_800AEB64[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(1, 0xC5, 3),  POSE(1, 0xC5, 3),
    POSE(1, 0xC5, 3), POSE(-3, 0x06, 0), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AEB84[] = {
    POSE(4, 0xCB, 3), POSE(6, 0xCC, 3), POSE(5, 0xCD, 3),
    POSE(5, 0xCE, 3), POSE(5, 0xCF, 3), POSE(64, 0x0F, 3),
};

static AnimationFrame D_800AEB9C[] = {
    POSE(1, 0xC7, 3), POSE(1, 0xC7, 3), POSE(1, 0xC7, 3),
    POSE(2, 0xC7, 3), POSE(4, 0xC8, 3), POSE(4, 0xC9, 3),
    POSE(4, 0xCA, 3), POSE(4, 0xCB, 3), POSE_END,
};

static AnimationFrame D_800AEBC0[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(1, 0xC6, 3),  POSE(1, 0xC6, 3),
    POSE(1, 0xC6, 3), POSE(-3, 0x06, 0), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AEBE0[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7),  POSE(1, 0xD1, 7),
    POSE(2, 0xD1, 7), POSE(-3, 0x0A, 0), POSE_END,
};

static AnimationFrame D_800AEBF8[] = {
    POSE(1, 0xD2, 7), POSE(1, 0xD2, 7), POSE(1, 0xD2, 7),
    POSE(2, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_800AEC10[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7),  POSE(1, 0xD5, 7),
    POSE(2, 0xD5, 7), POSE(-3, 0x07, 0), POSE_END,
};

static AnimationFrame D_800AEC28[] = {
    POSE(1, 0xD7, 7), POSE(1, 0xD7, 7), POSE(1, 0xD7, 7),
    POSE(2, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_800AEC40[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD6, 7),  POSE(1, 0xD6, 7),
    POSE(2, 0xD6, 7), POSE(-3, 0x07, 0), POSE_END,
};

static AnimationFrame D_800AEC58[] = {
    POSE(-3, 0x08, 0),
    POSE(-3, 0x0D, 0),
    POSE_END,
};

static AnimationFrame D_800AEC64[] = {
    POSE(1, 0xB9, 9), POSE(1, 0xB9, 9), POSE(1, 0xBA, 9), POSE(2, 0xBA, 9),
    POSE(8, 0xBA, 9), POSE(1, 0xBB, 9), POSE(1, 0xBB, 9), POSE(1, 0xBB, 9),
    POSE(1, 0xBB, 9), POSE(4, 0xBC, 9), POSE(4, 0xBD, 9), POSE(4, 0xBE, 9),
    POSE(4, 0xBF, 9), POSE_END,
};

static AnimationFrame D_800AEC9C[] = {
    POSE(-3, 0x08, 0),
    POSE(-3, 0x0E, 0),
    POSE_END,
};

static AnimationFrame D_800AECA8[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3),  POSE(1, 0xC5, 3),  POSE(2, 0xC5, 3),
    POSE(8, 0xC5, 3), POSE(-3, 0x09, 0), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AECC8[] = {
    POSE(1, 0xC7, 3), POSE(1, 0xC7, 3), POSE(1, 0xC7, 3),
    POSE(2, 0xC7, 3), POSE(4, 0xC8, 3), POSE(4, 0xC9, 3),
    POSE(4, 0xCA, 3), POSE(8, 0xCB, 3), POSE_END,
};

static AnimationFrame D_800AECEC[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3),  POSE(1, 0xC6, 3),  POSE(2, 0xC6, 3),
    POSE(8, 0xC6, 3), POSE(-3, 0x09, 0), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AED0C[] = {
    POSE(1, 0xD0, 7), POSE(1, 0xD0, 7),  POSE(1, 0xD1, 7), POSE(2, 0xD1, 7),
    POSE(8, 0xD1, 7), POSE(-3, 0x0A, 0), POSE_END,
};

static AnimationFrame D_800AED28[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7),  POSE(1, 0xD5, 7), POSE(2, 0xD5, 7),
    POSE(8, 0xD5, 7), POSE(-3, 0x07, 0), POSE_END,
};

static AnimationFrame D_800AED44[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7),  POSE(1, 0xD6, 7), POSE(2, 0xD6, 7),
    POSE(8, 0xD6, 7), POSE(-3, 0x07, 0), POSE_END,
};

static AnimationFrame D_800AED60[] = {
    POSE(-3, 0x0B, 0),
    POSE(-3, 0x0D, 0),
    POSE_END,
};

static AnimationFrame D_800AED6C[] = {
    POSE(1, 0xB9, 9), POSE(1, 0xB9, 9), POSE(1, 0xBA, 9), POSE(2, 0xBA, 9),
    POSE(2, 0xBA, 9), POSE(2, 0xBA, 9), POSE(2, 0xBA, 9), POSE(1, 0xBA, 9),
    POSE(1, 0xBA, 9), POSE(1, 0xBB, 9), POSE(1, 0xBB, 9), POSE(1, 0xBB, 9),
    POSE(1, 0xBB, 9), POSE(4, 0xBC, 9), POSE(4, 0xBD, 9), POSE(4, 0xBE, 9),
    POSE(4, 0xBF, 9), POSE_END,
};

static AnimationFrame D_800AEDB4[] = {
    POSE(-3, 0x0B, 0),
    POSE(-3, 0x0E, 0),
    POSE_END,
};

static AnimationFrame D_800AEDC0[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3),  POSE(1, 0xC5, 3),  POSE(2, 0xC5, 3),
    POSE(2, 0xC5, 3), POSE(2, 0xC5, 3),  POSE(2, 0xC5, 3),  POSE(1, 0xC5, 3),
    POSE(1, 0xC5, 3), POSE(-3, 0x06, 0), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AEDF0[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3),  POSE(1, 0xC6, 3),  POSE(2, 0xC6, 3),
    POSE(2, 0xC6, 3), POSE(2, 0xC6, 3),  POSE(2, 0xC6, 3),  POSE(1, 0xC6, 3),
    POSE(1, 0xC6, 3), POSE(-3, 0x06, 0), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AEE20[] = {
    POSE(1, 0xD0, 7), POSE(1, 0xD0, 7),  POSE(1, 0xD1, 7), POSE(2, 0xD1, 7),
    POSE(2, 0xD1, 7), POSE(2, 0xD1, 7),  POSE(2, 0xD1, 7), POSE(1, 0xD1, 7),
    POSE(1, 0xD1, 7), POSE(-3, 0x0A, 0), POSE_END,
};

static AnimationFrame D_800AEE4C[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7),  POSE(1, 0xD5, 7), POSE(2, 0xD5, 7),
    POSE(2, 0xD5, 7), POSE(2, 0xD5, 7),  POSE(2, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(1, 0xD5, 7), POSE(-3, 0x07, 0), POSE_END,
};

static AnimationFrame D_800AEE78[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7),  POSE(1, 0xD6, 7), POSE(2, 0xD6, 7),
    POSE(2, 0xD6, 7), POSE(2, 0xD6, 7),  POSE(2, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(1, 0xD6, 7), POSE(-3, 0x07, 0), POSE_END,
};

static AnimationFrame D_800AEEA4[] = {
    POSE(-3, 0x0C, 0),
    POSE(-3, 0x0D, 0),
    POSE_END,
};

static AnimationFrame D_800AEEB0[] = {
    POSE(2, 0xB9, 9), POSE(1, 0xB9, 9), POSE(1, 0xBA, 9), POSE(2, 0xBA, 9),
    POSE(2, 0xBA, 9), POSE(1, 0xBA, 9), POSE(1, 0xBA, 9), POSE(1, 0xBA, 9),
    POSE(3, 0xBA, 9), POSE(1, 0xBB, 9), POSE(1, 0xBB, 9), POSE(1, 0xBB, 9),
    POSE(1, 0xBB, 9), POSE(4, 0xBC, 9), POSE(4, 0xBD, 9), POSE(4, 0xBE, 9),
    POSE(8, 0xBF, 9), POSE_END,
};

static AnimationFrame D_800AEEF8[] = {
    POSE(-3, 0x0C, 0),
    POSE(-3, 0x0E, 0),
    POSE_END,
};

static AnimationFrame D_800AEF04[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC4, 3),  POSE(1, 0xC5, 3),  POSE(2, 0xC5, 3),
    POSE(2, 0xC5, 3), POSE(1, 0xC5, 3),  POSE(1, 0xC5, 3),  POSE(1, 0xC5, 3),
    POSE(3, 0xC5, 3), POSE(-3, 0x09, 0), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AEF34[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC4, 3),  POSE(1, 0xC6, 3),  POSE(2, 0xC6, 3),
    POSE(2, 0xC6, 3), POSE(1, 0xC6, 3),  POSE(1, 0xC6, 3),  POSE(1, 0xC6, 3),
    POSE(3, 0xC6, 3), POSE(-3, 0x09, 0), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AEF64[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD0, 7),  POSE(1, 0xD1, 7), POSE(2, 0xD1, 7),
    POSE(2, 0xD1, 7), POSE(1, 0xD1, 7),  POSE(1, 0xD1, 7), POSE(1, 0xD1, 7),
    POSE(3, 0xD1, 7), POSE(-3, 0x0A, 0), POSE_END,
};

static AnimationFrame D_800AEF90[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD4, 7),  POSE(1, 0xD5, 7), POSE(2, 0xD5, 7),
    POSE(2, 0xD5, 7), POSE(1, 0xD5, 7),  POSE(1, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(3, 0xD5, 7), POSE(-3, 0x07, 0), POSE_END,
};

static AnimationFrame D_800AEFBC[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD4, 7),  POSE(1, 0xD6, 7), POSE(2, 0xD6, 7),
    POSE(2, 0xD6, 7), POSE(1, 0xD6, 7),  POSE(1, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(3, 0xD6, 7), POSE(-3, 0x07, 0), POSE_END,
};

static AnimationFrame D_800AEFE8[] = {
    POSE(2, 0x7A, 1), POSE(2, 0x7B, 1), POSE(1, 0xBA, 9),  POSE(1, 0xBB, 9),
    POSE(1, 0xBC, 9), POSE(1, 0xBD, 9), POSE(1, 0xBE, 9),  POSE(3, 0xBF, 9),
    POSE(3, 0xC0, 1), POSE(3, 0xC1, 1), POSE(3, 0xC2, 1),  POSE(3, 0xC3, 1),
    POSE(2, 0x54, 1), POSE(2, 0x55, 1), POSE(-3, 0x10, 0), POSE_JUMP(2),
};

static AnimationFrame D_800AF028[] = {
    POSE(5, 0x57, 1), POSE(4, 0x58, 1),  POSE(3, 0x59, 1),
    POSE(3, 0x5A, 1), POSE(3, 0x5B, 1),  POSE(3, 0x5C, 1),
    POSE(3, 0x5D, 1), POSE(16, 0x79, 1), POSE_JUMP(3),
};

static AnimationFrame D_800AF04C[] = {
    POSE(4, 0x7A, 1),  POSE(4, 0x7B, 1),  POSE(4, 0x01, 1),
    POSE(-3, 0x10, 0), POSE(-3, 0x11, 0), POSE_JUMP(2),
};

static AnimationFrame D_800AF064[] = {
    POSE(6, 0x56, 2), POSE(6, 0x57, 1), POSE(6, 0x58, 1), POSE(6, 0x59, 1),
    POSE(6, 0x5A, 1), POSE(5, 0x5B, 1), POSE(3, 0x5C, 1), POSE(3, 0x5B, 1),
    POSE(2, 0x5C, 1), POSE(2, 0x5D, 1), POSE(2, 0x5C, 1), POSE(128, 0x5D, 1),
    POSE_JUMP(6),
};

static AnimationFrame D_800AF098[] = {
    POSE(1, 0xC5, 3), POSE(1, 0xC7, 3), POSE(1, 0xC8, 3), POSE(1, 0xC9, 3),
    POSE(1, 0xCA, 3), POSE(1, 0xCB, 3), POSE(4, 0xCC, 3), POSE(3, 0xCD, 3),
    POSE(3, 0xCE, 3), POSE(3, 0xCF, 3), POSE(1, 0x0F, 3), POSE_END,
};

static AnimationFrame D_800AF0C8[] = {
    POSE(2, 0x7A, 1),  POSE(2, 0x7A, 1), POSE(2, 0x7A, 1),
    POSE(64, 0x7B, 1), POSE_END,
};

static AnimationFrame D_800AF0DC[] = {
    POSE(2, 0x81, 3),  POSE(2, 0x81, 3), POSE(2, 0x81, 3),
    POSE(64, 0x82, 3), POSE_END,
};

static AnimationFrame D_800AF0F0[] = {
    POSE(-3, 0x02, 0), POSE(4, 0x50, 1), POSE(4, 0x51, 1), POSE(4, 0x52, 1),
    POSE(4, 0x53, 1),  POSE(4, 0x54, 1), POSE(4, 0x55, 1), POSE(4, 0x54, 1),
    POSE(4, 0x55, 1),  POSE_END,
};

static AnimationFrame D_800AF118[] = {
    POSE(-3, 0x02, 0), POSE(4, 0x4A, 1), POSE(4, 0x4B, 1), POSE(4, 0x4C, 1),
    POSE(4, 0x4D, 1),  POSE(4, 0x4E, 1), POSE(4, 0x4F, 1), POSE(4, 0x4E, 1),
    POSE(4, 0x4F, 1),  POSE_END,
};

static AnimationFrame D_800AF140[] = {
    POSE(-3, 0x12, 0),
    POSE(-3, 0x0D, 0),
    POSE_END,
};

static AnimationFrame D_800AF14C[] = {
    POSE(1, 0xB9, 9), POSE(1, 0xB9, 9), POSE(1, 0xBA, 9), POSE(1, 0xBA, 9),
    POSE(1, 0xBA, 9), POSE(1, 0xBA, 9), POSE(2, 0xBB, 9), POSE(2, 0xBB, 9),
    POSE(2, 0xBB, 9), POSE(4, 0xBC, 9), POSE(4, 0xBD, 9), POSE(4, 0xBE, 9),
    POSE(8, 0xBF, 9), POSE_END,
};

static AnimationFrame D_800AF184[] = {
    POSE(-3, 0x12, 0),
    POSE(-3, 0x0E, 0),
    POSE_END,
};

static AnimationFrame D_800AF190[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3),  POSE(1, 0xC5, 3), POSE(1, 0xC5, 3),
    POSE(1, 0xC5, 3), POSE(1, 0xC5, 3),  POSE(2, 0xC7, 3), POSE(2, 0xC7, 3),
    POSE(2, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AF1CC[] = {
    POSE(1, 0xC4, 3),  POSE(1, 0xC4, 3), POSE(1, 0xC6, 3), POSE(2, 0xC6, 3),
    POSE(1, 0xC6, 3),  POSE(2, 0xC7, 3), POSE(2, 0xC7, 3), POSE(2, 0xC7, 3),
    POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3), POSE(8, 0xCB, 3),
    POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AF204[] = {
    POSE(1, 0xD0, 7), POSE(1, 0xD0, 7), POSE(1, 0xD1, 7), POSE(1, 0xD1, 7),
    POSE(1, 0xD1, 7), POSE(1, 0xD1, 7), POSE(1, 0xD2, 7), POSE(1, 0xD2, 7),
    POSE(2, 0xD2, 7), POSE(2, 0xD3, 7), POSE(2, 0xD3, 7), POSE(2, 0xD3, 7),
    POSE(2, 0xD3, 7), POSE_END,
};

static AnimationFrame D_800AF23C[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD7, 7), POSE(1, 0xD7, 7),
    POSE(2, 0xD7, 7), POSE(2, 0xD8, 7), POSE(2, 0xD8, 7), POSE(2, 0xD8, 7),
    POSE(2, 0xD8, 7), POSE_END,
};

static AnimationFrame D_800AF274[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(1, 0xD6, 7), POSE(1, 0xD7, 7), POSE(1, 0xD7, 7), POSE(1, 0xD7, 7),
    POSE(2, 0xD8, 7), POSE(2, 0xD8, 7), POSE(2, 0xD8, 7), POSE(2, 0xD8, 7),
    POSE_END,
};

static AnimationFrame D_800AF2A8[] = {
    POSE(1, 0xD0, 1),  POSE(1, 0xD0, 2), POSE(1, 0xD1, 19), POSE(1, 0xD1, 4),
    POSE(16, 0xD1, 4), POSE(1, 0xBA, 4), POSE(1, 0xBA, 4),  POSE(1, 0xBB, 5),
    POSE(1, 0xBB, 6),  POSE(1, 0xBB, 7), POSE(2, 0xBC, 8),  POSE(2, 0xBD, 8),
    POSE(2, 0xBE, 8),  POSE(2, 0xBF, 8), POSE_END,
};

static AnimationFrame D_800AF2E4[] = {
    POSE(-3, 0x1C, 0),
    POSE(-3, 0x0D, 0),
    POSE_END,
};

// Unused
static AnimationFrame D_800AF2F0[] = {
    POSE(-3, 0x1C, 0),
    POSE(-3, 0x0E, 0),
    POSE_END,
};

static AnimationFrame D_800AF2FC[] = {
    POSE(2, 0x7C, 9), POSE(2, 0x7D, 9), POSE(1, 0x7E, 9),
    POSE(1, 0x7F, 9), POSE(2, 0x7E, 9), POSE(2, 0x7D, 9),
    POSE(4, 0x7C, 9), POSE(5, 0x80, 9), POSE_END,
};

static AnimationFrame D_800AF320[] = {
    POSE(2, 0x81, 3), POSE(2, 0x82, 3), POSE(1, 0x83, 3), POSE(1, 0x84, 3),
    POSE(2, 0x83, 3), POSE(2, 0x82, 3), POSE(4, 0x81, 3), POSE_END,
};

static AnimationFrame D_800AF340[] = {
    POSE(1, 0x85, 8), POSE(1, 0x86, 8), POSE(1, 0x87, 8),
    POSE(2, 0x86, 8), POSE(2, 0x85, 8), POSE_END,
};

static AnimationFrame D_800AF358[] = {
    POSE(1, 0x88, 7),
    POSE(4, 0x89, 7),
    POSE(2, 0x88, 7),
    POSE_END,
};

static AnimationFrame D_800AF368[] = {
    POSE(-3, 0x13, 0),
    POSE(-3, 0x0D, 0),
    POSE_END,
};

static AnimationFrame D_800AF374[] = {
    POSE(2, 0xB9, 9), POSE(1, 0xBA, 9), POSE(3, 0xBA, 9), POSE(1, 0xBB, 9),
    POSE(3, 0xBB, 9), POSE(4, 0xBC, 9), POSE(4, 0xBD, 9), POSE(4, 0xBE, 9),
    POSE(8, 0xBF, 9), POSE_END,
};

static AnimationFrame D_800AF39C[] = {
    POSE(-3, 0x13, 0),
    POSE(-3, 0x0E, 0),
    POSE_END,
};

static AnimationFrame D_800AF3A8[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(3, 0xC5, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AF3D4[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(3, 0xC6, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AF400[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7), POSE(3, 0xD1, 7), POSE(1, 0xD2, 7),
    POSE(3, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_800AF41C[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(3, 0xD5, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_800AF438[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD6, 7), POSE(3, 0xD6, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_800AF454[] = {
    POSE(1, 0x7C, 9), POSE(1, 0x7D, 9), POSE(1, 0x7E, 9),
    POSE(1, 0x7F, 9), POSE(2, 0x7E, 9), POSE(2, 0x7D, 9),
    POSE(4, 0x7C, 9), POSE(5, 0x80, 9), POSE_END,
};

static AnimationFrame D_800AF478[] = {
    POSE(1, 0x81, 3), POSE(1, 0x82, 3), POSE(1, 0x83, 3), POSE(1, 0x84, 3),
    POSE(2, 0x83, 3), POSE(2, 0x82, 3), POSE(4, 0x81, 3), POSE_END,
};

static AnimationFrame D_800AF498[] = {
    POSE(-3, 0x14, 0),
    POSE(-3, 0x0D, 0),
    POSE_END,
};

static AnimationFrame D_800AF4A4[] = {
    POSE(2, 0xB9, 9), POSE(1, 0xBA, 9), POSE(2, 0xBA, 9), POSE(1, 0xBB, 9),
    POSE(3, 0xBB, 9), POSE(4, 0xBC, 9), POSE(4, 0xBD, 9), POSE(4, 0xBE, 9),
    POSE(8, 0xBF, 9), POSE_END,
};

static AnimationFrame D_800AF4CC[] = {
    POSE(-3, 0x14, 0),
    POSE(-3, 0x0E, 0),
    POSE_END,
};

static AnimationFrame D_800AF4D8[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(2, 0xC5, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AF504[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(2, 0xC6, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AF530[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7), POSE(2, 0xD1, 7), POSE(1, 0xD2, 7),
    POSE(3, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_800AF54C[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(2, 0xD5, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_800AF568[] = {
    POSE(-3, 0x15, 0),
    POSE(-3, 0x0D, 0),
    POSE_END,
};

static AnimationFrame D_800AF574[] = {
    POSE(2, 0x7C, 9), POSE(2, 0x7D, 9), POSE(1, 0x7E, 9), POSE(1, 0x7F, 9),
    POSE(2, 0x7E, 9), POSE(2, 0x7E, 9), POSE(2, 0x7D, 9), POSE(2, 0x7C, 9),
    POSE(1, 0xB9, 9), POSE(1, 0xB9, 9), POSE(1, 0xBA, 9), POSE(3, 0xBA, 9),
    POSE(1, 0xBB, 9), POSE(3, 0xBB, 9), POSE(4, 0xBC, 9), POSE(4, 0xBD, 9),
    POSE(4, 0xBE, 9), POSE(4, 0xBF, 9), POSE_END,
};

static AnimationFrame D_800AF5C0[] = {
    POSE(-3, 0x15, 0),
    POSE(-3, 0x0E, 0),
    POSE_END,
};

static AnimationFrame D_800AF5CC[] = {
    POSE(2, 0x81, 3), POSE(2, 0x82, 3), POSE(1, 0x83, 3),  POSE(1, 0x84, 3),
    POSE(2, 0x83, 3), POSE(2, 0x83, 3), POSE(2, 0x82, 3),  POSE(2, 0x81, 3),
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(3, 0xC6, 3),
    POSE(1, 0xC7, 3), POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3),
    POSE(4, 0xCA, 3), POSE(4, 0xCB, 3), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AF61C[] = {
    POSE(1, 0xD0, 7), POSE(1, 0xD0, 7), POSE(1, 0xD1, 7), POSE(3, 0xD1, 7),
    POSE(1, 0xD2, 7), POSE(3, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_800AF63C[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD5, 7), POSE(3, 0xD5, 7),
    POSE(1, 0xD7, 7), POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_800AF65C[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD6, 7), POSE(3, 0xD6, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_800AF678[] = {
    POSE(-3, 0x16, 0),
    POSE(-3, 0x0D, 0),
    POSE_END,
};

static AnimationFrame D_800AF684[] = {
    POSE(2, 0xB9, 9), POSE(1, 0xBA, 9), POSE(1, 0xBA, 9), POSE(1, 0xBA, 9),
    POSE(1, 0xBA, 9), POSE(1, 0xBA, 9), POSE(1, 0xBB, 9), POSE(3, 0xBB, 9),
    POSE(4, 0xBC, 9), POSE(4, 0xBD, 9), POSE(4, 0xBE, 9), POSE(8, 0xBF, 9),
    POSE_END,
};

static AnimationFrame D_800AF6B8[] = {
    POSE(-3, 0x16, 0),
    POSE(-3, 0x0E, 0),
    POSE_END,
};

static AnimationFrame D_800AF6C4[] = {
    POSE(2, 0xC4, 3),  POSE(1, 0xC5, 3), POSE(1, 0xC5, 3), POSE(1, 0xC5, 3),
    POSE(1, 0xC5, 3),  POSE(1, 0xC5, 3), POSE(1, 0xC7, 3), POSE(3, 0xC7, 3),
    POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3), POSE(8, 0xCB, 3),
    POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AF6FC[] = {
    POSE(2, 0xC4, 3),  POSE(1, 0xC6, 3), POSE(1, 0xC6, 3), POSE(1, 0xC6, 3),
    POSE(1, 0xC6, 3),  POSE(1, 0xC6, 3), POSE(1, 0xC7, 3), POSE(3, 0xC7, 3),
    POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3), POSE(8, 0xCB, 3),
    POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AF734[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7), POSE(1, 0xD1, 7), POSE(1, 0xD1, 7),
    POSE(1, 0xD1, 7), POSE(1, 0xD1, 7), POSE(1, 0xD2, 7), POSE(3, 0xD2, 7),
    POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_800AF75C[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD7, 7), POSE(3, 0xD7, 7),
    POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_800AF784[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(1, 0xD6, 7), POSE(1, 0xD6, 7), POSE(1, 0xD7, 7), POSE(3, 0xD7, 7),
    POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_800AF7AC[] = {
    POSE(-3, 0x17, 0),
    POSE(-3, 0x0D, 0),
    POSE_END,
};

static AnimationFrame D_800AF7B8[] = {
    POSE(2, 0xB9, 9), POSE(1, 0xBA, 9), POSE(3, 0xBA, 9), POSE(2, 0xBB, 9),
    POSE(2, 0xBB, 9), POSE(4, 0xBC, 9), POSE(4, 0xBD, 9), POSE(4, 0xBE, 9),
    POSE(8, 0xBF, 9), POSE_END,
};

static AnimationFrame D_800AF7E0[] = {
    POSE(-3, 0x17, 0),
    POSE(-3, 0x0E, 0),
    POSE_END,
};

static AnimationFrame D_800AF7EC[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(3, 0xC5, 3), POSE(2, 0xC7, 3),
    POSE(2, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AF818[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7), POSE(3, 0xD1, 7), POSE(2, 0xD2, 7),
    POSE(2, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_800AF834[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(3, 0xD5, 7), POSE(2, 0xD7, 7),
    POSE(2, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_800AF850[] = {
    POSE(-3, 0x18, 0),
    POSE(-3, 0x0D, 0),
    POSE_END,
};

static AnimationFrame D_800AF85C[] = {
    POSE(3, 0xB9, 9), POSE(1, 0xBA, 9), POSE(4, 0xBA, 9), POSE(1, 0xBB, 9),
    POSE(3, 0xBB, 9), POSE(4, 0xBC, 9), POSE(4, 0xBD, 9), POSE(4, 0xBE, 9),
    POSE(8, 0xBF, 9), POSE_END,
};

static AnimationFrame D_800AF884[] = {
    POSE(-3, 0x18, 0),
    POSE(-3, 0x0E, 0),
    POSE_END,
};

static AnimationFrame D_800AF890[] = {
    POSE(3, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(4, 0xC5, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AF8BC[] = {
    POSE(3, 0xD0, 7), POSE(1, 0xD1, 7), POSE(4, 0xD1, 7), POSE(1, 0xD2, 7),
    POSE(3, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_800AF8D8[] = {
    POSE(3, 0xD4, 7), POSE(1, 0xD5, 7), POSE(4, 0xD5, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_800AF8F4[] = {
    POSE(-3, 0x19, 0),
    POSE(-3, 0x0D, 0),
    POSE_END,
};

static AnimationFrame D_800AF900[] = {
    POSE(4, 0xB9, 9), POSE(2, 0xBA, 9), POSE(3, 0xBA, 9), POSE(1, 0xBB, 9),
    POSE(3, 0xBB, 9), POSE(4, 0xBC, 9), POSE(4, 0xBD, 9), POSE(4, 0xBE, 9),
    POSE(8, 0xBF, 9), POSE_END,
};

static AnimationFrame D_800AF928[] = {
    POSE(-3, 0x19, 0),
    POSE(-3, 0x0E, 0),
    POSE_END,
};

static AnimationFrame D_800AF934[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC5, 3),  POSE(3, 0xC5, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AF960[] = {
    POSE(2, 0xC4, 3), POSE(1, 0xC6, 3),  POSE(3, 0xC6, 3), POSE(1, 0xC7, 3),
    POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),  POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(8, 0xCB, 3), POSE(-3, 0x0F, 0), POSE_END,
};

static AnimationFrame D_800AF98C[] = {
    POSE(2, 0xD0, 7), POSE(1, 0xD1, 7), POSE(3, 0xD1, 7), POSE(1, 0xD2, 7),
    POSE(3, 0xD2, 7), POSE(8, 0xD3, 7), POSE_END,
};

static AnimationFrame D_800AF9A8[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD5, 7), POSE(3, 0xD5, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_800AF9C4[] = {
    POSE(2, 0xD4, 7), POSE(1, 0xD6, 7), POSE(3, 0xD6, 7), POSE(1, 0xD7, 7),
    POSE(3, 0xD7, 7), POSE(8, 0xD8, 7), POSE_END,
};

static AnimationFrame D_800AF9E0[] = {
    POSE(-3, 0x1A, 0),
    POSE(-3, 0x0D, 0),
    POSE_END,
};

static AnimationFrame D_800AF9EC[] = {
    POSE(1, 0xB9, 9), POSE(1, 0xB9, 9), POSE(1, 0xB9, 9), POSE(1, 0xB9, 9),
    POSE(1, 0xBA, 9), POSE(1, 0xBA, 9), POSE(1, 0xBA, 9), POSE(1, 0xBA, 9),
    POSE(1, 0xBA, 9), POSE(1, 0xBB, 9), POSE(3, 0xBB, 9), POSE(4, 0xBC, 9),
    POSE(4, 0xBD, 9), POSE(4, 0xBE, 9), POSE(8, 0xBF, 9), POSE_END,
};

static AnimationFrame D_800AFA2C[] = {
    POSE(-3, 0x1A, 0),
    POSE(-3, 0x0E, 0),
    POSE_END,
};

static AnimationFrame D_800AFA38[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC4, 3),
    POSE(1, 0xC5, 3), POSE(1, 0xC5, 3), POSE(1, 0xC5, 3), POSE(1, 0xC5, 3),
    POSE(1, 0xC5, 3), POSE(1, 0xC7, 3), POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),
    POSE(4, 0xC9, 3), POSE(4, 0xCA, 3), POSE(8, 0xCB, 3), POSE(-3, 0x0F, 0),
    POSE_END,
};

static AnimationFrame D_800AFA7C[] = {
    POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC4, 3), POSE(1, 0xC4, 3),
    POSE(1, 0xC6, 3), POSE(1, 0xC6, 3), POSE(1, 0xC6, 3), POSE(1, 0xC6, 3),
    POSE(1, 0xC6, 3), POSE(1, 0xC7, 3), POSE(3, 0xC7, 3), POSE(4, 0xC8, 3),
    POSE(4, 0xC9, 3), POSE(4, 0xCA, 3), POSE(8, 0xCB, 3), POSE(-3, 0x0F, 0),
    POSE_END,
};

static AnimationFrame D_800AFAC0[] = {
    POSE(1, 0xD0, 7), POSE(1, 0xD0, 7), POSE(1, 0xD0, 7), POSE(1, 0xD0, 7),
    POSE(1, 0xD1, 7), POSE(1, 0xD1, 7), POSE(1, 0xD1, 7), POSE(1, 0xD1, 7),
    POSE(1, 0xD1, 7), POSE(1, 0xD2, 7), POSE(3, 0xD2, 7), POSE(8, 0xD3, 7),
    POSE_END,
};

static AnimationFrame D_800AFAF4[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD4, 7),
    POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7), POSE(1, 0xD5, 7),
    POSE(1, 0xD5, 7), POSE(1, 0xD7, 7), POSE(3, 0xD7, 7), POSE(8, 0xD8, 7),
    POSE_END,
};

static AnimationFrame D_800AFB28[] = {
    POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD4, 7), POSE(1, 0xD4, 7),
    POSE(1, 0xD6, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7), POSE(1, 0xD6, 7),
    POSE(1, 0xD6, 7), POSE(1, 0xD7, 7), POSE(3, 0xD7, 7), POSE(8, 0xD8, 7),
    POSE_END,
};

static AnimationFrame D_800AFB5C[] = {
    POSE(2, 0xC3, 1), POSE(2, 0xC2, 1),  POSE(2, 0xC1, 1), POSE(2, 0xC0, 1),
    POSE(2, 0xBF, 1), POSE(2, 0xC0, 1),  POSE(2, 0xBF, 1), POSE(2, 0xC0, 1),
    POSE(2, 0xBF, 1), POSE(36, 0xC0, 1), POSE_END,
};

static AnimationFrame D_800AFB88[] = {
    POSE(2, 0xC7, 3), POSE(2, 0xC8, 3),  POSE(2, 0xC9, 3), POSE(2, 0xCA, 3),
    POSE(2, 0xC9, 3), POSE(2, 0xCA, 3),  POSE(2, 0xC9, 3), POSE(2, 0xCA, 3),
    POSE(2, 0xC9, 3), POSE(24, 0xCA, 3), POSE_END,
};

static AnimationFrame D_800AFBB4[] = {
    POSE(2, 0xD2, 7), POSE(2, 0xD3, 7),  POSE(2, 0xD2, 7), POSE(2, 0xD3, 7),
    POSE(2, 0xD2, 7), POSE(36, 0xD3, 7), POSE_END,
};

// Unused
static AnimationFrame D_800AFBD0[] = {
    POSE(48, 0x7B, 1),
    POSE_END,
};

static AnimationFrame D_800AFBD8[] = {
    POSE(48, 0x79, 1),
    POSE_END,
};

static AnimationFrame D_800AFBE0[] = {
    POSE(3, 0x67, 1),  POSE(3, 0x68, 1), POSE(3, 0x69, 1),  POSE(3, 0x68, 1),
    POSE(3, 0x69, 1),  POSE(3, 0x68, 1), POSE(3, 0x69, 1),  POSE(3, 0x68, 1),
    POSE(24, 0x69, 1), POSE(4, 0x78, 1), POSE(32, 0x79, 1), POSE_END,
};

static AnimationFrame D_800AFC10[] = {
    POSE(6, 0x79, 1),
    POSE(6, 0x7A, 1),
    POSE(16, 0x7B, 1),
    POSE_END,
};

static AnimationFrame D_800AFC20[] = {
    POSE(6, 0x79, 1),
    POSE(6, 0x7A, 1),
    POSE(16, 0x79, 1),
    POSE_END,
};

static AnimationFrame D_800AFC30[] = {
    POSE(4, 0x8E, 1), POSE(4, 0x8F, 1), POSE(4, 0x90, 1),  POSE(20, 0x91, 1),
    POSE(4, 0x90, 1), POSE(4, 0x8F, 1), POSE(16, 0x8E, 1), POSE_JUMP(4),
};

AnimationFrame D_800AFC50[] = {
    POSE(40, 0x00, 0),
    POSE_END,
};

static AnimationFrame D_800AFC58[] = {
    POSE(2, 0x01, 15), POSE(3, 0x02, 15), POSE(4, 0x03, 15), POSE(4, 0x04, 15),
    POSE(3, 0x05, 15), POSE(2, 0x06, 15), POSE(2, 0x07, 15), POSE(2, 0x08, 15),
    POSE(2, 0x09, 15), POSE(2, 0x0A, 15), POSE_LOOP(0),
};

static AnimationFrame D_800AFC84[] = {
    POSE(1, 0x0C, 15), POSE(1, 0x0D, 15), POSE(1, 0x0F, 15), POSE(1, 0x10, 15),
    POSE(1, 0x0E, 15), POSE(1, 0x0D, 15), POSE(1, 0x0C, 15), POSE(1, 0x0D, 15),
    POSE(1, 0x0F, 15), POSE(2, 0x10, 15), POSE(2, 0x0E, 15), POSE(2, 0x0D, 15),
    POSE(2, 0x0C, 15), POSE(2, 0x0D, 15), POSE(2, 0x0F, 15), POSE(3, 0x10, 15),
    POSE(3, 0x0E, 15), POSE(3, 0x0D, 15), POSE_JUMP(196),
};

static AnimationFrame D_800AFCD0[] = {
    POSE(3, 0x01, 15), POSE(4, 0x02, 15), POSE(6, 0x03, 15), POSE(6, 0x04, 15),
    POSE(5, 0x05, 15), POSE(4, 0x06, 15), POSE(4, 0x07, 15), POSE(3, 0x08, 15),
    POSE(3, 0x09, 15), POSE(3, 0x0A, 15), POSE_LOOP(0),
};

static AnimationFrame D_800AFCFC[] = {
    POSE(4, 0x02, 15), POSE(6, 0x03, 15), POSE(6, 0x04, 15), POSE(5, 0x05, 15),
    POSE(4, 0x06, 15), POSE(4, 0x07, 15), POSE(3, 0x08, 15), POSE(3, 0x09, 15),
    POSE(3, 0x0A, 15), POSE(3, 0x01, 15), POSE_LOOP(9),
};

static AnimationFrame D_800AFD28[] = {
    POSE(6, 0x03, 15),
    POSE_END,
};

static AnimationFrame D_800AFD30[] = {
    POSE(4, 0xC7, 3), POSE(4, 0xC8, 3), POSE(4, 0xC9, 3), POSE(4, 0xCA, 3),
    POSE(4, 0xCB, 3), POSE(6, 0xCC, 3), POSE(5, 0xCD, 3), POSE(5, 0xCE, 3),
    POSE(5, 0xCF, 3), POSE_END,
};

static AnimationFrame D_800AFD58[] = {
    POSE(4, 0xCE, 3), POSE(4, 0xCD, 3), POSE(6, 0xCC, 3), POSE(5, 0xCD, 3),
    POSE(5, 0xCE, 3), POSE(5, 0xCF, 3), POSE_END,
};

static AnimationFrame D_800AFD74[] = {
    POSE(1, 0x0C, 15), POSE(1, 0x0D, 15), POSE(1, 0x0F, 15), POSE(1, 0x10, 15),
    POSE(1, 0x0E, 15), POSE(1, 0x0D, 15), POSE(1, 0x0C, 15), POSE(1, 0x0D, 15),
    POSE(1, 0x0F, 15), POSE(1, 0x10, 15), POSE(4, 0x0E, 15), POSE_END,
};

AnimationFrame D_800AFDA4[] = {
    POSE(128, 0x00, 0),
    POSE_END,
};

static AnimationFrame D_800AFDAC[] = {
    POSE(132, 0x5F, 0),
    POSE_END,
};

static AnimationFrame D_800AFDB4[] = {
    POSE(132, 0xC7, 0),
    POSE_END,
};

static AnimationFrame D_800AFDBC[] = {
    POSE(3, 0x01, 1), POSE(2, 0x02, 1), POSE(2, 0x03, 1), POSE(3, 0x04, 1),
    POSE(2, 0x03, 1), POSE(2, 0x02, 1), POSE_LOOP(0),
};

static AnimationFrame D_800AFDD8[] = {
    POSE(1, 0x05, 1),
    POSE(16, 0x06, 1),
    POSE_END,
};

static AnimationFrame D_800AFDE4[] = {
    POSE(128, 0x03, 1), POSE(1, 0x02, 1), POSE(16, 0x02, 1),
    POSE(16, 0x03, 1),  POSE(1, 0x02, 1), POSE(16, 0x02, 1),
    POSE(16, 0x03, 1),  POSE(1, 0x02, 1), POSE(16, 0x02, 1),
    POSE(16, 0x03, 1),  POSE(1, 0x02, 1), POSE(128, 0x02, 1),
    POSE_LOOP(0),
};

static AnimationFrame D_800AFE18[] = {
    POSE(128, 0x02, 1),
    POSE_END,
};

static AnimationFrame D_800AFE20[] = {
    POSE(128, 0x08, 1),
    POSE_END,
};

static AnimationFrame D_800AFE28[] = {
    POSE(1, 0x0C, 3),  POSE(1, 0x0B, 3), POSE(1, 0x0A, 3),
    POSE(24, 0x82, 3), POSE(1, 0x0F, 3), POSE_END,
};

static AnimationFrame D_800AFE40[] = {
    POSE(1, 0x10, 1),  POSE(1, 0x11, 1), POSE(1, 0x12, 1),
    POSE(20, 0x7D, 1), POSE(4, 0x7A, 1), POSE_JUMP(4),
};

static AnimationFrame D_800AFE58[] = {
    POSE(2, 0x1A, 0),   POSE(2, 0x1B, 0),  POSE(2, 0x1C, 0), POSE(2, 0x1D, 0),
    POSE(2, 0x1E, 0),   POSE(2, 0x1F, 0),  POSE(2, 0xD0, 0), POSE(4, 0xD1, 0),
    POSE(5, 0xD2, 0),   POSE(16, 0xD3, 0), POSE(2, 0x6A, 0), POSE(2, 0x6B, 0),
    POSE(2, 0x6C, 0),   POSE(2, 0x6D, 0),  POSE(3, 0x6E, 0), POSE(1, 0x6E, 0),
    POSE(128, 0x01, 0), POSE_END,
};

static AnimationFrame D_800AFEA0[] = {
    POSE(2, 0x1A, 0),   POSE(2, 0x1B, 0), POSE(2, 0x1C, 0), POSE(2, 0x1D, 0),
    POSE(2, 0x1E, 0),   POSE(2, 0x1F, 0), POSE(2, 0xD0, 0), POSE(4, 0xD1, 0),
    POSE(5, 0xD2, 0),   POSE(4, 0xD3, 0), POSE(2, 0xD0, 0), POSE(4, 0xD1, 0),
    POSE(5, 0xD2, 0),   POSE(4, 0xD3, 0), POSE(2, 0x6A, 0), POSE(2, 0x6B, 0),
    POSE(2, 0x6C, 0),   POSE(2, 0x6D, 0), POSE(3, 0x6E, 0), POSE(1, 0x6E, 0),
    POSE(128, 0x01, 0), POSE_END,
};

static AnimationFrame D_800AFEF8[] = {
    POSE(-3, 0x02, 0),
    POSE(4, 0x78, 1),
    POSE(64, 0x79, 1),
    POSE_END,
};

static AnimationFrame D_800AFF08[] = {
    POSE(1, 0xC5, 3), POSE(1, 0xC7, 3),  POSE(1, 0xC8, 3), POSE(1, 0xC9, 3),
    POSE(1, 0xCA, 3), POSE(1, 0xCB, 3),  POSE(4, 0xCC, 3), POSE(3, 0xCD, 3),
    POSE(3, 0xCE, 3), POSE(16, 0xCF, 3), POSE(8, 0x0F, 3), POSE_END,
};

static AnimationFrame D_800AFF38[] = {
    POSE(1, 0xC5, 3), POSE(1, 0xC7, 3),  POSE(1, 0xC8, 3), POSE(1, 0xC9, 3),
    POSE(1, 0xCA, 3), POSE(1, 0xCB, 3),  POSE(4, 0xCC, 3), POSE(3, 0xCD, 3),
    POSE(3, 0xCE, 3), POSE(16, 0xCF, 3), POSE(8, 0x0F, 3), POSE_END,
};

static AnimationFrame D_800AFF68[] = {
    POSE(128, 0x09, 18),
    POSE_LOOP(0),
};

static AnimationFrame D_800AFF70[] = {
    POSE(128, 0x0E, 18),
    POSE_LOOP(0),
};

static AnimationFrame D_800AFF78[] = {
    POSE(6, 0x0A, 18), POSE(6, 0x0B, 18), POSE(6, 0x0C, 18),
    POSE(6, 0x0D, 18), POSE(6, 0x0E, 18), POSE(6, 0x0F, 18),
    POSE(6, 0x10, 18), POSE(6, 0x11, 18), POSE_LOOP(0),
};

static AnimationFrame D_800AFF9C[] = {
    POSE(3, 0x09, 18), POSE(3, 0x21, 18), POSE(1, 0x22, 18), POSE(1, 0x22, 18),
    POSE(3, 0x21, 18), POSE(3, 0x09, 18), POSE_END,
};

AnimationFrame D_800AFFB8[] = {
    POSE(4, 0x02, 18), POSE(4, 0x03, 18), POSE(4, 0x04, 18),
    POSE(4, 0x05, 18), POSE(4, 0x06, 18), POSE(4, 0x07, 18),
    POSE(4, 0x08, 18), POSE(4, 0x09, 18), POSE_LOOP(0),
};

static AnimationFrame D_800AFFDC[] = {
    POSE(2, 0x12, 19),
    POSE(2, 0x13, 19),
    POSE_END,
};

static AnimationFrame D_800AFFE8[] = {
    POSE(2, 0x13, 19),
    POSE(2, 0x12, 19),
    POSE_END,
};

static AnimationFrame D_800AFFF4[] = {
    POSE(4, 0x12, 19),
    POSE(16, 0x14, 19),
    POSE(4, 0x12, 19),
    POSE_END,
};

static AnimationFrame D_800B0004[] = {
    POSE(16, 0x19, 20), POSE(6, 0x1A, 20), POSE(6, 0x1B, 20), POSE(6, 0x1C, 20),
    POSE(6, 0x1D, 20),  POSE(6, 0x1E, 20), POSE_END,
};

static AnimationFrame D_800B0020[] = {
    POSE(6, 0x15, 20), POSE(6, 0x16, 20), POSE(6, 0x17, 20), POSE(20, 0x18, 20),
    POSE(4, 0x17, 20), POSE(4, 0x16, 20), POSE(6, 0x1D, 20), POSE(4, 0x1E, 20),
    POSE(3, 0x1E, 20), POSE(3, 0x1E, 20), POSE(3, 0x1E, 20), POSE(3, 0x1E, 20),
    POSE_END,
};

static AnimationFrame D_800B0054[] = {
    POSE(4, 0x15, 20), POSE(4, 0x16, 20), POSE(4, 0x17, 20), POSE(4, 0x18, 20),
    POSE(4, 0x16, 20), POSE(6, 0x1D, 20), POSE(6, 0x1E, 20), POSE_END,
};

static AnimationFrame D_800B0074[] = {
    POSE(128, 0x46, 21),
    POSE_LOOP(0),
};

static AnimationFrame D_800B007C[] = {
    POSE(4, 0x55, 0),
    POSE_LOOP(0),
};

static AnimationFrame D_800B0084[] = {
    POSE(6, 0x1A, 20), POSE(6, 0x1B, 20), POSE(6, 0x1C, 20),
    POSE(6, 0x1D, 20), POSE(6, 0x1A, 20), POSE(6, 0x1B, 20),
    POSE(6, 0x1C, 20), POSE(6, 0x1D, 20), POSE_LOOP(0),
};

static AnimationFrame D_800B00A8[] = {
    POSE(2, 0x15, 20), POSE(2, 0x16, 20), POSE(2, 0x17, 20),
    POSE(8, 0x18, 20), POSE(2, 0x17, 20), POSE(2, 0x16, 20),
    POSE(2, 0x1D, 20), POSE(2, 0x1E, 20), POSE_END,
};

static AnimationFrame D_800B00CC[] = {
    POSE(8, 0xDA, 1),  POSE(8, 0xDB, 1), POSE(16, 0xDC, 1), POSE(8, 0xDD, 1),
    POSE(23, 0xDE, 1), POSE(4, 0xDF, 1), POSE_END,
};

static AnimationFrame D_800B00E8[] = {
    POSE(8, 0xDA, 1),
    POSE(8, 0xDB, 1),
    POSE(4, 0xE0, 1),
    POSE_END,
};

static AnimationFrame D_800B00F8[] = {
    POSE(3, 0x67, 1),  POSE(3, 0x68, 1), POSE(3, 0x69, 1),   POSE(3, 0x68, 1),
    POSE(3, 0x69, 1),  POSE(3, 0x68, 1), POSE(3, 0x69, 1),   POSE(3, 0x68, 1),
    POSE(24, 0x69, 1), POSE(4, 0x78, 1), POSE(512, 0x79, 1), POSE_END,
};

static AnimationFrame D_800B0128[] = {
    POSE(512, 0x79, 1),
    POSE_END,
};

s8 D_800B0130[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x14, 0x00, 0x07, 0x04,
    0x10, 0x00, 0x0D, 0x04, 0x09, 0x02, 0x03, 0x05, 0x0D, 0x05, 0xFF,
    0x08, 0x09, 0xFE, 0x04, 0x06, 0x10, 0x00, 0xFD, 0x04, 0x10, 0x05,
    0xFB, 0x06, 0x0C, 0x05, 0x01, 0x04, 0x14, 0x01, 0xF9, 0x0B, 0x09,
    0xFE, 0xFB, 0x19, 0x1A, 0xE0, 0xE1, 0x00, 0x00, 0x01, 0xFD, 0x07,
    0x07, 0x01, 0xFD, 0x07, 0x07, 0x00, 0x01, 0x04, 0x07, 0x01, 0xFD,
    0x07, 0x07, 0x00, 0x0D, 0x04, 0x0C, 0x00, 0x0D, 0x0A, 0x0A, 0x00,
    0x0F, 0x0A, 0x05, 0x00, 0x08, 0x0A, 0x08, 0x00, 0x0B, 0x08, 0x0C,
};

s8 D_800B0188[] = {
    0x00, 0x00, 0x00, 0x00, 0xE0, 0xE1, 0x00, 0x00, 0x09, 0x15, 0x04, 0x05,
    0x12, 0xF3, 0x05, 0x07, 0x12, 0xF5, 0x11, 0x07, 0x0B, 0x05, 0x05, 0x07,
    0x0C, 0x07, 0x10, 0x07, 0x0F, 0xF2, 0x05, 0x07, 0x12, 0xF6, 0x13, 0x07,
    0x06, 0xF6, 0x0C, 0x07, 0x13, 0x06, 0x08, 0x08, 0x15, 0x0C, 0x0B, 0x09,
};

AnimationFrame* D_800B01B8[] = {
    D_800AE2A8, D_800AE2C0, D_800AE2C8, D_800AE2DC, D_800AE2E4, D_800AE340,
    D_800AE374, D_800AE394, D_800AE3D8, D_800AE3F8, D_800AE424, D_800AE42C,
    D_800AE480, D_800AE488, D_800AE4CC, D_800AE514, D_800AE554, D_800AE594,
    D_800AE59C, D_800AE5A4, D_800AE5B8, D_800AE5C0, D_800AE5F8, D_800AE604,
    D_800AE61C, D_800AE628, D_800AE634, D_800AE640, D_800AE654, D_800AE66C,
    D_800AE6A8, D_800AE6C8, D_800AE6D4, D_800AE6FC, D_800AE708, D_800AEA1C,
    D_800AE788, D_800AE788, D_800AE7B0, D_800AE7B0, D_800AE7D4, D_800AE7EC,
    D_800AE804, D_800AE710, D_800AE710, D_800AE778, D_800AE82C, D_800AE834,
    D_800AE844, D_800AE84C, D_800AE878, D_800AE8A4, D_800AE8CC, D_800AE8F4,
    D_800AE900, D_800AE90C, D_800AE924, D_800AE92C, D_800AE934, D_800AE93C,
    D_800AEA74, D_800AEAC8, D_800AFC50, D_800AE964, D_800AE9E4, D_800AEAD0,
    D_800AEB34, D_800AEB64, D_800AEBC0, D_800AEBE0, D_800AEC10, D_800AEC40,
    D_800AEC58, D_800AEC9C, D_800AECA8, D_800AECEC, D_800AED0C, D_800AED28,
    D_800AED44, D_800AED60, D_800AEDB4, D_800AEDC0, D_800AEDF0, D_800AEE20,
    D_800AEE4C, D_800AEE78, D_800AEEA4, D_800AEEF8, D_800AEF04, D_800AEF34,
    D_800AEF64, D_800AEF90, D_800AEFBC, D_800AEFE8, D_800AF028, D_800AF098,
    D_800AF04C, D_800AF064, D_800AF098, D_800AF0C8, D_800AF0C8, D_800AF0DC,
    D_800AF0F0, D_800AF118, D_800AF140, D_800AF184, D_800AF190, D_800AF1CC,
    D_800AF204, D_800AF23C, D_800AF274, D_800AF2FC, D_800AF2FC, D_800AF320,
    D_800AF320, D_800AF340, D_800AF358, D_800AF358, D_800AF368, D_800AF39C,
    D_800AF3A8, D_800AF3D4, D_800AF400, D_800AF41C, D_800AF438, D_800AF454,
    D_800AF454, D_800AF478, D_800AF478, D_800AF340, D_800AF358, D_800AF358,
    D_800AF498, D_800AF4CC, D_800AF4D8, D_800AF504, D_800AF530, D_800AF54C,
    D_800AF54C, D_800AF568, D_800AF5C0, D_800AF5CC, D_800AF5CC, D_800AF61C,
    D_800AF63C, D_800AF65C, D_800AF678, D_800AF6B8, D_800AF6C4, D_800AF6FC,
    D_800AF734, D_800AF75C, D_800AF784, D_800AF7AC, D_800AF7E0, D_800AF7EC,
    D_800AF7EC, D_800AF818, D_800AF834, D_800AF834, D_800AF850, D_800AF884,
    D_800AF890, D_800AF890, D_800AF8BC, D_800AF8D8, D_800AF8D8, D_800AF8F4,
    D_800AF928, D_800AF934, D_800AF960, D_800AF98C, D_800AF9A8, D_800AF9C4,
    D_800AF9E0, D_800AFA2C, D_800AFA38, D_800AFA7C, D_800AFAC0, D_800AFAF4,
    D_800AFB28, D_800AFB5C, D_800AFB88, D_800AFBB4, D_800AFBD8, D_800AFBD8,
    D_800AFBE0, D_800AFBE0, D_800AFC10, D_800AFC20, D_800AFC30, D_800AFC30,
    D_800AEA44, D_800AEA60, D_800AFC58, D_800AFC84, D_800AFCD0, D_800AFCFC,
    D_800AFD28, D_800AFD30, D_800AFD58, D_800AFD74, D_800AFDA4, D_800AFDAC,
    D_800AFDB4, D_800AFDBC, D_800AFDD8, D_800AFDE4, D_800AFE18, D_800AFE20,
    D_800AFE40, D_800AFE40, D_800AFE28, D_800AFE28, D_800AF2E4, D_800AF2E4,
    D_800AFE58, D_800AFEA0, D_800AFEF8, D_800AE53C, D_800AFBD8, D_800AFBD8,
    D_800AFF68, D_800AFF70, D_800AFF78, D_800AFF9C, D_800AFFB8, D_800AFFDC,
    D_800AFFE8, D_800AFFF4, D_800B0004, D_800B0020, D_800B0054, D_800B0074,
    D_800B0054, D_800B007C, D_800B0084, D_800B00A8, D_800B00A8, D_800B00A8,
    D_800AFF08, D_800AFF38, D_800B00CC, D_800B00E8, D_800B00F8, D_800B0128,
    D_800AE5E0,
};

AnimationFrame* D_800B0594[] = {
    D_800AE434, D_800AE460, D_800AE4F4, D_800AE574, D_800AE690, D_800AEAFC,
    D_800AEB9C, D_800AEC28, D_800AEC64, D_800AECC8, D_800AEBF8, D_800AED6C,
    D_800AEEB0, D_800AEADC, D_800AEB40, D_800AEB84, D_800AE308, D_800AE324,
    D_800AF14C, D_800AF374, D_800AF4A4, D_800AF574, D_800AF684, D_800AF7B8,
    D_800AF85C, D_800AF900, D_800AF9EC, D_800AE990, D_800AF2A8,
};

u8 D_800B0608[] = {
    0x41, 0x48, 0x4F, 0x56, 0x56, 0x68, 0x6F, 0x76, 0x7D, 0x84,
    0x8B, 0x92, 0x99, 0xA0, 0xA7, 0xAE, 0xB5, 0x41, 0x41, 0x41,
    0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41,
};
