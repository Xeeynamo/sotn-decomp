#!/usr/bin/python3

# Generates a series of graphs to trace the call tree of a given function.
#

from fileinput import filename
from pathlib import Path

from sympy import intersection
import graphviz

# The 'entrypoint_sotn' is far too bloated.
# This splits the graph into smaller graphs.
# A node split is indicated by the color cyan.
#
# HOW TO USE:
# make force_extract
# ./tools/analyze_calls.py
#
# WARNING: This will bloat the root of the repo! Be careful when you run it.

# For now this only works with DRA
asm_path = "asm/us/dra"

node_breaks = [
    "HandleTitle",
    "HandlePlay",
    "HandleGameOver",
    "HandleNowLoading",
    "HandleVideoPlayback",
    "HandlePrologueEnd",
    "HandleMainMenu",
    "HandleEnding",
    "UpdateEntityAlucard",
]

# Hardcoded list of entry points.
# Not all of them can be detected programmatically.
entry_points = [
    # Called by main.exe
    "entrypoint_sotn",
    # Stripped from entrypoint_sotn
    "HandlePlay",
    "HandleGameOver",
    "HandleNowLoading",
    "HandleVideoPlayback",
    "HandlePrologueEnd",
    "HandleMainMenu",
    "HandleEnding",
    "UpdateEntityAlucard",
    # GameAPI
    "FreePrimitives",
    "AllocPrimitives",
    "CheckCollision",
    "func_80102CD8",
    "UpdateAnim",
    "AccelerateX",
    "GetFreeDraEntity",
    "GetEquipProperties",
    "func_800EA5E4",
    "func_800EAF28",
    "PlaySfx",
    "func_800EDB58",
    "func_800EA538",
    "func_800EA5AC",
    "func_801027C4",
    "func_800EB758",
    "func_8011AAFC",
    "func_80131F68",
    "func_800EDB08",
    "func_80106A28",
    "func_80118894",
    "func_80118970",
    "func_80118B18",
    "func_8010DB38",
    "func_8010DBFC",
    "func_80118C28",
    "func_8010E168",
    "func_8010DFF0",
    "func_800FF128",
    "func_800EB534",
    "AddHearts",
    "func_8010715C",
    "func_800FD4C0",
    "func_8010E0A8",
    "func_800FE044",
    "AddToInventory",
    "func_800FF7B8",
    "func_80134714",
    "func_80134678",
    "func_800F53A4",
    "CheckEquipmentItemCount",
    "func_8010BF64",
    "func_800F1FC4",
    "func_800F2288",
    "func_8011A3AC",
    "func_800FF460",
    "func_800FF494",
    "func_80133940",
    "func_80133950",
    "func_800F27F4",
    "func_800FF110",
    "func_800FD664",
    "func_800FD5BC",
    "func_800FDCE0",
    "func_800E2438",
    # Found in the entities array
    "func_8011A4C8",
    "func_8011AC3C",
    "func_8011B5A4",
    "func_8011E0EC",
    "EntitySubwpnThrownDagger",
    "func_8011E4BC",
    "func_8011B334",
    "func_801315F8",
    "EntitySubwpnCrashCross",
    "EntitySubwpnCrashCrossParticles",
    "EntitySubwpnThrownAxe",
    "EntityPlayerBlinkWhite",
    "EntitySubwpnThrownVibhuti",
    "func_8011E0E4",
    "func_8011EDA0",
    "func_8011B190",
    "func_8011EDA8",
    "func_80128C2C",
    "func_801291C4",
    "EntityNumberMovesToHpMeter",
    "EntitySubwpnReboundStone",
    "EntityLevelUpAnimation",
    "EntityHolyWater",
    "EntityHolyWaterFlame",
    "func_8011BBE0",
    "func_80126ECC",
    "func_801274DC",
    "func_80127840",
    "EntityExpandingCircle",
    "func_80127CC8",
    "EntityHitByLightning",
    "EntityMpReplenished",
    "EntityPlayerDissolves",
    "EntityHitByIce",
    "EntityMist",
    "func_8011E390",
    "func_8011B480",
    "EntityGuardText",
    "EntityTransparentWhiteCircle",
    "EntityPlayerPinkEffect",
    "EntityHolyWaterBreakGlass",
    "EntityStopWatch",
    "EntityStopWatchExpandingCircle",
    "EntitySubwpnBible",
    "func_8012B78C",
    "func_8012768C",
    "func_80123B40",
    "func_80119F70",
    "func_80123788",
    "func_801238CC",
    "func_80123A60",
    "func_80119D3C",
    "EntityBatEcho",
    "func_8011B530",
    "func_8011F074",
    "func_80130264",
    "func_8012F894",
    "func_80130618",
    "func_801309B4",
    "func_80130E94",
    "func_8013136C",
    "func_80129864",
    "EntitySummonSpirit",
    "func_80123F78",
    "EntityTeleport",
    "func_80124A8C",
    # Found in the CD callback array
    "func_801080DC",
    "CopyStageOvlCallback",
    "CopyRicOvlCallback",
    "func_801078C4",
    "func_80107B04",
    "func_80107DB4",
    "func_80107C6C",
    "func_80107EF0",
    # CdDataCallback
    "CopySupportOvlCallback",
    # VSyncCallback
    "func_800E7BB8",
    # CdReadyCallback
    "func_80107460",
    # Orphans
    "func_800E7BB8",
    "func_801072FC",
    "func_801072FC",
    "func_800E2B00",
    "func_800E2E98",
    "func_800E376C",
    "func_80131F94",
    "func_800F9D40",
    "func_8010DA2C",
    "func_800E97BC",
    "func_800E31C0",
    "func_800E9640",
    "func_800FF708",
    "func_800E2F3C",
    "func_800E9610",
    "func_80131F38",
    "func_800F1424",
    "func_801083F0",
    "func_800E249C",
    "func_800E2824",
    "func_800E38CC",
    "func_800FD39C",
]


