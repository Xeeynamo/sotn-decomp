package sotn

import (
	"fmt"
	"strings"
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
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
		"FLAG_1 | FLAG_2 // ignore\n" +
		"NUM_SOMETHING // ignore\n" +
		"} // malformed, it misses a semicolon\n"
	m, err := ParseCEnum(strings.NewReader(src), "MyEnum", 0x100)
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

func TestFetchEnumCachesFailures(t *testing.T) {
	// Missing headers are cached to avoid re-spawning cpp on every lookup
	// that ignores errors (eg. readEntityLayoutEntry)
	_, err := FetchEnum("src/st/does-not-exist", "does-not-exist", "EntityID")
	require.Error(t, err)

	lock.RLock()
	defer lock.RUnlock()
	cacheKey := fmt.Sprintf("%s:src/st/does-not-exist/does-not-exist.h:EntityID", GetVersion())
	cached, ok := enumCache[cacheKey]
	require.True(t, ok, "failed lookup was not cached")
	assert.Error(t, cached.err)
}
