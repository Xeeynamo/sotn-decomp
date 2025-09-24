
use crate::define_enum_transformer;


define_enum_transformer!(PrimitiveTypeTransformer<u16>, prim->type, [
    PRIM_NONE           = 0,
    PRIM_TILE           = 1,
    PRIM_LINE_G2        = 2,
    PRIM_G4             = 3,
    PRIM_GT4            = 4,
    PRIM_GT3            = 5,
    PRIM_SPRT           = 6,
    PRIM_ENV            = 7,
    FLAG_DRAW_UNK100    = 8,
    PRIM_TITLE_ALT      = 0x11,
    PRIM_LINE_G2        = 0x12,
    PRIM_G4_ALT         = 0x13,
]);


#[cfg(test)]
mod tests {
    use crate::line_transformer::LineTransformer;

    use super::*;
    use once_cell::sync::Lazy;

    static DMT: Lazy<PrimitiveTypeTransformer> = Lazy::new(|| PrimitiveTypeTransformer::default());

    #[test]
    fn test_type_hex() {
        let input_line = "prim->type = 0x5;";
        let expected_line = "prim->type = PRIM_GT3;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result.as_deref(), Some(expected_line))
    }

    #[test]
    fn test_type_decimal() {
        let input_line = "prim->type = 0x6, ";
        let expected_line = "prim->type = PRIM_SPRT, ";
        let result = DMT.transform_line(input_line);
        assert_eq!(result.as_deref(), Some(expected_line))
    }

    #[test]
    fn test_type_zero_hex() {
        let input_line = "(prim->type == 0x0)";
        let expected_line = "(prim->type == PRIM_NONE)";
        let result = DMT.transform_line(input_line);
        assert_eq!(result.as_deref(), Some(expected_line))
    }

    #[test]
    fn test_type_not_prim() {
        let input_line = "quad->type == 5;";
        let _expected_line = "quad->type == 5;";
        let result = DMT.transform_line(input_line);
        assert_eq!(result, None)
    }
}
