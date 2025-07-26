#include <memory.h>
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

static void _init_file_reader(FileReader *const fileReader, ErrorCode code);
static bool _read_lines(char *text, Map *const map);
static bool _read_token(char *line, Map *const map);
static bool _is_buffer_size_valid(const Map *const map);
static char *_strtok(char *str, char *delim, char **context);

#if defined(__cplusplus)
}
#endif
// *************************************************
// Public functions implementation.
// *************************************************
FileReader file_data(const char *fileName) {
  FileReader fileReader = {0};
  _init_file_reader(&fileReader, ERROR_CODE_UNDEFINED);

  if (FileExists(fileName)) {
    char *text = LoadFileText(fileName);
    if (_read_lines(text, &(fileReader.map))) {
      _init_file_reader(&fileReader, ERROR_CODE_FILE_NOT_VALID);
#if defined(AC_DEBUG)
      trace_map_size_exceeds(fileName);
#endif
    } else {
      fileReader.errorCode = ERROR_CODE_OK;
    }
    UnloadFileText(text);
  } else {
#if defined(AC_DEBUG)
    trace_file_not_found(fileName);
#endif
  }

  return fileReader;
}
// *************************************************
// Static functions implementation.
// *************************************************
static void _init_file_reader(FileReader *const fileReader, ErrorCode code) {
  memset(fileReader->map.buffer, AC_EMPTY_TOKEN,
         AC_BUFFER_SIZE * sizeof(uint16_t));
  fileReader->map.height = 0;
  fileReader->map.width = 0;
  fileReader->errorCode = code;
}

static bool _read_lines(char *text, Map *map) {
  char *context = NULL;
  char *line = _strtok(text, "\n", &context);
  bool hasError = false;

  while (!hasError && line != NULL) {
    if (_read_token(line, map)) {
      hasError = true;
      break;
    } else {
      line = _strtok(NULL, "\n", &context);
      map->height += 1;
      hasError = !_is_buffer_size_valid(map);
    }
  }

  return hasError;
}

static bool _read_token(char *line, Map *map) {
  char *context = NULL;
  char *token = _strtok(line, ",", &context);
  bool hasError = false;

  uint16_t j = 0;
  while (!hasError && token != NULL) {
    uint16_t *tmp = &map->buffer[map->height * map->width + j++];
    *tmp = TextToInteger(token);
    token = _strtok(NULL, ",", &context);
    if (map->height == 0) {
      map->width += 1;
    }
    hasError = !_is_buffer_size_valid(map);
  }

  return hasError;
}

static bool _is_buffer_size_valid(const Map *const map) {
  return (map->width * map->height) <= AC_BUFFER_SIZE;
}

static char *_strtok(char *str, char *delim, char **context) {
  char *ptr = NULL;
#if defined(__WIN32) || defined(_WIN64)
  ptr = strtok_s(str, delim, context);
#else
  ptr = strtok_r(str, delim, context);
#endif

  return ptr;
}
