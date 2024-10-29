package sotn

import (
	"bufio"
	"fmt"
	"io"
	"regexp"
	"strconv"
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

func ParseCEnum(r io.Reader, name string) (map[int]string, error) {
	enumMap := make(map[int]string, 0x100)
	for i := 0; i < 0x100; i++ {
		enumMap[i] = fmt.Sprintf("0x%02X", i)
	}
	scanner := bufio.NewScanner(r)
	startRegex := regexp.MustCompile(fmt.Sprintf(`enum\s+%s\s*{`, name))
	currentValue := 0
	for scanner.Scan() {
		line := removeComments(scanner.Text())
		if startRegex.MatchString(line) {
			for scanner.Scan() {
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
				if len(parts) > 1 {
					valueStr := strings.TrimSpace(parts[1])
					base := 10
					if strings.HasPrefix(valueStr, "0x") {
						valueStr = valueStr[2:]
						base = 16
					}
					value, err := strconv.ParseInt(valueStr, base, 32)
					if err != nil {
						return nil, err
					}
					currentValue = int(value)
				}
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
