package png

import (
	"bytes"
	"image/color"
	"math/rand"
	"testing"

	"github.com/stretchr/testify/require"
)

func TestDecode(t *testing.T) {
	const w int = 128
	const h int = 128
	t.Run("for 1bpp image", func(t *testing.T) {
		r := rand.NewSource(1234)
		expected := make([]byte, w*h/8)
		for i, _ := range expected {
			expected[i] = byte(r.Int63())
		}
		var buf bytes.Buffer
		err := Encode(&buf, expected, w, h, make([]color.RGBA, 2))
		require.NoError(t, err)
		actual, _, err := Decode(&buf)
		require.NoError(t, err)
		require.ElementsMatch(t, expected, actual)
	})
	t.Run("for 4bpp image", func(t *testing.T) {
		r := rand.NewSource(1234)
		expected := make([]byte, w*h/2)
		for i, _ := range expected {
			expected[i] = byte(r.Int63())
		}
		var buf bytes.Buffer
		err := Encode(&buf, expected, w, h, make([]color.RGBA, 16))
		require.NoError(t, err)
		actual, _, err := Decode(&buf)
		require.NoError(t, err)
		require.ElementsMatch(t, expected, actual)
	})
	t.Run("for 8bpp image", func(t *testing.T) {
		r := rand.NewSource(5678)
		expected := make([]byte, w*h)
		for i, _ := range expected {
			expected[i] = byte(r.Int63())
		}
		var buf bytes.Buffer
		err := Encode(&buf, expected, w, h, make([]color.RGBA, 256))
		require.NoError(t, err)
		actual, _, err := Decode(&buf)
		require.NoError(t, err)
		require.ElementsMatch(t, expected, actual)
	})
}
