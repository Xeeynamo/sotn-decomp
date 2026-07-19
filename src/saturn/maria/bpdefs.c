// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

u8 g_MariaEmptyAnimMarker = 0;

u8 g_MariaBlueprintColors[][4] = {
    {16, 127, 63, 0},   {16, 127, 0, 0},    {16, 63, 63, 127},
    {16, 63, 127, 63},  {16, 47, 63, 127},  {16, 63, 127, 127},
    {16, 31, 127, 127}, {16, 95, 95, 95},   {16, 0, 0, 127},
    {16, 127, 47, 47},  {16, 127, 127, 127},
};

SubweaponDef g_MariaSubweaponDefs[] = {
    {0, 30000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x1, 0xF, 0x0, 0x0},
    {10, 4, 0x1040, 0x6, 0x4, 0x4, 0x0, 0x2B, 0x2, 0x84, 0x15, 0x0, 0x20},
    {20, 4, 0x1040, 0x6, 0x20, 0x4, 0x0, 0x13, 0x2, 0x83, 0x14, 0x0, 0x20},
    {5, 1, 0x20, 0x1, 0x20, 0x4, 0x0, 0x6, 0x2, 0x1, 0x10, 0x0, 0x0},
    {40, 1, 0x1020, 0x3, 0x20, 0x4, 0x0, 0x2, 0x2, 0x81, 0xC, 0x0, 0x0},
    {15, 5, 0x1000, 0x2, 0x18, 0x4, 0x0, 0x3D, 0x2, 0x1, 0x1A, 0x0, 0x0},
    {0, 10, 0x0, 0x1, 0x32, 0x0, 0x0, 0x3F, 0x0, 0x0, 0x1B, 0x0, 0x0},
    {40, 1, 0x1020, 0x3, 0x20, 0x4, 0x0, 0x32, 0x2, 0x1, 0x19, 0x0, 0x0},
    {20, 2, 0x1000, 0x3, 0xA, 0x4, 0x0, 0x31, 0x2, 0x1, 0x18, 0x0, 0x0},
    {20, 10, 0x5000, 0x1, 0xA, 0xA, 0x0, 0x33, 0x2, 0x81, 0x1C, 0x0, 0x0},
    {15, 30000, 0x1000, 0x1, 0xA, 0x4, 0x0, 0x0, 0x2, 0x1, 0xA, 0x0, 0x0},
    {8, 1, 0x9000, 0x2, 0x10, 0x4, 0x0, 0x9, 0x2, 0x1, 0x0, 0x0, 0x0},
    {40, 20, 0x1020, 0x1, 0x20, 0x4, 0x0, 0xD, 0x2, 0x1, 0x0, 0x0, 0x0},
    {60, 0, 0x1020, 0x1, 0x18, 0x4, 0x0, 0x0, 0x2, 0x1, 0x0, 0x0, 0x0},
    {32, 5, 0x1020, 0x1, 0x20, 0x4, 0x0, 0x0, 0x2, 0x1, 0x0, 0x0, 0x0},
    {64, 15, 0x9020, 0x1, 0x20, 0x4, 0x0, 0x0, 0x2, 0x1, 0x0, 0x0, 0x20},
    {80, 15, 0x1020, 0x1, 0x20, 0x18, 0x0, 0xC, 0x82, 0x1, 0x0, 0x0, 0x0},
    {80, 0, 0x20, 0x1, 0x20, 0x4, 0x0, 0x0, 0x2, 0x1, 0x0, 0x0, 0x20},
    {20, 0, 0x20, 0x1, 0x20, 0x4, 0x0, 0x0, 0x2, 0x1, 0x0, 0x0, 0x0},
    {5, 0, 0x1020, 0x1, 0x20, 0x4, 0x0, 0x0, 0x2, 0x1, 0x0, 0x0, 0x0},
    {40, 10, 0x1040, 0x1, 0x20, 0x4, 0x0, 0x29, 0x2, 0x81, 0x0, 0x0, 0x20},
    {20, 10, 0x1040, 0x1, 0x4, 0x4, 0x0, 0x2C, 0x2, 0x81, 0x0, 0x0, 0x20},
    {80, 0, 0x20, 0x1, 0x20, 0x4, 0x0, 0x0, 0x2, 0x1, 0x0, 0x0, 0x20},
    {45, 0, 0x20, 0x1, 0x20, 0x4, 0x0, 0x0, 0x2, 0x1, 0x0, 0x0, 0x80},
    {20, 10, 0x1020, 0x1, 0x20, 0x4, 0x0, 0x36, 0x2, 0x1, 0x0, 0x0, 0x0},
    {20, 10, 0x20, 0x1, 0x20, 0x4, 0x0, 0x38, 0x2, 0x1, 0x0, 0x0, 0x0},
    {80, 15, 0x1020, 0x1, 0x20, 0x4, 0x0, 0x3B, 0x2, 0x1, 0x0, 0x0, 0x0},
    {0, 20, 0x20, 0x1, 0x20, 0x20, 0x0, 0x41, 0x2, 0x1, 0x0, 0x0, 0x0},
    {80, 20, 0x4020, 0x1, 0x20, 0x4, 0x0, 0x43, 0x2, 0x1, 0x0, 0x0, 0x0},
    {10, 30000, 0x20, 0x1, 0x20, 0x4, 0x0, 0x0, 0x82, 0x1, 0x0, 0x0, 0x0},
    {15, 30000, 0x4020, 0x1, 0x20, 0x40, 0x0, 0x0, 0x2, 0x1, 0x0, 0x0, 0x0},
};

