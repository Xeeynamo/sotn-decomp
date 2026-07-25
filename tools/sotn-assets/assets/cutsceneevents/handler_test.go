package cutsceneevents

import (
	"testing"
)

var romTimelines = map[string][]byte{
	"dai": {0x00, 0x00, 0x00, 0x84, 0x46, 0x08, 0x80, 0x08, 0x80,
		0x00, 0x00, 0x00, 0x85, 0x47, 0x11, 0x10, 0x0A, 0xA7,
		0xFF, 0xFF},
	"lib": {0x00, 0x00, 0x00, 0x82, 0x23, 0x08, 0x80, 0x08, 0x80,
		0x00, 0x00, 0x00, 0x83, 0x26, 0x08, 0x80, 0x08, 0x80,
		0xFF, 0xFF},
	"no3": {0x00, 0x00, 0x00, 0x20, 0x58, 0x08, 0x80, 0x08, 0x80,
		0x00, 0x00, 0x00, 0x21, 0x5A, 0x0A, 0xA0, 0x07, 0x78,
		0xFF, 0xFF},
	"nz0": {0x00, 0x00, 0x00, 0x81, 0x4D, 0x08, 0x80, 0x08, 0x80,
		0x00, 0x00, 0x00, 0x82, 0x4C, 0x00, 0x00, 0x08, 0x83,
		0xFF, 0xFF},
	"st0": {0x00, 0x00, 0x00, 0x81, 0x17, 0x08, 0x80, 0x08, 0x80,
		0xFF, 0xFF},
	"mar": {0x00, 0x00, 0x00, 0x20, 0x1F, 0x08, 0x80, 0x08, 0x80,
		0x00, 0x00, 0x00, 0x21, 0x20, 0x05, 0x58, 0x0A, 0xA3,
		0xFF, 0xFF},
	// two timelines back to back, reached by two separate SET_EVENTS()
	"dre": {0x00, 0x00, 0x00, 0x84, 0x21, 0x08, 0x80, 0x08, 0x80,
		0x00, 0x08, 0x00, 0x85, 0x22, 0x0C, 0xC0, 0x08, 0x83,
		0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x84, 0x23, 0x08, 0x80, 0x08, 0x80,
		0x00, 0x08, 0x00, 0x85, 0x24, 0x0C, 0xC0, 0x08, 0x83,
		0xFF, 0xFF},
}

func encode(events []event) []byte {
	out := []byte{}
	for _, e := range events {
		if e.Op == "END" {
			out = append(out, 0xFF, 0xFF)
			continue
		}
		out = append(out, byte(e.Timer>>8), byte(e.Timer))
		var opcode byte
		var def eventDef
		for i, d := range eventDefinitions {
			if d.name == e.Op {
				opcode, def = byte(i), d
			}
		}
		out = append(out, opcode)
		for i, param := range def.params {
			switch param {
			case "x", "y":
				out = append(out, byte((e.Args[i]&0xFF0)>>4), byte(e.Args[i]&0xFF))
			default:
				out = append(out, byte(e.Args[i]))
			}
		}
	}
	return out
}

func TestRoundTripMatchesRom(t *testing.T) {
	for name, want := range romTimelines {
		t.Run(name, func(t *testing.T) {
			events, err := parseEvents(want)
			if err != nil {
				t.Fatalf("parseEvents: %v", err)
			}
			got := encode(events)
			if len(got) != len(want) {
				t.Fatalf("re-encoded %d bytes, want %d", len(got), len(want))
			}
			for i := range want {
				if got[i] != want[i] {
					t.Fatalf("byte %d: got %#02x, want %#02x", i, got[i], want[i])
				}
			}
		})
	}
}

func TestDecodesExpectedEvents(t *testing.T) {
	events, err := parseEvents(romTimelines["no3"])
	if err != nil {
		t.Fatalf("parseEvents: %v", err)
	}
	// EntityDeathCutsceneManager, then EntityDeath
	want := []event{
		{Timer: 0, Op: "SPAWN_ENTITY", Args: []int{0x20, 0x58, 0x80, 0x80}},
		{Timer: 0, Op: "SPAWN_ENTITY", Args: []int{0x21, 0x5A, 0xA0, 0x78}},
		{Timer: terminator, Op: "END"},
	}
	if len(events) != len(want) {
		t.Fatalf("got %d events, want %d", len(events), len(want))
	}
	for i := range want {
		if events[i].Op != want[i].Op || events[i].Timer != want[i].Timer {
			t.Errorf("event %d: got %+v, want %+v", i, events[i], want[i])
		}
		for j := range want[i].Args {
			if events[i].Args[j] != want[i].Args[j] {
				t.Errorf("event %d arg %d: got %#x, want %#x", i, j, events[i].Args[j], want[i].Args[j])
			}
		}
	}
}

