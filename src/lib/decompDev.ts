// Fetches and parses a single decomp.dev objdiff report into per-overlay
// "Code" coverage. decomp.dev serves the report at:
//
//   https://decomp.dev/Xeeynamo/sotn-decomp/report?version=<VER>&mode=report
//
// with content negotiation, so we must request JSON explicitly. Each report
// unit carries metadata.progress_categories such as ["st","st.are"] or
// ["engine","engine.dra"]; we collapse those down to a single canonical
// overlay id (the original game binary) and aggregate matched code by size.

const PROJECT = "Xeeynamo/sotn-decomp";

interface ReportUnit {
  name: string;
  measures?: {
    total_code?: string | number;
    matched_code_percent?: number;
  };
  metadata?: {
    progress_categories?: string[];
  };
}

interface Report {
  units?: ReportUnit[];
}

export interface OverlayProgress {
  /** 0..100 matched code percentage for the overlay. */
  codePercent: number;
  /** Total code size in bytes (used as the aggregation weight). */
  totalCode: number;
}

/** Map of canonical overlay id -> aggregated progress for one build. */
export type VersionProgress = Map<string, OverlayProgress>;

// Collapse a unit's progress_categories into the canonical overlay id, i.e.
// the original game binary the unit belongs to.
function overlayIdForUnit(unit: ReportUnit): string | null {
  const cats = unit.metadata?.progress_categories ?? [];
  if (cats.length === 0) {
    return null;
  }

  // Weapons are split across many w0_*/w1_* units (PSP/HD) or engine.weapon/*
  // units (US); both collapse to the single WEAPON0.BIN overlay.
  if (cats.some((c) => c === "weapon" || c === "engine.weapon" || c.startsWith("weapon."))) {
    return "weapon";
  }

  // Otherwise use the second dotted segment of the most specific category,
  // e.g. "st.are" -> "are", "bo.rbo3" -> "rbo3", "engine.dra" -> "dra",
  // "servant.tt_000" -> "tt_000".
  const leaf = cats
    .filter((c) => c.includes("."))
    .sort((a, b) => b.length - a.length)[0];
  if (!leaf) {
    return null;
  }
  const parts = leaf.split(".");
  return parts[parts.length - 1] || null;
}

function toNumber(value: string | number | undefined): number {
  if (value == null) {
    return 0;
  }
  const n = typeof value === "string" ? Number(value) : value;
  return Number.isFinite(n) ? n : 0;
}

function parseReport(report: Report): VersionProgress {
  // Accumulate matched bytes and total bytes per overlay, then derive percent.
  const acc = new Map<string, { matched: number; total: number }>();

  for (const unit of report.units ?? []) {
    const id = overlayIdForUnit(unit);
    if (!id) {
      continue;
    }
    const total = toNumber(unit.measures?.total_code);
    const matched = (toNumber(unit.measures?.matched_code_percent) / 100) * total;
    const entry = acc.get(id) ?? { matched: 0, total: 0 };
    entry.matched += matched;
    entry.total += total;
    acc.set(id, entry);
  }

  const result: VersionProgress = new Map();
  for (const [id, { matched, total }] of acc) {
    result.set(id, {
      codePercent: total > 0 ? (matched / total) * 100 : 0,
      totalCode: total,
    });
  }
  return result;
}

// Fetches one version's report. Returns an empty map (no overlays) when the
// version is not yet tracked on decomp.dev (HTTP 404) so the column simply
// renders blank instead of erroring.
export async function fetchVersionProgress(version: string): Promise<VersionProgress> {
  const url = `https://decomp.dev/${PROJECT}/report?version=${encodeURIComponent(
    version,
  )}&mode=report`;
  const response = await fetch(url, { headers: { Accept: "application/json" } });
  if (response.status === 404) {
    return new Map();
  }
  if (!response.ok) {
    throw new Error(`decomp.dev returned ${response.status} for version "${version}"`);
  }
  const report = (await response.json()) as Report;
  return parseReport(report);
}
