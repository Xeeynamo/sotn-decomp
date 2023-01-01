package iso9660

// some of the code here was based from error_recalc.c:
// https://www.romhacking.net/utilities/1264/

// some of the code here was based from iso2raw.c:
// https://github.com/iamgreaser/psx-chain/blob/master/tools/iso2raw.c

const eccPolynomial = 0xD8018001

var ecc_f_lut, ecc_b_lut, edc_lut = eecEdcInit()

func eecEdcInit() ([]byte, []byte, []uint32) {
	ecc_f_lut := make([]byte, 256)
	ecc_b_lut := make([]byte, 256)
	edc_lut := make([]uint32, 256)
	for i := 0; i < 256; i++ {
		j := i << 1
		if (i & 0x80) != 0 {
			j ^= 0x11D
		}

		ecc_f_lut[i] = byte(j)
		ecc_b_lut[i^j] = byte(i)
		edc := uint32(i)
		for j := 0; j < 8; j++ {
			if (edc & 1) != 0 {
				edc = (edc >> 1) ^ eccPolynomial
			} else {
				edc >>= 1
			}
		}
		edc_lut[i] = edc
	}

	return ecc_f_lut, ecc_b_lut, edc_lut
}

func computeEDC(data []byte) uint32 {
	edc := uint32(0)
	for i := 0; i < len(data); i++ {
		edc = (edc >> 8) ^ edc_lut[byte(edc^uint32(data[i]))]
	}

	return edc
}

func calcPParity(data []byte) {
	eccComputeBlock(data[12:], 2*43, 24, 2, 2*43, data[0x81C:])
}

func calcQParity(data []byte) {
	eccComputeBlock(data[12:], 2*26, 43, 2*43, 2*44, data[0x8C8:])
}

func eccComputeBlock(
	src []byte,
	major_count int,
	minor_count int,
	major_mult int,
	minor_inc int,
	dest []byte,
) {
	size := major_count * minor_count
	for major := 0; major < major_count; major++ {
		index := (major>>1)*major_mult + (major & 1)
		ecc_a := byte(0)
		ecc_b := byte(0)
		for minor := 0; minor < minor_count; minor++ {
			ecc_a = ecc_f_lut[ecc_a^src[index]]
			ecc_b ^= src[index]
			index += minor_inc
			if index >= size {
				index -= size
			}
		}
		ecc_a = ecc_b_lut[ecc_f_lut[ecc_a]^ecc_b]
		dest[major] = ecc_a
		dest[major+major_count] = ecc_a ^ ecc_b
	}
}
