#ifndef AC_PATHFINDER_H
#define AC_PATHFINDER_H

#include <stddef.h>

#include "config.h"
#include "heap.h"
#include "map.h"
#include "types.h"

typedef enum {
  SQUARE_DIRECTION_UP = 0,
  SQUARE_DIRECTION_RIGHT,
  SQUARE_DIRECTION_DOWN,
  SQUARE_DIRECTION_LEFT,
} SquareDirectionType;

typedef struct Square {
  uint16_t x;
  uint16_t y;
  uint16_t value;

  uint32_t realCost;
  uint32_t heuristicCost;
  uint32_t totalCost;

  bool inOpenSet;
  bool inCloseSet;
  bool walkable;

  struct Square *parent;

} Square;

typedef struct {
  Heap *openSet;
  Square _squareMap[AC_MAX_BUFFER_SIZE];
  size_t _squareMapWidth;
  size_t _squareMapHeight;

  ui16Point _end;
} Pathfinder;

#if defined(__cplusplus)
extern "C" {
#endif

AC Pathfinder *pathfinder_create(const Map *const map);
AC Square *pathfinder_search(Pathfinder *const pathfinder, ui16Point start,
                             ui16Point end);
AC void pathfinder_destroy(Pathfinder **pathfinder);

#if defined(__cplusplus)
}
#endif

#endif // AC_PATHFINDER_H
