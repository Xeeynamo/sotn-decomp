import sys


def add_spdx_license(file_path, license):  # AGPL-3.0-only
    spdx_line = f"// SPDX-License-Identifier: {license}"
    try:
        with open(file_path, "r") as file:
            lines = file.readlines()
        if lines and lines[0].strip() == spdx_line:
            return
        with open(file_path, "w") as file:
            file.write(spdx_line + "\n")
            file.writelines(lines)
    except FileNotFoundError:
        print(f"the file {file_path} does not exist")
    except Exception as e:
        print(f"an error occurred: {e}")


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("usage: python add_spdx.py <file_name> <license>")
        sys.exit(1)
    file_names = [sys.argv[1]]
    if file_names[0] == "-":
        file_names = sys.stdin.readlines()
    license = sys.argv[2]
    for file_name in file_names:
        add_spdx_license(file_name.strip(), license)
