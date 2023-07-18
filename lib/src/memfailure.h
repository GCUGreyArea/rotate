#ifndef MEMFILURE_H
#define MEMFILURE_H
#include <stdio.h>

#define memfailure(LN)                                                  \
    fprintf(stderr, "memory allocation failure %s:%d\n", __FILE__, LN); \
    abort();

#define mem_failure() memfailure(__LINE__)
#endif // MEMFILURE_H