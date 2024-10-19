#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "common.h"
#include "mednafen/spu.h"
#include "mednafen/dma.h"
#include "cdc.h"
#include "../../main/psxsdk/libsnd/libsnd_i.h"

// adjust SS_SEQ_TABSIZ in include/psxsdk/libsnd.h accordingly
#ifdef PLATFORM_64BIT
static_assert(sizeof(SeqStruct) == 192, "SS_SEQ_TABSIZ check");
#else
static_assert(sizeof(SeqStruct) == 172, "SS_SEQ_TABSIZ check");
#endif

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
        printf("warning expected size vs. writes size not the same %d vs. %d %s\n", expected.size(), writes.size(), filename);
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
bool test_mode = false;
bool init = false;
extern "C" void MySsInitHot(void);
extern "C" void mednafen_init()
{
    // MDFN_IEN_PSX::DMA_Init();
    // MDFN_IEN_PSX::DMA_Power();
    if(!test_mode)
    {
        MySsInitHot();
    }
    SPU = new PS_SPU();
    SPU->Power();
}


extern "C" void write_16(u32 addr, u16 data, char* file, int line)
{
    if(test_mode)
    {
        writes.push_back({addr, data, file, line, 0});
        printf("write16 %08X %04X %s:%d\n", addr, data, file, line);
    }
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
    writes.push_back({SPU->RWAddr, (u16)data, file, line, 1});
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


void check_set_key()
{
    SpuSetKey(0, 0xFFFFFF);
    CheckWrites("./src/pc/psxsdk/expected/SpuSetKey0.txt");
    SpuSetKey(1, 0xFFFFFF);
    CheckWrites("./src/pc/psxsdk/expected/SpuSetKey1.txt");
}

extern unsigned short _svm_okon1;
extern unsigned short _svm_okon2;
extern unsigned short _svm_okof1;
extern unsigned short _svm_okof2;
extern "C" unsigned short _svm_orev1;
extern "C" unsigned short _svm_orev2;

extern "C" s16 SsUtKeyOnV(s16 voice, s16 vabId, s16 prog, s16 tone, s16 note, s16 fine,
               s16 voll, s16 volr);
extern "C" void SsSetTableSize(char* table, short s_max, short t_max);
void test_spu_vm_do_allocate()
{
    struct thing *svm;
    ProgAtr temp[32] = {0};
    VagAtr vagAtr = {0};
    VabHdr vh = {0};     /* number: 21 */
    ProgAtr pg[16] = {0};    /* number: 22 */
    VagAtr tn[16] = {0}; /* number: 23 */
    s16 result;
    int i;

    char table[512 * 4 * 5] = {0};

    SsSetTableSize(table, 4, 5);

    for (i = 0; i < 16; i++)
    {
        tn[i].vag = 1;
        _svm_vab_pg[i] = &pg[i];
    }

    _svm_cur.field_0x1a = 1;

    _svm_cur.field_18_voice_idx = 1;

    _svm_pg = &temp[0];

    _svm_pg[0].reserved2 = 3;
    _svm_pg[0].reserved3 = 4;

    /*
    We can't link against SpuVmDoAllocate or SpuVmKeyOnNow. Need to test them indirectly
    */

    /*
    configuration for SpuVmVSetUp
    */
    kMaxPrograms = 3;
    _svm_vab_used[0] = 1;
    _svm_vab_used[1] = 1;
    _svm_vab_vh[0] = &vh;

    for (i = 0; i < 16; i++)
    {
        _svm_vab_tn[i] = &tn[i];
    }

    result = SpuVmVSetUp(1, 2);

    /*
    SpuVmSetUp checks
    */
    ASSERT_EQ(result, 0);
    ASSERT_EQ(_svm_cur.field_1_vabId, 1);
    ASSERT_EQ(_svm_cur.field_6_program, 2);

    _svm_tn = &vagAtr;
    _svm_cur.field_C_vag_idx = 1;
    _svm_cur.field_7_fake_program = 1;

    vagAtr.vag = 1;

    result = SsUtKeyOnV(
        2,   /*voice*/
        0,   /*vabId*/
        0,   /*prog*/
        1,   /*tone*/
        30,  /*note*/
        40,  /*fine*/
        64,  /*voll*/
        64); /*volr*/

    ASSERT_EQ(result, 2);

    /*
        SsUtKeyOnV checks
    */
    ASSERT_EQ(_svm_cur.field_2_note, 30);
    ASSERT_EQ(_svm_cur.field_0x3, 40);

    ASSERT_EQ(_svm_cur.field_0x5, 0x40);
    ASSERT_EQ(_svm_cur.field_4_voll, 64);

    /*
    SpuVmDoAllocate checks
    can't check most of the func since _svm_voice, _svm_envx_hist, _svm_sreg_buf and _svm_sreg_dirty are hidden
    */

    ASSERT_EQ(_svm_cur.unk1c.a, 16);
    ASSERT_EQ(_svm_cur.unk1c.b, 1);

    /*
        SpuVmKeyOnNow checks
    */

    ASSERT_EQ(_svm_orev1, 0);
    ASSERT_EQ(_svm_orev2, 0);
    ASSERT_EQ(_svm_okon1, 4);
    ASSERT_EQ(_svm_okon2, 0);
    ASSERT_EQ(_svm_okof1, 0);
    ASSERT_EQ(_svm_okof2, 0);

    /*
    Indirectly check _svm_sreg_buf by flushing
    */

    SpuVmFlush();

    CheckWrites("./src/pc/psxsdk/expected/spu_vm_do_allocate.txt");
}

extern "C" void SsInitHot(void);
extern "C" u8 aPbav[0x3000];
extern "C" s32 g_VabAddrs[];
extern "C" u8 D_8013B6A0[269488];

extern "C" void SsVabClose(s16 vabid);

extern "C" s32 SsVabTransCompleted(short immediateFlag);
extern "C" s32 SsVabOpenHeadSticky(u_char* addr, u_long vabid, u_long sbaddr);

#define SS_IMEDIATE 0

#define LOAD_VAB(vab_id, name, addr, data, dataLen)                            \
    SsVabClose(vab_id);                                                        \
    while (SsVabTransCompleted(SS_IMEDIATE) != 1)                              \
        ;                                                                      \
                                                                               \
    if (SsVabOpenHeadSticky(name, vab_id, addr) < 0) {                         \
        return -1;                                                             \
    }                                                                          \
    if (SsVabTransBodyPartly((u_char*)data, (u_long)dataLen, (u_long)vab_id) < 0) {                     \
        return -1;                                                             \
    }                                                                          \
    while (SsVabTransCompleted(SS_IMEDIATE) != 1)



void SsVabClose(short vab_id);

int load_it()
{
    LOAD_VAB(0, aPbav, g_VabAddrs[0], D_8013B6A0, 269488);

    return 0;
}

extern "C" void ReadToArray(const char* path, char* content, size_t maxlen);
extern "C" s32 _spu_mem_mode_unitM;
extern "C" s32 D_8003355C;
void check_ss_vab_open_head_with_mode()
{
    // SPU->Power();
    s8 temp[0x1000] = {0};
    SpuInitMalloc(32, temp);

    ReadToArray("assets/dra/vh_0.bin", (char*)aPbav, LEN(aPbav));

    SsInitHot();
    SpuMallocWithStartAddr(0x1010, 0x10000);
    ASSERT_EQ(_spu_rev_reserve_wa, 0);
    ASSERT_EQ(_spu_rev_offsetaddr, 65534);
    ASSERT_EQ(_spu_mem_mode_unitM, 7);
    ASSERT_EQ(_spu_mem_mode_plus, 3);
    ASSERT_EQ(D_8003355C, 32);

    ASSERT_EQ(_spu_memList[0].addr, 0x00001010);
    ASSERT_EQ(_spu_memList[1].addr, 0x40011010);
    ASSERT_EQ(_spu_memList[2].addr, 0);

    ASSERT_EQ(_spu_memList[0].size, 65536);
    ASSERT_EQ(_spu_memList[1].size, 454640);
    ASSERT_EQ(_spu_memList[2].size, 0);

    load_it();

    printf("_svm_vab_pg[vabId] %08X diff %d\n", _svm_vab_pg[0], (size_t)_svm_vab_pg[0] - (size_t)aPbav);
    printf("_svm_vab_vh[vabId] %08X diff %d\n", _svm_vab_vh[0], (size_t)_svm_vab_vh[0] - (size_t)aPbav);
    printf("_svm_vab_tn[vabId] %08X diff %d\n", _svm_vab_tn[0], (size_t)_svm_vab_tn[0] - (size_t)aPbav);

    ASSERT_EQ((size_t)_svm_vab_pg[0] - (size_t)aPbav, 32);
    ASSERT_EQ((size_t)_svm_vab_vh[0] - (size_t)aPbav, 0);
    ASSERT_EQ((size_t)_svm_vab_tn[0] - (size_t)aPbav, 2080);

    printf("  _svm_vab_tn[0].prior %08X\n", _svm_vab_tn[0]->prior);

    ASSERT_EQ(_svm_vab_tn[0]->prior, 8);

    ASSERT_EQ(_svm_vab_start[0], 0x00001010);
    ASSERT_EQ(_svm_vab_total[0], 269488);
    ASSERT_EQ(_svm_vab_used[0], 1);

    printf(" _svm_vab_start[0] %08X\n", _svm_vab_start[0]);

    printf("_svm_vab_total[0] %d\n", _svm_vab_total[0]);

    printf("_svm_vab_used[0] %d\n", _svm_vab_used[0]);

    for(int i = 0; i < 32; i++)
    {
        printf("_spu_memList[%d] addr %08X size %d\n", i, _spu_memList[i].addr, _spu_memList[i].size);
    }

    ASSERT_EQ(_spu_memList[0].addr, 0x00001010);
    ASSERT_EQ(_spu_memList[1].addr, 0x40011010);
    ASSERT_EQ(_spu_memList[2].addr, 0);

    ASSERT_EQ(_spu_memList[0].size, 65536);
    ASSERT_EQ(_spu_memList[1].size, 454640);
    ASSERT_EQ(_spu_memList[2].size, 0);
}

void print_memlist()
{
    int i;
    printf("-----------------------------------------\n");
    for (i = 0; i < 5; i++)
    {
        printf("_spu_memList[%d] addr %08X size %d\n", i, _spu_memList[i].addr, _spu_memList[i].size);
    }
}

extern "C" s32 SpuMalloc(s32 size);

void check_spu_malloc()
{
    s8 temp[0x1000] = {0};
    s32 result;
    SpuInitMalloc(32, temp);

    ASSERT_EQ(_spu_memList[0].addr, 0x40001010);
    ASSERT_EQ(_spu_memList[0].size, 520176);
    ASSERT_EQ(_spu_memList[1].addr, 0);
    ASSERT_EQ(_spu_memList[1].size, 0);

    print_memlist();

    SpuMallocWithStartAddr(0x1010, 0x10000);

    print_memlist();

    ASSERT_EQ(_spu_memList[0].addr, 0x00001010);
    ASSERT_EQ(_spu_memList[0].size, 65536);
    ASSERT_EQ(_spu_memList[1].addr, 0x40011010);
    ASSERT_EQ(_spu_memList[1].size, 454640);
    ASSERT_EQ(_spu_memList[2].addr, 0);
    ASSERT_EQ(_spu_memList[2].size, 0);

    result = SpuMalloc(269488);
    ASSERT_EQ(result, 0x11010);

    print_memlist();

    ASSERT_EQ(_spu_memList[0].addr, 0x00001010);
    ASSERT_EQ(_spu_memList[0].size, 65536);
    ASSERT_EQ(_spu_memList[1].addr, 0x00011010);
    ASSERT_EQ(_spu_memList[1].size, 269488);
    ASSERT_EQ(_spu_memList[2].addr, 0x40052CC0);
    ASSERT_EQ(_spu_memList[2].size, 185152);
    ASSERT_EQ(_spu_memList[3].addr, 0);
    ASSERT_EQ(_spu_memList[3].size, 0);
}

extern "C" void run_tests()
{
    test_mode = true;
    _spu_init(0);
    CheckWrites("./src/pc/psxsdk/expected/_spu_init.txt");

    check_spu_set_reverb();

    check_spu_malloc_with_start_addr();

    check_spu_clear_reverb_work_area();

    check_spu_set_common_attr();

    check_set_key();

    test_spu_vm_do_allocate();

    check_ss_vab_open_head_with_mode();

    check_spu_malloc();

    exit(0);
}

double accum = 0;
extern "C" void SsSeqCalledTbyT(void);
#include <string.h>

extern "C" int CdReading();
extern "C" void ExecCd();

extern "C" void SoundRevCallback(void *userdata, u8 *stream, int len)
{
    if(!init)
    {
        printf("not ready\n");
        return;
    }

    for(int i = 0; i < len / 4; i++)
    {
        if (AudioBuffer.ReadPos < AudioBuffer.Size) {
            // ok
        }
        else {
            // generate cd audio
            if(CdReading())
            {
                ExecCd();
            }
        }
        // generate one sample
        SPU->UpdateFromCDC(768);
        if(accum >= 735.735)
        {
         SsSeqCalledTbyT();
         accum -= 735.735;
        }
        accum += 1;
    }

    memcpy(stream, IntermediateBuffer, len);

    if (IntermediateBufferPos >= 1024)
    {
        IntermediateBufferPos = 0;
    }
}