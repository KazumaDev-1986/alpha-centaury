#ifndef AC_PATHFINDER_H
#define AC_PATHFINDER_H

#include <stdint.h>

#include "config.h"
#include "map.h"
#include "types.h"

typedef struct Node {
  // Point.
  ui16Point point;
  uint16_t value;
  
  // Manhattan.
  uint32_t realCost;
  uint32_t heuristicCost;
  uint32_t totalCost;

  // Flag.
  bool inOpenSet;
  bool inCloseSet;

  // Parent.
  struct Node *parent;
} Node;

typedef struct {
  uint32_t *path;
} Pathfinder;

#if defined(__cplusplus)
extern "C" {
#endif

AC Pathfinder *pathfinder_create(const Map *const map, ui16Point start,
                                 ui16Point end);

#if defined(__cplusplus)
}
#endif

#endif // AC_PATHFINDER_H
