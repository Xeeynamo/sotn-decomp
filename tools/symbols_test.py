#!/usr/bin/env python3

import os
import sys
import unittest
import tempfile
from pathlib import Path

sys.path.append(os.getcwd())
from tools.symbols import asm_tokenize_line, get_non_matching_symbols, sort


class TestSortSymbols(unittest.TestCase):
    def test_sort_symbol_list_based_on_their_offset(self):
        symbols = [
            "sym2 = 0x80185678; // some comment",
            "sym3 = 0x80189ABC;",
            "sym1 = 0x80181234;",
        ]
        with tempfile.NamedTemporaryFile(
            mode="w+", suffix=".txt", delete_on_close=False
        ) as tmp:
            tmp.write("\n".join(symbols) + "\n")
            tmp.seek(0)
            sort(tmp.name)
            sorted = tmp.read().rstrip("\n").splitlines()

        self.assertEqual(
            sorted,
            [
                "sym1 = 0x80181234;",
                "sym2 = 0x80185678; // some comment",
                "sym3 = 0x80189ABC;",
            ],
        )

    def test_remove_duplicates_with_same_name_and_offset(self):
        symbols = [
            "func_stuff = 0x80181234;",
            "func_stuff = 0x80181234;",
            "out_of_order = 0x0;",
        ]
        with tempfile.NamedTemporaryFile(
            mode="w+", suffix=".txt", delete_on_close=False
        ) as tmp:
            tmp.write("\n".join(symbols) + "\n")
            tmp.seek(0)
            sort(tmp.name)
            sorted = tmp.read().rstrip("\n").splitlines()

        self.assertEqual(
            sorted, ["out_of_order = 0x00000000;", "func_stuff = 0x80181234;"]
        )


