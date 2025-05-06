package sotn

import (
	"os"
	"strings"
)

type Version string

type Platform string

const (
	PlatformSaturn = Platform("saturn")
	PlatformPSP    = Platform("psp")
	PlatformPSX    = Platform("psx")
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
