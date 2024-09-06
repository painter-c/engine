#include "criterion/criterion.h"
#include "common/list.h"

Test(integration, can_append_list_with_item) {
    struct S {
        float a;
        float b;
    };
    struct S item1 = {1.0f, 1.0f};

    List* list = list_new(5, sizeof(struct S));
    list_append(list, &item1);

    cr_assert(
        list_size(list) == 1,
        "Expected list size to be 1 after append"
    );
}

Test(integration, list_expands_when_full) {
    float a = 1.0;
    List* list = list_new(1, sizeof(float));
    
    list_append(list, &a);
    list_append(list, &a);

    cr_assert(
        list_size(list) == 2,
        "Expected list to expand to accomodate second item"
    );
}

Test(integration, can_access_list_items) {
    float a = 1.0;
    List* list = list_new(1, sizeof(float));

    list_append(list, &a);
    float* a_accessed = (float*) list_access(list, 0);
    
    cr_assert(
        *a_accessed == 1.0,
        "Expected value to be 1.0"
    );
}

Test(integration, accessing_invalid_index_returns_null) {
    List* list = list_new(5, sizeof(int));

    int* bad_index = list_access(list, 5);

    cr_assert(
        bad_index == NULL,
        "Expected return value from bad index to be NULL"
    );
}

Test(integration, can_assign_list_items) {
    List* list = list_new(1, sizeof(int));

    int n = 0;
    list_append(list, &n);

    int m = 5;
    list_assign(list, 0, &m);
    int* result = list_access(list, 0);

    cr_assert(*result == 4, "Expected array index 0 to be 5");
}