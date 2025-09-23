use std::borrow::Cow;

use regex::Regex;

use lazy_static::lazy_static;

use crate::line_transformer::LineTransformer;

pub struct RelicsTransformer;

impl LineTransformer for RelicsTransformer {
    fn transform_line(&self, line: &str) -> Option<String> {
        transform_line_relics(line)
    }
}

const RELICS: [&str; 30] = [
    "RELIC_SOUL_OF_BAT",
    "RELIC_FIRE_OF_BAT",
    "RELIC_ECHO_OF_BAT",
    "RELIC_FORCE_OF_ECHO",
    "RELIC_SOUL_OF_WOLF",
    "RELIC_POWER_OF_WOLF",
    "RELIC_SKILL_OF_WOLF",
    "RELIC_FORM_OF_MIST",
    "RELIC_POWER_OF_MIST",
    "RELIC_GAS_CLOUD",
    "RELIC_CUBE_OF_ZOE",
    "RELIC_SPIRIT_ORB",
    "RELIC_GRAVITY_BOOTS",
    "RELIC_LEAP_STONE",
    "RELIC_HOLY_SYMBOL",
    "RELIC_FAERIE_SCROLL",
    "RELIC_JEWEL_OF_OPEN",
    "RELIC_MERMAN_STATUE",
    "RELIC_BAT_CARD",
    "RELIC_GHOST_CARD",
    "RELIC_FAERIE_CARD",
    "RELIC_DEMON_CARD",
    "RELIC_SWORD_CARD",
    "RELIC_JP_0",
    "RELIC_JP_1",
    "RELIC_HEART_OF_VLAD",
    "RELIC_TOOTH_OF_VLAD",
    "RELIC_RIB_OF_VLAD",
    "RELIC_RING_OF_VLAD",
    "RELIC_EYE_OF_VLAD",
];

fn replace_enum(captures: &regex::Captures) -> String {
    if let Some(Ok(relic_index)) = captures.get(1).map(|m| m.as_str().parse::<usize>()) {
        if let Some(relic_name) = RELICS.get(relic_index) {
            return format!("g_Status.relics[{relic_name}]");
        }
    }
    captures
        .get(0)
        .map_or_else(|| "".to_string(), |m| m.as_str().to_string())
}

lazy_static! {
    static ref REGEX: Regex = {
        let pattern = r"g_Status\.relics\[(\d+)\]";
        Regex::new(pattern).unwrap()
    };
}

fn transform_line_relics(line: &str) -> Option<String> {
    match REGEX.replace_all(line, |captures: &regex::Captures| replace_enum(captures)) {
        Cow::Borrowed(_) => None,
        Cow::Owned(s) => Some(s),
    }
}

#[test]
fn test_does_transform() {
    let input = "g_Status.relics[0]";
    let expected_output = "g_Status.relics[RELIC_SOUL_OF_BAT]".to_string();
    assert_eq!(transform_line_relics(input), Some(expected_output));
}

#[test]
fn test_no_transform() {
    let input = "g_Status.equipment[0]";
    let _expected_output = "g_Status.equipment[0]".to_string();
    assert_eq!(transform_line_relics(input).as_deref(), None);
}
