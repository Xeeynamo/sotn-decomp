package layer

import (
	"encoding/binary"
	"encoding/json"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"golang.org/x/sync/errgroup"
	"io"
	"os"
	"path"
	"slices"
	"strings"
)

type Layer struct {
	Data       psx.Addr
	Tiledef    psx.Addr
	PackedInfo uint32
	ZPriority  uint16
	UnkE       uint8
	UnkF       uint8
}

type LayerUnpacked struct {
	Data          string `json:"data"`
	Tiledef       string `json:"tiledef"`
	Left          int    `json:"left"`
	Top           int    `json:"top"`
	Right         int    `json:"right"`
	Bottom        int    `json:"bottom"`
	ScrollMode    int    `json:"scrollMode"`
	IsSaveRoom    bool   `json:"isSaveRoom"`
	IsLoadingRoom bool   `json:"isLoadingRoom"`
	UnusedFlag    bool   `json:"unusedFlag"`
	ZPriority     int    `json:"zPriority"`
	UnkE          int    `json:"unkE"`
	UnkF          int    `json:"unkF"`
}

type RoomLayers struct {
	fg *Layer
	bg *Layer
}

func (l *Layer) TilemapFileSize() int {
	sx := int((l.PackedInfo >> 0) & 0x3F)
	sy := int((l.PackedInfo >> 6) & 0x3F)
	ex := int((l.PackedInfo >> 12) & 0x3F)
	ey := int((l.PackedInfo >> 18) & 0x3F)
	w := ex - sx + 1
	h := ey - sy + 1
	return w * h * 512
}

func (l *Layer) Unpack() LayerUnpacked {
	return LayerUnpacked{
		Data:          GetTilemapFileName(l.Data),
		Tiledef:       GetTiledefFileName(l.Tiledef),
		Left:          int((l.PackedInfo >> 0) & 0x3F),
		Top:           int((l.PackedInfo >> 6) & 0x3F),
		Right:         int((l.PackedInfo >> 12) & 0x3F),
		Bottom:        int((l.PackedInfo >> 18) & 0x3F),
		ScrollMode:    int((l.PackedInfo >> 24) & 0x1F),
		IsSaveRoom:    int((l.PackedInfo>>24)&0x20) != 0,
		IsLoadingRoom: int((l.PackedInfo>>24)&0x40) != 0,
		UnusedFlag:    int((l.PackedInfo>>24)&0x80) != 0,
		ZPriority:     int(l.ZPriority),
		UnkE:          int(l.UnkE),
		UnkF:          int(l.UnkF),
	}
}

func (r RoomLayers) MarshalJSON() ([]byte, error) {
	m := map[string]interface{}{}
	if r.fg != nil {
		m["fg"] = r.fg.Unpack()
	}
	if r.bg != nil {
		m["bg"] = r.bg.Unpack()
	}
	return json.Marshal(m)
}

func ReadLayers(file *os.File, off psx.Addr) ([]RoomLayers, datarange.DataRange, error) {
	if off == 0 {
		return nil, datarange.DataRange{}, nil
	}
	if err := off.MoveFile(file, psx.RamStageBegin); err != nil {
		return nil, datarange.DataRange{}, err
	}

	// when the data starts to no longer makes sense, we can assume we reached the end of the array
	layerOffsets := []psx.Addr{}
	layersOff := make([]psx.Addr, 2)
	for {
		if err := binary.Read(file, binary.LittleEndian, layersOff); err != nil {
			return nil, datarange.DataRange{}, err
		}
		if layersOff[0] <= psx.RamStageBegin || layersOff[0] >= off ||
			layersOff[1] <= psx.RamStageBegin || layersOff[1] >= off {
			break
		}
		layerOffsets = append(layerOffsets, layersOff...)
	}

	// Creates a map of layers, so we can re-use them when a layer is used by multiple rooms
	pool := map[psx.Addr]*Layer{}
	pool[psx.Addr(0)] = nil
	for _, layerOffset := range layerOffsets {
		if _, exists := pool[layerOffset]; exists {
			continue
		}

		if err := layerOffset.MoveFile(file, psx.RamStageBegin); err != nil {
			return nil, datarange.DataRange{}, err
		}
		var l Layer
		if err := binary.Read(file, binary.LittleEndian, &l); err != nil {
			return nil, datarange.DataRange{}, err
		}
		if l.Data != psx.RamNull || l.Tiledef != psx.RamNull || l.PackedInfo != 0 {
			pool[layerOffset] = &l
		} else {
			pool[layerOffset] = nil
		}
	}

	// creates the real array with all the layers mapped
	count := len(layerOffsets) >> 1
	roomsLayers := make([]RoomLayers, count)
	for i := 0; i < count; i++ {
		roomsLayers[i].fg = pool[layerOffsets[i*2+0]]
		roomsLayers[i].bg = pool[layerOffsets[i*2+1]]
	}
	return roomsLayers, datarange.New(slices.Min(layerOffsets), off.Sum(count*8)), nil
}

