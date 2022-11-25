package tiled

import (
	"fmt"
	"strconv"
)

type Property struct {
	Name  string `xml:"name,attr"`
	Type  string `xml:"type,attr"`
	Value string `xml:"value,attr"`
}

func GetIntProperty(name string, value int) Property {
	return Property{Name: name, Type: "int", Value: strconv.Itoa(value)}
}

func (p *Property) GetInt() (int, error) {
	if len(p.Type) > 0 && p.Type != "int" {
		return 0, fmt.Errorf("invalid type '%s' for int", p.Type)
	}

	value, err := strconv.Atoi(p.Value)
	if err != nil {
		return 0, err
	}

	return value, nil
}
