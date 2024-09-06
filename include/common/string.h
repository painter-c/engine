#ifndef __STRING_H
#define __STRING_H

#include <string.h>
#include <stdlib.h>

// Moves a stack string onto the heap.
char* str_heapify(const char* str);

// Resize a block of memory to fit the string it contains.
char* str_resize_fit(char* str);

// Appends a string to another string. The function will reallocate 
// the target pointer to fit both strings, and then copy the second 
// string into target.
char* str_append(char* target, const char* str);

#endif