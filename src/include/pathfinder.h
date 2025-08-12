#ifndef AC_PATHFINDER_H
#define AC_PATHFINDER_H

#include <stdint.h>

#include "config.h"
#include "map.h"
#include "types.h"
#include "map.h"

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
