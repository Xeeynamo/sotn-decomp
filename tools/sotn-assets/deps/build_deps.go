package deps

import (
	"fmt"
	"os"
	"os/exec"
	"path/filepath"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"golang.org/x/sync/errgroup"
)

const cc1Psx26Release = "cc1-psx-26"

func EnsureBuildDeps(versions []string) error {
	deps := make(map[sotn.Platform]struct{})
	var eg errgroup.Group
	for _, version := range versions {
		p := sotn.Version(version).GetPlatform()
		if _, ok := deps[p]; ok {
			continue
		}
		switch p {
		case sotn.PlatformPSX:
			ensurePSXDeps(&eg)
		case sotn.PlatformPSP:
			ensurePSPDeps(&eg)
		default:
			return fmt.Errorf("unsupported platform version: %s", version)
		}
		deps[p] = struct{}{}
	}
	eg.Go(ensurePythonDeps)
	eg.Go(ensureSotnAssets)
	if err := eg.Wait(); err != nil {
		return fmt.Errorf("ensure build deps: %w", err)
	}
	return nil
}

func ensurePSXDeps(eg *errgroup.Group) {
	eg.Go(func() error {
		return GitSubmoduleInitAndUpdate("tools/maspsx", true)
	})
	eg.Go(func() error {
		return downloadTarGzFromGithubIfNotExists(
			"Xeeynamo/sotn-decomp", cc1Psx26Release,
			"cc1-psx-26", "bin/cc1-psx-26",
		)
	})
}

func ensurePSPDeps(eg *errgroup.Group) {
	eg.Go(func() error {
		return GitSubmoduleInitAndUpdate("tools/mwccgap", true)
	})
	eg.Go(func() error {
		return downloadTarGzFromGithubIfNotExists(
			"Xeeynamo/sotn-decomp", cc1Psx26Release,
			"allegrex-as", "bin/allegrex-as",
		)
	})
	eg.Go(func() error {
		return CargoBuild("tools/pspas/Cargo.toml", "bin/pspas")
	})
	eg.Go(func() error {
		return CargoBuild("tools/sotn_str/Cargo.toml", "")
	})
	eg.Go(func() error {
		return downloadFromGithubIfNotExists("decompals/wibo", "0.6.13", "wibo", "bin/wibo")
	})
	eg.Go(func() error {
		return downloadAndExtractAllTarGzFromGithub(
			"Xeeynamo/sotn-decomp", cc1Psx26Release,
			"mwccpsp_219", "bin",
		)
	})
}

func ensureSotnAssets() error {
	// must "build" itself due to how gen.py works
	if _, err := os.Stat("bin/sotn-assets"); err == nil {
		return nil
	}
	self, err := os.Executable()
	if err != nil {
		return fmt.Errorf("resolve own executable: %w", err)
	}
	if err := os.MkdirAll("bin", 0755); err != nil {
		return err
	}
	src, err := os.ReadFile(self)
	if err != nil {
		return fmt.Errorf("read own executable: %w", err)
	}
	return os.WriteFile("bin/sotn-assets", src, 0755)
}

func ensurePythonDeps() error {
	binPath, err := venvPython()
	if err != nil {
		return err
	}
	pipPath := filepath.Join(filepath.Dir(binPath), "pip3")
	// Check if splat is already installed as a proxy for all deps
	splatPath := filepath.Join(filepath.Dir(binPath), "splat")
	if _, err := os.Stat(splatPath); err == nil {
		return nil
	}
	cmd := exec.Command(pipPath, "install", "-r", "tools/requirements-python.txt")
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	return cmd.Run()
}
