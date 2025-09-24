use crate::define_flag_transformer;

define_flag_transformer!(ColliderEffectsTransformer<u16>, effects, [
    EFFECT_NONE                 = default,
    EFFECT_SOLID                = BIT(0),
    EFFECT_UNK_0002             = BIT(1),
    EFFECT_QUICKSAND            = BIT(2),
    EFFECT_WATER                = BIT(3),
    EFFECT_MIST_ONLY            = BIT(4),
    EFFECT_UNK_0020             = BIT(5),
    EFFECT_SOLID_FROM_ABOVE     = BIT(6),
    EFFECT_SOLID_FROM_BELOW     = BIT(7),
    EFFECT_UNK_0100             = BIT(8),
    EFFECT_UNK_0200             = BIT(9),
    EFFECT_UNK_0400             = BIT(10),
    EFFECT_UNK_0800             = BIT(11),
    EFFECT_UNK_1000             = BIT(12),
    EFFECT_UNK_2000             = BIT(13),
    EFFECT_UNK_4000             = BIT(14),
    EFFECT_UNK_8000             = BIT(15),
]);



#[cfg(test)]
mod tests {
    use crate::line_transformer::LineTransformer as _;

    use super::*;
    use once_cell::sync::Lazy;

    static FT: Lazy<ColliderEffectsTransformer> = Lazy::new(|| ColliderEffectsTransformer::default());

    #[test]
    fn test_draw_flags_hex() {
        let input_line = "self->effects = 0x5;";
        let expected_line = "self->effects = EFFECT_QUICKSAND | EFFECT_SOLID;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_decimal() {
        let input_line = "self->effects = 5;";
        let expected_line = "self->effects = EFFECT_QUICKSAND | EFFECT_SOLID;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_zero() {
        let input_line = "self->effects = 0;";
        let expected_line = "self->effects = EFFECT_NONE;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_zero_hex() {
        let input_line = "self->effects = 0x0;";
        let expected_line = "self->effects = EFFECT_NONE;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_flags() {
        let input_line = "self->effects = EFFECT_WATER;";
        let expected_line = "self->effects = EFFECT_WATER;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }
}
