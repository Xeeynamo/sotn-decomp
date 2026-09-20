#ifndef BUP_H
#define BUP_H

#include "xpt.h"

#define BUP_LIB_ADDRESS (*(Uint32*)(0x6000350 + 8))

#define BUP_VECTOR_ADDRESS (*(Uint32*)(0x6000350 + 4))

#define BUP_NON (1)
#define BUP_UNFORMAT (2)
#define BUP_WRITE_PROTECT (3)
#define BUP_NOT_ENOUGH_MEMORY (4)
#define BUP_NOT_FOUND (5)
#define BUP_FOUND (6)
#define BUP_NO_MATCH (7)
#define BUP_BROKEN (8)

#define BUP_HK_INIT(libaddr, workbuff, conf)                                   \
    (*(BupFnInit)(BUP_LIB_ADDRESS))(libaddr, workbuff, conf)

#define BUP_HK_SELPART(device, num)                                            \
    (**(BupFnSelPart)(BUP_VECTOR_ADDRESS + 4))(device, num)

#define BUP_HK_FORMAT(device) (**(BupFnFormat)(BUP_VECTOR_ADDRESS + 8))(device)

#define BUP_HK_STAT(device, datasize, stat)                                    \
    (**(BupFnStat)(BUP_VECTOR_ADDRESS + 12))(device, datasize, stat)

#define BUP_HK_WRITE(device, dir, data, owsw)                                  \
    (**(BupFnWrite)(BUP_VECTOR_ADDRESS + 16))(device, dir, data, owsw)

#define BUP_HK_READ(device, fname, data)                                       \
    (**(BupFnRead)(BUP_VECTOR_ADDRESS + 20))(device, fname, data)

#define BUP_HK_DELETE(device, fname)                                           \
    (**(BupFnDelete)(BUP_VECTOR_ADDRESS + 24))(device, fname)

#define BUP_HK_DIR(device, fname, dirsize, dir)                                \
    (**(BupFnDir)(BUP_VECTOR_ADDRESS + 28))(device, fname, dirsize, dir)

#define BUP_HK_VERIFY(device, fname, data)                                     \
    (**(BupFnVerify)(BUP_VECTOR_ADDRESS + 32))(device, fname, data)

#define BUP_HK_GETDATE(pdate, date)                                            \
    (**(BupFnGetDate)(BUP_VECTOR_ADDRESS + 36))(pdate, date)

#define BUP_HK_SETDATE(date) (**(BupFnSetDate)(BUP_VECTOR_ADDRESS + 40))(date)

typedef struct BupConfig {
    Uint16 unit_id;
    Uint16 partition;
} BupConfig;

typedef struct BupStat {
    Uint32 totalsize;
    Uint32 totalblock;
    Uint32 blocksize;
    Uint32 freesize;
    Uint32 freeblock;
    Uint32 datanum;
} BupStat;

typedef struct BupDir {
    Uint8 filename[12];
    Uint8 comment[11];
    Uint8 language;
    Uint32 date;
    Uint32 datasize;
    Uint16 blocksize;
} BupDir;

typedef struct BupDate {
    Uint8 year;
    Uint8 month;
    Uint8 day;
    Uint8 time;
    Uint8 min;
    Uint8 week;
} BupDate;

typedef void (*BupFnInit)(Uint32* libaddr, Uint32* workbuff, BupConfig conf[]);
typedef Sint32 (**BupFnSelPart)(Uint32 device, Uint16 num);
typedef Sint32 (**BupFnFormat)(Uint32 device);
typedef Sint32 (**BupFnStat)(Uint32 device, Uint32 datasize, BupStat* stat);
typedef Sint32 (**BupFnWrite)(
    Uint32 device, BupDir* dir, Uint8* data, Uint8 owsw);
typedef Sint32 (**BupFnRead)(Uint32 device, Uint8* fname, Uint8* data);
typedef Sint32 (**BupFnDelete)(Uint32 device, Uint8* fname);
typedef Sint32 (**BupFnDir)(
    Uint32 device, Uint8* fname, Uint16 dirsize, BupDir* dir);
typedef Sint32 (**BupFnVerify)(Uint32 device, Uint8* fname, Uint8* data);
typedef void (**BupFnGetDate)(Uint32 pdate, BupDate* date);
typedef Uint32 (**BupFnSetDate)(BupDate* date);

void BUP_Init(Uint32* libaddr, Uint32* workbuff, BupConfig conf[]);
Sint32 BUP_SelPart(Uint32 device, Uint16 num);
Sint32 BUP_Format(Uint32 device);
Sint32 BUP_Stat(Uint32 device, Uint32 datasize, BupStat* stat);
Sint32 BUP_Write(Uint32 device, BupDir* dir, Uint8* data, Uint8 owsw);
Sint32 BUP_Read(Uint32 device, Uint8* fname, Uint8* data);
Sint32 BUP_Delete(Uint32 device, Uint8* fname);
Sint32 BUP_Dir(Uint32 device, Uint8* fname, Uint16 dirsize, BupDir* dir);
Sint32 BUP_Verify(Uint32 device, Uint8* fname, Uint8* data);
void BUP_GetDate(Uint32 pdate, BupDate* date);
Uint32 BUP_SetDate(BupDate* date);

#endif
