#ifndef SND_H
#define SND_H

#include "xpt.h"

#define SND_RET_SET 0
#define SND_RET_NSET 1

#define SND_CTRL_OUTPUT_STEREO (0 << 7)
#define SND_CTRL_OUTPUT_MONO (1 << 7)

#define SND_MD_MONO (0 << 7)
#define SND_MD_STEREO (1 << 7)
#define SND_MD_16 (0 << 4)
#define SND_MD_8 (1 << 4)

#define SND_INI_PRG_ADR(sys_ini) ((sys_ini).prg_adr)
#define SND_INI_PRG_SZ(sys_ini) ((sys_ini).prg_sz)
#define SND_INI_ARA_ADR(sys_ini) ((sys_ini).ara_adr)
#define SND_INI_ARA_SZ(sys_ini) ((sys_ini).ara_sz)

#define SND_SEQ_STAT_MODE(status) ((status).mode)
#define SND_SEQ_STAT_STAT(status) ((status).stat)

#define SND_PRM_MODE(prm) ((prm).mode)
#define SND_PRM_SADR(prm) ((prm).sadr)
#define SND_PRM_SIZE(prm) ((prm).size)
#define SND_PRM_OFSET(prm) ((prm).ofset)

#define SND_PRM_NUM(prm) ((prm).num)
#define SND_PRM_LEV(prm) ((prm).lev)
#define SND_PRM_PAN(prm) ((prm).pan)
#define SND_PRM_PICH(prm) ((prm).pich)
#define SND_R_EFCT_IN(prm) ((prm).r_efct_in)
#define SND_R_EFCT_LEV(prm) ((prm).r_efct_lev)
#define SND_L_EFCT_IN(prm) ((prm).l_efct_in)
#define SND_L_EFCT_LEV(prm) ((prm).l_efct_lev)
#define SND_PRM_TL(prm) ((prm).t_lev)

#define SND_PCM_RADR(prm) ((prm).radr)
#define SND_PCM_LADR(prm) ((prm).ladr)

#define SND_POKE_B(adr, data) (*((volatile Uint8*)(adr)) = ((Uint8)(data)))
#define SND_POKE_W(adr, data) (*((volatile Uint16*)(adr)) = ((Uint16)(data)))
#define SND_PEEK_B(adr) (*((volatile Uint8*)(adr)))

#define SND_ADR_INTR_CTRL_WORD (0x00)
#define SND_ADR_INTR_MODE (0x01)
#define SND_ADR_PCM_PLAY_NUM (0x02)
#define SND_ADR_SND_CTRL (0x03)
#define SND_CMD_TIMING_FLAG (0x60)
#define SND_CMD_SEQ_CTRL_WORD (0x61)

#define SND_SET_SND_CTRL(ctrl_bit)                                             \
    do {                                                                       \
        SND_POKE_B(snd_adr_sys_int_work + SND_ADR_SND_CTRL, (ctrl_bit));       \
    } while (FALSE)

typedef struct {
    Uint16* prg_adr;
    Uint16 prg_sz;
    Uint16* ara_adr;
    Uint16 ara_sz;
} SndIniDt;

typedef Uint8 SndAreaMap;
typedef Uint8 SndTlVl;
typedef Uint8 SndEfctBnkNum;
typedef Uint8 SndToneBnkNum;
typedef Uint8 SndMixBnkNum;
typedef Uint8 SndEfctOut;
typedef Uint8 SndLev;
typedef Sint8 SndPan;
typedef Uint8 SndRet;
typedef Uint8 SndHardPrm;
typedef Uint16 SndHardStat;

typedef Uint8 SndSeqNum;
typedef Uint8 SndSeqBnkNum;
typedef Uint8 SndSeqSongNum;
typedef Uint8 SndSeqPri;
typedef Uint8 SndSeqVl;
typedef Uint8 SndFade;
typedef Sint16 SndTempo;

typedef struct {
    Uint16 mode;
    Uint8 stat;
} SndSeqStat;

typedef struct {
    Uint8 mode;
    Uint16 sadr;
    Uint16 size;
} SndPcmStartPrm;

typedef Uint8 SndPcmNum;
typedef Uint8 SndEfctIn;
typedef struct {
    SndPcmNum num;
    SndLev lev;
    SndPan pan;
    Uint16 pich;
    SndEfctIn r_efct_in;
    SndLev r_efct_lev;
    SndEfctIn l_efct_in;
    SndLev l_efct_lev;
    SndLev t_lev;
} SndPcmChgPrm;

typedef struct {
    Uint8 radr;
    Uint8 ladr;
} SndPcmPlayAdr;

extern Uint8* snd_adr_sys_int_work;

SndRet SND_ChgMixPrm(SndEfctOut, SndLev, SndPan);

SndRet SND_StartSeq_DR(SndSeqNum, SndSeqBnkNum, SndSeqSongNum, SndSeqPri);
SndRet SND_StopSeq(SndSeqNum);

SndRet SND_SetSeqVl(SndSeqNum, SndSeqVl, SndFade);

SndRet SND_SetSeqPan(SndSeqNum, Uint8, Uint8);

void SND_GetPcmPlayAdr(SndPcmPlayAdr*, SndPcmNum);

#endif
