package xamusicconfig

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"os"
	"path/filepath"
	"strings"
	"unsafe"

	"github.com/goccy/go-yaml"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
)

// copy of SubweaponDef
type xaMusicConfig struct {
	CdAddr          uint32 `yaml:"cd_addr"`
	Unk228          int32  `yaml:"unk228"`
	FilterFile      uint8  `yaml:"filter_file"`
	FilterChannelId uint8  `yaml:"filter_channel_id"`
	Volume          uint8  `yaml:"volume"`
	Unk22F          uint8  `yaml:"unk22F,omitempty"`
	Unk230          uint32 `yaml:"unk230"`
}

const entrySize = 0x10

var _ = func() interface{} {
	if entrySize == int(unsafe.Sizeof(xaMusicConfig{})) {
		panic(fmt.Sprintf("xaMusicConfig size: got %d, expected %d", unsafe.Sizeof(xaMusicConfig{}), entrySize))
	}
	return struct{}{}
}

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "xamusicconfig" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	entries, err := parse(e.Data[e.Start:e.End])
	if err != nil {
		return fmt.Errorf("parse error: %w", err)
	}
	asYaml, err := yaml.Marshal(entries)
	if err != nil {
		return fmt.Errorf("yaml error: %w", err)
	}
	return util.WriteFile(assetPath(e.AssetDir, e.Name), asYaml)
}

func (h *handler) Build(e assets.BuildArgs) error {
	inFileName := assetPath(e.AssetDir, e.Name)
	data, err := os.ReadFile(inFileName)
	if err != nil {
		return fmt.Errorf("failed to read file: %w", err)
	}
	var entries []xaMusicConfig
	if err := yaml.Unmarshal(data, &entries); err != nil {
		return fmt.Errorf("failed to parse %s: %w", inFileName, err)
	}

	sb := strings.Builder{}
	sb.WriteString("// clang-format off\n")
	for _, entry := range entries {
		sb.WriteString(fmt.Sprintf(
			"{0x%05X, 0x%04X, 0x%02X, %d, %d, %d, %d},\n",
			entry.CdAddr,
			entry.Unk228,
			entry.FilterFile,
			entry.FilterChannelId,
			entry.Volume,
			0,
			entry.Unk230,
		))
	}
	return util.WriteFile(sourcePath(e.SrcDir, e.Name), []uint8(sb.String()))
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	return assets.InfoResult{}, nil
}

func assetPath(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("%s.yaml", name))
}

func sourcePath(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("gen/%s.h", name))
}

func parse(data []byte) ([]xaMusicConfig, error) {
	count := len(data) / entrySize
	entries := make([]xaMusicConfig, count)
	r := bytes.NewReader(data)
	if err := binary.Read(r, binary.LittleEndian, &entries); err != nil {
		return nil, err
	}
	return entries, nil
}
