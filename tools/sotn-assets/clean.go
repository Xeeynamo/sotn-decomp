package main

import (
	"fmt"
	"path/filepath"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/deps"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"golang.org/x/sync/errgroup"
)

func clean(version string, verbose bool) error {
	var versions []sotn.Version
	if version == "" || version == "all" {
		for _, v := range sotn.VersionsEverything {
			versions = append(versions, v)
		}
	} else {
		versions = append(versions, sotn.Version(version))
	}

	var eg errgroup.Group
	for _, version := range versions {
		for _, path := range []string{
			fmt.Sprintf("asm/%s/", version),
			fmt.Sprintf("build/%s/", version),
		} {
			path := path
			eg.Go(func() error {
				return deps.GitClean(path, verbose)
			})
		}
	}
	eg.Go(func() error {
		return deps.GitClean("config/saturn", verbose)
	})
	eg.Go(func() error {
		return deps.GitClean("assets/", verbose)
	})
	eg.Go(func() error {
		return deps.GitClean("function_calls/", verbose)
	})
	eg.Go(func() error {
		return deps.GitClean("sotn_calltree.txt", verbose)
	})
	eg.Go(func() error {
		matches, err := filepath.Glob("src/*/gen")
		if err != nil {
			return err
		}
		nested, err := filepath.Glob("src/*/*/gen")
		if err != nil {
			return err
		}
		matches = append(matches, nested...)
		for _, dir := range matches {
			if err := deps.GitClean(dir, verbose); err != nil {
				return fmt.Errorf("cleaning %s: %w", dir, err)
			}
		}
		return nil
	})
	return eg.Wait()
}
