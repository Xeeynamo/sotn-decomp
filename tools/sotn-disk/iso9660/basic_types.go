package iso9660

import "encoding/binary"

type AString string
type DString string

type Data16 struct {
	LSB uint16
	MSB uint16
}

type Data32 struct {
	LSB uint32
	MSB uint32
}

var aChars = arrayToSet([]byte{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
	'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1',
	'2', '3', '4', '5', '6', '7', '8', '9', '_', '!', '"', '%', '&', '\'',
	'(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?',
	' ',
})

var dChars = arrayToSet([]byte{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
	'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1',
	'2', '3', '4', '5', '6', '7', '8', '9', '_', ' ',
})

func arrayToSet(a []byte) map[byte]struct{} {
	set := make(map[byte]struct{}, len(a))
	for _, elem := range a {
		set[elem] = struct{}{}
	}

	return set
}

func ToAString(str string, length int) AString {
	data := make([]byte, length)
	for i := 0; i < len(str); i++ {
		if _, found := aChars[str[i]]; found {
			data[i] = str[i]
		} else {
			data[i] = ' '
		}
	}
	for i := len(str); i < length; i++ {
		data[i] = ' '
	}

	return AString(data)
}

func ToDString(str string, length int) DString {
	data := make([]byte, length)
	for i := 0; i < len(str); i++ {
		if _, found := dChars[str[i]]; found {
			data[i] = str[i]
		} else {
			data[i] = ' '
		}
	}
	for i := len(str); i < length; i++ {
		data[i] = ' '
	}

	return DString(data)
}

func read16(data []byte) Data16 {
	return Data16{
		LSB: binary.LittleEndian.Uint16(data[0:]),
		MSB: binary.BigEndian.Uint16(data[2:]),
	}
}

func read32(data []byte) Data32 {
	return Data32{
		LSB: binary.LittleEndian.Uint32(data[0:]),
		MSB: binary.BigEndian.Uint32(data[4:]),
	}
}

func make16(v uint16) Data16 {
	return Data16{LSB: v, MSB: v}
}

func make32(v uint32) Data32 {
	return Data32{LSB: v, MSB: v}
}

func serialize16(data Data16) []byte {
	finalData := make([]byte, 4)
	binary.LittleEndian.PutUint16(finalData[0:2], data.LSB)
	binary.BigEndian.PutUint16(finalData[2:4], data.MSB)
	return finalData
}

func serialize32(data Data32) []byte {
	finalData := make([]byte, 8)
	binary.LittleEndian.PutUint32(finalData[0:4], data.LSB)
	binary.BigEndian.PutUint32(finalData[4:8], data.MSB)
	return finalData
}
