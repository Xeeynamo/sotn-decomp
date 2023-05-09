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
				return fmt.Errorf("unable to parse '%s': token keys not recognised", line)
			}

			op := tokens[0]
			dstReg := tokens[1] + tokens[2]
			addr := tokens[4]
			ptrReg := tokens[6] + tokens[7]

			iAddr, err := strconv.Atoi(addr) // check if it's a digit or identifier
			if err != nil || iAddr > 0x10000 {
				w.WriteString("\t.set\tnoat\n")
				w.WriteString(fmt.Sprintf("\tlui\t$1,%%hi(%s)\n", addr))
				w.WriteString(fmt.Sprintf("\taddu\t$1,$1,%s\n", ptrReg))
				w.WriteString(fmt.Sprintf("\t%s\t%s,%%lo(%s)($1)\n", op, dstReg, addr))
				w.WriteString("\t.set\tat\n")
			} else {
				// fallback
				w.WriteString(line)
			}
		case 10: // variant with label
			w.WriteString(line)
		default:
			return fmt.Errorf("unable to parse '%s': len(tokens)=%d", line, len(tokens))
		}
	case "rem":
		srcReg1 := tokens[4] + tokens[5]
		srcReg2 := tokens[7] + tokens[8]
		dstReg := tokens[1] + tokens[2]
		w.WriteString("\t.set\tnoat\n")
		w.WriteString(fmt.Sprintf("\tdiv\t$0,%s,%s\n", srcReg1, srcReg2))
		w.WriteString(fmt.Sprintf("\tbnez\t%s,.L_NOT_DIV_BY_ZERO\n", srcReg2))
		w.WriteString("\tbreak\t0x7\n")
		w.WriteString(".L_NOT_DIV_BY_ZERO:\n")
		w.WriteString("\taddiu\t$1,$0,-1\n")
		w.WriteString(fmt.Sprintf("\tbne\t%s,$1,.L_DIV_BY_POSITIVE_SIGN\n", srcReg2))
		w.WriteString("\tlui\t$1,0x8000\n")
		w.WriteString(fmt.Sprintf("\tbne\t%s,$1,.L_DIV_BY_POSITIVE_SIGN\n", srcReg1))
		w.WriteString("\tbreak\t0x6\n")
		w.WriteString(".L_DIV_BY_POSITIVE_SIGN:\n")
		w.WriteString(fmt.Sprintf("\tmfhi\t%s\n", dstReg))
		w.WriteString("\tnop\n")
		w.WriteString("\t.set\tat\n")
	case "divu":
		srcReg1 := tokens[4] + tokens[5]
		srcReg2 := tokens[7] + tokens[8]
		dstReg := tokens[1] + tokens[2]
		w.WriteString("\t.set\tnoat\n")
		w.WriteString(fmt.Sprintf("\tdivu\t$0,%s,%s\n", srcReg1, srcReg2))
		w.WriteString(fmt.Sprintf("\tbnez\t%s,.L_NOT_DIV_BY_ZERO\n", srcReg2))
		w.WriteString("\tbreak\t0x7\n")
		w.WriteString(".L_NOT_DIV_BY_ZERO:\n")
		w.WriteString(fmt.Sprintf("\tmflo\t%s\n", dstReg))
		w.WriteString("\t.set\tat\n")
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
