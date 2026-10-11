use lang_c::ast::*;
use lang_c::driver::{parse, Config, Error, SyntaxError};
use lang_c::span::Span;
use lang_c::visit::*;
use once_cell::sync::Lazy;
use regex::Regex;
use std::collections::HashMap;
use std::path::Path;
use std::string::ToString;

/// A visitor that extracts the values of an `enum` from a source file
struct EnumTypeVisitor {
    name: String,
    elements: Vec<(String, i64)>,
    done: bool,
}

impl EnumTypeVisitor {
    pub fn new(name: String) -> Self {
        Self {
            name,
            elements: Vec::new(),
            done: false,
        }
    }
}

impl<'ast> Visit<'ast> for EnumTypeVisitor {
    fn visit_enum_type(&mut self, n: &'ast EnumType, span: &'ast Span) {
        if self.done {
            return;
        }

        let mut ev = EnumVisitor::new(&self.name);
        ev.visit_enum_type(n, span);
        self.elements = ev.elements;

        if self.elements.len() > 0 {
            self.done = true;
        }
    }
}

struct EnumVisitor<'a> {
    symbol: &'a String,
    elements: Vec<(String, i64)>,
    next_value: i64,
    found: bool,
    done: bool,
}

impl<'a> EnumVisitor<'a> {
    fn new(symbol: &'a String) -> Self {
        Self {
            symbol,
            elements: Vec::new(),
            next_value: 0,
            found: false,
            done: false,
        }
    }
}

/// EnumVisitor takes the `enum` type declaration, it's identifier,
/// and then defers to EnumItemVistor to manage state for each
/// enumerator.
impl<'ast, 'a> Visit<'ast> for EnumVisitor<'a> {
    fn visit_enum_type(&mut self, n: &'ast EnumType, span: &'ast Span) {
        if self.done {
            return;
        }

        visit_enum_type(self, n, span);

        if self.found {
            self.done = true;
        }
    }

    fn visit_identifier(&mut self, identifier: &'ast Identifier, span: &'ast Span) {
        if self.done {
            return;
        }

        if *self.symbol != identifier.name {
            return;
        }

        self.found = true;

        visit_identifier(self, identifier, span);
    }

    // called for each value in the enum
    fn visit_enumerator(&mut self, n: &'ast Enumerator, span: &'ast Span) {
        if self.done || !self.found {
            return;
        }

        let mut eiv = EnumItemVisitor::new(self.next_value);
        eiv.visit_enumerator(n, span);
        let value = eiv.value().expect("enum value");

        self.elements.push((eiv.symbol, value));
        self.next_value = value + 1;
    }
}

/// EnumItemVisitor collects the name and opertional value from each enumerator.
struct EnumItemVisitor {
    symbol: String,
    value: String,
    base: u32,
}

impl EnumItemVisitor {
    fn new(default_value: i64) -> Self {
        Self {
            symbol: "".to_string(),
            value: default_value.to_string(),
            base: 10,
        }
    }

    fn value(&self) -> Result<i64, std::num::ParseIntError> {
        i64::from_str_radix(&self.value, self.base)
    }
}

impl ToString for EnumItemVisitor {
    fn to_string(&self) -> String {
        format!("{} = 0x{:X},", self.symbol, self.value().unwrap())
    }
}

impl<'ast> Visit<'ast> for EnumItemVisitor {
    fn visit_identifier(&mut self, identifier: &'ast Identifier, span: &'ast Span) {
        self.symbol = identifier.name.clone();
        visit_identifier(self, identifier, span);
    }

    fn visit_integer(&mut self, n: &'ast Integer, span: &'ast Span) {
        self.value = n.number.to_string();
        visit_integer(self, n, span);
    }

    fn visit_integer_base(&mut self, n: &'ast IntegerBase, span: &'ast Span) {
        match *n {
            IntegerBase::Decimal => self.base = 10,
            IntegerBase::Octal => self.base = 8,
            IntegerBase::Hexadecimal => self.base = 16,
            IntegerBase::Binary => self.base = 2,
        }
        visit_integer_base(self, n, span);
    }
}

/// Get the values of an enum type. Currently only
/// named enums (not anonymous typedefs) are supported.
///
///
///    let value = enum_values("sfx.h", "Sfx");
pub fn enum_values(source: &Path, enum_type: &str) -> Result<HashMap<String, i64>, String> {
    let config = Config::default();
    let c = parse(&config, source);

    let c = match c {
        Ok(c) => c,
        Err(Error::SyntaxError(SyntaxError {
            source,
            line,
            column: _,
            offset: _,
            expected,
        })) => {
            let mut i = 0;
            eprintln!("Error {}: expected {:?}", line, expected);
            source.lines().for_each(|l| {
                i += 1;
                if i == line {
                    eprintln!("{:4}: {}", i, l);
                }
            });
            return Err(format!("Failed to parse header: {line:4}: {expected:?}"));
        }
        Err(e) => return Err(format!("Failed to parse header: {:?}", e)),
    };

    let mut enum_type_visitor = EnumTypeVisitor::new(enum_type.to_string());
    enum_type_visitor.visit_translation_unit(&c.unit);

    let map: HashMap<String, i64> = enum_type_visitor.elements.into_iter().collect();

    Ok(map)
}

