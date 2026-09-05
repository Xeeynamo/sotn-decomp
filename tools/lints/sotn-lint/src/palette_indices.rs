use lazy_static::lazy_static;
use regex::Regex;
use std::collections::HashMap;
use std::path::Path;
use std::sync::{LazyLock, Mutex};

use crate::c::enum_values;
use crate::line_transformer::LineTransformer;

/// `process_directory` builds the transformers once per directory, so parse the
/// header once and share the result.
static PALETTE_INDICES: LazyLock<Mutex<Option<HashMap<i64, String>>>> =
    LazyLock::new(|| Mutex::new(None));

pub struct PaletteIndicesTransformer {
    palettes: HashMap<i64, String>,
}

impl PaletteIndicesTransformer {
    pub fn new() -> Self {
        Self::new_with_header_path("include/palettes.h")
    }

    fn new_with_header_path(path: &str) -> Self {
        let mut cached = PALETTE_INDICES.lock().unwrap();
        if cached.is_none() {
            let names = enum_values(Path::new(path), "PaletteIndices").expect("palettes.h");
            *cached = Some(by_value(&names));
        }
        Self {
            palettes: cached.clone().unwrap(),
        }
    }
}

/// Invert the enum's name -> value map. `PaletteIndices` has aliases
/// (`PAL_SERVANT` and `PAL_RIC_WHIP` are both 0x140), and nothing in the line
/// tells us which one the author meant, so ambiguous values are dropped and
/// left as hex.
fn by_value(names: &HashMap<String, i64>) -> HashMap<i64, String> {
    let mut counts: HashMap<i64, usize> = HashMap::new();
    for value in names.values() {
        *counts.entry(*value).or_insert(0) += 1;
    }

    names
        .iter()
        .filter(|(_, value)| counts[value] == 1)
        // PAL_NULL is 0x0, but a zero palette is just as often "no palette".
        .filter(|(_, value)| **value != 0)
        .map(|(name, value)| (*value, name.clone()))
        .collect()
}

lazy_static! {
    // The palette index inside an already flagged value.
    static ref PAL_FLAG_REGEX: Regex = Regex::new(r"PAL_FLAG\(0x(?P<value>[0-9A-Fa-f]+)\)").unwrap();

    // An unflagged palette index assigned to or compared against an identifier
    // ending in `palette`/`Palette`. `&` is excluded: it masks rather than
    // names an index.
    static ref PALETTE_REGEX: Regex = Regex::new(
        r"(?P<lhs>\b[0-9A-Za-z_]*[Pp]alette\b\s*(?:==|!=|<=|>=|\|=|=|<|>)\s*)0x(?P<value>[0-9A-Fa-f]+)(?P<tail>[;,)\s]|$)"
    )
    .unwrap();
}

impl PaletteIndicesTransformer {
    fn name_of(&self, hex: &str) -> Option<&String> {
        i64::from_str_radix(hex, 16)
            .ok()
            .and_then(|value| self.palettes.get(&value))
    }
}