func TestDreHasTwoTimelines(t *testing.T) {
	events, err := parseEvents(romTimelines["dre"])
	if err != nil {
		t.Fatalf("parseEvents: %v", err)
	}
	ends := 0
	for _, e := range events {
		if e.Op == "END" {
			ends++
		}
	}
	if ends != 2 {
		t.Fatalf("got %d terminators, want 2", ends)
	}
	// the second timeline spawns a different pair of actors than the first
	if events[0].Args[1] == events[3].Args[1] {
		t.Errorf("both timelines spawn entity id %#x", events[0].Args[1])
	}
}

func TestIgnoresTrailingAlignmentPadding(t *testing.T) {
	// DRE pads 2 bytes, NO3 and NZ0 pad 3
	for _, padLen := range []int{1, 2, 3, 8, 71} {
		padded := append(append([]byte{}, romTimelines["dai"]...),
			make([]byte, padLen)...)
		events, err := parseEvents(padded)
		if err != nil {
			t.Fatalf("pad %d: parseEvents: %v", padLen, err)
		}
		got := encode(events)
		if len(got) != len(romTimelines["dai"]) {
			t.Fatalf("pad %d: re-encoded %d bytes, want %d (padding must not round-trip)",
				padLen, len(got), len(romTimelines["dai"]))
		}
		for i := range romTimelines["dai"] {
			if got[i] != romTimelines["dai"][i] {
				t.Fatalf("pad %d: byte %d: got %#02x, want %#02x",
					padLen, i, got[i], romTimelines["dai"][i])
			}
		}
	}
}

func TestOnlyAbsorbsZeroPaddingAfterTerminator(t *testing.T) {
	// LIB's next asset starts immediately with non-zero bytes: absorbing it
	// silently would hide a config mistake
	trailing := append(append([]byte{}, romTimelines["lib"]...),
		0x18, 0x20, 0x61, 0x21)
	if _, err := parseEvents(trailing); err == nil {
		t.Error("expected an error for non-zero data after the terminator")
	}
	// zeros before any terminator are a truncated record, not padding
	if _, err := parseEvents([]byte{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}); err == nil {
		t.Error("expected an error for zeros with no preceding terminator")
	}
}

func TestRejectsTruncatedRecordThatLooksLikePadding(t *testing.T) {
	if _, err := parseEvents([]byte{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}); err == nil {
		t.Fatal("expected an error for a 6-byte all-zero SPAWN with missing operands")
	}
}

func TestFormatArg(t *testing.T) {
	entityIDs := map[int]string{0x58: "E_DEATH_SCENE_MGR"}
	for _, tc := range []struct {
		param string
		value int
		want  string
	}{
		// entity ids resolve to their enum name when the overlay declares one
		{"id", 0x58, "E_DEATH_SCENE_MGR"},
		// and fall back to hex when it does not (ST0 has gaps in its enum)
		{"id", 0x17, "0x17"},
		// coordinates read as decimal, they are screen positions
		{"x", 0x80, "128"},
		{"y", 0x110, "272"},
		// slots and flags stay hex
		{"slot", 0x84, "0x84"},
		{"flag", 0xC, "0xC"},
	} {
		if got := formatArg(tc.param, tc.value, entityIDs); got != tc.want {
			t.Errorf("formatArg(%q, %#x) = %q, want %q",
				tc.param, tc.value, got, tc.want)
		}
	}
}

func TestRejectsUnknownOpcode(t *testing.T) {
	if _, err := parseEvents([]byte{0x00, 0x00, 0x09, 0x00}); err == nil {
		t.Fatal("expected an error for opcode 0x9")
	}
}

func TestRejectsTruncatedTimeline(t *testing.T) {
	// a SPAWN whose operands are cut off, with no terminator
	if _, err := parseEvents([]byte{0x00, 0x00, 0x00, 0x20}); err == nil {
		t.Fatal("expected an error for a truncated timeline")
	}
}
