#include <stdint.h>

#include "include/config.h"
#include "include/heap.h"
#include "include/memory.h"
#include "include/pathfinder.h"

// *************************************************
// Static functions definition.
// *************************************************
static int _cmp(const void *const a, const void *const b);
static bool _initialize_square_map(Square *squareMap, const Map *const map);

// *************************************************
// Public functions implementation.
// *************************************************
Pathfinder *pathfinder_create(const Map *const map) {
  Pathfinder *pathfinder = NULL;
  size_t capacity = map->height * map->width;
  bool hasError = false;

  if (map && capacity >= AC_MAX_BUFFER_SIZE) {
    return NULL;
  }

  Result result = memory_make_alloc(sizeof(Pathfinder));
  if (result.code == ERROR_CODE_OK) {
    pathfinder = result.data;
    pathfinder->openSet = heap_create(capacity, _cmp);
    if (pathfinder->openSet) {
      hasError = _initialize_square_map(pathfinder->_squareMap, map);
    } else {
      hasError = true;
    }
  }

  if (hasError) {
    pathfinder_destroy(&pathfinder);
  }

  return pathfinder;
}

void pathfinder_search(Pathfinder *const pathfinder, ui32Point start,
                       ui32Point end) {
  // TODO
}

void pathfinder_destroy(Pathfinder **pathfinder) {
  if (pathfinder && *pathfinder) {
    if ((*pathfinder)->openSet) {
      heap_destroy(&(*pathfinder)->openSet);
    }
    memory_free_container((void **)pathfinder);
  }
}
// *************************************************
// Static functions implementation.
// *************************************************
static int _cmp(const void *const a, const void *const b) {
  const Square *const sa = (const Square *const)a;
  const Square *const sb = (const Square *const)b;

  if (sa->totalCost < sb->totalCost) {
    return -1;
  } else if (sa->totalCost > sb->totalCost) {
    return 1;
  }
  return 0;
}
static bool _initialize_square_map(Square *squareMap, const Map *const map) {
  size_t size = map->height * map->width;
  if (size >= AC_MAX_BUFFER_SIZE) {
    return true;
  }

  for (uint16_t i = 0; i < map->height; ++i) {
    for (uint16_t j = 0; j < map->width; ++j) {
      size_t index = i * map->width + j;
      Square square = (Square){
          .x = j,
          .y = i,
          .value = map->buffer[index],
          .realCost = 0,
          .heuristicCost = 0,
          .totalCost = 0,
      };
      squareMap[index] = square;
    }
  }

  return false;
}
