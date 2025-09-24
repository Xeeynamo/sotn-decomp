/// Define the trait for the transform method
pub trait LineTransformer: Sync {
    /// if transform wants to change line, it returns Some(String)
    fn transform_line(&self, line: &str) -> Option<String>;
}