func BuildLayers(inputDir string, fileName string, outputDir string) error {
	getHash := func(l LayerUnpacked) string {
		return fmt.Sprintf("%s-%s-%d-%d-%d-%d", l.Data, l.Tiledef, l.Left, l.Top, l.Right, l.Bottom)
	}
	pack := func(l LayerUnpacked) map[string]interface{} {
		return map[string]interface{}{
			"data":    makeSymbolFromFileName(l.Data),
			"tiledef": makeSymbolFromFileName(l.Tiledef),
			"params": l.Left | (l.Top << 6) | (l.Right << 12) | (l.Bottom << 18) | (l.ScrollMode << 24) |
				(util.Btoi(l.IsSaveRoom) << 29) | (util.Btoi(l.IsLoadingRoom) << 30) | (util.Btoi(l.UnusedFlag) << 31),
			"zPriority": l.ZPriority,
			"unkE":      l.UnkE,
			"unkF":      l.UnkF,
		}
	}

	data, err := os.ReadFile(fileName)
	if err != nil {
		return err
	}

	var roomsLayers []map[string]*LayerUnpacked
	if err := json.Unmarshal(data, &roomsLayers); err != nil {
		return err
	}

	tilemaps := map[string]struct{}{}
	tiledefs := map[string]struct{}{}
	for _, room := range roomsLayers {
		// the split on '.' is to remove the extension
		if layer, found := room["fg"]; found {
			tilemaps[layer.Data] = struct{}{}
			tiledefs[layer.Tiledef] = struct{}{}
		}
		if layer, found := room["bg"]; found {
			tilemaps[layer.Data] = struct{}{}
			tiledefs[layer.Tiledef] = struct{}{}
		}
	}

	// use unused tiledefs
	files, err := os.ReadDir(inputDir)
	if err != nil {
		return err
	}
	for _, file := range files {
		if !file.IsDir() && strings.HasPrefix(file.Name(), "tiledef_") && strings.HasSuffix(file.Name(), ".json") {
			tiledefs[file.Name()] = struct{}{}
		}
	}

	eg := errgroup.Group{}
	for name := range tilemaps {
		fullPath := path.Join(path.Dir(fileName), name)
		symbol := makeSymbolFromFileName(name)
		eg.Go(func() error {
			return buildGenericU16(fullPath, symbol, outputDir)
		})
	}
	for name := range tiledefs {
		fullPath := path.Join(path.Dir(fileName), name)
		symbol := makeSymbolFromFileName(name)
		eg.Go(func() error {
			return buildTiledefs(fullPath, symbol, outputDir)
		})
	}
	if err := eg.Wait(); err != nil {
		return err
	}

	layers := []map[string]interface{}{} // first layer is always empty
	layers = append(layers, map[string]interface{}{})
	roomLayersId := make([]int, len(roomsLayers)*2)
	pool := map[string]int{}
	pool[""] = 0
	for _, rl := range roomsLayers {
		if l, fgFound := rl["fg"]; fgFound {
			hash := getHash(*l)
			if index, found := pool[hash]; !found {
				pool[hash] = len(layers)
				roomLayersId = append(roomLayersId, len(layers))
				layers = append(layers, pack(*l))
			} else {
				roomLayersId = append(roomLayersId, index)
			}
		} else {
			roomLayersId = append(roomLayersId, 0)
		}
		if l, bgFound := rl["bg"]; bgFound {
			hash := getHash(*l)
			if index, found := pool[hash]; !found {
				pool[hash] = len(layers)
				roomLayersId = append(roomLayersId, len(layers))
				layers = append(layers, pack(*l))
			} else {
				roomLayersId = append(roomLayersId, index)
			}
		} else {
			roomLayersId = append(roomLayersId, 0)
		}
	}

	sb := strings.Builder{}
	sb.WriteString("// clang-format off\n")
	for name := range tilemaps {
		symbol := makeSymbolFromFileName(name)
		sb.WriteString(fmt.Sprintf("extern u16 %s[];\n", symbol))
	}
	for name := range tiledefs {
		symbol := makeSymbolFromFileName(name)
		sb.WriteString(fmt.Sprintf("extern TileDefinition %s[];\n", symbol))
	}

	sb.WriteString("static MyLayer layers[] = {\n")
	sb.WriteString("    { NULL, NULL, 0, 0, 0, 0 },\n")
	for _, l := range layers[1:] {
		sb.WriteString(fmt.Sprintf("    { %s, %s, 0x%08X, 0x%02X, %d, %d },\n",
			makeSymbolFromFileName(l["data"].(string)),
			makeSymbolFromFileName(l["tiledef"].(string)),
			l["params"],
			l["zPriority"],
			l["unkE"],
			l["unkF"],
		))
	}
	sb.WriteString("};\n")

	sb.WriteString("MyRoomDef OVL_EXPORT(rooms_layers)[] = {\n")
	for _, rl := range roomsLayers {
		if l, found := rl["fg"]; found {
			sb.WriteString(fmt.Sprintf("    { &layers[%d], ", pool[getHash(*l)]))
		} else {
			sb.WriteString(fmt.Sprintf("    { &layers[0], "))
		}
		if l, found := rl["bg"]; found {
			sb.WriteString(fmt.Sprintf("&layers[%d] },\n", pool[getHash(*l)]))
		} else {
			sb.WriteString(fmt.Sprintf("&layers[0] },\n"))
		}
	}
	sb.WriteString("};\n")
	return os.WriteFile(path.Join(outputDir, "layers.h"), []byte(sb.String()), 0644)
}