u16 g_MariaBlueprintPadding = 0;

u8 g_MariaPrimitiveSizeIndices[] = {0x1B, 0x1A, 0x09, 0x18, 0x17, 0x16};

AnimationFrame g_MariaAnimSmokeDark[] = {
    POSE(2, 1, 0),  POSE(2, 2, 0),  POSE(2, 3, 0),  POSE(2, 4, 0),
    POSE(2, 5, 0),  POSE(2, 6, 0),  POSE(2, 7, 0),  POSE(2, 8, 0),
    POSE(2, 9, 0),  POSE(2, 10, 0), POSE(2, 11, 0), POSE(2, 12, 0),
    POSE(2, 13, 0), POSE_END,
};

u16 g_MariaBlueprintAuxPadding = 0;

extern void func_060B099C(Entity*);
extern void func_060AC9E0(Entity*);
extern void func_060AD3A8(Entity*);
extern void func_060B7A48(Entity*);
extern void func_060B7E08(Entity*);
extern void func_060AD7D8(Entity*);
extern void func_060B7F50(Entity*);
extern void func_060B8B24(Entity*);
extern void func_060B9048(Entity*);
extern void func_060AE014(Entity*);
extern void func_060B868C(Entity*);
extern void func_060B72B4(Entity*);
extern void func_060AE2C8(Entity*);
extern void func_060B82AC(Entity*);
extern void func_060B776C(Entity*);
extern void func_060AE3C0(Entity*);
extern void func_060ACD98(Entity*);
extern void func_060ACF8C(Entity*);
extern void func_060AE730(Entity*);
extern void func_060AE8D8(Entity*);
extern void func_060AD048(Entity*);
extern void func_060AEB18(Entity*);
extern void func_060B805C(Entity*);
extern void func_060AEFB4(Entity*);
extern void func_060AF17C(Entity*);
extern void func_060B82B8(Entity*);
extern void func_060B668C(Entity*);
extern void func_060B6C94(Entity*);
extern void func_060B626C(Entity*);
extern void func_060ACE84(Entity*);
extern void func_060AF444(Entity*);
extern void func_060AFBA4(Entity*);
extern void func_060B09CC(Entity*);
extern void func_060B1474(Entity*);
extern void func_060B1A58(Entity*);
extern void func_060B1E78(Entity*);
extern void func_060B2604(Entity*);
extern void func_060B2474(Entity*);
extern void func_060B2FC8(Entity*);
extern void func_060B29D4(Entity*);
extern void func_060B2E7C(Entity*);
extern void func_060B3678(Entity*);
extern void func_060B30BC(Entity*);
extern void func_060B5E28(Entity*);
extern void func_060B5C3C(Entity*);
extern void func_060B4CF4(Entity*);
extern void func_060B4B80(Entity*);
extern void func_060B44E8(Entity*);
extern void func_060B3684(Entity*);
extern void func_060B46BC(Entity*);
extern void func_060B46A0(Entity*);
extern void MariaEntityCrashReboundStoneParticles(Entity*);
extern void func_060AC458(Entity*);
extern void func_060AC1FC(Entity*);
extern void func_060B382C(Entity*);
extern void MariaEntityStopwatchCrashLightning(Entity*);
extern void func_060B0474(Entity*);
extern void func_060B09B4(Entity*);
extern void func_060B85C8(Entity*);
extern void func_060B9404(Entity*);
extern void func_060AD0E8(Entity*);
extern void func_060AD248(Entity*);
extern void func_060B96C0(Entity*);
extern void func_060BADA8(Entity*);
extern void func_060BAFF0(Entity*);
extern void func_060BB4AC(Entity*);
extern void func_060BBEF8(Entity*);
extern void func_060BC320(Entity*);
extern void func_060BB334(Entity*);
extern void func_060BB868(Entity*);
extern void func_060BB724(Entity*);
extern void func_060BCBD8(Entity*);
extern void func_060B9B88(Entity*);
extern void func_060B9D88(Entity*);
extern void func_060B99A8(Entity*);
extern void func_060BD0D0(Entity*);
extern void func_060B18C8(Entity*);
extern void func_060BD150(Entity*);
extern void func_060BD244(Entity*);
extern void func_060BCCE8(Entity*);
extern void func_060BCFF4(Entity*);
extern void func_060BD474(Entity*);

