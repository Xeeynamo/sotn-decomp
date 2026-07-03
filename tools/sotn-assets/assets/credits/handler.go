package credits

import (
	"bytes"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strconv"
	"strings"

	"github.com/goccy/go-yaml"
	"github.com/goccy/go-yaml/ast"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
)

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "credits" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	if e.Start == e.End {
		return fmt.Errorf("a credits script cannot be 0 bytes")
	}
	r := bytes.NewReader(e.Data)
	script, err := parseScript(r, e.RamBase, e.RamBase.Sum(e.Start), e.End-e.Start)
	if err != nil {
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
	return util.WriteFile(assetPath(e.AssetDir, e.Name), []byte(yaml))
}

type scriptRow []string

// skip conversion of hex values into decimals
func (r *scriptRow) UnmarshalYAML(node ast.Node) error {
	seq, ok := node.(*ast.SequenceNode)
	if !ok {
		return fmt.Errorf("expected sequence, got %T", node)
	}
	for _, n := range seq.Values {
		*r = append(*r, n.GetToken().Value)
	}
	return nil
}

type scriptSrc struct {
	Script []scriptRow `yaml:"script"`
}

func (h *handler) Build(e assets.BuildArgs) error {
	platform := sotn.GetPlatform()
	inFileName := assetPath(e.AssetDir, e.Name)
	data, err := os.ReadFile(inFileName)
	if err != nil {
		return fmt.Errorf("failed to read credits file: %w", err)
	}
	var script scriptSrc
	if err := yaml.Unmarshal(data, &script); err != nil {
		return fmt.Errorf("failed to parse credits file: %w", err)
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
			for _, r := range text {
				if r == '\'' {
					sb.WriteString("'\\'',")
				} else {
					byteValue := byte(r)

					// If the byte is in the PSP's upper language character position,
					// output the hex literal
					if platform == sotn.PlatformPSP && byteValue >= 0xA0 && byteValue <= 0xDF {
						// TODO: This can probably output something like _SE() which
						// can be handled by sotn_str
						sb.WriteString(fmt.Sprintf("'\\x%02X',", byteValue))
					} else {
						// Otherwise, just output the character as-is
						sb.WriteString(fmt.Sprintf("'%c',", r))
					}
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
		if cmd.params != len(args)-1 {
			return fmt.Errorf("command %q at line %d expects %d arguments but got %d",
				op, i+1, cmd.params, len(args)-1)
		}
		sb.WriteString(strings.Join(args[1:], ","))
		sb.WriteString("),\n")
	}
	return util.WriteFile(sourcePath(e.SrcDir, e.Name), []byte(sb.String()))
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	return assets.InfoResult{}, nil
}

func assetPath(dir, name string) string {
	if name == "" {
		name = "credits_script"
	}
	return filepath.Join(dir, fmt.Sprintf("%s.yaml", name))
}

func sourcePath(dir, name string) string {
	if name == "" {
		name = "credits_script"
	}
	return filepath.Join(dir, fmt.Sprintf("gen/%s.h", name))
}

type cmdDef struct {
	name   string
	params int
}

var commandDefinitions = []cmdDef{
	{name: "END_CREDITS", params: 0},
	{name: "CREDITS_SUBTEXT", params: 1},
	{name: "CREDITS_ENTRY", params: 1},
	{name: "CREDITS_SECTION", params: 1},
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
		return nil, fmt.Errorf("unable to read credits script: %w", err)
	}
	platform := sotn.GetPlatform()

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
	for length > 0 {
		op := int(read1(r))
		if op < len(commandDefinitions) {
			flushText()
			command := []string{commandDefinitions[op].name}
			for i := 0; i < commandDefinitions[op].params; i++ {
				command = append(command, strconv.FormatInt(int64(read1(r)), 10))
			}
			script = append(script, command)
		} else if op < 0x20 {
			text += fmt.Sprintf("\\x%02X", byte(op))
		} else if op < 0x7F {
			if op == 0x22 {
				text += "\\\""
			} else {
				text += string([]byte{byte(op)})
			}
		} else if op >= 0x80 && op <= 0x9F {
			strByte := "0x" + strconv.FormatInt(int64(op), 16)
			script = append(script, []string{"BYTE", strByte})
			strByte = "0x" + strconv.FormatInt(int64(read1(r)), 16)
			script = append(script, []string{"BYTE", strByte})
		} else if platform == sotn.PlatformPSP && op >= 0xA0 && op <= 0xDF {
			// PSP has multi-language support with characters that exceed the ASCII range
			text += fmt.Sprintf("\\x%02X", byte(op))
		} else {
			strByte := "0x" + strconv.FormatInt(int64(op), 16)
			script = append(script, []string{"BYTE", strByte})
		}
	}
	flushText()
	return script, nil
}
