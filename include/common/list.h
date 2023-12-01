#ifndef __LIST_H
#define __LIST_H

typedef struct List List;

List* List_Construct(int initialCapacity, int itemSizeBytes);

void List_Destruct(List* list);

void List_Append(List* list, void* element);

void* List_Access(List* list, int index);

int List_Size(List* list);

#endif