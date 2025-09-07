#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "include/config.h"
#include "include/heap.h"
#include "include/memory.h"
#include "include/pathfinder.h"
#include "include/types.h"

// *************************************************
// Static functions definition.
// *************************************************
static int _cmp(const void *const a, const void *const b);

static void _initialize_square_map(Pathfinder *const pathfinder,
                                   const Map *const map);

static void _evaluate_square_neighbours(Pathfinder *const pathfinder,
                                        ui16Point currentPoint);

static void _update_and_insert_openSet(Pathfinder *const pathfinder,
                                       Square *currentSquare,
                                       Square *parentSquare);

static void _evaluate_square_by_direction(Pathfinder *const pathfinder,
                                          ui16Point parentPoint,
                                          SquareDirectionType type);

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
      _initialize_square_map(pathfinder, map);
    } else {
      hasError = true;
    }
  }

  if (hasError) {
    pathfinder_destroy(&pathfinder);
  }

  return pathfinder;
}

Square *pathfinder_search(Pathfinder *const pathfinder, ui16Point start,
                          ui16Point end) {
  size_t width = pathfinder->_squareMapWidth;
  Square *startSquare = &pathfinder->_squareMap[start.y * width + start.x];
  heap_insert(pathfinder->openSet, startSquare);

  Square *currentSquare = heap_get(pathfinder->openSet);
  memcpy(&pathfinder->_end, &end, sizeof(end));

  printf(">> heap->size: %zu \n", pathfinder->openSet->size);

  while (currentSquare != NULL) {
    // Agregar a closeSet
    currentSquare->inCloseSet = true;

    // Verificar si es end.
    ui16Point currentPoint = (ui16Point){
        .x = currentSquare->x,
        .y = currentSquare->y,
    };
    if (check_equal_points_ui16(currentPoint, end)) {
      break;
    }

    // si no. Evaluar vecinos y agregarlos a openSet
    _evaluate_square_neighbours(pathfinder, currentPoint);

    // obtener el nuevo Square
    currentSquare = heap_get(pathfinder->openSet);
  }

  return currentSquare;
}

AC void pathfider_reset(Pathfinder *const pathfinder) {
  if (pathfinder) {
    for (size_t i = 0; i < pathfinder->_squareMapHeight; ++i) {
      for (size_t j = 0; j < pathfinder->_squareMapWidth; ++j) {
        size_t index = i * pathfinder->_squareMapWidth + j;
        pathfinder->_squareMap[index].realCost = 0;
        pathfinder->_squareMap[index].heuristicCost = 0;
        pathfinder->_squareMap[index].totalCost = 0;

        pathfinder->_squareMap[index].inOpenSet = false;
        pathfinder->_squareMap[index].inCloseSet = false;
      }
    }
    heap_reset_buffer(pathfinder->openSet);
  }
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

static void _initialize_square_map(Pathfinder *const pathfinder,
                                   const Map *const map) {
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
          .inOpenSet = false,
          .inCloseSet = false,
          .walkable = map->buffer[index] != -1,
          .parent = NULL,
      };
      pathfinder->_squareMap[index] = square;
    }
  }

  pathfinder->_squareMapWidth = map->width;
  pathfinder->_squareMapHeight = map->height;
}

static void _evaluate_square_neighbours(Pathfinder *const pathfinder,
                                        ui16Point currentPoint) {
  size_t width = pathfinder->_squareMapWidth;
  size_t height = pathfinder->_squareMapHeight;

  // UP
  if (currentPoint.y > 0) {
    _evaluate_square_by_direction(pathfinder, currentPoint,
                                  SQUARE_DIRECTION_UP);
  }

  // RIGHT
  if (currentPoint.x < (width - 1)) {
    _evaluate_square_by_direction(pathfinder, currentPoint,
                                  SQUARE_DIRECTION_RIGHT);
  }

  // DOWN
  if (currentPoint.y < (height - 1)) {
    _evaluate_square_by_direction(pathfinder, currentPoint,
                                  SQUARE_DIRECTION_DOWN);
  }

  // LEFT
  if (currentPoint.x > 0) {
    _evaluate_square_by_direction(pathfinder, currentPoint,
                                  SQUARE_DIRECTION_LEFT);
  }
}

static void _update_and_insert_openSet(Pathfinder *const pathfinder,
                                       Square *currentSquare,
                                       Square *parentSquare) {
  ui16Point currentPoint = (ui16Point){
      .x = currentSquare->x,
      .y = currentSquare->y,
  };
  ui16Point endPoint = pathfinder->_end;
  uint32_t realCost = parentSquare->realCost + 1;
  uint32_t heuristicCost = manhattan_distance_ui16(currentPoint, endPoint);
  uint32_t totalCost = realCost + heuristicCost;

  if (!currentSquare->inOpenSet || currentSquare->totalCost > totalCost) {
    currentSquare->realCost = realCost;
    currentSquare->heuristicCost = heuristicCost;
    currentSquare->totalCost = totalCost;
    currentSquare->parent = parentSquare;
  }

  if (!currentSquare->inOpenSet) {
    currentSquare->inOpenSet = true;
    heap_insert(pathfinder->openSet, currentSquare);
  }
}

static void _evaluate_square_by_direction(Pathfinder *const pathfinder,
                                          ui16Point parentPoint,
                                          SquareDirectionType type) {
  size_t index = 0;
  size_t width = pathfinder->_squareMapWidth;

  switch (type) {
    case SQUARE_DIRECTION_UP:
      index = (parentPoint.y - 1) * width + parentPoint.x;
      break;
    case SQUARE_DIRECTION_RIGHT:
      index = parentPoint.y * width + (parentPoint.x + 1);
      break;
    case SQUARE_DIRECTION_DOWN:
      index = (parentPoint.y + 1) * width + parentPoint.x;
      break;
    case SQUARE_DIRECTION_LEFT:
      index = parentPoint.y * width + (parentPoint.x - 1);
      break;
  }

  Square *currentSquare = &pathfinder->_squareMap[index];
  Square *parentSquare =
      &pathfinder->_squareMap[parentPoint.y * width + parentPoint.x];
  if (!currentSquare->inCloseSet && currentSquare->walkable) {
    _update_and_insert_openSet(pathfinder, currentSquare, parentSquare);
  }
}
