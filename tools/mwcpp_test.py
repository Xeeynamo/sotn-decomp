import os
import random
import shutil
import unittest

from mwcpp import process_file


class TestProcessFile(unittest.TestCase):
    @classmethod
    def setUp(self) -> None:
        self.seed = f"{random.randint(0, 100000)}"
        self.seed = 81666
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

    def test_process_include_asm(self):
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
            f.write("/* 0 */ jmp .LABEL\n")
            f.write(".LABEL:\n")
            f.write("/* 4 */ lui $a0, %hi(my_symbol)\n")
            f.write("/* 8 */ addiu $a0, %lo(my_symbol)\n")
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
/* 0 */ jmp LABEL
LABEL:
/* 4 */ lui $a0, my_symbol@ha
/* 8 */ addiu $a0, my_symbol@l
}
// INCLUDE_ASM("ovl", func_name)
""",
        )


if __name__ == "__main__":
    unittest.main()
