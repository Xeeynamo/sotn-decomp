use std::path::Path;

/// A transformer that sees a whole file at once. Unlike a `LineTransformer`
/// it knows the file's path and can add, remove or join lines.
pub trait FileTransformer: Sync {
    fn transform_file(&self, path: &Path, lines: Vec<String>) -> Vec<String>;
}
