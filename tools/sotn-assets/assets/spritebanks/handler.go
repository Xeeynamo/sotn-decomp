package spritebanks

import (
	"bytes"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"path"
)

const banksCount = 24 // the number seems to be fixed

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "sprite_banks" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	if e.Start == e.End {
		return fmt.Errorf("a group of sprites cannot be 0 bytes long")
	}
	r := bytes.NewReader(e.Data)
	banks, _, err := ReadSpritesBanks(r, e.RamBase, e.RamBase.Sum(e.Start))
	if err != nil {
		return fmt.Errorf("failed to read sprites: %w", err)
	}
	return util.WriteJsonFile(assetPath(e.AssetDir, e.Name), banks)
}

func (h *handler) Build(e assets.BuildArgs) error {
	return buildSprites(assetPath(e.AssetDir, e.Name), e.SrcDir)
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	r := bytes.NewReader(a.StageData)
	header, err := sotn.ReadStageHeader(r)
	if err != nil {
		return assets.InfoResult{}, err
	}
	_, dataRange, err := ReadSpritesBanks(r, psx.RamStageBegin, header.Sprites)
	if err != nil {
		return assets.InfoResult{}, err
	}
	return assets.InfoResult{
		AssetEntries: []assets.InfoAssetEntry{
			{
				DataRange: datarange.FromAddr(header.Sprites, banksCount*4),
				Kind:      h.Name(),
				Name:      "sprite_banks",
			},
		},
		SplatEntries: []assets.InfoSplatEntry{
			{
				DataRange: dataRange,
				Name:      "sprites",
			},
		},
	}, nil
}

func assetPath(dir, name string) string {
	return path.Join(dir, fmt.Sprintf("%s.json", name))
}
