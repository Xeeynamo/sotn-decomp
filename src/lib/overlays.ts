// Derives the ordered list of overlay rows from the union of overlays present
// across every fetched build, then classifies and sorts them. The overlay set
// is data-driven: no overlay is hardcoded, so a newly imported overlay appears
// automatically.

import { CategoryId, overlayMeta } from "../data/builds";
import { VersionProgress } from "./decompDev";

export interface OverlayRow {
  /** Canonical overlay id (e.g. "dra", "are", "rbo3", "tt_000", "weapon"). */
  id: string;
  category: CategoryId;
  /** Friendly name (falls back to the id). */
  name: string;
  /** Description (falls back to the id). */
  desc: string;
}

// Player / engine overlays that are not stage/boss/weapon/familiar binaries.
const PLAYER_IDS = new Set(["dra", "ric", "maria", "main", "sel"]);
const DEBUG_ENGINE_IDS = new Set(["fname", "sd", "tek"]);

function classify(id: string): CategoryId {
  if (id === "weapon") {
    return "weapon";
  }
  if (id.startsWith("tt_")) {
    return "familiar";
  }
  // Debug / test stages: the MAD debug room and the TE1..TE5 test stages.
  if (id === "mad" || /^te\d+$/.test(id)) {
    return "debug";
  }
  if (DEBUG_ENGINE_IDS.has(id)) {
    return "debug";
  }
  if (PLAYER_IDS.has(id)) {
    return "player";
  }
  // Reverse bosses (rbo*) before bosses (bo*), reverse stages (r*) before
  // stages, matching the original RBO/BO and R<name> naming conventions.
  if (/^rbo\d+$/.test(id)) {
    return "rboss";
  }
  if (/^bo\d+$/.test(id) || id === "mar") {
    return "boss";
  }
  if (id.startsWith("r")) {
    return "rstage";
  }
  return "stage";
}

// Stable secondary ordering within a category: bo0..bo7 then mar, tt_000..,
// otherwise alphabetical. Keeps the table tidy and predictable.
function sortKey(id: string): string {
  const m = id.match(/^(r?bo|tt_|te)(\d+)$/);
  if (m) {
    return `${m[1]}${m[2].padStart(4, "0")}`;
  }
  return id;
}

export function buildOverlayRows(versions: VersionProgress[]): OverlayRow[] {
  const ids = new Set<string>();
  for (const v of versions) {
    for (const id of v.keys()) {
      ids.add(id);
    }
  }

  return [...ids]
    .map((id) => {
      const meta = overlayMeta[id];
      return {
        id,
        category: classify(id),
        name: meta?.name ?? id.toUpperCase(),
        desc: meta?.desc ?? "Overlay derived from the decomp.dev report",
      };
    })
    .sort((a, b) => sortKey(a.id).localeCompare(sortKey(b.id)));
}
