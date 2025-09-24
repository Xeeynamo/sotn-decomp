use crate::define_flag_transformer;

define_flag_transformer!(AttackElementTransformer<u32>, attackElement, [
    ELEMENT_NONE      = default,
    ELEMENT_HIT       = BIT(5),
    ELEMENT_CUT       = BIT(6),
    ELEMENT_POISON    = BIT(7),
    ELEMENT_CURSE     = BIT(8),
    ELEMENT_STONE     = BIT(9),
    ELEMENT_WATER     = BIT(10),
    ELEMENT_DARK      = BIT(11),
    ELEMENT_HOLY      = BIT(12),
    ELEMENT_ICE       = BIT(13),
    ELEMENT_THUNDER   = BIT(14),
    ELEMENT_FIRE      = BIT(15),
    ELEMENT_UNK_10000 = BIT(16),
]);



#[cfg(test)]
mod tests {
    use super::*;
    use crate::line_transformer::LineTransformer;
    use once_cell::sync::Lazy;

    static AET: Lazy<AttackElementTransformer> = Lazy::new(|| AttackElementTransformer::default());

    #[test]
    fn test_attack_element_hex() {
        let input_line = "self->attackElement = 0x60;";
        let expected_line = "self->attackElement = ELEMENT_CUT | ELEMENT_HIT;";
        let result = AET.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_attack_element_decimal() {
        let input_line = "self->attackElement = 96;";
        let expected_line = "self->attackElement = ELEMENT_CUT | ELEMENT_HIT;";
        let result = AET.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_attack_element_zero() {
        let input_line = "self->attackElement = 0;";
        let expected_line = "self->attackElement = ELEMENT_NONE;";
        let result = AET.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_attack_element_zero_hex() {
        let input_line = "self->attackElement = 0x0;";
        let expected_line = "self->attackElement = ELEMENT_NONE;";
        let result = AET.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_attack_element_flags() {
        let input_line = "self->attackElement = ELEMENT_DARK;";
        let expected_line = "self->attackElement = ELEMENT_DARK;";
        let result = AET.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_attack_element_set() {
        let input_line = "self->attackElement |= 0x80;";
        let expected_line = "self->attackElement |= ELEMENT_POISON;";
        let result = AET.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_attack_element_clear() {
        let input_line = "self->attackElement &= 0xFFFF7FFF;";
        let expected_line = "self->attackElement &= ~ELEMENT_FIRE;";
        let result = AET.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_attack_element_clear_many() {
        let input_line = "self->attackElement &= 0xFFFF7BFF;";
        let expected_line = "self->attackElement &= ~(ELEMENT_FIRE | ELEMENT_WATER);";
        let result = AET.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_attack_element_inverted_many() {
        let input_line = "self->attackElement &= ~0x300;";
        let expected_line = "self->attackElement &= ~(ELEMENT_STONE | ELEMENT_CURSE);";
        let result = AET.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_equality() {
        let input_line = "if (self->attackElement == 256) {";
        let expected_line = "if (self->attackElement == ELEMENT_CURSE) {";
        let result = AET.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_inequality() {
        let input_line = "if (self->attackElement != 256) {";
        let expected_line = "if (self->attackElement != ELEMENT_CURSE) {";
        let result = AET.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }
}
