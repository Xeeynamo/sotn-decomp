// Hand-maintained metadata for the progress table.
//
// This is intentionally the ONLY place where game builds and overlay
// names/descriptions live. The actual per-overlay percentages and the list of
// which overlays exist in each build are derived entirely from the decomp.dev
// reports at runtime (see ../lib/decompDev.ts), so adding a newly imported
// overlay requires no change here unless you want a nicer name/description.

export interface Build {
  /** Short id shown in the table header (uppercased). */
  id: string;
  /** decomp.dev version slug to query, or null when not yet tracked there. */
  decompDevVersion: string | null;
  /** Full human readable name, shown on hover. */
  name: string;
  /** Longer description, shown on hover. */
  description: string;
  /**
   * Overlay ids that are known to exist in this build's game data but that
   * decomp.dev does not yet report (e.g. not split into the build config).
   * They render as 0% instead of an empty cell. Keep this minimal: only add an
   * id when the binary genuinely ships in the build but is missing from the
   * report. Anything decomp.dev already reports does not belong here.
   */
  knownExtraOverlays?: string[];
}

// Columns are rendered left to right in this order. Builds with a null
// decompDevVersion render as an entirely empty column (a visible roadmap of
// what is coming) until decomp.dev starts serving a report for them.
export const builds: Build[] = [
  {
    id: "US",
    decompDevVersion: "us",
    name: "PlayStation 1 (US)",
    description: "Original North American PlayStation release. The most complete build.",
    // RBO8 (Dracula) ships in the US disk (BOSS/RBO8/RBO8.BIN) but is not yet
    // in the US decomp.dev report.
    knownExtraOverlays: ["rbo8"],
  },
  {
    id: "HD",
    decompDevVersion: "hd",
    name: "PlayStation 1 Debug",
    description:
      "Debug build of the PlayStation 1 game (extracted from the PSP hdbin). " +
      "All PSP builds ship an identical hdbin, so it is reported only once. " +
      "Contains extra debug overlays not present in retail builds.",
  },
  {
    id: "PSPEU",
    decompDevVersion: "pspeu",
    name: "PlayStation Portable (EU)",
    description:
      "PSP European release. The same code also powers the Android, iOS and " +
      "Castlevania Requiem (PS4) ports.",
  },
  {
    id: "SATURN",
    decompDevVersion: "saturn",
    name: "Sega Saturn",
    description: "Sega Saturn release, with Saturn-exclusive areas and content.",
  },
  {
    id: "JP10",
    decompDevVersion: null,
    name: "PlayStation 1 (Japan 1.0)",
    description: "Original Japanese PlayStation release, revision 1.0.",
  },
  {
    id: "JP11",
    decompDevVersion: null,
    name: "PlayStation 1 (Japan 1.1)",
    description: "Japanese PlayStation release, revision 1.1.",
  },
  {
    id: "JP12",
    decompDevVersion: null,
    name: "PlayStation 1 (Japan 1.2)",
    description: "Japanese PlayStation release, revision 1.2.",
  },
  {
    id: "EU",
    decompDevVersion: null,
    name: "PlayStation 1 (Europe)",
    description: "European PlayStation release.",
  },
  {
    id: "HK",
    decompDevVersion: null,
    name: "PlayStation 1 (Hong Kong)",
    description: "Hong Kong PlayStation release.",
  },
  {
    id: "USPROTO",
    decompDevVersion: null,
    name: "PlayStation 1 (E3 prototype)",
    description: "Early US prototype shown at E3.",
  },
  {
    id: "PSPJP",
    decompDevVersion: null,
    name: "PlayStation Portable (Japan)",
    description: "PSP Japanese release.",
  },
  {
    id: "PSPKO",
    decompDevVersion: null,
    name: "PlayStation Portable (Korea)",
    description: "PSP Korean release.",
  },
];

// Overlay categories, in the order their sections appear vertically.
export type CategoryId =
  | "player"
  | "stage"
  | "rstage"
  | "boss"
  | "rboss"
  | "weapon"
  | "familiar"
  | "debug";

export interface Category {
  id: CategoryId;
  name: string;
}