PfnEntityUpdate g_MariaEntityUpdates[] = {
    func_060B099C, // 0
    func_060AC9E0, // 1
    func_060AD3A8, // 2
    func_060B7A48, // 3
    func_060B7E08, // 4
    func_060AD7D8, // 5
    func_060B7F50, // 6
    func_060B8B24, // 7
    func_060B9048, // 8
    func_060AE014, // 9
    func_060B099C, // 10
    func_060B868C, // 11
    func_060B099C, // 12
    func_060B72B4, // 13
    func_060B099C, // 14
    func_060B099C, // 15
    func_060B099C, // 16
    func_060B099C, // 17
    func_060B099C, // 18
    func_060AE2C8, // 19
    func_060B82AC, // 20
    func_060B776C, // 21
    func_060AE3C0, // 22
    func_060ACD98, // 23
    func_060ACF8C, // 24
    func_060AE730, // 25
    func_060AE8D8, // 26
    func_060B099C, // 27
    func_060B099C, // 28
    func_060AD048, // 29
    func_060B099C, // 30
    func_060AEB18, // 31
    func_060B805C, // 32
    func_060AEFB4, // 33
    func_060AF17C, // 34
    func_060B82B8, // 35
    func_060B668C, // 36
    func_060B6C94, // 37
    func_060B626C, // 38
    func_060ACE84, // 39
    func_060AF444, // 40
    func_060AFBA4, // 41
    func_060B09CC, // 42
    func_060B1474, // 43
    func_060B1A58, // 44
    func_060B1E78, // 45
    func_060B2604, // 46
    func_060B2474, // 47
    func_060B2FC8, // 48
    func_060B29D4, // 49
    func_060B2E7C, // 50
    func_060B3678, // 51
    func_060B30BC, // 52
    func_060B5E28, // 53
    func_060B5C3C, // 54
    func_060B4CF4, // 55
    func_060B4B80, // 56
    func_060B44E8, // 57
    func_060B3684, // 58
    func_060B46BC, // 59
    func_060B46A0, // 60
    MariaEntityCrashReboundStoneParticles, // 61
    func_060AC458, // 62
    func_060AC1FC, // 63
    func_060B382C, // 64
    MariaEntityStopwatchCrashLightning, // 65
    func_060B0474, // 66
    func_060B09B4, // 67
    func_060B85C8, // 68
    func_060B9404, // 69
    func_060AD0E8, // 70
    func_060AD248, // 71
    func_060B96C0, // 72
    func_060BADA8, // 73
    func_060BAFF0, // 74
    func_060BB4AC, // 75
    func_060BBEF8, // 76
    func_060BC320, // 77
    func_060BB334, // 78
    func_060BB868, // 79
    func_060BB724, // 80
    func_060BCBD8, // 81
    func_060B9B88, // 82
    func_060B9D88, // 83
    func_060B96C0, // 84
    func_060B99A8, // 85
    func_060BD0D0, // 86
    func_060B18C8, // 87
    func_060BD150, // 88
    func_060BD244, // 89
    func_060BCCE8, // 90
    func_060BCFF4, // 91
    func_060BD474, // 92
};

