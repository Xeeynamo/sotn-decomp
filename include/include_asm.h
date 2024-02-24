#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

#define ASM_RODATA __asm__(".section .rodata")

#ifndef PERMUTER

#ifndef INCLUDE_ASM

#ifndef INCLUDE_ASM_OLD
#define INCLUDE_ASM(FOLDER, NAME)                                              \
    __asm__(".pushsection .text\n"                                             \
            "\t.align\t2\n"                                                    \
            "\t.globl\t" #NAME "\n"                                            \
            "\t.ent\t" #NAME "\n" #NAME ":\n"                                  \
            ".include \"asm/" VERSION "/" FOLDER "/" #NAME ".s\"\n"            \
            "\t.set reorder\n"                                                 \
            "\t.set at\n"                                                      \
            "\t.end\t" #NAME "\n"                                              \
            ".popsection");
#else
#define INCLUDE_ASM(FOLDER, NAME)                                              \
    __asm__(".pushsection .text\n"                                             \
            "\t.align\t2\n"                                                    \
            "\t.globl\t" #NAME "\n"                                            \
            "\t.ent\t" #NAME "\n" #NAME ":\n"                                  \
            ".include \"" FOLDER "/" #NAME ".s\"\n"                            \
            "\t.set reorder\n"                                                 \
            "\t.set at\n"                                                      \
            "\t.end\t" #NAME "\n"                                              \
            ".popsection");
#endif

#endif

// omit .global
#ifdef USE_INCLUDE_ASM
__asm__(".include \"macro.inc\"\n");
#endif

#else
#define INCLUDE_ASM(FOLDER, NAME)
#endif

#endif
