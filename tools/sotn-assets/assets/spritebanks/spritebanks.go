package spritebanks

import (
	"encoding/json"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"sort"
	"strings"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/spriteset"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
)

type SpriteBanks struct {
	Banks   []spriteset.SpriteSet `json:"banks"`
	Indices []int                 `json:"indices"`
}

func ReadSpritesBanks(r io.ReadSeeker, baseAddr, addr psx.Addr, numBanks int) (SpriteBanks, datarange.DataRange, error) {
	if err := addr.MoveFile(r, baseAddr); err != nil {
		return SpriteBanks{}, datarange.DataRange{}, err
	}
	boundaries := baseAddr.Boundaries()
	offBanks := make([]psx.Addr, 0, banksCount)
	for {
		addr := psx.ReadAddr(r)
		if (addr != psx.RamNull && !addr.InRange(baseAddr, boundaries.GameEnd)) || (len(offBanks) == numBanks) {
			break
		}
		offBanks = append(offBanks, addr)
	}
	_, _ = r.Seek(-4, io.SeekCurrent)

	// the order sprites are stored must be preserved
	pool := map[psx.Addr]spriteset.SpriteSet{}
	var spriteRanges []datarange.DataRange
	for _, spriteAddr := range offBanks {
		if spriteAddr == psx.RamNull {
			continue
		}
		if _, found := pool[spriteAddr]; found {
			continue
		}
		bank, bankRange, err := spriteset.ReadSpriteSet(r, baseAddr, spriteAddr)
		if err != nil {
			return SpriteBanks{}, datarange.DataRange{}, fmt.Errorf("unable to read sprite Indices: %w", err)
		}
		pool[spriteAddr] = bank
		spriteRanges = append(spriteRanges, bankRange)
	}

	// scan for unreferenced sprite banks and add their ranges
	spriteRanges = append(spriteRanges, recoverGaps(r, baseAddr, spriteRanges, pool)...)

	// the indices do not guarantee sprites to be stored in a linear order
	// we must sort the offsets to preserve the order sprites are stored
	sortedOffsets := make([]psx.Addr, 0, len(pool))
	for offset := range pool {
		sortedOffsets = append(sortedOffsets, offset)
	}
	sort.Slice(sortedOffsets, func(i, j int) bool { return sortedOffsets[i] < sortedOffsets[j] })

	// create a list of indices to replace the original pointers
	indices := make([]int, len(offBanks))
	for i, offset := range offBanks {
		if offset == psx.RamNull {
			indices[i] = -1
		}
		for j, sortedOffset := range sortedOffsets {
			if offset == sortedOffset {
				indices[i] = j
			}
		}
	}

	banks := make([]spriteset.SpriteSet, len(sortedOffsets))
	for i, offset := range sortedOffsets {
		banks[i] = pool[offset]
	}

	return SpriteBanks{
		Banks:   banks,
		Indices: indices,
	}, datarange.MergeDataRanges(spriteRanges), nil
}

// Several overlays (RNO0, RCEN, RLIB, RNO2, RNZ1, BO7, RBO6) have an unreferenced sprite bank
// with no corresponding entry in the table. recoverGaps attempts to parse gaps in the referenced sprite banks
// and identify any which are unreferenced sprite banks, returning the ranges of recovered entries.
func recoverGaps(r io.ReadSeeker, baseAddr psx.Addr, ranges []datarange.DataRange, pool map[psx.Addr]spriteset.SpriteSet) []datarange.DataRange {
	known := append([]datarange.DataRange{}, ranges...)
	var recovered []datarange.DataRange
	for {
		gapAddr, gapEnd, found := firstGap(known)
		if !found {
			return recovered
		}
		bank, bankRange, err := spriteset.ReadSpriteSet(r, baseAddr, gapAddr)
		// Return error if the gap contains something other than a sprite bank
		if err != nil || bankRange.Begin() != gapAddr || bankRange.End() <= gapAddr || bankRange.End() > gapEnd {
			return recovered
		}
		pool[gapAddr] = bank
		known = append(known, bankRange)
		recovered = append(recovered, bankRange)
	}
}

// firstGap is the lowest gap between the given ranges, as a (begin, end) pair.
func firstGap(ranges []datarange.DataRange) (psx.Addr, psx.Addr, bool) {
	sorted := append([]datarange.DataRange{}, ranges...)
	sort.Slice(sorted, func(i, j int) bool { return sorted[i].Begin() < sorted[j].Begin() })
	end := psx.RamNull
	for _, cur := range sorted {
		if end != psx.RamNull && end < cur.Begin() {
			return end, cur.Begin(), true
		}
		if cur.End() > end {
			end = cur.End()
		}
	}
	return psx.RamNull, psx.RamNull, false
}

func buildSprites(jsonFileName, name, outputDir, ovlName string) error {
	data, err := os.ReadFile(jsonFileName)
	if err != nil {
		return err
	}

	var spritesBanks SpriteBanks
	if err := json.Unmarshal(data, &spritesBanks); err != nil {
		return err
	}
	if len(spritesBanks.Indices) != banksCount && len(spritesBanks.Indices) != banksCount+1 {
		return fmt.Errorf("the number of banks must be exactly %d, got %d", banksCount, len(spritesBanks.Indices))
	}

	sbHeader := strings.Builder{}
	sbHeader.WriteString("// clang-format off\n")
	sbData := strings.Builder{}
	sbData.WriteString("// clang-format off\n")
	sbData.WriteString("#include \"common.h\"\n")
	var symbols []string
	for i, ss := range spritesBanks.Banks {
		if len(ss) == 0 {
			symbols = append(symbols, "")
			continue
		}
		symbol := fmt.Sprintf("sprites_%s_%d", ovlName, i)
		sbHeader.WriteString(fmt.Sprintf("extern s16* %s[];\n", symbol))
		spriteset.BuildSpriteSet(&sbData, ss, symbol, false)
		symbols = append(symbols, symbol)
	}

	sbHeader.WriteString("s16** spriteBanks[] = {\n")
	for _, index := range spritesBanks.Indices {
		if index >= 0 {
			sbHeader.WriteString(fmt.Sprintf("    %s,\n", symbols[index]))
		} else {
			sbHeader.WriteString(fmt.Sprintf("    0,\n"))
		}
	}
	sbHeader.WriteString("};\n")

	spriteBanksFileName := filepath.Join(outputDir, "gen", fmt.Sprintf("%s.h", name))
	if err := util.WriteFile(filepath.Join(filepath.Dir(spriteBanksFileName), "sprites.c"), []byte(sbData.String())); err != nil {
		return err
	}
	return util.WriteFile(spriteBanksFileName, []byte(sbHeader.String()))
}
