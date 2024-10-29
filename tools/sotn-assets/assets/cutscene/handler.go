package cutscene

import (
	"bytes"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"gopkg.in/yaml.v2"
	"io"
	"os"
	"path"
	"path/filepath"
	"strconv"
	"strings"
)

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "cutscene" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	if e.Start == e.End {
		return fmt.Errorf("a cutscene script cannot be 0 bytes")
	}
	r := bytes.NewReader(e.Data)
	script, err := parseScript(r, e.RamBase, e.RamBase.Sum(e.Start), e.End-e.Start)
	if err != nil {
		return err
	}
	outFileName := assetPath(e.AssetDir, e.Name)
	dir := filepath.Dir(outFileName)
	if err := os.MkdirAll(dir, 0755); err != nil {
		fmt.Printf("failed to create directory %s: %v\n", dir, err)
		return err
	}
	yaml := "script:\n"
	for _, command := range script {
		if len(command) == 0 {
			continue
		}
		switch command[0] {
		case "TEXT":
			yaml += fmt.Sprintf("  - [TEXT, \"%s\"]\n", command[1])
		case "BYTE":
			yaml += fmt.Sprintf("  - [BYTE, %s]\n", command[1])
		default:
			yaml += fmt.Sprintf("  - [%s]\n", strings.Join(command, ", "))
		}
	}
	return os.WriteFile(outFileName, []byte(yaml), 0644)
}

type scriptSrc struct {
	Script [][]string `yaml:"script"`
}

func (h *handler) Build(e assets.BuildArgs) error {
	inFileName := assetPath(e.AssetDir, e.Name)
	data, err := os.ReadFile(inFileName)
	if err != nil {
		return fmt.Errorf("failed to read cutscene file: %w", err)
	}
	var script scriptSrc
	if err := yaml.Unmarshal(data, &script); err != nil {
		return fmt.Errorf("failed to parse cutscene file: %w", err)
	}
	pool := getCommandPool()
	sb := strings.Builder{}
	sb.WriteString("// clang-format off\n")
	for i, args := range script.Script {
		if len(args) == 0 {
			return fmt.Errorf("")
		}
		op := args[0]
		if op == "TEXT" {
			text := args[1]
			for i, _ := range text {
				if text[i] == '\'' {
					sb.WriteString("'\\'',")
				} else {
					sb.WriteString(fmt.Sprintf("'%c',", text[i]))
				}
			}
			sb.WriteString("\n")
			continue
		}
		if op == "BYTE" {
			if len(args) != 2 {
				return fmt.Errorf("BYTE must have exactly one argument")
			}
			sb.WriteString(args[1])
			sb.WriteString(",\n")
			continue
		}
		cmd, found := pool[op]
		if !found {
			return fmt.Errorf("script %q does not have a command", args[0])
		}
		sb.WriteString(args[0])
		sb.WriteString("(")
		if len(cmd.params) != len(args)-1 {
			return fmt.Errorf("command %q at line %d expects %d arguments but got %d",
				op, i+1, len(cmd.params), len(args)-1)
		}
		sb.WriteString(strings.Join(args[1:], ","))
		sb.WriteString("),\n")
	}
	return os.WriteFile(sourcePath(e.SrcDir, e.Name), []byte(sb.String()), 0644)
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	return assets.InfoResult{}, nil
}

func assetPath(dir, name string) string {
	if name == "" {
		name = "cutscene_script"
	}
	return path.Join(dir, fmt.Sprintf("%s.yaml", name))
}

func sourcePath(dir, name string) string {
	if name == "" {
		name = "cutscene_script"
	}
	return path.Join(dir, fmt.Sprintf("%s.h", name))
}

type cmdDef struct {
	name   string
	params []int
}

var commandDefinitions = []cmdDef{
	{name: "END_CUTSCENE", params: []int{}},
	{name: "LINE_BREAK", params: []int{}},
	{name: "SET_SPEED", params: []int{1}},
	{name: "SET_WAIT", params: []int{1}},
	{name: "HIDE_DIALOG", params: []int{}},
	{name: "SET_PORTRAIT", params: []int{1, 1}},
	{name: "NEXT_DIALOG", params: []int{}},
	{name: "SET_POS", params: []int{1, 1}},
	{name: "CLOSE_DIALOG", params: []int{}},
	{name: "PLAY_SOUND", params: []int{2}},
	{name: "WAIT_FOR_SOUND", params: []int{}},
	{name: "SCRIPT_UNKNOWN_11", params: []int{}},
	{name: "SET_END", params: []int{4}},
	{name: "SCRIPT_UNKNOWN_13", params: []int{}},
	{name: "SCRIPT_UNKNOWN_14", params: []int{4, 4, 4}},
	{name: "SCRIPT_UNKNOWN_15", params: []int{4}},
	{name: "WAIT_FOR_FLAG", params: []int{1}},
	{name: "SET_FLAG", params: []int{1}},
	{name: "SCRIPT_UNKNOWN_18", params: []int{}},
	{name: "LOAD_PORTRAIT", params: []int{4, 1}},
	{name: "SCRIPT_UNKNOWN_20", params: []int{2}},
	{name: "SCRIPT_UNKNOWN_21", params: []int{}},
	{name: "RESET_FLAG", params: []int{1}},
	{name: "SCRIPT_UNKNOWN_23", params: []int{}},
	{name: "WAIT_FOR_FLAG_RESET", params: []int{1}},
}

func getCommandPool() map[string]cmdDef {
	cmdPool := map[string]cmdDef{}
	for _, command := range commandDefinitions {
		cmdPool[command.name] = command
	}
	return cmdPool
}

func parseScript(r io.ReadSeeker, baseAddr, addr psx.Addr, length int) ([][]string, error) {
	if err := addr.MoveFile(r, baseAddr); err != nil {
		return nil, fmt.Errorf("unable to read cutscene script: %w", err)
	}

	script := make([][]string, 0)
	text := ""
	flushText := func() {
		if len(text) > 0 {
			script = append(script, []string{"TEXT", text})
			text = ""
		}
	}
	read1 := func(r io.ReadSeeker) byte {
		b := make([]byte, 1)
		_, _ = r.Read(b)
		length -= 1
		return b[0]
	}
	read2 := func(r io.ReadSeeker) int {
		b := make([]byte, 2)
		_, _ = r.Read(b)
		length -= 2
		return int(b[1]) | (int(b[0]) << 4)
	}
	read4 := func(r io.ReadSeeker) int {
		b := make([]byte, 4)
		_, _ = r.Read(b)
		length -= 4
		return int(b[3]) | (int(b[2]) << 4) | (int(b[1]) << 8) | (int(b[0]) << 12) | 0x80100000
	}
	for length > 0 {
		op := int(read1(r))
		if op < 0x20 {
			flushText()
			command := []string{commandDefinitions[op].name}
			for _, param := range commandDefinitions[op].params {
				switch param {
				case 1:
					command = append(command, strconv.FormatInt(int64(read1(r)), 10))
				case 2:
					command = append(command, "0x"+strconv.FormatInt(int64(read2(r)), 16))
				case 4:
					command = append(command, "0x"+strconv.FormatInt(int64(read4(r)), 16))
				}
			}
			script = append(script, command)
		} else if op < 0x7F {
			text += string([]byte{byte(op)})
		} else {
			strByte := "0x" + strconv.FormatInt(int64(op), 16)
			script = append(script, []string{"BYTE", strByte})
		}
	}
	flushText()
	return script, nil
}
