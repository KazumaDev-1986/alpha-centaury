#ifndef AC_HEAP_H
#define AC_HEAP_H

#include <stddef.h>

typedef int (*HeapCompare)(const void *const, const void *const);

typedef struct {
  void **buffer;
  size_t size;
  size_t capacity;
  HeapCompare _cmp;
} Heap;

#if defined(__cplusplus)
extern "C" {
#endif

Heap *heap_create(size_t capacity, HeapCompare cmp);
void heap_insert(Heap *const heap, void *ptr);
void *heap_get(Heap *const heap);
void heap_destroy(Heap **heap);

#if defined(__cplusplus)
}
#endif

#endif // AC_HEAP_H
