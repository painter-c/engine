#include "criterion/criterion.h"
#include "common/list.h"

Test(integration, can_append_list_with_item) {
    struct S {
        float a;
        float b;
    };
    struct S item1 = {1.0f, 1.0f};

    List* list = List_Construct(5, sizeof(struct S));
    List_Append(list, &item1);

    cr_assert(
        List_Size(list) == 1,
        "Expected list size to be 1 after append"
    );
}

Test(integration, list_expands_when_full) {
    float a = 1.0;
    List* list = List_Construct(1, sizeof(float));
    
    List_Append(list, &a);
    List_Append(list, &a);

    cr_assert(
        List_Size(list) == 2,
        "Expected list to expand to accomodate second item"
    );
}

Test(integration, can_access_list_items) {
    float a = 1.0;
    List* list = List_Construct(1, sizeof(float));

    List_Append(list, &a);
    float* a_accessed = (float*) List_Access(list, 0);
    
    cr_assert(
        *a_accessed == 1.0,
        "Expected value to be 1.0"
    );
}

Test(integration, accessing_invalid_index_returns_null) {
    List* list = List_Construct(5, sizeof(int));

    int* bad_index = List_Access(list, 5);

    cr_assert(
        bad_index == NULL,
        "Expected return value from bad index to be NULL"
    );
}