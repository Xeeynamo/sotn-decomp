#include <game.h>

typedef struct {
    int length;
    void** values;
} EntityDef;

void* g_EntitiesDra[] = {
    (void*)0x8011A4C8, (void*)0x8011AC3C, (void*)0x8011B5A4, (void*)0x8011E0EC,
    (void*)0x80124B88, (void*)0x8011E4BC, (void*)0x8011B334, (void*)0x801315F8,
    (void*)0x801267B0, (void*)0x80126C48, (void*)0x80125330, (void*)0x8011BDA4,
    (void*)0x80128714, (void*)0x8011E0E4, (void*)0x8011EDA0, (void*)0x8011B190,
    (void*)0x8011EDA8, (void*)0x80128C2C, (void*)0x801291C4, (void*)0x80118D0C,
    (void*)0x80127F40, (void*)0x80121980, (void*)0x80125C2C, (void*)0x801262AC,
    (void*)0x8011BBE0, (void*)0x80126ECC, (void*)0x801274DC, (void*)0x80127840,
    (void*)0x801279FC, (void*)0x80127CC8, (void*)0x8011F24C, (void*)0x8011D9F8,
    (void*)0x80120DD0, (void*)0x8011F934, (void*)0x8012231C, (void*)0x8011E390,
    (void*)0x8011B480, (void*)0x80119588, (void*)0x801200AC, (void*)0x80120AF8,
    (void*)0x80125E68, (void*)0x8012A89C, (void*)0x8012A528, (void*)0x8012B990,
    (void*)0x8012B78C, (void*)0x8012768C, (void*)0x80123B40, (void*)0x80119F70,
    (void*)0x80123788, (void*)0x801238CC, (void*)0x80123A60, (void*)0x80119D3C,
    (void*)0x8012BEF8, (void*)0x8011B530, (void*)0x8011F074, (void*)0x80130264,
    (void*)0x8012F894, (void*)0x80130618, (void*)0x801309B4, (void*)0x80130E94,
    (void*)0x8013136C, (void*)0x80129864, (void*)0x8011A4C8, (void*)0x8012A0A4,
    (void*)0x80123F78, (void*)0x801243B0, (void*)0x80124A8C, (void*)0x8011A4C8,
};

