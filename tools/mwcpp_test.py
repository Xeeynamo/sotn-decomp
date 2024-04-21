import os
import random
import shutil
import unittest

from mwcpp import process_file


class TestProcessFile(unittest.TestCase):
    @classmethod
    def setUp(self) -> None:
        self.seed = f"{random.randint(0, 100000)}"
        self.c_file_name = f"test_file_{self.seed}.c"
        self.asm_dir_name = f"asm/{self.seed}"
        self.output_name = f"test_processed_file_{self.seed}.c"
        os.makedirs(f"{self.asm_dir_name}/ovl")
        return super().setUp(self)

    @classmethod
    def tearDown(self) -> None:
        shutil.rmtree(self.asm_dir_name)
        os.remove(self.c_file_name)
        os.remove(self.output_name)
        return super().tearDown(self)

    def helper_process_lines(self, assembly):
        with open(self.c_file_name, "w") as f:
            f.write(f'INCLUDE_ASM("ovl", func_name)')
        with open(f"{self.asm_dir_name}/ovl/func_name.s", "w") as f:
            f.write(assembly)
        with open(self.output_name, "w") as f:
            process_file(self.c_file_name, f, self.seed)
        with open(self.output_name, "r") as f:
            return "".join(f.readlines())

    def test_process_basic_include_asm(self):
        with open(self.c_file_name, "w") as f:
            f.writelines(
                [
                    "ignore this line\n",
                    "// this too\n" f'INCLUDE_ASM("ovl", func_name)\n',
                    f'// INCLUDE_ASM("ovl", func_name)\n',
                    "",
                ]
            )
        with open(f"{self.asm_dir_name}/ovl/func_name.s", "w") as f:
            f.write("glabel function_name_should_be_skipped\n")
            f.write("/* 0 */ nop\n")
            f.write(".size this_part_should_be_skipped\n")
        with open(self.output_name, "w") as f:
            process_file(self.c_file_name, f, self.seed)
        with open(self.output_name, "r") as f:
            lines = "".join(f.readlines())

        self.assertEqual(
            lines,
            """ignore this line
// this too
asm void func_name() {
/* 0 */ nop
}
// INCLUDE_ASM("ovl", func_name)
""",
        )

    def test_fix_jalr(self):
        self.assertEqual(
            self.helper_process_lines(
                """jalr $v0
"""
            ),
            """asm void func_name() {
jalr $ra, $v0
}
""",
        )

    def test_fix_jlabel(self):
        self.assertEqual(
            self.helper_process_lines(
                """jlabel .LHELLO
"""
            ),
            """asm void func_name() {
LHELLO:
}
""",
        )

    def test_fix_lui_addiu_combo(self):
        self.assertEqual(
            self.helper_process_lines(
                """lui        $a0, %hi(D_8D1DC40)
/* some stuff */   addiu      $a0, $a0, %lo(D_8D1DC40)
"""
            ),
            """asm void func_name() {
la $a0, D_8D1DC40
}
""",
        )

    def test_fix_lui_lh_combo(self):
        self.assertEqual(
            self.helper_process_lines(
                """lui        $v1, %hi(D_92EFFDE)
/* some stuff */   lh         $a0, -0x2948($v1)
"""
            ),
            """asm void func_name() {
lui        $v1, (D_92EFFDE)@ha
/* some stuff */   lh         $a0, -0x2948($v1)
}
""",
        )

    def test_fix_lower_16bit(self):
        self.assertEqual(
            self.helper_process_lines(
                """lw $s1, %lo(g_EventQueue)($v1)
"""
            ),
            """asm void func_name() {
lw $s1, (g_EventQueue@l)($v1)
}
""",
        )

    def test_fix_dot_on_label_names(self):
        self.assertEqual(
            self.helper_process_lines(
                """jmp .LABEL
.LABEL:
"""
            ),
            """asm void func_name() {
jmp LABEL
LABEL:
}
""",
        )

    def test_remove_trailing_hash_comment(self):
        self.assertEqual(
            self.helper_process_lines(
                """nop# comment
"""
            ),
            """asm void func_name() {
nop
}
""",
        )


if __name__ == "__main__":
    unittest.main()
