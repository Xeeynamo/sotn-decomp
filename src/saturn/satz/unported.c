// SPDX-License-Identifier: AGPL-3.0-or-later
void sotn_satz_unimplemented(const char* name) __attribute__((noreturn));

#define UNPORTED(name)                                                         \
    void name(void) { sotn_satz_unimplemented(#name); }
