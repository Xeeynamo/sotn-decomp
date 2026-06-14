import { Build, categories } from "../data/builds";
import { VersionProgress } from "../lib/decompDev";
import { OverlayRow } from "../lib/overlays";

interface Props {
  builds: Build[];
  rows: OverlayRow[];
  // Per-build parsed progress, keyed by build id (matching Build.id).
  progress: Map<string, VersionProgress>;
}

// Maps a 0..100 percentage to a heat colour: green only at a full 100% match,
// yellow for anything in progress (including a yellow-ish tint at 0%), so the
// whole table can be scanned at a glance.
function heatStyle(percent: number): React.CSSProperties {
  if (percent >= 99.995) {
    return { backgroundColor: "hsl(125, 55%, 30%)" };
  }
  // Yellow (hue ~48), deepening with completion. Stays yellow right up to 100%.
  const t = Math.max(0, Math.min(1, percent / 100));
  const bg = `hsl(48, ${30 + t * 35}%, ${17 + t * 11}%)`;
  return { backgroundColor: bg };
}

function formatPercent(percent: number): string {
  if (percent >= 99.995) {
    return "100%";
  }
  if (percent > 0 && percent < 0.5) {
    return "<1%";
  }
  return `${Math.round(percent)}%`;
}

export function ProgressTable({ builds, rows, progress }: Props) {
  return (
    <div className="table-scroll">
      <table className="progress-table">
        <thead>
          <tr>
            <th className="corner" scope="col">
              Overlay
            </th>
            {builds.map((b) => (
              <th key={b.id} scope="col" title={`${b.name}\n\n${b.description}`}>
                {b.id}
              </th>
            ))}
          </tr>
        </thead>
        <tbody>
          {categories.map((cat) => {
            const catRows = rows.filter((r) => r.category === cat.id);
            if (catRows.length === 0) {
              return null;
            }
            return (
              <CategorySection
                key={cat.id}
                name={cat.name}
                colSpan={builds.length + 1}
                rows={catRows}
                builds={builds}
                progress={progress}
              />
            );
          })}
        </tbody>
      </table>
    </div>
  );
}

interface SectionProps {
  name: string;
  colSpan: number;
  rows: OverlayRow[];
  builds: Build[];
  progress: Map<string, VersionProgress>;
}

function CategorySection({ name, colSpan, rows, builds, progress }: SectionProps) {
  return (
    <>
      <tr className="section-row">
        <th className="section-head" colSpan={colSpan} scope="colgroup">
          {name}
        </th>
      </tr>
      {rows.map((row) => (
        <tr key={row.id}>
          <th className="overlay-name" scope="row" title={`${row.name}\n\n${row.desc}`}>
            {row.id}
          </th>
          {builds.map((b) => {
            const overlay = progress.get(b.id)?.get(row.id);
            if (!overlay) {
              // Overlay does not exist in this build (or build not tracked).
              return <td key={b.id} className="cell empty" />;
            }
            return (
              <td
                key={b.id}
                className="cell"
                style={heatStyle(overlay.codePercent)}
                title={`${b.id} / ${row.id}: ${overlay.codePercent.toFixed(2)}% code`}
              >
                {formatPercent(overlay.codePercent)}
              </td>
            );
          })}
        </tr>
      ))}
    </>
  );
}
