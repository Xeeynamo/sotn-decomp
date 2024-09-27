package main

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"io"
	"strings"
)

func readCutscene(r io.ReadSeeker, baseAddr, addr psx.Addr, length int) ([]string, error) {
	if err := addr.MoveFile(r, baseAddr); err != nil {
		return []string{}, fmt.Errorf("unable to read cutscene: %w", err)
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
	script := make([]string, 0)
	for length > 0 {
		op := read1(r)
		switch op {
		case 0:
			script = append(script, "END_CUTSCENE()")
		case 1:
			script = append(script, "LINE_BREAK()")
		case 2:
			script = append(script, fmt.Sprintf("SET_SPEED(%d)", read1(r)))
		case 3:
			script = append(script, fmt.Sprintf("SET_WAIT(%d)", read1(r)))
		case 4:
			script = append(script, "HIDE_DIALOG()")
		case 5:
			script = append(script, fmt.Sprintf("SET_PORTRAIT(%d, %d)", read1(r), read1(r)))
		case 6:
			script = append(script, "NEXT_DIALOG()")
		case 7:
			script = append(script, fmt.Sprintf("SET_POS(%d, %d)", read1(r), read1(r)))
		case 8:
			script = append(script, "CLOSE_DIALOG()")
		case 9:
			script = append(script, fmt.Sprintf("PLAY_SOUND(0x%X)", read2(r)))
		case 10:
			script = append(script, "WAIT_FOR_SOUND()")
		case 11:
			script = append(script, "SCRIPT_UNKNOWN_11()")
		case 12:
			script = append(script, fmt.Sprintf(
				"SCRIPT_UNKNOWN_12(0x%08X)", read4(r)))
		case 13:
			script = append(script, "SCRIPT_UNKNOWN_13()")
		case 14:
			script = append(script, fmt.Sprintf(
				"SCRIPT_UNKNOWN_14(0x%08X, 0x%08X, 0x%08X)", read4(r), read4(r), read4(r)))
		case 15:
			script = append(script, fmt.Sprintf(
				"SCRIPT_UNKNOWN_15(0x%08X)", read4(r)))
		case 16:
			script = append(script, fmt.Sprintf("WAIT_FOR_FLAG(%d)", read1(r)))
		case 17:
			script = append(script, fmt.Sprintf("SET_FLAG(%d)", read1(r)))
		case 18:
			script = append(script, "SCRIPT_UNKOWN_18()")
		case 19:
			script = append(script, fmt.Sprintf(
				"LOAD_PORTRAIT(0x%08X, %d)", read4(r), read1(r)))
		case 20:
			script = append(script, fmt.Sprintf("SCRIPT_UNKNOWN_20(0x%X)", read2(r)))
		case 0x27:
			script = append(script, "'\\''")
		case 0xFF:
			script = append(script, "0xFF")
		default:
			if op >= 0x20 && op <= 0x7E {
				script = append(script, fmt.Sprintf("'%s'", string([]byte{op})))
			} else {
				script = append(script, fmt.Sprintf("0x%02X", op))
			}
		}
	}
	return script, nil
}

func parseCutsceneAsC(r io.ReadSeeker, baseAddr, addr psx.Addr, length int) (string, error) {
	script, err := readCutscene(r, baseAddr, addr, length)
	if err != nil {
		return "", err
	}
	return "// clang-format off\n" + strings.ReplaceAll(strings.Join(script, ",\n"), "',\n'", "','"), nil
}
