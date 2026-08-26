// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_ZERO_FONTMAP_H
#define SATURN_ZERO_FONTMAP_H

#include "sattypes.h"

typedef struct {
    u16 shiftJis;
    u16 characterOffset;
} SaturnFontGlyphMapping;

extern SaturnFontGlyphMapping g_SaturnFontGlyphMappings[92];

#endif
