#ifndef __LIST_H
#define __LIST_H

#include <stddef.h>

typedef struct List List;

List* list_new(size_t initialCapacity, size_t itemSizeBytes);

void list_delete(List* list);

void list_append(List* list, void* item);

void* list_access(List* list, size_t index);

// Passing a pointer to an item that is an incorrect size in bytes results 
// in undefined behaviour.
void list_assign(List* list, size_t index, void* item);

int list_size(List* list);

#endif