#include "include/memory.h"
#include "include/raylib.h"

ResultMemory memory_make_alloc(unsigned int size) {
  ResultMemory result = {0};
  result.code = ERROR_CODE_OK;

  void *ptr = MemAlloc(size);
  if (!ptr) {
    TraceLog(LOG_DEBUG, "MemAlloc failed");
    result.code = ERROR_CODE_OUT_OF_MEMORY;
  } else {
    result.data = ptr;
  }

  return result;
}
