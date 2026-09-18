#include "sattypes.h"
#include "inc_asm.h"

#include "bup.h"

// SEGA_BUP.A
const char* bup_version = "BUP Version 1.25 1997-06-20";
const u32 pad_06030400 = 0x00000000;

extern Sint32 DAT_06057F04;
extern void* DAT_06065D50;
extern void* DAT_06065D54;
void func_06030580(void);

static inline void set_sr(register Uint32 sr) {
    __asm__ volatile("ldc	%0, sr" : : "r"(sr));
}

static inline Uint32 get_sr(void) {
    Uint32 sr;
    __asm__ volatile("stc	sr, %0" : "=r"(sr));
    return sr;
}

static inline Uint32 get_imask(void) {
    Uint32 imask = (get_sr() & 0x000000F0) >> 4;
    return imask;
}

static inline void set_imask(register Uint32 imask) {
    Uint32 sr = get_sr();

    sr &= ~0x000000F0;
    sr |= imask << 4;
    set_sr(sr);
}

// 0x06030404
void BUP_Init(Uint32* libaddr, Uint32* workbuff, BupConfig conf[]) {
    Uint32 msk;

    DAT_06057F04 = 0;
    msk = preProc();
    BUP_HK_INIT(libaddr, workbuff, conf);
    postProc(msk);
    if (isConSeri()) {
        conf[2].unit_id = 3;
    }
    return;
}

// 0x06030478
Uint32 preProc(void) {
    Uint32 msk;

    msk = get_imask();
    set_imask(15);
    if (DAT_06057F04++ == 0) {
        change_dfunc();
    }
    return msk;
}

// 0x060304CC
void postProc(Uint32 msk) {
    if (--DAT_06057F04 == 0) {
        return_dfunc();
    }
    set_imask(msk);
    return;
}

// 0x06030518
void change_dfunc(void) {
    DAT_06065D54 = (*(Uint32*)(0x06000340));
    (*(Uint32*)(0x06000340)) = &func_06030580;
    DAT_06065D50 = (*(Uint32*)(0x06000344));
    (*(Uint32*)(0x06000344)) = &func_06030580;
}

// 0x06030554
void return_dfunc(void) {
    (*(Uint32*)(0x06000340)) = DAT_06065D54;
    (*(Uint32*)(0x06000344)) = DAT_06065D50;
}

void func_06030580(void) {}

// 0x0603058C
Sint32 isConSeri(void) {
    Sint32 status;
    BupStat stat;

    status = BUP_Stat(2, 0, &stat);
    if (status == BUP_NON) {
        return FALSE;
    }
    return TRUE;
}

// 0x060305CC
Sint32 BUP_SelPart(Uint32 device, Uint16 num) {
    Sint32 status;
    Uint32 msk;

    msk = preProc();
    status = BUP_HK_SELPART(device, num);
    postProc(msk);
    return status;
}

// 0x06030640
Sint32 BUP_Format(Uint32 device) {
    Sint32 status;
    Uint32 msk;

    msk = preProc();
    status = BUP_HK_FORMAT(device);
    postProc(msk);
    return status;
}

// 0x06030690
Sint32 BUP_Stat(Uint32 device, Uint32 datasize, BupStat* stat) {
    Sint32 status;
    Uint32 msk;

    msk = preProc();
    status = BUP_HK_STAT(device, datasize, stat);
    postProc(msk);
    return status;
}

// 0x060306EC
Sint32 BUP_Write(Uint32 device, BupDir* dir, Uint8* data, Uint8 owsw) {
    Sint32 status;
    Uint32 msk;

    msk = preProc();
    status = BUP_HK_WRITE(device, dir, data, owsw);
    postProc(msk);
    return status;
}

// 0x06030768
Sint32 BUP_Read(Uint32 device, Uint8* fname, Uint8* data) {
    Sint32 status;
    Uint32 msk;

    msk = preProc();
    status = BUP_HK_READ(device, fname, data);
    postProc(msk);
    return status;
}

// 0x060307C4
Sint32 BUP_Delete(Uint32 device, Uint8* fname) {
    Sint32 status;
    Uint32 msk;

    msk = preProc();
    status = BUP_HK_DELETE(device, fname);
    postProc(msk);
    return status;
}

// 0x0603081C
Sint32 BUP_Dir(Uint32 device, Uint8* fname, Uint16 dirsize, BupDir* dir) {
    Sint32 status;
    Uint32 msk;

    msk = preProc();
    status = BUP_HK_DIR(device, fname, dirsize, dir);
    postProc(msk);
    return status;
}

// 0x06030898
Sint32 BUP_Verify(Uint32 device, Uint8* fname, Uint8* data) {
    Sint32 status;
    Uint32 msk;

    msk = preProc();
    status = BUP_HK_VERIFY(device, fname, data);
    postProc(msk);
    return status;
}

// 0x060308F4
void BUP_GetDate(Uint32 pdate, BupDate* date) {
    BUP_HK_GETDATE(pdate, date);
    if (date->month == 12 && date->day == 32) {
        date->year++;
        date->month = 1;
        date->day = 1;
    }
    return;
}

// 0x06030968
Uint32 BUP_SetDate(BupDate* date) {
    Uint32 status;

    status = BUP_HK_SETDATE(date);
    return status;
}
