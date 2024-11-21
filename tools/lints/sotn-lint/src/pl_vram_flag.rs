use lazy_static::lazy_static;

use crate::bit_flag_line_transformer::BitFlagLineTransformer;
use crate::line_transformer::LineTransformer;

pub struct PlayerVramFlagTransformer {
    transformer: BitFlagLineTransformer<u32>,
}

lazy_static! {
    static ref PLAYER_VRAM_FLAGS: [(u32, &'static str); 16] = [
        (1 << 0, "TOUCHING_GROUND"),
        (1 << 1, "TOUCHING_CEILING"),
        (1 << 2, "TOUCHING_R_WALL"),
        (1 << 3, "TOUCHING_L_WALL"),
        (1 << 4, "VRAM_UNK10"),
        (1 << 5, "IN_AIR_OR_EDGE"),
        (1 << 6, "VRAM_UNK40"),
        (1 << 7, "VRAM_UNK80"),
        (1 << 8, "VRAM_UNK100"),
        (1 << 9, "VRAM_UNK200"),
        (1 << 10, "VRAM_UNK400"),
        (1 << 11, "TOUCHING_CEILING_SLOPE"),
        (1 << 12, "STANDING_SLIGHT_SLOPE"),
        (1 << 13, "VRAM_UNK2000"),
        (1 << 14, "STANDING_RAISING_SLOPE"),
        (1 << 15, "STANDING_ANY_SLOPE")
    ];
}

impl PlayerVramFlagTransformer {
    pub fn new() -> Self {
        Self {
            transformer: BitFlagLineTransformer::<u32>::new(
                "pl_vram_flag",
                "0",
                &PLAYER_VRAM_FLAGS.iter().collect(),
            ),
        }
    }
}

impl LineTransformer for PlayerVramFlagTransformer {
    fn transform_line(&self, line: &str) -> String {
        self.transformer.transform_line(line)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use once_cell::sync::Lazy;

    static DMT: Lazy<PlayerVramFlagTransformer> = Lazy::new(|| PlayerVramFlagTransformer::new());

    #[test]
    fn test_pl_vram_flag_hex() {
        let input_line = "g_Player.pl_vram_flag = 0x80;";
        let expected_line = "g_Player.pl_vram_flag = VRAM_UNK80;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_pl_vram_flag_decimal() {
        let input_line = "g_Player.pl_vram_flag = 32;";
        let expected_line = "g_Player.pl_vram_flag = IN_AIR_OR_EDGE;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_pl_vram_flag_zero() {
        let input_line = "g_Player.pl_vram_flag = 0;";
        let expected_line = "g_Player.pl_vram_flag = 0;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_pl_vram_flag_zero_hex() {
        let input_line = "g_Player.pl_vram_flag = 0x0;";
        let expected_line = "g_Player.pl_vram_flag = 0;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_pl_vram_flag_flags() {
        let input_line = "g_Player.pl_vram_flag = TOUCHING_CEILING_SLOPE;";
        let expected_line = "g_Player.pl_vram_flag = TOUCHING_CEILING_SLOPE;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_pl_vram_flag_set() {
        let input_line = "g_Player.pl_vram_flag |= 0x8000;";
        let expected_line = "g_Player.pl_vram_flag |= STANDING_ANY_SLOPE;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_pl_vram_flag_clear() {
        let input_line = "g_Player.pl_vram_flag &= 0xFFFFBFFF;";
        let expected_line = "g_Player.pl_vram_flag &= ~STANDING_RAISING_SLOPE;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_pl_vram_flag_clear_many() {
        let input_line = "g_Player.pl_vram_flag &= 0xFFFF3FFF;";
        let expected_line =
            "g_Player.pl_vram_flag &= ~(STANDING_ANY_SLOPE | STANDING_RAISING_SLOPE);";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_pl_vram_flag_inverted_many() {
        let input_line = "g_Player.pl_vram_flag &= ~0x300;";
        let expected_line = "g_Player.pl_vram_flag &= ~(VRAM_UNK200 | VRAM_UNK100);";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_equality() {
        let input_line = "if (g_Player.pl_vram_flag == 8) {";
        let expected_line = "if (g_Player.pl_vram_flag == TOUCHING_L_WALL) {";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_inequality() {
        let input_line = "if (g_Player.pl_vram_flag != 8) {";
        let expected_line = "if (g_Player.pl_vram_flag != TOUCHING_L_WALL) {";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }
}
