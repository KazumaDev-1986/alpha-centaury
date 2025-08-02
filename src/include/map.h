#ifndef AC_MAP_H
#define AC_MAP_H

#include <stdint.h>

#include "config.h"
#include "memory.h"

typedef struct {
  uint16_t width;
  uint16_t height;
  int16_t buffer[AC_BUFFER_SIZE];
} Map;

#if defined(__cplusplus)
extern "C" {
#endif

AC void map_draw(const Map *const map);

#if defined(__cplusplus)
}
#endif

#endif  // AC_MAP_H
