#[derive(Clone, Debug, PartialEq)]
pub struct Function {
    pub name: String,
    pub ops: Vec<Instruction>,
    pub key: Vec<u8>,
    pub dir: String,
    pub file: String,
    pub similarity: f64,
    pub decompiled: bool,
}

#[derive(Clone, Debug, PartialEq)]
pub struct Instruction {
    pub file_addr: u64,
    pub vram_addr: u64,
    pub op: u32,
}

pub struct DupsFile {
    pub name: String,
    pub funcs: Vec<Function>,
}
