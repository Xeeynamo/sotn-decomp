use std::cmp::Eq;
use std::cmp::Ord;
use std::fmt::Debug;
use std::str::FromStr;
use std::vec::Vec;
use num::PrimInt;
use num::Unsigned;
use regex::Regex;

use crate::line_transformer::LineTransformer;
use crate::enum_statement::EnumStatementMatcher;

pub trait EnumValue: Unsigned + 'static + Sync + Eq + Ord + PrimInt + FromStr { }

impl EnumValue for u8 where <u8 as FromStr>::Err: Debug { }
impl EnumValue for u16 where <u16 as FromStr>::Err: Debug { }
impl EnumValue for u32 where <u32 as FromStr>::Err: Debug { }
impl EnumValue for u64 where <u64 as FromStr>::Err: Debug { }

pub struct EnumLineTransformer<U: EnumValue> where <U as FromStr>::Err: Debug {
    enum_values: Vec<&'static (U, &'static str)>,
    regex: Regex,
}

impl<U: EnumValue> EnumLineTransformer<U> where <U as FromStr>::Err: Debug {
    pub fn new(variable_name: Option<&str>, field_name: &str, enum_values: &Vec<&'static (U, &'static str)>) -> Self {
        let mut _enum_values: Vec<&'static (U, &'static str)> = Vec::new();
        _enum_values.extend_from_slice(&enum_values[..]);
        _enum_values.sort_by(|(a, _), (b, _)| b.cmp(a));

        let regex = EnumStatementMatcher::new(variable_name, field_name).regex().clone();

        Self {
            enum_values: _enum_values,
            regex: regex,
        }
    }

    fn replace_enum(&self, captures: &regex::Captures) -> String {
        if let (Some(prefix), Some(field_value_string), Some(terminal_string)) = (
                captures.get(1).map(|m| m.as_str().to_string()),
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

            if let Some(Some(rvalue)) = self.enum_values.iter()
                .map(|(value, name)|
                    if *value == field_value {
                        Some(name)
                    } else {
                        None
                    }
                )
                .filter(|e| e.is_some())
                .next() {
                return format!("{}{}{}", prefix.to_string(), rvalue, terminal_string);
            }
        }
        captures
            .get(0)
            .map_or_else(|| "".to_string(), |m| m.as_str().to_string())
    }
}

impl<U: EnumValue> LineTransformer for EnumLineTransformer<U> where <U as FromStr>::Err: Debug {
    fn transform_line(&self, line: &str) -> String where {
        self.regex.replace_all(line, |captures: &regex::Captures| self.replace_enum(captures)).to_string()
    }
}
