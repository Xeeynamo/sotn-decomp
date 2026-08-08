package sotn

import (
	"os"
	"path/filepath"
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
)

// repoRoot walks up from the test's working directory until it finds the
// marker file that only exists at the top of the repo.
func repoRoot(t *testing.T) string {
	t.Helper()
	dir, err := os.Getwd()
	require.NoError(t, err)
	for {
		if _, err := os.Stat(filepath.Join(dir, "disks/us/DRA.BIN")); err == nil {
			return dir
		}
		parent := filepath.Dir(dir)
		require.NotEqual(t, dir, parent, "unable to find repo root")
		dir = parent
	}
}

func TestInflateSize(t *testing.T) {
	data, err := os.ReadFile(filepath.Join(repoRoot(t), "disks/us/ST/LIB/LIB.BIN"))
	require.NoError(t, err)

	// verified against the hand-tuned boundaries in config/assets.us.yaml
	for _, tc := range []struct {
		offset       int
		compressed   int
		decompressed int
	}{
		{0x4FC8, 715, 8192},
		{0x5294, 1263, 8192},
		{0x5784, 3689, 8192},
		{0x15388, 901, 8192},
	} {
		compressed, decompressed, ok := InflateSize(data[tc.offset:])
		assert.True(t, ok, "offset 0x%X should inflate", tc.offset)
		assert.Equal(t, tc.compressed, compressed, "compressed size at 0x%X", tc.offset)
		assert.Equal(t, tc.decompressed, decompressed, "decompressed size at 0x%X", tc.offset)
	}
}

func TestInflateSizeAgreesWithInflate(t *testing.T) {
	data, err := os.ReadFile(filepath.Join(repoRoot(t), "disks/us/ST/LIB/LIB.BIN"))
	require.NoError(t, err)
	compressed, decompressed, ok := InflateSize(data[0x4FC8:])
	require.True(t, ok)
	// the two functions must agree on the decompressed length
	assert.Len(t, Inflate(data[0x4FC8:0x4FC8+compressed]), decompressed)
}

func TestInflateSizeTruncated(t *testing.T) {
	data, err := os.ReadFile(filepath.Join(repoRoot(t), "disks/us/ST/LIB/LIB.BIN"))
	require.NoError(t, err)
	// cut the stream in half: it can never reach the terminator opcode
	_, _, ok := InflateSize(data[0x4FC8 : 0x4FC8+300])
	assert.False(t, ok, "a truncated stream must not report success")
}

func TestInflateSizeEmpty(t *testing.T) {
	_, _, ok := InflateSize(nil)
	assert.False(t, ok)
	_, _, ok = InflateSize([]byte{0x00, 0x01, 0x02})
	assert.False(t, ok, "a stream shorter than the 8-byte dictionary must fail")
}
