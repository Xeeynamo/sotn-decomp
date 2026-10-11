use lazy_static::lazy_static;
use regex::Regex;
use std::collections::HashMap;
use std::path::Path;
use std::sync::{LazyLock, Mutex};

use crate::c::{enum_entries, parse_int};
use crate::line_transformer::LineTransformer;

/// `process_directory` builds the transformers once per directory, so parse the
/// header once and share the result.
static ENEMY_IDS: LazyLock<Mutex<Option<HashMap<i64, String>>>> =
    LazyLock::new(|| Mutex::new(None));

/// Replaces a literal index into the enemy definition table with its
/// `EnemyIds` name: `g_api.enemyDefs[148]` becomes
/// `g_api.enemyDefs[ENEMY_FIRE_WARG]`.
pub struct EnemyDefsTransformer {
    enemies: HashMap<i64, String>,
}

impl EnemyDefsTransformer {
    pub fn new() -> Self {
        Self::new_with_header_path("include/game.h")
    }

    fn new_with_header_path(path: &str) -> Self {
        let mut cached = ENEMY_IDS.lock().unwrap();
        if cached.is_none() {
            let mut names = HashMap::new();
            for (name, value) in enum_entries(Path::new(path), "EnemyIds").expect("game.h") {
                names.entry(value).or_insert(name);
            }
            *cached = Some(names);
        }
        Self {
            enemies: cached.clone().unwrap(),
        }
    }
}

lazy_static! {
    // `g_api.enemyDefs`, its PSP alias `g_api_enemyDefs` and DRA's `g_EnemyDefs`
    static ref ENEMY_DEFS_REGEX: Regex = Regex::new(
        r"(?P<table>(?:(?:\.|->)\s*enemyDefs|\bg_api_enemyDefs|\bg_EnemyDefs)\s*\[\s*)(?P<index>0[xX][0-9A-Fa-f]+|[0-9]+)(?P<close>\s*\])"
    )
    .unwrap();

    // a declaration such as `extern EnemyDef g_EnemyDefs[400];` holds a size, not an index
    static ref DECLARATION_REGEX: Regex = Regex::new(r"\bEnemyDef\s*\*?\s*\w+\s*\[").unwrap();
}

impl LineTransformer for EnemyDefsTransformer {
    fn transform_line(&self, line: &str) -> String {
        if DECLARATION_REGEX.is_match(line) {
            return line.to_string();
        }
        ENEMY_DEFS_REGEX
            .replace_all(line, |caps: &regex::Captures| {
                match parse_int(&caps["index"]).and_then(|v| self.enemies.get(&v)) {
                    Some(name) => format!("{}{}{}", &caps["table"], name, &caps["close"]),
                    None => caps[0].to_string(),
                }
            })
            .to_string()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn transform(line: &str) -> String {
        EnemyDefsTransformer::new_with_header_path("../../../include/game.h").transform_line(line)
    }

    #[test]
    fn test_decimal_index() {
        // from src/st/e_fire_warg.h
        assert_eq!(
            transform("            enemyDefPtr = &g_api.enemyDefs[148];"),
            "            enemyDefPtr = &g_api.enemyDefs[ENEMY_FIRE_WARG];"
        );
    }

    #[test]
    fn test_hex_index() {
        // from src/st/nz0/gaibon.c
        assert_eq!(
            transform("            if (self->hitPoints < g_api.enemyDefs[0xFE].hitPoints / 2) {"),
            "            if (self->hitPoints < g_api.enemyDefs[ENEMY_GAIBON].hitPoints / 2) {"
        );
    }

    #[test]
    fn test_several_on_one_line() {
        assert_eq!(
            transform("x = g_api.enemyDefs[14].hitPoints + g_api.enemyDefs[15].hitPoints;"),
            "x = g_api.enemyDefs[ENEMY_FLYING_ZOMBIE_1].hitPoints + g_api.enemyDefs[ENEMY_FLYING_ZOMBIE_2].hitPoints;"
        );
    }

    #[test]
    fn test_psp_alias_and_pointer() {
        assert_eq!(transform("    x = g_api_enemyDefs[2].hitPoints;"), "    x = g_api_enemyDefs[ENEMY_PARTICLE].hitPoints;");
        assert_eq!(transform("    x = api->enemyDefs[5].flags;"), "    x = api->enemyDefs[ENEMY_INTERACTABLE].flags;");
    }

    #[test]
    fn test_dra_table() {
        assert_eq!(transform("    e = &g_EnemyDefs[3];"), "    e = &g_EnemyDefs[ENEMY_COMMON];");
    }

    #[test]
    fn test_non_literal_index_left_alone() {
        // from src/st/collision.h
        for line in [
            "        enemyDef = &g_api.enemyDefs[entityHit->enemyId];",
            "    enemyDef = &g_api.enemyDefs[enemyId];",
            "            enemyDef = &g_api.enemyDefs[WHITE_DRAGON_ID];",
            "extern EnemyDef g_EnemyDefs[400];",
            "    x = g_api.enemyDefs[0x1000];",
        ] {
            assert_eq!(transform(line), line);
        }
    }

    #[test]
    fn test_other_arrays_left_alone() {
        let line = "    x = g_api.otherDefs[148] + myEnemyDefs[3];";
        assert_eq!(transform(line), line);
    }
}
