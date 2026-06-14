import { useEffect, useState } from "react";
import { builds } from "./data/builds";
import { fetchVersionProgress, VersionProgress } from "./lib/decompDev";
import { buildOverlayRows, OverlayRow } from "./lib/overlays";
import { ProgressTable } from "./components/ProgressTable";

const HEADER_LINKS = [
  { name: "Source Code", url: "https://github.com/xeeynamo/sotn-decomp" },
  { name: "Discord Server", url: "https://sotn-discord.xee.dev" },
  { name: "decomp.dev Progress", url: "https://decomp.dev/Xeeynamo/sotn-decomp" },
  { name: "SOTN Wiki", url: "https://www.sotn.fun" },
];

type LoadState =
  | { status: "loading" }
  | { status: "error"; message: string }
  | {
    status: "ready";
    progress: Map<string, VersionProgress>;
    rows: OverlayRow[];
  };

export function App() {
  const [state, setState] = useState<LoadState>({ status: "loading" });

  useEffect(() => {
    let cancelled = false;

    (async () => {
      try {
        // Fetch every tracked build in parallel; untracked builds resolve to
        // an empty map without a network call.
        const entries = await Promise.all(
          builds.map(async (b) => {
            const data = b.decompDevVersion
              ? await fetchVersionProgress(b.decompDevVersion)
              : (new Map() as VersionProgress);
            // Surface overlays that ship in this build but are not yet in the
            // report as 0% (rather than an empty "does not exist" cell).
            for (const id of b.knownExtraOverlays ?? []) {
              if (!data.has(id)) {
                data.set(id, { codePercent: 0, totalCode: 0 });
              }
            }
            return [b.id, data] as const;
          }),
        );
        if (cancelled) {
          return;
        }
        const progress = new Map(entries);
        const rows = buildOverlayRows([...progress.values()]);
        setState({ status: "ready", progress, rows });
      } catch (err) {
        if (!cancelled) {
          setState({
            status: "error",
            message: err instanceof Error ? err.message : String(err),
          });
        }
      }
    })();

    return () => {
      cancelled = true;
    };
  }, []);

  return (
    <div className="app">
      <header className="app-header">
        <h1>Castlevania: Symphony of the Night decompilation</h1>
        <nav className="links">
          {HEADER_LINKS.map((l) => (
            <a key={l.url} href={l.url} target="_blank" rel="noopener noreferrer">
              {l.name}
            </a>
          ))}
        </nav>
      </header>

      <main>
        {state.status === "loading" && <p className="status">Loading progress…</p>}
        {state.status === "error" && (
          <p className="status error">Failed to load progress: {state.message}</p>
        )}
        {state.status === "ready" && (
          <ProgressTable builds={builds} rows={state.rows} progress={state.progress} />
        )}
      </main>

      <footer className="app-footer">
        <p>
          Data from{" "}
          <a href="https://decomp.dev/Xeeynamo/sotn-decomp" target="_blank" rel="noopener noreferrer">
            decomp.dev
          </a>
        </p>
      </footer>
    </div>
  );
}
