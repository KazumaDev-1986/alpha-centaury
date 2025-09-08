#include <stdlib.h>
#include <string.h>

#include "include/heap.h"
#include "include/memory.h"

// *************************************************
// Static functions definition.
// *************************************************

static void _swap(void **a, void **b);
static void _heapifyUp(Heap *const heap, size_t index);
static void _heapifyDown(Heap *const heap);

// *************************************************
// Public functions implementation.
// *************************************************
Heap *heap_create(size_t capacity, HeapCompare cmp) {
  Heap *heap = NULL;

  if (cmp == NULL)
    return heap;

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
      memory_free_container((void **)&heap);
      heap = NULL;
    }
  }

  return heap;
}

void heap_insert(Heap *const heap, void *ptr) {
  if (heap != NULL && heap->size < heap->capacity) {
    size_t index = heap->size;
    heap->buffer[index] = ptr;
    _heapifyUp(heap, heap->size);
    ++heap->size;
  }
}

void *heap_get(Heap *const heap) {
  void *ptr = NULL;

  if (heap != NULL && heap->size > 0) {
    ptr = heap->buffer[0];
    _swap(&heap->buffer[0], &heap->buffer[heap->size - 1]);
    --heap->size;
    _heapifyDown(heap);
  }

  return ptr;
}

void heap_destroy(Heap **ptrHeap) {
  if (ptrHeap && *ptrHeap) {
    if ((*ptrHeap)->buffer != NULL) {
      memory_free_container((void **)&(*ptrHeap)->buffer);
    }
    memory_free_container((void **)ptrHeap);
  }
}

void heap_reset_buffer(Heap *const heap) { heap->size = 0; }

// *************************************************
// Static functions implementation.
// *************************************************
static void _swap(void **a, void **b) {
  void *tmp = *a;
  *a = *b;
  *b = tmp;
}

static void _heapifyUp(Heap *const heap, size_t index) {
  HeapCompare cmp = heap->_cmp;
  while (index > 0) {
    size_t parent = (index - 1) / 2;

    if (cmp(heap->buffer[parent], heap->buffer[index]) > 0) {
      _swap(&heap->buffer[parent], &heap->buffer[index]);
    }
    index = parent;
  }
}

static void _heapifyDown(Heap *const heap) {
  HeapCompare cmp = heap->_cmp;
  size_t index = 0;
  size_t evaluateIndex = index;

  while (heap->size > 0) {
    evaluateIndex = index;
    size_t leftIndex = (index * 2) + 1;
    size_t rightIndex = (index * 2) + 2;

    if (leftIndex < heap->size &&
        cmp(heap->buffer[leftIndex], heap->buffer[evaluateIndex]) < 0) {
      evaluateIndex = leftIndex;
    }

    if (rightIndex < heap->size &&
        cmp(heap->buffer[rightIndex], heap->buffer[evaluateIndex]) < 0) {
      evaluateIndex = rightIndex;
    }

    if (index != evaluateIndex) {
      _swap(&heap->buffer[index], &heap->buffer[evaluateIndex]);
      index = evaluateIndex;
    } else {
      break;
    }
  }
}
