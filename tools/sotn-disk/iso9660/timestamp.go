package iso9660

type Timestamp struct {
	Year   byte
	Month  byte
	Day    byte
	Hour   byte
	Minute byte
	Second byte
	Offset byte
}

type VolumeTimestamp struct {
	Year      string
	Month     string
	Day       string
	Hour      string
	Minute    string
	Second    string
	Hundredth string
	Offset    byte
}

var DefaultVolumeTimestamp = VolumeTimestamp{
	"0000", "00", "00", "00", "00", "00", "00", 0,
}

func parseTimestamp(data []byte) Timestamp {
	return Timestamp{
		Year:   data[0],
		Month:  data[1],
		Day:    data[2],
		Hour:   data[3],
		Minute: data[4],
		Second: data[5],
		Offset: data[6],
	}
}

func parseVolumeTimestamp(data []byte) VolumeTimestamp {
	return VolumeTimestamp{
		Year:      string(data[0:4]),
		Month:     string(data[4:6]),
		Day:       string(data[6:8]),
		Hour:      string(data[8:10]),
		Minute:    string(data[10:12]),
		Second:    string(data[12:14]),
		Hundredth: string(data[14:16]),
		Offset:    data[16],
	}
}

func serializeVolumeTimestamp(t VolumeTimestamp) []byte {
	data := make([]byte, 17)

	copy(data[0:4], []byte(t.Year))
	copy(data[4:6], []byte(t.Month))
	copy(data[6:8], []byte(t.Day))
	copy(data[8:10], []byte(t.Hour))
	copy(data[10:12], []byte(t.Minute))
	copy(data[12:14], []byte(t.Second))
	copy(data[14:16], []byte(t.Hundredth))
	data[16] = t.Offset

	return data
}

func serializeTimestamp(t Timestamp) []byte {
	data := make([]byte, 7)

	data[0] = t.Year
	data[1] = t.Month
	data[2] = t.Day
	data[3] = t.Hour
	data[4] = t.Minute
	data[5] = t.Second
	data[6] = t.Offset

	return data
}
