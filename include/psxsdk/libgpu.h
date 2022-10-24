#ifndef LIBGPU_H
#define LIBGPU_H
#include <types.h>

typedef struct {
    /* 0x0 */ short x;
    /* 0x2 */ short y; /* offset point on VRAM */
    /* 0x4 */ short w; /* width */
    /* 0x6 */ short h; /* height */
} RECT; /* size = 0x8 */ 

typedef struct {
    /* 0x0 */ u_long tag;
    /* 0x4 */ u_long code[15];
} DR_ENV; /* Packed Drawing Environment, size = 0x40 */

typedef struct {
    /* 0x00 */ u_long tag;
    /* 0x04 */ u_char r0;
    /* 0x05 */ u_char g0;
    /* 0x06 */ u_char b0;
    /* 0x07 */ u_char code;
    /* 0x08 */ short x0;
    /* 0x0A */ short y0;
    /* 0x0C */ u_char u0;
    /* 0x0D */ u_char v0;
    /* 0x0E */ u_short clut;
    /* 0x10 */ u_char r1;
    /* 0x11 */ u_char g1;
    /* 0x12 */ u_char b1;
    /* 0x13 */ u_char p1;
    /* 0x14 */ short x1;
    /* 0x16 */ short y1;
    /* 0x18 */ u_char u1
    /* 0x19 */ u_char v1;
    /* 0x1A */ u_short tpage;
    /* 0x1C */ u_char r2;
    /* 0x1D */ u_char g2;
    /* 0x1E */ u_char b2;
    /* 0x1F */ u_char p2;
    /* 0x2A */ short x2;
    /* 0x2C */ short y2;
    /* 0x2E */ u_char u2;
    /* 0x2F */ u_char v2;
    /* 0x30 */ u_short pad2;
} POLY_GT3; /* Gouraud Textured Triangle, size = 0x32 */

typedef struct {
    /* 0x00 */ u_long tag;
    /* 0x04 */ u_char r0;
    /* 0x05 */ u_char g0;
    /* 0x06 */ u_char b0;
    /* 0x07 */ u_char code;
    /* 0x08 */ short x0
    /* 0x0A */ short y0;
    /* 0x0C */ u_char r1;
    /* 0x0D */ u_char g1;
    /* 0x0E */ u_char b1;
    /* 0x0F */ u_char pad1;
    /* 0x10 */ short x1;
    /* 0x12 */ short y1;
    /* 0x14 */ u_char r2;
    /* 0x15 */ u_char g2;
    /* 0x16 */ u_char b2;
    /* 0x17 */ u_char pad2;
    /* 0x18 */ short x2;
    /* 0x2A */ short y2;
    /* 0x2C */ u_char r3;
    /* 0x2D */ u_char g3;
    /* 0x2E */ u_char b3;
    /* 0x2F */ u_char pad3;
    /* 0x30 */ short x3;
    /* 0x32 */ short y3;
} POLY_G4; /* Gouraud Quadrangle, size = 0x34 */

typedef struct {
    /* 0x00 */ u_long tag;
    /* 0x04 */ u_char r0;
    /* 0x05 */ u_char g0;
    /* 0x06 */ u_char b0;
    /* 0x07 */ u_char code;
    /* 0x08 */ short x0;
    /* 0x0A */ short y0;
    /* 0x0C */ u_char u0;
    /* 0x0D */ u_char v0;
    /* 0x0E */ u_short clut;
    /* 0x10 */ u_char r1;
    /* 0x11 */ u_char g1;
    /* 0x12 */ u_char b1;
    /* 0x13 */ u_char p1;
    /* 0x14 */ short x1;
    /* 0x16 */ short y1;
    /* 0x18 */ u_char u1;
    /* 0x19 */ u_char v1;
    /* 0x1A */ u_short tpage;
    /* 0x1C */ u_char r2;
    /* 0x1D */ u_char g2;
    /* 0x1E */ u_char b2;
    /* 0x1F */ u_char p2;
    /* 0x20 */ short x2;
    /* 0x22 */ short y2;
    /* 0x24 */ u_char u2;
    /* 0x25 */ u_char v2;
    /* 0x26 */ u_short pad2;
    /* 0x28 */ u_char r3;
    /* 0x29 */ u_char g3;
    /* 0x2A */ u_char b3;
    /* 0x2B */ u_char p3;
    /* 0x2C */ short x3;
    /* 0x2E */ short y3;
    /* 0x30 */ u_char u3;
    /* 0x31 */ u_char v3;
    /* 0x32 */ u_short pad3;
} POLY_GT4; /* Gouraud Textured Quadrangle, size = 0x34*/

