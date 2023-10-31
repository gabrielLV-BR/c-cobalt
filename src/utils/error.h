#if !defined(ERROR_H)
#define ERROR_H

#include <stdio.h>

#define ERROR(x) { printf("[ERROR] On %s:%s\n\t%s", __FILE__, __LINE__, x); perror(x); };

#define WARNING(x) { printf("[WARNING] %s\n", x); };

#endif // ERROR_H
