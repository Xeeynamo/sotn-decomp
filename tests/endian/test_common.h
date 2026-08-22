// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SOTN_ENDIAN_TEST_COMMON_H
#define SOTN_ENDIAN_TEST_COMMON_H

#include <common.h>
#include <endian_utils.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

extern unsigned g_failures;

static inline uint32_t f32_bits(f32 value) {
    uint32_t bits;
    memcpy(&bits, &value.val, sizeof(bits));
    return bits;
}

static inline uint16_t s16_bits(s16 value) {
    uint16_t bits;
    memcpy(&bits, &value, sizeof(bits));
    return bits;
}

#define CHECK_EQ_HEX(test_name, expected, actual)                              \
    do {                                                                       \
        uint64_t check_expected = (uint64_t)(expected);                        \
        uint64_t check_actual = (uint64_t)(actual);                            \
        if (check_expected != check_actual) {                                  \
            fprintf(stderr, "%s: expected 0x%" PRIX64                        \
                            ", got 0x%" PRIX64 "\n",                         \
                    test_name, check_expected, check_actual);                  \
            g_failures++;                                                      \
        }                                                                      \
    } while (0)

#define CHECK_EQ_S32(test_name, expected, actual)                              \
    do {                                                                       \
        int32_t check_expected = (int32_t)(expected);                          \
        int32_t check_actual = (int32_t)(actual);                              \
        if (check_expected != check_actual) {                                  \
            fprintf(stderr, "%s: expected %" PRId32 ", got %" PRId32        \
                            " (0x%08" PRIX32 ")\n",                          \
                    test_name, check_expected, check_actual,                   \
                    (uint32_t)check_actual);                                   \
            g_failures++;                                                      \
        }                                                                      \
    } while (0)

#endif
