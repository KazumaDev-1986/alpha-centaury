#include "include/memory.h"
#if defined(__linux__) || defined(__APPLE__)
#define _POSIX_C_SOURCE 200809L
#endif

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
static void _init_file_reader(FileReader *const fileReader, ErrorCode code);
static bool _has_error_read_lines(char *text, Map *const map);
static bool _has_error_read_token(char *line, Map *const map);
static bool _has_error_buffer_size(const Map *const map);
static char *_strtok(char *str, char *delim, char **context);

// *************************************************
// Public functions implementation.
// *************************************************
FileReader file_data(const char *fileName) {
  FileReader fileReader = {0};
  _init_file_reader(&fileReader, ERROR_CODE_UNDEFINED);

  if (fileName != NULL && FileExists(fileName)) {
    char *text = LoadFileText(fileName);
    if (_has_error_read_lines(text, &(fileReader.map))) {
      fileReader.errorCode = ERROR_CODE_FILE_NOT_VALID;
#if defined(AC_DEBUG)
      trace_map_size_exceeds(fileName, fileReader.map.height,
                             fileReader.map.width);
#endif
    } else {
      fileReader.errorCode = ERROR_CODE_OK;
    }
    UnloadFileText(text);
  } else {
    fileReader.errorCode = ERROR_CODE_FILE_NOT_FOUND;
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
  if (fileReader != NULL) {
    return;
  }

  memset(fileReader->map.buffer, AC_EMPTY_TOKEN,
         AC_MAX_BUFFER_SIZE * sizeof(int16_t));
  fileReader->map.height = 0;
  fileReader->map.width = 0;
  fileReader->errorCode = code;
}

static bool _has_error_read_lines(char *text, Map *map) {
  bool hasError = false;

  if (text != NULL && map != NULL) {
    char *context = NULL;
    char *line = _strtok(text, "\n", &context);

    while (!hasError && line != NULL) {
      if (_has_error_read_token(line, map)) {
        hasError = true;
        break;
      } else {
        line = _strtok(NULL, "\n", &context);
        map->height += 1;
        hasError = _has_error_buffer_size(map);
      }
    }
  }

  return hasError;
}

static bool _has_error_read_token(char *line, Map *map) {
  bool hasError = false;

  if (line != NULL && map != NULL) {
    char *context = NULL;
    char *token = _strtok(line, ",", &context);

    uint16_t j = 0;
    while (!hasError && token != NULL) {
      size_t index = map->height * map->width + j++;
      if (index >= AC_MAX_BUFFER_SIZE) {
        hasError = true;
        break;
      }
      int16_t *tmp = &map->buffer[index];
      *tmp = TextToInteger(token);
      token = _strtok(NULL, ",", &context);
      if (map->height == 0) {
        map->width += 1;
      }
      hasError = _has_error_buffer_size(map);
    }
  }

  return hasError;
}

static bool _has_error_buffer_size(const Map *const map) {
  return map != NULL ? (map->width * map->height) >= AC_MAX_BUFFER_SIZE : true;
}

static char *_strtok(char *str, char *delim, char **context) {
  char *ptr = NULL;
  if (str != NULL && delim != NULL && context != NULL) {
#if defined(__WIN32) || defined(_WIN64)
    ptr = strtok_s(str, delim, context);
#else
    ptr = strtok_r(str, delim, context);
#endif
  }

  return ptr;
}
