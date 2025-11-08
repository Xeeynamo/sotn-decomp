package sotn

import (
	"bufio"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"io"
	"os/exec"
	"regexp"
	"strings"
)

func removeComments(line string) string {
	for {
		start := strings.Index(line, "/*")
		end := strings.Index(line, "*/")
		if start == -1 || end == -1 || end < start {
			break
		}
		line = line[:start] + line[end+2:]
	}
	trailingCommentIndex := strings.Index(line, "//")
	if trailingCommentIndex != -1 {
		line = line[:trailingCommentIndex]
	}
	return strings.TrimSpace(line)
}

func ParseCEnum(r io.Reader, name string, min int) (map[int]string, error) {
	nameSet := make(map[string]int)
	enumMap := make(map[int]string, min)
	for i := 0; i < min; i++ {
		enumMap[i] = fmt.Sprintf("0x%02X", i)
	}
	scanner := bufio.NewScanner(r)
	startRegex := regexp.MustCompile(fmt.Sprintf(`enum\s+%s\s*{`, name))
	currentValue := 0
	nLine := 0
	for scanner.Scan() {
		nLine++
		line := removeComments(scanner.Text())
		if startRegex.MatchString(line) {
			for scanner.Scan() {
				nLine++
				line := removeComments(scanner.Text())
				line = strings.TrimRight(line, ",")
				if strings.Contains(line, "}") {
					break
				}
				parts := strings.Split(line, "=")
				name := strings.TrimSpace(parts[0])
				if name == "" {
					continue
				}
				if strings.HasPrefix(name, "NUM_") {
					continue
				}
				if len(parts) > 1 {
					valueStr := strings.TrimSpace(parts[1])
					if strings.Contains(valueStr, " |") { // ignore FLAG_1 | FLAG_2
						continue
					}
					value, err := util.ParseCNumber(valueStr)
					if err != nil {
						return nil, err
					}
					currentValue = value
				}
				if nLineDup, ok := nameSet[name]; ok {
					return nil, fmt.Errorf("duplicate enum field %s at line %d, already found at line %d", name, nLine, nLineDup)
				}
				nameSet[name] = nLine
				enumMap[currentValue] = name
				currentValue++
			}
		}
	}
	if err := scanner.Err(); err != nil {
		return nil, err
	}
	return enumMap, nil
}

// Read an enum from a header file after prepreprocessing
func FetchEnumWithMin(srcDir, ovlName, enumName string, min int) (map[int]string, error) {
    header := fmt.Sprintf("%s/%s.h", srcDir, ovlName)
    cpp, err := exec.LookPath("cpp")
    cmd := exec.Command(cpp,
                        fmt.Sprintf("-DVERSION=%s"),
                        "-lang-c",
                        "-Iinclude",
                        "-Iinclude/psxsdk",
                        "-fno-builtin",
                        "-undef",
                        "-P",
                        header)
    o, err := cmd.Output()

	if err != nil {
		return nil, fmt.Errorf("failed preprocess header: %s %s: %w", cmd.Path, cmd.Args, err)
	}
    r := strings.NewReader(string(o))
	return ParseCEnum(r, enumName, min)
}


func FetchEnum(srcDir, ovlName, enumName string) (map[int]string, error) {
    return FetchEnumWithMin(srcDir, ovlName, enumName, 0)
}
