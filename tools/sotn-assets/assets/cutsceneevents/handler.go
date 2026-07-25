package cutsceneevents

import (
	"fmt"
	"os"
	"path/filepath"
	"strconv"
	"strings"

	"github.com/goccy/go-yaml"
	"github.com/goccy/go-yaml/ast"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
)

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "cutscene_events" }

const terminator = 0xFFFF

type eventDef struct {
	name   string
	macro  string
	params []string
}

// indexed by CutsceneEventOpcode
var eventDefinitions = []eventDef{
	{name: "SPAWN_ENTITY", macro: "EVENT_SPAWN_ENTITY", params: []string{"slot", "id", "x", "y"}},
	{name: "DESTROY_ENTITY", macro: "EVENT_DESTROY_ENTITY", params: []string{"slot"}},
	{name: "WAIT_FOR_FLAG", macro: "EVENT_WAIT_FLAG", params: []string{"flag"}},
	{name: "SET_FLAG", macro: "EVENT_SET_FLAG", params: []string{"flag"}},
}

func isAllZero(b []byte) bool {
	for _, v := range b {
		if v != 0 {
			return false
		}
	}
	return true
}

func getEventPool() map[string]eventDef {
	pool := map[string]eventDef{}
	for _, e := range eventDefinitions {
		pool[e.name] = e
	}
	return pool
}

type event struct {
	Timer int
	Op    string
	Args  []int
}

func fetchEntityIDs(ovlName string) (map[int]string, error) {
	path := "src/st"
	if strings.HasPrefix(ovlName, "bo") || strings.HasPrefix(ovlName, "rbo") ||
		ovlName == "mar" {
		path = "src/boss"
	}
	return sotn.FetchEnumWithMin(path+"/"+ovlName, ovlName, "EntityID", 0x100)
}

func formatArg(param string, value int, entityIDs map[int]string) string {
	switch param {
	case "id":
		if name, ok := entityIDs[value]; ok && !strings.HasPrefix(name, "0x") {
			return name
		}
		return fmt.Sprintf("0x%02X", value)
	case "x", "y":
		return strconv.Itoa(value)
	default:
		return fmt.Sprintf("0x%X", value)
	}
}

func parseEvents(data []byte) ([]event, error) {
	events := make([]event, 0, 4)
	read1 := func(p int) (int, error) {
		if p >= len(data) {
			return 0, fmt.Errorf("event timeline runs past the end of its asset range")
		}
		return int(data[p]), nil
	}
	terminatorSentinel := false
	for p := 0; p < len(data); {
		// skip 0x00 bytes padding
		if terminatorSentinel && isAllZero(data[p:]) {
			break
		}
		hi, err := read1(p)
		if err != nil {
			return nil, err
		}
		lo, err := read1(p + 1)
		if err != nil {
			return nil, err
		}
		timer := hi<<8 | lo
		p += 2
		if timer == terminator {
			events = append(events, event{Timer: timer, Op: "END"})
			terminatorSentinel = true
			continue
		}
		opcode, err := read1(p)
		if err != nil {
			return nil, err
		}
		p++
		if opcode >= len(eventDefinitions) {
			return nil, fmt.Errorf("unknown event opcode %#x at offset %#x", opcode, p-1)
		}
		def := eventDefinitions[opcode]
		e := event{Timer: timer, Op: def.name}
		for _, param := range def.params {
			switch param {
			case "x", "y":
				// nibble-packed 16-bit position
				hi, err := read1(p)
				if err != nil {
					return nil, err
				}
				lo, err := read1(p + 1)
				if err != nil {
					return nil, err
				}
				e.Args = append(e.Args, hi<<4|lo)
				p += 2
			default:
				v, err := read1(p)
				if err != nil {
					return nil, err
				}
				e.Args = append(e.Args, v)
				p++
			}
		}
		events = append(events, e)
	}
	return events, nil
}

func (h *handler) Extract(e assets.ExtractArgs) error {
	if e.Start == e.End {
		return fmt.Errorf("a cutscene event timeline cannot be 0 bytes")
	}
	events, err := parseEvents(e.Data[e.Start:e.End])
	if err != nil {
		return fmt.Errorf("%s: %w", e.Name, err)
	}
	// a missing enum only costs readability, so fall back to raw numbers
	entityIDs, _ := fetchEntityIDs(e.OvlName)
	pool := getEventPool()
	sb := strings.Builder{}
	sb.WriteString("events:\n")
	for _, ev := range events {
		if ev.Op == "END" {
			sb.WriteString("  - [END]\n")
			continue
		}
		row := []string{strconv.Itoa(ev.Timer), ev.Op}
		for i, arg := range ev.Args {
			row = append(row, formatArg(pool[ev.Op].params[i], arg, entityIDs))
		}
		sb.WriteString(fmt.Sprintf("  - [%s]\n", strings.Join(row, ", ")))
	}
	return util.WriteFile(assetPath(e.AssetDir, e.Name), []byte(sb.String()))
}

type eventRow []string

func (r *eventRow) UnmarshalYAML(node ast.Node) error {
	seq, ok := node.(*ast.SequenceNode)
	if !ok {
		return fmt.Errorf("expected sequence, got %T", node)
	}
	for _, n := range seq.Values {
		*r = append(*r, n.GetToken().Value)
	}
	return nil
}

type eventsSrc struct {
	Events []eventRow `yaml:"events"`
}

func (h *handler) Build(e assets.BuildArgs) error {
	inFileName := assetPath(e.AssetDir, e.Name)
	data, err := os.ReadFile(inFileName)
	if err != nil {
		return fmt.Errorf("failed to read cutscene events file: %w", err)
	}
	var src eventsSrc
	if err := yaml.Unmarshal(data, &src); err != nil {
		return fmt.Errorf("failed to parse cutscene events file: %w", err)
	}
	pool := getEventPool()
	sb := strings.Builder{}
	sb.WriteString("// clang-format off\n")
	for i, row := range src.Events {
		if len(row) == 0 {
			return fmt.Errorf("event at line %d is empty", i+1)
		}
		if row[0] == "END" {
			if len(row) != 1 {
				return fmt.Errorf("END at line %d takes no arguments", i+1)
			}
			sb.WriteString("EVENT_END(),\n")
			continue
		}
		if len(row) < 2 {
			return fmt.Errorf("event at line %d needs a timer and an opcode", i+1)
		}
		timer, op, args := row[0], row[1], row[2:]
		def, found := pool[op]
		if !found {
			return fmt.Errorf("event %q at line %d is not a known opcode", op, i+1)
		}
		if len(args) != len(def.params) {
			return fmt.Errorf("event %q at line %d expects %d arguments but got %d",
				op, i+1, len(def.params), len(args))
		}
		sb.WriteString(def.macro)
		sb.WriteString("(")
		sb.WriteString(timer)
		for _, arg := range args {
			sb.WriteString(", ")
			sb.WriteString(arg)
		}
		sb.WriteString("),\n")
	}
	return util.WriteFile(sourcePath(e.SrcDir, e.Name), []byte(sb.String()))
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	return assets.InfoResult{}, nil
}

func assetPath(dir, name string) string {
	if name == "" {
		name = "cutscene_events"
	}
	return filepath.Join(dir, fmt.Sprintf("%s.yaml", name))
}

func sourcePath(dir, name string) string {
	if name == "" {
		name = "cutscene_events"
	}
	return filepath.Join(dir, fmt.Sprintf("gen/%s.h", name))
}
