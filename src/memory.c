#include "include/memory.h"
#include "include/raylib.h"

Result memory_make_alloc(unsigned int size) {
  Result result = {0};
  result.code = ERR_OK;

  void *ptr = MemAlloc(size);
  if (!ptr) {
    TraceLog(LOG_DEBUG, "MemAlloc failed");
    result.code = ERR_OUT_OF_MEMORY;
  } else {
    result.data = ptr;
  }

  return result;
}
