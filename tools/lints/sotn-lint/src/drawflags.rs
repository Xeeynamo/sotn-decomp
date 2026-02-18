use lazy_static::lazy_static;

use crate::bit_flag_line_transformer::BitFlagLineTransformer;
use crate::line_transformer::LineTransformer;

pub struct DrawFlagsTransformer {
    transformer: BitFlagLineTransformer<u16>,
}

lazy_static! {
    static ref DRAW_FLAGS: [(u16, &'static str); 8] = [
        (1 << 0, "ENTITY_SCALEX"),
        (1 << 1, "ENTITY_SCALEY"),
        (1 << 2, "ENTITY_ROTATE"),
        (1 << 3, "ENTITY_OPACITY"),
        (1 << 4, "ENTITY_MASK_R"),
        (1 << 5, "ENTITY_MASK_G"),
        (1 << 6, "ENTITY_MASK_B"),
        (1 << 7, "ENTITY_BLINK"),
    ];
}

impl DrawFlagsTransformer {
    pub fn new() -> Self {
        Self {
            transformer: BitFlagLineTransformer::<u16>::new(
                "drawFlags",
                "ENTITY_DEFAULT",
                &DRAW_FLAGS.iter().collect(),
            ),
        }
    }
}

impl LineTransformer for DrawFlagsTransformer {
    fn transform_line(&self, line: &str) -> String {
        self.transformer.transform_line(line)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use once_cell::sync::Lazy;

    static FT: Lazy<DrawFlagsTransformer> = Lazy::new(|| DrawFlagsTransformer::new());

    #[test]
    fn test_draw_flags_hex() {
        let input_line = "self->drawFlags = 0x3;";
        let expected_line = "self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_decimal() {
        let input_line = "self->drawFlags = 3;";
        let expected_line = "self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_zero() {
        let input_line = "self->drawFlags = 0;";
        let expected_line = "self->drawFlags = ENTITY_DEFAULT;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_zero_hex() {
        let input_line = "self->drawFlags = 0x0;";
        let expected_line = "self->drawFlags = ENTITY_DEFAULT;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_flags() {
        let input_line = "self->drawFlags = ENTITY_SCALEX;";
        let expected_line = "self->drawFlags = ENTITY_SCALEX;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_set() {
        let input_line = "self->drawFlags |= 0x80;";
        let expected_line = "self->drawFlags |= ENTITY_BLINK;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_clear() {
        let input_line = "PLAYER.drawFlags &= 0xFF7F;";
        let expected_line = "PLAYER.drawFlags &= ~ENTITY_BLINK;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_clear_many() {
        let input_line = "self->drawFlags &= 0xFFFC;";
        let expected_line = "self->drawFlags &= ~(ENTITY_SCALEY | ENTITY_SCALEX);";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_equality() {
        let input_line = "if (self->drawFlags == 8) {";
        let expected_line = "if (self->drawFlags == ENTITY_OPACITY) {";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_inequality() {
        let input_line = "if (self->drawFlags != 8) {";
        let expected_line = "if (self->drawFlags != ENTITY_OPACITY) {";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }
}
