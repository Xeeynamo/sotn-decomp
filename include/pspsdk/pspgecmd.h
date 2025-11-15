#ifndef __GECMD_H__
#define __GECMD_H__

#include <psptypes.h>

#define GE_EXTRACT_ADDR24(_adr32)           (((u32)(_adr32)) & 0x00FFFFFFU)
#define GE_EXTRACT_BASE8(_adr32)            ((((u32)(_adr32))>>24) & 0x0FU)

#define GE_CMD_NOP                  0x00    // No operation
#define GE_CMD_VADR                 0x01    // Set vertex data

#define GE_CMD_PRIM                 0x04    // Draw primitive

#define GE_CMD_JUMP                 0x08    // Jump

#define GE_CMD_CALL                 0x0A    // List call
#define GE_CMD_RET                  0x0B    // List return

#define GE_CMD_BASE                 0x10    // Set address base

#define GE_CMD_VTYPE                0x12    // Set vertex type

#define GE_CMD_LTE                  0x17    // Lighting enable

#define GE_CMD_CLE                  0x1C    // Clipping enable
#define GE_CMD_BCE                  0x1D    // Culling enable
#define GE_CMD_TME                  0x1E    // Texture enable
#define GE_CMD_FGE                  0x1F    // Fog enable
#define GE_CMD_DTE                  0x20    // Dither enable
#define GE_CMD_ABE                  0x21    // Alpha blending enable
#define GE_CMD_ATE                  0x22    // Alpha test enable
#define GE_CMD_ZTE                  0x23    // Depth test enable
#define GE_CMD_STE                  0x24    // Stencil test enable
#define GE_CMD_AAE                  0x25    // Antialiasing enable

#define GE_CMD_CTE                  0x27    // Color test enable

#define GE_CMD_OFFSETX              0x4C    // Set screen offset
#define GE_CMD_OFFSETY              0x4D    // Set screen offset

#define GE_CMD_SHADE                0x50    // Set shading mode

#define GE_CMD_AC                   0x5C    // Set ambient light color
#define GE_CMD_AA                   0x5D    // Set ambient light color

#define GE_CMD_FBP                  0x9C    // Set frame buffer
#define GE_CMD_FBW                  0x9D    // Set frame buffer

#define GE_CMD_TBP0                 0xA0    // Set texture buffer

#define GE_CMD_TBW0                 0xA8    // Set texture buffer

#define GE_CMD_CBP                  0xB0    // Set CLUT buffer
#define GE_CMD_CBW                  0xB1    // Set CLUT buffer
#define GE_CMD_XBP1                 0xB2    // Set transfer buffer (source)
#define GE_CMD_XBW1                 0xB3    // Set transfer buffer (source)
#define GE_CMD_XBP2                 0xB4    // Set transfer buffer (destination)
#define GE_CMD_XBW2                 0xB5    // Set transfer buffer (destination)

#define GE_CMD_TSIZE0               0xB8    // Set texture size

#define GE_CMD_TMODE                0xC2    // Set texture mode
#define GE_CMD_TPF                  0xC3    // Set texture pixel format
#define GE_CMD_CLOAD                0xC4    // CLUT load
#define GE_CMD_CLUT                 0xC5    // Set CLUT
#define GE_CMD_TFILTER              0xC6    // Set texture filter
#define GE_CMD_TWRAP                0xC7    // Set texture wrap mode

#define GE_CMD_TFUNC                0xC9    // Set texture function

#define GE_CMD_TFLUSH               0xCB    // Texture flush
#define GE_CMD_TSYNC                0xCC    // Texture synchronization

#define GE_CMD_SCISSOR1             0xD4    // Set scissoring area
#define GE_CMD_SCISSOR2             0xD5    // Set scissoring area

#define GE_CMD_CTEST                0xD8    // Set color test parameter
#define GE_CMD_CREF                 0xD9    // Set color test reference
#define GE_CMD_CMSK                 0xDA    // Set color test mask
#define GE_CMD_ATEST                0xDB    // Set alpha test parameters

#define GE_CMD_BLEND                0xDF    // Set alpha blending parameters
#define GE_CMD_FIXA                 0xE0    // Set fixed color A
#define GE_CMD_FIXB                 0xE1    // Set fixed color B

#define GE_CMD_ZMSK                 0xE7    // Depth mask

