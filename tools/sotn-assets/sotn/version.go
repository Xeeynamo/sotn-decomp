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

	VersionUS    = Version("us")
	VersionHD    = Version("hd")
	VersionPSPEU = Version("pspeu")
)

var (
	VersionsAll = []Version{VersionUS, VersionHD, VersionPSPEU}
)

func GetVersion() Version {
	version := os.Getenv("VERSION")
	if version == "" {
		return "us"
	}
	return Version(version)
}

func GetPlatform() Platform {
	version := GetVersion()
	if version == "saturn" {
		return PlatformSaturn
	}
	if strings.HasPrefix(string(version), "psp") {
		return PlatformPSP
	}
	return PlatformPSX
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
