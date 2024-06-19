#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "common.h"
#include "mednafen/spu.h"
#include "mednafen/dma.h"

PS_SPU* SPU = nullptr;

struct WriteEntry {
   u32 A;
   u16 V;
   std::string file;
   int line;
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
    writes.push_back({addr, data, file, line});
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

extern "C" s32 _spu_init(s32 arg0);

extern "C" void run_tests()
{
    _spu_init(0);
    CheckWrites("./src/pc/psxsdk/expected/_spu_init.txt");

    exit(0);
}