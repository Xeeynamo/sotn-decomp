use lazy_static::lazy_static;

use crate::line_transformer::LineTransformer;
use crate::bit_flag_line_transformer::BitFlagLineTransformer;

pub struct DrawFlagsTransformer {
    transformer: BitFlagLineTransformer<u16>,
}

lazy_static! {
    static ref DRAW_FLAGS: [(u16, &'static str); 9] = [
        (1 << 0, "FLAG_DRAW_ROTX"),
        (1 << 1, "FLAG_DRAW_ROTY"),
        (1 << 2, "FLAG_DRAW_ROTZ"),
        (1 << 3, "FLAG_DRAW_UNK8"),
        (1 << 4, "FLAG_DRAW_UNK10"),
        (1 << 5, "FLAG_DRAW_UNK20"),
        (1 << 6, "FLAG_DRAW_UNK40"),
        (1 << 7, "FLAG_BLINK"),
        (1 << 8, "FLAG_DRAW_UNK100"),
    ];
}

impl DrawFlagsTransformer {
    pub fn new() -> Self {
        Self {
            transformer: BitFlagLineTransformer::<u16>::new(
                "drawFlags", "FLAG_DRAW_DEFAULT", &DRAW_FLAGS.iter().collect()),
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
        let expected_line = "self->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_decimal() {
        let input_line = "self->drawFlags = 3;";
        let expected_line = "self->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_zero() {
        let input_line = "self->drawFlags = 0;";
        let expected_line = "self->drawFlags = FLAG_DRAW_DEFAULT;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_zero_hex() {
        let input_line = "self->drawFlags = 0x0;";
        let expected_line = "self->drawFlags = FLAG_DRAW_DEFAULT;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_flags() {
        let input_line = "self->drawFlags = FLAG_DRAW_ROTX;";
        let expected_line = "self->drawFlags = FLAG_DRAW_ROTX;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_set() {
        let input_line = "self->drawFlags |= 0x80;";
        let expected_line = "self->drawFlags |= FLAG_BLINK;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_clear() {
        let input_line = "PLAYER.drawFlags &= 0xFF7F;";
        let expected_line = "PLAYER.drawFlags &= ~FLAG_BLINK;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_clear_many() {
        let input_line = "self->drawFlags &= 0xFFFC;";
        let expected_line = "self->drawFlags &= ~(FLAG_DRAW_ROTY | FLAG_DRAW_ROTX);";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_equality() {
        let input_line = "if (self->drawFlags == 8) {";
        let expected_line = "if (self->drawFlags == FLAG_DRAW_UNK8) {";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_inequality() {
        let input_line = "if (self->drawFlags != 8) {";
        let expected_line = "if (self->drawFlags != FLAG_DRAW_UNK8) {";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }
}
