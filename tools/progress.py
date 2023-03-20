#!/usr/bin/env python3
import argparse
import mapfile_parser
import mapfile_parser.utils
import mapfile_parser.frontends.upload_frogress
import os
import requests
import subprocess
import sys
from pathlib import Path
from mapfile_parser import MapFile
from mapfile_parser import ProgressStats

slug = "sotn"

parser = argparse.ArgumentParser(description="Report decompilation progress")
parser.add_argument('--version', metavar='version', default='us', required=False,
                    type=str, help='Game version')
parser.add_argument('--dry-run', dest="dryrun", default=False, required=False,
                    action="store_true", help='Print the request instead of posting it to the server')
args = parser.parse_args()


def exiterr(msg: str):
    print(msg, file=sys.stderr)
    exit(-1)


def get_git_commit_message() -> str:
    return subprocess.check_output(['git', 'show', '-s', '--format=%s']).decode('ascii').rstrip()


class DecompProgressStats:
    name: str
    code_matching: int
    code_total: int
    functions_matching: int
    functions_total: int
    code_matching_prev: int
    functions_prev: int

    def __init__(self, module_name: str, path: str):
        self.name = module_name
        self.code_matching = 0
        self.code_total = 0
        self.functions_matching = 0
        self.functions_total = 0

        map_path = Path(f"build/{args.version}/{module_name}.map")
        if not os.path.exists(map_path):
            exiterr(f"file '{map_path}' not found")

        map_file = mapfile_parser.MapFile()
        map_file.readMapFile(map_path)

        asm_path = f"asm/{args.version}/{path}"
        if not os.path.exists(asm_path):
            exiterr(f"path '{asm_path}' not found")

        nonmatchings = f"{asm_path}/nonmatchings"
        if not os.path.exists(nonmatchings):
            exiterr(f"path '{nonmatchings}' not found")

        depth = 4 + path.count("/")

        self.calculate_progress(map_file.filterBySegmentType(
            ".text"), asm_path, nonmatchings, depth)

    # modified version of mapfile_parser.MapFile.getProgress
    def calculate_progress(self, map_file: MapFile, asmPath: Path, nonmatchings: Path, pathIndex: int):
        totalStats = ProgressStats()
        progressPerFolder: dict[str, ProgressStats] = dict()

        for file in map_file.filesList:
            if len(file.symbols) == 0:
                continue

            folder = file.filepath.parts[pathIndex]
            if folder not in progressPerFolder:
                progressPerFolder[folder] = ProgressStats()

            originalFilePath = Path(*file.filepath.parts[pathIndex:])

            extensionlessFilePath = originalFilePath
            while extensionlessFilePath.suffix:
                extensionlessFilePath = extensionlessFilePath.with_suffix("")

            fullAsmFile = asmPath / extensionlessFilePath.with_suffix(".s")
            wholeFileIsUndecomped = fullAsmFile.exists()

            for func in file.symbols:
                self.functions_total += 1
                funcAsmPath = nonmatchings / \
                    extensionlessFilePath / f"{func.name}.s"

                if wholeFileIsUndecomped:
                    totalStats.undecompedSize += func.size
                    progressPerFolder[folder].undecompedSize += func.size
                elif funcAsmPath.exists():
                    totalStats.undecompedSize += func.size
                    progressPerFolder[folder].undecompedSize += func.size
                else:
                    self.functions_matching += 1
                    totalStats.decompedSize += func.size
                    progressPerFolder[folder].decompedSize += func.size

        self.code_matching = totalStats.decompedSize
        self.code_total = totalStats.decompedSize + totalStats.undecompedSize


def get_progress(module_name: str, path: str) -> DecompProgressStats:
    return DecompProgressStats(module_name, path)


def hydrate_previous_metrics(progresses: dict[str, DecompProgressStats], version: str):
    def fetch_metrics(category, callback):
        api_base_url = os.getenv("FROGRESS_API_BASE_URL")
        r = requests.get(f"{api_base_url}/data/{slug}/{version}/{category}")
        r.raise_for_status()
        res = r.json()
        if res == None or res[slug] == None or res[slug][version] == None or res[slug][version][category] == None:
            return progress
        last_measures = res[slug][version][category][0]["measures"]
        assert (last_measures != None)

        for ovl in progress:
            last_measure = last_measures[ovl]
            if last_measure != None:
                callback(ovl, last_measure)

    def set_code_prev(ovl_name, value):
        progresses[ovl_name].code_matching_prev = value

    def set_func_prev(ovl_name, value):
        progresses[ovl_name].functions_prev = value

    fetch_metrics("code", set_code_prev)
    fetch_metrics("functions", set_func_prev)


