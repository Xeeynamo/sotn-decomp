package dependency

import (
	"fmt"
	"io"
	"net/http"
	"os"
	"path/filepath"
)

func DownloadIfNotExists(url string, filename string) error {
	if _, err := os.Stat(filename); os.IsNotExist(err) {
		return Download(url, filename)
	}
	return nil
}

func Download(url string, filename string) error {
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
