#!/usr/bin/env python3

import git
import sys

repo = git.Repo()

changed_files = [item.a_path for item in repo.index.diff(None)]
if not changed_files:
    print("tree is clean")
    sys.exit(0)
else:
    print("tree is dirty. Changed files:")
    for file in changed_files:
        print(file)
    sys.exit(1)
