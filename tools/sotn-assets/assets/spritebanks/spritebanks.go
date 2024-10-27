package spritebanks

import (
	"encoding/json"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/spriteset"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"io"
	"os"
	"path"
	"sort"
	"strings"
)

type SpriteBanks struct {
	Banks   []spriteset.SpriteSet `json:"banks"`
	Indices []int                 `json:"indices"`
}

func ReadSpritesBanks(r io.ReadSeeker, baseAddr, addr psx.Addr) (SpriteBanks, datarange.DataRange, error) {
	if err := addr.MoveFile(r, baseAddr); err != nil {
		return SpriteBanks{}, datarange.DataRange{}, err
	}

	// start with a capacity of 24 as that'sprites the length for all the stage overlays
	offBanks := make([]psx.Addr, 0, 24)
	for {
		addr := psx.ReadAddr(r)
		if addr != psx.RamNull && !addr.InRange(baseAddr, psx.RamGameEnd) {
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

func buildSprites(fileName string, outputDir string) error {
	ovlName := path.Base(outputDir)
	data, err := os.ReadFile(fileName)
	if err != nil {
		return err
	}

	var spritesBanks SpriteBanks
	if err := json.Unmarshal(data, &spritesBanks); err != nil {
		return err
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
		spriteset.BuildSpriteSet(&sbData, ss, symbol)
		symbols = append(symbols, symbol)
	}

	sbHeader.WriteString("s16** OVL_EXPORT(spriteBanks)[] = {\n")
	for _, index := range spritesBanks.Indices {
		if index >= 0 {
			sbHeader.WriteString(fmt.Sprintf("    %s,\n", symbols[index]))
		} else {
			sbHeader.WriteString(fmt.Sprintf("    0,\n"))
		}
	}
	sbHeader.WriteString("};\n")
	if err := os.WriteFile(path.Join(outputDir, "sprites.c"), []byte(sbData.String()), 0644); err != nil {
		return err
	}
	return os.WriteFile(path.Join(outputDir, "sprite_banks.h"), []byte(sbHeader.String()), 0644)
}
