#ifndef LIBSND_H
#define LIBSND_H

extern void SsSeqClose(short);

extern void SsSetMVol(short, short);
extern void SsSetSerialAttr(char, char, char);
extern void SsSetSerialVol(short s_num, short voll, short volr);

#endif
