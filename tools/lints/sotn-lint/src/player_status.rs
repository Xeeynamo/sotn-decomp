use crate::define_flag_transformer;


define_flag_transformer!(PlayerStatusTransformer<u32>, status, [
    0                           = default,
    PLAYER_STATUS_BAT_FORM      = BIT(0),
    PLAYER_STATUS_MIST_FORM     = BIT(1),
    PLAYER_STATUS_WOLF_FORM     = BIT(2),
    PLAYER_STATUS_UNK8          = BIT(3),
    PLAYER_STATUS_UNK10         = BIT(4),
    PLAYER_STATUS_CROUCH        = BIT(5),
    PLAYER_STATUS_UNK40         = BIT(6),
    PLAYER_STATUS_STONE         = BIT(7),
    PLAYER_STATUS_UNK100        = BIT(8),
    PLAYER_STATUS_UNK200        = BIT(9),
    PLAYER_STATUS_UNK400        = BIT(10),
    PLAYER_STATUS_UNK800        = BIT(11),
    PLAYER_STATUS_UNK1000       = BIT(12),
    PLAYER_STATUS_UNK2000       = BIT(13),
    PLAYER_STATUS_POISON        = BIT(14),
    PLAYER_STATUS_CURSE         = BIT(15),
    PLAYER_STATUS_UNK10000      = BIT(16),
    PLAYER_STATUS_UNK20000      = BIT(17),
    PLAYER_STATUS_DEAD          = BIT(18),
    PLAYER_STATUS_UNK80000      = BIT(19),
    PLAYER_STATUS_UNK100000     = BIT(20),
    PLAYER_STATUS_UNK200000     = BIT(21),
    PLAYER_STATUS_UNK400000     = BIT(22),
    PLAYER_STATUS_UNK800000     = BIT(23),
    PLAYER_STATUS_AXEARMOR      = BIT(24),
    PLAYER_STATUS_ABSORB_BLOOD  = BIT(25),
    PLAYER_STATUS_UNK4000000    = BIT(26),
    NO_AFTERIMAGE               = BIT(27),
    PLAYER_STATUS_UNK10000000   = BIT(28),
    PLAYER_STATUS_UNK40000000   = BIT(29),
    PLAYER_STATUS_UNK8000000    = BIT(30),
]);

#[cfg(test)]
mod tests {
    use crate::line_transformer::LineTransformer;

    use super::*;
    use once_cell::sync::Lazy;

    static DMT: Lazy<PlayerStatusTransformer> = Lazy::new(|| PlayerStatusTransformer::new());

    #[test]
    fn test_player_status_hex() {
        let input_line = "g_Player.status = 0x80;";
        let expected_line = "g_Player.status = PLAYER_STATUS_STONE;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_player_status_decimal() {
        let input_line = "g_Player.status = 32;";
        let expected_line = "g_Player.status = PLAYER_STATUS_CROUCH;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_player_status_zero() {
        let input_line = "g_Player.status = 0;";
        let expected_line = "g_Player.status = 0;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_player_status_zero_hex() {
        let input_line = "g_Player.status = 0x0;";
        let expected_line = "g_Player.status = 0;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_player_status_flags() {
        let input_line = "g_Player.status = PLAYER_STATUS_AXEARMOR;";
        let expected_line = "g_Player.status = PLAYER_STATUS_AXEARMOR;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_player_status_set() {
        let input_line = "g_Player.status |= 0x2000000;";
        let expected_line = "g_Player.status |= PLAYER_STATUS_ABSORB_BLOOD;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_player_status_clear() {
        let input_line = "g_Player.status &= 0xFFFF7FFF;";
        let expected_line = "g_Player.status &= ~PLAYER_STATUS_CURSE;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_player_status_clear_many() {
        let input_line = "g_Player.status &= 0xFFFF6FFF;";
        let expected_line = "g_Player.status &= ~(PLAYER_STATUS_CURSE | PLAYER_STATUS_UNK1000);";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_player_status_inverted_many() {
        let input_line = "g_Player.status &= ~0x300;";
        let expected_line = "g_Player.status &= ~(PLAYER_STATUS_UNK200 | PLAYER_STATUS_UNK100);";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_equality() {
        let input_line = "if (g_Player.status == 8) {";
        let expected_line = "if (g_Player.status == PLAYER_STATUS_UNK8) {";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_inequality() {
        let input_line = "if (g_Player.status != 8) {";
        let expected_line = "if (g_Player.status != PLAYER_STATUS_UNK8) {";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    // TODO: Implement PLAYER_STATUS_TRANSFORM 0x7 flag
    //
    // #[test]
    // fn test_player_status_combo_flag() {
    //     let input_line = "g_Player.status = 0x7;";
    //     let expected_line = "g_Player.status = PLAYER_STATUS_TRANSFORM;";
    //     let result = DMT.transform_line(input_line);
    //     assert_eq!(result, expected_line)
    // }
}
