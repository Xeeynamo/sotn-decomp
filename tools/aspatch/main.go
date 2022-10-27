package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
	"unicode"
)

func main() {
	writer := bufio.NewWriter(os.Stdout)
	reader := bufio.NewReader(os.Stdin)

	err := patch(writer, reader)
	if err != nil {
		panic(err)
	}
}

func patch(w *bufio.Writer, r *bufio.Reader) error {
	nLine := 0
	for {
		line, err := r.ReadString('\n')
		nLine += 1
		if err != nil {
			if err != io.EOF {
				return err
			}
			return w.Flush()
		}

		err = patchLine(w, line)
		if err != nil {
			return fmt.Errorf("%s at line %d", err, nLine)
		}
	}
}

func patchLine(w *bufio.Writer, line string) error {
	tokens, err := tokenize(line)
	if err != nil {
		return err
	}

	if len(tokens) == 0 {
		w.WriteString(line) // passtrough comments
		return nil
	}

	switch tokens[0] {
	case "lb":
		fallthrough
	case "lbu":
		fallthrough
	case "lh":
		fallthrough
	case "lhu":
		fallthrough
	case "lw":
		switch len(tokens) {
		case 5: // variant without pointer
			w.WriteString(line)
		case 9: // variant with pointer
			if tokens[3] != "," || tokens[5] != "(" || tokens[8] != ")" {
				return fmt.Errorf("unable to parse '%s'", line)
			}

			op := tokens[0]
			dstReg := tokens[1] + tokens[2]
			addr := tokens[4]
			ptrReg := tokens[6] + tokens[7]

			iAddr, err := strconv.Atoi(addr) // check if it's a digit or identifier
			if err != nil || iAddr > 0x10000 {
				w.WriteString(fmt.Sprintf("\tlui\t$1,%%hi(%s)\n", addr))
				w.WriteString(fmt.Sprintf("\taddu\t$1,$1,%s\n", ptrReg))
				w.WriteString(fmt.Sprintf("\t%s\t%s,%%lo(%s)($1)\n", op, dstReg, addr))
			} else {
				// fallback
				w.WriteString(line)
			}
		default:
			return fmt.Errorf("unable to parse '%s'", line)
		}
	default:
		w.WriteString(line)
	}

	return nil
}

func tokenize(line string) ([]string, error) {
	tokens := make([]string, 0)
	token := ""

	flush := func() {
		if len(token) > 0 {
			tokens = append(tokens, token)
			token = ""
		}
	}

	r := strings.NewReader(line)
	for {
		ch, size, _ := r.ReadRune()
		if size == 0 {
			return tokens, nil
		}

		switch {
		case unicode.IsSpace(ch):
			if len(token) > 0 {
				flush()
			}
		case unicode.IsLetter(ch) || unicode.IsDigit(ch) || ch == '_' || ch == '+' || ch == '-':
			token += string(ch)
		case ch == '"':
			token += "\""
			for {
				ch, size, _ = r.ReadRune()
				if size == 0 {
					return tokens, fmt.Errorf("unexpected end of string")
				}
				if ch == '"' {
					token += "\""
					break
				}

				token += string(ch)
			}
		case ch == '$':
			fallthrough
		case ch == '(':
			fallthrough
		case ch == ')':
			fallthrough
		case ch == ':':
			fallthrough
		case ch == '.':
			fallthrough
		case ch == ',':
			flush()
			token = string(ch)
			flush()
		case ch == '#':
			flush()
			return tokens, nil
		default:
			return tokens, fmt.Errorf("unrecognized character '%s'", string(ch))
		}
	}
}