void* g_EntitiesNO0[] = {};
void* g_EntitiesNO1[] = {};
void* g_EntitiesLIB[] = {};
void* g_EntitiesCAT[] = {};
void* g_EntitiesNO2[] = {};
void* g_EntitiesCHI[] = {};
void* g_EntitiesDAI[] = {};
void* g_EntitiesNP3[] = {
    (void*)0x801B26FC, (void*)0x801BE768, (void*)0x801BDEF4, (void*)0x801BA608,
    (void*)0x801BB89C, (void*)0x801C119C, (void*)0x801C34E4, (void*)0x801C3D28,
    (void*)0x801C2860, (void*)0x801BE908, (void*)0x801BF1A0, (void*)0x801BFC70,
    (void*)0x801C3878, (void*)0x801BFD98, (void*)0x801BD2E0, (void*)0x801BD2E0,
    (void*)0x801B246C, (void*)0x801B2540, (void*)0x801C03E4, (void*)0x801C070C,
    (void*)0x801C07FC, (void*)0x801B2830, (void*)0x801B28E4, (void*)0x801B39CC,
    (void*)0x801B2C20, (void*)0x801B2F30, (void*)0x801B32A8, (void*)0x801B3704,
    (void*)0x801B3E84, (void*)0x801B4004, (void*)0x801B40F8, (void*)0x801B4558,
    (void*)0x801B4680, (void*)0x801B4940, (void*)0x801B4BE8, (void*)0x801B4D60,
    (void*)0x801B5108, (void*)0x801B5488, (void*)0x801B560C, (void*)0x801B5DE8,
    (void*)0x801B5E98, (void*)0x801B5F60, (void*)0x801B6084, (void*)0x801C424C,
    (void*)0x801C4DCC, (void*)0x801C56D8, (void*)0x801C5BC4, (void*)0x801C5F58,
    (void*)0x801C61B4, (void*)0x801C6564, (void*)0x801C7954, (void*)0x801C7880,
    (void*)0x801C7E18, (void*)0x801C7650, (void*)0x801C8010, (void*)0x801C7D80,
    (void*)0x801C8238, (void*)0x801C8DF0, (void*)0x801C8F54, (void*)0x801C8FEC,
    (void*)0x801C80DC, (void*)0x801C91C4, (void*)0x801C9874, (void*)0x801C997C,
    (void*)0x801B644C, (void*)0x801C9BC8, (void*)0x801C9E28, (void*)0x801CC2E0,
    (void*)0x801CB018, (void*)0x801CD540, (void*)0x801CD620, (void*)0x801CA654,
    (void*)0x801CAE0C, (void*)0x801C9F98, (void*)0x801B5790, (void*)0x801B5C5C,
    (void*)0x801B65FC, (void*)0x801B6990, (void*)0x801B75EC, (void*)0x801B7798,
    (void*)0x801B78BC, (void*)0x801B8CC0, (void*)0x801B8D84, (void*)0x801B8E94,
    (void*)0x801CE69C, (void*)0x801CF254, (void*)0x801CF5B8, (void*)0x801CF94C,
    (void*)0x801D0730, (void*)0x801D0D40, (void*)0x801D1BB8,
};
void* g_EntitiesCEN[] = {
    (void*)0x8018D89C, (void*)0x801964F8, (void*)0x80195C84, (void*)0x80192398,
    (void*)0x8019362C, (void*)0x80198F2C, (void*)0x8019B274, (void*)0x8019BAB8,
    (void*)0x8019A5F0, (void*)0x80196698, (void*)0x80196F30, (void*)0x80197A00,
    (void*)0x8019B608, (void*)0x80197B28, (void*)0x80195070, (void*)0x80195070,
    (void*)0x8018D600, (void*)0x8018D6E0, (void*)0x80198174, (void*)0x8019849C,
    (void*)0x8019858C, (void*)0x8018E7C8, (void*)0x8018F95C, (void*)0x80190374,
    (void*)0x8019007C, (void*)0x80190540, (void*)0x80190A78, (void*)0x80190B64,
};
void* g_EntitiesNO4[] = {};
void* g_EntitiesARE[] = {};
void* g_EntitiesTOP[] = {};
void* g_EntitiesNZ0[] = {
    (void*)0x801B0EEC, (void*)0x801BEB80, (void*)0x801BE30C, (void*)0x801BAA20,
    (void*)0x801BBCB4, (void*)0x801C15B4, (void*)0x801C2AA8, (void*)0x801C32EC,
    (void*)0x801C8CAC, (void*)0x801BED20, (void*)0x801BF5B8, (void*)0x801C0088,
    (void*)0x801C2E3C, (void*)0x801C01B0, (void*)0x801BD6F8, (void*)0x801BD6F8,
    (void*)0x801B0958, (void*)0x801B0AA4, (void*)0x801C07FC, (void*)0x801C0B24,
    (void*)0x801C0C14, (void*)0x801B12E8, (void*)0x801B14C4, (void*)0x801B1770,
    (void*)0x801B1C18, (void*)0x801B1E54, (void*)0x801B20CC, (void*)0x801B23B4,
    (void*)0x801B25C4, (void*)0x801B2874, (void*)0x801B2978, (void*)0x801B2AD8,
    (void*)0x801B2D08, (void*)0x801B19A0, (void*)0x801B11C0, (void*)0x801B2FD8,
    (void*)0x801B3294, (void*)0x801C7958, (void*)0x801C37E4, (void*)0x801C3E94,
    (void*)0x801C45BC, (void*)0x801C4D18, (void*)0x801C5568, (void*)0x801C5D20,
    (void*)0x801C4EAC, (void*)0x801C5FC4, (void*)0x801C6574, (void*)0x801C6494,
    (void*)0x801C672C, (void*)0x801C6B24, (void*)0x801C6C6C, (void*)0x801B3534,
    (void*)0x801B3648, (void*)0x801B3A50, (void*)0x801B37C0, (void*)0x801B3C38,
    (void*)0x801C7048, (void*)0x801C7538, (void*)0x801C7654, (void*)0x801C77B8,
    (void*)0x801C7884, (void*)0x801B3FCC, (void*)0x801B4518, (void*)0x801B4778,
    (void*)0x801B54A8, (void*)0x801B5654, (void*)0x801B5778, (void*)0x801B69E8,
    (void*)0x801B6AAC, (void*)0x801B6BBC, (void*)0x801B7034, (void*)0x801B6DE4,
    (void*)0x801CA160, (void*)0x801C7D68, (void*)0x801B7D58, (void*)0x801B8F94,
    (void*)0x801B8E0C,
};
void* g_EntitiesNZ1[] = {};
void* g_EntitiesWRP[] = {};
void* g_EntitiesDRE[] = {
    (void*)0x80191D00, (void*)0x8019C63C, (void*)0x8019BDC8, (void*)0x801984DC,
    (void*)0x80199770, (void*)0x8019F070, (void*)0x801A13B8, (void*)0x801A1BFC,
    (void*)0x801A0734, (void*)0x8019C7DC, (void*)0x8019D074, (void*)0x8019DB44,
    (void*)0x801A174C, (void*)0x8019DC6C, (void*)0x8019B1B4, (void*)0x8019B1B4,
    (void*)0x80191A64, (void*)0x80191B44, (void*)0x8019E2B8, (void*)0x8019E5E0,
    (void*)0x8019E6D0, (void*)0x801A2F10, (void*)0x801A2E20, (void*)0x80191E34,
    (void*)0x80192104, (void*)0x80193B3C, (void*)0x80193D7C, (void*)0x80193E18,
    (void*)0x80194214, (void*)0x80194488, (void*)0x801946C4, (void*)0x801950F8,
    (void*)0x80196238, (void*)0x8019697C, (void*)0x80196678, (void*)0x80196CC8,
};
void* g_EntitiesBO7[] = {};
void* g_EntitiesMAR[] = {};
void* g_EntitiesBO6[] = {};
void* g_EntitiesBO5[] = {};
void* g_EntitiesBO4[] = {};
void* g_EntitiesBO3[] = {};
void* g_EntitiesBO2[] = {};
void* g_EntitiesBO1[] = {};
void* g_EntitiesBO0[] = {};
void* g_EntitiesST0[] = {
    (void*)0x801A805C, (void*)0x801B6B60, (void*)0x801B6358, (void*)0x801B2A3C,
    (void*)0x801B3CD0, (void*)0x801B89B4, (void*)0x801B9EA8, (void*)0x801BA6EC,
    (void*)0x801B5948, (void*)0x801B6D34, (void*)0x801B5948, (void*)0x801B5948,
    (void*)0x801B5948, (void*)0x801B5948, (void*)0x801B5948, (void*)0x801B5948,
    (void*)0x801A7D64, (void*)0x801A7EB0, (void*)0x801B7BFC, (void*)0x801B7F24,
    (void*)0x801B8014, (void*)0x801A9210, (void*)0x801AA290, (void*)0x801AB5E4,
    (void*)0x801AB0C8, (void*)0x801AC564, (void*)0x801AD530, (void*)0x801AD658,
    (void*)0x801AD430, (void*)0x801AD838, (void*)0x801AD8C0, (void*)0x801ADD60,
    (void*)0x801AEFD8, (void*)0x801AF154, (void*)0x801BD8F0, (void*)0x801BE1B4,
    (void*)0x801BAB08, (void*)0x801A8328, (void*)0x801AABA4, (void*)0x801AA8DC,
    (void*)0x801AACB4, (void*)0x801BB2AC, (void*)0x801AF774, (void*)0x801BB764,
    (void*)0x801BC4D0, (void*)0x801BC5C0,
};
void* g_EntitiesRNO0[] = {};
void* g_EntitiesRNO1[] = {};
void* g_EntitiesRLIB[] = {};
void* g_EntitiesRCAT[] = {};
void* g_EntitiesRNO2[] = {};
void* g_EntitiesRCHI[] = {};
void* g_EntitiesRDAI[] = {};
void* g_EntitiesRNO3[] = {};
void* g_EntitiesRCEN[] = {};
void* g_EntitiesRNO4[] = {};
void* g_EntitiesRARE[] = {};
void* g_EntitiesRTOP[] = {};
void* g_EntitiesRNZ0[] = {};
void* g_EntitiesRNZ1[] = {};
void* g_EntitiesRWRP[] = {};
void* g_EntitiesRBO8[] = {};
void* g_EntitiesRBO7[] = {};
void* g_EntitiesRBO6[] = {};
void* g_EntitiesRBO5[] = {};
void* g_EntitiesRBO4[] = {};
void* g_EntitiesRBO3[] = {};
void* g_EntitiesRBO2[] = {};
void* g_EntitiesRBO1[] = {};
void* g_EntitiesRBO0[] = {};
void* g_EntitiesMAD[] = {
    (void*)0x8018E830, (void*)0x80194218, (void*)0x801939E0, (void*)0x8018FEA0,
    (void*)0x80191120, (void*)0x801964E4, (void*)0x801982BC, (void*)0x80198B00,
    (void*)0x80197B94, (void*)0x801943EC, (void*)0x801949C0, (void*)0x80195520,
    (void*)0x80198650, (void*)0x80192DA8, (void*)0x80192DA8, (void*)0x80192DA8,
    (void*)0x8018E5AC, (void*)0x8018E674, (void*)0x8019572C, (void*)0x80195A54,
    (void*)0x80195B44,
};
void* g_EntitiesNO3[] = {
    (void*)0x801B7A64, (void*)0x801C6EF8, (void*)0x801C6684, (void*)0x801C2D98,
    (void*)0x801C402C, (void*)0x801C992C, (void*)0x801CBC74, (void*)0x801CC4B8,
    (void*)0x801CAFF0, (void*)0x801C7098, (void*)0x801C7930, (void*)0x801C8400,
    (void*)0x801CC008, (void*)0x801C8528, (void*)0x801C5A70, (void*)0x801C5A70,
    (void*)0x801B77D4, (void*)0x801B78A8, (void*)0x801C8B74, (void*)0x801C8E9C,
    (void*)0x801C8F8C, (void*)0x801B7B98, (void*)0x801B7C4C, (void*)0x801B9198,
    (void*)0x801B8254, (void*)0x801B8564, (void*)0x801B8A74, (void*)0x801B8ED0,
    (void*)0x801B9650, (void*)0x801B97D0, (void*)0x801B989C, (void*)0x801B9CE8,
    (void*)0x801B9E10, (void*)0x801BA0A0, (void*)0x801BA348, (void*)0x801BA4C0,
    (void*)0x801BA868, (void*)0x801BABE8, (void*)0x801BAD6C, (void*)0x801BBB8C,
    (void*)0x801BBDC0, (void*)0x801BBE70, (void*)0x801BBF38, (void*)0x801BC05C,
    (void*)0x801CC974, (void*)0x801CE98C, (void*)0x801CED60, (void*)0x801CDD80,
    (void*)0x801CDF10, (void*)0x801CE2F4, (void*)0x801CEF88, (void*)0x801D0B34,
    (void*)0x801D16B4, (void*)0x801D1FC0, (void*)0x801D24AC, (void*)0x801D2840,
    (void*)0x801D2A9C, (void*)0x801D2E4C, (void*)0x801D423C, (void*)0x801D4168,
    (void*)0x801D4700, (void*)0x801D3F38, (void*)0x801D48F8, (void*)0x801D4668,
    (void*)0x801D4B20, (void*)0x801D56D8, (void*)0x801D583C, (void*)0x801D58D4,
    (void*)0x801D49C4, (void*)0x801D5AAC, (void*)0x801D615C, (void*)0x801D6264,
    (void*)0x801BC3FC, (void*)0x801CF740, (void*)0x801D04A4, (void*)0x801D64B0,
    (void*)0x801D6710, (void*)0x801BC4EC, (void*)0x801BC93C, (void*)0x801BCC4C,
    (void*)0x801BCE08, (void*)0x801BD564, (void*)0x801BC780, (void*)0x801BD71C,
    (void*)0x801BDEB0, (void*)0x801BE080, (void*)0x801BEEB0, (void*)0x801BFF00,
    (void*)0x801C033C, (void*)0x801C083C, (void*)0x801C11A4, (void*)0x801BAEF0,
    (void*)0x801BB3BC, (void*)0x801C12E8, (void*)0x801BE134, (void*)0x801BE444,
    (void*)0x801D0624, (void*)0x801C14B8,
};
void* g_EntitiesSEL[] = {};
void* g_EntitiesTE1[] = {};
void* g_EntitiesTE2[] = {};
void* g_EntitiesTE3[] = {};
void* g_EntitiesTE4[] = {};
void* g_EntitiesTE5[] = {};

