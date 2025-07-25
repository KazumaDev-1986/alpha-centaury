#ifndef AC_FILE_READER_H
#define AC_FILE_READER_H

#include <stdint.h>

#include "config.h"

// Maximum map size 16x16 == 256.
#define AC_BUFFER_SIZE 256

typedef struct {
  uint16_t width;
  uint16_t height;
  uint32_t buffer[AC_BUFFER_SIZE];
} FileReader;

#if defined(__cplusplus)
extern "C" {
#endif

FileReader file_data(const char *fileName);

#if defined(__cplusplus)
}
#endif

#endif  // AC_FILE_READER_H
