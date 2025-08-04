#include "include/memory.h"
#include "include/pathfinder.h"
#include "include/trace_utils.h"
#include "include/types.h"

// *************************************************
// Static functions & variables declaration.
// *************************************************

// *************************************************
// Public functions implementation.
// *************************************************
Pathfinder pathfinder_create(const Map *const map, ui16Point2D start, ui16Point2D end) {
  Pathfinder pathfinder = {0};
  size_t size = map->height * map->width;
  Result result = memory_make_alloc(size * sizeof(ui16Point2D));
  if (result.code == ERROR_CODE_OK) {
    pathfinder.data = result.data;
    pathfinder.size = size;
#if defined(AC_DEBUG)
    trace_created("PATHFINDER", "");
#endif
  }

  return pathfinder;
}

void pathfinder_destroy(Pathfinder *pathfinder) {
  if (pathfinder != NULL) {
    void *tmp = pathfinder->data;
    memory_free_container(&tmp);
#if defined(AC_DEBUG)
    trace_destroyed("PATHFINDER", "");
#endif
  }
}

// *************************************************
// Static functions implementation.
// *************************************************
