#include "include/memory.h"
#include "include/raylib.h"

#include <stddef.h>

Result memory_make_alloc(unsigned int size) {
  Result result = {0};
  result.code = ERROR_CODE_OK;

  void *ptr = MemAlloc(size);
  if (ptr == NULL) {
    result.code = ERROR_CODE_OUT_OF_MEMORY;
  } else {
    result.data = ptr;
  }

  return result;
}

void memory_free_container(void **const ptr) {
  if (ptr && *ptr) {
    MemFree(*ptr);
    *ptr = NULL;
  }
}
