// SPDX-License-Identifier: AGPL-3.0-or-later
#include "test_common.h"

void test_numeric_parts(void) {
    const u32 value = UINT32_C(0x12345678);
    const s32 negative = (s32)UINT32_C(0xFFFEA000);

    CHECK_EQ_HEX("numeric.low_u8", 0x78, SotnNumericLowU8(value));
    CHECK_EQ_HEX("numeric.low_u16", 0x5678, SotnNumericLowU16(value));
    CHECK_EQ_S32("numeric.low_s16", 0x5678,
                 SotnNumericLowS16((s32)value));
    CHECK_EQ_HEX("numeric.high_u16", 0x1234, SotnNumericHighU16(value));
    CHECK_EQ_S32("numeric.high_s16", 0x1234,
                 SotnNumericHighS16((s32)value));
    CHECK_EQ_S32("numeric.high_s16.negative", -2,
                 SotnNumericHighS16(negative));
    CHECK_EQ_S32("numeric.low_s16.negative", (s16)UINT16_C(0xA000),
                 SotnNumericLowS16(negative));
    CHECK_EQ_S32("fixed.integer.negative", -2,
                 SotnFixedInteger(negative));
    CHECK_EQ_S32("fixed_to_i.negative", -2, FIX_TO_I(negative));
    CHECK_EQ_HEX("i_to_fix.negative", UINT32_C(0xFFFC0000),
                 (u32)I_TO_FIX(-4));
}
