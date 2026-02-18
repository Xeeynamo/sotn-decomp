use lazy_static::lazy_static;

use crate::bit_flag_line_transformer::BitFlagLineTransformer;
use crate::line_transformer::LineTransformer;

pub struct BlendModeTransformer {
    transformer: BitFlagLineTransformer<u16>,
}

lazy_static! {
    static ref BLEND_MODES: [(u16, &'static str); 5] = [
        (0, "BLEND_NO"),
        (0x10, "BLEND_TRANSP"),
        (0x20, "BLEND_ADD"),
        (0x40, "BLEND_SUB"),
        (0x60, "BLEND_QUARTER"),
    ];
}

impl BlendModeTransformer {
    pub fn new() -> Self {
        Self {
            transformer: BitFlagLineTransformer::<u16>::new(
                "blendMode",
                "BLEND_NO",
                &BLEND_MODES.iter().collect(),
            ),
        }
    }
}

impl LineTransformer for BlendModeTransformer {
    fn transform_line(&self, line: &str) -> String {
        self.transformer.transform_line(line)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use once_cell::sync::Lazy;

    static DMT: Lazy<BlendModeTransformer> = Lazy::new(|| BlendModeTransformer::new());

    #[test]
    fn test_blend_mode_hex() {
        let input_line = "self->blendMode = 0x30;";
        let expected_line = "self->blendMode = BLEND_ADD | BLEND_TRANSP;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_blend_mode_decimal() {
        let input_line = "self->blendMode = 32;";
        let expected_line = "self->blendMode = BLEND_ADD;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_blend_mode_zero() {
        let input_line = "self->blendMode = 0;";
        let expected_line = "self->blendMode = BLEND_NO;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_blend_mode_zero_hex() {
        let input_line = "self->blendMode = 0x0;";
        let expected_line = "self->blendMode = BLEND_NO;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_blend_mode_flags() {
        let input_line = "self->blendMode = BLEND_TRANSP;";
        let expected_line = "self->blendMode = BLEND_TRANSP;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_blend_mode_set_combo() {
        let input_line = "self->blendMode = 0x60;";
        let expected_line = "self->blendMode = BLEND_QUARTER;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_blend_mode_add() {
        let input_line = "self->blendMode |= 0x40;";
        let expected_line = "self->blendMode |= BLEND_SUB;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_blend_mode_add_combo() {
        let input_line = "self->blendMode |= 0x60;";
        let expected_line = "self->blendMode |= BLEND_QUARTER;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_blend_mode_clear() {
        let input_line = "self->blendMode &= 0xFFEF;";
        let expected_line = "self->blendMode &= ~BLEND_TRANSP;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_blend_mode_clear_many() {
        let input_line = "self->blendMode &= 0xFFCF;";
        let expected_line = "self->blendMode &= ~(BLEND_ADD | BLEND_TRANSP);";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_blend_mode_inverted_many() {
        let input_line = "self->blendMode &= ~0x30;";
        let expected_line = "self->blendMode &= ~(BLEND_ADD | BLEND_TRANSP);";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_equality() {
        let input_line = "if (self->blendMode == 16) {";
        let expected_line = "if (self->blendMode == BLEND_TRANSP) {";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_inequality() {
        let input_line = "if (self->blendMode != 16) {";
        let expected_line = "if (self->blendMode != BLEND_TRANSP) {";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }
}
