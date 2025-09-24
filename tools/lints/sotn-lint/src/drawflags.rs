use crate::define_flag_transformer;

define_flag_transformer!(DrawFlagsTransformer<u16>, drawFlags, [
    FLAG_DRAW_DEFAULT   = default,
    FLAG_DRAW_SCALEX    = BIT(0),
    FLAG_DRAW_SCALEY    = BIT(1),
    FLAG_DRAW_ROTATE    = BIT(2),
    FLAG_DRAW_OPACITY   = BIT(3),
    FLAG_DRAW_UNK10     = BIT(4),
    FLAG_DRAW_UNK20     = BIT(5),
    FLAG_DRAW_UNK40     = BIT(6),
    FLAG_BLINK          = BIT(7),
    FLAG_DRAW_UNK100    = BIT(8),
]);

#[cfg(test)]
mod tests {
    use crate::line_transformer::LineTransformer;

    use super::*;
    use once_cell::sync::Lazy;

    static FT: Lazy<DrawFlagsTransformer> = Lazy::new(|| DrawFlagsTransformer::default());

    #[test]
    fn test_draw_flags_hex() {
        let input_line = "self->drawFlags = 0x3;";
        let expected_line = "self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;";
        let result = FT.transform_line(input_line);
        assert_eq!(result.as_deref(), Some(expected_line))
    }

    #[test]
    fn test_draw_flags_decimal() {
        let input_line = "self->drawFlags = 3;";
        let expected_line = "self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;";
        let result = FT.transform_line(input_line);
        assert_eq!(result.as_deref(), Some(expected_line))
    }

    #[test]
    fn test_draw_flags_zero() {
        let input_line = "self->drawFlags = 0;";
        let expected_line = "self->drawFlags = FLAG_DRAW_DEFAULT;";
        let result = FT.transform_line(input_line);
        assert_eq!(result.as_deref(), Some(expected_line))
    }

    #[test]
    fn test_draw_flags_zero_hex() {
        let input_line = "self->drawFlags = 0x0;";
        let expected_line = "self->drawFlags = FLAG_DRAW_DEFAULT;";
        let result = FT.transform_line(input_line);
        assert_eq!(result.as_deref(), Some(expected_line))
    }

    #[test]
    fn test_draw_flags_flags() {
        let input_line = "self->drawFlags = FLAG_DRAW_SCALEX;";
        let _expected_line = "self->drawFlags = FLAG_DRAW_SCALEX;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, None)
    }

    #[test]
    fn test_draw_flags_set() {
        let input_line = "self->drawFlags |= 0x80;";
        let expected_line = "self->drawFlags |= FLAG_BLINK;";
        let result = FT.transform_line(input_line);
        assert_eq!(result.as_deref(), Some(expected_line))
    }

    #[test]
    fn test_draw_flags_clear() {
        let input_line = "PLAYER.drawFlags &= 0xFF7F;";
        let expected_line = "PLAYER.drawFlags &= ~FLAG_BLINK;";
        let result = FT.transform_line(input_line);
        assert_eq!(result.as_deref(), Some(expected_line))
    }

    #[test]
    fn test_draw_flags_clear_many() {
        let input_line = "self->drawFlags &= 0xFFFC;";
        let expected_line = "self->drawFlags &= ~(FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX);";
        let result = FT.transform_line(input_line);
        assert_eq!(result.as_deref(), Some(expected_line))
    }

    #[test]
    fn test_equality() {
        let input_line = "if (self->drawFlags == 8) {";
        let expected_line = "if (self->drawFlags == FLAG_DRAW_OPACITY) {";
        let result = FT.transform_line(input_line);
        assert_eq!(result.as_deref(), Some(expected_line))
    }

    #[test]
    fn test_inequality() {
        let input_line = "if (self->drawFlags != 8) {";
        let expected_line = "if (self->drawFlags != FLAG_DRAW_OPACITY) {";
        let result = FT.transform_line(input_line);
        assert_eq!(result.as_deref(), Some(expected_line))
    }
}
