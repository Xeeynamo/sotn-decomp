package splat

import (
	"os"

	"github.com/goccy/go-yaml"
)

type Segment struct {
	Name        string `yaml:"name"`
	Type        string `yaml:"type"`
	Start       uint64 `yaml:"start"`
	VRAM        uint64 `yaml:"vram"`
	Align       uint64 `yaml:"align"`
	Subalign    uint64 `yaml:"subalign"`
	Subsegments []any  `yaml:"subsegments"`
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
	Sha1     string `yaml:"sha1"`
	Segments []any  `yaml:"segments"`
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

func (c *Config) ForEachCodeSubsegment(f func(segment Segment, subsegments []any)) {
	for _, segmentRaw := range c.Segments {
		segmentMap, ok := segmentRaw.(map[string]any)
		if !ok {
			continue
		}
		if kind, ok := segmentMap["type"]; !ok || kind != "code" {
			continue
		}
		subsegments, ok := segmentMap["subsegments"].([]any)
		if !ok {
			continue
		}
		f(Segment{
			VRAM: segmentMap["vram"].(uint64),
		}, subsegments)
	}
}

func (c *Config) GetSymbolName(offset int) string {
	ret := ""
	c.ForEachCodeSubsegment(func(segment Segment, subsegments []any) {
		for _, seg := range subsegments {
			subsegment, ok := seg.([]any)
			if !ok {
				continue
			}
			if len(subsegment) < 3 {
				continue
			}
			off := subsegment[0].(int)
			if off == offset {
				if val, ok := subsegment[2].(string); ok {
					ret = val
					return
				}
			}
		}
	})
	return ret
}
