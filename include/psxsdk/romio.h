#ifndef _ROMIO_H
#define _ROMIO_H

#define FREAD 0x0001   /* readable */
#define FWRITE 0x0002  /* writable */
#define FNBLOCK 0x0004 /* non-blocking reads */
#define FRLOCK 0x0010  /* read locked (non-shared) */
#define FWLOCK 0x0020  /* write locked (non-shared) */
#define FAPPEND 0x0100 /* append on each write */
#define FCREAT 0x0200  /* create if nonexistant */
#define FTRUNC 0x0400  /* truncate to zero length */
#define FSCAN 0x1000   /* scan type */
#define FRCOM 0x2000   /* remote command entry */
#define FNBUF 0x4000   /* no ring buf. and console interrupt */
#define FASYNC 0x8000  /* asyncronous i/o */

#define O_RDONLY FREAD
#define O_WRONLY FWRITE
#define O_RDWR FREAD | FWRITE
#define O_CREAT FCREAT   /* open with file create */
#define O_NOBUF FNBUF    /* no device buffer and console interrupt */
#define O_NBLOCK FNBLOCK /* non blocking mode */
#define O_NOWAIT FASYNC  /* asyncronous i/o */

#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif
#ifndef SEEK_END
#define SEEK_END 2
#endif

#endif
