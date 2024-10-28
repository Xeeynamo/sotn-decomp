package skip

import "github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "skip" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	return nil
}

func (h *handler) Build(e assets.BuildArgs) error {
	return nil
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	return assets.InfoResult{}, nil
}
