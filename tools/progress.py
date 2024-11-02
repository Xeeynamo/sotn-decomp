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
parser.add_argument("--version", required=False, type=str, help="Game version")
parser.add_argument(
    "--dry-run",
    dest="dryrun",
    default=False,
    required=False,
    action="store_true",
    help="Print the request instead of posting it to the server",
)
parser.add_argument(
    "--markdown",
    dest="markdown",
    default=False,
    required=False,
    action="store_true",
    help="Like a dry-run but format the output as a markdown",
)
args = parser.parse_args()
if args.version == None:
    args.version = os.getenv("VERSION")
    if args.version == None:
        args.version = "us"


def printerr(msg: str):
    print(msg, file=sys.stderr)


def exiterr(msg: str):
    printerr(msg)
    exit(-1)


def get_git_commit_message() -> str:
    return (
        subprocess.check_output(["git", "show", "-s", "--format=%s"])
        .decode("utf-8")
        .rstrip()
    )


class DecompProgressStats:
    name: str
    exists: bool
    data_imported: int
    data_total: int
    code_matching: int
    code_total: int
    functions_matching: int
    functions_total: int
    code_matching_prev: int
    functions_prev: int
    data_prev: int

    def get_asm_path(self, ovl_path) -> Path:
        """
        Returns one of the following valid paths:
        `asm/us/st/wrp`
        `asm/pspeu/st/wrp_psp`
        """
        asm_path = f"asm/{args.version}/{ovl_path}"
        if os.path.exists(asm_path):
            return Path(asm_path)
        asm_path_psp = f"asm/{args.version}/{ovl_path}_psp"
        if os.path.exists(asm_path_psp):
            return Path(asm_path_psp)
        exiterr(f"path '{asm_path}' or '{asm_path_psp}' not found")

    def get_nonmatchings_path(self, asm_path: Path) -> Path:
        """
        Returns one of the following valid paths:
        `asm/us/main/nonmatchings`
        `asm/us/st/wrp/nonmatchings`
        `asm/pspeu/dra_psp/psp/dra_psp`
        `asm/pspeu/st/wrp_psp/psp/wrp_psp`
        """
        nonmatchings = f"{asm_path}/nonmatchings"
        if not os.path.exists(nonmatchings):
            nonmatchings_psp = f"{asm_path}/psp/{os.path.basename(asm_path)}"
            if os.path.exists(nonmatchings_psp) and os.path.exists(
                f"{asm_path}/matchings"
            ):
                nonmatchings = nonmatchings_psp
            else:
                print("unable to determine nonmatchings path")
                exit(1)
        # hack to return 'asm/us/main/nonmatchings' instead of 'asm/us/main/nonmatchings/main'
        if nonmatchings.endswith("/main"):
            nonmatchings = nonmatchings[:-5]
        return Path(nonmatchings)

    def __init__(self, module_name: str, path: str):
        self.name = module_name
        self.data_imported = 0
        self.data_total = 0
        self.code_matching = 0
        self.code_total = 0
        self.functions_matching = 0
        self.functions_total = 0

        map_path = Path(f"build/{args.version}/{module_name}.map")
        if not os.path.exists(map_path):
            printerr(f"file '{map_path}' not found")
            self.exists = False
            return
        self.exists = True

        map_file = mapfile_parser.MapFile()
        map_file.readMapFile(map_path)

        asm_path = self.get_asm_path(path)
        nonmatchings = self.get_nonmatchings_path(asm_path)
        depth = 4 + path.count("/")
        self.calculate_progress(
            map_file.filterBySectionType(".text"), asm_path, nonmatchings, depth
        )
        self.add_segment_progress(map_file.filterBySectionType(".data"))
        self.add_segment_progress(map_file.filterBySectionType(".rodata"))
        self.add_segment_progress(map_file.filterBySectionType(".bss"))

    def add_segment_progress(self, map_file: MapFile):
        for file in [file for segment in map_file for file in segment]:
            if "dra_data" in str(
                file.filepath
            ):  # exclude the VAB chunk at the end of DRA.BIN
                continue
            self.data_total += file.size
            if "src/" in str(file.filepath) or "assets/" in str(file.filepath):
                self.data_imported += file.size
            else:
                continue
        return

    # modified version of mapfile_parser.MapFile.getProgress
    def calculate_progress(
        self, map_file: MapFile, asmPath: Path, nonmatchings: Path, pathIndex: int
    ):
        totalStats = ProgressStats()
        progressPerFolder: dict[str, ProgressStats] = dict()
        for file in [file for segment in map_file for file in segment]:
            if len(file) == 0:
                continue

            folder = file.filepath.parts[pathIndex]
            if folder not in progressPerFolder:
                progressPerFolder[folder] = ProgressStats()

            originalFilePath = Path(*file.filepath.parts[pathIndex:])

            extensionlessFilePath = originalFilePath
            while extensionlessFilePath.suffix:
                extensionlessFilePath = extensionlessFilePath.with_suffix("")

            if asmPath != "":
                fullAsmFile = asmPath / extensionlessFilePath.with_suffix(".s")
                wholeFileIsUndecomped = fullAsmFile.exists()
            else:  # nonmatchings path does not exist, the overlay is 100% decompiled
                wholeFileIsUndecomped = False

            for func in file:
                self.functions_total += 1
                funcAsmPath = nonmatchings / extensionlessFilePath / f"{func.name}.s"

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


