#ifndef AC_MEMORY_H
#define AC_MEMORY_H

#include "raylib.h"

typedef enum {
  ERROR_CODE_OK = 0,
  ERROR_CODE_NULL_POINTER,
  ERROR_CODE_OUT_OF_MEMORY,
  ERROR_CODE_FILE_NOT_FOUND,
  ERROR_CODE_INVALID_ARGUMENT,
  ERROR_CODE_UNKNOWN
} ErrorCode;

typedef struct {
  ErrorCode code;
  void *data;
} ResultMemory;

#if defined(__cplusplus)
extern "C" {
#endif

ResultMemory memory_make_alloc(unsigned int size);

#if defined(__cplusplus)
}
#endif

#endif  // AC_MEMORY_H