class TestTokenizeAssembly(unittest.TestCase):
    def test_tokenize_instruction_with_no_parameters(self):
        asm = "/* 0 1 2 */  nop"
        tokens = asm_tokenize_line(asm)
        self.assertEqual(
            tokens,
            {
                "LOC": "0",
                "VRAM": "1",
                "VAL": "2",
                "OP": "nop",
            },
        )

    def test_tokenize_instruction_with_left(self):
        asm = "/* 72DEC 80112DEC 28348424 */  addiu      $a0, $a1"
        tokens = asm_tokenize_line(asm)
        self.assertEqual(
            tokens,
            {
                "LOC": "72DEC",
                "VRAM": "80112DEC",
                "VAL": "28348424",
                "OP": "addiu",
                "DST": "$a0",
                "LEFT": "$a1",
            },
        )

    def test_tokenize_instruction_with_symbol(self):
        asm = "/* 72BF4 80112BF4 0780023C */  lui        $v0, %hi(g_MyStruct_field)"
        tokens = asm_tokenize_line(asm)
        self.assertEqual(
            tokens,
            {
                "LOC": "72BF4",
                "VRAM": "80112BF4",
                "VAL": "0780023C",
                "OP": "lui",
                "DST": "$v0",
                "FUNC": "%hi",
                "SYM": "g_MyStruct_field",
            },
        )

    def test_tokenize_instruction_with_symbol_offset(self):
        asm = "/* 72BB0 80112BB0 D0FFBD27 */  lhu $v0, %lo(g_MyStruct_field)($v0)"
        tokens = asm_tokenize_line(asm)
        self.assertEqual(
            tokens,
            {
                "LOC": "72BB0",
                "VRAM": "80112BB0",
                "VAL": "D0FFBD27",
                "OP": "lhu",
                "DST": "$v0",
                "FUNC": "%lo",
                "SYM": "g_MyStruct_field",
                "IMM": "$v0",
            },
        )

    def test_tokenize_instruction_with_left_reg_and_right_sym(self):
        asm = "/* 72DEC 80112DEC 28348424 */  addiu      $a0, $a1, %lo(PLAYER_animFrameIdx)"
        tokens = asm_tokenize_line(asm)
        self.assertEqual(
            tokens,
            {
                "LOC": "72DEC",
                "VRAM": "80112DEC",
                "VAL": "28348424",
                "OP": "addiu",
                "DST": "$a0",
                "LEFT": "$a1",
                "FUNC": "%lo",
                "SYM": "PLAYER_animFrameIdx",
            },
        )

    def test_tokenize_instruction_with_left_reg_and_right_sym_with_imm(self):
        asm = "/* 72DEC 80112DEC 28348424 */  addiu      $a0, $a1, %lo(PLAYER_animFrameIdx)($at)"
        tokens = asm_tokenize_line(asm)
        self.assertEqual(
            tokens,
            {
                "LOC": "72DEC",
                "VRAM": "80112DEC",
                "VAL": "28348424",
                "OP": "addiu",
                "DST": "$a0",
                "LEFT": "$a1",
                "FUNC": "%lo",
                "SYM": "PLAYER_animFrameIdx",
                "IMM": "$at",
            },
        )

    def test_tokenize_instruction_with_left_and_right_syms(self):
        asm = "/* 72DEC 80112DEC 28348424 */  addiu      $a0, $a1, $a2"
        tokens = asm_tokenize_line(asm)
        self.assertEqual(
            tokens,
            {
                "LOC": "72DEC",
                "VRAM": "80112DEC",
                "VAL": "28348424",
                "OP": "addiu",
                "DST": "$a0",
                "LEFT": "$a1",
                "RIGHT": "$a2",
            },
        )

    def test_tokenize_instruction_with_label(self):
        asm = "/* 72DEC 80112DEC 28348424 */  jmp      .MY_LABEL"
        tokens = asm_tokenize_line(asm)
        self.assertEqual(
            tokens,
            {
                "LOC": "72DEC",
                "VRAM": "80112DEC",
                "VAL": "28348424",
                "OP": "jmp",
                "LABEL": "MY_LABEL",
            },
        )

    def test_tokenize_instruction_with_dst_and_label(self):
        asm = "/* 72DEC 80112DEC 28348424 */  bne      $v0, .MY_LABEL"
        tokens = asm_tokenize_line(asm)
        self.assertEqual(
            tokens,
            {
                "LOC": "72DEC",
                "VRAM": "80112DEC",
                "VAL": "28348424",
                "OP": "bne",
                "DST": "$v0",
                "LABEL": "MY_LABEL",
            },
        )


