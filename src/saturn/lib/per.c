#include "sattypes.h"
#include "inc_asm.h"

#include "per.h"

extern Uint8 DAT_06065D30;
extern Uint8 per_hot_res;
extern volatile Uint8 per_set_sys_flg;
extern Uint8* per_get_time_adr;
extern PerGetSys per_get_sys_data;
extern Uint8 per_time_out_flg;

#define IREG0_SYS 0x01
#define IREG0_NSYS 0x00

#define IREG0_CONT (1 << 7)
#define IREG0_BR (1 << 6)

#define IREG1_P1MD_15 0x00
#define IREG1_P1MD_255 (1 << 4)

#define IREG1_P2MD_15 0x00
#define IREG1_P2MD_255 (1 << 6)

#define IREG1_PEN_RET (1 << 3)
#define IREG1_PEN_NRET 0x00

#define IREG1_OPE_ON 0x00
#define IREG1_OPE_OFF (1 << 1)

#define TIME_OUT_MAX 3

#define HOT_RES_MAX 3

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
extern Uint8 now_cont;
extern PerKind intback_kind;
extern Uint8 intback_v_blank;
extern PerNum intback_num;
extern PerSize intback_size;

extern void* intback_work;

extern int get_per_cnt;
extern int v_blank_cnt;
extern void* get_per_adr;
extern void* set_per_adr;
extern void* change_work;

extern Uint8* bdry_work_adr;
extern Uint8 bdry_size;
extern Uint8* get_per_data_adr;
extern Uint8* set_per_data_adr;

extern Uint8 set_time_flg;
extern Uint8 time_data[2][7];
extern Uint8* set_time_adr;

extern PerMulInfo DAT_06057EB8;
extern PerMulInfo DAT_06057EBC;
extern PerMulInfo* DAT_06057EC0;
extern PerMulInfo* DAT_06057EC4;
extern void* DAT_06057EC8;

extern int hot_res_cnt;

extern Uint8* get_oreg_adr;
extern int body_conect_cnt;
extern int DAT_06057ED8;
extern Uint8 end_flg;
extern int remain_conect_cnt;

extern PerSize backup_size;

extern Uint8 get_per_id_flg;
extern Uint8 get_exp_per_size_flg;
extern Uint8 set_bdr_flg;
extern Uint8 get_per_data_flg;
extern Uint8 set_per_data_flg;
extern Uint8 skip_per_data_flg;

static inline void set_sr(u32 sr) { asm volatile("ldc\t%0,sr" : : "r"(sr)); }

static inline u32 get_sr(void) {
    u32 sr;

    asm volatile("stc\tsr,%0" : "=r"(sr));
    return sr;
}

static inline u32 get_imask(void) {
    u32 imask = (get_sr() & 0x000000F0) >> 4;

    return imask;
}

static inline void set_imask(u32 imask) {
    u32 sr = get_sr();

    sr &= ~0x000000F0;
    sr |= (imask << 4);
    set_sr(sr);
}

Uint32 PER_LInit(
    PerKind kind, PerNum num, PerSize size, Uint8* work, Uint8 v_blank) {
    Uint32 msk;

    per_time_out_flg = 0;
    per_hot_res = 0;
    hot_res_cnt = 0;
    intback_ireg[0] = 0;
    intback_ireg[1] = 0;
    intback_ireg[2] = -0x10;
    PER_PokeByte(0x20100079, 0);
    PER_PokeByte(0x2010007B, 0);
    PER_PokeByte(0x2010007F, 0);
    PER_PokeByte(0x2010007D, 0);
    intback_kind = kind;
    switch (intback_kind) {
    case PER_KD_SYS:
        intback_ireg[0] = IREG0_SYS;
        intback_ireg[1] = IREG1_PEN_NRET;
        per_set_sys_flg = OFF;
        msk = get_imask();
        set_imask(15);
        SYS_SETUINT_NO_MACSAVE(INT_SCU_SYS, PER_IntFunc);
        INT_ChgMsk(INT_MSK_SYS, INT_MSK_NULL);
        end_flg = 0;
        set_imask(msk);
        return GoIntBack();

    case PER_KD_PER:
        intback_ireg[0] = IREG0_NSYS;
        intback_ireg[1] = IREG1_PEN_RET | IREG1_OPE_ON;
        break;

    case PER_KD_PERTIM:
        intback_ireg[0] = IREG0_SYS;
        intback_ireg[1] = IREG1_PEN_RET | IREG1_OPE_ON;
        set_time_flg = OFF;
        break;
    }

    intback_size = size;
    intback_num = num;
    intback_v_blank = v_blank;
    intback_work = (void*)work;
    v_blank_cnt = 0;

    if (intback_size <= 15) {
        intback_ireg[1] |= IREG1_P1MD_15 | IREG1_P2MD_15;
    } else {
        intback_ireg[1] |= IREG1_P1MD_255 | IREG1_P2MD_255;
    }
    set_time_adr = time_data[0];
    per_get_time_adr = time_data[1];

    DAT_06057EC4 = &DAT_06057EB8;
    DAT_06057EC0 = &DAT_06057EBC;
    do {
        DAT_06057EC0[0].id = PER_MID_NCON_ONE;
        DAT_06057EC0[0].con = PER_MCON_NCON_UNKNOWN;
        DAT_06057EC0[1].id = PER_MID_NCON_ONE;
        DAT_06057EC0[1].con = PER_MCON_NCON_UNKNOWN;
    } while (FALSE);

    get_per_adr = intback_work;
    set_per_adr = (Uint8*)intback_work + intback_num * (intback_size + 2);
    bdry_work_adr = (Uint8*)intback_work + intback_num * (intback_size + 2) * 2;
    DAT_06065D30 = 0;
    InitIntBackPer();
    msk = get_imask();
    set_imask(15);
    SYS_SETUINT_NO_MACSAVE(INT_SCU_SYS, PER_IntFunc);
    INT_ChgMsk(INT_MSK_SYS, INT_MSK_NULL);
    end_flg = 0;
    set_imask(msk);
    return GoIntBack();
}

