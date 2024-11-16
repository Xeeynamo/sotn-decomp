use lazy_static::lazy_static;

use crate::bit_flag_line_transformer::BitFlagLineTransformer;
use crate::line_transformer::LineTransformer;

pub struct PlayerStatusTransformer {
    transformer: BitFlagLineTransformer<u32>,
}

lazy_static! {
    static ref PLAYER_STATUSES: [(u32, &'static str); 31] = [
        (1 << 0, "PLAYER_STATUS_BAT_FORM"),
        (1 << 1, "PLAYER_STATUS_MIST_FORM"),
        (1 << 2, "PLAYER_STATUS_WOLF_FORM"),
        (1 << 3, "PLAYER_STATUS_UNK8"),
        (1 << 4, "PLAYER_STATUS_UNK10"),
        (1 << 5, "PLAYER_STATUS_UNK_20"),
        (1 << 6, "PLAYER_STATUS_UNK40"),
        (1 << 7, "PLAYER_STATUS_STONE"),
        (1 << 8, "PLAYER_STATUS_UNK100"),
        (1 << 9, "PLAYER_STATUS_UNK200"),
        (1 << 10, "PLAYER_STATUS_UNK400"),
        (1 << 11, "PLAYER_STATUS_UNK800"),
        (1 << 12, "PLAYER_STATUS_UNK1000"),
        (1 << 13, "PLAYER_STATUS_UNK2000"),
        (1 << 14, "PLAYER_STATUS_POISON"),
        (1 << 15, "PLAYER_STATUS_CURSE"),
        (1 << 16, "PLAYER_STATUS_UNK10000"),
        (1 << 17, "PLAYER_STATUS_UNK20000"),
        (1 << 18, "PLAYER_STATUS_ZERO_HP"),
        (1 << 19, "PLAYER_STATUS_UNK80000"),
        (1 << 20, "PLAYER_STATUS_UNK100000"),
        (1 << 21, "PLAYER_STATUS_UNK200000"),
        (1 << 22, "PLAYER_STATUS_UNK400000"),
        (1 << 23, "PLAYER_STATUS_UNK800000"),
        (1 << 24, "PLAYER_STATUS_AXEARMOR"),
        (1 << 25, "PLAYER_STATUS_ABSORB_BLOOD"),
        (1 << 26, "PLAYER_STATUS_UNK4000000"),
        (1 << 27, "NO_AFTERIMAGE"),
        (1 << 28, "PLAYER_STATUS_UNK10000000"),
        (1 << 29, "PLAYER_STATUS_UNK40000000"),
        (1 << 30, "PLAYER_STATUS_UNK80000000")
    ];
}

impl PlayerStatusTransformer {
    pub fn new() -> Self {
        Self {
            transformer: BitFlagLineTransformer::<u32>::new(
                "status",
                "0",
                &PLAYER_STATUSES.iter().collect(),
            ),
        }
    }
}

impl LineTransformer for PlayerStatusTransformer {
    fn transform_line(&self, line: &str) -> String {
        self.transformer.transform_line(line)
    }
}

#[cfg(test)]
mod tests {
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
        let expected_line = "g_Player.status = PLAYER_STATUS_UNK_20;";
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
