#ifndef AC_PATHFINDER_H
#define AC_PATHFINDER_H

#include <stddef.h>
#include <stdint.h>

#include "config.h"
#include "heap.h"
#include "map.h"
#include "types.h"

typedef enum {
  DIRECTION_UP = 0,
  DIRECTION_RIGHT,
  DIRECTION_DOWN,
  DIRECTION_LEFT
} DirectionType;

typedef struct {
  ui32Point *path;
  size_t size;

  // Internal data.
  Node * _nodeMap[AC_MAX_BUFFER_SIZE];
  uint16_t _height;
  uint16_t _width;
  
  Heap *_openSet;
} Pathfinder;

#if defined(__cplusplus)
extern "C" {
#endif

AC Pathfinder *pathfinder_create(const Map **const map);

AC void pathfinder_search(Pathfinder *const pathfinder, ui32Point start, ui32Point end);

AC void pathfinder_destroy(Pathfinder *pathfinder);

#if defined(__cplusplus)
}
#endif

#endif // AC_PATHFINDER_H
