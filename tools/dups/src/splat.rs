extern crate yaml_rust;
use yaml_rust::{YamlLoader, YamlEmitter};
use yaml_rust::yaml::Yaml;
use std::fs::File;
use std::io::Read;
use std::fmt;


pub struct Options {
    platform: String,
    basename: String,
    base_path: String,
    target_path: String,
    asm_path: String,
    asset_path: String,
    src_path: String,
    ld_script_path: String,
    compiler: String,
    symbol_addrs_path: Vec<String>,
    undefined_funcs_auto_path: String,
    undefined_syms_auto_path: String,
    find_file_boundaries: bool,
    use_legacy_include_asm: bool,
    migrate_rodata_to_functions: bool,
    asm_jtbl_label_macro: String,
    symbol_name_format: String, // interpolated string
    section_order: Vec<String>,
    ld_bss_is_noload: bool,
    disasm_unknown: bool,
    include_macro_inc: bool,
    disassemball_all: bool,
}

pub struct Subsegment {
    offset: u64,
    section: String,
    name: String,
}

pub struct Segment {
    name: String,
    r#type: String,
    start: u64,
    vram: u64,
    align: u8,
    subalign: u8,
    subsegments: Vec<Subsegment>,
}

pub struct Config {
    path: String,
    options: Options,
    sha1: [u8; 20],
    segments: Vec<Segment>
}

impl Config {
    pub fn new_from_str(path: &str) -> Self {
        Self::new(path.to_string())
    }

    pub fn new(path: String) -> Self {
        let buffer = std::fs::read_to_string(&path).unwrap();

        let yaml = YamlLoader::load_from_str(&buffer).unwrap();
        let doc = &yaml[0];
        Config::from_yaml(path, doc)
    }

    pub fn from_yaml(path: String, yaml: &Yaml) -> Self {

        let sha1String = yaml["sha1"].as_str().unwrap();
        let mut sha1: [u8; 20] = [0; 20];
        let mut n = 0;
        (0..sha1String.len())
            .step_by(2)
            .map(|i| u8::from_str_radix(&sha1String[i..i + 2], 16).unwrap())
            .for_each(|b| { sha1[n] = b; n += 1; });

        Self {
            path,
            options: Options::new(&yaml["options"]),
            sha1,
            segments: Segment::from(&yaml["segments"]),
        }
    }
}

impl fmt::Display for Config {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}\n", self.path);
        write!(f, "options:\n");
        write!(f, "    {}\n", self.options.platform);
        write!(f, "    {}\n", self.options.basename);
        write!(f, "    {}\n", self.options.base_path);
        /*
        write!(f, "    {}\n", self.target_path: String,
        write!(f, "    {}\n", self.asm_path: String,
        write!(f, "    {}\n", self.asset_path: String,
        write!(f, "    {}\n", self.src_path: String,
        write!(f, "    {}\n", self.ld_script_path: String,
        write!(f, "    {}\n", self.compiler: String,
        write!(f, "    {}\n", self.symbol_addrs_path: Vec<String>,
        write!(f, "    {}\n", self.undefined_funcs_auto_path: String,
        write!(f, "    {}\n", self.undefined_syms_auto_path: String,
        write!(f, "    {}\n", self.find_file_boundaries: bool,
        */
        write!(f, "    {}\n", self.options.use_legacy_include_asm);
        write!(f, "    {}\n", self.options.migrate_rodata_to_functions);
        write!(f, "    {}\n", self.options.asm_jtbl_label_macro);
        write!(f, "    {}\n", self.options.symbol_name_format);
        // write!(f, "    {}\n", self.options.section_order);
        write!(f, "    {}\n", self.options.ld_bss_is_noload);
        write!(f, "    {}\n", self.options.disasm_unknown);
        write!(f, "    {}\n", self.options.include_macro_inc);
        write!(f, "    {}", self.options.disassemball_all)

    }
}

