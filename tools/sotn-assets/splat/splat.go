package splat

import (
	"gopkg.in/yaml.v3"
	"os"
)

type Segment struct {
	Name        string  `yaml:"name"`
	Type        string  `yaml:"type"`
	Start       int64   `yaml:"start"`
	VRAM        int64   `yaml:"vram"`
	Align       int64   `yaml:"align"`
	Subalign    int64   `yaml:"subalign"`
	Subsegments [][]any `yaml:"subsegments"`
}

type Config struct {
	Options struct {
		Platform                 string   `yaml:"platform"`
		Basename                 string   `yaml:"basename"`
		BasePath                 string   `yaml:"base_path"`
		BuildPath                string   `yaml:"build_path"`
		TargetPath               string   `yaml:"target_path"`
		AsmPath                  string   `yaml:"asm_path"`
		AssetPath                string   `yaml:"asset_path"`
		SrcPath                  string   `yaml:"src_path"`
		LdScriptPath             string   `yaml:"ld_script_path"`
		Compiler                 string   `yaml:"compiler"`
		SymbolAddrsPath          []string `yaml:"symbol_addrs_path"`
		UndefinedFuncsAutoPath   string   `yaml:"undefined_funcs_auto_path"`
		UndefinedSymsAutoPath    string   `yaml:"undefined_syms_auto_path"`
		FindFileBoundaries       string   `yaml:"find_file_boundaries"`
		UseLegacyIncludeAsm      string   `yaml:"use_legacy_include_asm"`
		MigrateRodataToFunctions string   `yaml:"migrate_rodata_to_functions"`
		AsmJtblLabelMacro        string   `yaml:"asm_jtbl_label_macro"`
		ExtensionsPath           string   `yaml:"extensions_path"`
		DisassembleAll           bool     `yaml:"disassemble_all"`
		SectionOrder             []string `yaml:"section_order"`
	} `yaml:"options"`
	Sha1     string    `yaml:"sha1"`
	Segments []Segment `yaml:"segments"`
}

func ReadConfig(path string) (*Config, error) {
	yamlFile, err := os.ReadFile(path)
	if err != nil {
		return nil, err
	}
	var config Config
	_ = yaml.Unmarshal(yamlFile, &config)
	// ignore error due to the final section of the last segment yaml being funny
	return &config, nil
}

func (c *Config) GetSymbolName(offset int) string {
	for _, segment := range c.Segments {
		for _, subsegment := range segment.Subsegments {
			if len(subsegment) < 3 {
				continue
			}
			off := subsegment[0].(int)
			if off == offset {
				return subsegment[2].(string)
			}
		}
	}
	return ""
}
