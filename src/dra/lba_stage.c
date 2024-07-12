#include "stage.h"

// clang-format off
Lba g_StagesLba[] = {
#if defined(VERSION_US)
    { 0x7E5D, 0x7F16, 0x5F58C, 0x7EDD, 0x1A20, 0x1A3A0, 0x30D, "F_NO0", "NO0", "rou", 0x16, 0xFF, 0, },
    { 0x7FD6, 0x808E, 0x57064, 0x8056, 0x1A20, 0x19CA0, 0x313, "F_NO1", "NO1", "tou", 0x02, 0xFF, 0, },
    { 0x7C0E, 0x7CBF, 0x552CC, 0x7C8E, 0x1A20, 0x16250, 0x309, "F_LIB", "LIB", "lib", 0x29, 0x00, 0, },
    { 0x7849, 0x7766, 0x585C0, 0x7817, 0x1A20, 0x16960, 0x307, "F_CAT", "CAT", "cat", 0x12, 0xFF, 0, },
    { 0x813E, 0x81F6, 0x4FDBC, 0x81BE, 0x1C20, 0x19D00, 0x317, "F_NO2", "NO2", "olst", 0x01, 0xFF, 0, },
    { 0x7A34, 0x79BF, 0x2F428, 0x7A1E, 0x1420, 0x09420, 0x319, "F_CHI", "CHI", "chi", 0x32, 0xFF, 0, },
    { 0x7B8C, 0x7AB5, 0x5B404, 0x7B6C, 0x1A20, 0x0DF10, 0x305, "F_DAI", "DAI", "chu", 0x17, 0x01, 0, },
    { 0x917F, 0x9235, 0x53434, 0x91FF, 0x1C20, 0x18D10, 0x30F, "F_NP3", "NP3", "siro1", 0x03, 0xFF, 0, },
    { 0x793E, 0x78CA, 0x1D46C, 0x7905, 0x1A20, 0x1A3A0, 0x325, "F_CEN", "CEN", "rou", 0x05, 0xFF, 0, },
    { 0x8400, 0x84AF, 0x5F85C, 0x8480, 0x1A20, 0x151C0, 0x30B, "F_NO4", "NO4", "mizu", 0x04, 0xFF, 0, },
    { 0x76E5, 0x7600, 0x5617C, 0x76AD, 0x1C20, 0x19FD0, 0x323, "F_ARE", "ARE", "togi", 0x1A, 0xFF, 0, },
    { 0x9554, 0x95DE, 0x3C55C, 0x95D4, 0x1A20, 0x028C0, 0x31B, "F_TOP", "TOP", "top", 0x24, 0xFF, 0, },
    { 0x92DD, 0x937D, 0x4B780, 0x935D, 0x1820, 0x0DE90, 0x32E, "F_NZ0", "NZ0", "gold", 0x0D, 0xFF, 0, },
    { 0x9415, 0x94CE, 0x42340, 0x9495, 0x1C20, 0x1A060, 0x311, "F_NZ1", "NZ1", "toke", 0x2B, 0xFF, 0, },
    { 0x996C, 0x9A25, 0x14768, 0x99EC, 0x1C20, 0x1A060, 0x2FF, "F_WRP", "WRP", "toke", 0x2E, 0xFF, 0, },
    { 0x7FD6, 0x808E, 0x57064, 0x8056, 0x1A20, 0x19CA0, 0x30D, "F_NO1", "NO1", "rou", 0x11, 0xFF, 0, },
    { 0x7E5D, 0x7F16, 0x5F58C, 0x7EDD, 0x1A20, 0x1A3A0, 0x30D, "F_NO0", "NO0", "rou", 0x11, 0xFF, 0, },
    { 0x7FD6, 0x808E, 0x57064, 0x8056, 0x1A20, 0x19CA0, 0x30D, "F_NO1", "NO1", "rou", 0x11, 0xFF, 0, },
    { 0x9DAA, 0x9E62, 0x23FCC, 0x9E2A, 0x1620, 0x1A610, 0x2FF, "F_DRE", "DRE", "sakyu", 0x33, 0xFF, 0, },
    { 0x92DD, 0x937D, 0x4B780, 0x935D, 0x1820, 0x0DE90, 0x32E, "F_NZ0", "NZ0", "gold", 0x40, 0xFF, 0, },
    { 0x9415, 0x94CE, 0x42340, 0x9495, 0x1C20, 0x1A060, 0x311, "F_NZ1", "NZ1", "toke", 0x80, 0xFF, 0, },
    { 0x7C0E, 0x7CBF, 0x552CC, 0x7C8E, 0x1A20, 0x16250, 0x309, "F_LIB", "LIB", "lib", 0x81, 0x00, 0, },
    { 0xB23A, 0xB2DA, 0x23460, 0xB2BA, 0x1A20, 0x0DCE0, 0x2FF, "F_CHI", "BO7", "keru", 0x57, 0xFF, 0, },
    { 0xAF3A, 0xAFF3, 0x1AF70, 0x7EDD, 0x1A20, 0x1A3A0, 0x2FF, "F_NO0", "MAR", "rou", 0x64, 0xFF, 0, },
    { 0xACDD, 0xAD91, 0x516E8, 0xAD5D, 0x1820, 0x17AB0, 0x2FF, "F_TOP", "BO6", "rihi", 0x65, 0xFF, 0, },
    { 0xABD1, 0xAC71, 0x35630, 0xAC51, 0x1A20, 0x0DF10, 0x2FF, "F_DAI", "BO5", "chu", 0x68, 0xFF, 0, },
    { 0xAA76, 0xAB26, 0x54E38, 0xAAF6, 0x1420, 0x162F0, 0x2FF, "F_NO1", "BO4", "nalk", 0x6C, 0xFF, 0, },
    { 0xA956, 0xAA0E, 0x33530, 0xA9D6, 0x1A20, 0x19850, 0x2FF, "F_NO4", "BO3", "sukyu", 0x6F, 0xFF, 0, },
    { 0xA854, 0xA8E7, 0x36934, 0xA8D4, 0x1A20, 0x070F0, 0x2FF, "F_ARE", "BO2", "mino", 0x72, 0xFF, 0, },
    { 0xA737, 0xA7EE, 0x323BC, 0xA7B7, 0x1020, 0x19E70, 0x2FF, "F_CAT", "BO1", "regi", 0x76, 0xFF, 0, },
    { 0xA5E2, 0xA699, 0x4E5B4, 0xA662, 0x1420, 0x19D50, 0x2FF, "F_NO2", "BO0", "olro", 0x7D, 0xFF, 0, },
    { 0x9044, 0x90F9, 0x425C4, 0x90C4, 0x1220, 0x18BC0, 0x321, "F_ST0", "ST0", "dora1", 0x7F, 0xFF, 0, },
    { 0x89C4, 0x8A7B, 0x54B8C, 0x8A44, 0x1C20, 0x19170, 0x338, "F_RNO0", "RNO0", "roux", 0x00, 0xFF, 0, },
    { 0x8B26, 0x8BDC, 0x380E0, 0x8BA6, 0x1A20, 0x18E40, 0x338, "F_RNO1", "RNO1", "toux", 0x00, 0xFF, 0, },
    { 0x88BE, 0x8960, 0x31430, 0x893E, 0x1A20, 0x0EE70, 0x301, "F_RLIB", "RLIB", "libx", 0x00, 0xFF, 0, },
    { 0x8570, 0x860E, 0x43EAC, 0x85F0, 0x1A20, 0x0CA30, 0x303, "F_RCAT", "RCAT", "catx", 0x00, 0xFF, 0, },
    { 0x8C4E, 0x8D01, 0x4C9D8, 0x8CCE, 0x1C20, 0x170E0, 0x338, "F_RNO2", "RNO2", "olstx", 0x00, 0xFF, 0, },
    { 0x8697, 0x8737, 0x2AB20, 0x8717, 0x1620, 0x0E020, 0x319, "F_RCHI", "RCHI", "chix", 0x00, 0xFF, 0, },
    { 0x878E, 0x882C, 0x48338, 0x880E, 0x1820, 0x0C820, 0x301, "F_RDAI", "RDAI", "chux", 0x00, 0xFF, 0, },
    { 0x8D9C, 0x8E3C, 0x4A52C, 0x8E1C, 0x1A20, 0x0DF40, 0x338, "F_RNO3", "RNO3", "sirox", 0x00, 0xFF, 0, },
    { 0x9658, 0x970F, 0x2D3D4, 0x96D8, 0x1420, 0x19E50, 0x325, "F_RCEN", "RCEN", "syafu", 0x00, 0xFF, 0, },
    { 0x8ED2, 0x8F87, 0x5DC14, 0x8F52, 0x1A20, 0x185D0, 0x301, "F_RNO4", "RNO4", "mizux", 0x00, 0xFF, 0, },
    { 0x976B, 0x980F, 0x39390, 0x97EB, 0x1A20, 0x0F9C0, 0x315, "F_RARE", "RARE", "togix", 0x00, 0xFF, 0, },
    { 0x9883, 0x9908, 0x3111C, 0x9903, 0x1A20, 0x006F0, 0x31B, "F_RTOP", "RTOP", "topx", 0x00, 0xFF, 0, },
    { 0x9A4F, 0x9B02, 0x44BA8, 0x9ACF, 0x1C20, 0x17430, 0x338, "F_RNZ0", "RNZ0", "goldx", 0x00, 0xFF, 0, },
    { 0x9B8D, 0x9C44, 0x3FB60, 0x9C0D, 0x1C20, 0x19350, 0x338, "F_RNZ1", "RNZ1", "tokex", 0x00, 0xFF, 0, },
    { 0x9CC5, 0x9D7C, 0x166E8, 0x9D45, 0x1C20, 0x19350, 0x2FF, "F_RWRP", "RWRP", "tokex", 0x00, 0xFF, 0, },
    { 0x7FD6, 0x808E, 0x57064, 0x8056, 0x1A20, 0x19CA0, 0x338, "F_NO1", "NO1", "rou", 0x00, 0xFF, 0, },
    { 0x7FD6, 0x808E, 0x57064, 0x8056, 0x1A20, 0x19CA0, 0x338, "F_NO1", "NO1", "rou", 0x00, 0xFF, 0, },
    { 0x7FD6, 0x808E, 0x57064, 0x8056, 0x1A20, 0x19CA0, 0x338, "F_NO1", "NO1", "rou", 0x00, 0xFF, 0, },
    { 0x7FD6, 0x808E, 0x57064, 0x8056, 0x1A20, 0x19CA0, 0x338, "F_NO1", "NO1", "rou", 0x00, 0xFF, 0, },
    { 0x7FD6, 0x808E, 0x57064, 0x8056, 0x1A20, 0x19CA0, 0x338, "F_NO1", "NO1", "rou", 0x00, 0xFF, 0, },
    { 0x7FD6, 0x808E, 0x57064, 0x8056, 0x1A20, 0x19CA0, 0x338, "F_NO1", "NO1", "rou", 0x00, 0xFF, 0, },
    { 0x9B8D, 0x9C44, 0x3FB60, 0x9C0D, 0x1C20, 0x19350, 0x338, "F_RNZ1", "RNZ1", "tokex", 0x82, 0xFF, 0, },
    { 0xB88F, 0xB93F, 0x275BC, 0xB90F, 0x1420, 0x16750, 0x2FF, "F_RCAT", "RBO8", "gara", 0x43, 0xFF, 0, },
    { 0xB791, 0xB848, 0x22CEC, 0xB811, 0x1020, 0x19F60, 0x2FF, "F_RNO2", "RBO7", "mirra", 0x46, 0xFF, 0, },
    { 0xB671, 0xB727, 0x34044, 0xB6F1, 0x1820, 0x18910, 0x2FF, "F_RCEN", "RBO6", "dora", 0x08, 0xFF, 0, },
    { 0xB517, 0xB5C7, 0x54408, 0xB597, 0x1420, 0x162F0, 0x2FF, "F_RNO4", "RBO5", "nalk", 0x4B, 0xFF, 0, },
    { 0xB415, 0xB4CA, 0x25C24, 0xB495, 0x1420, 0x18C30, 0x2FF, "F_RNO1", "RBO4", "frank", 0x4F, 0xFF, 0, },
    { 0xB322, 0xB3D3, 0x20630, 0xB3A2, 0x1220, 0x16E90, 0x2FF, "F_RDAI", "RBO3", "medyu", 0x53, 0xFF, 0, },
    { 0xB125, 0xB1DB, 0x2E948, 0xB1A5, 0x1420, 0x191E0, 0x2FF, "F_RCHI", "RBO2", "deth", 0x5B, 0xFF, 0, },
    { 0xB02A, 0xB0E0, 0x21F60, 0xB0AA, 0x1020, 0x193E0, 0x2FF, "F_RNZ0", "RBO1", "verz", 0x60, 0xFF, 0, },
    { 0xAE35, 0xAEEA, 0x274DC, 0xAEB5, 0x1420, 0x18D60, 0x2FF, "F_RARE", "RBO0", "verm", 0x79, 0xFF, 0, },
    { 0x7FD6, 0x808E, 0x57064, 0x8056, 0x1A20, 0x19CA0, 0x338, "F_NO1", "NO1", "rou", 0x00, 0xFF, 0, },
    { 0x7D6F, 0x7E28, 0x19E94, 0x7DEF, 0x1820, 0x1A700, 0x34B, "F_MAD", "MAD", "rou", 0x37, 0xFF, 0, },
    { 0x8297, 0x834F, 0x57E18, 0x8317, 0x1C20, 0x19AD0, 0x30F, "F_NO3", "NO3", "siro", 0x36, 0xFF, 0, },
    { 0x7FD6, 0x808E, 0x57064, 0x8056, 0x1A20, 0x19CA0, 0x338, "F_DAI", "DAI", "tou", 0x3D, 0xFF, 0, },
    { 0x7C0E, 0x7CBF, 0x552CC, 0x7C8E, 0x1A20, 0x16250, 0x338, "F_LIB", "LIB", "lib", 0x3E, 0xFF, 0, },
    { 0x7FD6, 0x808E, 0x57064, 0x8056, 0x1A20, 0x19CA0, 0x338, "F_NO1", "NO1", "tou", 0x3F, 0xFF, 0, },
    { 0x74B6, 0x754F, 0x56B28, 0x7516, 0x1A20, 0x1A3A0, 0x000, "F_SEL", "SEL", "rou", 0x00, 0xFF, 0, },
    { 0x9EAB, 0x9F64, 0x5D520, 0x9F2B, 0x1820, 0x1A700, 0x301, "F_NO0", "TE1", "rou", 0x7E, 0xFF, 0, },
    { 0xA020, 0xA0D9, 0x5F004, 0xA0A0, 0x1820, 0x1A700, 0x303, "F_NO0", "TE2", "rou", 0x7E, 0xFF, 0, },
    { 0xA199, 0xA252, 0x55440, 0xA219, 0x1820, 0x1A700, 0x305, "F_NO0", "TE3", "rou", 0x7E, 0xFF, 0, },
    { 0xA2FE, 0xA3B7, 0x595A0, 0xA37E, 0x1820, 0x1A700, 0x307, "F_NO0", "TE4", "rou", 0x7E, 0xFF, 0, },
    { 0xA020, 0xA0D9, 0x5F004, 0xA0A0, 0x1820, 0x1A700, 0x301, "F_NO0", "TE5", "rou", 0x7E, 0xFF, 0, },
    { 0x9554, 0x95DE, 0x3C55C, 0x95D4, 0x1A20, 0x028C0, 0x2FF, "F_TOP", "TOP", "top", 0x2C, 0xFF, 0, },
    { 0xA020, 0xA0D9, 0x5F004, 0xA0A0, 0x1820, 0x1A700, 0x301, "F_NO0", "TE2", "rou", 0x7E, 0xFF, 0, },
    { 0xA020, 0xA0D9, 0x5F004, 0xA0A0, 0x1820, 0x1A700, 0x301, "F_NO0", "TE2", "rou", 0x7E, 0xFF, 0, },
    { 0xA020, 0xA0D9, 0x5F004, 0xA0A0, 0x1820, 0x1A700, 0x301, "F_NO0", "TE2", "rou", 0x7E, 0xFF, 0, },
    { 0xA020, 0xA0D9, 0x5F004, 0xA0A0, 0x1820, 0x1A700, 0x301, "F_NO0", "TE2", "rou", 0x7E, 0xFF, 0, },
#elif defined(VERSION_HD)
    { 0x7E97, 0x7F50, 0x5F39C, 0x7F17, 0x1A20, 0x1A510, 0x30D, "F_NO0", "NO0", "rou", 0x16, 0xFF, 0, },
    { 0x8010, 0x80C9, 0x55554, 0x8090, 0x1A20, 0x1A340, 0x313, "F_NO1", "NO1", "tou", 0x02, 0xFF, 0, },
    { 0x7C4A, 0x7CFB, 0x543A0, 0x7CCA, 0x1A20, 0x16250, 0x309, "F_LIB", "LIB", "lib", 0x29, 0x00, 0, },
    { 0x7888, 0x77AC, 0x57A0C, 0x785C, 0x1A20, 0x13E70, 0x307, "F_CAT", "CAT", "cat", 0x12, 0xFF, 0, },
    { 0x8175, 0x822D, 0x4F0C8, 0x81F5, 0x1C20, 0x198C0, 0x317, "F_NO2", "NO2", "olst", 0x01, 0xFF, 0, },
    { 0x7A72, 0x79FD, 0x2E9F0, 0x7A5B, 0x1420, 0x09CD0, 0x319, "F_CHI", "CHI", "chi", 0x32, 0xFF, 0, },
    { 0x7BC8, 0x7AF3, 0x5A7B0, 0x7BA8, 0x1A20, 0x0DF10, 0x305, "F_DAI", "DAI", "chu", 0x17, 0x01, 0, },
    { 0x919C, 0x9251, 0x52B38, 0x921C, 0x1C20, 0x18520, 0x30F, "F_NP3", "NP3", "siro1", 0x03, 0xFF, 0, },
    { 0x797C, 0x7909, 0x1CB00, 0x7943, 0x1A20, 0x1A510, 0x325, "F_CEN", "CEN", "rou", 0x05, 0xFF, 0, },
    { 0x8436, 0x84E5, 0x5F1E8, 0x84B6, 0x1A20, 0x154C0, 0x30B, "F_NO4", "NO4", "mizu", 0x04, 0xFF, 0, },
    { 0x772B, 0x7647, 0x555AC, 0x76F2, 0x1C20, 0x1A340, 0x323, "F_ARE", "ARE", "togi", 0x1A, 0xFF, 0, },
    { 0x956B, 0x95F4, 0x3BA64, 0x95EB, 0x1A20, 0x02100, 0x31B, "F_TOP", "TOP", "top", 0x24, 0xFF, 0, },
    { 0x92F8, 0x9397, 0x4ABDC, 0x9378, 0x1820, 0x0D6D0, 0x32B, "F_NZ0", "NZ0", "gold", 0x0D, 0xFF, 0, },
    { 0x942E, 0x94E7, 0x4169C, 0x94AE, 0x1C20, 0x1A630, 0x311, "F_NZ1", "NZ1", "toke", 0x2B, 0xFF, 0, },
    { 0x997F, 0x9A38, 0x13E80, 0x99FF, 0x1C20, 0x1A630, 0x2FF, "F_WRP", "WRP", "toke", 0x2E, 0xFF, 0, },
    { 0x8010, 0x80C9, 0x55554, 0x8090, 0x1A20, 0x1A340, 0x30D, "F_NO1", "NO1", "rou", 0x11, 0xFF, 0, },
    { 0x7E97, 0x7F50, 0x5F39C, 0x7F17, 0x1A20, 0x1A510, 0x30D, "F_NO0", "NO0", "rou", 0x11, 0xFF, 0, },
    { 0x8010, 0x80C9, 0x55554, 0x8090, 0x1A20, 0x1A340, 0x30D, "F_NO1", "NO1", "rou", 0x11, 0xFF, 0, },
    { 0x9DBA, 0x9E70, 0x2328C, 0x9E3A, 0x1A20, 0x18F00, 0x2FF, "F_DRE", "DRE", "sakyu", 0x33, 0xFF, 0, },
    { 0x92F8, 0x9397, 0x4ABDC, 0x9378, 0x1820, 0x0D6D0, 0x32B, "F_NZ0", "NZ0", "gold", 0x40, 0xFF, 0, },
    { 0x942E, 0x94E7, 0x4169C, 0x94AE, 0x1C20, 0x1A630, 0x311, "F_NZ1", "NZ1", "toke", 0x80, 0xFF, 0, },
    { 0x7C4A, 0x7CFB, 0x543A0, 0x7CCA, 0x1A20, 0x16250, 0x309, "F_LIB", "LIB", "lib", 0x81, 0x00, 0, },
    { 0xB233, 0xB2D3, 0x22B70, 0xB2B3, 0x1A20, 0x0DCE0, 0x2FF, "F_CHI", "BO7", "keru", 0x57, 0xFF, 0, },
    { 0xAF38, 0xAFF1, 0x1A61C, 0x7F17, 0x1A20, 0x1A510, 0x2FF, "F_NO0", "MAR", "rou", 0x64, 0xFF, 0, },
    { 0xACE9, 0xADA0, 0x50D3C, 0xAD69, 0x1820, 0x194E0, 0x2FF, "F_TOP", "BO6", "rihi", 0x65, 0xFF, 0, },
    { 0xABDC, 0xAC7C, 0x35B58, 0xAC5C, 0x1A20, 0x0DF10, 0x2FF, "F_DAI", "BO5", "chu", 0x68, 0xFF, 0, },
    { 0xAA7F, 0xAB32, 0x5451C, 0xAAFF, 0x1420, 0x17980, 0x2FF, "F_NO1", "BO4", "nalk", 0x6C, 0xFF, 0, },
    { 0xA960, 0xAA18, 0x32C30, 0xA9E0, 0x1A20, 0x19E90, 0x2FF, "F_NO4", "BO3", "sukyu", 0x6F, 0xFF, 0, },
    { 0xA85E, 0xA8F3, 0x35F70, 0xA8DE, 0x1A20, 0x083C0, 0x2FF, "F_ARE", "BO2", "mino", 0x72, 0xFF, 0, },
    { 0xA742, 0xA7F9, 0x31ACC, 0xA7C2, 0x1020, 0x19E70, 0x2FF, "F_CAT", "BO1", "regi", 0x76, 0xFF, 0, },
    { 0xA5EF, 0xA6A5, 0x4DCC4, 0xA66F, 0x1420, 0x19270, 0x2FF, "F_NO2", "BO0", "olro", 0x7D, 0xFF, 0, },
    { 0x9060, 0x9116, 0x421C0, 0x90E0, 0x1620, 0x193A0, 0x321, "F_ST0", "ST0", "dora1", 0x7F, 0xFF, 0, },
    { 0x89F4, 0x8AA6, 0x54260, 0x8A74, 0x1C20, 0x16D90, 0x335, "F_RNO0", "RNO0", "roux", 0x00, 0xFF, 0, },
    { 0x8B50, 0x8C06, 0x377C0, 0x8BD0, 0x1A20, 0x18E40, 0x335, "F_RNO1", "RNO1", "toux", 0x00, 0xFF, 0, },
    { 0x88EF, 0x8991, 0x30B58, 0x896F, 0x1A20, 0x0EE70, 0x301, "F_RLIB", "RLIB", "libx", 0x00, 0xFF, 0, },
    { 0x85A5, 0x8642, 0x435DC, 0x8625, 0x1A20, 0x0C730, 0x303, "F_RCAT", "RCAT", "catx", 0x00, 0xFF, 0, },
    { 0x8C76, 0x8D20, 0x4C0C8, 0x8CF6, 0x1C20, 0x129B0, 0x335, "F_RNO2", "RNO2", "olstx", 0x00, 0xFF, 0, },
    { 0x86CA, 0x876A, 0x2A248, 0x874A, 0x1620, 0x0E020, 0x319, "F_RCHI", "RCHI", "chix", 0x00, 0xFF, 0, },
    { 0x87C0, 0x885E, 0x47A14, 0x8840, 0x1820, 0x0C820, 0x301, "F_RDAI", "RDAI", "chux", 0x00, 0xFF, 0, },
    { 0x8DBA, 0x8E5A, 0x49BD8, 0x8E3A, 0x1A20, 0x0DF40, 0x335, "F_RNO3", "RNO3", "sirox", 0x00, 0xFF, 0, },
    { 0x966D, 0x9724, 0x2C98C, 0x96ED, 0x1420, 0x198C0, 0x325, "F_RCEN", "RCEN", "syafu", 0x00, 0xFF, 0, },
    { 0x8EEF, 0x8FA4, 0x5D29C, 0x8F6F, 0x1A20, 0x185D0, 0x301, "F_RNO4", "RNO4", "mizux", 0x00, 0xFF, 0, },
    { 0x977F, 0x9824, 0x38AB8, 0x97FF, 0x1A20, 0x10700, 0x315, "F_RARE", "RARE", "togix", 0x00, 0xFF, 0, },
    { 0x9897, 0x991C, 0x30838, 0x9917, 0x1A20, 0x006F0, 0x31B, "F_RTOP", "RTOP", "topx", 0x00, 0xFF, 0, },
    { 0x9A61, 0x9B15, 0x442C0, 0x9AE1, 0x1C20, 0x17CE0, 0x335, "F_RNZ0", "RNZ0", "goldx", 0x00, 0xFF, 0, },
    { 0x9B9F, 0x9C56, 0x3F1EC, 0x9C1F, 0x1C20, 0x19350, 0x335, "F_RNZ1", "RNZ1", "tokex", 0x00, 0xFF, 0, },
    { 0x9CD6, 0x9D8D, 0x15E00, 0x9D56, 0x1C20, 0x19350, 0x2FF, "F_RWRP", "RWRP", "tokex", 0x00, 0xFF, 0, },
    { 0x8010, 0x80C9, 0x55554, 0x8090, 0x1A20, 0x1A340, 0x335, "F_NO1", "NO1", "rou", 0x00, 0xFF, 0, },
    { 0x8010, 0x80C9, 0x55554, 0x8090, 0x1A20, 0x1A340, 0x335, "F_NO1", "NO1", "rou", 0x00, 0xFF, 0, },
    { 0x8010, 0x80C9, 0x55554, 0x8090, 0x1A20, 0x1A340, 0x335, "F_NO1", "NO1", "rou", 0x00, 0xFF, 0, },
    { 0x8010, 0x80C9, 0x55554, 0x8090, 0x1A20, 0x1A340, 0x335, "F_NO1", "NO1", "rou", 0x00, 0xFF, 0, },
    { 0x8010, 0x80C9, 0x55554, 0x8090, 0x1A20, 0x1A340, 0x335, "F_NO1", "NO1", "rou", 0x00, 0xFF, 0, },
    { 0x8010, 0x80C9, 0x55554, 0x8090, 0x1A20, 0x1A340, 0x335, "F_NO1", "NO1", "rou", 0x00, 0xFF, 0, },
    { 0x9B9F, 0x9C56, 0x3F1EC, 0x9C1F, 0x1C20, 0x19350, 0x335, "F_RNZ1", "RNZ1", "tokex", 0x82, 0xFF, 0, },
    { 0xB86E, 0xB91E, 0x26CCC, 0xB8EE, 0x1420, 0x16750, 0x2FF, "F_RCAT", "RBO8", "gara", 0x43, 0xFF, 0, },
    { 0xB770, 0xB828, 0x223FC, 0xB7F0, 0x1020, 0x1A6D0, 0x2FF, "F_RNO2", "RBO7", "mirra", 0x46, 0xFF, 0, },
    { 0xB64F, 0xB708, 0x336F8, 0xB6CF, 0x1820, 0x1A300, 0x2FF, "F_RCEN", "RBO6", "dora", 0x08, 0xFF, 0, },
    { 0xB4F3, 0xB5A6, 0x53B18, 0xB573, 0x1420, 0x17980, 0x2FF, "F_RNO4", "RBO5", "nalk", 0x4B, 0xFF, 0, },
    { 0xB402, 0xB4A7, 0x25334, 0xB482, 0x1420, 0x10B60, 0x2FF, "F_RNO1", "RBO4", "frank", 0x4F, 0xFF, 0, },
    { 0xB31A, 0xB3C1, 0x1FD40, 0xB39A, 0x1220, 0x11E10, 0x2FF, "F_RDAI", "RBO3", "medyu", 0x53, 0xFF, 0, },
    { 0xB121, 0xB1D6, 0x2DFE8, 0xB1A1, 0x1420, 0x18DE0, 0x2FF, "F_RCHI", "RBO2", "deth", 0x5B, 0xFF, 0, },
    { 0xB027, 0xB0DD, 0x21670, 0xB0A7, 0x1020, 0x193E0, 0x2FF, "F_RNZ0", "RBO1", "verz", 0x60, 0xFF, 0, },
    { 0xAE43, 0xAEE9, 0x26BEC, 0xAEC3, 0x1420, 0x11600, 0x2FF, "F_RARE", "RBO0", "verm", 0x79, 0xFF, 0, },
    { 0x8010, 0x80C9, 0x55554, 0x8090, 0x1A20, 0x1A340, 0x335, "F_NO1", "NO1", "rou", 0x00, 0xFF, 0, },
    { 0x7DA9, 0x7E62, 0x19E94, 0x7E29, 0x1820, 0x1A700, 0x349, "F_MAD", "MAD", "rou", 0x37, 0xFF, 0, },
    { 0x82CD, 0x8386, 0x5744C, 0x834D, 0x1C20, 0x1A3B0, 0x30F, "F_NO3", "NO3", "siro", 0x36, 0xFF, 0, },
    { 0x8010, 0x80C9, 0x55554, 0x8090, 0x1A20, 0x1A340, 0x335, "F_DAI", "DAI", "tou", 0x3D, 0xFF, 0, },
    { 0x7C4A, 0x7CFB, 0x543A0, 0x7CCA, 0x1A20, 0x16250, 0x335, "F_LIB", "LIB", "lib", 0x3E, 0xFF, 0, },
    { 0x8010, 0x80C9, 0x55554, 0x8090, 0x1A20, 0x1A340, 0x335, "F_NO1", "NO1", "tou", 0x3F, 0xFF, 0, },
    { 0x74FE, 0x7597, 0x56228, 0x755E, 0x1A20, 0x1A510, 0x000, "F_SEL", "SEL", "rou", 0x00, 0xFF, 0, },
    { 0x9EB8, 0x9F71, 0x5D520, 0x9F38, 0x1820, 0x1A700, 0x301, "F_NO0", "TE1", "rou", 0x7E, 0xFF, 0, },
    { 0xA02D, 0xA0E6, 0x5F004, 0xA0AD, 0x1820, 0x1A700, 0x303, "F_NO0", "TE2", "rou", 0x7E, 0xFF, 0, },
    { 0xA1A6, 0xA25F, 0x55440, 0xA226, 0x1820, 0x1A700, 0x305, "F_NO0", "TE3", "rou", 0x7E, 0xFF, 0, },
    { 0xA30B, 0xA3C4, 0x595A0, 0xA38B, 0x1820, 0x1A700, 0x307, "F_NO0", "TE4", "rou", 0x7E, 0xFF, 0, },
    { 0xA02D, 0xA0E6, 0x5F004, 0xA0AD, 0x1820, 0x1A700, 0x301, "F_NO0", "TE5", "rou", 0x7E, 0xFF, 0, },
    { 0x956B, 0x95F4, 0x3BA64, 0x95EB, 0x1A20, 0x02100, 0x2FF, "F_TOP", "TOP", "top", 0x2C, 0xFF, 0, },
    { 0xA02D, 0xA0E6, 0x5F004, 0xA0AD, 0x1820, 0x1A700, 0x301, "F_NO0", "TE2", "rou", 0x7E, 0xFF, 0, },
    { 0xA02D, 0xA0E6, 0x5F004, 0xA0AD, 0x1820, 0x1A700, 0x301, "F_NO0", "TE2", "rou", 0x7E, 0xFF, 0, },
    { 0xA02D, 0xA0E6, 0x5F004, 0xA0AD, 0x1820, 0x1A700, 0x301, "F_NO0", "TE2", "rou", 0x7E, 0xFF, 0, },
    { 0xA02D, 0xA0E6, 0x5F004, 0xA0AD, 0x1820, 0x1A700, 0x301, "F_NO0", "TE2", "rou", 0x7E, 0xFF, 0, },
#endif
};
