#include <__stddef_size_t.h>

#include "include/heap_node.h"
#include "include/memory.h"

// *************************************************
// Static functions declaration.
// *************************************************
void _swap(Node **a, Node **b);
void _heapifyUp(HeapNode *const heapNode);
void _heapifyDown(HeapNode *const heapNode);

// *************************************************
// Public functions implementation.
// *************************************************
HeapNode *heap_node_create(size_t size) {
  HeapNode *heapNode = NULL;
  Result result = memory_make_alloc(sizeof(HeapNode));
  if (result.code == ERROR_CODE_OK) {
    heapNode = result.data;

    result = memory_make_alloc(size);
    if (result.code == ERROR_CODE_OK) {
      heapNode->buffer = result.data;
      heapNode->size = 0;
      heapNode->capacity = size;
    } else {
      void *tmp = heapNode;
      memory_free_container(tmp);
    }
  }

  return heapNode;
}

void heap_node_insert(HeapNode *const heapNode, Node *node) {
  size_t index = heapNode->size;
  heapNode->buffer[index] = node;
  _heapifyUp(heapNode);
  ++heapNode->size;
}

Node *heap_node_get_min(HeapNode *const heapNode) {
  Node *node = NULL;

  if (heapNode != NULL && heapNode->size > 0) {
    size_t size = heapNode->size;
    node = heapNode->buffer[0];
    heapNode->buffer[0] = heapNode->buffer[size - 1];
    --heapNode->size;
    _heapifyDown(heapNode);
  }

  return node;
}

void heap_node_destroy(HeapNode *heap) {
  if (heap != NULL) {
    void *tmp = heap->buffer;
    memory_free_container(&tmp);
    tmp = heap;
    memory_free_container(&tmp);
  }
}
// *************************************************
// Static functions implementation.
// *************************************************
void _swap(Node **a, Node **b) {
  Node *tmp = *a;
  *a = *b;
  *b = tmp;
}
void _heapifyUp(HeapNode *const heapNode) {
  size_t index = heapNode->size;

  while (index) {
    size_t index = heapNode->size;
    size_t parent = (index - 1) / 2;

    Node *currentNode = heapNode->buffer[index];
    Node *parentNode = heapNode->buffer[parent];
    if (currentNode->totalCost < parentNode->totalCost) {
      _swap(&currentNode, &parentNode);
    }

    index = parent;
  }
}
void _heapifyDown(HeapNode *const heapNode) {
  bool exit = !(heapNode->size > 0);
  size_t index = 0;

  while (!exit) {
    size_t leftIndex = (2 * index) + 1;
    size_t rightIndex = (2 * index) + 2;

    Node *node = heapNode->buffer[index];
    uint32_t totalCost = node->totalCost;
    
    Node *leftNode = heapNode->buffer[leftIndex];
    Node *rightNode = heapNode->buffer[rightIndex];

    if (leftIndex < heapNode->size && leftNode->totalCost < node->totalCost) {
      index = leftIndex;
      totalCost = leftNode->totalCost;
    }

    if (rightIndex < heapNode->size && rightNode->totalCost < totalCost) {
      index = rightIndex;
      totalCost = rightNode->totalCost;
    }

    exit = index != leftIndex && index != rightIndex;
  }
}
