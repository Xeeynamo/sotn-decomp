#!/usr/bin/env python3

# tool to move nonmatchings -> matchings for cases where splat incorrectly assumes they are not matching.
# for example when code is IFDEF out for certain versions
import mapfile_parser
from pathlib import Path

def read_nonmatchings_from_disk():
    # Find all .s files in subdirectories of "nonmatchings"
    return [
        path for path in Path('./asm/us').rglob("*.s")
        if "nonmatchings" in path.parts and path.parts[path.parts.index("nonmatchings") - 1] != "nonmatchings"
    ]

def read_nonmatchings_from_mapfile():
    non_matching_map = list()

    # Get all .map files in the current directory
    map_files = list(Path('./build/us').rglob('*.map'))

    for map_path in map_files:
        map_file = mapfile_parser.MapFile()
        map_file.readMapFile(map_path)
        map_file = map_file.filterBySectionType(".text")

        for segment in map_file:
            for file in segment:
                if len(file) == 0:
                    continue

                for func in file:
                    if func.name.endswith(".NON_MATCHING"):
                        continue

                    funcNonMatching = f"{func.name}.NON_MATCHING"

                    if map_file.findSymbolByName(funcNonMatching) is not None:
                        # Replace "build/us/src" with "asm/us"
                        new_path = Path("asm/us") / file.filepath.relative_to("build/us/src")

                        # Detect "nonmatching" path
                        for parent in new_path.parents:
                            nonmatchings_path = parent / "nonmatchings"
                            if nonmatchings_path.exists() and nonmatchings_path.is_dir():
                                #print(f"Matched {nonmatchings_path}")
                                break

                        new_path = nonmatchings_path / new_path.relative_to(parent).with_suffix('')

                        # Remove ".o" from the file extension
                        new_path = new_path.with_suffix('')

                        # Append function name
                        new_path = new_path / func.name

                        # Change the extension from ".c" to ".s"
                        new_path = new_path.with_suffix('.s')

                        if new_path.is_file():
                            non_matching_map.append(new_path)
                        else:
                            print(f"{new_path} did not match a file")

    return non_matching_map

if __name__ == "__main__":
    non_matching_map = read_nonmatchings_from_mapfile()
    non_matchings_disk = read_nonmatchings_from_disk()

    actually_matches = [path for path in non_matchings_disk if path not in non_matching_map]
    print(f"{len(non_matchings_disk)} nonmatchings on disk but {len(actually_matches)} were actually matches, going to move these to /matchings")

    for path in actually_matches:
        new_path = Path(path.as_posix().replace("nonmatchings", "matchings"))
        new_path.parent.mkdir(parents=True, exist_ok=True)
        path.rename(new_path)
        #print(f"Moved: {path} -> {new_path}")
