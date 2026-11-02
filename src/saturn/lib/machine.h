#ifndef MACHINE_H
#define MACHINE_H

#ifndef SATZ
static inline void set_sr(unsigned int sr) {
    asm volatile("ldc\t%0,sr" : : "r"(sr));
}

static inline unsigned int get_sr(void) {
    unsigned int sr;

    asm volatile("stc\tsr,%0" : "=r"(sr));
    return sr;
}

static inline unsigned int get_imask(void) {
    unsigned int imask = (get_sr() & 0x000000F0) >> 4;

    return imask;
}

static inline void set_imask(unsigned int imask) {
    unsigned int sr = get_sr();

    sr &= ~0x000000F0;
    sr |= (imask << 4);
    set_sr(sr);
}
#endif

#endif
