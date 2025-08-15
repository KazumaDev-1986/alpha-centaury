#include <stdlib.h>

#include "include/heap_node.h"
#include "include/memory.h"

// *************************************************
// Static functions definition.
// *************************************************

void _swap(void **a, void **b);
void _heapifyUp(Heap *const heap);
void _heapifyDown(Heap *const heap);

// *************************************************
// Public functions implementation.
// *************************************************
Heap *heap_create(size_t capacity, HeapCompare cmp) {
  Heap *heap = NULL;

  Result result = memory_make_alloc(sizeof(Heap));
  if (result.code == ERROR_CODE_OK) {
    heap = result.data;
    result = memory_make_alloc(sizeof(void *) * capacity);
    if (result.code == ERROR_CODE_OK) {
      heap->buffer = result.data;
      heap->size = 0;
      heap->capacity = capacity;
      heap->_cmp = cmp;
    } else {
      void *tmp = heap;
      memory_free_container(&tmp);
      heap = NULL;
    }
  }

  return heap;
}

void heap_insert(Heap *const heap, void *ptr) {
  if (heap != NULL && heap->size < heap->capacity) {
    size_t index = heap->size;
    heap->buffer[index] = ptr;
    _heapifyUp(heap);
    ++heap->size;
  }
}

void *heap_get_min(Heap *const heap) {
  void *ptr = NULL;

  if (heap != NULL && heap->size > 0) {
    ptr = heap->buffer[0];
    _swap(&heap->buffer[0], &heap->buffer[heap->size - 1]);
    --heap->size;
    _heapifyDown(heap);
  }

  return ptr;
}

void heap_destroy(Heap *heap) {
  if (heap != NULL) {
    if (heap->buffer != NULL) {
      memory_free_container((void **)&heap->buffer);
    }
    void *tmp = heap;
    memory_free_container(&tmp);
  }
}
// *************************************************
// Static functions implementation.
// *************************************************
void _swap(void **a, void **b) {
  void *tmp = *a;
  *b = *a;
  *a = tmp;
}

void _heapifyUp(Heap *const heap) {
  size_t index = heap->size;
  HeapCompare cmp = heap->_cmp;
  while (index > 0) {
    size_t parent = (index - 1) / 2;

    if (cmp(heap->buffer[parent], heap->buffer[index]) > 0) {
      _swap(&heap->buffer[parent], &heap->buffer[index]);
    }
    index = parent;
  }
}

void _heapifyDown(Heap *const heap) {

  HeapCompare cmp = heap->_cmp;
  size_t index = 0;
  size_t leftIndex = (index * 2) + 1;
  size_t rightIndex = (index * 2) + 2;

  void *evalute = heap->buffer[index];

  if (leftIndex < heap->size && cmp(heap->buffer[leftIndex], evalute) < 0) {
    evalute = heap->buffer[leftIndex];
  }

  if (rightIndex < heap->size && cmp(heap->buffer[rightIndex], evalute) < 0) {
    evalute = heap->buffer[rightIndex];
  }

  if (cmp(heap->buffer[index], evalute) != 0) {
    // TODO
  }
}
