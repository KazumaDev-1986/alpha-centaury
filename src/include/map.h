#ifndef AC_MAP_H
#define AC_MAP_H

#include <stdint.h>

#include "config.h"
#include "memory.h"

typedef struct {
  uint16_t width;
  uint16_t height;

  uint32_t *vector;
} Map;

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__cplusplus)
}
#endif

#endif  // AC_MAP_H