Uint32 PER_LGetPer(PerGetPer** output_dt, PerMulInfo** mul_info) {
    if ((intback_kind != PER_KD_PER) && (intback_kind != PER_KD_PERTIM)) {
        *output_dt = NULL;
        return PER_INT_ERR;
    }
    if ((*PER_REG_SR & 0x10) == 0x10) {
        hot_res_cnt++;
        if (hot_res_cnt >= HOT_RES_MAX) {
            per_hot_res = PER_HOT_RES_ON;
            hot_res_cnt--;
        }
    } else {
        per_hot_res = PER_HOT_RES_OFF;
        hot_res_cnt = 0;
    }
    if (v_blank_cnt < intback_v_blank) {
        v_blank_cnt++;
        return PER_INT_OK;
    }
    v_blank_cnt = 0;
    if ((get_per_cnt == 0) || (end_flg == END_CONT) || (end_flg == 3)) {
        if (end_flg != 4) {
            end_flg = 4;
        } else {
            end_flg = END_END;
        }
        if (end_flg == END_END) {
            per_time_out_flg++;
        }
        if (per_time_out_flg >= TIME_OUT_MAX) {
            if (get_exp_per_size_flg == ON) {
                SetPerSize(PER_SIZE_NCON_15);
            }
            if (remain_conect_cnt > 0) {
                body_conect_cnt++;
            }
            AnyInitPerData();
            while (body_conect_cnt < 2) {
                do {
                    DAT_06057EC4[body_conect_cnt].id = PER_MID_NCON_ONE;
                    DAT_06057EC4[body_conect_cnt].con = PER_MCON_NCON_UNKNOWN;
                } while (FALSE);
                body_conect_cnt++;
            }
            per_time_out_flg--;
        } else {
            func_0602CF8C();
        }
    } else {
        if (end_flg != 4) {
            per_time_out_flg = 0;
        }
        end_flg = END_END;
    }
    if (set_time_flg == ON) {
        DAT_06065D30 = 1;
        change_work = set_time_adr;
        set_time_adr = per_get_time_adr;
        per_get_time_adr = change_work;
    } else {
        DAT_06065D30 = 0;
    }
    DAT_06057EC8 = DAT_06057EC4;
    DAT_06057EC4 = DAT_06057EC0;
    DAT_06057EC0 = DAT_06057EC8;
    change_work = set_per_adr;
    set_per_adr = get_per_adr;
    get_per_adr = change_work;
    *output_dt = (PerGetPer*)get_per_adr;
    *mul_info = DAT_06057EC0;
    InitIntBackPer();
    return GoIntBack();
}

// PER_IntFunc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602C214, PER_IntFunc);

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

static void InitIntBackPer(void) {
    get_per_id_flg = ON;
    get_exp_per_size_flg = OFF;
    set_bdr_flg = OFF;
    get_per_data_flg = OFF;
    set_per_data_flg = OFF;
    skip_per_data_flg = OFF;
    set_time_flg = OFF;
    get_per_cnt = 0;
    body_conect_cnt = 0;
    DAT_06057ED8 = 0;
    remain_conect_cnt = 0;
    now_cont = 0;
    do {
        DAT_06057EC4[0].id = PER_MID_NCON_ONE;
        DAT_06057EC4[0].con = PER_MCON_NCON_UNKNOWN;
        DAT_06057EC4[1].id = PER_MID_NCON_ONE;
        DAT_06057EC4[1].con = PER_MCON_NCON_UNKNOWN;
    } while (FALSE);
}

static Uint32 GoIntBack(void) {
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
