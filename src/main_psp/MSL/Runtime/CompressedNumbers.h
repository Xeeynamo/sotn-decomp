// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef MSL_RUNTIME_COMPRESSEDNUMBERS_H
#define MSL_RUNTIME_COMPRESSEDNUMBERS_H

char* __DecodeAddress(char* p, void** paddr);
char* __DecodeSignedNumber(char* p, long* pnum);
char* __DecodeUnsignedNumber(char* p, unsigned long* pnum);

#endif // MSL_RUNTIME_COMPRESSEDNUMBERS_H
