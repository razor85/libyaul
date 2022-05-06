#ifndef _LIB_STDLIB_H_
#define _LIB_STDLIB_H_

#include <sys/cdefs.h>

#include <stddef.h>

__BEGIN_DECLS

#define ATEXIT_MAX (32)

extern int abs(int);
extern long labs(long);

extern int atoi(const char *);
extern long atol(const char *);

unsigned long strtoul(const char *__restrict, char **__restrict, int);
long strtol(const char *__restrict, char **__restrict, int);

extern void *malloc(size_t);
extern void *memalign(size_t, size_t);
extern void *realloc(void *, size_t);
extern void free(void *);

extern void abort(void) __noreturn;
extern int atexit(void (*function)(void));
extern void exit(int code) __noreturn;

__END_DECLS

#endif /* _LIB_STDLIB_H_ */
