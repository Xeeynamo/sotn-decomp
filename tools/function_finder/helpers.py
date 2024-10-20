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

zip_cache = {}

def get_asm(slug):
    if slug in zip_cache:
        return zip_cache[slug]
    url = f'https://decomp.me/api/scratch/{slug}/export'
    response = requests.get(url)
    if response.status_code == 200:
        with zipfile.ZipFile(BytesIO(response.content)) as the_zip:
            zip_contents = the_zip.namelist()
            if 'target.s' in zip_contents:
                with the_zip.open('target.s') as file:
                    target_content = file.read().decode('utf-8')
                zip_cache[slug] = target_content
                return target_content
            else:
                print("target.s not found in the zip file")
    else:
        print(f"Failed to download the zip file: Status code {response.status_code}")
    return None

result_cache = {}

def fetch_all_results(url):
    if url in result_cache:
        return result_cache[url]

    results = []

    while url:
        response = requests.get(url)
        data = response.json()

        results.extend(data.get('results', []))

        url = data.get('next')

    result_cache[url] = results
    return results

def find_scratches(name, platform, local_asm=None, use_local=False):
    results = fetch_all_results(f"https://decomp.me/api/scratch?search={name}&page_size=100")

    best_result = None
    best_percent = 0

    for result in results:
        if not "name" in result:
            continue
        if not result["name"].startswith(name):
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
