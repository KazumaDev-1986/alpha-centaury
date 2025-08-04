#ifndef AC_PATHFINDER_H
#define AC_PATHFINDER_H

#include <stdint.h>
#include <stddef.h>

#include "config.h"
#include "types.h"
#include "map.h"

typedef struct Node {
  // Point.
  ui16Point2D point;

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

typedef struct {
  ui16Point2D *data;
  size_t size;
}Pathfinder;

#if defined(__cplusplus)
extern "C" {
#endif

AC Pathfinder pathfinder_create(const Map *const map, ui16Point2D start,  ui16Point2D end);
AC void pathfinder_destroy(Pathfinder *pathfinder);

#if defined(__cplusplus)
}
#endif


#endif  // AC_PATHFINDER_H
