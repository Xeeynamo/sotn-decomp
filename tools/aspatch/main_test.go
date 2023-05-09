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
		"\tlw\t$2,$L37($2)\n",
	} {
		t.Run(tcase, func(t *testing.T) {
			assertPatch(t, tcase, tcase)
		})
	}
}

func TestPatchLoadByteWithPointer(t *testing.T) {
	assertPatch(t,
		"\tlb\t$2,D_801809EC($4)\n",

		"\t.set\tnoat\n",
		"\tlui\t$1,%hi(D_801809EC)\n",
		"\taddu\t$1,$1,$4\n",
		"\tlb\t$2,%lo(D_801809EC)($1)\n",
		"\t.set\tat\n",
	)
}

func TestPatchLoadByteUnsignedWithPointer(t *testing.T) {
	assertPatch(t,
		"\tlbu\t$2,D_801809EC($4)\n",

		"\t.set\tnoat\n",
		"\tlui\t$1,%hi(D_801809EC)\n",
		"\taddu\t$1,$1,$4\n",
		"\tlbu\t$2,%lo(D_801809EC)($1)\n",
		"\t.set\tat\n",
	)
}

func TestPatchLoadHalfWithPointer(t *testing.T) {
	assertPatch(t,
		"\tlh\t$2,D_801809EC($4)\n",

		"\t.set\tnoat\n",
		"\tlui\t$1,%hi(D_801809EC)\n",
		"\taddu\t$1,$1,$4\n",
		"\tlh\t$2,%lo(D_801809EC)($1)\n",
		"\t.set\tat\n",
	)
}

func TestPatchLoadHalfUnsignedWithPointer(t *testing.T) {
	assertPatch(t,
		"\tlhu\t$2,D_801809EC($4)\n",

		"\t.set\tnoat\n",
		"\tlui\t$1,%hi(D_801809EC)\n",
		"\taddu\t$1,$1,$4\n",
		"\tlhu\t$2,%lo(D_801809EC)($1)\n",
		"\t.set\tat\n",
	)
}

func TestPatchLoadWordWithPointer(t *testing.T) {
	assertPatch(t,
		"\tlw\t$2,D_801809EC($4)\n",

		"\t.set\tnoat\n",
		"\tlui\t$1,%hi(D_801809EC)\n",
		"\taddu\t$1,$1,$4\n",
		"\tlw\t$2,%lo(D_801809EC)($1)\n",
		"\t.set\tat\n",
	)
}

func TestPatchRemWithAspsxRem(t *testing.T) {
	assertPatch(t,
		"\trem	$4,$2,$3\n",

		"\t.set\tnoreorder\n",
		"\t.set\tnomacro\n",
		"\t.set\tnoat\n",
		"\tdiv\t$0,$2,$3\n",
		"\tbnez\t$3,.L_NOT_DIV_BY_ZERO_1\n",
		"\tnop\n",
		"\tbreak\t0x7\n",
		".L_NOT_DIV_BY_ZERO_1:\n",
		"\taddiu\t$1,$0,-1\n",
		"\tbne\t$3,$1,.L_DIV_BY_POSITIVE_SIGN_1\n",
		"\tlui\t$1,0x8000\n",
		"\tbne\t$2,$1,.L_DIV_BY_POSITIVE_SIGN_1\n",
		"\tnop\n",
		"\tbreak\t0x6\n",
		".L_DIV_BY_POSITIVE_SIGN_1:\n",
		"\tmfhi\t$4\n",
		"\tnop\n",
		"\t.set\tat\n",
		"\t.set\tmacro\n",
		"\t.set\treorder\n",
	)
}

func TestPatchRemWithAspsxDiv(t *testing.T) {
	assertPatch(t,
		"\tdiv	$4,$2,$3\n",

		"\t.set\tnoreorder\n",
		"\t.set\tnomacro\n",
		"\t.set\tnoat\n",
		"\tdiv\t$0,$2,$3\n",
		"\tbnez\t$3,.L_NOT_DIV_BY_ZERO_1\n",
		"\tnop\n",
		"\tbreak\t0x7\n",
		".L_NOT_DIV_BY_ZERO_1:\n",
		"\taddiu\t$1,$0,-1\n",
		"\tbne\t$3,$1,.L_DIV_BY_POSITIVE_SIGN_1\n",
		"\tlui\t$1,0x8000\n",
		"\tbne\t$2,$1,.L_DIV_BY_POSITIVE_SIGN_1\n",
		"\tnop\n",
		"\tbreak\t0x6\n",
		".L_DIV_BY_POSITIVE_SIGN_1:\n",
		"\tmflo\t$4\n",
		"\t.set\tat\n",
		"\t.set\tmacro\n",
		"\t.set\treorder\n",
	)
}

func TestPatchRemWithAspsxDivu(t *testing.T) {
	assertPatch(t,
		"\tdivu $4,$2,$3\n",

		"\t.set\tnoat\n",
		"\tdivu\t$0,$2,$3\n",
		"\tbnez\t$3,.L_NOT_DIV_BY_ZERO_1\n",
		"\tbreak\t0x7\n",
		".L_NOT_DIV_BY_ZERO_1:\n",
		"\tmflo\t$4\n",
		"\t.set\tat\n",
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
