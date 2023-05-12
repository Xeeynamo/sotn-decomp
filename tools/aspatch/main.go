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

type patcher struct {
	r     *bufio.Reader
	w     *bufio.Writer
	nLine int
}

func main() {
	err := initPatcher(os.Stdin, os.Stdout).patch()
	if err != nil {
		panic(err)
	}
}

func initPatcher(r io.Reader, w io.Writer) *patcher {
	return &patcher{
		r:     bufio.NewReader(r),
		w:     bufio.NewWriter(w),
		nLine: 0,
	}
}

func (p *patcher) readLine() (string, error) {
	line, err := p.r.ReadString('\n')
	p.nLine += 1
	if err == io.EOF {
		err = p.w.Flush()
		if err == nil {
			return "", io.EOF
		}
	}
	if err != nil {
		if err != nil {
			return "", err
		}
	}

	return line, nil
}

func (p *patcher) write(str string) {
	p.w.WriteString(str)
}

func (p *patcher) makeError(err error) error {
	return fmt.Errorf("line %d: %s", p.nLine, err.Error())
}

func (p *patcher) patch() error {
	for {
		line, err := p.readLine()
		if err != nil {
			if err == io.EOF {
				return nil
			}
			return err
		}

		err = p.patchLine(line)
		if err != nil {
			if err == io.EOF {
				return nil
			}
			return p.makeError(err)
		}
	}
}

func (p *patcher) isLabel(tokens []string) bool {
	return len(tokens) >= 2 && tokens[0] == "$" && tokens[2] == ":"
}

