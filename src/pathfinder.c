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
static Node **_openSet = NULL;
static uint32_t _countOpenSet = 0;

static ui16Point _dimension = {0};
static ui16Point _start = {0};
static ui16Point _end = {0};

static void _dimension_initialize(const Map *const map);
static bool _grid_initialize(const Map *const map);
static bool _openSet_initialize(void);
static void _openSet_add_node(Node *node);
static Node *_openSet_get_for_lowest_total(void);

static void *_load_pointer(size_t size);
static void _unload_internal_data(void);
static void _unload_pointer(void *ptr);

static Node *_node_create(uint16_t value, ui16Point point);
static void _node_calculate_distance(Node *const node);

static Node *_grid_get_node_by_point(ui16Point point);

static Node *_search_path(void);

static uint32_t _heuristc_cost(ui16Point a, ui16Point b);

static void _node_evaluate(Node *const node);

static void _check_point_by_index(ui16Point point, size_t index);

// *************************************************
// Public functions implementation.
// *************************************************
Pathfinder *pathfinder_create(const Map *const map, ui16Point start,
                              ui16Point end) {
  Pathfinder *pathfinder = NULL;

  _dimension_initialize(map);
  bool hasGridError = _grid_initialize(map);
  bool hasOpenSetError = _openSet_initialize();

  memcpy(&_start, &start, sizeof(ui16Point));
  memcpy(&_end, &end, sizeof(ui16Point));

  if (!hasGridError && !hasOpenSetError) {
    // TODO
  }

  _unload_internal_data();
  return pathfinder;
}
// *************************************************
// Static functions implementation.
// *************************************************
static void _check_point_by_index(ui16Point point, size_t index) {
  Node *tmp = _grid[index];
  if (!tmp->inCloseSet && !tmp->inOpenSet && tmp->value != 0) {
    _node_calculate_distance(tmp);
    _openSet_add_node(tmp);
  }
}

static void _node_evaluate(Node *const node) {
  ui16Point point = node->point;

  // UP
  if (point.y - 1 >= 0) {
    size_t index = (point.y - 1) + _dimension.x + point.x;
    _check_point_by_index(point, index);
  }
  // RIGHT
  if (point.x + 1 < _dimension.x) {
    size_t index = point.y + _dimension.x + (point.x + 1);
    _check_point_by_index(point, index);
  }
  // DOWN
  if (point.y + 1 < _dimension.y) {
    size_t index = (point.y + 1) + _dimension.x + point.x;
    _check_point_by_index(point, index);
  }
  // LEFT
  if (point.x - 1 >= 0) {
    size_t index = point.y + _dimension.x + (point.x - 1);
    _check_point_by_index(point, index);
  }
}

static uint32_t _heuristc_cost(ui16Point a, ui16Point b) {
  int32_t dx = (int32_t)a.x - (int32_t)b.x;
  int32_t dy = (int32_t)a.y - (int32_t)b.y;

  if (dx < 0)
    dx = -dx;
  if (dy < 0)
    dy = -dy;

  return dx + dy;
}

static void _node_calculate_distance(Node *const node) {
  node->realCost = (node->parent == NULL ? 0 : node->realCost) + 1;
  node->heuristicCost = _heuristc_cost(node->point, _end);
  node->totalCost = node->realCost + node->heuristicCost;
}

static Node *_search_path(void) {

  Node *node = _openSet_get_for_lowest_total();
  while (node != NULL && !check_equal_points_ui16(node->point, _end)) {
    _node_calculate_distance(node);

    node->inCloseSet = true;
    node = _openSet_get_for_lowest_total();
  }

  return node;
}

static Node *_grid_get_node_by_point(ui16Point point) {
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

static void _dimension_initialize(const Map *const map) {
  _dimension.x = map->width;
  _dimension.y = map->height;
}

static bool _grid_initialize(const Map *const map) {
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
        Node *node = _node_create(map->buffer[index], point);
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

static bool _openSet_initialize(void) {
  size_t size = _dimension.x * _dimension.y * sizeof(Node *);
  _openSet = _load_pointer(size);
  if (_openSet != NULL) {
    memset(_openSet, NULL, size);
  }
  bool hasError = _openSet == NULL;
  return hasError;
}

static void _openSet_add_node(Node *node) {
  _openSet[_countOpenSet] = node;
  _openSet[_countOpenSet]->inOpenSet = true;
  ++_countOpenSet;
}

static Node *_openSet_get_for_lowest_total(void) {
  Node *node;
  uint32_t total = 9999999;
  uint32_t index = 0;

  // TODO: I need to improve this.
  for (uint32_t i = 0; i < _countOpenSet; ++i) {
    Node *tmp = _openSet[i];
    if (tmp->totalCost < total) {
      total = tmp->totalCost;
      node = tmp;
    }
  }

  return node;
}

static Node *_node_create(uint16_t value, ui16Point point) {
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
