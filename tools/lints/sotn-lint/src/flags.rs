use lazy_static::lazy_static;

use crate::line_transformer::LineTransformer;
use crate::bit_flag_line_transformer::BitFlagLineTransformer;

pub struct FlagsTransformer {
    transformer: BitFlagLineTransformer<u32>,
}

lazy_static! {
    static ref FLAGS: [(u32, &'static str); 28] = [
        (1 << 4, "FLAG_UNK_10"),
        (1 << 5, "FLAG_UNK_20"),
        (1 << 6, "FLAG_UNK_40"),
        (1 << 7, "FLAG_UNK_80"),
        (1 << 8, "FLAG_DEAD"),
        (1 << 9, "FLAG_UNK_200"),
        (1 << 10, "FLAG_UNK_400"),
        (1 << 11, "FLAG_UNK_800"),
        (1 << 12, "FLAG_UNK_1000"),
        (1 << 13, "FLAG_UNK_2000"),
        (1 << 14, "FLAG_UNK_4000"),
        (1 << 15, "FLAG_UNK_8000"),
        (1 << 16, "FLAG_UNK_10000"),
        (1 << 17, "FLAG_UNK_20000"),
        (1 << 18, "FLAG_POS_PLAYER_LOCKED"),
        (1 << 19, "FLAG_UNK_80000"),
        (1 << 20, "FLAG_UNK_100000"),
        (1 << 21, "FLAG_UNK_00200000"),
        (1 << 22, "FLAG_UNK_400000"),
        (1 << 23, "FLAG_HAS_PRIMS"),
        (1 << 24, "FLAG_NOT_AN_ENEMY"),
        (1 << 25, "FLAG_UNK_02000000"),
        (1 << 26, "FLAG_KEEP_ALIVE_OFFCAMERA"),
        (1 << 27, "FLAG_POS_CAMERA_LOCKED"),
        (1 << 28, "FLAG_UNK_10000000"),
        (1 << 29, "FLAG_UNK_20000000"),
        (1 << 30, "FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA"),
        (1 << 31, "FLAG_DESTROY_IF_OUT_OF_CAMERA"),
    ];
}

impl FlagsTransformer {
    pub fn new() -> Self {
        Self {
            transformer: BitFlagLineTransformer::<u32>::new(
                "flags", "0", &FLAGS.iter().collect()),
        }
    }
}

impl LineTransformer for FlagsTransformer {
    fn transform_line(&self, line: &str) -> String {
        if line.contains("g_BgLayers") ||
            line.contains("g_Tilemap") {
            return line.to_string();
        }
        self.transformer.transform_line(line)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use once_cell::sync::Lazy;

    static FT: Lazy<FlagsTransformer> = Lazy::new(|| FlagsTransformer::new());

    #[test]
    fn test_flags_hex() {
        let input_line = "self->flags = 0x04070000;";
        let expected_line = "self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000 | FLAG_UNK_10000;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_decimal() {
        let input_line = "self->flags = 8781824;";
        let expected_line = "self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_zero() {
        let input_line = "self->flags = 0;";
        let expected_line = "self->flags = 0;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_zero_hex() {
        let input_line = "self->flags = 0x0;";
        let expected_line = "self->flags = 0;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_flags() {
        let input_line = "self->flags = FLAG_HAS_PRIMS;";
        let expected_line = "self->flags = FLAG_HAS_PRIMS;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_set() {
        let input_line = "self->flags |= 0x2000;";
        let expected_line = "self->flags |= FLAG_UNK_2000;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_clear() {
        let input_line = "PLAYER.flags &= 0xFF7FFFFF;";
        let expected_line = "PLAYER.flags &= ~FLAG_HAS_PRIMS;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_clear_many() {
        let input_line = "self->flags &= 0xFF7FCFFF;";
        let expected_line = "self->flags &= ~(FLAG_HAS_PRIMS | FLAG_UNK_2000 | FLAG_UNK_1000);";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_inverted_constant() {
        let input_line = "self->flags &= ~256;";
        let expected_line = "self->flags &= ~FLAG_DEAD;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_invalid_flags_ignored() {
        let input_line = "self->flags = 0xf;";
        let expected_line = "self->flags = 0xf;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_not_gb_layers_flags() {
        let input_line = "g_BgLayers[0]->flags &= ~4;";
        let expected_line = "g_BgLayers[0]->flags &= ~4;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_not_tilemap_flags() {
        let input_line = "g_Tilemap->flags &= ~4;";
        let expected_line = "g_Tilemap->flags &= ~4;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_equality() {
        let input_line = "if (self->flags == 256) {";
        let expected_line = "if (self->flags == FLAG_DEAD) {";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_inequality() {
        let input_line = "if (self->flags != 256) {";
        let expected_line = "if (self->flags != FLAG_DEAD) {";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_bitwise_and() {
        let input_line = "if (D_8003C708.flags & 0x60) {";
        let expected_line = "if (D_8003C708.flags & (FLAG_UNK_40 | FLAG_UNK_20)) {";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_bitwise_or() {
        let input_line = "D_8003C708.flags | 0x40;";
        let expected_line = "D_8003C708.flags | FLAG_UNK_40;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_bitwise_xor() {
        let input_line = "D_8003C708.flags ^ 0x40;";
        let expected_line = "D_8003C708.flags ^ FLAG_UNK_40;";
        let result = FT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }
}