class TestCrossReferenceSymbols(unittest.TestCase):
    def test_get_non_matching_symbols_for_the_same_function(self):
        asm_sample_reference = [
            ".some asm_directive /* with some comments */",
            "",
            "glabel func_my_func_name_reference",
            "/* 72BB0 80112BB0 D0FFBD27 */  addiu      $sp, $sp, -0x30",
            "/* 72BBC 80112BBC 58000234 */  ori        $v0, $zero, 0xAAA",
            "/* 72BF4 80112BF4 0780023C */  lui        $v0, %hi(g_MyStruct_field)",
            "/* 72BF8 80112BF8 642F4294 */  lhu        $v0, %lo(g_MyStruct_field)($v0)",
            "/* 72C04 80112C04 09004014 */  bnez       $v0, .L80112C2C",
            "/* 72DC8 80112DC8 1480023C */  lui        $v0, %hi(D_80139824)",
            "/* 72BA0 80112BA0 21082200 */  addu       $at, $at, $v0",
            "/* 72DCC 80112DCC 2498428C */  lhu        $v0, %lo(D_80139824)($v0)",
            ".L80112DE8:",
            "/* 72DE8 80112DE8 0780043C */  lui        $a0, %hi(PLAYER_animFrameIdx)",
            "/* 72DEC 80112DEC 28348424 */  addiu      $a0, $a0, %lo(PLAYER_animFrameIdx)",
            "/* 73140 80113140 0800E003 */  jr         $ra",
            "/* 73144 80113144 00000000 */   nop",
        ]
        asm_sample_to_cross = [
            ".some asm_directive /* with some comments */",
            "",
            "glabel func_my_func_name_cross",
            "/* 72BB0 80112BB0 D0FFBD27 */  addiu      $sp, $sp, -0x30",
            "/* 72BBC 80112BBC 58000234 */  ori        $v0, $zero, 0xBBB",
            "/* 728E4 801128E4 0780023C */  lui        $v0, %hi(D_80012354)",
            "/* 728E8 801128E8 642F4294 */  lhu        $v0, %lo(D_80012354)($v0)",
            "/* 72D1C 80112D1C 04004014 */  bnez       $v0, .L80112D30",
            "/* 72B9C 80112B9C 0B80013C */  lui        $at, %hi(D_800AD040)",
            "/* 72BA0 80112BA0 21082200 */  addu       $at, $at, $v0",
            "/* 72BA4 80112BA4 40D02394 */  lhu        $zero, %lo(D_800AD040)($at)",
            ".L80112AD8:",
            "/* 72AD8 80112AD8 0780043C */  lui        $a0, %hi(PLAYER_animFrameIdx)",
            "/* 72ADC 80112ADC 28348424 */  addiu      $a0, $a0, %lo(PLAYER_animFrameIdx)",
            "/* 73140 80113140 0800E003 */  jr         $ra",
            "/* 73144 80113144 00000000 */   nop",
        ]
        status, symbols = get_non_matching_symbols(
            asm_sample_reference, asm_sample_to_cross
        )
        self.assertEqual(status, "ok")
        self.assertEqual(
            symbols,
            {"g_MyStruct_field": 0x80072F64, "D_80139824": 0x800AD040},
        )

    def test_fail_if_the_line_count_between_the_sources_is_different(self):
        status, _ = get_non_matching_symbols(["a", "b"], ["a", "b", "c"])
        self.assertEqual(status, "fail")

    def test_fail_if_the_sources_are_too_different_between_each_other(self):
        asm_sample_reference = [
            ".some asm_directive /* with some comments */",
            "",
            "glabel func_my_func_name",
            "/* 72BB0 80112BB0 D0FFBD27 */  addiu      $sp, $sp, -0x30",
            "/* 72BBC 80112BBC 58000234 */  addiu      $v0, $zero, 0xAAA",
            "/* 72BF4 80112BF4 0780023C */  lui        $v0, %hi(g_MyStruct_field)",
            "/* 72BF8 80112BF8 642F4294 */  lhu        $v0, %lo(g_MyStruct_field)($v0)",
            "/* 72C04 80112C04 09004014 */  bnez       $v0, .L80112C2C",
            "/* 73140 80113140 0800E003 */  jr         $ra",
            "/* 73144 80113144 00000000 */   nop",
        ]
        asm_sample_to_cross = [
            ".some asm_directive /* with some comments */",
            "",
            "glabel func_my_func_name",
            "/* 72BB0 80112BB0 D0FFBD27 */  addiu      $sp, $sp, -0x30",
            "/* 72BBC 80112BBC 58000234 */  addiu      $v0, $zero, 0xAAA",
            "/* 72C04 80112C04 09004014 */  bnez       $v0, .L80112C2C",
            "/* 72BF4 80112BF4 0780023C */  lui        $v0, %hi(g_MyStruct_field)",
            "/* 72BF8 80112BF8 642F4294 */  lhu        $v0, %lo(g_MyStruct_field)($v0)",
            "/* 73140 80113140 0800E003 */  jr         $ra",
            "/* 73144 80113144 00000000 */   nop",
        ]
        status, _ = get_non_matching_symbols(asm_sample_reference, asm_sample_to_cross)
        self.assertEqual(status, "fail")


if __name__ == "__main__":
    unittest.main()
