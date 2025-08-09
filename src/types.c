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
