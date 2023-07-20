#include "utils/string.h"
#include "stdio.h"
#include "assert.h"

int main() {

    // Can move a stack string onto the heap
    char example[] = "example";
    char* s1 = su_heapify(example);

    assert(strcmp(example, s1) == 0);

    // Can append a string to another string
    char* s2 = su_append(s1, " append");

    assert(strcmp(s2, "example append") == 0);

    printf("All tests passed");
}