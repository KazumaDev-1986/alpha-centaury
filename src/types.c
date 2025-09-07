#include "include/types.h"

// *************************************************
// Public functions implementation.
// *************************************************
bool check_equal_points_ui16(ui16Point a, ui16Point b) {
  return a.x == b.x && a.y == b.y;
}
bool check_equal_points_ui32(ui32Point a, ui32Point b) {
  return a.x == b.x && a.y == b.y;
}

uint32_t manhattan_distance_ui16(ui16Point a, ui16Point b) {
  int32_t x = (int32_t)a.x - (int32_t)b.x;
  if (x < 0)
    x = -x;

  int32_t y = (int32_t)a.y - (int32_t)b.y;
  if (y < 0)
    y = -y;

  return x + y;
}
