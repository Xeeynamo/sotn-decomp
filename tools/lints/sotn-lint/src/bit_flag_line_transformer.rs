use std::cmp::Eq;
use std::cmp::Ord;
use std::fmt::Debug;
use std::mem::size_of;
use std::str::FromStr;
use std::vec::Vec;
use num::PrimInt;
use num::Unsigned;
use regex::Regex;

use crate::line_transformer::LineTransformer;

pub trait EnumValue: Unsigned + 'static + Sync + Eq + Ord + PrimInt + FromStr { }

impl EnumValue for u8 where <u8 as FromStr>::Err: Debug { }
impl EnumValue for u16 where <u16 as FromStr>::Err: Debug { }
impl EnumValue for u32 where <u32 as FromStr>::Err: Debug { }
impl EnumValue for u64 where <u64 as FromStr>::Err: Debug { }

// `BitFlagLineTransformer` supports transforminging fields of
// an enum type to a boolean combination of the enum flags
// of that type.
//
// This supports transforming lines in the following forms:
//
//  * assignment:
//      self->field = 35;
//      self->field = 0x23;
//      s.field = 0x23;
//
//  * bitwise-OR assignment:
//      self->field |= 524288;
//      s.field |= 0x80000;
//
//  * bitwise-AND assignment:
//      self->field &= ~4;
//      self->field &= 0xFFFB;
//
//  * bitwise-XOR assignment:
//      self->field ^= ~4;
//      self->field ^= 0xFFFB;
//
//  * bitwise-OR
//      self->field | 0x8300;
//
//  * bitwise-AND
//      self->field & 0x8200;
//
//  * bitwise-XOR
//      self->field ^ 0x8400;
//
//  * equality
//      if (self->field == 8) {
//
//  * inequality
//      if (self->field != 8) {
//
// If a constant contains bits which are not represented by
// enum values, no transformation will be made.
pub struct BitFlagLineTransformer<U: EnumValue> where <U as FromStr>::Err: Debug {
    enum_values: Vec<&'static (U, &'static str)>,
    regex: Regex,
    default_value: &'static str,
    safe_mask: U,
}

impl<U: EnumValue> BitFlagLineTransformer<U> where <U as FromStr>::Err: Debug {
    pub fn new(field_name: &str, default_value: &'static str, enum_values: &Vec<&'static (U, &'static str)>) -> Self {
        let mut _enum_values: Vec<&'static (U, &'static str)> = Vec::new();
        _enum_values.extend_from_slice(&enum_values[..]);
        _enum_values.sort_by(|(a, _), (b, _)| b.cmp(a));
        let pattern = format!(r"([.>]{}\s*((?:(?:[&|=!^~]?)=)|(?:[&|^]))\s*)([~]?)((?:0x[A-Fa-f0-9]+)|0|(?:[1-9][0-9]*))([;),? ])", field_name.to_string());
        let regex = Regex::new(&pattern).unwrap();

        let safe_mask: U = enum_values.iter().fold(U::zero(), |mask, (bit, _)| mask | *bit);

        Self {
            enum_values: _enum_values,
            regex: regex,
            default_value: default_value,
            safe_mask: safe_mask,
        }
    }

    fn replace_enum(&self, captures: &regex::Captures) -> String {
        if let (Some(prefix), Some(operator), Some(field_value_string), Some(terminal_string)) = (
                captures.get(1).map(|m| m.as_str().to_string()),
                captures.get(2).map(|m| m.as_str().to_string()),
                captures.get(4).map(|m| m.as_str().to_string()),
                captures.get(5).map(|m| m.as_str().to_string())) {

            let inverted = captures.get(3).map(|m| m.as_str()) == Some("~");

            // if it starts with 0x, hex string, otherwise int
            let mut field_value: U;
            if field_value_string.starts_with("0x") {
                if let Ok(v) = U::from_str_radix(field_value_string.strip_prefix("0x").unwrap(), 16) {
                    field_value = v;
                } else {
                    return captures.get(0)
                        .map_or_else(|| "".to_string(), |m| m.as_str().to_string())
                }
            } else {
                field_value = field_value_string.parse::<U>().unwrap();
            }

            if inverted {
                field_value = !field_value;
            }

            let invert: String;
            if field_value.count_ones() > ((size_of::<U>() as u32) * 8 / 2) {
                invert = "~".to_string();
                field_value = !field_value;
            } else {
                invert = "".to_string();
            }

            // there are bits present which are not enum values, so ignore
            if !((field_value & !self.safe_mask).is_zero()) {
                return captures
                    .get(0)
                    .map_or_else(|| "".to_string(), |m| m.as_str().to_string());
            }

            let mut rvalue: String;
            if field_value.is_zero() {
                rvalue = self.default_value.to_string();
            } else {
                // n.b.! there may be values missing from the enums which would
                //       result in an incorrect value being produced.
                rvalue = self.enum_values.iter()
                    .map(|(mask, name)|
                        if !((*mask & field_value).is_zero()) {
                            Some(name)
                        } else {
                            None
                        })
                    .filter(|e| e.is_some())
                    .map(|e| *e.unwrap())
                    .collect::<Vec<&str>>()
                    .join(" | ");

                if field_value.count_ones() > 1 &&
                    (operator == "^" || operator == "&" || operator == "|" ||
                     invert == "~" || inverted) {
                    rvalue = format!("({})", rvalue);
                }
            }
            return format!("{}{}{}{}", prefix.to_string(), invert, rvalue, terminal_string);
        }
        captures
            .get(0)
            .map_or_else(|| "".to_string(), |m| m.as_str().to_string())
    }
}

impl<U: EnumValue> LineTransformer for BitFlagLineTransformer<U> where <U as FromStr>::Err: Debug {
    fn transform_line(&self, line: &str) -> String where {
        self.regex.replace_all(line, |captures: &regex::Captures| self.replace_enum(captures)).to_string()
    }
}
