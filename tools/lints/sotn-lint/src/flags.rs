use crate::define_flag_transformer;

define_flag_transformer!(FlagsTransformer<u32>, flags, [
    0                                       = default,
    FLAG_UNK_10                             = BIT(4),
    FLAG_UNK_20                             = BIT(5),
    FLAG_UNK_40                             = BIT(6),
    FLAG_UNK_80                             = BIT(7),
    FLAG_DEAD                               = BIT(8),
    FLAG_UNK_200                            = BIT(9),
    FLAG_UNK_400                            = BIT(10),
    FLAG_UNK_800                            = BIT(11),
    FLAG_UNK_1000                           = BIT(12),
    FLAG_UNK_2000                           = BIT(13),
    FLAG_UNK_4000                           = BIT(14),
    FLAG_UNK_8000                           = BIT(15),
    FLAG_UNK_10000                          = BIT(16),
    FLAG_UNK_20000                          = BIT(17),
    FLAG_POS_PLAYER_LOCKED                  = BIT(18),
    FLAG_UNK_80000                          = BIT(19),
    FLAG_UNK_100000                         = BIT(20),
    FLAG_UNK_00200000                       = BIT(21),
    FLAG_UNK_400000                         = BIT(22),
    FLAG_HAS_PRIMS                          = BIT(23),
    FLAG_NOT_AN_ENEMY                       = BIT(24),
    FLAG_UNK_02000000                       = BIT(25),
    FLAG_KEEP_ALIVE_OFFCAMERA               = BIT(26),
    FLAG_POS_CAMERA_LOCKED                  = BIT(27),
    FLAG_UNK_10000000                       = BIT(28),
    FLAG_UNK_20000000                       = BIT(29),
    FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA    = BIT(30),
    FLAG_DESTROY_IF_OUT_OF_CAMERA           = BIT(31),
]);

#[cfg(test)]
mod tests {
    use crate::line_transformer::LineTransformer;

    use super::*;
    use once_cell::sync::Lazy;

    static FT: Lazy<FlagsTransformer> = Lazy::new(|| FlagsTransformer::new());

    #[test]
    fn test_flags_hex() {
        let input_line = "self->flags = 0x04070000;";
        let expected_line = "self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000 | FLAG_UNK_10000;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_decimal() {
        let input_line = "self->flags = 8781824;";
        let expected_line = "self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_zero() {
        let input_line = "self->flags = 0;";
        let expected_line = "self->flags = 0;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_zero_hex() {
        let input_line = "self->flags = 0x0;";
        let expected_line = "self->flags = 0;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_flags() {
        let input_line = "self->flags = FLAG_HAS_PRIMS;";
        let expected_line = "self->flags = FLAG_HAS_PRIMS;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_set() {
        let input_line = "self->flags |= 0x2000;";
        let expected_line = "self->flags |= FLAG_UNK_2000;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_clear() {
        let input_line = "PLAYER.flags &= 0xFF7FFFFF;";
        let expected_line = "PLAYER.flags &= ~FLAG_HAS_PRIMS;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_clear_many() {
        let input_line = "self->flags &= 0xFF7FCFFF;";
        let expected_line = "self->flags &= ~(FLAG_HAS_PRIMS | FLAG_UNK_2000 | FLAG_UNK_1000);";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_inverted_constant() {
        let input_line = "self->flags &= ~256;";
        let expected_line = "self->flags &= ~FLAG_DEAD;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_invalid_flags_ignored() {
        let input_line = "self->flags = 0xf;";
        let expected_line = "self->flags = 0xf;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_not_gb_layers_flags() {
        let input_line = "g_BgLayers[0]->flags &= ~4;";
        let expected_line = "g_BgLayers[0]->flags &= ~4;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_flags_not_tilemap_flags() {
        let input_line = "g_Tilemap->flags &= ~4;";
        let expected_line = "g_Tilemap->flags &= ~4;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_equality() {
        let input_line = "if (self->flags == 256) {";
        let expected_line = "if (self->flags == FLAG_DEAD) {";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_inequality() {
        let input_line = "if (self->flags != 256) {";
        let expected_line = "if (self->flags != FLAG_DEAD) {";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_bitwise_and() {
        let input_line = "if (D_8003C708.flags & 0x60) {";
        let expected_line = "if (D_8003C708.flags & (FLAG_UNK_40 | FLAG_UNK_20)) {";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_bitwise_or() {
        let input_line = "D_8003C708.flags | 0x40;";
        let expected_line = "D_8003C708.flags | FLAG_UNK_40;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_bitwise_xor() {
        let input_line = "D_8003C708.flags ^ 0x40;";
        let expected_line = "D_8003C708.flags ^ FLAG_UNK_40;";
        let result = FT.transform_line_owned(input_line);
        assert_eq!(result, expected_line)
    }
}
