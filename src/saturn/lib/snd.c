// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"

#include "per.h"
#include "snd.h"

extern Uint8* snd_adr_sys_int_work;

#define ADR_SCSP_REG ((Uint8*)0x25b00400)
#define ADR_SND_MEM ((Uint8*)0x25a00000)
#define ADR_SND_VECTOR ((Uint8*)0x25a00000)
#define ADR_SYS_TBL (ADR_SND_MEM + 0x400)

#define ADR_SYS_INFO (0x00)
#define ADR_HOST_INT (0x04)
#define ADR_ARA_CRNT (0x08)
#define ADR_SYS_INT_WORK (0x12)
#define ADR_HARD_CHK_STAT (0x18)
#define ADR_TIMING_FLAG (0xe0)
#define ADR_CMD_MODE (0xe1)

#define ADR_PRG_ADR (0x00)
#define ADR_PRG_SIZE (0x04)
#define ADR_ARA_ADR (0x08)

#define ADR_COM_DATA (0x00)
#define ADR_PRM_DATA (0x02)
#define ADR_SONG_STAT (0x80)
#define ADR_TL_VL (0x90)
#define ADR_TL_HZ_VL (0x94)
#define ADR_PCM (0xa0)
#define ADR_SEQ (0xb0)

#define SIZE_COM_BLOCK (0x10)
#define MAX_NUM_COM_BLOCK 8

#define SCSP_REG_SET 0x0200
#define MEM_CLR_SIZE 0xb000

#define ARA_MAP_SIZE 0x2

#define ARA_MAP_0 0x0
#define ARA_MAP_4 0x1

#define B_END_MARK 31
#define B_DATA_ID 28
#define B_ID_NUM 24
#define B_START_ADR 0
#define B_LOAD_MARK 31
#define B_AREA_SIZE 0

#define M_END_MARK (0x1 << B_END_MARK)
#define M_DATA_ID (0x7 << B_DATA_ID)
#define M_ID_NUM (0xf << B_ID_NUM)
#define M_START_ADR (0xfffff << B_START_ADR)
#define M_LOAD_MARK (0x1 << B_LOAD_MARK)
#define M_AREA_SIZE (0xfffff << B_AREA_SIZE)

#define COM_START_SEQ 0x01       /* Sequence Start			*/
#define COM_STOP_SEQ 0x02        /* Sequence Stop			*/
#define COM_PAUSE_SEQ 0x03       /* Sequence Pause			*/
#define COM_CONT_SEQ 0x04        /* Sequence Continue		*/
#define COM_SET_SEQ_VL 0x05      /* Sequence Volume			*/
#define COM_CHG_TEMPO 0x07       /* Tempo Change				*/
#define COM_CHG_MAP 0x08         /* map Change				*/
#define COM_CTRL_DIR_MIDI 0x09   /* MIDI direct control		*/
#define COM_START_VL_ANL 0x0a    /* Volume analize start		*/
#define COM_STOP_VL_ANL 0x0b     /* Volume analize stop		*/
#define COM_STOP_DSP 0x0c        /* DSP stop					*/
#define COM_OFF_ALL_SOUND 0x0d   /* Sound all OFF			*/
#define COM_SET_SEQ_PAN 0x0e     /* Sequence PAN				*/
#define COM_INIT_SOUND 0x10      /* Sound Initialize			*/
#define COM_SET_3D_SOUND 0x11    /* 3D sound parameter set	*/
#define COM_SET_QSOUND 0x12      /* Qsound parameter set		*/
#define COM_SET_3D_INIT 0x13     /* 3D sound position init	*/
#define COM_SET_TEMPO_MODE 0x14  /* tempo mode set			*/
#define COM_SET_TEMPO_RATIO 0x15 /* tempo ratio set			*/
#define COM_SET_CD_DA_LEV 0x80   /* CD-DA Level				*/
#define COM_SET_CD_DA_PAN 0x81   /* CD-DA pan				*/
#define COM_SET_TL_VL 0x82       /* Total Volume				*/
#define COM_CHG_EFCT 0x83        /* Effect Change			*/
#define COM_START_PCM 0x85       /* PCM start				*/
#define COM_STOP_PCM 0x86        /* PCM stop					*/
#define COM_CHG_MIX 0x87         /* Mixer change				*/
#define COM_CHG_MIX_PRM 0x88     /* Mixer parameter change	*/
#define COM_CHK_HARD 0x89        /* Hard check				*/
#define COM_CHG_PCM_PRM 0x8a     /* PCM parameter change		*/
#define COM_ALLOC_PCM 0x8b       /* PCM slot allocation		*/
#define COM_REL_PCM 0x8c         /* PCM slot release			*/

