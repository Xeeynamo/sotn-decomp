use crate::define_flag_transformer;

define_flag_transformer!(DrawModeTransformer<u16>, drawMode, [
    DRAW_DEFAULT    = default,
    DRAW_TRANSP     = BIT(0),
    DRAW_UNK02      = BIT(1),
    DRAW_COLORS     = BIT(2),
    DRAW_HIDE       = BIT(3),
    DRAW_TPAGE      = BIT(4),
    DRAW_TPAGE2     = BIT(5),
    DRAW_UNK_40     = BIT(6),
    DRAW_MENU       = BIT(7),
    DRAW_UNK_100    = BIT(8),
    DRAW_UNK_200    = BIT(9),
    DRAW_UNK_400    = BIT(10),
    DRAW_UNK_800    = BIT(11),
    DRAW_UNK_1000   = BIT(12),
    DRAW_ABSPOS     = BIT(13),
]);


#[cfg(test)]
mod tests {
    use crate::line_transformer::LineTransformer;

    use super::*;
    use once_cell::sync::Lazy;

    static DMT: Lazy<DrawModeTransformer> = Lazy::new(|| DrawModeTransformer::new());

    #[test]
    fn test_draw_mode_hex() {
        let input_line = "self->drawMode = 0x30;";
        let expected_line = "self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;";
        let result = DMT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_decimal() {
        let input_line = "self->drawMode = 32;";
        let expected_line = "self->drawMode = DRAW_TPAGE2;";
        let result = DMT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_zero() {
        let input_line = "self->drawMode = 0;";
        let expected_line = "self->drawMode = DRAW_DEFAULT;";
        let result = DMT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_zero_hex() {
        let input_line = "self->drawMode = 0x0;";
        let expected_line = "self->drawMode = DRAW_DEFAULT;";
        let result = DMT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_flags() {
        let input_line = "self->drawMode = DRAW_TPAGE;";
        let expected_line = "self->drawMode = DRAW_TPAGE;";
        let result = DMT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_set() {
        let input_line = "self->drawMode |= 0x80;";
        let expected_line = "self->drawMode |= DRAW_MENU;";
        let result = DMT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_clear() {
        let input_line = "self->drawMode &= 0xFF7F;";
        let expected_line = "self->drawMode &= ~DRAW_MENU;";
        let result = DMT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_clear_many() {
        let input_line = "self->drawMode &= 0xFFCF;";
        let expected_line = "self->drawMode &= ~(DRAW_TPAGE2 | DRAW_TPAGE);";
        let result = DMT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_mode_inverted_many() {
        let input_line = "self->drawMode &= ~0x300;";
        let expected_line = "self->drawMode &= ~(DRAW_UNK_200 | DRAW_UNK_100);";
        let result = DMT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_equality() {
        let input_line = "if (self->drawMode == 8) {";
        let expected_line = "if (self->drawMode == DRAW_HIDE) {";
        let result = DMT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_inequality() {
        let input_line = "if (self->drawMode != 8) {";
        let expected_line = "if (self->drawMode != DRAW_HIDE) {";
        let result = DMT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }
}
