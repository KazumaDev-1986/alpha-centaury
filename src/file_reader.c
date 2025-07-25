#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "include/file_reader.h"
#include "include/raylib.h"
#include "include/config.h"

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

static void _init_file_reader(FileReader *const fileReader);
static bool _read_lines(char *text, FileReader *const fileReader);
static bool _read_token(char *line, FileReader *const fileReader);
static bool _is_buffer_size_valid(const FileReader *const fileReader);

#if defined(__cplusplus)
}
#endif
// *************************************************
// Public functions implementation.
// *************************************************
FileReader file_data(const char *fileName) {
  FileReader fileReader = {0};
  _init_file_reader(&fileReader);

  if (FileExists(fileName)) {
    char *text = LoadFileText(fileName);
    if (_read_lines(text, &fileReader)) {
      _init_file_reader(&fileReader);
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

  return fileReader;
}
// *************************************************
// Static functions implementation.
// *************************************************
static void _init_file_reader(FileReader *const fileReader) {
  memset(fileReader->buffer, AC_EMPTY_TOKEN, AC_BUFFER_SIZE * sizeof(uint32_t));
  fileReader->height = 0;
  fileReader->width = 0;
}

static bool _read_lines(char *text, FileReader *fileReader) {
  char *context = NULL;
  char *line = strtok_s(text, "\n", &context);
  bool hasError = false;

  while (line != NULL) {
    if (_read_token(line, fileReader)) {
      hasError = true;
      break;
    } else {
      line = strtok_s(NULL, "\n", &context);
      fileReader->height += 1;
      if (!_is_buffer_size_valid(fileReader)) {
        hasError = true;
        break;
      }
    }
  }

  return hasError;
}

static bool _read_token(char *line, FileReader *fileReader) {
  char *context = NULL;
  char *token = strtok_s(line, ",", &context);
  bool hasError = false;

  while (token != NULL) {
    uint32_t *tmp = fileReader->buffer;
    while (*tmp != AC_EMPTY_TOKEN) ++tmp;
    *tmp = TextToInteger(token);
    token = strtok_s(NULL, ",", &context);
    if (fileReader->height == 0) fileReader->width += 1;
    if (!_is_buffer_size_valid(fileReader)) {
      hasError = true;
      break;
    }
  }

  return hasError;
}

static bool _is_buffer_size_valid(const FileReader *const fileReader) {
  return (fileReader->width * fileReader->height) <= AC_BUFFER_SIZE;
}