#define POKE_B(adr, data) (*((volatile Uint8*)(adr)) = ((Uint8)(data)))
#define POKE_W(adr, data) (*((volatile Uint16*)(adr)) = ((Uint16)(data)))
#define POKE_L(adr, data) (*((volatile Uint32*)(adr)) = ((Uint32)(data)))

#define PEEK_B(adr) (*((volatile Uint8*)(adr)))
#define PEEK_W(adr) (*((volatile Uint16*)(adr)))
#define PEEK_L(adr) (*((volatile Uint32*)(adr)))

#define CHG_LONG(x) (((x) * 2) + (0x4 - (((x) * 2) % 4)))

#define MAX_ADR_COM_DATA                                                       \
    (adr_host_int_work + ADR_COM_DATA + (SIZE_COM_BLOCK * MAX_NUM_COM_BLOCK))
#define NOW_ADR_COM_DATA (adr_com_block + ADR_COM_DATA)

extern Uint32 intrflag;

#define HOST_SET_RETURN(ret)                                                   \
    do {                                                                       \
        intrflag = 0;                                                          \
        return (ret);                                                          \
    } while (0)

#define _WAIT_()                                                               \
    do {                                                                       \
        int i, j;                                                              \
        for (i = 0; i < 32; i++)                                               \
            j = *(volatile int*)0;                                             \
    } while (0)

#define SET_COMMAND(set_com)                                                   \
    (POKE_W((adr_com_block + ADR_COM_DATA), (Uint16)(set_com) << 8))

#define SET_PRM(no, set_prm)                                                   \
    (POKE_B(adr_com_block + ADR_PRM_DATA + (no), (set_prm)))

extern volatile Uint8* adr_sys_info_tbl;
extern volatile Uint8* adr_host_int_work;
extern volatile Uint32* adr_snd_area_crnt;
extern volatile Uint16* adr_song_stat;
extern volatile Uint16* adr_tl_vl;
extern volatile Uint16* adr_tl_hz_vl;
extern volatile Uint16* adr_pcm;
extern volatile Uint16* adr_seq;
extern volatile Uint8* adr_com_block;

void DmaClrZero(void*, Uint32);
Uint16 ChgPan(SndPan);
Uint8 GetComBlockAdr(void);

// func_060186C8
void SND_Init(SndIniDt* sys_ini) {
    PER_SMPC_SND_OFF();
    POKE_W(ADR_SCSP_REG, SCSP_REG_SET);
    DmaClrZero(ADR_SND_MEM, MEM_CLR_SIZE);
    CopyMem(ADR_SND_VECTOR, (void*)(SND_INI_PRG_ADR(*sys_ini)),
            SND_INI_PRG_SZ(*sys_ini));
    adr_sys_info_tbl =
        (Uint8*)(ADR_SND_MEM + PEEK_L(ADR_SYS_TBL + ADR_SYS_INFO));
    adr_host_int_work =
        (Uint8*)(ADR_SND_MEM + PEEK_L(ADR_SYS_TBL + ADR_HOST_INT));
    snd_adr_sys_int_work =
        (Uint8*)(ADR_SND_MEM +
                 ((Uint32)PEEK_W(ADR_SYS_TBL + ADR_SYS_INT_WORK) << 16 |
                  (Uint32)PEEK_W(ADR_SYS_TBL + ADR_SYS_INT_WORK + 2)));
    adr_com_block = adr_host_int_work;
    adr_snd_area_crnt =
        (Uint32*)(ADR_SND_MEM + PEEK_L(ADR_SYS_TBL + ADR_ARA_CRNT));
    adr_song_stat = (Uint16*)(adr_host_int_work + ADR_SONG_STAT);
    adr_pcm = (Uint16*)(adr_host_int_work + ADR_PCM);
    adr_seq = (Uint16*)(adr_host_int_work + ADR_SEQ);
    adr_tl_vl = (Uint16*)(adr_host_int_work + ADR_TL_VL);
    adr_tl_hz_vl = (Uint16*)(adr_host_int_work + ADR_TL_HZ_VL);
    CopyMem((void*)(PEEK_L(adr_sys_info_tbl + ADR_ARA_ADR) + ADR_SND_MEM),
            (void*)(SND_INI_ARA_ADR(*sys_ini)),
            CHG_LONG(SND_INI_ARA_SZ(*sys_ini)));
    intrflag = 0;
    PER_SMPC_SND_ON();
}

