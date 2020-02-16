#include "std/heap.h"

typedef struct Heap {
  ArrayT *array;
  PtrArrayT *heap;
} HeapT;

static inline size_t LeftChildIndex(size_t i) {
  return (i + 1) * 2 - 1;
}

static inline size_t RightChildIndex(size_t i) {
  return (i + 1) * 2;
}

static inline size_t ParentIndex(size_t i) {
  return (i - 1) / 2;
}

PtrT HeapTop(HeapT *self) {
  return (self->heap->size > 0) ? PtrArrayGetFast(self->heap, 0) : NULL;
}

PtrT HeapPop(HeapT *self) {
  PtrT item = HeapTop(self);

  if (item) {
    PtrArrayRemoveFast(self->heap, 0);

  }
  
  return item;
}

ArrayT *HeapPush(ArrayT *heap, PtrT item) {
}

ArrayT *Heapify(ArrayT *array) {
}
