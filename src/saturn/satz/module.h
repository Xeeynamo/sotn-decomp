// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATZ_MODULE_H
#define SATZ_MODULE_H

#include <stdint.h>

typedef enum {
    SATZ_AREA_PLAYER,
    SATZ_AREA_STAGE,
    SATZ_AREA_WEAPON0,
    SATZ_AREA_WEAPON1,
    SATZ_AREA_COUNT,
} SatzArea;

typedef struct {
    const char* name;
    uint32_t address;
    uint8_t* data;
    uint32_t retail_size;
} SotnFixedSymbol;

void satz_module_open(SatzArea area, const char* name, void* dst);
void satz_module_close(SatzArea area);
const char* satz_module_name(SatzArea area);
void* satz_module_symbol(const char* symbol);

void satz_fixed_symbols_add(const SotnFixedSymbol* table);
void satz_fixed_symbols_remove(const SotnFixedSymbol* table);
const SotnFixedSymbol* satz_fixed_symbol_named(const char* name);
const SotnFixedSymbol* satz_fixed_symbol_at(uint32_t address);

#define SATZ_MODULE_EXPORT __attribute__((visibility("default")))

#endif
