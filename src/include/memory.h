#ifndef AC_MEMORY_H
#define AC_MEMORY_H

#include "raylib.h"

typedef enum {
  ERROR_CODE_UNDEFINED = 0,
  ERROR_CODE_OK,
  ERROR_CODE_NULL_POINTER,
  ERROR_CODE_OUT_OF_MEMORY,
  ERROR_CODE_FILE_NOT_FOUND,
  ERROR_CODE_INVALID_ARGUMENT,
  ERROR_CODE_UNKNOWN
} ErrorCode;

typedef struct {
  ErrorCode code;
  void *data;
} Result;

#if defined(__cplusplus)
extern "C" {
#endif

Result memory_make_alloc(unsigned int size);

void memory_free_container(void **const ptr);

#if defined(__cplusplus)
}
#endif

#endif // AC_MEMORY_H
