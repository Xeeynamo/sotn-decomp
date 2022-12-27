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
