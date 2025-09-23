use crate::line_transformer::LineTransformer;
use crate::bit_flag_line_transformer::BitFlagLineTransformer;

pub struct AttackElementTransformer {
    transformer: BitFlagLineTransformer<u32>,
}

static ATTACK_ELEMENTS: [(u32, &'static str); 12] = [
    (0x20, "ELEMENT_HIT"),
    (0x40, "ELEMENT_CUT"),
    (0x80, "ELEMENT_POISON"),
    (0x100, "ELEMENT_CURSE"),
    (0x200, "ELEMENT_STONE"),
    (0x400, "ELEMENT_WATER"),
    (0x800, "ELEMENT_DARK"),
    (0x1000, "ELEMENT_HOLY"),
    (0x2000, "ELEMENT_ICE"),
    (0x4000, "ELEMENT_THUNDER"),
    (0x8000, "ELEMENT_FIRE"),
    (0x10000, "ELEMENT_UNK_10000"),
];

impl AttackElementTransformer {
    pub fn new() -> Self {
        Self {
            transformer: BitFlagLineTransformer::<u32>::new(
                "attackElement", "ELEMENT_NONE", &ATTACK_ELEMENTS.iter().collect()),
        }
    }
}

impl LineTransformer for AttackElementTransformer {
    fn transform_line(&self, line: &str) -> String {
        self.transformer.transform_line(line)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use once_cell::sync::Lazy;

    static AET: Lazy<AttackElementTransformer> = Lazy::new(|| AttackElementTransformer::new());

    #[test]
    fn test_attack_element_hex() {
        let input_line = "self->attackElement = 0x60;";
        let expected_line = "self->attackElement = ELEMENT_CUT | ELEMENT_HIT;";
        let result = AET.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_attack_element_decimal() {
        let input_line = "self->attackElement = 96;";
        let expected_line = "self->attackElement = ELEMENT_CUT | ELEMENT_HIT;";
        let result = AET.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_attack_element_zero() {
        let input_line = "self->attackElement = 0;";
        let expected_line = "self->attackElement = ELEMENT_NONE;";
        let result = AET.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_attack_element_zero_hex() {
        let input_line = "self->attackElement = 0x0;";
        let expected_line = "self->attackElement = ELEMENT_NONE;";
        let result = AET.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_attack_element_flags() {
        let input_line = "self->attackElement = ELEMENT_DARK;";
        let expected_line = "self->attackElement = ELEMENT_DARK;";
        let result = AET.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_attack_element_set() {
        let input_line = "self->attackElement |= 0x80;";
        let expected_line = "self->attackElement |= ELEMENT_POISON;";
        let result = AET.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_attack_element_clear() {
        let input_line = "self->attackElement &= 0xFFFF7FFF;";
        let expected_line = "self->attackElement &= ~ELEMENT_FIRE;";
        let result = AET.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_attack_element_clear_many() {
        let input_line = "self->attackElement &= 0xFFFF7BFF;";
        let expected_line = "self->attackElement &= ~(ELEMENT_FIRE | ELEMENT_WATER);";
        let result = AET.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_attack_element_inverted_many() {
        let input_line = "self->attackElement &= ~0x300;";
        let expected_line = "self->attackElement &= ~(ELEMENT_STONE | ELEMENT_CURSE);";
        let result = AET.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_equality() {
        let input_line = "if (self->attackElement == 256) {";
        let expected_line = "if (self->attackElement == ELEMENT_CURSE) {";
        let result = AET.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_inequality() {
        let input_line = "if (self->attackElement != 256) {";
        let expected_line = "if (self->attackElement != ELEMENT_CURSE) {";
        let result = AET.transform_line(input_line);
        assert_eq!(result, expected_line)
    }
}
