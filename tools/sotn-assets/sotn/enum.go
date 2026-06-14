package sotn

import (
	"bufio"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"io"
	"os/exec"
	"regexp"
	"strings"
	"sync"
)

func removeComments(line string) string {
	for {
		start := strings.Index(line, "/*")
		if start == -1 {
			break
		}
		end := strings.Index(line[start+2:], "*/")
		if end == -1 {
			break
		}
		line = line[:start] + line[start+end+4:]
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
		line := scanner.Text()
		if strings.Contains(line, "enum") && startRegex.MatchString(removeComments(line)) {
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

// Cache keyed by: version:file:enum
var enumCache = make(map[string]map[int]string)
var lock = sync.RWMutex{}

// Read an enum from a header file after prepreprocessing
func FetchEnumWithMin(srcDir, ovlName, enumName string, min int) (map[int]string, error) {
	version := GetVersion()
	header := fmt.Sprintf("%s/%s.h", srcDir, ovlName)
	cacheKey := fmt.Sprintf("%s:%s:%s", version, header, enumName)

	lock.RLock()
	parsed, ok := enumCache[cacheKey]
	lock.RUnlock()
	if ok {
		return parsed, nil
	}

	cpp, err := exec.LookPath("cpp")
	if err != nil {
		return nil, fmt.Errorf("failed to find `cpp': %w", err)
	}

	cmd := exec.Command(cpp,
		fmt.Sprintf("-DVERSION=%s", GetVersion()),
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
	parsed, err = ParseCEnum(r, enumName, min)

	if err == nil {
		lock.Lock()
		enumCache[cacheKey] = parsed
		lock.Unlock()
	}

	return parsed, err
}

func FetchEnum(srcDir, ovlName, enumName string) (map[int]string, error) {
	return FetchEnumWithMin(srcDir, ovlName, enumName, 0)
}
