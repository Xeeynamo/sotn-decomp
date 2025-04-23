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
