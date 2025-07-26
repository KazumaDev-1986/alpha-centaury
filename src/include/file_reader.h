#ifndef AC_FILE_READER_H
#define AC_FILE_READER_H

#include <stdint.h>

#include "config.h"
#include "map.h"
#include "memory.h"

typedef struct {
  Map map;
  ErrorCode errorCode;
} FileReader;

#if defined(__cplusplus)
extern "C" {
#endif

AC FileReader file_data(const char *fileName);

#if defined(__cplusplus)
}
#endif

#endif  // AC_FILE_READER_H
