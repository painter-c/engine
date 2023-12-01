#include "common/list.h"
#include <string.h>
#include <stdlib.h>

struct List {
    int size;
    int capacity;
    int initialCapacity;
    int itemSizeBytes;
    void* items;
};

List* List_Construct(int initialCapacity, int itemSizeBytes) {
    List* instance = malloc(sizeof(List));
    instance->size = 0;
    instance->capacity = initialCapacity;
    instance->initialCapacity = initialCapacity;
    instance->itemSizeBytes = itemSizeBytes;
    instance->items = malloc(initialCapacity * itemSizeBytes);
    return instance;
}

void List_Destruct(List* list) {
    free(list->items);
    free(list);
}

void _list_expand(List* list) {
    list->capacity = list->capacity + list->initialCapacity;
    list->items = realloc(list->items, list->capacity * list->itemSizeBytes);
}

void* _list_offset(List* list, int n) {
    return ((char*) list->items) + (n * list->itemSizeBytes);
}

void List_Append(List* list, void* item) {
    if (list->size == list->capacity) {
        _list_expand(list);
    } else {
        void* offset = _list_offset(list, list->size);
        memcpy(offset, item, list->itemSizeBytes);
    }
    list->size++;
}

void* List_Access(List* list, int index) {
    if (!(index < list->size)) {
        return NULL;
    } else {
        return _list_offset(list, index);
    }
}

int List_Size(List* list) {
    return list->size;
}