// func_06018848
SndRet SND_ChgMap(SndAreaMap area_no) {
    if (intrflag)
        return SND_RET_NSET;
    intrflag = 1;
    if (GetComBlockAdr() == 0)
        HOST_SET_RETURN(SND_RET_NSET);
    SET_PRM(0, area_no);
    SET_COMMAND(COM_CHG_MAP);
    while (PEEK_W(adr_com_block + ADR_COM_DATA))
        _WAIT_();

    if (GetComBlockAdr() == 0)
        HOST_SET_RETURN(SND_RET_NSET);
    SET_PRM(0, area_no);
    SET_COMMAND(COM_CHG_MAP);
    while (PEEK_W(adr_com_block + ADR_COM_DATA))
        _WAIT_();

    HOST_SET_RETURN(SND_RET_SET);
}

// func_06018910
SndRet SND_SetTlVl(SndTlVl vol) {
    if (intrflag)
        return SND_RET_NSET;
    intrflag = 1;
    if (GetComBlockAdr() == 0)
        HOST_SET_RETURN(SND_RET_NSET);
    SET_PRM(0, vol);
    SET_COMMAND(COM_SET_TL_VL);
    HOST_SET_RETURN(SND_RET_SET);
}

// func_0601896C
SndRet SND_ChgMixPrm(SndEfctOut efct_out, SndLev level, SndPan pan) {
    if (intrflag)
        return SND_RET_NSET;
    intrflag = 1;
    if (GetComBlockAdr() == 0)
        HOST_SET_RETURN(SND_RET_NSET);
    SET_PRM(0, efct_out);
    SET_PRM(1, ChgPan(pan) | (level << 5));
    SET_COMMAND(COM_CHG_MIX_PRM);
    HOST_SET_RETURN(SND_RET_SET);
}

// func_060189F0
SndRet SND_StartSeq_DR(SndSeqNum seq_no, SndSeqBnkNum seq_bk_no,
                       SndSeqSongNum song_no, SndSeqPri pri_lev) {
    if (intrflag)
        return SND_RET_NSET;
    intrflag = 1;
    if (GetComBlockAdr() == 0)
        HOST_SET_RETURN(SND_RET_NSET);
    SET_PRM(0, seq_no);
    SET_PRM(1, seq_bk_no);
    SET_PRM(2, song_no);
    SET_PRM(3, pri_lev);
    SET_COMMAND(COM_START_SEQ);
    HOST_SET_RETURN(SND_RET_SET);
}

// func_06018A78
SndRet SND_StopSeq(SndSeqNum seq_no) {
    if (intrflag)
        return SND_RET_NSET;
    intrflag = 1;
    if (GetComBlockAdr() == 0)
        HOST_SET_RETURN(SND_RET_NSET);
    SET_PRM(0, seq_no);
    SET_COMMAND(COM_STOP_SEQ);
    HOST_SET_RETURN(SND_RET_SET);
}

