// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SOTN_ENDIAN_H
#define SOTN_ENDIAN_H

#ifndef SOTN_BIG_ENDIAN
#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define SOTN_BIG_ENDIAN 1
#elif defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define SOTN_BIG_ENDIAN 0
#elif defined(_WIN32) || defined(_MIPSEL) || defined(__MWERKS__) ||            \
    defined(VERSION)
#define SOTN_BIG_ENDIAN 0
#else
#error "Unable to determine target byte order"
#endif
#endif

#if SOTN_BIG_ENDIAN != 0 && SOTN_BIG_ENDIAN != 1
#error "SOTN_BIG_ENDIAN must be 0 or 1"
#endif

#endif
