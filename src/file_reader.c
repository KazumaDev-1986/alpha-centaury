#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "include/config.h"
#include "include/file_reader.h"
#include "include/raylib.h"

#if defined(AC_DEBUG)
#include "include/trace_utils.h"
#endif

#define AC_EMPTY_TOKEN 0

// *************************************************
// Static functions definition.
// *************************************************
#if defined(__cplusplus)
extern "C" {
#endif

static void _init_file_reader(Map *const map);
static bool _read_lines(char *text, Map *const map);
static bool _read_token(char *line, Map *const map);
static bool _is_buffer_size_valid(const Map *const map);

#if defined(__cplusplus)
}
#endif
// *************************************************
// Public functions implementation.
// *************************************************
Map get_map_file(const char *fileName) {
  Map map = {0};
  _init_file_reader(&map);

  if (FileExists(fileName)) {
    char *text = LoadFileText(fileName);
    if (_read_lines(text, &map)) {
      _init_file_reader(&map);
#if defined(AC_DEBUG)
      trace_map_size_exceeds(fileName);
#endif
    }
    UnloadFileText(text);
  } else {
#if defined(AC_DEBUG)
    trace_file_not_found(fileName);
#endif
  }

  return map;
}
// *************************************************
// Static functions implementation.
// *************************************************
static void _init_file_reader(Map *const map) {
  memset(map->buffer, AC_EMPTY_TOKEN, AC_BUFFER_SIZE * sizeof(uint32_t));
  map->height = 0;
  map->width = 0;
}

static bool _read_lines(char *text, Map *map) {
  char *context = NULL;
  char *line = strtok_s(text, "\n", &context);
  bool hasError = false;

  while (line != NULL) {
    if (_read_token(line, map)) {
      hasError = true;
      break;
    } else {
      line = strtok_s(NULL, "\n", &context);
      map->height += 1;
      if (!_is_buffer_size_valid(map)) {
        hasError = true;
        break;
      }
    }
  }

  return hasError;
}

static bool _read_token(char *line, Map *map) {
  char *context = NULL;
  char *token = strtok_s(line, ",", &context);
  bool hasError = false;

  while (token != NULL) {
    uint32_t *tmp = map->buffer;
    while (*tmp != AC_EMPTY_TOKEN) ++tmp;
    *tmp = TextToInteger(token);
    token = strtok_s(NULL, ",", &context);
    if (map->height == 0) map->width += 1;
    if (!_is_buffer_size_valid(map)) {
      hasError = true;
      break;
    }
  }

  return hasError;
}

static bool _is_buffer_size_valid(const Map *const map) {
  return (map->width * map->height) <= AC_BUFFER_SIZE;
}
