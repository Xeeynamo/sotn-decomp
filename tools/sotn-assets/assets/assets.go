package assets

import (
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/splat"
)

type ExtractArgs struct {
	Data        []byte
	Start       int
	End         int
	AssetDir    string
	SrcDir      string
	Name        string
	Args        []string
	OvlName     string
	Version     sotn.Version
	SplatConfig *splat.Config
	RamBase     psx.Addr
	Boundaries  psx.Offsets
	Symbol      func(addr psx.Addr) string
}
type Extractor interface {
	Extract(a ExtractArgs) error
}

type BuildArgs struct {
	AssetDir string
	SrcDir   string
	Name     string
	Args     []string
	OvlName  string
}
type Builder interface {
	Build(a BuildArgs) error
}

type InfoArgs struct {
	StageFilePath string
	StageData     []byte
	Boundaries    psx.Offsets
}
type InfoAssetEntry struct {
	DataRange datarange.DataRange
	Kind      string
	Name      string
	Args      string // trailing YAML args, e.g. "128, 128, 4" or "16"
	Comment   string
}
type InfoSplatEntry struct {
	DataRange datarange.DataRange
	Kind      string
	Name      string
	Comment   string
}

// InfoGraphic is a graphic as described by a gfx bank entry, before its
// boundaries are resolved.
type InfoGraphic struct {
	Addr   psx.Addr
	Kind   uint32 // 1/2/3 raw at 4/8/16bpp, 4 compressed
	Width  int
	Height int
}

// InfoPalette is a palette as described by a palette def. ClutID is -1 when
// the def carries only pointers and no destination to derive it from.
type InfoPalette struct {
	Addr   psx.Addr
	Length int
	ClutID int
}

type InfoResult struct {
	AssetEntries []InfoAssetEntry
	SplatEntries []InfoSplatEntry
	Graphics     []InfoGraphic
	Palettes     []InfoPalette
}
type InfoGatherer interface {
	Info(a InfoArgs) (InfoResult, error)
}

type Handler interface {
	Name() string
	Extractor
	Builder
	InfoGatherer
}
