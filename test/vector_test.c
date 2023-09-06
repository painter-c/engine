#include "criterion/criterion.h"
#include "math/vector.h"

// UTILITY FUNCTIONS

float min(float a, float b) {
    return a < b ? a : b;
}

float max(float a, float b) {
    return a > b ? a : b;
}

int close(float a, float b) {
    return (max(a,b) - min(a, b)) < 0.01;
}

int vec3_equal(vec3 a, vec3 b) {
    return close(a.x,b.x) && 
           close(a.y,b.y) &&
           close(a.z,b.z);
}

// TEST CASES

Test(operations, can_add_two_vectors) {
    vec3 a = {1,1,1};
    vec3 b = {2,2,2};
    vec3 expected = {3,3,3};
    
    vec3 result = vec3_add(a, b);

    cr_assert(
        vec3_equal(result, expected),
        "Expected result to be {3,3,3}"
    );
}

Test(operations, can_subtract_two_vectors) {
    vec3 a = {1,1,1};
    vec3 b = {2,2,2};
    vec3 expected = {1,1,1};

    vec3 result = vec3_subtract(b, a);

    cr_assert(
        vec3_equal(result, expected),
        "Expected result to be {1,1,1}"
    );
}

Test(operations, can_multiply_vector_by_scalar) {
    vec3 v = {1,1,1};
    float s = 2;
    vec3 expected = {2,2,2};

    vec3 result = vec3_scale(v, s);

    cr_assert(
        vec3_equal(result, expected),
        "Expected result to be {2,2,2}"
    );
}

Test(operations, can_take_dot_product_of_vectors) {
    vec3 a = {1,1,1};
    vec3 b = {2,2,2};
    float expected = 6;

    float result = vec3_dot(a, b);

    cr_assert(
        result == expected,
        "Expected dot product to be 6"
    );
}

Test(operations, can_take_cross_product_of_vectors) {
    vec3 a = {2, 1, 1};
    vec3 b = {1, 1, 2};
    vec3 expected = {1,-3, 1};

    vec3 result = vec3_cross(a, b);

    cr_assert(
        vec3_equal(result, expected),
        "Expected a x b to be {1, -3, 1}"
    );
}

Test(operations, can_calc_magnitude_of_vector) {
    vec3 v = {1, 2, 3};
    float expected = 3.742; // = sqrt(1^2+2^2+3^2)

    float result = vec3_magnitude(v);

    cr_assert(
        close(result, expected),
        "Expected result to be ~= 3.742"
    );
}

Test(operations, can_normalize_vectors) {
    vec3 v = {1,1,1};
    vec3 expected = {.577, .577, .577};

    vec3 result = vec3_norm(v);

    cr_assert(
        vec3_equal(result, expected),
        "Expected result to be {.577, .577, .577}"
    );
}