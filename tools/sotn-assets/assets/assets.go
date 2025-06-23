package assets

import (
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
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
}
type InfoSplatEntry struct {
	DataRange datarange.DataRange
	Kind      string
	Name      string
	Comment   string
}
type InfoResult struct {
	AssetEntries []InfoAssetEntry
	SplatEntries []InfoSplatEntry
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
