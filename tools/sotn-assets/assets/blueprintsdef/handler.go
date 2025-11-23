package blueprintsdef

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"os"
	"path/filepath"
	"strconv"
	"strings"

	"github.com/goccy/go-yaml"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
)

// copy of SubweaponDef
const entrySize = 6

type blueprintRawEntry [entrySize]uint8

type blueprintModel struct {
	Entity        string `yaml:"entity"`
	Amount        uint8  `yaml:"amount"`
	NPerCycle     uint8  `yaml:"nPerCycle"`
	IsNonCritical bool   `yaml:"isNonCritical"`
	IncParamsKind bool   `yaml:"incParamsKind"`
	TimerCycle    uint8  `yaml:"timerCycle"`
	Kind          string `yaml:"kind"`
	Origin        string `yaml:"origin"`
	TimerDelay    uint8  `yaml:"timerDelay"`
}

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "blueprintsdef" }

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
	bpKindFields, err := sotn.FetchEnum(e.SrcDir, e.OvlName, "BlueprintKind")
	if err != nil || len(bpKindFields) == 0 {
		if err == nil {
			err = fmt.Errorf("not found")
		}
		return fmt.Errorf("fetch enum %s: %w", "BlueprintKind", err)
	}
	bpOriginFields, err := sotn.FetchEnum(e.SrcDir, e.OvlName, "BlueprintOrigin")
	if err != nil || len(bpOriginFields) == 0 {
		if err == nil {
			err = fmt.Errorf("not found")
		}
		return fmt.Errorf("fetch enum %s: %w", "BlueprintOrigin", err)
	}
	blueprintFields, err := sotn.FetchEnum(e.SrcDir, e.OvlName, e.Args[0])
	if err != nil || len(blueprintFields) == 0 {
		if err == nil {
			err = fmt.Errorf("not found")
		}
		return fmt.Errorf("fetch enum %s: %w", e.Args[0], err)
	}
	entityFields, err := sotn.FetchEnum(e.SrcDir, e.OvlName, e.Args[1])
	if err != nil || len(entityFields) == 0 {
		if err == nil {
			err = fmt.Errorf("not found")
		}
		return fmt.Errorf("fetch enum %s: %w", e.Args[1], err)
	}

	entries, err := parse(e.Data[e.Start:e.End], e.OvlName == "dra", entityFields, bpKindFields, bpOriginFields)
	if err != nil {
		return fmt.Errorf("parse error: %w", err)
	}
	yamlEntries := yaml.MapSlice{}
	for i, entry := range entries {
		indexName, ok := blueprintFields[i]
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
	fields, err := sotn.FetchEnum(e.SrcDir, e.OvlName, enumName)
	if err != nil {
		return fmt.Errorf("fetch enum %s: %w", enumName, err)
	}

	// the entry order, amount and continuity is not guaranteed; we need to re-map it into a contiguous array
	var entryMap map[string]blueprintModel
	if err := yaml.Unmarshal(data, &entryMap); err != nil {
		return fmt.Errorf("failed to parse %s: %w", inFileName, err)
	}
	entries := make([]blueprintModel, len(entryMap))
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
			"B_MAKE(%s,%d,%d,%t,%t,%d,%s,%s,%d),\n",
			entry.Entity,
			entry.Amount,
			entry.NPerCycle,
			entry.IsNonCritical,
			entry.IncParamsKind,
			entry.TimerCycle,
			entry.Kind,
			entry.Origin,
			entry.TimerDelay))
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

func parse(
	data []byte,
	isDra bool,
	entities map[int]string,
	kinds map[int]string,
	origins map[int]string,
) ([]blueprintModel, error) {
	count := len(data) / entrySize
	entries := make([]blueprintRawEntry, count)
	r := bytes.NewReader(data)
	if err := binary.Read(r, binary.LittleEndian, &entries); err != nil {
		return nil, fmt.Errorf("failed to parse blueprintRawEntry: %w", err)
	}
	mappedEntries := make([]blueprintModel, count)
	for i, entry := range entries {
		mappedEntries[i].Amount = entry[1]
		mappedEntries[i].NPerCycle = entry[2] & 0x3F
		mappedEntries[i].IncParamsKind = false
		if (entry[2] & 0x40) != 0 {
			mappedEntries[i].IncParamsKind = true
		}
		mappedEntries[i].IsNonCritical = false
		if (entry[2] & 0x80) != 0 {
			mappedEntries[i].IsNonCritical = true
		}
		mappedEntries[i].TimerCycle = entry[3]
		mappedEntries[i].TimerDelay = entry[5]

		var kind, origin int
		if isDra {
			// DRA parses the data differently than RIC and MARIA
			kind = int(entry[4] & 15)
			origin = int((entry[4] >> 4) & 15)
		} else {
			kind = int(entry[4] & 7)
			origin = int((entry[4] >> 3) & 31)
		}
		entity := int(entry[0])

		entityName, ok := entities[entity]
		if !ok {
			return nil, fmt.Errorf("cannot find entity %d", entity)
		}
		mappedEntries[i].Entity = entityName

		kindName, ok := kinds[kind]
		if !ok {
			return nil, fmt.Errorf("cannot find blueprint kind %d", kind)
		}
		mappedEntries[i].Kind = kindName

		originName, ok := origins[origin]
		if !ok {
			return nil, fmt.Errorf("cannot find blueprint origin %d", origin)
		}
		mappedEntries[i].Origin = originName
	}
	return mappedEntries, nil
}
