#ifndef AC_MEMORY_H
#define AC_MEMORY_H

#include "raylib.h"

typedef enum {
  ERR_OK = 0,
  ERR_NULL_POINTER,
  ERR_OUT_OF_MEMORY,
  ERR_FILE_NOT_FOUND,
  ERR_INVALID_ARGUMENT,
  ERR_UNKNOWN
} ErrorCode;

typedef struct {
  ErrorCode code;
  void *data;
} Result;

#if defined(__cplusplus)
extern "C" {
#endif

Result memory_make_alloc(unsigned int size);

#if defined(__cplusplus)
}
#endif

#endif // AC_MEMORY_H