EntityDef g_DraEntities[] = {
    {ARRAY_COUNT(g_EntitiesDra), g_EntitiesDra},
};
EntityDef g_StageEntities[] = {
    {ARRAY_COUNT(g_EntitiesNO0), g_EntitiesNO0},
    {ARRAY_COUNT(g_EntitiesNO1), g_EntitiesNO1},
    {ARRAY_COUNT(g_EntitiesLIB), g_EntitiesLIB},
    {ARRAY_COUNT(g_EntitiesCAT), g_EntitiesCAT},
    {ARRAY_COUNT(g_EntitiesNO2), g_EntitiesNO2},
    {ARRAY_COUNT(g_EntitiesCHI), g_EntitiesCHI},
    {ARRAY_COUNT(g_EntitiesDAI), g_EntitiesDAI},
    {ARRAY_COUNT(g_EntitiesNP3), g_EntitiesNP3},
    {ARRAY_COUNT(g_EntitiesCEN), g_EntitiesCEN},
    {ARRAY_COUNT(g_EntitiesNO4), g_EntitiesNO4},
    {ARRAY_COUNT(g_EntitiesARE), g_EntitiesARE},
    {ARRAY_COUNT(g_EntitiesTOP), g_EntitiesTOP},
    {ARRAY_COUNT(g_EntitiesNZ0), g_EntitiesNZ0},
    {ARRAY_COUNT(g_EntitiesNZ1), g_EntitiesNZ1},
    {ARRAY_COUNT(g_EntitiesWRP), g_EntitiesWRP},
    {ARRAY_COUNT(g_EntitiesNO1), g_EntitiesNO1},
    {ARRAY_COUNT(g_EntitiesNO0), g_EntitiesNO0},
    {ARRAY_COUNT(g_EntitiesNO1), g_EntitiesNO1},
    {ARRAY_COUNT(g_EntitiesDRE), g_EntitiesDRE},
    {ARRAY_COUNT(g_EntitiesNZ0), g_EntitiesNZ0},
    {ARRAY_COUNT(g_EntitiesNZ1), g_EntitiesNZ1},
    {ARRAY_COUNT(g_EntitiesLIB), g_EntitiesLIB},
    {ARRAY_COUNT(g_EntitiesBO7), g_EntitiesBO7},
    {ARRAY_COUNT(g_EntitiesMAR), g_EntitiesMAR},
    {ARRAY_COUNT(g_EntitiesBO6), g_EntitiesBO6},
    {ARRAY_COUNT(g_EntitiesBO5), g_EntitiesBO5},
    {ARRAY_COUNT(g_EntitiesBO4), g_EntitiesBO4},
    {ARRAY_COUNT(g_EntitiesBO3), g_EntitiesBO3},
    {ARRAY_COUNT(g_EntitiesBO2), g_EntitiesBO2},
    {ARRAY_COUNT(g_EntitiesBO1), g_EntitiesBO1},
    {ARRAY_COUNT(g_EntitiesBO0), g_EntitiesBO0},
    {ARRAY_COUNT(g_EntitiesST0), g_EntitiesST0},
    {ARRAY_COUNT(g_EntitiesRNO0), g_EntitiesRNO0},
    {ARRAY_COUNT(g_EntitiesRNO1), g_EntitiesRNO1},
    {ARRAY_COUNT(g_EntitiesRLIB), g_EntitiesRLIB},
    {ARRAY_COUNT(g_EntitiesRCAT), g_EntitiesRCAT},
    {ARRAY_COUNT(g_EntitiesRNO2), g_EntitiesRNO2},
    {ARRAY_COUNT(g_EntitiesRCHI), g_EntitiesRCHI},
    {ARRAY_COUNT(g_EntitiesRDAI), g_EntitiesRDAI},
    {ARRAY_COUNT(g_EntitiesRNO3), g_EntitiesRNO3},
    {ARRAY_COUNT(g_EntitiesRCEN), g_EntitiesRCEN},
    {ARRAY_COUNT(g_EntitiesRNO4), g_EntitiesRNO4},
    {ARRAY_COUNT(g_EntitiesRARE), g_EntitiesRARE},
    {ARRAY_COUNT(g_EntitiesRTOP), g_EntitiesRTOP},
    {ARRAY_COUNT(g_EntitiesRNZ0), g_EntitiesRNZ0},
    {ARRAY_COUNT(g_EntitiesRNZ1), g_EntitiesRNZ1},
    {ARRAY_COUNT(g_EntitiesRWRP), g_EntitiesRWRP},
    {ARRAY_COUNT(g_EntitiesNO1), g_EntitiesNO1},
    {ARRAY_COUNT(g_EntitiesNO1), g_EntitiesNO1},
    {ARRAY_COUNT(g_EntitiesNO1), g_EntitiesNO1},
    {ARRAY_COUNT(g_EntitiesNO1), g_EntitiesNO1},
    {ARRAY_COUNT(g_EntitiesNO1), g_EntitiesNO1},
    {ARRAY_COUNT(g_EntitiesNO1), g_EntitiesNO1},
    {ARRAY_COUNT(g_EntitiesRNZ1), g_EntitiesRNZ1},
    {ARRAY_COUNT(g_EntitiesRBO8), g_EntitiesRBO8},
    {ARRAY_COUNT(g_EntitiesRBO7), g_EntitiesRBO7},
    {ARRAY_COUNT(g_EntitiesRBO6), g_EntitiesRBO6},
    {ARRAY_COUNT(g_EntitiesRBO5), g_EntitiesRBO5},
    {ARRAY_COUNT(g_EntitiesRBO4), g_EntitiesRBO4},
    {ARRAY_COUNT(g_EntitiesRBO3), g_EntitiesRBO3},
    {ARRAY_COUNT(g_EntitiesRBO2), g_EntitiesRBO2},
    {ARRAY_COUNT(g_EntitiesRBO1), g_EntitiesRBO1},
    {ARRAY_COUNT(g_EntitiesRBO0), g_EntitiesRBO0},
    {ARRAY_COUNT(g_EntitiesNO1), g_EntitiesNO1},
    {ARRAY_COUNT(g_EntitiesMAD), g_EntitiesMAD},
    {ARRAY_COUNT(g_EntitiesNO3), g_EntitiesNO3},
    {ARRAY_COUNT(g_EntitiesDAI), g_EntitiesDAI},
    {ARRAY_COUNT(g_EntitiesLIB), g_EntitiesLIB},
    {ARRAY_COUNT(g_EntitiesNO1), g_EntitiesNO1},
    {ARRAY_COUNT(g_EntitiesSEL), g_EntitiesSEL},
    {ARRAY_COUNT(g_EntitiesTE1), g_EntitiesTE1},
    {ARRAY_COUNT(g_EntitiesTE2), g_EntitiesTE2},
    {ARRAY_COUNT(g_EntitiesTE3), g_EntitiesTE3},
    {ARRAY_COUNT(g_EntitiesTE4), g_EntitiesTE4},
    {ARRAY_COUNT(g_EntitiesTE5), g_EntitiesTE5},
    {ARRAY_COUNT(g_EntitiesTOP), g_EntitiesTOP},
    {ARRAY_COUNT(g_EntitiesTE2), g_EntitiesTE2},
    {ARRAY_COUNT(g_EntitiesTE2), g_EntitiesTE2},
    {ARRAY_COUNT(g_EntitiesTE2), g_EntitiesTE2},
    {ARRAY_COUNT(g_EntitiesTE2), g_EntitiesTE2},
};

