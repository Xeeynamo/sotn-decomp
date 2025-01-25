use lazy_static::lazy_static;

use crate::line_transformer::LineTransformer;
use crate::enum_line_transformer::EnumLineTransformer;

pub struct PrimitiveTypeTransformer {
    transformer: EnumLineTransformer<u16>,
}

lazy_static! {
    static ref TYPES: [(u16, &'static str); 12] = [
        (0, "PRIM_NONE"),
        (1, "PRIM_TILE"),
        (2, "PRIM_LINE_G2"),
        (3, "PRIM_G4"),
        (4, "PRIM_GT4"),
        (5, "PRIM_GT3"),
        (6, "PRIM_SPRT"),
        (7, "PRIM_ENV"),
        (8, "FLAG_DRAW_UNK100"),
        (0x11, "PRIM_TITLE_ALT"),
        (0x12, "PRIM_LINE_G2"),
        (0x13, "PRIM_G4_ALT"),
    ];
}

impl PrimitiveTypeTransformer {
    pub fn new() -> Self {
        Self {
            transformer: EnumLineTransformer::<u16>::new(
                Some("prim"), "type", &TYPES.iter().collect()),
        }
    }
}

impl LineTransformer for PrimitiveTypeTransformer {
    fn transform_line(&self, line: &str) -> String {
        self.transformer.transform_line(line)
    }
}


#[cfg(test)]
mod tests {
    use super::*;
    use once_cell::sync::Lazy;

    static DMT: Lazy<PrimitiveTypeTransformer> = Lazy::new(|| PrimitiveTypeTransformer::new());

    #[test]
    fn test_type_hex() {
        let input_line = "prim->type = 0x5;";
        let expected_line = "prim->type = PRIM_GT3;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_type_decimal() {
        let input_line = "prim->type = 0x6, ";
        let expected_line = "prim->type = PRIM_SPRT, ";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_type_zero_hex() {
        let input_line = "(prim->type == 0x0)";
        let expected_line = "(prim->type == PRIM_NONE)";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }

    #[test]
    fn test_type_not_prim() {
        let input_line = "quad->type == 5;";
        let expected_line = "quad->type == 5;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, expected_line)
    }
}
