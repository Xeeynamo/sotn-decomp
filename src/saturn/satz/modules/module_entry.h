// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATZ_MODULE_ENTRY_H
#define SATZ_MODULE_ENTRY_H

#include <string.h>
#include "../module.h"

extern const SotnFixedSymbol sotn_fixed_symbols[];

#define SATZ_MODULE_COPY(type, header)                                         \
    extern type header;                                                        \
    static void install(void* area) { memcpy(area, &header, sizeof(type)); }

#define SATZ_MODULE_ENTRY                                                      \
    SATZ_MODULE_EXPORT void satz_module_start(void* area) {                    \
        satz_fixed_symbols_add(sotn_fixed_symbols);                            \
        install(area);                                                         \
    }                                                                          \
    SATZ_MODULE_EXPORT void satz_module_stop(void) {                           \
        satz_fixed_symbols_remove(sotn_fixed_symbols);                         \
    }

#endif
