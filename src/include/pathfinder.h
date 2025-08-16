#ifndef AC_PATHFINDER_H
#define AC_PATHFINDER_H

#include <stddef.h>
#include <stdint.h>

#include "config.h"
#include "map.h"
#include "types.h"

typedef struct {
  ui32Point *array;
  size_t size;
} Pathfinder;

#if defined(__cplusplus)
extern "C" {
#endif

AC Pathfinder *pathfinder_create(const Map **const map);

AC void pathfinder_search(ui32Point start, ui32Point end);

AC void pathfinder_destroy(Pathfinder *pathfinder);

#if defined(__cplusplus)
}
#endif

#endif // AC_PATHFINDER_H
