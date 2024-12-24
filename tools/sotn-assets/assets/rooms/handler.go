package rooms

import (
	"bytes"
	"encoding/binary"
	"encoding/json"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"io"
	"os"
	"path"
	"strings"
)

type Room struct {
	Left           int8 `json:"left"`
	Top            int8 `json:"top"`
	Right          int8 `json:"right"`
	Bottom         int8 `json:"bottom"`
	LayerID        int8 `json:"layerId"`
	TileDefID      int8 `json:"tileDefId"`
	EntityGfxID    int8 `json:"entityGfxId"`
	EntityLayoutID int8 `json:"entityLayoutId"`
}

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "rooms" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	r := bytes.NewReader(e.Data)
	rooms, _, err := readRooms(r, e.RamBase.Sum(e.Start))
	if err != nil {
		return fmt.Errorf("failed to read rooms: %w", err)
	}
	return util.WriteJsonFile(assetPath(e.AssetDir, e.Name), rooms)
}

func (h *handler) Build(e assets.BuildArgs) error {
	inPath := assetPath(e.AssetDir, e.Name)
	outPath := sourcePath(e.SrcDir, e.Name)
	ovlName := path.Base(path.Dir(outPath))
	data, err := os.ReadFile(inPath)
	if err != nil {
		return err
	}

	var rooms []Room
	if err := json.Unmarshal(data, &rooms); err != nil {
		return err
	}

	content := strings.Builder{}
	content.WriteString("// clang-format off\n")
	content.WriteString(fmt.Sprintf("unsigned char %s_rooms[] = {\n", strings.ToUpper(ovlName)))
	for _, room := range rooms {
		s := fmt.Sprintf("    %d, %d, %d, %d, %d, %d, %d, %d,\n",
			room.Left, room.Top, room.Right, room.Bottom,
			room.LayerID, room.TileDefID, room.EntityGfxID, room.EntityLayoutID)
		content.WriteString(s)
	}
	content.WriteString("    0x40\n};\n")
	return os.WriteFile(outPath, []byte(content.String()), 0644)
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	r := bytes.NewReader(a.StageData)
	header, err := sotn.ReadStageHeader(r)
	if err != nil {
		return assets.InfoResult{}, err
	}
	_, dataRange, err := readRooms(r, header.Rooms)
	if err != nil {
		return assets.InfoResult{}, err
	}
	return assets.InfoResult{
		AssetEntries: []assets.InfoAssetEntry{
			{
				DataRange: dataRange,
				Kind:      "rooms",
				Name:      "rooms",
			},
		},
		SplatEntries: []assets.InfoSplatEntry{
			{
				DataRange: dataRange,
				Name:      "rooms",
			},
		},
	}, nil
}

func assetPath(dir, name string) string {
	return path.Join(dir, fmt.Sprintf("%s.json", name))
}

func sourcePath(dir, name string) string {
	return path.Join(dir, fmt.Sprintf("%s.c", name))
}

func (r Room) isTerminator() bool {
	return r.Left == 0x40
}

func readRooms(r io.ReadSeeker, off psx.Addr) ([]Room, datarange.DataRange, error) {
	if off == 0 {
		return nil, datarange.DataRange{}, nil
	}
	if err := off.MoveFile(r, psx.RamStageBegin); err != nil {
		return nil, datarange.DataRange{}, err
	}

	var rooms []Room
	for {
		var room Room
		if err := binary.Read(r, binary.LittleEndian, &room); err != nil {
			return nil, datarange.DataRange{}, err
		}
		if room.isTerminator() {
			break
		}
		rooms = append(rooms, room)
	}
	return rooms, datarange.FromAddr(off, len(rooms)*8+4), nil
}