/// Parse a C integer literal: hexadecimal, octal or decimal.
pub fn parse_int(text: &str) -> Option<i64> {
    let text = text.trim();
    if let Some(hex) = text.strip_prefix("0x").or_else(|| text.strip_prefix("0X")) {
        return i64::from_str_radix(hex, 16).ok();
    }
    if text.is_empty() || !text.bytes().all(|b| b.is_ascii_digit()) {
        return None;
    }
    if text.len() > 1 && text.starts_with('0') {
        return i64::from_str_radix(text, 8).ok();
    }
    text.parse().ok()
}

static COMMENT_PATTERN: Lazy<Regex> =
    Lazy::new(|| Regex::new(r"(?s)/\*.*?\*/|//[^\n]*").unwrap());

/// Entries of a named enum in declaration order, read without a preprocessor.
/// Values: literals, earlier entries, or sums of those. `Ok(None)` if absent.
pub fn parse_enum_entries(text: &str, enum_type: &str) -> Result<Option<Vec<(String, i64)>>, String> {
    let text = COMMENT_PATTERN.replace_all(text, "");
    let pattern = format!(r"\benum\s+{}\s*\{{([^}}]*)\}}", regex::escape(enum_type));
    let Some(captures) = Regex::new(&pattern).unwrap().captures(&text) else {
        return Ok(None);
    };

    let body: String = captures[1]
        .lines()
        .filter(|line| !line.trim_start().starts_with('#'))
        .collect::<Vec<_>>()
        .join("\n");

    let mut entries: Vec<(String, i64)> = Vec::new();
    let mut next_value = 0;
    for item in body.split(',').map(str::trim).filter(|item| !item.is_empty()) {
        let (name, value) = match item.split_once('=') {
            None => (item, next_value),
            Some((name, expression)) => {
                let mut value = 0;
                for term in expression.split('+').map(str::trim) {
                    value += parse_int(term)
                        .or_else(|| entries.iter().find(|(n, _)| n == term).map(|(_, v)| *v))
                        .ok_or_else(|| format!("enum {}: cannot evaluate `{}`", enum_type, item))?;
                }
                (name.trim(), value)
            }
        };
        entries.push((name.to_string(), value));
        next_value = value + 1;
    }

    Ok(Some(entries))
}

/// `parse_enum_entries` on a file. A missing enum is an error here.
pub fn enum_entries(source: &Path, enum_type: &str) -> Result<Vec<(String, i64)>, String> {
    let text = std::fs::read_to_string(source)
        .map_err(|e| format!("{}: {}", source.display(), e))?;
    parse_enum_entries(&text, enum_type)?
        .ok_or_else(|| format!("{}: enum {} not found", source.display(), enum_type))
}

pub trait CLang {
    fn strip_line_comment(&self) -> Self;
}

impl CLang for String {
    fn strip_line_comment(&self) -> Self {
        // to_owned() to go from &str to String, so you can chain String methods
        self.split("//").next().unwrap().to_owned()
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn read() {
        let sfx = enum_values(Path::new("../../../include/sfx.h"), "Sfx");
        assert!(sfx.unwrap().len() > 400);
    }

    #[test]
    fn test_parse_int() {
        assert_eq!(parse_int("0x8002"), Some(0x8002));
        assert_eq!(parse_int("148"), Some(148));
        assert_eq!(parse_int("0"), Some(0));
        assert_eq!(parse_int("010"), Some(8));
        assert_eq!(parse_int("PAL_NONE"), None);
        assert_eq!(parse_int(""), None);
    }

    #[test]
    fn test_parse_enum_entries() {
        let text = "
            enum Other { NOPE = 7 };
            enum Palettes {
                PAL_NONE, // implicit zero
                PAL_A = 0x200,
                PAL_B,
            #ifdef VERSION_PSP
                PAL_C = 10, /* decimal */
            #endif
                PAL_D = PAL_A + 4,
                PAL_ALIAS = PAL_A,
            };";
        let entries = parse_enum_entries(text, "Palettes").unwrap().unwrap();
        let expected = [
            ("PAL_NONE", 0),
            ("PAL_A", 0x200),
            ("PAL_B", 0x201),
            ("PAL_C", 10),
            ("PAL_D", 0x204),
            ("PAL_ALIAS", 0x200),
        ];
        assert_eq!(entries.len(), expected.len());
        for ((name, value), (expected_name, expected_value)) in entries.iter().zip(expected) {
            assert_eq!((name.as_str(), *value), (expected_name, expected_value));
        }
    }

    #[test]
    fn test_parse_enum_entries_missing() {
        assert_eq!(parse_enum_entries("enum Palette { A };", "Palettes"), Ok(None));
    }

    #[test]
    fn test_parse_enum_entries_unsupported_value() {
        assert!(parse_enum_entries("enum Palettes { A = sizeof(int) };", "Palettes").is_err());
    }

    #[test]
    fn test_enum_entries_from_headers() {
        // neither header can go through the preprocessor on its own
        let enemies = enum_entries(Path::new("../../../include/enemies.h"), "EnemyIds").unwrap();
        assert_eq!(enemies[0], ("ENEMY_BREAKABLE".to_string(), 0));
        let palettes = enum_entries(Path::new("../../../src/st/tek/tek.h"), "Palettes").unwrap();
        assert!(palettes.contains(&("PAL_DODO_BIRD".to_string(), 0x200)));
    }

    #[test]
    fn test_strip_line_comments() {
        assert_eq!("hello // world".to_string().strip_line_comment(), "hello ");
        assert_eq!(
            "foo().bar()".to_string().strip_line_comment(),
            "foo().bar()"
        );
    }
}
