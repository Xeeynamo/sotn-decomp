// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

#define IMA_ADPCM_ROW(step)                                                    \
    {(step) >> 3,                                                              \
     ((step) >> 3) + ((step) >> 2),                                            \
     ((step) >> 3) + ((step) >> 1),                                            \
     ((step) >> 3) + ((step) >> 1) + ((step) >> 2),                            \
     ((step) >> 3) + (step),                                                   \
     ((step) >> 3) + (step) + ((step) >> 2),                                   \
     ((step) >> 3) + (step) + ((step) >> 1),                                   \
     ((step) >> 3) + (step) + ((step) >> 1) + ((step) >> 2),                   \
     -((step) >> 3),                                                           \
     -(((step) >> 3) + ((step) >> 2)),                                         \
     -(((step) >> 3) + ((step) >> 1)),                                         \
     -(((step) >> 3) + ((step) >> 1) + ((step) >> 2)),                         \
     -(((step) >> 3) + (step)),                                                \
     -(((step) >> 3) + (step) + ((step) >> 2)),                                \
     -(((step) >> 3) + (step) + ((step) >> 1)),                                \
     -(((step) >> 3) + (step) + ((step) >> 1) + ((step) >> 2))}

s32 g_AdpcmDeltaTable[89][16] = {
    IMA_ADPCM_ROW(7),     IMA_ADPCM_ROW(8),     IMA_ADPCM_ROW(9),
    IMA_ADPCM_ROW(10),    IMA_ADPCM_ROW(11),    IMA_ADPCM_ROW(12),
    IMA_ADPCM_ROW(13),    IMA_ADPCM_ROW(14),    IMA_ADPCM_ROW(16),
    IMA_ADPCM_ROW(17),    IMA_ADPCM_ROW(19),    IMA_ADPCM_ROW(21),
    IMA_ADPCM_ROW(23),    IMA_ADPCM_ROW(25),    IMA_ADPCM_ROW(28),
    IMA_ADPCM_ROW(31),    IMA_ADPCM_ROW(34),    IMA_ADPCM_ROW(37),
    IMA_ADPCM_ROW(41),    IMA_ADPCM_ROW(45),    IMA_ADPCM_ROW(50),
    IMA_ADPCM_ROW(55),    IMA_ADPCM_ROW(60),    IMA_ADPCM_ROW(66),
    IMA_ADPCM_ROW(73),    IMA_ADPCM_ROW(80),    IMA_ADPCM_ROW(88),
    IMA_ADPCM_ROW(97),    IMA_ADPCM_ROW(107),   IMA_ADPCM_ROW(118),
    IMA_ADPCM_ROW(130),   IMA_ADPCM_ROW(143),   IMA_ADPCM_ROW(157),
    IMA_ADPCM_ROW(173),   IMA_ADPCM_ROW(190),   IMA_ADPCM_ROW(209),
    IMA_ADPCM_ROW(230),   IMA_ADPCM_ROW(253),   IMA_ADPCM_ROW(279),
    IMA_ADPCM_ROW(307),   IMA_ADPCM_ROW(337),   IMA_ADPCM_ROW(371),
    IMA_ADPCM_ROW(408),   IMA_ADPCM_ROW(449),   IMA_ADPCM_ROW(494),
    IMA_ADPCM_ROW(544),   IMA_ADPCM_ROW(598),   IMA_ADPCM_ROW(658),
    IMA_ADPCM_ROW(724),   IMA_ADPCM_ROW(796),   IMA_ADPCM_ROW(876),
    IMA_ADPCM_ROW(963),   IMA_ADPCM_ROW(1060),  IMA_ADPCM_ROW(1166),
    IMA_ADPCM_ROW(1282),  IMA_ADPCM_ROW(1411),  IMA_ADPCM_ROW(1552),
    IMA_ADPCM_ROW(1707),  IMA_ADPCM_ROW(1878),  IMA_ADPCM_ROW(2066),
    IMA_ADPCM_ROW(2272),  IMA_ADPCM_ROW(2499),  IMA_ADPCM_ROW(2749),
    IMA_ADPCM_ROW(3024),  IMA_ADPCM_ROW(3327),  IMA_ADPCM_ROW(3660),
    IMA_ADPCM_ROW(4026),  IMA_ADPCM_ROW(4428),  IMA_ADPCM_ROW(4871),
    IMA_ADPCM_ROW(5358),  IMA_ADPCM_ROW(5894),  IMA_ADPCM_ROW(6484),
    IMA_ADPCM_ROW(7132),  IMA_ADPCM_ROW(7845),  IMA_ADPCM_ROW(8630),
    IMA_ADPCM_ROW(9493),  IMA_ADPCM_ROW(10442), IMA_ADPCM_ROW(11487),
    IMA_ADPCM_ROW(12635), IMA_ADPCM_ROW(13899), IMA_ADPCM_ROW(15289),
    IMA_ADPCM_ROW(16818), IMA_ADPCM_ROW(18500), IMA_ADPCM_ROW(20350),
    IMA_ADPCM_ROW(22385), IMA_ADPCM_ROW(24623), IMA_ADPCM_ROW(27086),
    IMA_ADPCM_ROW(29794), IMA_ADPCM_ROW(32767),
};

s32 g_AdpcmIndexAdjust[16] = {
    -1, -1, -1, -1, 2, 4, 6, 8, -1, -1, -1, -1, 2, 4, 6, 8,
};
