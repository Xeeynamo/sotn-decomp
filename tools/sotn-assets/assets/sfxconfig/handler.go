package sfxconfig

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
type sfxEntry struct {
	VabID  uint8
	Prog   uint8
	Note   uint8
	Volume uint8
	Mode   uint8
	Tone   uint8
	Unk6   uint8
}

const entrySize = 7

var _ = func() interface{} {
	if entrySize == int(unsafe.Sizeof(sfxEntry{})) {
		panic(fmt.Sprintf("sfxEntry size: got %d, expected %d", unsafe.Sizeof(sfxEntry{}), entrySize))
	}
	return struct{}{}
}

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "sfxconfig" }

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
	var entries []sfxEntry
	if err := yaml.Unmarshal(data, &entries); err != nil {
		return fmt.Errorf("failed to parse %s: %w", inFileName, err)
	}

	sb := strings.Builder{}
	sb.WriteString("// clang-format off\n")
	for _, entry := range entries {
		sb.WriteString(fmt.Sprintf(
			"{%d, %d, %d, %d, %d, %d, %d},\n",
			entry.VabID,
			entry.Prog,
			entry.Note,
			entry.Volume,
			entry.Mode,
			entry.Tone,
			entry.Unk6,
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

func parse(data []byte) ([]sfxEntry, error) {
	count := len(data) / entrySize
	entries := make([]sfxEntry, count)
	r := bytes.NewReader(data)
	if err := binary.Read(r, binary.LittleEndian, &entries); err != nil {
		return nil, err
	}
	return entries, nil
}