class DecompProgressWeaponStats:
    name: str
    exists: bool
    code_matching: int
    code_total: int
    functions_matching: int
    functions_total: int
    data_imported: int
    data_total: int
    code_matching_prev: int
    functions_prev: int

    def __init__(self):
        self.name = "weapon"
        self.exists = True
        self.code_matching = 0
        self.code_total = 0
        self.functions_matching = 0
        self.functions_total = 0
        self.data_imported = 0
        self.data_total = 0
        for i in range(0, 59):
            stats = DecompProgressStats(f"weapon/w0_{i:03d}", "weapon")
            if stats.exists:
                self.code_matching += stats.code_matching
                self.code_total += stats.code_total
                self.functions_matching += stats.functions_matching
                self.functions_total += stats.functions_total
                self.data_imported += stats.data_imported
                self.data_total += stats.data_total


def remove_not_existing_overlays(progresses):
    new_progresses = dict[str, DecompProgressStats]()
    for key in progresses:
        value = progresses[key]
        if value.exists == True:
            new_progresses[key] = value
    return new_progresses


def get_progress(module_name: str, path: str) -> DecompProgressStats:
    return DecompProgressStats(module_name, path)


def hydrate_previous_metrics(progresses: dict[str, DecompProgressStats], version: str):
    def fetch_metrics(category, callback):
        api_base_url = os.getenv("FROGRESS_API_BASE_URL")
        r = requests.get(f"{api_base_url}/data/{slug}/{version}/{category}")
        if r.status_code == 404:
            for ovl in progress:
                callback(ovl, 0)
            return
        r.raise_for_status()
        res = r.json()
        if (
            res == None
            or res[slug] == None
            or res[slug][version] == None
            or res[slug][version][category] == None
        ):
            return progress
        if len(res[slug][version][category]) > 0:
            last_measures = res[slug][version][category][0]["measures"]
        else:
            last_measures = {}

        for ovl in progress:
            if ovl in last_measures:
                last_measure = last_measures[ovl]
                if last_measure != None:
                    callback(ovl, last_measure)
            else:
                callback(ovl, 0)

    def set_code_prev(ovl_name, value):
        progresses[ovl_name].code_matching_prev = value

    def set_func_prev(ovl_name, value):
        progresses[ovl_name].functions_prev = value

    def set_data_prev(ovl_name, value):
        progresses[ovl_name].data_prev = value

    progress = remove_not_existing_overlays(progresses)
    fetch_metrics("code", set_code_prev)
    fetch_metrics("functions", set_func_prev)
    fetch_metrics("data", set_data_prev)


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

    def as_data(progresses: DecompProgressStats):
        obj = {}
        for key in progresses:
            overlay_progress = progresses[key]
            obj[overlay_progress.name] = overlay_progress.data_imported
            obj[f"{overlay_progress.name}/total"] = overlay_progress.data_total
        return obj

    return {
        "timestamp": mapfile_parser.utils.getGitCommitTimestamp(),
        "git_hash": mapfile_parser.utils.getGitCommitHash(),
        "categories": {
            "code": as_code(progresses),
            "functions": as_functions(progresses),
            "data": as_data(progresses),
        },
    }


def report_stdout(entry):
    print(entry)


def report_human_readable_dryrun(progresses: dict[str, DecompProgressStats]):
    for overlay in progresses:
        stat = progresses[overlay]
        if (
            stat.code_matching != stat.code_matching_prev
            or stat.data_imported != stat.data_prev
        ):
            coverage = stat.code_matching / stat.code_total
            coverage_diff = (
                stat.code_matching - stat.code_matching_prev
            ) / stat.code_total
            funcs = stat.functions_matching / stat.functions_total
            funcs_diff = (
                stat.functions_matching - stat.functions_prev
            ) / stat.functions_total
            data = stat.data_imported / stat.data_total
            data_diff = (stat.data_imported - stat.data_prev) / stat.data_total
            report = f"{overlay.upper()} ({args.version}): "
            if stat.code_matching != stat.code_matching_prev:
                report += f"coverage {coverage*100:.2f}% ({coverage_diff*100:+.2f}%) "
                report += f"funcs {funcs*100:.2f}% ({funcs_diff*100:+.2f}%) "
            if stat.data_imported != stat.data_prev:
                report += f"data {data*100:.2f}% ({data_diff*100:+.2f}%) "
            print(report)
        else:
            print(f"{overlay.upper()} no new progress")