def get_progress_entry(progresses: dict[str, DecompProgressStats]):
    def as_code(progresses: dict[str, DecompProgressStats]):
        obj = {}
        for key in progresses:
            overlay_progress = progresses[key]
            obj[overlay_progress.name] = overlay_progress.code_matching
            obj[f"{overlay_progress.name}/total"] = overlay_progress.code_total
        return obj

    def as_functions(progresses: DecompProgressStats):
        obj = {}
        for key in progresses:
            overlay_progress = progresses[key]
            obj[overlay_progress.name] = overlay_progress.functions_matching
            obj[f"{overlay_progress.name}/total"] = overlay_progress.functions_total
        return obj

    return {
        "timestamp": mapfile_parser.utils.getGitCommitTimestamp(),
        "git_hash": mapfile_parser.utils.getGitCommitHash(),
        "categories": {
            "code": as_code(progresses),
            "functions": as_functions(progresses),
        }
    }


def report_stdout(entry):
    print(entry)


def report_human_readable_dryrun(progresses: dict[str, DecompProgressStats]):
    for overlay in progresses:
        stat = progresses[overlay]
        if stat.code_matching != stat.code_matching_prev:
            coverage = stat.code_matching / stat.code_total
            coverage_diff = (stat.code_matching -
                             stat.code_matching_prev) / stat.code_total
            funcs = stat.functions_matching / stat.functions_total
            funcs_diff = (stat.functions_matching -
                          stat.functions_prev) / stat.functions_total
            print(str.join(" ", [
                f"{overlay.upper()}:",
                f"coverage {coverage*100:.2f}%",
                f"({coverage_diff:+.3f}%)",
                f"funcs {funcs*100:.2f}%",
                f"({funcs_diff:+.3f}%)",
            ]))
        else:
            print(f"{overlay.upper()} no new progress")


def report_frogress(entry, version):
    api_base_url = os.getenv("FROGRESS_API_BASE_URL")
    url = f"{api_base_url}/data/{slug}/{version}/"
    requests.post(url, json={
        "api_key": os.getenv("FROGRESS_API_SECRET"),
        "entries": [entry]
    }).raise_for_status()


def report_discord(progresses: dict[str, DecompProgressStats]):
    report = ""
    for overlay in progresses:
        stat = progresses[overlay]
        if stat.code_matching != stat.code_matching_prev:
            coverage = stat.code_matching / stat.code_total
            coverage_diff = coverage - \
                (stat.code_matching_prev / stat.code_total)
            funcs = stat.functions_matching / stat.functions_total
            funcs_diff = funcs - (stat.functions_prev / stat.functions_total)
            report += str.join(" ", [
                f"**{overlay.upper()}**:",
                f"coverage {coverage*100:.2f}%",
                f"({coverage_diff:+.2f}%)",
                f"funcs {funcs*100:.2f}%",
                f"({funcs_diff:+.2f}%)",
            ]) + "\n"
    if len(report) == 0:
        # nothing to report, do not send any message to Discord
        return

    url = os.getenv("DISCORD_PROGRESS_WEBHOOK")
    data = {
        "username": "Progress",
        "embeds": [{
            "title": get_git_commit_message(),
            "description": report,
        }],
    }
    requests.post(url, json=data).raise_for_status()


if __name__ == "__main__":
    progress = dict[str, DecompProgressStats]()
    progress["dra"] = DecompProgressStats("dra", "dra")
    progress["ric"] = DecompProgressStats("ric", "ric")
    progress["stcen"] = DecompProgressStats("stcen", "st/cen")
    progress["stdre"] = DecompProgressStats("stdre", "st/dre")
    progress["stmad"] = DecompProgressStats("stmad", "st/mad")
    progress["stno3"] = DecompProgressStats("stno3", "st/no3")
    progress["stnp3"] = DecompProgressStats("stnp3", "st/np3")
    progress["stnz0"] = DecompProgressStats("stnz0", "st/nz0")
    progress["stsel"] = DecompProgressStats("stsel", "st/sel")
    progress["stst0"] = DecompProgressStats("stst0", "st/st0")
    progress["stwrp"] = DecompProgressStats("stwrp", "st/wrp")
    progress["strwrp"] = DecompProgressStats("strwrp", "st/rwrp")
    progress["tt_000"] = DecompProgressStats("tt_000", "servant/tt_000")

    hydrate_previous_metrics(progress, args.version)
    entry = get_progress_entry(progress)
    if args.dryrun == False:
        report_discord(progress)
        report_frogress(entry, args.version)
    else:
        report_stdout(entry)
        report_human_readable_dryrun(progress)
