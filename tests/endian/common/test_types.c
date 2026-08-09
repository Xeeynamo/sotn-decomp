// SPDX-License-Identifier: AGPL-3.0-or-later
#include "test_common.h"

_Static_assert(sizeof(s8) == 1, "s8 must be 8 bits");
_Static_assert(sizeof(u8) == 1, "u8 must be 8 bits");
_Static_assert(sizeof(s16) == 2, "s16 must be 16 bits");
_Static_assert(sizeof(u16) == 2, "u16 must be 16 bits");
_Static_assert(sizeof(s32) == 4, "s32 must be 32 bits");
_Static_assert(sizeof(u32) == 4, "u32 must be 32 bits");
_Static_assert(sizeof(f16) == 2, "f16 must be 2 bytes");
_Static_assert(sizeof(f32) == 4, "f32 must be 4 bytes");

void test_target_byte_order(void) {
    const uint32_t value = UINT32_C(0x01020304);
    uint8_t bytes[sizeof(value)];

    memcpy(bytes, &value, sizeof(bytes));
#if SOTN_BIG_ENDIAN
    CHECK_EQ_HEX("target.byte_order.big", 0x01, bytes[0]);
#else
    CHECK_EQ_HEX("target.byte_order.little", 0x04, bytes[0]);
#endif
}

void test_f32_read_views(void) {
    static const struct {
        uint32_t val;
        int16_t hi;
        uint16_t lo;
    } cases[] = {
        {UINT32_C(0x12345678), INT16_C(0x1234), UINT16_C(0x5678)},
        {UINT32_C(0xFFFF8000), INT16_C(-1), UINT16_C(0x8000)},
        {UINT32_C(0x80000001), INT16_MIN, UINT16_C(0x0001)},
        {UINT32_C(0x007B4567), INT16_C(123), UINT16_C(0x4567)},
        {UINT32_C(0xFFFE4000), INT16_C(-2), UINT16_C(0x4000)},
    };
    size_t i;

    for (i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        f32 value;
        memcpy(&value.val, &cases[i].val, sizeof(value.val));
        CHECK_EQ_S32("f32.read.hi", cases[i].hi, value.i.hi);
        CHECK_EQ_HEX("f32.read.lo", cases[i].lo, s16_bits(value.i.lo));
    }
}

void test_f32_write_views(void) {
    f32 value;

    value.val = (s32)UINT32_C(0x12345678);
    value.i.hi = (s16)UINT16_C(0x9ABC);
    CHECK_EQ_HEX("f32.write.hi.value", UINT32_C(0x9ABC5678),
                 f32_bits(value));
    CHECK_EQ_HEX("f32.write.hi.preserve_lo", UINT16_C(0x5678),
                 s16_bits(value.i.lo));

    value.i.lo = (s16)UINT16_C(0xDEF0);
    CHECK_EQ_HEX("f32.write.lo.value", UINT32_C(0x9ABCDEF0),
                 f32_bits(value));
    CHECK_EQ_HEX("f32.write.lo.preserve_hi", UINT16_C(0x9ABC),
                 s16_bits(value.i.hi));

    value.i.lo = 0;
    CHECK_EQ_HEX("f32.clear.fraction", UINT32_C(0x9ABC0000),
                 f32_bits(value));
}

void test_f16_views(void) {
    static const uint16_t cases[] = {0x1234, 0x80FF, 0xFFFF};
    size_t i;

    for (i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        f16 value;
        memcpy(&value.val, &cases[i], sizeof(value.val));
        CHECK_EQ_HEX("f16.read.hi", cases[i] >> 8, value.i.hi);
        CHECK_EQ_HEX("f16.read.lo", cases[i] & 0xFF, value.i.lo);
    }

    {
        f16 value;
        value.val = (s16)UINT16_C(0x1234);
        value.i.hi = 0xAB;
        CHECK_EQ_HEX("f16.write.hi", UINT16_C(0xAB34),
                     s16_bits(value.val));
        value.i.lo = 0xCD;
        CHECK_EQ_HEX("f16.write.lo", UINT16_C(0xABCD),
                     s16_bits(value.val));
    }
}

void test_fixed_arithmetic(void) {
    f32 value;

    value.val = FIX(10.75);
    value.val += FIX(0.5);
    CHECK_EQ_HEX("fixed.positive_carry.val", UINT32_C(0x000B4000),
                 f32_bits(value));
    CHECK_EQ_S32("fixed.positive_carry.hi", 11, value.i.hi);

    value.val = FIX(-1.25);
    value.val += FIX(-0.875);
    CHECK_EQ_HEX("fixed.negative_borrow.val", UINT32_C(0xFFFDE000),
                 f32_bits(value));
    CHECK_EQ_S32("fixed.negative_borrow.hi", -3, value.i.hi);

    value.val = FIX(-0.25);
    value.val += FIX(0.5);
    CHECK_EQ_HEX("fixed.zero_crossing.val", UINT32_C(0x00004000),
                 f32_bits(value));
    CHECK_EQ_S32("fixed.zero_crossing.hi", 0, value.i.hi);
}

void test_fix_frac(void) {
    s32 positive = (s32)UINT32_C(0x007B4567);
    s32 negative = (s32)UINT32_C(0xFFFEA000);

    CHECK_EQ_HEX("fix_frac.positive", UINT16_C(0x4567),
                 s16_bits(FIX_FRAC(positive)));
    CHECK_EQ_HEX("fix_frac.negative", UINT16_C(0xA000),
                 s16_bits(FIX_FRAC(negative)));
    FIX_FRAC(positive) = (s16)UINT16_C(0xBEEF);
    CHECK_EQ_HEX("fix_frac.write", UINT32_C(0x007BBEEF), (u32)positive);
}
