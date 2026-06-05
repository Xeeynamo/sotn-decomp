#ifndef PER_H
#define PER_H

#include "xpt.h"

#define PER_REG_COMREG ((volatile Uint8*)0x2010001F)
#define PER_REG_SR ((volatile Uint8*)0x20100061)
#define PER_REG_SF ((volatile Uint8*)0x20100063)
#define PER_REG_IREG ((volatile Uint8*)0x20100001)
#define PER_REG_OREG ((volatile Uint8*)0x20100021)

#define PER_B_SF 0x1

#define PER_PokeByte(address, data)                                            \
    (*(volatile Uint8*)(address) = (Uint8)(data))
#define PER_PeekByte(address) (*(volatile Uint8*)(address))

#define PER_ID_NCON_UNKNOWN 0xf0
#define PER_ID_DGT 0x00
#define PER_ID_ANL 0x10
#define PER_ID_PNT 0x20
#define PER_ID_KBD 0x30
#define PER_ID_MD 0xe0

#define PER_SIZE_NCON_15 0x0f
#define PER_SIZE_DGT 2
#define PER_SIZE_PNT 3
#define PER_SIZE_KBD 4
#define PER_SIZE_M3BP 1
#define PER_SIZE_M6BP 2
#define PER_SIZE_ANL 5

#define PER_INT_OK 0x0
#define PER_INT_ERR 0x1

typedef Uint8 PerId;
typedef Uint8 PerSize;
typedef Uint8 PerKind;
typedef Uint16 PerNum;
typedef Uint8 PerMulId;
typedef Uint8 PerMulCon;

#define PER_SM_MSHON 0x00
#define PER_SM_SSHON 0x02
#define PER_SM_SSHOFF 0x03
#define PER_SM_SNDON 0x06
#define PER_SM_SNDOFF 0x07
#define PER_SM_CDON 0x08
#define PER_SM_CDOFF 0x09
#define PER_SM_SYSRES 0x0d
#define PER_SM_NMIREQ 0x18
#define PER_SM_RESENA 0x19
#define PER_SM_RESDIS 0x1a
#define PER_SM_SETSM 0x17
#define PER_SM_SETTIM 0x16

#define PER_SMPC_WAIT()                                                        \
    do {                                                                       \
        while ((PER_PeekByte(PER_REG_SF) & PER_B_SF) == PER_B_SF)              \
            ;                                                                  \
        PER_PokeByte(PER_REG_SF, PER_B_SF);                                    \
    } while (0)

#define PER_SMPC_GO_CMD(smpc_cmd)                                              \
    do {                                                                       \
        PER_PokeByte(PER_REG_COMREG, smpc_cmd);                                \
        while (PER_PeekByte(PER_REG_SF) & PER_B_SF)                            \
            ;                                                                  \
    } while (0)

#define PER_SMPC_NO_IREG(com)                                                  \
    do {                                                                       \
        PER_SMPC_WAIT();                                                       \
        PER_SMPC_GO_CMD(com);                                                  \
    } while (0)

#define PER_SMPC_SND_ON()                                                      \
    do {                                                                       \
        PER_SMPC_NO_IREG(PER_SM_SNDON);                                        \
    } while (FALSE)

#define PER_SMPC_SND_OFF()                                                     \
    do {                                                                       \
        PER_SMPC_NO_IREG(PER_SM_SNDOFF);                                       \
    } while (0)

#endif
