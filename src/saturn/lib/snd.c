// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"

#include "snd.h"

#define ADR_COM_DATA (0x00)
#define ADR_PRM_DATA (0x02)
#define ADR_SONG_STAT (0x80)
#define ADR_TL_VL (0x90)
#define ADR_TL_HZ_VL (0x94)
#define ADR_PCM (0xa0)
#define ADR_SEQ (0xb0)

#define SIZE_COM_BLOCK (0x10)
#define MAX_NUM_COM_BLOCK 8

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

#define MAX_ADR_COM_DATA                                                       \
    (adr_host_int_work + ADR_COM_DATA + (SIZE_COM_BLOCK * MAX_NUM_COM_BLOCK))
#define NOW_ADR_COM_DATA (adr_com_block + ADR_COM_DATA)

extern Uint32 intrflag;

#define HOST_SET_RETURN(ret)                                                   \
    do {                                                                       \
        intrflag = 0;                                                          \
        return (ret);                                                          \
    } while (0)

#define SET_COMMAND(set_com)                                                   \
    (POKE_W((adr_com_block + ADR_COM_DATA), (Uint16)(set_com) << 8))

#define SET_PRM(no, set_prm)                                                   \
    (POKE_B(adr_com_block + ADR_PRM_DATA + (no), (set_prm)))

extern volatile Uint8* adr_host_int_work;
extern volatile Uint8* adr_com_block;

Uint8 GetComBlockAdr(void);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60186C8, func_060186C8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018848, func_06018848);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018910, func_06018910);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f601896C, func_0601896C);

// SND_StartSeq_DR
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60189F0, func_060189F0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018A78, func_06018A78);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018AD4, func_06018AD4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018B30, func_06018B30);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018B8C, func_06018B8C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018C00, func_06018C00);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018C74, func_06018C74);

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

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018DE4, func_06018DE4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018EB8, func_06018EB8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018EE0, func_06018EE0);

// func_06018F04
void DmaClrZero(void* dst, Uint32 cnt) { memset(dst, 0x00, cnt); }

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6018F20, func_06018F20);

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