typedef struct {
    /* 0x00 */ u_long tag;
    /* 0x04 */ u_char r0;
    /* 0x05 */ u_char g0;
    /* 0x06 */ u_char b0;
    /* 0x07 */ u_char code;
    /* 0x08 */ short x0;
    /* 0x0A */ short y0;
    /* 0x0C */ u_char u0;
    /* 0x0D */ u_char v0;
    /* 0x0E */ u_short clut;
    /* 0x10 */ short w;
    /* 0x12 */ short h;
} SPRT; /* free size Sprite, size = 0x14 */

typedef struct {
    /* 0x00 */ u_long tag;
    /* 0x04 */ u_char r0;
    /* 0x05 */ u_char g0;
    /* 0x06 */ u_char b0;
    /* 0x07 */ u_char code;
    /* 0x08 */ short x0;
    /* 0x0A */ short y0;
    /* 0x0C */ u_char u0;
    /* 0x0D */ u_char v0;
    /* 0x0E */ u_short clut;
} SPRT_16; /* 16x16 Sprite, size = 0x10 */

typedef struct {
    /* 0x00 */ u_long tag;
    /* 0x04 */ u_char r0;
    /* 0x05 */ u_char g0;
    /* 0x06 */ u_char b0;
    /* 0x07 */ u_char code;
    /* 0x08 */ short x0;
    /* 0x0A */ short y0;
    /* 0x0C */ u_char u0;
    /* 0x0D */ u_char v0;
    /* 0x0E */ u_short clut;
} SPRT_8; /* 8x8 Sprite, size = 0x10 */

typedef struct {
    /* 0x00 */ RECT clip;         /* clip area */
    /* 0x08 */ short ofs[2];      /* drawing offset */
    /* 0x0A */ RECT tw;           /* texture window */
    /* 0x12 */ u_short tpage;     /* texture page */
    /* 0x14 */ u_char dtd;        /* dither flag (0:off, 1:on) */
    /* 0x15 */ u_char dfe;        /* flag to draw on display area (0:off 1:on) */
    /* 0x16 */ u_char isbg;       /* enable to auto-clear */
    /* 0x17 */ u_char r0, g0, b0; /* initital background color */
    /* 0x18 */ DR_ENV dr_env;     /* reserved */
} DRAWENV; /* size = 0x58 */

typedef struct {
    /* 0x00 */ RECT disp;         /* display area */
    /* 0x08 */ RECT screen;       /* display start point */
    /* 0x10 */ u_char isinter;    /* interlace 0: off 1: on */
    /* 0x11 */ u_char isrgb24;    /* RGB24 bit mode */
    /* 0x12 */ u_char pad0, pad1; /* reserved */
} DISPENV; /* size = 0x13 */

typedef struct {
    /* 0x00 */ u_long tag;
    /* 0x04 */ u_long code[2];
} DR_MODE; /* Drawing Mode, size = 0x08 */

extern void AddPrim(void* ot, void* p);
extern void SetShadeTex(void* p, int tge);
extern void SetPolyGT3(POLY_GT3* p);
extern void SetPolyG4(POLY_G4* p);
extern void SetPolyGT4(POLY_GT4* p);
extern void SetSprt(SPRT* p);
extern void SetSprt16(SPRT_16* p);
extern void SetSprt8(SPRT_8* p);
extern int ResetGraph(int mode);
extern int SetGraphReverse(int mode);
extern int SetGraphQueue(int mode);
extern u_long DrawSyncCallback(void (*func)());
extern void SetDispMask(int mask);
extern void SetDrawMode(DR_MODE* p, int dfe, int dtd, int tpage, RECT* tw);
extern int DrawSync(int mode);
extern int ClearImage(RECT* rect, u_char r, u_char g, u_char b);
extern int LoadImage(RECT* rect, u_long* p);
extern int StoreImage(RECT* rect, u_long* p);
extern int MoveImage(RECT* rect, int x, int y);
extern u_long* ClearOTag(u_long* ot, int n);
extern u_long* ClearOTagR(u_long* ot, int n);
extern void DrawOTag(u_long* p);
extern DRAWENV* PutDrawEnv(DRAWENV* env);
extern DISPENV* PutDispEnv(DISPENV* env);

#endif