// SPDX-License-Identifier: AGPL-3.0-only
#ifndef SYS_H
#define SYS_H

#include "xpt.h"

#define SYS_VERSION_STR ("SYS Version 2.50 1997-06-10")
#define SYS_VERSION_LEN (32)

#define SYS_VER_250

#ifndef SYS_VER_250
#define SYS_SETUINT(_Num_, _Hdr_)                                              \
    ((**(volatile void (**)(Uint32, void*))0x6000300)((_Num_), (_Hdr_)))
#define SYS_GETUINT(_Num_)                                                     \
    ((void*)(**(void (*(**)(Uint32))(Uint32))0x6000304)(_Num_))
#else

#define SYS_SETUINT(_Num_, _Hdr_) SYS_SetUintMacSave(_Num_, _Hdr_);
#define SYS_SETUINT_NO_MACSAVE(_Num_, _Hdr_)                                   \
    ((**(volatile void (**)(Uint32, void*))0x6000300)((_Num_), (_Hdr_)))
#define SYS_GETUINT(_Num_) SYS_GetUintMacSave(_Num_);
#define SYS_GETUINT_NO_MACSAVE(_Num_)                                          \
    ((void*)(**(void (*(**)(Uint32))(Uint32))0x6000304)(_Num_))
#endif

#define SYS_SETSINT(_Num_, _Hdr_)                                              \
    ((**(volatile void (**)(Uint32, void*))0x6000310)((_Num_), (_Hdr_)))
#define SYS_GETSINT(_Num_)                                                     \
    ((void*)(**(void (*(**)(Uint32))(Uint32))0x6000314)(_Num_))

#define SYS_TASSEM(_Num_) ((**(volatile Uint32(**)(Uint32))0x6000330)(_Num_))
#define SYS_CLRSEM(_Num_) ((**(volatile void (**)(Uint32))0x6000334)(_Num_))

#define SYS_SETSCUIM(_MaskPat_)                                                \
    ((**(volatile void (**)(Uint32))0x6000340)(_MaskPat_))
#define SYS_CHGSCUIM(_AndMask_, _OrMask_)                                      \
    ((**(volatile void (**)(Uint32, Uint32))0x6000344)((_AndMask_), (_OrMask_)))

#define SYS_GETSCUIM (*(volatile Uint32*)0x6000348)

#define SYS_CHGSYSCK(_CkMode_)                                                 \
    ((**(volatile void (**)(Uint32))0x6000320)(_CkMode_))
#define SYS_GETSYSCK (*(volatile Uint32*)0x6000324)

#define SYS_CHGUIPR(_IprTab_)                                                  \
    ((**(volatile void (**)(Uint32*))0x6000280)(_IprTab_))

#define SYS_EXECDMP (**(volatile void (**)(void))0x600026C)

#define SYS_PCLRMEM (*(volatile Uint8*)0x6000210)

#define SYS_CHKMPEG(_dummy_)                                                   \
    ((**(volatile Sint32(**)(Sint32))0x6000274)(_dummy_))

void SYS_CheckTrack(Sint32 tno);
void SYS_Exit(Sint32 code);
void SYS_SETSCUIM_NR(Uint32 MaskPat);
void SYS_CHGSCUIM_NR(Uint32 AndMask, Uint32 OrMask);

#ifndef SYS_VER_250
#else

typedef void (*interrupt_t)(void);

void SYS_SetUintMacSave(Uint32 Num, interrupt_t Hdr);
interrupt_t SYS_GetUintMacSave(Uint32 Num);

volatile void SYS_GetMac(volatile Uint32* addr_mac);
volatile void SYS_SetMac(volatile Uint32* addr_mac);

volatile Uint32 SYS_GetMach(void);
volatile Uint32 SYS_GetMacl(void);
volatile void SYS_SetMach(volatile Uint32 mach);
volatile void SYS_SetMacl(volatile Uint32 macl);
volatile void SYS_SetMac_hl(volatile Uint32 mach, volatile Uint32 macl);
#endif

#endif
