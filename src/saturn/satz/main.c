// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../zero.h"

void entrypoint(void);

extern char end[];

void satz_saturn_main(void) {
    if ((unsigned long)end >= 0x80000000ul) {
        satz_die("the program image ends above 2 GB (%p)", (void*)end);
    }
    entrypoint();
}

void sotn_satz_unimplemented(const char* name) {
    satz_die("unimplemented: %s (still assembly)", name);
}