typedef struct {
    u8 childId;
    u8 amount;
    u8 packedCount;
    u8 timerCycle;
    u8 packedOrigin;
    u8 timerDelay;
} MariaFactoryBlueprint;

#define B_MAKE(entityId, amount, nPerCycle, isNonCritical, incParamsKind,      \
               timerCycle, kind, origin, timerDelay)                           \
    {(entityId), (amount),                                                     \
     ((nPerCycle) & 0x3F) | ((!!(incParamsKind)) << 6) |                       \
         ((!!(isNonCritical)) << 7),                                           \
     (timerCycle), ((kind) & 7) | (((origin) & 31) << 3), (timerDelay)}

MariaFactoryBlueprint g_MariaFactoryBlueprints[] = {
    B_MAKE(0x02, 5, 1, 1, 1, 2, 0, 0, 0), // 0 @ 0x1CF24
    B_MAKE(0x02, 3, 1, 1, 1, 4, 0, 4, 0), // 1 @ 0x1CF2A
    B_MAKE(0x03, 1, 1, 1, 1, 0, 1, 3, 8), // 2 @ 0x1CF30
    B_MAKE(0x04, 3, 1, 1, 1, 2, 0, 0, 0), // 3 @ 0x1CF36
    B_MAKE(0x05, 1, 1, 1, 1, 0, 0, 0, 0), // 4 @ 0x1CF3C
    B_MAKE(0x06, 1, 1, 1, 1, 0, 0, 0, 1), // 5 @ 0x1CF42
    B_MAKE(0x07, 1, 1, 1, 1, 0, 1, 3, 8), // 6 @ 0x1CF48
    B_MAKE(0x08, 1, 1, 1, 1, 0, 1, 0, 0), // 7 @ 0x1CF4E
    B_MAKE(0x09, 6, 1, 1, 1, 12, 0, 7, 0), // 8 @ 0x1CF54
    B_MAKE(0x09, 128, 1, 1, 1, 3, 0, 7, 8), // 9 @ 0x1CF5A
    B_MAKE(0x0A, 15, 15, 0, 1, 0, 2, 3, 0), // 10 @ 0x1CF60
    B_MAKE(0x05, 72, 1, 1, 1, 2, 3, 2, 0), // 11 @ 0x1CF66
    B_MAKE(0x0B, 48, 1, 0, 1, 6, 1, 2, 48), // 12 @ 0x1CF6C
    B_MAKE(0x0D, 1, 1, 0, 1, 0, 1, 1, 0), // 13 @ 0x1CF72
    B_MAKE(0x0C, 6, 1, 1, 1, 24, 1, 1, 0), // 14 @ 0x1CF78
    B_MAKE(0x0E, 16, 16, 0, 1, 0, 0, 3, 0), // 15 @ 0x1CF7E
    B_MAKE(0x0F, 15, 15, 1, 1, 0, 0, 3, 0), // 16 @ 0x1CF84
    B_MAKE(0x10, 1, 1, 0, 1, 0, 4, 3, 0), // 17 @ 0x1CF8A
    B_MAKE(0x11, 1, 1, 1, 1, 0, 0, 1, 0), // 18 @ 0x1CF90
    B_MAKE(0x24, 3, 1, 1, 1, 4, 1, 3, 10), // 19 @ 0x1CF96
    B_MAKE(0x13, 1, 1, 1, 1, 0, 0, 8, 0), // 20 @ 0x1CF9C
    B_MAKE(0x14, 1, 1, 1, 1, 0, 0, 0, 0), // 21 @ 0x1CFA2
    B_MAKE(0x15, 1, 1, 0, 1, 0, 3, 0, 0), // 22 @ 0x1CFA8
    B_MAKE(0x16, 4, 1, 0, 1, 24, 3, 0, 6), // 23 @ 0x1CFAE
    B_MAKE(0x02, 1, 1, 1, 1, 0, 0, 0, 0), // 24 @ 0x1CFB4
    B_MAKE(0x17, 1, 1, 1, 1, 0, 1, 0, 0), // 25 @ 0x1CFBA
    B_MAKE(0x18, 1, 1, 1, 1, 0, 1, 0, 0), // 26 @ 0x1CFC0
    B_MAKE(0x19, 1, 1, 1, 1, 0, 3, 0, 0), // 27 @ 0x1CFC6
    B_MAKE(0x1A, 1, 1, 1, 1, 0, 3, 0, 0), // 28 @ 0x1CFCC
    B_MAKE(0x1B, 1, 1, 0, 1, 0, 5, 0, 0), // 29 @ 0x1CFD2
    B_MAKE(0x1C, 4, 1, 1, 1, 4, 3, 0, 0), // 30 @ 0x1CFD8
    B_MAKE(0x27, 1, 1, 1, 1, 0, 1, 0, 0), // 31 @ 0x1CFDE
    B_MAKE(0x1E, 1, 1, 1, 1, 0, 0, 0, 0), // 32 @ 0x1CFE4
    B_MAKE(0x1F, 1, 1, 1, 1, 0, 0, 0, 0), // 33 @ 0x1CFEA
    B_MAKE(0x20, 1, 1, 1, 1, 0, 0, 0, 0), // 34 @ 0x1CFF0
    B_MAKE(0x21, 1, 1, 1, 1, 0, 0, 0, 0), // 35 @ 0x1CFF6
    B_MAKE(0x22, 1, 1, 1, 1, 0, 0, 0, 0), // 36 @ 0x1CFFC
    B_MAKE(0x22, 1, 1, 1, 1, 0, 0, 0, 4), // 37 @ 0x1D002
    B_MAKE(0x22, 1, 1, 1, 1, 0, 0, 0, 8), // 38 @ 0x1D008
    B_MAKE(0x22, 1, 1, 1, 1, 0, 0, 0, 12), // 39 @ 0x1D00E
    B_MAKE(0x23, 1, 1, 1, 1, 0, 0, 0, 0), // 40 @ 0x1D014
    B_MAKE(0x25, 8, 8, 0, 1, 0, 1, 2, 32), // 41 @ 0x1D01A
    B_MAKE(0x05, 3, 1, 1, 1, 3, 0, 0, 0), // 42 @ 0x1D020
    B_MAKE(0x26, 3, 1, 1, 1, 4, 1, 3, 8), // 43 @ 0x1D026
    B_MAKE(0x26, 128, 1, 0, 1, 4, 6, 9, 8), // 44 @ 0x1D02C
    B_MAKE(0x1D, 1, 1, 1, 1, 0, 1, 0, 0), // 45 @ 0x1D032
    B_MAKE(0x05, 12, 1, 1, 1, 2, 0, 7, 0), // 46 @ 0x1D038
    B_MAKE(0x28, 1, 1, 1, 1, 0, 0, 0, 0), // 47 @ 0x1D03E
    B_MAKE(0x29, 1, 1, 1, 1, 0, 0, 0, 0), // 48 @ 0x1D044
    B_MAKE(0x2B, 1, 1, 1, 1, 0, 1, 2, 8), // 49 @ 0x1D04A
    B_MAKE(0x2A, 1, 1, 1, 1, 0, 1, 2, 4), // 50 @ 0x1D050
    B_MAKE(0x2C, 1, 1, 1, 1, 0, 1, 2, 4), // 51 @ 0x1D056
    B_MAKE(0x2D, 1, 1, 1, 1, 0, 0, 2, 0), // 52 @ 0x1D05C
    B_MAKE(0x09, 72, 1, 1, 1, 2, 3, 2, 16), // 53 @ 0x1D062
    B_MAKE(0x2E, 1, 1, 0, 1, 0, 0, 0, 18), // 54 @ 0x1D068
    B_MAKE(0x2F, 1, 1, 1, 1, 0, 6, 0, 0), // 55 @ 0x1D06E
    B_MAKE(0x30, 1, 1, 0, 1, 0, 0, 0, 0), // 56 @ 0x1D074
    B_MAKE(0x31, 1, 1, 1, 1, 0, 1, 0, 0), // 57 @ 0x1D07A
    B_MAKE(0x32, 1, 1, 0, 1, 0, 1, 0, 0), // 58 @ 0x1D080
    B_MAKE(0x33, 1, 1, 0, 1, 0, 1, 0, 0), // 59 @ 0x1D086
    B_MAKE(0x34, 1, 1, 1, 1, 0, 1, 0, 0), // 60 @ 0x1D08C
    B_MAKE(0x35, 1, 1, 1, 1, 0, 1, 0, 0), // 61 @ 0x1D092
    B_MAKE(0x36, 1, 1, 1, 1, 0, 0, 0, 0), // 62 @ 0x1D098
    B_MAKE(0x37, 1, 1, 1, 1, 0, 1, 0, 0), // 63 @ 0x1D09E
    B_MAKE(0x38, 1, 1, 1, 1, 0, 0, 0, 0), // 64 @ 0x1D0A4
    B_MAKE(0x39, 1, 1, 0, 1, 0, 0, 0, 0), // 65 @ 0x1D0AA
    B_MAKE(0x3A, 2, 1, 1, 1, 2, 0, 0, 0), // 66 @ 0x1D0B0
    B_MAKE(0x3B, 1, 1, 0, 1, 0, 1, 0, 20), // 67 @ 0x1D0B6
    B_MAKE(0x3C, 1, 1, 1, 1, 0, 0, 0, 0), // 68 @ 0x1D0BC
    B_MAKE(0x3D, 1, 1, 1, 1, 0, 3, 0, 0), // 69 @ 0x1D0C2
    B_MAKE(0x3E, 96, 1, 1, 1, 4, 0, 3, 0), // 70 @ 0x1D0C8
    B_MAKE(0x3F, 1, 1, 1, 1, 0, 0, 0, 0), // 71 @ 0x1D0CE
    B_MAKE(0x40, 1, 1, 1, 1, 0, 0, 0, 0), // 72 @ 0x1D0D4
    B_MAKE(0x41, 1, 1, 1, 1, 0, 1, 0, 0), // 73 @ 0x1D0DA
    B_MAKE(0x02, 1, 1, 1, 1, 0, 1, 0, 0), // 74 @ 0x1D0E0
    B_MAKE(0x02, 4, 1, 1, 1, 2, 0, 6, 0), // 75 @ 0x1D0E6
    B_MAKE(0x02, 6, 6, 1, 1, 0, 0, 0, 0), // 76 @ 0x1D0EC
    B_MAKE(0x42, 1, 1, 0, 1, 0, 3, 0, 0), // 77 @ 0x1D0F2
    B_MAKE(0x44, 1, 1, 1, 1, 0, 0, 0, 0), // 78 @ 0x1D0F8
    B_MAKE(0x45, 1, 1, 1, 1, 0, 7, 3, 0), // 79 @ 0x1D0FE
    B_MAKE(0x46, 1, 1, 1, 1, 0, 7, 3, 0), // 80 @ 0x1D104
    B_MAKE(0x47, 1, 1, 1, 1, 0, 7, 5, 0), // 81 @ 0x1D10A
    B_MAKE(0x48, 1, 1, 1, 1, 0, 7, 3, 0), // 82 @ 0x1D110
    B_MAKE(0x49, 1, 1, 1, 1, 0, 7, 3, 0), // 83 @ 0x1D116
    B_MAKE(0x4A, 1, 1, 1, 1, 0, 7, 3, 6), // 84 @ 0x1D11C
    B_MAKE(0x4B, 1, 1, 1, 1, 0, 7, 3, 6), // 85 @ 0x1D122
    B_MAKE(0x4C, 1, 1, 1, 1, 0, 7, 3, 6), // 86 @ 0x1D128
    B_MAKE(0x4D, 1, 1, 1, 1, 0, 2, 3, 6), // 87 @ 0x1D12E
    B_MAKE(0x16, 1, 1, 1, 1, 0, 7, 3, 0), // 88 @ 0x1D134
    B_MAKE(0x4E, 1, 1, 1, 1, 0, 7, 0, 0), // 89 @ 0x1D13A
    B_MAKE(0x4F, 1, 1, 1, 1, 0, 7, 0, 0), // 90 @ 0x1D140
    B_MAKE(0x50, 1, 1, 1, 1, 0, 7, 0, 0), // 91 @ 0x1D146
    B_MAKE(0x51, 1, 1, 1, 1, 0, 0, 0, 0), // 92 @ 0x1D14C
    B_MAKE(0x52, 1, 1, 1, 1, 0, 7, 0, 0), // 93 @ 0x1D152
    B_MAKE(0x53, 1, 1, 1, 1, 0, 7, 0, 0), // 94 @ 0x1D158
    B_MAKE(0x54, 1, 1, 1, 1, 0, 7, 0, 0), // 95 @ 0x1D15E
    B_MAKE(0x55, 1, 1, 1, 1, 0, 7, 0, 0), // 96 @ 0x1D164
    B_MAKE(0x56, 1, 1, 1, 1, 0, 0, 0, 0), // 97 @ 0x1D16A
    B_MAKE(0x57, 1, 1, 1, 1, 0, 1, 0, 0), // 98 @ 0x1D170
    B_MAKE(0x58, 1, 1, 0, 1, 0, 7, 3, 0), // 99 @ 0x1D176
    B_MAKE(0x59, 4, 1, 0, 1, 3, 0, 1, 1), // 100 @ 0x1D17C
    B_MAKE(0x5A, 1, 1, 1, 1, 0, 0, 1, 0), // 101 @ 0x1D182
    B_MAKE(0x5B, 1, 1, 0, 1, 1, 6, 2, 10), // 102 @ 0x1D188
    B_MAKE(0x5C, 3, 1, 1, 1, 5, 0, 2, 1), // 103 @ 0x1D18E
    B_MAKE(0x5C, 1, 1, 1, 1, 0, 0, 2, 1), // 104 @ 0x1D194
};