def collect_calls(asm_path):
    funcs = dict()
    for path in Path(asm_path).rglob("*.s"):
        # ignore data
        if not "nonmatchings" in str(path):
            continue
        # ignore main since it's just PSY-Q functions
        if "asm/us/main" in str(path):
            continue

        with open(f"{path}", "r") as f:
            func_name = path.stem
            func_calls = set()
            for line in f.readlines():
                # ignore
                if not "jal" in line:
                    continue
                func_name_call = line.split(" ")[-1].strip()
                func_calls.add(func_name_call)
            funcs[func_name] = func_calls
    return funcs


def count_calls(funcs: dict):
    n_calls = dict()
    for func_name in funcs:
        for call in funcs[func_name]:
            if call not in n_calls:
                n_calls[call] = 1
            else:
                n_calls[call] += 1
    return sorted(n_calls.items(), key=lambda x: x[1], reverse=True)


def get_call_tree(funcs, callees: set, func_name: str):
    nodes = []
    callees.add(func_name)
    if func_name in funcs:
        for call in funcs[func_name]:
            if call not in callees:  # avoid circular calls
                nodes.append(get_call_tree(funcs, set(callees), call))
    return {"name": func_name, "calls": nodes}


def make_graph(call_tree):
    traversed_nodes = set()
    graph = graphviz.Digraph("G", filename=call_tree["name"], engine="dot")
    graph.format = "pdf"

    def add_node(parent):
        parent_name = parent["name"]
        traversed_nodes.add(parent_name)
        if parent_name in node_breaks and parent != call_tree:
            return
        for child in parent["calls"]:
            graph.edge(parent_name, child["name"])
            add_node(child)

    add_node(call_tree)
    return graph, traversed_nodes


if __name__ == "__main__":
    funcs = collect_calls(asm_path)
    n_calls = count_calls(funcs)
    max_call_count = n_calls[0][1]
    n_calls = dict(n_calls)

    entries = dict()
    for entry in entry_points:
        traversed_funcs = set()
        entries[entry] = get_call_tree(funcs, set(), entry)

    for entry in entry_points:
        g, traversed = make_graph(entries[entry])
        for func_name in traversed:
            if func_name not in n_calls:
                continue
            if func_name in node_breaks:
                # The node's content is rendered in another file
                color = f"#00e0ff"
            else:
                # If just one call, don't bother with the heat map
                count = n_calls[func_name]
                if count == 1:
                    continue
                heat = 255 - int(count / max_call_count * 255)
                color = f"#ff{heat:02X}{heat:02X}"
            g.node(func_name, style="filled", fillcolor=color)
        g.render()
