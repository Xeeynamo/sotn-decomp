use regex::Regex;

use lazy_static::lazy_static;

use crate::line_transformer::LineTransformer;

pub struct DrawModeTransformer;

impl LineTransformer for DrawModeTransformer {
    fn transform_line(&self, line: &str) -> String {
        transform_line_draw_mode(line)
    }
}

lazy_static! {

    static ref DRAW_MODES: [(u16, &'static str); 14] = {
        let mut draw_modes = [
            (1 << 0, "DRAW_TRANSP"),
            (1 << 1, "DRAW_UNK02"),
            (1 << 2, "DRAW_COLORS"),
            (1 << 3, "DRAW_HIDE"),
            (1 << 4, "DRAW_TPAGE"),
            (1 << 5, "DRAW_TPAGE2"),
            (1 << 6, "DRAW_UNK_40"),
            (1 << 7, "DRAW_MENU"),
            (1 << 8, "DRAW_UNK_100"),
            (1 << 9, "DRAW_UNK_200"),
            (1 << 10, "DRAW_UNK_400"),
            (1 << 11, "DRAW_UNK_800"),
            (1 << 12, "DRAW_UNK_1000"),
            (1 << 13, "DRAW_ABSPOS"),
        ];
        draw_modes.sort_by(|(a, _), (b, _)| b.cmp(a));
        draw_modes
    };

    static ref REGEX: Regex = {
        let pattern = r"([.>]drawMode\s*(?:[&|]?)=\s*)((?:0x)?[A-Fa-f0-9]*)(?:;)";
        Regex::new(pattern).unwrap()
    };
}

fn replace_enum(captures: &regex::Captures) -> String {
    if let Some(assignment) = captures.get(1).map(|m| m.as_str().to_string()) {
        if let Some(draw_mode) = captures.get(2).map(|m| m.as_str().to_string()) {
            // if it starts with 0x, hex string, otherwise int
            let mut draw_mode_value: u16;
            if draw_mode.starts_with("0x") {
                if let Ok(v) = u16::from_str_radix(draw_mode.strip_prefix("0x").unwrap(), 16) {
                    draw_mode_value = v;
                } else {
                    return captures.get(0)
                        .map_or_else(|| "".to_string(), |m| m.as_str().to_string())
                }
            } else {
                draw_mode_value = draw_mode.parse::<u16>().unwrap();
            }

            let invert: String;
            if (draw_mode_value & 0x8000) != 0 {
                invert = "~".to_string();
                draw_mode_value = !draw_mode_value;
            } else {
                invert = "".to_string();
            }

            let mut rvalue: String;
            if draw_mode_value == 0 {
                rvalue = "DRAW_DEFAULT".to_string();
            } else {
                rvalue = DRAW_MODES.iter()
                    .map(|(mask, name)|
                        if (mask & draw_mode_value) != 0 {
                            Some(name)
                        } else {
                            None
                        })
                    .filter(|e| e.is_some())
                    .map(|e| *e.unwrap())
                    .collect::<Vec<&str>>()
                    .join(" | ");
                if u16::count_ones(draw_mode_value) > 1 && invert == "~" {
                    rvalue = format!("({})", rvalue);
                }
            }
            return format!("{}{}{};", assignment.to_string(), invert, rvalue);
        }
    }
    captures
        .get(0)
        .map_or_else(|| "".to_string(), |m| m.as_str().to_string())
}

fn transform_line_draw_mode(line: &str) -> String {
    REGEX.replace_all(line, |captures: &regex::Captures| replace_enum(captures)).to_string()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_draw_mode_hex() {
        let input_line = "self->drawMode = 0x30;";
        let expected_line = "self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;";
        let result = transform_line_draw_mode(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_decimal() {
        let input_line = "self->drawMode = 32;";
        let expected_line = "self->drawMode = DRAW_TPAGE2;";
        let result = transform_line_draw_mode(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_zero() {
        let input_line = "self->drawMode = 0;";
        let expected_line = "self->drawMode = DRAW_DEFAULT;";
        let result = transform_line_draw_mode(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_zero_hex() {
        let input_line = "self->drawMode = 0x0;";
        let expected_line = "self->drawMode = DRAW_DEFAULT;";
        let result = transform_line_draw_mode(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_flags() {
        let input_line = "self->drawMode = DRAW_TPAGE;";
        let expected_line = "self->drawMode = DRAW_TPAGE;";
        let result = transform_line_draw_mode(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_set() {
        let input_line = "self->drawMode |= 0x80;";
        let expected_line = "self->drawMode |= DRAW_MENU;";
        let result = transform_line_draw_mode(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_clear() {
        let input_line = "self->drawMode &= 0xFF7F;";
        let expected_line = "self->drawMode &= ~DRAW_MENU;";
        let result = transform_line_draw_mode(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_clear_many() {
        let input_line = "self->drawMode &= 0xFFCF;";
        let expected_line = "self->drawMode &= ~(DRAW_TPAGE2 | DRAW_TPAGE);";
        let result = transform_line_draw_mode(input_line);
        assert_eq!(result, expected_line)
    }
}
