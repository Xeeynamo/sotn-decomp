// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stdint.h>
#include <string.h>

typedef struct {
    const char* name;
    uint32_t address;
    uint8_t* data;
    uint32_t retail_size;
} SotnFixedSymbol;
extern const SotnFixedSymbol sotn_fixed_symbols[];
void sotn_satz_unimplemented(const char* name) __attribute__((noreturn));

void sotn_satz_clear_range(uint32_t start, uint32_t size) {
    const SotnFixedSymbol* s;

    for (s = sotn_fixed_symbols; s->name; s++) {
        if (s->address >= start && s->address < start + size) {
            memset(s->data, 0, s->retail_size * 2);
        }
    }
}

uint8_t g_FileLoadBuffer[0x10000] __attribute__((aligned(16)));

uint8_t g_StageOvlArea[0x6000] __attribute__((aligned(16)));

uint8_t DAT_00252000[0x00300000 - 0x00252000] __attribute__((aligned(16)));

void* sotn_satz_retail_address(uint32_t address) {
    const SotnFixedSymbol* s;

    if (address >= 0x00252000 && address < 0x00300000) {
        return DAT_00252000 + (address - 0x00252000);
    }
    if (address >= 0x060485E0 &&
        address < 0x060485E0 + sizeof(g_FileLoadBuffer)) {
        return g_FileLoadBuffer + (address - 0x060485E0);
    }
    for (s = sotn_fixed_symbols; s->name; s++) {
        if (address >= s->address && address < s->address + s->retail_size) {
            return s->data + (address - s->address);
        }
    }
    sotn_satz_unimplemented("sotn_satz_retail_address: no native object");
}

uint32_t sotn_satz_be16_copy(const void* src, uint32_t bytes) {
    static uint16_t ring[0x2000];
    static uint32_t next;
    const uint16_t* in = src;
    uint16_t* out;
    uint32_t i, words = (bytes + 1) / 2;

    if (next + words > sizeof(ring) / 2) {
        next = 0;
    }
    out = &ring[next];
    next += words;
    for (i = 0; i < words; i++) {
        out[i] = (uint16_t)((in[i] >> 8) | (in[i] << 8));
    }
    return (uint32_t)(uintptr_t)out;
}
