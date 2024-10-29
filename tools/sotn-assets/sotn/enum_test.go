package sotn

import (
	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
	"strings"
	"testing"
)

func TestParseCEnum(t *testing.T) {
	src := "" +
		"typedef enum IgnoreMe{ ONE, TWO, THREE };\n" +
		"// typedef struct MyEnum { this is a comment\n" +
		"enum MyEnum { // this is also a comment\n" +
		"First,\n" +
		"Second,\n" +
		"SomeId = 10\n" +
		"SomeHexId = 0x10\n" +
		"/* 0x18nope */ E_MARIA = 0x18\n" +
		"E_COMMENT = 123 // ignore\n" +
		"E_COMMENT_2 /* ignore this as well */\n" +
		"} // malformed, it misses a semicolon\n"
	m, err := ParseCEnum(strings.NewReader(src), "MyEnum")
	require.NoError(t, err)
	assert.Equal(t, "First", m[0])
	assert.Equal(t, "Second", m[1])
	assert.Equal(t, "0x02", m[2])
	assert.Equal(t, "SomeId", m[10])
	assert.Equal(t, "SomeHexId", m[0x10])
	assert.Equal(t, "E_MARIA", m[0x18])
	assert.Equal(t, "E_COMMENT", m[123])
	assert.Equal(t, "E_COMMENT_2", m[124])
}
