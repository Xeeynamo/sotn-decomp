use lazy_static::lazy_static;
use regex::Regex;

use crate::line_transformer::LineTransformer;

pub struct FixedTransformer;

impl LineTransformer for FixedTransformer {
    fn transform_line(&self, line: &str) -> String {
        transform_line_fixed(line)
    }
}

fn fixed(x: f64, group: &str, has_semicolon: &bool) -> String {
    let formatted_str = format!("{:.20}", x);
    let mut trimmed_str = formatted_str.trim_end_matches('0').to_string();
    if trimmed_str.ends_with('.') {
        trimmed_str.push('0');
    }
    if *has_semicolon {
        format!("{}FIX({});", group, trimmed_str)
    } else {
        format!("{}FIX({}))", group, trimmed_str)
    }
}

struct Pattern {
    regex: Regex,
    should_replace: bool,
}

fn gen_patterns(patterns: &mut Vec<Pattern>) {
    let regs = [
        (r"(OBJECT->NAME\s*\=\s*)(-?0x[0-9a-fA-F]+);", true), // =
        (r"(OBJECT->NAME\s*\+=\s*)(-?0x[0-9a-fA-F]+);", true), // +=
        (r"(OBJECT->NAME\s*-=\s*)(-?0x[0-9a-fA-F]+);", true), // -=
        (r"(OBJECT->NAME\s*>\s*)(-?0x[0-9a-fA-F]+)\)", false), // >
        (r"(OBJECT->NAME\s*>=\s*)(-?0x[0-9a-fA-F]+)\)", false), // >=
        (r"(OBJECT->NAME\s*<\s*)(-?0x[0-9a-fA-F]+)\)", false), // <
        (r"(OBJECT->NAME\s*<=\s*)(-?0x[0-9a-fA-F]+)\)", false), // <=
    ];

    let objs = ["entity", "g_CurrentEntity", "self"];

    let names = ["velocityX", "velocityY", "posX.val", "posY.val"];

    for obj in objs.iter() {
        for name in names.iter() {
            for (regex_str, rep) in regs.iter() {
                let temp = regex_str.replace("OBJECT", obj).replace("NAME", name);
                let regex = Regex::new(&temp).unwrap();
                let should_replace = *rep;
                patterns.push(Pattern {
                    regex,
                    should_replace,
                });
            }
        }
    }
}

fn count_digits_after_decimal(number: f64) -> usize {
    let binding = number.to_string();
    let decimal_part: Vec<&str> = binding.split('.').collect();
    if decimal_part.len() > 1 {
        decimal_part[1].len()
    } else {
        0
    }
}

fn count_digits_before_decimal(number: f64) -> usize {
    let binding = number.to_string();
    let decimal_part: Vec<&str> = binding.split('.').collect();
    if decimal_part.len() > 0 {
        decimal_part[0].len()
    } else {
        0
    }
}

fn hex_string_to_float(hex_str: &str) -> Option<f64> {
    let cleaned_str = hex_str.trim_start_matches("-0x").trim_start_matches("0x");
    if let Ok(hex_value) = i64::from_str_radix(cleaned_str, 16) {
        let result = hex_value as f64 / 65536.0;
        if hex_str.starts_with('-') {
            Some(-result)
        } else {
            Some(result)
        }
    } else {
        None
    }
}

fn transform_line_fixed(line: &str) -> String {
    for pattern in PATTERNS.iter() {
        if let Some(thing) = pattern.regex.captures(line) {
            if let Some(hex_str) = thing.get(2) {
                if let Some(conv) = hex_string_to_float(hex_str.into()) {
                    if count_digits_after_decimal(conv) > 5 || count_digits_before_decimal(conv) > 3
                    {
                        println!("skipping");
                        return line.to_string();
                    } else {
                        if let Some(group_str) = thing.get(1) {
                            let fixed_value =
                                fixed(conv, group_str.as_str(), &pattern.should_replace);
                            return pattern.regex.replace(line, &fixed_value).to_string();
                        }
                    }
                }
            }
        }
    }
    line.to_string()
}

fn get_regexes() -> Vec<Pattern> {
    let mut patterns = Vec::new();
    gen_patterns(&mut patterns);
    patterns
}

lazy_static! {
    static ref PATTERNS: Vec<Pattern> = get_regexes();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_positive() {
        let input_line = "entity->velocityY = -0x8000;";
        let expected_line = "entity->velocityY = FIX(-0.5);";
        let result = transform_line_fixed(input_line);
        assert_eq!(result, expected_line);
    }

    #[test]
    fn test_negative() {
        let input_line = "entity->velocityY = 0x8000;";
        let expected_line = "entity->velocityY = FIX(0.5);";
        let result = transform_line_fixed(input_line);
        assert_eq!(result, expected_line);
    }

    #[test]
    fn test_complex_line() {
        // don't format
        let input_line = "entity->velocityX += 0x8000 - (Random() << 8);";
        let expected_line = "entity->velocityX += 0x8000 - (Random() << 8);";
        let result = transform_line_fixed(input_line);
        assert_eq!(result, expected_line);
    }

    #[test]
    fn test_trailing_zero() {
        let input_line = "if (self->velocityY < -0x20000) {";
        let expected_line = "if (self->velocityY < FIX(-2.0)) {";
        let result = transform_line_fixed(input_line);
        assert_eq!(result, expected_line);
    }
}
