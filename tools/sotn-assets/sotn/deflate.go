package sotn

func Deflate(src []byte) []byte {
	nibbles := make([]byte, len(src)*2)
	for i, b := range src {
		nibbles[i*2] = b & 0xF
		nibbles[i*2+1] = (b >> 4) & 0xF
	}
	dict := buildDictionary(nibbles)
	out := make([]byte, 8)
	copy(out, dict[:])

	writeFlag := 0
	writeNibble := func(ch byte) {
		if writeFlag == 0 {
			writeFlag = 1
			out = append(out, ch<<4)
		} else {
			writeFlag = 0
			out[len(out)-1] |= ch & 0xF
		}
	}

	var w1Dict, w2Dict [16]int
	var zDict [19]int
	for i := 0; i < 8; i++ {
		kind := dict[i] & 0xF0
		val := dict[i] & 0x0F
		opcode := i + 7
		switch kind {
		case 0x10:
			w1Dict[val] = opcode
		case 0x20:
			w2Dict[val] = opcode
		case 0x60:
			zDict[int(val)+3] = opcode
		}
	}

	i := 0
	for i < len(nibbles) {
		runLen := 1
		for i+runLen < len(nibbles) && nibbles[i+runLen] == nibbles[i] {
			runLen++
		}
		val := nibbles[i]
		if val == 0 {
			for runLen > 0 {
				if runLen >= 19 {
					consume := runLen
					if consume > 274 {
						consume = 274
					}
					writeNibble(0)
					amount := consume - 0x13
					writeNibble(byte(amount >> 4))
					writeNibble(byte(amount & 0xF))
					i += consume
					runLen -= consume
				} else if runLen >= 3 {
					consume := runLen
					if consume > 18 { // ************************************
						consume = 18
					}
					if zDict[consume] > 0 {
						writeNibble(byte(zDict[consume]))
					} else {
						writeNibble(6)
						writeNibble(byte(consume - 3))
					}
					i += consume
					runLen -= consume
				} else if runLen == 2 {
					if w2Dict[0] > 0 {
						writeNibble(byte(w2Dict[0]))
					} else {
						writeNibble(2)
						writeNibble(0)
					}
					i += 2
					runLen -= 2
				} else {
					break
				}
			}
			if runLen == 0 {
				continue
			}
		} else {
			for runLen > 0 {
				if runLen >= 3 {
					consume := runLen
					if consume > 18 {
						consume = 18
					}
					writeNibble(5)
					writeNibble(val)
					writeNibble(byte(consume - 3))
					i += consume
					runLen -= consume
				} else if runLen == 2 {
					if w2Dict[val] > 0 {
						writeNibble(byte(w2Dict[val]))
					} else {
						writeNibble(2)
						writeNibble(val)
					}
					i += 2
					runLen -= 2
				} else {
					break
				}
			}
			if runLen == 0 {
				continue
			}
		}
		litStart := i
		for i < len(nibbles) {
			rl := 1
			for i+rl < len(nibbles) && nibbles[i+rl] == nibbles[i] {
				rl++
			}
			if rl >= 2 {
				break
			}
			i++
		}
		j := litStart
		for i-j >= 3 {
			writeNibble(4)
			writeNibble(nibbles[j])
			writeNibble(nibbles[j+1])
			writeNibble(nibbles[j+2])
			j += 3
		}
		if i-j == 2 {
			writeNibble(3)
			writeNibble(nibbles[j])
			writeNibble(nibbles[j+1])
		} else if i-j == 1 {
			if w1Dict[nibbles[j]] > 0 {
				writeNibble(byte(w1Dict[nibbles[j]]))
			} else {
				writeNibble(1)
				writeNibble(nibbles[j])
			}
		}
	}
	writeNibble(15)
	for len(out)%4 != 0 {
		out = append(out, 0)
	}
	return out
}

func buildDictionary(nibbles []byte) [8]byte {
	w1Counts := [16]int{}
	w2Counts := [16]int{}
	zCounts := [16]int{}

	i := 0
	for i < len(nibbles) {
		runLen := 1
		for i+runLen < len(nibbles) && nibbles[i+runLen] == nibbles[i] {
			runLen++
		}

		val := nibbles[i]
		if val == 0 {
			remaining := runLen
			if remaining >= 19 {
				remaining %= 274
				if remaining >= 19 {
					remaining = 0
				}
			}
			for remaining >= 3 {
				consume := remaining
				if consume > 18 {
					consume = 18
				}
				zCounts[consume-3]++
				remaining -= consume
			}
			if remaining == 2 {
				w2Counts[0]++
				remaining = 0
			}
			if remaining == 1 {
				i += runLen - 1
				runLen = 1
			} else {
				i += runLen
				continue
			}
		} else {
			remaining := runLen
			for remaining >= 3 {
				consume := remaining
				if consume > 18 {
					consume = 18
				}
				remaining -= consume
			}
			if remaining == 2 {
				w2Counts[val]++
				remaining = 0
			}
			if remaining == 1 {
				i += runLen - 1
				runLen = 1
			} else {
				i += runLen
				continue
			}
		}

		litStart := i
		for i < len(nibbles) {
			rl := 1
			for i+rl < len(nibbles) && nibbles[i+rl] == nibbles[i] {
				rl++
			}
			if rl >= 2 {
				break
			}
			i++
		}
		litLen := i - litStart

		// Group as op4/op3/op1 and count op1 uses
		pos := litStart
		for litLen >= 3 {
			pos += 3
			litLen -= 3
		}
		if litLen == 2 {
			// op3, no w1 count
		} else if litLen == 1 {
			w1Counts[nibbles[pos]]++
		}
	}

	type candidate struct {
		dictByte byte
		count    int
	}
	var candidates []candidate
	for v := 0; v < 16; v++ {
		if w1Counts[v] > 0 {
			candidates = append(candidates, candidate{byte(0x10 | v), w1Counts[v]})
		}
	}
	for v := 0; v < 16; v++ {
		if w2Counts[v] > 0 {
			candidates = append(candidates, candidate{byte(0x20 | v), w2Counts[v]})
		}
	}
	for c := 0; c < 16; c++ {
		if zCounts[c] > 0 {
			candidates = append(candidates, candidate{byte(0x60 | c), zCounts[c]})
		}
	}
	for i := 0; i < len(candidates); i++ {
		for j := i + 1; j < len(candidates); j++ {
			if candidates[j].count > candidates[i].count ||
				(candidates[j].count == candidates[i].count && candidates[j].dictByte < candidates[i].dictByte) {
				candidates[i], candidates[j] = candidates[j], candidates[i]
			}
		}
	}

	var dict [8]byte
	for i := 0; i < 8 && i < len(candidates); i++ {
		dict[i] = candidates[i].dictByte
	}
	return dict
}
