#include "str-util.h"

char* su_heapify(const char* str) {
    char* new = malloc((strlen(str) + 1) + sizeof(char));
    strcpy(new, str);

    return new;
}

char* su_resize_fit(char* str) {
    return realloc(str, (strlen(str) + 1) * sizeof(char));
}

char* su_append(char* target, const char* str) {
    int target_len = strlen(target);
    int new_len = target_len + strlen(str);

    char* result = realloc(target, sizeof(char) * new_len + 1);
    strcpy(result + target_len, str);

    return result;
}