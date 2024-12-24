use lazy_static::lazy_static;

use crate::line_transformer::LineTransformer;
use crate::bit_flag_line_transformer::BitFlagLineTransformer;

pub struct ColliderEffectsTransformer {
    transformer: BitFlagLineTransformer<u16>,
}

lazy_static! {
    static ref COLLIDER_EFFECTS: [(u16, &'static str); 16] = [
        (1 << 0, "EFFECT_SOLID"),
        (1 << 1, "EFFECT_UNK_0002"),
        (1 << 2, "EFFECT_QUICKSAND"),
        (1 << 3, "EFFECT_WATER"),
        (1 << 4, "EFFECT_MIST_ONLY"),
        (1 << 5, "EFFECT_UNK_0020"),
        (1 << 6, "EFFECT_SOLID_FROM_ABOVE"),
        (1 << 7, "EFFECT_SOLID_FROM_BELOW"),
        (1 << 8, "EFFECT_UNK_0100"),
        (1 << 9, "EFFECT_UNK_0200"),
        (1 << 10, "EFFECT_UNK_0400"),
        (1 << 11, "EFFECT_UNK_0800"),
        (1 << 12, "EFFECT_UNK_1000"),
        (1 << 13, "EFFECT_UNK_2000"),
        (1 << 14, "EFFECT_UNK_4000"),
        (1 << 15, "EFFECT_UNK_8000"),
    ];
}

impl ColliderEffectsTransformer {
    pub fn new() -> Self {
        Self {
            transformer: BitFlagLineTransformer::<u16>::new(
                "effects", "EFFECT_NONE", &COLLIDER_EFFECTS.iter().collect()),
        }
    }
}

impl LineTransformer for ColliderEffectsTransformer {
    fn transform_line(&self, line: &str) -> String {
        self.transformer.transform_line(line)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use once_cell::sync::Lazy;

    static FT: Lazy<ColliderEffectsTransformer> = Lazy::new(|| ColliderEffectsTransformer::new());

    #[test]
    fn test_draw_flags_hex() {
        let input_line = "self->effects = 0x5;";
        let expected_line = "self->effects = EFFECT_QUICKSAND | EFFECT_SOLID;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_decimal() {
        let input_line = "self->effects = 5;";
        let expected_line = "self->effects = EFFECT_QUICKSAND | EFFECT_SOLID;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_zero() {
        let input_line = "self->effects = 0;";
        let expected_line = "self->effects = EFFECT_NONE;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_zero_hex() {
        let input_line = "self->effects = 0x0;";
        let expected_line = "self->effects = EFFECT_NONE;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_draw_flags_flags() {
        let input_line = "self->effects = EFFECT_WATER;";
        let expected_line = "self->effects = EFFECT_WATER;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }
}
