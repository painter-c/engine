#include "common/list.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct List {
    size_t size;
    size_t capacity;
    size_t initialCapacity;
    size_t itemSizeBytes;
    void* items;
};

List* list_new(size_t initialCapacity, size_t itemSizeBytes) {
    List* instance = malloc(sizeof(List));
    instance->size = 0;
    instance->capacity = initialCapacity;
    instance->initialCapacity = initialCapacity;
    instance->itemSizeBytes = itemSizeBytes;
    instance->items = malloc(initialCapacity * itemSizeBytes);
    return instance;
}

void list_delete(List* list) {
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

void list_append(List* list, void* item) {
    if (list->size == list->capacity) {
        _list_expand(list);
    } else {
        void* offset = _list_offset(list, list->size);
        memcpy(offset, item, list->itemSizeBytes);
    }
    list->size++;
}

void list_assign(List* list, size_t index, void* item) {
    assert(index < list->size);
    memcpy(_list_offset(list, index), item, list->itemSizeBytes);
}

void* list_access(List* list, size_t index) {
    if (!(index < list->size)) {
        return NULL;
    } else {
        return _list_offset(list, index);
    }
}

int list_size(List* list) {
    return list->size;
}