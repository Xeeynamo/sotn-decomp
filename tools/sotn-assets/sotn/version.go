package sotn

import (
	"os"
	"strings"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
)

type Version string

type Platform string

const (
	PlatformSaturn = Platform("saturn")
	PlatformPSP    = Platform("psp")
	PlatformPSX    = Platform("psx")

	VersionUS     = Version("us")
	VersionHD     = Version("hd")
	VersionPSPEU  = Version("pspeu")
	VersionSaturn = Version("saturn")
)

var (
	// VersionsAll defaults when doing `build [all]`
	VersionsAll = []Version{VersionUS, VersionHD, VersionPSPEU}

	// VersionsEverything adds Saturn to the mix for more specific stuff we do
	// not want to propagate to the usual build chain
	VersionsEverything = append(VersionsAll, VersionSaturn)
)

func GetVersion() Version {
	version := os.Getenv("VERSION")
	if version == "" {
		return "us"
	}
	return Version(version)
}

func GetPlatform() Platform {
	return GetVersion().GetPlatform()
}

func (p Platform) GetBoundaries() psx.Offsets {
	switch p {
	case PlatformPSX:
		return psx.Addr(0x80000000).Boundaries()
	case PlatformPSP:
		return psx.Addr(0x08000000).Boundaries()
	default:
		panic("unsupported platform " + string(p))
	}
}

func (v Version) IsAll() bool {
	return len(v) == 0 || v == "all"
}

func (v Version) GetPlatform() Platform {
	if v == "saturn" {
		return PlatformSaturn
	}
	if strings.HasPrefix(string(v), "psp") {
		return PlatformPSP
	}
	return PlatformPSX
}
