package deps

import (
	"fmt"
	"io"
	"net/http"
	"os"
	"path/filepath"
)

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
