#ifndef CSH_H
#define CSH_H

#define CSH_CCR (*(volatile Uint8*)0xfffffe92)

#define CSH_4WAY ((Uint16)0x0000)
#define CSH_2WAY ((Uint16)0x0008)
#define CSH_DISABLE ((Uint16)0x0000)
#define CSH_ENABLE ((Uint16)0x0001)
#define CSH_CODE_ENABLE ((Uint16)0x0000)
#define CSH_CODE_DISABLE ((Uint16)0x0002)
#define CSH_DATA_ENABLE ((Uint16)0x0000)
#define CSH_DATA_DISABLE ((Uint16)0x0004)

#define CSH_GET_CCR() ((Uint16)CSH_CCR)
#define CSH_SET_CCR(sw) ((Uint16)(CSH_CCR = (Uint8)(sw)))
#define CSH_SET_ENABLE(sw)                                                     \
    ((Uint16)(CSH_CCR = (Uint8)((CSH_CCR & 0xfe) | (sw))))
#define CSH_SET_CODE_FILL(sw)                                                  \
    ((Uint16)(CSH_CCR = (Uint8)((CSH_CCR & 0xfd) | (sw))))
#define CSH_SET_DATA_FILL(sw)                                                  \
    ((Uint16)(CSH_CCR = (Uint8)((CSH_CCR & 0xfb) | (sw))))
#define CSH_SET_WAY_MODE(sw)                                                   \
    ((Uint16)(CSH_CCR = (Uint8)((CSH_CCR & 0xf7) | (sw))))
#define CSH_SET_ACS_WAY(way)                                                   \
    ((Uint16)(CSH_CCR = (Uint8)((CSH_CCR & 0x3f) | ((way) << 6))))

void CSH_Init(Uint16);
void CSH_AllClr(void);
void CSH_Purge(void*, Uint32);

#endif
