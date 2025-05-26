#!/usr/bin/env python3
import hashlib
import sys
from pathlib import Path


def sha1sum(filepath):
    h = hashlib.sha1()
    with open(filepath, "rb") as f:
        for chunk in iter(lambda: f.read(8192), b""):
            h.update(chunk)
    return h.hexdigest()


def check_sha1_file(checkfile):
    all_ok = True
    with open(checkfile, "r") as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            try:
                expected_hash, filename = line.split(None, 1)
                filename = filename.strip().lstrip("*")
                filepath = Path(filename)
                if not filepath.exists():
                    print(f"{filename}: FAILED (No such file)")
                    all_ok = False
                    continue

                actual_hash = sha1sum(filepath)
                if actual_hash.lower() == expected_hash.lower():
                    print(f"✅ {filename}")
                else:
                    print(f"❌ {filename}")
                    all_ok = False
            except ValueError:
                print(f"Malformed line: {line}")
                all_ok = False

    return all_ok


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: check.py <checkfile.sha>")
        sys.exit(1)

    checkfile = sys.argv[1]
    ok = check_sha1_file(checkfile)
    sys.exit(0 if ok else 1)