def report_markdown(progresses: dict[str, DecompProgressStats]):
    for overlay in progresses:
        stat = progresses[overlay]
        if (
            stat.code_matching != stat.code_matching_prev
            or stat.data_imported != stat.data_prev
        ):
            coverage = stat.code_matching / stat.code_total
            coverage_diff = (
                stat.code_matching - stat.code_matching_prev
            ) / stat.code_total
            funcs = stat.functions_matching / stat.functions_total
            funcs_diff = (
                stat.functions_matching - stat.functions_prev
            ) / stat.functions_total
            data = stat.data_imported / stat.data_total
            data_diff = (stat.data_imported - stat.data_prev) / stat.data_total
            report = f"## **{overlay.upper()}** *{args.version}*\n\n"
            if stat.code_matching != stat.code_matching_prev:
                report += (
                    f"coverage {coverage*100:.2f}% ({coverage_diff*100:+.2f}%)\n\n"
                )
                report += f"funcs {funcs*100:.2f}% ({funcs_diff*100:+.2f}%)\n\n"
            if stat.data_imported != stat.data_prev:
                report += f"data {data*100:.2f}% ({data_diff*100:+.2f}%)\n\n"
            report += "\n"
            print(report)
        else:
            continue  # no new progress


def report_frogress(entry, version):
    api_base_url = os.getenv("FROGRESS_API_BASE_URL")
    url = f"{api_base_url}/data/{slug}/{version}/"
    requests.post(
        url, json={"api_key": os.getenv("FROGRESS_API_SECRET"), "entries": [entry]}
    ).raise_for_status()


def report_discord(progresses: dict[str, DecompProgressStats]):
    report = ""
    for overlay in progresses:
        stat = progresses[overlay]
        if (
            stat.code_matching != stat.code_matching_prev
            or stat.data_imported != stat.data_prev
        ):
            coverage = stat.code_matching / stat.code_total
            coverage_diff = coverage - (stat.code_matching_prev / stat.code_total)
            funcs = stat.functions_matching / stat.functions_total
            funcs_diff = funcs - (stat.functions_prev / stat.functions_total)
            data = stat.data_imported / stat.data_total
            data_diff = (stat.data_imported - stat.data_prev) / stat.data_total

            report += f"**{overlay.upper()} ({args.version})**:"
            if stat.code_matching != stat.code_matching_prev:
                report += f"coverage {coverage*100:.2f}% ({coverage_diff*100:+.2f}%) "
                report += f"funcs {funcs*100:.2f}% ({funcs_diff*100:+.2f}%) "
            if stat.data_imported != stat.data_prev:
                report += f"data {data*100:.2f}% ({data_diff*100:+.2f}%) "
            report += "\n"
    if len(report) == 0:
        # nothing to report, do not send any message to Discord
        return

    url = os.getenv("DISCORD_PROGRESS_WEBHOOK")
    data = {
        "username": "Progress",
        "embeds": [
            {
                "title": get_git_commit_message(),
                "description": report,
            }
        ],
    }
    requests.post(url, json=data).raise_for_status()


if __name__ == "__main__":
    progress = dict[str, DecompProgressStats]()
    # progress["main"] = DecompProgressStats("main", "main")
    progress["dra"] = DecompProgressStats("dra", "dra")
    # progress["weapon"] = DecompProgressWeaponStats()
    # progress["ric"] = DecompProgressStats("ric", "ric")
    # progress["stcen"] = DecompProgressStats("stcen", "st/cen")
    # progress["stdre"] = DecompProgressStats("stdre", "st/dre")
    # progress["stmad"] = DecompProgressStats("stmad", "st/mad")
    # progress["stno0"] = DecompProgressStats("stno0", "st/no0")
    # progress["stno3"] = DecompProgressStats("stno3", "st/no3")
    # progress["stnp3"] = DecompProgressStats("stnp3", "st/np3")
    # progress["stnz0"] = DecompProgressStats("stnz0", "st/nz0")
    # progress["stsel"] = DecompProgressStats("stsel", "st/sel")
    # progress["stst0"] = DecompProgressStats("stst0", "st/st0")
    # progress["stwrp"] = DecompProgressStats("stwrp", "st/wrp")
    # progress["strwrp"] = DecompProgressStats("strwrp", "st/rwrp")
    # progress["bomar"] = DecompProgressStats("bomar", "boss/mar")
    # progress["borbo3"] = DecompProgressStats("borbo3", "boss/rbo3")
    # progress["tt_000"] = DecompProgressStats("tt_000", "servant/tt_000")
    # progress["tt_001"] = DecompProgressStats("tt_001", "servant/tt_001")
    # progress["tt_002"] = DecompProgressStats("tt_002", "servant/tt_002")

    hydrate_previous_metrics(progress, args.version)
    progress = remove_not_existing_overlays(progress)

    entry = get_progress_entry(progress)
    if args.dryrun:
        report_stdout(entry)
        report_human_readable_dryrun(progress)
    elif args.markdown:
        report_markdown(progress)
    else:
        report_discord(progress)
        report_frogress(entry, args.version)