impl LineTransformer for PaletteIndicesTransformer {
    fn transform_line(&self, line: &str) -> String {
        let line = PAL_FLAG_REGEX.replace_all(line, |caps: &regex::Captures| {
            match self.name_of(&caps["value"]) {
                Some(name) => format!("PAL_FLAG({})", name),
                None => caps[0].to_string(),
            }
        });

        PALETTE_REGEX
            .replace_all(&line, |caps: &regex::Captures| {
                match self.name_of(&caps["value"]) {
                    Some(name) => format!("{}{}{}", &caps["lhs"], name, &caps["tail"]),
                    None => caps[0].to_string(),
                }
            })
            .to_string()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn make_transformer() -> PaletteIndicesTransformer {
        PaletteIndicesTransformer::new_with_header_path("../../../include/palettes.h")
    }

    fn transform(line: &str) -> String {
        make_transformer().transform_line(line)
    }

    #[test]
    fn test_enum_parsed() {
        assert!(make_transformer().palettes.len() > 60);
    }

    #[test]
    fn test_descriptive_name_in_pal_flag() {
        // from src/dra/7879C.c, after the PAL_FLAG lint has run
        assert_eq!(
            transform("        (PLAYER.palette == PAL_FLAG(0x10D))) {"),
            "        (PLAYER.palette == PAL_FLAG(PAL_PLAYER_HIDDEN))) {"
        );
    }

    #[test]
    fn test_implicit_enumerator_value() {
        // PAL_FILL_WHITE has no initialiser; it is 0x158 + 7
        assert_eq!(
            transform("        self->palette = PAL_FLAG(0x15F);"),
            "        self->palette = PAL_FLAG(PAL_FILL_WHITE);"
        );
        assert_eq!(
            transform("        self->palette = PAL_FLAG(0x168);"),
            "        self->palette = PAL_FLAG(PAL_CC_GREEN_EFFECT_A);"
        );
    }

    #[test]
    fn test_unk_name_in_pal_flag() {
        // from src/st/rno4/unk_44B0C.c
        assert_eq!(
            transform("            self->palette = PAL_FLAG(0x195);"),
            "            self->palette = PAL_FLAG(PAL_UNK_195);"
        );
    }

    #[test]
    fn test_lowercase_hex() {
        assert_eq!(
            transform("            self->palette = PAL_FLAG(0x19f);"),
            "            self->palette = PAL_FLAG(PAL_UNK_19F);"
        );
    }

    #[test]
    fn test_unflagged_assignment() {
        // from src/weapon/w_043.c
        assert_eq!(
            transform("        self->palette = 0x110;"),
            "        self->palette = PAL_UNK_110;"
        );
    }

    #[test]
    fn test_unflagged_other_palette_field() {
        // from src/weapon/w_026.c
        assert_eq!(
            transform("            self->ext.shield.childPalette = 0x111;"),
            "            self->ext.shield.childPalette = PAL_UNK_111;"
        );
    }

    #[test]
    fn test_unflagged_designated_initializer() {
        assert_eq!(
            transform("     .palette = 0x120,"),
            "     .palette = PAL_RICHTER,"
        );
    }

    #[test]
    fn test_unflagged_comparison() {
        assert_eq!(
            transform("        if (self->palette == 0x128) {"),
            "        if (self->palette == PAL_UNK_128) {"
        );
    }

    #[test]
    fn test_value_outside_enum_left_alone() {
        // 0x200-0x2FF is deliberately not in PaletteIndices
        let line = "        self->palette = PAL_FLAG(0x200);";
        assert_eq!(transform(line), line);
        // stage-local palettes below 0x100 are not in it either
        let line = "        self->palette = PAL_FLAG(0x4F);";
        assert_eq!(transform(line), line);
        let line = "        self->palette = 0x4F;";
        assert_eq!(transform(line), line);
    }

    #[test]
    fn test_ambiguous_value_left_alone() {
        // 0x140 is both PAL_SERVANT and PAL_RIC_WHIP
        let line = "        self->palette = PAL_FLAG(0x140);";
        assert_eq!(transform(line), line);
        let line = "        self->palette = 0x140;";
        assert_eq!(transform(line), line);
    }

    #[test]
    fn test_zero_left_alone() {
        // PAL_NULL is 0x0, but a zero palette usually just means "none"
        let line = "        self->palette = 0x0;";
        assert_eq!(transform(line), line);
        let line = "        self->palette = 0;";
        assert_eq!(transform(line), line);
    }

    #[test]
    fn test_mask_left_alone() {
        let line = "        if (self->palette & 0x110) {";
        assert_eq!(transform(line), line);
    }

    #[test]
    fn test_complex_expression_left_alone() {
        // from src/weapon/w_030.c
        let line = "        self->palette = D_D6000_8017A640[s0] + ((u16)randRes | 0x110);";
        assert_eq!(transform(line), line);
    }

    #[test]
    fn test_non_palette_identifier_left_alone() {
        let line = "        self->animFrameIdx = 0x110;";
        assert_eq!(transform(line), line);
    }

    #[test]
    fn test_already_named_left_alone() {
        let line = "        self->palette = PAL_FLAG(PAL_UNK_195);";
        assert_eq!(transform(line), line);
    }
}
