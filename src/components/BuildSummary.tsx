import { Build } from "../data/builds";
import { VersionProgress } from "../lib/decompDev";

interface Props {
  builds: Build[];
  progress: Map<string, VersionProgress>;
}

// Size-weighted matched percentage over every overlay of one build, plus how
// many of its overlays are fully matched.
function summarise(version: VersionProgress) {
  let matched = 0;
  let total = 0;
  let done = 0;
  for (const overlay of version.values()) {
    matched += (overlay.codePercent / 100) * overlay.totalCode;
    total += overlay.totalCode;
    if (overlay.codePercent >= 99.995) {
      done += 1;
    }
  }
  return {
    percent: total > 0 ? (matched / total) * 100 : 0,
    done,
    count: version.size,
  };
}

export function BuildSummary({ builds, progress }: Props) {
  return (
    <div className="summary">
      {builds.map((b) => {
        const version = progress.get(b.id);
        if (!version || version.size === 0) {
          return null;
        }
        const { percent, done, count } = summarise(version);
        return (
          <div key={b.id} className="stat" title={`${b.name}\n\n${b.description}`}>
            <div className="stat-label">{b.id}</div>
            <div className="stat-value">{percent.toFixed(1)}%</div>
            <div className="stat-sub">
              {done}/{count} overlays matched
            </div>
            <div className="stat-bar">
              <span style={{ width: `${Math.max(1, percent)}%` }} />
            </div>
          </div>
        );
      })}
    </div>
  );
}
