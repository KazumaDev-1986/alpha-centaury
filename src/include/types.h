#ifndef AC_TYPES_H
#define AC_TYPES_H

#include <stdint.h>
#include <stdbool.h>

#include "config.h"

typedef struct {
  uint16_t x;
  uint16_t y;
} ui16Point;

typedef struct {
  uint32_t x;
  uint32_t y;
} ui32Point;


typedef struct Node {
  // Point.
  ui16Point point;
  int32_t value;
  
  // Functions.
  uint32_t realCost;
  uint32_t heuristicCost;
  uint32_t totalCost;

  // Flags.
  bool walkable;
  bool inOpenSet;
  bool inCloseSet;

  // Parent.
  struct Node *parent;
}Node;

#if defined(__cplusplus)
extern "C" {
#endif

AC bool check_equal_points_ui16(ui16Point a, ui16Point b);
AC bool check_equal_points_ui32(ui32Point a, ui32Point b);

#if defined(__cplusplus)
}
#endif

#endif
