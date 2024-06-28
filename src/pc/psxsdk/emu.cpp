#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "common.h"
#include "mednafen/spu.h"
#include "mednafen/dma.h"
#include "../../main/psxsdk/libsnd/libsnd_i.h"

PS_SPU* SPU = nullptr;

struct WriteEntry {
   u32 A;
   u16 V;
   std::string file;
   int line;
   int type = 0;
};

std::vector<WriteEntry> writes;

void CheckWrites(char* filename)
{
    std::ifstream infile(filename);
    std::string line;

    if (!infile) {
        std::cerr << "Unable to open file";
        exit(1);
    }

    std::vector<WriteEntry> expected;

    while (std::getline(infile, line)) {
        std::string addressStr, valueStr;

        // Find the position of "Write: "
        size_t pos = line.find("Write: ");
        if (pos != std::string::npos) {
            // Extract the substrings after "Write: "
            std::istringstream iss(line.substr(pos + 7));
            iss >> addressStr >> valueStr;

            // Convert the extracted strings to integers
            u32 address = std::stoul(addressStr, nullptr, 16);
            u16 value = std::stoul(valueStr, nullptr, 16);

            expected.push_back({address, value});
        }
    }

    if(expected.size() != writes.size())
    {
        printf("warning expected size vs. writes size not the same %d vs. %d\n", expected.size(), writes.size());
        exit(1);
    }

    for(int i = 0; i < expected.size(), i < writes.size(); i++)
    {
        if(
            expected[i].A != writes[i].A ||
            expected[i].V != writes[i].V
            )
        {
            printf("mismatch: %d expected %0X %04X != actual %0X %04X %s:%d\n", i, expected[i].A, expected[i].V,
            
             writes[i].A, writes[i].V, writes[i].file.c_str(), writes[i].line);

            exit(1);
        }
        else {
            printf("match: %d %0X %04X\n", i, expected[i].A, expected[i].V);
        }
    }
    infile.close();

    writes.clear();

    printf("OK: %s\n", filename);
}

bool init = false;

extern "C" void mednafen_init()
{
    // MDFN_IEN_PSX::DMA_Init();
    // MDFN_IEN_PSX::DMA_Power();
    SPU = new PS_SPU();
    SPU->Power();
}

extern "C" void write_16(u32 addr, u16 data, char* file, int line)
{
    writes.push_back({addr, data, file, line, 0});
    printf("write16 %08X %04X %s:%d\n", addr, data, file, line);
    if(!init)
    {
        mednafen_init();
        init = true;
    }
    SPU->Write(0, addr, data, file, line);
}

extern "C" u16 read_16(u32 addr, char* file, int line)
{
    if(!init)
    {
        mednafen_init();
        init = true;
    }

    return SPU->Read(0, addr);
}

extern "C" void write_dma(u32 data, char* file, int line)
{
    printf("write_dma %08X %04X %s:%d\n", SPU->RWAddr, data, file, line);
    writes.push_back({SPU->RWAddr, data, file, line, 1});
    SPU->WriteDMA(data);
}

extern "C" s32 _spu_init(s32 arg0);
extern "C" s32 SpuSetReverb(s32);
extern "C" s32 SpuInitMalloc(s32 num, s8* top);

extern "C" s32 _spu_rev_reserve_wa;
extern "C" s32 _spu_rev_offsetaddr;
extern "C" s32 _spu_mem_mode_plus;
typedef struct tagSpuMalloc {
    u32 addr;
    u32 size;
} SPU_MALLOC;

extern "C" SPU_MALLOC* _spu_memList;
extern "C" s32 _SpuIsInAllocateArea_(u32);

#define ASSERT_EQ(value1, value2)                                                           \
    if ((value1) != (value2))                                                               \
    {                                                                                       \
        printf("%d != %d in %s %s:%d\n", value1, value2, __FUNCTION__, __FILE__, __LINE__); \
        exit(1);                                                                            \
    }

void check_spu_set_reverb()
{
    SPU->Power();
    SpuSetReverb(0);
    CheckWrites("./src/pc/psxsdk/expected/SpuSetReverb0.txt");

    SPU->Power();
    // avoid crashing in spuallocatearea
    s8 temp[0x1000] = {0};
    SpuInitMalloc(32, temp);

    ASSERT_EQ(_spu_mem_mode_plus, 3);
    ASSERT_EQ(_spu_rev_reserve_wa, 0);
    ASSERT_EQ(_spu_rev_offsetaddr, 0);
    ASSERT_EQ(_spu_memList[0].addr, 0x40001010);
    ASSERT_EQ(_spu_memList[0].size, 520176);
    ASSERT_EQ(_SpuIsInAllocateArea_(_spu_rev_offsetaddr), 0);

    SpuSetReverb(1);
    CheckWrites("./src/pc/psxsdk/expected/SpuSetReverb1.txt");
}

extern "C" long SpuMallocWithStartAddr(unsigned long addr, long size);

void check_spu_malloc_with_start_addr()
{
    int i;

    SPU->Power();
    s8 temp[0x1000] = {0};
    
    SpuInitMalloc(32, temp);
    SpuMallocWithStartAddr(0x00001010, 0x00010000);

    ASSERT_EQ(_spu_memList[0].addr, 0x00001010);
    ASSERT_EQ(_spu_memList[0].size, 65536);

    ASSERT_EQ(_spu_memList[1].addr, 0x40011010);
    ASSERT_EQ(_spu_memList[1].size, 454640);

    ASSERT_EQ(_spu_memList[2].addr, 0);
    ASSERT_EQ(_spu_memList[2].size, 0);
}

extern "C" s32 _spu_rev_startaddr[];
extern "C" s32 SpuClearReverbWorkArea(s32 rev_mode);
void check_spu_clear_reverb_work_area()
{
    SPU->Power();
    s8 temp[0x1000] = {0};
    SpuInitMalloc(32, temp);
    ASSERT_EQ(_spu_rev_startaddr[0], 0x0000FFFE);
    SpuClearReverbWorkArea(0);
    CheckWrites("./src/pc/psxsdk/expected/SpuClearReverbWorkArea0.txt");
}

void check_spu_set_common_attr()
{
    SPU->Power();

    SpuCommonAttr attr;

    attr.mask = 0xffffffff;
    attr.mvol.left = 1;
    attr.mvol.right = 2;
    attr.mvolmode.left = 1;
    attr.mvolmode.right = 1;
    attr.mvolx.left = 3;
    attr.mvolx.right = 4;
    attr.cd.volume.left = 1;
    attr.cd.volume.right = 2;
    attr.cd.reverb = 0;
    attr.cd.mix = 0;
    attr.ext.volume.left = 2;
    attr.ext.volume.right = 3;
    attr.ext.reverb = 0;
    attr.ext.mix = 0;

    SpuSetCommonAttr(&attr);
    CheckWrites("./src/pc/psxsdk/expected/SpuSetCommonAttr0.txt");

    SPU->Power();

    attr.cd.reverb = 1;
    attr.cd.mix = 1;
    attr.ext.reverb = 1;
    attr.ext.mix = 1;

    SpuSetCommonAttr(&attr);
    CheckWrites("./src/pc/psxsdk/expected/SpuSetCommonAttr1.txt");
}

extern "C" void run_tests()
{
    _spu_init(0);
    CheckWrites("./src/pc/psxsdk/expected/_spu_init.txt");

    check_spu_set_reverb();

    check_spu_malloc_with_start_addr();

    check_spu_clear_reverb_work_area();

    check_spu_set_common_attr();

    exit(0);
}