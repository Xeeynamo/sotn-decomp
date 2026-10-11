use regex::Regex;
use std::collections::HashMap;
use std::path::Path;
use std::sync::{Arc, LazyLock, Mutex};

use crate::c::{enum_entries, parse_enum_entries, parse_int};
use crate::file_transformer::FileTransformer;

const ANIMSET_OVL_FLAG: i64 = 0x8000;
const PAL_UNK_FLAG: i64 = 0x8000;
const PAL_NONE: &str = "PAL_NONE";
const FORMAT_OFF: &str = "// clang-format off";
const FORMAT_ON: &str = "// clang-format on";

/// Names shared by every overlay.
struct GlobalNames {
    /// `EnemyIds` from enemies.h
    enemies: HashMap<i64, String>,
    /// `PaletteIndices` from palettes.h, minus the values with several names
    palettes: HashMap<i64, String>,
}

/// `process_directory` builds the transformers once per directory, so read
/// the headers once and share the result.
static GLOBAL_NAMES: LazyLock<Mutex<Option<Arc<GlobalNames>>>> =
    LazyLock::new(|| Mutex::new(None));

/// Rewrites each `EInit` definition as one line, naming palettes from the
/// overlay's `enum Palettes` and enemies from `enum EnemyIds`.
pub struct EInitTransformer {
    names: Arc<GlobalNames>,
}

impl EInitTransformer {
    pub fn new() -> Self {
        Self::new_with_include_dir("include")
    }

    fn new_with_include_dir(dir: &str) -> Self {
        let mut cached = GLOBAL_NAMES.lock().unwrap();
        if cached.is_none() {
            let dir = Path::new(dir);
            let enemies = enum_entries(&dir.join("enemies.h"), "EnemyIds").expect("enemies.h");
            let palettes =
                enum_entries(&dir.join("palettes.h"), "PaletteIndices").expect("palettes.h");
            *cached = Some(Arc::new(GlobalNames {
                enemies: first_by_value(&enemies),
                palettes: unique_by_value(&palettes),
            }));
        }
        Self {
            names: cached.clone().unwrap(),
        }
    }
}

/// Invert an enum, the first declared name wins when a value has several.
fn first_by_value(entries: &[(String, i64)]) -> HashMap<i64, String> {
    let mut names = HashMap::new();
    for (name, value) in entries {
        names.entry(*value).or_insert_with(|| name.clone());
    }
    names
}

/// Invert an enum, dropping the values that have several names.
fn unique_by_value(entries: &[(String, i64)]) -> HashMap<i64, String> {
    let mut counts: HashMap<i64, usize> = HashMap::new();
    for (_, value) in entries {
        *counts.entry(*value).or_insert(0) += 1;
    }
    entries
        .iter()
        .filter(|(_, value)| counts[value] == 1)
        .map(|(name, value)| (*value, name.clone()))
        .collect()
}

static DEFINITION_START: LazyLock<Regex> =
    LazyLock::new(|| Regex::new(r"^(static\s+)?EInit\s+(\w+)\s*=\s*\{(.*)$").unwrap());
static FORMAT_MARKER: LazyLock<Regex> =
    LazyLock::new(|| Regex::new(r"^\s*//\s*clang-format\s+(on|off)\b").unwrap());
