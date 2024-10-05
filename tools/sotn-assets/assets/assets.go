package assets

import "github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"

type ExtractEntry struct {
	Data     []byte
	Start    int
	End      int
	AssetDir string
	SrcDir   string
	Name     string
	Args     []string
	RamBase  psx.Addr
}

type BuildEntry struct {
	AssetDir string
	SrcDir   string
	Name     string
}

type Extracter interface {
	Extract(e ExtractEntry) error
}

type Builder interface {
	Build(e BuildEntry) error
}

type Handler interface {
	Name() string
	Extracter
	Builder
}
