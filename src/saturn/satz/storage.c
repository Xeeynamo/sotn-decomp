// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stdint.h>
#include <string.h>

#include "module.h"

extern const SotnFixedSymbol sotn_fixed_symbols[];
void sotn_satz_unimplemented(const char* name) __attribute__((noreturn));
void satz_die(const char* fmt, ...) __attribute__((noreturn));

static const SotnFixedSymbol* s_FixedTables[1 + SATZ_AREA_COUNT] = {
    sotn_fixed_symbols};

void satz_fixed_symbols_add(const SotnFixedSymbol* table) {
    int i;

    for (i = 1; i < 1 + SATZ_AREA_COUNT; i++) {
        if (!s_FixedTables[i]) {
            s_FixedTables[i] = table;
            return;
        }
    }
    satz_die("satz_fixed_symbols_add: no room");
}

void satz_fixed_symbols_remove(const SotnFixedSymbol* table) {
    int i;

    for (i = 1; i < 1 + SATZ_AREA_COUNT; i++) {
        if (s_FixedTables[i] == table) {
            s_FixedTables[i] = NULL;
        }
    }
}

const SotnFixedSymbol* satz_fixed_symbol_named(const char* name) {
    const SotnFixedSymbol* s;
    int i;

    for (i = 0; i < 1 + SATZ_AREA_COUNT; i++) {
        for (s = s_FixedTables[i]; s && s->name; s++) {
            if (!strcmp(s->name, name)) {
                return s;
            }
        }
    }
    return NULL;
}

const SotnFixedSymbol* satz_fixed_symbol_at(uint32_t address) {
    const SotnFixedSymbol* s;
    int i;

    for (i = 0; i < 1 + SATZ_AREA_COUNT; i++) {
        for (s = s_FixedTables[i]; s && s->name; s++) {
            if (address >= s->address &&
                address < s->address + s->retail_size) {
                return s;
            }
        }
    }
    return NULL;
}

void sotn_satz_clear_range(uint32_t start, uint32_t size) {
    const SotnFixedSymbol* s;
    int i;

    for (i = 0; i < 1 + SATZ_AREA_COUNT; i++) {
        for (s = s_FixedTables[i]; s && s->name; s++) {
            if (s->address >= start && s->address < start + size) {
                memset(s->data, 0, s->retail_size * 2);
            }
        }
    }
}

extern uint8_t g_WorkBuffer[0x8020];

uint32_t DAT_06002000[16 * 1024 / sizeof(uint32_t)];
uint8_t DAT_00200000[0x00211800 - 0x00200000];
uint8_t DAT_00211800[0x0022A000 - 0x00211800];
uint8_t DAT_0022A000[0x00232000 - 0x0022A000];

void* g_BatServantDesc[0x10];
void* DAT_060A5000;
void* DAT_060A5004;
void* DAT_060A5008;
void* func_060CF01C;
void* g_BatResourceDescriptorList;
void* DAT_060D6004;
void* DAT_060D6008;
void* DAT_060D600C;
void* DAT_060D6010;
void* DAT_060D6014;
void* DAT_060D6018;
void* DAT_060D601C;
void* DAT_060D6020;
void* DAT_060D6024;
void* DAT_060D6028;
void* DAT_060D602C;
void* DAT_060D6030;
void* DAT_060D6034;
void* DAT_060D6038;
void* DAT_060D603C;
void* DAT_060D6040;
void* DAT_060D6044;
void* DAT_060D6048;
void* DAT_060D9040;
uint8_t g_Weapon0OvlArea[0x3000] __attribute__((aligned(16)));
uint8_t g_Weapon1OvlArea[0x3000] __attribute__((aligned(16)));

uint8_t g_StageOvlArea[0x6000] __attribute__((aligned(16)));

uint8_t DAT_00252000[0x00300000 - 0x00252000] __attribute__((aligned(16)));

void* sotn_satz_retail_address(uint32_t address) {
    const SotnFixedSymbol* s;

    if (address >= 0x00252000 && address < 0x00300000) {
        return DAT_00252000 + (address - 0x00252000);
    }
    if (address >= 0x060485C0 && address < 0x060485C0 + sizeof(g_WorkBuffer)) {
        return g_WorkBuffer + (address - 0x060485C0);
    }
    s = satz_fixed_symbol_at(address);
    if (s) {
        return s->data + (address - s->address);
    }
    sotn_satz_unimplemented("sotn_satz_retail_address: no native object");
}

void* sotn_satz_be16_copy(const void* src, uint32_t bytes) {
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
    return out;
}
