package deps

import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"net/http"
	"os"
	"os/exec"
	"path"
	"path/filepath"
	"sync"
)

func downloadTarGzFromGithubIfNotExists(repo, tag, name, destination string) error {
	tagPath := destination + ".tag"
	if tagData, err := os.ReadFile(tagPath); err == nil && string(tagData) == tag {
		return nil
	}
	_ = os.Remove(destination)
	url := fmt.Sprintf("https://github.com/%s/releases/download/%s/%s.tar.gz", repo, tag, name)
	tarGzPath := destination + ".tar.gz"
	if err := download(url, tarGzPath); err != nil {
		return fmt.Errorf("failed to download %s: %w", url, err)
	}
	defer os.Remove(tarGzPath)

	if err := extractTarGz(tarGzPath, name, destination); err != nil {
		return fmt.Errorf("failed to extract %s: %w", tarGzPath, err)
	}

	if err := os.Chmod(destination, 0755); err != nil {
		return fmt.Errorf("failed to chmod %s: %w", destination, err)
	}

	return os.WriteFile(tagPath, []byte(tag), 0o644)
}

func extractTarGz(tarGzPath, targetName, destination string) error {
	f, err := os.Open(tarGzPath)
	if err != nil {
		return err
	}
	defer f.Close()

	gr, err := gzip.NewReader(f)
	if err != nil {
		return err
	}
	defer gr.Close()

	tr := tar.NewReader(gr)
	for {
		header, err := tr.Next()
		if err == io.EOF {
			break
		}
		if err != nil {
			return err
		}

		// Extract the file matching targetName (could be at root or in a subdirectory)
		baseName := filepath.Base(header.Name)
		if baseName == targetName && header.Typeflag == tar.TypeReg {
			out, err := os.Create(destination)
			if err != nil {
				return err
			}
			if _, err := io.Copy(out, tr); err != nil {
				out.Close()
				return err
			}
			return out.Close()
		}
	}

	return fmt.Errorf("file %s not found in archive", targetName)
}

func downloadFromGithubIfNotExists(repo, tag, name, destination string) error {
	tagPath := destination + ".tag"
	if tagData, err := os.ReadFile(tagPath); err == nil && string(tagData) == tag {
		return nil
	}
	_ = os.Remove(destination)
	url := fmt.Sprintf("https://github.com/%s/releases/download/%s/%s", repo, tag, name)
	if err := downloadIfNotExists(url, destination); err != nil {
		return fmt.Errorf("failed to download at %s", url)
	}
	return os.WriteFile(tagPath, []byte(tag), 0o644)
}

func downloadIfNotExists(url string, filename string) error {
	if _, err := os.Stat(filename); os.IsNotExist(err) {
		return download(url, filename)
	}
	return nil
}

func download(url string, filename string) error {
	resp, err := http.Get(url)
	if err != nil {
		return err
	}
	defer resp.Body.Close()
	if resp.StatusCode != http.StatusOK {
		return fmt.Errorf("unexpected HTTP status %d for %s", resp.StatusCode, url)
	}
	out, err := os.Create(filename)
	if err != nil {
		return err
	}
	if _, err := io.Copy(out, resp.Body); err != nil {
		return err
	}
	if err := out.Close(); err != nil {
		return err
	}
	if filepath.Dir(filename) != "bin" {
		return nil
	}
	return os.Chmod(filename, 0755)
}

var muPip sync.Mutex

func pipPackagePath(name string) (string, error) {
	binPath, err := venvPython()
	if err != nil {
		return "", err
	}
	muPip.Lock()
	defer muPip.Unlock()
	pkgPath := filepath.Join(path.Dir(binPath), name)
	if _, err := os.Stat(pkgPath); os.IsNotExist(err) {
		cmd := &exec.Cmd{
			Path: binPath,
			Args: []string{binPath, "-m", "pip", "install", name},
		}
		if err := cmd.Run(); err != nil {
			return "", err
		}
	} else if err != nil {
		return "", err
	}
	return pkgPath, nil
}

var muVenv sync.Mutex

func venvPython() (string, error) {
	muVenv.Lock()
	defer muVenv.Unlock()
	const bin = ".venv/bin/python3"
	if _, err := os.Stat(bin); err != nil {
		if !os.IsNotExist(err) {
			return "", fmt.Errorf("fetch python venv: %w", err)
		}
		binPath, err := exec.LookPath("python3")
		if err != nil {
			return "", err
		}
		if err := (&exec.Cmd{
			Path:   binPath,
			Args:   []string{binPath, "-m", "venv", ".venv"},
			Stdin:  os.Stdin,
			Stdout: os.Stdout,
			Stderr: os.Stderr,
		}).Run(); err != nil {
			return "", fmt.Errorf("init python venv: %w", err)
		}
	}
	return bin, nil
}
