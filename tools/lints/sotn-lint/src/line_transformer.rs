// Define the trait for the transform method
pub trait LineTransformer: Sync {
    fn transform_line(&self, line: &str) -> String;
}
