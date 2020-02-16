#ifndef __STD_HEAP_H__
#define __STD_HEAP_H__

#include "std/array.h"

PtrT HeapTop(ArrayT *heap);
PtrT HeapPop(ArrayT *heap);
ArrayT *HeapPush(ArrayT *heap, PtrT item);
ArrayT *Heapify(ArrayT *array);

#endif
