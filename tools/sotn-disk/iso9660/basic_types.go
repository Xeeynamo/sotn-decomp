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

func ToAString(str string) AString {
	// TODO
	// A B C D E F G H I J K L M N O P Q R S T U V W X Y Z 0 1 2 3 4 5 6 7 8 9
	// _ ! " % & ' ( ) * + , - . / : ; < = > ?
	return AString(str)
}

func ToDString(str string) DString {
	// TODO
	// A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
	// 0 1 2 3 4 5 6 7 8 9 _
	return DString(str)
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
		MSB: binary.BigEndian.Uint32(data[2:]),
	}
}
