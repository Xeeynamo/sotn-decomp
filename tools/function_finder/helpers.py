# search for scratches with the name on decomp.me
import json
import requests
import sys
import zipfile
from io import BytesIO
import difflib

def are_strings_similar(str1, str2, threshold=0.8):
    similarity = difflib.SequenceMatcher(None, str1, str2).ratio()
    return similarity >= threshold

def get_asm(slug):
    url = f'https://decomp.me/api/scratch/{slug}/export'
    response = requests.get(url)
    if response.status_code == 200:
        with zipfile.ZipFile(BytesIO(response.content)) as the_zip:
            zip_contents = the_zip.namelist()
            if 'target.s' in zip_contents:
                with the_zip.open('target.s') as file:
                    target_content = file.read().decode('utf-8')
                return target_content
            else:
                print("target.s not found in the zip file")
    else:
        print(f"Failed to download the zip file: Status code {response.status_code}")
    return None

def find_scratches(name, platform, local_asm=None, use_local=False):
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

        if use_local:
            remote_asm = get_asm(result['slug'])

            if not are_strings_similar(local_asm, remote_asm):
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
