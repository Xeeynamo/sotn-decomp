#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

#ifdef GHIDRA

#define INCLUDE_ASM(FOLDER, NAME, LABEL)
#define INCLUDE_ASM_NO_ALIGN(FOLDER, NAME, LABEL)

// uncomment to define all unknown funcs as void void
// #define INCLUDE_ASM(FOLDER, NAME, LABEL) \
    // void LABEL(void) {}
// #define INCLUDE_ASM_NO_ALIGN(FOLDER, NAME, LABEL) \
    // void LABEL(void) {}

#elif defined(PERMUTER)

#define INCLUDE_ASM(FOLDER, NAME, LABEL)
#define INCLUDE_ASM_NO_ALIGN(FOLDER, NAME, LABEL)

#else

#define INCLUDE_ASM(FOLDER, NAME, LABEL)                                       \
    __asm__(".text\n"                                                          \
            "\t.align\t2\n"                                                    \
            "\t.global\t _" #LABEL "\n"                                        \
            ".include \"" FOLDER "/" #NAME ".s\"\n");

// omit .global
__asm__(".include \"macro.inc\"\n");

#define INCLUDE_ASM_NO_ALIGN(FOLDER, NAME, LABEL)                              \
    __asm__(".text\n"                                                          \
            "\t.global\t _" #LABEL "\n"                                        \
            ".include \"" FOLDER "/" #NAME ".s\"\n");
__asm__(".include \"macro.inc\"\n");

#endif

#endif // INCLUDE_ASM_H