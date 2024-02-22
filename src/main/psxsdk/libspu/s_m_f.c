#include "common.h"
#include "libspu_internal.h"

extern s32 D_8003355C;

void SpuFree(unsigned long arg0) {
    s32 temp_v1;
    s32 cur_block_num;
    SPU_MALLOC* cur_mem;
    s32 temp;
    s32 mask4;
    s32 block_num;
    u8 pad[2];
    cur_block_num = 0;
    if (temp_v1 = D_8003355C > 0) {
        mask4 = 0x40000000;
        temp = arg0 | 0x80000000;
        block_num = D_8003355C;
        cur_mem = _spu_memList;
        while (true) {
            temp_v1 = cur_mem->addr;
            if (temp_v1 & mask4) {
                break;
            }
            if (temp_v1 == arg0) {
                cur_mem->addr = temp;
                break;
            }
            cur_mem++;
            cur_block_num++;
            if (cur_block_num >= block_num) {
                break;
            }
        }
    }
    func_800286E0();
}