impl Options {
    pub fn new(option_yaml: &Yaml) -> Self {
        Self {
            platform: option_yaml["platform"].as_str().unwrap_or("").to_string(),
            basename: option_yaml["basename"].as_str().unwrap_or("").to_string(),
            base_path: option_yaml["base_path"].as_str().unwrap_or("").to_string(),
            target_path: option_yaml["target_path"].as_str().unwrap_or("").to_string(),
            asm_path: option_yaml["asm_path"].as_str().unwrap_or("").to_string(),
            asset_path: option_yaml["asset_path"].as_str().unwrap_or("").to_string(),
            src_path: option_yaml["src_path"].as_str().unwrap_or("").to_string(),
            ld_script_path: option_yaml["ld_script_path"].as_str().unwrap_or("").to_string(),
            compiler: option_yaml["compiler"].as_str().unwrap_or("").to_string(),
            symbol_addrs_path: option_yaml["symbol_addrs_path"]
                .as_vec()
                .unwrap()
                .iter()
                .map(|p| p.as_str().unwrap().to_string())
                .collect(),
            undefined_funcs_auto_path: option_yaml["undefined_funcs_auto_path"].as_str().unwrap_or("").to_string(),
            undefined_syms_auto_path: option_yaml["undefined_syms_auto_path"].as_str().unwrap_or("").to_string(),
            find_file_boundaries: option_yaml[""].as_bool().unwrap_or(false),
            use_legacy_include_asm: option_yaml[""].as_bool().unwrap_or(false),
            migrate_rodata_to_functions: option_yaml[""].as_bool().unwrap_or(false),
            asm_jtbl_label_macro: option_yaml["asm_jtbl_label_macro"].as_str().unwrap_or("").to_string(),
            symbol_name_format: option_yaml["symbol_name_format"].as_str().unwrap_or("").to_string(), // interpolated string
            section_order: option_yaml["section_order"]
                .as_vec()
                .unwrap()
                .iter()
                .map(|p| p.as_str().unwrap().to_string())
                .collect(),
            ld_bss_is_noload: option_yaml["ld_bss_is_noload"].as_bool().unwrap_or(false),
            disasm_unknown: option_yaml["disasm_unknown"].as_bool().unwrap_or(false),
            include_macro_inc: option_yaml["include_macro_inc"].as_bool().unwrap_or(false),
            disassemball_all: option_yaml["disassemball_all"].as_bool().unwrap_or(false),
        }
    }
}

impl Segment {
    pub fn from(segments_yaml: &Yaml) -> Vec<Self> {
        segments_yaml.as_vec()
            .unwrap()
            .iter()
            .map(|y| Self::new(&y))
            .collect()
    }

    pub fn new(segment_yaml: &Yaml) -> Self {
        if let Some(a) = segment_yaml.as_vec() {
            Self {
                name: "".to_string(),
                r#type: "".to_string(),
                start: a[0].as_i64().unwrap() as u64,
                vram: 0,
                align: 0,
                subalign: 0,
                subsegments: Vec::new(),
            }
        } else {
            Self {
                name: segment_yaml["name"].as_str().unwrap_or("").to_string(),
                r#type: segment_yaml["type"].as_str().unwrap_or("").to_string(),
                start: segment_yaml["start"].as_i64().unwrap_or(0) as u64,
                vram: segment_yaml["vram"].as_i64().unwrap_or(0) as u64,
                align: segment_yaml["align"].as_i64().unwrap_or(0) as u8,
                subalign: segment_yaml["subalign"].as_i64().unwrap_or(0) as u8,
                subsegments: segment_yaml["subsegments"].as_vec()
                    .unwrap()
                    .iter()
                    .map(|s| Subsegment::new(s))
                    .collect(),
            }
        }
    }
}

impl Subsegment {
    pub fn new(subsegment_yaml: &Yaml) -> Self {
        Self {
            offset: 0,
            section: "".to_string(),
            name: "".to_string(),
        }
    }
}
