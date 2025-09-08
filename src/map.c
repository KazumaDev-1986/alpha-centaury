#include <stdlib.h>
#include <string.h>

#include "include/file_reader.h"
#include "include/map.h"
#include "include/memory.h"
#include "include/trace_utils.h"

// *************************************************
// Public functions implementation.
// *************************************************
AC Map *map_load(const char *fileName) {
  Map *map = NULL;
  FileReader fileReader = file_reader_get_map(fileName);
  if (fileReader.errorCode != ERROR_CODE_OK) {
    return map;
  }

  Result result = memory_make_alloc(sizeof(Map));
  if (result.code != ERROR_CODE_OK) {
    return map;
  }

  map = (Map *)result.data;
  memcpy(map, &(fileReader.map), sizeof(fileReader.map));

#if defined(AC_DEBUG)
  trace_created("Map", fileName);
#endif
  return map;
}

AC void map_draw(const Map *const map) {
  // TODO
}

AC void map_unload(Map **ptr) {
  if (ptr && *ptr) {
    memory_free_container((void **)ptr);

#if defined(AC_DEBUG)
    trace_destroyed("Map", "");
#endif
  }
}
