#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "include/memory.h"
#include "include/pathfinder.h"
#include "include/types.h"

// *************************************************
// Static functions && variables definition.
// *************************************************
static Node **_grid = NULL;
static ui16Point *_openSet = NULL;
static ui16Point _dimension = {0};

static void _initialize_dimension(const Map *const map);
static bool _initialize_grid(const Map *const map);
static bool _initialize_openSet(void);
static void *_load_pointer(size_t size);
static void _unload_internal_data(void);
static void _unload_pointer(void *ptr);
static Node *_create_node(uint16_t value, ui16Point point);

static Node *_get_node_by_point(ui16Point point);

static Node *_search_path(ui32Point start, ui32Point end);

// *************************************************
// Public functions implementation.
// *************************************************
Pathfinder *pathfinder_create(const Map *const map, ui16Point start,
                              ui16Point end) {
  Pathfinder *pathfinder = NULL;

  _initialize_dimension(map);
  bool hasGridError = _initialize_grid(map);
  bool hasOpenSetError = _initialize_openSet();

  if (!hasGridError && !hasOpenSetError) {
    // TODO
  }

  _unload_internal_data();
  return pathfinder;
}
// *************************************************
// Static functions implementation.
// *************************************************
static Node *_search_path(ui32Point start, ui32Point end) {
  // TODO
}

static Node *_get_node_by_point(ui16Point point) {
  Node *node = NULL;

  for (uint16_t i = 0; node == NULL && i < _dimension.y; ++i) {
    for (uint16_t j = 0; j < _dimension.y; ++j) {
      size_t index = i * _dimension.x + j;

      if (i == _grid[index]->point.y && j == _grid[index]->point.x) {
        node = _grid[index];
        break;
      }
    }
  }

  return node;
}

static void _initialize_dimension(const Map *const map) {
  _dimension.x = map->width;
  _dimension.y = map->height;
}

static bool _initialize_grid(const Map *const map) {
  bool hasError = false;
  size_t size = _dimension.x * _dimension.y;
  _grid = _load_pointer(size * sizeof(Node *));
  if (_grid != NULL) {
    uint16_t height = map->height;
    uint16_t width = map->width;

    for (uint16_t i = 0; !hasError && i < map->height; ++i) {
      for (uint16_t j = 0; j < map->width; ++j) {
        size_t index = i * width + j;
        ui16Point point = (ui16Point){.x = j, .y = i};
        Node *node = _create_node(map->buffer[index], point);
        if (node != NULL) {
          _grid[index] = node;
        } else {
          hasError = true;
          break;
        }
      }
    }
  } else {
    hasError = true;
  }

  return hasError;
}

static bool _initialize_openSet(void) {
  size_t size = _dimension.x * _dimension.y;
  _openSet = _load_pointer(size * sizeof(ui16Point));
  if (_openSet != NULL) {
    memset(_openSet, NULL, size * sizeof(ui16Point));
  }
  bool hasError = _openSet == NULL;
  return hasError;
}

static Node *_create_node(uint16_t value, ui16Point point) {
  Node *node = (Node *)_load_pointer(sizeof(Node));
  if (node != NULL) {
    memset(node, 0, sizeof(Node));
    memcpy(&(node->point), &point, sizeof(ui16Point));
    node->value = value;
  }

  return node;
}

static void *_load_pointer(size_t size) {
  void *ptr = NULL;
  Result result = memory_make_alloc(size);
  if (result.code == ERROR_CODE_OK) {
    ptr = result.data;
  }

  return ptr;
}

static void _unload_internal_data(void) {
  if (_grid != NULL) {
    size_t size = _dimension.x * _dimension.y;
    for (size_t i = 0; i < size; ++i) {
      _unload_pointer(_grid[i]);
    }
    _unload_pointer(_grid);
  }
  _unload_pointer(_openSet);
  memset(&_dimension, 0, sizeof(ui16Point));
}

static void _unload_pointer(void *ptr) {
  if (ptr != NULL) {
    void *tmp = ptr;
    memory_free_container(&tmp);
  }
}
