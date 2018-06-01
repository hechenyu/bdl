#ifndef __unp_wrapposix_h
#define __unp_wrapposix_h

#include <unistd.h>

int      Open(const char *, int , ...);
ssize_t  Read(int, void *, size_t);
void     Write(int, void *, size_t);
off_t    Lseek(int, off_t, int);
void     Close(int);
void     Ftruncate(int, off_t);

#endif
