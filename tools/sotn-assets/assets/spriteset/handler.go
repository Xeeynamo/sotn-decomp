package spriteset

import (
	"bytes"
	"encoding/json"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"os"
	"path"
	"strings"
)

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "spriteset" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	var sprites []*spriteParts
	var err error
	if e.Start != e.End {
		r := bytes.NewReader(e.Data)
		sprites, _, err = ReadSpriteSet(r, e.RamBase, e.RamBase.Sum(e.Start))
		if err != nil {
			return fmt.Errorf("failed to read sprites: %w", err)
		}
	} else {
		sprites = make([]*spriteParts, 0)
	}
	return util.WriteJsonFile(assetPath(e.AssetDir, e.Name), sprites)
}

func (h *handler) Build(e assets.BuildArgs) error {
	in := assetPath(e.AssetDir, e.Name)
	out := sourcePath(e.SrcDir, e.Name)
	data, err := os.ReadFile(in)
	if err != nil {
		return fmt.Errorf("unable to open %q: %v", in, err)
	}

	var ss []*spriteParts
	if err := json.Unmarshal(data, &ss); err != nil {
		return fmt.Errorf("unable to parse %q: %v", in, err)
	}
	sb := strings.Builder{}
	sb.WriteString("// clang-format off\n")
	if len(ss) > 0 {
		BuildSpriteSet(&sb, ss, e.Name)
	}
	return os.WriteFile(out, []byte(sb.String()), 0644)
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	return assets.InfoResult{}, nil
}

func assetPath(dir, name string) string {
	return path.Join(dir, fmt.Sprintf("%s.animset.json", name))
}

func sourcePath(dir, name string) string {
	return path.Join(dir, fmt.Sprintf("%s.h", name))
}
