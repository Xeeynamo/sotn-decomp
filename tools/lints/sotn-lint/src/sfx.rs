use lazy_static::lazy_static;
use regex::Regex;
use std::collections::HashMap;
use std::path::Path;

use crate::c::enum_values;
use crate::line_transformer::LineTransformer;

use std::sync::{LazyLock, Mutex};

static SFX_IDS: LazyLock<Mutex<HashMap<i64, String>>> =
    LazyLock::new(|| Mutex::new(HashMap::new()));

/// A `LineTransformer` that finds numeric SFX IDs and converts them to Sfx values.
pub struct SfxLineTransformer {
    sfx_ids: HashMap<i64, String>,
}

impl SfxLineTransformer {
    pub fn new() -> Self {
        Self::new_with_header_path("include/sfx.h")
    }

    fn new_with_header_path(path: &str) -> Self {
        let mut si = SFX_IDS.lock().unwrap();
        if si.is_empty() {
            let sfx_enum = enum_values(Path::new(path), "Sfx").expect("sfx.h");
            sfx_enum.iter().for_each(|(name, value)| {
                si.insert(*value, name.clone());
            })
        }
        Self {
            sfx_ids: si.clone(),
        }
    }
}

lazy_static! {
    static ref REGEX: Regex = {
        Regex::new(r"(Play[^(. ]*?Sfx[^(. ]*?\()((?:0x[0-9A-Fa-f]+)|(?:[0-9]+))([^0-9A-Fa-f])")
            .unwrap()
    };
}

impl LineTransformer for SfxLineTransformer {
    fn transform_line(&self, line: &str) -> String {
        let Some(captures) = REGEX.captures(line) else {
            return line.to_string();
        };

        let func = captures.get(1).map(|m| m.as_str()).expect("function");
        let id_str = captures.get(2).map(|m| m.as_str()).expect("sfxId");
        let terminal_str = captures.get(3).map(|m| m.as_str()).expect("terminal");

        let id = if id_str.starts_with("0x") {
            i64::from_str_radix(id_str.strip_prefix("0x").expect("string"), 16).expect("int")
        } else {
            id_str.parse::<i64>().unwrap()
        };

        let Some(sfx_name) = self.sfx_ids.get(&id) else {
            return line.to_string();
        };

        let r = format!("{func}{sfx_name}{terminal_str}");
        REGEX.replace(line, &r).to_string()
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn test_sfx() {
        let t = SfxLineTransformer::new_with_header_path("../../../include/sfx.h");

        assert_eq!(
            t.transform_line("PlaySfx(0x7D1);"),
            "PlaySfx(SFX_SCIFI_BLAST);"
        );
        assert_eq!(
            t.transform_line("PlaySfx(SFX_MEDUSA_PAIN_A);"),
            "PlaySfx(SFX_MEDUSA_PAIN_A);"
        );

        // PlaySfx variations/decimal and hex
        assert_eq!(
            t.transform_line("PlaySfxVolPan(1549, 0x60, 6);"),
            "PlaySfxVolPan(SFX_METAL_CLANG_A, 0x60, 6);"
        );
        assert_eq!(
            t.transform_line("PlaySfxPositional(0x622);"),
            "PlaySfxPositional(SFX_SKULL_BONK);"
        );

        // values not in the enum
        assert_eq!(t.transform_line("PlaySfx(0x30B);"), "PlaySfx(0x30B);");
    }
}
