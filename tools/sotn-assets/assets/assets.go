package assets

import (
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
)

type ExtractArgs struct {
	Data     []byte
	Start    int
	End      int
	AssetDir string
	Name     string
	Args     []string
	RamBase  psx.Addr
}
type Extractor interface {
	Extract(a ExtractArgs) error
}

type BuildArgs struct {
	AssetDir string
	SrcDir   string
	Name     string
}
type Builder interface {
	Build(a BuildArgs) error
}

type InfoArgs struct {
	StageFilePath string
	StageData     []byte
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
