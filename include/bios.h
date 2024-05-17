#ifndef BIOS_H
#define BIOS_H

#include "common.h"

// Defines the syscall stub for various functions
#define BIOS_FUNCTION(name, section, id)                                       \
    __asm__(                                                                   \
        ".pushsection .text\n"                                                 \
        "\t.align\t2\n"                                                        \
        "\t.globl\t" #name "\n"                                                \
        "\t.ent\t" #name "\n"                                                  \
        "" #name " :\n"                                                        \
        ".set noat\n"                                                          \
        ".set noreorder\n"                                                     \
        "\n"                                                                   \
        "glabel " #name "\n"                                                   \
        "\taddiu  $t2, $zero, " #section "\n"                                  \
        "\tjr     $t2\n"                                                       \
        "\t addiu $t1, $zero, " #id "\n"                                       \
        "\tnop\n"                                                              \
        ".size " #name ", . - " #name "\n"                                     \
        "\t.set reorder\n"                                                     \
        "\t.set at\n"                                                          \
        "\t.end\t" #name "\n"                                                  \
        ".popsection");

#define BIOS_A_FUNCTION(name, id) BIOS_FUNCTION(name, 0xA0, id)

#define BIOS_B_FUNCTION(name, id) BIOS_FUNCTION(name, 0xB0, id)

#define BIOS_C_FUNCTION(name, id) BIOS_FUNCTION(name, 0xC0, id)

#define SYSCALL(name, number)                                                  \
    __asm__(                                                                   \
        ".pushsection .text\n"                                                 \
        "\t.align\t2\n"                                                        \
        "\t.globl\t" #name "\n"                                                \
        "\t.ent\t" #name "\n"                                                  \
        "" #name " :\n"                                                        \
        ".set noat\n"                                                          \
        ".set noreorder\n"                                                     \
        "\n"                                                                   \
        "glabel " #name "\n"                                                   \
        "\taddiu  $a0, $zero, " #number "\n"                                   \
        "\tsyscall 0\n"                                                        \
        "\tjr     $ra\n"                                                       \
        "\tnop\n"                                                              \
        ".size " #name ", . - " #name "\n"                                     \
        "\t.set reorder\n"                                                     \
        "\t.set at\n"                                                          \
        "\t.end\t" #name "\n"                                                  \
        ".popsection");

#endif // BIOS_H
