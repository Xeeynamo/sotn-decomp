// SPDX-License-Identifier: AGPL-3.0-or-later
#include "test_common.h"

unsigned g_failures;

void test_target_byte_order(void);
void test_f32_read_views(void);
void test_f32_write_views(void);
void test_f16_views(void);
void test_fixed_arithmetic(void);
void test_fix_frac(void);
void test_numeric_parts(void);

int main(void) {
    test_target_byte_order();
    test_f32_read_views();
    test_f32_write_views();
    test_f16_views();
    test_fixed_arithmetic();
    test_fix_frac();
    test_numeric_parts();

    if (g_failures != 0) {
        fprintf(stderr, "endian contracts: %u failure(s)\n", g_failures);
        return 1;
    }
    puts("endian contracts: all tests passed");
    return 0;
}
