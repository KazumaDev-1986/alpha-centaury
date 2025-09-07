#ifndef AC_TYPES_H
#define AC_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "config.h"

typedef struct {
  uint16_t x;
  uint16_t y;
} ui16Point;

typedef struct {
  uint32_t x;
  uint32_t y;
} ui32Point;

#if defined(__cplusplus)
extern "C" {
#endif

AC bool check_equal_points_ui16(ui16Point a, ui16Point b);
AC bool check_equal_points_ui32(ui32Point a, ui32Point b);
AC uint32_t manhattan_distance_ui16(ui16Point a, ui16Point b);

#if defined(__cplusplus)
}
#endif

#endif
