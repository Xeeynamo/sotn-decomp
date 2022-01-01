.include "main.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

.section .text, "ax"

syscalldef _card_info       0xA0 0xAB
syscalldef _card_load       0xA0 0xAC
syscalldef InitCARD         0xB0 0x4A
syscalldef StartCARD        0xB0 0x4B

glabel _card_clear
/* 724C 80016A4C E8FFBD27 */  addiu      $sp, $sp, -0x18
/* 7250 80016A50 1000B0AF */  sw         $s0, 0x10($sp)
/* 7254 80016A54 1400BFAF */  sw         $ra, 0x14($sp)
/* 7258 80016A58 A55A000C */  jal        _new_card
/* 725C 80016A5C 21808000 */   addu      $s0, $a0, $zero
/* 7260 80016A60 21200002 */  addu       $a0, $s0, $zero
/* 7264 80016A64 3F000534 */  ori        $a1, $zero, 0x3f
/* 7268 80016A68 A15A000C */  jal        _card_write
/* 726C 80016A6C 21300000 */   addu      $a2, $zero, $zero
/* 7270 80016A70 1400BF8F */  lw         $ra, 0x14($sp)
/* 7274 80016A74 1000B08F */  lw         $s0, 0x10($sp)
/* 7278 80016A78 1800BD27 */  addiu      $sp, $sp, 0x18
/* 727C 80016A7C 0800E003 */  jr         $ra
/* 7280 80016A80 00000000 */   nop

syscalldef _card_write      0xB0 0x4E
syscalldef _new_card        0xB0 0x50
