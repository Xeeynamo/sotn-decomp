package main

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"
	"testing"
	"unicode/utf8"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
)

func TestCheck(t *testing.T) {
	changeDirToRepoRoot()
	makeTmpVer := func(version string, lines []string) func() {
		t.Helper()
		fileName := filepath.Join("config", fmt.Sprintf("check.%s.sha", version))
		if _, err := os.Stat(fileName); err == nil {
			t.Fatalf("%q must not exists", fileName)
		}
		require.NoError(t, os.WriteFile(fileName, []byte(strings.Join(lines, "\n")), 0644))
		return func() {
			t.Helper()
			require.NoError(t, os.Remove(fileName))
		}
	}
	t.Run("All versions matching", func(t *testing.T) {
		sha1sumCheck = func(_ string, _ string) bool {
			return true
		}
		t.Run("one only", func(t *testing.T) {
			out := strings.Builder{}
			require.NoError(t, checkVersions(&out, []string{"us"}))
			assert.Equal(t, "✅ us\n", out.String())
		})
		t.Run("stack horizontally", func(t *testing.T) {
			out := strings.Builder{}
			require.NoError(t, checkVersions(&out, []string{"us", "hd"}))
			assert.Equal(t, "✅ us  ✅ hd\n", out.String())
		})
		t.Run("stack horizontally and equally distanced", func(t *testing.T) {
			cleanup := makeTmpVer("loooong", []string{})
			defer cleanup()
			out := strings.Builder{}
			require.NoError(t, checkVersions(&out, []string{"us", "hd", "loooong"}))
			assert.Equal(t, "✅ us       ✅ hd       ✅ loooong\n", out.String())
		})
	})
	t.Run("when multiple version has non-matching entries", func(t *testing.T) {
		sha1sumCheck = func(str string, sum string) bool {
			if sum == "fail" {
				return false
			}
			return true
		}
		cleanup := makeTmpVer("test2-1", []string{
			"ok ovl1", "fail ovl2",
		})
		cleanup2 := makeTmpVer("test2-2", []string{
			"fail ovl1", "ok ovl2",
		})
		defer cleanup()
		defer cleanup2()
		out := strings.Builder{}
		require.NoError(t, checkVersions(&out, []string{"test2-1", "test2-2"}))
		assert.Equal(t,
			"⚠️ test2-1\n"+
				"  ✅ ovl1  ❌ ovl2  \n"+
				"⚠️ test2-2\n"+
				"  ❌ ovl1  ✅ ovl2  \n", out.String())
	})
	t.Run("when one version has non-matching entries", func(t *testing.T) {
		sha1sumCheck = func(str string, sum string) bool {
			if sum == "fail" {
				return false
			}
			return true
		}
		cleanup := makeTmpVer("test1", []string{
			"ok ovl1", "ok ovl2", "fail ovl", "ok foo",
		})
		defer cleanup()
		out := strings.Builder{}
		require.NoError(t, checkVersions(&out, []string{"us", "test1", "hd"}))
		assert.Equal(t,
			"✅ us     ✅ hd\n"+
				"⚠️ test1\n"+
				"  ✅ ovl1  ✅ ovl2  ❌ ovl   ✅ foo   \n", out.String())
	})
	t.Run("stack version entries in a grid of max 60 characters wide", func(t *testing.T) {
		sha1sumCheck = func(str string, sum string) bool {
			if sum == "fail" {
				return false
			}
			return true
		}
		cleanup := makeTmpVer("test3", []string{
			"ok zero", "fail one", "ok two", "fail three", "ok four",
			"fail five", "ok six", "fail seven", "ok eight", "fail nine",
			"ok ten", "fail eleven", "ok twelve",
		})
		defer cleanup()
		out := strings.Builder{}
		require.NoError(t, checkVersions(&out, []string{"test3"}))
		for _, line := range strings.Split(out.String(), "\n") {
			assert.True(t, utf8.RuneCountInString(line) <= 60, "line less than 60 characters")
		}
		assert.Equal(t, "⚠️ test3\n"+
			"  ✅ zero    ❌ one     ✅ two     ❌ three   ✅ four    ❌ five\n"+
			"  ✅ six     ❌ seven   ✅ eight   ❌ nine    ✅ ten     ❌ eleven\n"+
			"  ✅ twelve  \n", out.String())
	})
}