func makeSymbolFromFileName(fileName string) string {
	return strings.Split(path.Base(fileName), ".")[0]
}

func writeStaticU8(w io.Writer, fileName string, symbol string) error {
	data, err := os.ReadFile(fileName)
	if err != nil {
		return err
	}

	var sb strings.Builder
	sb.WriteString("// clang-format off\n")
	sb.WriteString(fmt.Sprintf("static unsigned char %s[] = {\n", symbol))
	for i := 0; i < len(data); i++ {
		sb.WriteString(fmt.Sprintf("0x%02X,", data[i]))
		if (i & 15) == 15 {
			sb.WriteString("\n")
		}
	}
	sb.WriteString("};\n")

	_, err = w.Write([]byte(sb.String()))
	return err
}

func buildGenericU16(fileName string, symbol string, outputDir string) error {
	data, err := os.ReadFile(fileName)
	if err != nil {
		return err
	}

	var sb strings.Builder
	sb.WriteString("// clang-format off\n")
	sb.WriteString(fmt.Sprintf("u16 %s[] = {\n", symbol))
	for i := 0; i < len(data); i += 2 {
		sb.WriteString(fmt.Sprintf("0x%02X%02X,", data[i+1], data[i]))
		if (i & 31) == 30 {
			sb.WriteString("\n")
		}
	}
	sb.WriteString("};\n")

	return os.WriteFile(path.Join(outputDir, fmt.Sprintf("%s.h", symbol)), []byte(sb.String()), 0644)
}

func buildTiledefs(fileName string, symbol string, outputDir string) error {
	data, err := os.ReadFile(fileName)
	if err != nil {
		return err
	}

	var tiledef TileDefPaths
	if err := json.Unmarshal(data, &tiledef); err != nil {
		return err
	}

	f, err := os.Create(path.Join(outputDir, fmt.Sprintf("%s.h", symbol)))
	if err != nil {
		return err
	}
	defer f.Close()

	tilesSymbol := makeSymbolFromFileName(tiledef.Tiles)
	tilesFileName := path.Join(path.Dir(fileName), tiledef.Tiles)
	if err := writeStaticU8(f, tilesFileName, tilesSymbol); err != nil {
		return err
	}

	pagesSymbol := makeSymbolFromFileName(tiledef.Pages)
	pagesFileName := path.Join(path.Dir(fileName), tiledef.Pages)
	if err := writeStaticU8(f, pagesFileName, pagesSymbol); err != nil {
		return err
	}

	clutsSymbol := makeSymbolFromFileName(tiledef.Cluts)
	clutsFileName := path.Join(path.Dir(fileName), tiledef.Cluts)
	if err := writeStaticU8(f, clutsFileName, clutsSymbol); err != nil {
		return err
	}

	colsSymbol := makeSymbolFromFileName(tiledef.Collisions)
	colsFileName := path.Join(path.Dir(fileName), tiledef.Collisions)
	if err := writeStaticU8(f, colsFileName, colsSymbol); err != nil {
		return err
	}

	_, _ = f.WriteString("// clang-format off\n")
	_, _ = f.WriteString(fmt.Sprintf("TileDefinition %s[] = {\n", symbol))
	_, _ = f.WriteString(fmt.Sprintf("    %s,\n", tilesSymbol))
	_, _ = f.WriteString(fmt.Sprintf("    %s,\n", pagesSymbol))
	_, _ = f.WriteString(fmt.Sprintf("    %s,\n", clutsSymbol))
	_, _ = f.WriteString(fmt.Sprintf("    %s,\n", colsSymbol))
	_, _ = f.WriteString("};\n")

	return nil
}