// func_06018AD4
SndRet SND_PauseSeq(SndSeqNum seq_no) {
    if (intrflag)
        return SND_RET_NSET;
    intrflag = 1;
    if (GetComBlockAdr() == 0)
        HOST_SET_RETURN(SND_RET_NSET);
    SET_PRM(0, seq_no);
    SET_COMMAND(COM_PAUSE_SEQ);
    HOST_SET_RETURN(SND_RET_SET);
}

// func_06018B30
SndRet SND_ContSeq(SndSeqNum seq_no) {
    if (intrflag)
        return SND_RET_NSET;
    intrflag = 1;
    if (GetComBlockAdr() == OFF)
        HOST_SET_RETURN(SND_RET_NSET);
    SET_PRM(0, seq_no);
    SET_COMMAND(COM_CONT_SEQ);
    HOST_SET_RETURN(SND_RET_SET);
}

// func_06018B8C
SndRet SND_SetSeqVl(SndSeqNum seq_no, SndSeqVl seq_vl, SndFade fade) {
    if (intrflag)
        return SND_RET_NSET;
    intrflag = 1;
    if (GetComBlockAdr() == 0)
        HOST_SET_RETURN(SND_RET_NSET);
    SET_PRM(0, seq_no);
    SET_PRM(1, seq_vl);
    SET_PRM(2, fade);
    SET_COMMAND(COM_SET_SEQ_VL);
    HOST_SET_RETURN(SND_RET_SET);
}

// func_06018C00
SndRet SND_SetSeqPan(SndSeqNum seq_no, Uint8 ctrl_sw, Uint8 md_pan) {
    if (intrflag)
        return SND_RET_NSET;
    intrflag = 1;
    if (GetComBlockAdr() == 0)
        HOST_SET_RETURN(SND_RET_NSET);
    SET_PRM(0, seq_no);
    SET_PRM(1, (ctrl_sw | md_pan));
    SET_COMMAND(COM_SET_SEQ_PAN);
    HOST_SET_RETURN(SND_RET_SET);
}

// func_06018C74
SndRet SND_StartPcmTL(SndPcmStartPrm* sprm, SndPcmChgPrm* cprm) {
    if (intrflag)
        return SND_RET_NSET;
    intrflag = 1;
    if (GetComBlockAdr() == 0)
        HOST_SET_RETURN(SND_RET_NSET);
    SET_PRM(0, SND_PRM_MODE(*sprm) | SND_PRM_NUM(*cprm));
    SET_PRM(1, (SND_PRM_LEV(*cprm) << 5) | ChgPan(SND_PRM_PAN(*cprm)));
    SET_PRM(2, SND_PRM_SADR(*sprm) >> 8);
    SET_PRM(3, SND_PRM_SADR(*sprm));
    SET_PRM(4, SND_PRM_SIZE(*sprm) >> 8);
    SET_PRM(5, SND_PRM_SIZE(*sprm));
    SET_PRM(6, SND_PRM_PICH(*cprm) >> 8);
    SET_PRM(7, SND_PRM_PICH(*cprm));
    SET_PRM(8, (SND_R_EFCT_IN(*cprm) << 3) | SND_R_EFCT_LEV(*cprm));
    SET_PRM(9, (SND_L_EFCT_IN(*cprm) << 3) | SND_L_EFCT_LEV(*cprm));
    SET_PRM(10, SND_PRM_TL(*cprm));
    SET_PRM(11, 0);
    SET_COMMAND(COM_START_PCM);
    HOST_SET_RETURN(SND_RET_SET);
}

// func_06018D88
SndRet SND_StopPcm2(SndPcmNum pcm_num) {
    if (intrflag)
        return SND_RET_NSET;
    intrflag = 1;
    if (GetComBlockAdr() == 0)
        HOST_SET_RETURN(SND_RET_NSET);
    SET_PRM(0, pcm_num);
    SET_COMMAND(COM_STOP_PCM);
    HOST_SET_RETURN(SND_RET_SET);
}

