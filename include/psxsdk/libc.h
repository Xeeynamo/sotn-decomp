#ifndef LIBC_H
#define LIBC_H

extern void exit();
extern void puts(char*);
// setjmp
extern char* strcat(char*, char*);
extern int strcmp(const char*, const char*);
extern int strncmp(const char*, const char*);
extern char* strcpy(const char*, const char*);
extern int strlen(const char*);
extern void* memcpy(void*, const void*, size_t);
extern void* memset(unsigned char*, unsigned char, int);

/*
 * Returns a pseudo-random number from 0 to RAND_MAX (0x7FFF=32767).
 */
extern int rand(void);
extern void srand(unsigned int);
extern void* malloc(size_t // Size of memory block to be allocated
);
extern void free(void*);
int printf(char*, ...);

int abs(int x);

#endif // LIBC_H