#define GE_CMD_XSTART               0xEA    // Inter-buffer transfer start
#define GE_CMD_XPOS1                0xEB    // Set source buffer transfer position
#define GE_CMD_XPOS2                0xEC    // Set destination buffer transfer position

#define GE_CMD_XSIZE                0xEE    // Set transfer size

#define GE_SET_NOP()                        (GE_CMD_NOP<<24)
#define GE_SET_VADR_ADDR24(_adr32)          ((GE_CMD_VADR<<24) | GE_EXTRACT_ADDR24(_adr32))

#define GE_SET_PRIM(_count,_prim)           ((GE_CMD_PRIM<<24) | (((_prim)<<16) | (_count)))

#define GE_SET_JUMP_ADDR24(_adr32)          ((GE_CMD_JUMP<<24) | GE_EXTRACT_ADDR24(_adr32))

#define GE_SET_CALL_ADDR24(_adr32)          ((GE_CMD_CALL<<24) | GE_EXTRACT_ADDR24(_adr32))
#define GE_SET_RET()                        ((GE_CMD_RET<<24))

#define GE_SET_BASE_BASE8(_base32)          ((GE_CMD_BASE<<24) | ((u32)_base32 & 0xFF000000) >> 8)

#define GE_SET_VTYPE(_vtype)                ((GE_CMD_VTYPE<<24) | ((_vtype) & 0x00FFFFFF))

#define GE_SET_LTE(_lte)                    ((GE_CMD_LTE<<24) | (_lte))

#define GE_SET_CLE(_cle)                    ((GE_CMD_CLE<<24) | (_cle))
#define GE_SET_BCE(_bce)                    ((GE_CMD_BCE<<24) | (_bce))
#define GE_SET_TME(_tme)                    ((GE_CMD_TME<<24) | (_tme))
#define GE_SET_FGE(_fge)                    ((GE_CMD_FGE<<24) | (_fge))
#define GE_SET_DTE(_dte)                    ((GE_CMD_DTE<<24) | (_dte))
#define GE_SET_ABE(_abe)                    ((GE_CMD_ABE<<24) | (_abe))
#define GE_SET_ATE(_ate)                    ((GE_CMD_ATE<<24) | (_ate))
#define GE_SET_ZTE(_zte)                    ((GE_CMD_ZTE<<24) | (_zte))
#define GE_SET_STE(_ste)                    ((GE_CMD_STE<<24) | (_ste))
#define GE_SET_AAE(_aae)                    ((GE_CMD_AAE<<24) | (_aae))

#define GE_SET_CTE(_cte)                    ((GE_CMD_CTE<<24) | (_cte))

#define GE_SET_OFFSETX(_offx)               ((GE_CMD_OFFSETX<<24) | (_offx))
#define GE_SET_OFFSETY(_offy)               ((GE_CMD_OFFSETY<<24) | (_offy))

#define GE_SET_SHADE(_iip)                  ((GE_CMD_SHADE<<24) | (_iip))

#define GE_SET_AC(_r,_g,_b)                 ((GE_CMD_AC<<24) | ((_b)<<16) | ((_g)<<8) | (_r))
#define GE_SET_AA(_a)                       ((GE_CMD_AA<<24) | (_a))

#define GE_SET_FBP_ADDR24(_fbp32)           ((GE_CMD_FBP<<24) | GE_EXTRACT_ADDR24(_fbp32))
#define GE_SET_FBW_BASE8(_fbw,_base32)      ((GE_CMD_FBW<<24) | (GE_EXTRACT_BASE8(_base32)<<16) | (_fbw))

#define GE_SET_TBP0_ADDR24(_tbp32)          ((GE_CMD_TBP0<<24) | GE_EXTRACT_ADDR24(_tbp32))

#define GE_SET_TBW0_BASE8(_tbw,_base32)     ((GE_CMD_TBW0<<24) | ((((u32)_base32 & 0xFF000000) >> 8) | (_tbw)))

