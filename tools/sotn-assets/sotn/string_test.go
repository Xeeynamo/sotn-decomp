package sotn

import (
	"testing"

	"github.com/stretchr/testify/require"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
)

func TestDecodeString(t *testing.T) {
	const base = psx.Addr(0x800A0000)
	tests := []struct {
		name     string
		platform Platform
		data     []byte
		want     string
	}{
		{
			name:     "empty",
			platform: PlatformPSX,
			data:     []byte{0xFF, 0},
			want:     "",
		},
		{
			name:     "synthetic PSX text",
			platform: PlatformPSX,
			data:     []byte{0x34, 0x45, 0x53, 0x54, 0xFF, 0},
			want:     "Test",
		},
		{
			name:     "PSP accented text",
			platform: PlatformPSP,
			data:     []byte{0x21, 0xA0, 0xFF, 0},
			want:     "Aé",
		},
		{
			name:     "dakuten",
			platform: PlatformPSX,
			data:     []byte{0x76, 0xFF, 0x9E, 0xFF, 0},
			want:     "ガ",
		},
		{
			name:     "handakuten",
			platform: PlatformPSX,
			data:     []byte{0x8A, 0xFF, 0x9F, 0xFF, 0},
			want:     "パ",
		},
		{
			name:     "special moon",
			platform: PlatformPSX,
			data:     []byte{0xFF, 0xFF, 0xFF, 0},
			want:     "月",
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			got, err := DecodeString(tt.data, base, base, tt.platform)
			require.NoError(t, err)
			require.Equal(t, tt.want, got)
		})
	}
}

func TestDecodeStringRejectsInvalidInput(t *testing.T) {
	const base = psx.Addr(0x800A0000)
	_, err := DecodeString(
		[]byte{0xFF, 0}, base-1, base, PlatformPSX)
	require.ErrorContains(t, err, "precedes RAM base")

	_, err = DecodeString(
		[]byte{0xFF, 0}, base+2, base, PlatformPSX)
	require.ErrorContains(t, err, "resolves outside")

	_, err = DecodeString(
		[]byte{0x21, 0xFF}, base, base, PlatformPSX)
	require.ErrorContains(t, err, "unterminated")

	_, err = DecodeString(
		[]byte{0xFF, 0x01}, base, base, PlatformPSX)
	require.ErrorContains(t, err, "unknown string escape")

	_, err = DecodeString(
		[]byte{0xFF, 0}, base, base, PlatformSaturn)
	require.ErrorContains(t, err, "unsupported string platform")
}

func TestEncodeString(t *testing.T) {
	tests := []struct {
		name     string
		value    string
		platform Platform
		want     []byte
	}{
		{
			name:     "synthetic PSX text",
			value:    "Test",
			platform: PlatformPSX,
			want:     []byte{0x34, 0x45, 0x53, 0x54, 0xFF},
		},
		{
			name:     "PSP accented text",
			value:    "Aé",
			platform: PlatformPSP,
			want:     []byte{0x21, 0xA0, 0xFF},
		},
		{
			name:     "voice marks and moon",
			value:    "ガパ月",
			platform: PlatformPSX,
			want: []byte{
				0x76, 0xFF, 0x9E,
				0x8A, 0xFF, 0x9F,
				0xFF, 0xFF,
				0xFF,
			},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			got, err := EncodeString(tt.value, tt.platform)
			require.NoError(t, err)
			require.Equal(t, tt.want, got)
		})
	}
}

func TestEncodeStringRejectsUnsupportedCharacters(t *testing.T) {
	_, err := EncodeString("€", PlatformPSP)
	require.ErrorContains(t, err, "not available")
}

func TestMenuDescriptionCodec(t *testing.T) {
	const base = psx.Addr(0x800A0000)
	tests := []struct {
		name     string
		platform Platform
		value    string
		raw      []byte
	}{
		{
			name:     "PSX punctuation and quotes",
			platform: PlatformPSX,
			value:    `STR＋１０ "test"`,
			raw: []byte{
				0x53, 0x54, 0x52, 0x81, 0x7B, 0x82, 0x50, 0x82, 0x4F,
				0x20, 0x22, 0x74, 0x65, 0x73, 0x74, 0x22,
			},
		},
		{
			name:     "PSP European substitutions",
			platform: PlatformPSP,
			value:    "Cadáveres œufs",
			raw: []byte{
				0x43, 0x61, 0x64, 0xCC, 0x76, 0x65, 0x72, 0x65, 0x73,
				0x20, 0xAA, 0x75, 0x66, 0x73,
			},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			encoded, err := EncodeMenuDescription(tt.value, tt.platform)
			require.NoError(t, err)
			require.Equal(t, tt.raw, encoded)

			data := append(append([]byte{}, tt.raw...), 0)
			decoded, err := DecodeMenuDescription(
				data, base, base, tt.platform)
			require.NoError(t, err)
			require.Equal(t, tt.value, decoded)
		})
	}
}

func TestMenuDescriptionCodecRejectsInvalidInput(t *testing.T) {
	const base = psx.Addr(0x800A0000)

	_, err := DecodeMenuDescription(
		[]byte{0}, base-1, base, PlatformPSX)
	require.ErrorContains(t, err, "precedes RAM base")

	_, err = DecodeMenuDescription(
		[]byte{0x81}, base, base, PlatformPSX)
	require.ErrorContains(t, err, "unterminated")

	_, err = EncodeMenuDescription("€", PlatformPSX)
	require.ErrorContains(t, err, "encode Shift-JIS")

	_, err = EncodeMenuDescription("test", PlatformSaturn)
	require.ErrorContains(t, err, "unsupported")
}
