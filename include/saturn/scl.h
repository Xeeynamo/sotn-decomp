#ifndef SCL_H
#define SCL_H
typedef unsigned char Uint8;
typedef signed char Sint8;
typedef unsigned short Uint16;
typedef signed short Sint16;
typedef unsigned long Uint32;
typedef signed long Sint32;
typedef float Float32;
typedef double Float64;

typedef int Int;

typedef int Bool;

typedef struct SclConfig {
    Uint8 dispenbl;
    Uint8 charsize;
    Uint8 pnamesize;
    Uint8 platesize;
    Uint8 bmpsize;
    Uint8 coltype;
    Uint8 datatype;
    Uint8 mapover;
    Uint8 flip;
    Uint16 patnamecontrl;
    Uint32 plate_addr[32];
} SclConfig;

extern void SCL_InitConfigTb(SclConfig* scfg);
extern void SCL_SetConfig(Uint16 sclnum, SclConfig* scfg);

#define SCL_NBG0 0x00000004
#endif
