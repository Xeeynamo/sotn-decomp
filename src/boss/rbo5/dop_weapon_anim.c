// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

static u16 D_us_80184124[] = {
    WPOSE(1, 1),  WPOSE(2, 2),  WPOSE(3, 2),  WPOSE(4, 2), WPOSE(5, 2),
    WPOSE(6, 3),  WPOSE(7, 3),  WPOSE(8, 3),  WPOSE(9, 3), WPOSE(10, 4),
    WPOSE(11, 4), WPOSE(12, 4), WPOSE(13, 4), WPOSE_END};
static u16 D_us_80184140[] = {
    WPOSE(14, 5), WPOSE(15, 6), WPOSE(16, 6), WPOSE(17, 6), WPOSE(18, 6),
    WPOSE(19, 7), WPOSE(20, 7), WPOSE(21, 7), WPOSE(22, 7), WPOSE(31, 4),
    WPOSE(32, 4), WPOSE(33, 4), WPOSE(34, 4), WPOSE_END};
static u16 D_us_8018415C[] = {
    WPOSE(14, 5),  WPOSE(23, 8),  WPOSE(24, 9),  WPOSE(25, 8),  WPOSE(26, 9),
    WPOSE(27, 10), WPOSE(28, 10), WPOSE(29, 10), WPOSE(30, 10), WPOSE(31, 4),
    WPOSE(32, 4),  WPOSE(33, 4),  WPOSE(34, 4),  WPOSE_END};
static u16 D_us_80184178[] = {
    WPOSE(35, 11), WPOSE(36, 12), WPOSE(37, 12), WPOSE(38, 12),
    WPOSE(39, 12), WPOSE(40, 13), WPOSE(41, 13), WPOSE(42, 13),
    WPOSE(43, 13), WPOSE(44, 4),  WPOSE_END,     0};
static u16 D_us_80184190[] = {
    WPOSE(45, 14), WPOSE(46, 15), WPOSE(47, 15), WPOSE(48, 15),
    WPOSE(49, 15), WPOSE(50, 16), WPOSE(51, 16), WPOSE(52, 16),
    WPOSE(53, 16), WPOSE(62, 4),  WPOSE_END,     0};
static u16 D_us_801841A8[] = {
    WPOSE(45, 14), WPOSE(54, 17), WPOSE(55, 17), WPOSE(56, 17),
    WPOSE(57, 17), WPOSE(58, 18), WPOSE(59, 18), WPOSE(60, 18),
    WPOSE(61, 18), WPOSE(62, 4),  WPOSE_END,     0};
static s8 D_us_801841C0[][4] = {
    {0, 0, 0, 0},     {4, -23, 8, 5},   {30, -17, 35, 8}, {30, -14, 18, 4},
    {-32, -31, 0, 0}, {-4, -6, 8, 5},   {22, 0, 35, 8},   {22, 3, 18, 4},
    {29, 22, 13, 11}, {12, 7, 19, 12},  {14, 14, 18, 4},  {1, -25, 8, 5},
    {27, -19, 35, 8}, {27, -16, 18, 4}, {-8, -26, 8, 5},  {24, -17, 35, 8},
    {24, -14, 18, 4}, {23, 0, 27, 14},  {18, 2, 21, 11},  {29, -14, 34, 4},
    {21, 3, 34, 4},   {28, 21, 12, 10}, {26, -16, 34, 4}, {23, -14, 34, 4},
    {22, 3, 26, 10}};
static u16 D_us_80184224[] = {
    WPOSE(1, 1), WPOSE(2, 2), WPOSE(3, 2), WPOSE(4, 3), WPOSE(5, 3),
    WPOSE(6, 3), WPOSE(7, 3), WPOSE(8, 3), WPOSE(9, 3), WPOSE_END};
static u16 D_us_80184238[] = {
    WPOSE(10, 4), WPOSE(11, 5), WPOSE(12, 5), WPOSE(13, 3), WPOSE(14, 3),
    WPOSE(19, 3), WPOSE(20, 3), WPOSE(21, 3), WPOSE(22, 3), WPOSE_END};
static u16 D_us_8018424C[] = {
    WPOSE(10, 4), WPOSE(15, 6), WPOSE(16, 7), WPOSE(17, 8), WPOSE(18, 3),
    WPOSE(19, 3), WPOSE(20, 3), WPOSE(21, 3), WPOSE(22, 3), WPOSE_END};
static u16 D_us_80184260[] = {
    WPOSE(23, 9), WPOSE(24, 10), WPOSE(25, 10), WPOSE(26, 3),
    WPOSE(27, 3), WPOSE(28, 3),  WPOSE_END,     0};
static u16 D_us_80184270[] = {
    WPOSE(29, 11), WPOSE(30, 12), WPOSE(31, 12), WPOSE(32, 3),
    WPOSE(33, 3),  WPOSE(38, 3),  WPOSE_END,     0};
static u16 D_us_80184280[] = {
    WPOSE(29, 11), WPOSE(34, 13), WPOSE(35, 14), WPOSE(36, 3),
    WPOSE(37, 3),  WPOSE(38, 3),  WPOSE_END,     0};
static s8 D_us_80184290[][4] = {
    {0, 0, 0, 0},     {3, -24, 5, 4},  {25, -13, 24, 3}, {-32, -31, 0, 0},
    {-5, -5, 5, 4},   {17, 4, 24, 3},  {7, 15, 14, 8},   {19, 21, 15, 7},
    {13, 18, 17, 5},  {-1, -25, 5, 4}, {23, -15, 24, 7}, {-9, -27, 5, 4},
    {19, -14, 24, 7}, {15, 2, 19, 10}, {29, 8, 11, 8}};
static u16* D_us_801842CC[] = {
    D_us_80184124, D_us_80184124, D_us_80184140, D_us_8018415C,
    D_us_80184178, D_us_80184190, D_us_801841A8,
};
static u16* D_us_801842E8[] = {
    D_us_80184224, D_us_80184224, D_us_80184238, D_us_8018424C,
    D_us_80184260, D_us_80184270, D_us_80184280,
};
DopWeaponAnimation D_us_80184304[] = {
    {(AnimationFrame*)D_us_801842CC, (s8*)D_us_801841C0, 0x060B, 0x41, 0x04},
    {(AnimationFrame*)D_us_801842E8, (s8*)D_us_80184290, 0x060B, 0xA7, 0x04},
    {(AnimationFrame*)D_us_801842CC, (s8*)D_us_801841C0, 0x060B, 0x41, 0x04},
};