void EntitySpawner(void* ptrs);
Entity* AllocEntity(Entity* start, Entity* end);
void DestroyEntity(Entity* item);

int GetEntityAllocationCount() {
    s32 allocated = 0;
    s32 i;

    for (i = 0; i < MaxEntityCount; i++) {
        if (D_8007D858[i].objectId) {
            allocated++;
        }
    }

    return allocated;
}

u8 g_SpawnObjId;
u16 g_SpawnSubId;
void InitEntitySpawn(void) {
    g_SpawnObjId = 0;
    g_SpawnSubId = 0;
}

void UpdateEntitySpawn(int variant) {
    int i;
    EntityDef* def;
    void* entUpdate;

    switch (variant) {
    case 0:
        FntPrint("L2=spawn\n");
        def = &g_DraEntities[0];
        break;
    case 1:
        FntPrint("L2=spawn\n");
        def = &g_StageEntities[g_StageId];
        break;
    }

    if (def == NULL || def->length == 0) {
        FntPrint("no entities");
        return;
    }

    entUpdate = def->values[g_SpawnObjId];

    FntPrint("alloc %d/%d\n", GetEntityAllocationCount(), MaxEntityCount);
    FntPrint("objID %02X\n", g_SpawnObjId + 1);
    FntPrint("subID %02X\n", g_SpawnSubId);
    FntPrint("func  %08X\n", entUpdate);
    if (g_pads->tapped & PAD_LEFT) {
        if (g_SpawnObjId > 0) {
            g_SpawnObjId--;
            g_SpawnSubId = 0;
        }
    } else if (g_pads->tapped & PAD_RIGHT) {
        if (g_SpawnObjId < def->length) {
            g_SpawnObjId++;
            g_SpawnSubId = 0;
        }
    } else if (g_pads->tapped & PAD_UP) {
        g_SpawnSubId--;
    } else if (g_pads->tapped & PAD_DOWN) {
        g_SpawnSubId++;
    }

    if (g_pads->tapped & (PAD_R1 | PAD_L1)) {
        for (i = 0; i < MaxEntityCount; i++) {
            DestroyEntity(&D_8007D858[i]);
        }
    }

    if (g_pads->tapped & PAD_L2 && entUpdate) {
        Entity* e = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
        if (e != NULL) {
            DestroyEntity(e);
            e->objectId = g_SpawnObjId;
            e->pfnUpdate = entUpdate;
            e->subId = g_SpawnSubId;
            e->zPriority = PLAYER.zPriority + 0x20;

            // these coords will spawn the entity at the right side
            // of the camera, a bit far from Alucard.
            e->posX.i.hi = 176;
            e->posY.i.hi = 120;
            e->hitboxWidth = 8;
            e->hitboxHeight = 8;
        }
    }
}

void UpdateDraEntitySpawn() { UpdateEntitySpawn(0); }
void UpdateStageEntitySpawn() { UpdateEntitySpawn(1); }

Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;
    while (current < end) {
        if (current->objectId == 0) {
            return current;
        }

        current++;
    }
    return NULL;
}

void DestroyEntity(Entity* item) {
    s32 i;
    s32 length;
    u32* ptr;

    if (item->flags & 0x800000) {
        g_api.FreePolygons(item->firstPolygonIndex);
    }

    ptr = (u32*)item;
    length = sizeof(Entity) / sizeof(s32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}
