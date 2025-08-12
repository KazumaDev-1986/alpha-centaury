#ifndef AC_HEAP_NODE_H
#define AC_HEAP_NODE_H

#include <stddef.h>

#include "config.h"
#include "types.h"

typedef struct {
  Node **buffer;
  size_t size;
  size_t capacity;
} HeapNode;

#if defined(__cplusplus)
extern "C" {
#endif

AC HeapNode *heap_node_create(size_t size);
AC void heap_node_insert(HeapNode *const heapNode, Node *node);
AC Node *heap_node_get_min(HeapNode *const heapNode);
AC void heap_node_destroy(HeapNode *heapNode);

#if defined(__cplusplus)
}
#endif

#endif  // AC_HEAP_NODE_H