export const categories: Category[] = [
  { id: "player", name: "Playable / Engine" },
  { id: "stage", name: "Stages" },
  { id: "rstage", name: "Reverse Stages" },
  { id: "boss", name: "Bosses" },
  { id: "rboss", name: "Reverse Bosses" },
  { id: "weapon", name: "Weapons" },
  { id: "familiar", name: "Familiars" },
  { id: "debug", name: "Debug / Test" },
];

export interface OverlayMeta {
  name: string;
  desc: string;
}

// Optional friendly names/descriptions per overlay id (the canonical overlay
// id is the collapsed form, e.g. "dra", "are", "rbo3", "tt_000", "weapon").
// Anything missing here falls back to the raw overlay id, so the table never
// breaks when a brand new overlay shows up in a report.
export const overlayMeta: Record<string, OverlayMeta> = {
  // Playable characters and engine
  dra: { name: "DRA.BIN", desc: "Game engine and Alucard" },
  ric: { name: "BIN/RIC.BIN", desc: "Richter Belmont program" },
  maria: { name: "PSPBIN/MARIA.BIN", desc: "Maria Renard program (PSP only)" },
  main: { name: "Main executable", desc: "Boot / main program" },
  sel: { name: "ST/SEL/SEL.BIN", desc: "Title and map selection screen" },
  fname: { name: "FNAME.BIN", desc: "Debug build overlay (purpose unknown)" },
  sd: { name: "SD.BIN", desc: "Debug build overlay (purpose unknown)" },
  tek: { name: "TEK.BIN", desc: "Debug build overlay (purpose unknown)" },

  // Stages
  are: { name: "ST/ARE/ARE.BIN", desc: "Colosseum" },
  cat: { name: "ST/CAT/CAT.BIN", desc: "Catacombs" },
  cen: { name: "ST/CEN/CEN.BIN", desc: "Center Cube" },
  chi: { name: "ST/CHI/CHI.BIN", desc: "Abandoned Mine" },
  dai: { name: "ST/DAI/DAI.BIN", desc: "Royal Chapel" },
  dre: { name: "ST/DRE/DRE.BIN", desc: "Nightmare (dream sequence)" },
  lib: { name: "ST/LIB/LIB.BIN", desc: "Long Library" },
  no0: { name: "ST/NO0/NO0.BIN", desc: "Marble Gallery" },
  no1: { name: "ST/NO1/NO1.BIN", desc: "Outer Wall" },
  no2: { name: "ST/NO2/NO2.BIN", desc: "Olrox's Quarters" },
  no3: { name: "ST/NO3/NO3.BIN", desc: "Entrance (first visit)" },
  no4: { name: "ST/NO4/NO4.BIN", desc: "Underground Caverns" },
  np3: { name: "ST/NP3/NP3.BIN", desc: "Entrance (second visit)" },
  nz0: { name: "ST/NZ0/NZ0.BIN", desc: "Alchemy Laboratory" },
  nz1: { name: "ST/NZ1/NZ1.BIN", desc: "Clock Tower" },
  st0: { name: "ST/ST0/ST0.BIN", desc: "Prologue (Final Stage: Bloodlines)" },
  top: { name: "ST/TOP/TOP.BIN", desc: "Castle Keep" },
  wrp: { name: "ST/WRP/WRP.BIN", desc: "Warp rooms" },

  // Reverse stages
  rare: { name: "ST/RARE/RARE.BIN", desc: "Reverse Colosseum" },
  rcat: { name: "ST/RCAT/RCAT.BIN", desc: "Floating Catacombs" },
  rcen: { name: "ST/RCEN/RCEN.BIN", desc: "Reverse Center Cube" },
  rchi: { name: "ST/RCHI/RCHI.BIN", desc: "Cave" },
  rdai: { name: "ST/RDAI/RDAI.BIN", desc: "Anti-Chapel" },
  rlib: { name: "ST/RLIB/RLIB.BIN", desc: "Forbidden Library" },
  rno0: { name: "ST/RNO0/RNO0.BIN", desc: "Black Marble Gallery" },
  rno1: { name: "ST/RNO1/RNO1.BIN", desc: "Reverse Outer Wall" },
  rno2: { name: "ST/RNO2/RNO2.BIN", desc: "Death Wing's Lair" },
  rno3: { name: "ST/RNO3/RNO3.BIN", desc: "Reverse Entrance" },
  rno4: { name: "ST/RNO4/RNO4.BIN", desc: "Reverse Caverns" },
  rnz0: { name: "ST/RNZ0/RNZ0.BIN", desc: "Necromancy Laboratory" },
  rnz1: { name: "ST/RNZ1/RNZ1.BIN", desc: "Reverse Clock Tower" },
  rtop: { name: "ST/RTOP/RTOP.BIN", desc: "Reverse Castle Keep" },
  rwrp: { name: "ST/RWRP/RWRP.BIN", desc: "Reverse warp rooms" },

  // Bosses
  bo0: { name: "BOSS/BO0/BO0.BIN", desc: "Boss: Cerberus" },
  bo1: { name: "BOSS/BO1/BO1.BIN", desc: "Boss: Slogra and Gaibon" },
  bo2: { name: "BOSS/BO2/BO2.BIN", desc: "Boss: Doppleganger Lv.10" },
  bo3: { name: "BOSS/BO3/BO3.BIN", desc: "Boss: Olrox" },
  bo4: { name: "BOSS/BO4/BO4.BIN", desc: "Boss: Granfaloon" },
  bo5: { name: "BOSS/BO5/BO5.BIN", desc: "Boss: Minotaur and Werewolf" },
  bo6: { name: "BOSS/BO6/BO6.BIN", desc: "Boss: Richter (Olrox's Quarters)" },
  bo7: { name: "BOSS/BO7/BO7.BIN", desc: "Boss: Scylla" },
  mar: { name: "BOSS/MAR/MAR.BIN", desc: "Maria cutscene (clock room)" },

  // Reverse bosses
  rbo0: { name: "BOSS/RBO0/RBO0.BIN", desc: "Reverse boss: Beelzebub" },
  rbo1: { name: "BOSS/RBO1/RBO1.BIN", desc: "Reverse boss: Death" },
  rbo2: { name: "BOSS/RBO2/RBO2.BIN", desc: "Reverse boss: Medusa" },
  rbo3: { name: "BOSS/RBO3/RBO3.BIN", desc: "Reverse boss: Creature" },
  rbo4: { name: "BOSS/RBO4/RBO4.BIN", desc: "Reverse boss: Doppleganger Lv.40" },
  rbo5: { name: "BOSS/RBO5/RBO5.BIN", desc: "Reverse boss: Akmodan II" },
  rbo6: { name: "BOSS/RBO6/RBO6.BIN", desc: "Reverse boss: Galamoth" },
  rbo7: { name: "BOSS/RBO7/RBO7.BIN", desc: "Reverse boss: The Trio" },
  rbo8: { name: "BOSS/RBO8/RBO8.BIN", desc: "Reverse boss: Dracula" },

  // Weapons (single binary holding every sub-weapon program)
  weapon: { name: "BIN/WEAPON0.BIN", desc: "Weapons, shields and consumable programs" },

  // Familiars
  tt_000: { name: "SERVANT/TT_000.BIN", desc: "Familiar: Bat" },
  tt_001: { name: "SERVANT/TT_001.BIN", desc: "Familiar: Ghost" },
  tt_002: { name: "SERVANT/TT_002.BIN", desc: "Familiar: Faerie" },
  tt_003: { name: "SERVANT/TT_003.BIN", desc: "Familiar: Demon" },
  tt_004: { name: "SERVANT/TT_004.BIN", desc: "Familiar: Sword" },
  tt_005: { name: "SERVANT/TT_005.BIN", desc: "Familiar: Yousei (Nose Demon)" },
  tt_006: { name: "SERVANT/TT_006.BIN", desc: "Familiar: unused" },

  // Debug / test stages
  mad: { name: "ST/MAD/MAD.BIN", desc: "Debug room" },
  te1: { name: "ST/TE1/TE1.BIN", desc: "Test stage 1" },
  te2: { name: "ST/TE2/TE2.BIN", desc: "Test stage 2" },
  te3: { name: "ST/TE3/TE3.BIN", desc: "Test stage 3" },
  te4: { name: "ST/TE4/TE4.BIN", desc: "Test stage 4" },
  te5: { name: "ST/TE5/TE5.BIN", desc: "Test stage 5" },
};