u16 g_MariaFactoryBlueprintPadding = 0;

typedef struct {
    s16 attack;
    u8 hitboxWidth;
    u8 hitboxHeight;
    s8 hitboxOffX;
    s8 hitboxOffY;
    u16 attackElement;
    u16 hitboxState;
    u8 nFramesInvincibility;
    u8 stunFrames;
    u16 hitEffect;
    u16 entityRoomIndex;
} MariaEntityCombatData;

typedef struct {
    u16 firstPose;
    u16 lastPose;
} MariaEntityPoseWindow;

u8 g_MariaEntitySlotRanges[8][2] = {
    {0x30, 0x3F}, {0x20, 0x2F}, {0x10, 0x1E}, {0x10, 0x3F},
    {0x1F, 0x1F}, {0x30, 0x30}, {0x10, 0x2F}, {0x12, 0x2F},
};

MariaEntityCombatData g_MariaEntityCombatData[] = {
    {30, 16, 5, 28, -3, 0x20, 2, 0x1A, 4, 1, 8},
    {30, 16, 6, 23, 23, 0x20, 2, 0x1A, 4, 1, 8},
    {30, 16, 5, 26, 6, 0x20, 2, 0x1A, 4, 1, 8},
    {30, 13, 5, 20, 20, 0x20, 2, 0x1A, 4, 1, 8},
};

MariaEntityPoseWindow g_MariaEntityPoseWindows[] = {
    {3, 8}, {3, 5}, {3, 7}, {2, 5},
};

MariaEntityCombatData g_MariaSpecialEntityCombatData = {
    30, 8, 8, 26, 26, 0x20, 2, 8, 4, 1, 8,
};
