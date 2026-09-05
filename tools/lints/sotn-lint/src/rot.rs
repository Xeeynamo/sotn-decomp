use lazy_static::lazy_static;
use regex::Regex;

use crate::line_transformer::LineTransformer;

pub struct RotationTransformer;

impl LineTransformer for RotationTransformer {
    fn transform_line(&self, line: &str) -> String {
        transform_line_rotation(line)
    }
}

fn rotation(x: f64, group: &str, terminal: char) -> String {
    let formatted_str = format!("{:.20}", x);
    let trimmed_str = formatted_str
        .trim_end_matches('0')
        .trim_end_matches('.')
        .to_string();
    format!("{group}ROT({trimmed_str}){terminal}")
}

struct Pattern {
    regex: Regex,
    terminal: char,
}

fn gen_patterns(patterns: &mut Vec<Pattern>) {
    // MATRIX and ratan2 not supported
    // n.b.! GsBG, GsSPRITE, GsRVIEWUNIT use a different format for rotation
    let regs = [
        (r"(OBJECT->NAME\s*=\s*)(-?0x[0-9a-fA-F]+);", ';'), // =
        (r"(OBJECT->NAME\s*\+=\s*)(-?0x[0-9a-fA-F]+);", ';'), // +=
        (r"(OBJECT->NAME\s*-=\s*)(-?0x[0-9a-fA-F]+);", ';'), // -=
        (r"(OBJECT->NAME\s*>\s*)(-?0x[0-9a-fA-F]+)\)", ')'), // >
        (r"(OBJECT->NAME\s*>=\s*)(-?0x[0-9a-fA-F]+)\)", ')'), // >=
        (r"(OBJECT->NAME\s*<\s*)(-?0x[0-9a-fA-F]+)\)", ')'), // <
        (r"(OBJECT->NAME\s*<=\s*)(-?0x[0-9a-fA-F]+)\)", ')'), // <=
        (
            r"(^.*(?:catan|ccos|csin|rcos|rsin|rtan)\()(-?0x[0-9a-fA-F]+)\)",
            ')',
        ), // rsin/rcos/rtan
        (r"(^.*RotMatrix[XYZ]\()(-?0x[0-9a-fA-F]+),", ','), // RotMatrixX/Y/Z
    ];

    let objs = ["entity", "g_CurrentEntity", "self"];

    let names = ["rotate"];

    for obj in objs.iter() {
        for name in names.iter() {
            for (regex_str, c) in regs.iter() {
                let temp = regex_str.replace("OBJECT", obj).replace("NAME", name);
                let regex = Regex::new(&temp).unwrap();
                let terminal = *c;
                patterns.push(Pattern { regex, terminal });
            }
        }
    }
}

fn hex_string_to_float(hex_str: &str) -> Option<f64> {
    let cleaned_str = hex_str.trim_start_matches("-0x").trim_start_matches("0x");
    if let Ok(hex_value) = i64::from_str_radix(cleaned_str, 16) {
        let result = 360.0 * (hex_value as f64 / 4096.0);
        if hex_str.starts_with('-') {
            Some(-result)
        } else {
            Some(result)
        }
    } else {
        None
    }
}

fn transform_line_rotation(line: &str) -> String {
    for pattern in PATTERNS.iter() {
        if let Some(thing) = pattern.regex.captures(line) {
            if let Some(hex_str) = thing.get(2) {
                if let Some(conv) = hex_string_to_float(hex_str.into()) {
                    if let Some(group_str) = thing.get(1) {
                        let rotation_value = rotation(conv, group_str.as_str(), pattern.terminal);
                        return pattern.regex.replace(line, &rotation_value).to_string();
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
    fn test_negative() {
        let input_line = "entity->rotate = -0x800;";
        let expected_line = "entity->rotate = ROT(-180);";
        let result = transform_line_rotation(input_line);
        assert_eq!(result, expected_line);
    }

    #[test]
    fn test_positive() {
        let input_line = "entity->rotate = 0x800;";
        let expected_line = "entity->rotate = ROT(180);";
        let result = transform_line_rotation(input_line);
        assert_eq!(result, expected_line);
    }

    #[test]
    fn test_complex_line() {
        // don't format
        let input_line = "entity->rotate += 0x800 - (Random() << 8);";
        let expected_line = "entity->rotate += 0x800 - (Random() << 8);";
        let result = transform_line_rotation(input_line);
        assert_eq!(result, expected_line);
    }

    #[test]
    fn test_trailing_zero() {
        let input_line = "if (self->rotate < -0x180) {";
        let expected_line = "if (self->rotate < ROT(-33.75)) {";
        let result = transform_line_rotation(input_line);
        assert_eq!(result, expected_line);
    }

    #[test]
    fn test_rsin() {
        let input_line = "foo = rsin(0x1000) * …";
        let expected_line = "foo = rsin(ROT(360)) * …";
        let result = transform_line_rotation(input_line);
        assert_eq!(result, expected_line);
    }

    #[test]
    fn test_rotmatrix() {
        let input_line = "m = *RotMatrixX(0x57D, &m);";
        let expected_line = "m = *RotMatrixX(ROT(123.486328125), &m);";
        let result = transform_line_rotation(input_line);
        assert_eq!(result, expected_line);
    }
}