// func_06018DE4
SndRet SND_ChgPcmTL(SndPcmChgPrm* cprm) {
    if (intrflag)
        return SND_RET_NSET;
    intrflag = 1;
    if (GetComBlockAdr() == 0)
        HOST_SET_RETURN(SND_RET_NSET);
    SET_PRM(0, SND_PRM_NUM(*cprm));
    SET_PRM(1, (SND_PRM_LEV(*cprm) << 5) | ChgPan(SND_PRM_PAN(*cprm)));
    SET_PRM(2, SND_PRM_PICH(*cprm) >> 8);
    SET_PRM(3, SND_PRM_PICH(*cprm));
    SET_PRM(4, (SND_R_EFCT_IN(*cprm) << 3) | SND_R_EFCT_LEV(*cprm));
    SET_PRM(5, (SND_L_EFCT_IN(*cprm) << 3) | SND_L_EFCT_LEV(*cprm));
    SET_PRM(6, SND_PRM_TL(*cprm));
    SET_COMMAND(COM_CHG_PCM_PRM);
    HOST_SET_RETURN(SND_RET_SET);
}

// func_06018EB8
void SND_GetSeqStat(SndSeqStat* status, SndSeqNum seq_no) {
    SND_SEQ_STAT_MODE(*status) = (PEEK_W(adr_song_stat + seq_no)) & 0xff00;
    SND_SEQ_STAT_STAT(*status) = (Uint8)(PEEK_W(adr_song_stat + seq_no));
}

// func_06018EE0
void SND_GetPcmPlayAdr(SndPcmPlayAdr* pcm_adr, SndPcmNum num) {
    SND_PCM_RADR(*pcm_adr) = (Uint8)(PEEK_W(adr_pcm + num) >> 8);
    SND_PCM_LADR(*pcm_adr) = (Uint8)PEEK_W(adr_pcm + num);
}

// func_06018F04
void DmaClrZero(void* dst, Uint32 cnt) { memset(dst, 0x00, cnt); }

// func_06018F20
void GetSndMapInfo(
    void** adr, Uint32** ladr, Uint16 data_kind, Uint16 data_no) {
    Uint32 i;
    Uint32 map0;

    map0 = PEEK_L(adr_snd_area_crnt + ARA_MAP_0);
    for (i = 1; (map0 & M_END_MARK) != M_END_MARK; i++) {
        if ((((map0 & M_DATA_ID) >> B_DATA_ID) == (Uint32)data_kind) &&
            (((map0 & M_ID_NUM) >> B_ID_NUM) == (Uint32)data_no)) {
            *adr = (void*)(ADR_SND_MEM + ((map0 & M_START_ADR) >> B_START_ADR));
            *ladr = (Uint32*)(adr_snd_area_crnt + ARA_MAP_SIZE * (i - 1) +
                              ARA_MAP_4);
            break;
        }
        map0 = PEEK_L(adr_snd_area_crnt + ARA_MAP_SIZE * i + ARA_MAP_0);
    }
}

// func_06018FA8
Uint16 ChgPan(SndPan pan) { return ((pan) < 0) ? (~(pan) + 0x10 + 1) : (pan); }

// func_06018FC4
void CopyMem(void* dst, void* src, Uint32 cnt) { memcpy(dst, src, cnt); }

// func_06018FDC
Uint8 GetComBlockAdr(void) {
    if (*NOW_ADR_COM_DATA) {
        if (adr_com_block >= (MAX_ADR_COM_DATA - SIZE_COM_BLOCK)) {
            return 0;
        } else {
            adr_com_block += SIZE_COM_BLOCK;
            while (NOW_ADR_COM_DATA < (MAX_ADR_COM_DATA - SIZE_COM_BLOCK)) {
                if (*NOW_ADR_COM_DATA) {
                    adr_com_block += SIZE_COM_BLOCK;
                } else {
                    return 1;
                }
            }
            return 0;
        }
    } else {
        adr_com_block = adr_host_int_work;
        while (NOW_ADR_COM_DATA < (MAX_ADR_COM_DATA - SIZE_COM_BLOCK)) {
            if (*NOW_ADR_COM_DATA) {
                adr_com_block += SIZE_COM_BLOCK;
            } else {
                return 1;
            }
        }
        return 0;
    }
}

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6019058, func_06019058);
