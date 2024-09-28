package main

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"io"
	"strings"
)

func readCutscene(r io.ReadSeeker, baseAddr, addr psx.Addr) ([]string, error) {
	if err := addr.MoveFile(r, baseAddr); err != nil {
		return []string{}, fmt.Errorf("unable to read cutscene: %w", err)
	}

	read1 := func(r io.ReadSeeker) byte {
		b := make([]byte, 1)
		_, _ = r.Read(b)
		return b[0]
	}
	script := make([]string, 0)
	loop := true
	for loop {
		op := read1(r)
		switch op {
		case 0:
			script = append(script, "END_CUTSCENE()")
			script = append(script, "0xFF")
			script = append(script, "0xFF")
			loop = false
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
			script = append(script, fmt.Sprintf("PLAY_SOUND(0x%02X, 0x%02X)", read1(r), read1(r)))
		case 10:
			script = append(script, "WAIT_FOR_SOUND()")
		case 11:
			script = append(script, "SCRIPT_UNKNOWN_11()")
		case 13:
			script = append(script, "SCRIPT_UNKNOWN_13()")
		case 16:
			script = append(script, fmt.Sprintf("WAIT_FOR_FLAG(%d)", read1(r)))
		case 17:
			script = append(script, fmt.Sprintf("SET_FLAG(%d)", read1(r)))
		case 18:
			script = append(script, "SCRIPT_UNKOWN_18()")
		case 19:
			script = append(script, fmt.Sprintf(
				"LOAD_PORTRAIT(0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X)",
				read1(r), read1(r), read1(r), read1(r), read1(r)))
		case 20:
			script = append(script, fmt.Sprintf("SCRIPT_UNKNOWN_20(0x%02X, 0x%02X)", read1(r), read1(r)))
		case 0x27:
			script = append(script, "'\\''")
		default:
			if op >= 0x20 && op <= 0x7e {
				script = append(script, fmt.Sprintf("'%s'", string([]byte{op})))
			} else {
				return script, fmt.Errorf("unknown op 0x%02X", op)
			}
		}
	}
	return script, nil
}

func parseCutsceneAsC(r io.ReadSeeker, baseAddr, addr psx.Addr) (string, error) {
	script, err := readCutscene(r, baseAddr, addr)
	if err != nil {
		return "", err
	}
	return strings.ReplaceAll(strings.Join(script, ",\n"), "',\n'", "','"), nil
}
