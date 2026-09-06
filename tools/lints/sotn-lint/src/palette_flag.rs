use lazy_static::lazy_static;
use regex::Regex;

use crate::line_transformer::LineTransformer;

pub struct PaletteFlagTransformer;

lazy_static! {
    // Any identifier ending in `palette`/`Palette` compared or assigned a raw
    // 16 bit palette index that has PAL_UNK_FLAG (0x8000) set. The trailing
    // terminator keeps us out of larger expressions such as
    // `self->palette = tbl[i] + ((u16)randRes | 0x8110);`.
    static ref PALETTE_REGEX: Regex = Regex::new(
        r"(?P<lhs>\b[0-9A-Za-z_]*[Pp]alette\b\s*(?P<op>==|!=|<=|>=|\|=|=|<|>|&)\s*)0x(?P<value>8[0-9A-Fa-f]{3})(?P<tail>[;,)\s]|$)"
    )
    .unwrap();
}

impl LineTransformer for PaletteFlagTransformer {
    fn transform_line(&self, line: &str) -> String {
        PALETTE_REGEX
            .replace_all(line, |caps: &regex::Captures| {
                let lhs = &caps["lhs"];
                let tail = &caps["tail"];
                let index = caps["value"][1..].trim_start_matches('0');

                if index.is_empty() {
                    // 0x8000 on its own is just the flag, with no palette index.
                    return format!("{}PAL_UNK_FLAG{}", lhs, tail);
                }

                if &caps["op"] == "&" {
                    // `palette & 0x8195` is a mask, not a flagged index.
                    return caps[0].to_string();
                }

                format!("{}PAL_FLAG(0x{}){}", lhs, index, tail)
            })
            .to_string()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn transform(line: &str) -> String {
        PaletteFlagTransformer.transform_line(line)
    }

    #[test]
    fn test_assignment() {
        // from src/st/rno4/unk_44B0C.c
        assert_eq!(
            transform("            self->palette = 0x8195;"),
            "            self->palette = PAL_FLAG(0x195);"
        );
    }

    #[test]
    fn test_leading_zero_trimmed() {
        // from src/st/rno1/unk_26178.c
        assert_eq!(
            transform("        self->palette = 0x8004;"),
            "        self->palette = PAL_FLAG(0x4);"
        );
    }

    #[test]
    fn test_hex_case_preserved() {
        // from src/boss/bo6/us_3E79C.c
        assert_eq!(
            transform("            self->palette = 0x815F;"),
            "            self->palette = PAL_FLAG(0x15F);"
        );
        assert_eq!(
            transform("            self->palette = 0x815f;"),
            "            self->palette = PAL_FLAG(0x15f);"
        );
    }

    #[test]
    fn test_dot_access() {
        // from src/boss/bo6/richter.c
        assert_eq!(
            transform("    RIC.palette = 0x8220;"),
            "    RIC.palette = PAL_FLAG(0x220);"
        );
    }

    #[test]
    fn test_bare_local() {
        // from src/boss/bo6/us_3E79C.c
        assert_eq!(
            transform("        palette = 0x810D;"),
            "        palette = PAL_FLAG(0x10D);"
        );
    }

    #[test]
    fn test_designated_initializer() {
        // from src/st/rno3/e_room_bg.c
        assert_eq!(
            transform("     .palette = 0x8068,"),
            "     .palette = PAL_FLAG(0x68),"
        );
    }

    #[test]
    fn test_other_palette_fields() {
        // from src/boss/bo6/us_39144.c
        assert_eq!(
            transform("        g_Ric.damagePalette = 0x8166;"),
            "        g_Ric.damagePalette = PAL_FLAG(0x166);"
        );
        assert_eq!(
            transform("    self->childPalette = 0x8166;"),
            "    self->childPalette = PAL_FLAG(0x166);"
        );
    }

    #[test]
    fn test_equality_in_parens() {
        // from src/dra/7879C.c
        assert_eq!(
            transform(
                "    if (((PLAYER.step == Player_SpellHellfire) && (PLAYER.palette == 0x810D)) ||"
            ),
            "    if (((PLAYER.step == Player_SpellHellfire) && (PLAYER.palette == PAL_FLAG(0x10D))) ||"
        );
    }

    #[test]
    fn test_comparisons() {
        assert_eq!(
            transform("        if (self->palette > 0x8058) {"),
            "        if (self->palette > PAL_FLAG(0x58)) {"
        );
        assert_eq!(
            transform("        if (self->palette != 0x8058) {"),
            "        if (self->palette != PAL_FLAG(0x58)) {"
        );
        assert_eq!(
            transform("        if (self->palette <= 0x8058) {"),
            "        if (self->palette <= PAL_FLAG(0x58)) {"
        );
    }

    #[test]
    fn test_or_assign() {
        assert_eq!(
            transform("        self->palette |= 0x8058;"),
            "        self->palette |= PAL_FLAG(0x58);"
        );
    }

    #[test]
    fn test_bare_flag() {
        // from src/st/rno0/e_gorgon.c
        assert_eq!(
            transform("        if (g_CurrentEntity->palette & 0x8000) {"),
            "        if (g_CurrentEntity->palette & PAL_UNK_FLAG) {"
        );
        assert_eq!(
            transform("        self->palette = 0x8000;"),
            "        self->palette = PAL_UNK_FLAG;"
        );
    }

    #[test]
    fn test_mask_left_alone() {
        // masking out an index is not a flagged palette value
        let line = "        if (self->palette & 0x81FF) {";
        assert_eq!(transform(line), line);
    }

    #[test]
    fn test_complex_expression_left_alone() {
        // from src/weapon/w_030.c
        let line = "        self->palette = D_D6000_8017A640[s0] + ((u16)randRes | 0x8110);";
        assert_eq!(transform(line), line);
    }

    #[test]
    fn test_unflagged_value_left_alone() {
        let line = "        self->palette = 0x0195;";
        assert_eq!(transform(line), line);
    }

    #[test]
    fn test_already_wrapped_left_alone() {
        // from src/boss/rbo5/doors.c
        let line = "        self->palette = PAL_FLAG(0x4F);";
        assert_eq!(transform(line), line);
    }

    #[test]
    fn test_non_palette_identifier_left_alone() {
        let line = "        self->animFrameIdx = 0x8195;";
        assert_eq!(transform(line), line);
    }

    #[test]
    fn test_flag_macro_definition_left_alone() {
        // from include/game.h
        let line = "#define PAL_UNK_FLAG 0x8000";
        assert_eq!(transform(line), line);
    }
}
