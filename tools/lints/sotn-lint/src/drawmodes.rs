use lazy_static::lazy_static;

use crate::line_transformer::LineTransformer;
use crate::bit_flag_line_transformer::BitFlagLineTransformer;

pub struct DrawModeTransformer {
    transformer: BitFlagLineTransformer<u16>,
}

lazy_static! {
    static ref DRAW_MODES: [(u16, &'static str); 14] = [
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
}

impl DrawModeTransformer {
    pub fn new() -> Self {
        Self {
            transformer: BitFlagLineTransformer::<u16>::new(
                "drawMode", "DRAW_DEFAULT", &DRAW_MODES.iter().collect()),
        }
    }
}

impl LineTransformer for DrawModeTransformer {
    fn transform_line(&self, line: &str) -> String {
        self.transformer.transform_line(line)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use once_cell::sync::Lazy;

    static DMT: Lazy<DrawModeTransformer> = Lazy::new(|| DrawModeTransformer::new());

    #[test]
    fn test_draw_mode_hex() {
        let input_line = "self->drawMode = 0x30;";
        let expected_line = "self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_decimal() {
        let input_line = "self->drawMode = 32;";
        let expected_line = "self->drawMode = DRAW_TPAGE2;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_zero() {
        let input_line = "self->drawMode = 0;";
        let expected_line = "self->drawMode = DRAW_DEFAULT;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_zero_hex() {
        let input_line = "self->drawMode = 0x0;";
        let expected_line = "self->drawMode = DRAW_DEFAULT;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_flags() {
        let input_line = "self->drawMode = DRAW_TPAGE;";
        let expected_line = "self->drawMode = DRAW_TPAGE;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_set() {
        let input_line = "self->drawMode |= 0x80;";
        let expected_line = "self->drawMode |= DRAW_MENU;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_clear() {
        let input_line = "self->drawMode &= 0xFF7F;";
        let expected_line = "self->drawMode &= ~DRAW_MENU;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_clear_many() {
        let input_line = "self->drawMode &= 0xFFCF;";
        let expected_line = "self->drawMode &= ~(DRAW_TPAGE2 | DRAW_TPAGE);";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_inverted_many() {
        let input_line = "self->drawMode &= ~0x300;";
        let expected_line = "self->drawMode &= ~(DRAW_UNK_200 | DRAW_UNK_100);";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)

    }
}
