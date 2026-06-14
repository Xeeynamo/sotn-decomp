#include "sattypes.h"
#include "inc_asm.h"

#include "per.h"

#define END_END 0
#define END_BREAK 1
#define END_CONT 2

#define BODY_CONECT_MAX 2
#define OREG_MAX 32
#define REG_OREG_MAX (PER_REG_OREG + OREG_MAX * 2)

#define BDRY_OREG 2
#define BDRY_WORK 1

#define SM_INTBACK 0x10

#define GET_PER_DATA(data) (*(get_per_data_adr + (data) * bdry_size))
#define ARY_REG_IREG(data) (*(PER_REG_IREG + (data) * 2))

extern Uint8 intback_ireg[3];

extern PerNum intback_num;
extern PerSize intback_size;

extern void* set_per_adr;

extern Uint8* bdry_work_adr;
extern Uint8 bdry_size;
extern Uint8* get_per_data_adr;
extern Uint8* set_per_data_adr;

extern int get_per_cnt;

extern Uint8* get_oreg_adr;

extern Uint8 end_flg;
extern int remain_conect_cnt;

extern PerSize backup_size;

// PER_Init
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602BB98, func_0602BB98);

// PER_GetPer
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602BF40, func_0602BF40);

// PER_IntFunc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602C214, func_0602C214);

void JudgeGetPerNum(void) {
    if (get_per_cnt >= intback_num) {
        end_flg = END_BREAK;
    }
}

void JudgeOreg(void) {
    if (get_oreg_adr >= REG_OREG_MAX) {
        if ((*PER_REG_SR & 0x20) == 0x20) {
            end_flg = END_CONT;
        }
    }
}

void MoveBdryData(Uint8* adr_max) {
    get_per_data_adr = bdry_work_adr;
    set_per_data_adr = bdry_work_adr;
    bdry_size = BDRY_WORK;
    while (get_oreg_adr < adr_max) {
        *set_per_data_adr = *get_oreg_adr;
        set_per_data_adr++;
        get_oreg_adr += 2;
    }
}

void SetPerData(void) {
    Uint32 i;

    for (i = 0; i < backup_size; i++) {
        *((Uint8*)set_per_adr + get_per_cnt * (intback_size + 2) + 2 + i) =
            GET_PER_DATA(i);
    }
}

// InitIntBackPer
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CD44, func_0602CD44);

Uint32 GoIntBack(void) {
    if (end_flg == 4) {
        return PER_INT_ERR;
    }
    end_flg = 3;
    if ((PER_PeekByte(PER_REG_SF) & PER_B_SF) == PER_B_SF) {
        return PER_INT_ERR;
    }
    PER_PokeByte(PER_REG_SF, PER_B_SF);

    ARY_REG_IREG(0) = intback_ireg[0];
    ARY_REG_IREG(1) = intback_ireg[1];
    ARY_REG_IREG(2) = intback_ireg[2];

    PER_PokeByte(PER_REG_COMREG, SM_INTBACK);
    end_flg = END_CONT;
    return PER_INT_OK;
}

void AnyInitPerData(void) {
    while (remain_conect_cnt > 0 && get_per_cnt < intback_num) {
        SetPerId(PER_ID_NCON_UNKNOWN);
        SetPerSize(PER_SIZE_NCON_15);
        remain_conect_cnt--;
        get_per_cnt++;
    }
}

void SetPerId(PerId id) {
    *((Uint8*)set_per_adr + get_per_cnt * (intback_size + 2)) = id;
}

void SetPerSize(PerSize size) {
    *((Uint8*)set_per_adr + get_per_cnt * (intback_size + 2) + 1) = size;
}

// MoveOldToNew
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CF8C, func_0602CF8C);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602D008, func_0602D008);

INCLUDE_ASM("asm/saturn/zero/data", d602D3F4, d_0602D3F4);
