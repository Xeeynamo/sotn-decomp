package spriteset

import (
	"encoding/binary"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"io"
	"math/rand"
	"strings"
)

type SpriteSet []*spriteParts

func ReadSpriteSet(r io.ReadSeeker, baseAddr, addr psx.Addr) (SpriteSet, datarange.DataRange, error) {
	if err := addr.MoveFile(r, baseAddr); err != nil {
		return nil, datarange.DataRange{}, fmt.Errorf("invalid sprite offset: %w", err)
	}

	// the end of the Sprite array is the beginning of the earliest Sprite offset
	earliestSpriteOff := psx.RamStageEnd
	currentOff := addr
	var spriteOffsets []psx.Addr
	for {
		if currentOff == earliestSpriteOff {
			break
		}
		currentOff += 4

		var spriteOffset psx.Addr
		if err := binary.Read(r, binary.LittleEndian, &spriteOffset); err != nil {
			return nil, datarange.DataRange{}, err
		}
		spriteOffsets = append(spriteOffsets, spriteOffset)
		if spriteOffset != psx.RamNull {
			if !spriteOffset.InRange(baseAddr, psx.RamGameEnd) {
				err := fmt.Errorf("sprite offset %s is not valid", spriteOffset)
				return nil, datarange.DataRange{}, err
			}
			earliestSpriteOff = min(earliestSpriteOff, spriteOffset)
		}
	}
	headerRange := datarange.New(addr, earliestSpriteOff)
	bank := make(SpriteSet, len(spriteOffsets))
	var spriteRanges []datarange.DataRange
	for i, offset := range spriteOffsets {
		if offset == psx.RamNull {
			bank[i] = nil
			continue
		}
		sprites, ranges, err := readSpriteParts(r, baseAddr, offset)
		if err != nil {
			return nil, datarange.DataRange{}, fmt.Errorf("unable to read sprites: %w", err)
		}
		bank[i] = &sprites
		spriteRanges = append(spriteRanges, ranges)
	}

	return bank, datarange.MergeDataRanges(append(spriteRanges, headerRange)), nil
}

func BuildSpriteSet(sb *strings.Builder, set SpriteSet, mainSymbol string, r *rand.Rand) {
	var symbols []string
	for _, spriteGroup := range set {
		if spriteGroup != nil {
			symbol := fmt.Sprintf("spriteGroup_%08X", r.Int31())
			size := len(*spriteGroup)*11 + 1
			if (len(*spriteGroup) & 1) == 1 { // perform alignment at the end
				size += 2
			} else {
				size += 1
			}
			sb.WriteString(fmt.Sprintf("static s16 %s[%d];\n", symbol, size))
			symbols = append(symbols, symbol)
		} else {
			symbols = append(symbols, "")
		}
	}
	sb.WriteString(fmt.Sprintf("s16* %s[] = {\n", mainSymbol))
	for _, symbol := range symbols {
		if len(symbol) > 0 {
			sb.WriteString(fmt.Sprintf("    %s,\n", symbol))
		} else {
			sb.WriteString("    0,\n")
		}
	}
	sb.WriteString("};\n")
	for i, spriteGroup := range set {
		if spriteGroup == nil {
			continue
		}
		sb.WriteString(fmt.Sprintf("static s16 %s[] = {\n", symbols[i]))
		sb.WriteString(fmt.Sprintf("    %d,\n", len(*spriteGroup)))
		for _, sprite := range *spriteGroup {
			sb.WriteString(fmt.Sprintf("    %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,\n",
				sprite.Flags, sprite.X, sprite.Y, sprite.Width, sprite.Height,
				sprite.Clut, sprite.Tileset, sprite.Left, sprite.Top, sprite.Right, sprite.Bottom))
		}
		if (len(*spriteGroup) & 1) == 1 { // perform alignment at the end
			sb.WriteString("    0, 0\n")
		} else {
			sb.WriteString("    0\n")
		}
		sb.WriteString("};\n")
	}
}
