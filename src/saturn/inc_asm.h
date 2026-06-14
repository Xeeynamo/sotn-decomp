// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

#if defined(SKIP_ASM) || defined(PERMUTER)
#define INCLUDE_ASM(FOLDER, NAME, LABEL)
#define INCLUDE_ASM_NO_ALIGN(FOLDER, NAME, LABEL)
#endif

#ifndef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME, LABEL)                                       \
    __asm__(".text\n"                                                          \
            "\t.align\t2\n"                                                    \
            "\t.global\t _" #LABEL "\n"                                        \
            ".include \"" FOLDER "/" #NAME ".s\"\n");
#define INCLUDE_ASM_NO_ALIGN(FOLDER, NAME, LABEL)                              \
    __asm__(".text\n"                                                          \
            "\t.global\t _" #LABEL "\n"                                        \
            ".include \"" FOLDER "/" #NAME ".s\"\n");
__asm__(".include \"src/saturn/macro.inc\"\n");
#endif

#endif // INCLUDE_ASM_H
