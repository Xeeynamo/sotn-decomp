// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include "sfx.h"

// Animations for EntityDraculaFinalForm
static u8 anim_80180AA4[] = {
    0x18, 0x01, 0x0F, 0x02, 0x0F, 0x03, 0x0F, 0x02, 0x00, 0x00};
static u8 anim_80180AB0[] = {
    0x07, 0x01, 0x07, 0x04, 0x0B, 0x03, 0x06, 0x05, 0x04, 0x06, 0x03, 0x07,
    0x02, 0x08, 0x02, 0x0F, 0x01, 0x14, 0x01, 0x13, 0x01, 0x14, 0xFF, 0x00};
static u8 anim_80180AC8[] = {
    0x0E, 0x14, 0x01, 0x10, 0x03, 0x0F, 0x07, 0x11, 0x06, 0x12, 0xFF, 0x00};
static u8 anim_80180AD4[] = {
    0x04, 0x06, 0x03, 0x05, 0x01, 0x04, 0x04, 0x03, 0x03, 0x02, 0x04,
    0x01, 0x02, 0x02, 0x02, 0x03, 0x05, 0x02, 0x10, 0x01, 0xFF, 0x00};
static u8 anim_80180AEC[] = {0x09, 0x01, 0x09, 0x09, 0x09, 0x0A, 0x08,
                             0x06, 0x07, 0x19, 0x10, 0x06, 0xFF, 0x00};
static u8 anim_80180AFC[] = {
    0x08, 0x06, 0x01, 0x1C, 0x07, 0x0A, 0x01, 0x1D, 0x07, 0x09, 0x01, 0x1E,
    0x05, 0x01, 0x01, 0x1F, 0x03, 0x16, 0x01, 0x20, 0x04, 0x17, 0x01, 0x21,
    0x08, 0x18, 0x01, 0x22, 0x06, 0x1A, 0x10, 0x1B, 0xFF, 0x00};
static u8 anim_80180B20[] = {
    0x01, 0x1B, 0x04, 0x1A, 0x09, 0x18, 0x03, 0x17, 0x03, 0x16, 0x02, 0x01,
    0x01, 0x09, 0x01, 0x0A, 0x02, 0x06, 0x05, 0x19, 0x10, 0x06, 0xFF, 0x00};
static u8 anim_80180B38_unused[] = {0x0C, 0x06, 0x0B, 0x0A, 0x09, 0x09, 0x04,
                                    0x01, 0x07, 0x02, 0x10, 0x01, 0xFF, 0x00};
static u8 anim_80180B48[] = {0x09, 0x01, 0x05, 0x0B, 0x05, 0x0C, 0x06,
                             0x23, 0x05, 0x0A, 0x10, 0x01, 0xFF, 0x00};
static u8 anim_80180B58[] = {0x09, 0x01, 0x06, 0x0D, 0x09, 0x0E, 0xFF, 0x00};
static u8 anim_80180B60[] = {
    0x10, 0x01, 0x09, 0x24, 0x09, 0x24, 0x10, 0x01, 0xFF, 0x00, 0x00, 0x00};
static u8 anim_80180B6C[] = {
    0x18, 0x01, 0x05, 0x31, 0x04, 0x04, 0x08, 0x03, 0x02,
    0x28, 0x04, 0x29, 0x04, 0x2A, 0x02, 0x18, 0xFF, 0x00};
static u8 anim_80180B80[] = {
    0x0C, 0x18, 0x03, 0x2B, 0x02, 0x2C, 0x01, 0x2D, 0x01, 0x2E,
    0x02, 0x2F, 0x01, 0x30, 0x01, 0x32, 0x01, 0x33, 0x02, 0x34,
    0x02, 0x35, 0x03, 0x36, 0x06, 0x13, 0x10, 0x36, 0xFF, 0x00};
static u8 anim_80180BA0[] = {
    0x04, 0x3D, 0x04, 0x3E, 0x04, 0x3F, 0x04, 0x40, 0x04, 0x41, 0x04, 0x42,
    0x04, 0x43, 0x04, 0x44, 0x04, 0x45, 0x04, 0x46, 0x06, 0x47, 0xFF, 0x00};
static u8 anim_80180BB8[] = {
    0x02, 0x48, 0x02, 0x49, 0x02, 0x4A, 0x02, 0x4B, 0x02,
    0x4C, 0x02, 0x4D, 0x02, 0x4E, 0x02, 0x4F, 0x00, 0x00};
static u8 anim_80180BCC[] = {0x01, 0x50, 0x01, 0x51, 0x01, 0x52, 0x01,
                             0x53, 0x01, 0x54, 0x01, 0x55, 0x00, 0x00};
static u8 anim_80180BDC[] = {0x01, 0x56, 0x01, 0x57, 0x01, 0x58, 0xFF, 0x00};

