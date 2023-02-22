package main

import (
	"encoding/binary"
	"fmt"
	"os"
	"strings"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-disk/iso9660"
)

type patch struct {
	offset int
	name   string
	mode   int
}

func patchDRAEntry(fileName string, img *iso9660.WritableImage, base int, stage string) error {
	prefix := "ST"
	if strings.HasPrefix(stage, "BO") ||
		strings.HasPrefix(stage, "RBO") ||
		stage == "MAR" {
		prefix = "BOSS"
	}

	sound := "SD_ZK"
	if stage[0] == 'R' && len(stage) == 4 {
		sound = "SD_Z"
	}

	return patchBinary(fileName, []patch{
		{base + 0x00, fmt.Sprintf("%s/%s/F_%s.BIN", prefix, stage, stage), 0},
		{base + 0x04, fmt.Sprintf("%s/%s/%s.BIN", prefix, stage, stage), 0},
		{base + 0x08, fmt.Sprintf("%s/%s/%s.BIN", prefix, stage, stage), 1},
		{base + 0x0C, fmt.Sprintf("%s/%s/%s%s.VH", prefix, stage, sound, stage), 0},
		{base + 0x10, fmt.Sprintf("%s/%s/%s%s.VH", prefix, stage, sound, stage), 1},
		{base + 0x14, fmt.Sprintf("%s/%s/%s%s.VB", prefix, stage, sound, stage), 1},
	}, img)
}

func patchDRA(fileName string, img *iso9660.WritableImage) error {
	stages := []string{
		"NO0", "NO1", "LIB", "CAT", "NO2", "CHI", "DAI", "NP3",
		"CEN", "NO4", "ARE", "TOP", "NZ0", "NZ1", "WRP", "NO1",
		"NO0", "NO1", "DRE", "NZ0", "NZ1", "LIB", "BO7", "MAR",
		"BO6", "BO5", "BO4", "BO3", "BO2", "BO1", "BO0", "ST0",
		"RNO0", "RNO1", "RLIB", "RCAT", "RNO2", "RCHI", "RDAI", "RNO3",
		"RCEN", "RNO4", "RARE", "RTOP", "RNZ0", "RNZ1", "RWRP", "NO1",
		"NO1", "NO1", "NO1", "NO1", "NO1", "RNZ1", "RBO8", "RBO7",
		"RBO6", "RBO5", "RBO4", "RBO3", "RBO2", "RBO1", "RBO0", "NO1",
		"MAD", "NO3", "DAI", "LIB", "NO1", "SEL", "TE1", "TE2",
		"TE3", "TE4", "TE5", "TOP", "TE2", "TE2", "TE2", "TE2",
	}
	for idx, stage := range stages {
		if err := patchDRAEntry(fileName, img, 0x3C40+idx*0x2C, stage); err != nil {
			return err
		}
	}

	return patchBinary(fileName, []patch{
		{0xC9D8, "BIN/F_TITLE0.BIN", 0},
		{0xC9E8, "BIN/F_PROLO0.BIN", 0},
		{0xCA08, "ST/NO0/F_NO0.BIN", 0},
		{0xCA18, "VAB/SD_ALK.VH", 0},
		{0xCA28, "VAB/SD_ALK.VB", 0},
		{0xCA38, "VAB/SD_RIH.VH", 0},
		{0xCA48, "VAB/SD_RIH.VB", 0},
		{0xCA58, "VAB/SD_MAR.VH", 0},
		{0xCA68, "VAB/SD_MAR.VB", 0},
		{0xCA78, "SD_J010.VH", 0},
		{0xCA88, "SD_J010.VB", 0},
		{0xCA98, "SD_J010.VH", 0},
		{0xCAA8, "SD_J010.VB", 0},
		{0xCAE8, "SD_J010.VH", 0},
		{0xCAF8, "SD_J010.VB", 0},
		{0xCB08, "BIN/WEAPON0.BIN", 0},
		{0xCB18, "BIN/WEAPON1.BIN", 0},
		{0xCB28, "BIN/MONSTER.BIN", 0},
		{0xCB38, "BIN/DEMOKEY.BIN", 0},
		{0xCB48, "SERVANT/FT_000.BIN", 0},
		{0xCB4C, "SERVANT/FT_001.BIN", 0},
		{0xCB50, "SERVANT/FT_002.BIN", 0},
		{0xCB54, "SERVANT/FT_003.BIN", 0},
		{0xCB58, "SERVANT/FT_004.BIN", 0},
		{0xCB5C, "SERVANT/FT_005.BIN", 0},
		{0xCB60, "SERVANT/FT_006.BIN", 0},
		{0xCB64, "SERVANT/SD_BAT.VH", 0},
		{0xCB68, "SERVANT/SD_GHOST.VH", 0},
		{0xCB6C, "SERVANT/SD_FAIRY.VH", 0},
		{0xCB70, "SERVANT/SD_DEVIL.VH", 0},
		{0xCB74, "SERVANT/SD_SWORD.VH", 0},
		{0xCB78, "SERVANT/SD_FAIR2.VH", 0},
		{0xCB7C, "SERVANT/SD_DEVI2.VH", 0},
		{0xCB9C, "SERVANT/SD_BAT.VB", 0},
		{0xCBA0, "SERVANT/SD_GHOST.VB", 0},
		{0xCBA4, "SERVANT/SD_FAIRY.VB", 0},
		{0xCBA8, "SERVANT/SD_DEVIL.VB", 0},
		{0xCBAC, "SERVANT/SD_SWORD.VB", 0},
		{0xCBB0, "SERVANT/SD_FAIR2.VB", 0},
		{0xCBB4, "SERVANT/SD_DEVI2.VB", 0},
		{0xCC04, "BIN/RIC.BIN", 0},
		{0xCC14, "BIN/ARC_F.BIN", 0},
		{0xCC24, "OPN_WS.STR", 0},
		{0xCC44, "BIN/F_GO.BIN", 0},
		{0xCC54, "BIN/F_END.BIN", 0},
		{0xCD04, "ST/DAI/SEQ_DAI.SEQ", 0},
	}, img)
}

