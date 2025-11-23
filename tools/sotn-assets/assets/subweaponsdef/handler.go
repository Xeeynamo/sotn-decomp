package subweaponsdef

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"os"
	"path/filepath"
	"strconv"
	"strings"
	"unsafe"

	"github.com/goccy/go-yaml"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
)

// copy of SubweaponDef
type subweaponRawEntry struct {
	Attack               int16
	HeartCost            int16
	AttackElement        uint16
	ChainLimit           uint8
	NFramesInvincibility uint8
	StunFrames           uint16
	Anim                 uint8
	BlueprintNum         uint8
	HitboxState          uint16
	HitEffect            uint16
	CrashId              uint8
	Unk11                uint8
	EntityRoomIndex      uint16
}
type subweaponModel struct {
	Attack               int16
	HeartCost            int16
	AttackElement        []string
	ChainLimit           uint8
	NFramesInvincibility uint8
	StunFrames           uint16
	Anim                 uint8
	Blueprint            string
	HitboxState          uint16
	HitEffect            uint16
	CrashId              string
	Unk11                uint8
	EntityRoomIndex      uint16
}

const entrySize = 0x14

var _ = func() interface{} {
	if entrySize == int(unsafe.Sizeof(subweaponRawEntry{})) {
		panic(fmt.Sprintf("subweaponEntry size: got %d, expected %d", unsafe.Sizeof(subweaponRawEntry{}), entrySize))
	}
	return struct{}{}
}

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "subweaponsdef" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	if len(e.Args) > 2 {
		return fmt.Errorf("too many arguments")
	}
	if len(e.Args) < 1 {
		return fmt.Errorf("require subweapon enum name as first argument")
	}
	if len(e.Args) < 2 {
		return fmt.Errorf("require blueprint enum name as second argument")
	}
	elementFields, err := sotn.FetchEnum("include", "game", "Elements")
	if err != nil || len(elementFields) == 0 {
		return fmt.Errorf("fetch enum %s: %w", "Elements", err)
	}
	weaponFields, err := sotn.FetchEnum(e.SrcDir, e.OvlName, e.Args[0])
	if err != nil || len(weaponFields) == 0 {
		return fmt.Errorf("fetch enum %s: %w", e.Args[0], err)
	}
	blueprintFields, err := sotn.FetchEnum(e.SrcDir, e.OvlName, e.Args[1])
	if err != nil || len(blueprintFields) == 0 {
		return fmt.Errorf("fetch enum %s: %w", e.Args[1], err)
	}

	entries, err := parse(e.Data[e.Start:e.End], elementFields, blueprintFields, weaponFields)
	if err != nil {
		return fmt.Errorf("parse error: %w", err)
	}
	yamlEntries := yaml.MapSlice{}
	for i, entry := range entries {
		indexName, ok := weaponFields[i]
		if !ok {
			indexName = strconv.Itoa(i)
		}
		yamlEntries = append(yamlEntries, yaml.MapItem{
			Key:   indexName,
			Value: entry,
		})
	}
	asYaml, err := yaml.Marshal(yamlEntries)
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
	enumName := e.Args[0]
	ovlName := filepath.Base(e.AssetDir)
	fields, err := sotn.FetchEnum(e.SrcDir, ovlName, enumName)
	if err != nil {
		return fmt.Errorf("fetch enum %s: %w", enumName, err)
	}

	// the entry order, amount and continuity is not guaranteed; we need to re-map it into a contiguous array
	var entryMap map[string]subweaponModel
	if err := yaml.Unmarshal(data, &entryMap); err != nil {
		return fmt.Errorf("failed to parse %s: %w", inFileName, err)
	}
	entries := make([]subweaponModel, len(entryMap))
	for index, name := range fields {
		entry, ok := entryMap[name]
		if !ok {
			return fmt.Errorf("entry %s not found in %s", name, inFileName)
		}
		entries[index] = entry
	}
	// check if any YAML entry was missed due to its absence in the enum
	fieldsByName := util.ReverseMap(fields)
	for name, _ := range entryMap {
		if _, ok := fieldsByName[name]; !ok {
			return fmt.Errorf("entry %s not found in enum %s", name, enumName)
		}
	}

	sb := strings.Builder{}
	sb.WriteString("// clang-format off\n")
	for _, entry := range entries {
		sb.WriteString(fmt.Sprintf(
			"{%d,%d,%s,%d,%d,%d,%d,%s,%d,%d,%s,%d,%d},\n",
			entry.Attack,
			entry.HeartCost,
			strings.Join(append(entry.AttackElement, "0"), "|"),
			entry.ChainLimit,
			entry.NFramesInvincibility,
			entry.StunFrames,
			entry.Anim,
			entry.Blueprint,
			entry.HitboxState,
			entry.HitEffect,
			entry.CrashId,
			entry.Unk11,
			entry.EntityRoomIndex))
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

func parse(data []byte, elements map[int]string, blueprints map[int]string, weapons map[int]string) ([]subweaponModel, error) {
	count := len(data) / entrySize
	entries := make([]subweaponRawEntry, count)
	r := bytes.NewReader(data)
	if err := binary.Read(r, binary.LittleEndian, &entries); err != nil {
		return nil, fmt.Errorf("failed to parse []subweaponRawEntry: %w", err)
	}
	mappedEntries := make([]subweaponModel, count)
	for i, entry := range entries {
		mappedEntries[i].Attack = entry.Attack
		mappedEntries[i].HeartCost = entry.HeartCost
		mappedEntries[i].AttackElement = []string{}
		mappedEntries[i].ChainLimit = entry.ChainLimit
		mappedEntries[i].NFramesInvincibility = entry.NFramesInvincibility
		mappedEntries[i].StunFrames = entry.StunFrames
		mappedEntries[i].Anim = entry.Anim
		mappedEntries[i].HitboxState = entry.HitboxState
		mappedEntries[i].HitEffect = entry.HitEffect
		mappedEntries[i].Unk11 = entry.Unk11
		mappedEntries[i].EntityRoomIndex = entry.EntityRoomIndex

		blueprintName, ok := blueprints[int(entry.BlueprintNum)]
		if !ok {
			return nil, fmt.Errorf("cannot find blueprint %d", entry.BlueprintNum)
		}
		mappedEntries[i].Blueprint = blueprintName

		crashWeaponName, ok := weapons[int(entry.CrashId)]
		if !ok {
			return nil, fmt.Errorf("cannot find Crash ID %d", entry.CrashId)
		}
		mappedEntries[i].CrashId = crashWeaponName

		for flag := 1; flag < 0x10000; flag <<= 1 {
			if (entry.AttackElement & uint16(flag)) == 0 {
				continue
			}
			name, ok := elements[flag]
			if !ok {
				name = fmt.Sprintf("0x%08X", flag)
			}
			mappedEntries[i].AttackElement = append(mappedEntries[i].AttackElement, name)
		}
	}
	return mappedEntries, nil
}
