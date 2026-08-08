package sotn

func Inflate(src []byte) []byte {
	srcPos := 8
	dstPos := 0
	dictionary := src[:srcPos]
	readFlag := 0
	writeFlag := 0
	dst := make([]byte, 0, len(src)*2)

	readNibble := func() byte {
		if readFlag == 0 {
			readFlag = 1
			return (src[srcPos] >> 4) & 15
		} else {
			readFlag = 0
			srcPos++
			return src[srcPos-1] & 15
		}
	}
	writeNibble := func(ch byte) {
		if writeFlag == 0 {
			writeFlag = 1
			dst = append(dst, ch)
		} else {
			writeFlag = 0
			dstPos++
			dst[dstPos-1] += ch << 4
		}
	}

	for {
		op := readNibble()
		if op == 0 {
			amount := int(readNibble() << 4)
			amount += int(readNibble() + 0x13)
			for ; amount > 0; amount-- {
				writeNibble(0)
			}
		} else if op == 1 {
			writeNibble(readNibble())
		} else if op == 2 {
			ch := readNibble()
			writeNibble(ch)
			writeNibble(ch)
		} else if op == 3 {
			writeNibble(readNibble())
			writeNibble(readNibble())
		} else if op == 4 {
			writeNibble(readNibble())
			writeNibble(readNibble())
			writeNibble(readNibble())
		} else if op == 5 {
			ch := readNibble()
			for amount := int(readNibble() + 3); amount > 0; amount-- {
				writeNibble(ch)
			}
		} else if op == 6 {
			for amount := int(readNibble() + 3); amount > 0; amount-- {
				writeNibble(0)
			}
		} else if op == 15 {
			return dst
		} else {
			kind := dictionary[op-7] & 0xF0
			amount := dictionary[op-7] & 0x0F
			if kind == 0x10 {
				writeNibble(amount & 15)
			} else if kind == 0x20 {
				writeNibble(amount & 15)
				writeNibble(amount & 15)
			} else if kind == 0x60 {
				for count := (amount & 15) + 3; count > 0; count-- {
					writeNibble(0)
				}
			}
		}
	}
}

// maxInflateSize bounds the decompressed output so a stream of garbage that
// happens to decode cannot allocate without limit. The largest real image is
// 128x128 at 16bpp.
const maxInflateSize = 0x40000

// InflateSize walks the same opcode stream as Inflate but reports how many
// bytes of src it consumed instead of returning the output. Unlike Inflate it
// is bounds-checked, so a truncated or non-image stream reports ok == false
// rather than panicking.
//
// Note a stream of arbitrary bytes will often decode "successfully": this
// tells you how long a compressed image is, not whether one is present.
func InflateSize(src []byte) (compressed int, decompressed int, ok bool) {
	if len(src) < 8 {
		return 0, 0, false
	}
	srcPos := 8
	dstLen := 0
	dictionary := src[:srcPos]
	readFlag := 0
	writeFlag := 0
	overflow := false

	readNibble := func() byte {
		if srcPos >= len(src) {
			overflow = true
			return 0
		}
		if readFlag == 0 {
			readFlag = 1
			return (src[srcPos] >> 4) & 15
		}
		readFlag = 0
		srcPos++
		return src[srcPos-1] & 15
	}
	writeNibble := func() {
		if writeFlag == 0 {
			writeFlag = 1
			dstLen++
		} else {
			writeFlag = 0
		}
	}

	for {
		op := readNibble()
		if overflow {
			return 0, 0, false
		}
		switch {
		case op == 0:
			amount := int(readNibble() << 4)
			amount += int(readNibble() + 0x13)
			for ; amount > 0; amount-- {
				writeNibble()
			}
		case op == 1:
			readNibble()
			writeNibble()
		case op == 2:
			readNibble()
			writeNibble()
			writeNibble()
		case op == 3:
			readNibble()
			readNibble()
			writeNibble()
			writeNibble()
		case op == 4:
			readNibble()
			readNibble()
			readNibble()
			writeNibble()
			writeNibble()
			writeNibble()
		case op == 5:
			readNibble()
			for amount := int(readNibble() + 3); amount > 0; amount-- {
				writeNibble()
			}
		case op == 6:
			for amount := int(readNibble() + 3); amount > 0; amount-- {
				writeNibble()
			}
		case op == 15:
			// the reader consumes a byte on every second nibble, so a
			// terminator on a high nibble still counts that byte
			if readFlag != 0 {
				srcPos++
			}
			if srcPos > len(src) {
				return 0, 0, false
			}
			return srcPos, dstLen, true
		default:
			kind := dictionary[op-7] & 0xF0
			amount := dictionary[op-7] & 0x0F
			switch kind {
			case 0x10:
				writeNibble()
			case 0x20:
				writeNibble()
				writeNibble()
			case 0x60:
				for count := (amount & 15) + 3; count > 0; count-- {
					writeNibble()
				}
			}
		}
		if overflow || dstLen > maxInflateSize {
			return 0, 0, false
		}
	}
}
