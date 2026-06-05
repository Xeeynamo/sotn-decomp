#ifndef SND_H
#define SND_H

#include "xpt.h"

#define SND_RET_SET 0
#define SND_RET_NSET 1

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

#endif
