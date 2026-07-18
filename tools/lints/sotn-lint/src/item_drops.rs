use lazy_static::lazy_static;
use regex::Regex;
use std::cell::Cell;
use std::collections::HashMap;
use std::path::Path;
use std::sync::{LazyLock, Mutex};

use crate::c::enum_values;
use crate::line_transformer::LineTransformer;

static ITEM_DROP_IDS: LazyLock<Mutex<HashMap<i64, String>>> =
    LazyLock::new(|| Mutex::new(HashMap::new()));

thread_local! {
    static IN_PRIZE_DROPS: Cell<bool> = Cell::new(false);
}

pub struct ItemDropsTransformer {
    item_drops: HashMap<i64, String>,
}

impl ItemDropsTransformer {
    pub fn new() -> Self {
        Self::new_with_header_path("include/items.h")
    }

    fn new_with_header_path(path: &str) -> Self {
        let mut ids = ITEM_DROP_IDS.lock().unwrap();
        if ids.is_empty() {
            let drops = enum_values(Path::new(path), "ItemDrops").expect("items.h");
            drops.iter().for_each(|(name, value)| {
                ids.insert(*value, name.clone());
            });
        }
        Self {
            item_drops: ids.clone(),
        }
    }
}

lazy_static! {
    static ref HEX_REGEX: Regex = Regex::new(r"0x[0-9A-Fa-f]+").unwrap();
}

impl LineTransformer for ItemDropsTransformer {
    fn transform_line(&self, line: &str) -> String {
        if line.contains("OVL_EXPORT(PrizeDrops)") && line.contains("= {") {
            IN_PRIZE_DROPS.with(|s| s.set(true));
        }

        let in_array = IN_PRIZE_DROPS.with(|s| s.get());

        if line.contains("};") {
            IN_PRIZE_DROPS.with(|s| s.set(false));
        }

        if !in_array {
            return line.to_string();
        }

        HEX_REGEX
            .replace_all(line, |caps: &regex::Captures| {
                let hex_str = &caps[0];
                if let Ok(val) = i64::from_str_radix(&hex_str[2..], 16) {
                    if let Some(name) = self.item_drops.get(&val) {
                        return name.clone();
                    }
                }
                hex_str.to_string()
            })
            .to_string()
    }
}

#[cfg(test)]
mod test {
    use super::*;

    fn make_transformer() -> ItemDropsTransformer {
        ItemDropsTransformer::new_with_header_path("../../../include/items.h")
    }

    fn reset_state() {
        IN_PRIZE_DROPS.with(|s| s.set(false));
    }

    #[test]
    fn test_replaces_values_inside_prize_drops() {
        reset_state();
        let t = make_transformer();
        // from src/st/are/d_prize_drops.c
        t.transform_line("u16 OVL_EXPORT(PrizeDrops)[] = {");
        assert_eq!(
            t.transform_line("    0x000C, 0x0084, 0x0086, 0x0017,"),
            "    ITEMDROP_HEART_VESSEL, ITEMDROP_SHIELD_ROD, ITEMDROP_KNIGHT_SHIELD, ITEMDROP_LIFE_VESSEL,"
        );
    }

    #[test]
    fn test_no_replacement_outside_prize_drops() {
        reset_state();
        let t = make_transformer();
        assert_eq!(
            t.transform_line("    0x000C, 0x0084,"),
            "    0x000C, 0x0084,"
        );
    }

    #[test]
    fn test_stops_replacing_after_closing_brace() {
        reset_state();
        let t = make_transformer();
        t.transform_line("u16 OVL_EXPORT(PrizeDrops)[] = {");
        t.transform_line("    0x000C,");
        t.transform_line("};");
        assert_eq!(t.transform_line("    0x000C,"), "    0x000C,");
    }

    #[test]
    fn test_zero_len_array_unchanged() {
        reset_state();
        let t = make_transformer();
        // from src/st/cen/d_prize_drops.c and src/boss/rbo5/d_prize_drops.c
        let line = "u16 OVL_EXPORT(PrizeDrops)[ZERO_LEN] = {};";
        assert_eq!(t.transform_line(line), line);
        // state resets on };, so subsequent lines are not touched
        assert_eq!(t.transform_line("    0x000C,"), "    0x000C,");
    }

    #[test]
    fn test_extern_declaration_not_activated() {
        reset_state();
        let t = make_transformer();
        // extern forward-declaration in e_collect.h — no `= {`, must not activate
        t.transform_line("extern u16 OVL_EXPORT(PrizeDrops)[];");
        assert_eq!(t.transform_line("    0x000C,"), "    0x000C,");
    }

    #[test]
    fn test_unknown_value_left_unchanged() {
        reset_state();
        let t = make_transformer();
        // 0x18-0x7F are unused slots in ItemDrops
        t.transform_line("u16 OVL_EXPORT(PrizeDrops)[] = {");
        assert_eq!(t.transform_line("    0x0018,"), "    0x0018,");
    }

    #[test]
    fn test_rare_multiline_table() {
        reset_state();
        let t = make_transformer();
        // from src/st/rare/d_prize_drops.c
        t.transform_line("u16 OVL_EXPORT(PrizeDrops)[] = {");
        assert_eq!(
            t.transform_line("    0x000C, 0x0017, 0x000C,"),
            "    ITEMDROP_HEART_VESSEL, ITEMDROP_LIFE_VESSEL, ITEMDROP_HEART_VESSEL,"
        );
    }
}
