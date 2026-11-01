// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_HW_H
#define SATURN_HW_H

#ifdef SATZ
#define HW_STORE(ptr, value)                                                   \
    satz_bus_write((unsigned long)(ptr), (value), sizeof(*(ptr)))
#define HW_LOAD(ptr)                                                           \
    ((__typeof__(*(ptr)))satz_bus_read((unsigned long)(ptr), sizeof(*(ptr))))
#else
#define HW_STORE(ptr, value) (*(ptr) = (value))
#define HW_LOAD(ptr) (*(ptr))
#endif

#ifdef SATZ
#define HW_WRITE8(addr, value)                                                 \
    satz_bus_write((unsigned long)(addr), (u8)(value), 1)
#define HW_WRITE16(addr, value)                                                \
    satz_bus_write((unsigned long)(addr), (u16)(value), 2)
#define HW_WRITE32(addr, value)                                                \
    satz_bus_write((unsigned long)(addr), (u32)(value), 4)
#define HW_READ8(addr) ((u8)satz_bus_read((unsigned long)(addr), 1))
#define HW_READ16(addr) ((u16)satz_bus_read((unsigned long)(addr), 2))
#define HW_READ32(addr) ((u32)satz_bus_read((unsigned long)(addr), 4))
#else
#define HW_WRITE8(addr, value) (*(u8*)(addr) = (value))
#define HW_WRITE16(addr, value) (*(u16*)(addr) = (value))
#define HW_WRITE32(addr, value) (*(s32*)(addr) = (value))
#define HW_READ8(addr) (*(u8*)(addr))
#define HW_READ16(addr) (*(u16*)(addr))
#define HW_READ32(addr) (*(u32*)(addr))
#endif

#endif
