#include <string.h>

#include "include/config.h"
#include "include/heap.h"
#include "include/memory.h"
#include "include/pathfinder.h"

// *************************************************
// Static functions definition.
// *************************************************
static Node *_nodeMap[AC_MAX_BUFFER_SIZE];
static Heap *_openSet = NULL;

static int _cmp(const void *const a, const void *const b);
static bool _load_local_variables(const Map **const map);
static bool _load_nodeMap(const Map **const map);
static void _unload_local_variables(void);

// *************************************************
// Public functions implementation.
// *************************************************
Pathfinder *pathfinder_create(const Map **const map) {
  Pathfinder *pathfinder = NULL;
  Result result = memory_make_alloc(sizeof(Pathfinder));
  if (result.code == ERROR_CODE_OK) {
    pathfinder = result.data;
    pathfinder->array = NULL;
    pathfinder->size = 0;
    if (_load_local_variables(map)) {
      memory_free_container((void **)&pathfinder);
    }
  }

  return pathfinder;
}

void pathfinder_destroy(Pathfinder *pathfinder) {
  _unload_local_variables();
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
static bool _load_local_variables(const Map **const map) {
  bool hasError = _load_nodeMap(map);

  if (!hasError) {
    _openSet = heap_create(AC_MAX_BUFFER_SIZE, _cmp);
    hasError = _openSet == NULL;
  }

  return hasError;
}

static bool _load_nodeMap(const Map **const map) {
  bool hasError = false;

  size_t errorIndex = 0;
  for (size_t i = 0; i < AC_MAX_BUFFER_SIZE; ++i) {
    Result result = memory_make_alloc(sizeof(Node));
    if (result.code == ERROR_CODE_OK) {
      _nodeMap[i] = result.data;
    } else {
      errorIndex = i;
      hasError = true;
      break;
    }
  }

  if (hasError) {
    for (size_t i = 0; i < errorIndex; ++i) {
      memory_free_container((void **)&_nodeMap[i]);
    }
  }

  return hasError;
}

static void _unload_local_variables(void) {
  if (_nodeMap[0] != NULL) {
    for (size_t i = 0; i < AC_MAX_BUFFER_SIZE; ++i) {
      memory_free_container((void **)&_nodeMap[i]);
    }
  }

  if (_openSet != NULL) {
    heap_destroy(_openSet);
  }
}
