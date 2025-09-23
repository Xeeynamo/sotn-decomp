// Define the trait for the transform method
pub trait LineTransformer: Sync {
    /// if transform wants to change line line it returns Some(String)
    fn transform_line(&self, line: &str) -> Option<String>;

    #[cfg(test)]
    fn transform_line_owned(&self, line: &str) -> String {
        match self.transform_line(line) {
            Some(s) => s,
            None => line.to_string(),
        }
    }
}
