# search for scratches with the name on decomp.me
import json
import requests
import sys


def find_scratches(name, platform):
    try:
        response = requests.get(f"https://decomp.me/api/scratch?search={name}")
        response.raise_for_status()
        scratches = json.loads(response.text)
    except requests.exceptions.HTTPError as http_err:
        print(f"\033[91mfind_scratches HTTP error: {http_err}", file=sys.stderr)
        return None
    except Exception as err:
        print(f"\033[91mfind_scratches exception: {err}", file=sys.stderr)
        return None

    best_result = None
    best_percent = 0

    for result in scratches["results"]:
        if not "name" in result:
            continue
        # seems to give approximate matches, skip these
        if result["name"] != name:
            continue
        if result["platform"] != platform:
            continue

        score = result["score"]
        max_score = result["max_score"]
        percent = (max_score - score) / max_score

        if percent > best_percent:
            best_percent = percent
            best_result = result

    if best_result:
        return [f"https://decomp.me/scratch/{best_result['slug']}", round(best_percent, 3)]

    return None
