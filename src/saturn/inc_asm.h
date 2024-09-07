// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

#ifndef PERMUTER

#ifndef INCLUDE_ASM

#define INCLUDE_ASM(FOLDER, NAME, LABEL)                                       \
    __asm__(".text\n"                                                          \
            "\t.align\t2\n"                                                    \
            "\t.global\t _" #LABEL "\n"                                        \
            ".include \"" FOLDER "/" #NAME ".s\"\n");
#endif

// omit .global
__asm__(".include \"macro.inc\"\n");

#else
#define INCLUDE_ASM(FOLDER, NAME)
#endif

#define INCLUDE_ASM_NO_ALIGN(FOLDER, NAME, LABEL)                              \
    __asm__(".text\n"                                                          \
            "\t.global\t _" #LABEL "\n"                                        \
            ".include \"" FOLDER "/" #NAME ".s\"\n");
__asm__(".include \"macro.inc\"\n");

#endif