func (p *patcher) patchLine(line string) error {
	tokens, err := tokenize(line)
	if err != nil {
		return p.makeError(err)
	}

	if len(tokens) == 0 {
		p.write(line) // passtrough comments
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
			p.write(line)
		case 9: // variant with pointer
			if tokens[3] != "," || tokens[5] != "(" || tokens[8] != ")" {
				return p.makeError(fmt.Errorf("unable to parse '%s': token keys not recognised", line))
			}

			op := tokens[0]
			dstReg := tokens[1] + tokens[2]
			addr := tokens[4]
			ptrReg := tokens[6] + tokens[7]

			iAddr, err := strconv.Atoi(addr) // check if it's a digit or identifier
			if err != nil || iAddr > 0x10000 {
				p.write("\t.set\tnoat\n")
				p.write(fmt.Sprintf("\tlui\t$1,%%hi(%s)\n", addr))
				p.write(fmt.Sprintf("\taddu\t$1,$1,%s\n", ptrReg))
				p.write(fmt.Sprintf("\t%s\t%s,%%lo(%s)($1)\n", op, dstReg, addr))
				p.write("\t.set\tat\n")
			} else {
				// fallback
				p.write(line)
			}
		case 10: // variant with label
			p.write(line)
		default:
			return p.makeError(fmt.Errorf("unable to parse '%s': len(tokens)=%d", line, len(tokens)))
		}
	case "rem":
		srcReg1 := tokens[4] + tokens[5]
		srcReg2 := tokens[7] + tokens[8]
		dstReg := tokens[1] + tokens[2]
		p.write("\t.set\tnoreorder\n")
		p.write("\t.set\tnomacro\n")
		p.write("\t.set\tnoat\n")
		p.write(fmt.Sprintf("\tdiv\t$0,%s,%s\n", srcReg1, srcReg2))
		p.write(fmt.Sprintf("\tbnez\t%s,.L_NOT_DIV_BY_ZERO_%d\n", srcReg2, p.nLine))
		p.write("\tnop\n")
		p.write("\tbreak\t0x7\n")
		p.write(fmt.Sprintf(".L_NOT_DIV_BY_ZERO_%d:\n", p.nLine))
		p.write("\taddiu\t$1,$0,-1\n")
		p.write(fmt.Sprintf("\tbne\t%s,$1,.L_DIV_BY_POSITIVE_SIGN_%d\n", srcReg2, p.nLine))
		p.write("\tlui\t$1,0x8000\n")
		p.write(fmt.Sprintf("\tbne\t%s,$1,.L_DIV_BY_POSITIVE_SIGN_%d\n", srcReg1, p.nLine))
		p.write("\tnop\n")
		p.write("\tbreak\t0x6\n")
		p.write(fmt.Sprintf(".L_DIV_BY_POSITIVE_SIGN_%d:\n", p.nLine))
		p.write(fmt.Sprintf("\tmfhi\t%s\n", dstReg))
		p.write("\t.set\tat\n")
		p.write("\t.set\tmacro\n")
		p.write("\t.set\treorder\n")
	case "div":
		srcReg1 := tokens[4] + tokens[5]
		srcReg2 := tokens[7] + tokens[8]
		dstReg := tokens[1] + tokens[2]
		p.write("\t.set\tnoreorder\n")
		p.write("\t.set\tnomacro\n")
		p.write("\t.set\tnoat\n")
		p.write(fmt.Sprintf("\tdiv\t$0,%s,%s\n", srcReg1, srcReg2))
		p.write(fmt.Sprintf("\tbnez\t%s,.L_NOT_DIV_BY_ZERO_%d\n", srcReg2, p.nLine))
		p.write("\tnop\n")
		p.write("\tbreak\t0x7\n")
		p.write(fmt.Sprintf(".L_NOT_DIV_BY_ZERO_%d:\n", p.nLine))
		p.write("\taddiu\t$1,$0,-1\n")
		p.write(fmt.Sprintf("\tbne\t%s,$1,.L_DIV_BY_POSITIVE_SIGN_%d\n", srcReg2, p.nLine))
		p.write("\tlui\t$1,0x8000\n")
		p.write(fmt.Sprintf("\tbne\t%s,$1,.L_DIV_BY_POSITIVE_SIGN_%d\n", srcReg1, p.nLine))
		p.write("\tnop\n")
		p.write("\tbreak\t0x6\n")
		p.write(fmt.Sprintf(".L_DIV_BY_POSITIVE_SIGN_%d:\n", p.nLine))
		p.write(fmt.Sprintf("\tmflo\t%s\n", dstReg))
		p.write("\t.set\tat\n")
		p.write("\t.set\tmacro\n")
		p.write("\t.set\treorder\n")
	case "divu":
		srcReg1 := tokens[4] + tokens[5]
		srcReg2 := tokens[7] + tokens[8]
		dstReg := tokens[1] + tokens[2]
		p.write("\t.set\tnoat\n")
		p.write(fmt.Sprintf("\tdivu\t$0,%s,%s\n", srcReg1, srcReg2))
		p.write(fmt.Sprintf("\tbnez\t%s,.L_NOT_DIV_BY_ZERO_%d\n", srcReg2, p.nLine))
		p.write("\tbreak\t0x7\n")
		p.write(fmt.Sprintf(".L_NOT_DIV_BY_ZERO_%d:\n", p.nLine))
		p.write(fmt.Sprintf("\tmflo\t%s\n", dstReg))
		p.write("\t.set\tat\n")
	default:
		p.write(line)
	}

	return nil
}

func tokenize(line string) ([]string, error) {
	var tokens []string
	var token string
	r := strings.NewReader(line)

	flush := func() {
		if token != "" {
			tokens = append(tokens, token)
			token = ""
		}
	}

	for {
		ch, _, err := r.ReadRune()
		if err != nil {
			flush()
			return tokens, nil
		}

		switch {
		case ch == ' ' || ch == '\t' || ch == '\n':
			flush()
		case unicode.IsLetter(ch) || unicode.IsDigit(ch) || ch == '_' || ch == '+' || ch == '-':
			token += string(ch)
		case ch == '"':
			flush()
			token += string(ch)
			for {
				ch, _, err = r.ReadRune()
				if err != nil {
					return tokens, fmt.Errorf("unexpected end of string")
				}
				token += string(ch)
				if ch == '"' {
					break
				}
			}
		case ch == '$', ch == '(', ch == ')', ch == ':', ch == '.', ch == ',':
			flush()
			tokens = append(tokens, string(ch))
		case ch == '#':
			flush()
			return tokens, nil
		default:
			return tokens, fmt.Errorf("unrecognized character '%s'", string(ch))
		}
	}
}
