#!/usr/bin/env python3
import hashlib, os, shutil, sys

def sha1sum(filepath):
    h = hashlib.sha1()
    with open(filepath, "rb") as f:
        for chunk in iter(lambda: f.read(8192), b""):
            h.update(chunk)
    return h.hexdigest()


def read_checksums(filepath):
    checksums = []
    with open(filepath, "r") as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            checksum, name = line.split(None, 1)
            checksums.append({
                "name": name,
                "ovl": os.path.splitext(os.path.basename(name))[0],
                "checksum": checksum,
            })
    return checksums


def check_sha1_file(checkfile):
    checksums = read_checksums(checkfile)
    element_width = max([len(check['ovl']) for check in checksums]) + 2
    window_width = shutil.get_terminal_size((60, 24)).columns
    n_elements_per_line = window_width // element_width

    column = 0
    line = ""
    all_ok = True
    for check in checksums:
        if not os.path.exists(check['name']):
            result = "❓"
            all_ok = False
        elif sha1sum(check['name']).lower() != check['checksum'].lower():
            result = "❌"
            all_ok = False
        else:
            result = "✅"
        line += f"{result} {check['ovl']:<{element_width}}"
        column += 1
        if column % n_elements_per_line == 0:
            column = 0
            print(line)
            line = ""
    if line != "":
        print(line)
    return all_ok


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: check.py <checkfile.sha>")
        sys.exit(1)
    sys.exit(0 if check_sha1_file(sys.argv[1]) else 1)
