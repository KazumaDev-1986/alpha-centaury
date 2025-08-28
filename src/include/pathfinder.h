#ifndef AC_PATHFINDER_H
#define AC_PATHFINDER_H

#include <stddef.h>

#include "config.h"
#include "heap.h"
#include "map.h"
#include "types.h"

typedef struct {
  uint16_t x;
  uint16_t y;
  uint16_t value;

  uint32_t realCost;
  uint32_t heuristicCost;
  uint32_t totalCost;

} Square;

typedef struct {
  Heap *openSet;
  Square _squareMap[AC_MAX_BUFFER_SIZE];
  size_t _squreMapCount;

} Pathfinder;

#if defined(__cplusplus)
extern "C" {
#endif

AC Pathfinder *pathfinder_create(const Map *const map);
AC void pathfinder_search(Pathfinder *const pathfinder, ui32Point start,
                          ui32Point end);
AC void pathfinder_destroy(Pathfinder **pathfinder);

#if defined(__cplusplus)
}
#endif

#endif // AC_PATHFINDER_H
