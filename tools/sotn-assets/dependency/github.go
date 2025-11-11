package dependency

import (
	"fmt"
	"os"
)

func DownloadFromGithubIfNotExists(repo, tag, name, destination string) error {
	tagPath := destination + ".tag"
	if tagData, err := os.ReadFile(tagPath); err == nil && string(tagData) == tag {
		return nil
	}
	_ = os.Remove(destination)
	url := fmt.Sprintf("https://github.com/%s/releases/download/%s/%s", repo, tag, name)
	if err := DownloadIfNotExists(url, destination); err != nil {
		return fmt.Errorf("failed to download at %s", url)
	}
	return os.WriteFile(tagPath, []byte(tag), 0o644)
}
