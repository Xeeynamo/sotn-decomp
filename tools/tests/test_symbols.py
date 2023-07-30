#!/usr/bin/env python3

import io
import os
import sys
import unittest

sys.path.append(os.getcwd())
from tools.symbols import sort_symbols


class TestSortSymbols(unittest.TestCase):
    def test_sort_symbol_list_based_on_their_offset(self):
        sorted = sort_symbols(
            ["sym2 = 0x5678; // some comment", "sym3 = 0x9ABC;", "sym1 = 0x1234;"]
        )
        self.assertEqual(
            sorted,
            ["sym1 = 0x1234;", "sym2 = 0x5678; // some comment", "sym3 = 0x9ABC;"],
        )


if __name__ == "__main__":
    unittest.main()