static u16 D_80180BE4[][3][4] = {
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-24, -16, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {20, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {20, 44, 12, 12}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {34, 49, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -2, 28, 33}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -2, 28, 33}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -2, 28, 33}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -2, 28, 33}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {30, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {20, 44, 12, 12}, {10, -4, 28, 36}},
    {{-26, 48, 8, 24}, {37, 48, 10, 16}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {20, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {20, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {20, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {20, 44, 12, 12}, {10, -4, 28, 36}},
    {{-25, 40, 7, 14}, {20, 44, 12, 12}, {10, -4, 28, 36}},
};
static s16 D_801810F4[] = {0x180, 0x300, 0x200, -1};
static s16 D_801810FC[] = {0xFFF0, 0x0018, 0x0030, 0xFFE0, 0x0008, 0xFFFF};
static Point16 D_80181108[] = {
    {0x0000, 0x0000}, {0x0024, 0x0000}, {0xFFF0, 0x0040}, {0x0018, 0x0010},
    {0x0000, 0x0040}, {0xFFE0, 0x0020}, {0x0008, 0x0000}, {0x0014, 0x0018},
    {0x0000, 0x0000}, {0x0024, 0x0000}, {0xFFF0, 0x0040}, {0x0018, 0x0010},
    {0x0000, 0x0040}, {0xFFE0, 0x0020}, {0x0008, 0x0000}, {0x0014, 0x0018}};
static s32 D_80181148 = 0;
static u32 D_8018114C = 0;
static Point16 D_80181150[] = {
    {0x00, 0x00}, {0x03, 0x04}, {0x07, 0x06}, {0x01, 0x0B}, {0x03, 0x0C},
    {0x08, 0x09}, {0x05, 0x0D}, {0x19, 0x06}, {0x19, 0x06}, {0x19, 0x06},
    {0x19, 0x06}, {0x11, 0x08}, {0x1E, 0x03}, {0x1F, 0x13}, {0x28, 0x0B},
    {0x3B, 0x0B}, {0x2B, 0x1C}, {0x39, 0x11}, {0x3D, 0x11}, {0x1D, 0x0B},
    {0x42, 0x0F}, {0x3F, 0x06}, {0x46, 0x0D}, {0x45, 0x08}, {0x39, 0x11},
    {0x3D, 0x11}, {0x2B, 0x1C}, {0x28, 0x1C}, {0x27, 0x1E}, {0x1B, 0x19},
    {0x1F, 0x0E}, {0x3E, 0x1D}, {0x25, 0x22}, {0x1B, 0x1E}, {0x21, 0x0B},
    {0x20, 0x0D}, {0x1F, 0x0F}, {0x16, 0x1D}, {0x16, 0x21}, {0x1A, 0x0A},
    {0x1B, 0x0D}, {0x1C, 0x0F}, {0x15, 0x26}, {0x1C, 0x2A}, {0x1C, 0x2D},
    {0x1D, 0x2D}, {0x26, 0x26}, {0x18, 0x53}, {0x20, 0x3A}, {0x26, 0x26},
    {0x26, 0x32}, {0x27, 0x3C}, {0x22, 0x3F}, {0x24, 0x4A}, {0x2A, 0x4A},
    {0x25, 0x4E}, {0x2B, 0x4F}, {0x25, 0x53}, {0x2E, 0x53}, {0x15, 0x3B},
    {0x1B, 0x3D}, {0x16, 0x41}, {0x1C, 0x45}, {0x15, 0x4C}, {0x1A, 0x4C},
    {0x13, 0x4F}, {0x10, 0x53}, {0x16, 0x53}, {0x1C, 0x53}, {0x26, 0x32},
    {0x28, 0x53}, {0x42, 0x53}, {0x3D, 0x28}, {0x3D, 0x32}, {0x3D, 0x3D},
    {0x3E, 0x43}, {0x3F, 0x4E}, {0x05, 0x1F}, {0x05, 0x2C}, {0x05, 0x3B},
    {0x06, 0x4D}, {0x05, 0x53}, {0x11, 0x1B}};
static Point16 D_8018129C[] = {
    {0x00, 0x00}, {0x00, 0x1C}, {0x00, 0x13}, {0x0F, 0x1B}, {0x0F, 0x16},
    {0x09, 0x0C}, {0x0F, 0x13}, {0x14, 0x05}, {0x12, 0x16}, {0x1B, 0x06},
    {0x1A, 0x1D}, {0x1C, 0x02}, {0x23, 0x04}, {0x2F, 0x0B}, {0x3E, 0x02},
    {0x5E, 0x07}, {0x3D, 0x1A}, {0x50, 0x12}, {0x5D, 0x1A}, {0x67, 0x17},
    {0x56, 0x25}, {0x6F, 0x26}, {0x59, 0x29}, {0x62, 0x31}, {0x51, 0x18},
    {0x56, 0x1A}, {0x48, 0x1D}, {0x52, 0x1F}, {0x51, 0x29}, {0x38, 0x2B},
    {0x34, 0x22}, {0x53, 0x35}, {0x4C, 0x34}, {0x38, 0x31}, {0x2E, 0x1D},
    {0x25, 0x28}, {0x25, 0x2E}, {0x2E, 0x30}, {0x2F, 0x35}, {0x0F, 0x1C},
    {0x0E, 0x22}, {0x20, 0x33}, {0x28, 0x38}, {0x3C, 0x47}, {0x39, 0x4A},
    {0x42, 0x4C}, {0x50, 0x39}, {0x42, 0x54}, {0x49, 0x56}, {0x5A, 0x38},
    {0x61, 0x45}, {0x5F, 0x53}, {0x4E, 0x62}, {0x5C, 0x65}, {0x68, 0x67},
    {0x5F, 0x6A}, {0x72, 0x6A}, {0x5D, 0x74}, {0x78, 0x74}, {0x11, 0x4F},
    {0x26, 0x58}, {0x18, 0x5B}, {0x2A, 0x5D}, {0x20, 0x67}, {0x28, 0x69},
    {0x13, 0x6B}, {0x0E, 0x74}, {0x24, 0x74}, {0x31, 0x74}, {0x5C, 0x4C},
    {0x49, 0x56}, {0x78, 0x74}, {0x4C, 0x34}, {0x5C, 0x4C}, {0x5F, 0x53},
    {0x68, 0x67}, {0x72, 0x6A}, {0x2E, 0x30}, {0x28, 0x38}, {0x18, 0x5B},
    {0x20, 0x67}, {0x0E, 0x74}, {0x25, 0x28}};
static u8 D_801813E8[] = {
    0x02, 0x04, 0x01, 0x03, 0x05, 0x06, 0x02, 0x04, 0x11, 0x0F, 0x12, 0x13,
    0x12, 0x13, 0x14, 0x15, 0x14, 0x15, 0x16, 0x17, 0x1D, 0x1C, 0x21, 0x20,
    0x25, 0x1D, 0x26, 0x21, 0x26, 0x21, 0x2B, 0x20, 0x26, 0x2B, 0x2A, 0x2C,
    0x2A, 0x2C, 0x3B, 0x3C, 0x3B, 0x3C, 0x3D, 0x3E, 0x3D, 0x3E, 0x3F, 0x40,
    0x3F, 0x40, 0x43, 0x44, 0x41, 0x3F, 0x42, 0x43, 0x2B, 0x20, 0x2D, 0x2E,
    0x2D, 0x2E, 0x30, 0x45, 0x30, 0x45, 0x34, 0x33, 0x34, 0x33, 0x35, 0x36,
    0x35, 0x36, 0x37, 0x38, 0x37, 0x38, 0x39, 0x3A, 0x2C, 0x2D, 0x2F, 0x46,
    0x11, 0x12, 0x1B, 0x1F, 0x1B, 0x1F, 0x20, 0x48, 0x20, 0x48, 0x45, 0x49,
    0x45, 0x49, 0x33, 0x4A, 0x33, 0x4A, 0x36, 0x4B, 0x36, 0x4B, 0x38, 0x4C,
    0x38, 0x4C, 0x3A, 0x47, 0x06, 0x52, 0x4D, 0x25, 0x4D, 0x25, 0x4E, 0x2A,
    0x4E, 0x2A, 0x4F, 0x3D, 0x4F, 0x3D, 0x50, 0x3F, 0x50, 0x3F, 0x51, 0x42,
    0x0E, 0x0F, 0x1E, 0x11, 0x1E, 0x11, 0x24, 0x10, 0x24, 0x10, 0x0D, 0x1B,
    0x0D, 0x1B, 0x1D, 0x1C, 0x0C, 0x0E, 0x22, 0x1E, 0x23, 0x22, 0x24, 0x1E,
    0x0C, 0x22, 0x0A, 0x23, 0x0A, 0x23, 0x27, 0x24, 0x28, 0x29, 0x27, 0x24,
    0x0B, 0x0A, 0x05, 0x27, 0x27, 0x28, 0x05, 0x29, 0x24, 0x0D, 0x29, 0x1D,
    0x52, 0x29, 0x25, 0x1D, 0x06, 0x05, 0x52, 0x29, 0x00, 0x00, 0x00, 0x00};
static u8 D_801814A8[] = {
    0x02, 0x04, 0x01, 0x03, 0x05, 0x06, 0x02, 0x04, 0x05, 0x07, 0x06, 0x08,
    0x07, 0x09, 0x08, 0x0A, 0x07, 0x0B, 0x09, 0x0C, 0x09, 0x0C, 0x0A, 0x0D,
    0x0C, 0x0E, 0x0D, 0x0F, 0x0D, 0x0F, 0x10, 0x11, 0x11, 0x0F, 0x12, 0x13,
    0x11, 0x12, 0x18, 0x19, 0x10, 0x11, 0x1A, 0x18, 0x18, 0x19, 0x1A, 0x1B,
    0x19, 0x12, 0x1B, 0x14, 0x12, 0x13, 0x14, 0x15, 0x14, 0x15, 0x16, 0x17,
    0x1B, 0x14, 0x1C, 0x16, 0x1C, 0x16, 0x20, 0x1F, 0x0D, 0x10, 0x22, 0x1E,
    0x1E, 0x10, 0x1D, 0x1A, 0x1A, 0x1B, 0x1D, 0x1C, 0x1D, 0x1C, 0x21, 0x20,
    0x22, 0x1E, 0x23, 0x1D, 0x23, 0x1D, 0x26, 0x21, 0x25, 0x1D, 0x26, 0x21,
    0x26, 0x21, 0x2B, 0x20, 0x26, 0x2B, 0x2A, 0x2C, 0x2A, 0x2C, 0x3B, 0x3C,
    0x3B, 0x3C, 0x3D, 0x3E, 0x3D, 0x3E, 0x3F, 0x40, 0x3F, 0x40, 0x43, 0x44,
    0x41, 0x3F, 0x42, 0x43, 0x2B, 0x20, 0x2D, 0x2E, 0x2D, 0x2E, 0x30, 0x45,
    0x31, 0x32, 0x2E, 0x45, 0x30, 0x45, 0x34, 0x33, 0x34, 0x33, 0x35, 0x36,
    0x35, 0x36, 0x37, 0x38, 0x37, 0x38, 0x39, 0x3A, 0x2B, 0x2D, 0x2C, 0x30,
    0x28, 0x27, 0x29, 0x08, 0x29, 0x08, 0x24, 0x0A, 0x24, 0x0A, 0x22, 0x0D,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

bool func_801ADAC8(s32 arg0) {
    s32 unk = 0xD0;
    Entity* entity = g_CurrentEntity;
    s16 temp_v1 = entity->posY.i.hi + arg0;

    if (temp_v1 >= unk) {
        entity->posY.i.hi = unk - temp_v1 + entity->posY.i.hi;
        return true;
    } else {
        return false;
    }
}

// Function unique to ST0. Has many similarities to ClutLerp.
// Unclear what it actually does; no known calls.
void func_801ADB10(u16* arg0, u16 arg1, u16 arg2, s32 steps, u8* arg4) {
    u16 buf[COLORS_PER_PAL];
    RECT bufRect;
    s32 temp_a2;
    s32 factor;
    s32 temp_v0;
    s32 i;
    s32 j;
    s32 var_v0;
    u16* palA;

    u32 t;
    u32 r, g, b;
    u32 tempR;
    u32 tempG;
    u32 tempB;

    bufRect.x = *arg0;
    bufRect.w = COLORS_PER_PAL;
    bufRect.h = 1;

    arg4[0] >>= 3;
    arg4[1] >>= 3;
    arg4[2] >>= 3;
    palA = g_Clut + arg1 * COLORS_PER_PAL;

    for (i = 0; i < steps; arg2++, i++) {
        factor = i * 4096 / steps;
        for (j = 0; j < 16; j++) {
            if (j == 0) {
                buf[0] = *palA;
            } else {
                t = palA[j] & 0x8000;
                tempR = (palA[j] & 0x1F);
                r = (tempR * (4096 - factor)) + (arg4[0] * factor);
                tempG = (palA[j] >> 5) & 0x1F;
                tempR = r >> 12;
                g = (tempG * (4096 - factor)) + (arg4[1] * factor);
                tempB = (palA[j] >> 10) & 0x1F;
                tempG = g >> 12;
                b = (tempB * (4096 - factor)) + (arg4[2] * factor);
                tempB = b >> 12;
                buf[j] = ((t | (tempR)) | (tempG << 5)) | (tempB << 10);
                (g_Clut + (arg2 * COLORS_PER_PAL))[j] = buf[j];
            }
        }
        temp_a2 = arg2 - 0x200;
        var_v0 = temp_a2;
        if (var_v0 < 0) {
            var_v0 = arg2 - 0x1F1;
        }
        temp_v0 = var_v0 >> 4;
        bufRect.y = temp_v0 + 0xF0;
        bufRect.x = ((temp_a2 - (temp_v0 * 0x10)) * 0x10) + 0x100;
        LoadImage(&bufRect, buf);
        g_ClutIds[arg2] = GetClut(bufRect.x, bufRect.y);
    }
}

extern s32 D_80180910;
void EntityDraculaFinalForm(Entity* self) {
    byte stackpad[56];
    Entity* temp_s2;
    Entity* var_s1;
    Primitive* prim;
    s16 primIndex;
    s32 i;
    s16* temp_s1;
    s32 xShift;
    s32 timerDiff;
    u16 selfzPriority;
    s32 selfParams;

    if (self->flags & FLAG_DEAD) {
        self->hitboxState = 0;
        if (self->step < 6) {
            D_8003C744 = 3;
            SetStep(6);
        }
    }
    if (self->params == 0) {
        if (!(g_Timer & 1)) {
            self->palette = 0x204;
        } else {
            self->palette = 0x202;
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaFinalForm);
        self->hitboxHeight = 16;
        self->hitboxWidth = 16;
        self->hitboxOffX = -24;
        self->hitboxOffY = -16;
        self->hitboxState = 0;
        if (self->params == 0) {
            temp_s2 = self + 1;
            D_8003C744 = 2;
            var_s1 = self + 1;
            self->animCurFrame = 0;
            for (i = 1; i < 4; i++, temp_s2++, var_s1++) {
                CreateEntityFromCurrentEntity(E_DRACULA_UNK20, temp_s2);
                selfzPriority = self->zPriority;
                var_s1->params = i;
                var_s1->unk60 = temp_s2 - 1;
                var_s1->unk5C = self;

                var_s1->zPriority = selfzPriority + 2;
                // seems hitPoints might be used for something else
                var_s1->hitPoints = 0x7FFE;
            }
            self->unk5C = 0;
            self->unk60 = self + 3;
        } else {
            self->animCurFrame = 0;
            SetStep(16);
        }
        break;
    case 1:
        if (D_801C2578 == 0) {
            self->animCurFrame = 1;
        }
        if (D_80180910 != 0) {
            self->animCurFrame = 1;
            self->hitboxState = 3;
            self->unk6C = 0x80;
            self->drawFlags = FLAG_DRAW_DEFAULT;
            SetStep(2);
        }
        break;
    case 2:
        if (self->step_s == 0) {
            self->ext.dracFinalForm.timer = 80;
            self->step_s++;
        }
        if ((AnimateEntity(anim_80180AA4, self) == 0) &&
            (((GetSideToPlayer() & 1) ^ 1) != self->facingLeft)) {
            SetStep(3);
        }
        if (--self->ext.dracFinalForm.timer == 0) {
            SetStep(5);
            if ((self->posX.i.hi < 152) && (self->facingLeft == 1)) {
                if (Random() & 1) {
                    SetStep(7);
                } else {
                    SetStep(4);
                }
            } else if ((self->posX.i.hi > 104) && (self->facingLeft == 0)) {
                if (Random() & 1) {
                    SetStep(7);
                } else {
                    SetStep(4);
                }
            } else if (Random() & 1) {
                SetStep(8);
            } else {
                SetStep(4);
            }
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (AnimateEntity(anim_80180AB0, self) == 0) {
                SetSubStep(2);
            }
            if (self->animFrameIdx == 5 && self->animFrameDuration == 0) {
                if (self->facingLeft) {
                    self->velocityX = FIX(0.5);
                } else {
                    self->velocityX = FIX(-0.5);
                }
                self->velocityY = FIX(-4.0);
            }
            MoveEntity();
            if (self->velocityY != 0) {
                self->velocityY += FIX(10.0 / 128);
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY += FIX(10.0 / 128);
            if (self->velocityY >= 0) {
                AnimateEntity(anim_80180AC8, self);
            }
            if (func_801ADAC8(0x4C) != 0) {
                g_api.PlaySfx(SFX_START_SLAM_B);
                g_api.func_80102CD8(1);
                self->step_s++;
            }
            break;
        case 3:
            if (AnimateEntity(anim_80180AD4, self) == 0) {
                SetStep(2);
            }
        }
        break;
    case 3:
        if (AnimateEntity(anim_80180B60, self) == 0) {
            if ((self->posX.i.hi < 160) && (self->facingLeft == 1)) {
                if (Random() & 1) {
                    SetStep(4);
                } else {
                    SetStep(7);
                }
            } else if ((self->posX.i.hi > 96) && (self->facingLeft == 0)) {
                if (Random() & 1) {
                    SetStep(4);
                } else {
                    SetStep(7);
                }
            } else {
                SetStep(2);
            }
        }
        if (self->animFrameIdx == 2 && self->animFrameDuration == 0) {
            self->facingLeft = (self->facingLeft ^ 1);
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(anim_80180B48, self) == 0) {
                g_api.PlaySfx(0x866);
                self->step_s++;
            }
            break;
        case 1:
            temp_s2 = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (temp_s2 != NULL) {
                CreateEntityFromEntity(E_DRACULA_UNK21, self, temp_s2);
                temp_s2->posX.i.hi = temp_s2->posX.i.hi;
                temp_s2->posY.i.hi = temp_s2->posY.i.hi;
                temp_s2->facingLeft = self->facingLeft;
                temp_s2->params = 1;
            }
            self->ext.dracFinalForm.timer = 32;
            self->step_s++;
            break;
        case 2:
            // FAKE assignment to i
            if (i = --self->ext.dracFinalForm.timer == 0) {
                self->ext.dracFinalForm.unk84 = 0;
                self->step_s++;
            }
            break;
        case 3:
            if (self->ext.dracFinalForm.timer != 0) {
                self->ext.dracFinalForm.timer--;
                break;
            }
            self->ext.dracFinalForm.timer = 48;
            temp_s1 = &D_801810F4;
            temp_s1 += self->ext.dracFinalForm.unk84;
            if (*temp_s1 == -1) {
                SetStep(2);
                return;
            }
            if (self->facingLeft) {
                xShift = 32;
            } else {
                xShift = -32;
            }
            temp_s2 = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (temp_s2 != NULL) {
                g_api.PlaySfx(SFX_FIREBALL_SHOT_A);
                CreateEntityFromEntity(E_DRACULA_UNK21, self, temp_s2);
                temp_s2->posX.i.hi = (xShift + temp_s2->posX.i.hi);
                temp_s2->posY.i.hi = (temp_s2->posY.i.hi - 4);
                temp_s2->rotZ = *temp_s1;
                if (self->facingLeft) {
                    temp_s2->rotZ = (0x800 - temp_s2->rotZ);
                }
            }
            self->ext.dracFinalForm.unk84++;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.dracFinalForm.timer = 4;
            self->ext.dracFinalForm.unk84 = 0;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (AnimateEntity(anim_80180B80, self) == 0) {
                SetSubStep(2);
            }
            if (self->animFrameIdx == 3 && self->animFrameDuration == 0) {
                g_api.PlaySfx(0x866);
                self->velocityY = FIX(-7.0);
            }
            MoveEntity();
            if (self->velocityY != 0) {
                self->velocityY += FIX(0.09375);
            }
            if (--self->ext.dracFinalForm.timer == 0) {
                temp_s1 = &D_801810F4[4];
                temp_s1 += self->ext.dracFinalForm.unk84;
                if (*temp_s1 == -1) {
                    self->ext.dracFinalForm.timer = 0x7FFF;
                    return;
                }
                self->ext.dracFinalForm.timer = 6;
                temp_s2 = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (temp_s2 != NULL) {
                    g_api.PlaySfx(SFX_FIREBALL_SHOT_B);
                    CreateEntityFromEntity(E_DRACULA_FIREBALL, self, temp_s2);
                    temp_s2->posX.i.hi = (temp_s2->posX.i.hi + *temp_s1);
                    temp_s2->zPriority = (self->zPriority + 1);
                }
                self->ext.dracFinalForm.unk84++;
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (self->velocityY >= 0) {
                AnimateEntity(anim_80180AC8, self);
            }
            if (func_801ADAC8(0x4C) != 0) {
                g_api.PlaySfx(SFX_START_SLAM_B);
                g_api.func_80102CD8(1);
                self->step_s++;
            }
            break;
        case 3:
            if (AnimateEntity(anim_80180AD4, self) == 0) {
                SetStep(2);
            }
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(anim_80180AEC, self) == 0) {
                SetSubStep(1);
            }
            break;
        case 1:
            if (AnimateEntity(anim_80180AFC, self) == 0) {
                g_api.PlaySfx(0x856);
                temp_s2 = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (temp_s2 != NULL) {
                    CreateEntityFromEntity(E_DRACULA_UNK2E, self, temp_s2);
                    if (self->facingLeft != 0) {
                        temp_s2->posX.i.hi += 40;
                    } else {
                        temp_s2->posX.i.hi -= 40;
                    }
                    temp_s2->posY.i.hi += 16;
                    temp_s2->facingLeft = self->facingLeft;
                }
                SetSubStep(2);
            }
            break;
        case 2:
            if (AnimateEntity(anim_80180B20, self) == 0) {
                SetSubStep(3);
            }
            break;
        case 3:
            self->ext.dracFinalForm.timer = 256;
            self->step_s++;
            break;
        case 4:
            if (--self->ext.dracFinalForm.timer == 0) {
                SetStep(2);
            }
        }
        break;
    case 16:
        temp_s2 = self - self->params;
        self->facingLeft = temp_s2->facingLeft;
        self->hitboxState = temp_s2->hitboxState;
        temp_s1 = &D_80180BE4;
        self->posX.i.hi = temp_s2->posX.i.hi;
        self->posY.i.hi = temp_s2->posY.i.hi;
        // Fake reuse of the i variable
        i = temp_s2->animCurFrame - 1;
        temp_s1 += i * 12;
        temp_s1 += (self->params - 1) * 4;
        self->hitboxOffX = *temp_s1++;
        self->hitboxOffY = *temp_s1++;

        self->hitboxWidth = *temp_s1++;
        self->hitboxHeight = *temp_s1++;
        if (self->params == 1) {
            switch (self->step_s) {
            case 0:
                self->ext.dracFinalForm.timer = 100;
                self->step_s++;
                return;
            case 1:
                if (--self->ext.dracFinalForm.timer == 0) {
                    self->animCurFrame = 0x5A;
                    self->unk5A = 0x5E;
                    self->palette = PAL_OVL(0x15F);
                    self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
                    self->drawFlags =
                        FLAG_DRAW_UNK8 | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
                    self->unk6C = 0x10;
                    self->rotY = 0x400;
                    self->rotX = 0x400;
                    g_api.PlaySfx(0x880);
                    self->step_s++;
                }
                break;
            case 2:
                self->rotX = self->rotY = self->rotY - 0x18;
                if (self->rotY < 0x100) {
                    self->animCurFrame = 0;
                    self->drawMode = DRAW_DEFAULT;
                    self->drawFlags = FLAG_DRAW_DEFAULT;
                    self->step_s++;
                }
                break;
            case 3:
                if (D_801C2578 == 0) {
                    self->animCurFrame = 1;
                    self->unk5A = 0x50;
                    self->palette = PAL_OVL(0x15F);
                    self->drawFlags = FLAG_DRAW_UNK8;
                    self->unk6C = 0;
                    self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
                    self->step_s++;
                }
                break;
            case 4:
                self->unk6C += 4;
                self->animCurFrame = temp_s2->animCurFrame;
                if (self->unk6C > 0x60) {
                    self->step_s++;
                }
                break;
            case 5:
                self->unk6C -= 4;
                self->animCurFrame = temp_s2->animCurFrame;
                if (self->unk6C == 0) {
                    self->animCurFrame = 0;
                    self->drawMode = DRAW_DEFAULT;
                    self->drawFlags = FLAG_DRAW_DEFAULT;
                    self->step_s++;
                }
                break;
            }
        }
        break;
    case 6: // Time attack call indicates this state is Dracula's defeat
        switch (self->step_s) {
        case 0:
            g_api.PlaySfx(0x866);
            temp_s2 = self + 1;
            self->hitboxState = 0;
            for (i = 0; i < 3; i++) {
                DestroyEntity(temp_s2);
                temp_s2++;
            }
            g_api.PlaySfx(0x80);
            self->ext.dracFinalForm.timer = 4;
            self->ext.dracFinalForm.unk84 = 0;
            g_api.TimeAttackController(
                TIMEATTACK_EVENT_DRACULA_DEFEAT, TIMEATTACK_SET_RECORD);
            g_PauseAllowed = false;
            D_80181148 = 0x800;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (AnimateEntity(anim_80180B58, self) == 0) {
                self->step_s++;
            }
            break;
        case 2:
            if (g_api.func_80131F68() == true) {
                if (--D_80181148 == 0) {
                    D_80181148 = 0x800;
                    g_api.PlaySfx(0x80);
                }
            } else {
                g_api.PlaySfx(0x35E);
                D_8018114C = g_Timer;
                self->step_s++;
            }
            break;
        case 3:
            if (g_api.func_80131F68() == false) {
                // Fake reuse of the i variable
                i = g_Timer - D_8018114C;
                if (i >= 0x301) {
                    g_api.PlaySfx(SFX_EXPLODE_A);
                    self->ext.dracFinalForm.unk82 = 0x80;
                    self->step_s++;
                    break;
                }
                g_api.func_80102CD8(1);
                D_80181148--;
                if (D_80181148 == 0) {
                    D_80181148 = 0x800;
                    g_api.PlaySfx(0x80);
                    self->step_s--;
                    break;
                }
            } else {
                g_api.PlaySfx(SFX_EXPLODE_A);
                self->ext.dracFinalForm.unk82 = 0x80;
                self->step_s++;
            }
            break;
        case 4:
            if (--self->ext.dracFinalForm.unk82 == 0) {
                self->step_s++;
            }
            break;
        case 5:
            CreateEntityFromCurrentEntity(E_DRACULA_UNK2C, self + 1);
            self->step_s++;
            primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
            if (primIndex == -1) {
                g_GameEngineStep = 0xA;
                g_MenuStep = 0;
                return;
            }
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->ext.prim = prim;
            self->flags |= FLAG_HAS_PRIMS;
            prim->r0 = prim->g0 = prim->b0 = 0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->x0 = prim->x2 = 0;
            prim->x1 = prim->x3 = 0x100;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            prim->priority = self->zPriority + 0x10;
            prim->drawMode = DRAW_TRANSP | 0x30;
            self->step_s++;
        case 6:
            prim = self->ext.prim;
            prim->g0 = prim->b0 = prim->r0 = prim->r0 + 0x18;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            if (prim->r0 >= 0x81) {
                self->step_s++;
            }
            break;
        case 7:
            break;
        }
        if (--self->ext.dracFinalForm.timer == 0) {
            g_api.PlaySfx(SFX_EXPLODE_B);
            self->ext.dracFinalForm.timer = 8;
            temp_s2 = AllocEntity(&g_Entities[224], &g_Entities[256]);
            temp_s1 = &D_80181108[self->ext.dracFinalForm.unk84].x;
            if (temp_s2 != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, temp_s2);
                temp_s2->params = 3;
                temp_s2->zPriority = (self->zPriority + 1);
                temp_s2->posX.i.hi = (temp_s2->posX.i.hi + *temp_s1++);
                temp_s2->posY.i.hi = (temp_s2->posY.i.hi + *temp_s1++);
            }
            self->ext.dracFinalForm.unk84 =
                ((self->ext.dracFinalForm.unk84 + 1) & 0xF);
        }
        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
    }
}

void EntityDraculaMegaFireball(Entity* self) {
    s16 angle;

    if (self->step == 0) {
        InitializeEntity(g_EInitDraculaMegaFireball);
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        if (self->params == 0) {
            angle = self->rotZ;
            self->rotY = 0x80;
            self->rotX = 0x80;
            self->drawFlags |= FLAG_DRAW_ROTZ | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
            self->rotZ = 0x1C0 - angle;
            if (self->facingLeft != 0) {
                self->velocityX = rcos(angle) * 0x60;
            } else {
                self->velocityX = -(rcos(angle) * 0x60);
            }
            self->velocityY = rsin(angle) * 0x60;
        }
    }
    if (self->params != 0) {
        if (AnimateEntity(anim_80180BA0, self) == 0) {
            DestroyEntity(self);
        }
        if (g_Timer & 1) {
            self->animCurFrame = 0;
        }
    } else {
        if (self->rotX < 0x100) {
            self->rotX = self->rotY = self->rotY + 0x10;
        }
        AnimateEntity(anim_80180BB8, self);
        MoveEntity();
    }
}

extern EInit g_EInitDraculaRainAttack;
void EntityDraculaRainAttack(Entity* self) {
    Entity* newEntity;
    s32 velY;
    s32 velX;
    s16 angle;
    s32 i;

    if (self->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 2;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDraculaRainAttack);
        if (self->params != 0) {
            self->hitboxState = 0;
            self->animCurFrame = 0x59;
            velX = (Random() & 0x1F) + 0x10;
            angle = (Random() * 6) + 0x900;
            self->velocityX = velX * rcos(angle);
            velY = velX * rsin(angle);
            self->step = 3;
            self->velocityY = velY;
            break;
        }
        self->velocityY = FIX(4);

    case 1:
        MoveEntity();
        AnimateEntity(anim_80180BCC, self);
        if (func_801ADAC8(0x14) != 0) {
            SetStep(2);
        }
        break;

    case 2:
        if (AnimateEntity(anim_80180BDC, self) == 0) {

            for (i = 0; i < 4; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_DRACULA_FIREBALL, self, newEntity);
                    newEntity->params = 1;
                    newEntity->posY.i.hi += 12;
                }
            }
            DestroyEntity(self);
        }
        break;

    case 3:
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (self->posY.i.hi >= 0xF1) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_801AF380(void) {
    Primitive* prim;
    s16* var_t0;
    s32 i;
    u8* var_a3;
    s32 uBase;
    s32 vBase;

    var_t0 = &D_80181150[0];
    var_a3 = &D_801813E8;
    uBase = 0;
    vBase = 0;
    prim = g_CurrentEntity->ext.et_801AF774.prim1;
    for (i = 0; i < 47; i++) {
        prim->tpage = 0x17;
        prim->clut = 0x200;
        // This should REALLY be done using Point16, but no,
        // that would make too much sense for SOTN
        prim->u0 = uBase + var_t0[*var_a3 * 2];
        prim->v0 = vBase + var_t0[*var_a3 * 2 + 1];
        var_a3++;
        prim->u1 = uBase + var_t0[*var_a3 * 2];
        prim->v1 = vBase + var_t0[*var_a3 * 2 + 1];
        var_a3++;
        prim->u2 = uBase + var_t0[*var_a3 * 2];
        prim->v2 = vBase + var_t0[*var_a3 * 2 + 1];
        var_a3++;
        prim->u3 = uBase + var_t0[*var_a3 * 2];
        prim->v3 = vBase + var_t0[*var_a3 * 2 + 1];
        var_a3++;
        prim->r0 = prim->g0 = prim->b0 = 0x80;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0xA0;
        prim->drawMode = DRAW_TRANSP | 0x34;
        prim = prim->next;
    }
    var_t0 = (s16*)D_8018129C;
    var_a3 = (s16*)D_801814A8;
    uBase = 0;
    vBase = 0x80;
    g_CurrentEntity->ext.et_801AF774.prim2 = prim;
    for (i = 0; i < 42; i++) {
        prim->tpage = 0x17;
        prim->clut = 0x204;
        prim->u0 = uBase + var_t0[*var_a3 * 2];
        prim->v0 = vBase + var_t0[*var_a3 * 2 + 1];
        var_a3++;
        prim->u1 = uBase + var_t0[*var_a3 * 2];
        prim->v1 = vBase + var_t0[*var_a3 * 2 + 1];
        var_a3++;
        prim->u2 = uBase + var_t0[*var_a3 * 2];
        prim->v2 = vBase + var_t0[*var_a3 * 2 + 1];
        var_a3++;
        prim->u3 = uBase + var_t0[*var_a3 * 2];
        prim->v3 = vBase + var_t0[*var_a3 * 2 + 1];
        var_a3++;
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0xA0;
        prim->drawMode = DRAW_TRANSP | 0x34;
        prim = prim->next;
    }

    var_t0 = D_80181150;
    for (i = 0; i < LEN(D_80181150); i++) {
        D_801BEB64[i].x = (*var_t0++ - 0x1E) << 0x10;
        D_801BEB64[i].y = (*var_t0++ - 0x53) << 0x10;
    }
}

void func_801AF6D0(void) {
    s16* var_a0;
    s16* var_a1;
    s32 i;
    Point32* var_a2;
    s32 a, b, c, d;

    var_a1 = (s16*)D_80181150;
    var_a0 = (s16*)D_8018129C;

    d = -0x1E;
    c = -0x53;
    b = -0x38;
    a = -0x75;

    var_a2 = D_801BEB64;
    for (i = 0; i < LEN(D_80181150); ++i) {
        D_801BEB64[i].x += ((b + *var_a0++) - (d + *var_a1++)) << 9;
        D_801BEB64[i].y += ((a + *var_a0++) - (c + *var_a1++)) << 9;
        var_a2++;
    }
}

static inline s32 add(s32 a, s32 b) { return a + b; }
void func_801AF774(Entity* self) {
    RECT sp10;
    DRAWENV sp18;
    DRAWENV* var_a2;
    DRAWENV* var_a3;
    Primitive* prim;
    s32 primIndex;
    s32 i;
    u32 var_t0;
    u8 temp_t0;
    u8* var_a2_3;
    s16* temp_a3;
    s32 xBase;
    s32 yBase;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDracula);
        self->hitboxState = 0;
        self->animCurFrame = 0;
        self->drawMode |= (DRAW_TPAGE | 0x20);
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        D_801C2578 = 1;
        self->ext.et_801AF774.unk90 = 1;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x5C);
        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
            self->primIndex = primIndex;
            self->ext.et_801AF774.prim3 = prim;
            self->flags |= FLAG_HAS_PRIMS;
            prim->tpage = 0x110;
            if (!self->facingLeft) {
                prim->u0 = prim->u2 = 0;
                prim->u1 = prim->u3 = 0x80;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 0x80;
            } else {
                prim->u1 = prim->u3 = 0;
                do {
                    prim->u0 = prim->u2 = 0x7F;
                    prim->v0 = prim->v1 = 0;
                    prim->v2 = prim->v3 = 0x80;
                } while (0);
            }

            prim->x0 = prim->x2 = self->posX.i.hi - 0x40;
            prim->x1 = prim->x3 = self->posX.i.hi + 0x40;
            prim->y0 = prim->y1 = self->posY.i.hi - 0x25;
            prim->y2 = prim->y3 = self->posY.i.hi + 0x5B;
            prim->r0 = prim->g0 = prim->b0 = 0x80;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->drawMode = DRAW_UNK02 | DRAW_HIDE;
            prim->priority = 0xA8;
            prim = prim->next;
            self->ext.et_801AF774.prim4 = prim;
            if (g_api.func_800EDB08(prim) == NULL) {
                g_api.FreePrimitives(primIndex);
                self->step = 0;
                self->flags &= ~FLAG_HAS_PRIMS;
                return;
            }
            prim->type = PRIM_ENV;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            g_api.func_800EDB08(prim);
            if (prim == NULL) {
                g_api.FreePrimitives(primIndex);
                self->step = 0;
                self->flags &= ~FLAG_HAS_PRIMS;
                return;
            }
            prim->type = PRIM_ENV;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            self->ext.prim = prim;
            while (prim != NULL) {
                prim->priority = 0xA0;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
                var_a3 = &sp18;
            }
        } else {
            self->step = 0;
            FntPrint("can't get effect works!\n");
            return;
        }
    case 1:
        var_a3 = &sp18;
        prim = self->ext.et_801AF774.prim4;
        var_a2 = &g_CurrentBuffer->draw;
        *var_a3 = *var_a2;
        sp18.isbg = 1;
        sp18.r0 = 0;
        sp18.g0 = 0;
        sp18.b0 = 0;
        sp10.x = 0;
        sp10.y = 0x100;
        sp10.w = 0x7f;
        sp10.h = 0xff;
        sp18.clip = sp10;
        sp18.ofs[0] = 0;
        sp18.ofs[1] = 0x100;
        SetDrawEnv(LOW(prim->r1), &sp18);
        prim->priority = 0x9F;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        prim->priority = 0xA1;
        prim->drawMode = DRAW_UNK_800;
    case 6:
        self->step++;
        return;

    case 2:
        func_801AF380();
        var_a3 = &sp18;
        prim = self->ext.et_801AF774.prim4;
        var_a2 = &g_CurrentBuffer->draw;
        var_t0 = LOW(prim->r1);
        *var_a3 = *var_a2;
        sp18.isbg = 0;
        sp18.dtd = 0;
        sp10.x = 0;
        sp10.y = 0x100;
        sp10.w = 0x80;
        sp10.h = 0x80;
        sp18.clip = sp10;
        sp18.ofs[0] = 0;
        sp18.ofs[1] = 0x100;
        SetDrawEnv(var_t0, &sp18);
        prim->priority = 0x9F;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        prim->priority = 0xA1;
        prim->drawMode = DRAW_UNK_800;
        self->ext.et_801AF774.unk8E = 0x80;
        self->ext.et_801AF774.unk8C = 0x8000;
        self->step_s = 0;
        self->step++;
        return;
    case 3:
        prim = self->ext.et_801AF774.prim3;
        prim->drawMode =
            DRAW_TPAGE | DRAW_TPAGE2 | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        if (self->ext.et_801AF774.unk8E > 0) {
            func_801AF6D0();
        }
        var_t0 = (u16)self->ext.et_801AF774.unk8C >> 8;
        if (var_t0 >= 0x81) {
            var_t0 = 0x80;
        }
        var_t0 = (u8)var_t0 >> 3;
        prim = self->ext.prim;
        xBase = 0x40;
        yBase = 0x70;
        temp_a3 = &D_801BEB64;
        var_a2_3 = &D_801813E8;

        for (i = 0; i < 47; i++) {
            prim->x0 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y0 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x1 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y1 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x2 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y2 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x3 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y3 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->b0 = var_t0;
            prim->g0 = var_t0;
            prim->r0 = var_t0;

            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        var_t0 = (u16)self->ext.et_801AF774.unk8C >> 8;
        if (var_t0 >= 0x81U) {
            var_t0 = 0x80;
        }
        var_t0 = (0x80 - var_t0);
        temp_t0 = var_t0;
        temp_t0 >>= 3;
        prim = self->ext.et_801AF774.prim2;
        temp_a3 = &D_801BEB64;
        var_a2_3 = &D_801814A8;
        xBase = 0x40;
        yBase = 0x70;
        for (i = 0; i < 42; i++) {
            prim->x0 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y0 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x1 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y1 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x2 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y2 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;
            prim->x3 = add(xBase, temp_a3[*var_a2_3 * 4 + 1]);
            prim->y3 = add(yBase, temp_a3[*var_a2_3 * 4 + 3]);
            var_a2_3++;

            prim->r0 = prim->g0 = prim->b0 = temp_t0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
        }
        self->ext.et_801AF774.unk8C =
            ((--self->ext.et_801AF774.unk8E << 0x10) >> 8);
        if (self->ext.et_801AF774.unk8E < 0) {
            self->step = 4;
        }
        if ((self->ext.et_801AF774.unk90 != 0) &&
            (self->ext.et_801AF774.unk8E < 0x10)) {
            self->ext.et_801AF774.unk90 = 0;
            CreateEntityFromCurrentEntity(E_DRACULA_UNK23, self + 1);
        }
        return;
    case 4:
        prim = self->ext.et_801AF774.prim3;
        prim->drawMode =
            DRAW_TPAGE | DRAW_TPAGE2 | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
        D_801C2578 = 0;
        if (prim != NULL) {
            do {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            } while (prim != NULL);
        }
        self->ext.et_801AF774.unk8E = 0x10;
        self->step++;
        return;
    case 5:
        if (--self->ext.et_801AF774.unk8E == 0) {
            self->step++;
            return;
        }
        break;
    case 7:
        if (PrimDecreaseBrightness(self->ext.et_801AF774.prim3, 7) == 0) {
            D_80180910 = 1;
            DestroyEntity(self);
        }
        break;
    }
}