#define GE_SET_CBP_ADDR24(_cbp32)           ((GE_CMD_CBP<<24) | GE_EXTRACT_ADDR24(_cbp32))
#define GE_SET_CBW_BASE8(_base32)           ((GE_CMD_CBW<<24) | ((u32)_base32 & 0xFF000000) >> 8)
#define GE_SET_XBP1_ADDR24(_xbp32)          ((GE_CMD_XBP1<<24) | GE_EXTRACT_ADDR24(_xbp32))
#define GE_SET_XBW1_BASE8(_xbw,_base32)     ((GE_CMD_XBW1<<24) | (GE_EXTRACT_BASE8(_base32)<<16) | (_xbw))
#define GE_SET_XBP2_ADDR24(_xbp32)          ((GE_CMD_XBP2<<24) | GE_EXTRACT_ADDR24(_xbp32))
#define GE_SET_XBW2_BASE8(_xbw,_base32)     ((GE_CMD_XBW2<<24) | (GE_EXTRACT_BASE8(_base32)<<16) | (_xbw))

#define GE_SET_TSIZE0(_tw,_th)              ((GE_CMD_TSIZE0<<24) | ((_th)<<8) | (_tw))

#define GE_SET_TMODE(_hsm,_mc,_mxl)         ((GE_CMD_TMODE<<24) | ((_mxl)<<16) | ((_mc)<<8) | ((_hsm)))
#define GE_SET_TPF(_tpf,_ext)               ((GE_CMD_TPF<<24) | ((_ext)<<8) | (_tpf))
#define GE_SET_CLOAD(_np)                   ((GE_CMD_CLOAD<<24) | (_np))
#define GE_SET_CLUT(_cpf,_sft,_msk,_csa)    ((GE_CMD_CLUT<<24) | ((_csa)<<16) | ((_msk)<<8) | ((_sft)<<2) | (_cpf))
#define GE_SET_TFILTER(_min,_mag)           ((GE_CMD_TFILTER<<24) | ((_mag)<<8) | (_min))
#define GE_SET_TWRAP(_wms,_wmt)             ((GE_CMD_TWRAP<<24) | ((_wmt)<<8) | (_wms))

#define GE_SET_TFUNC(_txf,_tcc,_cd)         ((GE_CMD_TFUNC<<24) | ((_cd)<<16) | ((_tcc)<<8) | (_txf))

#define GE_SET_TFLUSH()                     (GE_CMD_TFLUSH<<24)
#define GE_SET_TSYNC()                      (GE_CMD_TSYNC<<24)

#define GE_SET_SCISSOR1(_sx1,_sy1)          ((GE_CMD_SCISSOR1<<24) | ((_sy1)<<10) | (_sx1))
#define GE_SET_SCISSOR2(_sx2,_sy2)          ((GE_CMD_SCISSOR2<<24) | ((_sy2)<<10) | (_sx2))

#define GE_SET_CTEST(_ctf)                  ((GE_CMD_CTEST<<24) | (_ctf))
#define GE_SET_CREF(_r,_g,_b)               ((GE_CMD_CREF<<24) | ((_b)<<16) | ((_g)<<8) | (_r))
#define GE_SET_CMSK(_r,_g,_b)               ((GE_CMD_CMSK<<24) | ((_b)<<16) | ((_g)<<8) | (_r))

#define GE_SET_ATEST(_atf,_aref,_amsk)      ((GE_CMD_ATEST<<24) | ((_amsk)<<16) | ((_aref)<<8) | (_atf))

#define GE_SET_BLEND(_a,_b,_equ)            ((GE_CMD_BLEND<<24) | ((_equ)<<8) | ((_b)<<4) | (_a))
#define GE_SET_FIXA_RGB24(_rgb24)           ((GE_CMD_FIXA<<24) | ((_rgb24) & 0x00FFFFFF))
#define GE_SET_FIXB_RGB24(_rgb24)           ((GE_CMD_FIXB<<24) | ((_rgb24) & 0x00FFFFFF))

#define GE_SET_ZMSK(_zmsk)                  ((GE_CMD_ZMSK<<24) | (_zmsk))

#define GE_SET_XSTART(_xpf)                 ((GE_CMD_XSTART<<24) | (_xpf))
#define GE_SET_XPOS1(_sx1,_sy1)             ((GE_CMD_XPOS1<<24) | ((_sy1)<<10) | (_sx1))
#define GE_SET_XPOS2(_sx2,_sy2)             ((GE_CMD_XPOS2<<24) | ((_sy2)<<10) | (_sx2))

#define GE_SET_XSIZE(_width,_height)        ((GE_CMD_XSIZE<<24) | ((_height)<<10) | (_width))

#endif __GECMD_H__