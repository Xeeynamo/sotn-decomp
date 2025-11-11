use lang_c::ast::*;
use lang_c::driver::{parse, Config, Error, SyntaxError};
use lang_c::span::Span;
use lang_c::visit::*;
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
    fn test_strip_line_comments() {
        assert_eq!("hello // world".to_string().strip_line_comment(), "hello ");
        assert_eq!(
            "foo().bar()".to_string().strip_line_comment(),
            "foo().bar()"
        );
    }
}
