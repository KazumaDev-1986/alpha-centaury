#include <stdint.h>
#include <string.h>

#include "include/config.h"
#include "include/heap.h"
#include "include/memory.h"
#include "include/pathfinder.h"

// *************************************************
// Static functions definition.
// *************************************************
static int _cmp(const void *const a, const void *const b);
static bool _load_internal_data(Pathfinder *const pathfinder,
                                const Map **const map);
static bool _load_nodeMap(Pathfinder *const pathfinder, const Map **const map);
static void _unload_internal_data(Pathfinder *const pathfinder);
static Node *_search_path(Pathfinder *const pathfinder, Node *end);
static void _evaluate_and_add_openSet(Pathfinder *const pathfinder,
                                      Node *const node,
                                      DirectionType direction);

// *************************************************
// Public functions implementation.
// *************************************************
Pathfinder *pathfinder_create(const Map **const map) {
  Pathfinder *pathfinder = NULL;
  Result result = memory_make_alloc(sizeof(Pathfinder));
  if (result.code == ERROR_CODE_OK) {
    pathfinder = result.data;
    pathfinder->path = NULL;
    pathfinder->size = 0;
    if (_load_internal_data(pathfinder, map)) {
      memory_free_container((void **)&pathfinder);
    }
  }

  return pathfinder;
}

void pathfinder_search(Pathfinder *const pathfinder, ui32Point start,
                       ui32Point end) {
  // TODO: Validate pathfined data.

  uint16_t width = pathfinder->_width;
  uint16_t height = pathfinder->_height;
  Node *nodeStart = pathfinder->_nodeMap[start.y * width + start.x];
  Node *nodeEnd = pathfinder->_nodeMap[end.y * width + end.x];

  heap_insert(pathfinder->_openSet, nodeStart);

  // TODO: Search end.
  Node *path = _search_path(pathfinder, nodeEnd);
}

void pathfinder_destroy(Pathfinder *pathfinder) {
  _unload_internal_data(pathfinder);
  memory_free_container((void **)&pathfinder);
}

// *************************************************
// Static functions implementation.
// *************************************************
static int _cmp(const void *const a, const void *const b) {
  const Node *const tmpA = (const Node *const)a;
  const Node *const tmpB = (const Node *const)b;

  if (tmpA->totalCost < tmpB->totalCost)
    return -1;
  else if (tmpA->totalCost > tmpB->totalCost)
    return 1;
  else
    return 0;
}
static bool _load_internal_data(Pathfinder *const pathfinder,
                                const Map **const map) {
  bool hasError = _load_nodeMap(pathfinder, map);

  if (!hasError) {
    pathfinder->_openSet = heap_create(AC_MAX_BUFFER_SIZE, _cmp);
    hasError = pathfinder->_openSet == NULL;
  }

  return hasError;
}

static bool _load_nodeMap(Pathfinder *const pathfinder, const Map **const map) {
  bool hasError = false;

  size_t errorIndex = 0;
  for (size_t i = 0; i < AC_MAX_BUFFER_SIZE; ++i) {
    Result result = memory_make_alloc(sizeof(Node));
    if (result.code == ERROR_CODE_OK) {
      pathfinder->_nodeMap[i] = result.data;
    } else {
      errorIndex = i;
      hasError = true;
      break;
    }
  }

  if (hasError) {
    for (size_t i = 0; i < errorIndex; ++i) {
      memory_free_container((void **)&pathfinder->_nodeMap[i]);
    }
  }

  return hasError;
}

static void _unload_internal_data(Pathfinder *const pathfinder) {
  if (pathfinder->_nodeMap[0] != NULL) {
    for (size_t i = 0; i < AC_MAX_BUFFER_SIZE; ++i) {
      memory_free_container((void **)&pathfinder->_nodeMap[i]);
    }
  }

  if (pathfinder->_openSet != NULL) {
    heap_destroy(pathfinder->_openSet);
  }
}

static Node *_search_path(Pathfinder *const pathfinder, Node *end) {
  Node *path = NULL;
  uint16_t height = pathfinder->_height;
  uint16_t width = pathfinder->_width;

  while (path != NULL || _cmp(path, end) != 0) {
    Node *node = heap_get(pathfinder->_openSet);
    if (node == NULL) {
      break;
    }

    // Up
    if ((node->point.y - 1) >= 0) {
      _evaluate_and_add_openSet(pathfinder, node, DIRECTION_UP);
    }
    // Down
    if ((node->point.y + 1) < height) {
      _evaluate_and_add_openSet(pathfinder, node, DIRECTION_DOWN);
    }
    // Left
    if ((node->point.x - 1) >= 0) {
      _evaluate_and_add_openSet(pathfinder, node, DIRECTION_LEFT);
    }
    // Right
    if ((node->point.x + 1) < width) {
      _evaluate_and_add_openSet(pathfinder, node, DIRECTION_RIGHT);
    }
  }

  return path;
}
static void _evaluate_and_add_openSet(Pathfinder *const pathfinder,
                                      Node *const node,
                                      DirectionType direction) {

  size_t index = 0;
  uint16_t height = pathfinder->_height;
  uint16_t width = pathfinder->_width;

  switch (direction) {
  case DIRECTION_UP: {
    uint16_t i = node->point.y - 1;
    index = i * width + node->point.x;
    break;
  }
  case DIRECTION_RIGHT: {
    uint16_t j = node->point.x + 1;
    index = node->point.y * width + j;
    break;
  }
  case DIRECTION_DOWN: {
    uint16_t i = node->point.y + 1;
    index = i * width + node->point.x;
    break;
  }
  case DIRECTION_LEFT: {
    uint16_t j = node->point.x - 1;
    index = node->point.y * width + j;
    break;
  }
  default:
    break;
  }

  Node *n = pathfinder->_nodeMap[index];

  if (n->walkable && !n->inCloseSet) {
    if (n->inOpenSet) {
      // TODO
    } else {
      n->inOpenSet = true;
      heap_insert(pathfinder->_openSet, n);
    }
  }
}
