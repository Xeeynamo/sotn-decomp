package main

import (
	"bufio"
	"bytes"
	"io"
	"strings"
	"testing"

	"github.com/stretchr/testify/require"
)

func TestIgnorePatch(t *testing.T) {
	// Essentially test the patcher does not break on silly stuff
	for _, tcase := range []string{
		"foo\n",
		"\"a string\"\n",
		"\t.someStuff\n",
		"#comment\n",
		"\tlh\t$2,65535($4)\n",
		"\tlh\t$2,D_801809EC\n",
	} {
		t.Run(tcase, func(t *testing.T) {
			assertPatch(t, tcase, tcase)
		})
	}
}

func TestPatchLoadHalfWithPointer(t *testing.T) {
	assertPatch(t,
		"\tlh\t$2,D_801809EC($4)\n",

		"\tlui\t$1,%hi(D_801809EC)\n",
		"\taddu\t$1,$1,$4\n",
		"\tlh\t$2,%lo(D_801809EC)($1)\n",
	)
}

func assertPatch(t *testing.T, in string, out ...string) {
	buf := new(bytes.Buffer)
	writer := bufio.NewWriter(buf)
	reader := bufio.NewReader(strings.NewReader(in))

	err := patch(writer, reader)

	assert := require.New(t)
	assert.NoError(err)

	patched := bufio.NewReader(buf)
	for _, expected := range out {
		actual, err := patched.ReadString('\n')
		assert.NoError(err, "Should have read '%s'", expected)
		assert.Equal(expected, actual)
	}

	_, err = patched.ReadString('\n')
	assert.Equal(err, io.EOF)
}
