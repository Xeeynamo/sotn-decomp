use regex::Regex;


pub struct EnumStatementMatcher {
    regex: Regex
}


impl EnumStatementMatcher {
    pub fn new(variable_name: Option<&str>, field_name: &str) -> Self {
        let var_and_operator_pattern =  if let Some(var) = variable_name {
            format!(r"(?x)
                {}                        # the variable name
                (?:                       # one of:
                    (?:->) |              #   * pointer field access operator
                    \.                    #   * struct/union field access operator
                )
            ", regex::escape(var))
        } else {
            // abbreviated pointer or struct field access
            format!(r"[.>]")
        };

        let pattern = format!(r"(?x)
            (                             # <1> a prefix containing:
                {}                        #   * a struct or pointer access operator
                {}                        #   * a field name (provided by format!)
                \s*                       #   * optional whitespace
                (                         #   * <2> a binary operator, one of:
                    (?:(?:[&|^~]?)=) |    #      * an assignment operator
                    (?:(?:[!=<>]=)|[<>]) |#      * a comparison operator
                    (?:[&|^])             #      * a bitwise operator
                )
                \s*                       #   * optional whitespace
            )
            ([~]?)                        # <3> an optional bitwise NOT
            (                             # <4> the number, one of:
                (?:0x[A-Fa-f0-9]+) |      #   * a hexidecimal integer
                0 |                       #   * a zero
                (?:[1-9][0-9]*)           #   * a decimal integer
            )
            ([;),? ])                     # <5> a statement terminal
        ", var_and_operator_pattern, regex::escape(field_name));

        Self { regex: Regex::new(&pattern).unwrap() }
    }

    pub fn regex(self: &Self) -> &Regex {
        &self.regex
    }
}