static INCLUDE: LazyLock<Regex> =
    LazyLock::new(|| Regex::new(r#"^\s*#\s*include\s+"([^"]+)""#).unwrap());
static ANIMSET: LazyLock<Regex> =
    LazyLock::new(|| Regex::new(r"^ANIMSET_(OVL|DRA)\((.+)\)$").unwrap());
static PAL_FLAG: LazyLock<Regex> =
    LazyLock::new(|| Regex::new(r"^PAL_FLAG\((.+)\)$").unwrap());

/// The longest definition clang-format produces spans three lines.
const MAX_DEFINITION_LINES: usize = 4;

/// An `EInit` definition read from one or more source lines.
struct Definition {
    line_count: usize,
    is_static: bool,
    name: String,
    fields: Vec<String>,
    /// what follows the closing brace: `;` and maybe a comment
    tail: String,
}

impl Definition {
    /// Read the definition starting at `lines[0]`, `None` if there is none or
    /// it is not a five field initializer this lint understands.
    fn read(lines: &[String]) -> Option<Self> {
        let captures = DEFINITION_START.captures(lines.first()?)?;
        let mut text = captures[3].to_string();
        let mut line_count = 1;
        while !text.contains('}') {
            if line_count == MAX_DEFINITION_LINES {
                return None;
            }
            text.push(' ');
            text.push_str(lines.get(line_count)?.trim());
            line_count += 1;
        }
        if lines[..line_count].iter().any(|l| l.contains("sotn-lint-ignore")) {
            return None;
        }

        let (body, tail) = text.split_once('}')?;
        let tail = tail.trim();
        if body.contains("//") || body.contains("/*") || !tail.starts_with(';') {
            return None;
        }

        let mut fields: Vec<String> = body.split(',').map(|f| f.trim().to_string()).collect();
        if fields.last().is_some_and(|f| f.is_empty()) {
            // trailing comma
            fields.pop();
        }
        if fields.len() != 5 || fields.iter().any(|f| f.is_empty()) {
            return None;
        }

        let comment = tail[1..].trim();
        Some(Self {
            line_count,
            is_static: captures.get(1).is_some(),
            name: captures[2].to_string(),
            fields,
            tail: if comment.is_empty() {
                ";".to_string()
            } else {
                format!("; {}", comment)
            },
        })
    }
}

impl EInitTransformer {
    fn format_definition(&self, def: &Definition, overlay: &HashMap<i64, String>) -> String {
        format!(
            "{}EInit {} = {{{}, {}, {}, {}, {}}}{}",
            if def.is_static { "static " } else { "" },
            def.name,
            format_anim_set(&def.fields[0]),
            format_byte(&def.fields[1]),
            format_byte(&def.fields[2]),
            self.format_palette(&def.fields[3], overlay),
            self.format_enemy(&def.fields[4]),
            def.tail
        )
    }

    fn format_palette(&self, field: &str, overlay: &HashMap<i64, String>) -> String {
        if let Some(value) = parse_int(field) {
            let name = self.palette_name(value & !PAL_UNK_FLAG, overlay);
            return if value & PAL_UNK_FLAG != 0 {
                format!("PAL_FLAG({})", name)
            } else {
                name
            };
        }
        if let Some(captures) = PAL_FLAG.captures(field) {
            return format!("PAL_FLAG({})", self.format_palette(&captures[1], overlay));
        }
        // palettes.h spells the zero palette PAL_NULL, overlays use PAL_NONE
        if field == "PAL_NULL" {
            return PAL_NONE.to_string();
        }
        field.to_string()
    }

    fn palette_name(&self, value: i64, overlay: &HashMap<i64, String>) -> String {
        if value == 0 {
            return PAL_NONE.to_string();
        }
        overlay
            .get(&value)
            .or_else(|| self.names.palettes.get(&value))
            .cloned()
            .unwrap_or_else(|| format!("0x{:03X}", value))
    }

    fn format_enemy(&self, field: &str) -> String {
        match parse_int(field) {
            Some(value) => self
                .names
                .enemies
                .get(&value)
                .cloned()
                .unwrap_or_else(|| format!("0x{:03X}", value)),
            None => field.to_string(),
        }
    }

    fn transform_lines(&self, overlay: &HashMap<i64, String>, lines: Vec<String>) -> Vec<String> {
        let mut out: Vec<String> = Vec::with_capacity(lines.len() + 2);
        let mut format_off = false;
        // this lint turned formatting off and the file never said otherwise
        let mut owes_format_on = false;
        let mut last_definition_end = None;

        let mut i = 0;
        while i < lines.len() {
            if let Some(captures) = FORMAT_MARKER.captures(&lines[i]) {
                format_off = &captures[1] == "off";
                owes_format_on = false;
            } else if let Some(def) = Definition::read(&lines[i..]) {
                if !format_off {
                    out.push(FORMAT_OFF.to_string());
                    format_off = true;
                    owes_format_on = true;
                }
                out.push(self.format_definition(&def, overlay));
                last_definition_end = Some(out.len());
                i += def.line_count;
                continue;
            }
            out.push(lines[i].clone());
            i += 1;
        }

        // Do not leave the code after the definitions unformatted.
        if let (true, Some(end)) = (owes_format_on, last_definition_end) {
            if out[end..].iter().any(|line| is_code(line)) {
                out.insert(end, FORMAT_ON.to_string());
            }
        }

        out
    }
}

fn is_code(line: &str) -> bool {
    let line = line.trim();
    !line.is_empty() && !line.starts_with("#endif")
}

fn format_anim_set(field: &str) -> String {
    if let Some(value) = parse_int(field) {
        return if value & ANIMSET_OVL_FLAG != 0 {
            format!("ANIMSET_OVL({})", value & !ANIMSET_OVL_FLAG)
        } else {
            format!("ANIMSET_DRA({})", value)
        };
    }
    if let Some(captures) = ANIMSET.captures(field) {
        if let Some(value) = parse_int(&captures[2]) {
            return format!("ANIMSET_{}({})", &captures[1], value);
        }
    }
    field.to_string()
}

fn format_byte(field: &str) -> String {
    match parse_int(field) {
        Some(value) => format!("0x{:02X}", value),
        None => field.to_string(),
    }
}

/// The `enum Palettes` of the first header the file includes that has one.
fn overlay_palettes(path: &Path, lines: &[String]) -> HashMap<i64, String> {
    let dir = path.parent().unwrap_or(Path::new("."));
    for line in lines {
        let Some(captures) = INCLUDE.captures(line) else {
            continue;
        };
        let header = dir.join(&captures[1]);
        let Ok(text) = std::fs::read_to_string(&header) else {
            continue;
        };
        match parse_enum_entries(&text, "Palettes") {
            Ok(Some(entries)) => return first_by_value(&entries),
            Ok(None) => (),
            Err(msg) => eprintln!("{}: \x1b[31m{}\x1b[0m", header.display(), msg),
        }
    }
    HashMap::new()
}

impl FileTransformer for EInitTransformer {
    fn transform_file(&self, path: &Path, lines: Vec<String>) -> Vec<String> {
        if !lines.iter().any(|line| DEFINITION_START.is_match(line)) {
            return lines;
        }
        let overlay = overlay_palettes(path, &lines);
        self.transform_lines(&overlay, lines)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    const INCLUDE_DIR: &str = "../../../include";

    fn overlay(header: &str) -> HashMap<i64, String> {
        first_by_value(&parse_enum_entries(header, "Palettes").unwrap().unwrap())
    }

    fn transform_with(header: &str, source: &str) -> String {
        let lines = source.lines().map(str::to_string).collect();
        EInitTransformer::new_with_include_dir(INCLUDE_DIR)
            .transform_lines(&overlay(header), lines)
            .join("\n")
    }

    /// Transform lines that already sit under a `// clang-format off`.
    fn transform(header: &str, source: &str) -> String {
        let out = transform_with(header, &format!("{}\n{}", FORMAT_OFF, source));
        out.strip_prefix(FORMAT_OFF).unwrap().trim_start().to_string()
    }

    const NO_PALETTES: &str = "enum Palettes { PAL_NONE };";

    #[test]
    fn test_raw_anim_set() {
        // from src/st/nz0/e_init.c
        assert_eq!(
            transform(
                "enum Palettes { PAL_NONE, PAL_BONE_SCIMITAR = 0x204 };",
                "EInit g_EInitBoneScimitar = {0x8003, 0x0001, 0x004D, 0x0204, 0x0069};"
            ),
            "EInit g_EInitBoneScimitar = {ANIMSET_OVL(3), 0x01, 0x4D, PAL_BONE_SCIMITAR, ENEMY_BONE_SCIMITAR};"
        );
        // from src/boss/mar/e_init.c
        assert_eq!(
            transform(NO_PALETTES, "EInit g_EInitBreakable = {0x0003, 0x0000, 0x0000, 0x0000, 0x0000};"),
            "EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};"
        );
    }

    #[test]
    fn test_anim_set_macro_is_kept() {
        // from src/st/tek/e_init.c: an overlay set with index zero
        let line = "EInit g_EInitGraveKeeperHitbox = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_GRAVE_KEEPER_HITBOX};";
        assert_eq!(transform(NO_PALETTES, line), line);
        assert_eq!(
            transform(NO_PALETTES, "EInit g_EInitParticle = {ANIMSET_DRA(3), 0, 0, 0, 2};"),
            "EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};"
        );
    }

    #[test]
    fn test_anim_set_argument_is_decimal() {
        // from src/st/are/e_init.c
        assert_eq!(
            transform(NO_PALETTES, "EInit g_EInitX = {ANIMSET_OVL(0x0D), 0x01, 0x4D, 0x000, 0x002};"),
            "EInit g_EInitX = {ANIMSET_OVL(13), 0x01, 0x4D, PAL_NONE, ENEMY_PARTICLE};"
        );
        assert_eq!(
            transform(NO_PALETTES, "EInit g_EInitX = {0x801E, 0, 0, 0, 2};"),
            "EInit g_EInitX = {ANIMSET_OVL(30), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};"
        );
    }

    #[test]
    fn test_decimal_fields() {
        // from src/st/no3/e_init.c
        assert_eq!(
            transform(
                "enum Palettes { PAL_NONE, PAL_BONE_SCIMITAR = 0x2C5 };",
                "EInit g_EInitBoneScimitar = {0x8002, 1, 0x48, 0x2c5, 105};"
            ),
            "EInit g_EInitBoneScimitar = {ANIMSET_OVL(2), 0x01, 0x48, PAL_BONE_SCIMITAR, ENEMY_BONE_SCIMITAR};"
        );
        // from src/st/dai/e_init.c
        assert_eq!(
            transform(
                "enum Palettes { PAL_NONE = 0, PAL_SPECTRAL_SWORD = 0x234 };",
                "EInit g_EInitSpectralSwordAura = {ANIMSET_OVL(13), 0, 81, PAL_SPECTRAL_SWORD, 0x002};"
            ),
            "EInit g_EInitSpectralSwordAura = {ANIMSET_OVL(13), 0x00, 0x51, PAL_SPECTRAL_SWORD, ENEMY_PARTICLE};"
        );
    }

    #[test]
    fn test_wrapped_definition_is_joined() {
        // from src/st/no2/e_init.c
        assert_eq!(
            transform(
                "enum Palettes { PAL_NONE = 0, PAL_VALHALLA_KNIGHT = 0x207 };",
                "EInit g_EInitValhallaKnight = {\n    ANIMSET_OVL(5), 0x01, 0x4C, PAL_VALHALLA_KNIGHT, 0x085};"
            ),
            "EInit g_EInitValhallaKnight = {ANIMSET_OVL(5), 0x01, 0x4C, PAL_VALHALLA_KNIGHT, ENEMY_VALHALLA_KNIGHT};"
        );
        // from src/boss/rbo3/e_init.c: trailing comma, brace on its own line
        assert_eq!(
            transform(
                NO_PALETTES,
                "EInit g_EInitInteractable = {\n    ANIMSET_DRA(0), 0x0000, 0x0000, PAL_NULL, 0x0005,\n};\nEInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x0000, 0x0000, PAL_NULL, 0x0002};"
            ),
            "EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};\nEInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};"
        );
    }

    #[test]
    fn test_palette_flag() {
        // from src/st/rwrp/e_init.c
        assert_eq!(
            transform(
                "enum Palettes { PAL_NONE, PAL_WARP = 0x2E8 };",
                "EInit g_EInitWarp = {ANIMSET_OVL(1), 0, 0x00, 0x82E8, 5};"
            ),
            "EInit g_EInitWarp = {ANIMSET_OVL(1), 0x00, 0x00, PAL_FLAG(PAL_WARP), ENEMY_INTERACTABLE};"
        );
        assert_eq!(
            transform(NO_PALETTES, "EInit g_EInitX = {ANIMSET_OVL(1), 0, 0, PAL_FLAG(0x2E8), 5};"),
            "EInit g_EInitX = {ANIMSET_OVL(1), 0x00, 0x00, PAL_FLAG(0x2E8), ENEMY_INTERACTABLE};"
        );
    }

    #[test]
    fn test_palette_from_palettes_h() {
        // from src/st/lib/e_init.c: 0x1B0 is not an overlay palette
        assert_eq!(
            transform(NO_PALETTES, "EInit g_EInitX = {ANIMSET_DRA(0), 0, 0, 0x81B0, 5};"),
            "EInit g_EInitX = {ANIMSET_DRA(0), 0x00, 0x00, PAL_FLAG(PAL_UNK_1B0), ENEMY_INTERACTABLE};"
        );
        // the overlay's own name wins over the one in palettes.h
        assert_eq!(
            transform(
                "enum Palettes { PAL_NONE, PAL_DAMAGE = 0x1B0 };",
                "EInit g_EInitX = {ANIMSET_DRA(0), 0, 0, 0x1B0, 5};"
            ),
            "EInit g_EInitX = {ANIMSET_DRA(0), 0x00, 0x00, PAL_DAMAGE, ENEMY_INTERACTABLE};"
        );
        // 0x140 is both PAL_SERVANT and PAL_RIC_WHIP
        assert_eq!(
            transform(NO_PALETTES, "EInit g_EInitX = {ANIMSET_DRA(0), 0, 0, 0x140, 5};"),
            "EInit g_EInitX = {ANIMSET_DRA(0), 0x00, 0x00, 0x140, ENEMY_INTERACTABLE};"
        );
    }

    #[test]
    fn test_first_declared_palette_wins() {
        // from src/st/are/are.h
        let header = "enum Palettes { PAL_NONE, PAL_PLATE_LORD_UNK3 = 0x228, PAL_BREAKABLE_TORCH_A = 0x228 };";
        assert_eq!(
            transform(header, "EInit g_EInitX = {ANIMSET_OVL(1), 0, 0, 0x228, 5};"),
            "EInit g_EInitX = {ANIMSET_OVL(1), 0x00, 0x00, PAL_PLATE_LORD_UNK3, ENEMY_INTERACTABLE};"
        );
        // a name picked by hand is not replaced
        let line = "EInit g_EInitX = {ANIMSET_OVL(1), 0x00, 0x00, PAL_BREAKABLE_TORCH_A, ENEMY_INTERACTABLE};";
        assert_eq!(transform(header, line), line);
    }

    #[test]
    fn test_unknown_values_stay_numeric() {
        assert_eq!(
            transform(NO_PALETTES, "EInit g_EInitX = {ANIMSET_OVL(1), 0, 0x48, 0x2ff, 0xFFF};"),
            "EInit g_EInitX = {ANIMSET_OVL(1), 0x00, 0x48, 0x2FF, 0xFFF};"
        );
    }

    #[test]
    fn test_static_and_trailing_comment() {
        // from src/st/no0/e_init.c
        assert_eq!(
            transform(NO_PALETTES, "EInit D_us_80180AC4 = {ANIMSET_DRA(3), 0x00, 0x48, 0x000, 0x05C};    // unused"),
            "EInit D_us_80180AC4 = {ANIMSET_DRA(3), 0x00, 0x48, PAL_NONE, ENEMY_UNK_5C}; // unused"
        );
        assert_eq!(
            transform(NO_PALETTES, "static  EInit  x={0,0,0,0,3};"),
            "static EInit x = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};"
        );
    }

    #[test]
    fn test_other_lines_left_alone() {
        for line in [
            "extern EInit g_EInitCommon;",
            "EInit g_EInitDamageNum;",
            "// EInit D_us_801808FC = {ANIMSET_OVL(8), 0x00, 0x50, 0x256, 0x005};",
            "EInit g_EInitX = {ANIMSET_OVL(1), 0, 0, 0x228};",
            "EInit g_EInitX = {ANIMSET_OVL(1), 0, 0, 0x228, 5}; // sotn-lint-ignore",
            "EInit g_EInitX = {ANIMSET_OVL(1), 0, /* why */ 0, 0x228, 5};",
            "    InitializeEntity(g_EInitCommon);",
        ] {
            assert_eq!(transform_with(NO_PALETTES, line), line);
        }
    }

    #[test]
    fn test_format_off_is_added() {
        assert_eq!(
            transform_with(
                NO_PALETTES,
                "#include \"mad.h\"\n\nEInit g_EInitBreakable = {ANIMSET_OVL(1), 0, 0, 0, 0};\nEInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, 0, 3};"
            ),
            "#include \"mad.h\"\n\n// clang-format off\nEInit g_EInitBreakable = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};\nEInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};"
        );
    }

    #[test]
    fn test_format_on_is_added_before_code() {
        // from src/pc/stages/stage_rno0.c
        assert_eq!(
            transform_with(
                NO_PALETTES,
                "EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, 0, 3};\nEInit g_EInitDamageNum;"
            ),
            "// clang-format off\nEInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};\n// clang-format on\nEInit g_EInitDamageNum;"
        );
        // from src/st/cen/e_init.c: a closing #endif needs no formatting
        assert_eq!(
            transform_with(
                NO_PALETTES,
                "#ifdef VERSION_PSP\nEInit g_EInitUnk = {ANIMSET_DRA(0), 0, 0x00, 0, 0xFFF};\n#endif\n"
            ),
            "#ifdef VERSION_PSP\n// clang-format off\nEInit g_EInitUnk = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, 0xFFF};\n#endif"
        );
    }

    #[test]
    fn test_existing_format_markers_are_respected() {
        let source = "// clang-format off\nEInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};\n// clang-format on\nvoid f(void);";
        assert_eq!(transform_with(NO_PALETTES, source), source);
        // formatting turned back on between two definitions
        assert_eq!(
            transform_with(
                NO_PALETTES,
                "// clang-format off\nEInit a = {0, 0, 0, 0, 3};\n// clang-format on\nEInit b = {0, 0, 0, 0, 3};"
            ),
            "// clang-format off\nEInit a = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};\n// clang-format on\n// clang-format off\nEInit b = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};"
        );
    }

    #[test]
    fn test_idempotent() {
        let source = "#include \"x.h\"\nEInit a = {0x8001, 1,\n    0x48, 0x200, 0x69};\nEInit b = {0, 0, 0, 0, 3};\nint x;";
        let header = "enum Palettes { PAL_NONE, PAL_A = 0x200 };";
        let once = transform_with(header, source);
        assert_eq!(transform_with(header, &once), once);
    }

    #[test]
    fn test_overlay_header_is_found_through_includes() {
        let path = Path::new("../../../src/st/tek/e_init.c");
        let lines = vec!["#include <stage.h>".to_string(), "#include \"tek.h\"".to_string()];
        assert_eq!(overlay_palettes(path, &lines)[&0x200], "PAL_DODO_BIRD");
        // src/st/e_init_common.h includes nothing
        assert!(overlay_palettes(Path::new("../../../src/st/e_init_common.h"), &[]).is_empty());
    }

    #[test]
    fn test_reference_file_is_stable() {
        let path = Path::new("../../../src/st/tek/e_init.c");
        let lines: Vec<String> = std::fs::read_to_string(path)
            .unwrap()
            .lines()
            .map(str::to_string)
            .collect();
        let out = EInitTransformer::new_with_include_dir(INCLUDE_DIR).transform_file(path, lines.clone());
        assert_eq!(out, lines);
    }
}
