use regex::Regex;
use once_cell::sync::Lazy;

/// The `Linter` trait is used for determining if a line matches a particular
/// rule. Unlike a `Transformer`, a `Linter` does not fix the line, it only
/// reports success or failure.
pub trait Linter: Sync {
    /// `check_line` determines if the line is acceptable (`Ok<()>`) or
    /// not (`Err<String>`)
    fn check_line(&self, line: &str) -> Result<(), String>;
}


trait CLang {
    fn strip_line_comment(&self) -> Self;
}

impl CLang for String {
    fn strip_line_comment(&self) -> Self {
        // to_owned() to go from &str to String, so you can chain String methods
        self.split("//").next().unwrap().to_owned()
    }
}

/// `EntityRangeLinter` is a linter which checks automatic
/// variable names to determine if they are in the range
/// of the the `g_Entities` table. These references should
/// be replaced by indexing into the table and, if appropriate,
/// using the appropriate `Entity` field.
pub struct EntityRangeLinter;

static SYMBOL_PATTERN: Lazy<Regex> = Lazy::new(|| Regex::new(r"(D_(?:[a-zA-F0-9]*_)?([A-F0-9]{8}))").unwrap());

impl Linter for EntityRangeLinter {
    fn check_line(&self, line: &str) -> Result<(), String> {

        let stripped = line.to_string().strip_line_comment();
        let Some(captures) = SYMBOL_PATTERN.captures(&stripped.as_str()) else {
            return Ok(());
        };

        let addr_str = captures.get(2).map(|m| m.as_str().to_string());
        let addr = u32::from_str_radix(&addr_str.clone().unwrap(), 16).unwrap();

        if (addr >= 0x800733D8 && addr < 0x8007EF1C) ||
            (addr >= 0x091e1680 && addr < 0x91ED1C4) {
            let var = captures.get(1).map(|m| m.as_str().to_string()).expect("entity global");
            return Err(format!("`{var}' should index into g_Entities"));
        }

        Ok(())
    }
}

/// `RegexLinter` takes a line and matches it against a regular expression.
/// Lines that match are considered failures and will return `Err<String>`.
pub struct RegexLinter {
    name: String,
    regex: Regex,
}

impl RegexLinter {
    pub fn new(name: &str, expression: &str) -> Self {
        Self {
            name: name.to_string(),
            regex: Regex::new(expression).unwrap()
        }
    }
}

impl Linter for RegexLinter {
    fn check_line(&self, line: &str) -> Result<(), String> {
        let stripped = line.to_string().strip_line_comment();
        if self.regex.is_match(&stripped) {
            Err(format!("{}: {}", self.name, self.regex))
        } else {
            Ok(())
        }
    }
}

/// `LocalExternLinter` looks for global variables that are declared `extern`.
/// The `extern` declaration means the variable is defined elsewhere, so
/// local globals with definitions should not be permitted.
pub struct LocalExternLinter;

static LOCAL_EXTERN_PATTERN: Lazy<Regex> = Lazy::new(|| Regex::new(r"^extern [^ ]+ ([a-zA-Z0-9$_]+)[^ ]* = ").unwrap());

impl Linter for LocalExternLinter {
    fn check_line(&self, line: &str) -> Result<(), String> {
        let Some(captures) = LOCAL_EXTERN_PATTERN.captures(line) else {
            return Ok(());
        };
        let symbol = captures.get(1).map(|m| m.as_str().to_string()).expect("symbol");
        Err(format!("`{symbol}' definition should not be `extern`"))
    }
}