func patchSEL(fileName string, img *iso9660.WritableImage) error {
	return patchBinary(fileName, []patch{
		// TODO TE1, TE2, TE3, TE4, TE5 seems to not be in SEL.BIN?
		// TODO all boss rooms are missing
		{0xA50C, "ST/NO0/NO0.BIN", 0},
		{0xA510, "ST/NO0/F_NO0.BIN", 0},
		{0xA518, "ST/NO0/SD_ZKNO0.VH", 0},
		{0xA538, "ST/NO1/NO1.BIN", 0},
		{0xA53C, "ST/NO1/F_NO1.BIN", 0},
		{0xA544, "ST/NO1/SD_ZKNO1.VH", 0},
		{0xA594, "ST/CAT/CAT.BIN", 0},
		{0xA598, "ST/CAT/F_CAT.BIN", 0},
		{0xA59C, "ST/CAT/SD_ZKCAT.VH", 0},
		{0xA5BC, "ST/NO2/NO2.BIN", 0},
		{0xA5C0, "ST/NO2/F_NO2.BIN", 0},
		{0xA5C8, "ST/NO2/SD_ZKNO2.VH", 0},
		{0xA5E8, "ST/CHI/CHI.BIN", 0},
		{0xA5EC, "ST/CHI/F_CHI.BIN", 0},
		{0xA5F4, "ST/CHI/SD_ZKCHI.VH", 0},
		{0xA614, "ST/DAI/DAI.BIN", 0},
		{0xA618, "ST/DAI/F_DAI.BIN", 0},
		{0xA620, "ST/DAI/SD_ZKDAI.VH", 0},
		{0xA640, "ST/NP3/NP3.BIN", 0},
		{0xA644, "ST/NP3/F_NP3.BIN", 0},
		{0xA64C, "ST/NP3/SD_ZKNP3.VH", 0},
		{0xA66C, "ST/CEN/CEN.BIN", 0},
		{0xA670, "ST/CEN/F_CEN.BIN", 0},
		{0xA678, "ST/CEN/SD_ZKCEN.VH", 0},
		{0xA698, "ST/NO4/NO4.BIN", 0},
		{0xA69C, "ST/NO4/F_NO4.BIN", 0},
		{0xA6A4, "ST/NO4/SD_ZKNO4.VH", 0},
		{0xA6C4, "ST/ARE/F_ARE.BIN", 0},
		{0xA6C8, "ST/ARE/ARE.BIN", 0},
		{0xA6D0, "ST/ARE/SD_ZKARE.VH", 0},
		{0xA71C, "ST/NZ0/NZ0.BIN", 0},
		{0xA720, "ST/NZ0/F_NZ0.BIN", 0},
		{0xA728, "ST/NZ0/SD_ZKNZ0.VH", 0},
		{0xA748, "ST/NZ1/NZ1.BIN", 0},
		{0xA74C, "ST/NZ1/F_NZ1.BIN", 0},
		{0xA754, "ST/NZ1/SD_ZKNZ1.VH", 0},
		{0xA774, "ST/WRP/WRP.BIN", 0},
		{0xA778, "ST/WRP/F_WRP.BIN", 0},
		{0xA780, "ST/WRP/SD_ZKWRP.VH", 0},
		{0xA824, "ST/DRE/DRE.BIN", 0},
		{0xA828, "ST/DRE/F_DRE.BIN", 0},
		{0xA830, "ST/DRE/SD_ZKDRE.VH", 0},
		{0xA8A8, "ST/LIB/LIB.BIN", 0},
		{0xA8AC, "ST/LIB/F_LIB.BIN", 0},
		{0xA8B4, "ST/LIB/SD_ZKLIB.VH", 0},
		{0xAA60, "ST/ST0/ST0.BIN", 0},
		{0xAA64, "ST/ST0/F_ST0.BIN", 0},
		{0xAA6C, "ST/ST0/SD_ZKST0.VH", 0},
		{0xAA8C, "ST/RNO0/RNO0.BIN", 0},
		{0xAA90, "ST/RNO0/F_RNO0.BIN", 0},
		{0xAA98, "ST/RNO0/SD_ZRNO0.VH", 0},
		{0xAAB8, "ST/RNO1/RNO1.BIN", 0},
		{0xAABC, "ST/RNO1/F_RNO1.BIN", 0},
		{0xAAC4, "ST/RNO1/SD_ZRNO1.VH", 0},
		{0xAAE4, "ST/RLIB/RLIB.BIN", 0},
		{0xAAE8, "ST/RLIB/F_RLIB.BIN", 0},
		{0xAAF0, "ST/RLIB/SD_ZRLIB.VH", 0},
		{0xAB10, "ST/RCAT/RCAT.BIN", 0},
		{0xAB14, "ST/RCAT/F_RCAT.BIN", 0},
		{0xAB1C, "ST/RCAT/SD_ZRCAT.VH", 0},
		{0xAB3C, "ST/RNO2/RNO2.BIN", 0},
		{0xAB40, "ST/RNO2/F_RNO2.BIN", 0},
		{0xAB48, "ST/RNO2/SD_ZRNO2.VH", 0},
		{0xAB68, "ST/RCHI/RCHI.BIN", 0},
		{0xAB6C, "ST/RCHI/F_RCHI.BIN", 0},
		{0xAB74, "ST/RCHI/SD_ZRCHI.VH", 0},
		{0xAB94, "ST/RDAI/RDAI.BIN", 0},
		{0xAB98, "ST/RDAI/F_RDAI.BIN", 0},
		{0xABA0, "ST/RDAI/SD_ZRDAI.VH", 0},
		{0xABC0, "ST/RNO3/RNO3.BIN", 0},
		{0xABC4, "ST/RNO3/F_RNO3.BIN", 0},
		{0xABCC, "ST/RNO3/SD_ZRNO3.VH", 0},
		{0xABEC, "ST/RCEN/RCEN.BIN", 0},
		{0xABF0, "ST/RCEN/F_RCEN.BIN", 0},
		{0xABF8, "ST/RCEN/SD_ZRCEN.VH", 0},
		{0xAC18, "ST/RNO4/RNO4.BIN", 0},
		{0xAC1C, "ST/RNO4/F_RNO4.BIN", 0},
		{0xAC24, "ST/RNO4/SD_ZRNO4.VH", 0},
		{0xAC44, "ST/RARE/RARE.BIN", 0},
		{0xAC48, "ST/RARE/F_RARE.BIN", 0},
		{0xAC50, "ST/RARE/SD_ZRARE.VH", 0},
		{0xAC70, "ST/RTOP/RTOP.BIN", 0},
		{0xAC74, "ST/RTOP/F_RTOP.BIN", 0},
		{0xAC7C, "ST/RTOP/SD_ZRTOP.VH", 0},
		{0xAC9C, "ST/RNZ0/RNZ0.BIN", 0},
		{0xACA0, "ST/RNZ0/F_RNZ0.BIN", 0},
		{0xACA8, "ST/RNZ0/SD_ZRNZ0.VH", 0},
		{0xACC8, "ST/RNZ1/RNZ1.BIN", 0},
		{0xACCC, "ST/RNZ1/F_RNZ1.BIN", 0},
		{0xACD4, "ST/RNZ1/SD_ZRNZ1.VH", 0},
		{0xACF4, "ST/RWRP/RWRP.BIN", 0},
		{0xACF8, "ST/RWRP/F_RWRP.BIN", 0},
		{0xAD00, "ST/RWRP/SD_ZRWRP.VH", 0},
		{0xB00C, "ST/MAD/MAD.BIN", 0},
		{0xB010, "ST/MAD/F_MAD.BIN", 0},
		{0xB018, "ST/MAD/SD_ZKMAD.VH", 0},
		{0xB038, "ST/NO3/NO3.BIN", 0},
		{0xB03C, "ST/NO3/F_NO3.BIN", 0},
		{0xB044, "ST/NO3/SD_ZKNO3.VH", 0},
		{0xB0E8, "ST/SEL/F_SEL.BIN", 0},
		{0xB0EC, "ST/SEL/SEL.BIN", 0},
		{0xB0F4, "ST/SEL/SD_ZKSEL.VH", 0},
		{0xB1F0, "ST/TOP/TOP.BIN", 0},
		{0xB1F4, "ST/TOP/F_TOP.BIN", 0},
		{0xB1FC, "ST/TOP/SD_ZKTOP.VH", 0},
	}, img)
}

func patchBinary(fileName string, patches []patch, img *iso9660.WritableImage) error {
	f, err := os.OpenFile(fileName, os.O_WRONLY, 0)
	if err != nil {
		return err
	}
	defer f.Close()

	for _, entry := range patches {
		var data uint32

		name := fmt.Sprintf("%s;1", entry.name)
		switch entry.mode {
		case 0:
			data, err = img.GetFileLocation(name)
			if err != nil {
				return err
			}
		case 1:
			data, err = img.GetFileSize(name)
			if err != nil {
				return err
			}
		}

		rawdata := make([]byte, 4)
		binary.LittleEndian.PutUint32(rawdata, data)
		if _, err = f.WriteAt(rawdata, int64(entry.offset)); err != nil {
			return err
		}
	}

	return nil
}
