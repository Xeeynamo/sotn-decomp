#ifndef LIBC_H
#define LIBC_H

extern void exit();
extern void puts(char*);
// setjmp
extern char* strcat(char*, char*);
extern int strcmp(char*, char*);
extern int strncmp(char*, char*);
extern char* strcpy(char*, char*);
extern int strlen(char*);
extern void* memcpy(unsigned char*, unsigned char*, int);
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
